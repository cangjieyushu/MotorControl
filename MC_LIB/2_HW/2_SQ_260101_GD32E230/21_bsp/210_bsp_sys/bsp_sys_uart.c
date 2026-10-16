/*
*     File Name :                        bsp_sys_uart
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             上位机通讯串口初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_sys_uart.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_SYS_UART_Init
Description: USART 参数配置
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_SYS_UART_Init(void)
{
    /* USART configure */
    usart_deinit(HW_SYS_UART);
    usart_baudrate_set(HW_SYS_UART, BSP_SYS_UART_BAUD);

    usart_parity_config(HW_SYS_UART, USART_PM_NONE);
    usart_word_length_set(HW_SYS_UART, USART_WL_8BIT);
    usart_stop_bit_set(HW_SYS_UART, USART_STB_1BIT);
    
    usart_receive_config(HW_SYS_UART, USART_RECEIVE_ENABLE);
    usart_transmit_config(HW_SYS_UART, USART_TRANSMIT_ENABLE);
    
    /* 使能 USART0 的 DMA 接收请求 */
    usart_dma_transmit_config(HW_SYS_UART, USART_DENT_ENABLE);
    usart_dma_receive_config(HW_SYS_UART, USART_DENR_ENABLE);
    usart_interrupt_enable(HW_SYS_UART, USART_INT_IDLE);
    
    usart_interrupt_flag_clear(HW_SYS_UART, USART_INT_FLAG_IDLE);
    usart_enable(HW_SYS_UART);
    
}
