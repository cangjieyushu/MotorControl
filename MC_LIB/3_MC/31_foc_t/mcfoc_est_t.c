/*
*     File Name :                        mcfoc_est_t
*     Library/Module Name :              mcfoc_t
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             速度角度观测器
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "mcfoc_est_t.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/**********************************反电动势观测器************************************/
void MCFOC_EST_EMF_Init_T(ST_EMF_CONTROL_T* pEMF)
{
    LPF_Init_T(&pEMF->FL_EMF_Ialfa_err, 0);
    LPF_Init_T(&pEMF->FL_EMF_Ibeta_err, 0);
    
    pEMF->V_Q14I_EMF_Ialfa_Last = 0;
    pEMF->V_Q14I_EMF_Ibeta_Last = 0;
}

void MCFOC_EST_EMF_Adapt_T(ST_EMF_CONTROL_T* pEMF, ST_PMSM_PARA_T* pPMSMa)
{
    pEMF->D_Q14I_EMF_Rs = pPMSMa->O_Q14I_Rs;
    pEMF->D_Q10I_EMF_Ls_Over_Ts = Q16I_LFT_10(pPMSMa->O_Q14I_Ls)/pPMSMa->O_Q14I_Ts;
}

void MCFOC_EST_EMF_Cal_T(ST_EMF_CONTROL_T* pEMF, ST_PMSM_ELEC_T* pPMSMe)
{
    pEMF->FL_EMF_Ialfa_err.I_Q14I_LPF_In = pPMSMe->V_Q14I_Ialfa - pEMF->V_Q14I_EMF_Ialfa_Last;
    pEMF->FL_EMF_Ibeta_err.I_Q14I_LPF_In = pPMSMe->V_Q14I_Ibeta - pEMF->V_Q14I_EMF_Ibeta_Last;
    
    LPF_Cal_T(&pEMF->FL_EMF_Ialfa_err);
    LPF_Cal_T(&pEMF->FL_EMF_Ibeta_err);
    
    pEMF->O_Q14I_EMF_Ealfa = pPMSMe->V_Q14I_Ualfa
                            - Q32I_RHT_14(pEMF->D_Q14I_EMF_Rs*pPMSMe->V_Q14I_Ialfa)
                            - Q32I_RHT_10(pEMF->D_Q10I_EMF_Ls_Over_Ts*pEMF->FL_EMF_Ialfa_err.O_Q14I_LPF_Out);
    pEMF->O_Q14I_EMF_Ebeta = pPMSMe->V_Q14I_Ubeta
                            - Q32I_RHT_14(pEMF->D_Q14I_EMF_Rs*pPMSMe->V_Q14I_Ibeta)
                            - Q32I_RHT_10(pEMF->D_Q10I_EMF_Ls_Over_Ts*pEMF->FL_EMF_Ibeta_err.O_Q14I_LPF_Out);
    
    pEMF->V_Q14I_EMF_Ialfa_Last = pPMSMe->V_Q14I_Ialfa;
    pEMF->V_Q14I_EMF_Ibeta_Last = pPMSMe->V_Q14I_Ibeta;
}


/**********************************滑模观测器************************************/
void MCFOC_EST_SMO_Init_T(ST_SMO_CONTROL_T* pSMO)
{
    PID_Pos_Init_T(&pSMO->PID_SMO_PLL, 0);
    LPF_Init_T(&pSMO->FL_SMO_FREQ, 0);
    pSMO->TG_SMO_Triangle.Q14U_Angle = 0;
    pSMO->TG_SMO_Triangle.Q14I_Cos = 16384;
    pSMO->TG_SMO_Triangle.Q14I_Sin = 0;
    pSMO->TG_SMO_Triangle.Q14U_ReAngle = 0;
    
    pSMO->V_Q28I_SMO_Angle_tmp = 0;
    pSMO->V_Q28I_SMO_Aalfa = 0;
    pSMO->V_Q28I_SMO_Abeta = 0;
}

void MCFOC_EST_SMO_Adapt_T(ST_SMO_CONTROL_T* pSMO, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa)
{
    Q32I_ Q14I_Freq_tmp = 0;
    Q14I_Freq_tmp = MATH_ABS_T(pPMSMe->O_Q14I_Freq);
    Q32I_ Q14I_Is_tmp = 0;
    Q14I_Is_tmp = MATH_ABS_T(pPMSMe->O_Q14I_Is);
    
    pSMO->D_Q14I_SMO_H1_Set = Q32I_RHT_14(pSMO->P_Q14I_SMO_H1*TABLE_1D_Inter_T(&pSMO->TAB_SMO_H1_Coeff, Q14I_Freq_tmp));
    pSMO->PID_SMO_PLL.P_Q14I_Kp = Q32I_RHT_14(pSMO->P_Q14I_SMO_PLL_Kp*TABLE_1D_Inter_T(&pSMO->TAB_SMO_Kp_Coeff, Q14I_Freq_tmp));
    pSMO->PID_SMO_PLL.P_Q14I_Ki = Q32I_RHT_14(pSMO->P_Q14I_SMO_PLL_Ki*TABLE_1D_Inter_T(&pSMO->TAB_SMO_Ki_Coeff, Q14I_Freq_tmp));
    pSMO->TG_SMO_Triangle_Comp.Q14U_Angle = TABLE_2D_Inter_T(&pSMO->TAB_SMO_Angle_Comp, Q14I_Freq_tmp, Q14I_Is_tmp);
    MATH_ANGLE_MOD_T(pSMO->TG_SMO_Triangle_Comp.Q14U_Angle);
    Math_SinCos_T(&pSMO->TG_SMO_Triangle_Comp);
    
    pSMO->D_Q14I_SMO_Ts = pPMSMa->O_Q14I_Ts;
    pSMO->D_Q10I_SMO_One_Over_Ld = Q24U_MAX_T/pPMSMa->O_Q14I_Ld;
    pSMO->D_Q10I_SMO_Rs_Over_Ld = Q16I_LFT_10(pPMSMa->O_Q14I_Rs)/pPMSMa->O_Q14I_Ld;
    pSMO->D_Q14I_SMO_Ld_Lq_Over_Ld = Q16I_LFT_14(pPMSMa->O_Q14I_Ld - pPMSMa->O_Q14I_Lq)/pPMSMa->O_Q14I_Ld;
}

void MCFOC_EST_SMO_Cal_T(ST_SMO_CONTROL_T* pSMO, ST_PMSM_ELEC_T* pPMSMe)
{
    pSMO->V_Q28I_SMO_Aalfa += pSMO->D_Q14I_SMO_Ts*Q32I_RHT_10(
                          - pSMO->D_Q10I_SMO_Rs_Over_Ld*pSMO->V_Q14I_SMO_Aalfa
                          - Q32I_RHT_06(Q32I_RHT_12(pSMO->D_Q14I_SMO_Ld_Lq_Over_Ld*pSMO->V_Q14I_SMO_Abeta)*pSMO->FL_SMO_FREQ.I_Q14I_LPF_In)
                          + pSMO->D_Q10I_SMO_One_Over_Ld*pPMSMe->V_Q14I_Ualfa
                          - pSMO->D_Q10I_SMO_One_Over_Ld*pSMO->V_Q14I_SMO_Ealfa);
    pSMO->V_Q28I_SMO_Abeta += pSMO->D_Q14I_SMO_Ts*Q32I_RHT_10(
                          - pSMO->D_Q10I_SMO_Rs_Over_Ld*pSMO->V_Q14I_SMO_Abeta
                          + Q32I_RHT_06(Q32I_RHT_12(pSMO->D_Q14I_SMO_Ld_Lq_Over_Ld*pSMO->V_Q14I_SMO_Aalfa)*pSMO->FL_SMO_FREQ.I_Q14I_LPF_In)
                          + pSMO->D_Q10I_SMO_One_Over_Ld*pPMSMe->V_Q14I_Ubeta
                          - pSMO->D_Q10I_SMO_One_Over_Ld*pSMO->V_Q14I_SMO_Ebeta);
    
    pSMO->V_Q28I_SMO_Aalfa = MATH_SAT_T(pSMO->V_Q28I_SMO_Aalfa, 1073741824, -1073741824);
    pSMO->V_Q28I_SMO_Abeta = MATH_SAT_T(pSMO->V_Q28I_SMO_Abeta, 1073741824, -1073741824);
    
    pSMO->V_Q14I_SMO_Aalfa = Q32I_RHT_14(pSMO->V_Q28I_SMO_Aalfa);
    pSMO->V_Q14I_SMO_Abeta = Q32I_RHT_14(pSMO->V_Q28I_SMO_Abeta);
    
    pSMO->V_Q14I_SMO_Ealfa = Q32I_RHT_14(pSMO->D_Q14I_SMO_H1_Set*(pSMO->V_Q14I_SMO_Aalfa - pPMSMe->V_Q14I_Ialfa));
    pSMO->V_Q14I_SMO_Ebeta = Q32I_RHT_14(pSMO->D_Q14I_SMO_H1_Set*(pSMO->V_Q14I_SMO_Abeta - pPMSMe->V_Q14I_Ibeta));
    
    pSMO->PID_SMO_PLL.I_Q14I_Rf = -Q32I_RHT_14(pPMSMe->I_Q00I_DIR_Target*pSMO->V_Q14I_SMO_Ealfa*pSMO->TG_SMO_Triangle.Q14I_Cos);
    pSMO->PID_SMO_PLL.I_Q14I_Fb =  Q32I_RHT_14(pPMSMe->I_Q00I_DIR_Target*pSMO->V_Q14I_SMO_Ebeta*pSMO->TG_SMO_Triangle.Q14I_Sin);
    PID_Pos_Cal_T(&pSMO->PID_SMO_PLL);
    
    pSMO->FL_SMO_FREQ.I_Q14I_LPF_In = pSMO->PID_SMO_PLL.O_Q14I_Output;
    LPF_Cal_T(&pSMO->FL_SMO_FREQ);
    
    pSMO->V_Q28I_SMO_Angle_tmp += pSMO->D_Q14I_SMO_Ts*pSMO->FL_SMO_FREQ.I_Q14I_LPF_In;
    MATH_ANGLE_TMP_T(pSMO->V_Q28I_SMO_Angle_tmp);
    pSMO->TG_SMO_Triangle.Q14U_Angle = Q32I_RHT_14(pSMO->V_Q28I_SMO_Angle_tmp);
    Math_SinCos_T(&pSMO->TG_SMO_Triangle);
}


/**********************************磁链观测器************************************/
void MCFOC_EST_FLUX_Init_T(ST_FLUX_CONTROL_T* pFLUX)
{
    PID_Pos_Init_T(&pFLUX->PID_FLUX_PLL, 0);
    LPF_Init_T(&pFLUX->FL_FLUX_FREQ, 0);

    pFLUX->TG_FLUX_Triangle.Q14U_Angle = 0;
    pFLUX->TG_FLUX_Triangle.Q14I_Cos = 16384;
    pFLUX->TG_FLUX_Triangle.Q14I_Sin = 0;
    pFLUX->TG_FLUX_Triangle.Q14U_ReAngle = 0;
    
    pFLUX->V_Q28I_FLUX_Angle_tmp = 0;
    pFLUX->V_Q28I_FLUX_Xalfa = pFLUX->D_Q14I_FLUX_Flux;
    pFLUX->V_Q28I_FLUX_Xbeta = 0;
}

void MCFOC_EST_FLUX_Adapt_T(ST_FLUX_CONTROL_T* pFLUX, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa)
{
    Q32I_ Q14I_Freq_tmp = 0;
    Q14I_Freq_tmp = MATH_ABS_T(pPMSMe->O_Q14I_Freq);
    Q32I_ Q14I_Is_tmp = 0;
    Q14I_Is_tmp = MATH_ABS_T(pPMSMe->O_Q14I_Is);
    
    pFLUX->D_Q14I_FLUX_Gamma_Set = Q32I_RHT_14(pFLUX->P_Q14I_FLUX_Gamma*TABLE_1D_Inter_T(&pFLUX->TAB_FLUX_Gamma_Coeff, Q14I_Freq_tmp));
    pFLUX->PID_FLUX_PLL.P_Q14I_Kp = Q32I_RHT_14(pFLUX->P_Q14I_FLUX_PLL_Kp*TABLE_1D_Inter_T(&pFLUX->TAB_FLUX_Kp_Coeff, Q14I_Freq_tmp));
    pFLUX->PID_FLUX_PLL.P_Q14I_Ki = Q32I_RHT_14(pFLUX->P_Q14I_FLUX_PLL_Ki*TABLE_1D_Inter_T(&pFLUX->TAB_FLUX_Ki_Coeff, Q14I_Freq_tmp));
    pFLUX->TG_FLUX_Triangle_Comp.Q14U_Angle = TABLE_2D_Inter_T(&pFLUX->TAB_FLUX_Angle_Comp, Q14I_Freq_tmp, Q14I_Is_tmp);
    MATH_ANGLE_MOD_T(pFLUX->TG_FLUX_Triangle_Comp.Q14U_Angle);
    Math_SinCos_T(&pFLUX->TG_FLUX_Triangle_Comp);
    
    pFLUX->D_Q14I_FLUX_Ts = pPMSMa->O_Q14I_Ts;
    pFLUX->D_Q14I_FLUX_Ld = pPMSMa->O_Q14I_Ld;
    pFLUX->D_Q14I_FLUX_Lq = pPMSMa->O_Q14I_Lq;
    pFLUX->D_Q14I_FLUX_Flux = pPMSMa->O_Q14I_Flux;
}

void MCFOC_EST_FLUX_Cal_T(ST_FLUX_CONTROL_T* pFLUX, ST_PMSM_ELEC_T* pPMSMe)
{
    Q32I_ Q14I_Id = 0, Q14I_Iq = 0;
    Q32I_ Q28I_Fluxalfa = 0, Q28I_Fluxbeta = 0;
    
    Q14I_Id =   Q32I_RHT_14(pPMSMe->V_Q14I_Ialfa*pFLUX->TG_FLUX_Triangle.Q14I_Cos
                          + pPMSMe->V_Q14I_Ibeta*pFLUX->TG_FLUX_Triangle.Q14I_Sin);
    Q14I_Iq = - Q32I_RHT_14(pPMSMe->V_Q14I_Ialfa*pFLUX->TG_FLUX_Triangle.Q14I_Sin
                          + pPMSMe->V_Q14I_Ibeta*pFLUX->TG_FLUX_Triangle.Q14I_Cos);
    
    Q14I_Id = Q32I_RHT_14(Q14I_Id*pFLUX->D_Q14I_FLUX_Ld) + pFLUX->D_Q14I_FLUX_Flux;
    Q14I_Iq = Q32I_RHT_14(Q14I_Iq*pFLUX->D_Q14I_FLUX_Lq);
    
    Q28I_Fluxalfa = Q14I_Id*pFLUX->TG_FLUX_Triangle.Q14I_Cos
                  - Q14I_Iq*pFLUX->TG_FLUX_Triangle.Q14I_Sin;
    Q28I_Fluxbeta = Q14I_Id*pFLUX->TG_FLUX_Triangle.Q14I_Sin
                  + Q14I_Iq*pFLUX->TG_FLUX_Triangle.Q14I_Cos;
    
    pFLUX->V_Q28I_FLUX_Xalfa += pFLUX->D_Q14I_FLUX_Ts*(pPMSMe->V_Q14I_Ualfa
                               + Q32I_RHT_14(pFLUX->D_Q14I_FLUX_Gamma_Set*Q32I_RHT_14(Q28I_Fluxalfa - pFLUX->V_Q28I_FLUX_Xalfa)));
    pFLUX->V_Q28I_FLUX_Xbeta += pFLUX->D_Q14I_FLUX_Ts*(pPMSMe->V_Q14I_Ubeta
                               + Q32I_RHT_14(pFLUX->D_Q14I_FLUX_Gamma_Set*Q32I_RHT_14(Q28I_Fluxbeta - pFLUX->V_Q28I_FLUX_Xbeta)));
    
    pFLUX->V_Q28I_FLUX_Xalfa = MATH_SAT_T(pFLUX->V_Q28I_FLUX_Xalfa, 1073741824, -1073741824);
    pFLUX->V_Q28I_FLUX_Xbeta = MATH_SAT_T(pFLUX->V_Q28I_FLUX_Xbeta, 1073741824, -1073741824);
    
    pFLUX->PID_FLUX_PLL.I_Q14I_Rf = Q32I_RHT_14(Q32I_RHT_14(pFLUX->V_Q28I_FLUX_Xbeta - pFLUX->D_Q14I_FLUX_Lq*pPMSMe->V_Q14I_Ibeta)
                        * pFLUX->TG_FLUX_Triangle.Q14I_Cos);
    pFLUX->PID_FLUX_PLL.I_Q14I_Fb = Q32I_RHT_14(Q32I_RHT_14(pFLUX->V_Q28I_FLUX_Xalfa - pFLUX->D_Q14I_FLUX_Lq*pPMSMe->V_Q14I_Ialfa)
                        * pFLUX->TG_FLUX_Triangle.Q14I_Sin);
    PID_Pos_Cal_T(&pFLUX->PID_FLUX_PLL);
    
    pFLUX->FL_FLUX_FREQ.I_Q14I_LPF_In = pFLUX->PID_FLUX_PLL.O_Q14I_Output;
    LPF_Cal_T(&pFLUX->FL_FLUX_FREQ);
    
    pFLUX->V_Q28I_FLUX_Angle_tmp += pFLUX->D_Q14I_FLUX_Ts*pFLUX->FL_FLUX_FREQ.I_Q14I_LPF_In;
    MATH_ANGLE_TMP_T(pFLUX->V_Q28I_FLUX_Angle_tmp);
    pFLUX->TG_FLUX_Triangle.Q14U_Angle = Q32I_RHT_14(pFLUX->V_Q28I_FLUX_Angle_tmp);
    Math_SinCos_T(&pFLUX->TG_FLUX_Triangle);
}
