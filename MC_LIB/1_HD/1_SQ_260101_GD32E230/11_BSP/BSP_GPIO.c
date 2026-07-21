/**************************************************************************************************
*     File Name :                        BSP_GPIO.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             GPIO初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_GPIO.h"

/**********************************************************************************************
Function: BSP_GPIO_Init
Description: GPIO初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_GPIO_Init(void)
{
    /*GPIO:*/ 
    
    /* configure RLYN GPIO port */ 
    gpio_mode_set(RLYN_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, RLYN_PIN);
    gpio_output_options_set(RLYN_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, RLYN_PIN);
    /* reset RLYN GPIO pin */
    gpio_bit_reset(RLYN_GPIO_PORT, RLYN_PIN);
//    /* configure RLY0 GPIO port */ 
//    gpio_mode_set(RLY0_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, RLY0_PIN);
//    gpio_output_options_set(RLY0_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, RLY0_PIN);
//    /* reset RLY0 GPIO pin */
//    gpio_bit_reset(RLY0_GPIO_PORT, RLY0_PIN);
//    /* configure RLY1 GPIO port */ 
//    gpio_mode_set(RLY1_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, RLY1_PIN);
//    gpio_output_options_set(RLY1_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, RLY1_PIN);
//    /* reset RLY1 GPIO pin */
//    gpio_bit_reset(RLY1_GPIO_PORT, RLY1_PIN);
    
//    /* configure BTN1 GPIO port */ 
//    gpio_mode_set(BTN1_GPIO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, BTN1_PIN);
////    /* reset BTN1 GPIO pin */
////    gpio_bit_reset(BTN1_GPIO_PORT, BTN1_PIN);
//    /* configure BTN2 GPIO port */ 
//    gpio_mode_set(BTN2_GPIO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, BTN2_PIN);
////    /* reset BTN2 GPIO pin */
////    gpio_bit_reset(BTN2_GPIO_PORT, BTN2_PIN);
//    /* configure BTN3 GPIO port */ 
//    gpio_mode_set(BTN3_GPIO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, BTN3_PIN);
////    /* reset BTN3 GPIO pin */
////    gpio_bit_reset(BTN3_GPIO_PORT, BTN3_PIN);
//    /* configure BTN4 GPIO port */ 
//    gpio_mode_set(BTN4_GPIO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, BTN4_PIN);
////    /* reset BTN4 GPIO pin */
////    gpio_bit_reset(BTN4_GPIO_PORT, BTN4_PIN);



    /*TIM0:*/ 
    /*configure PA8/PA9/PA10(TIMER0/CH0/CH1/CH2) as alternate function*/
    gpio_mode_set(UH_PWM_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, UH_PWM_PIN);
    gpio_output_options_set(UH_PWM_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UH_PWM_PIN);

    gpio_mode_set(VH_PWM_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, VH_PWM_PIN);
    gpio_output_options_set(VH_PWM_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,VH_PWM_PIN);

    gpio_mode_set(WH_PWM_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, WH_PWM_PIN);
    gpio_output_options_set(WH_PWM_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,WH_PWM_PIN);

    gpio_af_set(UH_PWM_GPIO_PORT, GPIO_AF_2, UH_PWM_PIN);
    gpio_af_set(VH_PWM_GPIO_PORT, GPIO_AF_2, VH_PWM_PIN);
    gpio_af_set(WH_PWM_GPIO_PORT, GPIO_AF_2, WH_PWM_PIN);

    /*configure PB13/PB14/PB15(TIMER0/CH0N/CH1N/CH2N) as alternate function*/
    gpio_mode_set(UL_PWM_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, UL_PWM_PIN);
    gpio_output_options_set(UL_PWM_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UL_PWM_PIN);

    gpio_mode_set(VL_PWM_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, VL_PWM_PIN);
    gpio_output_options_set(VL_PWM_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,VL_PWM_PIN);

    gpio_mode_set(WL_PWM_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, WL_PWM_PIN);
    gpio_output_options_set(WL_PWM_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,WL_PWM_PIN);

    gpio_af_set(UL_PWM_GPIO_PORT, GPIO_AF_2, UL_PWM_PIN);
    gpio_af_set(VL_PWM_GPIO_PORT, GPIO_AF_2, VL_PWM_PIN);
    gpio_af_set(WL_PWM_GPIO_PORT, GPIO_AF_2, WL_PWM_PIN);
    
    gpio_mode_set(BRK_PWM_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, BRK_PWM_PIN);
    gpio_af_set(BRK_PWM_GPIO_PORT, GPIO_AF_2, BRK_PWM_PIN);


    //ADC
    /* config the GPIO as analog mode */
    gpio_mode_set(ADC_U_BEMF_GPIO_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, ADC_U_BEMF_PIN);
    gpio_mode_set(ADC_V_BEMF_GPIO_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, ADC_V_BEMF_PIN);
    gpio_mode_set(ADC_W_BEMF_GPIO_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, ADC_W_BEMF_PIN);
    gpio_mode_set(ADC_PHASE_GPIO_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, ADC_PHASE_PIN);
    gpio_mode_set(ADC_VBUS_GPIO_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, ADC_VBUS_PIN);
    gpio_mode_set(ADC_TEMP_GPIO_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, ADC_TEMP_PIN);


    /* config port to USARTx_Tx */
    /* config port to USARTx_Rx */
    gpio_af_set(UART_TX_GPIO_PORT, GPIO_AF_0, UART_TX_PIN);
    gpio_af_set(UART_RX_GPIO_PORT, GPIO_AF_0, UART_RX_PIN);

    /* config USART Tx as alternate function push-pull */
    gpio_mode_set(UART_TX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, UART_TX_PIN);
    gpio_output_options_set(UART_TX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, UART_TX_PIN);

    /* config USART Rx as alternate function push-pull */
    gpio_mode_set(UART_RX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, UART_RX_PIN);
    gpio_output_options_set(UART_RX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, UART_RX_PIN);
    
    
//    /* config port to SPI */
//    gpio_af_set(SPI_SCK_GPIO_PORT, GPIO_AF_0, SPI_SCK_PIN);
//    gpio_mode_set(SPI_SCK_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, SPI_SCK_PIN);
//    gpio_output_options_set(SPI_SCK_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI_SCK_PIN);
//    
//    gpio_af_set(SPI_MOSI_GPIO_PORT, GPIO_AF_0, SPI_MOSI_PIN);
//    gpio_mode_set(SPI_MOSI_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, SPI_MOSI_PIN);
//    gpio_output_options_set(SPI_MOSI_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI_MOSI_PIN);
//    
//    /* configure SPI_CS GPIO port */ 
//    gpio_mode_set(SPI_CS_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SPI_CS_PIN);
//    gpio_output_options_set(SPI_CS_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, SPI_CS_PIN);
//    /* reset SPI_CS GPIO pin */
//    gpio_bit_reset(SPI_CS_GPIO_PORT, SPI_CS_PIN);
//    /* configure SPI_RST GPIO port */ 
//    gpio_mode_set(SPI_RST_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SPI_RST_PIN);
//    gpio_output_options_set(SPI_RST_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, SPI_RST_PIN);
//    /* reset SPI_RST GPIO pin */
//    gpio_bit_reset(SPI_RST_GPIO_PORT, SPI_RST_PIN);
//    /* configure SPI_A0 GPIO port */ 
//    gpio_mode_set(SPI_A0_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SPI_A0_PIN);
//    gpio_output_options_set(SPI_A0_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, SPI_A0_PIN);
//    /* reset SPI_A0 GPIO pin */
//    gpio_bit_reset(SPI_A0_GPIO_PORT, RLY0_PIN);
    
}


void BSP_GPIO_RLY0(Q32U_ state)
{
//    if(state == 1U)
//    {
//        gpio_bit_set(RLY0_GPIO_PORT, RLY0_PIN);
//    }
//    else
//    {
//        gpio_bit_reset(RLY0_GPIO_PORT, RLY0_PIN);
//    }
}

void BSP_GPIO_RLY1(Q32U_ state)
{
//    if(state == 1U)
//    {
//        gpio_bit_set(RLY1_GPIO_PORT, RLY1_PIN);
//    }
//    else
//    {
//        gpio_bit_reset(RLY1_GPIO_PORT, RLY1_PIN);
//    }
}

void BSP_GPIO_RLYN(Q32U_ state)
{
    if(state == 1U)
    {
        gpio_bit_set(RLYN_GPIO_PORT, RLYN_PIN);
    }
    else
    {
        gpio_bit_reset(RLYN_GPIO_PORT, RLYN_PIN);
    }
}


//Q32U_ BSP_GPIO_BTN1(void)
//{
//    return (Q32U_)gpio_input_bit_get(BTN1_GPIO_PORT, BTN1_PIN);
//}

//Q32U_ BSP_GPIO_BTN2(void)
//{
//    return (Q32U_)gpio_input_bit_get(BTN2_GPIO_PORT, BTN2_PIN);
//}

//Q32U_ BSP_GPIO_BTN3(void)
//{
//    return (Q32U_)gpio_input_bit_get(BTN3_GPIO_PORT, BTN3_PIN);
//}

//Q32U_ BSP_GPIO_BTN4(void)
//{
//    return (Q32U_)gpio_input_bit_get(BTN4_GPIO_PORT, BTN4_PIN);
//}


void BSP_SPI_RST(Q32U_ state)
{
//    if(state == 1U)
//    {
//        gpio_bit_set(SPI_RST_GPIO_PORT, SPI_RST_PIN);
//    }
//    else
//    {
//        gpio_bit_reset(SPI_RST_GPIO_PORT, SPI_RST_PIN);
//    }
}

void BSP_SPI_A0(Q32U_ state)
{
//    if(state == 1U)
//    {
//        gpio_bit_set(SPI_A0_GPIO_PORT, SPI_A0_PIN);
//    }
//    else
//    {
//        gpio_bit_reset(SPI_A0_GPIO_PORT, SPI_A0_PIN);
//    }
}

void BSP_SPI_CS(Q32U_ state)
{
//    if(state == 1U)
//    {
//        gpio_bit_set(SPI_CS_GPIO_PORT, SPI_CS_PIN);
//    }
//    else
//    {
//        gpio_bit_reset(SPI_CS_GPIO_PORT, SPI_CS_PIN);
//    }
}
