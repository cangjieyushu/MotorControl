/**
 * @file    hal_uart.h
 * @brief   系统串口 HAL 层头文件
 *          DMA 收发 / 环形缓冲区
 *          全部 static inline，无 .c 文件
 *
 * @warning DMA TC 判定"发送完成"只表示数据已搬到数据寄存器，
 *          最后一个字节仍在移位寄存器中。若协议层在 DMA TC 后立即调
 *          UARTH_Tx_DMA_Stop()（会切回 RS485 接收方向），最后一字节会被截断。
 *          正确流程：等 DMA TC → 等 USART TC → 调 UARTH_Tx_DMA_Stop()。
 *
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef HAL_UART_H
#define HAL_UART_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_para.h"
#include "bsp_sys.h"
#include "bsp_sys_dma.h"        /* 提供数据缓冲区 + 环形缓冲区 + 发送状态 extern */
#include <string.h>

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. UART 的 DMA 收发 ============= */

/**
 * @brief  读取 TX 传输完成标志
 * @return 非 0 = 完成
 * @warning 仅表示 DMA 已把数据搬到串口数据寄存器，不代表最后一字节已移出。
 *          若要判定 RS485 完全发完，还需结合 USART TC 标志（见文件头警告）
 */
static inline Q32U_ UARTH_Tx_Finish_Flag(void)
{
    return 1U;
}

/**
 * @brief  读取 TX DMA 传输完成标志
 * @return 非 0 = 完成
 * @warning 仅表示 DMA 已把数据搬到串口数据寄存器，不代表最后一字节已移出
 * @note   待按 RX32H6xx 库实现
 */
static inline Q32U_ UARTH_Tx_DMA_Flag(void)
{
    return 1U;
}

/**
 * @brief  启动 TX DMA（单次模式）
 * @param  txbuffer  数据指针
 * @param  len       数据长度（字节）
 * @note   内部完成：切换 RS485 发送方向 → 关通道清标志 → 重设地址长度
 *         → 使能 USART DMA 请求 → 启动 DMA 通道
 * @note   待按 RX32H6xx 库实现
 */
static inline void UARTH_Tx_DMA_Start(Q08U_* txbuffer, Q32U_ len)
{

}

/**
 * @brief  停止 TX DMA 并切回接收方向
 * @note   RS485 模式下会立刻切回接收方向，调用前必须确保数据已完全移出
 * @note   待按 RX32H6xx 库实现
 */
static inline void UARTH_Tx_DMA_Stop(void)
{

}

/**
 * @brief  读取 RX DMA 剩余计数
 * @return 剩余未接收的字节数
 * @note   已收字节数 = UART_RX_BUF_SIZE - 返回值
 * @note   待按 RX32H6xx 库实现
 */
static inline Q32U_ UARTH_Rx_DMA_RemainCount(void)
{
    return 1U;
}

/* ======================== 6. 环形缓冲区 =================== */

/**
 * @brief  初始化环形缓冲区
 */
static inline void ring_buffer_init(void)
{

}

/**
 * @brief  获取可读字节数
 * @return 缓冲区中已有字节数
 */
static inline uint16_t ring_buffer_available(void)
{
    return 1U;
}

/**
 * @brief  从缓冲区读取 1 字节
 * @return 读到的字节（0~255），-1 = 缓冲区为空
 */
static inline int ring_buffer_get(void)
{
    return 1U;
}

/**
 * @brief  向缓冲区写入 1 字节
 * @param  data  待写字节
 * @return 1 = 成功，0 = 缓冲区满
 */
static inline Q08U_ ring_buffer_put(uint8_t data)
{
    return 1U;
}

/**
 * @brief  清空环形缓冲区
 */
static inline void ring_buffer_clear(void)
{

}

#endif /* HAL_UART_H */
