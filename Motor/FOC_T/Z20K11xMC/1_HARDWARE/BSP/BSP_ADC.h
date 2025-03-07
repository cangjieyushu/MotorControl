/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef BSP_ADC_H
#define BSP_ADC_H

#include "MotorHal_cfg.h"

/**********************************************************************************************
Function: BSP_ADC_Init_Three_Shunt
Description: 电机控制用ADC初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_ADC_Init_Three_Shunt(isr_cb_t *ADCDoneCbf);

/**********************************************************************************************
Function: BSP_ADC_Init_One_Shunt
Description: 电机控制用ADC初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_ADC_Init_One_Shunt(isr_cb_t *ADCDoneCbf);

#endif /* BSP_ADC_H */
