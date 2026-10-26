/**
 * @file    bsp_sys_dma.h
 * @brief   系统级 DMA 初始化（串口循环接收 + 单次发送）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef BSP_SYS_DMA_H
#define BSP_SYS_DMA_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_para.h"

/* ======================== 2. Defines ====================== */

/* 数据寄存器访问 */
#define UART_TRANSMISSION_DATA     (HW_SYS_UART->TDR)
#define UART_RECEIVE_DATA          (HW_SYS_UART->RDR)

/* 缓冲区大小 */
#define UART_TX_BUF_SIZE           (256U)                /* 发送缓冲区大小 */
#define UART_RX_BUF_SIZE           (256U)                /* DMA 循环接收线性缓冲区大小 */
#define UART_RX_RING_SIZE          (UART_RX_BUF_SIZE)    /* 软件环形缓冲区大小 */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ---- DMA 线性缓冲区 ---- */
extern uint8_t           g_uart_tx_buf[UART_TX_BUF_SIZE];
extern uint8_t           g_uart_rx_buf[UART_RX_BUF_SIZE];
extern volatile uint16_t g_uart_tx_len;          /* 待发送字节数 */
extern volatile uint8_t  g_uart_tx_busy;         /* 1 = 协议层已入队，等待启动 */

/* ---- 软件环形缓冲区 ---- */
extern volatile uint8_t  g_ring_buf[UART_RX_RING_SIZE];
extern volatile uint16_t g_ring_write_index;     /* 写指针 */
extern volatile uint16_t g_ring_read_index;      /* 读指针 */
extern volatile uint16_t g_ring_dma_last_pos;    /* 上次从 DMA 缓冲搬走的绝对位置 */

/* ======================== 5. Function Prototypes ========== */
void BSP_SYS_DMA_UART_Init(void);

#endif /* BSP_SYS_DMA_H */
