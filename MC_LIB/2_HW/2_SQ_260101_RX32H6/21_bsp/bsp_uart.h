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
#define USART1_RESCEIVE_DATA        (UART1->DR)
#define USART1_TRANSMISSION_DATA    (UART1->DR)

#define USART2_RESCEIVE_DATA        (UART2->DR)
#define USART2_TRANSMISSION_DATA    (UART2->DR)


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: UART1_Enable_Rx
Description: USART1打开接收
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void UART1_Enable_Rx(void)
{
    SET_BIT(UART1->CR1, UART_CR1_RE);
}

/*
Function: UART1_Disable_Rx
Description: USART1关闭接收
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void UART1_Disable_Rx(void)
{
    CLEAR_BIT(UART1->CR1, UART_CR1_RE);
}

/*
Function: UART1_Enable_Tx
Description: USART1打开发送
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void UART1_Enable_Tx(void)
{
    SET_BIT(UART1->CR1, UART_CR1_TE);
}

/*
Function: UART1_Disable_Tx
Description: USART1关闭发送
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void UART1_Disable_Tx(void)
{
    CLEAR_BIT(UART1->CR1, UART_CR1_TE);
}

/*
Function: BSP_USART_Init
Description: USART初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
void BSP_USART_Init(void);

#endif /* BSP_UART_H */
