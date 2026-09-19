/*
*     File Name :                        bsp_adc
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             ADC初始化
*/


#ifndef BSP_ADC_H
#define BSP_ADC_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_clk.h"
#include "hw_map.h"
#include "hw_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
#define BSP_ADC_DATA_READ_VR        ((Q32U_)(HAL_MOTOR_ADC->DATA3))
#define BSP_ADC_DATA_READ_VBG       ((Q32U_)(HAL_MOTOR_ADC->DATA4))


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/
extern Q32U_ BSP_ADC_SYSTEM_BUFFER[10];
extern Q32U_ BSP_ADC_MOTOR_BUFFER[10];


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: BSP_ADC_Init
Description: 电机控制用ADC初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
void BSP_ADC_Init(void);


#endif /* BSP_ADC_H */
