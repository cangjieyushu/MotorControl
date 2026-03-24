/**************************************************************************************************
*     File Name :                        MCSQ_BLDC.h
*     Library/Module Name :              MCSQ
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             无感方波头文件
**************************************************************************************************/

#ifndef MCSQ_BLDC_H
#define MCSQ_BLDC_H


#include "MATH.h"
#include "MATH_LPF_T.h"
#include "MATH_PID_T.h"
#include "MATH_RAMP_T.h"


typedef enum
{
    CW,
    CCW,
}EM_DIRECTION;

typedef enum
{
    U_CHANNEL_NUM,
    V_CHANNEL_NUM,
    W_CHANNEL_NUM,
}EM_CHANNEL_NUM;

typedef enum
{
    sector_1,
    sector_2,
    sector_3,
    sector_4,
    sector_5,
    sector_6,
}EM_SECTOR_NUM;

typedef enum{
    SWITCH_FLUX,
    SWITCH_BEMF,
    SWITCH_CMP,
}EM_SWITCH_FLOW;

typedef enum{
    SQUARE_DIAG_ING,
    SQUARE_CROSS_ING,
    SQUARE_CROSS_SUCC,
    SQUARE_SWITCH_SUCC,
}EM_SQUARE_FLOW;

typedef enum
{
    ING,
    SUCS,
    FAIL,
}EM_FLAG_STATE;

typedef struct
{
    Q32U_   _I_Q32U_Time_Count;
    Q32U_   _O_Q32U_Switch_cnt;
    
    Q32U_   _V_Q32U_60Deg_Time_cnt;
    Q32U_   _V_Q32U_60Deg_Time_cnt_last;
    Q32U_   _V_Q32U_60Deg_Time_cnt_tmp[6];
    Q32U_   _V_Q32U_60Deg_Time_cnt_Filter;
    
    Q32U_   _P_Q32U_Hall_Time_Freq;
    Q32U_   _P_Q32U_Hall_Time_Max_count;
}ST_FREQ_CAL;

typedef struct
{
    EM_DIRECTION            DIR_Set;
    EM_DIRECTION            DIR_Target;
    EM_SECTOR_NUM           Sector;
    EM_SECTOR_NUM           Sector_Last;
    
    ST_FREQ_CAL             Freq_Cal;
    
    ST_LPF_T                FL_Freq;
    ST_LPF_T                FL_Ibus;
    ST_LPF_T                FL_Iphase;
    
    EM_SQUARE_FLOW          SQ_Flow;
    EM_SWITCH_FLOW          SW_Math;
    
    Q32U_                   _V_Q12U_Bemf_ADC_tmp[3];
    Q32U_                   _V_Q12U_Bemf_ON_ADC;
    Q32U_                   _V_Q12U_Bemf_ZI_ADC;
    Q32U_                   _V_Q12U_Bemf_OF_ADC;
    
    Q32U_                   _V_Q12U_Vbus_ADC;
    Q32U_                   _V_Q12U_Iphase_ADC;
    Q32U_                   _V_Q12U_Iphase_ADC_Offset;
    
    Q32U_                   _V_Q14U_Iphase_pu;
    Q32U_                   _V_Q14U_Vbus_pu;
    
    Q32U_                   _P_Q14U_Iphase_Max_pu;
    Q32U_                   _P_Q14U_Ibus_Max_pu;
    Q32U_                   _P_Q14U_Vbus_Max_pu;
    Q32U_                   _P_Q28U_Freq_Scale;
}ST_MCSQ_BLDC;

typedef struct
{
    Q32U_   _V_Q32U_Offset_Check_cnt;
    
    Q32U_   _P_Q12U_Offset_Max;
    Q32U_   _P_Q12U_Offset_Min;
    Q32U_   _P_Q16U_Offset_Check_Count;
}ST_MCSQ_OFFSET;

typedef struct
{
    Q32U_   _V_Q32U_Flying_Low_Bemf_cnt;
    Q32U_   _P_Q16U_Flying_Check_cnt;
    Q32U_   _P_Q16U_Flying_Phase_cnt;
    
    Q32U_   _P_Q32U_Flying_Low_Bemf_TL;
    Q32U_   _P_Q16U_Flying_Low_Bemf_Count;
    Q32U_   _P_Q16U_Flying_Check_Filter;
}ST_MCSQ_FLYING;

typedef struct
{
    Q32U_   _V_Q32U_Boot_Low_Bemf_cnt;
    
    Q32U_   _P_Q32U_Boot_Low_Bemf_TL;
    Q32U_   _P_Q16U_Boot_Low_Bemf_Count;
    Q32U_   _P_Q14U_Boot_Duty_Set;
}ST_MCSQ_BOOT;

typedef struct
{
    Q32U_   _V_Q12U_Position_Iphase_ADC_tmp[6];
    
    Q32U_   _V_Q32U_Position_cnt;
    Q32U_   _V_Q14U_Position_Duty_PWMCount;
    
    Q32U_   _P_Q12U_Position_Iphase_TL;
    Q32U_   _P_Q14U_Position_Duty_Set;
}ST_MCSQ_POSITION;

typedef struct{
    ST_RAMP_T   Ramp_Brake_Duty;
    
    Q32U_   _O_Q32U_Brake_Finish_Flag;
    Q32U_   _O_Q14U_Brake_Duty_Set;
    
    Q32U_   _V_Q32U_Brake_cnt;
    
    Q32U_   _P_Q16U_NoBrake_Count;
    Q32U_   _P_Q16U_SlowBrake_Count;
    Q32U_   _P_Q16U_ShortBrake_Count;
}ST_MCSQ_BRAKE;

typedef struct
{
    Q32U_   _V_Q32U_DIAG_cnt;
    
    Q32U_   _P_Q14U_DIAG_Rise_tl;
    Q32U_   _P_Q14U_DIAG_Fall_tl;
    Q32U_   _P_Q16U_DIAG_Filter_Count;
}ST_MS_DIAG;

typedef struct
{
    Q32U_   _V_Q32U_Flux_cnt;
    Q32U_   _V_Q32U_Flux_to_Bemf_cnt;
    
    Q32U_   _P_Q14U_Flux_Rise_tl;
    Q32U_   _P_Q14U_Flux_Fall_tl;
    Q32U_   _P_Q16U_Flux_Filter_Count;
    Q32U_   _P_Q14U_Flux_to_Bemf_Freq;
    Q32U_   _P_Q14U_Flux_to_Bemf_Count;
}ST_MS_FLUX;

typedef struct
{
    Q32U_   _V_Q32U_Bemf_cnt;
    Q32U_   _V_Q32U_Bemf_to_Flux_cnt;
    
    Q32U_   _P_Q16U_Bemf_Filter_Count;
    Q32U_   _P_Q14U_Bemf_Delay_Coeff;
    Q32U_   _P_Q14U_Bemf_to_Flux_Freq;
    Q32U_   _P_Q14U_Bemf_to_Flux_Count;
}ST_MS_BEMF;

typedef struct
{
    Q32U_   _V_Q32U_temp;
}ST_MS_CMP;

typedef struct
{
    ST_RAMP_T   Ramp_Duty;
    
    Q08U_   PWM_Freq_Flag;
    
    Q32U_   _I_Q14U_Duty_VR;
    
    Q32U_   _I_Q14U_Duty_Freq;
    Q32U_   _I_Q14U_Duty_Ibus;
    Q32U_   _I_Q14U_Duty_Iphase;
    
    Q32U_   _O_Q14U_Duty_Set;
    Q32U_   _O_Q32U_Duty_PWMCount;
    Q32U_   _O_Q32U_PWMCount_Set;
    
    Q32U_   _P_Q14U_Low_to_High_Duty;
    Q32U_   _P_Q14U_High_to_Low_Duty;
    Q32U_   _P_Q32U_Start_PWMCount;
    Q32U_   _P_Q32U_Low_PWMCount;
    Q32U_   _P_Q32U_High_PWMCount;
    
    Q32U_   _P_Q14U_Duty_Max;
    Q32U_   _P_Q14U_Duty_Min;
    Q32U_   _P_Q14U_Motor_Freq_Max;
    Q32U_   _P_Q14U_Motor_Freq_Min;
    
    Q32U_   _P_Q32U_ADC_Delay_Value;
    Q32U_   _P_Q32U_ADC_Sample_Value;
    Q32U_   _P_Q32U_ADC_Solve_Value;
    
    Q32U_   _P_Q32U_Tim_Delay_Value;
}ST_PWM_CONTROL;

typedef struct{
    Q32U_   _V_Q32U_Stall_cnt;
    Q32U_   _V_Q32U_Stall_Switch_cnt;
    
    Q32U_   _P_Q16U_Stall_Count;
    Q32U_   _P_Q06U_Stall_Switch_Coeff;
}ST_STALL_CONTROL;

typedef struct{
    ST_MCSQ_BLDC            MCSQ_BLDC;
    
    ST_MCSQ_OFFSET          MCSQ_OFFSET;
    ST_MCSQ_FLYING          MCSQ_FLYING;
    ST_MCSQ_BOOT            MCSQ_BOOT;
    ST_MCSQ_POSITION        MCSQ_POSITION;
    ST_MCSQ_BRAKE           MCSQ_BRAKE;
    
    ST_MS_DIAG              MCSQ_DIAG;
    ST_MS_FLUX              MCSQ_FLUX;
    ST_MS_BEMF              MCSQ_BEMF;
    ST_MS_CMP               MCSQ_CMP;
    
    ST_RAMP_T               Ramp_Freq;
    ST_PID_INC_T            PID_Freq;
    ST_PID_INC_T            PID_Ibus;
    ST_PID_INC_T            PID_Iphase;
    
    ST_PWM_CONTROL          PWM_CTRL;
    
    ST_STALL_CONTROL        STALL_CTRL;
}ST_MCSQ_CONTROL;


extern EM_SECTOR_NUM Position_Sector[6][2];
extern EM_SECTOR_NUM Last_Sector[6];
extern EM_SECTOR_NUM Next_Sector[6];


/**********************************************************************************************
Function: MCSQ_Init
Description: 方波算法初始化
Input: 无
Output: 无
Input_Output: 方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_Init(ST_MCSQ_CONTROL* pMS_CTRL);

/**********************************************************************************************
Function: MCSQ_Flying_Init
Description: 顺风启动初始化
Input: 无
Output: 无
Input_Output: 方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_Flying_Init(ST_MCSQ_CONTROL* pMS_CTRL);

/**********************************************************************************************
Function: MCSQ_Freq_Cal
Description: 频率计算
Input: 无
Output: 无
Input_Output: 频率计算指针，方波控制指针，换相定时器
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_Freq_Cal(ST_FREQ_CAL* pFREQ_CAL, ST_MCSQ_CONTROL* pMS_CTRL, Q32U_ Q32U_Time_Count);

/**********************************************************************************************
Function: MCSQ_Ibus_Cal
Description: 母线电流计算
Input: 无
Output: 无
Input_Output: 方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_Ibus_Cal(ST_MCSQ_CONTROL* pMS_CTRL);

/**********************************************************************************************
Function: MCSQ_Offset_Check
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针，BLDC参数指针，电流采样输入
Return: 偏置检测状态，0：未完成，1：成功，2：失败
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCSQ_Offset_Check(ST_MCSQ_OFFSET* pOFFSET, ST_MCSQ_BLDC* pBLDC, Q32U_ Q12U_Iphase_adc_value);

/**********************************************************************************************
Function: MCSQ_Flying_Check
Description: 顺风检测计算
Input: 无
Output: 无
Input_Output: 顺风检测指针，BLDC参数指针，换相定时器
Return: 顺风检测状态，0：未完成，1：成功，2：失败
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCSQ_Flying_Check(ST_MCSQ_FLYING* pFLYING, ST_MCSQ_BLDC* pBLDC, Q32U_ Q32U_Time_Count);

/**********************************************************************************************
Function: MCSQ_Boot_Check
Description: 自举控制计算
Input: 无
Output: 无
Input_Output: 自举控制指针，BLDC参数指针
Return: 自举检测状态，0：未完成，1：成功
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCSQ_Boot_Check(ST_MCSQ_BOOT* pMS_BOOT, ST_MCSQ_BLDC* pBLDC);

/**********************************************************************************************
Function: MCSQ_Pluse_Positon
Description: 脉冲定位计算
Input: 无
Output: 无
Input_Output: 脉冲定位控制指针，BLDC参数指针，电流采样输入
Return: 脉冲定位检测状态，0：未完成，1：成功，2：失败
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCSQ_Pluse_Positon(ST_MCSQ_POSITION* MCSQ_POSITION, ST_MCSQ_BLDC* pBLDC, Q32U_ Q32U_Iphase_adc_value);

/**********************************************************************************************
Function: MCSQ_Brake
Description: 刹车控制占空比计算
Input: 无
Output: 无
Input_Output: 刹车控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_Brake(ST_MCSQ_BRAKE* pBRAKE_CONTROL);

/**********************************************************************************************
Function: MCSQ_DIAG
Description: 续流检测计算
Input: 无
Output: 无
Input_Output: 续流检测指针，BLDC参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_DIAG(ST_MS_DIAG* pMS_DIAG, ST_MCSQ_BLDC* pBLDC);

/**********************************************************************************************
Function: MCSQ_FLUX
Description: 磁链换向计算
Input: 无
Output: 无
Input_Output: 磁链换向指针，BLDC参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_FLUX(ST_MS_FLUX* pMS_FLUX, ST_MCSQ_BLDC* pBLDC);

/**********************************************************************************************
Function: MCSQ_BEMF
Description: 反电动势换向计算
Input: 无
Output: 无
Input_Output: 反电动势换向指针，BLDC参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_BEMF(ST_MS_BEMF* pMS_BEMF, ST_MCSQ_BLDC* pBLDC);

/**********************************************************************************************
Function: MCSQ_CMP
Description: 比较器换向计算
Input: 无
Output: 无
Input_Output: 比较器换向指针，BLDC参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_CMP(ST_MS_CMP* pMS_CMP, ST_MCSQ_BLDC* pBLDC);

/**********************************************************************************************
Function: MCSQ_PWM_Freq_Switch
Description: 载频控制计算
Input: 无
Output: 无
Input_Output: 载频控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_PWM_Freq_Switch(ST_PWM_CONTROL* pPWM_CTRL);

/**********************************************************************************************
Function: MCSQ_Stall_Check
Description: 堵转检测计算
Input: 无
Output: 无
Input_Output: 堵转检测指针
Return: 堵转检测状态，0：未完成，1：堵转，2：正常
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCSQ_Stall_Check(ST_STALL_CONTROL* pSTALL_CTRL, ST_MCSQ_CONTROL* pMS_CTRL);


#endif /* MCSQ_BLDC_H */
