/**************************************************************************************************
*     File Name :                        MCFOC_PMSM_F.c
*     Library/Module Name :              MCFOC_F
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC电机参数源文件
**************************************************************************************************/

#include "MCFOC_PMSM_F.h"


/**********************************************************************************************
Function: MCFOC_PMSM_Para_Init_F
Description: PMSM电信号指针
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_PMSM_Para_Init_F(ST_PMSM_ELEC_F* pPMSMe)
{
    pPMSMe->TG_Triangle_Comp.F_Angle = 0.0f;
    pPMSMe->TG_Triangle_Comp.F_Cos = 1.0f;
    pPMSMe->TG_Triangle_Comp.F_Sin = 0.0f;
    pPMSMe->TG_Triangle_Comp.F_ReAngle = 0.0f;
}

/**********************************************************************************************
Function: MCFOC_PMSM_Para_Adapt_F
Description: 电机参数自适应
Input: 无
Output: 无
Input_Output: PMSM信号滤波指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_PMSM_Para_Adapt_F(ST_PMSM_FILTER_F* pPMSMf, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa)
{
    float F_UsMax_tmp = 0.0f;
    
    pPMSMe->_O_F_Freq = pPMSMf->Mean_Freq.F_MEAN_Out;
    pPMSMe->_O_F_Vbus = pPMSMf->Mean_Vbus.F_MEAN_Out;
    pPMSMe->_O_F_Is = MATH_SQADD_F(pPMSMf->Mean_Id.F_MEAN_Out, pPMSMf->Mean_Iq.F_MEAN_Out);
    pPMSMe->_O_F_Us = MATH_SQADD_F(pPMSMf->Mean_Ud.F_MEAN_Out, pPMSMf->Mean_Uq.F_MEAN_Out);
    pPMSMe->_O_F_Es = pPMSMf->Mean_Es.F_MEAN_Out;
    
    F_UsMax_tmp = pPMSMe->_O_F_Vbus*pPMSMe->_P_F_Modulation_Mode;
    if(F_UsMax_tmp != 0.0f)
    {
        pPMSMe->_O_F_One_Over_Vbus = 1.0f/pPMSMe->_O_F_Vbus;
        pPMSMe->_O_F_Modulation_Rate = pPMSMe->_O_F_Us/F_UsMax_tmp;
    }
    pPMSMe->_O_F_UsRef = F_UsMax_tmp*pPMSMe->_P_F_UsRef_Scale;
    
    pPMSMf->Mean_Ibus_10ms.F_MEAN_In = pPMSMf->Mean_Ibus.F_MEAN_Out;
    pPMSMf->Mean_Is_1000ms.F_MEAN_In = pPMSMe->_O_F_Is;
    MEAN_Cal_F(&pPMSMf->Mean_Ibus_10ms);
    MEAN_Cal_F(&pPMSMf->Mean_Is_1000ms);
    
    pPMSMe->_O_F_Ibus_10ms = pPMSMf->Mean_Ibus_10ms.F_MEAN_Out;
    pPMSMe->_O_F_Is_1000ms = pPMSMf->Mean_Is_1000ms.F_MEAN_Out;

    pPMSMa->PWM_FREQ_CHECK.Check_Flag.bit.Enable = 1U;
    pPMSMa->PWM_FREQ_CHECK.Check_Flag.bit.Condition_Set = (pPMSMe->_O_F_Freq <= pPMSMa->PWM_FREQ_CHECK._P_F_Check_TL);
    pPMSMa->PWM_FREQ_CHECK.Check_Flag.bit.Condition_Clear = (pPMSMe->_O_F_Freq >= pPMSMa->PWM_FREQ_CHECK._P_F_Clear_TL);
    pPMSMa->_O_Q32U_Low_PWM_Flag = Check_Cal(&pPMSMa->PWM_FREQ_CHECK, pPMSMa->_O_Q32U_Low_PWM_Flag);

    if(pPMSMa->_O_Q32U_Low_PWM_Flag)
    {
        pPMSMa->Ramp_PWM_FREQ.F_Target = pPMSMa->_P_F_PWM_FREQ_MIN;
    }
    else
    {
        pPMSMa->Ramp_PWM_FREQ.F_Target = pPMSMa->_P_F_PWM_FREQ_MAX;
    }
    Ramp_Cal_F(&pPMSMa->Ramp_PWM_FREQ);
    pPMSMa->_O_F_PWM_Freq_Coeff = pPMSMa->Ramp_PWM_FREQ.F_Output/pPMSMa->_P_F_PWM_FREQ_MAX;
    pPMSMa->_O_F_PWM_Period_Coeff = 1.0f/pPMSMa->_O_F_PWM_Freq_Coeff;
    

    pPMSMa->_O_F_Rs = pPMSMa->_P_F_Rs;
    pPMSMa->_O_F_Ld = pPMSMa->_P_F_Ld;
    pPMSMa->_O_F_Lq = pPMSMa->_P_F_Lq*TABLE_1D_Inter_F(&pPMSMa->TAB_Lq_Coeff, pPMSMe->_O_F_Is_1000ms);
    pPMSMa->_O_F_Ls = pPMSMa->_P_F_Ls;
    pPMSMa->_O_F_Flux = pPMSMa->_P_F_Flux;
    pPMSMa->_O_F_Ts = pPMSMa->_P_F_Ts*pPMSMa->_O_F_PWM_Period_Coeff;
    
    pPMSMe->TG_Triangle_Pre.F_Angle = pPMSMe->_P_F_Pre_Period*pPMSMe->_O_F_Freq*pPMSMa->_O_F_Ts;
    MATH_ANGLE_MOD_F(pPMSMe->TG_Triangle_Pre.F_Angle);
    Math_SinCos_F(&pPMSMe->TG_Triangle_Pre);
}


/*********************************坐标变换*************************************/

/**********************************************************************************************
Function: MCFOC_Clark_F
Description: Clark坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Clark_F(ST_PMSM_ELEC_F* pPMSMe)
{
    pPMSMe->_V_F_Ialfa = pPMSMe->_V_F_Ia;
    pPMSMe->_V_F_Ibeta = MATH_ONE_OVER_SQRT_THREE_F*(pPMSMe->_V_F_Ib - pPMSMe->_V_F_Ic);
}

/**********************************************************************************************
Function: MCFOC_Park_F
Description: Park坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Park_F(ST_PMSM_ELEC_F* pPMSMe)
{
    pPMSMe->_V_F_Sin_Real = pPMSMe->TG_Triangle_Est.F_Sin*pPMSMe->TG_Triangle_Comp.F_Cos
                          + pPMSMe->TG_Triangle_Est.F_Cos*pPMSMe->TG_Triangle_Comp.F_Sin;
    pPMSMe->_V_F_Cos_Real = pPMSMe->TG_Triangle_Est.F_Cos*pPMSMe->TG_Triangle_Comp.F_Cos
                          - pPMSMe->TG_Triangle_Est.F_Sin*pPMSMe->TG_Triangle_Comp.F_Sin;
    
    pPMSMe->_V_F_Id_Real =   pPMSMe->_V_F_Ialfa*pPMSMe->_V_F_Cos_Real
                           + pPMSMe->_V_F_Ibeta*pPMSMe->_V_F_Sin_Real;
    pPMSMe->_V_F_Iq_Real = - pPMSMe->_V_F_Ialfa*pPMSMe->_V_F_Sin_Real
                           + pPMSMe->_V_F_Ibeta*pPMSMe->_V_F_Cos_Real;
}

/**********************************************************************************************
Function: MCFOC_Ipark_F
Description: Ipark坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Ipark_F(ST_PMSM_ELEC_F* pPMSMe)
{
    pPMSMe->_V_F_Sin_Pre = pPMSMe->_V_F_Sin_Real*pPMSMe->TG_Triangle_Pre.F_Cos
                         + pPMSMe->_V_F_Cos_Real*pPMSMe->TG_Triangle_Pre.F_Sin;
    pPMSMe->_V_F_Cos_Pre = pPMSMe->_V_F_Cos_Real*pPMSMe->TG_Triangle_Pre.F_Cos
                         - pPMSMe->_V_F_Sin_Real*pPMSMe->TG_Triangle_Pre.F_Sin;
    
    pPMSMe->_V_F_Ualfa_Pre = pPMSMe->_V_F_Ud_Real*pPMSMe->_V_F_Cos_Pre
                           - pPMSMe->_V_F_Uq_Real*pPMSMe->_V_F_Sin_Pre;
    pPMSMe->_V_F_Ubeta_Pre = pPMSMe->_V_F_Ud_Real*pPMSMe->_V_F_Sin_Pre
                           + pPMSMe->_V_F_Uq_Real*pPMSMe->_V_F_Cos_Pre;
}

/**********************************************************************************************
Function: MCFOC_Iclark_F
Description: IClark坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Iclark_F(ST_PMSM_ELEC_F* pPMSMe)
{
    float F_Ialfa_Pre = 0.0f, F_Ibeta_Pre = 0.0f;
     
    F_Ialfa_Pre = pPMSMe->_V_F_Id_Real*pPMSMe->_V_F_Cos_Pre
                - pPMSMe->_V_F_Iq_Real*pPMSMe->_V_F_Sin_Pre;
    F_Ibeta_Pre = pPMSMe->_V_F_Id_Real*pPMSMe->_V_F_Sin_Pre
                + pPMSMe->_V_F_Iq_Real*pPMSMe->_V_F_Cos_Pre;
    
    pPMSMe->_V_F_Ia_Pre = F_Ialfa_Pre;
    pPMSMe->_V_F_Ib_Pre = 0.5f*( - F_Ialfa_Pre + MATH_SQRT_THREE_F*F_Ibeta_Pre);
    pPMSMe->_V_F_Ic_Pre = 0.5f*( - F_Ialfa_Pre - MATH_SQRT_THREE_F*F_Ibeta_Pre);
}
