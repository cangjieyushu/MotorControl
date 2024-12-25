/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef BSP_ADC_H
#define BSP_ADC_H

#include "MotorHal_cfg.h"

#define BSP_ADC_READ_DATA_VBUS      ((Q32U_)0)
#define BSP_ADC_READ_DATA_TEMP      ((Q32U_)0)
#define BSP_ADC_READ_DATA_VR        ((Q32U_)0)
#define BSP_ADC_READ_DATA_VBG       ((Q32U_)0)

//ADC_SYSTYM
#define ADC_TEMP_GPIO_PORT          GPIOC
#define ADC_TEMP_PIN                GPIO_PIN_1
#define ADC_TEMP_Channel            ADC_CHANNEL_3

#define ADC_VR_GPIO_PORT            GPIOB
#define ADC_VR_PIN                  GPIO_PIN_5
#define ADC_VR_Channel              ADC_CHANNEL_7

#define ADC_VBUS_GPIO_PORT          GPIOD
#define ADC_VBUS_PIN                GPIO_PIN_5
#define ADC_VBUS_Channel            ADC_CHANNEL_14

#define ADC_VBG_Channel             ADC_CHANNEL_VBGINT

void BSP_ADC_Init(void);

#endif /* BSP_ADC_H */
