/*
*     File Name :                        bsp_clk
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             时钟初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_clk.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 内部辅助函数 ----------------------------*/
/*
Function: BSP_CLK_SysTickConfig
Description: SysTick 定时器配置（用于系统滴答、软件定时）
Input: 无
Output: 无
Return: 无
*/
static void BSP_CLK_SysTickConfig(void)
{
    if (SysTick_Config(HAL_SLOW_TIM_VALUE))
    {
        while (1);
    }
}

/*
Function: BSP_CLK_PeriphClockSourceConfig
Description: 外设时钟源配置（ADC / TIM / USART）
Input: 无
Output: 无
Return: 无
*/
static void BSP_CLK_PeriphClockSourceConfig(void)
{
    /* ---- ADC 时钟源：PLL / 1 = 72 MHz（F303 最大允许值）---- */
    RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div1);   /* ADC1/ADC2 */
    RCC_ADCCLKConfig(RCC_ADC34PLLCLK_Div1);   /* ADC3/ADC4 */

    /* ---- TIM8 时钟源 ----
       默认来自 PCLK2 = 72 MHz，死区时间按 tDTS = 4/72MHz 计算。
       如需 144 MHz 高分辨率 PWM，取消下面这行注释：
       RCC_TIMCLKConfig(RCC_TIM8CLK_PLLCLK);
       注意：切换后死区时间计算要改为 tDTS = 4/144MHz。 */

    /* ---- USART1 时钟源 ----
       默认来自 PCLK2 = 72 MHz。如需其他时钟：
       RCC_USARTCLKConfig(RCC_USART1CLK_SYSCLK);
       RCC_USARTCLKConfig(RCC_USART1CLK_LSE);
       RCC_USARTCLKConfig(RCC_USART1CLK_HSI); */
}


/*-------------------------- 4. 公有接口实现 -----------------------------*/
/*
Function: BSP_CLK_Init
Description: 时钟初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_CLK_Init(void)
{
    /* ---- 1. SysTick 配置 ---- */
    BSP_CLK_SysTickConfig();

    /* ---- 2. 外设时钟源配置（ADC/TIM/USART）---- */
    BSP_CLK_PeriphClockSourceConfig();

    /* ---- 3. AHB 总线外设时钟 ---- */
    /* GPIOA/B/C/D（PA/PB/PC/PD 组）*/
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);

    /* DMA1（ADC1 规则组 DMA 通道）*/
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    /* ADC 接口时钟（F3 独立于 APB2）*/
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);   /* ADC1/ADC2 */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC34, ENABLE);   /* ADC3/ADC4 */

    /* ---- 4. APB1 总线外设时钟 ---- */
    /* DAC1（比较器窗口阈值输出）*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC1, ENABLE);

    /* TIM2（HALL 计时）*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* SPI3（HMI 通讯）*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);

    /* ---- 5. APB2 总线外设时钟 ---- */
    /* TIM8（三相 PWM）*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

    /* USART1（HMI 通讯）*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* SYSCFG（CMP 窗口模式、EXTI 端口映射）*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* ---- 6. 读取时钟频率（调试用，正式版可删）---- */
    {
        RCC_ClocksTypeDef clocks;
        RCC_GetClocksFreq(&clocks);
        /* 断点或串口打印 clocks.SYSCLK_Frequency 确认系统频率 */
    }
}
