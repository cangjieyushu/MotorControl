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
#define OVER_TEMP_PROTECT_LEVEL_TL       ((Q32U_)(1000.0f))                 //lsb，过温保护阈值
#define OVER_TEMP_PROTECT_LEVEL_TIME     (1000U)                            //ms，过温保护时间

#define LOW_TEMP_PROTECT_LEVEL_TL        ((Q32U_)(1500.0f))                 //lsb，低温保护阈值
#define LOW_TEMP_PROTECT_LEVEL_TIME      (1000U)                            //ms，低温保护时间

typedef struct{
    Q32U_ Q16U_temp_protect_tl;
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
