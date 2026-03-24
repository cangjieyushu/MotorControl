/**************************************************************************************************
*     File Name :                        MCSQ_TASK.h
*     Library/Module Name :              MCSQ
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机子任务头文件
**************************************************************************************************/

#ifndef MCSQ_TASK_H
#define MCSQ_TASK_H


#include "MCSQ_PARA.h"
#include "MCH.h"


typedef void(*pMOTOR_FUN)(ST_MOTOR_TASK*);
typedef void(*pFUN_HPWMLPWM_SET)(Q32U_);


/**********************************************************************************************
Function: MotorTask_Speed_Flow
Description: 电机控制速度环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Speed_Flow(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: MotorTask_Current_Flow
Description: 电机控制电流环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Current_Flow(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: MotorTask_Switch_Flow
Description: 电机控制换向
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Switch_Flow(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: MotorTask_PWM_Start_ADC_Flow
Description: 电机控制首次触发ADC
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_PWM_Start_ADC_Flow(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: MotorTask_Shut_Flow
Description: 电机控制故障关断
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Shut_Flow(ST_MOTOR_TASK* pMotor);


#endif /* MCSQ_TASK_H */
