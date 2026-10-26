/**
 * @file    bsp_mc_dma.c
 * @brief   电机控制 DMA 初始化（ADC1 规则组搬运）
 *          - 当前整体注释，规则组 DMA 暂不启用
 *          - 原设计：DMA1_Channel1，ADC1_DR → BSP_ADC_SYSTEM_BUFFER[0..1]
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
 * @brief  电机控制 DMA 初始化（ADC1 规则组搬运）
 * @note   当前为空实现，规则组 DMA 暂不启用
 */
void BSP_MC_DMA_Init(void)
{
    
}
