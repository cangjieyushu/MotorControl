/**
 * @file    hal_lcd.h
 * @brief   LCD HAL 层：引脚控制 / SPI 收发 / DMA 收发 / 延时
 *          全部 static inline，无对应 .c 文件
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

/**
 * @brief  粗略毫秒级延时
 * @param  ms  延时时长，单位：ms
 * @note   精度依赖主频与编译器优化，实现时按主频校准内层循环次数
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

/* ======================== 6. SPI 单字节阻塞收发 =========== */

/**
 * @brief  SPI 单字节阻塞收发（预留，待实现）
 * @param  data  待发送字节
 * @return 收到的字节
 */
static inline uint8_t HAL_LCD_SpiRwByte(uint8_t data)
{
    return 1U;
}

/* ======================== 7. DMA 收发 ===================== */

/**
 * @brief  等待 DMA 完成（带超时保护）
 * @return 1 = 完成；0 = 超时
 * @note   预留，待实现（实现时使用 HW_LCD_DMA_TIMEOUT 计数）
 */
static inline Q08U_ HAL_LCD_DmaWait(void)
{
    return 1U;
}

/**
 * @brief  【阻塞式】用 DMA 发送一块数据
 * @param  data  数据指针
 * @param  len   数据长度（字节）
 * @return 1 = 成功；0 = 超时
 * @note   函数返回时数据一定发完了
 */
static inline Q08U_ HAL_LCD_DmaSendBlock(const uint8_t *data, uint32_t len)
{
    return 1U;
}

/**
 * @brief  自动拆块发送（当数据超过缓存大小时）
 * @param  data  数据指针
 * @param  len   数据长度（字节）
 * @return 1 = 成功；0 = 超时
 * @note   预留，待实现
 */
static inline Q08U_ HAL_LCD_DmaSendBytes(const uint8_t *data, uint32_t len)
{
    return 1U;
}

#endif /* HAL_LCD_H */