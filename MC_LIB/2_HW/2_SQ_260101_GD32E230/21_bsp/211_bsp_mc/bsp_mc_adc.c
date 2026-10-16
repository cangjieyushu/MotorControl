/*
*     File Name :                        bsp_mc_adc
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             ADC 初始化
*                                        单 ADC1：注入组采样电机 BEMF/电流 + 规则组采样母线/温度/VR/VBG
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_mc_adc.h"


/*-------------------------- 2. 变量 ---------------------------------*/
/* 引用 bsp_mc_adc.c 中定义的规则组缓冲区 */
Q32U_ BSP_ADC_SYSTEM_BUFFER[10];


/*-------------------------- 3. 内部辅助函数 ----------------------------*/


/*-------------------------- 4. 公有接口实现 -----------------------------*/
/*
Function: BSP_MC_ADC_Init
Description: 电机控制用 ADC 初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_ADC_Init(void)
{
    /* ADC scan function enable */
    adc_special_function_config(ADC_SCAN_MODE, ENABLE);
    /* ADC data alignment config */
    adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
    
    // 使能连续转换模式 (CTN = 1)
    adc_special_function_config(ADC_CONTINUOUS_MODE, ENABLE);
    
    /* ADC channel length config */
    adc_channel_length_config(ADC_REGULAR_CHANNEL, 2U);
    /* ADC regular channel config */
    adc_regular_channel_config(0U, HW_MC_ADC_VBUS_Channel, ADC_SAMPLETIME_28POINT5);
    adc_regular_channel_config(1U, HW_MC_ADC_TEMP_Channel, ADC_SAMPLETIME_28POINT5);

    /* ADC trigger config */
    adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);
    adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_NONE);
    
    
    /* ADC DMA function enable */
    adc_dma_mode_enable();
    
    
    /* ADC channel length config */
    adc_channel_length_config(ADC_INSERTED_CHANNEL, 4U);
    /* ADC inserted channel config */
    adc_inserted_channel_config(0U, HW_MC_ADC_U_BEMF_Channel, ADC_SAMPLETIME_7POINT5);
    adc_inserted_channel_config(1U, HW_MC_ADC_V_BEMF_Channel, ADC_SAMPLETIME_7POINT5);
    adc_inserted_channel_config(2U, HW_MC_ADC_W_BEMF_Channel, ADC_SAMPLETIME_7POINT5);
    adc_inserted_channel_config(3U, HW_MC_ADC_CURRENT_Channel, ADC_SAMPLETIME_7POINT5);
    
    /* ADC trigger config */
    adc_external_trigger_config(ADC_INSERTED_CHANNEL, ENABLE);
    adc_external_trigger_source_config(ADC_INSERTED_CHANNEL, ADC_EXTTRIG_INSERTED_NONE);

    adc_interrupt_enable(ADC_INT_EOIC);
    
    /* enable ADC interface */
    adc_enable();
    Math_Delay_us(1000U);
    /* ADC calibration and reset calibration */
    adc_calibration_enable();
    
    adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
    
}
