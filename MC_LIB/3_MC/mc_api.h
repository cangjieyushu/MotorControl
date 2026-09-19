/*
*     File Name :                        mc_api
*     Library/Module Name :              mc
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制接口
*/


#ifndef MC_API_H
#define MC_API_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"
#include "pmsm_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: MC_API_Motor_StartStop
Description: 电机启停
Input: 电机编号0，1，2，3； 1（运行），0（停机）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
void MC_API_Motor_StartStop(Q32U_ motor_num, Q32U_ Enable);

/*
Function: MC_API_Motor_Get_State
Description: 获取电机是否为运行状态
Input: 电机编号0，1，2，3；
Output: 1（运行），0（停机）
Input_Output: 无
Return: 无
Author: CJYS
*/
Q32U_ MC_API_Motor_Read_State(Q32U_ motor_num);

/*
Function: MC_API_Motor_Set_Dir
Description: 设置电机运行方向
Input:  电机编号0，1，2，3；Dir，1（正转），0（反转）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
void MC_API_Motor_Set_Dir(Q32U_ motor_num, Q32U_ Dir);

/*
Function: MC_API_Motor_Read_Dir
Description: 获取电机运行方向
Input: 电机编号0，1，2，3；
Output: 1（正转），0（反转）
Input_Output: 无
Return: 无
Author: CJYS
*/
Q32I_ MC_API_Motor_Read_Dir(Q32U_ motor_num);

/*
Function: MC_API_Motor_Set_Speed
Description: 设置电机转速
Input: 电机编号0，1，2，3；电机转速（rpm）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
void MC_API_Motor_Set_Speed(Q32U_ motor_num, Q32U_ Speed);

/*
Function: MC_API_Motor_Read_Speed
Description: 读取电机转速
Input: 电机编号0，1，2，3；
Output: 电机转速（rpm）
Input_Output: 无
Return: 无
Author: CJYS
**/
Q32U_ MC_API_Motor_Read_Speed(Q32U_ motor_num);

/*
Function: MC_API_Motor_Read_Iphase
Description: 读取电机相电流
Input: 电机编号0，1，2，3；
Output: 电机电流（0.01A）
Input_Output: 无
Return: 无
Author: CJYS
*/
Q32U_ MC_API_Motor_Read_Iphase(Q32U_ motor_num);

/*
Function: MC_API_Motor_Read_Ibus
Description: 读取电机母线电流
Input: 电机编号0，1，2，3；
Output: 电机电流（0.01A）
Input_Output: 无
Return: 无
Author: CJYS
*/
Q32U_ MC_API_Motor_Read_Ibus(Q32U_ motor_num);

/*
Function: MC_API_Motor_Read_Err
Description: 读取电机故障码
Input: 电机编号0，1，2，3；
Output: 电机故障码
Input_Output: 无
Return: 无
Author: CJYS
*/
Q32U_ MC_API_Motor_Read_Err(Q32U_ motor_num);

/*
Function: MC_Motor_Clear_Err
Description: 清除电机故障
Input: 电机编号0，1，2，3；
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
void MC_API_Motor_Clear_Err(Q32U_ motor_num);


#endif /* MC_API_H */
