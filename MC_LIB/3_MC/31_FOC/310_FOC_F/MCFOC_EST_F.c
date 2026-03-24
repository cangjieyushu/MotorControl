/**************************************************************************************************
*     File Name :                        MCFOC_EST_F.c
*     Library/Module Name :              MCFOC_F
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             速度角度观测器源文件
**************************************************************************************************/

#include "MCFOC_EST_F.h"


/**********************************反电动势观测器************************************/

/**********************************************************************************************
Function: MCFOC_EST_EMF_Init_F
Description: 反电动势观测器初始化
Input: 无
Output: 无
Input_Output: 反电动势观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_EMF_Init_F(ST_EMF_CONTROL_F* pEMF)
{
    LPF_Init_F(&pEMF->FL_EMF_Ialfa_err, 0.0f);
    LPF_Init_F(&pEMF->FL_EMF_Ibeta_err, 0.0f);
    
    pEMF->_V_F_EMF_Ialfa_Last = 0.0f;
    pEMF->_V_F_EMF_Ibeta_Last = 0.0f;
}

/**********************************************************************************************
Function: MCFOC_EST_EMF_Adapt_F
Description: 反电动势观测器参数自适应
Input: 无
Output: 无
Input_Output: 反电动势观测器指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_EMF_Adapt_F(ST_EMF_CONTROL_F* pEMF, ST_PMSM_PARA_F* pPMSMa)
{
    pEMF->_D_F_EMF_Rs = pPMSMa->_O_F_Rs;
    pEMF->_D_F_EMF_Ls_Over_Ts = pPMSMa->_O_F_Ls/pPMSMa->_O_F_Ts;
}

/**********************************************************************************************
Function: MCFOC_EST_EMF_F
Description: 反电动势观测器计算
Input: 无
Output: 无
Input_Output: 反电动势观测器指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_EMF_F(ST_EMF_CONTROL_F* pEMF, ST_PMSM_ELEC_F* pPMSMe)
{
    pEMF->FL_EMF_Ialfa_err.F_LPF_In = pPMSMe->_V_F_Ialfa - pEMF->_V_F_EMF_Ialfa_Last;
    pEMF->FL_EMF_Ibeta_err.F_LPF_In = pPMSMe->_V_F_Ibeta - pEMF->_V_F_EMF_Ibeta_Last;
    
    LPF_Cal_F(&pEMF->FL_EMF_Ialfa_err);
    LPF_Cal_F(&pEMF->FL_EMF_Ibeta_err);
    
    pEMF->_O_F_EMF_Ealfa = pPMSMe->_V_F_Ualfa
                         - pEMF->_D_F_EMF_Rs*pPMSMe->_V_F_Ialfa
                         - pEMF->_D_F_EMF_Ls_Over_Ts*pEMF->FL_EMF_Ialfa_err.F_LPF_Out;
    pEMF->_O_F_EMF_Ebeta = pPMSMe->_V_F_Ubeta
                         - pEMF->_D_F_EMF_Rs*pPMSMe->_V_F_Ibeta
                         - pEMF->_D_F_EMF_Ls_Over_Ts*pEMF->FL_EMF_Ibeta_err.F_LPF_Out;
    
    pEMF->_V_F_EMF_Ialfa_Last = pPMSMe->_V_F_Ialfa;
    pEMF->_V_F_EMF_Ibeta_Last = pPMSMe->_V_F_Ibeta;
}


/**********************************滑模观测器************************************/

/**********************************************************************************************
Function: MCFOC_EST_SMO_Init_F
Description: 滑模观测器初始化
Input: 无
Output: 无
Input_Output: 滑模观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_SMO_Init_F(ST_SMO_CONTROL_F* pSMO)
{
    PID_Pos_Init_F(&pSMO->PID_SMO_PLL, 0.0f);
    LPF_Init_F(&pSMO->FL_SMO_FREQ, 0.0f);
    pSMO->TG_SMO_Triangle.F_Angle = 0.0f;
    pSMO->TG_SMO_Triangle.F_Cos = 1.0f;
    pSMO->TG_SMO_Triangle.F_Sin = 0.0f;
    pSMO->TG_SMO_Triangle.F_ReAngle = 0.0f;
    
    pSMO->_V_F_SMO_Aalfa = 0.0f;
    pSMO->_V_F_SMO_Abeta = 0.0f;
}

/**********************************************************************************************
Function: MCFOC_EST_SMO_Adapt_F
Description: SMO观测器参数自适应
Input: 无
Output: 无
Input_Output: SMO观测器指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_SMO_Adapt_F(ST_SMO_CONTROL_F* pSMO, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa)
{
    float F_Freq_tmp = 0.0f;
    F_Freq_tmp = MATH_ABS_F(pPMSMe->_O_F_Freq);
    float F_Is_tmp = 0.0f;
    F_Is_tmp = MATH_ABS_F(pPMSMe->_O_F_Is);
    
    pSMO->_D_F_SMO_H1_Set = pSMO->_P_F_SMO_H1*TABLE_1D_Inter_F(&pSMO->TAB_SMO_H1_Coeff, F_Freq_tmp);
    pSMO->PID_SMO_PLL.F_Kp = pSMO->_P_F_SMO_PLL_Kp*TABLE_1D_Inter_F(&pSMO->TAB_SMO_Kp_Coeff, F_Freq_tmp);
    pSMO->PID_SMO_PLL.F_Ki = pSMO->_P_F_SMO_PLL_Ki*TABLE_1D_Inter_F(&pSMO->TAB_SMO_Ki_Coeff, F_Freq_tmp);
    pSMO->TG_SMO_Triangle_Comp.F_Angle = TABLE_2D_Inter_F(&pSMO->TAB_SMO_Angle_Comp, F_Freq_tmp, F_Is_tmp);
    MATH_ANGLE_MOD_F(pSMO->TG_SMO_Triangle_Comp.F_Angle);
    Math_SinCos_F(&pSMO->TG_SMO_Triangle_Comp);
    
    pSMO->_D_F_SMO_Ts = pPMSMa->_O_F_Ts;
    pSMO->_D_F_SMO_One_Over_Ld = 1.0f/pPMSMa->_O_F_Ld;
    pSMO->_D_F_SMO_Rs_Over_Ld = pPMSMa->_O_F_Rs/pPMSMa->_O_F_Ld;
    pSMO->_D_F_SMO_Ld_Lq_Over_Ld = (pPMSMa->_O_F_Ld - pPMSMa->_O_F_Lq)/pPMSMa->_O_F_Ld;
}

/**********************************************************************************************
Function: MCFOC_EST_SMO_F
Description: 滑模观测器计算
Input: 无
Output: 无
Input_Output: 滑模观测器指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_SMO_F(ST_SMO_CONTROL_F* pSMO, ST_PMSM_ELEC_F* pPMSMe)
{
    pSMO->_V_F_SMO_Aalfa += pSMO->_D_F_SMO_Ts*(
					      - pSMO->_D_F_SMO_Rs_Over_Ld*pSMO->_V_F_SMO_Aalfa
                          - pSMO->_D_F_SMO_Ld_Lq_Over_Ld*pSMO->FL_SMO_FREQ.F_LPF_In*pSMO->_V_F_SMO_Abeta
                          + pSMO->_D_F_SMO_One_Over_Ld*pPMSMe->_V_F_Ualfa
                          - pSMO->_D_F_SMO_One_Over_Ld*pSMO->_V_F_SMO_Ealfa);
    pSMO->_V_F_SMO_Abeta += pSMO->_D_F_SMO_Ts*(
					      - pSMO->_D_F_SMO_Rs_Over_Ld*pSMO->_V_F_SMO_Abeta
                          + pSMO->_D_F_SMO_Ld_Lq_Over_Ld*pSMO->FL_SMO_FREQ.F_LPF_In*pSMO->_V_F_SMO_Aalfa
                          + pSMO->_D_F_SMO_One_Over_Ld*pPMSMe->_V_F_Ubeta
                          - pSMO->_D_F_SMO_One_Over_Ld*pSMO->_V_F_SMO_Ebeta);
    
    pSMO->_V_F_SMO_Ealfa = pSMO->_D_F_SMO_H1_Set*(pSMO->_V_F_SMO_Aalfa - pPMSMe->_V_F_Ialfa);
    pSMO->_V_F_SMO_Ebeta = pSMO->_D_F_SMO_H1_Set*(pSMO->_V_F_SMO_Abeta - pPMSMe->_V_F_Ibeta);

    pSMO->PID_SMO_PLL.F_Rf = -pPMSMe->_I_F_DIR_Target*pSMO->_V_F_SMO_Ealfa*pSMO->TG_SMO_Triangle.F_Cos;
    pSMO->PID_SMO_PLL.F_Fb =  pPMSMe->_I_F_DIR_Target*pSMO->_V_F_SMO_Ebeta*pSMO->TG_SMO_Triangle.F_Sin;
    PID_Pos_Cal_F(&pSMO->PID_SMO_PLL);
    
    pSMO->FL_SMO_FREQ.F_LPF_In = pSMO->PID_SMO_PLL.F_Output;
    LPF_Cal_F(&pSMO->FL_SMO_FREQ);
    
    pSMO->TG_SMO_Triangle.F_Angle += pSMO->_D_F_SMO_Ts*pSMO->FL_SMO_FREQ.F_LPF_In;
    MATH_ANGLE_MOD_F(pSMO->TG_SMO_Triangle.F_Angle);
    Math_SinCos_F(&pSMO->TG_SMO_Triangle);
}


/**********************************磁链观测器************************************/

/**********************************************************************************************
Function: MCFOC_EST_FLUX_Init_F
Description: 磁链观测器初始化
Input: 无
Output: 无
Input_Output: 磁链观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_FLUX_Init_F(ST_FLUX_CONTROL_F* pFLUX)
{
    PID_Pos_Init_F(&pFLUX->PID_FLUX_PLL, 0.0f);
    LPF_Init_F(&pFLUX->FL_FLUX_FREQ, 0.0f);

    pFLUX->TG_FLUX_Triangle.F_Angle = 0.0f;
    pFLUX->TG_FLUX_Triangle.F_Cos = 1.0f;
    pFLUX->TG_FLUX_Triangle.F_Sin = 0.0f;
    pFLUX->TG_FLUX_Triangle.F_ReAngle = 0.0f;
    
    pFLUX->_V_F_FLUX_Xalfa = pFLUX->_D_F_FLUX_Flux;
    pFLUX->_V_F_FLUX_Xbeta = 0.0f;
}

/**********************************************************************************************
Function: MCFOC_EST_FLUX_Adapt_F
Description: FLUX观测器参数自适应
Input: 无
Output: 无
Input_Output: FLUX观测器指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_FLUX_Adapt_F(ST_FLUX_CONTROL_F* pFLUX, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa)
{
    float F_Freq_tmp = 0.0f;
    F_Freq_tmp = MATH_ABS_F(pPMSMe->_O_F_Freq);
    float F_Is_tmp = 0.0f;
    F_Is_tmp = MATH_ABS_F(pPMSMe->_O_F_Is);
    
    pFLUX->_D_F_FLUX_Gamma_Set = pFLUX->_P_F_FLUX_Gamma*TABLE_1D_Inter_F(&pFLUX->TAB_FLUX_Gamma_Coeff, F_Freq_tmp);
    pFLUX->PID_FLUX_PLL.F_Kp = pFLUX->_P_F_FLUX_PLL_Kp*TABLE_1D_Inter_F(&pFLUX->TAB_FLUX_Kp_Coeff, pPMSMe->_O_F_Freq);
    pFLUX->PID_FLUX_PLL.F_Ki = pFLUX->_P_F_FLUX_PLL_Ki*TABLE_1D_Inter_F(&pFLUX->TAB_FLUX_Ki_Coeff, pPMSMe->_O_F_Freq);
    pFLUX->TG_FLUX_Triangle_Comp.F_Angle = TABLE_2D_Inter_F(&pFLUX->TAB_FLUX_Angle_Comp, pPMSMe->_O_F_Freq, F_Is_tmp);
    MATH_ANGLE_MOD_F(pFLUX->TG_FLUX_Triangle_Comp.F_Angle);
    Math_SinCos_F(&pFLUX->TG_FLUX_Triangle_Comp);
    
    pFLUX->_D_F_FLUX_Ts = pPMSMa->_O_F_Ts;
    pFLUX->_D_F_FLUX_Ld = pPMSMa->_O_F_Ld;
    pFLUX->_D_F_FLUX_Lq = pPMSMa->_O_F_Lq;
    pFLUX->_D_F_FLUX_Flux = pPMSMa->_O_F_Flux;
}

/**********************************************************************************************
Function: MCFOC_EST_FLUX_F
Description: 磁链观测器计算
Input: 无
Output: 无
Input_Output: 磁链观测器指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_FLUX_F(ST_FLUX_CONTROL_F* pFLUX, ST_PMSM_ELEC_F* pPMSMe)
{
    float F_Id = 0.0f, F_Iq = 0.0f;
    float F_Fluxalfa = 0.0f, F_Fluxbeta = 0.0f;

    F_Id =   pPMSMe->_V_F_Ialfa*pFLUX->TG_FLUX_Triangle.F_Cos
           + pPMSMe->_V_F_Ibeta*pFLUX->TG_FLUX_Triangle.F_Sin;
    F_Iq = - pPMSMe->_V_F_Ialfa*pFLUX->TG_FLUX_Triangle.F_Sin
           + pPMSMe->_V_F_Ibeta*pFLUX->TG_FLUX_Triangle.F_Cos;

    F_Id = F_Id*pFLUX->_D_F_FLUX_Ld + pFLUX->_D_F_FLUX_Flux;
    F_Iq = F_Iq*pFLUX->_D_F_FLUX_Lq;

    F_Fluxalfa = F_Id*pFLUX->TG_FLUX_Triangle.F_Cos
               - F_Iq*pFLUX->TG_FLUX_Triangle.F_Sin;
    F_Fluxbeta = F_Id*pFLUX->TG_FLUX_Triangle.F_Sin
               + F_Iq*pFLUX->TG_FLUX_Triangle.F_Cos;
    
    pFLUX->_V_F_FLUX_Xalfa += pFLUX->_D_F_FLUX_Ts*(pPMSMe->_V_F_Ualfa
                            + pFLUX->_D_F_FLUX_Gamma_Set*(F_Fluxalfa - pFLUX->_V_F_FLUX_Xalfa));
    pFLUX->_V_F_FLUX_Xbeta += pFLUX->_D_F_FLUX_Ts*(pPMSMe->_V_F_Ubeta
                            + pFLUX->_D_F_FLUX_Gamma_Set*(F_Fluxbeta - pFLUX->_V_F_FLUX_Xbeta));
    
    pFLUX->PID_FLUX_PLL.F_Rf = (pFLUX->_V_F_FLUX_Xbeta - pFLUX->_D_F_FLUX_Lq*pPMSMe->_V_F_Ibeta)
                        * pFLUX->TG_FLUX_Triangle.F_Cos;
    pFLUX->PID_FLUX_PLL.F_Fb = (pFLUX->_V_F_FLUX_Xalfa - pFLUX->_D_F_FLUX_Lq*pPMSMe->_V_F_Ialfa)
                        * pFLUX->TG_FLUX_Triangle.F_Sin;
    PID_Pos_Cal_F(&pFLUX->PID_FLUX_PLL);
    
    pFLUX->FL_FLUX_FREQ.F_LPF_In = pFLUX->PID_FLUX_PLL.F_Output;
    LPF_Cal_F(&pFLUX->FL_FLUX_FREQ);
    
    pFLUX->TG_FLUX_Triangle.F_Angle += pFLUX->_D_F_FLUX_Ts*pFLUX->FL_FLUX_FREQ.F_LPF_In;
    MATH_ANGLE_MOD_F(pFLUX->TG_FLUX_Triangle.F_Angle);
    Math_SinCos_F(&pFLUX->TG_FLUX_Triangle);
}
