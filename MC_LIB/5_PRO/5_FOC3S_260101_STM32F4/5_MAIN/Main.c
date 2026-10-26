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
 * @brief  TIM8 更新中断：FOC 电流环
 */
__attribute__CCMRAM
void TIM1_UP_TIM10_IRQHandler(void)
{
    if (TIM_GetITStatus(HW_MC_PWM, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(HW_MC_PWM, TIM_IT_Update);
        MCFOC_Current_Flow(HW_FUN_MC_MOTOR_NUMBER_N0);     //168M,18us,72M,42us
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
    MCFOC_Speed_Flow(HW_FUN_MC_MOTOR_NUMBER_N0);
#endif
}
