/* ==== SOURCE: 2_HW\2_FOC3S_260101_STM32F3\22_hal\hal_uart.h ==== */
/**************************************************************************************************
*     File Name :                        hal_uart
*     Library/Module Name :              hal_uart
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统串口 HAL 层头文件
*                                        引脚 / 收发使能 / DMA 收发 / 环形缓冲区 / 发送节流
*                                        全部 static inline，无 .c 文件
*
*     硬件映射（STM32F303，见 hw_map.h）：
*       USART1  TX = DMA1_Channel4（Normal 模式）
*       USART1  RX = DMA1_Channel5（Circular 模式，配 USART IDLE 中断分包）
*       RS485 方向 = PA11（BSP_SYS_GPIO_TXEN）
*
*     发送流程（节流，避免覆盖正在发送的数据）：
*       uart_send_data()      把数据拷进 g_uart_tx_buf，置 g_uart_tx_len / g_uart_tx_busy
*       UART_DMA_Tx_Poll()    由 10ms 任务调用，检测到待发就启动 DMA + 切 485 方向
*       DMA1_Channel4_IRQHandler 传输完成后等 USART TC，调用 UARTH_Disable_Tx() 切回接收
*
*     接收流程：
*       DMA1_Channel5 循环搬到 g_uart_rx_buf
*       USART1 IDLE 中断 → UART_DMA_Rx_Int() 把新数据搬进 g_ring_buf
*       协议层用 ring_buffer_available() / ring_buffer_get() 取字节
**************************************************************************************************/
#ifndef HAL_UART_H
#define HAL_UART_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_para.h"
#include "bsp_sys.h"
#include "bsp_sys_dma.h"        /* 提供数据缓冲区 + 环形缓冲区 + 发送状态 extern */
#include <string.h>


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/
/* 注：g_uart_tx_buf / g_uart_rx_buf / g_ring_* / g_uart_tx_len / g_uart_tx_busy
 *     的 extern 已在 bsp_sys_dma.h 中声明 */


/*-------------------------- 5. UART 收发使能 ---------------------------*/
/*
Function: UARTH_Enable_Rx
Description: UART 打开接收（含 DMA 接收请求）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UARTH_Enable_Rx(void)
{
    USART_DMACmd(HW_SYS_UART, USART_DMAReq_Rx, ENABLE);
    USART_ITConfig(HW_SYS_UART, USART_IT_IDLE, ENABLE);
}

/*
Function: UARTH_Disable_Rx
Description: UART 关闭接收
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UARTH_Disable_Rx(void)
{
    USART_ITConfig(HW_SYS_UART, USART_IT_IDLE, DISABLE);
    USART_DMACmd(HW_SYS_UART, USART_DMAReq_Rx, DISABLE);
}

/*
Function: UARTH_Enable_Tx
Description: UART 打开发送（先切 RS485 到发送方向）
             注意：不在此处等待 TC，TC 的等待放在关发送时做
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UARTH_Enable_Tx(void)
{
    BSP_SYS_GPIO_TXEN(1U);                                  /* 先切 485 到发送方向 */
    USART_DMACmd(HW_SYS_UART, USART_DMAReq_Tx, ENABLE);
}

/*
Function: UARTH_Disable_Tx
Description: UART 关闭发送（等最后一字节移出后，切回 RS485 接收方向）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UARTH_Disable_Tx(void)
{
    USART_DMACmd(HW_SYS_UART, USART_DMAReq_Tx, DISABLE);

    /* 等移位寄存器真的发完（最多一个字节时间，115200 下 <= 87us）*/
    while (USART_GetFlagStatus(HW_SYS_UART, USART_FLAG_TC) == RESET)
    {
    }

    BSP_SYS_GPIO_TXEN(0U);                                  /* 最后切回接收方向 */
}


/*-------------------------- 6. UART 的 DMA 收发 ------------------------*/
/*
Function: UARTH_Tx_DMA_Flag
Description: 读取 UART 的 DMA 发送完成标志（TC）
             Normal 模式下 TC 置位表示本次传输结束
Return: 0 - 未完成；非 0 - 已完成
Author: CJYS
*/
static inline Q32U_ UARTH_Tx_DMA_Flag(void)
{
    return (Q32U_)DMA_GetFlagStatus(HW_SYS_UART_TX_DMA_TC_FLAG);
}

/*
Function: UARTH_Tx_DMA_Start
Description: 启动 UART 的 DMA 发送
Input: txbuffer - 待发送数据指针；len - 长度
Return: 无
Author: CJYS
*/
static inline void UARTH_Tx_DMA_Start(Q08U_* txbuffer, Q32U_ len)
{
    if ((txbuffer == NULL) || (len == 0U) || (len > UART_TX_BUF_SIZE))
    {
        return;
    }

    /* 1. 关闭通道，清所有标志 */
    DMA_Cmd(HW_SYS_UART_TX_DMA_CH, DISABLE);
    DMA_ClearFlag(HW_SYS_UART_TX_DMA_GL_FLAG);

    /* 2. 重设源地址与长度 */
    HW_SYS_UART_TX_DMA_CH->CMAR  = (Q32U_)txbuffer;
    HW_SYS_UART_TX_DMA_CH->CNDTR = (Q16U_)len;

    /* 3. 启动通道 + 使能 USART 的 DMA 发送请求 */
    DMA_Cmd(HW_SYS_UART_TX_DMA_CH, ENABLE);
    USART_DMACmd(HW_SYS_UART, USART_DMAReq_Tx, ENABLE);
}

/*
Function: UARTH_Tx_DMA_Stop
Description: 停止 UART 的 DMA 发送
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UARTH_Tx_DMA_Stop(void)
{
    USART_DMACmd(HW_SYS_UART, USART_DMAReq_Tx, DISABLE);
    DMA_Cmd(HW_SYS_UART_TX_DMA_CH, DISABLE);
    DMA_ClearFlag(HW_SYS_UART_TX_DMA_GL_FLAG);
}

/*
Function: UARTH_Rx_DMA_Flag
Description: 读取 UART 的 DMA 接收完成标志
             接收用循环模式 + IDLE 中断，本函数仅用于诊断
Return: 0 - 未完成；非 0 - 已完成
Author: CJYS
*/
static inline Q32U_ UARTH_Rx_DMA_Flag(void)
{
    return (Q32U_)DMA_GetFlagStatus(HW_SYS_UART_RX_DMA_TC_FLAG);
}

/*
Function: UARTH_Rx_DMA_Start
Description: 启动 UART 的 DMA 接收
Input: rxbuffer - 接收缓冲区指针；len - 期望接收长度
Return: 无
Author: CJYS
*/
static inline void UARTH_Rx_DMA_Start(Q08U_* rxbuffer, Q32U_ len)
{
    if ((rxbuffer == NULL) || (len == 0U) || (len > UART_RX_BUF_SIZE))
    {
        return;
    }

    USART_DMACmd(HW_SYS_UART, USART_DMAReq_Rx, DISABLE);
    DMA_Cmd(HW_SYS_UART_RX_DMA_CH, DISABLE);
    DMA_ClearFlag(HW_SYS_UART_RX_DMA_GL_FLAG);

    HW_SYS_UART_RX_DMA_CH->CMAR  = (Q32U_)rxbuffer;
    HW_SYS_UART_RX_DMA_CH->CNDTR = (Q16U_)len;

    DMA_Cmd(HW_SYS_UART_RX_DMA_CH, ENABLE);
    USART_DMACmd(HW_SYS_UART, USART_DMAReq_Rx, ENABLE);
}

/*
Function: UARTH_Rx_DMA_Stop
Description: 停止 UART 的 DMA 接收
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UARTH_Rx_DMA_Stop(void)
{
    USART_DMACmd(HW_SYS_UART, USART_DMAReq_Rx, DISABLE);
    DMA_Cmd(HW_SYS_UART_RX_DMA_CH, DISABLE);
}

/*
Function: UARTH_Rx_DMA_RemainCount
Description: 读取 UART 的 DMA 接收剩余数据数（用于 IDLE 帧长度计算）
Return: 剩余未接收的字节数
Author: CJYS
*/
static inline Q32U_ UARTH_Rx_DMA_RemainCount(void)
{
    return (Q32U_)DMA_GetCurrDataCounter(HW_SYS_UART_RX_DMA_CH);
}


/*-------------------------- 7. DMA 通用发送接口 -----------------------*/
/*
 * 注意：本函数不是"启动发送"，只把数据拷进发送缓冲区并置忙标志。
 *       真正的 DMA 启动放在 UART_DMA_Tx_Poll() 里，由 10ms 任务调用，
 *       这样发送过程中新写入的数据会被识别并丢弃，而不会覆盖正在发送的内容。
 */
/*
Function: uart_send_data
Description: 通过 DMA 发送指定长度的数据（入队，非阻塞）
Input: data - 数据指针；len - 长度
Output: 无
Return: 无
Author: CJYS
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
        len = UART_TX_BUF_SIZE;                 /* 超长截断 */
    }
    if (g_uart_tx_busy != 0U)
    {
        return;                                 /* 上一帧还没发完，本帧丢弃 */
    }

    for (i = 0U; i < len; i++)
    {
        g_uart_tx_buf[i] = data[i];
    }

    g_uart_tx_len  = len;                       /* 实际帧长，供 Poll 使用 */
    g_uart_tx_busy = 1U;                        /* 交给 UART_DMA_Tx_Poll() 启动 */
}

/*
Function: uart_send_string
Description: 发送以 '\0' 结尾的字符串
Input: str - 字符串指针
Output: 无
Return: 无
Author: CJYS
*/
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
             检测到"待发送"且上一帧已发完（TC 置位）时，启动 DMA 并切 485 方向
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UART_DMA_Tx_Poll(void)
{
    if ((g_uart_tx_busy != 0U) && (UARTH_Tx_DMA_Flag() != 0U))
    {
        /* TC 已置位 = 上一帧（或首次上电后的初始状态）已完成 */
        DMA_ClearFlag(HW_SYS_UART_TX_DMA_GL_FLAG);      /* 清掉，避免下一拍重复判断 */
        UARTH_Enable_Tx();                              /* 切 485 方向 + 使能 DMA 请求 */
        UARTH_Tx_DMA_Start(g_uart_tx_buf, (Q32U_)g_uart_tx_len);
    }
}


/*-------------------------- 8. 环形缓冲区 ------------------------------*/
/*
Function: ring_buffer_init
Description: 环形缓冲区初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void ring_buffer_init(void)
{
    g_ring_write_index  = 0U;
    g_ring_read_index   = 0U;
    g_ring_dma_last_pos = 0U;
}

/*
Function: ring_buffer_available
Description: 返回缓冲区中可读字节数
Return: 可读字节数
Author: CJYS
*/
static inline uint16_t ring_buffer_available(void)
{
    return (uint16_t)((g_ring_write_index + UART_RX_RING_SIZE - g_ring_read_index)
                      % UART_RX_RING_SIZE);
}

/*
Function: ring_buffer_get
Description: 从缓冲区读取一个字节
Return: 0~255 - 读到的字节；-1 - 缓冲区为空
Author: CJYS
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

/*
Function: ring_buffer_put
Description: 向缓冲区写入一个字节
Input: data - 待写入字节
Return: 0 - 缓冲区满，丢弃；1 - 成功
Author: CJYS
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

/*
Function: ring_buffer_clear
Description: 环形缓冲区清空
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void ring_buffer_clear(void)
{
    g_ring_write_index = 0U;
    g_ring_read_index  = 0U;
}


/*-------------------------- 9. DMA 接收处理 ---------------------------*/
/*
Function: UART_DMA_Rx_Int
Description: UART 的 DMA 接收处理（在 USART1 IDLE 中断里调用）
             把 DMA 线性缓冲区中的新数据搬到环形缓冲区
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UART_DMA_Rx_Int(void)
{
    uint16_t remain;
    uint16_t curr_pos;                  /* DMA 已写入的绝对位置 */
    uint16_t new_len;
    uint16_t i;

    remain   = (uint16_t)UARTH_Rx_DMA_RemainCount();
    curr_pos = (uint16_t)(UART_RX_BUF_SIZE - remain);

    /* 计数值落到 0 且未重装时，按 0 处理，避免 curr_pos 越界 */
    if (remain == 0U)
    {
        curr_pos = 0U;
    }

    if (curr_pos >= g_ring_dma_last_pos)
    {
        new_len = (uint16_t)(curr_pos - g_ring_dma_last_pos);
    }
    else
    {
        /* DMA 缓冲区发生了回绕 */
        new_len = (uint16_t)((UART_RX_BUF_SIZE - g_ring_dma_last_pos) + curr_pos);
    }

    /* 将新数据从 DMA 线性缓冲区搬运到环形缓冲区 */
    for (i = 0U; i < new_len; i++)
    {
        uint16_t idx = (uint16_t)((g_ring_dma_last_pos + i) % UART_RX_BUF_SIZE);
        (void)ring_buffer_put(g_uart_rx_buf[idx]);      /* 缓冲区满时自动丢弃 */
    }

    /* 更新上次搬运位置 */
    g_ring_dma_last_pos = curr_pos;
}


#endif /* HAL_UART_H */
