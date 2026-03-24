/**************************************************************************************************
*     File Name :                        MCSQ_API_H.h
*     Library/Module Name :              MCSQ
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制接口头文件
**************************************************************************************************/

#ifndef MCSQ_API_H_H
#define MCSQ_API_H_H


#include "MCSQ_PARA.h"


/************************************电机控制接口函数*****************************************/

/**********************************************************************************************
Function: Motor_Start
Description: 电机启动
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Start(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: Motor_Stop
Description: 电机停机
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Stop(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: Motor_Set_Dir
Description: 设置电机运行方向
Input:  1（正转），-1（反转）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Set_Dir(ST_MOTOR_TASK* pMotor, Q32I_ Dir);

/**********************************************************************************************
Function: Motor_Read_Dir
Description: 获取电机运行方向
Input: 无
Output: 1（正转），-1（反转）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32I_ Motor_Read_Dir(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: Motor_Get_Run_State
Description: 获取电机是否为运行状态
Input: 无
Output: 1,0
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ Motor_Read_Run_State(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: Motor_Set_Target_Speed
Description: 设置电机转速
Input: 电机转速（rpm）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Set_Target_Speed(ST_MOTOR_TASK* pMotor, Q32I_ Speed);

/**********************************************************************************************
Function: Motor_Read_Speed
Description: 读取电机转速
Input: 无
Output: 电机转速（rpm）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ Motor_Read_Speed(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: Motor_Read_Error
Description: 读取电机故障码
Input: 无
Output: 电机故障码
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ Motor_Read_Error(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: Motor_Clear_Error
Description: 清除电机故障
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Clear_Error(ST_MOTOR_TASK* pMotor);


#endif /* MCSQ_API_H */
