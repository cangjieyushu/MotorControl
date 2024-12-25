/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef BSP_WDG_H
#define BSP_WDG_H

#include "MotorHal_cfg.h"

#define IWDG_TIM            1000  //ms
#define IWDGPrescaler       IWDG_PRESCALER_16
#define ReloadCounter       (32000*IWDG_TIM/(4<<IWDGPrescaler)/1000)

void BSP_WDG_Init(void);

#endif /* BSP_WDG_H */
