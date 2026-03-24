/**************************************************************************************************
*     File Name :                        MATH_PID_F.h
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             PID
**************************************************************************************************/

#ifndef MATH_PID_F_H
#define MATH_PID_F_H


#include "MATH.h"


typedef struct
{
    float F_Rf;
    float F_Fb;
    
    float F_Kp;
    float F_Ki;
    float F_Kd;
    
    float F_Int;
    float F_Output;
    float F_OutMax;
    float F_OutMin;
}ST_PID_POS_F;

typedef struct
{
    float F_Rf;
    float F_Fb;
    
    float F_Kp;
    float F_Ki;
    float F_Kd;
    float F_Kc;
    
    float F_Int;
    float F_USat;
    float F_Output;
    float F_OutMax;
    float F_OutMin;
}ST_PID_SAT_F;


/**********************************************************************************************
Function: PID_Pos_Init_F
Description: 浮点位置式PID初始化
Input: 浮点积分器初始值
Output: 无
Input_Output: 浮点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Init_F(ST_PID_POS_F* pPID, float init);

/**********************************************************************************************
Function: PID_Pos_Cal_F
Description: 浮点位置式PID计算
Input: 无
Output: 无
Input_Output: 浮点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Cal_F(ST_PID_POS_F* pPID);

/**********************************************************************************************
Function: PID_Sat_Init_F
Description: 抗饱和位置式PID初始化
Input: 抗饱和积分器初始值
Output: 无
Input_Output: 抗饱和位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Sat_Init_F(ST_PID_SAT_F* pPID, float init);

/**********************************************************************************************
Function: PID_Sat_Cal_F
Description: 抗饱和位置式PID计算
Input: 无
Output: 无
Input_Output: 抗饱和位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Sat_Cal_F(ST_PID_SAT_F* pPID);


#endif /* MATH_PID_F_H */
