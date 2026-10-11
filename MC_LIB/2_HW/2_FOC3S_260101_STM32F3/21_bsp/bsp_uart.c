/*
*     File Name :                        bsp_uart
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             UART初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_uart.h"


/*-------------------------- 2. 变量 ---------------------------------*/
/* 与 bsp_uart.h 中的 extern 声明一致 */
uint8_t g_uart_tx_buf[UART1_TX_BUF_SIZE];
uint8_t g_uart_rx_buf[UART1_RX_BUF_SIZE];


/*-------------------------- 3. 公有接口实现 -----------------------------*/
void BSP_UART_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* ---------------- 1. 引脚复用配置 ----------------
     * F303 的 USART1 可选引脚：
     *   PA9 (TX) / PA10 (RX)   ← 本工程使用（AF7）
     *   PB6 (TX) / PB7 (RX)    ← 备用（AF7）
     *   PC4 (TX) / PC5 (RX)    ← 备用（AF7）
     */
    GPIO_PinAFConfig(UART_TX_PORT, UART_TX_Pin_Source, GPIO_AF_7);   /* PA9  → USART1_TX */
    GPIO_PinAFConfig(UART_RX_PORT, UART_RX_Pin_Source, GPIO_AF_7);   /* PA10 → USART1_RX */

    /* ---------------- 2. TX 引脚配置（PA9）---------------- */
    GPIO_InitStructure.GPIO_Pin   = UART_TX_Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(UART_TX_PORT, &GPIO_InitStructure);

    /* ---------------- 3. RX 引脚配置（PA10）---------------- */
    GPIO_InitStructure.GPIO_Pin = UART_RX_Pin;
    GPIO_Init(UART_RX_PORT, &GPIO_InitStructure);

    /* ---------------- 4. RS485 方向控制（PA11，GPIO 输出）---------------- */
    GPIO_InitStructure.GPIO_Pin   = UART_EN_Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_Init(UART_EN_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(UART_EN_PORT, UART_EN_Pin);              /* 默认接收方向 */

    /* ---------------- 5. USART1 参数配置 ---------------- */
    USART_InitStructure.USART_BaudRate            = 115200;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(HAL_HMI_UART, &USART_InitStructure);         /* ★ 用 HAL_HMI_UART */

    /* ---------------- 6. 中断使能（DMA 接收用 IDLE）---------------- */
    USART_ITConfig(HAL_HMI_UART, USART_IT_IDLE, ENABLE);    /* ★ 帧结束检测 */
    USART_ITConfig(HAL_HMI_UART, USART_IT_RXNE, DISABLE);   /* ★ DMA 接收不用 RXNE */

    /* ---------------- 7. 使能 USART1 ---------------- */
    USART_Cmd(HAL_HMI_UART, ENABLE);
}


void BSP_UART_DMA_Init(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    /* ============================================================
     * DMA1_Channel5：USART1_RX（循环模式）
     * ============================================================ */
    DMA_DeInit(HAL_HMI_USART_RX_DMA_CH);                    /* ★ */

    DMA_InitStructure.DMA_PeripheralBaseAddr = (Q32U_)&HAL_HMI_UART->RDR;   /* ★ */
    DMA_InitStructure.DMA_MemoryBaseAddr     = (Q32U_)g_uart_rx_buf;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize         = UART1_RX_BUF_SIZE;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(HAL_HMI_USART_RX_DMA_CH, &DMA_InitStructure);
    DMA_Cmd(HAL_HMI_USART_RX_DMA_CH, ENABLE);

    /* 使能 DMA 传输完成/半完成中断（可选）*/
    DMA_ITConfig(HAL_HMI_USART_RX_DMA_CH, DMA_IT_TC | DMA_IT_HT, ENABLE);

    /* USART1 使能 DMA 接收 */
    USART_DMACmd(HAL_HMI_UART, USART_DMAReq_Rx, ENABLE);

    /* ============================================================
     * DMA1_Channel4：USART1_TX（单次模式）
     * ============================================================ */
    DMA_DeInit(HAL_HMI_USART_TX_DMA_CH);                    /* ★ */

    DMA_InitStructure.DMA_PeripheralBaseAddr = (Q32U_)&HAL_HMI_UART->TDR;   /* ★ */
    DMA_InitStructure.DMA_MemoryBaseAddr     = (Q32U_)g_uart_tx_buf;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;       /* 内存 → 外设 */
    DMA_InitStructure.DMA_BufferSize         = UART1_TX_BUF_SIZE;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; /* ★ 补全 */
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;     /* ★ 补全 */
    DMA_InitStructure.DMA_Priority           = DMA_Priority_Medium;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(HAL_HMI_USART_TX_DMA_CH, &DMA_InitStructure);

    /* 使能 DMA 传输完成中断 */
    DMA_ITConfig(HAL_HMI_USART_TX_DMA_CH, DMA_IT_TC, ENABLE);

    /* USART1 使能 DMA 发送请求（通道默认关闭，等发送时由 UARTH_Tx_DMA_Start 打开）*/
    USART_DMACmd(HAL_HMI_UART, USART_DMAReq_Tx, ENABLE);

    DMA_Cmd(HAL_HMI_USART_TX_DMA_CH, DISABLE);
}
