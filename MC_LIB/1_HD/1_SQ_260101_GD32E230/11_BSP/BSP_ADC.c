/**************************************************************************************************
*     File Name :                        BSP_ADC.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             ADC初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_ADC.h"

/**********************************************************************************************
Function: BSP_ADC_Init
Description: 电机控制用ADC初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_ADC_Init(void)
{
    /* ADC scan function enable */
    adc_special_function_config(ADC_SCAN_MODE, ENABLE);
    /* ADC data alignment config */
    adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
    
    /* ADC channel length config */
    adc_channel_length_config(ADC_REGULAR_CHANNEL, 2U);
    /* ADC regular channel config */
    adc_regular_channel_config(0U, ADC_VBUS_Channel, ADC_SAMPLETIME_28POINT5);
    adc_regular_channel_config(1U, ADC_TEMP_Channel, ADC_SAMPLETIME_28POINT5);

    /* ADC trigger config */
    adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);
    adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_NONE);
    
    
    /* ADC DMA function enable */
    adc_dma_mode_enable();
    
    
    /* ADC channel length config */
    adc_channel_length_config(ADC_INSERTED_CHANNEL, 4U);
    /* ADC inserted channel config */
    adc_inserted_channel_config(0U, ADC_U_BEMF_Channel, ADC_SAMPLETIME_7POINT5);
    adc_inserted_channel_config(1U, ADC_V_BEMF_Channel, ADC_SAMPLETIME_7POINT5);
    adc_inserted_channel_config(2U, ADC_W_BEMF_Channel, ADC_SAMPLETIME_7POINT5);
    adc_inserted_channel_config(3U, ADC_PHASE_Channel, ADC_SAMPLETIME_7POINT5);
    
    /* ADC trigger config */
    adc_external_trigger_config(ADC_INSERTED_CHANNEL, ENABLE);
    adc_external_trigger_source_config(ADC_INSERTED_CHANNEL, ADC_EXTTRIG_INSERTED_NONE);

    adc_interrupt_enable(ADC_INT_EOIC);
    
    /* enable ADC interface */
    adc_enable();
    Math_Delay_us(1000U);
    /* ADC calibration and reset calibration */
    adc_calibration_enable();
    
}

/**********************************************************************************************
Function: BSP_ADC_S_Enable
Description: 系统ADC使能
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_ADC_S_Enable(Q32U_* adcbuffer)
{
    adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
}
