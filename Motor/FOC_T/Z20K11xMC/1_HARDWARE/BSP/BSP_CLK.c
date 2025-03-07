/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_CLK.h"

/**********************************************************************************************
Function: SysTickConfig
Description: 1ms时钟初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void SysTickConfig(void)
{
    if(SysTick_Config(HAL_SLOW_TIMER_COUNT))
    {	
        while(1);
    }
}

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
    SysTickConfig();
    
    /* Disable wdog */
    SYSCTRL_EnableModule(SYSCTRL_WDOG);
    WDOG_Disable();

    /* Select FIRC64M as system clock*/
    /* Clock init */
    CLK_OSC40MEnable2(CLK_OSC_FREQ_MODE_HIGH, DISABLE, CLK_OSC_XTAL);
    CLK_FIRC64MEnable(ENABLE);
    while (ERR == CLK_SysClkSrc(CLK_SYS_FIRC64M));

    /* set the core&bus clock divider */
    CLK_SetClkDivider(CLK_CORE, CLK_DIV_1);
    CLK_SetClkDivider(CLK_BUS, CLK_DIV_1);
   
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
    
    /* config the port clock and enable gpios */
    CLK_ModuleSrc(CLK_PORTA, CLK_SRC_FIRC64M);
    SYSCTRL_EnableModule(SYSCTRL_PORTA);
    CLK_ModuleSrc(CLK_PORTB, CLK_SRC_FIRC64M);
    SYSCTRL_EnableModule(SYSCTRL_PORTB);
    CLK_ModuleSrc(CLK_PORTC, CLK_SRC_FIRC64M);
    SYSCTRL_EnableModule(SYSCTRL_PORTC);
    CLK_ModuleSrc(CLK_PORTD, CLK_SRC_FIRC64M);
    SYSCTRL_EnableModule(SYSCTRL_PORTD);
    CLK_ModuleSrc(CLK_PORTE, CLK_SRC_FIRC64M);
    SYSCTRL_EnableModule(SYSCTRL_PORTE);
    /*Config GPIO module*/
    SYSCTRL_EnableModule(SYSCTRL_GPIO);

    /*TIM clock source select*/
    //SYSCTRL_EnableModule(SYSCTRL_TIM2);
    CLK_ModuleSrc(CLK_TIM0, CLK_SRC_FIRC64M);
    CLK_SetClkDivider(CLK_TIM0, CLK_DIV_1);

    /* Configure STIM function clock*/
    CLK_ModuleSrc(CLK_STIM, CLK_SRC_FIRC64M);

    /* Select clock source for ADC */
    CLK_ModuleSrc(CLK_ADC0, CLK_SRC_FIRC64M);
    /*set clock for ADC , make sure it is not greater than bus clock*/
    CLK_SetClkDivider(CLK_ADC0, CLK_DIV_1);

    /* Select clock source for TDG */
    CLK_ModuleSrc(CLK_TDG0, CLK_SRC_FIRC64M);
    /* set divide ratio of TDG's function clock*/
    CLK_SetClkDivider(CLK_TDG0, CLK_DIV_1);

    /* choose osc clock as function clock of uart1 */
    CLK_ModuleSrc(CLK_UART1, CLK_SRC_FIRC64M);
    /* set divide ratio of uart1's function clock*/
    CLK_SetClkDivider(CLK_UART1, CLK_DIV_1);
}
