/*
*     File Name :                        math_angle_f
*     Library/Module Name :              math
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             三角函数
*/


#ifndef math_angle_f
#define math_angle_f


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
#define MATH_SIN_TABLE_SIZE_F                   512U


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef struct
{
    float F_Angle;
    float F_Cos;
    float F_Sin;
    float F_ReAngle;
}ST_TRIG_F;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: Math_SinCos_F
Description: 浮点正余弦计算
Input: 角度，0到1
Output: 正弦，余弦
Input_Output: 浮点角度指针
Return: 无
Author: CJYS
*/
void Math_SinCos_F(ST_TRIG_F* pTIG);


#endif /* math_angle_f */
