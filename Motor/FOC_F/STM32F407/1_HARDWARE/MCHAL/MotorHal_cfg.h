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
#include "stm32f4xx.h"
#include "Math.h"
#include "Matrix.h"

//三电阻采样或者单电阻采样选择
#define HAL_ONE_SHUNT               (0U)
#define HAL_THREE_SHUNT             (1U)
#define HAL_CURRENT_SAMPLE_MODE     HAL_THREE_SHUNT   

//频率设置
#define HAL_SYSTEM_FREQ                         (168000.0f)                      //kHz，系统时钟频率
#define HAL_PWM_CLK_FREQ                        (HAL_SYSTEM_FREQ)               //kHz，PWM时钟频率
#define HAL_HALL_TIM_CLK_FREQ                   (HAL_SYSTEM_FREQ)          //kHz，用过零点计数定时器时钟频率
#define HAL_SWITCH_TIM_CLK_FREQ                 (HAL_SYSTEM_FREQ)          //kHz，用于换向计数定时器时钟频率

#define HAL_PWM_PRESCALER                       (1.0f-1.0f)
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

#define HAL_PWM_SET_FREQ                        (HAL_PWM_FREQ_20K)
#define HAL_PWM_ALL_COUNT_F                     (HAL_PWM_PRE_FREQ/HAL_PWM_SET_FREQ)
#define HAL_PWM_SET_COUNT_F                     (HAL_PWM_ALL_COUNT_F/2.0f)
#define HAL_PWM_SET_COUNT_U                     (Q32U_)(HAL_PWM_SET_COUNT_F)

//PWM设置
#define HAL_PWM_DEADTIME_TIME                   (0.5f)                  		//us，死区时间
#define HAL_PWM_DEADTIME_VALUE                  (Q32U_)(HAL_PWM_PRE_FREQ*HAL_PWM_DEADTIME_TIME/1000.0f/4.0f)


//ADC采样时刻设置
#define HAL_ADC_TRIGGER_TIME1                   (0.15f)
#define HAL_ADC_TRIGGER_TIME2                   (0.35f)
#define HAL_ADC_TRIGGER_TIME3                   (0.50f)

#if(HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
#define HAL_ADC_DELAY_TIME                      (2.0f)                  //us，米勒平台时间
#define HAL_ADC_DELAY_DUTY                      (HAL_ADC_DELAY_TIME*HAL_PWM_SET_FREQ/1000.0f)
#define HAL_ADC_DELAY_VALUE                     (Q32U_)(HAL_ADC_DELAY_DUTY*HAL_PWM_ALL_COUNT_F)

#define HAL_ADC_SAMPLE_TIME                     (3.0f)                  //us，ADC采样时间
#define HAL_ADC_SAMPLE_DUTY                     (HAL_ADC_SAMPLE_TIME*HAL_PWM_SET_FREQ/1000.0f)
#define HAL_ADC_SAMPLE_VALUE                    (Q32U_)(HAL_ADC_SAMPLE_DUTY*HAL_PWM_ALL_COUNT_F)

#define HAL_MAX_DUTY                            (1.0f - (HAL_ADC_DELAY_DUTY + HAL_ADC_SAMPLE_DUTY))
#define HAL_MIN_DUTY                            (HAL_ADC_DELAY_DUTY + HAL_ADC_SAMPLE_DUTY)

#elif(HAL_CURRENT_SAMPLE_MODE == HAL_ONE_SHUNT)
#define HAL_ADC_DELAY_TIME                      (2.0f)                  //us，米勒平台时间
#define HAL_ADC_DELAY_DUTY                      (HAL_ADC_DELAY_TIME*HAL_PWM_SET_FREQ/1000.0f)
#define HAL_ADC_DELAY_VALUE                     (Q16U_)(HAL_ADC_DELAY_DUTY*HAL_PWM_ALL_COUNT_F)

#define HAL_ADC_SAMPLE_TIME                     (2.0f)                  //us，ADC采样时间
#define HAL_ADC_SAMPLE_DUTY                     (HAL_ADC_SAMPLE_TIME*HAL_PWM_SET_FREQ/1000.0f)
#define HAL_ADC_SAMPLE_VALUE                    (Q16U_)(HAL_ADC_SAMPLE_DUTY*HAL_PWM_ALL_COUNT_F)

#define HAL_MAX_DUTY                            (1.0f - 2.0f*(HAL_ADC_DELAY_DUTY + HAL_ADC_SAMPLE_DUTY))
#define HAL_MIN_DUTY                            (2.0f*(HAL_ADC_DELAY_DUTY + HAL_ADC_SAMPLE_DUTY))

#endif

//TIM设置
#define HAL_HALL_TIM_PRESCALER                  (168.0f-1.0f)    
#define HAL_HALL_TIM_PRE_FREQ                   (Q32U_)(1000.0f*HAL_HALL_TIM_CLK_FREQ/(HAL_HALL_TIM_PRESCALER+1.0f))//Hz，HALL换相时钟频率，1M  

#define HAL_SLOW_TIMER_FREQ                     (1.0f)                  //kHz，滴答定时器周期
#define HAL_SLOW_TIMER_COUNT                    (Q32U_)(HAL_SYSTEM_FREQ/HAL_SLOW_TIMER_FREQ)     //kHz，滴答定时器周期


//ADC设置
#define HAL_ADC_REF_VOLTAGE_V                   (3.3f)                  //V，ADC参考电平
#define HAL_ADC_SCALE_BIT                       (4095.0f)               //lsb，ADC精度

//母线电压采样
#define HAL_ADC_VOLTAGE_RESISTOR_UP             (24.0f)                 //母线电压采样上分压电阻
#define HAL_ADC_VOLTAGE_RESISTOR_DOWN           (1.00f)                 //母线电压采样下分压电阻
#define HAL_ADC_VOLTAGE_COEFF                   ((HAL_ADC_VOLTAGE_RESISTOR_UP+HAL_ADC_VOLTAGE_RESISTOR_DOWN)/HAL_ADC_VOLTAGE_RESISTOR_DOWN)
#define HAL_ADC_VOLTAGE_MAX                     (HAL_ADC_REF_VOLTAGE_V*HAL_ADC_VOLTAGE_COEFF)   //V，最大采样电压
#define HAL_ADC_VOLTAGE_SCALE                   (HAL_ADC_VOLTAGE_MAX/HAL_ADC_SCALE_BIT)         //V/lsb，电压刻度

//相电流采样
#define HAL_ADC_CURRENT_GAIN                    (6.0f)                  //相电流采样放大倍数
#define HAL_ADC_CURRENT_RESISTOR                (0.020f)                //Ω，相电流采样电阻
#define HAL_ADC_CURRENT_COEFF                   (1.0f/(HAL_ADC_CURRENT_RESISTOR*HAL_ADC_CURRENT_GAIN))
#define HAL_ADC_CURRENT_MAX                     (HAL_ADC_REF_VOLTAGE_V*HAL_ADC_CURRENT_COEFF)   //A，最大采样电流
#define HAL_ADC_CURRENT_SCALE                   (HAL_ADC_CURRENT_MAX/HAL_ADC_SCALE_BIT)         //A/lsb，电流刻度


//引脚
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


#define U_HALL_GPIO_Port            GPIOH
#define U_HALL_Pin                  GPIO_Pin_10

#define V_HALL_GPIO_Port            GPIOH
#define V_HALL_Pin                  GPIO_Pin_11

#define W_HALL_GPIO_Port            GPIOH
#define W_HALL_Pin                  GPIO_Pin_12

#endif /* MotorHal_cfg_H */
