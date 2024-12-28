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

#define BSP_ADC_READ_DATA_VBUS              (ADC1->JDR4)
#define BSP_ADC_READ_DATA_TEMP              (0U)
#define BSP_ADC_READ_DATA_VR                (4095U)
#define BSP_ADC_READ_DATA_VBG               (0U)

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
void BSP_DMA_Init(void);
	
#endif /* BSP_ADC_H */
