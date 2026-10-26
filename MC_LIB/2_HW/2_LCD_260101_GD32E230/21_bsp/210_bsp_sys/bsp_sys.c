/**
 * @file    bsp_sys.c
 * @brief   系统级外设汇总初始化
 *          - 调用顺序：CLK → GPIO → ISR → DMA_UART → UART
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_sys.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  系统级外设汇总初始化
 */
void BSP_SYS_Init(void)
{
    BSP_SYS_CLK_Init();         /* 系统时钟 + SysTick */
    BSP_SYS_GPIO_Init();        /* 按键/LED/测试点/RS485 EN */
    BSP_SYS_ISR_Init();         /* NVIC 优先级 */

    BSP_SYS_DMA_UART_Init();    /* 串口 DMA 先配置 */
    BSP_SYS_UART_Init();        /* 再使能 USART */
}
