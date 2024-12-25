/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include "MotorHal_cfg.h"

void BSP_GPIO_Init(void);

Q32U_ BSP_GPIO_Read_SW0_State(void);
Q32U_ BSP_GPIO_Read_SW1_State(void);
Q32U_ BSP_GPIO_Read_SW2_State(void);

#endif /* BSP_GPIO_H */
