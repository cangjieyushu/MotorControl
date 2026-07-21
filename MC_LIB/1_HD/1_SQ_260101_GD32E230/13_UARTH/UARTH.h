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


#define UART_RESCEIVE_DATA        USART_RDATA(HAL_MOTOR_UART)
#define UART_TRANSMISSION_DATA    USART_TDATA(HAL_MOTOR_UART)


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
    usart_receive_config(HAL_MOTOR_UART, USART_RECEIVE_ENABLE);
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
    usart_receive_config(HAL_MOTOR_UART, USART_RECEIVE_DISABLE);
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
    usart_transmit_config(HAL_MOTOR_UART, USART_TRANSMIT_ENABLE);
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
    usart_transmit_config(HAL_MOTOR_UART, USART_TRANSMIT_DISABLE);
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
    return (Q32U_)dma_flag_get(HAL_USART_TX_DMA_CH, DMA_FLAG_FTF);
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
    dma_flag_clear(HAL_USART_TX_DMA_CH, DMA_FLAG_G);
    dma_channel_disable(HAL_USART_TX_DMA_CH);
    dma_memory_address_config(HAL_USART_TX_DMA_CH, (Q32U_)txbuffer);
    dma_transfer_number_config(HAL_USART_TX_DMA_CH, HAL_UART_TX_NUM);
    dma_channel_enable(HAL_USART_TX_DMA_CH);
    usart_dma_transmit_config(HAL_MOTOR_UART, USART_DENT_ENABLE);
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
    return (Q32U_)dma_flag_get(HAL_USART_RX_DMA_CH, DMA_FLAG_FTF);
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
    dma_flag_clear(HAL_USART_RX_DMA_CH, DMA_FLAG_G);
    dma_channel_disable(HAL_USART_RX_DMA_CH);
    dma_memory_address_config(HAL_USART_RX_DMA_CH, (Q32U_)rxbuffer);
    dma_transfer_number_config(HAL_USART_RX_DMA_CH, HAL_UART_RX_NUM);
    dma_channel_enable(HAL_USART_RX_DMA_CH);
    usart_dma_receive_config(HAL_MOTOR_UART, USART_DENR_ENABLE);
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
    return (Q32U_)dma_flag_get(HAL_SPI_TX_DMA_CH, DMA_FLAG_FTF);
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
    dma_flag_clear(HAL_SPI_TX_DMA_CH, DMA_FLAG_G);
    dma_channel_disable(HAL_SPI_TX_DMA_CH);
    dma_memory_address_config(HAL_SPI_TX_DMA_CH, (Q32U_)spitxbuffer);
    dma_transfer_number_config(HAL_SPI_TX_DMA_CH, len);
    dma_channel_enable(HAL_SPI_TX_DMA_CH);
    spi_dma_enable(HAL_MOTOR_SPI, SPI_DMA_TRANSMIT);
}

#endif /* UARTH_H */
