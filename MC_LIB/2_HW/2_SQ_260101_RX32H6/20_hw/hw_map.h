/*
 *  File Name        : hw_map.h
 *  Library/Module   : hw
 *  Author           : CJYS
 *  Create Date      : 2024/1/1
 *  Description      : 外设实例、引脚映射
 *
 *  组织方式：
 *    第 1 节  头文件包含
 *    第 2 节  外设实例定义
 *    第 3 节  DMA 通道定义
 *    第 4 节  系统级（按键 / LED / 测试点 / 串口 / 串口 DMA）
 *    第 5 节  电机控制（ADC / OPA / CMP / DAC / PWM / ADC-DMA）
 *    第 6 节  LCD（SPI / 辅助 GPIO / SPI-DMA）
 */

#ifndef HW_MAP_H
#define HW_MAP_H


/* ========================== 1. 头文件包含 ========================== */
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
#include "math_type.h"


/* ========================== 2. 外设实例定义 ========================== */
/* ---- 2.1 系统级 ---- */
/* 预留：系统级外设实例宏待补充。 */

/* ---- 2.2 电机控制 ---- */
#define HW_MC_ADC           ADC1      /* 电机控制 ADC：相电流 / BEMF / 母线 / 温度采样 */
#define HW_MC_PWM           TIM8      /* 三相 PWM，互补输出 */
#define HW_MC_HTIM          TIM2      /* HALL 换相计时 */
#define HW_MC_STIM          TIM3      /* SWITCH 状态计时 */
#define HW_MC_OPAMP         OPAMP2    /* 电流采样跟随器 */
#define HW_MC_CMP           COMP2     /* 过流 / 窗口比较器 */

/* ---- 2.3 LCD ---- */
/* 预留：LCD SPI 实例宏待补充。 */


/* ========================== 3. DMA 通道定义 ========================== */
/* ---- 3.1 系统级：USART1 ---- */
/* 预留：USART1 TX / RX DMA 通道宏待补充。 */

/* ---- 3.2 电机控制：ADC1 规则组 ---- */
/* 预留：ADC1 规则组 DMA 通道宏待补充。 */

/* ---- 3.3 LCD：SPI3 ---- */


/* ========================== 4. 系统级引脚映射 ========================== */
/* ---- 4.1 GPIO 输入 ---- */
/* 预留：按键 / 输入 GPIO 宏待补充。 */

/* ---- 4.2 GPIO 输出（LED / 测试点）---- */
/* 预留：LED / 测试点 GPIO 宏待补充。 */

/* ---- 4.3 USART1 引脚（含 RS485 方向控制）---- */
/* 预留：USART1 TX / RX / TXEN 宏待补充。 */


/* ========================== 5. 电机控制引脚映射 ========================== */
/* ---- 5.1 ADC 三相 BEMF / 电流采样 ---- */
/* U 相 BEMF：PC0 → ADC_CHANNEL_4 */
#define HW_MC_ADC_U_BEMF_GPIO_Port      GPIOC
#define HW_MC_ADC_U_BEMF_Pin            GPIO_PIN_0
#define HW_MC_ADC_U_BEMF_Channel        ADC_CHANNEL_4

/* V 相 BEMF：PB6 → ADC_CHANNEL_6 */
#define HW_MC_ADC_V_BEMF_GPIO_Port      GPIOB
#define HW_MC_ADC_V_BEMF_Pin            GPIO_PIN_6
#define HW_MC_ADC_V_BEMF_Channel        ADC_CHANNEL_6

/* W 相 BEMF：PB4 → ADC_CHANNEL_8 */
#define HW_MC_ADC_W_BEMF_GPIO_Port      GPIOB
#define HW_MC_ADC_W_BEMF_Pin            GPIO_PIN_4
#define HW_MC_ADC_W_BEMF_Channel        ADC_CHANNEL_8

/* 相电流：OPAMP2 输出 → ADC_CHANNEL_OPA2 */
#define HW_MC_ADC_CURRENT_Channel       ADC_CHANNEL_OPA2


/* ---- 5.2 ADC 系统采样（母线电压 / 外部温度 / VR）---- */
/* 母线电压：PD5 → ADC_CHANNEL_14 */
#define HW_MC_ADC_VBUS_GPIO_Port        GPIOD
#define HW_MC_ADC_VBUS_Pin              GPIO_PIN_5
#define HW_MC_ADC_VBUS_Channel          ADC_CHANNEL_14

/* 外部温度：PC1 → ADC_CHANNEL_3 */
#define HW_MC_ADC_TEMP_GPIO_Port        GPIOC
#define HW_MC_ADC_TEMP_Pin              GPIO_PIN_1
#define HW_MC_ADC_TEMP_Channel          ADC_CHANNEL_3

/* 外部 VR：PB5 → ADC_CHANNEL_7 */
#define HW_MC_ADC_VR_GPIO_Port          GPIOB
#define HW_MC_ADC_VR_Pin                GPIO_PIN_5
#define HW_MC_ADC_VR_Channel            ADC_CHANNEL_7


/* ---- 5.3 OPA 运算放大器 ---- */

/* OPAMP2 同相输入：PA6 */
#define HW_MC_OPAMP_VINP_GPIO_Port      GPIOA
#define HW_MC_OPAMP_VINP_Pin            GPIO_PIN_6

/* OPAMP2 反相输入：PA7 */
#define HW_MC_OPAMP_VINN_GPIO_Port      GPIOA
#define HW_MC_OPAMP_VINN_Pin            GPIO_PIN_7


/* ---- 5.4 DAC 阈值输出 ---- */


/* ---- 5.5 CMP 过流保护 ---- */

/* CMP 同相输入：PA6 */
#define HW_MC_CMP_VINP_GPIO_Port        GPIOA
#define HW_MC_CMP_VINP_Pin              GPIO_PIN_6

/* CMP 反相输入：PA7 */
#define HW_MC_CMP_VINN_GPIO_Port        GPIOA
#define HW_MC_CMP_VINN_Pin              GPIO_PIN_7


/* ---- 5.6 PWM（TIM8 互补输出）---- */
/* U 相上桥：PD3，TIM8_CH1 */
#define HW_MC_PWM_UH_GPIO_Port          GPIOD
#define HW_MC_PWM_UH_Pin                GPIO_PIN_3
#define HW_MC_PWM_UH_AF                 GPIO_AF1
#define HW_MC_PWM_UH_CHANNEL            TIM_CHANNEL_CH1

/* V 相上桥：PD1，TIM8_CH2 */
#define HW_MC_PWM_VH_GPIO_Port          GPIOD
#define HW_MC_PWM_VH_Pin                GPIO_PIN_1
#define HW_MC_PWM_VH_AF                 GPIO_AF1
#define HW_MC_PWM_VH_CHANNEL            TIM_CHANNEL_CH2

/* W 相上桥：PC7，TIM8_CH3 */
#define HW_MC_PWM_WH_GPIO_Port          GPIOC
#define HW_MC_PWM_WH_Pin                GPIO_PIN_7
#define HW_MC_PWM_WH_AF                 GPIO_AF1
#define HW_MC_PWM_WH_CHANNEL            TIM_CHANNEL_CH3

/* U 相下桥：PD2，TIM8_CH1N */
#define HW_MC_PWM_UL_GPIO_Port          GPIOD
#define HW_MC_PWM_UL_Pin                GPIO_PIN_2
#define HW_MC_PWM_UL_AF                 GPIO_AF1
#define HW_MC_PWM_UL_CHANNEL            TIM_CHANNEL_CH1N

/* V 相下桥：PD0，TIM8_CH2N */
#define HW_MC_PWM_VL_GPIO_Port          GPIOD
#define HW_MC_PWM_VL_Pin                GPIO_PIN_0
#define HW_MC_PWM_VL_AF                 GPIO_AF1
#define HW_MC_PWM_VL_CHANNEL            TIM_CHANNEL_CH2N

/* W 相下桥：PC6，TIM8_CH3N */
#define HW_MC_PWM_WL_GPIO_Port          GPIOC
#define HW_MC_PWM_WL_Pin                GPIO_PIN_6
#define HW_MC_PWM_WL_AF                 GPIO_AF1
#define HW_MC_PWM_WL_CHANNEL            TIM_CHANNEL_CH3N

/* TIM8_CH4 用于 ADC 触发，仅内部 OC4REF 信号，不输出到引脚 */
#define HW_MC_PWM_TRIG_ADC_CHANNEL      TIM_CHANNEL_CH4


/* ========================== 6. LCD 引脚映射 ========================== */
/* ---- 6.1 SPI3 引脚 ---- */
/* 预留：LCD SPI3 引脚宏待补充。 */

/* ---- 6.2 辅助 GPIO ---- */
/* 预留：LCD 辅助 GPIO 宏待补充。 */


#endif /* HW_MAP_H */
