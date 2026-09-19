/*
*     File Name :                        math_type
*     Library/Module Name :              math
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             数学运算库
*/

/*-------------------------- 1. 对应头文件--------------------------------*/
#include "math_type.h"

/*-------------------------- 2. 变量 ---------------------------------*/

/*-------------------------- 3. 公有接口实现 -----------------------------*/
float Math_Sqrt_F(float A)
{
    if (A <= 0.0f) return 0.0f;

    union{float f;Q32U_ i;}conv;
    conv.f = A;

    float xhalf = 0.5f * conv.f;
    conv.i = 0x5f375a86 - (conv.i >> 1U);
    conv.f = conv.f * (1.5f - xhalf * conv.f * conv.f);

    return A * conv.f;
}

Q32I_ Math_Sqrt_T(Q32I_ A)
{
    if (A <= 0) return 0;

    Q32U_ ua = (Q32U_)A;
    Q32U_ bit = 0U;
    while (ua != 0U) {
        ua = ua>>1U;
        bit++;
    }

    Q32U_ guess = (Q32U_)1U << (bit >> 1U);

    for (Q32U_ i = 0U; i < 3U; i++) {
        Q32U_ quot = A / guess;
        guess = (guess + quot) >> 1U;
    }

    return (Q32I_)guess;
}

void Math_Delay_us(Q32U_ time)
{
    for(Q32U_ i = 0U; i < time; i++)
    {
        for(Q32U_ j = 0U; j < 1U; j++)
        {
        }
    }
    
}

void Math_Delay_ms(Q32U_ time)
{
    for(Q32U_ i = 0U; i < time; i++)
    {
        Math_Delay_us(1000U);
    }
    
}
