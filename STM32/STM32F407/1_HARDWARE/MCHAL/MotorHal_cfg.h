/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef MotorHal_cfg_H
#define MotorHal_cfg_H

#include <stdint.h>

//ADC设置
#define HAL_ADC_REF_VOLTAGE                     (3.3f)                  //V，ADC参考电平
#define HAL_ADC_SCALE_BIT                       (4095.0f)               //lsb，ADC精度

//母线电压采样
#define HAL_ADC_VOLTAGE_RESISTOR_UP             (24.0f)                 //母线电压采样上分压电阻
#define HAL_ADC_VOLTAGE_RESISTOR_DOWN           (1.0f)                  //母线电压采样下分压电阻
#define HAL_ADC_SCALE_VOLTAGE                   (HAL_ADC_REF_VOLTAGE*(HAL_ADC_VOLTAGE_RESISTOR_UP+HAL_ADC_VOLTAGE_RESISTOR_DOWN)/HAL_ADC_VOLTAGE_RESISTOR_DOWN/HAL_ADC_SCALE_BIT)//V

//相电流采样
#define HAL_ADC_CURRENT_GAIN                    (6.0f)                 //相电流采样放大倍数
#define HAL_ADC_CURRENT_RESISTOR                (0.020f)                //Ω，相电流采样电阻
#define HAL_ADC_FULL_SCALE_CURRENT              (HAL_ADC_REF_VOLTAGE/HAL_ADC_CURRENT_RESISTOR/HAL_ADC_CURRENT_GAIN/HAL_ADC_SCALE_BIT)//A

//频率设置
#define HAL_SYSTEM_FREQ                         (168000.0f)             //kHz，系统时钟频率
#define HAL_PWM_CLK_FREQ                        (HAL_SYSTEM_FREQ)       //kHz，系统时钟频率
#define HAL_TIM_SWITCH_FREQ                     (10000.0f)              //kHz，用于换向时间计数的定时器频率

#define HAL_PWM_FREQ                            (20.0f)                                     //kHz，PWM载率
#define HAL_PWM_TIME                            (1.0f / HAL_PWM_FREQ / 1000.0f)             //s，PWM载率
#define HAL_CURRENT_LOOP_RATE                   (1.0f)                                      //电流周期倍率
#define HAL_CURRENT_LOOP_FREQ                   (HAL_PWM_FREQ / HAL_CURRENT_LOOP_RATE)      //kHz，电流环频率
#define HAL_CURRENT_LOOP_TIME                   (1.0f / HAL_CURRENT_LOOP_FREQ / 1000.0f)    //s，电流环周期

#define HAL_SLOW_TIMER_MS                       (0.5f)                  //ms，滴答定时器周期

//MCPWM设置
#define HAL_PWM_MAX_COUNTER_F                   (float)(HAL_PWM_CLK_FREQ / 2.0f / HAL_PWM_FREQ)
#define HAL_PWM_MAX_COUNTER_2                   (float)(HAL_PWM_CLK_FREQ / HAL_PWM_FREQ)
#define HAL_PWM_MAX_COUNTER                     (uint32_t)(HAL_PWM_CLK_FREQ / 2.0f / HAL_PWM_FREQ)

//MCPWM设置
#define HAL_PWM_DEADTIME_TIME                   (0.5f)                  //ADC采样时间
#define HAL_PWM_DEADTIME_DUTY                   (HAL_PWM_DEADTIME_TIME / (1000.0f / HAL_PWM_FREQ))
#define HAL_PWM_DEADTIME_VALUE                  (uint16_t)(2.0f * HAL_PWM_DEADTIME_DUTY * HAL_PWM_MAX_COUNTER_F)

//ADC采样时刻设置
#define HAL_ADC_SAMPLE_TIME                     (3.0f)                  //ADC采样时间
#define HAL_ADC_SAMPLE_DUTY                     (0.5f * HAL_ADC_SAMPLE_TIME / (1000.0f / HAL_PWM_FREQ))
#define HAL_ADC_SAMPLE_VALUE                    (uint32_t)(2.0f * HAL_ADC_SAMPLE_DUTY * HAL_PWM_MAX_COUNTER_F)

#endif /* MotorHal_cfg_H */
