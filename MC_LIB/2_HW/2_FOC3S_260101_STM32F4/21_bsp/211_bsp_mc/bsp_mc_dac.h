/*
*     File Name :                        bsp_mc_dac
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             DAC 阈值输出初始化
*/


#ifndef BSP_MC_DAC_H
#define BSP_MC_DAC_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: BSP_MC_DAC_Init
Description: DAC 初始化（窗口比较器阈值输出）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_DAC_Init(void);


#endif /* BSP_MC_DAC_H */
