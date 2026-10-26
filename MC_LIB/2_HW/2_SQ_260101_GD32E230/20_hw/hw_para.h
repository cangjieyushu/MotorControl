/**
 * @file    hw_para.h
 * @brief   硬件参数
 * @author  CJYS
 * @date    2024/1/1
 */

/* 命名规则
 * 为了提高系统使用效率，电机控制的硬件参数单独使用一个头文件。OPA 和 CMP 的使用具体需要看 MCU 是否支持相关的资源配置。
 * 1、通常高级定时器只有 16 位，为了方便设计，只使用一个预分频参数。考虑到变频算法，最低按照 1k 开关频率，最高按照 20k 开关频率计算。
 *    高级定时器的时钟频率一般需要在 24M 到 64M。这样即可以保证 1k 下周期溢出计数器不会超过 16 位，也可以保证 20k 的开关频率下有千分之一的占空比精度。
 * 2、方波算法需要设置三个开关频率：初始化开关频率、低速开关频率、高速开关频率。
 *    初始化开关频率用于六脉冲定位等等状态。
 *    定位完成后，进入低速开关频率，达到一定的占空比后，逐渐过渡到高速开关频率。
 *    顺风启动后，直接进入高速开关频率，后续根据占空比自适应调节开关频率。
 * 3、死区时间的设置需要详细阅读芯片的手册，确认周期的配置逻辑。
 * 4、ADC 采样方式使用的是软件触发方式。每个开关周期进行多次采样。
 *    第一次触发通过 PWM 通道 4 比较中断，通过 HW_ADC_DELAY_TIME 配置 PWM 通道 4 比较中断的触发时刻，目的是为了避开米勒平台。
 *    后续触发根据方波算法计算时间 HW_ADC_SOLVE_TIME 以及 ADC 采样时刻 HW_ADC_SAMPLE_TIME，如果剩余的高电平时刻可以满足一次采样，就再触发一次 ADC。
 * 5、为了方便计算电机转速，即过零点之间的时间，以及延迟换向。通常 HALL_TIM 和 SWITCH_TIM 的频率都设置为 1M，周期正好为 1us。
 *    检测到过零点后，使用 SWITCH_TIM 的通道 1 的比较中断进行延迟换向操作。
 *
 * 方波控制器配置外设：
 *     系统时钟：      SYSTEM_CLK
 *     PWM 定时器：    PWM          上升计数模式，极性为先开后关
 *     零点定时器：    HALL_TIM     上升计数，一直循环，不停止
 *     换相定时器：    SWITCH_TIM   上升计数
 *     ADC 注入通道：  ADC_INJ      采样电机三相端电压及母线电流，先采 UVW 端电压，再采母线电流
 *     ADC 规则通道：  ADC_REG      采样母线电压、温度等
 *     OPA：（本芯片不支持）
 *     CMP：（本板未使用）
 *
 * 中断资源：
 *     PWM 刹车中断：              硬件过流，通常为比较器输出信号
 *     PWM 通道 4 比较中断：       触发第一次 ADC
 *     ADC 转换完成中断：          方波状态任务执行
 *     SWITCH_TIM 通道 1 比较中断：延迟换向
 *     嘀嗒定时器中断：            1ms 周期，节约外设
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

#define HW_PWM_INIT_FREQ                        (HW_PWM_FREQ_1K)                        /* kHz，初始化开关频率 */
#define HW_PWM_LOW_FREQ                         (HW_PWM_FREQ_1K)                        /* kHz，低速开关频率 */
#define HW_PWM_HIGH_FREQ                        (HW_PWM_FREQ_8K)                        /* kHz，高速开关频率 */

#define HW_PWM_INIT_VALUE                       (Q32U_)(HW_PWM_PRE_FREQ/HW_PWM_INIT_FREQ)
#define HW_PWM_LOW_VALUE                        (Q32U_)(HW_PWM_PRE_FREQ/HW_PWM_LOW_FREQ)
#define HW_PWM_HIGH_VALUE                       (Q32U_)(HW_PWM_PRE_FREQ/HW_PWM_HIGH_FREQ)

#define HW_PWM_DEADTIME_TIME                    (5.0f)                                  /* us，死区时间 */

/* ---------------- ADC 采样时刻设置 ---------------- */
#define HW_ADC_DELAY_TIME                       (15.0f)                                 /* us，米勒平台时间（第一次触发避开） */
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