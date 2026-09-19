/*
*     File Name :                        math_filter_f
*     Library/Module Name :              math
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             滤波器
*/


#ifndef MATH_FILTER_F_H
#define MATH_FILTER_F_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef struct
{
    float I_F_LPF_In;
    float O_F_LPF_Out;
    
    float P_F_LPF_Coeff;
}ST_LPF_F;

typedef struct
{
    float I_F_MEAN_In;
    float O_F_MEAN_Out;

    float V_F_MEAN_Tmp;
    Q32U_ V_Q32U_MEAN_Cnt;
    
    Q32U_ P_Q32U_MEAN_Num;
}ST_MEAN_F;

typedef struct
{
    float I_F_MAX_In;
    float O_F_MAX_Out;

    float V_F_MAX_Tmp;
    Q32U_ V_Q32U_MAX_Cnt;
    
    Q32U_ P_Q32U_MAX_Num;
}ST_MAX_F;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: LPF_Init_F
Description: 浮点低通滤波初始化
Input: 浮点低通滤波初始值
Output: 无
Input_Output: 浮点低通滤波指针
Return: 无
Author: CJYS
*/
void LPF_Init_F(ST_LPF_F* pLPF, float init);

/*
Function: LPF_Cal_F
Description: 浮点低通滤波计算
Input: 无
Output: 无
Input_Output: 浮点低通滤波指针
Return: 无
Author: CJYS
*/
void LPF_Cal_F(ST_LPF_F* pLPF);

/*
Function: MEAN_Init_F
Description: 浮点平均值滤波初始化
Input: 无
Output: 无
Input_Output: 浮点平均值滤波指针
Return: 无
Author: CJYS
*/
void MEAN_Init_F(ST_MEAN_F* pMEAN);

/*
Function: MEAN_Cal_F
Description: 浮点平均值滤波计算
Input: 无
Output: 无
Input_Output: 浮点平均值滤波指针
Return: 无
Author: CJYS
*/
void MEAN_Cal_F(ST_MEAN_F* pMEAN);

/*
Function: MAX_Init_F
Description: 浮点最大值滤波初始化
Input: 无
Output: 无
Input_Output: 浮点最大值滤波指针
Return: 无
Author: CJYS
*/
void MAX_Init_F(ST_MAX_F* pMAX);

/*
Function: MAX_Cal_F
Description: 浮点最大值滤波计算
Input: 输入需大于0
Output: 无
Input_Output: 浮点最大值滤波指针
Return: 无
Author: CJYS
*/
void MAX_Cal_F(ST_MAX_F* pMAX);


#endif /* MATH_FILTER_F_H */
