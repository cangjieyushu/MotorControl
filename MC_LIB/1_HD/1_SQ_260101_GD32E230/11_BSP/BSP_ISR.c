/**************************************************************************************************
*     File Name :                        BSP_ISR.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             中断优先级初始化
**************************************************************************************************/
#include "BSP_ISR.h"

/**********************************************************************************************
Function: BSP_ISR_Init
Description: 中断优先级初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_ISR_Init(void)
{
    nvic_irq_enable(TIMER0_BRK_UP_TRG_COM_IRQn, 0);     //使能 刹车 中断
    nvic_irq_enable(TIMER2_IRQn, 3);                    //使能 比较 中断
    nvic_irq_enable(ADC_CMP_IRQn, 3);                   //使能 ADC 中断
    nvic_irq_enable(TIMER0_Channel_IRQn, 2);            //使能 触发 中断
    nvic_irq_enable(SysTick_IRQn, 5);                   //使能 SYS 中断
    
}
