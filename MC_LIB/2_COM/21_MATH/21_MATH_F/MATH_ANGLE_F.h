/**************************************************************************************************
*     File Name :                        MATH_ANGLE_F.h
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             三角函数
**************************************************************************************************/

#ifndef MATH_ANGLE_F_H
#define MATH_ANGLE_F_H


#include "MATH.h"


typedef struct
{
    float F_Angle;
    float F_Cos;
    float F_Sin;
    float F_ReAngle;
}ST_TRIG_F;


/**********************************************************************************************
Function: Math_SinCos_F
Description: 浮点正余弦计算
Input: 角度，0到1
Output: 正弦，余弦
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Math_SinCos_F(ST_TRIG_F* pTIG);


#endif /* MATH_ANGLE_F_H */
