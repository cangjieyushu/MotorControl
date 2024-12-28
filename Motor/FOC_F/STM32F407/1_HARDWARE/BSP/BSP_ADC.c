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
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef ADC_InitStructure;

	ADC_TempSensorVrefintCmd(ENABLE);/*使能内部温度传感器*/

	/*通用控制寄存器的配置*/
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;             /*DMA能*/
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                            /*独立模式*/
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;                         /*APB2的2分频*/
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;        /*两个采样阶段的延时5个时钟*/
	ADC_CommonInit(&ADC_CommonInitStructure);
    
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;                      /*12位模式*/
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;                                /*扫描模式*/
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                          /*连续转换*/
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; /*禁止触发检测 使用软件触发*/
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                      /*右对齐*/
	ADC_InitStructure.ADC_NbrOfConversion = 1;                                  /*只使用1通道 规则通为1*/
	ADC_Init(ADC1,&ADC_InitStructure);
    
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_84Cycles);
    
    ADC_InjectedSequencerLengthConfig(ADC1, 4);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_15Cycles);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_6, 2, ADC_SampleTime_15Cycles);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_15Cycles);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_9, 4, ADC_SampleTime_15Cycles);
    
    ADC_InjectedDiscModeCmd(ADC1, DISABLE);
    ADC_ExternalTrigInjectedConvEdgeConfig(ADC1, ADC_ExternalTrigInjecConvEdge_Falling);
    ADC_ExternalTrigInjectedConvConfig(ADC1, ADC_ExternalTrigInjecConv_T1_TRGO);
    
    ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);
    ADC_ITConfig(ADC1, ADC_IT_JEOC, ENABLE);
    
	ADC_Cmd(ADC1, ENABLE);
    ADC_SoftwareStartConv(ADC1);
}

uint16_t ADC_INT_RAW_DATA[4] = {0,0,0,0};

void BSP_DMA_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	while(DMA_GetCmdStatus(DMA2_Stream0) != DISABLE);                               /*等待DMA可以配置*/
	 
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;                                  /*DMA通道0*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)0;                         /*外设地址*/
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)ADC_INT_RAW_DATA;             /*存取器地址*/
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;                         /*方向从外设到内存*/
	DMA_InitStructure.DMA_BufferSize = 1;                                           /*数据传输的数量为1*/
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;                /*地址不增加*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                         /*地址不增加*/
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;     /*数据长度半字*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;             /*数据长度半字*/
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;                             /*高优先级*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                                 /*循环模式*/
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;                          /*禁止FIFO*/
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;               /*FIFO的值*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;                     /*单次传输*/
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;             /*单次传输*/
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);/**/
    
    DMA_Cmd(DMA2_Stream0, ENABLE);
}
