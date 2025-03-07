/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_TIM.h"

void BSP_TIM_Init(isr_cb_t *StimSWIntCbf)
{	
    /* Enable STIM module */
    SYSCTRL_EnableModule(SYSCTRL_STIM);
    /* STIM configuration */
    const STIM_Config_t stimConfig =
    {
        .workMode = STIM_FREE_COUNT,
        .compareValue = 0xFFFFFFFFU,    /*counter clock is 64M, compare value =64000,  period = 1ms*/
        .countResetMode = STIM_INCREASE_FROM_0,
        .clockSource = STIM_FUNCTION_CLOCK,
        .prescalerOrFilterValue = STIM_DIV_64_FILTER_31,
    };
    
    /* Init STIM_0*/
    STIM_Init(STIM_1, &stimConfig);
    /*Disable STIM*/
    STIM_Enable(STIM_1);
    
    /* Init STIM_0*/
    STIM_Init(STIM_0, &stimConfig);
//    /*Disable STIM*/
//    STIM_Disable(STIM_0);
    
    STIM_InstallCallBackFunc(STIM_0, STIM_INT, StimSWIntCbf);
    
    STIM_Enable(STIM_0);    
    // Enable STIM_0 interrupt
    STIM_IntCmd(STIM_0, ENABLE); 
}
