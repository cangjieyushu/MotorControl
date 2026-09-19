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
#include "stm32f4xx.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_flash.h"
#include "stm32f4xx_flash_ramfunc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_wwdg.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
//外设重定义
#define HAL_MOTOR_ADC               ADC1
#define HAL_MOTOR_PWM               TIM1
#define HAL_MOTOR_HALL_TIM          TIM2

#define HAL_HMI_UART                UART1


//全局引脚定义
//GPIO输入
#define KEY0_GPIO_PORT              GPIOE
#define KEY0_Pin                    GPIO_Pin_2

#define KEY1_GPIO_PORT              GPIOE
#define KEY1_Pin                    GPIO_Pin_3

#define KEY2_GPIO_PORT              GPIOE
#define KEY2_Pin                    GPIO_Pin_4


//GPIO输出
#define Recover_GPIO_Port             GPIOF
#define Recover_Pin                   GPIO_Pin_10

#define LED0_GPIO_PORT              GPIOE
#define LED0_Pin                    GPIO_Pin_0

#define LED1_GPIO_PORT              GPIOE
#define LED1_Pin                    GPIO_Pin_1


//ADC_MOTOR
#define ADC_U_CURRENT_GPIO_Port     GPIOB
#define ADC_U_CURRENT_Pin           GPIO_Pin_0
#define ADC_U_CURRENT_Channel       ADC_Channel_8

#define ADC_V_CURRENT_GPIO_Port     GPIOA
#define ADC_V_CURRENT_Pin           GPIO_Pin_6
#define ADC_V_CURRENT_Channel       ADC_Channel_6

#define ADC_W_CURRENT_GPIO_Port     GPIOA
#define ADC_W_CURRENT_Pin           GPIO_Pin_3
#define ADC_W_CURRENT_Channel       ADC_Channel_3


//ADC_SYSTEM
#define ADC_VBUS_GPIO_Port          GPIOB
#define ADC_VBUS_Pin                GPIO_Pin_1
#define ADC_VBUS_Channel            ADC_Channel_9

#define ADC_TEMP_GPIO_Port          GPIOA
#define ADC_TEMP_Pin                GPIO_Pin_0
#define ADC_TEMP_Channel            ADC_Channel_0



//PWM
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

#define ADC_TRIGGER_CHANNEL         TIM_CHANNEL_CH4


//HALL
#define U_HALL_GPIO_Port            GPIOH
#define U_HALL_Pin                  GPIO_Pin_10

#define V_HALL_GPIO_Port            GPIOH
#define V_HALL_Pin                  GPIO_Pin_11

#define W_HALL_GPIO_Port            GPIOH
#define W_HALL_Pin                  GPIO_Pin_12


#endif /* HW_MAP_H */
