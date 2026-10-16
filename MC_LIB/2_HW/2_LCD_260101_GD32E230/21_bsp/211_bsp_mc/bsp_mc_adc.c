/*
*     File Name :                        bsp_mc_adc
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             ADC 初始化
*                                        单 ADC1：注入组采样电机 BEMF/电流 + 规则组采样母线/温度/VR/VBG
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_mc_adc.h"


/*-------------------------- 2. 变量 ---------------------------------*/
/* 引用 bsp_mc_adc.c 中定义的规则组缓冲区 */
Q32U_ BSP_ADC_SYSTEM_BUFFER[10];


/*-------------------------- 3. 内部辅助函数 ----------------------------*/


/*-------------------------- 4. 公有接口实现 -----------------------------*/
/*
Function: BSP_MC_ADC_Init
Description: 电机控制用 ADC 初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_ADC_Init(void)
{
    
}
