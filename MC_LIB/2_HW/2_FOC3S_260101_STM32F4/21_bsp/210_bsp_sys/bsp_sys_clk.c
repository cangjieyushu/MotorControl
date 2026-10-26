/**
 * @file    bsp_sys_clk.c
 * @brief   系统时钟初始化
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_sys_clk.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  SysTick 定时器配置（1ms 系统滴答）
 */
static void BSP_SYS_CLK_SysTickConfig(void)
{
    if (SysTick_Config(HW_STICK_SET_VALUE))
    {
        while (1);
    }
}

/**
 * @brief  系统时钟初始化
 */
void BSP_SYS_CLK_Init(void)
{
    /* ---- 1. SysTick 配置（168MHz 已在 SystemInit 完成） ---- */
    BSP_SYS_CLK_SysTickConfig();

    /* ---- 2. 外设时钟源配置 ---- */
    /* （F4 ADC 时钟 = PCLK2 / 2 / 分频，TIM 时钟默认 APBx，此处无需额外配置） */

    /* ---- 3. AHB1 总线外设时钟（GPIOA~I） ---- */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);

    /* ---- 4. APB1 总线外设时钟 ---- */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* ---- 5. APB2 总线外设时钟 ---- */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,   ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,   ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* 调试用：确认系统时钟频率（断点观察 clocks.SYSCLK_Frequency 是否为 168000000） */
    {
        RCC_ClocksTypeDef clocks;
        RCC_GetClocksFreq(&clocks);
        RCC_GetClocksFreq(&clocks);
    }
}
