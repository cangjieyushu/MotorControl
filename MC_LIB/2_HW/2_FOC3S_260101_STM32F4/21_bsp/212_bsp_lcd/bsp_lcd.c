/*
*     File Name :                        bsp_lcd
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             LCD 外设汇总初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_lcd.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_LCD_Init
Description: LCD 外设初始化汇总
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_LCD_Init(void)
{
    BSP_LCD_GPIO_Init();   /* 引脚复用 */
    BSP_LCD_SPI_Init();    /* SPI 外设配置 */
    BSP_LCD_DMA_Init();    /* SPI DMA 通道 */
}
