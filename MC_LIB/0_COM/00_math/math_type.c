/**
 * @file    math_type.c
 * @brief   数学运算库实现
 * @author  CJYS
 * @date    2024/1/1
 *
 * 实现浮点/定点平方根及软件延时。
 */

/* ======================== 1. Header ======================= */
#include "math_type.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  浮点数平方根（快速倒数开方迭代）
 * @param  A  输入值，需 > 0
 * @return A 的平方根
 */
float Math_Sqrt_F(float A)
{
    union
    {
        float f;
        Q32U_ i;
    } conv;
    float xhalf;

    if (A <= 0.0f)
    {
        return 0.0f;
    }

    conv.f = A;
    xhalf = 0.5f * conv.f;
    conv.i = 0x5f375a86U - (conv.i >> 1U);
    conv.f = conv.f * (1.5f - xhalf * conv.f * conv.f);

    return A * conv.f;
}

/**
 * @brief  定点整数平方根（牛顿迭代）
 * @param  A  输入值，需 > 0
 * @return A 的平方根（向下取整）
 */
Q32I_ Math_Sqrt_T(Q32I_ A)
{
    Q32U_ ua;
    Q32U_ bit;
    Q32U_ guess;
    Q32U_ quot;
    Q32U_ i;

    if (A <= 0)
    {
        return 0;
    }

    ua = (Q32U_)A;
    bit = 0U;
    while (ua != 0U)
    {
        ua = ua >> 1U;
        bit++;
    }

    guess = (Q32U_)1U << (bit >> 1U);

    for (i = 0U; i < 3U; i++)
    {
        quot = (Q32U_)A / guess;
        guess = (guess + quot) >> 1U;
    }

    return (Q32I_)guess;
}

/**
 * @brief  软件微秒级延时
 * @param  time  延时时间（微秒）
 */
void Math_Delay_us(Q32U_ time)
{
    Q32U_ i;
    Q32U_ j;

    for (i = 0U; i < time; i++)
    {
        for (j = 0U; j < 1U; j++)
        {
            /* 空循环，依赖编译器不优化 */
        }
    }
}

/**
 * @brief  软件毫秒级延时
 * @param  time  延时时间（毫秒）
 */
void Math_Delay_ms(Q32U_ time)
{
    Q32U_ i;

    for (i = 0U; i < time; i++)
    {
        Math_Delay_us(1000U);
    }
}
