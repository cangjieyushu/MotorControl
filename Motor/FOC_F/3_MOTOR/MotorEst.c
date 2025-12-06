/**************************************************************************************************
*     File Name :                        MotorEst.c
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             速度角度观测器源文件
**************************************************************************************************/
#include "MotorEst.h"

/**********************************************************************/

/**********************************HFI观测器************************************/

/**********************************************************************************************
Function: Est_HFI_Init_F
Description: HFI观观测器初始化
Input: 无
Output: 无
Input_Output: HFI观观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_HFI_Init_F(ST_HFI_CONTROL_F* pCTRL)
{
    PID_Pos_Init_F(&pCTRL->PID_PLL, 0.0f);
    Filter_Init_F(&pCTRL->FL_SRAD, 0.0f);
    pCTRL->TG_Triangle.F_Angle = 0.0f;
    pCTRL->TG_Triangle.F_Cos = 1.0f;
    pCTRL->TG_Triangle.F_Sin = 0.0f;
    pCTRL->TG_Triangle.F_ReAngle = 0.0f;
    
    pCTRL->_V_Q32U_Pole_Cnt = 0U;
    pCTRL->_V_Q08U_Pole_State = 0U;
    pCTRL->_V_F_Current_pos = 0.0f;
    pCTRL->_V_F_Current_neg = 0.0f;
    
    pCTRL->_V_Q32U_Ud_cnt = 0U;
    pCTRL->_V_Q32U_Ud_Count = (Q32U_)(pCTRL->_P_F_PWM_Freq/pCTRL->_P_F_Ud_Freq/2.0f);
    pCTRL->_V_F_Ud_Sign = 1.0f;
    pCTRL->_V_F_Ialfa_LPF = 0.0f;
    pCTRL->_V_F_Ibeta_LPF = 0.0f;
    pCTRL->_V_F_Ialfa_HPF = 0.0f;
    pCTRL->_V_F_Ibeta_HPF = 0.0f;
    pCTRL->_V_F_Ialfa_Last = 0.0f;
    pCTRL->_V_F_Ibeta_Last = 0.0f;
    pCTRL->_O_F_Ialfa = 0.0f;
    pCTRL->_O_F_Ibeta = 0.0f;
    pCTRL->_O_F_Ud_HFI = 0.0f;
}

/**********************************************************************************************
Function: Est_HFI_F
Description: HFI观测器计算
Input: 无
Output: 无
Input_Output: HFI观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_HFI_F(ST_HFI_CONTROL_F* pCTRL)
{
    pCTRL->_V_Q32U_Ud_cnt++;
    if(pCTRL->_V_Q32U_Ud_cnt == pCTRL->_V_Q32U_Ud_Count)
    {
        pCTRL->_V_Q32U_Ud_cnt = 0U;
        
        pCTRL->_V_F_Ialfa_LPF = 0.5f*(pCTRL->_I_F_Ialfa + pCTRL->_V_F_Ialfa_Last);
        pCTRL->_V_F_Ialfa_HPF = 0.5f*(pCTRL->_I_F_Ialfa - pCTRL->_V_F_Ialfa_Last)*pCTRL->_V_F_Ud_Sign;
        pCTRL->_V_F_Ibeta_LPF = 0.5f*(pCTRL->_I_F_Ibeta + pCTRL->_V_F_Ibeta_Last);
        pCTRL->_V_F_Ibeta_HPF = 0.5f*(pCTRL->_I_F_Ibeta - pCTRL->_V_F_Ibeta_Last)*pCTRL->_V_F_Ud_Sign;
        
        pCTRL->_V_F_Ialfa_Last = pCTRL->_I_F_Ialfa;
        pCTRL->_V_F_Ibeta_Last = pCTRL->_I_F_Ibeta;
        pCTRL->_O_F_Ialfa = pCTRL->_V_F_Ialfa_LPF;
        pCTRL->_O_F_Ibeta = pCTRL->_V_F_Ibeta_LPF;
        
        if(pCTRL->_V_F_Ud_Sign == 1.0f)
        {
            pCTRL->_V_F_Ud_Sign = -1.0f;
        }
        else if(pCTRL->_V_F_Ud_Sign == -1.0f)
        {
            pCTRL->_V_F_Ud_Sign = 1.0f;
        }
    }
    pCTRL->_O_F_Ud_HFI = pCTRL->_V_F_Ud_Sign*pCTRL->_P_F_UdRef;
        
    if(pCTRL->_V_Q08U_Pole_State == 0U)
    {
        if(++pCTRL->_V_Q32U_Pole_Cnt == 160U)
        {
            pCTRL->_V_Q32U_Pole_Cnt = 0U;
            pCTRL->_V_Q08U_Pole_State = 1U;
        }
        
        pCTRL->PID_PLL.F_Rf = pCTRL->_V_F_Ibeta_HPF*pCTRL->TG_Triangle.F_Cos;
        pCTRL->PID_PLL.F_Fb = pCTRL->_V_F_Ialfa_HPF*pCTRL->TG_Triangle.F_Sin;
        PID_Pos_Cal_F(&pCTRL->PID_PLL);
        
        pCTRL->FL_SRAD.F_Filter_in = pCTRL->PID_PLL.F_Output;
    
        Filter_Cal_F(&pCTRL->FL_SRAD);
        
        pCTRL->TG_Triangle.F_Angle += pCTRL->_P_F_Ts*pCTRL->FL_SRAD.F_Filter_in;
        MATH_ANGLE_MOD_F(pCTRL->TG_Triangle.F_Angle);

        Math_SinCos_F(&pCTRL->TG_Triangle);
        
        pCTRL->_O_F_IdRef = 0.0f;
        pCTRL->_O_F_IqRef = 0.0f;
    }
    else if(pCTRL->_V_Q08U_Pole_State == 1U)
    {
        if(++pCTRL->_V_Q32U_Pole_Cnt == 1600U)
        {
            pCTRL->_V_Q32U_Pole_Cnt = 0U;
            pCTRL->_V_Q08U_Pole_State = 2U;
        }
        
        pCTRL->_O_F_IdRef = 0.0f;
        pCTRL->_O_F_IqRef = 0.0f;
    }
    else if(pCTRL->_V_Q08U_Pole_State == 2U)
    {
        if(++pCTRL->_V_Q32U_Pole_Cnt == 16000U)
        {
            pCTRL->_V_Q32U_Pole_Cnt = 0U;
            pCTRL->_V_Q08U_Pole_State = 3U;
        }
        
        pCTRL->_V_F_Current_pos += Math_Sqrt_F(MATH_SQUARE_F(pCTRL->_V_F_Ialfa_HPF) + MATH_SQUARE_F(pCTRL->_V_F_Ibeta_HPF));
        
        pCTRL->_O_F_IdRef = pCTRL->_P_F_IdRef;
        pCTRL->_O_F_IqRef = 0.0f;
    }
    else if(pCTRL->_V_Q08U_Pole_State == 3U)
    {
        if(++pCTRL->_V_Q32U_Pole_Cnt == 160U)
        {
            pCTRL->_V_Q32U_Pole_Cnt = 0U;
            pCTRL->_V_Q08U_Pole_State = 4U;
        }
        
        pCTRL->_O_F_IdRef = 0.0f;
        pCTRL->_O_F_IqRef = 0.0f;
    }
    else if(pCTRL->_V_Q08U_Pole_State == 4U)
    {
        if(++pCTRL->_V_Q32U_Pole_Cnt == 16000U)
        {
            pCTRL->_V_Q32U_Pole_Cnt = 0U;
            pCTRL->_V_Q08U_Pole_State = 5U;
        }
        
        pCTRL->_V_F_Current_neg += Math_Sqrt_F(MATH_SQUARE_F(pCTRL->_V_F_Ialfa_HPF) + MATH_SQUARE_F(pCTRL->_V_F_Ibeta_HPF));
        
        pCTRL->_O_F_IdRef = -pCTRL->_P_F_IdRef;
        pCTRL->_O_F_IqRef = 0.0f;
    }
    else if(pCTRL->_V_Q08U_Pole_State == 5U)
    {
        if(++pCTRL->_V_Q32U_Pole_Cnt == 160U)
        {
            pCTRL->_V_Q32U_Pole_Cnt = 0U;
            pCTRL->_V_Q08U_Pole_State = 6U;
            if(pCTRL->_V_F_Current_neg > pCTRL->_V_F_Current_pos)
            {
                pCTRL->TG_Triangle.F_Angle += 0.5f;
                MATH_ANGLE_MOD_F(pCTRL->TG_Triangle.F_Angle);

                Math_SinCos_F(&pCTRL->TG_Triangle);
            }
        }
        
        pCTRL->_O_F_IdRef = 0.0f;
        pCTRL->_O_F_IqRef = 0.0f;
    }
    else if(pCTRL->_V_Q08U_Pole_State == 6U)
    {
        pCTRL->PID_PLL.F_Rf = pCTRL->_V_F_Ibeta_HPF*pCTRL->TG_Triangle.F_Cos;
        pCTRL->PID_PLL.F_Fb = pCTRL->_V_F_Ialfa_HPF*pCTRL->TG_Triangle.F_Sin;
        PID_Pos_Cal_F(&pCTRL->PID_PLL);
        
        pCTRL->FL_SRAD.F_Filter_in = pCTRL->PID_PLL.F_Output;
        
        Filter_Cal_F(&pCTRL->FL_SRAD);
        
        pCTRL->TG_Triangle.F_Angle += pCTRL->_P_F_Ts*pCTRL->FL_SRAD.F_Filter_in;
        MATH_ANGLE_MOD_F(pCTRL->TG_Triangle.F_Angle);
        
        Math_SinCos_F(&pCTRL->TG_Triangle);
        
        pCTRL->_O_F_IdRef = pCTRL->_P_F_IdRef;
        pCTRL->_O_F_IqRef = pCTRL->_I_F_IqRef;
    }
}

/**********************************磁链观测器************************************/

/**********************************************************************************************
Function: Est_Flux_Init_F
Description: 磁链观测器初始化
Input: 无
Output: 无
Input_Output: 磁链观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Flux_Init_F(ST_FLUX_CONTROL_F* pCTRL)
{
    PID_Pos_Init_F(&pCTRL->PID_PLL, 0.0f);
    Filter_Init_F(&pCTRL->FL_SRAD, 0.0f);
    pCTRL->TG_Triangle.F_Angle = 0.0f;
    pCTRL->TG_Triangle.F_Cos = 1.0f;
    pCTRL->TG_Triangle.F_Sin = 0.0f;
    pCTRL->TG_Triangle.F_ReAngle = 0.0f;
    
    pCTRL->_V_F_Xalfa = pCTRL->_P_F_Flux;
    pCTRL->_V_F_Xbeta = 0.0f;
}

/**********************************************************************************************
Function: Est_Flux_F
Description: 磁链观测器计算
Input: 无
Output: 无
Input_Output: 磁链观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Flux_F(ST_FLUX_CONTROL_F* pCTRL)
{
    pCTRL->_V_F_Yalfa = pCTRL->_I_F_Ualfa - pCTRL->_P_F_Rs*pCTRL->_I_F_Ialfa;
    pCTRL->_V_F_Ybeta = pCTRL->_I_F_Ubeta - pCTRL->_P_F_Rs*pCTRL->_I_F_Ibeta;
    
    pCTRL->_V_F_Nalfa = pCTRL->_V_F_Xalfa - pCTRL->_P_F_Ls*pCTRL->_I_F_Ialfa;
    pCTRL->_V_F_Nbeta = pCTRL->_V_F_Xbeta - pCTRL->_P_F_Ls*pCTRL->_I_F_Ibeta;
    pCTRL->_V_F_Nn2 = MATH_SQUARE_F(pCTRL->_V_F_Nalfa) + MATH_SQUARE_F(pCTRL->_V_F_Nbeta) - MATH_SQUARE_F(pCTRL->_P_F_Ld*pCTRL->_I_F_IdRef);
    
    pCTRL->_V_F_Ealfa = pCTRL->_P_F_Gamma*pCTRL->_V_F_Nalfa*(pCTRL->_P_F_Flux2 - pCTRL->_V_F_Nn2);
    pCTRL->_V_F_Ebeta = pCTRL->_P_F_Gamma*pCTRL->_V_F_Nbeta*(pCTRL->_P_F_Flux2 - pCTRL->_V_F_Nn2);
    
    pCTRL->_V_F_Xalfa += pCTRL->_P_F_Ws*(pCTRL->_V_F_Yalfa + pCTRL->_V_F_Ealfa);
    pCTRL->_V_F_Xbeta += pCTRL->_P_F_Ws*(pCTRL->_V_F_Ybeta + pCTRL->_V_F_Ebeta);
        
    pCTRL->_V_F_Nalfa = pCTRL->_V_F_Xalfa - pCTRL->_P_F_Ls*pCTRL->_I_F_Ialfa;
    pCTRL->_V_F_Nbeta = pCTRL->_V_F_Xbeta - pCTRL->_P_F_Ls*pCTRL->_I_F_Ibeta;
    
    float Freq_abs = MATH_ABS_F(pCTRL->FL_SRAD.F_Filter_out);
    if      (Freq_abs < 0.125f) {pCTRL->PID_PLL.F_Kp = 0.125f*pCTRL->_P_F_PLL_Kp;   pCTRL->PID_PLL.F_Ki = 0.015625f*pCTRL->_P_F_PLL_Ki;}
    else if (Freq_abs < 0.25f)  {pCTRL->PID_PLL.F_Kp = 0.25f*pCTRL->_P_F_PLL_Kp;    pCTRL->PID_PLL.F_Ki = 0.0625f*pCTRL->_P_F_PLL_Ki;}
    else if (Freq_abs < 0.5f)   {pCTRL->PID_PLL.F_Kp = 0.5f*pCTRL->_P_F_PLL_Kp;     pCTRL->PID_PLL.F_Ki = 0.25f*pCTRL->_P_F_PLL_Ki;}
    else                        {pCTRL->PID_PLL.F_Kp = pCTRL->_P_F_PLL_Kp;          pCTRL->PID_PLL.F_Ki = pCTRL->_P_F_PLL_Ki;}
    
    pCTRL->PID_PLL.F_Rf = pCTRL->_V_F_Nbeta*pCTRL->TG_Triangle.F_Cos;
    pCTRL->PID_PLL.F_Fb = pCTRL->_V_F_Nalfa*pCTRL->TG_Triangle.F_Sin;
    PID_Pos_Cal_F(&pCTRL->PID_PLL);
    
    pCTRL->FL_SRAD.F_Filter_in = pCTRL->PID_PLL.F_Output;
    Filter_Cal_F(&pCTRL->FL_SRAD);
    
    pCTRL->TG_Triangle.F_Angle += pCTRL->_P_F_Ts*pCTRL->FL_SRAD.F_Filter_in;
    MATH_ANGLE_MOD_F(pCTRL->TG_Triangle.F_Angle);
    
    Math_SinCos_F(&pCTRL->TG_Triangle);
}

/**********************************滑模观测器************************************/

/**********************************************************************************************
Function: Est_SMO_Init_F
Description: 滑模观测器初始化
Input: 无
Output: 无
Input_Output: 滑模观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_SMO_Init_F(ST_SMO_CONTROL_F* pCTRL)
{
    PID_Pos_Init_F(&pCTRL->PID_PLL, 0.0f);
    Filter_Init_F(&pCTRL->FL_SRAD, 0.0f);
    pCTRL->TG_Triangle.F_Angle = 0.0f;
    pCTRL->TG_Triangle.F_Cos = 1.0f;
    pCTRL->TG_Triangle.F_Sin = 0.0f;
    pCTRL->TG_Triangle.F_ReAngle = 0.0f;
    
    pCTRL->_V_F_Aalfa = 0.0f;
    pCTRL->_V_F_Abeta = 0.0f;
}

/**********************************************************************************************
Function: Est_SMO_F
Description: 滑模观测器计算
Input: 无
Output: 无
Input_Output: 滑模观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_SMO_F(ST_SMO_CONTROL_F* pCTRL)
{
    pCTRL->_V_F_Aalfa += pCTRL->_P_F_Ws*(
					   - pCTRL->_P_F_Rs_Over_Ld*pCTRL->_V_F_Aalfa
                       - pCTRL->FL_SRAD.F_Filter_in*pCTRL->_P_F_Ld_Lq_Over_Ld*pCTRL->_V_F_Abeta
                       + pCTRL->_P_F_One_Over_Ld*pCTRL->_I_F_Ualfa
                       - pCTRL->_P_F_One_Over_Ld*pCTRL->_V_F_Ealfa);
    pCTRL->_V_F_Abeta += pCTRL->_P_F_Ws*(
					   - pCTRL->_P_F_Rs_Over_Ld*pCTRL->_V_F_Abeta
                       + pCTRL->FL_SRAD.F_Filter_in*pCTRL->_P_F_Ld_Lq_Over_Ld*pCTRL->_V_F_Aalfa
                       + pCTRL->_P_F_One_Over_Ld*pCTRL->_I_F_Ubeta
                       - pCTRL->_P_F_One_Over_Ld*pCTRL->_V_F_Ebeta);
    
    float Freq_abs = MATH_ABS_F(pCTRL->FL_SRAD.F_Filter_out);
    if      (Freq_abs < 0.125f) {pCTRL->_V_F_H1 = 0.125f*pCTRL->_P_F_H1;    pCTRL->PID_PLL.F_Ki = 0.125f*pCTRL->_P_F_PLL_Ki;}
    else if (Freq_abs < 0.25f)  {pCTRL->_V_F_H1 = 0.25f*pCTRL->_P_F_H1;     pCTRL->PID_PLL.F_Ki = 0.25f*pCTRL->_P_F_PLL_Ki;}
    else if (Freq_abs < 0.5f)   {pCTRL->_V_F_H1 = 0.5f*pCTRL->_P_F_H1;      pCTRL->PID_PLL.F_Ki = 0.5f*pCTRL->_P_F_PLL_Ki;}
    else                        {pCTRL->_V_F_H1 = pCTRL->_P_F_H1;           pCTRL->PID_PLL.F_Ki = pCTRL->_P_F_PLL_Ki;}
    
    pCTRL->_V_F_IErralfa = pCTRL->_P_F_H1*(pCTRL->_V_F_Aalfa - pCTRL->_I_F_Ialfa);
    pCTRL->_V_F_IErrbeta = pCTRL->_P_F_H1*(pCTRL->_V_F_Abeta - pCTRL->_I_F_Ibeta);
	
    if      (pCTRL->_V_F_IErralfa >  pCTRL->_P_F_K1)    {pCTRL->_V_F_Ealfa =  pCTRL->_P_F_K1;}
    else if (pCTRL->_V_F_IErralfa < -pCTRL->_P_F_K1)    {pCTRL->_V_F_Ealfa = -pCTRL->_P_F_K1;}
    else                                                {pCTRL->_V_F_Ealfa =  pCTRL->_V_F_IErralfa;}
    if      (pCTRL->_V_F_IErrbeta >  pCTRL->_P_F_K1)    {pCTRL->_V_F_Ebeta =  pCTRL->_P_F_K1;}
    else if (pCTRL->_V_F_IErrbeta < -pCTRL->_P_F_K1)    {pCTRL->_V_F_Ebeta = -pCTRL->_P_F_K1;}
    else                                                {pCTRL->_V_F_Ebeta =  pCTRL->_V_F_IErrbeta;}
    
    pCTRL->PID_PLL.F_Rf = -pCTRL->_I_F_DIR_Target*pCTRL->_V_F_Ealfa*pCTRL->TG_Triangle.F_Cos;
    pCTRL->PID_PLL.F_Fb =  pCTRL->_I_F_DIR_Target*pCTRL->_V_F_Ebeta*pCTRL->TG_Triangle.F_Sin;
    PID_Pos_Cal_F(&pCTRL->PID_PLL);
    
    pCTRL->FL_SRAD.F_Filter_in = pCTRL->PID_PLL.F_Output;
    Filter_Cal_F(&pCTRL->FL_SRAD);
    
    pCTRL->TG_Triangle.F_Angle += pCTRL->_P_F_Ts*pCTRL->FL_SRAD.F_Filter_in;
    MATH_ANGLE_MOD_F(pCTRL->TG_Triangle.F_Angle);
    
    Math_SinCos_F(&pCTRL->TG_Triangle);
}

/**********************************************************************************************
Function: Est_SMO_Study_F
Description: 滑模观测器参数学习
Input: 无
Output: 无
Input_Output: 滑模观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_SMO_Study_F(ST_SMO_CONTROL_F* pCTRL)
{
    float Alfa_abs;
    float Alfa_sign;
    float Beta_abs;
    float Beta_sign;
    
    Alfa_abs = MATH_ABS_T(pCTRL->_V_F_IErralfa);
    Alfa_sign = MATH_SIGN_T(pCTRL->_V_F_IErralfa);
    Beta_abs = MATH_ABS_T(pCTRL->_V_F_IErrbeta);
    Beta_sign = MATH_SIGN_T(pCTRL->_V_F_IErrbeta);
    
    pCTRL->_V_F_K1_alfa_tmp = - pCTRL->_P_F_Rs*Alfa_abs + pCTRL->_V_F_Ealfa*Alfa_sign
                              - Alfa_sign*pCTRL->FL_SRAD.F_Filter_in*(pCTRL->_P_F_Ld - pCTRL->_P_F_Lq)*pCTRL->_V_F_IErrbeta;
    pCTRL->_V_F_K1_beta_tmp = - pCTRL->_P_F_Rs*Beta_abs + pCTRL->_V_F_Ebeta*Beta_sign
                              + Beta_sign*pCTRL->FL_SRAD.F_Filter_in*(pCTRL->_P_F_Ld - pCTRL->_P_F_Lq)*pCTRL->_V_F_IErralfa;
}

/**********************************************************************/

void Hallest_Positon_Control(ST_POSITION_CONTROL* pCTRL)
{
    float tmp1;
    if(pCTRL->I_Position_Error > pCTRL->P_K1)
    {
        tmp1 = pCTRL->P_K1;
    }
    else if(pCTRL->I_Position_Error < -pCTRL->P_K1)
    {
        tmp1 = -pCTRL->P_K1;
    }
    else
    {
        tmp1 = pCTRL->I_Position_Error;
    }
    
    tmp1 += pCTRL->P_K2*pCTRL->I_Position_Error;
    
    pCTRL->O_Follow_Speed = pCTRL->I_Target_Speed - tmp1;
}

/**********************************************************************/

float Hallest_Angle_Mean(float* DATA, ST_HALL_CONTROL_F* pCTRL)
{
    float tmp = 0.0f;
    for(Q08U_ i=0;i<pCTRL->P_HS_num;i++)
    {
        tmp += (*(DATA+3+i));
    }
    tmp /= (float)pCTRL->P_HS_num;
    return tmp;
}

void Hallest_Study_Task_Flow(ST_HALL_CONTROL_F* pCTRL)
{
    switch(pCTRL->HS_Flow)
    {
    case EM_HALL_STUDY_INIT:
        {
            Ramp_Init_F(&pCTRL->AngleRadRamp, pCTRL->AngleRadRamp.F_Init);
            pCTRL->Set_Dir = 1.0f;
            pCTRL->HS_Sector_cnt = 0;
            pCTRL->HS_cnt = 0;
            pCTRL->HS_Flow = EM_HALL_STUDY_CW;
        }break;
    case EM_HALL_STUDY_CW:
        {
            Ramp_Cal_F(&pCTRL->AngleRadRamp);
            if(pCTRL->HS_cnt >= pCTRL->P_HS_num+5)
            {
                pCTRL->HS_Sector_Tab_Init[0] = pCTRL->HS_Sector_tmp[0];
                pCTRL->HS_Sector_Tab_Init[1] = pCTRL->HS_Sector_tmp[1];
                pCTRL->HS_Sector_Tab_Init[2] = pCTRL->HS_Sector_tmp[2];
                pCTRL->HS_Sector_Tab_Init[3] = pCTRL->HS_Sector_tmp[3];
                pCTRL->HS_Sector_Tab_Init[4] = pCTRL->HS_Sector_tmp[4];
                pCTRL->HS_Sector_Tab_Init[5] = pCTRL->HS_Sector_tmp[5];
                
                pCTRL->HS_Angle_Tab_CW_Init[0] = Hallest_Angle_Mean(pCTRL->HS_Angle_tmp_1, pCTRL);
                pCTRL->HS_Angle_Tab_CW_Init[1] = Hallest_Angle_Mean(pCTRL->HS_Angle_tmp_2, pCTRL);
                pCTRL->HS_Angle_Tab_CW_Init[2] = Hallest_Angle_Mean(pCTRL->HS_Angle_tmp_3, pCTRL);
                pCTRL->HS_Angle_Tab_CW_Init[3] = Hallest_Angle_Mean(pCTRL->HS_Angle_tmp_4, pCTRL);
                pCTRL->HS_Angle_Tab_CW_Init[4] = Hallest_Angle_Mean(pCTRL->HS_Angle_tmp_5, pCTRL);
                pCTRL->HS_Angle_Tab_CW_Init[5] = Hallest_Angle_Mean(pCTRL->HS_Angle_tmp_6, pCTRL);
                
                Ramp_Init_F(&pCTRL->AngleRadRamp, pCTRL->AngleRadRamp.F_Init);
                pCTRL->Set_Dir = -1.0f;
                pCTRL->HS_Sector_cnt = 0;
                pCTRL->HS_cnt = 0;
                pCTRL->HS_Flow = EM_HALL_STUDY_CCW;
            }
        }break;
    case EM_HALL_STUDY_CCW:
        {
            Ramp_Cal_F(&pCTRL->AngleRadRamp);
            if(pCTRL->HS_cnt >= pCTRL->P_HS_num+5)
            {
                pCTRL->HS_Angle_Tab_CCW_Init[0] = Hallest_Angle_Mean(pCTRL->HS_Angle_tmp_1, pCTRL);
                pCTRL->HS_Angle_Tab_CCW_Init[1] = Hallest_Angle_Mean(pCTRL->HS_Angle_tmp_2, pCTRL);
                pCTRL->HS_Angle_Tab_CCW_Init[2] = Hallest_Angle_Mean(pCTRL->HS_Angle_tmp_3, pCTRL);
                pCTRL->HS_Angle_Tab_CCW_Init[3] = Hallest_Angle_Mean(pCTRL->HS_Angle_tmp_4, pCTRL);
                pCTRL->HS_Angle_Tab_CCW_Init[4] = Hallest_Angle_Mean(pCTRL->HS_Angle_tmp_5, pCTRL);
                pCTRL->HS_Angle_Tab_CCW_Init[5] = Hallest_Angle_Mean(pCTRL->HS_Angle_tmp_6, pCTRL);
                
                for(Q08U_ i=0;i<=5;i++)
                {
                    for(Q08U_ j=0;j<=5;j++)
                    {
                        if(pCTRL->HS_Sector_Tab_Init[i] == pCTRL->HS_Sector_tmp[j])
                        {
                            pCTRL->HS_Angle_Tab_Init[i] = 0.5f*(pCTRL->HS_Angle_Tab_CW_Init[i] + pCTRL->HS_Angle_Tab_CCW_Init[j]);
                        }
                    }
                }
                
                if(pCTRL->HS_Angle_Tab_Init[0] > pCTRL->HS_Angle_Tab_Init[1])
                {
                    pCTRL->HS_Angle_Tab_Init[0] -= MATH_PI_F;
                }
                
                if(pCTRL->HS_Angle_Tab_Init[4] > pCTRL->HS_Angle_Tab_Init[5])
                {
                    pCTRL->HS_Angle_Tab_Init[5] += MATH_PI_F;
                }
                
                pCTRL->HS_Flow = EM_HALL_STUDY_FINISH;
            }
        }break;
    default:break;
    }
}

void Hallest_Study_VF(ST_HALL_CONTROL_F* pCTRL)
{
    pCTRL->AngleRad += pCTRL->Set_Dir*pCTRL->P_Ts*pCTRL->AngleRadRamp.F_Output*MATH_2PI_F;
    if(pCTRL->AngleRad > MATH_2PI_F)
    {
        pCTRL->HS_Sector_cnt = 0;
        pCTRL->HS_cnt++;
        pCTRL->AngleRad -= MATH_2PI_F;
    }
    else if(pCTRL->AngleRad < 0.0f)
    {
        pCTRL->HS_Sector_cnt = 0;
        pCTRL->HS_cnt++;
        pCTRL->AngleRad += MATH_2PI_F;
    }
}

void Hallest_Study_Self(ST_HALL_CONTROL_F* pCTRL)
{
    pCTRL->HS_Sector_tmp[pCTRL->HS_Sector_cnt] = pCTRL->HallCurrentLevel;
    switch(pCTRL->HS_Sector_cnt)
    {
    case 0:
        {
            pCTRL->HS_Angle_tmp_1[pCTRL->HS_cnt] = pCTRL->AngleRad;
        }break;
    case 1:
        {
            pCTRL->HS_Angle_tmp_2[pCTRL->HS_cnt] = pCTRL->AngleRad;
        }break;
    case 2:
        {
            pCTRL->HS_Angle_tmp_3[pCTRL->HS_cnt] = pCTRL->AngleRad;
        }break;
    case 3:
        {
            pCTRL->HS_Angle_tmp_4[pCTRL->HS_cnt] = pCTRL->AngleRad;
        }break;
    case 4:
        {
            pCTRL->HS_Angle_tmp_5[pCTRL->HS_cnt] = pCTRL->AngleRad;
        }break;
    case 5:
        {
            pCTRL->HS_Angle_tmp_6[pCTRL->HS_cnt] = pCTRL->AngleRad;
        }break;
    default:break;
    }
    pCTRL->HS_Sector_cnt++;
}

void Hallest_Angle_Initial(ST_HALL_CONTROL_F* pCTRL)
{
    pCTRL->HS_Sector_Tab[0] = pCTRL->HS_Sector_Tab_Init[5];
    pCTRL->HS_Sector_Tab[1] = pCTRL->HS_Sector_Tab_Init[0];
    pCTRL->HS_Sector_Tab[2] = pCTRL->HS_Sector_Tab_Init[1];
    pCTRL->HS_Sector_Tab[3] = pCTRL->HS_Sector_Tab_Init[2];
    pCTRL->HS_Sector_Tab[4] = pCTRL->HS_Sector_Tab_Init[3];
    pCTRL->HS_Sector_Tab[5] = pCTRL->HS_Sector_Tab_Init[4];
    pCTRL->HS_Sector_Tab[6] = pCTRL->HS_Sector_Tab_Init[5];
    pCTRL->HS_Sector_Tab[7] = pCTRL->HS_Sector_Tab_Init[0];
    
    pCTRL->HS_Angle_Tab[0] = pCTRL->HS_Angle_Tab_Init[5];
    pCTRL->HS_Angle_Tab[1] = pCTRL->HS_Angle_Tab_Init[0];
    pCTRL->HS_Angle_Tab[2] = pCTRL->HS_Angle_Tab_Init[1];
    pCTRL->HS_Angle_Tab[3] = pCTRL->HS_Angle_Tab_Init[2];
    pCTRL->HS_Angle_Tab[4] = pCTRL->HS_Angle_Tab_Init[3];
    pCTRL->HS_Angle_Tab[5] = pCTRL->HS_Angle_Tab_Init[4];
    pCTRL->HS_Angle_Tab[6] = pCTRL->HS_Angle_Tab_Init[5];
    pCTRL->HS_Angle_Tab[7] = pCTRL->HS_Angle_Tab_Init[0];
    
    pCTRL->HS_Angle_Tab_CW[0] = 0.5f*(pCTRL->HS_Angle_Tab[6] + pCTRL->HS_Angle_Tab[5]);
    pCTRL->HS_Angle_Tab_CW[1] = 0.5f*(pCTRL->HS_Angle_Tab[1] + pCTRL->HS_Angle_Tab[6]) - MATH_PI_F;
    pCTRL->HS_Angle_Tab_CW[2] = 0.5f*(pCTRL->HS_Angle_Tab[2] + pCTRL->HS_Angle_Tab[1]);
    pCTRL->HS_Angle_Tab_CW[3] = 0.5f*(pCTRL->HS_Angle_Tab[3] + pCTRL->HS_Angle_Tab[2]);
    pCTRL->HS_Angle_Tab_CW[4] = 0.5f*(pCTRL->HS_Angle_Tab[4] + pCTRL->HS_Angle_Tab[3]);
    pCTRL->HS_Angle_Tab_CW[5] = 0.5f*(pCTRL->HS_Angle_Tab[5] + pCTRL->HS_Angle_Tab[4]);
    pCTRL->HS_Angle_Tab_CW[6] = 0.5f*(pCTRL->HS_Angle_Tab[6] + pCTRL->HS_Angle_Tab[5]);
    pCTRL->HS_Angle_Tab_CW[7] = 0.5f*(pCTRL->HS_Angle_Tab[1] + pCTRL->HS_Angle_Tab[6]) - MATH_PI_F;
    for(Q08U_ i=0;i<=7;i++)
    {
        while(pCTRL->HS_Angle_Tab_CW[i] > MATH_2PI_F)
        {
            pCTRL->HS_Angle_Tab_CW[i] -= MATH_2PI_F;
        }
        while(pCTRL->HS_Angle_Tab_CW[i] < 0.0f)
        {
            pCTRL->HS_Angle_Tab_CW[i] += MATH_2PI_F;
        }
    }
    
    pCTRL->HS_Angle_Tab_CCW[0] = 0.5f*(pCTRL->HS_Angle_Tab[6] + pCTRL->HS_Angle_Tab[1]) - MATH_PI_F;
    pCTRL->HS_Angle_Tab_CCW[1] = 0.5f*(pCTRL->HS_Angle_Tab[1] + pCTRL->HS_Angle_Tab[2]);
    pCTRL->HS_Angle_Tab_CCW[2] = 0.5f*(pCTRL->HS_Angle_Tab[2] + pCTRL->HS_Angle_Tab[3]);
    pCTRL->HS_Angle_Tab_CCW[3] = 0.5f*(pCTRL->HS_Angle_Tab[3] + pCTRL->HS_Angle_Tab[4]);
    pCTRL->HS_Angle_Tab_CCW[4] = 0.5f*(pCTRL->HS_Angle_Tab[4] + pCTRL->HS_Angle_Tab[5]);
    pCTRL->HS_Angle_Tab_CCW[5] = 0.5f*(pCTRL->HS_Angle_Tab[5] + pCTRL->HS_Angle_Tab[6]);
    pCTRL->HS_Angle_Tab_CCW[6] = 0.5f*(pCTRL->HS_Angle_Tab[6] + pCTRL->HS_Angle_Tab[1]) - MATH_PI_F;
    pCTRL->HS_Angle_Tab_CCW[7] = 0.5f*(pCTRL->HS_Angle_Tab[1] + pCTRL->HS_Angle_Tab[2]);
    for(Q08U_ i=0;i<=7;i++)
    {
        while(pCTRL->HS_Angle_Tab_CCW[i] > MATH_2PI_F)
        {
            pCTRL->HS_Angle_Tab_CCW[i] -= MATH_2PI_F;
        }
        while(pCTRL->HS_Angle_Tab_CCW[i] < 0.0f)
        {
            pCTRL->HS_Angle_Tab_CCW[i] += MATH_2PI_F;
        }
    }
}

void Hallest_Init(ST_HALL_CONTROL_F* pCTRL)
{
    pCTRL->Set_Dir = pCTRL->I_Target_Dir;
    pCTRL->Hall_Dir = pCTRL->I_Target_Dir;  
    
    pCTRL->Switch_Phase_Flag = 0;  
    
    pCTRL->HallCount_tmp[0] = 0;
    pCTRL->HallCount_tmp[1] = 0;
    pCTRL->HallCount_tmp[2] = 0;
    pCTRL->HallCount_tmp[3] = 0;
    pCTRL->HallCount_tmp[4] = 0;
    pCTRL->HallCount_tmp[5] = 0;
    pCTRL->HallLastCount = 0;  
    pCTRL->HallCurrentCount = 0;  
    pCTRL->HallSpeedCount = 0;      
    
    pCTRL->HallStallCount = 0;             
    pCTRL->HallStallLastCount = 0;         
    pCTRL->HallStall_cnt = 0;     
    
    pCTRL->AngleRad = 0.0f;                 
    pCTRL->AngleRad_Hall = 0.0f;        
    
    pCTRL->ElecFreqHz = 0.0f;                  
    pCTRL->ElecFreqHz_Filter = 0.0f;   
    
    Ramp_Init_F(&pCTRL->AngleRadRamp, pCTRL->AngleRadRamp.F_Init);
    pCTRL->HS_Flow = EM_HALL_STUDY_INIT;
    pCTRL->HS_Sector_cnt = 0;  
    pCTRL->HS_cnt = 0;
    
    for(Q08U_ i=1;i<=6;i++)
    {
        if(pCTRL->HallCurrentLevel == pCTRL->HS_Sector_Tab[i])
        {
            pCTRL->HS_Sector_cnt = i;
            break;
        }
    }
    pCTRL->AngleRad_Hall = pCTRL->HS_Angle_Tab[pCTRL->HS_Sector_cnt];
}

void Hallest_High_Speed_Anlge(ST_HALL_CONTROL_F* pCTRL)
{
    for(Q08U_ i=1;i<=6;i++)
    {
        if(pCTRL->HallCurrentLevel == pCTRL->HS_Sector_Tab[i])
        {
            pCTRL->HS_Sector_cnt = i;
            break;
        }
    }
    
    if(pCTRL->Set_Dir == 1.0f)
    {
        pCTRL->AngleRad_Hall = pCTRL->HS_Angle_Tab_CW[pCTRL->HS_Sector_cnt];
    }
    else if(pCTRL->Set_Dir == -1.0f)
    {
        pCTRL->AngleRad_Hall = pCTRL->HS_Angle_Tab_CCW[pCTRL->HS_Sector_cnt];
    }
    
    if(pCTRL->HallLastLevel == pCTRL->HS_Sector_Tab[pCTRL->HS_Sector_cnt-1])
    {
        pCTRL->Hall_Dir = 1.0f;
    }
    else if(pCTRL->HallLastLevel == pCTRL->HS_Sector_Tab[pCTRL->HS_Sector_cnt+1])
    {
        pCTRL->Hall_Dir = -1.0f;
    }
}

void Hallest_Speed_Cal(ST_HALL_CONTROL_F* pCTRL)
{
    pCTRL->HallStallCount++;
    
    if(pCTRL->HallCurrentCount >  pCTRL->HallLastCount)
    {
        pCTRL->HallCount_tmp[0] = pCTRL->HallCurrentCount - pCTRL->HallLastCount;
    }
    else
    {
        pCTRL->HallCount_tmp[0] =  (pCTRL->P_TIM_Max_Count - pCTRL->HallLastCount) + pCTRL->HallCurrentCount;
    }
    
    pCTRL->ElecFreqHz = pCTRL->P_TIM_FreqHz/((float)pCTRL->HallCount_tmp[0] + (float)pCTRL->HallCount_tmp[1] + (float)pCTRL->HallCount_tmp[2]
                                           + (float)pCTRL->HallCount_tmp[3] + (float)pCTRL->HallCount_tmp[4] + (float)pCTRL->HallCount_tmp[5]);
    
    pCTRL->HallCount_tmp[5] = pCTRL->HallCount_tmp[4];
    pCTRL->HallCount_tmp[4] = pCTRL->HallCount_tmp[3];
    pCTRL->HallCount_tmp[3] = pCTRL->HallCount_tmp[2];
    pCTRL->HallCount_tmp[2] = pCTRL->HallCount_tmp[1];
    pCTRL->HallCount_tmp[1] = pCTRL->HallCount_tmp[0];
    
    pCTRL->ElecFreqHz_Filter = 0.001f*(pCTRL->P_Freq_Filter_Coeff*pCTRL->ElecFreqHz_Filter + (1000.0f-pCTRL->P_Freq_Filter_Coeff)*pCTRL->ElecFreqHz);
    
    pCTRL->HallLastCount = pCTRL->HallCurrentCount;
    
    pCTRL->Switch_Phase_Flag = 1;
}

void Hallest_Angle_Inc(ST_HALL_CONTROL_F* pCTRL)
{
    float AngleRad_Hall_tmp = 0.0f;
    float AngleRad_Add_tmp = 0.0f;
    Q32U_ HallCurrentCount_tmp = 0;
    Q32U_ HallDelta_tmp = 0;
    
    pCTRL->Switch_Phase_Flag = 0U;
    
    AngleRad_Hall_tmp = pCTRL->AngleRad_Hall;
    HallCurrentCount_tmp = pCTRL->HallCurrentCount;
    
    if(pCTRL->HallSpeedCount >  HallCurrentCount_tmp)
    {
        HallDelta_tmp = pCTRL->HallSpeedCount - HallCurrentCount_tmp;
    }
    else
    {
        HallDelta_tmp = (pCTRL->P_TIM_Max_Count - HallCurrentCount_tmp) + pCTRL->HallSpeedCount;
    }
    
    AngleRad_Add_tmp = ((float)HallDelta_tmp)*MATH_2PI_F*pCTRL->ElecFreqHz_Filter/pCTRL->P_TIM_FreqHz;
    
    if(AngleRad_Add_tmp > MATH_PI_OVER_TWO_F)
    {
        AngleRad_Add_tmp = MATH_PI_OVER_TWO_F;
    }
    if(AngleRad_Add_tmp < -MATH_PI_OVER_TWO_F)
    {
        AngleRad_Add_tmp = -MATH_PI_OVER_TWO_F;
    }
    
    if(pCTRL->Switch_Phase_Flag == 1U)
    {
        pCTRL->AngleRad = pCTRL->AngleRad_Hall;
    }
    else
    {
        pCTRL->AngleRad = AngleRad_Hall_tmp + AngleRad_Add_tmp;
    }
}
