/*
*     File Name :                        math_ramp_f
*     Library/Module Name :              math
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             斜坡函数
*/


#ifndef MATH_RAMP_F_H
#define MATH_RAMP_F_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef struct
{
    float O_F_Output;

    float P_F_Init;
    float P_F_Target;
    float P_F_ADDStep;
    float P_F_SUBStep;
}ST_RAMP_F;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: Ramp_Init_F
Description: 浮点斜坡初始化
Input: 浮点斜坡输出初始值
Output: 无
Input_Output: 浮点斜坡指针
Return: 无
Author: CJYS
*/
void Ramp_Init_F(ST_RAMP_F* pRamp, float init);

/*
Function: Ramp_Cal_F
Description: 浮点斜坡计算
Input: 无
Output: 无
Input_Output: 浮点斜坡指针
Return: 无
Author: CJYS
*/
void Ramp_Cal_F(ST_RAMP_F* pRamp);


#endif /* MATH_RAMP_F_H */
