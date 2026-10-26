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
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* ---------------- 1. 引脚复用配置（PA9/PA10，AF7） ---------------- */
    GPIO_PinAFConfig(HW_SYS_UART_TX_Port, HW_SYS_UART_TX_Pin_Source, GPIO_AF_7);
    GPIO_PinAFConfig(HW_SYS_UART_RX_Port, HW_SYS_UART_RX_Pin_Source, GPIO_AF_7);

    /* ---------------- 2. TX 引脚配置（PA9） ---------------- */
    GPIO_InitStructure.GPIO_Pin   = HW_SYS_UART_TX_Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(HW_SYS_UART_TX_Port, &GPIO_InitStructure);

    /* ---------------- 3. RX 引脚配置（PA10） ---------------- */
    GPIO_InitStructure.GPIO_Pin = HW_SYS_UART_RX_Pin;
    GPIO_Init(HW_SYS_UART_RX_Port, &GPIO_InitStructure);

    /* 注：RS485 方向控制（PA11）已在 BSP_SYS_GPIO_Init 中配置 */

    /* ---------------- 4. USART1 参数配置 ---------------- */
    USART_InitStructure.USART_BaudRate            = 9600;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(HW_SYS_UART, &USART_InitStructure);

    /* ---------------- 5. 关闭所有接收中断（纯 DMA 轮询） ---------------- */
    USART_ITConfig(HW_SYS_UART, USART_IT_IDLE, DISABLE);
    USART_ITConfig(HW_SYS_UART, USART_IT_RXNE, DISABLE);

    /* ---------------- 6. 使能 USART1 ---------------- */
    USART_Cmd(HW_SYS_UART, ENABLE);
}
