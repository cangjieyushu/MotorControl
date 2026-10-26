/**
 * @file    bsp_mc_tim.c
 * @brief   TIM 初始化
 *          - HALL 换向计时（TIMER13）+ 延迟换向计时（TIMER2）
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
    timer_parameter_struct timer_initpara;

    /* ---- 1. HALL 换向计时 TIMER13 ---- */
    timer_initpara.prescaler         = (Q32U_)HW_HTIM_PRESCALER - 1U;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = HW_HTIM_SET_VALUE;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0U;
    timer_init(HW_MC_HTIM, &timer_initpara);
    timer_enable(HW_MC_HTIM);

    /* ---- 2. 延迟换向计时 TIMER2 ---- */
    timer_initpara.prescaler         = (Q32U_)HW_STIM_PRESCALER - 1U;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = HW_STIM_SET_VALUE;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0U;
    timer_init(HW_MC_STIM, &timer_initpara);

    /* CH0 用于延迟换向比较中断（单脉冲模式） */
    timer_channel_output_pulse_value_config(HW_MC_STIM, TIMER_CH_0, 1);
    timer_channel_output_mode_config(HW_MC_STIM, TIMER_CH_0, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(HW_MC_STIM, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);

    timer_auto_reload_shadow_disable(HW_MC_STIM);

    /* ---- 3. 清标志，先关闭，等换向时由状态机启动 ---- */
    timer_interrupt_flag_clear(HW_MC_STIM, TIMER_INT_FLAG_UP);
    timer_interrupt_flag_clear(HW_MC_STIM, TIMER_INT_FLAG_CH0);
    timer_interrupt_flag_clear(HW_MC_STIM, TIMER_INT_FLAG_CH1);
    timer_interrupt_flag_clear(HW_MC_STIM, TIMER_INT_FLAG_CH2);
    timer_interrupt_flag_clear(HW_MC_STIM, TIMER_INT_FLAG_CH3);

    timer_disable(HW_MC_STIM);

    timer_interrupt_enable(HW_MC_STIM, TIMER_INT_CH0);
}
