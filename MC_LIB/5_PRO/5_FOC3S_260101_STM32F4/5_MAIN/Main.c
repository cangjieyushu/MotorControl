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
    if(ADC_GetFlagStatus(ADC1, ADC_FLAG_JEOC))
    {
        ADC_ClearFlag(ADC1, ADC_FLAG_JEOC);
        MCFOC_Current_Flow(HW_MC_MOTOR_NUMBER_N0);     //168M,18us,72M,42us
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
