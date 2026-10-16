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
    nvic_irq_enable(TIMER0_BRK_UP_TRG_COM_IRQn, 0);     //使能 刹车 中断
    nvic_irq_enable(TIMER2_IRQn, 2);                    //使能 比较 中断
    nvic_irq_enable(ADC_CMP_IRQn, 2);                   //使能 ADC 中断
    nvic_irq_enable(TIMER0_Channel_IRQn, 1);            //使能 触发 中断
    nvic_irq_enable(SysTick_IRQn, 5);                   //使能 SYS 中断
    nvic_irq_enable(USART0_IRQn, 4);                    //使能 串口 中断
    nvic_irq_enable(DMA_Channel1_2_IRQn, 3);
    nvic_irq_enable(DMA_Channel3_4_IRQn, 3);            //★ 新增：USART0 TX(CH3)/RX(CH4)
}
