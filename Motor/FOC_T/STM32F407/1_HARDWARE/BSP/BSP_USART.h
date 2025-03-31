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

#define USART1_RESCEIVE_DATA        USART1->DR
#define USART1_TRANSMISSION_DATA    USART1->DR

#define USART2_RESCEIVE_DATA        USART2->DR
#define USART2_TRANSMISSION_DATA    USART2->DR

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
    SET_BIT(USART1->CR1, USART_CR1_RE);
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
    CLEAR_BIT(USART1->CR1, USART_CR1_RE);
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
    SET_BIT(USART1->CR1, USART_CR1_TE);
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
    CLEAR_BIT(USART1->CR1, USART_CR1_TE);
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
    SET_BIT(USART2->CR1, USART_CR1_RE);
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
    CLEAR_BIT(USART2->CR1, USART_CR1_RE);
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
    SET_BIT(USART2->CR1, USART_CR1_TE);
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
    CLEAR_BIT(USART2->CR1, USART_CR1_TE);
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
