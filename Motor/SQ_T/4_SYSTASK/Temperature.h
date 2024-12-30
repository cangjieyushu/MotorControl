/**************************************************************************************************
*     File Name :                        Temperature.h
*     Library/Module Name :              SysTask
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             温度保护头文件
**************************************************************************************************/
#ifndef Temperature_H
#define Temperature_H

#include "SysTask.h"

//温度保护
//保护时间除号后面的时间是任务周期，只需要填除号之前的时间即可
//除32说明该任务32ms执行一次，最小分辨率就是32ms，然后系统会取整
//比如填96，就是96ms触发，填120也是96ms触发，只有填128，才是128ms触发
#define OVER_TEMP_PROTECT_LEVEL_TL       ((Q32U_)(10.0f))                   //lsb，过温保护阈值
#define OVER_TEMP_PROTECT_LEVEL_TIME     ((Q32U_)(100.0f/128.0f))           //ms，过温保护时间

#define LOW_TEMP_PROTECT_LEVEL_TL        ((Q32U_)(15.0f))                   //lsb，低温保护阈值
#define LOW_TEMP_PROTECT_LEVEL_TIME      ((Q32U_)(1000.0f/128.0f))          //ms，低温保护时间

typedef struct{
    Q32I_ Q16I_temp_protect_tl;
    Q32U_ Q16U_temp_protect_time;
    
    Q32U_ Q16U_temp_protect_cnt;
}ST_TEMP_PROTECT;

/**********************************************************************************************
Function: Temperature_Protect_Flow
Description: 温度保护控制
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Temperature_Protect_Flow(ST_SYSTEM_TASK*  pST);
    
#endif /* Temperature_H */
