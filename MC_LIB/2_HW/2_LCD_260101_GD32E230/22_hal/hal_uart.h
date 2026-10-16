/**************************************************************************************************
*     File Name :                        hal_uart
*     Library/Module Name :              hal_uart
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统串口 HAL 层头文件
*                                        引脚 / 收发使能 / DMA 收发 / 环形缓冲区
*                                        全部 static inline，无 .c 文件
**************************************************************************************************/
#ifndef HAL_UART_H
#define HAL_UART_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_para.h"
#include "bsp_sys.h"
#include "bsp_sys_dma.h"        /* ★ 提供数据缓冲区 + 环形缓冲区 extern 声明 */
#include <string.h>


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. UART 收发使能 ---------------------------*/
static inline void UARTH_Enable_Rx(void)
{
    usart_receive_config(HW_SYS_UART, USART_RECEIVE_ENABLE);
    usart_dma_receive_config(HW_SYS_UART, USART_DENR_ENABLE);
}

static inline void UARTH_Disable_Rx(void)
{
    usart_dma_receive_config(HW_SYS_UART, USART_DENR_DISABLE);
    usart_receive_config(HW_SYS_UART, USART_RECEIVE_DISABLE);
}

static inline void UARTH_Enable_Tx(void)
{
    BSP_SYS_GPIO_TXEN(1U);                                  /* 先切 485 到发送方向 */
    usart_transmit_config(HW_SYS_UART, USART_TRANSMIT_ENABLE);
    usart_dma_transmit_config(HW_SYS_UART, USART_DENT_ENABLE);
}

static inline void UARTH_Disable_Tx(void)
{
    usart_dma_transmit_config(HW_SYS_UART, USART_DENT_DISABLE);
    usart_transmit_config(HW_SYS_UART, USART_TRANSMIT_DISABLE);
    BSP_SYS_GPIO_TXEN(0U);                                  /* 最后切回接收方向 */
}


/*-------------------------- 6. UART 的 DMA 收发 ------------------------*/
static inline Q32U_ UARTH_Tx_DMA_Flag(void)
{
    return (Q32U_)dma_flag_get(HAL_SYS_USART_TX_DMA_CH, DMA_FLAG_FTF);
}

static inline void UARTH_Tx_DMA_Start(Q08U_* txbuffer, Q32U_ len)
{
    if ((txbuffer == NULL) || (len == 0U))
    {
        return;
    }

    dma_channel_disable(HAL_SYS_USART_TX_DMA_CH);
    dma_flag_clear(HAL_SYS_USART_TX_DMA_CH, DMA_FLAG_G);
    dma_memory_address_config(HAL_SYS_USART_TX_DMA_CH, (uint32_t)txbuffer);
    dma_transfer_number_config(HAL_SYS_USART_TX_DMA_CH, len);
    dma_channel_enable(HAL_SYS_USART_TX_DMA_CH);
}

static inline void UARTH_Tx_DMA_Stop(void)
{
    usart_dma_transmit_config(HW_SYS_UART, USART_DENT_DISABLE);
    dma_channel_disable(HAL_SYS_USART_TX_DMA_CH);
    dma_flag_clear(HAL_SYS_USART_TX_DMA_CH, DMA_FLAG_G);
}

static inline Q32U_ UARTH_Rx_DMA_Flag(void)
{
    /* 接收用循环模式 + IDLE 中断，不查 TC 标志 */
    return (Q32U_)dma_flag_get(HAL_SYS_USART_RX_DMA_CH, DMA_FLAG_FTF);
}

static inline void UARTH_Rx_DMA_Start(Q08U_* rxbuffer, Q32U_ len)
{
    if ((rxbuffer == NULL) || (len == 0U))
    {
        return;
    }

    usart_dma_receive_config(HW_SYS_UART, USART_DENR_DISABLE);
    dma_channel_disable(HAL_SYS_USART_RX_DMA_CH);
    dma_flag_clear(HAL_SYS_USART_RX_DMA_CH, DMA_FLAG_G);
    dma_memory_address_config(HAL_SYS_USART_RX_DMA_CH, (uint32_t)rxbuffer);
    dma_transfer_number_config(HAL_SYS_USART_RX_DMA_CH, len);
    dma_channel_enable(HAL_SYS_USART_RX_DMA_CH);
    usart_dma_receive_config(HW_SYS_UART, USART_DENR_ENABLE);
}

static inline void UARTH_Rx_DMA_Stop(void)
{
    usart_dma_receive_config(HW_SYS_UART, USART_DENR_DISABLE);
    dma_channel_disable(HAL_SYS_USART_RX_DMA_CH);
}

static inline Q32U_ UARTH_Rx_DMA_RemainCount(void)
{
    return (Q32U_)dma_transfer_number_get(HAL_SYS_USART_RX_DMA_CH);
}


/*-------------------------- 7. DMA 通用发送接口 -----------------------*/
/*
 * 注意：本函数不是"启动发送"，只是把数据拷进发送缓冲区并置忙标志。
 *       真正的 DMA 启动放在 UART_DMA_Tx_Poll() 里，由 10ms 任务调用，
 *       这样发送过程中新写入的数据会排队，不会被覆盖。
 */
static inline void uart_send_data(uint8_t *data, uint16_t len)
{
    uint16_t i;

    if ((data == NULL) || (len == 0U))
    {
        return;
    }
    if (len > UART_TX_BUF_SIZE)
    {
        len = UART_TX_BUF_SIZE;                 /* 超长截断，自行按需改成返回错误 */
    }
    if (g_uart_tx_busy != 0U)
    {
        return;                                 /* 上一帧未发完，直接丢弃 */
    }

    for (i = 0U; i < len; i++)
    {
        g_uart_tx_buf[i] = data[i];
    }
    
    g_uart_tx_len = len;
    g_uart_tx_busy = 1U;                        /* 交给 UART_DMA_Tx_Poll() 启动 */
}

static inline void uart_send_string(const char *str)
{
    if (str != NULL)
    {
        uart_send_data((uint8_t *)str, (uint16_t)strlen(str));
    }
}

/*
Function: UART_DMA_Tx_Poll
Description: 发送轮询（放在 10ms 任务里调用）
             检测到"待发送"标志后启动 DMA，并把 RS485 切到发送方向
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UART_DMA_Tx_Poll(void)
{
    if ((g_uart_tx_busy != 0U) && (UARTH_Tx_DMA_Flag() == 0U))
    {
        UARTH_Enable_Tx();                      /* 切 485 方向 + 使能发送/DMA 请求 */
        UARTH_Tx_DMA_Start(g_uart_tx_buf, (Q32U_)g_uart_tx_len);   /* ★ 用实际帧长 */
    }
}


/*-------------------------- 8. 环形缓冲区 ------------------------------*/
static inline void ring_buffer_init(void)
{
    g_ring_write_index  = 0U;
    g_ring_read_index   = 0U;
    g_ring_dma_last_pos = 0U;
}

static inline uint16_t ring_buffer_available(void)
{
    return (uint16_t)((g_ring_write_index + UART_RX_RING_SIZE - g_ring_read_index)
                      % UART_RX_RING_SIZE);
}

static inline int ring_buffer_get(void)
{
    uint8_t data;

    if (g_ring_read_index == g_ring_write_index)
    {
        return -1;                                          /* 空 */
    }
    data = g_ring_buf[g_ring_read_index];
    g_ring_read_index = (uint16_t)((g_ring_read_index + 1U) % UART_RX_RING_SIZE);
    return (int)data;
}

static inline Q08U_ ring_buffer_put(uint8_t data)
{
    uint16_t next = (uint16_t)((g_ring_write_index + 1U) % UART_RX_RING_SIZE);

    if (next == g_ring_read_index)
    {
        return 0U;                                          /* 满，丢弃 */
    }
    g_ring_buf[g_ring_write_index] = data;
    g_ring_write_index = next;
    return 1U;
}

static inline void ring_buffer_clear(void)
{
    g_ring_write_index = 0U;
    g_ring_read_index  = 0U;
}


/*-------------------------- 9. DMA 接收处理 ---------------------------*/
static inline void UART_DMA_Rx_Int(void)
{
    uint16_t remain    = (uint16_t)UARTH_Rx_DMA_RemainCount();
    uint16_t curr_pos  = (uint16_t)(UART_RX_BUF_SIZE - remain);   /* DMA 已写入位置 */
    uint16_t new_len;
    uint16_t i;

    if (remain == 0U)
    {
        curr_pos = 0U;          /* 计数值落到 0 且未重装，按 0 处理，避免 curr_pos 越界 */
    }

    if (curr_pos >= g_ring_dma_last_pos)
    {
        new_len = (uint16_t)(curr_pos - g_ring_dma_last_pos);
    }
    else
    {
        new_len = (uint16_t)((UART_RX_BUF_SIZE - g_ring_dma_last_pos) + curr_pos);  /* 回绕 */
    }

    for (i = 0U; i < new_len; i++)
    {
        uint16_t idx = (uint16_t)((g_ring_dma_last_pos + i) % UART_RX_BUF_SIZE);
        (void)ring_buffer_put(g_uart_rx_buf[idx]);          /* 满则丢 */
    }

    g_ring_dma_last_pos = curr_pos;
}



#endif /* HAL_UART_H */
