/**
 * @file    hal_lcd.h
 * @brief   LCD HAL 层头文件
 *          引脚控制 / SPI 收发 / DMA 收发 / 延时
 *          全部 static inline，无 .c 文件
 *          基于 GD32E23x 标准外设库 (gd32e23x_spi.c / gd32e23x_dma.c)
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef HAL_LCD_H
#define HAL_LCD_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_lcd.h"
#include "bsp_lcd.h"

#include "gd32e23x_spi.h"
#include "gd32e23x_dma.h"

/* ======================== 2. Defines ====================== */
/* DMA 等待超时计数（防止 DMA 出错时死等） */
#define HW_LCD_DMA_TIMEOUT      (0x00FFFFFFU)

/* DMA 传输完成标志（GD32 中对应 full transfer finish） */
#define HW_LCD_DMA_TC_FLAG      DMA_FLAG_FTF

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
 * @brief  SPI 单字节阻塞收发
 * @param  data  待发送字节
 * @return 收到的字节
 * @note   使用 GD32 标准库 spi_i2s_flag_get / spi_i2s_data_transmit / spi_i2s_data_receive
 *         SPI0 / SPI1 均可用（SPI1 的 FIFO 模式同样由 TBE/RBNE 标志工作）
 */
static inline uint8_t HAL_LCD_SpiRwByte(uint8_t data)
{
    /* 等发送缓冲区空（TBE = Transmit Buffer Empty） */
    while (spi_i2s_flag_get(HW_LCD_SPI, SPI_FLAG_TBE) == RESET)
    {
    }

    /* 发送一个字节（8 位帧，高位补 0 即可） */
    spi_i2s_data_transmit(HW_LCD_SPI, (uint16_t)data);

    /* 等接收缓冲区非空（RBNE = Receive Buffer Not Empty） */
    while (spi_i2s_flag_get(HW_LCD_SPI, SPI_FLAG_RBNE) == RESET)
    {
    }

    /* 读数据（同时清 RBNE） */
    return (uint8_t)spi_i2s_data_receive(HW_LCD_SPI);
}

/* ======================== 7. DMA 收发 ===================== */

/**
 * @brief  等待 DMA 完成（带超时保护）
 * @return 1 = 完成；0 = 超时
 */
static inline Q08U_ HAL_LCD_DmaWait(void)
{
    Q32U_ timeout = HW_LCD_DMA_TIMEOUT;

    while (dma_flag_get(HW_LCD_SPI_TX_DMA_CH, HW_LCD_DMA_TC_FLAG) == RESET)
    {
        if (--timeout == 0U)
        {
            return 0U;      /* 超时 */
        }
    }
    return 1U;              /* 成功 */
}

/**
 * @brief  【阻塞式】用 DMA 发送一块数据
 * @param  data  数据指针
 * @param  len   数据长度（字节）
 * @return 1 = 成功；0 = 超时
 * @note   函数返回时数据一定发完了
 *         DMA 通道的外设地址、位宽、方向等参数需在 hw_lcd.c 初始化阶段用
 *         dma_init()/dma_periph_address_config() 配好，本函数只更新内存地址和长度
 */
static inline Q08U_ HAL_LCD_DmaSendBlock(const uint8_t *data, uint32_t len)
{
    Q32U_ timeout;

    if (len == 0U)
    {
        return 1U;          /* 空数据视为成功 */
    }

    /* 关闭通道，准备配置 */
    dma_channel_disable(HW_LCD_SPI_TX_DMA_CH);

    /* 配置内存地址与传输长度 */
    dma_memory_address_config(HW_LCD_SPI_TX_DMA_CH, (uint32_t)(uintptr_t)data);
    dma_transfer_number_config(HW_LCD_SPI_TX_DMA_CH, len);

    /* 清 FTF 标志（必须在 Enable 之前，否则会误判为已完成） */
    dma_flag_clear(HW_LCD_SPI_TX_DMA_CH, HW_LCD_DMA_TC_FLAG);

    /* 开通道，开始传输 */
    dma_channel_enable(HW_LCD_SPI_TX_DMA_CH);

    /* 轮询 FTF 标志（带超时） */
    timeout = HW_LCD_DMA_TIMEOUT;
    while (dma_flag_get(HW_LCD_SPI_TX_DMA_CH, HW_LCD_DMA_TC_FLAG) == RESET)
    {
        if (--timeout == 0U)
        {
            /* 超时：关通道，返回失败 */
            dma_channel_disable(HW_LCD_SPI_TX_DMA_CH);
            return 0U;
        }
    }
    return 1U;
}

/**
 * @brief  自动拆块发送（当数据超过缓存大小时）
 * @param  data  数据指针
 * @param  len   数据长度（字节）
 * @return 1 = 成功；0 = 超时
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
