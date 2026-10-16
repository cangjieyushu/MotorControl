/*
*     File Name :                        bsp_mc_tim
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             TIM 初始化
*                                        HALL 换向计时（TIM2） + 延迟换向计时（TIM3）
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_mc_tim.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_MC_TIM_Init
Description: HALL 换向时间计数器 + 延迟换向计数器初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_TIM_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};

    /* ---------------- 1. HALL 换向计时（TIM2）---------------- */
    TIM_TimeBaseInitStruct.CounterMode       = TIM_COUNTERMODE_UP;
    TIM_TimeBaseInitStruct.RepetitionCounter = 0U;
    TIM_TimeBaseInitStruct.Period            = HW_HTIM_SET_VALUE;
    TIM_TimeBaseInitStruct.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    TIM_TimeBaseInitStruct.Prescaler         = (uint16_t)(HW_HTIM_PRESCALER) - 1U;
    TIM_TimeBaseInit(HW_MC_HTIM, &TIM_TimeBaseInitStruct);
    TIM_Enable_CEN(HW_MC_HTIM);

    /* ---------------- 2. 延迟换向计时（TIM3）---------------- */
    TIM_TimeBaseInitStruct.CounterMode       = TIM_COUNTERMODE_UP;
    TIM_TimeBaseInitStruct.RepetitionCounter = 0U;
    TIM_TimeBaseInitStruct.Period            = HW_STIM_SET_VALUE;
    TIM_TimeBaseInitStruct.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    TIM_TimeBaseInitStruct.Prescaler         = (uint16_t)(HW_STIM_PRESCALER) - 1U;
    TIM_TimeBaseInit(HW_MC_STIM, &TIM_TimeBaseInitStruct);

    /* 关闭 CH1 预装载，由 HM_SWITCH_TIM_Delay() 动态设置比较值 */
    TIM_Disable_OC_Preload(HW_MC_STIM, TIM_CHANNEL_CH1);

    /* 使能 CH1 比较中断（延迟换向触发） */
    TIM_Enable_IT(HW_MC_STIM, TIM_DIER_CC1IE);
}
