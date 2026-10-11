/*
*     File Name :                        bsp_isr
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             中断优先级初始化
*/


#ifndef BSP_ISR_H
#define BSP_ISR_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_clk.h"
#include "hw_map.h"
#include "hw_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: BSP_ISR_Init
Description: 中断优先级初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
void BSP_ISR_Init(void);


#endif /* BSP_ISR_H */
