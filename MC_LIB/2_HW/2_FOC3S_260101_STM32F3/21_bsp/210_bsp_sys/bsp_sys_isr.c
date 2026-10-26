/**
 * @file    bsp_sys_isr.c
 * @brief   中断优先级初始化
 *          - NVIC 分组 Group 2（抢占 0~3，子 0~3）
 *          - TIM8_UP：抢占 0，子 0（最高）
 *          - SysTick：抢占 1，子 0
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_sys_isr.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  中断优先级初始化
 */
void BSP_SYS_ISR_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 抢占 0~3，子 0~3（Group 2） */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* ---------------- TIM8 更新：抢占 0 ---------------- */
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM8_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* ---------------- SysTick：抢占 1，子 0 ----------------
     * SysTick 是内核异常，不能用 NVIC_Init，必须用 NVIC_SetPriority。
     * Group 2 下 4 位优先级中 [3:2]=抢占，[1:0]=子，
     * 抢占 1、子 0 对应编码值 0b0100 = 4。
     */
    NVIC_SetPriority(SysTick_IRQn, 4);
}
