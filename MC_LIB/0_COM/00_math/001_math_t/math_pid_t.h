/*
*     File Name :                        math_pid_t
*     Library/Module Name :              math
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             PID
*/

#ifndef MATH_PID_T_H
#define MATH_PID_T_H

/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"

/*-------------------------- 2. 宏定义 -----------------------------------*/

/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef struct
{
    Q32I_ I_Q14I_Rf;
    Q32I_ I_Q14I_Fb;
    Q32I_ O_Q14I_Output;
    
    Q32I_ V_Q14I_LastError;   
    Q32I_ V_Q14I_PrevError;
    Q32I_ V_Q28I_Step;
    Q32I_ V_Q28I_Output_tmp;

    Q32I_ P_Q14I_Kp;
    Q32I_ P_Q14I_Ki;
    Q32I_ P_Q14I_Kd;
    Q32I_ P_Q28I_StepMax;
    Q32I_ P_Q28I_StepMin;
    Q32I_ P_Q14I_OutMax;
    Q32I_ P_Q14I_OutMin;
    
}ST_PID_INC_T;

typedef struct
{
    Q32I_ I_Q14I_Rf;
    Q32I_ I_Q14I_Fb;
    Q32I_ O_Q14I_Output;
    
    Q32I_ V_Q14I_Int;
    Q32I_ V_Q28I_Ui_tmp;

    Q32I_ P_Q14I_Kp;
    Q32I_ P_Q14I_Ki;
    Q32I_ P_Q14I_Kd;
    Q32I_ P_Q14I_OutMax;
    Q32I_ P_Q14I_OutMin;
}ST_PID_POS_T;

typedef struct
{
    Q32I_ I_Q14I_Rf;
    Q32I_ I_Q14I_Fb;
    Q32I_ O_Q14I_Output;
    
    Q32I_ V_Q14I_Int;
    Q32I_ V_Q28I_Ui_tmp;
    Q32I_ V_Q14I_USat;
    
    Q32I_ P_Q14I_Kp;
    Q32I_ P_Q14I_Ki;
    Q32I_ P_Q14I_Kd;
    Q32I_ P_Q14I_Kc;
    Q32I_ P_Q14I_OutMax;
    Q32I_ P_Q14I_OutMin;
}ST_PID_SAT_T;

/*-------------------------- 4. 外部全局变量声明 --------------------------*/

/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: PID_Inc_Init_T
Description: 定点增量式PID初始化
Input: 定点积分器初始值
Output: 无
Input_Output: 定点增量式PID指针
Return: 无
Author: CJYS
*/
void PID_Inc_Init_T(ST_PID_INC_T* pPID, Q32I_ init);

/*
Function: PID_Inc_Cal_T
Description: 定点增量式PID计算
Input: 无
Output: 无
Input_Output: 定点增量式PID指针
Return: 无
Author: CJYS
*/
void PID_Inc_Cal_T(ST_PID_INC_T* pPID);

/*
Function: PID_Pos_Init_T
Description: 定点位置式PID初始化
Input: 定点积分器初始值
Output: 无
Input_Output: 定点位置式PID指针
Return: 无
Author: CJYS
*/
void PID_Pos_Init_T(ST_PID_POS_T* pPID, Q32I_ init);

/*
Function: PID_Pos_Cal_T
Description: 定点位置式PID计算
Input: 无
Output: 无
Input_Output: 定点位置式PID指针
Return: 无
Author: CJYS
*/
void PID_Pos_Cal_T(ST_PID_POS_T* pPID);

/*
Function: PID_Sat_Init_T
Description: 抗饱和位置式PID初始化
Input: 抗饱和积分器初始值
Output: 无
Input_Output: 抗饱和位置式PID指针
Return: 无
Author: CJYS
*/
void PID_Sat_Init_T(ST_PID_SAT_T* pPID, Q32I_ init);
    
/*
Function: PID_Sat_Cal_T
Description: 抗饱和位置式PID计算
Input: 无
Output: 无
Input_Output: 抗饱和位置式PID指针
Return: 无
Author: CJYS
*/
void PID_Sat_Cal_T(ST_PID_SAT_T* pPID);


#endif /* MATH_PID_T_H */
