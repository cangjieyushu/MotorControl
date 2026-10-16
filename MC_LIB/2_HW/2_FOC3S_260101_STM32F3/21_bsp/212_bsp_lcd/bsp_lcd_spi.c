/*
*     File Name :                        bsp_lcd_spi
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             LCD SPI 外设初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_lcd_spi.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_LCD_SPI_Init
Description: LCD SPI3 外设初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_LCD_SPI_Init(void)
{
    SPI_InitTypeDef SPI_InitStructure;

    /* SPI3：全双工主机模式，8 位数据，MSB First */
    SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL              = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA              = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;   /* 18 MHz */
    SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial     = 7;

    SPI_Init(HW_LCD_SPI, &SPI_InitStructure);

    SPI_Cmd(HW_LCD_SPI, ENABLE);
}
