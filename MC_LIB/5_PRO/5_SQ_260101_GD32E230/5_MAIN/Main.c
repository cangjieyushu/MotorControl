/**************************************************************************************************
*     File Name :                        Main.c
*     Library/Module Name :              Main
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             任务管理
**************************************************************************************************/

#include "main.h"

int main(void)
{
    __disable_irq();
    
    BSP_CLK_Init();
    BSP_GPIO_Init();
    BSP_ADC_Init();
    BSP_DMA_Init_S();
    BSP_PWM_Init();
    BSP_TIM_Init();
    BSP_ISR_Init();
    BSP_USART_Init();
    BSP_SPI_Init();
    //BSP_DMA_Init_UART(UART_Ctrl.txdata, UART_Ctrl.rxdata, (Q08U_*)framebuffer);
    
#if(JSCOPE_RTT_EN == 1U)
    SEGGER_RTT_ConfigUpBuffer(1,JSCOPE_RTT_Sytle,Buffer,sizeof(Buffer),SEGGER_RTT_MODE_NO_BLOCK_SKIP);
#endif
    
    __enable_irq();
    
    for(;;)
    {
        System_10msTask_Flow();
    }
}

void ADC_CMP_IRQHandler(void)
{
    if(adc_interrupt_flag_get(ADC_INT_FLAG_EOIC))
    {
        adc_interrupt_flag_clear(ADC_INT_FLAG_EOIC);
		MCSQ_Current_Flow(MOTOR_NUMBER_N0);
    }
}

void SysTick_Handler(void)
{
    System_1msTask_Flow();
    MCSQ_Speed_Flow(MOTOR_NUMBER_N0);
}

void TIMER2_IRQHandler(void)
{
    if(timer_interrupt_flag_get(HAL_MOTOR_SWITCH_TIM, TIMER_INT_FLAG_CH0))
    {
        timer_interrupt_flag_clear(HAL_MOTOR_SWITCH_TIM, TIMER_INT_FLAG_CH0);
        MCSQ_Switch_Flow(MOTOR_NUMBER_N0);
    }
}
void TIMER0_Channel_IRQHandler(void)
{
    if(timer_interrupt_flag_get(HAL_MOTOR_PWM, TIMER_INT_FLAG_CH3))
    {
        timer_interrupt_flag_clear(HAL_MOTOR_PWM, TIMER_INT_FLAG_CH3);
        MCSQ_ADC_Trig_Flow(MOTOR_NUMBER_N0);
    }
}

void USART0_IRQHandler(void)
{
    if(RESET != usart_interrupt_flag_get(HAL_MOTOR_UART, USART_INT_FLAG_RBNE))
    {
        /* receive data */
        usart_interrupt_flag_clear(HAL_MOTOR_UART, USART_INT_FLAG_RBNE);
        UART_Resceive_Int();
    }
    if(RESET != usart_interrupt_flag_get(HAL_MOTOR_UART, USART_INT_FLAG_TC))
    {
        /* transmit data */
        usart_interrupt_flag_clear(HAL_MOTOR_UART, USART_INT_FLAG_TC);
        UART_Transmission_Int();
    }
}
