/**************************************************************************************************
*     File Name :                        Error.h
*     Library/Module Name :              SysTask
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             故障显示头文件
**************************************************************************************************/
#ifndef Error_H
#define Error_H

#include "SysTask.h"

typedef enum{
    ERROR_LED_INIT,
    ERROR_LED_BEGIN,
    ERROR_LED_WAIT,
    ERROR_LED_LIGHT,
    ERROR_LED_END,
}EM_ERROR_LED_FLOW;

typedef struct{
    EM_ERROR_LED_FLOW error_led_flow;
    Q32U_ error_led_table[32];
    Q32U_ error_code;
    Q32U_ error_code_led_1;
    Q32U_ error_code_led_2;
    Q32U_ led_cnt;
    
    Q32U_ error_led_on_time;
    Q32U_ error_led_off_time_1;
    Q32U_ error_led_off_time_2;
}ST_ERROR_CONTROL;

/**********************************************************************************************
Function: Error_Priority_Check
Description: 故障优先级控制
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Error_Priority_Check(ST_SYSTEM_TASK*  pST);
    
#endif /* Error_H */
