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
//保护时间除号后面的时间是任务周期，只需要填除号之前的时间即可
//除32说明该任务32ms执行一次，最小分辨率就是32ms，然后系统会取整
//比如填96，就是96ms触发，填120也是96ms触发，只有填128，才是128ms触发
#define OVER_SPEED_PROTECT_LEVEL_TL         (Q14I_FREQ_MOTOR_TO_PU(2000.0f))    //Hz，超速保护阈值
#define OVER_SPEED_PROTECT_LEVEL_TIME       ((Q32U_)(1000.0f/64.0f))            //ms，超速保护时间

#define LOW_SPEED_PROTECT_LEVEL_TL          (Q14I_FREQ_MOTOR_TO_PU(10.0f))      //Hz，低速保护阈值
#define LOW_SPEED_PROTECT_LEVEL_TIME        ((Q32U_)(1000.0f/64.0f))            //ms，低速保护时间

typedef struct{
    Q32I_ Q16I_speed_protect_tl;
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
