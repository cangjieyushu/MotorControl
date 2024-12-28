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
    ST_PID_POS_F    PID_PLL;
    ST_FILTER_F     FL_SRAD;
    ST_TRIG_F       TG_Triangle;

    float       _I_F_Ualfa;
    float       _I_F_Ubeta;
    float       _I_F_Ialfa;
    float       _I_F_Ibeta;
    float       _I_F_IdRef;
    
    float       _V_F_Yalfa;
    float       _V_F_Ybeta;
    float       _V_F_Nalfa;
    float       _V_F_Nbeta;
    float       _V_F_Nn2;
    float       _V_F_Ealfa;
    float       _V_F_Ebeta;
    float       _V_F_Xalfa;
    float       _V_F_Xbeta;
    
    float       _P_F_Ts;
    float       _P_F_Gamma;
    float       _P_F_Rs;
    float       _P_F_Ld;
    float       _P_F_Ls;
    float       _P_F_Flux2;
}ST_FLUX_CONTROL_F;

typedef struct
{
    ST_PID_POS_F    PID_PLL;
    ST_FILTER_F     FL_SRAD;
    ST_TRIG_F       TG_Triangle;

    float       _I_F_Ualfa;
    float       _I_F_Ubeta;
    float       _I_F_Ialfa;
    float       _I_F_Ibeta;
    
    float       _V_F_Aalfa;
    float       _V_F_Abeta;
    float       _V_F_ERRalfa;
    float       _V_F_ERRbeta;
    float       _V_F_Ealfa;
    float       _V_F_Ebeta;
    
    float       _P_F_Ts;
    float       _P_F_K1;
    float       _P_F_K2;
    float       _P_F_Rs;
    float       _P_F_Ld;
    float       _P_F_Lq;
    float       _P_F_One_Over_Ld;
    float       _P_F_Rs_Over_Ld;
    float       _P_F_Ld_Lq_Over_Ld;
}ST_SMO_CONTROL_F;

typedef enum
{
    EM_HALL_STUDY_INIT,
    EM_HALL_STUDY_CW,
    EM_HALL_STUDY_CCW,
    EM_HALL_STUDY_FINISH,
}EM_HALL_STUDY_FLOW;

typedef struct
{
    float I_Target_Speed;
    float I_Position_Error;
    
    float O_Follow_Speed;
    
    float P_K1;
    float P_K2;
}ST_POSITION_CONTROL;

typedef struct
{
    float Hall_Dir;
    float Set_Dir;
    
    Q08U_ Switch_Phase_Flag;
    
    Q08U_ HallLastLevel;
    Q08U_ HallCurrentLevel;
    
    Q32U_ HallCount_tmp[6];
    Q32U_ HallLastCount;
    Q32U_ HallCurrentCount;
    Q32U_ HallSpeedCount;  
    
    Q32U_ HallStallCount;           
    Q32U_ HallStallLastCount;       
    Q32U_ HallStall_cnt;   
    
    float AngleRad;                   
    float AngleRad_Hall;         
    
    float ElecFreqHz;                 
    float ElecFreqHz_Filter;  
    
    
    EM_HALL_STUDY_FLOW HS_Flow;
    ST_RAMP_F AngleRadRamp;   
    Q08U_ HS_Sector_Tab_Init[6];
    float HS_Angle_Tab_Init[6];
    float HS_Angle_Tab_CW_Init[6];
    float HS_Angle_Tab_CCW_Init[6];
    
    Q08U_ HS_Sector_cnt;  
    Q08U_ HS_Sector_tmp[10];  
    float HS_Angle_tmp[10];
    
    float HS_Angle_tmp_1[20];  
    float HS_Angle_tmp_2[20];  
    float HS_Angle_tmp_3[20];  
    float HS_Angle_tmp_4[20];  
    float HS_Angle_tmp_5[20];  
    float HS_Angle_tmp_6[20];  
    
    Q08U_ HS_Sector_Tab[8];  
    float HS_Angle_Tab[8];   
    float HS_Angle_Tab_CW[8];   
    float HS_Angle_Tab_CCW[8];   
    
    Q08U_ HS_cnt;
    
      
    Q08U_ I_Hall_Study_Flag;
    float I_Target_Dir;   
    float P_Freq_Filter_Coeff;
    float P_Ts;        
    float P_TIM_FreqHz;  
    Q32U_ P_TIM_Max_Count;  
    Q32U_ P_HallStallTime;   
    
    float P_HS_Ud;   
    Q08U_ P_HS_num;      
}ST_HALL_CONTROL_F;

/**********************************************************************************************
Function: Est_Flux_Init_F
Description: 磁链观测器初始化
Input: 无
Output: 无
Input_Output: 磁链观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void Est_Flux_Init_F(ST_FLUX_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: Est_Flux_F
Description: 磁链观测器计算
Input: 无
Output: 无
Input_Output: 磁链观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void Est_Flux_F(ST_FLUX_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: Est_SMO_Init_F
Description: 滑模观测器初始化
Input: 无
Output: 无
Input_Output: 滑模观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void Est_SMO_Init_F(ST_SMO_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: Est_SMO_F
Description: 滑模观测器计算
Input: 无
Output: 无
Input_Output: 滑模观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void Est_SMO_F(ST_SMO_CONTROL_F* pCTRL);

float Hallest_Angle_Mean(float* DATA, ST_HALL_CONTROL_F* pCTRL);
void Hallest_Study_Task_Flow(ST_HALL_CONTROL_F* pCTRL);
void Hallest_Study_VF(ST_HALL_CONTROL_F* pCTRL);
void Hallest_Study_Self(ST_HALL_CONTROL_F* pCTRL);
void Hallest_Angle_Initial(ST_HALL_CONTROL_F* pCTRL);
void Hallest_Init(ST_HALL_CONTROL_F* pCTRL);
void Hallest_High_Speed_Anlge(ST_HALL_CONTROL_F* pCTRL);
void Hallest_Speed_Cal(ST_HALL_CONTROL_F* pCTRL);
void Hallest_Angle_Inc(ST_HALL_CONTROL_F* pCTRL);

#endif /* MotorEst_H */
