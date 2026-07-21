/**************************************************************************************************
*     File Name :                        HAL_CFG.h
*     Library/Module Name :              HAL
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制硬件参数设置头文件
**************************************************************************************************/
#ifndef HAL_CFG_H
#define HAL_CFG_H

//调用所有外设的头文件
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
#include "MATH.h"

//频率设置
#define HAL_SYSTEM_FREQ                         (72000.0f)                      //kHz，系统时钟频率
#define HAL_PWM_CLK_FREQ                        (HAL_SYSTEM_FREQ)               //kHz，PWM时钟频率
#define HAL_HALL_TIM_CLK_FREQ                   (HAL_SYSTEM_FREQ)               //kHz，用过零点计数定时器时钟频率
#define HAL_SWITCH_TIM_CLK_FREQ                 (HAL_SYSTEM_FREQ)               //kHz，用于换向计数定时器时钟频率

#define HAL_PWM_PRESCALER                       (2.0f-1.0f)
#define HAL_PWM_PRE_FREQ                        (HAL_PWM_CLK_FREQ/(HAL_PWM_PRESCALER+1.0f))               //kHz，PWM计数器频率,36M


//载频选择
#define HAL_PWM_FREQ_1K                         (1.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_2K                         (2.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_5K                         (5.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_6K                         (6.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_8K                         (8.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_10K                        (10.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_12K                        (12.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_16K                        (16.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_18K                        (18.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_20K                        (20.0f)                         //kHz，PWM载频

#define HAL_PWM_INIT_FREQ                       (HAL_PWM_FREQ_1K)
#define HAL_PWM_RUN1_FREQ                       (HAL_PWM_FREQ_2K)
#define HAL_PWM_RUN2_FREQ                       (HAL_PWM_FREQ_5K)

#define HAL_PWM_INIT_SET                        (Q16U_)(HAL_PWM_PRE_FREQ/HAL_PWM_INIT_FREQ)
#define HAL_PWM_RUN1_SET                        (Q16U_)(HAL_PWM_PRE_FREQ/HAL_PWM_RUN1_FREQ)
#define HAL_PWM_RUN2_SET                        (Q16U_)(HAL_PWM_PRE_FREQ/HAL_PWM_RUN2_FREQ)


//PWM设置
#define HAL_PWM_DEADTIME_TIME                   (5.0f)                  //us，死区时间
#define HAL_PWM_DEADTIME_VALUE                  (Q32U_)(HAL_PWM_PRE_FREQ*HAL_PWM_DEADTIME_TIME/1000.0f)


//ADC采样时刻设置
#define HAL_ADC_DELAY_TIME                      (10.0f)                  //us，米勒平台时间
#define HAL_ADC_DELAY_VALUE                     (Q32U_)(HAL_ADC_DELAY_TIME*HAL_PWM_PRE_FREQ/1000.0f)
#define HAL_ADC_SAMPLE_TIME                     (5.0f)                  //us，ADC采样时间
#define HAL_ADC_SAMPLE_VALUE                    (Q32U_)(HAL_ADC_SAMPLE_TIME*HAL_PWM_PRE_FREQ/1000.0f)

#define HAL_ADC_SOLVE_TIME                      (20.0f)                 //us，换向判断时间
#define HAL_ADC_SOLVE_VALUE                     (Q32U_)(HAL_ADC_SOLVE_TIME*HAL_PWM_PRE_FREQ/1000.0f)


//TIM设置
#define HAL_HALL_TIM_PRESCALER                  (72.0f - 1.0f)
#define HAL_HALL_TIM_PRE_FREQ                   (Q32U_)(1000.0f*HAL_HALL_TIM_CLK_FREQ/(HAL_HALL_TIM_PRESCALER+1.0f))            //Hz，HALL换相时钟频率，1M
#define HAL_HALL_TIM_MAX_CNT                    (0xFFFFU)

#define HAL_SWITCH_TIM_PRESCALER                (72.0f - 1.0f)    
#define HAL_SWITCH_TIM_PRE_FREQ                 (Q32U_)(1000.0f*HAL_SWITCH_TIM_CLK_FREQ/(HAL_SWITCH_TIM_PRESCALER+1.0f))        //Hz，HALL换相时钟频率，1M

#define HAL_TIM_DELAY_MIN_TIME                  (10.0f)                                                     //us，TIM延迟最小时间
#define HAL_TIM_DELAY_MIN_VALUE                 (Q32U_)(HAL_TIM_DELAY_MIN_TIME)

#define HAL_SLOW_TIMER_FREQ                     (1.0f)                                                      //kHz，滴答定时器频率
#define HAL_SLOW_TIMER_COUNT                    (Q32U_)(HAL_SYSTEM_FREQ/HAL_SLOW_TIMER_FREQ)                //kHz，滴答定时器计数值


//ADC设置
#define HAL_ADC_REF_VOLTAGE_V                   (3.3f)                  //V，ADC参考电平
#define HAL_ADC_SCALE_BIT                       (4095.0f)               //lsb，ADC精度

//母线电压采样
#define HAL_ADC_VOLTAGE_RESISTOR_UP             (780.0f)                //母线电压采样上分压电阻
#define HAL_ADC_VOLTAGE_RESISTOR_DOWN           (3.9f)                  //母线电压采样下分压电阻
#define HAL_ADC_VOLTAGE_COEFF                   ((HAL_ADC_VOLTAGE_RESISTOR_UP+HAL_ADC_VOLTAGE_RESISTOR_DOWN)/HAL_ADC_VOLTAGE_RESISTOR_DOWN)
#define HAL_ADC_VOLTAGE_MAX                     (HAL_ADC_REF_VOLTAGE_V*HAL_ADC_VOLTAGE_COEFF)   //V，最大采样电压
#define HAL_ADC_VOLTAGE_SCALE                   (HAL_ADC_VOLTAGE_MAX/HAL_ADC_SCALE_BIT)         //V/lsb，电压刻度

//相电流采样
#define HAL_ADC_CURRENT_OFFSET                  (0.55f)                 //V，电流采样偏置电压
#define HAL_ADC_CURRENT_GAIN                    (11.0f)                 //相电流采样放大倍数
#define HAL_ADC_CURRENT_RESISTOR                (0.01f)                  //Ω，相电流采样电阻
#define HAL_ADC_CURRENT_COEFF                   (1.0f/(HAL_ADC_CURRENT_RESISTOR*HAL_ADC_CURRENT_GAIN))
#define HAL_ADC_CURRENT_MAX                     (HAL_ADC_REF_VOLTAGE_V*HAL_ADC_CURRENT_COEFF)   //A，最大采样电流
#define HAL_ADC_CURRENT_SCALE                   (HAL_ADC_CURRENT_MAX/HAL_ADC_SCALE_BIT)         //A/lsb，电流刻度


#define HAL_UART_RX_NUM                         (6U)
#define HAL_UART_TX_NUM                         ((4U + 1U) * 4U)
#define HAL_SPI_TX_NUM                          (1024U)

//外设
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


//引脚
//GPIO输入
//#define BTN1_GPIO_PORT              GPIOB
//#define BTN1_PIN                    GPIO_PIN_1

//#define BTN2_GPIO_PORT              GPIOB
//#define BTN2_PIN                    GPIO_PIN_2

//#define BTN3_GPIO_PORT              GPIOB
//#define BTN3_PIN                    GPIO_PIN_10

//#define BTN4_GPIO_PORT              GPIOB
//#define BTN4_PIN                    GPIO_PIN_11

//GPIO输出
#define RLYN_GPIO_PORT              GPIOA
#define RLYN_PIN                    GPIO_PIN_0

//#define RLY0_GPIO_PORT              GPIOA
//#define RLY0_PIN                    GPIO_PIN_1

//#define RLY1_GPIO_PORT              GPIOA
//#define RLY1_PIN                    GPIO_PIN_2


//ADC_MOTOR
#define ADC_U_BEMF_GPIO_PORT        GPIOA
#define ADC_U_BEMF_PIN              GPIO_PIN_5
#define ADC_U_BEMF_Channel          ADC_CHANNEL_5

#define ADC_V_BEMF_GPIO_PORT        GPIOA
#define ADC_V_BEMF_PIN              GPIO_PIN_6
#define ADC_V_BEMF_Channel          ADC_CHANNEL_6

#define ADC_W_BEMF_GPIO_PORT        GPIOA
#define ADC_W_BEMF_PIN              GPIO_PIN_7
#define ADC_W_BEMF_Channel          ADC_CHANNEL_7

#define ADC_PHASE_GPIO_PORT         GPIOB
#define ADC_PHASE_PIN               GPIO_PIN_0
#define ADC_PHASE_Channel           ADC_CHANNEL_8

//ADC_SYSTYM
#define ADC_TEMP_GPIO_PORT          GPIOA
#define ADC_TEMP_PIN                GPIO_PIN_3
#define ADC_TEMP_Channel            ADC_CHANNEL_3

#define ADC_VBUS_GPIO_PORT          GPIOA
#define ADC_VBUS_PIN                GPIO_PIN_4
#define ADC_VBUS_Channel            ADC_CHANNEL_4


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


#endif /* HAL_CFG_H */
