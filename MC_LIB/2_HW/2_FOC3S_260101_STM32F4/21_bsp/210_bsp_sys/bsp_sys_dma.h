/*
*     File Name :                        bsp_sys_dma
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统级 DMA 初始化（串口收发）
*                                        包含 DMA 通道配置、全局缓冲区、中断处理
*/


#ifndef BSP_SYS_DMA_H
#define BSP_SYS_DMA_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
/* 缓冲区大小 */
#define UART_TX_BUF_SIZE           (256U)      /* 发送缓冲区大小 */
#define UART_RX_BUF_SIZE           (256U)      /* 接收环形缓冲区大小 */

/* UART_TX_BUF_SIZE / UART_RX_BUF_SIZE 定义在 bsp_sys_uart.h 中 */
#define UART_RX_RING_SIZE           (UART_RX_BUF_SIZE)   /* 环形缓冲区字节数 */


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/
/* ---- 数据缓冲区 ---- */
extern uint8_t g_uart_tx_buf[UART_TX_BUF_SIZE];
extern uint8_t g_uart_rx_buf[UART_RX_BUF_SIZE];
extern volatile uint16_t g_uart_tx_len;

/* ---- 环形缓冲区 ---- */
extern volatile uint8_t  g_ring_buf[UART_RX_RING_SIZE];
extern volatile uint16_t g_ring_write_index;
extern volatile uint16_t g_ring_read_index;
extern volatile uint16_t g_ring_dma_last_pos;

/* ---- 发送状态（供 RS485 方向切换使用）---- */
extern volatile uint8_t  g_uart_tx_busy;    /* 1 = DMA 正在发送 */


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: BSP_SYS_DMA_UART_Init
Description: USART1 的 DMA 收发通道配置
             - DMA1_Channel5：USART1_RX（循环模式）
             - DMA1_Channel4：USART1_TX（单次模式）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_SYS_DMA_UART_Init(void);


#endif /* BSP_SYS_DMA_H */
