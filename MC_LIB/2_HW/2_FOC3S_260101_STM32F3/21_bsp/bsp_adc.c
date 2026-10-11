/*
*     File Name :                        bsp_adc
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             ADC初始化
*                                        三 ADC 同步采样三相电流 + ADC1 规则组 DMA 搬运电压/温度
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_adc.h"


/*-------------------------- 2. 变量 ---------------------------------*/
/* 规则组 DMA 缓冲区：[0] = 外部温度(PC2/ADC1_IN8)   [1] = 母线电压(PC3/ADC1_IN9) */
Q32U_ BSP_ADC_SYSTEM_BUFFER[10];

/* 注入组手动读取缓冲区：[0] = U相(ADC1)   [1] = V相(ADC2)   [2] = W相(ADC3) */
Q32U_ BSP_ADC_MOTOR_BUFFER[10];


/*-------------------------- 3. 内部辅助函数 ----------------------------*/
static void BSP_ADC_CommonConfig(void)
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

static void BSP_ADC_PowerUpCalib(ADC_TypeDef* ADCx)
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
void BSP_ADC_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InjectedInitTypeDef ADC_InjectedInitStructure;   /* ★ 新增 */

    /* ---------------- 1. 三 ADC 公共配置 ---------------- */
    BSP_ADC_CommonConfig();

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
    ADC_RegularChannelConfig(ADC1, ADC_TEMP_Channel, 1, ADC_SampleTime_181Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_VBUS_Channel, 2, ADC_SampleTime_181Cycles5);

    /* ---- 注入组：U 相电流（PA2/ADC1_IN3），TIM8_TRGO 下降沿触发 ---- */
    ADC_InjectedInitStructure.ADC_ExternalTrigInjecConvEvent = ADC_ExternalTrigInjecConvEvent_7;
    ADC_InjectedInitStructure.ADC_ExternalTrigInjecEventEdge = ADC_ExternalTrigInjecEventEdge_FallingEdge;
    ADC_InjectedInitStructure.ADC_NbrOfInjecChannel          = 1;
    ADC_InjectedInitStructure.ADC_InjecSequence1             = ADC_U_CURRENT_Channel;
    ADC_InjectedInitStructure.ADC_InjecSequence2             = ADC_Channel_1;
    ADC_InjectedInitStructure.ADC_InjecSequence3             = ADC_Channel_1;
    ADC_InjectedInitStructure.ADC_InjecSequence4             = ADC_Channel_1;
    ADC_InjectedInit(ADC1, &ADC_InjectedInitStructure);

    /* 采样时间单独配置 */
    ADC_InjectedChannelSampleTimeConfig(ADC1, ADC_U_CURRENT_Channel, ADC_SampleTime_19Cycles5);
    ADC_InjectedDiscModeCmd(ADC1, DISABLE);

    /* 使能注入组转换完成中断（只在 ADC1 上响应）*/
    ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);
    ADC_ITConfig(ADC1, ADC_IT_JEOC, ENABLE);

    /* ADC1 上电 + 校准 */
    BSP_ADC_PowerUpCalib(ADC1);

    /* ============================================================
     * ADC2：从 ADC，注入组 = V 相电流（PA6/ADC2_IN3）
     * ============================================================ */
    ADC_InitStructure.ADC_ContinuousConvMode    = ADC_ContinuousConvMode_Disable;
    ADC_InitStructure.ADC_NbrOfRegChannel       = 1;
    ADC_Init(ADC2, &ADC_InitStructure);

    ADC_InjectedInitStructure.ADC_ExternalTrigInjecConvEvent = ADC_ExternalTrigInjecConvEvent_7;
    ADC_InjectedInitStructure.ADC_ExternalTrigInjecEventEdge = ADC_ExternalTrigInjecEventEdge_FallingEdge;
    ADC_InjectedInitStructure.ADC_NbrOfInjecChannel          = 1;
    ADC_InjectedInitStructure.ADC_InjecSequence1             = ADC_V_CURRENT_Channel;
    ADC_InjectedInitStructure.ADC_InjecSequence2             = ADC_Channel_1;
    ADC_InjectedInitStructure.ADC_InjecSequence3             = ADC_Channel_1;
    ADC_InjectedInitStructure.ADC_InjecSequence4             = ADC_Channel_1;
    ADC_InjectedInit(ADC2, &ADC_InjectedInitStructure);

    ADC_InjectedChannelSampleTimeConfig(ADC2, ADC_V_CURRENT_Channel, ADC_SampleTime_19Cycles5);
    ADC_InjectedDiscModeCmd(ADC2, DISABLE);

    BSP_ADC_PowerUpCalib(ADC2);

    /* ============================================================
     * ADC3：从 ADC，注入组 = W 相电流（PB13/ADC3_IN5）
     * ============================================================ */
    ADC_InitStructure.ADC_ContinuousConvMode    = ADC_ContinuousConvMode_Disable;
    ADC_InitStructure.ADC_NbrOfRegChannel       = 1;
    ADC_Init(ADC3, &ADC_InitStructure);

    ADC_InjectedInitStructure.ADC_ExternalTrigInjecConvEvent = ADC_ExternalTrigInjecConvEvent_7;
    ADC_InjectedInitStructure.ADC_ExternalTrigInjecEventEdge = ADC_ExternalTrigInjecEventEdge_FallingEdge;
    ADC_InjectedInitStructure.ADC_NbrOfInjecChannel          = 1;
    ADC_InjectedInitStructure.ADC_InjecSequence1             = ADC_W_CURRENT_Channel;
    ADC_InjectedInitStructure.ADC_InjecSequence2             = ADC_Channel_1;
    ADC_InjectedInitStructure.ADC_InjecSequence3             = ADC_Channel_1;
    ADC_InjectedInitStructure.ADC_InjecSequence4             = ADC_Channel_1;
    ADC_InjectedInit(ADC3, &ADC_InjectedInitStructure);

    ADC_InjectedChannelSampleTimeConfig(ADC3, ADC_W_CURRENT_Channel, ADC_SampleTime_19Cycles5);
    ADC_InjectedDiscModeCmd(ADC3, DISABLE);

    BSP_ADC_PowerUpCalib(ADC3);
}

void BSP_DMA_Init(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    Q32U_ timeout = 0xFFFFU;

    /* ★ F3 无 DMA_GetCmdStatus()，直接读 CCR 的 EN 位判断 DMA 是否使能 */
    while ((DMA1_Channel1->CCR & DMA_CCR_EN) && timeout--)
    {
        DMA_Cmd(DMA1_Channel1, DISABLE);   /* 尝试关闭 */
    }

    /* 复位通道 */
    DMA_DeInit(DMA1_Channel1);

    /* DMA1_Channel1 关联 ADC1 规则组 */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (Q32U_)&ADC1->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr     = (Q32U_)BSP_ADC_SYSTEM_BUFFER;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize         = 2;                                /* 温度 + 母线电压 */
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;      /* ★ 32 位 */
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Word;          /* ★ 32 位 */
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel1, ENABLE);

    /* ADC1 关联 DMA */
    ADC_DMACmd(ADC1, ENABLE);

    /* ★ DMA 就绪后，启动 ADC1 规则组首次转换 */
    ADC_StartConversion(ADC1);
}

/* ============================================================
 * JEOC 中断处理函数
 * ============================================================ */
void BSP_ADC_JEOC_Handler(void)
{
    if (ADC_GetITStatus(ADC1, ADC_IT_JEOC) != RESET)
    {
        /* 读取三个 ADC 的注入数据，隐式扩展为 32 位 */
        BSP_ADC_MOTOR_BUFFER[0] = (Q32U_)ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);  /* U 相 */
        BSP_ADC_MOTOR_BUFFER[1] = (Q32U_)ADC_GetInjectedConversionValue(ADC2, ADC_InjectedChannel_1);  /* V 相 */
        BSP_ADC_MOTOR_BUFFER[2] = (Q32U_)ADC_GetInjectedConversionValue(ADC3, ADC_InjectedChannel_1);  /* W 相 */

        ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);
    }
}


/* ============================================================
 * DAC：窗口比较器阈值输出
 * ============================================================ */
void BSP_DAC_Init(void)
{
    DAC_InitTypeDef DAC_InitStructure;

    /* DAC 挂 APB1，使能时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC1, ENABLE);

    /* ---------------- 通道 1（PA4）：窗口上限 VH ---------------- */
    DAC_InitStructure.DAC_Trigger             = DAC_Trigger_None;
    DAC_InitStructure.DAC_WaveGeneration      = DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
    DAC_InitStructure.DAC_Buffer_Switch       = DAC_BufferSwitch_Enable;
    DAC_Init(DAC1, DAC_Channel_1, &DAC_InitStructure);

    /* ---------------- 通道 2（PA5）：窗口下限 VL ---------------- */
    DAC_Init(DAC1, DAC_Channel_2, &DAC_InitStructure);

    /* 上电默认阈值 */
    DAC_SetChannel1Data(DAC1, DAC_Align_12b_R, 3000);   /* VH → DAC1_OUT1 (PA4) */
    DAC_SetChannel2Data(DAC1, DAC_Align_12b_R, 1000);   /* VL → DAC1_OUT2 (PA5) */

    DAC_Cmd(DAC1, DAC_Channel_1, ENABLE);
    DAC_Cmd(DAC1, DAC_Channel_2, ENABLE);
}


/* ============================================================
 * OPAMP：电流采样信号跟随器
 * ============================================================ */
void BSP_OPAMP_Init(void)
{
    OPAMP_InitTypeDef OPAMP_InitStructure;

    /* ---- OPA1：跟随器模式，输出到 PA2 ---- */
    OPAMP_InitStructure.OPAMP_NonInvertingInput = OPAMP_NonInvertingInput_IO1;  /* PA7 */
    OPAMP_InitStructure.OPAMP_InvertingInput    = OPAMP_InvertingInput_Vout;    /* 跟随器 */
    OPAMP_Init(OPAMP_Selection_OPAMP1, &OPAMP_InitStructure);
    OPAMP_Cmd(OPAMP_Selection_OPAMP1, ENABLE);

    /* ---- OPA2：输出到 PC5 ---- */
    OPAMP_Init(OPAMP_Selection_OPAMP2, &OPAMP_InitStructure);
    OPAMP_Cmd(OPAMP_Selection_OPAMP2, ENABLE);

    /* ---- OPA3：输出到 PB1 ---- */
    OPAMP_Init(OPAMP_Selection_OPAMP3, &OPAMP_InitStructure);
    OPAMP_Cmd(OPAMP_Selection_OPAMP3, ENABLE);
}


/* ============================================================
 * CMP：三组窗口比较器过流保护
 * ============================================================ */
static void BSP_CMP_ConfigMaster(uint32_t compSel,
                                 uint32_t invert,
                                 uint32_t nonInvert,
                                 uint32_t output,
                                 uint32_t outputPol)
{
    COMP_InitTypeDef COMP_InitStructure;

    COMP_InitStructure.COMP_InvertingInput    = invert;
    COMP_InitStructure.COMP_NonInvertingInput = nonInvert;
    COMP_InitStructure.COMP_Output            = output;
    COMP_InitStructure.COMP_BlankingSrce      = COMP_BlankingSrce_None;
    COMP_InitStructure.COMP_OutputPol         = outputPol;
    COMP_InitStructure.COMP_Hysteresis        = COMP_Hysteresis_Low;
    COMP_InitStructure.COMP_Mode              = COMP_Mode_HighSpeed;

    COMP_Init(compSel, &COMP_InitStructure);
    COMP_Cmd(compSel, ENABLE);
}

static void BSP_CMP_ConfigSlave(uint32_t compSel,
                                uint32_t invert,
                                uint32_t output,
                                uint32_t outputPol)
{
    COMP_InitTypeDef COMP_InitStructure;

    COMP_InitStructure.COMP_InvertingInput    = invert;
    COMP_InitStructure.COMP_NonInvertingInput = COMP_NonInvertingInput_IO1;   /* 窗口模式下此字段被忽略 */
    COMP_InitStructure.COMP_Output            = output;
    COMP_InitStructure.COMP_BlankingSrce      = COMP_BlankingSrce_None;
    COMP_InitStructure.COMP_OutputPol         = outputPol;
    COMP_InitStructure.COMP_Hysteresis        = COMP_Hysteresis_Low;
    COMP_InitStructure.COMP_Mode              = COMP_Mode_HighSpeed;

    COMP_Init(compSel, &COMP_InitStructure);

    /* ★ 使能窗口模式 */
    COMP_WindowCmd(compSel, ENABLE);

    COMP_Cmd(compSel, ENABLE);
}

void BSP_CMP_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* 组 1：COMP1(主) + COMP2(从) */
    BSP_CMP_ConfigMaster(HAL_OCP_COMP1, HAL_OCP_COMP1_INVERT,
                         HAL_OCP_COMP1_NONINVERT, HAL_OCP_COMP1_OUTPUT,
                         HAL_OCP_COMP1_OUTPUTPOL);
    BSP_CMP_ConfigSlave(HAL_OCP_COMP2, HAL_OCP_COMP2_INVERT,
                        HAL_OCP_COMP2_OUTPUT, HAL_OCP_COMP2_OUTPUTPOL);

    /* 组 2：COMP3(主) + COMP4(从) */
    BSP_CMP_ConfigMaster(HAL_OCP_COMP3, HAL_OCP_COMP3_INVERT,
                         HAL_OCP_COMP3_NONINVERT, HAL_OCP_COMP3_OUTPUT,
                         HAL_OCP_COMP3_OUTPUTPOL);
    BSP_CMP_ConfigSlave(HAL_OCP_COMP4, HAL_OCP_COMP4_INVERT,
                        HAL_OCP_COMP4_OUTPUT, HAL_OCP_COMP4_OUTPUTPOL);

    /* 组 3：COMP5(主) + COMP6(从) */
    BSP_CMP_ConfigMaster(HAL_OCP_COMP5, HAL_OCP_COMP5_INVERT,
                         HAL_OCP_COMP5_NONINVERT, HAL_OCP_COMP5_OUTPUT,
                         HAL_OCP_COMP5_OUTPUTPOL);
    BSP_CMP_ConfigSlave(HAL_OCP_COMP6, HAL_OCP_COMP6_INVERT,
                        HAL_OCP_COMP6_OUTPUT, HAL_OCP_COMP6_OUTPUTPOL);
}
