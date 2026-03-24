/**************************************************************************************************
*     File Name :                        MATH_RAMP_T.h
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             斜坡函数
**************************************************************************************************/

#ifndef MATH_RAMP_T_H
#define MATH_RAMP_T_H


#include "MATH.h"


typedef struct
{
    Q32I_ Q14I_Init;
    Q32I_ Q14I_Target;
    Q32I_ Q28I_ADDStep;
    Q32I_ Q28I_SUBStep;
    Q32I_ Q28I_Output_tmp;
    Q32I_ Q14I_Output;
}ST_RAMP_T;


/**********************************************************************************************
Function: Ramp_Init_T
Description: 定点斜坡初始化
Input: 定点斜坡输出初始值
Output: 无
Input_Output: 定点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Init_T(ST_RAMP_T* pRamp, Q32I_ init);

/**********************************************************************************************
Function: Ramp_Cal_T
Description: 定点斜坡计算
Input: 无
Output: 无
Input_Output: 定点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Cal_T(ST_RAMP_T* pRamp);


#endif /* MATH_RAMP_T_H */
