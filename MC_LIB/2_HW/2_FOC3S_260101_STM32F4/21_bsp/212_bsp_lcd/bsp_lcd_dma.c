/*
*     File Name :                        bsp_lcd_dma
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             LCD SPI DMA 初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_lcd_dma.h"


/*-------------------------- 2. 变量 ---------------------------------*/
/* LCD DMA 完成标志：初始化时置 1（空闲）*/
volatile uint8_t lcd_dma_done = 1U;


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_LCD_DMA_Init
Description: LCD SPI3 的 DMA 收发通道配置
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_LCD_DMA_Init(void)
{
    
}
