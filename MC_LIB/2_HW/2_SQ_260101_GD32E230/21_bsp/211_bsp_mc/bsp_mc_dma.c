/**
 * @file    bsp_mc_dma.c
 * @brief   电机控制 DMA 初始化（ADC 规则组搬运）
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_mc_dma.h"
#include "bsp_mc_adc.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  ADC 规则组 DMA 初始化（循环模式）
 */
void BSP_MC_DMA_Init(void)
{
    dma_parameter_struct dma_data_parameter;

    /* ---- 1. 复位 ADC 对应的 DMA 通道 ---- */
    dma_deinit(HAL_MC_ADC_DMA_CH);

    /* ---- 2. 单次数据模式配置 ---- */
    dma_data_parameter.periph_addr  = (uint32_t)(&ADC_RDATA);                /* 外设地址：ADC 数据寄存器 */
    dma_data_parameter.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;            /* 外设地址不增 */
    dma_data_parameter.memory_addr  = (uint32_t)(&BSP_ADC_SYSTEM_BUFFER);     /* 内存地址：系统缓冲区 */
    dma_data_parameter.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;             /* 内存地址递增 */
    dma_data_parameter.periph_width = DMA_PERIPHERAL_WIDTH_32BIT;
    dma_data_parameter.memory_width = DMA_MEMORY_WIDTH_32BIT;
    dma_data_parameter.direction    = DMA_PERIPHERAL_TO_MEMORY;
    dma_data_parameter.number       = 2U;                                     /* VBUS + TEMP 共 2 个数据 */
    dma_data_parameter.priority     = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(HAL_MC_ADC_DMA_CH, &dma_data_parameter);

    /* ---- 3. 循环模式（连续转换持续搬运） ---- */
    dma_circulation_enable(HAL_MC_ADC_DMA_CH);

    /* ---- 4. 使能通道 ---- */
    dma_channel_enable(HAL_MC_ADC_DMA_CH);
}
