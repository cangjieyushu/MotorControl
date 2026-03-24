/**************************************************************************************************
*     File Name :                        MATH_RAMP_F.c
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             斜坡函数
**************************************************************************************************/

#include "MATH_RAMP_F.h"


/**********************************************************************************************
Function: Ramp_Init_F
Description: 浮点斜坡初始化
Input: 浮点斜坡输出初始值
Output: 无
Input_Output: 浮点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Init_F(ST_RAMP_F* pRamp, float init)
{
    pRamp->F_Output = init;
}

/**********************************************************************************************
Function: Ramp_Cal_F
Description: 浮点斜坡计算
Input: 无
Output: 无
Input_Output: 浮点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Cal_F(ST_RAMP_F* pRamp)
{    
    if(pRamp->F_Target > pRamp->F_Output) 
    { 
        if(pRamp->F_Target > pRamp->F_Output + pRamp->F_ADDStep) 
        {
            pRamp->F_Output += pRamp->F_ADDStep;
        }
        else 
        {
            pRamp->F_Output = pRamp->F_Target;
        }
    }
    else if(pRamp->F_Target < pRamp->F_Output) 
    { 
        if(pRamp->F_Target < pRamp->F_Output + pRamp->F_SUBStep) 
        {
            pRamp->F_Output += pRamp->F_SUBStep;
        }
        else 
        {
            pRamp->F_Output = pRamp->F_Target;
        }
    }
    else 
    {
        pRamp->F_Output = pRamp->F_Target;
    }
}
