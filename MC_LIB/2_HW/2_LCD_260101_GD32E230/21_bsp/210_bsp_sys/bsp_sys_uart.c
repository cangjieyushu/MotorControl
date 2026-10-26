/**
 * @file    bsp_sys_uart.c
 * @brief   上位机通讯串口初始化（纯 DMA，无 IDLE 中断）
 *          - 接收由 DMA 循环 + 轮询搬运，不使用 RXNE/IDLE 中断
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_sys_uart.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  USART 参数配置
 */
void BSP_SYS_UART_Init(void)
{
    /* USART 外设复位与基本参数 */
    usart_deinit(HW_SYS_UART);
    usart_baudrate_set(HW_SYS_UART, 9600U);

    usart_parity_config(HW_SYS_UART, USART_PM_NONE);
    usart_word_length_set(HW_SYS_UART, USART_WL_8BIT);
    usart_stop_bit_set(HW_SYS_UART, USART_STB_1BIT);

    usart_receive_config(HW_SYS_UART, USART_RECEIVE_ENABLE);
    usart_transmit_config(HW_SYS_UART, USART_TRANSMIT_ENABLE);

    /* 使能 USART0 的 DMA 收发请求 */
    usart_dma_transmit_config(HW_SYS_UART, USART_DENT_ENABLE);
    usart_dma_receive_config(HW_SYS_UART, USART_DENR_ENABLE);

    /* 关闭 IDLE / RXNE 中断（纯 DMA 轮询） */
    usart_interrupt_disable(HW_SYS_UART, USART_INT_IDLE);
    usart_interrupt_disable(HW_SYS_UART, USART_INT_RBNE);

    usart_enable(HW_SYS_UART);
}