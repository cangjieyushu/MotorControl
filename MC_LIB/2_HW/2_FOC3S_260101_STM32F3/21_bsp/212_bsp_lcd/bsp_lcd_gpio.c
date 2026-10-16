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
    GPIO_InitTypeDef GPIO_InitStruct;
    
    /* ---- SPI3：PA15(NSS) / PC10(SCK) / PC11(MISO) / PC12(MOSI)，AF6 ---- */
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;
    
    GPIO_InitStruct.GPIO_Pin = HW_LCD_SPI_SCK_Pin;  GPIO_Init(HW_LCD_SPI_SCK_Port,  &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_LCD_SPI_MISO_Pin; GPIO_Init(HW_LCD_SPI_MISO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_LCD_SPI_MOSI_Pin; GPIO_Init(HW_LCD_SPI_MOSI_Port, &GPIO_InitStruct);
    
    GPIO_PinAFConfig(HW_LCD_SPI_SCK_Port,  HW_LCD_SPI_SCK_Pin_Source,  GPIO_AF_6);
    GPIO_PinAFConfig(HW_LCD_SPI_MISO_Port, HW_LCD_SPI_MISO_Pin_Source, GPIO_AF_6);
    GPIO_PinAFConfig(HW_LCD_SPI_MOSI_Port, HW_LCD_SPI_MOSI_Pin_Source, GPIO_AF_6);
    
    /* NSS(PA15) 作软件片选：推挽输出，空闲高 */
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_InitStruct.GPIO_Pin   = HW_LCD_SPI_NSS_Pin;
    GPIO_Init(HW_LCD_SPI_NSS_Port, &GPIO_InitStruct);
    GPIO_SetBits(HW_LCD_SPI_NSS_Port, HW_LCD_SPI_NSS_Pin);
    
    /* ---- 辅助 GPIO：SPI_OUT（输出，可用作 LCD_DC / LCD_RST 等）---- */
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStruct.GPIO_Pin = HW_LCD_SPI_DC_Pin;
    GPIO_Init(HW_LCD_SPI_DC_Port, &GPIO_InitStruct);

    /* ---- 辅助 GPIO：SPI_IN（输入，可用作 LCD_BUSY）---- */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin  = HW_LCD_SPI_INT_Pin;
    GPIO_Init(HW_LCD_SPI_INT_Port, &GPIO_InitStruct);
    
    /* LCD 复位脚：推挽输出，空闲高 */
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStruct.GPIO_Pin   = HW_LCD_RST_Pin;
    GPIO_Init(HW_LCD_RST_PORT, &GPIO_InitStruct);
    GPIO_SetBits(HW_LCD_RST_PORT, HW_LCD_RST_Pin);
}

void HAL_LCD_Dc_Cmd(void)  { GPIO_ResetBits(HW_LCD_SPI_DC_Port, HW_LCD_SPI_DC_Pin); }
void HAL_LCD_Dc_Data(void) { GPIO_SetBits  (HW_LCD_SPI_DC_Port, HW_LCD_SPI_DC_Pin); }
void HAL_LCD_Cs_Low(void)  { GPIO_ResetBits(HW_LCD_SPI_NSS_Port, HW_LCD_SPI_NSS_Pin); }
void HAL_LCD_Cs_High(void) { GPIO_SetBits  (HW_LCD_SPI_NSS_Port, HW_LCD_SPI_NSS_Pin); }
void HAL_LCD_Rst_Low(void) { GPIO_ResetBits(HW_LCD_RST_PORT, HW_LCD_RST_Pin); }
void HAL_LCD_Rst_High(void){ GPIO_SetBits  (HW_LCD_RST_PORT, HW_LCD_RST_Pin); }
