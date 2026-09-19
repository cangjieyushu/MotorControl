/*
*     File Name :                        math_ramp_t
*     Library/Module Name :              math
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             斜坡函数
*/

/*-------------------------- 1. 对应头文件--------------------------------*/
#include "math_ramp_t.h"

/*-------------------------- 2. 变量 ---------------------------------*/

/*-------------------------- 3. 公有接口实现 -----------------------------*/
void Ramp_Init_T(ST_RAMP_T* pRamp, Q32I_ init)
{
    pRamp->O_Q14I_Output = init;
    pRamp->V_Q28I_Output_tmp = Q16I_LFT_14(init);
}

void Ramp_Cal_T(ST_RAMP_T* pRamp)
{
    Q32I_ Q28I_Target_tmp = Q16I_LFT_14(pRamp->P_Q14I_Target);
    if(Q28I_Target_tmp > pRamp->V_Q28I_Output_tmp) 
    {
        if(Q28I_Target_tmp > pRamp->V_Q28I_Output_tmp + pRamp->P_Q28I_ADDStep) 
        {
            pRamp->V_Q28I_Output_tmp += pRamp->P_Q28I_ADDStep;
        }
        else 
        {
            pRamp->V_Q28I_Output_tmp = Q28I_Target_tmp;
        }
    }
    else if(Q28I_Target_tmp < pRamp->V_Q28I_Output_tmp) 
    { 
        if(Q28I_Target_tmp < pRamp->V_Q28I_Output_tmp + pRamp->P_Q28I_SUBStep) 
        {
            pRamp->V_Q28I_Output_tmp += pRamp->P_Q28I_SUBStep;
        }
        else 
        {
            pRamp->V_Q28I_Output_tmp = Q28I_Target_tmp;
        }
    }
    else 
    {
        pRamp->V_Q28I_Output_tmp = Q28I_Target_tmp;
    }
    
    pRamp->O_Q14I_Output = Q32I_RHT_14(pRamp->V_Q28I_Output_tmp);
}
