/**************************************************************************************************
*     File Name :                        BSP_USART.h
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             USART初始化及应用层接口头文件
**************************************************************************************************/
#ifndef BSP_USART_H
#define BSP_USART_H

#include "hw_clk.h"
#include "hw_map.h"
#include "hw_para.h"


/* 控制宏 */
#define LCD_CS_LOW()    gpio_bit_reset(SPI_CS_GPIO_PORT, SPI_CS_PIN)
#define LCD_CS_HIGH()   gpio_bit_set(SPI_CS_GPIO_PORT, SPI_CS_PIN)
#define LCD_DC_CMD()    gpio_bit_reset(SPI_DC_GPIO_PORT, SPI_DC_PIN)
#define LCD_DC_DATA()   gpio_bit_set(SPI_DC_GPIO_PORT, SPI_DC_PIN)
#define LCD_RST_LOW()   gpio_bit_reset(SPI_RST_GPIO_PORT, SPI_RST_PIN)
#define LCD_RST_HIGH()  gpio_bit_set(SPI_RST_GPIO_PORT, SPI_RST_PIN)


/**********************************************************************************************
Function: BSP_USART_Init
Description: USART初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_USART_Init(void);

/**********************************************************************************************
Function: BSP_SPI_Init
Description: SPI初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_SPI_Init(void);


#endif /* BSP_USART_H */
