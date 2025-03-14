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

//ADC数据接口宏定义
#if(HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
#define BSP_ADC_READ_DATA_VBUS              (Hal_AdcLoopData[3] & 0x00000FFFU)
#elif(HAL_CURRENT_SAMPLE_MODE == HAL_ONE_SHUNT)
#define BSP_ADC_READ_DATA_VBUS              (Hal_AdcMapData[2] & 0x00000FFFU)
#endif

#define BSP_ADC_READ_DATA_VR                (Hal_AdcLoopData_S[0] & 0x00000FFFU)
#define BSP_ADC_READ_DATA_TEMP              (Hal_AdcLoopData_S[1] & 0x00000FFFU)

/**********************************************************************************************
Function: BSP_DMA_Init_Three_Shunt
Description: 电机控制用DMA初始化
Input: 电流环中断函数
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_DMA_Init_Three_Shunt(isr_cb_t *DMADoneCbf);

/**********************************************************************************************
Function: BSP_DMA_Init_One_Shunt
Description: 电机控制用DMA初始化
Input: 电流环中断函数
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_DMA_Init_One_Shunt(isr_cb_t *DMADoneCbf);

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

extern uint32_t Hal_AdcLoopData[24];
extern uint32_t Hal_AdcMapData[24];
extern uint32_t Hal_AdcLoopData_S[24];

#endif /* BSP_DMA_H */
