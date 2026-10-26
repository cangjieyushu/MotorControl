/**
 * @file    bsp_mc_pwm.c
 * @brief   PWM 初始化
 *          - TIM8 中心对齐互补 PWM + 死区 + OC4REF 触发 ADC
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
 * @note   GD32E230：TIM8 时钟 = 72MHz，
 *         CKD_DIV=4，tDTS = 4 / 72MHz，系数 = fTIM8/4 = 18.0
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
 * @brief  电机控制用 PWM 初始化（TIM8 中心对齐互补 PWM）
 */
void BSP_MC_PWM_Init(void)
{

}
