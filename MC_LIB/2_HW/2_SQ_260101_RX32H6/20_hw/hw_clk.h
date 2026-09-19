/*
*     File Name :                        hw_clk.h
*     Library/Module Name :              hw
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             时钟配置
*/


/*命名规则
为了提高系统使用效率，电机控制的硬件参数单独使用一个头文件。OPA和CMP的使用具体需要看MCU是否支持相关的资源配置。
1、通常高级定时器只有16位，为了方便设计，只使用一个预分频参数。考虑到变频算法，最低按照1k开关频率，最高按照20k开关频率计算。
高级定时器的时钟频率一般需要在24M到64M。这样即可以保证1k下周期溢出计数器不会超过16位，也可以保证20k的开关频率下有千分之一的占空比精度。
2、方波算法需要设置三个开关频率，初始化开关频率，低速开关频率，高速开关频率。
初始化开关频率用于六脉冲定位等等状态。
定位完成后，进入低速开关频率，达到一定的占空比后，逐渐过渡到高速开关频率。
顺风启动后，直接进入高速开关频率，后续根据占空比自适应调节开关频率。
3、死驱时间的设置需要详细阅读芯片的手册，确认周期的配置逻辑。
4、ADC采样方式使用的是软件触发方式。每个开关周期进行多次采样。
第一次触发通过PWM通道4比较中断，通过HAL_ADC_DELAY_TIME配置PWM通道4比较中断的触发时刻，目的是为了避开米勒平台。
后续触发根据方波算法计算时间HAL_ADC_SOLVE_TIME以及ADC采样时刻HAL_ADC_SAMPLE_TIME，如果剩余的高电平时刻可以满足一次采样，就再触发一次ADC。
5、为了方便计算电机转速，即过零点之间的时间，以及延迟换向。通常HALL_TIM和SWITCH_TIM的频率都设置为1M，周期正好为1us。
检测到过零点后，使用SWITCH_TIM的通道1的比较中断进行延迟换向操作。

方波控制器配置外设：
系统时钟：               SYSTEM_CLK
PWM定时器：              PWM                PWM配置为上升计数模式，极性为先开后关
零点定时器：             HALL_TIM           HALL_TIM配置为上升计数，一直循环，不停止
换相定时器：             SWITCH_TIM         SWITCH_TIM配置为上升计数
ADC注入通道：            ADC_INJ            ADC的注入通道需要采样电机的三相端电压以及母线电流，先采UVW的端电压，再采母线电流
ADC规则通道：            ADC_REG            ADC的规则通道用来采样母线电压，温度等等
OPA:
CMP:

中断资源：
PWM刹车中断：                  硬件过流，通常为比较器输出的信号
PWM通道4比较中断：             用于触发第一次的ADC
ADC转换完成中断：              用于方波状态任务的执行
SWITCH_TIM通道1比较中断：      用于延迟换向
嘀嗒定时器中断：               配置为1ms周期，节约外设

*/


#ifndef HW_CLK_H
#define HW_CLK_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
//时钟配置
#define HAL_SYSTEM_CLK_FREQ                     (144000.0f)                             //kHz，系统时钟频率
#define HAL_PWM_CLK_FREQ                        (HAL_SYSTEM_CLK_FREQ)                   //kHz，PWM时钟频率
#define HAL_HALL_TIM_CLK_FREQ                   (HAL_SYSTEM_CLK_FREQ)                   //kHz，用过零点计数定时器时钟频率
#define HAL_SWITCH_TIM_CLK_FREQ                 (HAL_SYSTEM_CLK_FREQ)                   //kHz，用于换向计数定时器时钟频率


//PWM定时器
#define HAL_PWM_PRESCALER                       (3.0f)                                  //分频系数
#define HAL_PWM_PRE_FREQ                        (HAL_PWM_CLK_FREQ/HAL_PWM_PRESCALER)    //kHz，PWM计数器频率,48M

#define HAL_PWM_FREQ_1K                         (1.0f)                                  //kHz，PWM载频
#define HAL_PWM_FREQ_2K                         (2.0f)                                  //kHz，PWM载频
#define HAL_PWM_FREQ_4K                         (4.0f)                                  //kHz，PWM载频
#define HAL_PWM_FREQ_8K                         (8.0f)                                  //kHz，PWM载频
#define HAL_PWM_FREQ_10K                        (10.0f)                                 //kHz，PWM载频
#define HAL_PWM_FREQ_12K                        (12.0f)                                 //kHz，PWM载频
#define HAL_PWM_FREQ_16K                        (16.0f)                                 //kHz，PWM载频
#define HAL_PWM_FREQ_20K                        (20.0f)                                 //kHz，PWM载频

#define HAL_PWM_INIT_FREQ                       (HAL_PWM_FREQ_1K)
#define HAL_PWM_LOW_FREQ                        (HAL_PWM_FREQ_2K)
#define HAL_PWM_HIGH_FREQ                       (HAL_PWM_FREQ_10K)

#define HAL_PWM_INIT_VALUE                      (Q32U_)(HAL_PWM_PRE_FREQ/HAL_PWM_INIT_FREQ)
#define HAL_PWM_LOW_VALUE                       (Q32U_)(HAL_PWM_PRE_FREQ/HAL_PWM_LOW_FREQ)
#define HAL_PWM_HIGH_VALUE                      (Q32U_)(HAL_PWM_PRE_FREQ/HAL_PWM_HIGH_FREQ)

#define HAL_PWM_DEADTIME_TIME                   (2.0f)                                  //us，死区时间
#define HAL_PWM_DEADTIME_VALUE                  (Q32U_)(HAL_PWM_PRE_FREQ*HAL_PWM_DEADTIME_TIME/1000.0f)


//ADC采样时刻设置
#define HAL_ADC_DELAY_TIME                      (10.0f)                                 //us，米勒平台时间
#define HAL_ADC_DELAY_VALUE                     (Q32U_)(HAL_ADC_DELAY_TIME*HAL_PWM_PRE_FREQ/1000.0f)
#define HAL_ADC_SAMPLE_TIME                     (5.0f)                                  //us，ADC采样时间
#define HAL_ADC_SAMPLE_VALUE                    (Q32U_)(HAL_ADC_SAMPLE_TIME*HAL_PWM_PRE_FREQ/1000.0f)

#define HAL_ADC_SOLVE_TIME                      (10.0f)                                 //us，换向判断时间
#define HAL_ADC_SOLVE_VALUE                     (Q32U_)(HAL_ADC_SOLVE_TIME*HAL_PWM_PRE_FREQ/1000.0f)


//TIM设置
#define HAL_HALL_TIM_PRESCALER                  (144.0f)                                                                //分频系数
#define HAL_HALL_TIM_PRE_FREQ                   (Q32U_)(1000.0f*HAL_HALL_TIM_CLK_FREQ/(HAL_HALL_TIM_PRESCALER))         //Hz，HALL换相时钟频率，1M
#define HAL_HALL_TIM_MAX_CNT                    (0x00FFFFFFU)

#define HAL_SWITCH_TIM_PRESCALER                (144.0f)                                                                //分频系数
#define HAL_SWITCH_TIM_PRE_FREQ                 (Q32U_)(1000.0f*HAL_SWITCH_TIM_CLK_FREQ/(HAL_SWITCH_TIM_PRESCALER))     //Hz，HALL换相时钟频率，1M
#define HAL_SWITCH_TIM_MAX_CNT                  (0x0000FFFFU)

#define HAL_SWITCH_DELAY_MIN_TIME               (10.0f)                                                                 //us，TIM延迟最小时间
#define HAL_SWITCH_DELAY_MIN_VALUE              (Q32U_)(HAL_SWITCH_DELAY_MIN_TIME)

#define HAL_SLOW_TIM_FREQ                       (1.0f)                                                                  //kHz，慢速控制频率
#define HAL_SLOW_TIM_VALUE                      (Q32U_)(HAL_SYSTEM_CLK_FREQ/HAL_SLOW_TIM_FREQ)                          //kHz，慢速控制计数值


#endif /* HW_CLK_H */
