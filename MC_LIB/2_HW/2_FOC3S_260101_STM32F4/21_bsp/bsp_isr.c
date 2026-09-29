/*
*     File Name :                        bsp_isr
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             中断优先级初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_isr.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
void BSP_ISR_Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   // 抢占 0~3，子 0~3

    NVIC_InitTypeDef NVIC_InitStructure;

    /* ADC 最高：抢占 0，子 0 */
    NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* USART1 低一点：抢占 3，子 0 */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* SysTick 也要低于 ADC，否则它会抢占 ADC。
    Group 2 下：原始值 15 = 抢占 3，子 3，最低。 */
    NVIC_SetPriority(SysTick_IRQn, 15);
    
}
