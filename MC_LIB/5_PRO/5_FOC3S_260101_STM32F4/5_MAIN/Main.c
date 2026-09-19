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
    
    BSP_CLK_Init();        // 系统时钟、外设时钟、SysTick
    BSP_ISR_Init();        // 配置各中断优先级（不要再次分组）
    BSP_GPIO_Init();       // GPIO
    BSP_TIM_Init();        // TIM2 自由计数
    BSP_PWM_Init();        // TIM1 PWM + 触发 ADC
    BSP_ADC_Init();        // ADC 规则/注入通道
    BSP_DMA_Init();        // 若使用 DMA，配置并关联 ADC
    BSP_UART_Init();       // UART（如需要）
    
    __enable_irq();
    
    for(;;)
    {
        System_10msTask_Flow();
    }
}

void ADC_IRQHandler(void)
{
    if(ADC_GetFlagStatus(ADC1, ADC_FLAG_JEOC))
    {
        ADC_ClearFlag(ADC1, ADC_FLAG_JEOC);
        MCFOC_Current_Flow(MOTOR_NUMBER_N0);
    }
}

void SysTick_Handler(void)
{
    System_1msTask_Flow();
    MCFOC_Speed_Flow(MOTOR_NUMBER_N0);
}
