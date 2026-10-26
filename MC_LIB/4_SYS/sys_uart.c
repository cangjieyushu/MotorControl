/**
 * @file    sys_uart.c
 * @brief   上位机通讯协议（自有协议）
 *          - 接收：DMA 循环 + 10ms 轮询搬运 + 拼帧
 *          - 发送：10ms 状态机 + DMA 单次发送
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "sys_uart.h"
#include "sys_task.h"
#include "hal_uart.h"           /* ring_buffer_* / UARTH_* inline 接口 */
#include "bsp_sys_dma.h"        /* g_uart_rx_buf / g_uart_tx_buf 等 */
#include "bsp_sys_gpio.h"
#include <string.h>

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */
ST_HMI_UART_CTRL Hmi_Uart_Ctrl = {
    .tx_flow     = HMI_TX_IDLE,
    .state.all   = 0U,
    .txdata_len  = 0U,
    .txdata_cnt  = 0U,
    .error_cnt   = 0U,
};

/* ---- 编号 / 帧头 ---- */
static uint8_t s_uart_num     = 5U;
static uint8_t s_uart_rx_head = 0xAAU;
static uint8_t s_uart_tx_head = 0xAEU;

/* ---- 接收拼帧状态 ---- */
static uint8_t s_rx_frame[HMI_RX_FRAME_LEN];
static uint8_t s_rx_index      = 0U;
static uint8_t s_frame_started = 0U;

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  10ms 轮询搬运 DMA 环形缓冲到软件环形缓冲
 */
void Uart_Rx_Poll_10ms(void)
{
    static uint16_t s_last_cndtr = UART_RX_BUF_SIZE;   /* 上次读到的 CNDTR */

    uint16_t curr_cndtr;
    uint16_t curr_pos;
    uint16_t new_cnt;
    uint16_t i;
    uint16_t idx;

    curr_cndtr = (uint16_t)UARTH_Rx_DMA_RemainCount();

    /* ① CNDTR 没变 → 10ms 内无新数据，直接返回 */
    if (curr_cndtr == s_last_cndtr)
    {
        return;
    }

    /* ② 计算当前绝对位置（remain==0 时表示正好满一圈，位置 = SIZE）*/
    curr_pos = (uint16_t)(UART_RX_BUF_SIZE - curr_cndtr);

    /* ③ 计算新增字节数（处理 DMA 缓冲回绕）*/
    if (curr_pos >= g_ring_dma_last_pos)
    {
        new_cnt = (uint16_t)(curr_pos - g_ring_dma_last_pos);
    }
    else
    {
        new_cnt = (uint16_t)((UART_RX_BUF_SIZE - g_ring_dma_last_pos) + curr_pos);
    }

    /* ④ 保护：10ms 内搬入超过一整圈（读得太慢），丢弃本次避免死循环 */
    if (new_cnt >= UART_RX_BUF_SIZE)
    {
        g_ring_dma_last_pos = curr_pos;
        s_last_cndtr        = curr_cndtr;
        return;
    }

    /* ⑤ 把新数据搬入软件环形缓冲 */
    for (i = 0U; i < new_cnt; i++)
    {
        idx = (uint16_t)((g_ring_dma_last_pos + i) % UART_RX_BUF_SIZE);
        (void)ring_buffer_put(g_uart_rx_buf[idx]);   /* 满自动丢弃 */
    }

    /* ⑥ 更新状态 */
    g_ring_dma_last_pos = curr_pos;
    s_last_cndtr        = curr_cndtr;
}

/**
 * @brief  CRC8 计算（poly=0x2F，初始值 = data）
 * @param  data  输入字节
 * @return CRC8 值
 */
uint8_t Hmi_Crc8(uint8_t data)
{
    uint8_t i;
    uint8_t crc = data;
    for (i = 8U; i > 0U; i--)
    {
        if (crc & 0x80U) { crc = (uint8_t)((crc << 1U) ^ 0x2FU); }
        else             { crc = (uint8_t)(crc << 1U); }
    }
    return crc;
}

/**
 * @brief  接收解析（从 ring buf 取字节拼帧）
 */
void Hmi_Uart_Read_Process(void)
{
    int     b;
    uint8_t data;
    uint8_t sum;
    uint8_t crc;
    uint8_t k;

    while (ring_buffer_available() > 0U)
    {
        b = ring_buffer_get();
        if (b < 0) { break; }
        data = (uint8_t)b;

        /* ---- 状态 1：等帧头 ---- */
        if (s_frame_started == 0U)
        {
            if (data == s_uart_rx_head)
            {
                s_rx_frame[0]   = data;
                s_rx_index      = 1U;
                s_frame_started = 1U;
            }
            continue;
        }

        /* ---- 状态 2：拼帧 ---- */
        s_rx_frame[s_rx_index++] = data;

        if (s_rx_index >= HMI_RX_FRAME_LEN)
        {
//            /* 7 个数据字节求和，再算 CRC8 */
//            sum = (uint8_t)(s_rx_frame[1] + s_rx_frame[2] + s_rx_frame[3] +
//                            s_rx_frame[4] + s_rx_frame[5] + s_rx_frame[6] +
//                            s_rx_frame[7]);
//            crc = Hmi_Crc8(sum);

//            if (crc == s_rx_frame[8])
//            {
//                /* ---- CRC 通过：解析 ---- */
//                Systask.System_State_Flag.bit.system_runflag =
//                    (s_rx_frame[1] >> s_uart_num) & 0x01U;

//                Hmi_Uart_Ctrl.state.BIT.transmission_enable = 1U;
//                s_rx_index      = 0U;
//                s_frame_started = 0U;
//            }
//            else
//            {
//                /* ---- CRC 失败：滑动窗口重找帧头 ---- */
//                k = 1U;
//                while ((k < HMI_RX_FRAME_LEN) && (s_rx_frame[k] != s_uart_rx_head))
//                {
//                    k++;
//                }
//                if (k < HMI_RX_FRAME_LEN)
//                {
//                    memmove(s_rx_frame, s_rx_frame + k, (size_t)(HMI_RX_FRAME_LEN - k));
//                    s_rx_index = (uint8_t)(HMI_RX_FRAME_LEN - k);
//                }
//                else
//                {
//                    s_rx_index      = 0U;
//                    s_frame_started = 0U;
//                }
//            }
//            /* 7 个数据字节求和，再算 CRC8 */
//            sum = (uint8_t)(s_rx_frame[1] + s_rx_frame[2] + s_rx_frame[3] +
//                            s_rx_frame[4] + s_rx_frame[5] + s_rx_frame[6] +
//                            s_rx_frame[7]);
//            crc = Hmi_Crc8(sum);

            if ((0x55U == s_rx_frame[1]) && (0xCCU == s_rx_frame[3]))
            {
                /* ---- CRC 通过：解析 ---- */
                Systask.Speed_rpm_Target = 500U*s_rx_frame[2];

                Hmi_Uart_Ctrl.state.BIT.transmission_enable = 0U;
                s_rx_index      = 0U;
                s_frame_started = 0U;
            }
            else
            {
                /* ---- CRC 失败：滑动窗口重找帧头 ---- */
                k = 1U;
                while ((k < HMI_RX_FRAME_LEN) && (s_rx_frame[k] != s_uart_rx_head))
                {
                    k++;
                }
                if (k < HMI_RX_FRAME_LEN)
                {
                    memmove(s_rx_frame, s_rx_frame + k, (size_t)(HMI_RX_FRAME_LEN - k));
                    s_rx_index = (uint8_t)(HMI_RX_FRAME_LEN - k);
                }
                else
                {
                    s_rx_index      = 0U;
                    s_frame_started = 0U;
                }
            }
        }
    }
}

/**
 * @brief  底层发送（DMA）
 * @param  data  数据指针
 * @param  len   数据长度
 */
void Hmi_Uart_Send_Data(uint8_t *data, uint16_t len)
{
    UARTH_Tx_DMA_Start((Q08U_*)data, (Q32U_)len);
}

/**
 * @brief  TX 状态机（10ms 调用）
 */
void Hmi_Uart_Tx_Process(void)
{
    ST_HMI_UART_CTRL *p = &Hmi_Uart_Ctrl;

    switch (p->tx_flow)
    {
        case HMI_TX_IDLE:
        {
//            if (p->state.BIT.transmission_enable == 1U)
            {
                /* 发送节流：2 + 10*num 个 10ms 后启动 */
                if (++p->txdata_cnt >= (uint32_t)(2U + 10U * s_uart_num))
                {
                    p->txdata_cnt = 0U;
                    p->txdata_len = 0U;

                    p->txdata[p->txdata_len++] = 0xFFU;
                    p->txdata[p->txdata_len++] = 0xFFU;
                    p->txdata[p->txdata_len++] = s_uart_tx_head;
                    p->txdata[p->txdata_len++] = 0U;
                    p->txdata[p->txdata_len++] = 0U;
                    p->txdata[p->txdata_len++] = 0U;
                    p->txdata[p->txdata_len++] = 0U;
                    p->txdata[p->txdata_len++] = Hmi_Crc8((uint8_t)(p->txdata[3] + p->txdata[4] +
                                                                    p->txdata[5] + p->txdata[6]));
                    p->txdata[p->txdata_len++] = 0xFFU;
                    p->txdata[p->txdata_len++] = 0xFFU;

                    p->error_cnt = 0U;
                    Hmi_Uart_Send_Data(p->txdata, (uint16_t)p->txdata_len);
                    p->tx_flow = HMI_TX_RUN;
                }
            }
        } break;

        case HMI_TX_RUN:
        {
            if (UARTH_Tx_DMA_Flag() != 0U)
            {
                if (UARTH_Tx_Finish_Flag() != 0U)
                {
                    UARTH_Tx_DMA_Stop();

                    p->error_cnt   = 0U;
                    p->txdata_cnt  = 0U;
                    p->txdata_len  = 0U;
                    p->state.BIT.transmission_enable = 0U;
                    p->state.BIT.resceive_enable     = 1U;
                    p->tx_flow = HMI_TX_END;
                }
                else if (++p->error_cnt > HMI_TX_TIMEOUT_CNT)
                {
                    UARTH_Tx_DMA_Stop();

                    p->error_cnt   = 0U;
                    p->txdata_cnt  = 0U;
                    p->txdata_len  = 0U;
                    p->state.BIT.transmission_enable = 0U;
                    p->state.BIT.resceive_enable     = 1U;
                    p->tx_flow = HMI_TX_IDLE;
                }
            }
            else if (++p->error_cnt > HMI_TX_TIMEOUT_CNT)
            {
                UARTH_Tx_DMA_Stop();

                p->error_cnt   = 0U;
                p->txdata_cnt  = 0U;
                p->txdata_len  = 0U;
                p->state.BIT.transmission_enable = 0U;
                p->state.BIT.resceive_enable     = 1U;
                p->tx_flow = HMI_TX_IDLE;
            }
        } break;

        case HMI_TX_END:
        {
            p->tx_flow = HMI_TX_IDLE;
        } break;

        default:
            p->tx_flow = HMI_TX_IDLE;
            break;
    }
}
