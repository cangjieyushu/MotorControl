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
    spi_parameter_struct spi_init_struct;

    spi_i2s_deinit(HW_LCD_SPI);

    spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode          = SPI_MASTER;
    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE; /* Mode 3 */
    spi_init_struct.nss                  = SPI_NSS_SOFT;
    spi_init_struct.prescale             = SPI_PSC_2;
    spi_init_struct.endian               = SPI_ENDIAN_MSB;

    spi_init(HW_LCD_SPI, &spi_init_struct);

    /* 使能 SPI 的 DMA 发送请求 */
    spi_dma_enable(HW_LCD_SPI, SPI_DMA_TRANSMIT);

    spi_enable(HW_LCD_SPI);
}
