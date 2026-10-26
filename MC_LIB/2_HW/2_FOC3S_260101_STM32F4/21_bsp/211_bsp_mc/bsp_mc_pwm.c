/**
 * @file    bsp_mc_pwm.c
 * @brief   PWM 初始化
 *          - 中心对齐互补 PWM，上桥"两边高中间低"，OC4REF 触发 ADC
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_mc_pwm.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  根据期望死区时间（us）计算 TIM8 BDTR 寄存器 DTG[7:0] 编码
 * @param  dt_us  期望死区时间，单位：微秒（us），浮点数
 * @return DTG[7:0] 寄存器值，可直接赋给 BDTR.TIM_DeadTime
 *
 * @note   TIM8 时钟 = 168MHz（PCLK2）、CKD_DIV=4，
 *         tDTS = 4 / 168MHz ≈ 23.8ns，系数 = fTIM8/4 = 42.0；
 *         编码向上取整，保证实际死区 ≥ 期望值；
 *         期望值超过最大范围（约 24us @ 168MHz）时返回 0xFF。
 */
static uint8_t BSP_MC_PWM_CalcDeadTimeReg_us(float dt_us)
{
    uint32_t n;    /* 死区时间 = n × tDTS，向上取整后的周期数 */
    float    nf;   /* 中间量：dt_us × 系数 */

    /* 非法输入：0 或负值 */
    if (dt_us <= 0.0f)
    {
        return 0U;
    }

    /* 计算所需 tDTS 周期数并向上取整，保证实际死区 ≥ 期望值 */
    nf = dt_us * 42.0f;
    n  = (uint32_t)nf;
    if (nf > (float)n)
    {
        n++;
    }

    /* 按 RM0316 Table 83 编码 DTG[7:0] */
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
 * @brief  电机控制用 PWM 初始化
 */
void BSP_MC_PWM_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef       TIM_OCInitStructure;
    TIM_BDTRInitTypeDef     HW_MC_PWM_BDTRInitStructure;

    /* ---------------- 1. 时基配置 ---------------- */
    TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV4;                      /* tDTS = 4/fTIM8 */
    TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_CenterAligned3;    /* 中心对称 */
    TIM_TimeBaseInitStructure.TIM_Prescaler         = (Q32U_)HW_PWM_PRESCALER - 1U;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 2U * (Q32U_)HW_CURRENT_LOOP_PRESCALER - 1U;
    TIM_TimeBaseInitStructure.TIM_Period            = (HW_PWM_SET_VALUE - 1U);
    TIM_TimeBaseInit(HW_MC_PWM, &TIM_TimeBaseInitStructure);

    /* ---------------- 2. OC1/2/3：三相互补 PWM ----------------
     * PWM1 模式 + OCPolarity_High  →  上桥"两边高中间低"
     *                                  下桥"两边低中间高"（中心时刻全导通）
     */
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse        = 0;
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

    TIM_OC1Init(HW_MC_PWM, &TIM_OCInitStructure);
    TIM_OC2Init(HW_MC_PWM, &TIM_OCInitStructure);
    TIM_OC3Init(HW_MC_PWM, &TIM_OCInitStructure);

    /* ---------------- 3. OC4：仅产生内部 OC4REF 作为 ADC 触发源 ----------------
     * 不输出到引脚（TIM_OutputState_Disable）
     * CCR4 决定采样点位置：CNT 上升段到达 CCR4 时产生 OC4REF 下降沿触发 ADC
     */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_Pulse       = HW_PWM_SET_VALUE - 2U - (Q32U_)MATH_ABS_T((Q32I_)HW_ADC_DELAY_VALUE - (Q32I_)HW_ADC_SAMPLE_VALUE);
    TIM_OC4Init(HW_MC_PWM, &TIM_OCInitStructure);

    /* OC4REF 作为 TRGO 触发 ADC */
    TIM_SelectOutputTrigger(HW_MC_PWM, TIM_TRGOSource_OC4Ref);

    /* ---------------- 4. BDTR：死区、刹车、主输出使能 ---------------- */
    HW_MC_PWM_BDTRInitStructure.TIM_OSSRState       = TIM_OSSRState_Enable;
    HW_MC_PWM_BDTRInitStructure.TIM_OSSIState       = TIM_OSSIState_Enable;
    HW_MC_PWM_BDTRInitStructure.TIM_LOCKLevel       = TIM_LOCKLevel_OFF;
    HW_MC_PWM_BDTRInitStructure.TIM_DeadTime        = BSP_MC_PWM_CalcDeadTimeReg_us(HW_PWM_DEADTIME_TIME);
    HW_MC_PWM_BDTRInitStructure.TIM_Break           = TIM_Break_Disable;    /* 过流时手动停车 */
    HW_MC_PWM_BDTRInitStructure.TIM_BreakPolarity   = TIM_BreakPolarity_High;
    HW_MC_PWM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
    TIM_BDTRConfig(HW_MC_PWM, &HW_MC_PWM_BDTRInitStructure);

    TIM_ClearITPendingBit(HW_MC_PWM, TIM_IT_Break);

    TIM_ITConfig(HW_MC_PWM, TIM_IT_Update, ENABLE);

    /* ---------------- 5. 使能 ARR 预装载 + 主输出 ---------------- */
    TIM_ARRPreloadConfig(HW_MC_PWM, ENABLE);
    TIM_CtrlPWMOutputs(HW_MC_PWM, DISABLE);

    /* ---------------- 6. 最后启动定时器 ---------------- */
    TIM_Cmd(HW_MC_PWM, ENABLE);
}
