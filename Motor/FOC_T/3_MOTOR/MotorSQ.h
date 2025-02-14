/**************************************************************************************************
*     File Name :                        MotorSQ.h
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             无感方波头文件
**************************************************************************************************/
#ifndef MotorSQ_H
#define MotorSQ_H

#include "Math.h"

typedef enum
{
    ING,
    SUCS,
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
    
    Q32I_   _I_Q12I_Ia_Data;
    Q32I_   _I_Q12I_Ib_Data;
    Q32I_   _I_Q12I_Ic_Data;
    Q32I_   _O_Q12I_Ia_Offset;
    Q32I_   _O_Q12I_Ib_Offset;
    Q32I_   _O_Q12I_Ic_Offset;
    
    Q32I_   _I_Q12I_Ishunt_1_Data;
    Q32I_   _I_Q12I_Ishunt_2_Data;
    Q32I_   _O_Q12I_Ishunt_1_Offset;
    Q32I_   _O_Q12I_Ishunt_2_Offset;
    
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
    
    Q32U_   _P_Q16U_boot_tl;
    Q32U_   _P_Q16U_boot_num;
    Q32U_   _P_Q16U_boot_time;
    Q32U_   _P_Q12U_boot_duty;
}ST_MS_BOOT;

typedef struct{
    UN_MS_FLAG  Flag;
    
    ST_RAMP_T   Ramp_Brake_Duty;
    
    Q32U_   _O_Q12U_brake_duty;
    
    Q32U_   _V_Q32U_cnt;
    
    Q32U_   _P_Q16U_no_time;
    Q32U_   _P_Q16U_slow_time;
    Q32U_   _P_Q16U_short_time;
    Q32U_   _P_Q12U_duty_max;
}ST_BRAKE_CONTROL;

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
Function: MotorSQ_Offset_Check_Three
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Offset_Check_Three(ST_MS_OFFSET* pMS_OFFSET);

/**********************************************************************************************
Function: MotorSQ_Offset_Check_One
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Offset_Check_One(ST_MS_OFFSET* pMS_OFFSET);

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
Function: MotorSQ_Brake_Init
Description: 刹车控制初始化
Input: 无
Output: 无
Input_Output: 刹车控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Brake_Init(ST_BRAKE_CONTROL* pBRAKE_CONTROL);

/**********************************************************************************************
Function: MotorSQ_Brake
Description: 刹车控制占空比计算
Input: 无
Output: 无
Input_Output: 刹车控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Brake(ST_BRAKE_CONTROL* pBRAKE_CONTROL);

#endif /* MotorSQ_H */
