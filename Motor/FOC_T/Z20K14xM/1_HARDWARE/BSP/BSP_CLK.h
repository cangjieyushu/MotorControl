/**************************************************************************************************
*     File Name :                        BSP_CLK.h
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             时钟初始化及应用层接口头文件
**************************************************************************************************/
#ifndef BSP_CLK_H
#define BSP_CLK_H

#include "MotorHal_cfg.h"

#define HAL_M1PWM_CLK_MODULE            CLK_MCPWM0
#define HAL_M1PWM_SYSCTRL_MODULE        SYSCTRL_MCPWM0
#define HAL_M2PWM_CLK_MODULE            CLK_MCPWM1
#define HAL_M2PWM_SYSCTRL_MODULE        SYSCTRL_MCPWM1

/**********************************************************************************************
Function: BSP_CLK_Init
Description: 时钟初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_CLK_Init(void);

#endif /* BSP_CLK_H */
