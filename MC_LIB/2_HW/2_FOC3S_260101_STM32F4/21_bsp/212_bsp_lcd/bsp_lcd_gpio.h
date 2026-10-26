/**
 * @file    bsp_lcd_gpio.h
 * @brief   LCD GPIO 初始化（SPI3 引脚复用）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef BSP_LCD_GPIO_H
#define BSP_LCD_GPIO_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_para.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */
void BSP_LCD_GPIO_Init(void);

void HAL_LCD_Dc_Cmd(void);
void HAL_LCD_Dc_Data(void);
void HAL_LCD_Cs_Low(void);
void HAL_LCD_Cs_High(void);
void HAL_LCD_Rst_Low(void);
void HAL_LCD_Rst_High(void);

#endif /* BSP_LCD_GPIO_H */
