/**************************************************************************************************
*     File Name :                        BSP_TIM.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             TIM初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_TIM.h"

/**********************************************************************************************
Function: BSP_TIM_Init
Description: HALL换向时间计数器初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_TIM_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
    
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV4; 
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInitStructure.TIM_Period = 0xFFFFFFFF;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
    
    TIM_Cmd(TIM2,ENABLE);
}
