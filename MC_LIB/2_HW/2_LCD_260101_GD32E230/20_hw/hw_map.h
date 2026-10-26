/**
 * @file    hw_map.h
 * @brief   外设、引脚映射
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef HW_MAP_H
#define HW_MAP_H

/* ======================== 1. Includes ===================== */
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

/* ======================== 2. Defines ====================== */

/* ---------------- 2.1 外设实例定义 ---------------- */

/* ---- 系统级 ---- */
#define HW_SYS_UART                     USART0                  /* 上位机通讯串口 */

/* ---- 电机控制 ---- */
#define HW_MC_ADC                       ADC                     /* 电机控制 ADC：相电流 / BEMF / 母线 / 温度采样 */
#define HW_MC_PWM                       TIMER0                  /* 三相 PWM，互补输出 */
#define HW_MC_HTIM                      TIMER13                 /* HALL 换相计时 */
#define HW_MC_STIM                      TIMER2                  /* SWITCH 状态计时 */

/* ---- LCD ---- */
#define HW_LCD_SPI                      SPI0                    /* LCD SPI 通讯 */


/* ---------------- 2.2 DMA 通道定义 ---------------- */

/* ---- 系统级：USART0 ---- */
#define HW_SYS_USART_TX_DMA_CH         DMA_CH3                 /* USART0_TX */
#define HW_SYS_USART_RX_DMA_CH         DMA_CH4                 /* USART0_RX */

/* ---- 电机控制：ADC 规则组 ---- */
/* （GD32E230 当前未配置 ADC 规则组 DMA，通道宏留空） */

/* ---- LCD：SPI0 ----
 * LCD SPI TX 使用 DMA_CH2，与电机 ADC DMA_CH0 无冲突。
 */
#define HW_LCD_SPI_TX_DMA_CH           DMA_CH2                 /* SPI0_TX */


/* ---------------- 2.3 系统级引脚映射 ---------------- */

/* ---- GPIO 输入 ---- */
#define HW_SYS_BTN1_GPIO_Port           GPIOB                   /* 按键 1 */
#define HW_SYS_BTN1_Pin                 GPIO_PIN_2

#define HW_SYS_BTN2_GPIO_Port           GPIOB                   /* 按键 2 */
#define HW_SYS_BTN2_Pin                 GPIO_PIN_1

#define HW_SYS_BTN3_GPIO_Port           GPIOB                   /* 按键 3 */
#define HW_SYS_BTN3_Pin                 GPIO_PIN_11

#define HW_SYS_BTN4_GPIO_Port           GPIOB                   /* 按键 4 */
#define HW_SYS_BTN4_Pin                 GPIO_PIN_10

/* ---- GPIO 输出（LED / 测试点） ---- */
/* （GD32E230 当前暂无宏定义，预留） */

/* ---- 系统串口引脚（含 RS485 方向控制） ---- */
#define HW_SYS_UART_TX_GPIO_Port        GPIOB                   /* USART0_TX */
#define HW_SYS_UART_TX_Pin              GPIO_PIN_6

#define HW_SYS_UART_RX_GPIO_Port        GPIOB                   /* USART0_RX */
#define HW_SYS_UART_RX_Pin              GPIO_PIN_7

#define HW_SYS_UART_TXEN_GPIO_Port      GPIOB                   /* RS485 方向控制 */
#define HW_SYS_UART_TXEN_Pin            GPIO_PIN_9


/* ---------------- 2.4 电机控制引脚映射 ---------------- */

/* ---- ADC 三相电流采样 ---- */
/* （GD32E230 当前未定义，留空） */

/* ---- ADC 系统采样（母线电压 / 外部温度 / VR） ---- */
/* （GD32E230 当前未定义，留空） */

/* ---- OPA 运算放大器 ---- */
/* （GD32E230 不支持 OPA，留空） */

/* ---- DAC 阈值输出 ---- */
/* （GD32E230 不支持 DAC，留空） */

/* ---- CMP 过流保护 ---- */
/* （GD32E230 支持 CMP，具体引脚未定义，留空） */

/* ---- PWM（TIMER0 互补输出） ---- */
/* （GD32E230 当前未定义，留空） */


/* ---------------- 2.5 LCD 引脚映射 ---------------- */

/* ---- SPI0 引脚 ---- */
#define HW_LCD_SPI_SCK_GPIO_Port        GPIOB                   /* SPI0_SCK */
#define HW_LCD_SPI_SCK_PIN              GPIO_PIN_3

#define HW_LCD_SPI_MOSI_GPIO_Port       GPIOB                   /* SPI0_MOSI */
#define HW_LCD_SPI_MOSI_PIN             GPIO_PIN_5

/* ---- 辅助 GPIO ---- */
#define HW_LCD_SPI_RST_GPIO_Port        GPIOA                   /* LCD 复位 */
#define HW_LCD_SPI_RST_PIN              GPIO_PIN_10

#define HW_LCD_SPI_DC_GPIO_Port         GPIOA                   /* 数据/命令控制 */
#define HW_LCD_SPI_DC_PIN               GPIO_PIN_11

#define HW_LCD_SPI_CS_GPIO_Port         GPIOA                   /* 片选 */
#define HW_LCD_SPI_CS_PIN               GPIO_PIN_12


/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

#endif /* HW_MAP_H */