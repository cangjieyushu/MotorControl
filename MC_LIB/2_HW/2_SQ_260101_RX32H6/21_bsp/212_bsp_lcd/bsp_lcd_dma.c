/*
*     File Name :                        bsp_lcd_dma
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             LCD SPI DMA 初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_lcd_dma.h"


/*-------------------------- 2. 变量定义 ---------------------------------*/
/* LCD DMA 完成标志：初始化时置 1（空闲）*/
volatile uint8_t lcd_dma_done = 1U;


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_LCD_DMA_Init
Description: LCD SPI TX DMA 通道配置
             只配置固定参数（外设地址、位宽、方向），源地址 / 长度在发送时动态重设
*/
void BSP_LCD_DMA_Init(void)
{
    
}
