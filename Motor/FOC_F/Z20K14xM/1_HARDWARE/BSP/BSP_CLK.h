/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef BSP_CLK_H
#define BSP_CLK_H

#include "MotorHal_cfg.h"

#define HAL_M1PWM_CLK_MODULE            CLK_MCPWM0
#define HAL_M1PWM_SYSCTRL_MODULE        SYSCTRL_MCPWM0
#define HAL_M2PWM_CLK_MODULE            CLK_MCPWM1
#define HAL_M2PWM_SYSCTRL_MODULE        SYSCTRL_MCPWM1

void BSP_CLK_Init(void);

#endif /* BSP_CLK_H */
