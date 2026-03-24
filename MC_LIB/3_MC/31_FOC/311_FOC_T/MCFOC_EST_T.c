/**************************************************************************************************
*     File Name :                        MCFOC_EST_T.c
*     Library/Module Name :              MCFOC_T
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             速度角度观测器源文件
**************************************************************************************************/

#include "MCFOC_EST_T.h"


/**********************************反电动势观测器************************************/

/**********************************************************************************************
Function: MCFOC_EST_EMF_Init_T
Description: 反电动势观测器初始化
Input: 无
Output: 无
Input_Output: 反电动势观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_EMF_Init_T(ST_EMF_CONTROL_T* pEMF)
{
    LPF_Init_T(&pEMF->FL_EMF_Ialfa_err, 0);
    LPF_Init_T(&pEMF->FL_EMF_Ibeta_err, 0);
    
    pEMF->_V_Q14I_EMF_Ialfa_Last = 0;
    pEMF->_V_Q14I_EMF_Ibeta_Last = 0;
}

/**********************************************************************************************
Function: MCFOC_EST_EMF_Adapt_T
Description: 反电动势观测器参数自适应
Input: 无
Output: 无
Input_Output: 反电动势观测器指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_EMF_Adapt_T(ST_EMF_CONTROL_T* pEMF, ST_PMSM_PARA_T* pPMSMa)
{
    pEMF->_D_Q14I_EMF_Rs = pPMSMa->_O_Q14I_Rs;
    pEMF->_D_Q10I_EMF_Ls_Over_Ts = Q16I_LFT_10(pPMSMa->_O_Q14I_Ls)/pPMSMa->_O_Q14I_Ts;
}

/**********************************************************************************************
Function: MCFOC_EST_EMF_T
Description: 反电动势观测器计算
Input: 无
Output: 无
Input_Output: 反电动势观测器指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_EMF_T(ST_EMF_CONTROL_T* pEMF, ST_PMSM_ELEC_T* pPMSMe)
{
    pEMF->FL_EMF_Ialfa_err.Q14I_LPF_In = pPMSMe->_V_Q14I_Ialfa - pEMF->_V_Q14I_EMF_Ialfa_Last;
    pEMF->FL_EMF_Ibeta_err.Q14I_LPF_In = pPMSMe->_V_Q14I_Ibeta - pEMF->_V_Q14I_EMF_Ibeta_Last;
    
    LPF_Cal_T(&pEMF->FL_EMF_Ialfa_err);
    LPF_Cal_T(&pEMF->FL_EMF_Ibeta_err);
    
    pEMF->_O_Q14I_EMF_Ealfa = pPMSMe->_V_Q14I_Ualfa
                            - Q32I_RHT_14(pEMF->_D_Q14I_EMF_Rs*pPMSMe->_V_Q14I_Ialfa)
                            - Q32I_RHT_10(pEMF->_D_Q10I_EMF_Ls_Over_Ts*pEMF->FL_EMF_Ialfa_err.Q14I_LPF_Out);
    pEMF->_O_Q14I_EMF_Ebeta = pPMSMe->_V_Q14I_Ubeta
                            - Q32I_RHT_14(pEMF->_D_Q14I_EMF_Rs*pPMSMe->_V_Q14I_Ibeta)
                            - Q32I_RHT_10(pEMF->_D_Q10I_EMF_Ls_Over_Ts*pEMF->FL_EMF_Ibeta_err.Q14I_LPF_Out);
    
    pEMF->_V_Q14I_EMF_Ialfa_Last = pPMSMe->_V_Q14I_Ialfa;
    pEMF->_V_Q14I_EMF_Ibeta_Last = pPMSMe->_V_Q14I_Ibeta;
}


/**********************************滑模观测器************************************/

/**********************************************************************************************
Function: MCFOC_EST_SMO_Init_T
Description: 滑模观测器初始化
Input: 无
Output: 无
Input_Output: 滑模观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_SMO_Init_T(ST_SMO_CONTROL_T* pSMO)
{
    PID_Pos_Init_T(&pSMO->PID_SMO_PLL, 0);
    LPF_Init_T(&pSMO->FL_SMO_FREQ, 0);
    pSMO->TG_SMO_Triangle.Q14U_Angle = 0;
    pSMO->TG_SMO_Triangle.Q14I_Cos = 16384;
    pSMO->TG_SMO_Triangle.Q14I_Sin = 0;
    pSMO->TG_SMO_Triangle.Q14U_ReAngle = 0;
    
    pSMO->_V_Q28I_SMO_Angle_tmp = 0;
    pSMO->_V_Q28I_SMO_Aalfa = 0;
    pSMO->_V_Q28I_SMO_Abeta = 0;
}

/**********************************************************************************************
Function: MCFOC_EST_SMO_Adapt_T
Description: SMO观测器参数自适应
Input: 无
Output: 无
Input_Output: SMO观测器指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_SMO_Adapt_T(ST_SMO_CONTROL_T* pSMO, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa)
{
    Q32I_ Q14I_Freq_tmp = 0;
    Q14I_Freq_tmp = MATH_ABS_F(pPMSMe->_O_Q14I_Freq);
    Q32I_ Q14I_Is_tmp = 0;
    Q14I_Is_tmp = MATH_ABS_F(pPMSMe->_O_Q14I_Is);
    
    pSMO->_D_Q14I_SMO_H1_Set = Q32I_RHT_14(pSMO->_P_Q14I_SMO_H1*TABLE_1D_Inter_T(&pSMO->TAB_SMO_H1_Coeff, Q14I_Freq_tmp));
	pSMO->PID_SMO_PLL.Q14I_Kp = Q32I_RHT_14(pSMO->_P_Q14I_SMO_PLL_Kp*TABLE_1D_Inter_T(&pSMO->TAB_SMO_Kp_Coeff, Q14I_Freq_tmp));
    pSMO->PID_SMO_PLL.Q14I_Ki = Q32I_RHT_14(pSMO->_P_Q14I_SMO_PLL_Ki*TABLE_1D_Inter_T(&pSMO->TAB_SMO_Ki_Coeff, Q14I_Freq_tmp));
    pSMO->TG_SMO_Triangle_Comp.Q14U_Angle = TABLE_2D_Inter_T(&pSMO->TAB_SMO_Angle_Comp, Q14I_Freq_tmp, Q14I_Is_tmp);
    MATH_ANGLE_MOD_T(pSMO->TG_SMO_Triangle_Comp.Q14U_Angle);
    Math_SinCos_T(&pSMO->TG_SMO_Triangle_Comp);
    
    pSMO->_D_Q14I_SMO_Ts = pPMSMa->_O_Q14I_Ts;
    pSMO->_D_Q10I_SMO_One_Over_Ld = 16777216/pPMSMa->_O_Q14I_Ld;
    pSMO->_D_Q10I_SMO_Rs_Over_Ld = Q16I_LFT_10(pPMSMa->_O_Q14I_Rs)/pPMSMa->_O_Q14I_Ld;
    pSMO->_D_Q14I_SMO_Ld_Lq_Over_Ld = Q16I_LFT_14(pPMSMa->_O_Q14I_Ld - pPMSMa->_O_Q14I_Lq)/pPMSMa->_O_Q14I_Ld;
}

/**********************************************************************************************
Function: MCFOC_EST_SMO_T
Description: 滑模观测器计算
Input: 无
Output: 无
Input_Output: 滑模观测器指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_SMO_T(ST_SMO_CONTROL_T* pSMO, ST_PMSM_ELEC_T* pPMSMe)
{
    pSMO->_V_Q28I_SMO_Aalfa += pSMO->_D_Q14I_SMO_Ts*Q32I_RHT_10(
					      - pSMO->_D_Q10I_SMO_Rs_Over_Ld*pSMO->_V_Q14I_SMO_Aalfa
                          - Q32I_RHT_08(Q32I_RHT_10(pSMO->_D_Q14I_SMO_Ld_Lq_Over_Ld*pSMO->_V_Q14I_SMO_Abeta)*pSMO->FL_SMO_FREQ.Q14I_LPF_In)
                          + pSMO->_D_Q10I_SMO_One_Over_Ld*pPMSMe->_V_Q14I_Ualfa
                          - pSMO->_D_Q10I_SMO_One_Over_Ld*pSMO->_V_Q14I_SMO_Ealfa);
    pSMO->_V_Q28I_SMO_Abeta += pSMO->_D_Q14I_SMO_Ts*Q32I_RHT_10(
					      - pSMO->_D_Q10I_SMO_Rs_Over_Ld*pSMO->_V_Q14I_SMO_Abeta
                          + Q32I_RHT_08(Q32I_RHT_10(pSMO->_D_Q14I_SMO_Ld_Lq_Over_Ld*pSMO->_V_Q14I_SMO_Aalfa)*pSMO->FL_SMO_FREQ.Q14I_LPF_In)
                          + pSMO->_D_Q10I_SMO_One_Over_Ld*pPMSMe->_V_Q14I_Ubeta
                          - pSMO->_D_Q10I_SMO_One_Over_Ld*pSMO->_V_Q14I_SMO_Ebeta);
    
    pSMO->_V_Q14I_SMO_Aalfa = Q32I_RHT_14(pSMO->_V_Q28I_SMO_Aalfa);
    pSMO->_V_Q14I_SMO_Abeta = Q32I_RHT_14(pSMO->_V_Q28I_SMO_Abeta);
	
    pSMO->_V_Q14I_SMO_Ealfa = Q32I_RHT_14(pSMO->_P_Q14I_SMO_H1*(pSMO->_V_Q14I_SMO_Aalfa - pPMSMe->_V_Q14I_Ialfa));
    pSMO->_V_Q14I_SMO_Ebeta = Q32I_RHT_14(pSMO->_P_Q14I_SMO_H1*(pSMO->_V_Q14I_SMO_Abeta - pPMSMe->_V_Q14I_Ibeta));

    pSMO->PID_SMO_PLL.Q14I_Rf = -Q32I_RHT_14(pPMSMe->_I_Q00I_DIR_Target*pSMO->_V_Q14I_SMO_Ealfa*pSMO->TG_SMO_Triangle.Q14I_Cos);
    pSMO->PID_SMO_PLL.Q14I_Fb =  Q32I_RHT_14(pPMSMe->_I_Q00I_DIR_Target*pSMO->_V_Q14I_SMO_Ebeta*pSMO->TG_SMO_Triangle.Q14I_Sin);
    PID_Pos_Cal_T(&pSMO->PID_SMO_PLL);
    
    pSMO->FL_SMO_FREQ.Q14I_LPF_In = pSMO->PID_SMO_PLL.Q14I_Output;
    LPF_Cal_T(&pSMO->FL_SMO_FREQ);
    
    pSMO->_V_Q28I_SMO_Angle_tmp += pSMO->_D_Q14I_SMO_Ts*pSMO->FL_SMO_FREQ.Q14I_LPF_In;
    MATH_ANGLE_TMP_T(pSMO->_V_Q28I_SMO_Angle_tmp);
    pSMO->TG_SMO_Triangle.Q14U_Angle = Q32I_RHT_14(pSMO->_V_Q28I_SMO_Angle_tmp);
    Math_SinCos_T(&pSMO->TG_SMO_Triangle);
}


/**********************************磁链观测器************************************/

/**********************************************************************************************
Function: MCFOC_EST_FLUX_Init_T
Description: 磁链观测器初始化
Input: 无
Output: 无
Input_Output: 磁链观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_FLUX_Init_T(ST_FLUX_CONTROL_T* pFLUX)
{
    PID_Pos_Init_T(&pFLUX->PID_FLUX_PLL, 0);
    LPF_Init_T(&pFLUX->FL_FLUX_FREQ, 0);

    pFLUX->TG_FLUX_Triangle.Q14U_Angle = 0;
    pFLUX->TG_FLUX_Triangle.Q14I_Cos = 16384;
    pFLUX->TG_FLUX_Triangle.Q14I_Sin = 0;
    pFLUX->TG_FLUX_Triangle.Q14U_ReAngle = 0;
    
    pFLUX->_V_Q28I_FLUX_Angle_tmp = 0;
    pFLUX->_V_Q28I_FLUX_Xalfa = pFLUX->_D_Q14I_FLUX_Flux;
    pFLUX->_V_Q28I_FLUX_Xbeta = 0;
}

/**********************************************************************************************
Function: MCFOC_EST_FLUX_Adapt_T
Description: FLUX观测器参数自适应
Input: 无
Output: 无
Input_Output: FLUX观测器指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_FLUX_Adapt_T(ST_FLUX_CONTROL_T* pFLUX, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa)
{
    Q32I_ Q14I_Freq_tmp = 0;
    Q14I_Freq_tmp = MATH_ABS_F(pPMSMe->_O_Q14I_Freq);
    Q32I_ Q14I_Is_tmp = 0;
    Q14I_Is_tmp = MATH_ABS_F(pPMSMe->_O_Q14I_Is);
    
    pFLUX->_D_Q14I_FLUX_Gamma_Set = Q32I_RHT_14(pFLUX->_P_Q14I_FLUX_Gamma*TABLE_1D_Inter_T(&pFLUX->TAB_FLUX_Gamma_Coeff, Q14I_Freq_tmp));
	pFLUX->PID_FLUX_PLL.Q14I_Kp = Q32I_RHT_14(pFLUX->_P_Q14I_FLUX_PLL_Kp*TABLE_1D_Inter_T(&pFLUX->TAB_FLUX_Kp_Coeff, pPMSMe->_O_Q14I_Freq));
    pFLUX->PID_FLUX_PLL.Q14I_Ki = Q32I_RHT_14(pFLUX->_P_Q14I_FLUX_PLL_Ki*TABLE_1D_Inter_T(&pFLUX->TAB_FLUX_Ki_Coeff, pPMSMe->_O_Q14I_Freq));
    pFLUX->TG_FLUX_Triangle_Comp.Q14U_Angle = TABLE_2D_Inter_T(&pFLUX->TAB_FLUX_Angle_Comp, pPMSMe->_O_Q14I_Freq, Q14I_Is_tmp);
    MATH_ANGLE_MOD_T(pFLUX->TG_FLUX_Triangle_Comp.Q14U_Angle);
    Math_SinCos_T(&pFLUX->TG_FLUX_Triangle_Comp);
    
    pFLUX->_D_Q14I_FLUX_Ts = pPMSMa->_O_Q14I_Ts;
    pFLUX->_D_Q14I_FLUX_Ld = pPMSMa->_O_Q14I_Ld;
    pFLUX->_D_Q14I_FLUX_Lq = pPMSMa->_O_Q14I_Lq;
    pFLUX->_D_Q14I_FLUX_Flux = pPMSMa->_O_Q14I_Flux;
}

/**********************************************************************************************
Function: MCFOC_EST_FLUX_T
Description: 磁链观测器计算
Input: 无
Output: 无
Input_Output: 磁链观测器指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_FLUX_T(ST_FLUX_CONTROL_T* pFLUX, ST_PMSM_ELEC_T* pPMSMe)
{
    Q32I_ Q14I_Id = 0, Q14I_Iq = 0;
    Q32I_ Q28I_Fluxalfa = 0, Q28I_Fluxbeta = 0;

    Q14I_Id =   Q32I_RHT_14(pPMSMe->_V_Q14I_Ialfa*pFLUX->TG_FLUX_Triangle.Q14I_Cos
                          + pPMSMe->_V_Q14I_Ibeta*pFLUX->TG_FLUX_Triangle.Q14I_Sin);
    Q14I_Iq = - Q32I_RHT_14(pPMSMe->_V_Q14I_Ialfa*pFLUX->TG_FLUX_Triangle.Q14I_Sin
                          + pPMSMe->_V_Q14I_Ibeta*pFLUX->TG_FLUX_Triangle.Q14I_Cos);

    Q14I_Id = Q32I_RHT_14(Q14I_Id*pFLUX->_D_Q14I_FLUX_Ld) + pFLUX->_D_Q14I_FLUX_Flux;
    Q14I_Iq = Q32I_RHT_14(Q14I_Iq*pFLUX->_D_Q14I_FLUX_Lq);

    Q28I_Fluxalfa = Q14I_Id*pFLUX->TG_FLUX_Triangle.Q14I_Cos
                  - Q14I_Iq*pFLUX->TG_FLUX_Triangle.Q14I_Sin;
    Q28I_Fluxbeta = Q14I_Id*pFLUX->TG_FLUX_Triangle.Q14I_Sin
                  + Q14I_Iq*pFLUX->TG_FLUX_Triangle.Q14I_Cos;
    
    pFLUX->_V_Q28I_FLUX_Xalfa += pFLUX->_D_Q14I_FLUX_Ts*(pPMSMe->_V_Q14I_Ualfa
                               + Q32I_RHT_14(pFLUX->_D_Q14I_FLUX_Gamma_Set*Q32I_RHT_14(Q28I_Fluxalfa - pFLUX->_V_Q28I_FLUX_Xalfa)));
    pFLUX->_V_Q28I_FLUX_Xbeta += pFLUX->_D_Q14I_FLUX_Ts*(pPMSMe->_V_Q14I_Ubeta
                               + Q32I_RHT_14(pFLUX->_D_Q14I_FLUX_Gamma_Set*Q32I_RHT_14(Q28I_Fluxbeta - pFLUX->_V_Q28I_FLUX_Xbeta)));
    
    pFLUX->PID_FLUX_PLL.Q14I_Rf = Q32I_RHT_14(Q32I_RHT_14(pFLUX->_V_Q28I_FLUX_Xbeta - pFLUX->_D_Q14I_FLUX_Lq*pPMSMe->_V_Q14I_Ibeta)
                        * pFLUX->TG_FLUX_Triangle.Q14I_Cos);
    pFLUX->PID_FLUX_PLL.Q14I_Fb = Q32I_RHT_14(Q32I_RHT_14(pFLUX->_V_Q28I_FLUX_Xalfa - pFLUX->_D_Q14I_FLUX_Lq*pPMSMe->_V_Q14I_Ialfa)
                        * pFLUX->TG_FLUX_Triangle.Q14I_Sin);
    PID_Pos_Cal_T(&pFLUX->PID_FLUX_PLL);
    
    pFLUX->FL_FLUX_FREQ.Q14I_LPF_In = pFLUX->PID_FLUX_PLL.Q14I_Output;
    LPF_Cal_T(&pFLUX->FL_FLUX_FREQ);
    
    pFLUX->_V_Q28I_FLUX_Angle_tmp += pFLUX->_D_Q14I_FLUX_Ts*pFLUX->FL_FLUX_FREQ.Q14I_LPF_In;
    MATH_ANGLE_TMP_T(pFLUX->_V_Q28I_FLUX_Angle_tmp);
    pFLUX->TG_FLUX_Triangle.Q14U_Angle = Q32I_RHT_14(pFLUX->_V_Q28I_FLUX_Angle_tmp);
    Math_SinCos_T(&pFLUX->TG_FLUX_Triangle);
}
