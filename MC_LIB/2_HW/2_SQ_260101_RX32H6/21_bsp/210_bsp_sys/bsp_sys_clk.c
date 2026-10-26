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
static void BSP_SYS_CLK_SysTickConfig(void);

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
    /* ---- 1. SysTick 配置 ---- */
    BSP_SYS_CLK_SysTickConfig();

    /* ---- 2. Flash 等待周期（144MHz 需要 3 个等待周期） ---- */
    FLASH_Set_Latency(FLASH_Latency_3);

    /* ---- 3. 时钟源：HSI 起振 → PLL ×18 → 144MHz ---- */
    RCC_Enable_HSI();
    while (RCC_Get_HSIRDY() != 1)
    {
    }
    RCC_Set_PLLMUL(RCC_CFGR_PLLMUL_18x);
    RCC_Enable_PLL();
    while (RCC_Get_PLLRDY() != 1)
    {
    }

    /* ---- 4. 总线分频：AHB/1、APB1/2、APB2/1 ---- */
    RCC_Set_AHBPrescaler(RCC_CFGR_HPRE_DIV1);
    RCC_Set_APB1Prescaler(RCC_CFGR_PPRE1_DIV2);
    RCC_Set_APB2Prescaler(RCC_CFGR_PPRE2_DIV1);

    /* ---- 5. 切换系统时钟源到 PLL ---- */
    RCC_Set_SysClkSource(RCC_CFGR_SW_PLL);
    while (RCC_Get_SysClkSource() != RCC_CFGR_SWS_PLL)
    {
    }

    /* ---- 6. ADC 时钟源：PLL2 / 8 ---- */
    RCC_Set_ADCClkSource(RCC_CFGR_ADCCLK_SEL_PLL2);
    RCC_Set_ADCPrescaler(RCC_CFGR_ADCPRE_DIV8);

    /* ---- 7. AHB 总线外设时钟 ---- */
    RCC_Enable_AHBClock(RCC_AHBENR_IOPAEN | RCC_AHBENR_IOPBEN | RCC_AHBENR_IOPCEN | RCC_AHBENR_IOPDEN);
    RCC_Enable_AHBClock(RCC_AHBENR_ADC1EN);
    RCC_Enable_AHBClock(RCC_AHBENR_MEEN);

    /* ---- 8. APB1 总线外设时钟 ---- */
    RCC_Enable_APB1Clock(RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN);

    /* ---- 9. APB2 总线外设时钟 ---- */
    RCC_Enable_APB2Clock(RCC_APB2ENR_TIM8EN | RCC_APB2ENR_SYSCFGEN);
}
