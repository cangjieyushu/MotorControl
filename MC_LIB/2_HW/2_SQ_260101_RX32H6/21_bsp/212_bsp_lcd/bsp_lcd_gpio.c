/**
 * @file    bsp_lcd_gpio.c
 * @brief   LCD GPIO 初始化
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_lcd_gpio.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  LCD GPIO 初始化（SPI3 引脚复用 + 辅助 GPIO）
 */
void BSP_LCD_GPIO_Init(void)
{

}

/**
 * @brief  DC 引脚拉低（命令模式）
 */
void HAL_LCD_Dc_Cmd(void)
{

}

/**
 * @brief  DC 引脚拉高（数据模式）
 */
void HAL_LCD_Dc_Data(void)
{

}

/**
 * @brief  片选拉低（选中 LCD）
 */
void HAL_LCD_Cs_Low(void)
{

}

/**
 * @brief  片选拉高（释放 LCD）
 */
void HAL_LCD_Cs_High(void)
{

}

/**
 * @brief  复位脚拉低（LCD 复位）
 */
void HAL_LCD_Rst_Low(void)
{

}

/**
 * @brief  复位脚拉高（LCD 正常工作）
 */
void HAL_LCD_Rst_High(void)
{

}
