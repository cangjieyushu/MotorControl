/*
*     File Name :                        bsp_adc
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             ADC初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_adc.h"


/*-------------------------- 2. 变量 ---------------------------------*/
Q32U_ BSP_ADC_SYSTEM_BUFFER[10];
Q32U_ BSP_ADC_MOTOR_BUFFER[10];


/*-------------------------- 3. 公有接口实现 -----------------------------*/
void BSP_ADC_Init(void)
{
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    ADC_TempSensorVrefintCmd(ENABLE);/*使能内部温度传感器*/

    /*通用控制寄存器的配置*/
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;                    /*DMA能*/
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                            /*独立模式*/
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;                         /*APB2的2分频*/
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;        /*两个采样阶段的延时5个时钟*/
    ADC_CommonInit(&ADC_CommonInitStructure);
    
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;                      /*12位模式*/
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;                                /*扫描模式*/
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                          /*连续转换*/
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; /*禁止触发检测 使用软件触发*/
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                      /*右对齐*/
    ADC_InitStructure.ADC_NbrOfConversion = 1;                                  /*只使用1通道 规则通为1*/
    ADC_Init(HAL_MOTOR_ADC,&ADC_InitStructure);
    
    ADC_RegularChannelConfig(HAL_MOTOR_ADC, ADC_TEMP_Channel, 1, ADC_SampleTime_84Cycles);
    
    ADC_InjectedSequencerLengthConfig(HAL_MOTOR_ADC, 4);
    ADC_InjectedChannelConfig(HAL_MOTOR_ADC, ADC_U_CURRENT_Channel, 1, ADC_SampleTime_3Cycles);
    ADC_InjectedChannelConfig(HAL_MOTOR_ADC, ADC_V_CURRENT_Channel, 2, ADC_SampleTime_3Cycles);
    ADC_InjectedChannelConfig(HAL_MOTOR_ADC, ADC_W_CURRENT_Channel, 3, ADC_SampleTime_3Cycles);
    ADC_InjectedChannelConfig(HAL_MOTOR_ADC, ADC_VBUS_Channel, 4, ADC_SampleTime_3Cycles);
    
    ADC_InjectedDiscModeCmd(HAL_MOTOR_ADC, DISABLE);
    ADC_ExternalTrigInjectedConvEdgeConfig(HAL_MOTOR_ADC, ADC_ExternalTrigInjecConvEdge_Falling);
    ADC_ExternalTrigInjectedConvConfig(HAL_MOTOR_ADC, ADC_ExternalTrigInjecConv_T1_TRGO);
    
    ADC_ClearITPendingBit(HAL_MOTOR_ADC, ADC_IT_JEOC);
    ADC_ITConfig(HAL_MOTOR_ADC, ADC_IT_JEOC, ENABLE);
    
    ADC_Cmd(HAL_MOTOR_ADC, ENABLE);
    ADC_SoftwareStartConv(HAL_MOTOR_ADC);
}

void BSP_DMA_Init(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    Q32U_ timeout = 0xFFFFU;
    while(DMA_GetCmdStatus(DMA2_Stream0) != DISABLE && timeout--);

    DMA_InitStructure.DMA_Channel = DMA_Channel_0;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (Q32U_)&HAL_MOTOR_ADC->DR; // 修正
    DMA_InitStructure.DMA_Memory0BaseAddr = (Q32U_)BSP_ADC_SYSTEM_BUFFER;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = 1; // 与规则通道数一致
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream0, &DMA_InitStructure);
    DMA_Cmd(DMA2_Stream0, ENABLE);

    // 关联 ADC 与 DMA
    ADC_DMACmd(HAL_MOTOR_ADC, ENABLE);
    ADC_DMARequestAfterLastTransferCmd(HAL_MOTOR_ADC, ENABLE);
}
