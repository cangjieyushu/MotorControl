/**************************************************************************************************
*     File Name :                        MATH_ANGLE_T.h
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             三角函数
**************************************************************************************************/

#ifndef MATH_ANGLE_T_H
#define MATH_ANGLE_T_H


#include "MATH.h"


typedef struct
{
    Q32I_ Q14U_Angle;
    Q32I_ Q14I_Cos;
    Q32I_ Q14I_Sin;
    Q32I_ Q14U_ReAngle;
}ST_TRIG_T;


/**********************************************************************************************
Function: Math_SinCos_T
Description: 定点正余弦计算
Input: 角度，0到16384
Output: 正弦，余弦
Input_Output: 定点角度指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Math_SinCos_T(ST_TRIG_T* pTIG);


#endif /* MATH_ANGLE_T_H */
