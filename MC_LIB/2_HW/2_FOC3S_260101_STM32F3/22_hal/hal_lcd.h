/**************************************************************************************************
*     File Name :                        hal_lcd
*     Library/Module Name :              hal_lcd
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             LCD HAL 层头文件
*                                        引脚控制 / SPI 收发 / DMA 收发 / 延时
*                                        全部 static inline，无 .c 文件
**************************************************************************************************/
#ifndef HAL_LCD_H
#define HAL_LCD_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_lcd.h"
#include "bsp_lcd.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
/* DMA 等待超时计数（防止 DMA 出错时死等）*/
#define HW_LCD_DMA_TIMEOUT      (0x00FFFFFFU)


/*-------------------------- 3. 外部变量 ---------------------------------*/
/* DMA 完成标志：定义在 bsp_lcd_dma.c，由 DMA_Channel1_2_IRQHandler 置 1 */
extern volatile uint8_t lcd_dma_done;


/*-------------------------- 4. 引脚控制（inline）------------------------*/


/*-------------------------- 6. 延时 -----------------------------------*/
/*
Function: HAL_LCD_DelayMs
Description: 毫秒级粗略延时（基于空循环，主频 72MHz 时约 1ms 循环 8000 次）
Input: ms - 毫秒数
Output: 无
Return: 无
Author: CJYS
*/
static inline void HAL_LCD_DelayMs(uint32_t ms)
{
    for (uint32_t i = 0U; i < ms; i++)
    {
        for (volatile uint32_t j = 0U; j < 8000U; j++)
        {
            /* 空循环 */
        }
    }
}


/*-------------------------- 7. SPI 单字节阻塞收发 ----------------------*/
/*
Function: HAL_LCD_SpiRwByte
Description: SPI 阻塞方式收发一个字节
Input: data - 待发送字节
Output: 无
Return: 接收到的字节
Author: CJYS
*/
static inline uint8_t HAL_LCD_SpiRwByte(uint8_t data)
{
    /* 等发送缓冲区空 */
    while (SPI_I2S_GetFlagStatus(HW_LCD_SPI, SPI_I2S_FLAG_TXE) == RESET) { }

    /* 发送 */
    SPI_SendData8(HW_LCD_SPI, data);

    /* 等接收缓冲区非空 */
    while (SPI_I2S_GetFlagStatus(HW_LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET) { }

    /* 读数据（同时清 RXNE）*/
    return (uint8_t)SPI_I2S_ReceiveData16(HW_LCD_SPI);
}


/*-------------------------- 8. DMA 收发 --------------------------------*/
/*
Function: HAL_LCD_DmaWait
Description: 等待 DMA 空闲（带超时保护）
Input: 无
Output: 无
Return: 0 - 超时；1 - 成功
Author: CJYS
*/
static inline Q08U_ HAL_LCD_DmaWait(void)
{
    Q32U_ timeout = HW_LCD_DMA_TIMEOUT;

    while (lcd_dma_done == 0U)
    {
        if (--timeout == 0U)
        {
            return 0U;      /* 超时 */
        }
    }
    return 1U;              /* 成功 */
}

/*
Function: HAL_LCD_DmaSendBlock
Description: DMA 发送一块数据（阻塞版，带超时保护）
Input: data - 数据首地址；len - 字节数
Output: 无
Return: 0 - 超时；1 - 成功
Author: CJYS
*/
static inline Q08U_ HAL_LCD_DmaSendBlock(const uint8_t *data, uint32_t len)
{
    Q32U_ timeout;

    if (len == 0U)
    {
        return 1U;          /* 空数据视为成功 */
    }

    lcd_dma_done = 0U;                              /* 标记 DMA 忙 */

    /* 关闭通道，准备配置 */
    DMA_Cmd(HW_LCD_SPI_TX_DMA_CH, DISABLE);

    /* 配置源地址与长度 */
    HW_LCD_SPI_TX_DMA_CH->CMAR  = (Q32U_)data;
    HW_LCD_SPI_TX_DMA_CH->CNDTR = (Q16U_)len;

    /* 清标志 */
    DMA_ClearFlag(HW_LCD_SPI_TX_DMA_GL_FLAG);

    /* 开通道，开始传输 */
    DMA_Cmd(HW_LCD_SPI_TX_DMA_CH, ENABLE);

    /* 等中断把 lcd_dma_done 置 1（带超时）*/
    timeout = HW_LCD_DMA_TIMEOUT;
    while (lcd_dma_done == 0U)
    {
        if (--timeout == 0U)
        {
            /* 超时：关通道，返回失败 */
            DMA_Cmd(HW_LCD_SPI_TX_DMA_CH, DISABLE);
            return 0U;
        }
    }
    return 1U;
}

/*
Function: HAL_LCD_DmaSendBytes
Description: DMA 发送任意长度数据（自动按缓存大小分块）
Input: data - 数据首地址；len - 字节数
Output: 无
Return: 0 - 超时；1 - 成功
Author: CJYS
*/
static inline Q08U_ HAL_LCD_DmaSendBytes(const uint8_t *data, uint32_t len)
{
    while (len > 0U)
    {
        uint32_t chunk = (len > HW_LCD_CACHE_SIZE) ? HW_LCD_CACHE_SIZE : len;

        if (HAL_LCD_DmaSendBlock(data, chunk) == 0U)
        {
            return 0U;      /* 分块失败，直接返回 */
        }
        data += chunk;
        len  -= chunk;
    }
    return 1U;
}


#endif /* HAL_LCD_H */
