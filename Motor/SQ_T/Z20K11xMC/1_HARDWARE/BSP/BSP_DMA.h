/**************************************************************************************************
*     File Name :                        BSP_DMA.h
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             DMA初始化及应用层接口头文件
**************************************************************************************************/
#ifndef BSP_DMA_H
#define BSP_DMA_H

#include "MotorHal_cfg.h"

#define BSP_ADC_READ_DATA_VBUS      (Hal_AdcLoopData[4] & 0x00000FFFU)
#define BSP_ADC_READ_DATA_VR        (Hal_AdcLoopData[5] & 0x00000FFFU)

/**********************************************************************************************
Function: BSP_DMA_Init
Description: 电机控制用DMA初始化
Input: 电流环中断函数
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_DMA_Init(void);

extern Q32U_ Hal_AdcLoopData[8];

#endif /* BSP_DMA_H */
