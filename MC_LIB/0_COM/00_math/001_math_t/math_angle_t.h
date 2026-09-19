/*
*     File Name :                        math_angle_t
*     Library/Module Name :              math
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             三角函数
*/

#ifndef MATH_ANGLE_T_H
#define MATH_ANGLE_T_H

/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"

/*-------------------------- 2. 宏定义 -----------------------------------*/
#define MATH_SIN_MASK_T         0x0C00U
#define MATH_SIN_U0_90          0x0000U
#define MATH_SIN_U90_180        0x0400U
#define MATH_SIN_U180_270       0x0800U
#define MATH_SIN_U270_360       0x0C00U

/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef struct
{
    Q32I_ Q14U_Angle;
    Q32I_ Q14I_Cos;
    Q32I_ Q14I_Sin;
    Q32I_ Q14U_ReAngle;
}ST_TRIG_T;

/*-------------------------- 4. 外部全局变量声明 --------------------------*/

/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: Math_SinCos_T
Description: 定点正余弦计算
Input: 角度，0到16384
Output: 正弦，余弦
Input_Output: 定点角度指针
Return: 无
Author: CJYS
*/
void Math_SinCos_T(ST_TRIG_T* pTIG);


#endif /* MATH_ANGLE_T_H */
