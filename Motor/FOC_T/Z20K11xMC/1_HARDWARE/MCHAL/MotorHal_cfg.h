/**************************************************************************************************
*     File Name :                        MotorHal_cfg.h
*     Library/Module Name :              MotorHal
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制硬件参数设置头文件
**************************************************************************************************/
#ifndef MotorHal_cfg_H
#define MotorHal_cfg_H

//调用所有外设的头文件
#include "device_regs.h"
#include "Z20K11xM_cfg.h"
#include "Z20K11xM_corecfg.h"
#include "Z20K118M.h"

#include "Z20K11xM_adc.h"
#include "Z20K11xM_can.h"
#include "Z20K11xM_clock.h"
#include "Z20K11xM_cmp.h"
#include "Z20K11xM_crc.h"
#include "Z20K11xM_dma.h"
#include "Z20K11xM_drv.h"
#include "Z20K11xM_ewdt.h"
#include "Z20K11xM_flash.h"
#include "Z20K11xM_gpio.h"
#include "Z20K11xM_hwdiv.h"
#include "Z20K11xM_i2c.h"
#include "Z20K11xM_pmu.h"
#include "Z20K11xM_regfile.h"
#include "Z20K11xM_rtc.h"
#include "Z20K11xM_spi.h"
#include "Z20K11xM_srmc.h"
#include "Z20K11xM_stim.h"
#include "Z20K11xM_sysctrl.h"
#include "Z20K11xM_tdg.h"
#include "Z20K11xM_tim.h"
#include "Z20K11xM_tmu.h"
#include "Z20K11xM_uart.h"
#include "Z20K11xM_wdog.h"

#include "Math.h"

//三电阻采样或者单电阻采样选择
#define HAL_THREE_SHUNT             (0U)
#define HAL_ONE_SHUNT               (1U)
#define HAL_CURRENT_SAMPLE_MODE     HAL_ONE_SHUNT   


//频率设置
#define HAL_SYSTEM_FREQ                         (64000.0f)                 //kHz，系统时钟频率
#define HAL_PWM_CLK_FREQ                        (HAL_SYSTEM_FREQ)          //kHz，PWM时钟频率
#define HAL_HALL_TIM_CLK_FREQ                   (HAL_SYSTEM_FREQ)          //kHz，用过零点计数定时器时钟频率
#define HAL_SWITCH_TIM_CLK_FREQ                 (HAL_SYSTEM_FREQ)          //kHz，用于换向计数定时器时钟频率

#define HAL_PWM_PRESCALER                       (1.0f)
#define HAL_PWM_PRE_FREQ                        (HAL_PWM_CLK_FREQ/HAL_PWM_PRESCALER)               //kHz，PWM计数器频率,80M


//载频选择
#define HAL_PWM_FREQ_1K                         (1.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_2K                         (2.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_5K                         (5.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_6K                         (6.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_8K                         (8.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_10K                        (10.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_12K                        (12.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_16K                        (16.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_18K                        (18.0f)                         //kHz，PWM载频
#define HAL_PWM_FREQ_20K                        (20.0f)                         //kHz，PWM载频

#define HAL_PWM_SET_FREQ                        (HAL_PWM_FREQ_16K)
#define HAL_PWM_ALL_COUNT_F                     (HAL_PWM_PRE_FREQ/HAL_PWM_SET_FREQ)
#define HAL_PWM_SET_COUNT_F                     (HAL_PWM_ALL_COUNT_F)
#define HAL_PWM_SET_COUNT_T                     (Q16U_)(HAL_PWM_SET_COUNT_F)

#define HAL_CURRENT_PRESCALER                   (2.0f)

#define HAL_PWM_DUTY_MAX_F                      (Q12U_MAX)
#define HAL_PWM_DUTY_MAX_T                      (Q16U_)(Q12U_MAX)

#define HAL_PWM_DUTY_1_PERCENT                  (Q16U_)(0.01f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_2_PERCENT                  (Q16U_)(0.02f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_3_PERCENT                  (Q16U_)(0.03f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_4_PERCENT                  (Q16U_)(0.04f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_5_PERCENT                  (Q16U_)(0.05f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_8_PERCENT                  (Q16U_)(0.08f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_10_PERCENT                 (Q16U_)(0.10f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_12_PERCENT                 (Q16U_)(0.12f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_15_PERCENT                 (Q16U_)(0.15f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_16_PERCENT                 (Q16U_)(0.16f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_18_PERCENT                 (Q16U_)(0.18f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_20_PERCENT                 (Q16U_)(0.20f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_30_PERCENT                 (Q16U_)(0.30f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_40_PERCENT                 (Q16U_)(0.40f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_50_PERCENT                 (Q16U_)(0.50f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_60_PERCENT                 (Q16U_)(0.60f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_70_PERCENT                 (Q16U_)(0.70f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_80_PERCENT                 (Q16U_)(0.80f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_90_PERCENT                 (Q16U_)(0.90f*HAL_PWM_DUTY_MAX_F)      //基础占空比
#define HAL_PWM_DUTY_100_PERCENT                (Q16U_)(1.00f*HAL_PWM_DUTY_MAX_F)      //基础占空比


//PWM设置
#define HAL_PWM_DEADTIME_TIME                   (0.5f)                  		//us，死区时间
#define HAL_PWM_DEADTIME_VALUE                  (Q32U_)(HAL_PWM_PRE_FREQ*HAL_PWM_DEADTIME_TIME/1000.0f)


//ADC采样时刻设置
#define HAL_ADC_TRIGGER_TIME1                   (0.15f)
#define HAL_ADC_TRIGGER_TIME2                   (0.35f)
#define HAL_ADC_TRIGGER_TIME3                   (0.55f)

#if(HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
#define HAL_ADC_DELAY_TIME                      (1.2f)                  //us，米勒平台时间
#define HAL_ADC_DELAY_DUTY                      (HAL_ADC_DELAY_TIME*HAL_PWM_SET_FREQ/1000.0f)
#define HAL_ADC_DELAY_VALUE                     (Q32U_)(HAL_ADC_DELAY_DUTY*HAL_PWM_ALL_COUNT_F)

#define HAL_ADC_SAMPLE_TIME                     (3.8f)                  //us，ADC采样时间
#define HAL_ADC_SAMPLE_DUTY                     (HAL_ADC_SAMPLE_TIME*HAL_PWM_SET_FREQ/1000.0f)
#define HAL_ADC_SAMPLE_VALUE                    (Q32U_)(HAL_ADC_SAMPLE_DUTY*HAL_PWM_ALL_COUNT_F)

#define HAL_MAX_DUTY                            (1.0f - (HAL_ADC_DELAY_DUTY + HAL_ADC_SAMPLE_DUTY))
#define HAL_MIN_DUTY                            (HAL_ADC_DELAY_DUTY + HAL_ADC_SAMPLE_DUTY)

#elif(HAL_CURRENT_SAMPLE_MODE == HAL_ONE_SHUNT)
#define HAL_ADC_DELAY_TIME                      (1.2f)                  //us，米勒平台时间
#define HAL_ADC_DELAY_DUTY                      (HAL_ADC_DELAY_TIME*HAL_PWM_SET_FREQ/1000.0f)
#define HAL_ADC_DELAY_VALUE                     (Q16U_)(HAL_ADC_DELAY_DUTY*HAL_PWM_ALL_COUNT_F)

#define HAL_ADC_SAMPLE_TIME                     (1.3f)                  //us，ADC采样时间
#define HAL_ADC_SAMPLE_DUTY                     (HAL_ADC_SAMPLE_TIME*HAL_PWM_SET_FREQ/1000.0f)
#define HAL_ADC_SAMPLE_VALUE                    (Q16U_)(HAL_ADC_SAMPLE_DUTY*HAL_PWM_ALL_COUNT_F)

#define HAL_MAX_DUTY                            (1.0f - 2.0f*(HAL_ADC_DELAY_DUTY + HAL_ADC_SAMPLE_DUTY))
#define HAL_MIN_DUTY                            (2.0f*(HAL_ADC_DELAY_DUTY + HAL_ADC_SAMPLE_DUTY))

#endif


//TIM设置
#define HAL_HALL_TIM_PRESCALER                  (16.0f)    
#define HAL_HALL_TIM_PRE_FREQ                   (Q32U_)(1000.0f*HAL_HALL_TIM_CLK_FREQ/(HAL_HALL_TIM_PRESCALER))     //Hz，HALL换相时钟频率，10M  

#define HAL_SLOW_TIMER_FREQ                     (1.0f)                  //kHz，滴答定时器周期
#define HAL_SLOW_TIMER_COUNT                    (Q32U_)(HAL_SYSTEM_FREQ/HAL_SLOW_TIMER_FREQ)     //kHz，滴答定时器周期


//ADC设置
#define HAL_ADC_REF_VOLTAGE_V                   (5.0f)                  //V，ADC参考电平
#define HAL_ADC_SCALE_BIT                       (4095.0f)               //lsb，ADC精度

//母线电压采样
#define HAL_ADC_VOLTAGE_RESISTOR_UP             (29.4f)                 //母线电压采样上分压电阻
#define HAL_ADC_VOLTAGE_RESISTOR_DOWN           (3.0f)                  //母线电压采样下分压电阻
#define HAL_ADC_VOLTAGE_COEFF                   ((HAL_ADC_VOLTAGE_RESISTOR_UP+HAL_ADC_VOLTAGE_RESISTOR_DOWN)/HAL_ADC_VOLTAGE_RESISTOR_DOWN)
#define HAL_ADC_VOLTAGE_MAX                     (HAL_ADC_REF_VOLTAGE_V*HAL_ADC_VOLTAGE_COEFF)   //V，最大采样电压
#define HAL_ADC_VOLTAGE_SCALE                   (HAL_ADC_VOLTAGE_MAX/HAL_ADC_SCALE_BIT)         //V/lsb，电压刻度

//相电流采样
#define HAL_ADC_CURRENT_OFFSET                  (2.5f)                  //V，电流采样偏置电压
#define HAL_ADC_CURRENT_GAIN                    (20.0f)                 //相电流采样放大倍数
#define HAL_ADC_CURRENT_RESISTOR                (0.005f)                //Ω，相电流采样电阻
#define HAL_ADC_CURRENT_COEFF                   (1.0f/(HAL_ADC_CURRENT_RESISTOR*HAL_ADC_CURRENT_GAIN))
#define HAL_ADC_CURRENT_MAX                     (HAL_ADC_REF_VOLTAGE_V*HAL_ADC_CURRENT_COEFF)   //A，最大采样电流
#define HAL_ADC_CURRENT_SCALE                   (HAL_ADC_CURRENT_MAX/HAL_ADC_SCALE_BIT)         //A/lsb，电流刻度


//外设
#define HAL_MOTOR_PWM               TIM0_ID
#define HAL_MOTOR_PWM_ADDRESS       TIM0_BASE_ADDR
#define HAL_MOTOR_ADC               ADC0_ID
#define HAL_MOTOR_ADC_ADDRESS       ADC0_BASE_ADDR
#define HAL_MOTOR_ADC_DATA_ADDRESS  (HAL_MOTOR_ADC_ADDRESS + 0x20U)
#define HAL_MOTOR_ADC_NUM           6U
#define HAL_MOTOR_TDG	            TDG0_ID   
#define HAL_MOTOR_TDG_ADDRESS       TDG0_BASE_ADDR

//PWM
#define HAL_PWM_UH_PORT             PORT_B
#define HAL_PWM_UH_PIN              GPIO_4
#define HAL_PWM_UH_PINMUX           PTB4_TIM0_CH4
#define HAL_PWM_UH_CHN              TIM_CHANNEL_4

#define HAL_PWM_UL_PORT             PORT_B
#define HAL_PWM_UL_PIN              GPIO_5
#define HAL_PWM_UL_PINMUX           PTB5_TIM0_CH5
#define HAL_PWM_UL_CHN              TIM_CHANNEL_5

#define HAL_PWM_VH_PORT             PORT_E
#define HAL_PWM_VH_PIN              GPIO_8
#define HAL_PWM_VH_PINMUX           PTE8_TIM0_CH6
#define HAL_PWM_VH_CHN              TIM_CHANNEL_6

#define HAL_PWM_VL_PORT             PORT_E
#define HAL_PWM_VL_PIN              GPIO_9
#define HAL_PWM_VL_PINMUX           PTE9_TIM0_CH7
#define HAL_PWM_VL_CHN              TIM_CHANNEL_7

#define HAL_PWM_WH_PORT             PORT_D
#define HAL_PWM_WH_PIN              GPIO_15
#define HAL_PWM_WH_PINMUX           PTD15_TIM0_CH0
#define HAL_PWM_WH_CHN              TIM_CHANNEL_0

#define HAL_PWM_WL_PORT             PORT_D
#define HAL_PWM_WL_PIN              GPIO_16
#define HAL_PWM_WL_PINMUX           PTD16_TIM0_CH1
#define HAL_PWM_WL_CHN              TIM_CHANNEL_1

#define HAL_PWM_U_PAIR              TIM_PAIR_CHANNEL_2
#define HAL_PWM_V_PAIR              TIM_PAIR_CHANNEL_3
#define HAL_PWM_W_PAIR              TIM_PAIR_CHANNEL_0

#define HAL_PWM_UH_CHN_EN           ((Q32U_)(0x1UL << ((Q32U_)HAL_PWM_UH_CHN)))
#define HAL_PWM_UL_CHN_EN           ((Q32U_)(0x1UL << ((Q32U_)HAL_PWM_UL_CHN)))
#define HAL_PWM_VH_CHN_EN           ((Q32U_)(0x1UL << ((Q32U_)HAL_PWM_VH_CHN)))
#define HAL_PWM_VL_CHN_EN           ((Q32U_)(0x1UL << ((Q32U_)HAL_PWM_VL_CHN)))
#define HAL_PWM_WH_CHN_EN           ((Q32U_)(0x1UL << ((Q32U_)HAL_PWM_WH_CHN)))
#define HAL_PWM_WL_CHN_EN           ((Q32U_)(0x1UL << ((Q32U_)HAL_PWM_WL_CHN)))
#define HAL_PWM_UP_CHN              (HAL_PWM_UH_CHN_EN|HAL_PWM_VH_CHN_EN|HAL_PWM_WH_CHN_EN)
#define HAL_PWM_DN_CHN              (HAL_PWM_UL_CHN_EN|HAL_PWM_VL_CHN_EN|HAL_PWM_WL_CHN_EN)
#define HAL_PWM_ALL_CHN             (HAL_PWM_UP_CHN|HAL_PWM_DN_CHN)

#define HAL_PWM_FAULT_PORT          PORT_A
#define HAL_PWM_FAULT_PIN           GPIO_6
#define HAL_PWM_FAULT_PINMUX        PTA6_TIM0_FLT1


//ADC_MOTOR
#define HAL_ADC_IU_PORT             PORT_C
#define HAL_ADC_IU_PIN              GPIO_17
#define HAL_ADC_IU_PINMUX           PTC17_ADC0_CH15
#define HAL_ADC_IU_CHN              ADC_P_CH15

#define HAL_ADC_IV_PORT             PORT_C
#define HAL_ADC_IV_PIN              GPIO_16
#define HAL_ADC_IV_PINMUX           PTC16_ADC0_CH14
#define HAL_ADC_IV_CHN              ADC_P_CH14

#define HAL_ADC_IW_PORT             PORT_C
#define HAL_ADC_IW_PIN              GPIO_15
#define HAL_ADC_IW_PINMUX           PTC15_ADC0_CH13
#define HAL_ADC_IW_CHN              ADC_P_CH13

#define HAL_ADC_VBUS_PORT           PORT_C
#define HAL_ADC_VBUS_PIN            GPIO_14
#define HAL_ADC_VBUS_PINMUX         PTC14_ADC0_CH12
#define HAL_ADC_VBUS_CHN            ADC_P_CH12

//ADC_SYSTEM
#define HAL_ADC_VR_PORT             PORT_C
#define HAL_ADC_VR_PIN              GPIO_1
#define HAL_ADC_VR_PINMUX           PTC1_ADC0_CH9
#define HAL_ADC_VR_CHN              ADC_P_CH9
    
#define HAL_ADC_TEMP_PORT           PORT_B
#define HAL_ADC_TEMP_PIN            GPIO_15
#define HAL_ADC_TEMP_PINMUX         PTB15_ADC1_CH14
#define HAL_ADC_TEMP_CHN            ADC_P_CH14

//HALL
#define HAL_HALLA_PORT              PORT_A
#define HAL_HALLA_PIN               GPIO_11
#define HAL_HALLA_PINMUX            PTA11_GPIO
#define HAL_HALLB_PORT              PORT_A
#define HAL_HALLB_PIN               GPIO_12
#define HAL_HALLB_PINMUX            PTA12_GPIO
#define HAL_HALLC_PORT              PORT_A
#define HAL_HALLC_PIN               GPIO_13
#define HAL_HALLC_PINMUX            PTA13_GPIO


#endif /* MotorHal_cfg_H */
