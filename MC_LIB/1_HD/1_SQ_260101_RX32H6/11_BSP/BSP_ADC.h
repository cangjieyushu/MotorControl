/**************************************************************************************************
*     File Name :                        BSP_ADC.h
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             ADC初始化及应用层接口头文件
**************************************************************************************************/
#ifndef BSP_ADC_H
#define BSP_ADC_H

#include "HAL_CFG.h"

#define BSP_ADC_DATA_READ_VBUS      HAL_MOTOR_ADC->DATA1
#define BSP_ADC_DATA_READ_TEMP      HAL_MOTOR_ADC->DATA2
#define BSP_ADC_DATA_READ_VR        HAL_MOTOR_ADC->DATA3
#define BSP_ADC_DATA_READ_VBG       HAL_MOTOR_ADC->DATA4

/**********************************************************************************************
Function: BSP_ADC_Init
Description: 电机控制用ADC初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_ADC_Init(void);

#endif /* BSP_ADC_H */
