/*
*     File Name :                        bsp_mc
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制外设汇总头文件
*/


#ifndef BSP_MC_H
#define BSP_MC_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "bsp_mc_gpio.h"
#include "bsp_mc_adc.h"
#include "bsp_mc_dma.h"
#include "bsp_mc_pwm.h"
#include "bsp_mc_tim.h"
#include "bsp_mc_cmp.h"
#include "bsp_mc_dac.h"
#include "bsp_mc_opamp.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: BSP_MC_Init
Description: 电机控制外设初始化汇总
             包含：GPIO、DAC、OPA、CMP、PWM、TIM、ADC、DMA
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_Init(void);


#endif /* BSP_MC_H */
