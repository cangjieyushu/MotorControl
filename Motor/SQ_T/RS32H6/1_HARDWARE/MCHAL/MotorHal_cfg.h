/**************************************************************************************************
*     File Name :                        MotorHal_cfg.h
*     Library/Module Name :              MotorHal
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制硬件参数设置头文件
**************************************************************************************************/
#ifndef MotorHal_cfg_H
#define MotorHal_cfg_H

//调用所有外设的头文件

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
#include "Math.h"


//频率设置
#define HAL_SYSTEM_FREQ                         (144000.0f)                      //kHz，系统时钟频率
#define HAL_PWM_CLK_FREQ                        (HAL_SYSTEM_FREQ)               //kHz，PWM时钟频率
#define HAL_HALL_TIM_CLK_FREQ                   (HAL_SYSTEM_FREQ)          //kHz，用过零点计数定时器时钟频率
#define HAL_SWITCH_TIM_CLK_FREQ                 (HAL_SYSTEM_FREQ)          //kHz，用于换向计数定时器时钟频率

#define HAL_PWM_PRESCALER                       (3.0f-1.0f)
#define HAL_PWM_PRE_FREQ                        (HAL_PWM_CLK_FREQ/(HAL_PWM_PRESCALER+1.0f))               //kHz，PWM计数器频率,48M


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
#define HAL_PWM_RUN1_FREQ                       (HAL_PWM_FREQ_5K)
#define HAL_PWM_RUN2_FREQ                       (HAL_PWM_FREQ_10K)

#define HAL_PWM_INIT_SET                        (Q16U_)(HAL_PWM_PRE_FREQ/HAL_PWM_INIT_FREQ)
#define HAL_PWM_RUN1_SET                        (Q16U_)(HAL_PWM_PRE_FREQ/HAL_PWM_RUN1_FREQ)
#define HAL_PWM_RUN2_SET                        (Q16U_)(HAL_PWM_PRE_FREQ/HAL_PWM_RUN2_FREQ)

#define HAL_PWM_DUTY_MAX                        (Q12U_MAX)                              //最大占空比定点值
#define HAL_PWM_DUTY_MAX_U                      (Q16U_)(Q12U_MAX)

#define HAL_PWM_DUTY_1_PERCENT                  (Q16U_)(0.01f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_2_PERCENT                  (Q16U_)(0.02f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_3_PERCENT                  (Q16U_)(0.03f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_4_PERCENT                  (Q16U_)(0.04f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_5_PERCENT                  (Q16U_)(0.05f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_8_PERCENT                  (Q16U_)(0.08f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_10_PERCENT                 (Q16U_)(0.10f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_12_PERCENT                 (Q16U_)(0.12f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_15_PERCENT                 (Q16U_)(0.15f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_16_PERCENT                 (Q16U_)(0.16f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_18_PERCENT                 (Q16U_)(0.18f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_20_PERCENT                 (Q16U_)(0.20f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_30_PERCENT                 (Q16U_)(0.30f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_40_PERCENT                 (Q16U_)(0.40f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_50_PERCENT                 (Q16U_)(0.50f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_60_PERCENT                 (Q16U_)(0.60f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_70_PERCENT                 (Q16U_)(0.70f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_80_PERCENT                 (Q16U_)(0.80f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_90_PERCENT                 (Q16U_)(0.90f*HAL_PWM_DUTY_MAX)      //基础占空比
#define HAL_PWM_DUTY_100_PERCENT                (Q16U_)(1.00f*HAL_PWM_DUTY_MAX)      //基础占空比


//PWM设置
#define HAL_PWM_DEADTIME_TIME                   (1.0f*1.5f)                  //us，死区时间
#define HAL_PWM_DEADTIME_VALUE                  (Q32U_)(HAL_PWM_PRE_FREQ*HAL_PWM_DEADTIME_TIME/1000.0f)


//ADC采样时刻设置
#define HAL_ADC_DELAY_TIME                      (5.0f)                  //us，ADC延迟采样时间
#define HAL_ADC_DELAY_VALUE                     (Q32U_)(HAL_PWM_PRE_FREQ*HAL_ADC_DELAY_TIME/1000.0f)
#define HAL_ADC_SAMPLE_TIME                     (5.0f)                  //us，ADC采样时间
#define HAL_ADC_SAMPLE_VALUE                    (Q32U_)(HAL_PWM_PRE_FREQ*HAL_ADC_SAMPLE_TIME/1000.0f)

#define HAL_ADC_SOLVE_TIME                      (15.0f)                 //us，换向判断时间
#define HAL_ADC_SOLVE_VALUE                     (Q32U_)(HAL_PWM_PRE_FREQ*HAL_ADC_SOLVE_TIME/1000.0f)


//TIM设置
#define HAL_HALL_TIM_PRESCALER                  (144.0f - 1.0f)    
#define HAL_HALL_TIM_PRE_FREQ                   (Q32U_)(1000.0f*HAL_HALL_TIM_CLK_FREQ/(HAL_HALL_TIM_PRESCALER+1.0f))          //Hz，PWM时钟频率，1M  

#define HAL_SWITCH_TIM_PRESCALER                (144.0f - 1.0f)    
#define HAL_SWITCH_TIM_PRE_FREQ                 (Q32U_)(1000.0f*HAL_SWITCH_TIM_CLK_FREQ/(HAL_SWITCH_TIM_PRESCALER+1.0f))      //Hz，PWM时钟频率，1M

#define HAL_TIM_DELAY_TIME                      (10.0f)                         //us，TIM延迟最小时间
#define HAL_TIM_DELAY_VALUE                     (Q32U_)(HAL_TIM_DELAY_TIME)

#define HAL_SLOW_TIMER_FREQ                     (1.0f)                          //kHz，滴答定时器频率
#define HAL_SLOW_TIMER_COUNT                    (Q32U_)(HAL_SYSTEM_FREQ/HAL_SLOW_TIMER_FREQ)              //kHz，滴答定时器计数值


//ADC设置
#define HAL_ADC_REF_VOLTAGE_V                   (3.3f)                  //V，ADC参考电平
#define HAL_ADC_SCALE_BIT                       (4095.0f)               //lsb，ADC精度

//母线电压采样
#define HAL_ADC_VOLTAGE_RESISTOR_UP             (10.0f)                 //母线电压采样上分压电阻
#define HAL_ADC_VOLTAGE_RESISTOR_DOWN           (0.47f)                 //母线电压采样下分压电阻
#define HAL_ADC_VOLTAGE_COEFF                   ((HAL_ADC_VOLTAGE_RESISTOR_UP+HAL_ADC_VOLTAGE_RESISTOR_DOWN)/HAL_ADC_VOLTAGE_RESISTOR_DOWN)
#define HAL_ADC_VOLTAGE_MAX                     (HAL_ADC_REF_VOLTAGE_V*HAL_ADC_VOLTAGE_COEFF)   //V，最大采样电压
#define HAL_ADC_VOLTAGE_SCALE                   (HAL_ADC_VOLTAGE_MAX/HAL_ADC_SCALE_BIT)         //V/lsb，电压刻度

//相电流采样
#define HAL_ADC_CURRENT_GAIN                    (8.0f)                  //相电流采样放大倍数
#define HAL_ADC_CURRENT_RESISTOR                (0.005f)                //Ω，相电流采样电阻
#define HAL_ADC_CURRENT_COEFF                   (1.0f/(HAL_ADC_CURRENT_RESISTOR*HAL_ADC_CURRENT_GAIN))
#define HAL_ADC_CURRENT_MAX                     (HAL_ADC_REF_VOLTAGE_V*HAL_ADC_CURRENT_COEFF)   //A，最大采样电流
#define HAL_ADC_CURRENT_SCALE                   (HAL_ADC_CURRENT_MAX/HAL_ADC_SCALE_BIT)         //A/lsb，电流刻度


//外设
#define HAL_MOTOR_ADC               ADC1
#define HAL_MOTOR_OPA               OPAMP2
#define HAL_MOTOR_CMP               COMP2
#define HAL_MOTOR_PWM               TIM8
#define HAL_MOTOR_HALL_TIM          TIM2
#define HAL_MOTOR_SWITCH_TIM        TIM3


//引脚
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


#endif /* MotorHal_cfg_H */
