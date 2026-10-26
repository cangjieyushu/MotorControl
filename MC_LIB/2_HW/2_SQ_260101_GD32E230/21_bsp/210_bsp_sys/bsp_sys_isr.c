/**
 * @file    bsp_sys_isr.c
 * @brief   中断优先级初始化
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
    nvic_irq_enable(TIMER0_Channel_IRQn,          0);    /* 触发中断 */
    nvic_irq_enable(TIMER2_IRQn,                  1);    /* 比较中断 */
    nvic_irq_enable(ADC_CMP_IRQn,                 1);    /* ADC 中断 */
    nvic_irq_enable(SysTick_IRQn,                 4);    /* SYS 中断 */
}
