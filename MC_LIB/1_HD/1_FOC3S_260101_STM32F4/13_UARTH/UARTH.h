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


#define UART_RESCEIVE_DATA        USART1->DR
#define UART_TRANSMISSION_DATA    USART1->DR


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
    
}

/**********************************************************************************************
Function: UARTH_Disable_Rx
Description: UART关闭接收
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void UARTH_Disable_Rx(void)
{
    
}

/**********************************************************************************************
Function: UARTH_Enable_Tx
Description: UART1打开发送
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void UARTH_Enable_Tx(void)
{
    
}

/**********************************************************************************************
Function: UARTH_Disable_Tx
Description: UART关闭发送
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void UARTH_Disable_Tx(void)
{
    
}

/**********************************************************************************************
Function: UARTH_Tx_Flag
Description: UART的DMA发送完成
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline Q32U_ UARTH_Tx_DMA_Flag(void)
{
    return 0;
}

/**********************************************************************************************
Function: UARTH_Tx_DMA_Start
Description: UART的DMA发送
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void UARTH_Tx_DMA_Start(Q08U_* txbuffer)
{
    
}

/**********************************************************************************************
Function: UARTH_Rx_Flag
Description: UART的DMA发送完成
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline Q32U_ UARTH_Rx_DMA_Flag(void)
{
    return 0;
}

/**********************************************************************************************
Function: UARTH_Rx_DMA_Start
Description: UART的DMA接收
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void UARTH_Rx_DMA_Start(Q08U_* rxbuffer)
{
    
}

/**********************************************************************************************
Function: SPIH_Tx_Flag
Description: SPI的DMA发送完成
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline Q32U_ SPIH_Tx_DMA_Flag(void)
{
    return 0;
}

/**********************************************************************************************
Function: SPIH_Tx_DMA_Start
Description: SPI的DMA发送
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void SPIH_Tx_DMA_Start(Q08U_* spitxbuffer, Q32U_ len)
{
    
}

#endif /* UARTH_H */
