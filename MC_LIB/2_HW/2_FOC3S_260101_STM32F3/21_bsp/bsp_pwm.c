/*
*     File Name :                        bsp_pwm
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             PWM初始化
*                                        中心对齐互补 PWM，上桥"两边高中间低"，OC4REF 触发 ADC
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_pwm.h"


/**
 * @brief  根据期望死区时间（us）计算 TIM8 BDTR 寄存器 DTG[7:0] 编码
 * @param  dt_us  期望死区时间，单位：微秒 (us)
 * @retval DTG[7:0] 寄存器值，可直接赋给 BDTR.TIM_DeadTime
 * @note   TIM8 时钟 = 72 MHz（PCLK2）、CKD_DIV=4，
 *         tDTS = 4 / 72 MHz ≈ 55.6 ns，系数 = 1/55.6ns ≈ 18
 *         若改用 RCC_TIM8CLK_PLLCLK（144 MHz），系数应改为 36
 */
static uint8_t BSP_PWM_CalcDeadTimeReg_us(uint32_t dt_us)
{
    uint32_t n;   /* 死区时间 = n × tDTS，向上取整 */

    if (dt_us == 0U)
    {
        return 0U;                 /* 死区为 0 */
    }

    /* ★ n = ceil(dt_us / tDTS) = ceil(dt_us * 18)，18 为 F303RB 72MHz 下的系数 */
    n = dt_us * 18U;

    if (n <= 127U)
    {
        /* DTG[7:5]=0xx : DT = n × tDTS */
        return (uint8_t)(n & 0x7FU);
    }
    else if (n <= 254U)
    {
        /* DTG[7:5]=10x : DT = (64 + x) × 2 × tDTS */
        uint32_t x = (n + 1U) / 2U - 64U;      /* ceil(n/2) - 64 */
        if (x > 63U) { x = 63U; }
        return (uint8_t)(0x80U | (uint8_t)(x & 0x3FU));
    }
    else if (n <= 504U)
    {
        /* DTG[7:5]=110 : DT = (32 + x) × 8 × tDTS */
        uint32_t x = (n + 7U) / 8U - 32U;      /* ceil(n/8) - 32 */
        if (x > 31U) { x = 31U; }
        return (uint8_t)(0xC0U | (uint8_t)(x & 0x1FU));
    }
    else if (n <= 1008U)
    {
        /* DTG[7:5]=111 : DT = (32 + x) × 16 × tDTS */
        uint32_t x = (n + 15U) / 16U - 32U;    /* ceil(n/16) - 32 */
        if (x > 31U) { x = 31U; }
        return (uint8_t)(0xE0U | (uint8_t)(x & 0x1FU));
    }
    else
    {
        /* 超出最大死区时间，返回最大编码 */
        return 0xFFU;
    }
}


/*-------------------------- 3. 公有接口实现 -----------------------------*/
void BSP_PWM_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef        TIM_OCInitStructure;
    TIM_BDTRInitTypeDef      HAL_MOTOR_PWM_BDTRInitStructure;

    /* ---------------- 1. 时基配置 ---------------- */
    TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV4;                      /* tDTS = 4/fTIM8 */
    TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_CenterAligned1;    /* 中心对称 */
    TIM_TimeBaseInitStructure.TIM_Prescaler         = (Q32U_)HAL_PWM_PRESCALER - 1U;     /* 预分频 */
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 1U * (Q32U_)HAL_CURRENT_LOOP_FREQ_PRESCALER;
    TIM_TimeBaseInitStructure.TIM_Period            = (HAL_PWM_SET_VALUE_T - 1U);        /* ARR */
    TIM_TimeBaseInit(HAL_MOTOR_PWM, &TIM_TimeBaseInitStructure);

    /* ---------------- 2. OC1/2/3：三相互补 PWM ----------------
     * ★ PWM1 模式 + OCPolarity_High  →  上桥"两边高中间低"
     *                                  下桥"两边低中间高"（中心时刻全导通）
     */
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;              /* ★ 从 PWM2 改为 PWM1 */
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse        = 0;
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

    TIM_OC1Init(HAL_MOTOR_PWM, &TIM_OCInitStructure);
    TIM_OC2Init(HAL_MOTOR_PWM, &TIM_OCInitStructure);
    TIM_OC3Init(HAL_MOTOR_PWM, &TIM_OCInitStructure);

    /* ---------------- 3. OC4：仅产生内部 OC4REF 作为 ADC 触发源 ----------------
     * 不输出到引脚（TIM_OutputState_Disable）
     * CCR4 决定采样点位置：CNT 上升段到达 CCR4 时产生 OC4REF 下降沿触发 ADC
     * 要"采样在中间附近"，CCR4 应接近 ARR
     */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;       /* ★ 不输出到 PC9 */
    TIM_OCInitStructure.TIM_Pulse       = HAL_PWM_SET_VALUE_T - HAL_ADC_DELAY_VALUE + HAL_ADC_SAMPLE_VALUE - 2U;
    /* ↑ 如果你的 hw_para.h 里 HAL_ADC_SAMPLE_VALUE 就是周期值，则保持原式：
     *   TIM_OCInitStructure.TIM_Pulse = (HAL_ADC_SAMPLE_VALUE - HAL_ADC_DELAY_VALUE)/2U + 1U;
     * 否则用上式，采样点更靠近波形中心。
     */
    TIM_OC4Init(HAL_MOTOR_PWM, &TIM_OCInitStructure);

    /* OC4REF 作为 TRGO 触发 ADC */
    TIM_SelectOutputTrigger(HAL_MOTOR_PWM, TIM_TRGOSource_OC4Ref);

    /* ---------------- 4. BDTR：死区、刹车、主输出使能 ---------------- */
    HAL_MOTOR_PWM_BDTRInitStructure.TIM_OSSRState       = TIM_OSSRState_Enable;
    HAL_MOTOR_PWM_BDTRInitStructure.TIM_OSSIState       = TIM_OSSIState_Enable;
    HAL_MOTOR_PWM_BDTRInitStructure.TIM_LOCKLevel       = TIM_LOCKLevel_OFF;
    HAL_MOTOR_PWM_BDTRInitStructure.TIM_DeadTime        = BSP_PWM_CalcDeadTimeReg_us(HAL_PWM_DEADTIME_TIME);
    HAL_MOTOR_PWM_BDTRInitStructure.TIM_Break           = TIM_Break_Disable;   /* 过流由 CMP→BKIN 硬件触发，此处不启用 */
    HAL_MOTOR_PWM_BDTRInitStructure.TIM_BreakPolarity   = TIM_BreakPolarity_High;
    HAL_MOTOR_PWM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
    TIM_BDTRConfig(HAL_MOTOR_PWM, &HAL_MOTOR_PWM_BDTRInitStructure);

    TIM_ClearITPendingBit(HAL_MOTOR_PWM, TIM_IT_Break);    /* 清中断标志位 */

    /* ---------------- 5. 使能 ARR 预装载 + 主输出 ---------------- */
    TIM_ARRPreloadConfig(HAL_MOTOR_PWM, ENABLE);
    TIM_CtrlPWMOutputs(HAL_MOTOR_PWM, ENABLE);

    /* ---------------- 6. 最后启动定时器 ---------------- */
    TIM_Cmd(HAL_MOTOR_PWM, ENABLE);
}
