/**************************************************************************************************
*     File Name :                        Speed.h
*     Library/Module Name :              SysTask
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             速度保护头文件
**************************************************************************************************/
#ifndef Speed_H
#define Speed_H

#include "SysTask.h"

//速度保护
#define OVER_SPEED_PROTECT_LEVEL_TL         (MOTOR_POLE_PAIR*25000.0f/60.0f)    //rpm，超速保护阈值
#define OVER_SPEED_PROTECT_LEVEL_TIME       (1000U)                             //ms，超速保护时间

#define LOW_SPEED_PROTECT_LEVEL_TL          (MOTOR_POLE_PAIR*250.0f/60.0f)      //rpm，低速保护阈值
#define LOW_SPEED_PROTECT_LEVEL_TIME        (1000U)                             //ms，低速保护时间

typedef struct{
    float F_speed_protect_tl;
    Q32U_ Q16U_speed_protect_time;
    
    Q32U_ Q16U_speed_protect_cnt;
}ST_SPEED_PROTECT;

/**********************************************************************************************
Function: Speed_Protect_Flow
Description: 速度保护控制
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Speed_Protect_Flow(ST_SYSTEM_TASK*  pST);
    
#endif /* Speed_H */
