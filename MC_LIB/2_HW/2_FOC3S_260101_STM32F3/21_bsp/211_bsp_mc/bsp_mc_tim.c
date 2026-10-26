/**
 * @file    bsp_mc_tim.c
 * @brief   TIM 初始化
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_mc_tim.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  TIM2 HALL 计时初始化
 */
void BSP_MC_TIM_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Prescaler         = (Q32U_)HW_HTIM_PRESCALER - 1U;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInitStructure.TIM_Period            = HW_HTIM_SET_VALUE;
    TIM_TimeBaseInit(HW_MC_HTIM, &TIM_TimeBaseInitStructure);

    /* 计数器清零，从 0 开始计时 */
    TIM_SetCounter(HW_MC_HTIM, 0);

    TIM_Cmd(HW_MC_HTIM, ENABLE);
}
