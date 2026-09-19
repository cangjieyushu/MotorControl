/*
*     File Name :                        math_ramp_f
*     Library/Module Name :              math
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             斜坡函数
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "math_ramp_f.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
void Ramp_Init_F(ST_RAMP_F* pRamp, float init)
{
    pRamp->O_F_Output = init;
}

void Ramp_Cal_F(ST_RAMP_F* pRamp)
{    
    if(pRamp->P_F_Target > pRamp->O_F_Output) 
    { 
        if(pRamp->P_F_Target > pRamp->O_F_Output + pRamp->P_F_ADDStep) 
        {
            pRamp->O_F_Output += pRamp->P_F_ADDStep;
        }
        else 
        {
            pRamp->O_F_Output = pRamp->P_F_Target;
        }
    }
    else if(pRamp->P_F_Target < pRamp->O_F_Output) 
    { 
        if(pRamp->P_F_Target < pRamp->O_F_Output + pRamp->P_F_SUBStep) 
        {
            pRamp->O_F_Output += pRamp->P_F_SUBStep;
        }
        else 
        {
            pRamp->O_F_Output = pRamp->P_F_Target;
        }
    }
    else 
    {
        pRamp->O_F_Output = pRamp->P_F_Target;
    }
}
