/**************************************************************************************************
*     File Name :                        UARTS.c
*     Library/Module Name :              UARTS
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             串口通讯源文件
**************************************************************************************************/

#include "sys_task.h"
#include "sys_uart.h"
#include <stdint.h>
#include <string.h>        // ← 添加这一行


ST_UART_CONTROL UART_Ctrl = {
    .UART_State.BIT.resceive_enable = 1U,
    .UART_State.BIT.transmission_enable = 0U,
    .rxdata_cnt = 10000U,
    .rxdata_maxlength = RESCEIVE_DATA_LENGTH,
    .txdata_maxlength = TRANSMISSION_DATA_LENGTH,
};

static Q08U_ HAL_ACCM_NUM = 0U;
static Q08U_ HAL_UART_RX_HEAD = 0U;
static Q08U_ HAL_UART_TX_HEAD = 0U;
void UART_NUM_Init(void)
{
//    if((BSP_GPIO_BTN1() == 1U) && (BSP_GPIO_BTN0() == 1U))
//    {
//        HAL_ACCM_NUM = 1U;
//        HAL_UART_RX_HEAD = 0xAAU; 
//        HAL_UART_TX_HEAD = 0xFAU;
//    }
//    else if((BSP_GPIO_BTN1() == 1U) && (BSP_GPIO_BTN0() == 0U))
//    {
//        HAL_ACCM_NUM = 2U;
//        HAL_UART_RX_HEAD = 0xAAU; 
//        HAL_UART_TX_HEAD = 0xFBU;
//    }
//    else if((BSP_GPIO_BTN1() == 0U) && (BSP_GPIO_BTN0() == 1U))
//    {
//        HAL_ACCM_NUM = 3U;
//        HAL_UART_RX_HEAD = 0xAAU; 
//        HAL_UART_TX_HEAD = 0xFCU;
//    }
//    else if((BSP_GPIO_BTN1() == 0U) && (BSP_GPIO_BTN0() == 0U))
//    {
//        HAL_ACCM_NUM = 4U;
//        HAL_UART_RX_HEAD = 0xAAU; 
//        HAL_UART_TX_HEAD = 0xFDU;
//    }
    /* 根据按键分配协议头（保留原注释逻辑）*/
}


/**********************************************************************************************
Function: Cal_CRC8
Description: CRC8 校验
***********************************************************************************************/
Q08U_ Cal_CRC8(const Q08U_ data)
{
    Q08U_ i, crc;
    crc = data;
    for (i = 8; i > 0; i--) {
        if (crc & 0x80) {
            crc = (crc << 1) ^ 0x2f;
        } else {
            crc = (crc << 1);
        }
    }
    return crc;
}


/**********************************************************************************************
Function: UART_Get_Resceive_Data
Description: 串口1 接收数据状态机
***********************************************************************************************/
void UART_Get_Resceive_Data(void)
{
    ST_UART_CONTROL* pUC = &UART_Ctrl;

    switch (pUC->UART_Resceive_Flow)
    {
        case UART_STATE_IDLE:
        {
            if (pUC->UART_State.BIT.resceive_enable == 1U)
            {
                if (++pUC->rxdata_cnt >= 80U - 10U * HAL_ACCM_NUM)
                {
                    pUC->rxdata_cnt = 0U;
                    UARTH_Enable_Rx();
                    pUC->UART_Resceive_Flow = UART_STATE_RUN;
                }
            }
        } break;

        case UART_STATE_RUN:
        {
            if (pUC->rxdata_length_tmp >= pUC->rxdata_maxlength)
            {
                UARTH_Disable_Rx();
                pUC->UART_Resceive_Flow = UART_STATE_ERROR;
            }
            if ((pUC->rxdata_length_tmp == pUC->rxdata_length_last)
                && (pUC->rxdata_length_tmp != 0U))
            {
                if (++pUC->rxdata_cnt >= 2U)
                {
                    pUC->rxdata_cnt = 0U;
                    UARTH_Disable_Rx();
                    pUC->UART_Resceive_Flow = UART_STATE_END;
                }
            }
            pUC->rxdata_length_last = pUC->rxdata_length_tmp;
        } break;

        case UART_STATE_END:
        {
            pUC->rx_num = 0U;
            while ((pUC->rx_num < 5U) && (pUC->rxdata[pUC->rx_num] != HAL_UART_RX_HEAD))
            {
                pUC->rx_num++;
            }

            Q08U_ rxdata_tmp = Cal_CRC8(pUC->rxdata[pUC->rx_num + 1] + pUC->rxdata[pUC->rx_num + 2]
                                        + pUC->rxdata[pUC->rx_num + 3] + pUC->rxdata[pUC->rx_num + 4]
                                        + pUC->rxdata[pUC->rx_num + 5] + pUC->rxdata[pUC->rx_num + 6]
                                        + pUC->rxdata[pUC->rx_num + 7]);

            if ((pUC->rxdata[pUC->rx_num] == HAL_UART_RX_HEAD)
                && (rxdata_tmp == pUC->rxdata[pUC->rx_num + 8]))
            {
                pUC->UART_State.BIT.transmission_enable = 1U;
                pUC->rxdata_cnt = 0U;
            }
            else
            {
                pUC->UART_State.BIT.resceive_enable = 1U;
                pUC->rxdata_cnt = 10000U;
            }

            pUC->error_cnt = 0U;

            pUC->rxdata_length_last = 0U;
            pUC->rxdata_length_tmp  = 0U;

            pUC->txdata_cnt         = 0U;
            pUC->txdata_length_tmp  = 0U;
            pUC->txdata_length_last = 0U;

            pUC->UART_Resceive_Flow = UART_STATE_IDLE;
        } break;

        case UART_STATE_ERROR:
        {
            pUC->error_cnt = 0U;

            pUC->rxdata_length_last = 0U;
            pUC->rxdata_length_tmp  = 0U;
            pUC->rxdata_cnt         = 0U;

            pUC->txdata_cnt         = 0U;
            pUC->txdata_length_tmp  = 0U;
            pUC->txdata_length_last = 0U;

            pUC->UART_State.BIT.transmission_enable = 0U;
            pUC->UART_State.BIT.resceive_enable     = 1U;
            pUC->UART_Resceive_Flow = UART_STATE_IDLE;
        } break;

        default:
            break;
    }
}


/**********************************************************************************************
Function: UART_Send_Transmission_Data
Description: 串口1 发送数据状态机
***********************************************************************************************/
void UART_Send_Transmission_Data(void)
{
    ST_UART_CONTROL* pUC = &UART_Ctrl;

    switch (pUC->UART_Transmission_Flow)
    {
        case UART_STATE_IDLE:
        {
            if (pUC->UART_State.BIT.transmission_enable == 1U)
            {
                if (++pUC->txdata_cnt >= 2U + 10U * HAL_ACCM_NUM)
                {
                    pUC->txdata_cnt         = 0U;
                    pUC->txdata_length_tmp  = 0U;
                    pUC->txdata_length_last = 0U;

                    pUC->txdata[pUC->txdata_length_tmp++] = 0xFFU;
                    pUC->txdata[pUC->txdata_length_tmp++] = HAL_UART_TX_HEAD;
                    pUC->txdata[pUC->txdata_length_tmp++] = 0xFFU;
                    pUC->txdata[pUC->txdata_length_tmp++] = 0xFFU;

                    UART_TRANSMISSION_DATA = pUC->txdata[0];
                    UARTH_Enable_Tx();

                    pUC->UART_Transmission_Flow = UART_STATE_RUN;
                }
            }
        } break;

        case UART_STATE_RUN:
        {
            if (pUC->txdata_length_last >= pUC->txdata_length_tmp)
            {
                pUC->UART_Transmission_Flow = UART_STATE_END;
            }
        } break;

        case UART_STATE_END:
        {
            pUC->error_cnt = 0U;

            pUC->rxdata_length_last = 0U;
            pUC->rxdata_length_tmp  = 0U;
            pUC->rxdata_cnt         = 0U;

            pUC->txdata_cnt         = 0U;
            pUC->txdata_length_tmp  = 0U;
            pUC->txdata_length_last = 0U;

            pUC->UART_State.BIT.transmission_enable = 0U;
            pUC->UART_State.BIT.resceive_enable     = 1U;
            pUC->UART_Transmission_Flow = UART_STATE_IDLE;
        } break;

        case UART_STATE_ERROR:
        {
            pUC->error_cnt = 0U;

            pUC->rxdata_length_last = 0U;
            pUC->rxdata_length_tmp  = 0U;
            pUC->rxdata_cnt         = 0U;

            pUC->txdata_cnt         = 0U;
            pUC->txdata_length_tmp  = 0U;
            pUC->txdata_length_last = 0U;

            pUC->UART_State.BIT.transmission_enable = 0U;
            pUC->UART_State.BIT.resceive_enable     = 1U;
            pUC->UART_Transmission_Flow = UART_STATE_IDLE;
        } break;

        default:
            break;
    }
}


/**********************************************************************************************
Function: UART_Resceive_Int
Description: 串口1 接收数据中断（DMA 方案下未使用，保留兼容）
***********************************************************************************************/
void UART_Resceive_Int(void)
{
    ST_UART_CONTROL* pUC = &UART_Ctrl;
    if (pUC->rxdata_length_tmp < pUC->rxdata_maxlength)
    {
        pUC->rxdata[pUC->rxdata_length_tmp++] = UART_RESCEIVE_DATA;
    }
    else
    {
        UARTH_Disable_Rx();
    }
}


/**********************************************************************************************
Function: UART_Transmission_Int
Description: 串口1 发送数据中断（DMA 方案下未使用，保留兼容）
***********************************************************************************************/
void UART_Transmission_Int(void)
{
    ST_UART_CONTROL* pUC = &UART_Ctrl;
    UART_TRANSMISSION_DATA = pUC->txdata[pUC->txdata_length_last++];
    if (pUC->txdata_length_last == pUC->txdata_length_tmp)
    {
        UARTH_Disable_Tx();
    }
}


/*-----------------------------------------------------------
 * 函数：uart_send_data
 * 功能：通过 DMA 发送指定长度的数据
 *----------------------------------------------------------*/
void uart_send_data(uint8_t *data, uint16_t len)
{
    if (len == 0 || data == NULL)
    {
        return;
    }

    /* 1. 关闭 TX DMA 通道 */
    DMA_Cmd(HAL_HMI_USART_TX_DMA_CH, DISABLE);

    /* 2. 清所有标志（GL/TC/HT/TE）*/
    DMA_ClearFlag(HAL_HMI_USART_TX_DMA_GL_FLAG);

    /* 3. 重新配置内存地址和数据长度 */
    HAL_HMI_USART_TX_DMA_CH->CMAR  = (Q32U_)data;
    HAL_HMI_USART_TX_DMA_CH->CNDTR = (Q16U_)len;

    /* 4. 使能 DMA 通道 */
    DMA_Cmd(HAL_HMI_USART_TX_DMA_CH, ENABLE);

    /* 5. 使能 USART1 的 DMA 发送请求 */
    USART_DMACmd(HAL_HMI_UART, USART_DMAReq_Tx, ENABLE);
}


/*-----------------------------------------------------------
 * 函数：uart_send_string
 * 功能：发送以 '\0' 结尾的字符串
 *----------------------------------------------------------*/
void uart_send_string(const char *str)
{
    uart_send_data((uint8_t *)str, (uint16_t)strlen(str));
}


/*-------------------------- 4. 环形缓冲区 ------------------------------*/
static volatile uint8_t  ring_buf[UART1_RX_BUF_SIZE];
static volatile uint16_t write_index = 0;
static volatile uint16_t read_index  = 0;
/* 上一次 DMA 已搬运的位置（用于计算新数据长度） */
static volatile uint16_t dma_last_pos = 0;


void ring_buffer_init(void)
{
    write_index = 0;
    read_index  = 0;
    dma_last_pos = 0;
}


/* 返回缓冲区中可读字节数 */
uint16_t ring_buffer_available(void)
{
    return (uint16_t)((write_index + UART1_RX_BUF_SIZE - read_index) % UART1_RX_BUF_SIZE);
}


/* 从缓冲区读取一个字节，返回 -1 表示空 */
int ring_buffer_get(void)
{
    if (read_index == write_index)
    {
        return -1;                              /* 缓冲区为空 */
    }
    uint8_t data = ring_buf[read_index];
    read_index = (read_index + 1) % UART1_RX_BUF_SIZE;
    return (int)data;
}


/* 向缓冲区写入一个字节，返回 0 表示缓冲区已满 */
Q08U_ ring_buffer_put(uint8_t data)
{
    uint16_t next = (write_index + 1) % UART1_RX_BUF_SIZE;
    if (next == read_index)
    {
        return 0U;                              /* 缓冲区满，丢弃数据 */
    }
    ring_buf[write_index] = data;
    write_index = next;
    return 1U;
}


void ring_buffer_clear(void)
{
    write_index = 0;
    read_index  = 0;
}


/**********************************************************************************************
Function: UART_DMA_Rx_Int
Description: UART 的 DMA 接收处理（在 USART1 IDLE 中断里调用）
***********************************************************************************************/
void UART_DMA_Rx_Int(void)
{
    /* 获取 DMA 当前剩余传输数量 */
    uint16_t remain = (uint16_t)DMA_GetCurrDataCounter(HAL_HMI_USART_RX_DMA_CH);

    /* DMA 已写入的绝对位置 */
    uint16_t curr_pos = UART1_RX_BUF_SIZE - remain;

    /* 计算本次新接收的数据长度 */
    uint16_t new_len;
    if (curr_pos >= dma_last_pos)
    {
        new_len = curr_pos - dma_last_pos;
    }
    else
    {
        /* DMA 缓冲区发生了回绕 */
        new_len = (UART1_RX_BUF_SIZE - dma_last_pos) + curr_pos;
    }

    /* 将新数据从 DMA 线性缓冲区搬运到环形缓冲区 */
    for (uint16_t i = 0; i < new_len; i++)
    {
        uint16_t idx = (dma_last_pos + i) % UART1_RX_BUF_SIZE;
        ring_buffer_put(g_uart_rx_buf[idx]);    /* 缓冲区满时自动丢弃 */
    }

    /* 更新上次搬运位置 */
    dma_last_pos = curr_pos;
}
