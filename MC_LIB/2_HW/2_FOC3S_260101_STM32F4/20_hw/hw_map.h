/*
*     File Name :                        hw_map
*     Library/Module Name :              hw
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             外设、引脚映射
*
*     组织方式：
*       第 1 节  头文件包含
*       第 2 节  外设实例定义
*       第 3 节  DMA 通道定义
*       第 4 节  系统级（按键 / LED / 测试点 / 串口 / 串口 DMA）
*       第 5 节  电机控制（ADC / OPA / CMP / DAC / PWM / ADC-DMA）
*       第 6 节  LCD（SPI / 辅助 GPIO / SPI-DMA）
*/

#ifndef HW_MAP_H
#define HW_MAP_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_flash.h"
#include "stm32f4xx_flash_ramfunc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_wwdg.h"
#include "math_type.h"


/*-------------------------- 2. 外设实例定义 -----------------------------*/
/* ---- 2.1 系统级 ---- */

/* ---- 2.2 电机控制 ---- */
#define HW_MC_ADC                      ADC1
#define HW_MC_PWM                      TIM8
#define HW_MC_HTIM                     TIM2

/* ---- 2.3 LCD ---- */


/*-------------------------- 3. DMA 通道定义 -----------------------------*/
/* ---- 3.1 系统级：USART1 ---- */

/* ---- 3.2 电机控制：ADC1 规则组 ---- */

/* ---- 3.3 LCD：SPI3 ----
 * SPI3_TX 使用 DMA1_Ch2（与 ADC1 无冲突）
 * SPI3_RX 默认映射到 DMA1_Ch1，但该通道被 ADC1 规则组占用，
 *         需通过 SYSCFG 重映射到 DMA2_Ch1
 */


/*-------------------------- 4. 系统级引脚映射 ---------------------------*/
/* ---- 4.1 GPIO 输入 ---- */
#define HW_SYS_START_GPIO_Port          GPIOE                   /* 启动按键 */
#define HW_SYS_START_Pin                GPIO_Pin_2

#define HW_SYS_STOP_GPIO_Port           GPIOE                   /* 停止按键 */
#define HW_SYS_STOP_Pin                 GPIO_Pin_3

#define HW_SYS_RESET_GPIO_Port          GPIOE                   /* 故障恢复按键 */
#define HW_SYS_RESET_Pin                GPIO_Pin_4

/* ---- 4.2 GPIO 输出（LED / 测试点）---- */
#define HW_SYS_LED0_GPIO_Port           GPIOE                   /* 红色 LED */
#define HW_SYS_LED0_Pin                 GPIO_Pin_7

#define HW_SYS_LED1_GPIO_Port           GPIOE                   /* 黄色 LED */
#define HW_SYS_LED1_Pin                 GPIO_Pin_1

#define HW_SYS_RECOVER_GPIO_Port        GPIOF                   /* 绿色 LED */
#define HW_SYS_RECOVER_Pin              GPIO_Pin_10


/* ---- 4.3 USART1 引脚（含 RS485 方向控制）---- */


/*-------------------------- 5. 电机控制引脚映射 -------------------------*/
/* ---- 5.1 ADC 三相电流采样 ---- */
/* U 相电流：PA2 → ADC1_IN3 */
#define HW_MC_ADC_U_CURRENT_GPIO_Port       GPIOB
#define HW_MC_ADC_U_CURRENT_Pin             GPIO_Pin_0
#define HW_MC_ADC_U_CURRENT_Channel         ADC_Channel_8

/* V 相电流：PA6 → ADC2_IN3 */
#define HW_MC_ADC_V_CURRENT_GPIO_Port       GPIOA
#define HW_MC_ADC_V_CURRENT_Pin             GPIO_Pin_6
#define HW_MC_ADC_V_CURRENT_Channel         ADC_Channel_6

/* W 相电流：PB13 → ADC3_IN5 */
#define HW_MC_ADC_W_CURRENT_GPIO_Port       GPIOA
#define HW_MC_ADC_W_CURRENT_Pin             GPIO_Pin_3
#define HW_MC_ADC_W_CURRENT_Channel         ADC_Channel_3

/* ---- 5.2 ADC 系统采样（母线电压 + 外部温度）---- */
/* 母线电压：PC3 → ADC1_IN9 */
#define HW_MC_ADC_VBUS_GPIO_Port            GPIOB
#define HW_MC_ADC_VBUS_Pin                  GPIO_Pin_1
#define HW_MC_ADC_VBUS_Channel              ADC_Channel_9

/* 外部温度：PC2 → ADC1_IN8 */
#define HW_MC_ADC_TEMP_GPIO_Port            GPIOA
#define HW_MC_ADC_TEMP_Pin                  GPIO_Pin_0
#define HW_MC_ADC_TEMP_Channel              ADC_Channel_0

/* ---- 5.3 OPA 运算放大器 ----
 * OPA 输出通过外部走线送到主比较器 P 端
 * OPA 引脚仅需配置为模拟模式，通过 OPAMP_Cmd 使能
 */
/*-------------------------- 2. 宏定义 -----------------------------------*/


/* ---- 5.4 DAC 阈值输出 ---- */


/* ---- 5.5 CMP 过流保护 ---- */


/* ---- 5.6 PWM（TIM8 互补输出）---- */
#define HW_MC_PWM_UH_GPIO_Port              GPIOA                   /* U 相上桥 */
#define HW_MC_PWM_UH_Pin                    GPIO_Pin_8
#define HW_MC_PWM_UH_Pin_Source             GPIO_PinSource8

#define HW_MC_PWM_VH_GPIO_Port              GPIOA                   /* V 相上桥 */
#define HW_MC_PWM_VH_Pin                    GPIO_Pin_9
#define HW_MC_PWM_VH_Pin_Source             GPIO_PinSource9

#define HW_MC_PWM_WH_GPIO_Port              GPIOA                   /* W 相上桥 */
#define HW_MC_PWM_WH_Pin                    GPIO_Pin_10
#define HW_MC_PWM_WH_Pin_Source             GPIO_PinSource10

#define HW_MC_PWM_UL_GPIO_Port              GPIOB                   /* U 相下桥 */
#define HW_MC_PWM_UL_Pin                    GPIO_Pin_13
#define HW_MC_PWM_UL_Pin_Source             GPIO_PinSource13

#define HW_MC_PWM_VL_GPIO_Port              GPIOB                   /* V 相下桥 */
#define HW_MC_PWM_VL_Pin                    GPIO_Pin_14
#define HW_MC_PWM_VL_Pin_Source             GPIO_PinSource14

#define HW_MC_PWM_WL_GPIO_Port              GPIOB                   /* W 相下桥 */
#define HW_MC_PWM_WL_Pin                    GPIO_Pin_15
#define HW_MC_PWM_WL_Pin_Source             GPIO_PinSource15

/* TIM8_CH4 用于 ADC 触发（仅内部 OC4REF 信号，不输出到引脚）*/
#define HW_MC_PWM_TRIG_ADC_CHANNEL          TIM_CHANNEL_CH4


/*-------------------------- 6. LCD 引脚映射 -----------------------------*/



#endif /* HW_MAP_H */
