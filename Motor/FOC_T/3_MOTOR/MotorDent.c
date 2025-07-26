/**************************************************************************************************
*     File Name :                        MotorDent.c
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             参数辨识源文件
**************************************************************************************************/
#include "MotorDent.h"

/**********************************************************************/

/**********************************静态参数辨识************************************/

/**********************************************************************************************
Function: Est_Para_Id_Init_T
Description: 静态参数辨识初始化
Input: 无
Output: 无
Input_Output: 静态参数辨识指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Para_Id_Init_T(ST_PARA_ID_T* pCTRL)
{
    pCTRL->_V_Q32U_State = 0U;
    pCTRL->_V_Q32U_cnt = 0U;
    
    Filter_Init_T(&pCTRL->FL_tmp1, 0);
    Filter_Init_T(&pCTRL->FL_tmp2, 0);
    pCTRL->TG_Triangle.Q12U_Angle = 0;
    pCTRL->TG_Triangle.Q14I_Cos = 16384;
    pCTRL->TG_Triangle.Q14I_Sin = 0;
    pCTRL->TG_Triangle.Q12U_ReAngle = 0;
    
    pCTRL->_V_Q14I_Udtmp1 = 0;
    pCTRL->_V_Q14I_Idtmp1 = 0;
    pCTRL->_V_Q14I_Udtmp2 = 0;
    pCTRL->_V_Q14I_Idtmp2 = 0;
            
    pCTRL->_V_Q14I_Istmp1 = 0;
    pCTRL->_V_Q14I_Istmp2 = 0;
    pCTRL->_V_Q32U_Ud_cnt = 0U;
    pCTRL->_V_Q32U_Ud_Count = pCTRL->_P_Q32U_PWM_Freq/pCTRL->_P_Q32U_Ud_Freq/2U;
    pCTRL->_V_Q14I_Ud_Sign = 1;
    pCTRL->_V_Q14I_Ialfa_LPF = 0;
    pCTRL->_V_Q14I_Ibeta_LPF = 0;
    pCTRL->_V_Q14I_Ialfa_HPF = 0;
    pCTRL->_V_Q14I_Ibeta_HPF = 0;
    pCTRL->_V_Q14I_Ialfa_Last = 0;
    pCTRL->_V_Q14I_Ibeta_Last = 0;
    pCTRL->_O_Q14I_Ialfa = 0;
    pCTRL->_O_Q14I_Ibeta = 0;
    pCTRL->_O_Q14I_Ud_HFI = 0;
    
    pCTRL->_V_Q28I_Yalfa_Hpf = 0;
    pCTRL->_V_Q28I_Ybeta_Hpf = 0;
    pCTRL->_V_Q28I_Yalfa_Last = 0;
    pCTRL->_V_Q28I_Ybeta_Last = 0;
    pCTRL->_V_Q28I_Xalfa_tmp = 0;
    pCTRL->_V_Q28I_Xbeta_tmp = 0;
}

/**********************************************************************************************
Function: Est_Para_Id_Srad_T
Description: 静态参数辨识计算
Input: 无
Output: 无
Input_Output: 静态参数辨识指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Para_Id_Srad_T(ST_PARA_ID_T* pCTRL)
{
    if(pCTRL->_V_Q32U_State == 0U)
    {
        pCTRL->_O_Q14I_IdRef = pCTRL->_P_Q14I_Id1;
        
        pCTRL->_V_Q32U_cnt++;
        if(pCTRL->_V_Q32U_cnt == pCTRL->_P_Q32U_Rs_Time)
        {
            pCTRL->_V_Q14I_Udtmp1 /= pCTRL->_P_Q32U_Rs_Time;
            pCTRL->_V_Q14I_Idtmp1 /= pCTRL->_P_Q32U_Rs_Time;
            Filter_Init_T(&pCTRL->FL_tmp1, 0);
            Filter_Init_T(&pCTRL->FL_tmp2, 0);
            pCTRL->_V_Q32U_State = 1U;
            pCTRL->_V_Q32U_cnt = 0U;
        }
        else
        {
            pCTRL->_V_Q14I_Udtmp1 += pCTRL->FL_tmp1.Q16I_Filter_out;
            pCTRL->_V_Q14I_Idtmp1 += pCTRL->FL_tmp2.Q16I_Filter_out;
        }
    }
    else if(pCTRL->_V_Q32U_State == 1U)
    {
        pCTRL->_O_Q14I_IdRef = pCTRL->_P_Q14I_Id2;
        
        pCTRL->_V_Q32U_cnt++;
        if(pCTRL->_V_Q32U_cnt == pCTRL->_P_Q32U_Rs_Time)
        {
            pCTRL->_V_Q14I_Udtmp2 /= pCTRL->_P_Q32U_Rs_Time;
            pCTRL->_V_Q14I_Idtmp2 /= pCTRL->_P_Q32U_Rs_Time;
            pCTRL->_P_Q14I_Rs = (Q16I_LFT_14(pCTRL->_V_Q14I_Udtmp2 - pCTRL->_V_Q14I_Udtmp1))/(pCTRL->_V_Q14I_Idtmp2 - pCTRL->_V_Q14I_Idtmp1);
            Filter_Init_T(&pCTRL->FL_tmp1, 0);
            Filter_Init_T(&pCTRL->FL_tmp2, 0);
            pCTRL->_V_Q32U_State = 2U;
            pCTRL->_V_Q32U_cnt = 0U;
        }
        else
        {
            pCTRL->_V_Q14I_Udtmp2 += pCTRL->FL_tmp1.Q16I_Filter_out;
            pCTRL->_V_Q14I_Idtmp2 += pCTRL->FL_tmp2.Q16I_Filter_out;
        }
    }
    else if(pCTRL->_V_Q32U_State == 2U)
    {
        pCTRL->_V_Q32U_cnt++;
        if(pCTRL->_V_Q32U_cnt == 1000U)
        {
            pCTRL->_V_Q32U_State = 3U;
            pCTRL->_V_Q32U_cnt = 0U;
        }
    }
    else if(pCTRL->_V_Q32U_State == 3U)
    {
        pCTRL->_V_Q32U_cnt++;
        if(pCTRL->_V_Q32U_cnt == pCTRL->_P_Q32U_Ls_Time)
        {
            pCTRL->_V_Q14I_Istmp1 /= pCTRL->_P_Q32U_Ls_Time;
            pCTRL->_P_Q24I_Ld = Q16I_LFT_10(Q16I_LFT_14(pCTRL->_P_Q14I_Ud_Ref)/(pCTRL->_P_Q32U_Ud_Freq*pCTRL->_V_Q14I_Istmp1))/4000;
            Filter_Init_T(&pCTRL->FL_tmp1, 0);
            pCTRL->_V_Q32U_State = 4U;
            pCTRL->_V_Q32U_cnt = 0U;
        }
        else
        {
            pCTRL->_V_Q14I_Istmp1 += pCTRL->FL_tmp1.Q16I_Filter_out;
        }
    }
    else if(pCTRL->_V_Q32U_State == 4U)
    {
        pCTRL->_O_Q14I_IdRef = pCTRL->_P_Q14I_Id1;
        
        pCTRL->_V_Q32U_cnt++;
        if(pCTRL->_V_Q32U_cnt == pCTRL->_P_Q32U_Ls_Time)
        {
            pCTRL->_V_Q14I_Istmp2 /= pCTRL->_P_Q32U_Ls_Time;
            pCTRL->_P_Q24I_Lq = Q16I_LFT_10(Q16I_LFT_14(pCTRL->_P_Q14I_Ud_Ref)/(pCTRL->_P_Q32U_Ud_Freq*pCTRL->_V_Q14I_Istmp2))/4000;
            Filter_Init_T(&pCTRL->FL_tmp1, 0);
            pCTRL->_V_Q32U_State = 5U;
            pCTRL->_V_Q32U_cnt = 0U;
        }
        else
        {
            pCTRL->_V_Q14I_Istmp2 += pCTRL->FL_tmp1.Q16I_Filter_out;
        }
    }
    else if(pCTRL->_V_Q32U_State == 5U)
    {
        pCTRL->_V_Q32U_cnt++;
        if(pCTRL->_V_Q32U_cnt == 1000U)
        {
            pCTRL->_V_Q32U_State = 6U;
            pCTRL->_V_Q32U_cnt = 0U;
        }
    }
    else if(pCTRL->_V_Q32U_State == 6U)
    {
        pCTRL->_V_Q32U_cnt++;
        if(pCTRL->_V_Q32U_cnt == pCTRL->_P_Q32U_Flux_Time)
        {
            pCTRL->_P_Q14I_Flux = pCTRL->FL_tmp1.Q16I_Filter_out;
            Filter_Init_T(&pCTRL->FL_tmp1, 0);
            pCTRL->_V_Q32U_State = 7U;
            pCTRL->_V_Q32U_cnt = 0U;
        }
    }
    else
    {
        
    }
}

/**********************************************************************************************
Function: Est_Para_Id_Current_T
Description: 静态参数辨识计算
Input: 无
Output: 无
Input_Output: 静态参数辨识指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Para_Id_Current_T(ST_PARA_ID_T* pCTRL)
{
    if((pCTRL->_V_Q32U_State == 0U) || (pCTRL->_V_Q32U_State == 1U))
    {
        pCTRL->FL_tmp1.Q16I_Filter_in = pCTRL->_I_Q14I_Ud;
        Filter_Cal_T(&pCTRL->FL_tmp1);
        pCTRL->FL_tmp2.Q16I_Filter_in = pCTRL->_I_Q14I_Id;
        Filter_Cal_T(&pCTRL->FL_tmp2);
    }
    else if((pCTRL->_V_Q32U_State == 3U) || (pCTRL->_V_Q32U_State == 4U))
    {
        pCTRL->_V_Q32U_Ud_cnt++;
        if(pCTRL->_V_Q32U_Ud_cnt == pCTRL->_V_Q32U_Ud_Count)
        {
            pCTRL->_V_Q32U_Ud_cnt = 0U;
            pCTRL->_V_Q14I_Ialfa_LPF = Q32I_RHT_01(pCTRL->_I_Q14I_Ialfa + pCTRL->_V_Q14I_Ialfa_Last);
            pCTRL->_V_Q14I_Ialfa_HPF = Q32I_RHT_01(pCTRL->_I_Q14I_Ialfa - pCTRL->_V_Q14I_Ialfa_Last)*pCTRL->_V_Q14I_Ud_Sign;
            pCTRL->_V_Q14I_Ibeta_LPF = Q32I_RHT_01(pCTRL->_I_Q14I_Ibeta + pCTRL->_V_Q14I_Ibeta_Last);
            pCTRL->_V_Q14I_Ibeta_HPF = Q32I_RHT_01(pCTRL->_I_Q14I_Ibeta - pCTRL->_V_Q14I_Ibeta_Last)*pCTRL->_V_Q14I_Ud_Sign;
            
            pCTRL->_V_Q14I_Ialfa_Last = pCTRL->_I_Q14I_Ialfa;
            pCTRL->_V_Q14I_Ibeta_Last = pCTRL->_I_Q14I_Ibeta;
            pCTRL->_O_Q14I_Ialfa = pCTRL->_V_Q14I_Ialfa_LPF;
            pCTRL->_O_Q14I_Ibeta = pCTRL->_V_Q14I_Ibeta_LPF;
            
            pCTRL->FL_tmp1.Q16I_Filter_in = (Q32I_)Math_Sqrt_F((float)(MATH_SQUARE_T(pCTRL->_V_Q14I_Ialfa_HPF)
                                          + MATH_SQUARE_T(pCTRL->_V_Q14I_Ibeta_HPF)));
            Filter_Cal_T(&pCTRL->FL_tmp1);
            
            if(pCTRL->_V_Q14I_Ud_Sign == 1)
            {
                pCTRL->_V_Q14I_Ud_Sign = -1;
            }
            else if(pCTRL->_V_Q14I_Ud_Sign == -1)
            {
                pCTRL->_V_Q14I_Ud_Sign = 1;
            }
        }
        
        pCTRL->_O_Q14I_Ud_HFI = pCTRL->_V_Q14I_Ud_Sign*pCTRL->_P_Q14I_Ud_Ref;
    }
    else if(pCTRL->_V_Q32U_State == 6U)
    {
        pCTRL->_V_Q28I_Yalfa_In = Q16I_LFT_14(pCTRL->_I_Q14I_Ualfa) - Q32I_RHT_14(pCTRL->_P_Q14I_Rs*pCTRL->_I_Q14I_Ialfa);
        pCTRL->_V_Q28I_Ybeta_In = Q16I_LFT_14(pCTRL->_I_Q14I_Ubeta) - Q32I_RHT_14(pCTRL->_P_Q14I_Rs*pCTRL->_I_Q14I_Ibeta);
        
        pCTRL->_V_Q28I_Yalfa_Hpf = (pCTRL->_V_Q28I_Yalfa_Hpf
                                 + pCTRL->_V_Q28I_Yalfa_In - pCTRL->_V_Q28I_Yalfa_Last)/256*pCTRL->_P_Q08I_Hpf_Coeff;
        pCTRL->_V_Q28I_Ybeta_Hpf = (pCTRL->_V_Q28I_Ybeta_Hpf
                                 + pCTRL->_V_Q28I_Ybeta_In - pCTRL->_V_Q28I_Ybeta_Last)/256*pCTRL->_P_Q08I_Hpf_Coeff;
        pCTRL->_V_Q28I_Yalfa_Last = pCTRL->_V_Q28I_Yalfa_In;
        pCTRL->_V_Q28I_Ybeta_Last = pCTRL->_V_Q28I_Ybeta_In;
        
        pCTRL->_V_Q28I_Xalfa_tmp += pCTRL->_P_Q14I_Ws*(pCTRL->_V_Q28I_Yalfa_Hpf/16384);
        pCTRL->_V_Q28I_Xbeta_tmp += pCTRL->_P_Q14I_Ws*(pCTRL->_V_Q28I_Ybeta_Hpf/16384);
    
        pCTRL->_V_Q28I_Xalfa_tmp = MATH_SAT_T(pCTRL->_V_Q28I_Xalfa_tmp, (Q32I_)Q28U_MAX, -(Q32I_)Q28U_MAX);
        pCTRL->_V_Q28I_Xbeta_tmp = MATH_SAT_T(pCTRL->_V_Q28I_Xbeta_tmp, (Q32I_)Q28U_MAX, -(Q32I_)Q28U_MAX);
    	
        pCTRL->_V_Q14I_Nalfa = Q32I_RHT_14(pCTRL->_V_Q28I_Xalfa_tmp - pCTRL->_P_Q14I_Ls*pCTRL->_I_Q14I_Ialfa);
        pCTRL->_V_Q14I_Nbeta = Q32I_RHT_14(pCTRL->_V_Q28I_Xbeta_tmp - pCTRL->_P_Q14I_Ls*pCTRL->_I_Q14I_Ibeta);
        
        pCTRL->FL_tmp1.Q16I_Filter_in = (Q32I_)Math_Sqrt_F((float)(MATH_SQUARE_T(pCTRL->_V_Q14I_Nalfa)
                                      + MATH_SQUARE_T(pCTRL->_V_Q14I_Nbeta)));
        Filter_Cal_T(&pCTRL->FL_tmp1);
    }
    else
    {
        
    }
}
