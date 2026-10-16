/*
*     File Name :                        bsp_mc_adc
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             ADC初始化
*                                        三 ADC 同步采样三相电流 + ADC1 规则组 DMA 搬运电压/温度
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
Description: 电机控制用ADC初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_ADC_Init(void)
{
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    ADC_TempSensorVrefintCmd(ENABLE);/*使能内部温度传感器*/

    /*通用控制寄存器的配置*/
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;                    /*DMA能*/
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                            /*独立模式*/
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;                         /*APB2的4分频*/
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;        /*两个采样阶段的延时5个时钟*/
    ADC_CommonInit(&ADC_CommonInitStructure);
    
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;                      /*12位模式*/
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;                                /*扫描模式*/
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                          /*连续转换*/
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; /*禁止触发检测 使用软件触发*/
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                      /*右对齐*/
    ADC_InitStructure.ADC_NbrOfConversion = 1;                                  /*只使用1通道 规则通为1*/
    ADC_Init(HW_MC_ADC,&ADC_InitStructure);
    
    ADC_RegularChannelConfig(HW_MC_ADC, HW_MC_ADC_TEMP_Channel, 1, ADC_SampleTime_84Cycles);
    
    ADC_InjectedSequencerLengthConfig(HW_MC_ADC, 4);
    ADC_InjectedChannelConfig(HW_MC_ADC, HW_MC_ADC_U_CURRENT_Channel, 1, ADC_SampleTime_3Cycles);
    ADC_InjectedChannelConfig(HW_MC_ADC, HW_MC_ADC_V_CURRENT_Channel, 2, ADC_SampleTime_3Cycles);
    ADC_InjectedChannelConfig(HW_MC_ADC, HW_MC_ADC_W_CURRENT_Channel, 3, ADC_SampleTime_3Cycles);
    ADC_InjectedChannelConfig(HW_MC_ADC, HW_MC_ADC_VBUS_Channel, 4, ADC_SampleTime_3Cycles);
    
    ADC_InjectedDiscModeCmd(HW_MC_ADC, DISABLE);
    ADC_ExternalTrigInjectedConvEdgeConfig(HW_MC_ADC, ADC_ExternalTrigInjecConvEdge_Falling);
    ADC_ExternalTrigInjectedConvConfig(HW_MC_ADC, ADC_ExternalTrigInjecConv_T1_TRGO);
    
    ADC_ClearITPendingBit(HW_MC_ADC, ADC_IT_JEOC);
    ADC_ITConfig(HW_MC_ADC, ADC_IT_JEOC, ENABLE);
    
    ADC_Cmd(HW_MC_ADC, ENABLE);
    ADC_SoftwareStartConv(HW_MC_ADC);
}
