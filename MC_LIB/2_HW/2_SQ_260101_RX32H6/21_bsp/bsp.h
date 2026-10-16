/*
*     File Name :                        bsp
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             BSP层接口头文件
*/


#ifndef BSP_H
#define BSP_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
/* 第一类：系统级 */
#include "bsp_sys.h"

/* 第二类：电机控制 */
#include "bsp_mc.h"

/* 第三类：LCD 通讯 */
#include "bsp_lcd.h"


#endif /* BSP_H */


/*
bsp/
│
├── bsp.h                         # BSP 层总入口
│
├── 【第一类】系统级
│   ├── bsp_sys.h / .c            # 汇总：BSP_SYS_Init()
│   ├── bsp_sys_clk.h / .c        # 系统时钟
│   ├── bsp_sys_gpio.h / .c       # 按键/LED/测试点/RS485_EN
│   ├── bsp_sys_isr.h / .c        # NVIC 优先级
│   ├── bsp_sys_uart.h / .c       # 上位机串口
│   └── bsp_sys_dma.h / .c        # UART 的 DMA 收发
│
├── 【第二类】电机控制
│   ├── bsp_mc.h / .c             # 汇总：BSP_MC_Init()
│   ├── bsp_mc_gpio.h / .c        # 电机相关引脚复用
│   ├── bsp_mc_adc.h / .c         # ADC 规则组 + 注入组 + DMA
│   ├── bsp_mc_dma.h / .c         # ADC 规则组 DMA
│   ├── bsp_mc_pwm.h / .c         # TIM8 三相互补 PWM
│   ├── bsp_mc_tim.h / .c         # TIM2 HALL 计时
│   ├── bsp_mc_cmp.h / .c         # CMP 窗口比较器
│   ├── bsp_mc_dac.h / .c         # DAC 阈值输出
│   └── bsp_mc_opamp.h / .c       # OPA 跟随器
│
└── 【第三类】LCD
    ├── bsp_lcd.h / .c            # 汇总：BSP_LCD_Init()
    ├── bsp_lcd_gpio.h / .c       # LCD 引脚复用
    ├── bsp_lcd_spi.h / .c        # SPI 外设配置
    └── bsp_lcd_dma.h / .c        # SPI 的 DMA 收发
*/
