/**************************************************************************************************
*     File Name :                        Voltage.h
*     Library/Module Name :              SysTask
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电压保护头文件
**************************************************************************************************/
#ifndef Voltage_H
#define Voltage_H

#include "SysTask.h"

//电压保护
#define LOW_VOLTAGE_PROTECT_LEVEL_TL        (Q14I_VOLTAGE_MOTOR_TO_PU(10.0f))           //V，低压保护阈值
#define LOW_VOLTAGE_PROTECT_LEVEL_TIME      (100U)                                      //ms，低压保护时间

#define OVER_VOLTAGE_PROTECT_LEVEL_TL       (Q14I_VOLTAGE_MOTOR_TO_PU(28.0f))           //V，过压保护阈值
#define OVER_VOLTAGE_PROTECT_LEVEL_TIME     (100U)                                      //ms，过压保护时间

typedef struct{
    Q32I_ Q16I_voltage_protect_tl;
    Q32U_ Q16U_voltage_protect_time;
    
    Q32U_ Q16U_voltage_protect_cnt;
}ST_VOLTAGE_PROTECT;

/**********************************************************************************************
Function: Voltage_Protect_Flow
Description: 电压保护控制
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Voltage_Protect_Flow(ST_SYSTEM_TASK*  pST);
    
#endif /* Voltage_H */
