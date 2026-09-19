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
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
    TIM_TimeBaseInitStruct.CounterMode          = TIM_COUNTERMODE_UP;
    TIM_TimeBaseInitStruct.RepetitionCounter    = 0U;
    TIM_TimeBaseInitStruct.Period               = HAL_HALL_TIM_MAX_CNT;
    TIM_TimeBaseInitStruct.ClockDivision        = TIM_CLOCKDIVISION_DIV1;
    TIM_TimeBaseInitStruct.Prescaler            = ((uint32_t)HAL_HALL_TIM_PRESCALER) - 1U;
    TIM_TimeBaseInit(HAL_MOTOR_HALL_TIM, &TIM_TimeBaseInitStruct);
    TIM_Enable_CEN(HAL_MOTOR_HALL_TIM); 
    
    TIM_TimeBaseInitStruct.CounterMode          = TIM_COUNTERMODE_UP;
    TIM_TimeBaseInitStruct.RepetitionCounter    = 0U;
    TIM_TimeBaseInitStruct.Period               = HAL_SWITCH_TIM_MAX_CNT;
    TIM_TimeBaseInitStruct.ClockDivision        = TIM_CLOCKDIVISION_DIV1;
    TIM_TimeBaseInitStruct.Prescaler            = ((uint32_t)HAL_SWITCH_TIM_PRESCALER) - 1U;
    TIM_TimeBaseInit(HAL_MOTOR_SWITCH_TIM, &TIM_TimeBaseInitStruct);
    
    TIM_Disable_OC_Preload(HAL_MOTOR_SWITCH_TIM, TIM_CHANNEL_CH1);
    
    TIM_Enable_IT(HAL_MOTOR_SWITCH_TIM, TIM_DIER_CC1IE);
}
