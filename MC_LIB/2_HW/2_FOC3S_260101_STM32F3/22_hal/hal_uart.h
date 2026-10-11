/**************************************************************************************************
*     File Name :                        UARTH.h
*     Library/Module Name :              UARTH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             UART HAL 层头文件（STM32F303 标准库）
**************************************************************************************************/
#ifndef UARTH_H
#define UARTH_H

#include "hw_clk.h"
#include "hw_map.h"
#include "hw_para.h"
#include "bsp.h"


/*-------------------------- 1. 数据寄存器访问宏 -------------------------*/
#define UART_RESCEIVE_DATA        (HAL_HMI_UART->RDR)
#define UART_TRANSMISSION_DATA    (HAL_HMI_UART->TDR)


/*-------------------------- 2. 接口函数声明 ----------------------------*/
void UARTH_Init(void);          /* 放在 UARTH.c 中实现 */


/*-------------------------- 3. UART 收发使能 ---------------------------*/
/**********************************************************************************************
Function: UARTH_Enable_Rx
Description: UART 打开接收
***********************************************************************************************/
static inline void UARTH_Enable_Rx(void)
{
    USART_DirectionModeCmd(HAL_HMI_UART, USART_Mode_Rx, ENABLE);
}

/**********************************************************************************************
Function: UARTH_Disable_Rx
Description: UART 关闭接收
***********************************************************************************************/
static inline void UARTH_Disable_Rx(void)
{
    USART_DirectionModeCmd(HAL_HMI_UART, USART_Mode_Rx, DISABLE);
}

/**********************************************************************************************
Function: UARTH_Enable_Tx
Description: UART 打开发送（同时切换到 RS485 发送方向）
***********************************************************************************************/
static inline void UARTH_Enable_Tx(void)
{
    BSP_GPIO_TXEN(1U);                                          /* 切到发送方向 */
    USART_DirectionModeCmd(HAL_HMI_UART, USART_Mode_Tx, ENABLE);
}

/**********************************************************************************************
Function: UARTH_Disable_Tx
Description: UART 关闭发送（同时切回 RS485 接收方向）
***********************************************************************************************/
static inline void UARTH_Disable_Tx(void)
{
    USART_DirectionModeCmd(HAL_HMI_UART, USART_Mode_Tx, DISABLE);
    BSP_GPIO_TXEN(0U);                                          /* 切回接收方向 */
}


/*-------------------------- 4. UART 的 DMA 收发 ------------------------*/
/**********************************************************************************************
Function: UARTH_Tx_DMA_Flag
Description: 读取 UART 的 DMA 发送完成标志（TC）
***********************************************************************************************/
static inline Q32U_ UARTH_Tx_DMA_Flag(void)
{
    return (Q32U_)DMA_GetFlagStatus(HAL_HMI_USART_TX_DMA_TC_FLAG);
}

/**********************************************************************************************
Function: UARTH_Tx_DMA_Start
Description: 启动 UART 的 DMA 发送
Input: txbuffer - 待发送数据指针；len - 长度
***********************************************************************************************/
static inline void UARTH_Tx_DMA_Start(Q08U_* txbuffer, Q32U_ len)
{
    DMA_Cmd(HAL_HMI_USART_TX_DMA_CH, DISABLE);
    DMA_ClearFlag(HAL_HMI_USART_TX_DMA_GL_FLAG);
    HAL_HMI_USART_TX_DMA_CH->CMAR  = (Q32U_)txbuffer;
    HAL_HMI_USART_TX_DMA_CH->CNDTR = (Q16U_)len;
    DMA_Cmd(HAL_HMI_USART_TX_DMA_CH, ENABLE);
    USART_DMACmd(HAL_HMI_UART, USART_DMAReq_Tx, ENABLE);
}

/**********************************************************************************************
Function: UARTH_Tx_DMA_Stop
Description: 停止 UART 的 DMA 发送
***********************************************************************************************/
static inline void UARTH_Tx_DMA_Stop(void)
{
    USART_DMACmd(HAL_HMI_UART, USART_DMAReq_Tx, DISABLE);
    DMA_Cmd(HAL_HMI_USART_TX_DMA_CH, DISABLE);
}

/**********************************************************************************************
Function: UARTH_Rx_DMA_Flag
Description: 读取 UART 的 DMA 接收完成标志
***********************************************************************************************/
static inline Q32U_ UARTH_Rx_DMA_Flag(void)
{
    return (Q32U_)DMA_GetFlagStatus(HAL_HMI_USART_RX_DMA_TC_FLAG);
}

/**********************************************************************************************
Function: UARTH_Rx_DMA_Start
Description: 启动 UART 的 DMA 接收
Input: rxbuffer - 接收缓冲区指针；len - 期望接收长度
***********************************************************************************************/
static inline void UARTH_Rx_DMA_Start(Q08U_* rxbuffer, Q32U_ len)
{
    DMA_Cmd(HAL_HMI_USART_RX_DMA_CH, DISABLE);
    DMA_ClearFlag(HAL_HMI_USART_RX_DMA_GL_FLAG);
    HAL_HMI_USART_RX_DMA_CH->CMAR  = (Q32U_)rxbuffer;
    HAL_HMI_USART_RX_DMA_CH->CNDTR = (Q16U_)len;
    DMA_Cmd(HAL_HMI_USART_RX_DMA_CH, ENABLE);
    USART_DMACmd(HAL_HMI_UART, USART_DMAReq_Rx, ENABLE);
}

/**********************************************************************************************
Function: UARTH_Rx_DMA_Stop
Description: 停止 UART 的 DMA 接收
***********************************************************************************************/
static inline void UARTH_Rx_DMA_Stop(void)
{
    USART_DMACmd(HAL_HMI_UART, USART_DMAReq_Rx, DISABLE);
    DMA_Cmd(HAL_HMI_USART_RX_DMA_CH, DISABLE);
}

/**********************************************************************************************
Function: UARTH_Rx_DMA_RemainCount
Description: 读取 UART 的 DMA 接收剩余数据数（用于 IDLE 帧长度计算）
***********************************************************************************************/
static inline Q32U_ UARTH_Rx_DMA_RemainCount(void)
{
    return (Q32U_)DMA_GetCurrDataCounter(HAL_HMI_USART_RX_DMA_CH);
}

#endif /* UARTH_H */
