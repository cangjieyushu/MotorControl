/**************************************************************************************************
*     File Name :                        hal_lcd.h
*     Library/Module Name :              hal
*     Author :                           CJYS
*     Abstract Description :             LCD HAL 层：引脚控制 / SPI 收发 / DMA 收发 / 延时
*                                        全部 static inline，无对应 .c 文件
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


/*-------------------------- 5. 延时 -----------------------------------*/
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


/*-------------------------- 6. SPI 单字节阻塞收发 ----------------------*/
static inline uint8_t HAL_LCD_SpiRwByte(uint8_t data)
{
    while (RESET == spi_i2s_flag_get(HW_LCD_SPI, SPI_FLAG_TBE))
    {
        /* 等发送缓冲区空 */
    }
    spi_i2s_data_transmit(HW_LCD_SPI, data);

    while (RESET == spi_i2s_flag_get(HW_LCD_SPI, SPI_FLAG_RBNE))
    {
        /* 等接收缓冲区非空 */
    }
    return (uint8_t)spi_i2s_data_receive(HW_LCD_SPI);
}


/*-------------------------- 7. DMA 收发 --------------------------------*/
/*
Function: HAL_LCD_DmaWait
Description: 等待 DMA 完成（带超时保护）
Return: 1 = 完成；0 = 超时
*/
static inline Q08U_ HAL_LCD_DmaWait(void)
{
    uint32_t timeout = HW_LCD_DMA_TIMEOUT;
    while ((lcd_dma_done == 0U) && (timeout > 0U))
    {
        timeout--;
    }
    return (lcd_dma_done != 0U) ? 1U : 0U;
}

/*
Function: HAL_LCD_DmaSendBlock
Description: 【阻塞式】用 DMA 发送一块数据
             函数返回时数据一定发完了
Return: 1 = 成功；0 = 超时
*/
static inline Q08U_ HAL_LCD_DmaSendBlock(const uint8_t *data, uint32_t len)
{
    if (len == 0U || data == 0)
    {
        return 1U;
    }

    lcd_dma_done = 0U;                                          /* 标记忙 */

    dma_channel_disable(HAL_LCD_SPI_TX_DMA_CH);
    dma_memory_address_config(HAL_LCD_SPI_TX_DMA_CH, (uint32_t)data);
    dma_transfer_number_config(HAL_LCD_SPI_TX_DMA_CH, len);
    dma_flag_clear(HAL_LCD_SPI_TX_DMA_CH, DMA_FLAG_FTF);
    dma_channel_enable(HAL_LCD_SPI_TX_DMA_CH);

    return HAL_LCD_DmaWait();
}

/*
Function: HAL_LCD_DmaSendBytes
Description: 自动拆块发送（当数据超过缓存大小时）
Return: 1 = 成功；0 = 超时
*/
static inline Q08U_ HAL_LCD_DmaSendBytes(const uint8_t *data, uint32_t len)
{
    while (len > 0U)
    {
        uint32_t chunk = (len > HW_LCD_CACHE_SIZE) ? HW_LCD_CACHE_SIZE : len;
        if (HAL_LCD_DmaSendBlock(data, chunk) == 0U)
        {
            return 0U;
        }
        data += chunk;
        len  -= chunk;
    }
    return 1U;
}


#endif /* HAL_LCD_H */
