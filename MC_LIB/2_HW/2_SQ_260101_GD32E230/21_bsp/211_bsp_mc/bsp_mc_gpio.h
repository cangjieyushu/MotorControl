/*
*     File Name :                        bsp_mc_gpio
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制 GPIO 初始化
*/


#ifndef BSP_MC_GPIO_H
#define BSP_MC_GPIO_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: BSP_MC_GPIO_Init
Description: 电机控制 GPIO 初始化（ADC/OPA/DAC/CMP/PWM 引脚）
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_GPIO_Init(void);


#endif /* BSP_MC_GPIO_H */
