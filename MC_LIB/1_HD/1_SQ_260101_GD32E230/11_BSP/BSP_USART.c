/**************************************************************************************************
*     File Name :                        BSP_USART.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             USART初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_USART.h"

/**********************************************************************************************
Function: BSP_USART_Init
Description: USART初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_USART_Init(void)
{
    /* USART configure */
    usart_deinit(HAL_MOTOR_UART);
    usart_baudrate_set(HAL_MOTOR_UART, 9600U);

    usart_parity_config(HAL_MOTOR_UART, USART_PM_NONE);
    usart_word_length_set(HAL_MOTOR_UART, USART_WL_8BIT);
    usart_stop_bit_set(HAL_MOTOR_UART, USART_STB_1BIT);
    
    usart_receive_config(HAL_MOTOR_UART, USART_RECEIVE_ENABLE);
//    usart_transmit_config(HAL_MOTOR_UART, USART_TRANSMIT_ENABLE);
    
    usart_interrupt_enable(HAL_MOTOR_UART, USART_INT_RBNE);
    usart_interrupt_enable(HAL_MOTOR_UART, USART_INT_TC);
    
    usart_enable(HAL_MOTOR_UART);
}

/**********************************************************************************************
Function: BSP_SPI_Init
Description: SPI初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_SPI_Init(void)
{
//    spi_parameter_struct spi_init_struct;
//    /* deinitilize SPI and the parameters */
//    spi_i2s_deinit(HAL_MOTOR_SPI);
//    spi_struct_para_init(&spi_init_struct);

//    /* configure SPI0 parameter */
//    spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
//    spi_init_struct.device_mode          = SPI_MASTER;
//    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
//    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
//    spi_init_struct.nss                  = SPI_NSS_SOFT;
//    spi_init_struct.prescale             = SPI_PSC_64;
//    spi_init_struct.endian               = SPI_ENDIAN_MSB;
//    spi_init(HAL_MOTOR_SPI, &spi_init_struct);
//    
//    spi_enable(HAL_MOTOR_SPI);
}
