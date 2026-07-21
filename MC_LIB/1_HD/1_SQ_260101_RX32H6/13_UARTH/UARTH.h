/**************************************************************************************************
*     File Name :                        UARTH.h
*     Library/Module Name :              UARTH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制HAL层头文件
**************************************************************************************************/
#ifndef UARTH_H
#define UARTH_H

#include "HAL_CFG.h"


//#define UART_RESCEIVE_DATA        USART_RDATA(HAL_MOTOR_UART)
//#define UART_TRANSMISSION_DATA    USART_TDATA(HAL_MOTOR_UART)
#define UART_RESCEIVE_DATA        UART1->DR
#define UART_TRANSMISSION_DATA    UART1->DR


/**********************************************************************************************
Function: UARTH_Enable_Rx
Description: UART打开接收
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void UARTH_Enable_Rx(void)
{
//    usart_receive_config(HAL_MOTOR_UART, USART_RECEIVE_ENABLE);
}

/**********************************************************************************************
Function: UART_Disable_Rx
Description: UART关闭接收
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void UARTH_Disable_Rx(void)
{
//    usart_receive_config(HAL_MOTOR_UART, USART_RECEIVE_DISABLE);
}

/**********************************************************************************************
Function: UART1_Enable_Tx
Description: UART1打开发送
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void UARTH_Enable_Tx(void)
{
//    usart_transmit_config(HAL_MOTOR_UART, USART_TRANSMIT_ENABLE);
}

/**********************************************************************************************
Function: UART_Disable_Tx
Description: UART关闭发送
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void UARTH_Disable_Tx(void)
{
//    usart_transmit_config(HAL_MOTOR_UART, USART_TRANSMIT_DISABLE);
}

/**********************************************************************************************
Function: UART_Tx_Flag
Description: UART的DMA发送完成
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline Q32U_ UARTH_Tx_Flag(void)
{
    return 0;
//    return (Q32U_)usart_flag_get(HAL_MOTOR_UART, USART_FLAG_TC);
}

/**********************************************************************************************
Function: UART_Tx_Clear
Description: UART的DMA发送清除
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void UARTH_Tx_Start(void)
{
//    usart_flag_clear(HAL_MOTOR_UART, USART_FLAG_TC);
//    dma_channel_enable(DMA_CH1);
}

/**********************************************************************************************
Function: UARTH_Rx_Start
Description: UART的DMA发送清除
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void UARTH_Rx_Start(void)
{
//    usart_flag_clear(HAL_MOTOR_UART, USART_FLAG_TC);
//    dma_channel_enable(DMA_CH1);
}


#endif /* UARTH_H */
