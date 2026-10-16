/*
*     File Name :                        bsp_lcd_dma
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             LCD SPI DMA 初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_lcd_dma.h"


/*-------------------------- 2. 变量定义 ---------------------------------*/
/* LCD DMA 完成标志：初始化时置 1（空闲）*/
volatile uint8_t lcd_dma_done = 1U;


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_LCD_DMA_Init
Description: LCD SPI TX DMA 通道配置
             只配置固定参数（外设地址、位宽、方向），源地址 / 长度在发送时动态重设
*/
void BSP_LCD_DMA_Init(void)
{
    dma_parameter_struct dma_init_struct;
    
    dma_deinit(HAL_LCD_SPI_TX_DMA_CH);
    
    dma_init_struct.periph_addr  = (uint32_t)(&SPI_DATA(HW_LCD_SPI));
    dma_init_struct.memory_addr  = (uint32_t)0U;            /* 发送时动态指定 */
    dma_init_struct.direction    = DMA_MEMORY_TO_PERIPHERAL;
    dma_init_struct.number       = 1U;                      /* 发送时动态指定 */
    dma_init_struct.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dma_init_struct.priority     = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(HAL_LCD_SPI_TX_DMA_CH, &dma_init_struct);

    dma_circulation_disable(HAL_LCD_SPI_TX_DMA_CH);
    dma_memory_to_memory_disable(HAL_LCD_SPI_TX_DMA_CH);

    /* 开启 DMA 传输完成中断 */
    dma_interrupt_enable(HAL_LCD_SPI_TX_DMA_CH, DMA_INT_FTF);

    /* 初始状态标记为空闲 */
    lcd_dma_done = 1U;
}
