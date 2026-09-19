/*
*     File Name :                        hw_map
*     Library/Module Name :              hw
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             中断、引脚重映射
*/


#ifndef HW_MAP_H
#define HW_MAP_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "rx32h6xx.h"
#include "rx32h6xx_adc.h"
#include "rx32h6xx_cmp.h"
#include "rx32h6xx_crc.h"
#include "rx32h6xx_exti.h"
#include "rx32h6xx_flash.h"
#include "rx32h6xx_gpio.h"
#include "rx32h6xx_i2c.h"
#include "rx32h6xx_iwdg.h"
#include "rx32h6xx_me.h"
#include "rx32h6xx_opamp.h"
#include "rx32h6xx_pwr.h"
#include "rx32h6xx_rcc.h"
#include "rx32h6xx_rtc.h"
#include "rx32h6xx_spi.h"
#include "rx32h6xx_tim.h"
#include "rx32h6xx_usart.h"
#include "core_cm0.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
//外设重定义
#define HAL_MOTOR_ADC               ADC1
#define HAL_MOTOR_OPA               OPAMP2
#define HAL_MOTOR_CMP               COMP2
#define HAL_MOTOR_PWM               TIM8
#define HAL_MOTOR_HALL_TIM          TIM2
#define HAL_MOTOR_SWITCH_TIM        TIM3

#define HAL_HMI_UART                UART1


//全局引脚定义
//GPIO输入
#define BUTTON_GPIO_PORT            GPIOB
#define BUTTON_PIN                  GPIO_PIN_5


//GPIO输出
#define LED0_GPIO_PORT              GPIOC
#define LED0_PIN                    GPIO_PIN_2

#define LED1_GPIO_PORT              GPIOC
#define LED1_PIN                    GPIO_PIN_3


//ADC_MOTOR
#define ADC_U_BEMF_GPIO_PORT        GPIOC
#define ADC_U_BEMF_PIN              GPIO_PIN_0
#define ADC_U_BEMF_Channel          ADC_CHANNEL_4

#define ADC_V_BEMF_GPIO_PORT        GPIOB
#define ADC_V_BEMF_PIN              GPIO_PIN_6
#define ADC_V_BEMF_Channel          ADC_CHANNEL_6

#define ADC_W_BEMF_GPIO_PORT        GPIOB
#define ADC_W_BEMF_PIN              GPIO_PIN_4
#define ADC_W_BEMF_Channel          ADC_CHANNEL_8

#define ADC_PHASE_Channel           ADC_CHANNEL_OPA2


//ADC_SYSTEM
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


//OPA
#define OPA_PHASE_P_GPIO_PORT       GPIOA
#define OPA_PHASE_P_PIN             GPIO_PIN_6

#define OPA_PHASE_N_GPIO_PORT       GPIOA
#define OPA_PHASE_N_PIN             GPIO_PIN_7


//CMP
#define CMP_PHASE_P_GPIO_PORT       GPIOA
#define CMP_PHASE_P_PIN             GPIO_PIN_6

#define CMP_PHASE_N_GPIO_PORT       GPIOA
#define CMP_PHASE_N_PIN             GPIO_PIN_7


//PWM
#define UH_PWM_GPIO_PORT            GPIOD
#define UH_PWM_PIN                  GPIO_PIN_3
#define UH_PWM_AF                   GPIO_AF1
#define UH_PWM_CHANNEL              TIM_CHANNEL_CH1
    
#define VH_PWM_GPIO_PORT            GPIOD
#define VH_PWM_PIN                  GPIO_PIN_1
#define VH_PWM_AF                   GPIO_AF1
#define VH_PWM_CHANNEL              TIM_CHANNEL_CH2
    
#define WH_PWM_GPIO_PORT            GPIOC
#define WH_PWM_PIN                  GPIO_PIN_7
#define WH_PWM_AF                   GPIO_AF1
#define WH_PWM_CHANNEL              TIM_CHANNEL_CH3
    
#define UL_PWM_GPIO_PORT            GPIOD
#define UL_PWM_PIN                  GPIO_PIN_2
#define UL_PWM_AF                   GPIO_AF1
#define UL_PWM_CHANNEL              TIM_CHANNEL_CH1N
    
#define VL_PWM_GPIO_PORT            GPIOD
#define VL_PWM_PIN                  GPIO_PIN_0
#define VL_PWM_AF                   GPIO_AF1
#define VL_PWM_CHANNEL              TIM_CHANNEL_CH2N
    
#define WL_PWM_GPIO_PORT            GPIOC
#define WL_PWM_PIN                  GPIO_PIN_6
#define WL_PWM_AF                   GPIO_AF1
#define WL_PWM_CHANNEL              TIM_CHANNEL_CH3N

#define ADC_TRIGGER_CHANNEL         TIM_CHANNEL_CH4


//HALL
#define U_HALL_GPIO_PORT            GPIOC
#define U_HALL_PIN                  GPIO_PIN_0

#define V_HALL_GPIO_PORT            GPIOB
#define V_HALL_PIN                  GPIO_PIN_6

#define W_HALL_GPIO_PORT            GPIOB
#define W_HALL_PIN                  GPIO_PIN_4


#endif /* HW_MAP_H */
