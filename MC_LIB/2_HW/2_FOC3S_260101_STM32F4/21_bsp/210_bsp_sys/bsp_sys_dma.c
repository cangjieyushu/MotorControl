/**
 * @file    bsp_sys_dma.c
 * @brief   系统级 DMA 初始化（串口循环接收 + 单次发送）
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_sys_dma.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ---- DMA 线性缓冲区 ---- */
uint8_t           g_uart_tx_buf[UART_TX_BUF_SIZE];
uint8_t           g_uart_rx_buf[UART_RX_BUF_SIZE];
volatile uint16_t g_uart_tx_len  = 0U;
volatile uint8_t  g_uart_tx_busy = 0U;

/* ---- 软件环形缓冲区 ---- */
volatile uint8_t  g_ring_buf[UART_RX_RING_SIZE];
volatile uint16_t g_ring_write_index  = 0U;
volatile uint16_t g_ring_read_index   = 0U;
volatile uint16_t g_ring_dma_last_pos = 0U;

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  串口 DMA 初始化（RX 循环 + TX 单次）
 */
void BSP_SYS_DMA_UART_Init(void)
{

}
