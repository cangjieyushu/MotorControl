/**************************************************************************************************
*     File Name :                        MotorDent.h
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             参数辨识头文件
**************************************************************************************************/
#ifndef MotorDent_H
#define MotorDent_H

#include "Math.h"

typedef struct
{
    ST_TRIG_F       TG_Triangle;
    ST_FILTER_F     FL_tmp1;
    ST_FILTER_F     FL_tmp2;

    Q32U_       _V_Q32U_State;
    Q32U_       _V_Q32U_cnt;
    
    float       _I_F_Ud;
    float       _I_F_Id;
    float       _V_F_Udtmp1;
    float       _V_F_Idtmp1;
    float       _V_F_Udtmp2;
    float       _V_F_Idtmp2;
    
    float       _O_F_IdRef;
    float       _O_F_Uq;
    
    float       _P_F_Ts;
    float       _P_F_Id1;
    float       _P_F_Id2;
    Q32U_       _P_Q32U_Rs_Time;
    Q32U_       _P_Q32U_Ls_Time;
    Q32U_       _P_Q32U_Flux_Time;
    
    float       _I_F_Ialfa;
    float       _I_F_Ibeta;
    
    float       _V_F_Istmp1;
    float       _V_F_Istmp2;
    Q32U_       _V_Q32U_Ud_cnt;
    Q32U_       _V_Q32U_Ud_Count;
    float       _V_F_Ud_Sign;
    float       _V_F_Ialfa_LPF;
    float       _V_F_Ibeta_LPF;
    float       _V_F_Ialfa_HPF;
    float       _V_F_Ibeta_HPF;
    float       _V_F_Ialfa_Last;
    float       _V_F_Ibeta_Last;
    
    float       _O_F_Ialfa;
    float       _O_F_Ibeta;
    float       _O_F_Ud_HFI;
    
    float       _I_F_Ualfa;
    float       _I_F_Ubeta;
    
    float       _V_F_Yalfa_In;
    float       _V_F_Ybeta_In;
    float       _V_F_Yalfa_Hpf;
    float       _V_F_Ybeta_Hpf;
    float       _V_F_Yalfa_Last;
    float       _V_F_Ybeta_Last;
    float       _V_F_Xalfa;
    float       _V_F_Xbeta;
    float       _V_F_Nalfa;
    float       _V_F_Nbeta;
    
    float       _P_F_Ud_Ref;
    Q32U_       _P_Q32U_PWM_Freq;
    Q32U_       _P_Q32U_Ud_Freq;
    float       _P_F_Udq_Coeff;
    
    float       _P_F_Hpf_Coeff;
    
    float       _P_F_Rs;
    float       _P_F_Ld;
    float       _P_F_Lq;
    float       _P_F_Ls;
    float       _P_F_Flux;
}ST_PARA_ID_F;

/**********************************************************************************************
Function: Est_Para_Id_Init_F
Description: 静态参数辨识初始化
Input: 无
Output: 无
Input_Output: 静态参数辨识指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Para_Id_Init_F(ST_PARA_ID_F* pCTRL);

/**********************************************************************************************
Function: Est_Para_Id_Srad_F
Description: 静态参数辨识计算
Input: 无
Output: 无
Input_Output: 静态参数辨识指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Para_Id_Srad_F(ST_PARA_ID_F* pCTRL);

/**********************************************************************************************
Function: Est_Para_Id_Current_F
Description: 静态参数辨识计算
Input: 无
Output: 无
Input_Output: 静态参数辨识指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Para_Id_Current_F(ST_PARA_ID_F* pCTRL);

#endif /* MotorDent_H */
