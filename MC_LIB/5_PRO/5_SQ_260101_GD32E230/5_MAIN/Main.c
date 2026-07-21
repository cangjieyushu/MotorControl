/**************************************************************************************************
*     File Name :                        Main.c
*     Library/Module Name :              Main
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             任务管理
**************************************************************************************************/

#include "Main.h"
#include "SYS_LCD.h"


#if(JSCOPE_RTT_EN == 1U)
Q32I_ Buffer[128];
Q32I_ RTT_DATA[8];
#endif


/**********************************************************************************************
Function: main
Description: 主函数，执行初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
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
    BSP_DMA_Init_UART(UART_Ctrl.txdata, UART_Ctrl.rxdata, (Q08U_*)framebuffer);
    
#if(JSCOPE_RTT_EN == 1U)
    SEGGER_RTT_ConfigUpBuffer(1,JSCOPE_RTT_Sytle,Buffer,sizeof(Buffer),SEGGER_RTT_MODE_NO_BLOCK_SKIP);
#endif
    
    __enable_irq();
    
    for(;;)
    {
        System_10msTask_Tick(&Systask);
    }
}

/**********************************************************************************************
Function: ADC_IRQHandler
Description: 电流环中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void ADC_CMP_IRQHandler(void)
{
    if(adc_interrupt_flag_get(ADC_INT_FLAG_EOIC))
    {
        adc_interrupt_flag_clear(ADC_INT_FLAG_EOIC);
        MotorTask_Current_Flow(&Motor);
#if(JSCOPE_RTT_EN == 1U)
        RTT_DATA[0] = 100;
        RTT_DATA[1] = 100;
        RTT_DATA[2] = 100;
        SEGGER_RTT_Write(1,&RTT_DATA,12);
#endif
    }
}

/**********************************************************************************************
Function: TIM3_IRQHandler
Description: 换向中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void TIMER2_IRQHandler(void)
{
    if(timer_interrupt_flag_get(HAL_MOTOR_SWITCH_TIM, TIMER_INT_FLAG_CH0))
    {
        timer_interrupt_flag_clear(HAL_MOTOR_SWITCH_TIM, TIMER_INT_FLAG_CH0);
        MotorTask_Switch_Flow(&Motor);
    }
}

/**********************************************************************************************
Function: IRQHandleMCBKIsr
Description: 刹车故障中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void TIMER0_BRK_UP_TRG_COM_IRQHandler(void)
{
    if(timer_interrupt_flag_get(HAL_MOTOR_PWM, TIMER_INT_FLAG_BRK))
    {
        timer_interrupt_flag_clear(HAL_MOTOR_PWM, TIMER_INT_FLAG_BRK);
        MotorTask_Shut_Flow(&Motor);
    }
}

/**********************************************************************************************
Function: TIM8_CC_IRQHandler
Description: 首次硬件触发ADC中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void TIMER0_Channel_IRQHandler(void)
{
    if(timer_interrupt_flag_get(HAL_MOTOR_PWM, TIMER_INT_FLAG_CH3))
    {
        timer_interrupt_flag_clear(HAL_MOTOR_PWM, TIMER_INT_FLAG_CH3);
        MotorTask_PWM_Start_ADC_Flow(&Motor);
    }
}

/**********************************************************************************************
Function: SysTick_Handler
Description: 速度环中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void SysTick_Handler(void)
{
    System_Task_Flow(&Systask);
    MotorTask_Speed_Flow(&Motor);
    BSP_ADC_S_Enable(Hal_AdcLoopData_S);
}
