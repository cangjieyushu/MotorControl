/*
*     File Name :                        mcfoc_pmsm_f
*     Library/Module Name :              mcfoc_f
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC电机参数
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "mcfoc_pmsm_f.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
void MCFOC_PMSM_Para_Init_F(ST_PMSM_ELEC_F* pPMSMe)
{
    pPMSMe->TG_Triangle_Comp.F_Angle = 0.0f;
    pPMSMe->TG_Triangle_Comp.F_Cos = 1.0f;
    pPMSMe->TG_Triangle_Comp.F_Sin = 0.0f;
    pPMSMe->TG_Triangle_Comp.F_ReAngle = 0.0f;
}

void MCFOC_PMSM_Para_Adapt_F(ST_PMSM_FILTER_F* pPMSMf, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa)
{
    float F_UsMax_tmp = 0.0f;
    
    pPMSMe->O_F_Freq = pPMSMf->Mean_Freq.O_F_MEAN_Out;
    pPMSMe->O_F_Vbus = pPMSMf->Mean_Vbus.O_F_MEAN_Out;
    pPMSMe->O_F_Is = MATH_SQRTADD_F(pPMSMf->Mean_Id.O_F_MEAN_Out, pPMSMf->Mean_Iq.O_F_MEAN_Out);
    pPMSMe->O_F_Us = MATH_SQRTADD_F(pPMSMf->Mean_Ud.O_F_MEAN_Out, pPMSMf->Mean_Uq.O_F_MEAN_Out);
    pPMSMe->O_F_Es = pPMSMf->Mean_Es.O_F_MEAN_Out;
    
    F_UsMax_tmp = pPMSMe->O_F_Vbus*pPMSMe->P_F_Modulation_Mode;
    if(F_UsMax_tmp != 0.0f)
    {
        pPMSMe->O_F_One_Over_Vbus = 1.0f/pPMSMe->O_F_Vbus;
        pPMSMe->O_F_Modulation_Rate = pPMSMe->O_F_Us/F_UsMax_tmp;
    }
    pPMSMe->O_F_UsRef = F_UsMax_tmp*pPMSMe->P_F_UsRef_Scale;
    
    pPMSMf->Mean_Ibus_10ms.I_F_MEAN_In = pPMSMf->Mean_Ibus.O_F_MEAN_Out;
    pPMSMf->Mean_Is_1000ms.I_F_MEAN_In = pPMSMe->O_F_Is;
    MEAN_Cal_F(&pPMSMf->Mean_Ibus_10ms);
    MEAN_Cal_F(&pPMSMf->Mean_Is_1000ms);
    
    pPMSMe->O_F_Ibus_10ms = pPMSMf->Mean_Ibus_10ms.O_F_MEAN_Out;
    pPMSMe->O_F_Is_1000ms = pPMSMf->Mean_Is_1000ms.O_F_MEAN_Out;

    pPMSMa->PWM_FREQ_CHECK.Check_Flag.bit.Enable = 1U;
    pPMSMa->PWM_FREQ_CHECK.Check_Flag.bit.Condition_Set = (pPMSMe->O_F_Freq <= pPMSMa->PWM_FREQ_CHECK.P_F_Check_TL);
    pPMSMa->PWM_FREQ_CHECK.Check_Flag.bit.Condition_Clear = (pPMSMe->O_F_Freq >= pPMSMa->PWM_FREQ_CHECK.P_F_Clear_TL);
    pPMSMa->O_Q32U_Low_PWM_Flag = Check_Cal(&pPMSMa->PWM_FREQ_CHECK, pPMSMa->O_Q32U_Low_PWM_Flag);

    if(pPMSMa->O_Q32U_Low_PWM_Flag)
    {
        pPMSMa->Ramp_PWM_FREQ.P_F_Target = pPMSMa->P_F_PWM_FREQ_MIN;
    }
    else
    {
        pPMSMa->Ramp_PWM_FREQ.P_F_Target = pPMSMa->P_F_PWM_FREQ_MAX;
    }
    Ramp_Cal_F(&pPMSMa->Ramp_PWM_FREQ);
    pPMSMa->O_F_PWM_Freq_Coeff = pPMSMa->Ramp_PWM_FREQ.O_F_Output/pPMSMa->P_F_PWM_FREQ_MAX;
    pPMSMa->O_F_PWM_Period_Coeff = 1.0f/pPMSMa->O_F_PWM_Freq_Coeff;
    

    pPMSMa->O_F_Rs = pPMSMa->P_F_Rs;
    pPMSMa->O_F_Ld = pPMSMa->P_F_Ld;
    pPMSMa->O_F_Lq = pPMSMa->P_F_Lq*TABLE_1D_Inter_F(&pPMSMa->TAB_Lq_Coeff, pPMSMe->O_F_Is_1000ms);
    pPMSMa->O_F_Ls = pPMSMa->P_F_Ls;
    pPMSMa->O_F_Flux = pPMSMa->P_F_Flux;
    pPMSMa->O_F_Ts = pPMSMa->P_F_Ts*pPMSMa->O_F_PWM_Period_Coeff;
    
    pPMSMe->TG_Triangle_Pre.F_Angle = pPMSMe->P_F_Pre_Period*pPMSMe->O_F_Freq*pPMSMa->O_F_Ts;
    MATH_ANGLE_MOD_F(pPMSMe->TG_Triangle_Pre.F_Angle);
    Math_SinCos_F(&pPMSMe->TG_Triangle_Pre);
}


/*********************************坐标变换*************************************/
void MCFOC_PMSM_Clark_F(ST_PMSM_ELEC_F* pPMSMe)
{
    pPMSMe->V_F_Ialfa = pPMSMe->V_F_Ia;
    pPMSMe->V_F_Ibeta = MATH_ONE_OVER_SQRT_THREE_F*(pPMSMe->V_F_Ib - pPMSMe->V_F_Ic);
}

void MCFOC_PMSM_Park_F(ST_PMSM_ELEC_F* pPMSMe)
{
    pPMSMe->V_F_Sin_Real = pPMSMe->TG_Triangle_Est.F_Sin*pPMSMe->TG_Triangle_Comp.F_Cos
                          + pPMSMe->TG_Triangle_Est.F_Cos*pPMSMe->TG_Triangle_Comp.F_Sin;
    pPMSMe->V_F_Cos_Real = pPMSMe->TG_Triangle_Est.F_Cos*pPMSMe->TG_Triangle_Comp.F_Cos
                          - pPMSMe->TG_Triangle_Est.F_Sin*pPMSMe->TG_Triangle_Comp.F_Sin;
    
    pPMSMe->V_F_Id_Real =   pPMSMe->V_F_Ialfa*pPMSMe->V_F_Cos_Real
                           + pPMSMe->V_F_Ibeta*pPMSMe->V_F_Sin_Real;
    pPMSMe->V_F_Iq_Real = - pPMSMe->V_F_Ialfa*pPMSMe->V_F_Sin_Real
                           + pPMSMe->V_F_Ibeta*pPMSMe->V_F_Cos_Real;
}

void MCFOC_PMSM_Ipark_F(ST_PMSM_ELEC_F* pPMSMe)
{
    pPMSMe->V_F_Sin_Pre = pPMSMe->V_F_Sin_Real*pPMSMe->TG_Triangle_Pre.F_Cos
                         + pPMSMe->V_F_Cos_Real*pPMSMe->TG_Triangle_Pre.F_Sin;
    pPMSMe->V_F_Cos_Pre = pPMSMe->V_F_Cos_Real*pPMSMe->TG_Triangle_Pre.F_Cos
                         - pPMSMe->V_F_Sin_Real*pPMSMe->TG_Triangle_Pre.F_Sin;
    
    pPMSMe->V_F_Ualfa_Pre = pPMSMe->V_F_Ud_Real*pPMSMe->V_F_Cos_Pre
                           - pPMSMe->V_F_Uq_Real*pPMSMe->V_F_Sin_Pre;
    pPMSMe->V_F_Ubeta_Pre = pPMSMe->V_F_Ud_Real*pPMSMe->V_F_Sin_Pre
                           + pPMSMe->V_F_Uq_Real*pPMSMe->V_F_Cos_Pre;
}

void MCFOC_PMSM_Iclark_F(ST_PMSM_ELEC_F* pPMSMe)
{
    float F_Ialfa_Pre = 0.0f, F_Ibeta_Pre = 0.0f;
     
    F_Ialfa_Pre = pPMSMe->V_F_Id_Real*pPMSMe->V_F_Cos_Pre
                - pPMSMe->V_F_Iq_Real*pPMSMe->V_F_Sin_Pre;
    F_Ibeta_Pre = pPMSMe->V_F_Id_Real*pPMSMe->V_F_Sin_Pre
                + pPMSMe->V_F_Iq_Real*pPMSMe->V_F_Cos_Pre;
    
    pPMSMe->V_F_Ia_Pre = F_Ialfa_Pre;
    pPMSMe->V_F_Ib_Pre = 0.5f*( - F_Ialfa_Pre + MATH_SQRT_THREE_F*F_Ibeta_Pre);
    pPMSMe->V_F_Ic_Pre = 0.5f*( - F_Ialfa_Pre - MATH_SQRT_THREE_F*F_Ibeta_Pre);
}

void MCFOC_PMSM_PQ_F(ST_PMSM_ELEC_F* pPMSMe)
{
    pPMSMe->O_F_Active_Power   = (pPMSMe->V_F_Ualfa*pPMSMe->V_F_Ialfa
                                + pPMSMe->V_F_Ubeta*pPMSMe->V_F_Ibeta)*1.5f;
    pPMSMe->O_F_Reactive_Power = (pPMSMe->V_F_Ubeta*pPMSMe->V_F_Ialfa
                                - pPMSMe->V_F_Ualfa*pPMSMe->V_F_Ibeta)*1.5f;
    
//    pPMSMe->O_F_Active_Power   = (pPMSMe->V_F_Ud_Real*pPMSMe->V_F_Id_Real
//                                + pPMSMe->V_F_Uq_Real*pPMSMe->V_F_Iq_Real)*1.5f;
//    pPMSMe->O_F_Reactive_Power = (pPMSMe->V_F_Uq_Real*pPMSMe->V_F_Id_Real
//                                - pPMSMe->V_F_Ud_Real*pPMSMe->V_F_Iq_Real)*1.5f;
}
