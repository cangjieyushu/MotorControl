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
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
    TIM_TimeBaseInitStruct.CounterMode          = TIM_COUNTERMODE_UP;
    TIM_TimeBaseInitStruct.RepetitionCounter    = 0;
    TIM_TimeBaseInitStruct.Period               = 0xFFFFFFFFU;
    TIM_TimeBaseInitStruct.ClockDivision        = TIM_CLOCKDIVISION_DIV1;
    TIM_TimeBaseInitStruct.Prescaler            = (uint32_t)HAL_HALL_TIM_PRESCALER;
    TIM_TimeBaseInit(HAL_MOTOR_HALL_TIM, &TIM_TimeBaseInitStruct);
    TIM_Enable_CEN(HAL_MOTOR_HALL_TIM); 
    
    TIM_TimeBaseInitStruct.CounterMode          = TIM_COUNTERMODE_UP;
    TIM_TimeBaseInitStruct.RepetitionCounter    = 0;
    TIM_TimeBaseInitStruct.Period               = 0xFFFFU;
    TIM_TimeBaseInitStruct.ClockDivision        = TIM_CLOCKDIVISION_DIV1;
    TIM_TimeBaseInitStruct.Prescaler            = (uint32_t)HAL_SWITCH_TIM_PRESCALER;
    TIM_TimeBaseInit(HAL_MOTOR_SWITCH_TIM, &TIM_TimeBaseInitStruct);

    TIM_Enable_IT(HAL_MOTOR_SWITCH_TIM, TIM_SR_UIF);
}
