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
    /* ---- SPI 复用引脚：SCK = PB3, MOSI = PB5, AF0 ---- */
    gpio_af_set(HW_LCD_SPI_SCK_GPIO_Port, GPIO_AF_0, HW_LCD_SPI_SCK_PIN | HW_LCD_SPI_MOSI_PIN);
    gpio_mode_set(HW_LCD_SPI_SCK_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, HW_LCD_SPI_SCK_PIN | HW_LCD_SPI_MOSI_PIN);
    gpio_output_options_set(HW_LCD_SPI_SCK_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HW_LCD_SPI_SCK_PIN | HW_LCD_SPI_MOSI_PIN);

    /* ---- 控制引脚：RST = PA0, DC = PA3, CS = PA4 ---- */
    gpio_mode_set(HW_LCD_SPI_RST_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, HW_LCD_SPI_RST_PIN);
    gpio_output_options_set(HW_LCD_SPI_RST_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HW_LCD_SPI_RST_PIN);

    gpio_mode_set(HW_LCD_SPI_DC_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, HW_LCD_SPI_DC_PIN);
    gpio_output_options_set(HW_LCD_SPI_DC_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HW_LCD_SPI_DC_PIN);

    gpio_mode_set(HW_LCD_SPI_CS_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, HW_LCD_SPI_CS_PIN);
    gpio_output_options_set(HW_LCD_SPI_CS_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HW_LCD_SPI_CS_PIN);

    /* ---- 初始电平 ---- */
    HAL_LCD_Cs_High();
    HAL_LCD_Rst_High();
    HAL_LCD_Dc_Data();
}

void HAL_LCD_Dc_Cmd(void)
{
    gpio_bit_reset(HW_LCD_SPI_DC_GPIO_Port, HW_LCD_SPI_DC_PIN);
}
void HAL_LCD_Dc_Data(void)
{
    gpio_bit_set(HW_LCD_SPI_DC_GPIO_Port, HW_LCD_SPI_DC_PIN);
}
void HAL_LCD_Cs_Low(void)
{
    gpio_bit_reset(HW_LCD_SPI_CS_GPIO_Port, HW_LCD_SPI_CS_PIN);
}
void HAL_LCD_Cs_High(void)
{
    gpio_bit_set(HW_LCD_SPI_CS_GPIO_Port, HW_LCD_SPI_CS_PIN);
}
void HAL_LCD_Rst_Low(void)
{
    gpio_bit_reset(HW_LCD_SPI_RST_GPIO_Port, HW_LCD_SPI_RST_PIN);
}
void HAL_LCD_Rst_High(void)
{
    gpio_bit_set(HW_LCD_SPI_RST_GPIO_Port, HW_LCD_SPI_RST_PIN);
}
