/**************************************************************************************************
*     File Name :                        MotorEst.h
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             速度角度观测器头文件
**************************************************************************************************/
#ifndef MotorEst_H
#define MotorEst_H

#include "Math.h"

typedef struct
{
    ST_PID_POS_T    PID_PLL;
    ST_FILTER_T     FL_SRAD;
    ST_TRIG_T       TG_Triangle;
    
    Q32I_       _O_Q28U_Angle_tmp;
    Q32I_       _I_Q14I_Ualfa;
    Q32I_       _I_Q14I_Ubeta;
    Q32I_       _I_Q14I_Ialfa;
    Q32I_       _I_Q14I_Ibeta;
    
    Q32I_       _V_Q14I_Yalfa;
    Q32I_       _V_Q14I_Ybeta;
    Q32I_       _V_Q14I_Nalfa;
    Q32I_       _V_Q14I_Nbeta;
    Q32I_       _V_Q14I_Nn2;
    Q32I_       _V_Q14I_Valfa;
    Q32I_       _V_Q14I_Vbeta;
    Q32I_       _V_Q28I_Xalfa_tmp;
    Q32I_       _V_Q28I_Xbeta_tmp;
    Q32I_       _V_Q14I_Xalfa;
    Q32I_       _V_Q14I_Xbeta;
    
    Q32I_       _P_Q14I_PLL_Kp;
    Q32I_       _P_Q14I_PLL_Ki;
    Q32I_       _P_Q14I_Ts;
    Q32I_       _P_Q14I_Ws;
    Q32I_       _P_Q14I_Gamma;
    Q32I_       _P_Q14I_Rs;
    Q32I_       _P_Q14I_Ls;
    Q32I_       _P_Q14I_Ld;
    Q32I_       _P_Q14I_Flux;
    Q32I_       _P_Q14I_Flux2;
}ST_FLUX_CONTROL_T;

typedef struct
{
    Q32I_       _I_Q00I_DIR_Target;
    ST_PID_POS_T    PID_PLL;
    ST_FILTER_T     FL_SRAD;
    ST_TRIG_T       TG_Triangle;

    Q32I_       _O_Q28U_Angle_tmp;
    Q32I_       _I_Q14I_Ualfa;
    Q32I_       _I_Q14I_Ubeta;
    Q32I_       _I_Q14I_Ialfa;
    Q32I_       _I_Q14I_Ibeta;
    
    Q32I_       _V_Q28I_Aalfa_tmp;
    Q32I_       _V_Q28I_Abeta_tmp;
    Q32I_       _V_Q14I_Aalfa;
    Q32I_       _V_Q14I_Abeta;
    Q32I_       _V_Q14I_IErralfa;
    Q32I_       _V_Q14I_IErrbeta;
    Q32I_       _V_Q14I_Ealfa;
    Q32I_       _V_Q14I_Ebeta;
    Q32I_       _V_Q32I_K1_alfa_tmp;
    Q32I_       _V_Q32I_K1_beta_tmp;
    
    Q32I_       _P_Q14I_PLL_Ki;
    Q32I_       _P_Q14I_Ts;
    Q32I_       _P_Q14I_Ws;
    Q32I_       _P_Q14I_H1;
    Q32I_       _P_Q14I_K1;
    Q32I_       _P_Q14I_Rs;
    Q32I_       _P_Q14I_Ld;
    Q32I_       _P_Q14I_Lq;
    Q32I_       _P_Q10I_One_Over_Ld;
    Q32I_       _P_Q14I_Rs_Over_Ld;
    Q32I_       _P_Q14I_Ld_Lq_Over_Ld;
}ST_SMO_CONTROL_T;

/**********************************************************************************************
Function: Est_Flux_Init_F
Description: 磁链观测器初始化
Input: 无
Output: 无
Input_Output: 磁链观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Flux_Init_T(ST_FLUX_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: Est_Flux_F
Description: 磁链观测器计算
Input: 无
Output: 无
Input_Output: 磁链观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_Flux_T(ST_FLUX_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: Est_SMO_Init_F
Description: 滑模观测器初始化
Input: 无
Output: 无
Input_Output: 滑模观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_SMO_Init_T(ST_SMO_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: Est_SMO_F
Description: 滑模观测器计算
Input: 无
Output: 无
Input_Output: 滑模观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_SMO_T(ST_SMO_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: Est_SMO_Study_T
Description: 滑模观测器参数学习
Input: 无
Output: 无
Input_Output: 滑模观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Est_SMO_Study_T(ST_SMO_CONTROL_T* pCTRL);

#endif /* MotorEst_H */
