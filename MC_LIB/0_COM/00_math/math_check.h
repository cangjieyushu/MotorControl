/*
*     File Name :                        math_check
*     Library/Module Name :              math
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             确认函数
*/


#ifndef MATH_CHECK_H
#define MATH_CHECK_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef union{
    SC_ALL all;
    struct{
        SC_BIT Enable              :1;
        SC_BIT Condition_Set       :1;
        SC_BIT Condition_Clear     :1;
        SC_BIT Clear_Mode          :1;     //0：条件不满足时，计数器清零；1：条件不满足时，计数器减1。
    }bit;
}UN_CHECK_FLAG;

typedef struct{
    UN_CHECK_FLAG       Check_Flag;
    Q32U_               V_Q32U_Check_cnt;
    
    float               P_F_Check_TL;
    Q32U_               P_Q14I_Check_TL;
    Q32U_               P_Q32U_Check_Time;
    
    float               P_F_Clear_TL;
    Q32U_               P_Q14I_Clear_TL;
    Q32U_               P_Q32U_Clear_Time;
    
    Q32U_               P_Q32U_Check_Count;
}ST_CHECK;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Description: 计数器初始化
Input: 无
Output: 无
Input_Output: 检测指针
Return: 无
Author: CJYS
*/
void Check_Init(ST_CHECK* pCheck);

/*
Function: Check_Cal
Description: 计数器检测
Input: 无
Output: 无
Input_Output: 检测指针，故障状态
Return: 无
Author: CJYS
*/
Q32U_ Check_Cal(ST_CHECK* pCheck, Q32U_ Fault_State);
   

#endif /* MATH_CHECK_H */
