/**************************************************************************************************
*     File Name :                        BSP_CLK.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             时钟初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_CLK.h"

/**********************************************************************************************
Function: BSP_CLK_Init
Description: 时钟初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_CLK_Init(void)
{
    CLK_PLLConfig_t PLLOSC40MSet160M =
    {
        /* PLL PreDivider value is 1 */
        .pllPreDivider = PLL_PRE_DIV_VALUE_4,
        /* PLL PostDivider value is 6 */
        .pllPostDivider = PLL_POST_DIV_VALUE_6,
        /* PLL Multiplier value is 24 */
        .pllMultiplier = 48,
        /* PLL Reference clock OSC40M */
        .pllRefClock = PLL_OSC_CLK,
        /* PLL PreScaler value is 1 */
        .pllPreScaler = PLL_SCALER_VALUE_2,
    };
    
    /* diable wdog module */
    SYSCTRL_EnableModule(SYSCTRL_WDOG);
    WDOG_Disable();
    CLK_OSC40MEnable(CLK_OSC_FREQ_MODE_HIGH, ENABLE, CLK_OSC_XTAL);
    CLK_PLLRefClockSelect(PLL_OSC_CLK);
    CLK_PLLConfig(&PLLOSC40MSet160M);
    CLK_PLLEnable(ENABLE);
    
    FLASH_SetWaitState(4);
    
    CLK_SysClkSrc(CLK_SYS_PLL);

    /* Set Core and bus clock */
    CLK_SetClkDivider(CLK_CORE, CLK_DIV_1);
    CLK_SetClkDivider(CLK_BUS, CLK_DIV_2);
    
    /* Select clock source for PWM1 */
    (void)CLK_ModuleSrc(HAL_M1PWM_CLK_MODULE, CLK_SRC_PLL);
    /* set clock for MCPWM0 , make sure it is not greater than bus clock */
    CLK_SetClkDivider(HAL_M1PWM_CLK_MODULE, CLK_DIV_2);
    /* Enable MCPWM0 clock */
    SYSCTRL_EnableModule(HAL_M1PWM_SYSCTRL_MODULE);
    
    /* Select clock source for PWM2 */
    (void)CLK_ModuleSrc(HAL_M2PWM_CLK_MODULE, CLK_SRC_PLL);
    /* set clock for MCPWM1 , make sure it is not greater than bus clock */
    CLK_SetClkDivider(HAL_M2PWM_CLK_MODULE, CLK_DIV_2);
    /* Enable MCPWM1 clock */
    SYSCTRL_EnableModule(HAL_M2PWM_SYSCTRL_MODULE);

     /* Select clock source for ADC0 */
    (void)CLK_ModuleSrc(CLK_ADC0, CLK_SRC_OSC40M);
    /* set clock for ADC , make sure it is not greater than bus clock */
    CLK_SetClkDivider(CLK_ADC0, CLK_DIV_1);
    /* Reset ADC */
    SYSCTRL_ResetModule(SYSCTRL_ADC0);
    /* Enable ADC clock */
    SYSCTRL_EnableModule(SYSCTRL_ADC0);
    /* Select clock source for ADC1 */
    (void)CLK_ModuleSrc(CLK_ADC1, CLK_SRC_OSC40M);
    /* set clock for ADC , make sure it is not greater than bus clock */
    CLK_SetClkDivider(CLK_ADC1, CLK_DIV_1);
    /* Reset ADC */
    SYSCTRL_ResetModule(SYSCTRL_ADC1);
    /* Enable ADC clock */
    SYSCTRL_EnableModule(SYSCTRL_ADC1);
     /* Select clock source for TDG0 */
    (void)CLK_ModuleSrc(CLK_TDG0, CLK_SRC_PLL);
    CLK_SetClkDivider(CLK_TDG0, CLK_DIV_2);
    /*Enable TDG0 module */
    SYSCTRL_EnableModule(SYSCTRL_TDG0);
    /* Select clock source for TDG1 */
    (void)CLK_ModuleSrc(CLK_TDG1, CLK_SRC_PLL);
    CLK_SetClkDivider(CLK_TDG1, CLK_DIV_2);
    /*Enable TDG1 module */
    SYSCTRL_EnableModule(SYSCTRL_TDG1);
    /* Select clock source for TMU */
    (void)CLK_ModuleSrc(CLK_TMU, CLK_SRC_OSC40M);
    /* Enable TMU module */
    SYSCTRL_EnableModule(SYSCTRL_TMU);
    /* Reset DMA */
    SYSCTRL_ResetModule(SYSCTRL_DMA);
    /* Enable DMA module */
    SYSCTRL_EnableModule(SYSCTRL_DMA);
    /* Reset DMAMUX module */
    SYSCTRL_ResetModule(SYSCTRL_DMAMUX);
    /* Enable DMAMUX module */
    SYSCTRL_EnableModule(SYSCTRL_DMAMUX);
    /* enable GPIO module */
    (void)CLK_ModuleSrc(CLK_PORTA, CLK_SRC_OSC40M);
    SYSCTRL_EnableModule(SYSCTRL_PORTA);
    (void)CLK_ModuleSrc(CLK_PORTB, CLK_SRC_OSC40M);
    SYSCTRL_EnableModule(SYSCTRL_PORTB);
    (void)CLK_ModuleSrc(CLK_PORTC, CLK_SRC_OSC40M);
    SYSCTRL_EnableModule(SYSCTRL_PORTC);
    (void)CLK_ModuleSrc(CLK_PORTD, CLK_SRC_OSC40M);
    SYSCTRL_EnableModule(SYSCTRL_PORTD);
    (void)CLK_ModuleSrc(CLK_PORTE, CLK_SRC_OSC40M);
    SYSCTRL_EnableModule(SYSCTRL_PORTE);
    SYSCTRL_EnableModule(SYSCTRL_GPIO);
}
