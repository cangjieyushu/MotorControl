/*
*     File Name :                        math_pid_f
*     Library/Module Name :              math
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             PID
*/


#ifndef MATH_PID_F_H
#define MATH_PID_F_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef struct
{
    float I_F_Rf;
    float I_F_Fb;
    float O_F_Output;
    
    float V_F_Int;

    float P_F_Kp;
    float P_F_Ki;
    float P_F_Kd;
    float P_F_OutMax;
    float P_F_OutMin;
}ST_PID_POS_F;

typedef struct
{
    float I_F_Rf;
    float I_F_Fb;
    float O_F_Output;
    
    float V_F_Int;
    float V_F_USat;

    float P_F_Kp;
    float P_F_Ki;
    float P_F_Kd;
    float P_F_Kc;
    float P_F_OutMax;
    float P_F_OutMin;
}ST_PID_SAT_F;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: PID_Pos_Init_F
Description: 浮点位置式PID初始化
Input: 浮点积分器初始值
Output: 无
Input_Output: 浮点位置式PID指针
Return: 无
Author: CJYS
*/
void PID_Pos_Init_F(ST_PID_POS_F* pPID, float init);

/*
Function: PID_Pos_Cal_F
Description: 浮点位置式PID计算
Input: 无
Output: 无
Input_Output: 浮点位置式PID指针
Return: 无
Author: CJYS
*/
void PID_Pos_Cal_F(ST_PID_POS_F* pPID);

/*
Function: PID_Sat_Init_F
Description: 抗饱和位置式PID初始化
Input: 抗饱和积分器初始值
Output: 无
Input_Output: 抗饱和位置式PID指针
Return: 无
Author: CJYS
*/
void PID_Sat_Init_F(ST_PID_SAT_F* pPID, float init);

/*
Function: PID_Sat_Cal_F
Description: 抗饱和位置式PID计算
Input: 无
Output: 无
Input_Output: 抗饱和位置式PID指针
Return: 无
Author: CJYS
*/
void PID_Sat_Cal_F(ST_PID_SAT_F* pPID);


#endif /* MATH_PID_F_H */
