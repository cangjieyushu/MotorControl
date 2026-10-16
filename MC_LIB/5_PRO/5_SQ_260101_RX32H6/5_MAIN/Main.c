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
void ADC_IRQHandler(void)
{
    if(ADC_Get_SR(HW_MC_ADC, ADC_SR_JEOC))
    {
        ADC_Clear_SR(HW_MC_ADC, ADC_SR_JEOC);
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
void TIM3_IRQHandler(void)
{
    if(TIM_Get_Flag(HW_MC_STIM, TIM_SR_CC1IF))
    {
        TIM_Clear_Flag(HW_MC_STIM, TIM_SR_CC1IF);
        MCSQ_Switch_Flow(HW_MC_MOTOR_NUMBER_N0);
    }
}
#endif

#if (SYS_CFG_MC_ENABLE != 0U)
void TIM8_CC_IRQHandler(void)
{
    if(TIM_Get_Flag(HW_MC_PWM, TIM_SR_CC4IF))
    {
        TIM_Clear_Flag(HW_MC_PWM, TIM_SR_CC4IF);
        MCSQ_ADC_Trig_Flow(HW_MC_MOTOR_NUMBER_N0);
    }
}
#endif

