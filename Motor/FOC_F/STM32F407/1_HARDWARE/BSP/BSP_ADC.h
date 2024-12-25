/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef BSP_ADC_H
#define BSP_ADC_H

#include "MotorHal_cfg.h"

#define BSP_ADC_READ_DATA_VBUS              (ADC1->JDR4)
#define BSP_ADC_READ_DATA_TEMP              (0U)
#define BSP_ADC_READ_DATA_VR                (4095U)
#define BSP_ADC_READ_DATA_VBG               (0U)

#define ADC1_DR_Address                     ((Q32U_)0x4001204C) 

void BSP_ADC_Init(void);
void BSP_DMA_Init(void);
	
#endif /* BSP_ADC_H */
