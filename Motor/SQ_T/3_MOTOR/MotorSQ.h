/**************************************************************************************************
*     File Name :                        MotorSQ.h
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             无感方波头文件
**************************************************************************************************/
#ifndef MotorFoc_H
#define MotorFoc_H

#include "Math.h"
#include "PmsmPara.h"

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
    SWITCH_CURRENT,
    SWITCH_FLUX,
    SWITCH_BEMF,
    SWITCH_CMP,
}EM_SWITCH_FLOW;

typedef enum{
    SQUARE_DIAG_ING,
    SQUARE_CROSS_ING,
    SQUARE_CROSS_SUCC,
    SQUARE_CROSS_FAIL,
    SQUARE_SWITCH_ING,
    SQUARE_SWITCH_SUCC,
}EM_SQUARE_FLOW;

typedef enum
{
    ING,
    SUCC,
    FAIL,
}EM_FALG_STATE;

typedef union{
    ALL     all;
    struct{
        BIT b0_init         :1;
        BIT b1_succ         :1;
        BIT b2_fail         :1;
    }bit;
}UN_MS_FLAG;

typedef struct
{
    UN_MS_FLAG  Flag;
    
    Q32I_   _I_Q12I_IPHASE_ADC;
    Q32I_   _O_Q12I_IPHASE_OFFSET;
    
    Q32U_   _V_Q32U_cnt;
    
    Q32U_   _P_Q16U_offset_max;
    Q32U_   _P_Q16U_offset_min;
    Q32U_   _P_Q16U_check_num;
}ST_MS_OFFSET;

typedef struct
{
    UN_MS_FLAG  Flag;
    
    Q32U_   _I_Q12I_BEMF_U_ADC;
    Q32U_   _I_Q12I_BEMF_V_ADC;
    Q32U_   _I_Q12I_BEMF_W_ADC;
    
    Q32U_   _V_Q32U_cnt;
    Q32U_   _V_Q32U_time_cnt;
    Q32U_   _V_Q32U_switch_cnt;
    Q32U_   _V_Q32U_phase_cnt;
    
    Q32U_   _P_Q16U_check_tl;
    Q32U_   _P_Q16U_check_num;
    Q32U_   _P_Q16U_flying_filter;
    Q32U_   _P_Q16U_flying_time;
    Q32U_   _P_Q12U_vbus_max_val;
}ST_MS_FLYING;

typedef struct
{
    UN_MS_FLAG  Flag;
    
    Q32U_   _I_Q12I_BEMF_U_ADC;
    Q32U_   _I_Q12I_BEMF_V_ADC;
    Q32U_   _I_Q12I_BEMF_W_ADC;
    
    Q32U_   _V_Q32U_cnt;
    Q32U_   _V_Q32U_time_cnt;
    
    Q32U_   _P_Q16U_boot_tl;
    Q32U_   _P_Q16U_boot_num;
    Q32U_   _P_Q16U_boot_time;
    Q32U_   _P_Q12U_boot_duty;
}ST_MS_BOOT;

typedef struct
{
    UN_MS_FLAG  Flag;
    
    Q32U_   _I_Q12I_Position_Current_VAL[6];
    
    Q32U_   _V_Q32U_cnt;
    Q32U_   _V_Q12U_duty_set;
    
    Q32U_   _P_Q16U_position_tl;
    Q32U_   _P_Q12U_position_duty;
    Q32U_   _P_Q12U_vbus_max_val;
}ST_MS_POSITION;

typedef struct{
    UN_MS_FLAG  Flag;
    
    ST_RAMP     Ramp_Brake_Duty;
    
    Q32U_   _O_Q12U_brake_duty;
    
    Q32U_   _V_Q32U_cnt;
    
    Q32U_   _P_Q16U_no_time;
    Q32U_   _P_Q16U_slow_time;
    Q32U_   _P_Q16U_short_time;
    Q32U_   _P_Q12U_duty_max;
}ST_BRAKE_CONTROL;

typedef struct
{
    Q32U_   _I_Q32U_time_count;
    
    Q32U_   _V_Q32U_60_degree_cnt_last;
    Q32U_   _V_Q32U_60_degree_cnt_tmp[10];
    
    Q32U_   _O_Q32U_60_degree_cnt;
    
    Q32U_   _P_Q32U_hall_tim_freq;
    Q32U_   _P_Q32U_hall_tim_max_cnt;
}ST_FREQ_CAL;

typedef struct
{
    UN_MS_FLAG  Flag;
    
    Q32I_   _I_Q12I_BEMF_ZI_VAL;
    Q32I_   _I_Q12I_VBUS_VAL;
    
    Q32U_   _V_Q32U_cnt;
    Q32U_   _V_Q32U_time_cnt;
    
    Q32U_   _P_Q06U_rise_tl;
    Q32U_   _P_Q06U_fall_tl;
    Q32U_   _P_Q08U_filter;
    Q32U_   _P_Q16U_current_filter;
}ST_MS_DIAG;

typedef struct
{
    UN_MS_FLAG  Flag;
    
    Q32I_   _I_Q12I_BEMF_ON_VAL;
    Q32I_   _I_Q12I_BEMF_ZI_VAL;
    Q32I_   _I_Q12I_BEMF_OF_VAL;
    
    Q32U_   _V_Q32U_cnt;
    Q32U_   _V_Q32U_time_cnt;
    Q32U_   _V_Q32U_switch_cnt;
    
    Q32U_   _P_Q06U_rise_tl;
    Q32U_   _P_Q06U_fall_tl;
    Q32U_   _P_Q08U_filter;
    Q32U_   _P_Q16U_current_filter;
    
    Q32U_   _P_Q14U_to_flux_freq;
    Q32U_   _P_Q16U_to_flux_num;
}ST_MS_CURRENT;

typedef struct
{
    UN_MS_FLAG  Flag;
    
    Q32I_   _I_Q12I_BEMF_ON_VAL;
    Q32I_   _I_Q12I_BEMF_ZI_VAL;
    Q32I_   _I_Q12I_BEMF_OF_VAL;
    
    Q32U_   _V_Q32U_cnt;
    Q32U_   _V_Q32U_time_cnt;
    Q32U_   _V_Q32U_switch_cnt;
    
    Q32U_   _P_Q06U_rise_tl;
    Q32U_   _P_Q06U_fall_tl;
    Q32U_   _P_Q08U_filter;
    
    Q32U_   _P_Q14U_to_current_freq;
    Q32U_   _P_Q16U_to_current_num;
    
    Q32U_   _P_Q14U_to_bemf_freq;
    Q32U_   _P_Q12U_to_bemf_duty;
    Q32U_   _P_Q16U_to_bemf_num;
}ST_MS_FLUX;

typedef struct
{
    UN_MS_FLAG  Flag;
    
    Q32I_   _I_Q12I_BEMF_ON_VAL;
    Q32I_   _I_Q12I_BEMF_ZI_VAL;
    Q32I_   _I_Q12I_BEMF_OF_VAL;
    
    Q32U_   _V_Q32U_cnt;
    Q32U_   _V_Q32U_time_cnt;
    
    Q32U_   _P_Q08U_filter;
    Q32U_   _P_Q06U_coeff;
    
    Q32U_   _P_Q14U_to_flux_freq;
    Q32U_   _P_Q12U_to_flux_duty;
    Q32U_   _P_Q16U_to_flux_num;
}ST_MS_BEMF;

typedef struct
{
    UN_MS_FLAG  Flag;
    
}ST_MS_CMP;

typedef struct{
    UN_MS_FLAG  Flag;
    
    Q32U_   _V_Q32U_cnt;
    Q32U_   _V_Q32U_current_cnt;
    Q32U_   _V_Q32U_switch_cnt;
    
    Q32U_   _P_Q16U_current_error_time;
    Q32U_   _P_Q16U_error_time;
    Q32U_   _P_Q06U_switch_coeff;
}ST_STALL_CONTROL;

typedef struct
{
    UN_MS_FLAG  Flag;
    ST_RAMP     Ramp_Duty;
    
    Q32U_   _I_Q14I_duty_vr;
    
    Q32U_   _I_Q12I_duty_freq;
    Q32U_   _I_Q12I_duty_ibus;
    Q32U_   _I_Q12I_duty_iphase;
    
    Q32U_   _O_Q12I_duty_set;
    Q32U_   _O_Q16U_duty_final_val;
    Q32U_   _O_Q16U_arr_set;
    
    Q32U_   _P_Q12U_low_to_high_duty;
    Q32U_   _P_Q12U_high_to_low_duty;
    Q32U_   _P_Q14U_low_pwm_freq;
    Q32U_   _P_Q14U_high_pwm_freq;
    
    Q32U_   _P_Q12U_duty_max;
    Q32U_   _P_Q12U_duty_min;
    Q32U_   _P_Q14U_motor_freq_max;
    Q32U_   _P_Q14U_motor_freq_min;
}ST_PWM_CONTROL;

typedef struct{
    EM_SQUARE_FLOW      SQ_Flow;
    EM_SWITCH_FLOW      SW_Math;
    
    ST_MS_DIAG          MS_DIAG;
    ST_MS_CURRENT       MS_CURRENT;
    ST_MS_FLUX          MS_FLUX;
    ST_MS_BEMF          MS_BEMF;
    ST_MS_CMP           MS_CMP;
    
    EM_DIRECTION        DIR_Set;
    EM_DIRECTION        DIR_Target;
    EM_SECTOR_NUM       Sector;
    EM_SECTOR_NUM       Sector_Last;
    
    ST_FREQ_CAL         FREQ_CAL;
    
    ST_PWM_CONTROL      PWM_CTRL;
    ST_STALL_CONTROL    STALL_CTRL;
    
    ST_RAMP             Ramp_Freq;
    Q32U_               Q14U_iphase_max_pu;
    Q32U_               Q14U_ibus_max_pu;
    Q32U_               Q14U_ibrake_max_pu;
    Q32U_               Q14U_vbus_max_pu;
    
    ST_FILTER           FL_Iphase;
    ST_FILTER           FL_Freq;
    ST_FILTER           FL_Ibus;
    ST_FILTER           FL_Ibrake;
    
    ST_PID_INC          PID_Iphase;
    ST_PID_INC          PID_Freq;
    ST_PID_INC          PID_Ibus;
    ST_PID_INC          PID_Ibrake;
    
    Q32I_               Q12I_BEMF_ADC_tmp[3];
    Q32I_               Q12I_VBUS_VAL;
    Q32I_               Q12I_IPHASE_ADC;
    Q32I_               Q12I_IPHASE_OFFSET;
    Q32I_               Q14I_IPHASE_PU;
    
    Q32U_               Q32U_switch_cnt;
}ST_MS_CONTROL;

extern EM_CHANNEL_NUM ADC_VAL_Table[6][3];
extern EM_SECTOR_NUM Position_CW[6][2];
extern EM_SECTOR_NUM Last_Sector[6];
extern EM_SECTOR_NUM Next_Sector[6];

/**********************************************************************************************
Function: MotorSQ_Init
Description: 方波算法初始化
Input: 无
Output: 无
Input_Output: 方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_Init(ST_MS_CONTROL* pMS_CTRL);

/**********************************************************************************************
Function: MotorSQ_Flying_Init
Description: 顺风启动初始化
Input: 无
Output: 无
Input_Output: 方波控制指针，顺风检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_Flying_Init(ST_MS_CONTROL* pMS_CTRL, ST_MS_FLYING* pMS_FLYING);

/**********************************************************************************************
Function: MotorSQ_Offset_Check_Init
Description: 偏置检测初始化
Input: 无
Output: 无
Input_Output: 偏置检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Offset_Check_Init(ST_MS_OFFSET* pMS_OFFSET);

/**********************************************************************************************
Function: MotorSQ_Offset_Check
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Offset_Check(ST_MS_OFFSET* pMS_OFFSET);
    
/**********************************************************************************************
Function: MotorSQ_Flying_Check_Init
Description: 顺风检测初始化
Input: 无
Output: 无
Input_Output: 顺风检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Flying_Check_Init(ST_MS_FLYING* pMS_FLYING);

/**********************************************************************************************
Function: MotorSQ_Flying_Check
Description: 顺风检测计算
Input: 无
Output: 无
Input_Output: 顺风检测指针，频率计算指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Flying_Check(ST_MS_FLYING* pMS_FLYING, ST_FREQ_CAL* pFREQ_CAL, ST_MS_CONTROL* pMS_CTRL);
    
/**********************************************************************************************
Function: MotorSQ_Boot_Check_Init
Description: 自举控制初始化
Input: 无
Output: 无
Input_Output: 自举控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Boot_Check_Init(ST_MS_BOOT* pMS_BOOT);

/**********************************************************************************************
Function: MotorSQ_Boot_Check
Description: 自举控制计算
Input: 无
Output: 无
Input_Output: 自举控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Boot_Check(ST_MS_BOOT* pMS_BOOT);

/**********************************************************************************************
Function: MotorSQ_Pluse_Positon_Init
Description: 脉冲定位初始化
Input: 无
Output: 无
Input_Output: 脉冲定位指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Pluse_Positon_Init(ST_MS_POSITION* MS_POSITION);

/**********************************************************************************************
Function: MotorSQ_Pluse_Positon
Description: 脉冲定位计算
Input: 无
Output: 无
Input_Output: 脉冲定位指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Pluse_Positon(ST_MS_POSITION* MS_POSITION, ST_MS_CONTROL* pMS_CTRL);

/**********************************************************************************************
Function: MotorSQ_Brake_Init
Description: 刹车控制初始化
Input: 无
Output: 无
Input_Output: 刹车控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Brake_Init(ST_BRAKE_CONTROL* pBRAKE_CONTROL, ST_MS_CONTROL* pMS_CTRL);

/**********************************************************************************************
Function: MotorSQ_Brake
Description: 刹车控制占空比计算
Input: 无
Output: 无
Input_Output: 刹车控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Brake(ST_BRAKE_CONTROL* pBRAKE_CONTROL, ST_MS_CONTROL* pMS_CTRL);

/**********************************************************************************************
Function: MotorSQ_DIAG_Init
Description: 续流检测初始化
Input: 无
Output: 无
Input_Output: 续流检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_DIAG_Init(ST_MS_DIAG* pMS_DIAG);

/**********************************************************************************************
Function: MotorSQ_DIAG_Zero_Cross
Description: 续流检测计算
Input: 无
Output: 无
Input_Output: 续流检测指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_DIAG_Zero_Cross(ST_MS_DIAG* pMS_DIAG, ST_MS_CONTROL* pMS_CTRL);

/**********************************************************************************************
Function: MotorSQ_CURRENT_Init
Description: 电流换向初始化
Input: 无
Output: 无
Input_Output: 电流换向指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_CURRENT_Init(ST_MS_CURRENT* pMS_CURRENT);

/**********************************************************************************************
Function: MotorSQ_CURRENT_Zero_Cross
Description: 电流换向计算
Input: 无
Output: 无
Input_Output: 电流换向指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_CURRENT_Zero_Cross(ST_MS_CURRENT* pMS_CURRENT, ST_MS_CONTROL* pMS_CTRL);

/**********************************************************************************************
Function: MotorSQ_FLUX_Init
Description: 磁链换向初始化
Input: 无
Output: 无
Input_Output: 磁链换向指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_FLUX_Init(ST_MS_FLUX* pMS_FLUX);

/**********************************************************************************************
Function: MotorSQ_FLUX_Zero_Cross
Description: 磁链换向计算
Input: 无
Output: 无
Input_Output: 磁链换向指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_FLUX_Zero_Cross(ST_MS_FLUX* pMS_FLUX, ST_MS_CONTROL* pMS_CTRL);

/**********************************************************************************************
Function: MotorSQ_BEMF_Init
Description: 反电动势换向初始化
Input: 无
Output: 无
Input_Output: 反电动势换向指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_BEMF_Init(ST_MS_BEMF* pMS_BEMF);

/**********************************************************************************************
Function: MotorSQ_BEMF_Zero_Cross
Description: 反电动势换向计算
Input: 无
Output: 无
Input_Output: 反电动势换向指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_BEMF_Zero_Cross(ST_MS_BEMF* pMS_BEMF, ST_MS_CONTROL* pMS_CTRL);

/**********************************************************************************************
Function: MotorSQ_CMP_Init
Description: 比较器换向初始化
Input: 无
Output: 无
Input_Output: 比较器换向指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_CMP_Init(ST_MS_CMP* pMS_CMP);

/**********************************************************************************************
Function: MotorSQ_CMP_Zero_Cross
Description: 比较器换向计算
Input: 无
Output: 无
Input_Output: 比较器换向指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_CMP_Zero_Cross(ST_MS_CMP* pMS_CMP, ST_MS_CONTROL* pMS_CTRL);

/**********************************************************************************************
Function: MotorSQ_Freq_Cal_Init
Description: 频率计算初始化
Input: 无
Output: 无
Input_Output: 频率计算指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_Freq_Cal_Init(ST_FREQ_CAL* pFREQ_CAL);

/**********************************************************************************************
Function: MotorSQ_Freq_Cal
Description: 频率计算
Input: 无
Output: 无
Input_Output: 频率计算指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_Freq_Cal(ST_FREQ_CAL* pFREQ_CAL, ST_MS_CONTROL* pMS_CTRL);

/**********************************************************************************************
Function: MotorSQ_PWM_Freq_Switch_Init
Description: 载频控制初始化
Input: 无
Output: 无
Input_Output: 载频控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_PWM_Freq_Switch_Init(ST_PWM_CONTROL* pPWM_CTRL);

/**********************************************************************************************
Function: MotorSQ_PWM_Freq_Switch
Description: 载频控制计算
Input: 无
Output: 无
Input_Output: 载频控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_PWM_Freq_Switch(ST_PWM_CONTROL* pPWM_CTRL);

/**********************************************************************************************
Function: MotorSQ_Stall_Check_Init
Description: 堵转检测初始化
Input: 无
Output: 无
Input_Output: 堵转检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_Stall_Check_Init(ST_STALL_CONTROL* pSTALL_CTRL, ST_MS_CONTROL* pMS_CTRL);

/**********************************************************************************************
Function: MotorSQ_Stall_Check
Description: 堵转检测计算
Input: 无
Output: 无
Input_Output: 堵转检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Stall_Check(ST_STALL_CONTROL* pSTALL_CTRL, ST_MS_CONTROL* pMS_CTRL);

/**********************************************************************************************
Function: MotorSQ_Ibus_Cal
Description: 母线电流计算
Input: 无
Output: 无
Input_Output: 方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_Ibus_Cal(ST_MS_CONTROL* pMS_CTRL);

#endif /* MotorSQ_H */
