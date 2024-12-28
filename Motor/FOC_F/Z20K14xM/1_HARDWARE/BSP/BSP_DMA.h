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

//ADC数据地址位
#define HAL_ADC_DATA_ADDRESS    (ADC0_BASE_ADDR + 0x20U)
#define HAL_ADC_DATA_ADDRESS_S  (ADC1_BASE_ADDR + 0x20U)

//ADC数据接口宏定义
#if(HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
#define BSP_ADC_READ_DATA_VBUS              (Hal_AdcLoopData[3] & 0x00000FFFU)
#else
#define BSP_ADC_READ_DATA_VBUS              (Hal_AdcMapData[2] & 0x00000FFFU)
#endif

#define BSP_ADC_READ_DATA_TEMP              (Hal_AdcLoopData_S[1] & 0x00000FFFU)
#define BSP_ADC_READ_DATA_VR                (Hal_AdcLoopData_S[0] & 0x00000FFFU)
#define BSP_ADC_READ_DATA_VBG               (Hal_AdcLoopData_S[2] & 0x00000FFFU)

/**********************************************************************************************
Function: DMA_ADC_Init
Description: 电机控制用DMA初始化
Input: 电流环中断函数
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_DMA_Init(isr_cb_t *DMADoneCbf);

/**********************************************************************************************
Function: BSP_DMA_Init_S
Description: 应用层DMA初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_DMA_Init_S(void);

extern uint32_t Hal_AdcLoopData[8];
extern uint32_t Hal_AdcMapData[8];
extern uint32_t Hal_AdcLoopData_S[8];

#endif /* BSP_DMA_H */
