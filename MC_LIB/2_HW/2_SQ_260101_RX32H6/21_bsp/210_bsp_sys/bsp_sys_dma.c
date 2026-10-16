/*
*     File Name :                        bsp_sys_dma
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统级 DMA 初始化（串口收发）
*                                        包含 DMA 通道配置、全局缓冲区、中断处理
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_sys_dma.h"
#include "bsp_sys_uart.h"


/*-------------------------- 2. 变量 ---------------------------------*/
/* ---- DMA 线性缓冲区 ---- */
uint8_t g_uart_tx_buf[UART_TX_BUF_SIZE];
uint8_t g_uart_rx_buf[UART_RX_BUF_SIZE];
volatile uint16_t g_uart_tx_len = 0U;

/* ---- 接收环形缓冲区 ---- */
volatile uint8_t  g_ring_buf[UART_RX_RING_SIZE];
volatile uint16_t g_ring_write_index  = 0U;
volatile uint16_t g_ring_read_index   = 0U;
volatile uint16_t g_ring_dma_last_pos = 0U;

/* ---- 发送状态 ---- */
volatile uint8_t  g_uart_tx_busy = 0U;


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_SYS_DMA_UART_Init
Description: USART1 的 DMA 收发通道配置
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_SYS_DMA_UART_Init(void)
{
    
}
