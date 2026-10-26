/**
 * @file    hw_para.h
 * @brief   硬件参数
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef HW_PARA_H
#define HW_PARA_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"

/* ======================== 2. Defines ====================== */

/* ---------------- 时钟配置 ---------------- */
/* 系统时钟 */
#define HW_CLK_CORE_FREQ                        (72000.0f)                              /* kHz，系统时钟频率 */
#define HW_CLK_PWM_FREQ                         (HW_CLK_CORE_FREQ)                      /* kHz，PWM 时钟频率 */
#define HW_CLK_HTIM_FREQ                        (HW_CLK_CORE_FREQ)                      /* kHz，过零点计数定时器时钟频率 */
#define HW_CLK_STIM_FREQ                        (HW_CLK_CORE_FREQ)                      /* kHz，换向计数定时器时钟频率 */

/* PWM 定时器 */
#define HW_PWM_PRESCALER                        (2.0f)                                  /* 分频系数 */
#define HW_PWM_PRE_FREQ                         (HW_CLK_PWM_FREQ/HW_PWM_PRESCALER)      /* kHz，PWM 计数器频率，36M */

#define HW_PWM_FREQ_1K                          (1.0f)                                  /* kHz，PWM 载频 */
#define HW_PWM_FREQ_2K                          (2.0f)                                  /* kHz，PWM 载频 */
#define HW_PWM_FREQ_4K                          (4.0f)                                  /* kHz，PWM 载频 */
#define HW_PWM_FREQ_8K                          (8.0f)                                  /* kHz，PWM 载频 */
#define HW_PWM_FREQ_10K                         (10.0f)                                 /* kHz，PWM 载频 */
#define HW_PWM_FREQ_12K                         (12.0f)                                 /* kHz，PWM 载频 */
#define HW_PWM_FREQ_16K                         (16.0f)                                 /* kHz，PWM 载频 */
#define HW_PWM_FREQ_20K                         (20.0f)                                 /* kHz，PWM 载频 */

#define HW_PWM_INIT_FREQ                        (HW_PWM_FREQ_1K)
#define HW_PWM_LOW_FREQ                         (HW_PWM_FREQ_1K)
#define HW_PWM_HIGH_FREQ                        (HW_PWM_FREQ_8K)

#define HW_PWM_INIT_VALUE                       (Q32U_)(HW_PWM_PRE_FREQ/HW_PWM_INIT_FREQ)
#define HW_PWM_LOW_VALUE                        (Q32U_)(HW_PWM_PRE_FREQ/HW_PWM_LOW_FREQ)
#define HW_PWM_HIGH_VALUE                       (Q32U_)(HW_PWM_PRE_FREQ/HW_PWM_HIGH_FREQ)

#define HW_PWM_DEADTIME_TIME                    (5.0f)                                  /* us，死区时间 */

/* ---------------- ADC 采样时刻设置 ---------------- */
#define HW_ADC_DELAY_TIME                       (15.0f)                                 /* us，米勒平台时间 */
#define HW_ADC_DELAY_VALUE                      (Q32U_)(HW_ADC_DELAY_TIME*HW_PWM_PRE_FREQ/1000.0f)

#define HW_ADC_SAMPLE_TIME                      (5.0f)                                  /* us，ADC 采样时间 */
#define HW_ADC_SAMPLE_VALUE                     (Q32U_)(HW_ADC_SAMPLE_TIME*HW_PWM_PRE_FREQ/1000.0f)

#define HW_ADC_SOLVE_TIME                       (15.0f)                                 /* us，换向判断时间 */
#define HW_ADC_SOLVE_VALUE                      (Q32U_)(HW_ADC_SOLVE_TIME*HW_PWM_PRE_FREQ/1000.0f)

#define HW_SWITCH_DELAY_MIN_VALUE               (Q32U_)(10.0f)                          /* 换向最小延迟计数值 */

/* ---------------- TIM 设置 ---------------- */
#define HW_HTIM_PRESCALER                       (72.0f)                                              /* 分频系数 */
#define HW_HTIM_FREQ                            (Q32U_)(1000.0f*HW_CLK_HTIM_FREQ/(HW_HTIM_PRESCALER)) /* Hz，HALL 换相时钟频率，1M */
#define HW_HTIM_SET_VALUE                       (0x0000FFFFU)

#define HW_STIM_PRESCALER                       (72.0f)                                              /* 分频系数 */
#define HW_STIM_FREQ                            (Q32U_)(1000.0f*HW_CLK_STIM_FREQ/(HW_STIM_PRESCALER)) /* Hz，SWITCH 换相时钟频率，1M */
#define HW_STIM_SET_VALUE                       (0x0000FFFFU)

#define HW_STICK_FREQ                           (1.0f)                                               /* kHz，慢速控制频率 */
#define HW_STICK_SET_VALUE                      (Q32U_)(HW_CLK_CORE_FREQ/HW_STICK_FREQ)              /* kHz，慢速控制计数值 */

/* ---------------- 硬件配置 ---------------- */
/* ADC 参数 */
#define HW_ADC_REF_VOLTAGE                      (3.3f)                  /* V，ADC 参考电平 */
#define HW_ADC_SCALE                            (4095.0f)               /* lsb，ADC 精度 */

/* 母线电压采样 */
#define HW_ADC_VOLTAGE_RESISTOR_UP              (780.0f)                /* 母线电压采样上分压电阻 */
#define HW_ADC_VOLTAGE_RESISTOR_DOWN            (3.9f)                  /* 母线电压采样下分压电阻 */
#define HW_ADC_VOLTAGE_COEFF                    ((HW_ADC_VOLTAGE_RESISTOR_UP+HW_ADC_VOLTAGE_RESISTOR_DOWN)/HW_ADC_VOLTAGE_RESISTOR_DOWN)
#define HW_ADC_VOLTAGE_MAX                      (HW_ADC_REF_VOLTAGE*HW_ADC_VOLTAGE_COEFF)    /* V，最大采样电压 */

/* 相电流采样 */
#define HW_ADC_CURRENT_OFFSET                   (0.55f)                 /* V，电流采样偏置电压 */
#define HW_ADC_CURRENT_GAIN                     (15.0f)                 /* 相电流采样放大倍数 */
#define HW_ADC_CURRENT_RESISTOR                 (0.005f)                /* Ω，相电流采样电阻 */
#define HW_ADC_CURRENT_COEFF                    (1.0f/(HW_ADC_CURRENT_RESISTOR*HW_ADC_CURRENT_GAIN))
#define HW_ADC_CURRENT_MAX                      (HW_ADC_REF_VOLTAGE*HW_ADC_CURRENT_COEFF)   /* A，最大采样电流 */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

#endif /* HW_PARA_H */