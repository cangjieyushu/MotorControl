/**************************************************************************************************
*     File Name :                        BSP_GPIO.h
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             GPIO初始化及应用层接口头文件
**************************************************************************************************/
#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include "MotorHal_cfg.h"

/**********************************************************************************************
Function: BSP_GPIO_Init
Description: GPIO初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_GPIO_Init(void);

/**********************************************************************************************
Function: BSP_GPIO_Read_SW0_State
Description: 按键0状态读取
Input: 无
Output: 无
Input_Output: 无
Return: 按键0状态
Author: CJYS
***********************************************************************************************/
Q32U_ BSP_GPIO_Read_SW0_State(void);

/**********************************************************************************************
Function: BSP_GPIO_Read_SW1_State
Description: 按键1状态读取
Input: 无
Output: 无
Input_Output: 无
Return: 按键1状态
Author: CJYS
***********************************************************************************************/
Q32U_ BSP_GPIO_Read_SW1_State(void);

/**********************************************************************************************
Function: BSP_GPIO_Read_SW2_State
Description: 按键2状态读取
Input: 无
Output: 无
Input_Output: 无
Return: 按键2状态
Author: CJYS
***********************************************************************************************/
Q32U_ BSP_GPIO_Read_SW2_State(void);

#endif /* BSP_GPIO_H */
