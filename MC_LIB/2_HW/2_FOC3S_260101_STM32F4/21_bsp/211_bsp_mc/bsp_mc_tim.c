/*
*     File Name :                        bsp_mc_tim
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             TIM初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_mc_tim.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_MC_TIM_Init
Description: HALL换向时间计数器初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_TIM_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;

    TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Prescaler         = (Q32U_)HW_HTIM_PRESCALER - 1U;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInitStructure.TIM_Period            = HW_HTIM_SET_VALUE;
    TIM_TimeBaseInit(HW_MC_HTIM, &TIM_TimeBaseInitStructure);

    /* 计数器清零，从 0 开始计时 */
    TIM_SetCounter(HW_MC_HTIM, 0);

    TIM_Cmd(HW_MC_HTIM, ENABLE);
}
