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
#include "stm32f30x_adc.h"
#include "stm32f30x_can.h"
#include "stm32f30x_crc.h"
#include "stm32f30x_comp.h"
#include "stm32f30x_dac.h"
#include "stm32f30x_dbgmcu.h"
#include "stm32f30x_dma.h"
#include "stm32f30x_exti.h"
#include "stm32f30x_flash.h"
#include "stm32f30x_fmc.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_hrtim.h"
#include "stm32f30x_syscfg.h"
#include "stm32f30x_i2c.h"
#include "stm32f30x_iwdg.h"
#include "stm32f30x_opamp.h"
#include "stm32f30x_pwr.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_rtc.h"
#include "stm32f30x_spi.h"
#include "stm32f30x_tim.h"
#include "stm32f30x_usart.h"
#include "stm32f30x_wwdg.h"
#include "stm32f30x_misc.h"
#include "math_type.h"


/*-------------------------- 2. 外设实例定义 -----------------------------*/
/* ---- 2.1 系统级 ---- */
#define HW_SYS_UART                     USART1                  /* 上位机通讯串口 */

/* ---- 2.2 电机控制 ---- */
#define HW_MC_ADC1                      ADC1                    /* U 相电流 */
#define HW_MC_ADC2                      ADC2                    /* V 相电流 */
#define HW_MC_ADC3                      ADC3                    /* W 相电流 */
#define HW_MC_PWM                       TIM8                    /* 三相 PWM */
#define HW_MC_HTIM                      TIM2                    /* HALL 计时 */

#define HW_MC_DAC                       DAC1                    /* CMP 窗口阈值 */
#define HW_MC_DAC_VH_CHANNEL            DAC_Channel_1           /* 窗口上限 */
#define HW_MC_DAC_VL_CHANNEL            DAC_Channel_2           /* 窗口下限 */

#define HW_MC_OPAMP1                    OPAMP_Selection_OPAMP1  /* 电流采样跟随器 1 */
#define HW_MC_OPAMP2                    OPAMP_Selection_OPAMP2  /* 电流采样跟随器 2 */
#define HW_MC_OPAMP3                    OPAMP_Selection_OPAMP3  /* 电流采样跟随器 3 */

/* ---- 2.3 LCD ---- */
#define HW_LCD_SPI                      SPI3                    /* LCD SPI 通讯 */


/*-------------------------- 3. DMA 通道定义 -----------------------------*/
/* ---- 3.1 系统级：USART1 ---- */
#define HW_SYS_UART_TX_DMA_CH           DMA1_Channel4           /* USART1_TX */
#define HW_SYS_UART_RX_DMA_CH           DMA1_Channel5           /* USART1_RX */

#define HW_SYS_UART_TX_DMA_TC_FLAG      DMA1_FLAG_TC4
#define HW_SYS_UART_TX_DMA_GL_FLAG      DMA1_FLAG_GL4
#define HW_SYS_UART_RX_DMA_TC_FLAG      DMA1_FLAG_TC5
#define HW_SYS_UART_RX_DMA_GL_FLAG      DMA1_FLAG_GL5

/* ---- 3.2 电机控制：ADC1 规则组 ---- */
#define HW_MC_ADC_DMA_CHANNEL           DMA1_Channel1           /* ADC1_DR → 系统缓冲区 */

/* ---- 3.3 LCD：SPI3 ----
 * SPI3_TX 使用 DMA1_Ch2（与 ADC1 无冲突）
 * SPI3_RX 默认映射到 DMA1_Ch1，但该通道被 ADC1 规则组占用，
 *         需通过 SYSCFG 重映射到 DMA2_Ch1
 */
#define HW_LCD_SPI_TX_DMA_CH            DMA1_Channel2           /* SPI3_TX */
#define HW_LCD_SPI_TX_DMA_TC_FLAG       DMA1_FLAG_TC2
#define HW_LCD_SPI_TX_DMA_GL_FLAG       DMA1_FLAG_GL2

#define HW_LCD_SPI_RX_DMA_CH            DMA2_Channel1           /* SPI3_RX（重映射）*/
#define HW_LCD_SPI_RX_DMA_TC_FLAG       DMA2_FLAG_TC1
#define HW_LCD_SPI_RX_DMA_GL_FLAG       DMA2_FLAG_GL1


/*-------------------------- 4. 系统级引脚映射 ---------------------------*/
/* ---- 4.1 GPIO 输入 ---- */
#define HW_SYS_START_GPIO_Port          GPIOC                   /* 启动按键 */
#define HW_SYS_START_Pin                GPIO_Pin_9
#define HW_SYS_START_Pin_Source         GPIO_PinSource9

#define HW_SYS_STOP_GPIO_Port           GPIOA                   /* 停止按键 */
#define HW_SYS_STOP_Pin                 GPIO_Pin_8
#define HW_SYS_STOP_Pin_Source          GPIO_PinSource8

/* ---- 4.2 GPIO 输出（LED / 测试点）---- */
#define HW_SYS_RED_GPIO_Port            GPIOB                   /* 红色 LED */
#define HW_SYS_RED_Pin                  GPIO_Pin_7

#define HW_SYS_YEW_GPIO_Port            GPIOB                   /* 黄色 LED */
#define HW_SYS_YEW_Pin                  GPIO_Pin_8

#define HW_SYS_GRE_GPIO_Port            GPIOB                   /* 绿色 LED */
#define HW_SYS_GRE_Pin                  GPIO_Pin_9

#define HW_SYS_TEST1_GPIO_Port          GPIOC                   /* 测试点 1 */
#define HW_SYS_TEST1_Pin                GPIO_Pin_0

#define HW_SYS_TEST2_GPIO_Port          GPIOC                   /* 测试点 2 */
#define HW_SYS_TEST2_Pin                GPIO_Pin_1

/* ---- 4.3 USART1 引脚（含 RS485 方向控制）---- */
#define HW_SYS_UART_TX_Port             GPIOA                   /* USART1_TX */
#define HW_SYS_UART_TX_Pin              GPIO_Pin_9
#define HW_SYS_UART_TX_Pin_Source       GPIO_PinSource9

#define HW_SYS_UART_RX_Port             GPIOA                   /* USART1_RX */
#define HW_SYS_UART_RX_Pin              GPIO_Pin_10
#define HW_SYS_UART_RX_Pin_Source       GPIO_PinSource10

#define HW_SYS_UART_EN_Port             GPIOA                   /* RS485 方向控制 */
#define HW_SYS_UART_EN_Pin              GPIO_Pin_11


/*-------------------------- 5. 电机控制引脚映射 -------------------------*/
/* ---- 5.1 ADC 三相电流采样 ---- */
/* U 相电流：PA2 → ADC1_IN3 */
#define HW_MC_ADC_U_CURRENT_GPIO_Port       GPIOA
#define HW_MC_ADC_U_CURRENT_Pin             GPIO_Pin_2
#define HW_MC_ADC_U_CURRENT_Pin_Source      GPIO_PinSource2
#define HW_MC_ADC_U_CURRENT_Channel         ADC_Channel_3
#define HW_MC_ADC_U_CURRENT_ADC             HW_MC_ADC1

/* V 相电流：PA6 → ADC2_IN3 */
#define HW_MC_ADC_V_CURRENT_GPIO_Port       GPIOA
#define HW_MC_ADC_V_CURRENT_Pin             GPIO_Pin_6
#define HW_MC_ADC_V_CURRENT_Pin_Source      GPIO_PinSource6
#define HW_MC_ADC_V_CURRENT_Channel         ADC_Channel_3
#define HW_MC_ADC_V_CURRENT_ADC             HW_MC_ADC2

/* W 相电流：PB13 → ADC3_IN5 */
#define HW_MC_ADC_W_CURRENT_GPIO_Port       GPIOB
#define HW_MC_ADC_W_CURRENT_Pin             GPIO_Pin_13
#define HW_MC_ADC_W_CURRENT_Pin_Source      GPIO_PinSource13
#define HW_MC_ADC_W_CURRENT_Channel         ADC_Channel_5
#define HW_MC_ADC_W_CURRENT_ADC             HW_MC_ADC3

/* ---- 5.2 ADC 系统采样（母线电压 + 外部温度）---- */
/* 母线电压：PC3 → ADC1_IN9 */
#define HW_MC_ADC_VBUS_GPIO_Port            GPIOC
#define HW_MC_ADC_VBUS_Pin                  GPIO_Pin_3
#define HW_MC_ADC_VBUS_Pin_Source           GPIO_PinSource3
#define HW_MC_ADC_VBUS_Channel              ADC_Channel_9
#define HW_MC_ADC_VBUS_ADC                  HW_MC_ADC1

/* 外部温度：PC2 → ADC1_IN8 */
#define HW_MC_ADC_TEMP_GPIO_Port            GPIOC
#define HW_MC_ADC_TEMP_Pin                  GPIO_Pin_2
#define HW_MC_ADC_TEMP_Pin_Source           GPIO_PinSource2
#define HW_MC_ADC_TEMP_Channel              ADC_Channel_8
#define HW_MC_ADC_TEMP_ADC                  HW_MC_ADC1

/* ---- 5.3 OPA 运算放大器 ----
 * OPA 输出通过外部走线送到主比较器 P 端
 * OPA 引脚仅需配置为模拟模式，通过 OPAMP_Cmd 使能
 */
/*-------------------------- 2. 宏定义 -----------------------------------*/
/* OPA 工作模式 */
#define HW_MC_OPAMP_MODE_FOLLOWER       0U    /* 跟随器（增益 1）*/
#define HW_MC_OPAMP_MODE_PGA            1U    /* PGA（增益 2/4/8/16）*/

/* 各 OPA 的工作模式 */
#define HW_MC_OPAMP1_MODE               HW_MC_OPAMP_MODE_PGA
#define HW_MC_OPAMP2_MODE               HW_MC_OPAMP_MODE_PGA
#define HW_MC_OPAMP3_MODE               HW_MC_OPAMP_MODE_PGA

/* 各 OPA 的 PGA 增益 */
#define HW_MC_OPAMP1_GAIN               OPAMP_OPAMP_PGAGain_8
#define HW_MC_OPAMP2_GAIN               OPAMP_OPAMP_PGAGain_8
#define HW_MC_OPAMP3_GAIN               OPAMP_OPAMP_PGAGain_8

/* 各 OPA 的 PGA 连接（P 端与 N 端的内部电阻网络接法）*/
#define HW_MC_OPAMP1_PGA_CONNECT        OPAMP_PGAConnect_IO2
#define HW_MC_OPAMP2_PGA_CONNECT        OPAMP_PGAConnect_IO2
#define HW_MC_OPAMP3_PGA_CONNECT        OPAMP_PGAConnect_IO2

/* OPA 输出引脚 */
#define HW_MC_OPAMP1_OUT_GPIO_Port          GPIOA                   /* OPA1_VOUT */
#define HW_MC_OPAMP1_OUT_Pin                GPIO_Pin_2              /* = PA2 */

#define HW_MC_OPAMP2_OUT_GPIO_Port          GPIOC                   /* OPA2_VOUT */
#define HW_MC_OPAMP2_OUT_Pin                GPIO_Pin_5              /* = PC5 */

#define HW_MC_OPAMP3_OUT_GPIO_Port          GPIOB                   /* OPA3_VOUT */
#define HW_MC_OPAMP3_OUT_Pin                GPIO_Pin_1              /* = PB1 */

/* OPA 同相输入引脚（PGA 模式或外部输入时使用）*/
#define HW_MC_OPAMP1_VINP_GPIO_Port         GPIOA                   /* OPAMP1 IO3 */
#define HW_MC_OPAMP1_VINP_Pin               GPIO_Pin_3              /* = PA3 */
#define HW_MC_OPAMP1_VINP_IO                OPAMP_NonInvertingInput_IO3

#define HW_MC_OPAMP2_VINP_GPIO_Port         GPIOB                   /* OPAMP2 IO3 */
#define HW_MC_OPAMP2_VINP_Pin               GPIO_Pin_0              /* = PB0 */
#define HW_MC_OPAMP2_VINP_IO                OPAMP_NonInvertingInput_IO3

#define HW_MC_OPAMP3_VINP_GPIO_Port         GPIOA                   /* OPAMP3 IO3 */
#define HW_MC_OPAMP3_VINP_Pin               GPIO_Pin_1              /* = PA1 */
#define HW_MC_OPAMP3_VINP_IO                OPAMP_NonInvertingInput_IO3

/* ---- 5.4 DAC 阈值输出 ----
 * DAC1_OUT1(PA4) 作窗口上限，DAC1_OUT2(PA5) 作窗口下限
 * 输出通过内部通道直接送 CMP 负端，无需外部走线
 */
#define HW_MC_DAC_VH_GPIO_Port              GPIOA
#define HW_MC_DAC_VH_Pin                    GPIO_Pin_4              /* DAC1_OUT1 */
#define HW_MC_DAC_VH_Pin_Source             GPIO_PinSource4

#define HW_MC_DAC_VL_GPIO_Port              GPIOA
#define HW_MC_DAC_VL_Pin                    GPIO_Pin_5              /* DAC1_OUT2 */
#define HW_MC_DAC_VL_Pin_Source             GPIO_PinSource5

/* ---- 5.5 CMP 过流保护 ----
 * 三组窗口比较器：CMP1+CMP2 / CMP3+CMP4 / CMP5+CMP6
 * 主比较器（1/3/5）非反相；从比较器（2/4/6）反相
 * 从比较器 P 端由 COMP_WindowCmd() 自动共用主比较器 P 端
 * 输出统一接 TIM8_BKIN 硬件刹车
 */

/* 组 1：主 CMP1，P 端 = PA1 */
#define HW_MC_OCP_COMP1                     COMP_Selection_COMP1
#define HW_MC_OCP_COMP1_INVERT              COMP_InvertingInput_DAC1OUT1
#define HW_MC_OCP_COMP1_NONINVERT           COMP_NonInvertingInput_IO1
#define HW_MC_OCP_COMP1_OUTPUT              COMP_Output_TIM8BKIN
#define HW_MC_OCP_COMP1_OUTPUTPOL           COMP_OutputPol_NonInverted
#define HW_MC_OCP_COMP1_GPIO_Port           GPIOA
#define HW_MC_OCP_COMP1_Pin                 GPIO_Pin_1

/* 组 1：从 CMP2（P 端由窗口模式共用，极性反转）*/
#define HW_MC_OCP_COMP2                     COMP_Selection_COMP2
#define HW_MC_OCP_COMP2_INVERT              COMP_InvertingInput_DAC1OUT2
#define HW_MC_OCP_COMP2_OUTPUT              COMP_Output_TIM8BKIN
#define HW_MC_OCP_COMP2_OUTPUTPOL           COMP_OutputPol_Inverted

/* 组 2：主 CMP3，P 端 = PB14 */
#define HW_MC_OCP_COMP3                     COMP_Selection_COMP3
#define HW_MC_OCP_COMP3_INVERT              COMP_InvertingInput_DAC1OUT1
#define HW_MC_OCP_COMP3_NONINVERT           COMP_NonInvertingInput_IO1
#define HW_MC_OCP_COMP3_OUTPUT              COMP_Output_TIM8BKIN
#define HW_MC_OCP_COMP3_OUTPUTPOL           COMP_OutputPol_NonInverted
#define HW_MC_OCP_COMP3_GPIO_Port           GPIOB
#define HW_MC_OCP_COMP3_Pin                 GPIO_Pin_14

/* 组 2：从 CMP4 */
#define HW_MC_OCP_COMP4                     COMP_Selection_COMP4
#define HW_MC_OCP_COMP4_INVERT              COMP_InvertingInput_DAC1OUT2
#define HW_MC_OCP_COMP4_OUTPUT              COMP_Output_TIM8BKIN
#define HW_MC_OCP_COMP4_OUTPUTPOL           COMP_OutputPol_Inverted

/* 组 3：主 CMP5，P 端 = PB13（与 W 相电流复用，硬件允许）*/
#define HW_MC_OCP_COMP5                     COMP_Selection_COMP5
#define HW_MC_OCP_COMP5_INVERT              COMP_InvertingInput_DAC1OUT1
#define HW_MC_OCP_COMP5_NONINVERT           COMP_NonInvertingInput_IO2
#define HW_MC_OCP_COMP5_OUTPUT              COMP_Output_TIM8BKIN
#define HW_MC_OCP_COMP5_OUTPUTPOL           COMP_OutputPol_NonInverted
#define HW_MC_OCP_COMP5_GPIO_Port           GPIOB
#define HW_MC_OCP_COMP5_Pin                 GPIO_Pin_13

/* 组 3：从 CMP6 */
#define HW_MC_OCP_COMP6                     COMP_Selection_COMP6
#define HW_MC_OCP_COMP6_INVERT              COMP_InvertingInput_DAC1OUT2
#define HW_MC_OCP_COMP6_OUTPUT              COMP_Output_TIM8BKIN
#define HW_MC_OCP_COMP6_OUTPUTPOL           COMP_OutputPol_Inverted

/* ---- 5.6 PWM（TIM8 互补输出）---- */
#define HW_MC_PWM_UH_GPIO_Port              GPIOC                   /* U 相上桥 */
#define HW_MC_PWM_UH_Pin                    GPIO_Pin_6
#define HW_MC_PWM_UH_Pin_Source             GPIO_PinSource6

#define HW_MC_PWM_VH_GPIO_Port              GPIOC                   /* V 相上桥 */
#define HW_MC_PWM_VH_Pin                    GPIO_Pin_7
#define HW_MC_PWM_VH_Pin_Source             GPIO_PinSource7

#define HW_MC_PWM_WH_GPIO_Port              GPIOC                   /* W 相上桥 */
#define HW_MC_PWM_WH_Pin                    GPIO_Pin_8
#define HW_MC_PWM_WH_Pin_Source             GPIO_PinSource8

#define HW_MC_PWM_UL_GPIO_Port              GPIOB                   /* U 相下桥 */
#define HW_MC_PWM_UL_Pin                    GPIO_Pin_3
#define HW_MC_PWM_UL_Pin_Source             GPIO_PinSource3

#define HW_MC_PWM_VL_GPIO_Port              GPIOB                   /* V 相下桥 */
#define HW_MC_PWM_VL_Pin                    GPIO_Pin_4
#define HW_MC_PWM_VL_Pin_Source             GPIO_PinSource4

#define HW_MC_PWM_WL_GPIO_Port              GPIOB                   /* W 相下桥 */
#define HW_MC_PWM_WL_Pin                    GPIO_Pin_5
#define HW_MC_PWM_WL_Pin_Source             GPIO_PinSource5

/* TIM8_CH4 用于 ADC 触发（仅内部 OC4REF 信号，不输出到引脚）*/
#define HW_MC_PWM_TRIG_ADC_CHANNEL          TIM_Channel_4


/*-------------------------- 6. LCD 引脚映射 -----------------------------*/
/* ---- 6.1 SPI3 引脚 ---- */
#define HW_LCD_SPI_NSS_Port                 GPIOA                   /* 软件片选 */
#define HW_LCD_SPI_NSS_Pin                  GPIO_Pin_15
#define HW_LCD_SPI_NSS_Pin_Source           GPIO_PinSource15

#define HW_LCD_SPI_SCK_Port                 GPIOC
#define HW_LCD_SPI_SCK_Pin                  GPIO_Pin_10
#define HW_LCD_SPI_SCK_Pin_Source           GPIO_PinSource10

#define HW_LCD_SPI_MISO_Port                GPIOC
#define HW_LCD_SPI_MISO_Pin                 GPIO_Pin_11
#define HW_LCD_SPI_MISO_Pin_Source          GPIO_PinSource11

#define HW_LCD_SPI_MOSI_Port                GPIOC
#define HW_LCD_SPI_MOSI_Pin                 GPIO_Pin_12
#define HW_LCD_SPI_MOSI_Pin_Source          GPIO_PinSource12

/* LCD 引脚（映射到 hw_map.h 中的引脚宏）*/
#define HW_LCD_DC_PORT                      HW_LCD_SPI_DC_Port
#define HW_LCD_DC_Pin                       HW_LCD_SPI_DC_Pin

#define HW_LCD_CS_PORT                      HW_LCD_SPI_NSS_Port
#define HW_LCD_CS_Pin                       HW_LCD_SPI_NSS_Pin

#define HW_LCD_RST_PORT                     GPIOD
#define HW_LCD_RST_Pin                      GPIO_Pin_3         /* 请按实际硬件修改 */

/* ---- 6.2 辅助 GPIO ---- */
#define HW_LCD_SPI_DC_Port                  GPIOD                   /* 数据/命令控制 */
#define HW_LCD_SPI_DC_Pin                   GPIO_Pin_2

#define HW_LCD_SPI_INT_Port                 GPIOB                   /* LCD_BUSY / INT */
#define HW_LCD_SPI_INT_Pin                  GPIO_Pin_6


#endif /* HW_MAP_H */
