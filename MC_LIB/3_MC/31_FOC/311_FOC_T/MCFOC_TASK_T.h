/**************************************************************************************************
*     File Name :                        MCFOC_TASK_T.h
*     Library/Module Name :              MCFOC_T
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机子任务头文件
**************************************************************************************************/

#ifndef MCFOC_TASK_T_H
#define MCFOC_TASK_T_H


#include "MCH.h"
#include "MCFOC_PARA_T.h"


typedef void(*pMOTOR_FUN)(ST_MOTOR_TASK*);


/**********************************************************************************************
Function: MotorTask_Speed_Flow_T
Description: 电机控制速度环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Speed_Flow_T(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: MotorTask_Current_Flow_T
Description: 电机控制电流环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Current_Flow_T(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: MotorTask_Shut_Flow_T
Description: 电机控制故障关断
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Shut_Flow_T(ST_MOTOR_TASK* pMotor);


#endif /* MCFOC_TASK_T_H */
