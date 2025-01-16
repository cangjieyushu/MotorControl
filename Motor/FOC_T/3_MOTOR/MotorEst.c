/**************************************************************************************************
*     File Name :                        MotorEst.c
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             速度角度观测器源文件
**************************************************************************************************/
#include "MotorEst.h"

/**********************************************************************/

//void Est_HFI_Init(ST_HFI_CONTROL* pCTRL)
//{
//    pCTRL->ElecFreqHz = 0.0f;
//    pCTRL->ElecFreqHz_Filter = 0.0f;
//    pCTRL->AngleRad = 0.0f;
//    pCTRL->AngleSpeed = 0.0f;
//    pCTRL->Id_LPF = 0.0f;
//    pCTRL->Iq_LPF = 0.0f;
//    pCTRL->Id_HPF = 0.0f;
//    pCTRL->Iq_HPF = 0.0f;
//    pCTRL->AngleRad_HFI = 0.0f;  
//    pCTRL->AngleRad_ERROR = 0.0f;    
//    pCTRL->Ud_HFI = 0.0f;     
//    pCTRL->cnt = 0U;
//    PID_POS_Init(&pCTRL->Pll_Pid, 0.0f);
//}

//void Est_HFI(ST_HFI_CONTROL* pCTRL)
//{
//    /* Clarke transform */   
//    Clarke_Transform(pFoc);
//    
//    pCTRL->cnt++;
//    if(pCTRL->cnt == 5U)
//    {
//        pCTRL->cnt = 0U;
//        pCTRL->Id_LPF = 0.5f*(pFoc->Ialpha + pCTRL->Id_Last);
//        pCTRL->Id_HPF = 0.5f*(pFoc->Ialpha - pCTRL->Id_Last)*pCTRL->SIGN;
//        pCTRL->Iq_LPF = 0.5f*(pFoc->Ibeta + pCTRL->Iq_Last);
//        pCTRL->Iq_HPF = 0.5f*(pFoc->Ibeta - pCTRL->Iq_Last)*pCTRL->SIGN;
//        
//        pCTRL->Id_Last = pFoc->Ialpha;
//        pCTRL->Iq_Last = pFoc->Ibeta;
//        pFoc->Ialpha = pCTRL->Id_LPF;
//        pFoc->Ibeta = pCTRL->Iq_LPF;
//        
//        pCTRL->Pll_Pid.Ref = pFoc->CosValue*pCTRL->Iq_HPF;
//        pCTRL->Pll_Pid.Fdb = pFoc->SinValue*pCTRL->Id_HPF;
//        PID_POS_Cal(&pCTRL->Pll_Pid);
//        
//        pCTRL->AngleSpeed = pCTRL->Pll_Pid.Output;
//        pCTRL->ElecFreqHz = ZXMATH_ONE_OVER_2PI*pCTRL->AngleSpeed;
//        pCTRL->ElecFreqHz_Filter = 0.001f*(USER_PLL_SPEED_LPF_COEFF*pCTRL->ElecFreqHz + (1000.0f-USER_PLL_SPEED_LPF_COEFF)*pCTRL->ElecFreqHz_Filter);
//        
//        pCTRL->AngleRad += 10.0f*pCTRL->Ts*pCTRL->AngleSpeed;
//        while(pCTRL->AngleRad > MATH_2PI_F)
//        {
//            pCTRL->AngleRad -= MATH_2PI_F;
//        }
//        while(pCTRL->AngleRad < 0.0f)
//        {
//            pCTRL->AngleRad += MATH_2PI_F;
//        }
//        
//        if(pCTRL->cnt_1 == 0U)
//        {
//            pCTRL->cnt_1 = 1U;
//            pCTRL->SIGN = 1.0f;
//        }
//        else if(pCTRL->cnt_1 == 1U)
//        {
//            pCTRL->cnt_1 = 0U;
//            pCTRL->SIGN = -1.0f;
//        }
//        pCTRL->Ud_HFI = pCTRL->SIGN*pCTRL->Ud_Ref;
//    }
//    
//    pFoc->AngleRad = pCTRL->AngleRad;
//    /* Park transform */
//    pFoc->SinValue = ZxMath_SinF32(pFoc->AngleRad);
//    pFoc->CosValue = ZxMath_CosF32(pFoc->AngleRad);
//    Park_Transform(pFoc);
//    
//    pFoc->VsMax = pFoc->RealVdc * pFoc->VsMaxScale;
//    /* Id PID */
//    pFoc->PidId.OutMax = pCTRL->Udq_Coeff*pFoc->VsMax;
//    pFoc->PidId.OutMin = -pCTRL->Udq_Coeff*pFoc->VsMax;
//    pFoc->PidId.Ref = pFoc->IdRef;
//    pFoc->PidId.Fdb = pFoc->Id;
//    PID_POS_Cal(&pFoc->PidId);
//    /* Iq PID */
//    pFoc->PidIq.OutMax = pCTRL->Udq_Coeff*pFoc->VsMax;
//    pFoc->PidIq.OutMin = -pCTRL->Udq_Coeff*pFoc->VsMax;
//    pFoc->PidIq.Ref = pFoc->IqRef;
//    pFoc->PidIq.Fdb = pFoc->Iq;
//    PID_POS_Cal(&pFoc->PidIq);
//    
//    pFoc->Ud = pFoc->PidId.Output + pCTRL->Ud_HFI;
//    pFoc->Uq = pFoc->PidIq.Output;
//    /* IPark transform */	
//    Ipark_Transform(pFoc);
//    /* SVGEN */
//    SVPWM_Cal(pFoc);
//}

/**********************************磁链观测器************************************/

/**********************************************************************************************
Function: Est_Flux_Init_T
Description: 磁链观测器初始化
Input: 无
Output: 无
Input_Output: 磁链观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Flux_Init_T(ST_FLUX_CONTROL_T* pCTRL)
{
    PID_Pos_Init_T(&pCTRL->PID_PLL, 0.0f);
    Filter_Init_T(&pCTRL->FL_SRAD, 0.0f);
    pCTRL->TG_Triangle.Q12U_Angle = 0.0f;
    
    pCTRL->_V_Q14I_Xalfa = 0.0f;
    pCTRL->_V_Q14I_Xbeta = 0.0f;
}

/**********************************************************************************************
Function: Est_Flux_T
Description: 磁链观测器计算
Input: 无
Output: 无
Input_Output: 磁链观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Flux_T(ST_FLUX_CONTROL_T* pCTRL)
{
    if(pCTRL->Est_State_Flag == 0U)
    {
        pCTRL->_V_F_R_set = pCTRL->_P_F_Rs_Coeff*pCTRL->_P_F_Rs;
        pCTRL->_V_F_Nn2_L = pCTRL->_P_F_Flux2;
    }
    else
    {
        pCTRL->_V_F_R_set = pCTRL->_P_F_Rs;
    }
	
    pCTRL->_V_Q14I_Yalfa = -Q32I_RHT_14(pCTRL->_P_Q14I_Rs*pCTRL->_I_Q14I_Ialfa) + pCTRL->_I_Q14I_Ualfa;
    pCTRL->_V_Q14I_Ybeta = -Q32I_RHT_14(pCTRL->_P_Q14I_Rs*pCTRL->_I_Q14I_Ibeta) + pCTRL->_I_Q14I_Ubeta;
    
    pCTRL->_V_F_Yalfa_HF = 0.999f*(pCTRL->_V_F_Yalfa_HF + pCTRL->_V_F_Yalfa - pCTRL->_V_F_Yalfa_L);
    pCTRL->_V_F_Ybeta_HF = 0.999f*(pCTRL->_V_F_Ybeta_HF + pCTRL->_V_F_Ybeta - pCTRL->_V_F_Ybeta_L);
        
    pCTRL->_V_F_Yalfa_L = pCTRL->_V_F_Yalfa;
    pCTRL->_V_F_Ybeta_L = pCTRL->_V_F_Ybeta; 
            
    pCTRL->_V_F_Xalfa_F += pCTRL->_P_F_Ts*pCTRL->_V_F_Yalfa_HF;
    pCTRL->_V_F_Xbeta_F += pCTRL->_P_F_Ts*pCTRL->_V_F_Ybeta_HF;
    
    pCTRL->_V_F_Nnalfa_F = pCTRL->_V_F_Xalfa_F - pCTRL->_P_F_Ls*pCTRL->_I_F_Ialfa;
    pCTRL->_V_F_Nnbeta_F = pCTRL->_V_F_Xbeta_F - pCTRL->_P_F_Ls*pCTRL->_I_F_Ibeta;
    pCTRL->_V_F_Nn2_F = MATH_SQUARE_F(pCTRL->_V_F_Nnalfa_F) + MATH_SQUARE_F(pCTRL->_V_F_Nnbeta_F);
    pCTRL->_V_F_Nn2_L = 0.95f*pCTRL->_V_F_Nn2_L + 0.05f*pCTRL->_V_F_Nn2_F;
	
    pCTRL->_V_Q14I_Nalfa = pCTRL->_V_Q14I_Xalfa - Q32I_RHT_14(pCTRL->_P_Q14I_Ls*pCTRL->_I_Q14I_Ialfa);
    pCTRL->_V_Q14I_Nbeta = pCTRL->_V_Q14I_Xbeta - Q32I_RHT_14(pCTRL->_P_Q14I_Ls*pCTRL->_I_Q14I_Ibeta);
    pCTRL->_V_Q14I_Nn2 = Q32I_RHT_14(MATH_SQUARE_F(pCTRL->_V_Q14I_Nalfa))
                       + Q32I_RHT_14(MATH_SQUARE_F(pCTRL->_V_Q14I_Nbeta))
                       - Q32I_RHT_14(MATH_SQUARE_F(Q32I_RHT_14(pCTRL->_P_Q14I_Ld*pCTRL->_I_Q14I_IdRef)));
    
    pCTRL->_V_Q14I_Ealfa = Q32I_RHT_14(pCTRL->_P_Q14I_Gamma*Q32I_RHT_14(pCTRL->_V_Q14I_Nalfa*(pCTRL->_P_Q14I_Flux2 - pCTRL->_V_Q14I_Nn2)));
    pCTRL->_V_Q14I_Ebeta = Q32I_RHT_14(pCTRL->_P_Q14I_Gamma*Q32I_RHT_14(pCTRL->_V_Q14I_Nbeta*(pCTRL->_P_Q14I_Flux2 - pCTRL->_V_Q14I_Nn2)));
    
    pCTRL->_V_Q14I_Xalfa += Q32I_RHT_14(pCTRL->_P_Q14I_Ts*(pCTRL->_V_Q14I_Yalfa + pCTRL->_V_Q14I_Ealfa));
    pCTRL->_V_Q14I_Xbeta += Q32I_RHT_14(pCTRL->_P_Q14I_Ts*(pCTRL->_V_Q14I_Ybeta + pCTRL->_V_Q14I_Ebeta));
        
    pCTRL->_V_Q14I_Nalfa = pCTRL->_V_Q14I_Xalfa - Q32I_RHT_14(pCTRL->_P_Q14I_Ls*pCTRL->_I_Q14I_Ialfa);
    pCTRL->_V_Q14I_Nbeta = pCTRL->_V_Q14I_Xbeta - Q32I_RHT_14(pCTRL->_P_Q14I_Ls*pCTRL->_I_Q14I_Ibeta);
        
    pCTRL->PID_PLL.Q14I_Rf = Q32I_RHT_14(pCTRL->_V_Q14I_Nbeta*pCTRL->TG_Triangle.Q14I_Cos);
    pCTRL->PID_PLL.Q14I_Fb = Q32I_RHT_14(pCTRL->_V_Q14I_Nalfa*pCTRL->TG_Triangle.Q14I_Sin);
    PID_Pos_Cal_T(&pCTRL->PID_PLL);
    
    pCTRL->FL_SRAD.Q16I_Filter_in = pCTRL->PID_PLL.Q14I_Output;
    Filter_Cal_T(&pCTRL->FL_SRAD);
    
    pCTRL->TG_Triangle.Q12U_Angle += Q32I_RHT_14(pCTRL->_P_Q14I_Ts*pCTRL->FL_SRAD.Q16I_Filter_in);
    MATH_ANGLE_MOD_T(pCTRL->TG_Triangle.Q12U_Angle);
    
    Math_SinCos_T(&pCTRL->TG_Triangle);
}

/**********************************滑模观测器************************************/

/**********************************************************************************************
Function: Est_SMO_Init_T
Description: 滑模观测器初始化
Input: 无
Output: 无
Input_Output: 滑模观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_SMO_Init_T(ST_SMO_CONTROL_T* pCTRL)
{
    PID_Pos_Init_T(&pCTRL->PID_PLL, 0.0f);
    Filter_Init_T(&pCTRL->FL_SRAD, 0.0f);
    pCTRL->TG_Triangle.Q12U_Angle = 0.0f;
    
    pCTRL->_V_Q14I_Aalfa = 0.0f;
    pCTRL->_V_Q14I_Abeta = 0.0f;
    pCTRL->_V_Q14I_Ealfa = 0.0f;
    pCTRL->_V_Q14I_Ebeta = 0.0f;
}

/**********************************************************************************************
Function: Est_SMO_T
Description: 滑模观测器计算
Input: 无
Output: 无
Input_Output: 滑模观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_SMO_T(ST_SMO_CONTROL_T* pCTRL)
{
    pCTRL->_V_Q14I_Aalfa += Q32I_RHT_14(pCTRL->_P_Q14I_Ts*(
                          - Q32I_RHT_14(pCTRL->_P_Q14I_Rs_Over_Ld*pCTRL->_V_Q14I_Aalfa)
                          - Q32I_RHT_14(pCTRL->FL_SRAD.Q16I_Filter_in*pCTRL->_P_Q14I_Ld_Lq_Over_Ld*pCTRL->_V_Q14I_Abeta)
                          + Q32I_RHT_14(pCTRL->_P_Q14I_One_Over_Ld*pCTRL->_I_Q14I_Ualfa)
                          - Q32I_RHT_14(pCTRL->_P_Q14I_One_Over_Ld*pCTRL->_V_Q14I_Ealfa)));
    pCTRL->_V_Q14I_Abeta += Q32I_RHT_14(pCTRL->_P_Q14I_Ts*(
                          - Q32I_RHT_14(pCTRL->_P_Q14I_Rs_Over_Ld*pCTRL->_V_Q14I_Abeta)
                          + Q32I_RHT_14(pCTRL->FL_SRAD.Q16I_Filter_in*pCTRL->_P_Q14I_Ld_Lq_Over_Ld*pCTRL->_V_Q14I_Aalfa)
                          + Q32I_RHT_14(pCTRL->_P_Q14I_One_Over_Ld*pCTRL->_I_Q14I_Ubeta)
                          - Q32I_RHT_14(pCTRL->_P_Q14I_One_Over_Ld*pCTRL->_V_Q14I_Ebeta)));
    
    pCTRL->_V_Q14I_ERRalfa = pCTRL->_V_Q14I_Aalfa - pCTRL->_I_Q14I_Ialfa;
    pCTRL->_V_Q14I_ERRbeta = pCTRL->_V_Q14I_Abeta - pCTRL->_I_Q14I_Ibeta;
    
    pCTRL->_V_Q14I_Ealfa = MATH_SAT_F(pCTRL->_V_Q14I_ERRalfa, pCTRL->_P_Q14I_K1, -pCTRL->_P_Q14I_K1);
    pCTRL->_V_Q14I_Ebeta = MATH_SAT_F(pCTRL->_V_Q14I_ERRbeta, pCTRL->_P_Q14I_K1, -pCTRL->_P_Q14I_K1);
    
    pCTRL->_V_Q14I_Ealfa += Q32I_RHT_14(pCTRL->_P_Q14I_K2*pCTRL->_V_Q14I_ERRalfa);
    pCTRL->_V_Q14I_Ebeta += Q32I_RHT_14(pCTRL->_P_Q14I_K2*pCTRL->_V_Q14I_ERRbeta);
        
    pCTRL->PID_PLL.Q14I_Rf = -Q32I_RHT_14(pCTRL->_V_Q14I_Ealfa*pCTRL->TG_Triangle.Q14I_Cos);
    pCTRL->PID_PLL.Q14I_Fb =  Q32I_RHT_14(pCTRL->_V_Q14I_Ebeta*pCTRL->TG_Triangle.Q14I_Sin);
    PID_Pos_Cal_T(&pCTRL->PID_PLL);
    
    pCTRL->FL_SRAD.Q16I_Filter_in = pCTRL->PID_PLL.Q14I_Output;
    Filter_Cal_T(&pCTRL->FL_SRAD);
    
    pCTRL->TG_Triangle.Q12U_Angle += Q32I_RHT_14(pCTRL->_P_Q14I_Ts*pCTRL->FL_SRAD.Q16I_Filter_in);
    MATH_ANGLE_MOD_T(pCTRL->TG_Triangle.Q12U_Angle);
    
    Math_SinCos_T(&pCTRL->TG_Triangle);
}
