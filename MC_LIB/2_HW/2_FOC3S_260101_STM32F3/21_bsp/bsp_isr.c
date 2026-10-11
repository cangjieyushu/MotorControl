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
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 抢占 0~3，子 0~3（Group 2）*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* ============================================================
     * 优先级分配策略（抢占优先 + 子优先）：
     *   抢占 0：ADC 电流环（最快，周期最短）
     *   抢占 1：DMA 收发（大数据量，避免溢出）
     *   抢占 2：USART1 协议解析（IDLE 帧结束）
     *   抢占 3：SysTick 系统滴答（最低）
     * ============================================================ */

    /* ---------------- ADC1/2 注入组 JEOC ---------------- */
    NVIC_InitStructure.NVIC_IRQChannel                   = ADC1_2_IRQn;   /* ★ 修正 */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* ---------------- USART1（IDLE + 可选 RXNE/TC）---------------- */
    NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* ---------------- DMA1_Channel5：USART1_RX ---------------- */
    NVIC_InitStructure.NVIC_IRQChannel                   = DMA1_Channel5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* ---------------- DMA1_Channel4：USART1_TX ---------------- */
    NVIC_InitStructure.NVIC_IRQChannel                   = DMA1_Channel4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* ---------------- SysTick：最低优先级 ---------------- */
    NVIC_SetPriority(SysTick_IRQn, 15);   /* 抢占 3，子 3 */
}
