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
Description: 1ms中断TIM初始化
Input: 速度环中断函数
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_TIM_Init(isr_cb_t *StimIntCbf)
{
    /* STIM configuration */
    const STIM_Config_t StimConfig =
    {
        .workMode = STIM_FREE_COUNT,
        /* counter clock is 160M, compare value =160000,  period = 0.5ms */
        .compareValue = (uint32_t)(HAL_SLOW_TIMER_FREQ * HAL_SYSTEM_FREQ),
        .countResetMode = STIM_INCREASE_FROM_0,
        .clockSource = STIM_FUNCTION_CLOCK,
    };
    /* Configure STIM function clock */
    (void)CLK_ModuleSrc(CLK_STIM, CLK_SRC_PLL);
    /* Enable STIM module */
    SYSCTRL_EnableModule(SYSCTRL_STIM);
    /* Init STIM_0*/
    STIM_Init(HAL_SYSTEM_STIM, &StimConfig);
    /* Disable STIM */
    STIM_Disable(HAL_SYSTEM_STIM);
    
    STIM_InstallCallBackFunc(HAL_SYSTEM_STIM, STIM_INT, StimIntCbf);
    STIM_ClearInt(HAL_SYSTEM_STIM);
    
    /* start counter STIM */
    STIM_Enable(HAL_SYSTEM_STIM);
    /* Enable STIM_0 interrupt */
    STIM_IntCmd(HAL_SYSTEM_STIM, ENABLE);
    /* start counter STIM */
    STIM_Enable(HAL_SYSTEM_STIM);
}

/**********************************************************************************************
Function: BSP_HALL_Init
Description: HALL换向时间计数器初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_HALL_Init(void)
{
    
}
