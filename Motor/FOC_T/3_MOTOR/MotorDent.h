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
    ST_TRIG_T       TG_Triangle;
    ST_FILTER_T     FL_tmp1;
    ST_FILTER_T     FL_tmp2;

    Q32U_       _V_Q32U_State;
    Q32U_       _V_Q32U_cnt;
    
    Q32I_       _I_Q14I_Ud;
    Q32I_       _I_Q14I_Id;
    Q32I_       _V_Q14I_Udtmp1;
    Q32I_       _V_Q14I_Idtmp1;
    Q32I_       _V_Q14I_Udtmp2;
    Q32I_       _V_Q14I_Idtmp2;
    
    Q32I_       _O_Q14I_IdRef;
    Q32I_       _O_Q14I_Uq;
    
    Q32I_       _P_Q14I_Ts;
    Q32I_       _P_Q14I_Ws;
    Q32I_       _P_Q14I_Id1;
    Q32I_       _P_Q14I_Id2;
    Q32U_       _P_Q32U_Rs_Time;
    Q32U_       _P_Q32U_Ls_Time;
    Q32U_       _P_Q32U_Flux_Time;
    
    Q32I_       _I_Q14I_Ialfa;
    Q32I_       _I_Q14I_Ibeta;
    
    Q32I_       _V_Q14I_Istmp1;
    Q32I_       _V_Q14I_Istmp2;
    Q32U_       _V_Q32U_Ud_cnt;
    Q32U_       _V_Q32U_Ud_Count;
    Q32I_       _V_Q14I_Ud_Sign;
    Q32I_       _V_Q14I_Ialfa_LPF;
    Q32I_       _V_Q14I_Ibeta_LPF;
    Q32I_       _V_Q14I_Ialfa_HPF;
    Q32I_       _V_Q14I_Ibeta_HPF;
    Q32I_       _V_Q14I_Ialfa_Last;
    Q32I_       _V_Q14I_Ibeta_Last;
    
    Q32I_       _O_Q14I_Ialfa;
    Q32I_       _O_Q14I_Ibeta;
    Q32I_       _O_Q14I_Ud_HFI;
    
    Q32I_       _I_Q14I_Ualfa;
    Q32I_       _I_Q14I_Ubeta;
    
    Q32I_       _V_Q28I_Yalfa_In;
    Q32I_       _V_Q28I_Ybeta_In;
    Q32I_       _V_Q28I_Yalfa_Hpf;
    Q32I_       _V_Q28I_Ybeta_Hpf;
    Q32I_       _V_Q28I_Yalfa_Last;
    Q32I_       _V_Q28I_Ybeta_Last;
    Q32I_       _V_Q28I_Xalfa_tmp;
    Q32I_       _V_Q28I_Xbeta_tmp;
    Q32I_       _V_Q14I_Nalfa;
    Q32I_       _V_Q14I_Nbeta;
    
    Q32I_       _P_Q14I_Ud_Ref;
    Q32U_       _P_Q32U_PWM_Freq;
    Q32U_       _P_Q32U_Ud_Freq;
    
    Q32I_       _P_Q08I_Hpf_Coeff;
    
    Q32I_       _P_Q14I_Rs;
    Q32I_       _P_Q24I_Ld;
    Q32I_       _P_Q24I_Lq;
    Q32I_       _P_Q14I_Ls;
    Q32I_       _P_Q14I_Flux;
}ST_PARA_ID_T;

/**********************************************************************************************
Function: Est_Para_Id_Init_T
Description: 静态参数辨识初始化
Input: 无
Output: 无
Input_Output: 静态参数辨识指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Para_Id_Init_T(ST_PARA_ID_T* pCTRL);

/**********************************************************************************************
Function: Est_Para_Id_Srad_F
Description: 静态参数辨识计算
Input: 无
Output: 无
Input_Output: 静态参数辨识指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Para_Id_Srad_T(ST_PARA_ID_T* pCTRL);

/**********************************************************************************************
Function: Est_Para_Id_Current_T
Description: 静态参数辨识计算
Input: 无
Output: 无
Input_Output: 静态参数辨识指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Para_Id_Current_T(ST_PARA_ID_T* pCTRL);

#endif /* MotorDent_H */
