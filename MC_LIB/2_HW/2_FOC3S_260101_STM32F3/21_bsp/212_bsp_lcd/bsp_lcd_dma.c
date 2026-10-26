/**
 * @file    bsp_lcd_dma.c
 * @brief   LCD SPI DMA 初始化
 *          - DMA1_Channel2：SPI3_TX（Normal，轮询 TC 标志判定完成）
 *          - DMA2_Channel1：SPI3_RX（需 SYSCFG 重映射）
 *          - 避免与 ADC1 的 DMA1_Ch1 冲突
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_lcd_dma.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  LCD SPI DMA 初始化（TX 单次 + RX 单次）
 */
void BSP_LCD_DMA_Init(void)
{
    
}
