/*
*     File Name :                        bsp_lcd_dma
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             LCD SPI DMA 初始化
*/


#ifndef BSP_LCD_DMA_H
#define BSP_LCD_DMA_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/
/* LCD DMA 完成标志：0 = 忙，1 = 空闲（由 DMA_Channel1_2_IRQHandler 置 1）*/
extern volatile uint8_t lcd_dma_done;


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: BSP_LCD_DMA_Init
Description: LCD SPI3 的 DMA 收发通道配置
             - DMA1_Channel2：SPI3_TX（单次模式，无冲突）
             - DMA2_Channel1：SPI3_RX（需 SYSCFG 重映射）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_LCD_DMA_Init(void);


#endif /* BSP_LCD_DMA_H */
