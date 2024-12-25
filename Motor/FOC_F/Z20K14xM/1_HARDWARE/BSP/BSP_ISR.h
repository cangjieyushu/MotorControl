/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef BSP_ISR_H
#define BSP_ISR_H

#include "MotorHal_cfg.h"

void BSP_ISR_Init(void);
void Hal_SetupInterrupts(isr_cb_t *M1FaultIntCbf, isr_cb_t *StimIntCbf);

#endif /* BSP_ISR_H */
