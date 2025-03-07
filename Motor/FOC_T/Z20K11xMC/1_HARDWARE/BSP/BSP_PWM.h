/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef BSP_PWM_H
#define BSP_PWM_H

#include "MotorHal_cfg.h"

/**********************************************************************************************
Function: BSP_PWM_Init_Three_Shunt
Description: 电机控制用PWM初始化
Input: 故障中断函数
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_PWM_Init_Three_Shunt(isr_cb_t *M1FaultIntCbf);

/**********************************************************************************************
Function: BSP_PWM_Init_One_Shunt
Description: 电机控制用PWM初始化
Input: 故障中断函数
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_PWM_Init_One_Shunt(isr_cb_t *M1FaultIntCbf);

#endif /* BSP_PWM_H */
