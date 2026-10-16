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
    ADC_Reg_InitTypeDef      ADC_Reg_InitStruct = {0};
    ADC_REG_RankInitTypeDef  ADC_REG_RankInitStruct = {0};
    ADC_Inj_InitTypeDef      ADC_Inj_InitStruct = {0};
    ADC_INJ_RankInitTypeDef  ADC_INJ_RankInitStruct = {0};

    /* ---------------- 1. 规则组：系统采样 ---------------- */
    ADC_Reg_InitStruct.TriggerSource        = ADC_CR2_EXTSEL_SWSTART;
    ADC_Reg_InitStruct.Continuous           = ADC_CR2_CONT_CONTINUOUS;
    ADC_Reg_InitStruct.ScanMode             = ADC_CR1_SCAN_ENABLE;
    ADC_Reg_InitStruct.DataAlignment        = ADC_CR2_ALIGN_RIGHT;
    ADC_Reg_InitStruct.AnalogWatchDog       = ADC_CR1_AWD_DISABLE;
    ADC_Reg_InitStruct.AWDChannelGroup      = ADC_AWD_DISABLE;
    ADC_Reg_InitStruct.RegularDiscont       = ADC_CR1_DISCEN_DISABLE;
    ADC_Reg_InitStruct.RegularDiscontNumber = ADC_CR1_DISCONT_DISABLE;
    ADC_Reg_InitStruct.EOCOption            = ADC_EOC_OPT_DISABLE;
    ADC_Reg_Init(HW_MC_ADC, &ADC_Reg_InitStruct);

    ADC_REG_RankInitStruct.Length = ADC_SQRL_SCAN_4RANKS;
    ADC_REG_RankInitStruct.Rank[0].Channel      = HW_MC_ADC_VBUS_Channel;
    ADC_REG_RankInitStruct.Rank[0].SamplingTime = ADC_SAMPLINGTIME_48p5CYCLES;
    ADC_REG_RankInitStruct.Rank[1].Channel      = HW_MC_ADC_TEMP_Channel;
    ADC_REG_RankInitStruct.Rank[1].SamplingTime = ADC_SAMPLINGTIME_48p5CYCLES;
    ADC_REG_RankInitStruct.Rank[2].Channel      = HW_MC_ADC_VR_Channel;
    ADC_REG_RankInitStruct.Rank[2].SamplingTime = ADC_SAMPLINGTIME_48p5CYCLES;
    ADC_REG_RankInitStruct.Rank[3].Channel      = ADC_CHANNEL_VBGINT;
    ADC_REG_RankInitStruct.Rank[3].SamplingTime = ADC_SAMPLINGTIME_48p5CYCLES;
    ADC_REG_RankInit(HW_MC_ADC, &ADC_REG_RankInitStruct);

    /* ---------------- 2. 注入组：电机采样 ---------------- */
    ADC_Inj_InitStruct.TriggerSource        = ADC_CR2_JEXTSEL_JSWSTART;
    ADC_Inj_InitStruct.ScanMode             = ADC_CR1_SCAN_ENABLE;
    ADC_Inj_InitStruct.DataAlignment        = ADC_CR2_ALIGN_RIGHT;
    ADC_Inj_InitStruct.TrigAuto             = ADC_CR1_JAUTO_INDEPENDENT;
    ADC_Inj_InitStruct.AnalogWatchDog       = ADC_CR1_AWD_DISABLE;
    ADC_Inj_InitStruct.AWDChannelGroup      = ADC_AWD_DISABLE;
    ADC_Inj_InitStruct.InjectDiscont        = ADC_CR1_JDISCEN_DISABLE;
    ADC_Inj_InitStruct.EOCOption            = ADC_EOC_OPT_DISABLE;
    ADC_Inj_Init(HW_MC_ADC, &ADC_Inj_InitStruct);

    ADC_INJ_RankInitStruct.Length = ADC_JSQRL_SCAN_4RANKS;
    ADC_INJ_RankInitStruct.Rank[0].Channel      = HW_MC_ADC_U_BEMF_Channel;
    ADC_INJ_RankInitStruct.Rank[0].SamplingTime = ADC_SAMPLINGTIME_25p5CYCLES;
    ADC_INJ_RankInitStruct.Rank[1].Channel      = HW_MC_ADC_V_BEMF_Channel;
    ADC_INJ_RankInitStruct.Rank[1].SamplingTime = ADC_SAMPLINGTIME_25p5CYCLES;
    ADC_INJ_RankInitStruct.Rank[2].Channel      = HW_MC_ADC_W_BEMF_Channel;
    ADC_INJ_RankInitStruct.Rank[2].SamplingTime = ADC_SAMPLINGTIME_25p5CYCLES;
    ADC_INJ_RankInitStruct.Rank[3].Channel      = HW_MC_ADC_CURRENT_Channel;
    ADC_INJ_RankInitStruct.Rank[3].SamplingTime = ADC_SAMPLINGTIME_25p5CYCLES;
    ADC_INJ_RankInit(HW_MC_ADC, &ADC_INJ_RankInitStruct);

    /* ---------------- 3. 使能与校准 ---------------- */
    ADC_Enable_ADON(HW_MC_ADC);

    ADC_Enable_IT(HW_MC_ADC, ADC_CR1_JEOCIE);
    ADC_Clear_SR(HW_MC_ADC, ADC_SR_JEOC);

    ADC_Trig_CAL(HW_MC_ADC);
    while (ADC_Get_CAL(HW_MC_ADC) != 0) { }

    /* 启动规则组首次转换 */
    ADC_Start_SW(HW_MC_ADC);
    while (ADC_Get_SR(HW_MC_ADC, ADC_SR_EOC) == 0) { }
    ADC_Clear_SR(HW_MC_ADC, ADC_SR_EOC);
}
