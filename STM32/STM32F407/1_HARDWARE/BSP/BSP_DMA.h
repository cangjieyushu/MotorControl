/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef BSP_DMA_H
#define BSP_DMA_H

#include <stdint.h>
#include "stm32f4xx.h"

#define ADC1_DR_Address                         ((uint32_t)0x4001204C) 
#define BSP_DMA_ADC_DATA_U_CURRENT              (0)
#define BSP_DMA_ADC_DATA_V_CURRENT              (1)
#define BSP_DMA_ADC_DATA_W_CURRENT              (2)
#define BSP_DMA_ADC_DATA_BAT_VOLTAGE            (3)

void BSP_DMA_Init(void);

extern uint16_t ADC_INT_RAW_DATA[4];

#endif /* BSP_DMA_H */
