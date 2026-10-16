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

/* ---- 3.3 LCD：SPI0 ---- */
/* LCD SPI TX 使用 DMA_CH2，与电机 ADC DMA_CH0 无冲突。 */
#define HAL_LCD_SPI_TX_DMA_CH           DMA_CH2


/* ========================== 4. 系统级引脚映射 ========================== */
/* ---- 4.1 GPIO 输入：按键 ---- */
#define HW_SYS_BTN1_GPIO_Port           GPIOB
#define HW_SYS_BTN1_Pin                 GPIO_PIN_2

#define HW_SYS_BTN2_GPIO_Port           GPIOB
#define HW_SYS_BTN2_Pin                 GPIO_PIN_1

#define HW_SYS_BTN3_GPIO_Port           GPIOB
#define HW_SYS_BTN3_Pin                 GPIO_PIN_11

#define HW_SYS_BTN4_GPIO_Port           GPIOB
#define HW_SYS_BTN4_Pin                 GPIO_PIN_10


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


/* ---- 5.2 ADC 系统采样（母线电压 / 外部温度 / VR）---- */


/* ---- 5.3 OPA 运算放大器 ---- */


/* ---- 5.4 DAC 阈值输出 ---- */


/* ---- 5.5 CMP 过流保护 ---- */


/* ---- 5.6 PWM（TIMER0 互补输出）---- */


/* ========================== 6. LCD 引脚映射 ========================== */
/* ---- 6.1 SPI0 引脚 ---- */
#define HW_LCD_SPI_SCK_GPIO_Port        GPIOB
#define HW_LCD_SPI_SCK_PIN              GPIO_PIN_3

#define HW_LCD_SPI_MOSI_GPIO_Port       GPIOB
#define HW_LCD_SPI_MOSI_PIN             GPIO_PIN_5

/* ---- 6.2 辅助 GPIO ---- */
#define HW_LCD_SPI_RST_GPIO_Port        GPIOA
#define HW_LCD_SPI_RST_PIN              GPIO_PIN_10

#define HW_LCD_SPI_DC_GPIO_Port         GPIOA
#define HW_LCD_SPI_DC_PIN               GPIO_PIN_11

#define HW_LCD_SPI_CS_GPIO_Port         GPIOA
#define HW_LCD_SPI_CS_PIN               GPIO_PIN_12


#endif /* HW_MAP_H */