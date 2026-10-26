/**
 * @file    bsp_mc_adc.c
 * @brief   ADC 初始化
 *          - ADC1 注入组采样 U/V/W 三相电流 + 母线电压（TIM1_TRGO 触发）
 *          - ADC1 规则组采样外部温度
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_mc_adc.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */
Q32U_ BSP_ADC_SYSTEM_BUFFER[10];   /* 规则组数据缓冲区（预留） */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  电机控制用 ADC 初始化
 */
void BSP_MC_ADC_Init(void)
{
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_InitTypeDef       ADC_InitStructure;

    ADC_TempSensorVrefintCmd(ENABLE);   /* 使能内部温度传感器 */

    /* ---- 1. 公共控制寄存器配置 ---- */
    ADC_CommonInitStructure.ADC_DMAAccessMode    = ADC_DMAAccessMode_Disabled;        /* DMA 访问模式 */
    ADC_CommonInitStructure.ADC_Mode             = ADC_Mode_Independent;              /* 独立模式 */
    ADC_CommonInitStructure.ADC_Prescaler        = ADC_Prescaler_Div4;                /* APB2 4 分频 */
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;      /* 两采样阶段延时 5 时钟 */
    ADC_CommonInit(&ADC_CommonInitStructure);

    /* ---- 2. 规则组参数配置 ---- */
    ADC_InitStructure.ADC_Resolution           = ADC_Resolution_12b;                  /* 12 位 */
    ADC_InitStructure.ADC_ScanConvMode         = ENABLE;                              /* 扫描模式 */
    ADC_InitStructure.ADC_ContinuousConvMode   = ENABLE;                              /* 连续转换 */
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;       /* 禁止触发，软件触发 */
    ADC_InitStructure.ADC_DataAlign            = ADC_DataAlign_Right;                 /* 右对齐 */
    ADC_InitStructure.ADC_NbrOfConversion      = 1;                                   /* 规则组仅 1 通道 */
    ADC_Init(HW_MC_ADC, &ADC_InitStructure);

    ADC_RegularChannelConfig(HW_MC_ADC, HW_MC_ADC_TEMP_Channel, 1, ADC_SampleTime_84Cycles);
    
    /* ---- 3. 注入组配置：U/V/W 电流 + 母线电压 ---- */
    ADC_InjectedSequencerLengthConfig(HW_MC_ADC, 4);
    ADC_InjectedChannelConfig(HW_MC_ADC, HW_MC_ADC_U_CURRENT_Channel, 1, ADC_SampleTime_3Cycles);
    ADC_InjectedChannelConfig(HW_MC_ADC, HW_MC_ADC_V_CURRENT_Channel, 2, ADC_SampleTime_3Cycles);
    ADC_InjectedChannelConfig(HW_MC_ADC, HW_MC_ADC_W_CURRENT_Channel, 3, ADC_SampleTime_3Cycles);
    ADC_InjectedChannelConfig(HW_MC_ADC, HW_MC_ADC_VBUS_Channel,      4, ADC_SampleTime_3Cycles);

    ADC_InjectedDiscModeCmd(HW_MC_ADC, DISABLE);

    /* ---- 4. 注入组外部触发：TIM1_TRGO 下降沿 ---- */
    ADC_ExternalTrigInjectedConvEdgeConfig(HW_MC_ADC, ADC_ExternalTrigInjecConvEdge_Falling);
    ADC_ExternalTrigInjectedConvConfig(HW_MC_ADC, ADC_ExternalTrigInjecConv_T1_TRGO);

    /* ---- 5. 注入组转换完成中断 ---- */
    ADC_ClearITPendingBit(HW_MC_ADC, ADC_IT_JEOC);
    ADC_ITConfig(HW_MC_ADC, ADC_IT_JEOC, DISABLE);

    /* ---- 6. 使能 ADC 并启动规则组首次转换 ---- */
    ADC_Cmd(HW_MC_ADC, ENABLE);
    ADC_SoftwareStartConv(HW_MC_ADC);
}
