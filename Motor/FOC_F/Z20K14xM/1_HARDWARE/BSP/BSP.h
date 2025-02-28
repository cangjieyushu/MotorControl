/**************************************************************************************************
*     File Name :                        BSP.h
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             BSP层接口头文件
**************************************************************************************************/

#include "BSP_ADC.h"
#include "BSP_CLK.h"
#include "BSP_DMA.h"
#include "BSP_GPIO.h"
#include "BSP_ISR.h"
#include "BSP_PWM.h"
#include "BSP_TIM.h"
#include "BSP_TMU.h"
#include "BSP_USART.h"
#include "BSP_WDG.h"

#if(HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
#define BSP_ADC_Init                    BSP_ADC_Init_Three_Shunt
#define BSP_DMA_Init                    BSP_DMA_Init_Three_Shunt
#define BSP_PWM_Init                    BSP_PWM_Init_Three_Shunt
#else
#define BSP_ADC_Init                    BSP_ADC_Init_One_Shunt
#define BSP_DMA_Init                    BSP_DMA_Init_One_Shunt
#define BSP_PWM_Init                    BSP_PWM_Init_One_Shunt
#endif
