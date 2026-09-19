/*
*     File Name :                        mcsq_task
*     Library/Module Name :              mcsq
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机任务
*/


#ifndef MCSQ_TASK_H
#define MCSQ_TASK_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "pmsm_para.h"
#include "hal_mc.h"
#include "mcsq_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: MCSQ_Speed_Flow
Description: 电机控制速度环
Input: 无
Output: 无
Input_Output: 电机编号0，1，2，3；
Return: 无
Author: CJYS
*/
void MCSQ_Speed_Flow(Q32U_ motor_num);

/*
Function: MCSQ_Current_Flow
Description: 电机控制电流环
Input: 无
Output: 无
Input_Output: 电机编号0，1，2，3；
Return: 无
Author: CJYS
*/
void MCSQ_Current_Flow(Q32U_ motor_num);

/*
Function: MCSQ_Switch_Flow
Description: 电机控制换向
Input: 无
Output: 无
Input_Output: 电机编号0，1，2，3；
Return: 无
Author: CJYS
*/
void MCSQ_Switch_Flow(Q32U_ motor_num);

/*
Function: MCSQ_ADC_Trig_Flow
Description: 触发采样
Input: 无
Output: 无
Input_Output: 电机编号0，1，2，3；
Return: 无
Author: CJYS
*/
void MCSQ_ADC_Trig_Flow(Q32U_ motor_num);


#endif /* MCSQ_TASK_H */
