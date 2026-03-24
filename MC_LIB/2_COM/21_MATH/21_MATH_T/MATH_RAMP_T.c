/**************************************************************************************************
*     File Name :                        MATH_RAMP_T.c
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             斜坡函数
**************************************************************************************************/

#include "MATH_RAMP_T.h"


/**********************************************************************************************
Function: Ramp_Init_T
Description: 定点斜坡初始化
Input: 定点斜坡输出初始值
Output: 无
Input_Output: 定点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Init_T(ST_RAMP_T* pRamp, Q32I_ init)
{
    pRamp->Q28I_Output_tmp = Q16I_LFT_14(init);
    pRamp->Q14I_Output = init;
}

/**********************************************************************************************
Function: Ramp_Cal_T
Description: 定点斜坡计算
Input: 无
Output: 无
Input_Output: 定点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Cal_T(ST_RAMP_T* pRamp)
{
    Q32I_ Q28I_Target_tmp = Q16I_LFT_14(pRamp->Q14I_Target);
    if(Q28I_Target_tmp > pRamp->Q28I_Output_tmp) 
    {
        if(Q28I_Target_tmp > pRamp->Q28I_Output_tmp + pRamp->Q28I_ADDStep) 
        {
            pRamp->Q28I_Output_tmp += pRamp->Q28I_ADDStep;
        }
        else 
        {
            pRamp->Q28I_Output_tmp = Q28I_Target_tmp;
        }
    }
    else if(Q28I_Target_tmp < pRamp->Q28I_Output_tmp) 
    { 
        if(Q28I_Target_tmp < pRamp->Q28I_Output_tmp + pRamp->Q28I_SUBStep) 
        {
            pRamp->Q28I_Output_tmp += pRamp->Q28I_SUBStep;
        }
        else 
        {
            pRamp->Q28I_Output_tmp = Q28I_Target_tmp;
        }
    }
    else 
    {
        pRamp->Q28I_Output_tmp = Q28I_Target_tmp;
    }
    
    pRamp->Q14I_Output = Q32I_RHT_14(pRamp->Q28I_Output_tmp);
}
