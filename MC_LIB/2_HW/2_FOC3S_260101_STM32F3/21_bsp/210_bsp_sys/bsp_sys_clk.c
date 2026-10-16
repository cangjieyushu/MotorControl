/*
*     File Name :                        bsp_sys_clk
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统时钟初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_sys_clk.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 内部辅助函数 ----------------------------*/
/*
Function: BSP_SYS_CLK_SysTickConfig
Description: SysTick 定时器配置（用于系统滴答、软件定时）
Input: 无
Output: 无
Return: 无
*/
static void BSP_SYS_CLK_SysTickConfig(void)
{
    if (SysTick_Config(HW_STICK_SET_VALUE))
    {
        while (1);
    }
}

/*
Function: BSP_SYS_CLK_PeriphClockSourceConfig
Description: 外设时钟源配置（ADC / TIM / USART）
Input: 无
Output: 无
Return: 无
*/
static void BSP_SYS_CLK_PeriphClockSourceConfig(void)
{
    /* ---- ADC 时钟源：PLL / 1 = 72 MHz（F303 最大允许值）---- */
    RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div1);   /* ADC1/ADC2 */
    RCC_ADCCLKConfig(RCC_ADC34PLLCLK_Div1);   /* ADC3/ADC4 */

    /* ---- TIM8 时钟源 ----
       默认来自 PCLK2 = 72 MHz。
       如需 144 MHz 高分辨率 PWM，取消下面这行注释：
       RCC_TIMCLKConfig(RCC_TIM8CLK_PLLCLK); */
}


/*-------------------------- 4. 公有接口实现 -----------------------------*/
/*
Function: BSP_SYS_CLK_Init
Description: 系统时钟初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_SYS_CLK_Init(void)
{
    /* ---- 1. SysTick 配置 ---- */
    BSP_SYS_CLK_SysTickConfig();

    /* ---- 2. 外设时钟源配置（ADC/TIM/USART）---- */
    BSP_SYS_CLK_PeriphClockSourceConfig();

    /* ---- 3. AHB 总线外设时钟 ---- */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,  ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,  ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC34, ENABLE);

    /* ---- 4. APB1 总线外设时钟 ---- */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);

    /* ---- 5. APB2 总线外设时钟 ---- */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,   ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    /* 调试用：确认系统时钟频率 */
    {
        RCC_ClocksTypeDef clocks;
        RCC_GetClocksFreq(&clocks);
        /* 断点观察 clocks.SYSCLK_Frequency 是否为 72000000 */
    }
}
