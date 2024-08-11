/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include <stdint.h>
#include "stm32f4xx.h"

#define SHUTDOWN1_GPIO_Port         GPIOF
#define SHUTDOWN1_Pin               GPIO_Pin_10

#define Start_Stop_GPIO_Port        GPIOE
#define Start_Stop_Pin              GPIO_Pin_4

#define LED0_GPIO_PORT              GPIOE
#define LED0_Pin                    GPIO_Pin_0

#define LED1_GPIO_PORT              GPIOE
#define LED1_Pin                    GPIO_Pin_1

#define KEY0_GPIO_PORT              GPIOE
#define KEY0_Pin                    GPIO_Pin_2

#define KEY1_GPIO_PORT              GPIOE
#define KEY1_Pin                    GPIO_Pin_3

#define KEY2_GPIO_PORT              GPIOE
#define KEY2_Pin                    GPIO_Pin_4


#define ADC_CURRENT_NUMB            ADC1
#define ADC_U_CURRENT_GPIO_Port     GPIOB
#define ADC_U_CURRENT_Pin           GPIO_Pin_0
#define ADC_U_CURRENT_Channel       ADC_Channel_8

#define ADC_V_CURRENT_GPIO_Port     GPIOA
#define ADC_V_CURRENT_Pin           GPIO_Pin_6
#define ADC_V_CURRENT_Channel       ADC_Channel_6

#define ADC_W_CURRENT_GPIO_Port     GPIOA
#define ADC_W_CURRENT_Pin           GPIO_Pin_3
#define ADC_W_CURRENT_Channel       ADC_Channel_3

#define ADC_VBAT_GPIO_Port          GPIOB
#define ADC_VBAT_Pin                GPIO_Pin_1
#define ADC_VBAT_Channel            ADC_Channel_9


#define ADC_BEMF_NUMB               ADC3
#define ADC_U_BEMF_GPIO_Port        GPIOF
#define ADC_U_BEMF_Pin              GPIO_Pin_9
#define ADC_U_BEMF_Channel          GPIO_Pin_7

#define ADC_V_BEMF_GPIO_Port        GPIOF
#define ADC_V_BEMF_Pin              GPIO_Pin_8
#define ADC_V_BEMF_Channel          GPIO_Pin_6

#define ADC_W_BEMF_GPIO_Port        GPIOF
#define ADC_W_BEMF_Pin              GPIO_Pin_7
#define ADC_W_BEMF_Channel          GPIO_Pin_5


#define UH_PWM_GPIO_Port            GPIOA
#define UH_PWM_Pin                  GPIO_Pin_8
#define UH_PWM_Pin_Source           GPIO_PinSource8
    
#define VH_PWM_GPIO_Port            GPIOA
#define VH_PWM_Pin                  GPIO_Pin_9
#define VH_PWM_Pin_Source           GPIO_PinSource9
    
#define WH_PWM_GPIO_Port            GPIOA
#define WH_PWM_Pin                  GPIO_Pin_10
#define WH_PWM_Pin_Source           GPIO_PinSource10
    
#define UL_PWM_GPIO_Port            GPIOB
#define UL_PWM_Pin                  GPIO_Pin_13
#define UL_PWM_Pin_Source           GPIO_PinSource13
    
#define VL_PWM_GPIO_Port            GPIOB
#define VL_PWM_Pin                  GPIO_Pin_14
#define VL_PWM_Pin_Source           GPIO_PinSource14
    
#define WL_PWM_GPIO_Port            GPIOB
#define WL_PWM_Pin                  GPIO_Pin_15
#define WL_PWM_Pin_Source           GPIO_PinSource15
    
#define BKIN_PWM_GPIO_Port          GPIOB
#define BKIN_PWM_Pin                GPIO_Pin_12
#define BKIN_PWM_Pin_Source         GPIO_PinSource12

void BSP_GPIO_Init(void);

#endif /* BSP_GPIO_H */
