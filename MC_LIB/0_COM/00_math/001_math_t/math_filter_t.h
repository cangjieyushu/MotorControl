/*
*     File Name :                        math_filter_t
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             滤波器
*/

#ifndef MATH_FILTER_T_H
#define MATH_FILTER_T_H

/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"

/*-------------------------- 2. 宏定义 -----------------------------------*/

/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef struct
{
    Q32I_ I_Q14I_LPF_In;
    Q32I_ O_Q14I_LPF_Out;

    Q32I_ V_Q28I_LPF_Tmp;
    
    Q32I_ P_Q14I_LPF_Coeff;
}ST_LPF_T;

typedef struct
{
    
    Q32I_ I_Q14I_MEAN_In;
    Q32I_ O_Q14I_MEAN_Out;

    Q32I_ V_Q14I_MEAN_Tmp;
    Q32U_ V_Q32U_MEAN_Cnt;
    
    Q32U_ P_Q32U_MEAN_Num;
    Q32U_ P_Q32U_MEAN_Bit;
}ST_MEAN_T;

typedef struct
{
    Q32I_ I_Q14I_MAX_In;
    Q32I_ O_Q14I_MAX_Out;
    
    Q32I_ V_Q14I_MAX_Tmp;
    Q32U_ V_Q32U_MAX_Cnt;
    
    Q32U_ P_Q32U_MAX_Num;
}ST_MAX_T;

/*-------------------------- 4. 外部全局变量声明 --------------------------*/

/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: LPF_Init_T
Description: 定点低通滤波初始化
Input: 定点低通滤波初始值
Output: 无
Input_Output: 定点低通滤波指针
Return: 无
Author: CJYS
*/
void LPF_Init_T(ST_LPF_T* pLPF, Q32I_ init);

/*
Function: LPF_Cal_T
Description: 定点低通滤波计算
Input: 无
Output: 无
Input_Output: 定点低通滤波指针
Return: 无
Author: CJYS
*/
void LPF_Cal_T(ST_LPF_T* pLPF);

/*
Function: MEAN_Init_T
Description: 定点平均值滤波初始化
Input: 无
Output: 无
Input_Output: 定点平均值滤波指针
Return: 无
Author: CJYS
*/
void MEAN_Init_T(ST_MEAN_T* pMEAN);

/*
Function: MEAN_Cal_T
Description: 定点平均值滤波计算
Input: 无
Output: 无
Input_Output: 定点平均值滤波指针
Return: 无
Author: CJYS
*/
void MEAN_Cal_T(ST_MEAN_T* pMEAN);

/*
Function: MAX_Init_T
Description: 定点最大值滤波初始化
Input: 无
Output: 无
Input_Output: 定点最大值滤波指针
Return: 无
Author: CJYS
*/
void MAX_Init_T(ST_MAX_T* pMAX);

/*
Function: MAX_Cal_T
Description: 定点最大值滤波计算
Input: 输入需大于0
Output: 无
Input_Output: 定点最大值滤波指针
Return: 无
Author: CJYS
*/
void MAX_Cal_T(ST_MAX_T* pMAX);


#endif /* MATH_FILTER_T_H */
