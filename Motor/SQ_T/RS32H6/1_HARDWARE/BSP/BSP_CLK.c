/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_CLK.h"

void SysTickConfig(void)
{
    if(SysTick_Config(HAL_SLOW_TIMER_COUNT))
    {	
        while(1);
    }
}

void BSP_CLK_Init(void)
{
    SysTickConfig();
    
	// set flash lantency
    FLASH_Set_Latency(FLASH_Latency_3);

    RCC_Enable_HSI();
    while(RCC_Get_HSIRDY() != 1)
    {
    }
    RCC_Set_PLLMUL(RCC_CFGR_PLLMUL_18x);
    RCC_Enable_PLL();
    while(RCC_Get_PLLRDY() != 1)
    {
    }
    RCC_Set_AHBPrescaler(RCC_CFGR_HPRE_DIV1);
    RCC_Set_APB1Prescaler(RCC_CFGR_PPRE1_DIV2);
    RCC_Set_APB2Prescaler(RCC_CFGR_PPRE2_DIV1);
    RCC_Set_SysClkSource(RCC_CFGR_SW_PLL);
    while(RCC_Get_SysClkSource() != RCC_CFGR_SWS_PLL)
    {
    }
    RCC_Set_ADCClkSource(RCC_CFGR_ADCCLK_SEL_PLL2);
    RCC_Set_ADCPrescaler(RCC_CFGR_ADCPRE_DIV8);
    
	RCC_Enable_AHBClock(RCC_AHBENR_IOPAEN | RCC_AHBENR_IOPBEN | RCC_AHBENR_IOPCEN |RCC_AHBENR_IOPDEN);
	RCC_Enable_AHBClock(RCC_AHBENR_ADC1EN);
	RCC_Enable_APB2Clock(RCC_AHBENR_MEEN);
    
    RCC_Enable_APB1Clock(RCC_APB1ENR_TIM2EN);
    RCC_Enable_APB1Clock(RCC_APB1ENR_TIM3EN);
    
    RCC_Enable_APB2Clock(RCC_APB2ENR_TIM8EN);
	RCC_Enable_APB2Clock(RCC_APB2ENR_SYSCFGEN);
    
	RCC_Enable_APB2Clock(RCC_APB2ENR_UART1EN);
	RCC_Enable_APB1Clock(RCC_APB1ENR_UART2EN);
}
