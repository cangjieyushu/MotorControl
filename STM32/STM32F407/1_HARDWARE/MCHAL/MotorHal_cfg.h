/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef MotorHal_cfg_H
#define MotorHal_cfg_H

#include <stdint.h>

//ADC设置
#define HAL_ADC_REF_VOLTAGE                     (5.0f)                  //V，ADC参考电平
#define HAL_ADC_SCALE_BIT                       (4095.0f)               //lsb，ADC精度

//母线电压采样
#define HAL_ADC_VOLTAGE_RESISTOR_UP             (29.4f)                 //母线电压采样上分压电阻
#define HAL_ADC_VOLTAGE_RESISTOR_DOWN           (3.0f)                  //母线电压采样下分压电阻
#define HAL_ADC_FULL_SCALE_VOLTAGE              (HAL_ADC_REF_VOLTAGE*(HAL_ADC_VOLTAGE_RESISTOR_UP+HAL_ADC_VOLTAGE_RESISTOR_DOWN)/HAL_ADC_VOLTAGE_RESISTOR_DOWN/HAL_ADC_SCALE_BIT)//V
//相电流采样

#define HAL_ADC_CURRENT_GAIN                    (10.0f)                 //相电流采样放大倍数
#define HAL_ADC_CURRENT_RESISTOR                (0.010f)                //Ω，相电流采样电阻
#define HAL_ADC_FULL_SCALE_CURRENT              (HAL_ADC_REF_VOLTAGE/HAL_ADC_CURRENT_RESISTOR/HAL_ADC_CURRENT_GAIN/HAL_ADC_SCALE_BIT)//A

//频率设置
#define HAL_SYSTEM_FREQ                         (160000.0f)             //kHz，系统时钟频率
#define HAL_STIM1_FREQ                          (10000000.0f)           //Hz，用于换向时间计数的定时器频率

#define HAL_PWM_FREQ                            (20.0f)                 //kHz，PWM载频
#define HAL_CURRENT_LOOP_FREQ                   (20.0f)                 //kHz，电流环频率
#define HAL_CURRENT_LOOP_TIME                   (0.001f / HAL_CURRENT_LOOP_FREQ)            //s，电流环周期

#define HAL_SLOW_TIMER_MS                       (0.5f)                  //s，滴答定时器周期

//MCPWM设置
#define HAL_MCPWM_MAX_COUNTER_F                 (float32)(HAL_SYSTEM_FREQ / 2.0f / HAL_PWM_FREQ)
#define HAL_M1PWM_MAX_COUNTER                   (uint32_t)(HAL_SYSTEM_FREQ / 2.0f / 2.0f / HAL_PWM_FREQ)
#define HAL_M2PWM_MAX_COUNTER                   (uint32_t)(HAL_SYSTEM_FREQ / 2.0f / 2.0f / HAL_PWM_FREQ)

//ADC采样时刻设置
#define HAL_MIN_ADCWINDOW_US                    (2.0f)                  //ADC采样时间
#define HAL_MIN_ADCWINDOW_DUTY                  (0.5f * HAL_MIN_ADCWINDOW_US * HAL_PWM_FREQ / 1000.0f)
#define HAL_MINTIMPWM_VALUE                     (uint32_t)(HAL_MIN_ADCWINDOW_DUTY * HAL_MCPWM_MAX_COUNTER_F)
#define HAL_TDG_OFFSET_VALUE                    (uint32_t)(HAL_MCPWM_MAX_COUNTER_F - HAL_MINTIMPWM_VALUE - 10.0f)
#define HAL_TDG_MOD_VALUE                       (uint32_t)(HAL_TDG_OFFSET_VALUE + 5U)

#endif /* MotorHal_cfg_H */
