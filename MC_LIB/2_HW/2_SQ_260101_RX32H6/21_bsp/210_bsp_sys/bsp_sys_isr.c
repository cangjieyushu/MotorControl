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
    NVIC_SetPriority(TIM8_CC_IRQn, 0);                  /* TIM8 触发中断 */
    NVIC_EnableIRQ(TIM8_CC_IRQn);

    NVIC_SetPriority(TIM3_IRQn,    1);                  /* TIM3 比较中断 */
    NVIC_EnableIRQ(TIM3_IRQn);

    NVIC_SetPriority(ADC_IRQn,     1);                  /* ADC 中断 */
    NVIC_EnableIRQ(ADC_IRQn);

    NVIC_SetPriority(SysTick_IRQn, 4);                  /* SysTick 中断 */
    NVIC_EnableIRQ(SysTick_IRQn);
}
