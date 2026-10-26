/**
 * @file    bsp_lcd.h
 * @brief   LCD 外设汇总初始化
 *          - 调用顺序：GPIO → DMA → SPI
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef BSP_LCD_H
#define BSP_LCD_H

/* ======================== 1. Header ======================= */
#include "bsp_lcd_dma.h"
#include "bsp_lcd_gpio.h"
#include "bsp_lcd_spi.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

void BSP_LCD_Init(void);

#endif /* BSP_LCD_H */
