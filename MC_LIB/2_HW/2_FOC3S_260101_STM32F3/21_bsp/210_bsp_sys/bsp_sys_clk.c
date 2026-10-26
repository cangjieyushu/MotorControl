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
        while (1)
        {
        }
    }
}

/**
 * @brief  外设时钟源配置（ADC / TIM）
 */
static void BSP_SYS_CLK_PeriphClockSourceConfig(void)
{
    /* ---- ADC 时钟源：PLL / 1 = 72MHz（F303 最大允许值） ---- */
    RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div1);   /* ADC1/ADC2 */
    RCC_ADCCLKConfig(RCC_ADC34PLLCLK_Div1);   /* ADC3/ADC4 */

    /* ---- TIM8 时钟源 ----
       默认来自 PCLK2 = 72MHz。
       如需 144MHz 高分辨率 PWM，取消下面这行注释：
       RCC_TIMCLKConfig(RCC_TIM8CLK_PLLCLK); */
}

/**
 * @brief  系统时钟初始化
 */
void BSP_SYS_CLK_Init(void)
{
    ErrorStatus HSEStartUpStatus;

    /* ---- 1. SysTick 配置 ---- */
    BSP_SYS_CLK_SysTickConfig();

    /* ---- 2. 复位 RCC 寄存器到默认状态 ---- */
    RCC_DeInit();

    /* ---- 3. 使能外部高速晶振 HSE 并等待起振 ---- */
    RCC_HSEConfig(RCC_HSE_ON);
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if (HSEStartUpStatus == SUCCESS)
    {
        /* 4. 设置 Flash 等待周期（72MHz 需要 2 个等待周期）+ 使能预取 */
        FLASH_SetLatency(FLASH_Latency_2);
        FLASH_PrefetchBufferCmd(ENABLE);

        /* 5. 配置总线分频
              AHB  = SYSCLK = 72MHz
              APB1 = AHB/2  = 36MHz（F303 APB1 上限）
              APB2 = AHB    = 72MHz */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        RCC_PCLK1Config(RCC_HCLK_Div2);
        RCC_PCLK2Config(RCC_HCLK_Div1);

        /* 6. 配置 PLL：HSE 不分频，9 倍频 → 8MHz × 9 = 72MHz */
        RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
        RCC_PLLCmd(ENABLE);

        /* 7. 等待 PLL 锁定 */
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
        }

        /* 8. 切换系统时钟源到 PLL，并等待生效（0x08 表示 PLL 已成为系统时钟） */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        while (RCC_GetSYSCLKSource() != 0x08)
        {
        }

        /* 9. 更新 SystemCoreClock 变量（供 SysTick 等使用） */
        SystemCoreClockUpdate();
    }
    else
    {
        /* HSE 启动失败，可在此处处理错误（如切换到 HSI） */
        while (1)
        {
        }
    }

    /* ---- 10. 外设时钟源配置 ---- */
    BSP_SYS_CLK_PeriphClockSourceConfig();

    /* ---- 11. AHB 总线外设时钟 ---- */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,  ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,  ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC34, ENABLE);

    /* ---- 12. APB1 总线外设时钟 ---- */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);

    /* ---- 13. APB2 总线外设时钟 ---- */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,   ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* 调试用：确认系统时钟频率，断点观察 clocks.SYSCLK_Frequency 是否为 72000000 */
    {
        RCC_ClocksTypeDef clocks;
        RCC_GetClocksFreq(&clocks);
    }
}
