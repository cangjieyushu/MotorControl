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
void ADC_CMP_IRQHandler(void)
{
    if(adc_interrupt_flag_get(ADC_INT_FLAG_EOIC))
    {
        adc_interrupt_flag_clear(ADC_INT_FLAG_EOIC);
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
void TIMER2_IRQHandler(void)
{
    if(timer_interrupt_flag_get(HW_MC_STIM, TIMER_INT_FLAG_CH0))
    {
        timer_interrupt_flag_clear(HW_MC_STIM, TIMER_INT_FLAG_CH0);
        MCSQ_Switch_Flow(HW_FUN_MC_MOTOR_NUMBER_N0);
    }
}
#endif

#if (HW_FUN_MC_ENABLE != 0U)
void TIMER0_Channel_IRQHandler(void)
{
    if(timer_interrupt_flag_get(HW_MC_PWM, TIMER_INT_FLAG_CH3))
    {
        timer_interrupt_flag_clear(HW_MC_PWM, TIMER_INT_FLAG_CH3);
        MCSQ_ADC_Trig_Flow(HW_FUN_MC_MOTOR_NUMBER_N0);
    }
}
#endif

