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
    BSP_DMA_Init_UART();
    BSP_PWM_Init();
    BSP_TIM_Init();
    BSP_ISR_Init();
    BSP_USART_Init();
    BSP_SPI_Init();
    
    __enable_irq();
    
    lcd_init();
    
    for(;;)
    {
        System_10msTask_Flow();
        /* 从环形缓冲区取数据并回显 */
        int byte = ring_buffer_get();
        if (byte >= 0) {
            uint8_t rx_data = (uint8_t)byte;
            uart_send_data(&rx_data, 1);
        }
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
    /* 检查空闲中断标志 */
    if (usart_interrupt_flag_get(HAL_MOTOR_UART, USART_INT_FLAG_IDLE) != RESET)
    {
        /* 正确清除 GD32E230 的 IDLE 标志 */
        usart_interrupt_flag_clear(HAL_MOTOR_UART, USART_INT_FLAG_IDLE);
        
        UART_DMA_Rx_Int();
    }
    
//    if(RESET != usart_interrupt_flag_get(HAL_MOTOR_UART, USART_INT_FLAG_RBNE))
//    {
//        /* receive data */
//        usart_interrupt_flag_clear(HAL_MOTOR_UART, USART_INT_FLAG_RBNE);
//        UART_Resceive_Int();
//    }
//    if(RESET != usart_interrupt_flag_get(HAL_MOTOR_UART, USART_INT_FLAG_TC))
//    {
//        /* transmit data */
//        usart_interrupt_flag_clear(HAL_MOTOR_UART, USART_INT_FLAG_TC);
//        UART_Transmission_Int();
//    }
}
