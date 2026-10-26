/**
 * @file    bsp_mc_tim.c
 * @brief   TIM 初始化
 *          - HALL 换向计时（TIM2）+ 延迟换向计时（TIM3）
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
 * @brief  HALL 换向时间计数器 + 延迟换向计数器初始化
 */
void BSP_MC_TIM_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};

    /* ---- 1. HALL 换向计时（TIM2） ---- */
    TIM_TimeBaseInitStruct.CounterMode       = TIM_COUNTERMODE_UP;
    TIM_TimeBaseInitStruct.RepetitionCounter = 0U;
    TIM_TimeBaseInitStruct.Period            = HW_HTIM_SET_VALUE;
    TIM_TimeBaseInitStruct.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    TIM_TimeBaseInitStruct.Prescaler         = (uint16_t)(HW_HTIM_PRESCALER) - 1U;
    TIM_TimeBaseInit(HW_MC_HTIM, &TIM_TimeBaseInitStruct);
    TIM_Enable_CEN(HW_MC_HTIM);

    /* ---- 2. 延迟换向计时（TIM3） ---- */
    TIM_TimeBaseInitStruct.CounterMode       = TIM_COUNTERMODE_UP;
    TIM_TimeBaseInitStruct.RepetitionCounter = 0U;
    TIM_TimeBaseInitStruct.Period            = HW_STIM_SET_VALUE;
    TIM_TimeBaseInitStruct.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    TIM_TimeBaseInitStruct.Prescaler         = (uint16_t)(HW_STIM_PRESCALER) - 1U;
    TIM_TimeBaseInit(HW_MC_STIM, &TIM_TimeBaseInitStruct);

    /* 关闭 CH1 预装载，由 HM_SWITCH_TIM_Delay() 动态设置比较值 */
    TIM_Disable_OC_Preload(HW_MC_STIM, TIM_CHANNEL_CH1);

    /* 使能 CH1 比较中断（延迟换向触发） */
    TIM_Enable_IT(HW_MC_STIM, TIM_DIER_CC1IE);
}
