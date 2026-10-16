/*
*     File Name :                        bsp_lcd
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             LCD 外设汇总头文件
*/


#ifndef BSP_LCD_H
#define BSP_LCD_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "bsp_lcd_gpio.h"
#include "bsp_lcd_spi.h"
#include "bsp_lcd_dma.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: BSP_LCD_Init
Description: LCD 外设初始化汇总
             包含：GPIO 引脚复用 + SPI 外设配置 + SPI DMA 配置
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
void BSP_LCD_Init(void);


#endif /* BSP_LCD_H */
