/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_ISR.h"
 
void BSP_ISR_Init(void)
{
    NVIC_SetPriority(SysTick_IRQn, 5);
	NVIC_EnableIRQ(SysTick_IRQn);
    
    NVIC_SetPriority (STIM_IRQn, 3); 
    NVIC_EnableIRQ(STIM_IRQn);
    
    NVIC_SetPriority (ADC0_IRQn, 3);
    NVIC_EnableIRQ(ADC0_IRQn);
    
    NVIC_SetPriority (TIM0_IRQn, 0);  
    NVIC_EnableIRQ(TIM0_IRQn);
}
