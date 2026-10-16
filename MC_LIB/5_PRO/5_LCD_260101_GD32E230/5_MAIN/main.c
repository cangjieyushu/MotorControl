/*
*     File Name :                        main
*     Library/Module Name :              main
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             任务管理
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "main.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
int main(void)
{
    __disable_irq();

    Systask_Init_Flow();

    __enable_irq();
    
    Systask_Init_Flow_Finish();
    
    for (;;)
    {
        Systask_10ms_Flow();
    }
}

#if (SYS_CFG_MC_ENABLE != 0U)
void ADC_CMP_IRQHandler(void)
{
    if(adc_interrupt_flag_get(ADC_INT_FLAG_EOIC))
    {
        adc_interrupt_flag_clear(ADC_INT_FLAG_EOIC);
        MCSQ_Current_Flow(HW_MC_MOTOR_NUMBER_N0);
    }
}
#endif

void SysTick_Handler(void)
{
    Systask_1ms_Flow();
#if (SYS_CFG_MC_ENABLE != 0U)
    MCSQ_Speed_Flow(HW_MC_MOTOR_NUMBER_N0);
#endif
}

#if (SYS_CFG_MC_ENABLE != 0U)
void TIMER2_IRQHandler(void)
{
    if(timer_interrupt_flag_get(HW_MC_STIM, TIMER_INT_FLAG_CH0))
    {
        timer_interrupt_flag_clear(HW_MC_STIM, TIMER_INT_FLAG_CH0);
        MCSQ_Switch_Flow(HW_MC_MOTOR_NUMBER_N0);
    }
}
#endif

#if (SYS_CFG_MC_ENABLE != 0U)
void TIMER0_Channel_IRQHandler(void)
{
    if(timer_interrupt_flag_get(HW_MC_PWM, TIMER_INT_FLAG_CH3))
    {
        timer_interrupt_flag_clear(HW_MC_PWM, TIMER_INT_FLAG_CH3);
        MCSQ_ADC_Trig_Flow(HW_MC_MOTOR_NUMBER_N0);
    }
}
#endif

#if (SYS_CFG_UART_ENABLE != 0U)
void USART0_IRQHandler(void)
{
    if (usart_interrupt_flag_get(HW_SYS_UART, USART_INT_FLAG_IDLE) != RESET)
    {
        usart_interrupt_flag_clear(HW_SYS_UART, USART_INT_FLAG_IDLE);

        UART_DMA_Rx_Int();
    }
}
void DMA_Channel3_4_IRQHandler(void)
{
    if (dma_interrupt_flag_get(HAL_SYS_USART_TX_DMA_CH, DMA_INT_FLAG_FTF) != RESET)
    {
        dma_interrupt_flag_clear(HAL_SYS_USART_TX_DMA_CH, DMA_INT_FLAG_FTF);
        
        while (usart_flag_get(HW_SYS_UART, USART_FLAG_TC) == RESET)
        {
        }

        UARTH_Disable_Tx();             /* 关发送 + RS485 切回接收 */
        g_uart_tx_busy = 0U;
    }
}
#endif

#if (SYS_CFG_LCD_ENABLE != 0U)
void DMA_Channel1_2_IRQHandler(void)
{
    if (SET == dma_interrupt_flag_get(HAL_LCD_SPI_TX_DMA_CH, DMA_INT_FLAG_FTF))
    {
        dma_interrupt_flag_clear(HAL_LCD_SPI_TX_DMA_CH, DMA_INT_FLAG_FTF);
        lcd_dma_done = 1U;
    }
}
#endif
