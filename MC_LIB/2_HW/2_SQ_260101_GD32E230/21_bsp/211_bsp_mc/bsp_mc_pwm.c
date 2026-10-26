/**
 * @file    bsp_mc_pwm.c
 * @brief   PWM 初始化
 *          - TIMER0 互补 PWM + 死区 + CH3 触发 ADC
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_mc_pwm.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */
static uint8_t BSP_MC_PWM_CalcDeadTimeReg_us(float dt_us);

/* ======================== 6. Functions ==================== */

/**
 * @brief  根据期望死区时间（us）计算 TIMER0 CHCTL0 死区编码
 * @param  dt_us  期望死区时间，单位：微秒（us），浮点数
 * @return 死区寄存器值，可直接赋给 timer_breakpara.deadtime
 *
 * @note   GD32E230：TIMER0 时钟 = 72MHz，
 *         CKD_DIV=4，tDTS = 4 / 72MHz，系数 = fTIMER0/4 = 18.0
 */
static uint8_t BSP_MC_PWM_CalcDeadTimeReg_us(float dt_us)
{
    uint32_t n;
    float    nf;

    if (dt_us <= 0.0f)
    {
        return 0U;
    }

    nf = dt_us * 18.0f;    /* 只需改这一处 */
    n  = (uint32_t)nf;
    if (nf > (float)n)
    {
        n++;
    }

    if (n <= 127U)
    {
        return (uint8_t)n;
    }
    else if (n <= 254U)
    {
        return (uint8_t)(0x80U | (uint8_t)((n + 1U) / 2U - 64U));
    }
    else if (n <= 504U)
    {
        return (uint8_t)(0xC0U | (uint8_t)((n + 7U) / 8U - 32U));
    }
    else if (n <= 1008U)
    {
        return (uint8_t)(0xE0U | (uint8_t)((n + 15U) / 16U - 32U));
    }
    else
    {
        return 0xFFU;
    }
}

/**
 * @brief  电机控制用 PWM 初始化（TIMER0 互补 PWM）
 */
void BSP_MC_PWM_Init(void)
{
    timer_oc_parameter_struct    timer_ocinitpara;
    timer_parameter_struct       timer_initpara;
    timer_break_parameter_struct timer_breakpara;

    /* ---- 1. TIMER0 复位 + 时基配置 ---- */
    timer_deinit(HW_MC_PWM);
    timer_struct_para_init(&timer_initpara);
    timer_initpara.prescaler         = (Q32U_)HW_PWM_PRESCALER - 1U;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = HW_PWM_INIT_VALUE - 1U;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV4;
    timer_initpara.repetitioncounter = 0;
    timer_init(HW_MC_PWM, &timer_initpara);

    /* ---- 2. CH0/1/2 互补 PWM 输出配置 ---- */
    timer_channel_output_struct_para_init(&timer_ocinitpara);
    timer_ocinitpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocinitpara.outputnstate = TIMER_CCXN_ENABLE;
    timer_ocinitpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocinitpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocinitpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocinitpara.ocnidlestate = TIMER_OC_IDLE_STATE_LOW;

    timer_channel_output_config(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL, &timer_ocinitpara);
    timer_channel_output_config(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL, &timer_ocinitpara);
    timer_channel_output_config(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL, &timer_ocinitpara);

    /* ---- 3. CH0/1/2 脉宽/模式/影子配置 ---- */
    timer_channel_output_pulse_value_config(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL, 0);
    timer_channel_output_mode_config(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL, TIMER_OC_SHADOW_ENABLE);

    timer_channel_output_pulse_value_config(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL, 0);
    timer_channel_output_mode_config(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL, TIMER_OC_SHADOW_ENABLE);

    timer_channel_output_pulse_value_config(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL, 0);
    timer_channel_output_mode_config(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL, TIMER_OC_SHADOW_ENABLE);

    /* ---- 4. CH3：内部触发 ADC（不输出到引脚） ---- */
    timer_channel_output_pulse_value_config(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL, 0);
    timer_channel_output_mode_config(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL, TIMER_OC_SHADOW_ENABLE);

    /* CH0~CH2 主/补输出在配置阶段先关闭，等主输出使能时统一打开 */
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN  | TIMER_CHCTL2_CH1EN  | TIMER_CHCTL2_CH2EN
                                       | TIMER_CHCTL2_CH0NEN | TIMER_CHCTL2_CH1NEN | TIMER_CHCTL2_CH2NEN));

    /* ---- 5. 死区 / 刹车 / 主输出配置 ---- */
    timer_break_struct_para_init(&timer_breakpara);
    timer_breakpara.runoffstate     = TIMER_ROS_STATE_ENABLE;
    timer_breakpara.ideloffstate    = TIMER_IOS_STATE_ENABLE;
    timer_breakpara.deadtime        = BSP_MC_PWM_CalcDeadTimeReg_us(HW_PWM_DEADTIME_TIME);
    timer_breakpara.breakpolarity   = TIMER_BREAK_POLARITY_LOW;
    timer_breakpara.outputautostate = TIMER_OUTAUTO_ENABLE;
    timer_breakpara.protectmode     = TIMER_CCHP_PROT_OFF;
    timer_breakpara.breakstate      = TIMER_BREAK_ENABLE;
    timer_break_config(HW_MC_PWM, &timer_breakpara);

    timer_primary_output_config(HW_MC_PWM, ENABLE);

    /* ---- 6. 清标志 ---- */
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_UP);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH0);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH1);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH2);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH3);
    timer_flag_clear(HW_MC_PWM, TIMER_INTF_BRKIF);

    /* ---- 7. 启动 TIMER0 ---- */
    timer_enable(HW_MC_PWM);

    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_UP);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH0);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH1);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH2);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH3);
    timer_flag_clear(HW_MC_PWM, TIMER_INTF_BRKIF);

    Math_Delay_us(1000U);

    timer_interrupt_flag_clear(HW_MC_PWM, TIMER_INT_FLAG_UP);
    timer_interrupt_flag_clear(HW_MC_PWM, TIMER_INT_FLAG_CH0);
    timer_interrupt_flag_clear(HW_MC_PWM, TIMER_INT_FLAG_CH1);
    timer_interrupt_flag_clear(HW_MC_PWM, TIMER_INT_FLAG_CH2);
    timer_interrupt_flag_clear(HW_MC_PWM, TIMER_INT_FLAG_CH3);
    timer_interrupt_flag_clear(HW_MC_PWM, TIMER_INTF_BRKIF);

    /* ---- 8. 中断使能 ---- */
    timer_interrupt_enable(HW_MC_PWM, TIMER_INT_CH3);   /* CH3 触发 ADC 中断 */
    /* timer_interrupt_enable(HW_MC_PWM, TIMER_INT_BRK); */   /* 刹车中断暂不使能 */
}
