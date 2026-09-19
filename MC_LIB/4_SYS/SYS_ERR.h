/*
*     File Name :                        sys_err
*     Library/Module Name :              sys
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             故障显示
*/


#ifndef SYS_ERR_H
#define SYS_ERR_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "sys_task.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
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


/*-------------------------- 4. 外部全局变量声明 --------------------------*/
extern ST_ERROR_CONTROL Error_Ctrl;


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: Error_Priority_Check
Description: 故障优先级控制
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
*/
Q32U_ Error_Priority_Check(Q32U_ error_all);

    
#endif /* SYS_ERR_H */
