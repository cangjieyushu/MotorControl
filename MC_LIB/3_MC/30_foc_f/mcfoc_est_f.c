/*
*     File Name :                        mcfoc_est_f
*     Library/Module Name :              mcfoc_f
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             速度角度观测器
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "mcfoc_est_f.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/**********************************反电动势观测器************************************/
void MCFOC_EST_EMF_Init_F(ST_EMF_CONTROL_F* pEMF)
{
    LPF_Init_F(&pEMF->FL_EMF_Ialfa_err, 0.0f);
    LPF_Init_F(&pEMF->FL_EMF_Ibeta_err, 0.0f);
    
    pEMF->V_F_EMF_Ialfa_Last = 0.0f;
    pEMF->V_F_EMF_Ibeta_Last = 0.0f;
}

void MCFOC_EST_EMF_Adapt_F(ST_EMF_CONTROL_F* pEMF, ST_PMSM_PARA_F* pPMSMa)
{
    pEMF->D_F_EMF_Rs = pPMSMa->O_F_Rs;
    pEMF->D_F_EMF_Ls_Over_Ts = pPMSMa->O_F_Ls/pPMSMa->O_F_Ts;
}

void MCFOC_EST_EMF_Cal_F(ST_EMF_CONTROL_F* pEMF, ST_PMSM_ELEC_F* pPMSMe)
{
    pEMF->FL_EMF_Ialfa_err.I_F_LPF_In = pPMSMe->V_F_Ialfa - pEMF->V_F_EMF_Ialfa_Last;
    pEMF->FL_EMF_Ibeta_err.I_F_LPF_In = pPMSMe->V_F_Ibeta - pEMF->V_F_EMF_Ibeta_Last;
    
    LPF_Cal_F(&pEMF->FL_EMF_Ialfa_err);
    LPF_Cal_F(&pEMF->FL_EMF_Ibeta_err);
    
    pEMF->O_F_EMF_Ealfa = pPMSMe->V_F_Ualfa
                         - pEMF->D_F_EMF_Rs*pPMSMe->V_F_Ialfa
                         - pEMF->D_F_EMF_Ls_Over_Ts*pEMF->FL_EMF_Ialfa_err.O_F_LPF_Out;
    pEMF->O_F_EMF_Ebeta = pPMSMe->V_F_Ubeta
                         - pEMF->D_F_EMF_Rs*pPMSMe->V_F_Ibeta
                         - pEMF->D_F_EMF_Ls_Over_Ts*pEMF->FL_EMF_Ibeta_err.O_F_LPF_Out;
    
    pEMF->V_F_EMF_Ialfa_Last = pPMSMe->V_F_Ialfa;
    pEMF->V_F_EMF_Ibeta_Last = pPMSMe->V_F_Ibeta;
}


/**********************************滑模观测器************************************/
void MCFOC_EST_SMO_Init_F(ST_SMO_CONTROL_F* pSMO)
{
    PID_Pos_Init_F(&pSMO->PID_SMO_PLL, 0.0f);
    LPF_Init_F(&pSMO->FL_SMO_FREQ, 0.0f);
    pSMO->TG_SMO_Triangle.F_Angle = 0.0f;
    pSMO->TG_SMO_Triangle.F_Cos = 1.0f;
    pSMO->TG_SMO_Triangle.F_Sin = 0.0f;
    pSMO->TG_SMO_Triangle.F_ReAngle = 0.0f;
    
    pSMO->V_F_SMO_Aalfa = 0.0f;
    pSMO->V_F_SMO_Abeta = 0.0f;
}

void MCFOC_EST_SMO_Adapt_F(ST_SMO_CONTROL_F* pSMO, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa)
{
    float F_Freq_tmp = 0.0f;
    F_Freq_tmp = MATH_ABS_F(pPMSMe->O_F_Freq);
    float F_Is_tmp = 0.0f;
    F_Is_tmp = MATH_ABS_F(pPMSMe->O_F_Is);
    
    pSMO->D_F_SMO_H1_Set = pSMO->P_F_SMO_H1*TABLE_1D_Inter_F(&pSMO->TAB_SMO_H1_Coeff, F_Freq_tmp);
    pSMO->PID_SMO_PLL.P_F_Kp = pSMO->P_F_SMO_PLL_Kp*TABLE_1D_Inter_F(&pSMO->TAB_SMO_Kp_Coeff, F_Freq_tmp);
    pSMO->PID_SMO_PLL.P_F_Ki = pSMO->P_F_SMO_PLL_Ki*TABLE_1D_Inter_F(&pSMO->TAB_SMO_Ki_Coeff, F_Freq_tmp);
    pSMO->TG_SMO_Triangle_Comp.F_Angle = TABLE_2D_Inter_F(&pSMO->TAB_SMO_Angle_Comp, F_Freq_tmp, F_Is_tmp);
    MATH_ANGLE_MOD_F(pSMO->TG_SMO_Triangle_Comp.F_Angle);
    Math_SinCos_F(&pSMO->TG_SMO_Triangle_Comp);
    
    pSMO->D_F_SMO_Ts = pPMSMa->O_F_Ts;
    pSMO->D_F_SMO_One_Over_Ld = 1.0f/pPMSMa->O_F_Ld;
    pSMO->D_F_SMO_Rs_Over_Ld = pPMSMa->O_F_Rs/pPMSMa->O_F_Ld;
    pSMO->D_F_SMO_Ld_Lq_Over_Ld = (pPMSMa->O_F_Ld - pPMSMa->O_F_Lq)/pPMSMa->O_F_Ld;
}

void MCFOC_EST_SMO_Cal_F(ST_SMO_CONTROL_F* pSMO, ST_PMSM_ELEC_F* pPMSMe)
{
    pSMO->V_F_SMO_Aalfa += pSMO->D_F_SMO_Ts*(
                          - pSMO->D_F_SMO_Rs_Over_Ld*pSMO->V_F_SMO_Aalfa
                          - pSMO->D_F_SMO_Ld_Lq_Over_Ld*pSMO->FL_SMO_FREQ.I_F_LPF_In*pSMO->V_F_SMO_Abeta
                          + pSMO->D_F_SMO_One_Over_Ld*pPMSMe->V_F_Ualfa
                          - pSMO->D_F_SMO_One_Over_Ld*pSMO->V_F_SMO_Ealfa);
    pSMO->V_F_SMO_Abeta += pSMO->D_F_SMO_Ts*(
                          - pSMO->D_F_SMO_Rs_Over_Ld*pSMO->V_F_SMO_Abeta
                          + pSMO->D_F_SMO_Ld_Lq_Over_Ld*pSMO->FL_SMO_FREQ.I_F_LPF_In*pSMO->V_F_SMO_Aalfa
                          + pSMO->D_F_SMO_One_Over_Ld*pPMSMe->V_F_Ubeta
                          - pSMO->D_F_SMO_One_Over_Ld*pSMO->V_F_SMO_Ebeta);
    
    pSMO->V_F_SMO_Ealfa = pSMO->D_F_SMO_H1_Set*(pSMO->V_F_SMO_Aalfa - pPMSMe->V_F_Ialfa);
    pSMO->V_F_SMO_Ebeta = pSMO->D_F_SMO_H1_Set*(pSMO->V_F_SMO_Abeta - pPMSMe->V_F_Ibeta);

    pSMO->PID_SMO_PLL.I_F_Rf = -pPMSMe->I_F_DIR_Target*pSMO->V_F_SMO_Ealfa*pSMO->TG_SMO_Triangle.F_Cos;
    pSMO->PID_SMO_PLL.I_F_Fb =  pPMSMe->I_F_DIR_Target*pSMO->V_F_SMO_Ebeta*pSMO->TG_SMO_Triangle.F_Sin;
    PID_Pos_Cal_F(&pSMO->PID_SMO_PLL);
    
    pSMO->FL_SMO_FREQ.I_F_LPF_In = pSMO->PID_SMO_PLL.O_F_Output;
    LPF_Cal_F(&pSMO->FL_SMO_FREQ);
    
    pSMO->TG_SMO_Triangle.F_Angle += pSMO->D_F_SMO_Ts*pSMO->FL_SMO_FREQ.I_F_LPF_In;
    MATH_ANGLE_MOD_F(pSMO->TG_SMO_Triangle.F_Angle);
    Math_SinCos_F(&pSMO->TG_SMO_Triangle);
}


/**********************************磁链观测器************************************/
void MCFOC_EST_FLUX_Init_F(ST_FLUX_CONTROL_F* pFLUX)
{
    PID_Pos_Init_F(&pFLUX->PID_FLUX_PLL, 0.0f);
    LPF_Init_F(&pFLUX->FL_FLUX_FREQ, 0.0f);

    pFLUX->TG_FLUX_Triangle.F_Angle = 0.0f;
    pFLUX->TG_FLUX_Triangle.F_Cos = 1.0f;
    pFLUX->TG_FLUX_Triangle.F_Sin = 0.0f;
    pFLUX->TG_FLUX_Triangle.F_ReAngle = 0.0f;
    
    pFLUX->V_F_FLUX_Xalfa = pFLUX->D_F_FLUX_Flux;
    pFLUX->V_F_FLUX_Xbeta = 0.0f;
}

void MCFOC_EST_FLUX_Adapt_F(ST_FLUX_CONTROL_F* pFLUX, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa)
{
    float F_Freq_tmp = 0.0f;
    F_Freq_tmp = MATH_ABS_F(pPMSMe->O_F_Freq);
    float F_Is_tmp = 0.0f;
    F_Is_tmp = MATH_ABS_F(pPMSMe->O_F_Is);
    
    pFLUX->D_F_FLUX_Gamma_Set = pFLUX->P_F_FLUX_Gamma*TABLE_1D_Inter_F(&pFLUX->TAB_FLUX_Gamma_Coeff, F_Freq_tmp);
    pFLUX->PID_FLUX_PLL.P_F_Kp = pFLUX->P_F_FLUX_PLL_Kp*TABLE_1D_Inter_F(&pFLUX->TAB_FLUX_Kp_Coeff, F_Freq_tmp);
    pFLUX->PID_FLUX_PLL.P_F_Ki = pFLUX->P_F_FLUX_PLL_Ki*TABLE_1D_Inter_F(&pFLUX->TAB_FLUX_Ki_Coeff, F_Freq_tmp);
    pFLUX->TG_FLUX_Triangle_Comp.F_Angle = TABLE_2D_Inter_F(&pFLUX->TAB_FLUX_Angle_Comp, F_Freq_tmp, F_Is_tmp);
    MATH_ANGLE_MOD_F(pFLUX->TG_FLUX_Triangle_Comp.F_Angle);
    Math_SinCos_F(&pFLUX->TG_FLUX_Triangle_Comp);
    
    pFLUX->D_F_FLUX_Ts = pPMSMa->O_F_Ts;
    pFLUX->D_F_FLUX_Ld = pPMSMa->O_F_Ld;
    pFLUX->D_F_FLUX_Lq = pPMSMa->O_F_Lq;
    pFLUX->D_F_FLUX_Flux = pPMSMa->O_F_Flux;
}

void MCFOC_EST_FLUX_Cal_F(ST_FLUX_CONTROL_F* pFLUX, ST_PMSM_ELEC_F* pPMSMe)
{
    float F_Id = 0.0f, F_Iq = 0.0f;
    float F_Fluxalfa = 0.0f, F_Fluxbeta = 0.0f;
    
    F_Id =   pPMSMe->V_F_Ialfa*pFLUX->TG_FLUX_Triangle.F_Cos
           + pPMSMe->V_F_Ibeta*pFLUX->TG_FLUX_Triangle.F_Sin;
    F_Iq = - pPMSMe->V_F_Ialfa*pFLUX->TG_FLUX_Triangle.F_Sin
           + pPMSMe->V_F_Ibeta*pFLUX->TG_FLUX_Triangle.F_Cos;
    
    F_Id = F_Id*pFLUX->D_F_FLUX_Ld + pFLUX->D_F_FLUX_Flux;
    F_Iq = F_Iq*pFLUX->D_F_FLUX_Lq;
    
    F_Fluxalfa = F_Id*pFLUX->TG_FLUX_Triangle.F_Cos
               - F_Iq*pFLUX->TG_FLUX_Triangle.F_Sin;
    F_Fluxbeta = F_Id*pFLUX->TG_FLUX_Triangle.F_Sin
               + F_Iq*pFLUX->TG_FLUX_Triangle.F_Cos;
    
    pFLUX->V_F_FLUX_Xalfa += pFLUX->D_F_FLUX_Ts*(pPMSMe->V_F_Ualfa
                            + pFLUX->D_F_FLUX_Gamma_Set*(F_Fluxalfa - pFLUX->V_F_FLUX_Xalfa));
    pFLUX->V_F_FLUX_Xbeta += pFLUX->D_F_FLUX_Ts*(pPMSMe->V_F_Ubeta
                            + pFLUX->D_F_FLUX_Gamma_Set*(F_Fluxbeta - pFLUX->V_F_FLUX_Xbeta));
    
    pFLUX->PID_FLUX_PLL.I_F_Rf = (pFLUX->V_F_FLUX_Xbeta - pFLUX->D_F_FLUX_Lq*pPMSMe->V_F_Ibeta)
                        * pFLUX->TG_FLUX_Triangle.F_Cos;
    pFLUX->PID_FLUX_PLL.I_F_Fb = (pFLUX->V_F_FLUX_Xalfa - pFLUX->D_F_FLUX_Lq*pPMSMe->V_F_Ialfa)
                        * pFLUX->TG_FLUX_Triangle.F_Sin;
    PID_Pos_Cal_F(&pFLUX->PID_FLUX_PLL);
    
    pFLUX->FL_FLUX_FREQ.I_F_LPF_In = pFLUX->PID_FLUX_PLL.O_F_Output;
    LPF_Cal_F(&pFLUX->FL_FLUX_FREQ);
    
    pFLUX->TG_FLUX_Triangle.F_Angle += pFLUX->D_F_FLUX_Ts*pFLUX->FL_FLUX_FREQ.I_F_LPF_In;
    MATH_ANGLE_MOD_F(pFLUX->TG_FLUX_Triangle.F_Angle);
    Math_SinCos_F(&pFLUX->TG_FLUX_Triangle);
}
