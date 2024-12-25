/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_TIM.h"

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
