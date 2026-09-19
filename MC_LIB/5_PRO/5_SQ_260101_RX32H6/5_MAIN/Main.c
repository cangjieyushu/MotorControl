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
    
    BSP_CLK_Init();
    BSP_GPIO_Init();
    BSP_ADC_Init();
    BSP_PWM_Init();
    BSP_OPA_Init();
    BSP_CMP_Init();
    BSP_TIM_Init();
    BSP_ISR_Init();
    BSP_USART_Init();
    
    __enable_irq();
    
    for(;;)
    {
        System_10msTask_Flow();
    }
}

void ADC_IRQHandler(void)
{
    if(ADC_Get_SR(HAL_MOTOR_ADC, ADC_SR_JEOC))
    {
        ADC_Clear_SR(HAL_MOTOR_ADC, ADC_SR_JEOC);
        MCSQ_Current_Flow(MOTOR_NUMBER_N0);
    }
}

void SysTick_Handler(void)
{
    System_1msTask_Flow();
    MCSQ_Speed_Flow(MOTOR_NUMBER_N0);
}

void TIM3_IRQHandler(void)
{
    if(TIM_Get_Flag(HAL_MOTOR_SWITCH_TIM, TIM_SR_CC1IF))
    {
        TIM_Clear_Flag(HAL_MOTOR_SWITCH_TIM, TIM_SR_CC1IF);
        MCSQ_Switch_Flow(MOTOR_NUMBER_N0);
    }
}

void TIM8_CC_IRQHandler(void)
{
    if(TIM_Get_Flag(HAL_MOTOR_PWM, TIM_SR_CC4IF))
    {
        TIM_Clear_Flag(HAL_MOTOR_PWM, TIM_SR_CC4IF);
        MCSQ_ADC_Trig_Flow(MOTOR_NUMBER_N0);
    }
}
