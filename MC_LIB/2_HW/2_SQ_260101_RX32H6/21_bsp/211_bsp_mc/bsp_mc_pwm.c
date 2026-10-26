/**
 * @file    bsp_mc_pwm.c
 * @brief   PWM 初始化
 *          - TIM8 互补 PWM + 死区 + CH4 触发 ADC
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
 * @brief  根据期望死区时间（us）计算 TIM8 BDTR 寄存器 DTG[7:0] 编码
 * @param  dt_us  期望死区时间，单位：微秒（us），浮点数
 * @return DTG[7:0] 寄存器值，可直接赋给 BDTR.TIM_DeadTime
 *
 * @note   RX32H6xx：TIM8 时钟 = 144MHz，系数 = fTIM8/4 = 36.0；
 *         若时钟改用 288MHz，系数改为 72.0；
 *         编码向上取整，保证实际死区 ≥ 期望值；
 *         期望值超过最大范围（约 28us @ 144MHz）时返回 0xFF。
 */
static uint8_t BSP_MC_PWM_CalcDeadTimeReg_us(float dt_us)
{
    uint32_t n;
    float    nf;

    if (dt_us <= 0.0f)
    {
        return 0U;
    }

    nf = dt_us * 36.0f;    /* 只需改这一处 */
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
 * @brief  电机控制用 PWM 初始化（TIM8 互补 PWM）
 */
void BSP_MC_PWM_Init(void)
{
    /* ---- 1. 时基配置 ---- */
    TIM_Set_CounterMode(HW_MC_PWM, TIM_COUNTERMODE_UP);
    TIM_Set_Prescaler(HW_MC_PWM, ((uint32_t)HW_PWM_PRESCALER) - 1U);
    TIM_Set_AutoReload(HW_MC_PWM, (HW_PWM_INIT_VALUE - 1U));
    TIM_Set_RepetitionCounter(HW_MC_PWM, 0U);

    /* ---- 2. CH1 / CH1N ---- */
    TIM_Set_OC_Mode(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL, TIM_OCMODE_PWM1);
    TIM_Set_OC_Polarity(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL, TIM_OCPOLARITY_HIGH);
    TIM_Set_OC_Polarity(HW_MC_PWM, HW_MC_PWM_UL_CHANNEL, TIM_OCPOLARITY_HIGH);

    /* ---- 3. CH2 / CH2N ---- */
    TIM_Set_OC_Mode(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL, TIM_OCMODE_PWM1);
    TIM_Set_OC_Polarity(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL, TIM_OCPOLARITY_HIGH);
    TIM_Set_OC_Polarity(HW_MC_PWM, HW_MC_PWM_VL_CHANNEL, TIM_OCPOLARITY_HIGH);

    /* ---- 4. CH3 / CH3N ---- */
    TIM_Set_OC_Mode(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL, TIM_OCMODE_PWM1);
    TIM_Set_OC_Polarity(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL, TIM_OCPOLARITY_HIGH);
    TIM_Set_OC_Polarity(HW_MC_PWM, HW_MC_PWM_WL_CHANNEL, TIM_OCPOLARITY_HIGH);

    TIM_Set_OC_CompareCH1(HW_MC_PWM, 0U);
    TIM_Set_OC_CompareCH2(HW_MC_PWM, 0U);
    TIM_Set_OC_CompareCH3(HW_MC_PWM, 0U);

    /* ---- 5. CH4：内部触发 ADC ---- */
    TIM_Set_OC_Mode(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL, TIM_OCMODE_PWM1);
    TIM_Set_OC_Polarity(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL, TIM_OCPOLARITY_HIGH);
    TIM_Set_OC_CompareCH4(HW_MC_PWM, HW_ADC_DELAY_VALUE);

    /* ---- 6. 预装载使能 ---- */
    TIM_Enable_OC_Preload(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL);
    TIM_Enable_OC_Preload(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL);
    TIM_Enable_OC_Preload(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL);
    TIM_Enable_OC_Preload(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL);

    /* ---- 7. 死区 ---- */
    TIM_Set_ClockDivision(HW_MC_PWM, TIM_CLOCKDIVISION_DIV1);
    TIM_Set_OC_DeadTime(HW_MC_PWM, BSP_MC_PWM_CalcDeadTimeReg_us(HW_PWM_DEADTIME_TIME));

    /* ---- 8. 刹车配置：CMP1 输出经 BKCMP1E 触发 BRK ---- */
    TIM_Config_BRK(HW_MC_PWM, TIM_BREAK_POLARITY_HIGH, TIM_BREAK_FILTER_FDIV4_N8, TIM_BREAK_AFMODE_INPUT);
    TIM_Disable_BreakInputSource(HW_MC_PWM, TIM_BREAK_INPUT_BKIN, TIM_AF_BKINE);              /* BKINE=0 */
    TIM_Set_BreakInputSourcePolarity(HW_MC_PWM, TIM_BREAK_INPUT_BKIN, TIM_AF_BKCMP1P,
                                     TIM_BKCMP_POLARITY_NoInvert);                            /* BKCMPxP=0 */
    TIM_Enable_BreakInputSource(HW_MC_PWM, TIM_BREAK_INPUT_BKIN, TIM_AF_BKCMP1E);             /* BKCMPxE=1 */

    /* ---- 9. 各通道受刹车控制 + AOE 关闭 ---- */
    TIM_Enable_Break_Control(HW_MC_PWM);
    TIM_Set_CH1Break_Invalid(HW_MC_PWM);
    TIM_Set_CH2Break_Invalid(HW_MC_PWM);
    TIM_Set_CH3Break_Invalid(HW_MC_PWM);
    TIM_Disable_AOE(HW_MC_PWM);

    /* ---- 10. 使能 CH4 输出 + 中断 ---- */
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL);

    /* TIM_Enable_IT(HW_MC_PWM, TIM_DIER_BIE); */   /* 刹车中断暂不使能 */
    TIM_Enable_IT(HW_MC_PWM, TIM_DIER_CC4IE);

    /* ---- 11. 主输出使能 + 启动计数器 ---- */
    TIM_Enable_MOE(HW_MC_PWM);
    TIM_Enable_CEN(HW_MC_PWM);
}
