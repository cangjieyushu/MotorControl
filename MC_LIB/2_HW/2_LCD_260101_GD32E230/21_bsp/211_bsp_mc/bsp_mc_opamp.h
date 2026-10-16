/*
*     File Name :                        bsp_mc_opamp
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             OPA 跟随器初始化
*/


#ifndef BSP_MC_OPAMP_H
#define BSP_MC_OPAMP_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: BSP_MC_OPAMP_Init
Description: OPA1/2/3 跟随器初始化（输出到 CMP 的 P 端）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_OPAMP_Init(void);


#endif /* BSP_MC_OPAMP_H */
