/*
*     File Name :                        bsp_tim
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             TIM初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_tim.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
void BSP_TIM_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
    
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV4; 
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Prescaler = (Q32U_)HAL_HALL_TIM_PRESCALER - 1U;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInitStructure.TIM_Period = HAL_HALL_TIM_MAX_CNT;
    TIM_TimeBaseInit(HAL_MOTOR_HALL_TIM,&TIM_TimeBaseInitStructure);
    
    TIM_Cmd(HAL_MOTOR_HALL_TIM,ENABLE);
}
