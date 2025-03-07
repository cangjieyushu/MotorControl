/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef BSP_PWM_H
#define BSP_PWM_H

#include "MotorHal_cfg.h"

void BSP_PWM_Init(isr_cb_t *PwmFaultIntCbf, isr_cb_t *PwmCPIntCbf);

#endif /* BSP_PWM_H */
