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
    DMA_InitTypeDef DMA_InitStructure;

    /* ============================================================
     * DMA1_Channel5：USART1_RX（循环模式）
     * ============================================================ */
    DMA_DeInit(HW_SYS_UART_RX_DMA_CH);

    DMA_InitStructure.DMA_PeripheralBaseAddr = (Q32U_)&UART_RECEIVE_DATA;
    DMA_InitStructure.DMA_MemoryBaseAddr     = (Q32U_)g_uart_rx_buf;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize         = UART_RX_BUF_SIZE;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(HW_SYS_UART_RX_DMA_CH, &DMA_InitStructure);

    /* 上电即启动循环接收 */
    DMA_Cmd(HW_SYS_UART_RX_DMA_CH, ENABLE);
    USART_DMACmd(HW_SYS_UART, USART_DMAReq_Rx, ENABLE);

    /* ============================================================
     * DMA1_Channel4：USART1_TX（单次模式）
     * ============================================================ */
    DMA_DeInit(HW_SYS_UART_TX_DMA_CH);

    DMA_InitStructure.DMA_PeripheralBaseAddr = (Q32U_)&UART_TRANSMISSION_DATA;
    DMA_InitStructure.DMA_MemoryBaseAddr     = (Q32U_)g_uart_tx_buf;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize         = UART_TX_BUF_SIZE;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_Medium;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(HW_SYS_UART_TX_DMA_CH, &DMA_InitStructure);

    /* USART 使能 DMA 发送请求，但通道默认关闭，等协议层启动 */
    USART_DMACmd(HW_SYS_UART, USART_DMAReq_Tx, ENABLE);
    DMA_Cmd(HW_SYS_UART_TX_DMA_CH, DISABLE);
}
