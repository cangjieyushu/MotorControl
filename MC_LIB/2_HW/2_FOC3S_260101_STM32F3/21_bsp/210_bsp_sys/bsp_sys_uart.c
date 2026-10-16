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
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* ---------------- 1. 引脚复用配置（PA9/PA10，AF7）---------------- */
    GPIO_PinAFConfig(HW_SYS_UART_TX_Port, HW_SYS_UART_TX_Pin_Source, GPIO_AF_7);
    GPIO_PinAFConfig(HW_SYS_UART_RX_Port, HW_SYS_UART_RX_Pin_Source, GPIO_AF_7);

    /* ---------------- 2. TX 引脚配置（PA9）---------------- */
    GPIO_InitStructure.GPIO_Pin   = HW_SYS_UART_TX_Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(HW_SYS_UART_TX_Port, &GPIO_InitStructure);

    /* ---------------- 3. RX 引脚配置（PA10）---------------- */
    GPIO_InitStructure.GPIO_Pin = HW_SYS_UART_RX_Pin;
    GPIO_Init(HW_SYS_UART_RX_Port, &GPIO_InitStructure);

    /* 注：RS485 方向控制（PA11）已在 BSP_SYS_GPIO_Init 中配置 */

    /* ---------------- 4. USART1 参数配置 ---------------- */
    USART_InitStructure.USART_BaudRate            = 115200;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(HW_SYS_UART, &USART_InitStructure);

    /* ---------------- 5. 中断使能（DMA 接收用 IDLE）---------------- */
    USART_ITConfig(HW_SYS_UART, USART_IT_IDLE, ENABLE);
    USART_ITConfig(HW_SYS_UART, USART_IT_RXNE, DISABLE);

    /* ---------------- 6. 使能 USART1 ---------------- */
    USART_Cmd(HW_SYS_UART, ENABLE);
}
