/*
*     File Name :                        bsp_lcd_gpio
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             LCD GPIO 初始化（SPI3 引脚复用）
*/


#ifndef BSP_LCD_GPIO_H
#define BSP_LCD_GPIO_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/
void HAL_LCD_Dc_Cmd(void);
void HAL_LCD_Dc_Data(void);
void HAL_LCD_Cs_Low(void);
void HAL_LCD_Cs_High(void);
void HAL_LCD_Rst_Low(void);
void HAL_LCD_Rst_High(void);


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: BSP_LCD_GPIO_Init
Description: LCD SPI3 引脚复用 + 辅助 GPIO 初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_LCD_GPIO_Init(void);


#endif /* BSP_LCD_GPIO_H */
