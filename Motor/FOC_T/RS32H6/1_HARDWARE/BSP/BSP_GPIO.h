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

//ADC_SYSTYM
#define ADC_TEMP_GPIO_PORT          GPIOC
#define ADC_TEMP_PIN                GPIO_PIN_1
#define ADC_TEMP_Channel            ADC_CHANNEL_3

#define ADC_VR_GPIO_PORT            GPIOB
#define ADC_VR_PIN                  GPIO_PIN_5
#define ADC_VR_Channel              ADC_CHANNEL_7

#define ADC_VBUS_GPIO_PORT          GPIOD
#define ADC_VBUS_PIN                GPIO_PIN_5
#define ADC_VBUS_Channel            ADC_CHANNEL_14

#define ADC_VBG_Channel             ADC_CHANNEL_VBGINT

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

#endif /* BSP_GPIO_H */
