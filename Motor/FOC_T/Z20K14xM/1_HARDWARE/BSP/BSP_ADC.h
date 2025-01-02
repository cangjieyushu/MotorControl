/**************************************************************************************************
*     File Name :                        BSP_ADC.h
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             ADC初始化及应用层接口头文件
**************************************************************************************************/
#ifndef BSP_ADC_H
#define BSP_ADC_H

#include "MotorHal_cfg.h"

#define ADC_DATA_NUM_S          (3)     //应用层ADC采样通道个数

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

/**********************************************************************************************
Function: BSP_ADC_Init_S
Description: 应用层ADC初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_ADC_Init_S(void);

#endif /* BSP_ADC_H */
