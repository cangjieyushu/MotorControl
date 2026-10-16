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
#include "gd32e23x_adc.h"
#include "gd32e23x_crc.h"
#include "gd32e23x_dbg.h"
#include "gd32e23x_dma.h"
#include "gd32e23x_exti.h"
#include "gd32e23x_fmc.h"
#include "gd32e23x_gpio.h"
#include "gd32e23x_syscfg.h"
#include "gd32e23x_i2c.h"
#include "gd32e23x_fwdgt.h"
#include "gd32e23x_pmu.h"
#include "gd32e23x_rcu.h"
#include "gd32e23x_rtc.h"
#include "gd32e23x_spi.h"
#include "gd32e23x_timer.h"
#include "gd32e23x_usart.h"
#include "gd32e23x_wwdgt.h"
#include "gd32e23x_misc.h"
#include "gd32e23x_cmp.h"
#include "math_type.h"


/* ========================== 2. 外设实例定义 ========================== */
/* ---- 2.1 系统级 ---- */
#define HW_SYS_UART                     USART0

/* ---- 2.2 电机控制 ---- */
#define HW_MC_ADC                       ADC         /* 电机控制 ADC：相电流 / BEMF / 母线 / 温度采样 */
#define HW_MC_PWM                       TIMER0      /* 三相 PWM，互补输出 */
#define HW_MC_HTIM                      TIMER13     /* HALL 换相计时 */
#define HW_MC_STIM                      TIMER2      /* SWITCH 状态计时 */

/* ---- 2.3 LCD ---- */
#define HW_LCD_SPI                      SPI0


/* ========================== 3. DMA 通道定义 ========================== */
/* ---- 3.1 系统级：USART0 ---- */
#define HAL_SYS_USART_TX_DMA_CH         DMA_CH3
#define HAL_SYS_USART_RX_DMA_CH         DMA_CH4

/* ---- 3.2 电机控制：ADC 规则组 ---- */
#define HAL_MC_ADC_DMA_CH               DMA_CH0

/* ---- 3.3 LCD：SPI0 ---- */
/* LCD SPI TX 使用 DMA_CH2，与电机 ADC DMA_CH0 无冲突。 */
#define HAL_LCD_SPI_TX_DMA_CH           DMA_CH2


/* ========================== 4. 系统级引脚映射 ========================== */
/* ---- 4.1 GPIO 输入：按键 ---- */


/* ---- 4.2 GPIO 输出（LED / 测试点）---- */
/* 暂无宏定义，预留。 */


/* ---- 4.3 系统串口引脚（含 RS485 方向控制）---- */
#define HW_SYS_UART_TX_GPIO_Port        GPIOB
#define HW_SYS_UART_TX_Pin              GPIO_PIN_6

#define HW_SYS_UART_RX_GPIO_Port        GPIOB
#define HW_SYS_UART_RX_Pin              GPIO_PIN_7

#define HW_SYS_UART_TXEN_GPIO_Port      GPIOB
#define HW_SYS_UART_TXEN_Pin            GPIO_PIN_9


/* ========================== 5. 电机控制引脚映射 ========================== */
/* ---- 5.1 ADC 三相 BEMF / 电流采样 ---- */
/* U 相 BEMF：PA6 → ADC_CHANNEL_6 */
#define HW_MC_ADC_U_BEMF_GPIO_Port      GPIOA
#define HW_MC_ADC_U_BEMF_Pin            GPIO_PIN_6
#define HW_MC_ADC_U_BEMF_Channel        ADC_CHANNEL_6

/* V 相 BEMF：PA7 → ADC_CHANNEL_7 */
#define HW_MC_ADC_V_BEMF_GPIO_Port      GPIOA
#define HW_MC_ADC_V_BEMF_Pin            GPIO_PIN_7
#define HW_MC_ADC_V_BEMF_Channel        ADC_CHANNEL_7

/* W 相 BEMF：PB0 → ADC_CHANNEL_8 */
#define HW_MC_ADC_W_BEMF_GPIO_Port      GPIOB
#define HW_MC_ADC_W_BEMF_Pin            GPIO_PIN_0
#define HW_MC_ADC_W_BEMF_Channel        ADC_CHANNEL_8

/* 相电流：PA5 → ADC_CHANNEL_5 */
#define HW_MC_ADC_CURRENT_GPIO_Port     GPIOA
#define HW_MC_ADC_CURRENT_Pin           GPIO_PIN_5
#define HW_MC_ADC_CURRENT_Channel       ADC_CHANNEL_5


/* ---- 5.2 ADC 系统采样（母线电压 / 外部温度 / VR）---- */
/* 母线电压：PB1 → ADC_CHANNEL_9 */
#define HW_MC_ADC_VBUS_GPIO_Port        GPIOB
#define HW_MC_ADC_VBUS_Pin              GPIO_PIN_1
#define HW_MC_ADC_VBUS_Channel          ADC_CHANNEL_9

/* 外部温度：PA1 → ADC_CHANNEL_1 */
#define HW_MC_ADC_TEMP_GPIO_Port        GPIOA
#define HW_MC_ADC_TEMP_Pin              GPIO_PIN_1
#define HW_MC_ADC_TEMP_Channel          ADC_CHANNEL_1

/* ---- 5.3 OPA 运算放大器 ---- */


/* ---- 5.4 DAC 阈值输出 ---- */


/* ---- 5.5 CMP 过流保护 ---- */


/* ---- 5.6 PWM（TIMER0 互补输出）---- */
/* U 相上桥：PA8，TIMER0_CH0 */
#define HW_MC_PWM_UH_GPIO_Port          GPIOA
#define HW_MC_PWM_UH_Pin                GPIO_PIN_8
#define HW_MC_PWM_UH_CHANNEL            TIMER_CH_0

/* V 相上桥：PA9，TIMER0_CH1 */
#define HW_MC_PWM_VH_GPIO_Port          GPIOA
#define HW_MC_PWM_VH_Pin                GPIO_PIN_9
#define HW_MC_PWM_VH_CHANNEL            TIMER_CH_1

/* W 相上桥：PA10，TIMER0_CH2 */
#define HW_MC_PWM_WH_GPIO_Port          GPIOA
#define HW_MC_PWM_WH_Pin                GPIO_PIN_10
#define HW_MC_PWM_WH_CHANNEL            TIMER_CH_2

/* U 相下桥：PB13，TIMER0_CH0N */
#define HW_MC_PWM_UL_GPIO_Port          GPIOB
#define HW_MC_PWM_UL_Pin                GPIO_PIN_13
#define HW_MC_PWM_UL_CHANNEL            TIMER_CH_0

/* V 相下桥：PB14，TIMER0_CH1N */
#define HW_MC_PWM_VL_GPIO_Port          GPIOB
#define HW_MC_PWM_VL_Pin                GPIO_PIN_14
#define HW_MC_PWM_VL_CHANNEL            TIMER_CH_1

/* W 相下桥：PB15，TIMER0_CH2N */
#define HW_MC_PWM_WL_GPIO_Port          GPIOB
#define HW_MC_PWM_WL_Pin                GPIO_PIN_15
#define HW_MC_PWM_WL_CHANNEL            TIMER_CH_2

/* TIMER0_CH3 用于 ADC 触发，仅内部 OC4REF 信号，不输出到引脚 */
#define HW_MC_PWM_TRIG_ADC_CHANNEL      TIMER_CH_3

/* 刹车输入：PB12 */
#define HW_MC_PWM_BRK_GPIO_Port         GPIOB
#define HW_MC_PWM_BRK_Pin               GPIO_PIN_12


/* ========================== 6. LCD 引脚映射 ========================== */
/* ---- 6.1 SPI0 引脚 ---- */

/* ---- 6.2 辅助 GPIO ---- */


#endif /* HW_MAP_H */