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

/* ---- 接收环形缓冲区 ---- */
volatile uint8_t  g_ring_buf[UART_RX_RING_SIZE];
volatile uint16_t g_ring_write_index  = 0U;
volatile uint16_t g_ring_read_index   = 0U;
volatile uint16_t g_ring_dma_last_pos = 0U;

/* ---- 发送状态 ---- */
volatile uint8_t  g_uart_tx_busy = 0U;

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  串口 DMA 初始化（RX 循环 + TX 单次）
 */
void BSP_SYS_DMA_UART_Init(void)
{
    dma_parameter_struct dma_init_struct;

    /* ---- DMA 接收通道（循环模式） ---- */
    dma_deinit(HAL_SYS_USART_RX_DMA_CH);

    dma_init_struct.direction       = DMA_PERIPHERAL_TO_MEMORY;
    dma_init_struct.memory_addr     = (uint32_t)g_uart_rx_buf;
    dma_init_struct.memory_inc      = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.memory_width    = DMA_MEMORY_WIDTH_8BIT;
    dma_init_struct.number          = UART_RX_BUF_SIZE;
    dma_init_struct.periph_addr     = (uint32_t)(&USART_RDATA(HW_SYS_UART));
    dma_init_struct.periph_inc      = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.periph_width    = DMA_PERIPHERAL_WIDTH_8BIT;
    dma_init_struct.priority        = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(HAL_SYS_USART_RX_DMA_CH, &dma_init_struct);

    dma_circulation_enable(HAL_SYS_USART_RX_DMA_CH);
    dma_memory_to_memory_disable(HAL_SYS_USART_RX_DMA_CH);

    /* 上电即启动循环接收 */
    dma_channel_enable(HAL_SYS_USART_RX_DMA_CH);

    /* ---- DMA 发送通道（单次模式） ---- */
    dma_deinit(HAL_SYS_USART_TX_DMA_CH);

    dma_init_struct.direction       = DMA_MEMORY_TO_PERIPHERAL;
    dma_init_struct.memory_addr     = (uint32_t)g_uart_tx_buf;   /* 发送时动态指定 */
    dma_init_struct.memory_inc      = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.memory_width    = DMA_MEMORY_WIDTH_8BIT;
    dma_init_struct.number          = 1;                         /* 发送时动态指定 */
    dma_init_struct.periph_addr     = (uint32_t)(&USART_TDATA(HW_SYS_UART));
    dma_init_struct.periph_inc      = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.periph_width    = DMA_PERIPHERAL_WIDTH_8BIT;
    dma_init_struct.priority        = DMA_PRIORITY_HIGH;
    dma_init(HAL_SYS_USART_TX_DMA_CH, &dma_init_struct);

    dma_circulation_disable(HAL_SYS_USART_TX_DMA_CH);
    dma_memory_to_memory_disable(HAL_SYS_USART_TX_DMA_CH);

    /* 纯 DMA 轮询模式：不使能 TX 完成中断，通道保持关闭，等协议层启动 */
    dma_channel_disable(HAL_SYS_USART_TX_DMA_CH);
}
