/*
*     File Name :                        bsp_uart
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             UART初始化
*/


#ifndef BSP_UART_H
#define BSP_UART_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_clk.h"
#include "hw_map.h"
#include "hw_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
#define USART1_TRANSMISSION_DATA    (HAL_HMI_UART->TDR)
#define USART1_RESCEIVE_DATA        (HAL_HMI_UART->RDR)

#define UART1_TX_BUF_SIZE            256U    /* 发送缓冲区大小 */
#define UART1_RX_BUF_SIZE            256U    /* 接收环形缓冲区大小 */


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/
extern uint8_t g_uart_rx_buf[UART1_RX_BUF_SIZE];
extern uint8_t g_uart_tx_buf[UART1_TX_BUF_SIZE];


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: BSP_USART_Init
Description: USART初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
void BSP_UART_Init(void);
void BSP_UART_DMA_Init(void);

#endif /* BSP_UART_H */
