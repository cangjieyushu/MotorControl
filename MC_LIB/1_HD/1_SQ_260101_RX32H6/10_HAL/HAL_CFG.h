/**************************************************************************************************
*     File Name :                        HAL_CFG.h
*     Library/Module Name :              HAL
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制硬件参数设置
**************************************************************************************************/


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


#ifndef HAL_CFG_H
#define HAL_CFG_H


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
#include "MATH.h"


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
#define HAL_ADC_DELAY_TIME                      (15.0f)                                 //us，米勒平台时间
#define HAL_ADC_DELAY_VALUE                     (Q32U_)(HAL_ADC_DELAY_TIME*HAL_PWM_PRE_FREQ/1000.0f)
#define HAL_ADC_SAMPLE_TIME                     (5.0f)                                  //us，ADC采样时间
#define HAL_ADC_SAMPLE_VALUE                    (Q32U_)(HAL_ADC_SAMPLE_TIME*HAL_PWM_PRE_FREQ/1000.0f)

#define HAL_ADC_SOLVE_TIME                      (10.0f)                                 //us，换向判断时间
#define HAL_ADC_SOLVE_VALUE                     (Q32U_)(HAL_ADC_SOLVE_TIME*HAL_PWM_PRE_FREQ/1000.0f)


//TIM设置
#define HAL_HALL_TIM_PRESCALER                  (144.0f)                                                                //分频系数
#define HAL_HALL_TIM_PRE_FREQ                   (Q32U_)(1000.0f*HAL_HALL_TIM_CLK_FREQ/(HAL_HALL_TIM_PRESCALER))         //Hz，HALL换相时钟频率，1M
#define HAL_HALL_TIM_MAX_CNT                    (0xFFFFFFFFU)

#define HAL_SWITCH_TIM_PRESCALER                (144.0f)                                                                //分频系数
#define HAL_SWITCH_TIM_PRE_FREQ                 (Q32U_)(1000.0f*HAL_SWITCH_TIM_CLK_FREQ/(HAL_SWITCH_TIM_PRESCALER))     //Hz，HALL换相时钟频率，1M

#define HAL_SWITCH_DELAY_MIN_TIME               (10.0f)                                                                 //us，TIM延迟最小时间
#define HAL_SWITCH_DELAY_MIN_VALUE              (Q32U_)(HAL_SWITCH_DELAY_MIN_TIME)

#define HAL_SLOW_TIM_FREQ                       (1.0f)                                                                  //kHz，慢速控制频率
#define HAL_SLOW_TIM_VALUE                      (Q32U_)(HAL_SYSTEM_CLK_FREQ/HAL_SLOW_TIM_FREQ)                          //kHz，慢速控制计数值


//ADC硬件参数设置
#define HAL_ADC_REF_VOLTAGE_V                   (3.3f)                  //V，ADC参考电平
#define HAL_ADC_SCALE_BIT                       (4095.0f)               //lsb，ADC精度

//母线电压采样
#define HAL_ADC_VOLTAGE_RESISTOR_UP             (10.0f)                 //母线电压采样上分压电阻
#define HAL_ADC_VOLTAGE_RESISTOR_DOWN           (0.47f)                 //母线电压采样下分压电阻
#define HAL_ADC_VOLTAGE_COEFF                   ((HAL_ADC_VOLTAGE_RESISTOR_UP+HAL_ADC_VOLTAGE_RESISTOR_DOWN)/HAL_ADC_VOLTAGE_RESISTOR_DOWN)
#define HAL_ADC_VOLTAGE_MAX                     (HAL_ADC_REF_VOLTAGE_V*HAL_ADC_VOLTAGE_COEFF)   //V，最大采样电压
#define HAL_ADC_VOLTAGE_SCALE                   (HAL_ADC_VOLTAGE_MAX/HAL_ADC_SCALE_BIT)         //V/lsb，电压刻度

//相电流采样
#define HAL_ADC_CURRENT_OFFSET                  (0.5f)                  //V，电流采样偏置电压
#define HAL_ADC_CURRENT_GAIN                    (8.0f)                  //相电流采样放大倍数
#define HAL_ADC_CURRENT_RESISTOR                (0.005f)                //Ω，相电流采样电阻
#define HAL_ADC_CURRENT_COEFF                   (1.0f/(HAL_ADC_CURRENT_RESISTOR*HAL_ADC_CURRENT_GAIN))
#define HAL_ADC_CURRENT_MAX                     (HAL_ADC_REF_VOLTAGE_V*HAL_ADC_CURRENT_COEFF)   //A，最大采样电流
#define HAL_ADC_CURRENT_SCALE                   (HAL_ADC_CURRENT_MAX/HAL_ADC_SCALE_BIT)         //A/lsb，电流刻度


//外设重定义
#define HAL_MOTOR_ADC               ADC1
#define HAL_MOTOR_OPA               OPAMP2
#define HAL_MOTOR_CMP               COMP2
#define HAL_MOTOR_PWM               TIM8
#define HAL_MOTOR_HALL_TIM          TIM2
#define HAL_MOTOR_SWITCH_TIM        TIM3

#define HAL_HMI_UART                UART1


//全局引脚定义
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

//ADC_SYSTYM
#define ADC_TEMP_GPIO_PORT          GPIOC
#define ADC_TEMP_PIN                GPIO_PIN_1
#define ADC_TEMP_Channel            ADC_CHANNEL_3

#define ADC_VR_GPIO_PORT            GPIOB
#define ADC_VR_PIN                  GPIO_PIN_5
#define ADC_VR_Channel              ADC_CHANNEL_7

#define ADC_VBUS_GPIO_PORT          GPIOD
#define ADC_VBUS_PIN                GPIO_PIN_5
#define ADC_VBUS_Channel            ADC_CHANNEL_14

#define ADC_VBG_Channel             ADC_CHANNEL_VBGINT


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


#endif /* HAL_CFG_H */
