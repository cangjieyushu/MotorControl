/**************************************************************************************************
*     File Name :                        MATH_RAMP_F.h
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             斜坡函数
**************************************************************************************************/

#ifndef MATH_RAMP_F_H
#define MATH_RAMP_F_H


#include "MATH.h"


typedef struct
{
    float F_Init;
    float F_Target;
    float F_ADDStep;
    float F_SUBStep;
    float F_Output;
}ST_RAMP_F;


/**********************************************************************************************
Function: Ramp_Init_F
Description: 浮点斜坡初始化
Input: 浮点斜坡输出初始值
Output: 无
Input_Output: 浮点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Init_F(ST_RAMP_F* pRamp, float init);

/**********************************************************************************************
Function: Ramp_Cal_F
Description: 浮点斜坡计算
Input: 无
Output: 无
Input_Output: 浮点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Cal_F(ST_RAMP_F* pRamp);


#endif /* MATH_RAMP_F_H */
