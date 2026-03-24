/**************************************************************************************************
*     File Name :                        MCFOC_PMSM_T.c
*     Library/Module Name :              MCFOC_PMSM_T
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC电机参数源文件
**************************************************************************************************/

#include "MCFOC_PMSM_T.h"


/**********************************************************************************************
Function: MCFOC_PMSM_Para_Init_T
Description: PMSM电信号指针
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_PMSM_Para_Init_T(ST_PMSM_ELEC_T* pPMSMe)
{
    pPMSMe->TG_Triangle_Comp.Q14U_Angle = 0;
    pPMSMe->TG_Triangle_Comp.Q14I_Cos = 16384;
    pPMSMe->TG_Triangle_Comp.Q14I_Sin = 0;
    pPMSMe->TG_Triangle_Comp.Q14U_ReAngle = 0;
}

/**********************************************************************************************
Function: MCFOC_PMSM_Para_Adapt_T
Description: 电机参数自适应
Input: 无
Output: 无
Input_Output: PMSM信号滤波指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_PMSM_Para_Adapt_T(ST_PMSM_FILTER_T* pPMSMf, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa)
{
    Q32I_ Q14I_UsMax_tmp = 0.0f;
    
    pPMSMe->_O_Q14I_Freq = pPMSMf->Mean_Freq.Q14I_MEAN_Out;
    pPMSMe->_O_Q14I_Vbus = pPMSMf->Mean_Vbus.Q14I_MEAN_Out;
    pPMSMe->_O_Q14I_Is = MATH_SQADD_T(pPMSMf->Mean_Id.Q14I_MEAN_Out, pPMSMf->Mean_Iq.Q14I_MEAN_Out);
    pPMSMe->_O_Q14I_Us = MATH_SQADD_T(pPMSMf->Mean_Ud.Q14I_MEAN_Out, pPMSMf->Mean_Uq.Q14I_MEAN_Out);
    pPMSMe->_O_Q14I_Es = pPMSMf->Mean_Es.Q14I_MEAN_Out;
    
    Q14I_UsMax_tmp = Q32I_RHT_14(pPMSMe->_O_Q14I_Vbus*pPMSMe->_P_Q14I_Modulation_Mode);
    if(Q14I_UsMax_tmp != 0)
    {
        pPMSMe->_O_Q14I_One_Over_Vbus = 268435456/pPMSMe->_O_Q14I_Vbus;
        pPMSMe->_O_Q14I_Modulation_Rate = Q16I_LFT_14(pPMSMe->_O_Q14I_Us)/Q14I_UsMax_tmp;
    }
    pPMSMe->_O_Q14I_UsRef = Q32I_RHT_14(Q14I_UsMax_tmp*pPMSMe->_P_Q14I_UsRef_Scale);
    
    pPMSMf->Mean_Ibus_10ms.Q14I_MEAN_In = pPMSMf->Mean_Ibus.Q14I_MEAN_Out;
    pPMSMf->Mean_Is_1000ms.Q14I_MEAN_In = pPMSMe->_O_Q14I_Is;
    MEAN_Cal_T(&pPMSMf->Mean_Ibus_10ms);
    MEAN_Cal_T(&pPMSMf->Mean_Is_1000ms);
    
    pPMSMe->_O_Q14I_Ibus_10ms = pPMSMf->Mean_Ibus_10ms.Q14I_MEAN_Out;
    pPMSMe->_O_Q14I_Is_1000ms = pPMSMf->Mean_Is_1000ms.Q14I_MEAN_Out;

    pPMSMa->PWM_FREQ_CHECK.Check_Flag.bit.Enable = 1U;
    pPMSMa->PWM_FREQ_CHECK.Check_Flag.bit.Condition_Set = (pPMSMe->_O_Q14I_Freq <= pPMSMa->PWM_FREQ_CHECK._P_Q14I_Check_TL);
    pPMSMa->PWM_FREQ_CHECK.Check_Flag.bit.Condition_Clear = (pPMSMe->_O_Q14I_Freq >= pPMSMa->PWM_FREQ_CHECK._P_Q14I_Clear_TL);
    pPMSMa->_O_Q32U_Low_PWM_Flag = Check_Cal(&pPMSMa->PWM_FREQ_CHECK, pPMSMa->_O_Q32U_Low_PWM_Flag);

    if(pPMSMa->_O_Q32U_Low_PWM_Flag)
    {
        pPMSMa->Ramp_PWM_FREQ.Q14I_Target = pPMSMa->_P_Q32U_PWM_FREQ_MIN;
    }
    else
    {
        pPMSMa->Ramp_PWM_FREQ.Q14I_Target = pPMSMa->_P_Q32U_PWM_FREQ_MAX;
    }
    Ramp_Cal_T(&pPMSMa->Ramp_PWM_FREQ);
    pPMSMa->_O_Q14I_PWM_Freq_Coeff = Q16I_LFT_14(pPMSMa->Ramp_PWM_FREQ.Q14I_Output)/pPMSMa->_P_Q32U_PWM_FREQ_MAX;
    pPMSMa->_O_Q14I_PWM_Period_Coeff = 268435456/pPMSMa->_O_Q14I_PWM_Freq_Coeff;
    

    pPMSMa->_O_Q14I_Rs = pPMSMa->_P_Q14I_Rs;
    pPMSMa->_O_Q14I_Ld = pPMSMa->_P_Q14I_Ld;
    pPMSMa->_O_Q14I_Lq = Q32I_RHT_14(pPMSMa->_P_Q14I_Lq*TABLE_1D_Inter_T(&pPMSMa->TAB_Lq_Coeff, pPMSMe->_O_Q14I_Is_1000ms));
    pPMSMa->_O_Q14I_Ls = pPMSMa->_P_Q14I_Ls;
    pPMSMa->_O_Q14I_Flux = pPMSMa->_P_Q14I_Flux;
    pPMSMa->_O_Q14I_Ts = Q32I_RHT_14(pPMSMa->_P_Q14I_Ts*pPMSMa->_O_Q14I_PWM_Period_Coeff);
    
    pPMSMe->TG_Triangle_Pre.Q14U_Angle = Q32I_RHT_08(pPMSMe->_P_Q08U_Pre_Period*Q32I_RHT_14(pPMSMe->_O_Q14I_Freq*pPMSMa->_O_Q14I_Ts));
    MATH_ANGLE_MOD_T(pPMSMe->TG_Triangle_Pre.Q14U_Angle);
    Math_SinCos_T(&pPMSMe->TG_Triangle_Pre);
}


/*********************************坐标变换*************************************/

/**********************************************************************************************
Function: MCFOC_Clark_T
Description: Clark坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Clark_T(ST_PMSM_ELEC_T* pPMSMe)
{
    pPMSMe->_V_Q14I_Ialfa = pPMSMe->_V_Q14I_Ia;
    pPMSMe->_V_Q14I_Ibeta = MATH_ONE_OVER_SQRT_THREE_T(pPMSMe->_V_Q14I_Ib - pPMSMe->_V_Q14I_Ic);
}

/**********************************************************************************************
Function: MCFOC_Park_T
Description: Park坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Park_T(ST_PMSM_ELEC_T* pPMSMe)
{
    pPMSMe->_V_Q14I_Sin_Real = Q32I_RHT_14(pPMSMe->TG_Triangle_Est.Q14I_Sin*pPMSMe->TG_Triangle_Comp.Q14I_Cos
                                         + pPMSMe->TG_Triangle_Est.Q14I_Cos*pPMSMe->TG_Triangle_Comp.Q14I_Sin);
    pPMSMe->_V_Q14I_Cos_Real = Q32I_RHT_14(pPMSMe->TG_Triangle_Est.Q14I_Cos*pPMSMe->TG_Triangle_Comp.Q14I_Cos
                                         - pPMSMe->TG_Triangle_Est.Q14I_Sin*pPMSMe->TG_Triangle_Comp.Q14I_Sin);
    
    pPMSMe->_V_Q14I_Id_Real = Q32I_RHT_14(   pPMSMe->_V_Q14I_Ialfa*pPMSMe->_V_Q14I_Cos_Real
                                           + pPMSMe->_V_Q14I_Ibeta*pPMSMe->_V_Q14I_Sin_Real);
    pPMSMe->_V_Q14I_Iq_Real = Q32I_RHT_14( - pPMSMe->_V_Q14I_Ialfa*pPMSMe->_V_Q14I_Sin_Real
                                           + pPMSMe->_V_Q14I_Ibeta*pPMSMe->_V_Q14I_Cos_Real);
}

/**********************************************************************************************
Function: MCFOC_Ipark_T
Description: Ipark坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Ipark_T(ST_PMSM_ELEC_T* pPMSMe)
{
    pPMSMe->_V_Q14I_Sin_Pre = Q32I_RHT_14(pPMSMe->_V_Q14I_Sin_Real*pPMSMe->TG_Triangle_Pre.Q14I_Cos
                                        + pPMSMe->_V_Q14I_Cos_Real*pPMSMe->TG_Triangle_Pre.Q14I_Sin);
    pPMSMe->_V_Q14I_Cos_Pre = Q32I_RHT_14(pPMSMe->_V_Q14I_Cos_Real*pPMSMe->TG_Triangle_Pre.Q14I_Cos
                                        - pPMSMe->_V_Q14I_Sin_Real*pPMSMe->TG_Triangle_Pre.Q14I_Sin);
    
    pPMSMe->_V_Q14I_Ualfa_Pre = Q32I_RHT_14(pPMSMe->_V_Q14I_Ud_Real*pPMSMe->_V_Q14I_Cos_Pre
                                          - pPMSMe->_V_Q14I_Uq_Real*pPMSMe->_V_Q14I_Sin_Pre);
    pPMSMe->_V_Q14I_Ubeta_Pre = Q32I_RHT_14(pPMSMe->_V_Q14I_Ud_Real*pPMSMe->_V_Q14I_Sin_Pre
                                          + pPMSMe->_V_Q14I_Uq_Real*pPMSMe->_V_Q14I_Cos_Pre);
}

/**********************************************************************************************
Function: MCFOC_Iclark_T
Description: IClark坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Iclark_T(ST_PMSM_ELEC_T* pPMSMe)
{
    Q32I_ Q14I_Ialfa_Pre = 0, Q14I_Ibeta_Pre = 0;
     
    Q14I_Ialfa_Pre = Q32I_RHT_14(pPMSMe->_V_Q14I_Id_Real*pPMSMe->_V_Q14I_Cos_Pre
                               - pPMSMe->_V_Q14I_Iq_Real*pPMSMe->_V_Q14I_Sin_Pre);
    Q14I_Ibeta_Pre = Q32I_RHT_14(pPMSMe->_V_Q14I_Id_Real*pPMSMe->_V_Q14I_Sin_Pre
                               + pPMSMe->_V_Q14I_Iq_Real*pPMSMe->_V_Q14I_Cos_Pre);
    
    pPMSMe->_V_Q14I_Ia_Pre = Q14I_Ialfa_Pre;
    pPMSMe->_V_Q14I_Ib_Pre = Q32I_RHT_15( - Q14I_Ialfa_Pre + MATH_SQRT_THREE_T(Q14I_Ibeta_Pre));
    pPMSMe->_V_Q14I_Ic_Pre = Q32I_RHT_15( - Q14I_Ialfa_Pre - MATH_SQRT_THREE_T(Q14I_Ibeta_Pre));
}
