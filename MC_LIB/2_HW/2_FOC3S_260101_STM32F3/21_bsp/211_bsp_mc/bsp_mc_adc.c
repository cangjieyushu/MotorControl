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
static void BSP_MC_ADC_CommonConfig(void)
{
    ADC_CommonInitTypeDef ADC_CommonInitStructure;

    ADC_CommonInitStructure.ADC_Mode             = ADC_Mode_Independent;      /* 三 ADC 独立，同源触发 */
    ADC_CommonInitStructure.ADC_Clock            = ADC_Clock_AsynClkMode;     /* 时钟由 RCC_ADCCLKConfig 设定 */
    ADC_CommonInitStructure.ADC_DMAAccessMode    = ADC_DMAAccessMode_1;       /* 12/10bit 分辨率下 DMA 模式 1 */
    ADC_CommonInitStructure.ADC_DMAMode          = ADC_DMAMode_OneShot;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = 5U;

    ADC_CommonInit(ADC1, &ADC_CommonInitStructure);   /* 配置 ADC12_COMMON */
    ADC_CommonInit(ADC3, &ADC_CommonInitStructure);   /* 配置 ADC34_COMMON */
}

static void BSP_MC_ADC_PowerUpCalib(ADC_TypeDef* ADCx)
{
    volatile Q32U_ delay;

    /* 1. 启动内部电压调节器 */
    ADC_VoltageRegulatorCmd(ADCx, ENABLE);

    /* 2. 延时 ≥ 10us */
    delay = 0x2000;
    while (delay--) { }

    /* 3. 使能 ADC */
    ADC_Cmd(ADCx, ENABLE);

    /* 4. 校准（单端模式） */
    ADC_SelectCalibrationMode(ADCx, ADC_CalibrationMode_Single);
    ADC_StartCalibration(ADCx);
    while (ADC_GetCalibrationStatus(ADCx) != RESET) { }
}


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
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InjectedInitTypeDef ADC_InjectedInitStructure;

    /* ---------------- 1. 三 ADC 公共配置 ---------------- */
    BSP_MC_ADC_CommonConfig();

    /* ============================================================
     * ADC1：主 ADC
     *   规则组：外部温度 + 母线电压（DMA 搬运）
     *   注入组：U 相电流（TIM8_TRGO 触发）
     * ============================================================ */
    ADC_InitStructure.ADC_Resolution            = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode    = ADC_ContinuousConvMode_Enable;
    ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;
    ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
    ADC_InitStructure.ADC_DataAlign             = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_OverrunMode           = ADC_OverrunMode_Disable;
    ADC_InitStructure.ADC_AutoInjMode           = ADC_AutoInjec_Disable;
    ADC_InitStructure.ADC_NbrOfRegChannel       = 2;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* 规则组：Rank 1 = 温度 PC2/ADC1_IN8，Rank 2 = 母线电压 PC3/ADC1_IN9 */
    ADC_RegularChannelConfig(ADC1, HW_MC_ADC_TEMP_Channel, 1, ADC_SampleTime_181Cycles5);
    ADC_RegularChannelConfig(ADC1, HW_MC_ADC_VBUS_Channel, 2, ADC_SampleTime_181Cycles5);

    /* 注入组：U 相电流（PA2/ADC1_IN3），TIM8_TRGO 下降沿触发 */
    ADC_InjectedInitStructure.ADC_ExternalTrigInjecConvEvent = ADC_ExternalTrigInjecConvEvent_7;
    ADC_InjectedInitStructure.ADC_ExternalTrigInjecEventEdge = ADC_ExternalTrigInjecEventEdge_FallingEdge;
    ADC_InjectedInitStructure.ADC_NbrOfInjecChannel          = 1;
    ADC_InjectedInitStructure.ADC_InjecSequence1             = HW_MC_ADC_U_CURRENT_Channel;
    ADC_InjectedInitStructure.ADC_InjecSequence2             = ADC_Channel_1;
    ADC_InjectedInitStructure.ADC_InjecSequence3             = ADC_Channel_1;
    ADC_InjectedInitStructure.ADC_InjecSequence4             = ADC_Channel_1;
    ADC_InjectedInit(ADC1, &ADC_InjectedInitStructure);

    ADC_InjectedChannelSampleTimeConfig(ADC1, HW_MC_ADC_U_CURRENT_Channel, ADC_SampleTime_19Cycles5);
    ADC_InjectedDiscModeCmd(ADC1, DISABLE);

    /* 使能注入组转换完成中断（只在 ADC1 上响应）*/
    ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);
    ADC_ITConfig(ADC1, ADC_IT_JEOC, ENABLE);

    BSP_MC_ADC_PowerUpCalib(ADC1);

    /* ============================================================
     * ADC2：从 ADC，注入组 = V 相电流（PA6/ADC2_IN3）
     * ============================================================ */
    ADC_InitStructure.ADC_ContinuousConvMode    = ADC_ContinuousConvMode_Disable;
    ADC_InitStructure.ADC_NbrOfRegChannel       = 1;
    ADC_Init(ADC2, &ADC_InitStructure);

    ADC_InjectedInitStructure.ADC_ExternalTrigInjecConvEvent = ADC_ExternalTrigInjecConvEvent_7;
    ADC_InjectedInitStructure.ADC_ExternalTrigInjecEventEdge = ADC_ExternalTrigInjecEventEdge_FallingEdge;
    ADC_InjectedInitStructure.ADC_NbrOfInjecChannel          = 1;
    ADC_InjectedInitStructure.ADC_InjecSequence1             = HW_MC_ADC_V_CURRENT_Channel;
    ADC_InjectedInitStructure.ADC_InjecSequence2             = ADC_Channel_1;
    ADC_InjectedInitStructure.ADC_InjecSequence3             = ADC_Channel_1;
    ADC_InjectedInitStructure.ADC_InjecSequence4             = ADC_Channel_1;
    ADC_InjectedInit(ADC2, &ADC_InjectedInitStructure);

    ADC_InjectedChannelSampleTimeConfig(ADC2, HW_MC_ADC_V_CURRENT_Channel, ADC_SampleTime_19Cycles5);
    ADC_InjectedDiscModeCmd(ADC2, DISABLE);

    BSP_MC_ADC_PowerUpCalib(ADC2);

    /* ============================================================
     * ADC3：从 ADC，注入组 = W 相电流（PB13/ADC3_IN5）
     * ============================================================ */
    ADC_InitStructure.ADC_ContinuousConvMode    = ADC_ContinuousConvMode_Disable;
    ADC_InitStructure.ADC_NbrOfRegChannel       = 1;
    ADC_Init(ADC3, &ADC_InitStructure);

    ADC_InjectedInitStructure.ADC_ExternalTrigInjecConvEvent = ADC_ExternalTrigInjecConvEvent_7;
    ADC_InjectedInitStructure.ADC_ExternalTrigInjecEventEdge = ADC_ExternalTrigInjecEventEdge_FallingEdge;
    ADC_InjectedInitStructure.ADC_NbrOfInjecChannel          = 1;
    ADC_InjectedInitStructure.ADC_InjecSequence1             = HW_MC_ADC_W_CURRENT_Channel;
    ADC_InjectedInitStructure.ADC_InjecSequence2             = ADC_Channel_1;
    ADC_InjectedInitStructure.ADC_InjecSequence3             = ADC_Channel_1;
    ADC_InjectedInitStructure.ADC_InjecSequence4             = ADC_Channel_1;
    ADC_InjectedInit(ADC3, &ADC_InjectedInitStructure);

    ADC_InjectedChannelSampleTimeConfig(ADC3, HW_MC_ADC_W_CURRENT_Channel, ADC_SampleTime_19Cycles5);
    ADC_InjectedDiscModeCmd(ADC3, DISABLE);

    BSP_MC_ADC_PowerUpCalib(ADC3);
}
