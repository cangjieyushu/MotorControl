/**************************************************************************************************
*     File Name :                        MATH.c
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             数学运算库源文件
                                         注意：定点数学库中应用到了有符号数移位，暂不做处理。
**************************************************************************************************/

#include "MATH.h"


/**********************************************************************************************
Function: Math_Sqrt_T
Description: 定点平方根计算
Input: 正浮点数
Output: 平方根
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32I_ Math_Sqrt_T(Q32I_ A)
{
    if (A <= 0) return 0;
    Q32I_ guess = 0;
    
    // 初始猜测：x/2 + 1，保证对于 A >= 2 初始值大于 sqrt(A)
    if(A > 268435456)
    {
        guess = (A >> 14) + 1;
    }
    else if(A > 1048576)
    {
        guess = (A >> 10) + 1;
    }
    else if(A > 4096)
    {
        guess = (A >> 6) + 1;
    }
    else
    {
        guess = (A >> 1) + 1;
    }
    
    // 5次牛顿迭代
    for(Q32I_ i = 0; i < 5; i++) {
        Q32I_ quot = A / guess;      // 除零不会发生（A>0）
        guess = (guess + quot) >> 1;
    }
    
    return guess;
}

/**********************************************************************************************
Function: Math_Sqrt_F
Description: 浮点平方根计算
Input: 正浮点数
Output: 平方根
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
float Math_Sqrt_F(float A)
{
    if(A > 0.0f)
    {
        float xhalf = 0.5f * A;
        Q32I_ i = *(Q32I_*)&A;
        i = 0x1FBD1DF5 + (i >> 1U);
        A = *(float*)&i;
        A = 0.5f * A + xhalf / A;
    }
    else
    {
        A = 0.0f;
    }
    return A;
}

/**********************************************************************************************
Function: Math_Delay_us
Description: 延迟函数
Input: 延迟时间
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Math_Delay_us(Q32U_ time)
{
    for(Q32U_ i = 0U; i < time; i++)
    {
        for(Q32U_ j = 0U; j < 1U; j++)
        {
        }
    }
    
}

/**********************************************************************************************
Function: Math_Delay_ms
Description: 延迟函数
Input: 延迟时间
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Math_Delay_ms(Q32U_ time)
{
    for(Q32U_ i = 0U; i < time; i++)
    {
        Math_Delay_us(1000U);
    }
    
}
