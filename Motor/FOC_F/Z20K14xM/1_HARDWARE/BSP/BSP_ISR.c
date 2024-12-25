/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#include "BSP_ISR.h"

void BSP_ISR_Init(void)
{
    INT_SetPriority(STIM_IRQn, 2);
    INT_SetPriority(DMA_Ch0_IRQn, 1);
    INT_SetPriority(MCPWM1_Fault_IRQn, 0);
    INT_EnableIRQ(STIM_IRQn);
    INT_EnableIRQ(DMA_Ch0_IRQn);
    INT_EnableIRQ(MCPWM1_Fault_IRQn);
}
