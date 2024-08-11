/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_ADC.h"
#include "BSP_GPIO.h"

void BSP_ADC_Init(void)
{
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef ADC_InitStructure;

	ADC_TempSensorVrefintCmd(ENABLE);/*使能内部温度传感器*/

	/*通用控制寄存器的配置*/
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;            /*DMA能*/
	ADC_CommonInitStructure.ADC_Mode          = ADC_Mode_Independent;           /*独立模式*/
	ADC_CommonInitStructure.ADC_Prescaler     = ADC_Prescaler_Div2;             /*APB2的2分频*/
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;/*两个采样阶段的延时5个时钟*/
	ADC_CommonInit(&ADC_CommonInitStructure);
	ADC_InitStructure.ADC_Resolution        = ADC_Resolution_12b;               /*12位模式*/
	ADC_InitStructure.ADC_ScanConvMode      = ENABLE;                           /*扫描模式*/
	ADC_InitStructure.ADC_ContinuousConvMode    = ENABLE;                       /*连续转换*/
	ADC_InitStructure.ADC_ExternalTrigConvEdge  = ADC_ExternalTrigConvEdge_None;/*禁止触发检测 使用软件触发*/
	ADC_InitStructure.ADC_DataAlign         = ADC_DataAlign_Right;              /*右对齐*/
	ADC_InitStructure.ADC_NbrOfConversion   = 1;                                /*只使用1通道 规则通为1*/
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
    
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
    
	ADC_Cmd(ADC1, ENABLE);
    ADC_SoftwareStartConv(ADC1);
}
