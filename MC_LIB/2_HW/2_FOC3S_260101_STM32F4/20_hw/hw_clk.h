/*
*     File Name :                        hw_clk.h
*     Library/Module Name :              hw
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             时钟配置
*/


#ifndef HW_CLK_H
#define HW_CLK_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
//时钟配置
#define HAL_SYSTEM_CLK_FREQ                     (168000.0f)                             //kHz，系统时钟频率
#define HAL_PWM_CLK_FREQ                        (HAL_SYSTEM_CLK_FREQ)                   //kHz，PWM时钟频率
#define HAL_HALL_TIM_CLK_FREQ                   (HAL_SYSTEM_CLK_FREQ)                   //kHz，用过零点计数定时器时钟频率
#define HAL_SWITCH_TIM_CLK_FREQ                 (HAL_SYSTEM_CLK_FREQ)                   //kHz，用于换向计数定时器时钟频率


//PWM定时器
#define HAL_PWM_PRESCALER                       (2.0f)                                  //分频系数
#define HAL_PWM_PRE_FREQ                        (HAL_PWM_CLK_FREQ/HAL_PWM_PRESCALER)    //kHz，PWM计数器频率,84M

#define HAL_PWM_FREQ_2K                         (2.0f)                                  //kHz，PWM载频
#define HAL_PWM_FREQ_4K                         (4.0f)                                  //kHz，PWM载频
#define HAL_PWM_FREQ_8K                         (8.0f)                                  //kHz，PWM载频
#define HAL_PWM_FREQ_10K                        (10.0f)                                 //kHz，PWM载频
#define HAL_PWM_FREQ_12K                        (12.0f)                                 //kHz，PWM载频
#define HAL_PWM_FREQ_16K                        (16.0f)                                 //kHz，PWM载频
#define HAL_PWM_FREQ_20K                        (20.0f)                                 //kHz，PWM载频

#define HAL_PWM_INIT_VALUE                      (Q32U_)(HAL_PWM_PRE_FREQ/HAL_PWM_INIT_FREQ)
#define HAL_PWM_LOW_VALUE                       (Q32U_)(HAL_PWM_PRE_FREQ/HAL_PWM_LOW_FREQ)
#define HAL_PWM_HIGH_VALUE                      (Q32U_)(HAL_PWM_PRE_FREQ/HAL_PWM_HIGH_FREQ)

#define HAL_PWM_LOW_FREQ                        (HAL_PWM_FREQ_20K)
#define HAL_PWM_HIGH_FREQ                       (HAL_PWM_FREQ_20K)
#define HAL_PWM_ALL_VALUE_F                     (HAL_PWM_PRE_FREQ/HAL_PWM_HIGH_FREQ)
#define HAL_PWM_SET_VALUE_T                     (Q32U_)(HAL_PWM_ALL_VALUE_F/2.0f)

#define HAL_PWM_DEADTIME_TIME                   (Q32U_)(2.0f)                           //us，死区时间

#define HAL_CURRENT_LOOP_FREQ_PRESCALER         (1.0f)//电流环分频

//ADC采样时刻设置
#define HAL_ADC_DELAY_TIME                      (2.0f)                  //us，米勒平台时间
#define HAL_ADC_DELAY_DUTY                      (HAL_ADC_DELAY_TIME*HAL_PWM_HIGH_FREQ/1000.0f)
#define HAL_ADC_DELAY_VALUE                     (Q32U_)(HAL_ADC_DELAY_DUTY*HAL_PWM_ALL_VALUE_F)

#define HAL_ADC_SAMPLE_TIME                     (2.0f)                  //us，ADC采样时间
#define HAL_ADC_SAMPLE_DUTY                     (HAL_ADC_SAMPLE_TIME*HAL_PWM_HIGH_FREQ/1000.0f)
#define HAL_ADC_SAMPLE_VALUE                    (Q32U_)(HAL_ADC_SAMPLE_DUTY*HAL_PWM_ALL_VALUE_F)

#define HAL_MAX_DUTY                            (1.0f)
#define HAL_MID_DUTY                            (1.0f - (HAL_ADC_DELAY_DUTY + HAL_ADC_SAMPLE_DUTY))
#define HAL_MIN_DUTY                            (HAL_ADC_DELAY_DUTY + HAL_ADC_SAMPLE_DUTY)


//TIM设置
#define HAL_HALL_TIM_PRESCALER                  (84.0f)                                                                 //分频系数
#define HAL_HALL_TIM_PRE_FREQ                   (Q32U_)(1000.0f*HAL_HALL_TIM_CLK_FREQ/(HAL_HALL_TIM_PRESCALER))         //Hz，HALL换相时钟频率，1M
#define HAL_HALL_TIM_MAX_CNT                    (0x00FFFFFFU)

#define HAL_SLOW_TIM_FREQ                       (1.0f)                                                                  //kHz，慢速控制频率
#define HAL_SLOW_TIM_VALUE                      (Q32U_)(HAL_SYSTEM_CLK_FREQ/HAL_SLOW_TIM_FREQ)                          //kHz，慢速控制计数值


#endif /* HW_CLK_H */
