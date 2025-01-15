/**************************************************************************************************
*     File Name :                        Current.h
*     Library/Module Name :              SysTask
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电流保护头文件
**************************************************************************************************/
#ifndef Current_H
#define Current_H

#include "SysTask.h"

//电流保护
#define CURRENT_PROTECT_LEVEL           3                                   //过流保护档位

#define CURRENT_PROTECT_LEVEL_1_TL      (Q14I_CURRENT_MOTOR_TO_PU(30.0f))   //A，过流保护阈值
#define CURRENT_PROTECT_LEVEL_1_TIME    (100U)                              //ms，过流保护时间

#define CURRENT_PROTECT_LEVEL_2_TL      (Q14I_CURRENT_MOTOR_TO_PU(35.0f))   //A，过流保护阈值
#define CURRENT_PROTECT_LEVEL_2_TIME    (1000U)                             //ms，过流保护时间

#define CURRENT_PROTECT_LEVEL_3_TL      (Q14I_CURRENT_MOTOR_TO_PU(40.0f))   //A，过流保护阈值
#define CURRENT_PROTECT_LEVEL_3_TIME    (10000U)                            //ms，过流保护时间

typedef struct{
    Q32U_ Q16U_current_protect_tl;
    Q32U_ Q16U_current_protect_time;
    
    Q32U_ Q16U_current_protect_cnt;
}ST_CURRENT_PROTECT;

/**********************************************************************************************
Function: Current_Protect_Flow
Description: 电流保护控制
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Current_Protect_Flow(ST_SYSTEM_TASK*  pST);
    
#endif /* Current_H */
