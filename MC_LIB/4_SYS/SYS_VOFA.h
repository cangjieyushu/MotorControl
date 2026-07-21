/**************************************************************************************************
*     File Name :                        SYS_VOFA.h
*     Library/Module Name :              SYS
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             上位机收发头文件
**************************************************************************************************/

#ifndef SYS_VOFA_H
#define SYS_VOFA_H


#include "SYSTASK.h"
#include "UARTS.h"


/**********************************************************************************************
Function: SYS_VOFA_TASK
Description: 系统通讯控制
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void SYS_VOFA_TASK(ST_MOTOR_TASK* pMotor, ST_SYSTEM_TASK* pST, ST_UART_CONTROL* pUC);


#endif /* SYS_VOFA_H */
