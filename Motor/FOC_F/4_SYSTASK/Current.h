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
//保护时间除号后面的时间是任务周期，只需要填除号之前的时间即可
//除32说明该任务32ms执行一次，最小分辨率就是32ms，然后系统会取整
//比如填96，就是96ms触发，填120也是96ms触发，只有填128，才是128ms触发
#define CURRENT_PROTECT_LEVEL           3                                   //过流保护档位

#define CURRENT_PROTECT_LEVEL_1_TL      (30.0f)                             //A，过流保护阈值
#define CURRENT_PROTECT_LEVEL_1_TIME    ((Q32U_)(100.0f /32.0f))            //ms，过流保护时间

#define CURRENT_PROTECT_LEVEL_2_TL      (35.0f)                             //A，过流保护阈值
#define CURRENT_PROTECT_LEVEL_2_TIME    ((Q32U_)(1000.0f /32.0f))           //ms，过流保护时间

#define CURRENT_PROTECT_LEVEL_3_TL      (40.0f)                             //A，过流保护阈值
#define CURRENT_PROTECT_LEVEL_3_TIME    ((Q32U_)(10000.0f /32.0f))          //ms，过流保护时间

typedef struct{
    float F_current_protect_tl;
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
