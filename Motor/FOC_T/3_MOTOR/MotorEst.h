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

//typedef struct
//{
//    float ElecFreqHz;
//    float ElecFreqHz_Filter;
//    float AngleRad;
//    float AngleSpeed;
//    
//    float AngleRad_HFI;  
//    float AngleRad_ERROR;    
//    
//    float Ud_HFI;     
//    
//    uint8_t cnt;
//    uint8_t cnt_1;
//    float SIGN;
//    float Id_LPF;
//    float Iq_LPF;
//    float Id_HPF;
//    float Iq_HPF;
//    float Id_Last;
//    float Iq_Last;
//    
//    float Ud_Ref;     
//    float Ud_Freq;       
//    float Udq_Coeff;     
//    float Speed;  
//    float Ts;
//    ST_PID_POS        Pll_Pid;      /*!< Internal Variable: The PLL PID in FSO */
//}ST_HFI_CONTROL;

typedef struct
{
    Q08U_       Est_State_Flag;
    ST_PID_POS_T    PID_PLL;
    ST_FILTER_T     FL_SRAD;
    ST_TRIG_T       TG_Triangle;

    Q32I_       _O_Q28U_Angle_tmp;
    Q32I_       _I_Q14I_Ualfa;
    Q32I_       _I_Q14I_Ubeta;
    Q32I_       _I_Q14I_Ialfa;
    Q32I_       _I_Q14I_Ibeta;
    
    Q32I_       _V_Q14I_R_set;
    Q32I_       _V_Q14I_Yalfa;
    Q32I_       _V_Q14I_Ybeta;
    Q32I_       _V_Q14I_Nalfa;
    Q32I_       _V_Q14I_Nbeta;
    Q32I_       _V_Q14I_Nn2;
    ST_56_SPLIT _V_Q56I_Valfa;
    ST_56_SPLIT _V_Q56I_Vbeta;
    ST_56_SPLIT _V_Q56I_Xalfa_tmp;
    ST_56_SPLIT _V_Q56I_Xbeta_tmp;
    Q32I_       _V_Q14I_Xalfa;
    Q32I_       _V_Q14I_Xbeta;
    
    Q32I_       _P_Q14I_Ts;
    Q32I_       _P_Q14I_Gamma;
    Q32I_       _P_Q14I_Rs_Coeff;
    Q32I_       _P_Q14I_Rs;
    Q32I_       _P_Q14I_Ls;
    Q32I_       _P_Q14I_Flux2;
}ST_FLUX_CONTROL_T;

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
    
    Q32I_       _V_Q28I_Aalfa_tmp;
    Q32I_       _V_Q28I_Abeta_tmp;
    Q32I_       _V_Q14I_Aalfa;
    Q32I_       _V_Q14I_Abeta;
    Q32I_       _V_Q28I_ERRalfa_tmp;
    Q32I_       _V_Q28I_ERRbeta_tmp;
    Q32I_       _V_Q28I_Ealfa_tmp;
    Q32I_       _V_Q28I_Ebeta_tmp;
    Q32I_       _V_Q14I_Ealfa;
    Q32I_       _V_Q14I_Ebeta;
    
    Q32I_       _P_Q14I_Ts;
    Q32I_       _P_Q10I_K1;
    Q32I_       _P_Q14I_K2;
    Q32I_       _P_Q14I_Limit;
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

#endif /* MotorEst_H */
