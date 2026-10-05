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
#include "gd32e23x_adc.h"
#include "gd32e23x_crc.h"
#include "gd32e23x_dbg.h"
#include "gd32e23x_dma.h"
#include "gd32e23x_exti.h"
#include "gd32e23x_fmc.h"
#include "gd32e23x_gpio.h"
#include "gd32e23x_syscfg.h"
#include "gd32e23x_i2c.h"
#include "gd32e23x_fwdgt.h"
#include "gd32e23x_pmu.h"
#include "gd32e23x_rcu.h"
#include "gd32e23x_rtc.h"
#include "gd32e23x_spi.h"
#include "gd32e23x_timer.h"
#include "gd32e23x_usart.h"
#include "gd32e23x_wwdgt.h"
#include "gd32e23x_misc.h"
#include "gd32e23x_cmp.h"
#include "math_type.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
//外设重定义
#define HAL_MOTOR_ADC               ADC
#define HAL_MOTOR_PWM               TIMER0
#define HAL_MOTOR_HALL_TIM          TIMER13
#define HAL_MOTOR_SWITCH_TIM        TIMER2
#define HAL_MOTOR_UART              USART0
#define HAL_MOTOR_SPI               SPI0
#define HAL_USART_TX_DMA_CH         DMA_CH3
#define HAL_USART_RX_DMA_CH         DMA_CH4
#define HAL_SPI_TX_DMA_CH           DMA_CH2
#define HAL_ADC_DMA_CH              DMA_CH0


//全局引脚定义
//GPIO输入
#define BTN0_GPIO_PORT              GPIOB
#define BTN0_PIN                    GPIO_PIN_4

#define BTN1_GPIO_PORT              GPIOB
#define BTN1_PIN                    GPIO_PIN_3

//#define BTN3_GPIO_PORT              GPIOB
//#define BTN3_PIN                    GPIO_PIN_10

//#define BTN4_GPIO_PORT              GPIOB
//#define BTN4_PIN                    GPIO_PIN_11

//GPIO输出
//#define RLYN_GPIO_PORT              GPIOA
//#define RLYN_PIN                    GPIO_PIN_0

//#define RLY0_GPIO_PORT              GPIOA
//#define RLY0_PIN                    GPIO_PIN_1

//#define RLY1_GPIO_PORT              GPIOA
//#define RLY1_PIN                    GPIO_PIN_2


//ADC_MOTOR
#define ADC_U_BEMF_GPIO_PORT        GPIOA
#define ADC_U_BEMF_PIN              GPIO_PIN_6
#define ADC_U_BEMF_Channel          ADC_CHANNEL_6

#define ADC_V_BEMF_GPIO_PORT        GPIOA
#define ADC_V_BEMF_PIN              GPIO_PIN_7
#define ADC_V_BEMF_Channel          ADC_CHANNEL_7

#define ADC_W_BEMF_GPIO_PORT        GPIOB
#define ADC_W_BEMF_PIN              GPIO_PIN_0
#define ADC_W_BEMF_Channel          ADC_CHANNEL_8

#define ADC_PHASE_GPIO_PORT         GPIOA
#define ADC_PHASE_PIN               GPIO_PIN_5
#define ADC_PHASE_Channel           ADC_CHANNEL_5

//ADC_SYSTEM
#define ADC_TEMP_GPIO_PORT          GPIOA
#define ADC_TEMP_PIN                GPIO_PIN_1
#define ADC_TEMP_Channel            ADC_CHANNEL_1

#define ADC_TPFC_GPIO_PORT          GPIOA
#define ADC_TPFC_PIN                GPIO_PIN_2
#define ADC_TPFC_Channel            ADC_CHANNEL_2

#define ADC_VBUS_GPIO_PORT          GPIOB
#define ADC_VBUS_PIN                GPIO_PIN_1
#define ADC_VBUS_Channel            ADC_CHANNEL_9


//PWM
#define UH_PWM_GPIO_PORT            GPIOA
#define UH_PWM_PIN                  GPIO_PIN_8
#define UH_PWM_CHANNEL              TIMER_CH_0
    
#define VH_PWM_GPIO_PORT            GPIOA
#define VH_PWM_PIN                  GPIO_PIN_9
#define VH_PWM_CHANNEL              TIMER_CH_1
    
#define WH_PWM_GPIO_PORT            GPIOA
#define WH_PWM_PIN                  GPIO_PIN_10
#define WH_PWM_CHANNEL              TIMER_CH_2
    
#define UL_PWM_GPIO_PORT            GPIOB
#define UL_PWM_PIN                  GPIO_PIN_13
#define UL_PWM_CHANNEL              TIMER_CH_0
    
#define VL_PWM_GPIO_PORT            GPIOB
#define VL_PWM_PIN                  GPIO_PIN_14
#define VL_PWM_CHANNEL              TIMER_CH_1
    
#define WL_PWM_GPIO_PORT            GPIOB
#define WL_PWM_PIN                  GPIO_PIN_15
#define WL_PWM_CHANNEL              TIMER_CH_2

#define BRK_PWM_GPIO_PORT           GPIOB
#define BRK_PWM_PIN                 GPIO_PIN_12

#define ADC_TRIGGER_CHANNEL         TIMER_CH_3


//UART
#define UART_RX_GPIO_PORT           GPIOB
#define UART_RX_PIN                 GPIO_PIN_7

#define UART_TX_GPIO_PORT           GPIOB
#define UART_TX_PIN                 GPIO_PIN_6

#define UART_TXEN_GPIO_PORT         GPIOB
#define UART_TXEN_PIN               GPIO_PIN_5


//SPI
//#define SPI_SCK_GPIO_PORT           GPIOB
//#define SPI_SCK_PIN                 GPIO_PIN_3

//#define SPI_MOSI_GPIO_PORT          GPIOB
//#define SPI_MOSI_PIN                GPIO_PIN_5

//#define SPI_RST_GPIO_PORT           GPIOB
//#define SPI_RST_PIN                 GPIO_PIN_8

//#define SPI_A0_GPIO_PORT            GPIOB
//#define SPI_A0_PIN                  GPIO_PIN_9

//#define SPI_CS_GPIO_PORT            GPIOA
//#define SPI_CS_PIN                  GPIO_PIN_15


#endif /* HW_MAP_H */
