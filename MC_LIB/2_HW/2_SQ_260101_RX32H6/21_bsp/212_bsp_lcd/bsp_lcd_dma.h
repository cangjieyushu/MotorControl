/**
 * @file    bsp_lcd_dma.h
 * @brief   LCD SPI DMA 初始化
 *          - DMA1_Channel2：SPI3_TX（单次，轮询 TC 标志）
 *          - DMA2_Channel1：SPI3_RX（需 SYSCFG 重映射）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef BSP_LCD_DMA_H
#define BSP_LCD_DMA_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_para.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */
void BSP_LCD_DMA_Init(void);

#endif /* BSP_LCD_DMA_H */
