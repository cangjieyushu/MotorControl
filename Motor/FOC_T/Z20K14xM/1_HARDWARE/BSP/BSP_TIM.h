/**************************************************************************************************
*     File Name :                        BSP_TIM.h
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             TIM初始化及应用层接口头文件
**************************************************************************************************/
#ifndef BSP_TIM_H
#define BSP_TIM_H

#include "MotorHal_cfg.h"

/**********************************************************************************************
Function: BSP_TIM_Init
Description: 1ms中断TIM初始化
Input: 速度环中断函数
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_TIM_Init(isr_cb_t *StimIntCbf);

/**********************************************************************************************
Function: BSP_HALL_Init
Description: HALL换向时间计数器初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_HALL_Init(void);

#endif /* BSP_TIM_H */
