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
    
    /* ---- 3. AHB 总线外设时钟 ---- */    
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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    
    /* 调试用：确认系统时钟频率 */
    {
        RCC_ClocksTypeDef clocks;
        RCC_GetClocksFreq(&clocks);
        /* 断点观察 clocks.SYSCLK_Frequency 是否为 72000000 */
    }
}
