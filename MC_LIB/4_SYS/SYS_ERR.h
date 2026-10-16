/*
*     File Name :                        sys_err
*     Library/Module Name :              sys
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             故障显示（LED 闪烁错误码）
*/


#ifndef SYS_ERR_H
#define SYS_ERR_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
/* 错误 LED 闪烁时间常量（单位：10ms 调用一次）*/
#define HW_ERR_LED_ON_TIME          (5U)    /* 亮 50ms */
#define HW_ERR_LED_OFF_TIME_1       (5U)    /* 间隔 1：50ms */
#define HW_ERR_LED_OFF_TIME_2       (10U)   /* 间隔 2：100ms */

/* 错误码最大个数 */
#define HW_ERR_CODE_MAX             (32U)


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef enum{
    ERROR_LED_INIT,         /* 初始化：拆分错误码 */
    ERROR_LED_WAIT,         /* 等待熄灭期 */
    ERROR_LED_LIGHT,        /* 点亮期 */
    ERROR_LED_END,          /* 结束等待 */
} EM_ERROR_LED_FLOW;

typedef struct{
    EM_ERROR_LED_FLOW  error_led_flow;        /* 当前状态 */
    Q32U_              error_led_counter;     /* 状态内的计数器 */

    Q32U_              error_led_table[HW_ERR_CODE_MAX];  /* 错误码 → 显示值映射 */
    Q32U_              error_code;            /* 当前错误码（0 = 正常）*/
    Q32U_              error_code_led_1;      /* 错误码十位 */
    Q32U_              error_code_led_2;      /* 错误码个位 */

    Q32U_              error_led_on_time;     /* 点亮持续时间 */
    Q32U_              error_led_off_time_1;  /* 第一次熄灭时间 */
    Q32U_              error_led_off_time_2;  /* 第二次熄灭时间 */
} ST_ERROR_CONTROL;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/
extern ST_ERROR_CONTROL Error_Ctrl;


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: Error_Priority_Check
Description: 故障优先级检查（返回最高优先级的错误码）
             同时更新 Error_Ctrl 内部的 LED 闪烁状态机
Input: error_all - 32 位错误位图（bit0 优先级最高）
Output: 无
Return: 错误码（0 = 无错误；1~32 = 对应错误）
Author: CJYS
*/
Q32U_ Error_Priority_Check(Q32U_ error_all);


#endif /* SYS_ERR_H */
