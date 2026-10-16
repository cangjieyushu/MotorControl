/*
*     File Name :                        bsp_sys_dma
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统级 DMA 初始化（串口收发）
*                                        包含 DMA 通道配置、全局缓冲区、中断处理
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_sys_dma.h"
#include "bsp_sys_uart.h"


/*-------------------------- 2. 变量 ---------------------------------*/
/* ---- DMA 线性缓冲区 ---- */
uint8_t g_uart_tx_buf[UART_TX_BUF_SIZE];
uint8_t g_uart_rx_buf[UART_RX_BUF_SIZE];
volatile uint16_t g_uart_tx_len = 0U;

/* ---- 接收环形缓冲区 ---- */
volatile uint8_t  g_ring_buf[UART_RX_RING_SIZE];
volatile uint16_t g_ring_write_index  = 0U;
volatile uint16_t g_ring_read_index   = 0U;
volatile uint16_t g_ring_dma_last_pos = 0U;

/* ---- 发送状态 ---- */
volatile uint8_t  g_uart_tx_busy = 0U;


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_SYS_DMA_UART_Init
Description: USART1 的 DMA 收发通道配置
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_SYS_DMA_UART_Init(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    /* ============================================================
     * DMA1_Channel5：USART1_RX（循环模式）
     * ============================================================ */
    DMA_DeInit(HW_SYS_UART_RX_DMA_CH);

    DMA_InitStructure.DMA_PeripheralBaseAddr = (Q32U_)&HW_SYS_UART->RDR;
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
    DMA_Cmd(HW_SYS_UART_RX_DMA_CH, ENABLE);

    /* 使能 DMA 传输完成/半完成中断（可选）*/
    DMA_ITConfig(HW_SYS_UART_RX_DMA_CH, DMA_IT_TC | DMA_IT_HT, ENABLE);

    /* USART1 使能 DMA 接收 */
    USART_DMACmd(HW_SYS_UART, USART_DMAReq_Rx, ENABLE);

    /* ============================================================
     * DMA1_Channel4：USART1_TX（单次模式）
     * ============================================================ */
    DMA_DeInit(HW_SYS_UART_TX_DMA_CH);

    DMA_InitStructure.DMA_PeripheralBaseAddr = (Q32U_)&HW_SYS_UART->TDR;
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

    /* 使能 DMA 传输完成中断 */
    DMA_ITConfig(HW_SYS_UART_TX_DMA_CH, DMA_IT_TC, ENABLE);

    /* USART1 使能 DMA 发送请求（通道默认关闭，等发送时由上层启动）*/
    USART_DMACmd(HW_SYS_UART, USART_DMAReq_Tx, ENABLE);

    DMA_Cmd(HW_SYS_UART_TX_DMA_CH, DISABLE);
}
