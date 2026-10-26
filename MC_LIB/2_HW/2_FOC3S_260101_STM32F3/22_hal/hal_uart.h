/**
 * @file    hal_uart.h
 * @brief   系统串口 HAL 层头文件
 *          DMA 收发 / 环形缓冲区
 *          全部 static inline，无 .c 文件
 *
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef HAL_UART_H
#define HAL_UART_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_para.h"
#include "bsp_sys.h"
#include "bsp_sys_dma.h"        /* 提供数据缓冲区 + 环形缓冲区 + 发送状态 extern */
#include <string.h>

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. UART 的 DMA 收发 ============= */

/**
 * @brief  读取 TX 传输完成标志
 * @return 非 0 = 完成
 * @warning 仅表示 DMA 已把数据搬到串口数据寄存器，不代表最后一字节已移出。
 *          若要判定 RS485 完全发完，还需结合 USART TC 标志（见文件头警告）
 */
static inline Q32U_ UARTH_Tx_Finish_Flag(void)
{
    return USART_GetFlagStatus(HW_SYS_UART, USART_FLAG_TC);
}

/**
 * @brief  读取 TX DMA 传输完成标志
 * @return 非 0 = 完成
 * @warning 仅表示 DMA 已把数据搬到 TDR，不代表最后一字节已移出。
 *          若要判定 RS485 完全发完，还需结合 USART TC 标志（见文件头警告）
 */
static inline Q32U_ UARTH_Tx_DMA_Flag(void)
{
    return (Q32U_)DMA_GetFlagStatus(HW_SYS_UART_TX_DMA_TC_FLAG);
}

/**
 * @brief  启动 TX DMA（单次模式）
 * @param  txbuffer  数据指针
 * @param  len       数据长度（字节）
 */
static inline void UARTH_Tx_DMA_Start(Q08U_* txbuffer, Q32U_ len)
{
    if ((txbuffer == NULL) || (len == 0U) || (len > UART_TX_BUF_SIZE))
    {
        return;
    }

#if (HW_FUN_UART_PHY == HW_FUN_UART_PHY_RS485)
    BSP_SYS_GPIO_TXEN(1U);                              /* 强制切回发送 */
#endif

    /* 1. 关闭通道，清标志 */
    DMA_Cmd(HW_SYS_UART_TX_DMA_CH, DISABLE);
    DMA_ClearFlag(HW_SYS_UART_TX_DMA_GL_FLAG);

    /* 2. 清 USART TC（否则首字节触发失败） */
    USART_ClearFlag(HW_SYS_UART, USART_FLAG_TC);

    /* 3. 重设源地址与长度 */
    HW_SYS_UART_TX_DMA_CH->CMAR  = (Q32U_)txbuffer;
    HW_SYS_UART_TX_DMA_CH->CNDTR = (Q16U_)len;

    /* 4. 启动通道 + 使能 USART 的 DMA 发送请求 */
    USART_DMACmd(HW_SYS_UART, USART_DMAReq_Tx, ENABLE);
    DMA_Cmd(HW_SYS_UART_TX_DMA_CH, ENABLE);
}

/**
 * @brief  停止 TX DMA 并切回接收方向
 * @note   RS485 模式下会立刻切回接收方向，**调用前必须确保数据已完全移出**
 */
static inline void UARTH_Tx_DMA_Stop(void)
{
#if (HW_FUN_UART_PHY == HW_FUN_UART_PHY_RS485)
    BSP_SYS_GPIO_TXEN(0U);                              /* 强制切回接收 */
#endif

    USART_DMACmd(HW_SYS_UART, USART_DMAReq_Tx, DISABLE);
    DMA_Cmd(HW_SYS_UART_TX_DMA_CH, DISABLE);
    DMA_ClearFlag(HW_SYS_UART_TX_DMA_GL_FLAG);
    USART_ClearFlag(HW_SYS_UART, USART_FLAG_TC);
}

/**
 * @brief  读取 RX DMA 剩余计数
 * @return 剩余未接收的字节数
 * @note   已收字节数 = UART_RX_BUF_SIZE - 返回值
 */
static inline Q32U_ UARTH_Rx_DMA_RemainCount(void)
{
    return (Q32U_)DMA_GetCurrDataCounter(HW_SYS_UART_RX_DMA_CH);
}

/* ======================== 6. 环形缓冲区 =================== */

/**
 * @brief  初始化环形缓冲区
 */
static inline void ring_buffer_init(void)
{
    g_ring_write_index  = 0U;
    g_ring_read_index   = 0U;
    g_ring_dma_last_pos = 0U;
}

/**
 * @brief  获取可读字节数
 * @return 缓冲区中已有字节数
 */
static inline uint16_t ring_buffer_available(void)
{
    return (uint16_t)((g_ring_write_index + UART_RX_RING_SIZE - g_ring_read_index) % UART_RX_RING_SIZE);
}

/**
 * @brief  从缓冲区读取 1 字节
 * @return 读到的字节（0~255），-1 = 缓冲区为空
 */
static inline int ring_buffer_get(void)
{
    uint8_t data;

    if (g_ring_read_index == g_ring_write_index)
    {
        return -1;                              /* 缓冲区为空 */
    }
    data = g_ring_buf[g_ring_read_index];
    g_ring_read_index = (uint16_t)((g_ring_read_index + 1U) % UART_RX_RING_SIZE);
    return (int)data;
}

/**
 * @brief  向缓冲区写入 1 字节
 * @param  data  待写字节
 * @return 1 = 成功，0 = 缓冲区满
 */
static inline Q08U_ ring_buffer_put(uint8_t data)
{
    uint16_t next = (uint16_t)((g_ring_write_index + 1U) % UART_RX_RING_SIZE);

    if (next == g_ring_read_index)
    {
        return 0U;                              /* 缓冲区满，丢弃数据 */
    }
    g_ring_buf[g_ring_write_index] = data;
    g_ring_write_index = next;
    return 1U;
}

/**
 * @brief  清空环形缓冲区
 */
static inline void ring_buffer_clear(void)
{
    g_ring_write_index = 0U;
    g_ring_read_index  = 0U;
}

#endif /* HAL_UART_H */
