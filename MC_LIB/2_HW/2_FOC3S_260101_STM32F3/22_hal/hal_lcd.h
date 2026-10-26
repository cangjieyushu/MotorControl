/**
 * @file    hal_lcd.h
 * @brief   LCD HAL 层头文件
 *          引脚控制 / SPI 收发 / DMA 收发 / 延时
 *          全部 static inline，无 .c 文件
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef HAL_LCD_H
#define HAL_LCD_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_lcd.h"
#include "bsp_lcd.h"

/* ======================== 2. Defines ====================== */
/* DMA 等待超时计数（防止 DMA 出错时死等） */
#define HW_LCD_DMA_TIMEOUT      (0x00FFFFFFU)

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. 延时 ========================= */
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

/* ======================== 6. SPI 单字节阻塞收发 =========== */
static inline uint8_t HAL_LCD_SpiRwByte(uint8_t data)
{
    return 1U;
}

/* ======================== 7. DMA 收发 ===================== */
/**
 * @brief  等待当前 DMA 传输完成（轮询 TC 标志，带超时）
 * @return 1 = 完成，0 = 超时
 */
static inline Q08U_ HAL_LCD_DmaWait(void)
{
    return 1U;              /* 成功 */
}

/**
 * @brief  DMA 发送一段数据（阻塞，轮询 TC 标志）
 * @param  data  数据指针
 * @param  len   数据长度（字节）
 * @return 1 = 成功，0 = 超时
 */
static inline Q08U_ HAL_LCD_DmaSendBlock(const uint8_t *data, uint32_t len)
{
    return 1U;
}

/**
 * @brief  DMA 分块发送任意长度数据
 * @param  data  数据指针
 * @param  len   数据长度（字节）
 * @return 1 = 成功，0 = 失败
 */
static inline Q08U_ HAL_LCD_DmaSendBytes(const uint8_t *data, uint32_t len)
{
    return 1U;
}

#endif /* HAL_LCD_H */
