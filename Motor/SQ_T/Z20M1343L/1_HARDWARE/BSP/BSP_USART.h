/**************************************************************************************************
*     File Name :                        BSP_USART.h
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             USART初始化及应用层接口头文件
**************************************************************************************************/
#ifndef BSP_USART_H
#define BSP_USART_H

#include "MotorHal_cfg.h"

/*PRQA S 0303 ++*/
static Reg_Uart_WType* const Uart_RegWPtr = (Reg_Uart_WType*)UART_BASE_ADDR;
/*PRQA S 0303 --*/

#define USART1_RESCEIVE_DATA        Uart_RegWPtr->UART_RAR
#define USART1_TRANSMISSION_DATA    Uart_RegWPtr->UART_TAR

#define USART2_RESCEIVE_DATA        Uart_RegWPtr->UART_RAR
#define USART2_TRANSMISSION_DATA    Uart_RegWPtr->UART_TAR

/**********************************************************************************************
Function: USART1_Enable_Rx
Description: USART1打开接收
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void USART1_Enable_Rx(void)
{
    
}

/**********************************************************************************************
Function: USART1_Disable_Rx
Description: USART1关闭接收
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void USART1_Disable_Rx(void)
{
    
}

/**********************************************************************************************
Function: USART1_Enable_Tx
Description: USART1打开发送
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void USART1_Enable_Tx(void)
{
    
}

/**********************************************************************************************
Function: USART1_Disable_Tx
Description: USART1关闭发送
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void USART1_Disable_Tx(void)
{
    
}

/**********************************************************************************************
Function: USART2_Enable_Rx
Description: USART2打开接收
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void USART2_Enable_Rx(void)
{
    
}

/**********************************************************************************************
Function: USART2_Disable_Rx
Description: USART2关闭接收
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void USART2_Disable_Rx(void)
{
    
}

/**********************************************************************************************
Function: USART2_Enable_Tx
Description: USART2打开发送
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void USART2_Enable_Tx(void)
{
    
}

/**********************************************************************************************
Function: USART2_Disable_Tx
Description: USART2关闭发送
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void USART2_Disable_Tx(void)
{
    
}

/**********************************************************************************************
Function: BSP_USART_Init
Description: USART初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_USART_Init(void);

#endif /* BSP_USART_H */
