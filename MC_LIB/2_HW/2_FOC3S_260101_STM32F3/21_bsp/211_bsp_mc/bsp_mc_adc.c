/**
 * @file    bsp_mc_adc.c
 * @brief   ADC 初始化
 *          - 三 ADC 同步采样三相电流（注入组，TIM8_CC4 触发）
 *          - ADC1 规则组 DMA 搬运电压/温度到 BSP_ADC_SYSTEM_BUFFER
 *          - 遵守 Errata 2.3.5：上电/校准与使能严格分离
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_mc_adc.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */
Q32U_ BSP_ADC_SYSTEM_BUFFER[10];

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  ADC 公共配置（时钟源 / 模式 / DMA / 采样延迟）
 */
static void BSP_MC_ADC_CommonConfig(void)
{
    ADC_CommonInitTypeDef ADC_CommonInitStructure;

    ADC_CommonInitStructure.ADC_Mode             = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Clock            = ADC_Clock_SynClkModeDiv2;    /* 同步时钟，AHB/2 */
    ADC_CommonInitStructure.ADC_DMAAccessMode    = ADC_DMAAccessMode_1;
    ADC_CommonInitStructure.ADC_DMAMode          = ADC_DMAMode_OneShot;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = 5U;

    ADC_CommonInit(HW_MC_ADC1, &ADC_CommonInitStructure);
    ADC_CommonInit(HW_MC_ADC2, &ADC_CommonInitStructure);
    ADC_CommonInit(HW_MC_ADC3, &ADC_CommonInitStructure);
}

/**
 * @brief  ADC 上电与校准（不使能 ADC）
 * @param  ADCx  ADC 实例
 * @note   此函数只负责上电和校准，绝不在内部使能 ADC
 */
static void BSP_MC_ADC_PowerUpCalib(ADC_TypeDef* ADCx)
{
    volatile Q32U_ delay;

    /* 0. 软件复位 ADC，确保状态机绝对干净 */
    ADC_DeInit(ADCx);

    /* 1. 开启内部稳压器 */
    ADC_VoltageRegulatorCmd(ADCx, ENABLE);

    /* 2. 延时至少 10us */
    delay = 0x10000;
    while (delay--)
    {
        __NOP();
    }

    /* 3. 确保 ADC 处于禁用状态 (ADEN = 0) */
    if ((ADCx->CR & ADC_CR_ADEN) != 0U)
    {
        ADCx->CR |= ADC_CR_ADDIS;
        while ((ADCx->CR & ADC_CR_ADEN) != 0U)
        {
        }
    }

    /* 4. 启动校准（单端模式） */
    ADC_SelectCalibrationMode(ADCx, ADC_CalibrationMode_Single);
    ADC_StartCalibration(ADCx);
    while (ADC_GetCalibrationStatus(ADCx) != RESET)
    {
    }
}

/**
 * @brief  ADC 初始化（三 ADC 注入组 + ADC1 规则组）
 */
void BSP_MC_ADC_Init(void)
{
    ADC_InitTypeDef         ADC_InitStructure;
    ADC_InjectedInitTypeDef ADC_InjectedInitStructure;
    uint32_t                timeout;

    /* ============================================================
     * 第一步：公共配置 (确立 CKMODE 时钟源)
     * ============================================================ */
    BSP_MC_ADC_CommonConfig();

    /* ============================================================
     * 第二步：依次上电、校准 (此时不使能 ADC)
     * ============================================================ */
    BSP_MC_ADC_PowerUpCalib(HW_MC_ADC1);
    BSP_MC_ADC_PowerUpCalib(HW_MC_ADC2);
    BSP_MC_ADC_PowerUpCalib(HW_MC_ADC3);

    /* ============================================================
     * 第三步：配置 HW_MC_ADC1（规则组 + 注入组）
     * ============================================================ */
    ADC_InitStructure.ADC_Resolution            = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode    = ADC_ContinuousConvMode_Disable;
    ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;
    ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
    ADC_InitStructure.ADC_DataAlign             = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_OverrunMode           = ADC_OverrunMode_Disable;
    ADC_InitStructure.ADC_AutoInjMode           = ADC_AutoInjec_Disable;
    ADC_InitStructure.ADC_NbrOfRegChannel       = 0;
    ADC_Init(HW_MC_ADC1, &ADC_InitStructure);

    ADC_InjectedInitStructure.ADC_ExternalTrigInjecConvEvent = ADC_ExternalTrigInjecConvEvent_9;

    /* 如果延迟时间大于采样时间，在后半周期进行 ADC 采样，也就是 CCR4 上升沿触发 */
    if (HW_ADC_DELAY_TIME >= HW_ADC_SAMPLE_TIME)
    {
        ADC_InjectedInitStructure.ADC_ExternalTrigInjecEventEdge = ADC_ExternalTrigInjecEventEdge_RisingEdge;
    }
    else
    {
        ADC_InjectedInitStructure.ADC_ExternalTrigInjecEventEdge = ADC_ExternalTrigInjecEventEdge_FallingEdge;
    }

    ADC_InjectedInitStructure.ADC_NbrOfInjecChannel = 3;
    ADC_InjectedInitStructure.ADC_InjecSequence1    = HW_MC_ADC_U_CURRENT_Channel;
    ADC_InjectedInitStructure.ADC_InjecSequence2    = HW_MC_ADC_VBUS_Channel;
    ADC_InjectedInitStructure.ADC_InjecSequence3    = HW_MC_ADC_TEMP_Channel;
    ADC_InjectedInitStructure.ADC_InjecSequence4    = ADC_Channel_1;
    ADC_InjectedInit(HW_MC_ADC1, &ADC_InjectedInitStructure);

    ADC_InjectedChannelSampleTimeConfig(HW_MC_ADC1, HW_MC_ADC_U_CURRENT_Channel, ADC_SampleTime_19Cycles5);
    ADC_InjectedChannelSampleTimeConfig(HW_MC_ADC1, HW_MC_ADC_VBUS_Channel,      ADC_SampleTime_19Cycles5);
    ADC_InjectedChannelSampleTimeConfig(HW_MC_ADC1, HW_MC_ADC_TEMP_Channel,      ADC_SampleTime_19Cycles5);
    ADC_InjectedDiscModeCmd(HW_MC_ADC1, DISABLE);

    /* ============================================================
     * 第四步：配置 HW_MC_ADC2 和 HW_MC_ADC3（注入组）
     * ============================================================ */
    ADC_InitStructure.ADC_NbrOfRegChannel                     = 0;
    ADC_InjectedInitStructure.ADC_NbrOfInjecChannel           = 1;

    ADC_Init(HW_MC_ADC2, &ADC_InitStructure);
    ADC_InjectedInitStructure.ADC_InjecSequence1 = HW_MC_ADC_V_CURRENT_Channel;
    ADC_InjectedInit(HW_MC_ADC2, &ADC_InjectedInitStructure);
    ADC_InjectedChannelSampleTimeConfig(HW_MC_ADC2, HW_MC_ADC_V_CURRENT_Channel, ADC_SampleTime_19Cycles5);

    ADC_Init(HW_MC_ADC3, &ADC_InitStructure);
    ADC_InjectedInitStructure.ADC_InjecSequence1 = HW_MC_ADC_W_CURRENT_Channel;
    ADC_InjectedInit(HW_MC_ADC3, &ADC_InjectedInitStructure);
    ADC_InjectedChannelSampleTimeConfig(HW_MC_ADC3, HW_MC_ADC_W_CURRENT_Channel, ADC_SampleTime_19Cycles5);

    /* ============================================================
     * 第五步：最后使能 ADC (必须在这里，避开 Errata 2.3.5 的陷阱)
     * ============================================================ */
    /* --- 使能 HW_MC_ADC1 --- */
    ADC_Cmd(HW_MC_ADC1, ENABLE);
    timeout = 0xFFFFF;
    while ((HW_MC_ADC1->ISR & ADC_ISR_ADRD) == 0U)
    {
        /* 根据 Errata，ADEN 可能被内部复位，这里强制重新置位直到成功 */
        HW_MC_ADC1->CR |= ADC_CR_ADEN;
        if (--timeout == 0)
        {
            break;      /* 防止死循环 */
        }
    }

    /* --- 使能 HW_MC_ADC2 --- */
    ADC_Cmd(HW_MC_ADC2, ENABLE);
    timeout = 0xFFFFF;
    while ((HW_MC_ADC2->ISR & ADC_ISR_ADRD) == 0U)
    {
        HW_MC_ADC2->CR |= ADC_CR_ADEN;
        if (--timeout == 0)
        {
            break;
        }
    }

    /* --- 使能 HW_MC_ADC3 --- */
    ADC_Cmd(HW_MC_ADC3, ENABLE);
    timeout = 0xFFFFF;
    while ((HW_MC_ADC3->ISR & ADC_ISR_ADRD) == 0U)
    {
        HW_MC_ADC3->CR |= ADC_CR_ADEN;
        if (--timeout == 0)
        {
            break;
        }
    }

    /* ============================================================
     * 第六步：ADC 就绪后，启动注入组和规则组
     * ============================================================ */
    ADC_StartInjectedConversion(HW_MC_ADC1);
    ADC_StartInjectedConversion(HW_MC_ADC2);
    ADC_StartInjectedConversion(HW_MC_ADC3);
}
