/*
*     File Name :                        bsp_sys_isr
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             中断优先级初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_sys_isr.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_SYS_ISR_Init
Description: 中断优先级初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_SYS_ISR_Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   // 抢占 0~3，子 0~3

    NVIC_InitTypeDef NVIC_InitStructure;

    /* ADC 最高：抢占 0，子 0 */
    NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* SysTick 也要低于 ADC，否则它会抢占 ADC。
    Group 2 下：原始值 15 = 抢占 3，子 3，最低。 */
    NVIC_SetPriority(SysTick_IRQn, 15);
    
}
