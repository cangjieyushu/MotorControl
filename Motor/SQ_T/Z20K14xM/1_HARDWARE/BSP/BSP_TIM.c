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
void BSP_TIM_Init(void)
{
    /* Configure STIM function clock */
    (void)CLK_ModuleSrc(CLK_STIM, CLK_SRC_PLL);
    /* Enable STIM module */
    SYSCTRL_EnableModule(SYSCTRL_STIM);
    
    /* STIM configuration */
    const STIM_Config_t StimConfig =
    {
        .workMode = STIM_FREE_COUNT,
        .compareValue = 0xFFFFFFFFU,
        .countResetMode = STIM_INCREASE_FROM_0,
        .clockSource = STIM_FUNCTION_CLOCK,
        .prescalerOrFilterValue = STIM_DIV_16_FILTER_7,
        .prescalerMode = ENABLE,
    };
    
    /* Init STIM_0*/
    STIM_Init(STIM_1, &StimConfig);
    /*Disable STIM*/
    STIM_Enable(STIM_1);
    
    /* Init STIM_0*/
    STIM_Init(STIM_0, &StimConfig);
//    /*Disable STIM*/
//    STIM_Disable(STIM_0);
    
    STIM_Enable(STIM_0);    
    // Enable STIM_0 interrupt
    STIM_IntCmd(STIM_0, ENABLE); 
}
