/**
 * @file    main.c
 * @brief   任务管理
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "main.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  程序入口
 */
int main(void)
{
    __disable_irq();                                    /* 关中断，临界区初始化 */

    Systask_Init_Flow();                                /* 基础外设初始化 */

    __enable_irq();                                     /* 开中断 */

    Systask_Init_Flow_Finish();                         /* 完成初始化（LCD 等需开中断后执行） */

    for (;;)
    {
        Systask_10ms_Flow();                            /* 10ms 时间片任务 */
    }
}

#if (HW_FUN_MC_ENABLE != 0U)
/**
 * @brief  ADC 更新中断：FOC 电流环
 */
void ADC_IRQHandler(void)
{
    if(ADC_Get_SR(HW_MC_ADC, ADC_SR_JEOC))
    {
        ADC_Clear_SR(HW_MC_ADC, ADC_SR_JEOC);
        MCSQ_Current_Flow(HW_FUN_MC_MOTOR_NUMBER_N0);
    }
}
#endif

/**
 * @brief  SysTick 中断：1ms 任务 + 速度环
 */
void SysTick_Handler(void)
{
    Systask_1ms_Flow();
#if (HW_FUN_MC_ENABLE != 0U)
    MCSQ_Speed_Flow(HW_FUN_MC_MOTOR_NUMBER_N0);
#endif
}

#if (HW_FUN_MC_ENABLE != 0U)
void TIM3_IRQHandler(void)
{
    if(TIM_Get_Flag(HW_MC_STIM, TIM_SR_CC1IF))
    {
        TIM_Clear_Flag(HW_MC_STIM, TIM_SR_CC1IF);
        MCSQ_Switch_Flow(HW_FUN_MC_MOTOR_NUMBER_N0);
    }
}
#endif

#if (HW_FUN_MC_ENABLE != 0U)
void TIM8_CC_IRQHandler(void)
{
    if(TIM_Get_Flag(HW_MC_PWM, TIM_SR_CC4IF))
    {
        TIM_Clear_Flag(HW_MC_PWM, TIM_SR_CC4IF);
        MCSQ_ADC_Trig_Flow(HW_FUN_MC_MOTOR_NUMBER_N0);
    }
}
#endif

