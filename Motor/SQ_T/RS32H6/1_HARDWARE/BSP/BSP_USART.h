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

#define USART1_RESCEIVE_DATA         UART1->DR
#define USART1_TRANSMISSION_DATA     UART1->DR

#define USART2_RESCEIVE_DATA         UART2->DR
#define USART2_TRANSMISSION_DATA     UART2->DR

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
