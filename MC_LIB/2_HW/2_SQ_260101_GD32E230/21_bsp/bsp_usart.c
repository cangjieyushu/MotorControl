/**************************************************************************************************
*     File Name :                        BSP_USART.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             USART初始化及应用层接口源文件
**************************************************************************************************/
#include "bsp_usart.h"

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
//    /* USART configure */
//    usart_deinit(HAL_MOTOR_UART);
//    usart_baudrate_set(HAL_MOTOR_UART, 9600U);

//    usart_parity_config(HAL_MOTOR_UART, USART_PM_NONE);
//    usart_word_length_set(HAL_MOTOR_UART, USART_WL_8BIT);
//    usart_stop_bit_set(HAL_MOTOR_UART, USART_STB_1BIT);
//    
//    usart_receive_config(HAL_MOTOR_UART, USART_RECEIVE_ENABLE);
////    usart_transmit_config(HAL_MOTOR_UART, USART_TRANSMIT_ENABLE);
//    
//    usart_interrupt_enable(HAL_MOTOR_UART, USART_INT_RBNE);
//    usart_interrupt_enable(HAL_MOTOR_UART, USART_INT_TC);
//    
//    usart_enable(HAL_MOTOR_UART);
    
    /* USART configure */
    usart_deinit(HAL_MOTOR_UART);
    usart_baudrate_set(HAL_MOTOR_UART, 9600U);

    usart_parity_config(HAL_MOTOR_UART, USART_PM_NONE);
    usart_word_length_set(HAL_MOTOR_UART, USART_WL_8BIT);
    usart_stop_bit_set(HAL_MOTOR_UART, USART_STB_1BIT);
    
    usart_receive_config(HAL_MOTOR_UART, USART_RECEIVE_ENABLE);
    usart_transmit_config(HAL_MOTOR_UART, USART_TRANSMIT_ENABLE);
    
    /* 使能 USART0 的 DMA 接收请求 */
    usart_dma_transmit_config(HAL_MOTOR_UART, USART_DENT_ENABLE);
    usart_dma_receive_config(HAL_MOTOR_UART, USART_DENR_ENABLE);
    usart_interrupt_enable(HAL_MOTOR_UART, USART_INT_IDLE);
    
    usart_enable(HAL_MOTOR_UART);
}

#define SPI_SCK_GPIO_PORT           GPIOB
#define SPI_SCK_PIN                 GPIO_PIN_3

#define SPI_MOSI_GPIO_PORT          GPIOB
#define SPI_MOSI_PIN                GPIO_PIN_5

#define SPI_RST_GPIO_PORT           GPIOA
#define SPI_RST_PIN                 GPIO_PIN_0

#define SPI_DC_GPIO_PORT            GPIOA
#define SPI_DC_PIN                  GPIO_PIN_3

#define SPI_CS_GPIO_PORT            GPIOA
#define SPI_CS_PIN                  GPIO_PIN_4


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
    spi_parameter_struct spi_init_struct;

    /* SPI1 复用引脚：PB3=SCK, PB4=MISO, PB5=MOSI */
    gpio_af_set(SPI_SCK_GPIO_PORT, GPIO_AF_0, SPI_SCK_PIN | SPI_MOSI_PIN);
    gpio_mode_set(SPI_SCK_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, SPI_SCK_PIN | SPI_MOSI_PIN);
    gpio_output_options_set(SPI_SCK_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI_SCK_PIN | SPI_MOSI_PIN);

    /* 控制引脚：CS=PA4, DC=PA3, RST=PA0 */
    gpio_mode_set(SPI_RST_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SPI_RST_PIN);
    gpio_output_options_set(SPI_RST_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI_RST_PIN);

    gpio_mode_set(SPI_DC_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SPI_DC_PIN);
    gpio_output_options_set(SPI_DC_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI_DC_PIN);

    gpio_mode_set(SPI_CS_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SPI_CS_PIN);
    gpio_output_options_set(SPI_CS_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI_CS_PIN);

    /* 初始电平 */
    LCD_CS_HIGH();
    LCD_RST_HIGH();
    LCD_DC_DATA();

    /* SPI1 主机配置：Mode 3，8位，18MHz（APB1=36MHz 时 SPI_PSC_2） */
    spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode          = SPI_MASTER;
    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE; /* CPOL=1, CPHA=1 */
    spi_init_struct.nss                  = SPI_NSS_SOFT;
    spi_init_struct.prescale             = SPI_PSC_2;
    spi_init_struct.endian               = SPI_ENDIAN_MSB;
    
    /* 使能 SPI1 的 DMA 发送请求 */
    spi_dma_enable(HAL_MOTOR_SPI, SPI_DMA_TRANSMIT);
    
    spi_init(HAL_MOTOR_SPI, &spi_init_struct);
    spi_enable(HAL_MOTOR_SPI);
}
