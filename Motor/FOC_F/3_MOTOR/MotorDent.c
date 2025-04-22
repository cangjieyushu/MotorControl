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
Function: Est_Para_Id_Init_F
Description: 静态参数辨识初始化
Input: 无
Output: 无
Input_Output: 静态参数辨识指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Para_Id_Init_F(ST_PARA_ID_F* pCTRL)
{
    pCTRL->_V_Q32U_State = 0U;
    pCTRL->_V_Q32U_cnt = 0U;
    
    Filter_Init_F(&pCTRL->FL_tmp1, 0.0f);
    Filter_Init_F(&pCTRL->FL_tmp2, 0.0f);
    pCTRL->TG_Triangle.F_Angle = 0.0f;
    pCTRL->TG_Triangle.F_Cos = 1.0f;
    pCTRL->TG_Triangle.F_Sin = 0.0f;
    pCTRL->TG_Triangle.F_ReAngle = 0.0f;
    
    pCTRL->_V_F_Udtmp1 = 0.0f;
    pCTRL->_V_F_Idtmp1 = 0.0f;
    pCTRL->_V_F_Udtmp2 = 0.0f;
    pCTRL->_V_F_Idtmp2 = 0.0f;
            
    pCTRL->_V_F_Istmp1 = 0.0f;
    pCTRL->_V_F_Istmp2 = 0.0f;
    pCTRL->_V_Q32U_Ud_cnt = 0U;
    pCTRL->_V_Q32U_Ud_Count = pCTRL->_P_Q32U_PWM_Freq/pCTRL->_P_Q32U_Ud_Freq/2U;
    pCTRL->_V_F_Ud_Sign = 1.0f;
    pCTRL->_V_F_Ialfa_LPF = 0.0f;
    pCTRL->_V_F_Ibeta_LPF = 0.0f;
    pCTRL->_V_F_Ialfa_HPF = 0.0f;
    pCTRL->_V_F_Ibeta_HPF = 0.0f;
    pCTRL->_V_F_Ialfa_Last = 0.0f;
    pCTRL->_V_F_Ibeta_Last = 0.0f;
    pCTRL->_O_F_Ialfa = 0.0f;
    pCTRL->_O_F_Ibeta = 0.0f;
    pCTRL->_O_F_Ud_HFI = 0.0f;
    
    pCTRL->_V_F_Yalfa_Hpf = 0.0f;
    pCTRL->_V_F_Ybeta_Hpf = 0.0f;
    pCTRL->_V_F_Yalfa_Last = 0.0f;
    pCTRL->_V_F_Ybeta_Last = 0.0f;
    pCTRL->_V_F_Xalfa = 0.0f;
    pCTRL->_V_F_Xbeta = 0.0f;
}

/**********************************************************************************************
Function: Est_Para_Id_Srad_F
Description: 静态参数辨识计算
Input: 无
Output: 无
Input_Output: 静态参数辨识指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Para_Id_Srad_F(ST_PARA_ID_F* pCTRL)
{
    if(pCTRL->_V_Q32U_State == 0U)
    {
        pCTRL->_O_F_IdRef = pCTRL->_P_F_Id1;
        
        pCTRL->_V_Q32U_cnt++;
        if(pCTRL->_V_Q32U_cnt == pCTRL->_P_Q32U_Rs_Time)
        {
            pCTRL->_V_F_Udtmp1 /= pCTRL->_P_Q32U_Rs_Time;
            pCTRL->_V_F_Idtmp1 /= pCTRL->_P_Q32U_Rs_Time;
            Filter_Init_F(&pCTRL->FL_tmp1, 0.0f);
            Filter_Init_F(&pCTRL->FL_tmp2, 0.0f);
            pCTRL->_V_Q32U_State = 1U;
            pCTRL->_V_Q32U_cnt = 0U;
        }
        else
        {
            pCTRL->_V_F_Udtmp1 += pCTRL->FL_tmp1.F_Filter_out;
            pCTRL->_V_F_Idtmp1 += pCTRL->FL_tmp2.F_Filter_out;
        }
    }
    else if(pCTRL->_V_Q32U_State == 1U)
    {
        pCTRL->_O_F_IdRef = pCTRL->_P_F_Id2;
        
        pCTRL->_V_Q32U_cnt++;
        if(pCTRL->_V_Q32U_cnt == pCTRL->_P_Q32U_Rs_Time)
        {
            pCTRL->_V_F_Udtmp2 /= pCTRL->_P_Q32U_Rs_Time;
            pCTRL->_V_F_Idtmp2 /= pCTRL->_P_Q32U_Rs_Time;
            pCTRL->_P_F_Rs = (pCTRL->_V_F_Udtmp2 - pCTRL->_V_F_Udtmp1)/(pCTRL->_V_F_Idtmp2 - pCTRL->_V_F_Idtmp1);
            Filter_Init_F(&pCTRL->FL_tmp1, 0.0f);
            Filter_Init_F(&pCTRL->FL_tmp2, 0.0f);
            pCTRL->_V_Q32U_State = 2U;
            pCTRL->_V_Q32U_cnt = 0U;
        }
        else
        {
            pCTRL->_V_F_Udtmp2 += pCTRL->FL_tmp1.F_Filter_out;
            pCTRL->_V_F_Idtmp2 += pCTRL->FL_tmp2.F_Filter_out;
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
            pCTRL->_V_F_Istmp1 /= pCTRL->_P_Q32U_Ls_Time;
            pCTRL->_P_F_Ld = pCTRL->_P_F_Ud_Ref/(((float)pCTRL->_P_Q32U_Ud_Freq)*4000.0f*pCTRL->_V_F_Istmp1);
            Filter_Init_F(&pCTRL->FL_tmp1, 0.0f);
            pCTRL->_V_Q32U_State = 4U;
            pCTRL->_V_Q32U_cnt = 0U;
        }
        else
        {
            pCTRL->_V_F_Istmp1 += pCTRL->FL_tmp1.F_Filter_out;
        }
    }
    else if(pCTRL->_V_Q32U_State == 4U)
    {
        pCTRL->_O_F_IdRef = pCTRL->_P_F_Id1;
        
        pCTRL->_V_Q32U_cnt++;
        if(pCTRL->_V_Q32U_cnt == pCTRL->_P_Q32U_Ls_Time)
        {
            pCTRL->_V_F_Istmp2 /= pCTRL->_P_Q32U_Ls_Time;
            pCTRL->_P_F_Lq = pCTRL->_P_F_Ud_Ref/(((float)pCTRL->_P_Q32U_Ud_Freq)*4000.0f*pCTRL->_V_F_Istmp2);
            Filter_Init_F(&pCTRL->FL_tmp1, 0.0f);
            pCTRL->_V_Q32U_State = 5U;
            pCTRL->_V_Q32U_cnt = 0U;
        }
        else
        {
            pCTRL->_V_F_Istmp2 += pCTRL->FL_tmp1.F_Filter_out;
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
            pCTRL->_P_F_Flux = pCTRL->FL_tmp1.F_Filter_out;
            Filter_Init_F(&pCTRL->FL_tmp1, 0.0f);
            pCTRL->_V_Q32U_State = 7U;
            pCTRL->_V_Q32U_cnt = 0U;
        }
    }
    else
    {
        
    }
}

/**********************************************************************************************
Function: Est_Para_Id_Current_F
Description: 静态参数辨识计算
Input: 无
Output: 无
Input_Output: 静态参数辨识指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Para_Id_Current_F(ST_PARA_ID_F* pCTRL)
{
    if((pCTRL->_V_Q32U_State == 0U) || (pCTRL->_V_Q32U_State == 1U))
    {
        pCTRL->FL_tmp1.F_Filter_in = pCTRL->_I_F_Ud;
        Filter_Cal_F(&pCTRL->FL_tmp1);
        pCTRL->FL_tmp2.F_Filter_in = pCTRL->_I_F_Id;
        Filter_Cal_F(&pCTRL->FL_tmp2);
    }
    else if((pCTRL->_V_Q32U_State == 3U) || (pCTRL->_V_Q32U_State == 4U))
    {
        pCTRL->_V_Q32U_Ud_cnt++;
        if(pCTRL->_V_Q32U_Ud_cnt == pCTRL->_V_Q32U_Ud_Count)
        {
            pCTRL->_V_Q32U_Ud_cnt = 0U;
            pCTRL->_V_F_Ialfa_LPF = 0.5f*(pCTRL->_I_F_Ialfa + pCTRL->_V_F_Ialfa_Last);
            pCTRL->_V_F_Ialfa_HPF = 0.5f*(pCTRL->_I_F_Ialfa - pCTRL->_V_F_Ialfa_Last)*pCTRL->_V_F_Ud_Sign;
            pCTRL->_V_F_Ibeta_LPF = 0.5f*(pCTRL->_I_F_Ibeta + pCTRL->_V_F_Ibeta_Last);
            pCTRL->_V_F_Ibeta_HPF = 0.5f*(pCTRL->_I_F_Ibeta - pCTRL->_V_F_Ibeta_Last)*pCTRL->_V_F_Ud_Sign;
            
            pCTRL->_V_F_Ialfa_Last = pCTRL->_I_F_Ialfa;
            pCTRL->_V_F_Ibeta_Last = pCTRL->_I_F_Ibeta;
            pCTRL->_O_F_Ialfa = pCTRL->_V_F_Ialfa_LPF;
            pCTRL->_O_F_Ibeta = pCTRL->_V_F_Ibeta_LPF;
            
            pCTRL->FL_tmp1.F_Filter_in = Math_Sqrt_F(MATH_SQUARE_F(pCTRL->_V_F_Ialfa_HPF) + MATH_SQUARE_F(pCTRL->_V_F_Ibeta_HPF));
            Filter_Cal_F(&pCTRL->FL_tmp1);
            
            if(pCTRL->_V_F_Ud_Sign == 1.0f)
            {
                pCTRL->_V_F_Ud_Sign = -1.0f;
            }
            else if(pCTRL->_V_F_Ud_Sign == -1.0f)
            {
                pCTRL->_V_F_Ud_Sign = 1.0f;
            }
        }
        
        pCTRL->_O_F_Ud_HFI = pCTRL->_V_F_Ud_Sign*pCTRL->_P_F_Ud_Ref;
    }
    else if(pCTRL->_V_Q32U_State == 6U)
    {
        pCTRL->_V_F_Yalfa_In = -pCTRL->_P_F_Rs*pCTRL->_I_F_Ialfa + pCTRL->_I_F_Ualfa;
        pCTRL->_V_F_Ybeta_In = -pCTRL->_P_F_Rs*pCTRL->_I_F_Ibeta + pCTRL->_I_F_Ubeta;
        
        pCTRL->_V_F_Yalfa_Hpf = pCTRL->_P_F_Hpf_Coeff*(pCTRL->_V_F_Yalfa_Hpf + pCTRL->_V_F_Yalfa_In - pCTRL->_V_F_Yalfa_Last);
        pCTRL->_V_F_Ybeta_Hpf = pCTRL->_P_F_Hpf_Coeff*(pCTRL->_V_F_Ybeta_Hpf + pCTRL->_V_F_Ybeta_In - pCTRL->_V_F_Ybeta_Last);
        pCTRL->_V_F_Yalfa_Last = pCTRL->_V_F_Yalfa_In;
        pCTRL->_V_F_Ybeta_Last = pCTRL->_V_F_Ybeta_In;
        
        pCTRL->_V_F_Xalfa += pCTRL->_P_F_Ws*pCTRL->_V_F_Yalfa_Hpf;
        pCTRL->_V_F_Xbeta += pCTRL->_P_F_Ws*pCTRL->_V_F_Ybeta_Hpf;
    
        pCTRL->_V_F_Nalfa = pCTRL->_V_F_Xalfa - pCTRL->_P_F_Ls*pCTRL->_I_F_Ialfa;
        pCTRL->_V_F_Nbeta = pCTRL->_V_F_Xbeta - pCTRL->_P_F_Ls*pCTRL->_I_F_Ibeta;
        
        pCTRL->FL_tmp1.F_Filter_in = Math_Sqrt_F(MATH_SQUARE_F(pCTRL->_V_F_Nalfa) + MATH_SQUARE_F(pCTRL->_V_F_Nbeta));
        Filter_Cal_F(&pCTRL->FL_tmp1);
    }
    else
    {
        
    }
}
