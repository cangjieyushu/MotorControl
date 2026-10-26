/**
 * @file    bsp_mc_adc.c
 * @brief   ADC 初始化
 *          - 注入组：U/V/W 相 BEMF + 相电流
 *          - 规则组：母线电压 + 外部温度（DMA 搬运）
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_mc_adc.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */
Q32U_ BSP_ADC_SYSTEM_BUFFER[10];   /* 规则组 DMA 数据缓冲区 */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  电机控制用 ADC 初始化
 */
void BSP_MC_ADC_Init(void)
{
    /* ---- 1. 规则组公共配置 ---- */
    adc_special_function_config(ADC_SCAN_MODE,       ENABLE);        /* 扫描模式 */
    adc_data_alignment_config(ADC_DATAALIGN_RIGHT);                  /* 数据右对齐 */
    adc_special_function_config(ADC_CONTINUOUS_MODE, ENABLE);        /* 连续转换 CTN=1 */

    /* ---- 2. 规则组：VBUS + TEMP ---- */
    adc_channel_length_config(ADC_REGULAR_CHANNEL, 2U);
    adc_regular_channel_config(0U, HW_MC_ADC_VBUS_Channel, ADC_SAMPLETIME_28POINT5);
    adc_regular_channel_config(1U, HW_MC_ADC_TEMP_Channel, ADC_SAMPLETIME_28POINT5);

    /* ---- 3. 规则组触发：软件触发 ---- */
    adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);
    adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_NONE);

    /* ---- 4. DMA 请求使能（规则组数据搬入 BSP_ADC_SYSTEM_BUFFER） ---- */
    adc_dma_mode_enable();

    /* ---- 5. 注入组：U/V/W 相 BEMF + 相电流 ---- */
    adc_channel_length_config(ADC_INSERTED_CHANNEL, 4U);
    adc_inserted_channel_config(0U, HW_MC_ADC_U_BEMF_Channel,  ADC_SAMPLETIME_7POINT5);
    adc_inserted_channel_config(1U, HW_MC_ADC_V_BEMF_Channel,  ADC_SAMPLETIME_7POINT5);
    adc_inserted_channel_config(2U, HW_MC_ADC_W_BEMF_Channel,  ADC_SAMPLETIME_7POINT5);
    adc_inserted_channel_config(3U, HW_MC_ADC_CURRENT_Channel, ADC_SAMPLETIME_7POINT5);

    /* ---- 6. 注入组触发：软件触发（外部触发由后续使能） ---- */
    adc_external_trigger_config(ADC_INSERTED_CHANNEL, ENABLE);
    adc_external_trigger_source_config(ADC_INSERTED_CHANNEL, ADC_EXTTRIG_INSERTED_NONE);

    /* ---- 7. 注入组转换完成中断 ---- */
    adc_interrupt_enable(ADC_INT_EOIC);

    /* ---- 8. 使能 ADC + 校准 + 启动首次规则组转换 ---- */
    adc_enable();
    Math_Delay_us(1000U);       /* 使能后需等待 ≥ 1ms 才能校准 */
    adc_calibration_enable();

    adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
}