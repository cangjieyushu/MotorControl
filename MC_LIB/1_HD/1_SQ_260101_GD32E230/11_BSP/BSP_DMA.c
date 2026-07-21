/**************************************************************************************************
*     File Name :                        BSP_DMA.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             DMA初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_DMA.h"
#include "BSP_ADC.h"

uint32_t Hal_AdcLoopData_S[8] = {0,0,0,0,0,0,0,0};
#define USART0_TDATA_ADDRESS        ((uint32_t)&USART_TDATA(USART0))
#define USART0_RDATA_ADDRESS        ((uint32_t)&USART_RDATA(USART0))
#define SPI0_RDATA_ADDRESS          ((uint32_t)&SPI_DATA(SPI0))

/**********************************************************************************************
Function: DMA_ADC_Init
Description: 电机控制用DMA初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_DMA_Init(void)
{
    
}

/**********************************************************************************************
Function: BSP_DMA_Init_S
Description: 应用层DMA初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_DMA_Init_S(void)
{
    /* ADC_DMA_channel configuration */
    dma_parameter_struct dma_data_parameter;

    /* ADC DMA_channel configuration */
    dma_deinit(HAL_ADC_DMA_CH);

    /* initialize DMA single data mode */
    dma_data_parameter.periph_addr  = (uint32_t)(&ADC_RDATA);
    dma_data_parameter.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;
    dma_data_parameter.memory_addr  = (uint32_t)(&Hal_AdcLoopData_S);
    dma_data_parameter.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;
    dma_data_parameter.periph_width = DMA_PERIPHERAL_WIDTH_32BIT;
    dma_data_parameter.memory_width = DMA_MEMORY_WIDTH_32BIT;
    dma_data_parameter.direction    = DMA_PERIPHERAL_TO_MEMORY;
    dma_data_parameter.number       = 2U;
    dma_data_parameter.priority     = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(HAL_ADC_DMA_CH, &dma_data_parameter);

    dma_circulation_enable(HAL_ADC_DMA_CH);

    /* enable DMA channel */
    dma_channel_enable(HAL_ADC_DMA_CH);
}

/**********************************************************************************************
Function: BSP_DMA_Init_UART
Description: 串口用DMA初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_DMA_Init_UART(Q08U_* ustxbuffer, Q08U_* usrxbuffer, Q08U_* spitxbuffer)
{
//    dma_parameter_struct dma_init_struct;
//    
//    /* initialize DMA channel1 */
//    dma_deinit(HAL_USART_TX_DMA_CH);
//    dma_struct_para_init(&dma_init_struct);
//    
//    dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;
//    dma_init_struct.memory_addr = (uint32_t)ustxbuffer;
//    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
//    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
//    dma_init_struct.number = HAL_UART_TX_NUM;
//    dma_init_struct.periph_addr = USART0_TDATA_ADDRESS;
//    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
//    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
//    dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
//    dma_init(HAL_USART_TX_DMA_CH, &dma_init_struct);
//    
//    /* initialize DMA channel2 */
//    dma_deinit(HAL_USART_RX_DMA_CH);
//    dma_init_struct.direction = DMA_PERIPHERAL_TO_MEMORY;
//    dma_init_struct.memory_addr = (uint32_t)usrxbuffer;
//    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
//    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
//    dma_init_struct.number = HAL_UART_RX_NUM;
//    dma_init_struct.periph_addr = USART0_RDATA_ADDRESS;
//    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
//    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
//    dma_init_struct.priority = DMA_PRIORITY_HIGH;
//    dma_init(HAL_USART_RX_DMA_CH, &dma_init_struct);
//        
//    /* configure DMA mode */
//    dma_circulation_disable(HAL_USART_TX_DMA_CH);
//    dma_memory_to_memory_disable(HAL_USART_TX_DMA_CH);
//    dma_circulation_disable(HAL_USART_RX_DMA_CH);
//    dma_memory_to_memory_disable(HAL_USART_RX_DMA_CH);
//    
//    /* USART DMA enable for transmission */
//    usart_dma_transmit_config(HAL_MOTOR_UART, USART_DENT_ENABLE);
//    /* enable DMA channel1 */
//    dma_channel_enable(HAL_USART_TX_DMA_CH);
//    /* USART DMA enable for reception */
//    usart_dma_receive_config(HAL_MOTOR_UART, USART_DENR_ENABLE);
//    /* enable DMA channel2 */
//    dma_channel_enable(HAL_USART_RX_DMA_CH);
//    
//  
//    /* initialize DMA channel3 */
//    dma_deinit(HAL_SPI_TX_DMA_CH);
//    dma_struct_para_init(&dma_init_struct);
//    
//    dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;
//    dma_init_struct.memory_addr = (uint32_t)spitxbuffer;
//    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
//    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
//    dma_init_struct.number = HAL_SPI_TX_NUM;
//    dma_init_struct.periph_addr = SPI0_RDATA_ADDRESS;
//    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
//    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
//    dma_init_struct.priority = DMA_PRIORITY_LOW;
//    dma_init(HAL_SPI_TX_DMA_CH, &dma_init_struct);
//    
//    /* configure DMA mode */
//    dma_circulation_disable(HAL_SPI_TX_DMA_CH);
//    dma_memory_to_memory_disable(HAL_SPI_TX_DMA_CH);
//    
//    /* SPI DMA enable for transmission */
//    spi_dma_enable(HAL_MOTOR_SPI, SPI_DMA_TRANSMIT);
//    /* enable DMA channel2 */
//    dma_channel_enable(HAL_SPI_TX_DMA_CH);
    
}