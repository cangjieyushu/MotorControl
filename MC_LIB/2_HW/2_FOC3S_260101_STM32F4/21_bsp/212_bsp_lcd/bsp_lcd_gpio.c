/*
*     File Name :                        bsp_lcd_gpio
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             LCD GPIO 初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_lcd_gpio.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_LCD_GPIO_Init
Description: LCD SPI3 引脚复用 + 辅助 GPIO 初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_LCD_GPIO_Init(void)
{
    
}

void HAL_LCD_Dc_Cmd(void){}
void HAL_LCD_Dc_Data(void){}
void HAL_LCD_Cs_Low(void){}
void HAL_LCD_Cs_High(void){}
void HAL_LCD_Rst_Low(void){}
void HAL_LCD_Rst_High(void){}
