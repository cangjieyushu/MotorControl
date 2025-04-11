/**************************************************************************************************
*     File Name :                        MotorEst.c
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             速度角度观测器源文件
**************************************************************************************************/
#include "MotorEst.h"

/**********************************************************************/

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
    PID_Pos_Init_T(&pCTRL->PID_PLL, 0);
    Filter_Init_T(&pCTRL->FL_SRAD, 0);
    pCTRL->TG_Triangle.Q12U_Angle = 0;
    pCTRL->TG_Triangle.Q14I_Cos = 16384;
    pCTRL->TG_Triangle.Q14I_Sin = 0;
    pCTRL->TG_Triangle.Q12U_ReAngle = 0;
	
    pCTRL->_V_Q28I_Xalfa_tmp = Q16I_LFT_14(pCTRL->_P_Q14I_Flux);
	pCTRL->_V_Q28I_Xbeta_tmp = 0;
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
    pCTRL->_V_Q14I_Yalfa = pCTRL->_I_Q14I_Ualfa - Q32I_RHT_14(pCTRL->_P_Q14I_Rs*pCTRL->_I_Q14I_Ialfa);
    pCTRL->_V_Q14I_Ybeta = pCTRL->_I_Q14I_Ubeta - Q32I_RHT_14(pCTRL->_P_Q14I_Rs*pCTRL->_I_Q14I_Ibeta);
    
    pCTRL->_V_Q14I_Nalfa = pCTRL->_V_Q14I_Xalfa - Q32I_RHT_14(pCTRL->_P_Q14I_Ls*pCTRL->_I_Q14I_Ialfa);
    pCTRL->_V_Q14I_Nbeta = pCTRL->_V_Q14I_Xbeta - Q32I_RHT_14(pCTRL->_P_Q14I_Ls*pCTRL->_I_Q14I_Ibeta);
    pCTRL->_V_Q14I_Nn2 = Q32I_RHT_14(MATH_SQUARE_T(pCTRL->_V_Q14I_Nalfa) + MATH_SQUARE_T(pCTRL->_V_Q14I_Nbeta));
    
    pCTRL->_V_Q14I_Valfa = Q32I_RHT_14(pCTRL->_P_Q14I_Gamma*Q32I_RHT_14(pCTRL->_V_Q14I_Nalfa*(pCTRL->_P_Q14I_Flux2 - pCTRL->_V_Q14I_Nn2)));
    pCTRL->_V_Q14I_Vbeta = Q32I_RHT_14(pCTRL->_P_Q14I_Gamma*Q32I_RHT_14(pCTRL->_V_Q14I_Nbeta*(pCTRL->_P_Q14I_Flux2 - pCTRL->_V_Q14I_Nn2)));
    
    pCTRL->_V_Q28I_Xalfa_tmp += pCTRL->_P_Q14I_Ws*(pCTRL->_V_Q14I_Yalfa + pCTRL->_V_Q14I_Valfa);
    pCTRL->_V_Q28I_Xbeta_tmp += pCTRL->_P_Q14I_Ws*(pCTRL->_V_Q14I_Ybeta + pCTRL->_V_Q14I_Vbeta);
    
    pCTRL->_V_Q28I_Xalfa_tmp = MATH_SAT_T(pCTRL->_V_Q28I_Xalfa_tmp, (Q32I_)Q28U_MAX, -(Q32I_)Q28U_MAX);
    pCTRL->_V_Q28I_Xbeta_tmp = MATH_SAT_T(pCTRL->_V_Q28I_Xbeta_tmp, (Q32I_)Q28U_MAX, -(Q32I_)Q28U_MAX);
    
    pCTRL->_V_Q14I_Xalfa = Q32I_RHT_14(pCTRL->_V_Q28I_Xalfa_tmp);
    pCTRL->_V_Q14I_Xbeta = Q32I_RHT_14(pCTRL->_V_Q28I_Xbeta_tmp);
        
    pCTRL->_V_Q14I_Nalfa = pCTRL->_V_Q14I_Xalfa - Q32I_RHT_14(pCTRL->_P_Q14I_Ls*pCTRL->_I_Q14I_Ialfa);
    pCTRL->_V_Q14I_Nbeta = pCTRL->_V_Q14I_Xbeta - Q32I_RHT_14(pCTRL->_P_Q14I_Ls*pCTRL->_I_Q14I_Ibeta);
    
    pCTRL->PID_PLL.Q14I_Rf = Q32I_RHT_14(pCTRL->_V_Q14I_Nbeta*pCTRL->TG_Triangle.Q14I_Cos);
    pCTRL->PID_PLL.Q14I_Fb = Q32I_RHT_14(pCTRL->_V_Q14I_Nalfa*pCTRL->TG_Triangle.Q14I_Sin);
    PID_Pos_Cal_T(&pCTRL->PID_PLL);
    
    pCTRL->FL_SRAD.Q16I_Filter_in = pCTRL->PID_PLL.Q14I_Output;
    Filter_Cal_T(&pCTRL->FL_SRAD);
    
    pCTRL->_O_Q28U_Angle_tmp += pCTRL->_P_Q14I_Ts*pCTRL->FL_SRAD.Q16I_Filter_in;
    MATH_ANGLE_TMP_T(pCTRL->_O_Q28U_Angle_tmp);
    pCTRL->TG_Triangle.Q12U_Angle = Q32I_RHT_16(pCTRL->_O_Q28U_Angle_tmp);
    
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
    PID_Pos_Init_T(&pCTRL->PID_PLL, 0);
    Filter_Init_T(&pCTRL->FL_SRAD, 0);
    pCTRL->TG_Triangle.Q12U_Angle = 0;
    pCTRL->TG_Triangle.Q14I_Cos = 16384;
    pCTRL->TG_Triangle.Q14I_Sin = 0;
    pCTRL->TG_Triangle.Q12U_ReAngle = 0;
    
    pCTRL->_V_Q28I_Aalfa_tmp = 0;
    pCTRL->_V_Q28I_Abeta_tmp = 0;
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
    pCTRL->_V_Q28I_Aalfa_tmp += pCTRL->_P_Q14I_Ws*(
                              - Q32I_RHT_14(pCTRL->_P_Q14I_Rs_Over_Ld*pCTRL->_V_Q14I_Aalfa)
                              - Q32I_RHT_14(pCTRL->FL_SRAD.Q16I_Filter_in*Q32I_RHT_14(pCTRL->_P_Q14I_Ld_Lq_Over_Ld*pCTRL->_V_Q14I_Abeta))
                              + Q32I_RHT_10(pCTRL->_P_Q10I_One_Over_Ld*pCTRL->_I_Q14I_Ualfa)
                              - Q32I_RHT_10(pCTRL->_P_Q10I_One_Over_Ld*pCTRL->_V_Q14I_Ealfa));
    pCTRL->_V_Q28I_Abeta_tmp += pCTRL->_P_Q14I_Ws*(
                              - Q32I_RHT_14(pCTRL->_P_Q14I_Rs_Over_Ld*pCTRL->_V_Q14I_Abeta)
                              + Q32I_RHT_14(pCTRL->FL_SRAD.Q16I_Filter_in*Q32I_RHT_14(pCTRL->_P_Q14I_Ld_Lq_Over_Ld*pCTRL->_V_Q14I_Aalfa))
                              + Q32I_RHT_10(pCTRL->_P_Q10I_One_Over_Ld*pCTRL->_I_Q14I_Ubeta)
                              - Q32I_RHT_10(pCTRL->_P_Q10I_One_Over_Ld*pCTRL->_V_Q14I_Ebeta));
    
    pCTRL->_V_Q28I_Aalfa_tmp = MATH_SAT_T(pCTRL->_V_Q28I_Aalfa_tmp, (Q32I_)Q28U_MAX, -(Q32I_)Q28U_MAX);
    pCTRL->_V_Q28I_Abeta_tmp = MATH_SAT_T(pCTRL->_V_Q28I_Abeta_tmp, (Q32I_)Q28U_MAX, -(Q32I_)Q28U_MAX);
    
    pCTRL->_V_Q14I_Aalfa = Q32I_RHT_14(pCTRL->_V_Q28I_Aalfa_tmp);
    pCTRL->_V_Q14I_Abeta = Q32I_RHT_14(pCTRL->_V_Q28I_Abeta_tmp);
    
    pCTRL->_V_Q14I_IErralfa = pCTRL->_V_Q14I_Aalfa - pCTRL->_I_Q14I_Ialfa;
    pCTRL->_V_Q14I_IErrbeta = pCTRL->_V_Q14I_Abeta - pCTRL->_I_Q14I_Ibeta;
    
    if      (pCTRL->_V_Q14I_IErralfa >  pCTRL->_P_Q14I_K1)  {pCTRL->_V_Q14I_Ealfa =  pCTRL->_P_Q14I_K1;}
    else if (pCTRL->_V_Q14I_IErralfa < -pCTRL->_P_Q14I_K1)  {pCTRL->_V_Q14I_Ealfa = -pCTRL->_P_Q14I_K1;}
    else                                                    {pCTRL->_V_Q14I_Ealfa =  pCTRL->_V_Q14I_IErralfa;}
    if      (pCTRL->_V_Q14I_IErrbeta >  pCTRL->_P_Q14I_K1)  {pCTRL->_V_Q14I_Ebeta =  pCTRL->_P_Q14I_K1;}
    else if (pCTRL->_V_Q14I_IErrbeta < -pCTRL->_P_Q14I_K1)  {pCTRL->_V_Q14I_Ebeta = -pCTRL->_P_Q14I_K1;}
    else                                                    {pCTRL->_V_Q14I_Ebeta =  pCTRL->_V_Q14I_IErrbeta;}
    
    pCTRL->PID_PLL.Q14I_Rf = -pCTRL->_I_Q00I_DIR_Target*Q32I_RHT_14(pCTRL->_V_Q14I_Ealfa*pCTRL->TG_Triangle.Q14I_Cos);
    pCTRL->PID_PLL.Q14I_Fb =  pCTRL->_I_Q00I_DIR_Target*Q32I_RHT_14(pCTRL->_V_Q14I_Ebeta*pCTRL->TG_Triangle.Q14I_Sin);
    PID_Pos_Cal_T(&pCTRL->PID_PLL);
    
    pCTRL->FL_SRAD.Q16I_Filter_in = pCTRL->PID_PLL.Q14I_Output;
    Filter_Cal_T(&pCTRL->FL_SRAD);
    
    pCTRL->_O_Q28U_Angle_tmp += pCTRL->_P_Q14I_Ts*pCTRL->FL_SRAD.Q16I_Filter_in;
    MATH_ANGLE_TMP_T(pCTRL->_O_Q28U_Angle_tmp);
    pCTRL->TG_Triangle.Q12U_Angle = Q32I_RHT_16(pCTRL->_O_Q28U_Angle_tmp);
    
    Math_SinCos_T(&pCTRL->TG_Triangle);
}

/**********************************************************************************************
Function: Est_SMO_Study_T
Description: 滑模观测器参数学习
Input: 无
Output: 无
Input_Output: 滑模观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_SMO_Study_T(ST_SMO_CONTROL_T* pCTRL)
{
    Q32I_ Alfa_abs;
    Q32I_ Alfa_sign;
    Q32I_ Beta_abs;
    Q32I_ Beta_sign;
    
    Alfa_abs = MATH_ABS_T(pCTRL->_V_Q14I_IErralfa);
    Alfa_sign = MATH_SIGN_T(pCTRL->_V_Q14I_IErralfa);
    Beta_abs = MATH_ABS_T(pCTRL->_V_Q14I_IErrbeta);
    Beta_sign = MATH_SIGN_T(pCTRL->_V_Q14I_IErrbeta);
    
    pCTRL->_V_Q32I_K1_alfa_tmp = - Q32I_RHT_14(pCTRL->_P_Q14I_Rs*Alfa_abs) + pCTRL->_V_Q14I_Ealfa*Alfa_sign
                                 - Alfa_sign*Q32I_RHT_14(pCTRL->FL_SRAD.Q16I_Filter_in*Q32I_RHT_14((pCTRL->_P_Q14I_Ld - pCTRL->_P_Q14I_Lq)
                                   *pCTRL->_V_Q14I_IErrbeta));
    pCTRL->_V_Q32I_K1_beta_tmp = - Q32I_RHT_14(pCTRL->_P_Q14I_Rs*Beta_abs) + pCTRL->_V_Q14I_Ebeta*Beta_sign
                                 + Beta_sign*Q32I_RHT_14(pCTRL->FL_SRAD.Q16I_Filter_in*Q32I_RHT_14((pCTRL->_P_Q14I_Ld - pCTRL->_P_Q14I_Lq)
                                   *pCTRL->_V_Q14I_IErralfa));
}
