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
    NVIC_SetPriority(TIM8_CC_IRQn, 2);                //设置中断优先级
    NVIC_EnableIRQ(TIM8_CC_IRQn);                    //使能 触发 中断

    NVIC_SetPriority(TIM3_IRQn, 3);                    //设置中断优先级
    NVIC_EnableIRQ(TIM3_IRQn);                        //使能 比较 中断
    
    NVIC_SetPriority(ADC_IRQn, 3);                    //设置中断优先级
    NVIC_EnableIRQ(ADC_IRQn);                        //使能 ADC 中断
    
    NVIC_SetPriority(SysTick_IRQn, 5);                //设置中断优先级
    NVIC_EnableIRQ(SysTick_IRQn);                    //使能 SYS 中断
}
