/*
*     File Name :                        bsp_mc_dma
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制 DMA 初始化（ADC1 规则组搬运）
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_mc_dma.h"
#include "bsp_mc_adc.h"

/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_MC_DMA_Init
Description: ADC1 规则组 DMA 初始化（预留）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_DMA_Init(void)
{
    /* ADC_DMA_channel configuration */
    dma_parameter_struct dma_data_parameter;

    /* ADC DMA_channel configuration */
    dma_deinit(HAL_MC_ADC_DMA_CH);

    /* initialize DMA single data mode */
    dma_data_parameter.periph_addr  = (uint32_t)(&ADC_RDATA);
    dma_data_parameter.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;
    dma_data_parameter.memory_addr  = (uint32_t)(&BSP_ADC_SYSTEM_BUFFER);
    dma_data_parameter.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;
    dma_data_parameter.periph_width = DMA_PERIPHERAL_WIDTH_32BIT;
    dma_data_parameter.memory_width = DMA_MEMORY_WIDTH_32BIT;
    dma_data_parameter.direction    = DMA_PERIPHERAL_TO_MEMORY;
    dma_data_parameter.number       = 3U;
    dma_data_parameter.priority     = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(HAL_MC_ADC_DMA_CH, &dma_data_parameter);

    dma_circulation_enable(HAL_MC_ADC_DMA_CH);

    /* enable DMA channel */
    dma_channel_enable(HAL_MC_ADC_DMA_CH);
}
