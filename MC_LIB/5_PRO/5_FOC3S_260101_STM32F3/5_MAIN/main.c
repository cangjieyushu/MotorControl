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
void ADC1_2_IRQHandler(void)
{
    if (ADC_GetITStatus(ADC1, ADC_IT_JEOC) != RESET)
    {
        ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);
        MCFOC_Current_Flow(HW_MC_MOTOR_NUMBER_N0);
    }
}
#endif

void SysTick_Handler(void)
{
    Systask_1ms_Flow();
#if (SYS_CFG_MC_ENABLE != 0U)
    MCFOC_Speed_Flow(HW_MC_MOTOR_NUMBER_N0);
#endif
}

#if (SYS_CFG_UART_ENABLE != 0U)
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(HW_SYS_UART, USART_IT_IDLE) != RESET)
    {
        /* 清 IDLE 标志（先读 ISR 再读 RDR）*/
        (void)HW_SYS_UART->ISR;
        (void)HW_SYS_UART->RDR;

        /* 从 DMA 线性缓冲区搬到环形缓冲区 */
        UART_DMA_Rx_Int();
    }
}

void DMA1_Channel4_IRQHandler(void)
{
    if (DMA_GetITStatus(DMA1_IT_TC4) != RESET)
    {
        DMA_ClearITPendingBit(DMA1_IT_TC4);

        /* 关 TX DMA + 等 TC + 切回 RS485 接收方向（都在 HAL 里）*/
        UARTH_Tx_DMA_Stop();
        UARTH_Disable_Tx();

        g_uart_tx_busy = 0U;        /* ★ 关键：不清这一位，第二帧永远发不出去 */
    }
}

#endif

#if (SYS_CFG_LCD_ENABLE != 0U)
void DMA1_Channel2_IRQHandler(void)
{
    if (DMA_GetITStatus(DMA1_IT_TC2) != RESET)
    {
        DMA_ClearITPendingBit(DMA1_IT_TC2);
        lcd_dma_done = 1U;      /* 标记 DMA 空闲 */
    }
}
#endif
