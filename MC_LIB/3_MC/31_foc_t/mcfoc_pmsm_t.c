/*
*     File Name :                        mcfoc_pmsm_t
*     Library/Module Name :              mcfoc_t
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC电机参数
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "mcfoc_pmsm_t.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
void MCFOC_PMSM_Para_Init_T(ST_PMSM_ELEC_T* pPMSMe)
{
    pPMSMe->TG_Triangle_Comp.Q14U_Angle = 0;
    pPMSMe->TG_Triangle_Comp.Q14I_Cos = 16384;
    pPMSMe->TG_Triangle_Comp.Q14I_Sin = 0;
    pPMSMe->TG_Triangle_Comp.Q14U_ReAngle = 0;
}

void MCFOC_PMSM_Para_Adapt_T(ST_PMSM_FILTER_T* pPMSMf, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa)
{
    Q32I_ Q14I_UsMax_tmp = 0.0f;
    
    pPMSMe->O_Q14I_Freq = pPMSMf->Mean_Freq.O_Q14I_MEAN_Out;
    pPMSMe->O_Q14I_Vbus = pPMSMf->Mean_Vbus.O_Q14I_MEAN_Out;
    pPMSMe->O_Q14I_Is = MATH_SQRTADD_T(pPMSMf->Mean_Id.O_Q14I_MEAN_Out, pPMSMf->Mean_Iq.O_Q14I_MEAN_Out);
    pPMSMe->O_Q14I_Us = MATH_SQRTADD_T(pPMSMf->Mean_Ud.O_Q14I_MEAN_Out, pPMSMf->Mean_Uq.O_Q14I_MEAN_Out);
    pPMSMe->O_Q14I_Es = pPMSMf->Mean_Es.O_Q14I_MEAN_Out;
    
    Q14I_UsMax_tmp = Q32I_RHT_14(pPMSMe->O_Q14I_Vbus*pPMSMe->P_Q14I_Modulation_Mode);
    if(Q14I_UsMax_tmp != 0)
    {
        pPMSMe->O_Q14I_One_Over_Vbus = 268435456/pPMSMe->O_Q14I_Vbus;
        pPMSMe->O_Q14I_Modulation_Rate = Q16I_LFT_14(pPMSMe->O_Q14I_Us)/Q14I_UsMax_tmp;
    }
    pPMSMe->O_Q14I_UsRef = Q32I_RHT_14(Q14I_UsMax_tmp*pPMSMe->P_Q14I_UsRef_Scale);
    
    pPMSMf->Mean_Ibus_10ms.I_Q14I_MEAN_In = pPMSMf->Mean_Ibus.O_Q14I_MEAN_Out;
    pPMSMf->Mean_Is_1000ms.I_Q14I_MEAN_In = pPMSMe->O_Q14I_Is;
    MEAN_Cal_T(&pPMSMf->Mean_Ibus_10ms);
    MEAN_Cal_T(&pPMSMf->Mean_Is_1000ms);
    
    pPMSMe->O_Q14I_Ibus_10ms = pPMSMf->Mean_Ibus_10ms.O_Q14I_MEAN_Out;
    pPMSMe->O_Q14I_Is_1000ms = pPMSMf->Mean_Is_1000ms.O_Q14I_MEAN_Out;

    pPMSMa->PWM_FREQ_CHECK.Check_Flag.bit.Enable = 1U;
    pPMSMa->PWM_FREQ_CHECK.Check_Flag.bit.Condition_Set = (pPMSMe->O_Q14I_Freq <= pPMSMa->PWM_FREQ_CHECK.P_Q14I_Check_TL);
    pPMSMa->PWM_FREQ_CHECK.Check_Flag.bit.Condition_Clear = (pPMSMe->O_Q14I_Freq >= pPMSMa->PWM_FREQ_CHECK.P_Q14I_Clear_TL);
    pPMSMa->O_Q32U_Low_PWM_Flag = Check_Cal(&pPMSMa->PWM_FREQ_CHECK, pPMSMa->O_Q32U_Low_PWM_Flag);

    if(pPMSMa->O_Q32U_Low_PWM_Flag)
    {
        pPMSMa->Ramp_PWM_FREQ.P_Q14I_Target = pPMSMa->P_Q32U_PWM_FREQ_MIN;
    }
    else
    {
        pPMSMa->Ramp_PWM_FREQ.P_Q14I_Target = pPMSMa->P_Q32U_PWM_FREQ_MAX;
    }
    Ramp_Cal_T(&pPMSMa->Ramp_PWM_FREQ);
    pPMSMa->O_Q14I_PWM_Freq_Coeff = Q16I_LFT_14(pPMSMa->Ramp_PWM_FREQ.O_Q14I_Output)/pPMSMa->P_Q32U_PWM_FREQ_MAX;
    pPMSMa->O_Q14I_PWM_Period_Coeff = 268435456/pPMSMa->O_Q14I_PWM_Freq_Coeff;
    

    pPMSMa->O_Q14I_Rs = pPMSMa->P_Q14I_Rs;
    pPMSMa->O_Q14I_Ld = pPMSMa->P_Q14I_Ld;
    pPMSMa->O_Q14I_Lq = Q32I_RHT_14(pPMSMa->P_Q14I_Lq*TABLE_1D_Inter_T(&pPMSMa->TAB_Lq_Coeff, pPMSMe->O_Q14I_Is_1000ms));
    pPMSMa->O_Q14I_Ls = pPMSMa->P_Q14I_Ls;
    pPMSMa->O_Q14I_Flux = pPMSMa->P_Q14I_Flux;
    pPMSMa->O_Q14I_Ts = Q32I_RHT_14(pPMSMa->P_Q14I_Ts*pPMSMa->O_Q14I_PWM_Period_Coeff);
    
    pPMSMe->TG_Triangle_Pre.Q14U_Angle = Q32I_RHT_08(pPMSMe->P_Q08U_Pre_Period*Q32I_RHT_14(pPMSMe->O_Q14I_Freq*pPMSMa->O_Q14I_Ts));
    MATH_ANGLE_MOD_T(pPMSMe->TG_Triangle_Pre.Q14U_Angle);
    Math_SinCos_T(&pPMSMe->TG_Triangle_Pre);
}


/*********************************坐标变换*************************************/
void MCFOC_PMSM_Clark_T(ST_PMSM_ELEC_T* pPMSMe)
{
    pPMSMe->V_Q14I_Ialfa = pPMSMe->V_Q14I_Ia;
    pPMSMe->V_Q14I_Ibeta = MATH_ONE_OVER_SQRT_THREE_T(pPMSMe->V_Q14I_Ib - pPMSMe->V_Q14I_Ic);
}

void MCFOC_PMSM_Park_T(ST_PMSM_ELEC_T* pPMSMe)
{
    pPMSMe->V_Q14I_Sin_Real = Q32I_RHT_14(pPMSMe->TG_Triangle_Est.Q14I_Sin*pPMSMe->TG_Triangle_Comp.Q14I_Cos
                                         + pPMSMe->TG_Triangle_Est.Q14I_Cos*pPMSMe->TG_Triangle_Comp.Q14I_Sin);
    pPMSMe->V_Q14I_Cos_Real = Q32I_RHT_14(pPMSMe->TG_Triangle_Est.Q14I_Cos*pPMSMe->TG_Triangle_Comp.Q14I_Cos
                                         - pPMSMe->TG_Triangle_Est.Q14I_Sin*pPMSMe->TG_Triangle_Comp.Q14I_Sin);
    
    pPMSMe->V_Q14I_Id_Real = Q32I_RHT_14(   pPMSMe->V_Q14I_Ialfa*pPMSMe->V_Q14I_Cos_Real
                                           + pPMSMe->V_Q14I_Ibeta*pPMSMe->V_Q14I_Sin_Real);
    pPMSMe->V_Q14I_Iq_Real = Q32I_RHT_14( - pPMSMe->V_Q14I_Ialfa*pPMSMe->V_Q14I_Sin_Real
                                           + pPMSMe->V_Q14I_Ibeta*pPMSMe->V_Q14I_Cos_Real);
}

void MCFOC_PMSM_Ipark_T(ST_PMSM_ELEC_T* pPMSMe)
{
    pPMSMe->V_Q14I_Sin_Pre = Q32I_RHT_14(pPMSMe->V_Q14I_Sin_Real*pPMSMe->TG_Triangle_Pre.Q14I_Cos
                                        + pPMSMe->V_Q14I_Cos_Real*pPMSMe->TG_Triangle_Pre.Q14I_Sin);
    pPMSMe->V_Q14I_Cos_Pre = Q32I_RHT_14(pPMSMe->V_Q14I_Cos_Real*pPMSMe->TG_Triangle_Pre.Q14I_Cos
                                        - pPMSMe->V_Q14I_Sin_Real*pPMSMe->TG_Triangle_Pre.Q14I_Sin);
    
    pPMSMe->V_Q14I_Ualfa_Pre = Q32I_RHT_14(pPMSMe->V_Q14I_Ud_Real*pPMSMe->V_Q14I_Cos_Pre
                                          - pPMSMe->V_Q14I_Uq_Real*pPMSMe->V_Q14I_Sin_Pre);
    pPMSMe->V_Q14I_Ubeta_Pre = Q32I_RHT_14(pPMSMe->V_Q14I_Ud_Real*pPMSMe->V_Q14I_Sin_Pre
                                          + pPMSMe->V_Q14I_Uq_Real*pPMSMe->V_Q14I_Cos_Pre);
}

void MCFOC_PMSM_Iclark_T(ST_PMSM_ELEC_T* pPMSMe)
{
    Q32I_ Q14I_Ialfa_Pre = 0, Q14I_Ibeta_Pre = 0;
     
    Q14I_Ialfa_Pre = Q32I_RHT_14(pPMSMe->V_Q14I_Id_Real*pPMSMe->V_Q14I_Cos_Pre
                               - pPMSMe->V_Q14I_Iq_Real*pPMSMe->V_Q14I_Sin_Pre);
    Q14I_Ibeta_Pre = Q32I_RHT_14(pPMSMe->V_Q14I_Id_Real*pPMSMe->V_Q14I_Sin_Pre
                               + pPMSMe->V_Q14I_Iq_Real*pPMSMe->V_Q14I_Cos_Pre);
    
    pPMSMe->V_Q14I_Ia_Pre = Q14I_Ialfa_Pre;
    pPMSMe->V_Q14I_Ib_Pre = Q32I_RHT_15( - Q14I_Ialfa_Pre + MATH_SQRT_THREE_T(Q14I_Ibeta_Pre));
    pPMSMe->V_Q14I_Ic_Pre = Q32I_RHT_15( - Q14I_Ialfa_Pre - MATH_SQRT_THREE_T(Q14I_Ibeta_Pre));
}
