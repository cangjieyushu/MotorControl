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
#include "platform_cfg.h"
#include "adc_drv.h"
#include "clock_drv.h"
#include "common_drv.h"
#include "dma_drv.h"
#include "flash_drv.h"
#include "gpio_drv.h"
#include "int_drv.h"
#include "mcpwm_drv.h"
#include "scm_drv.h"
#include "stim_drv.h"
#include "sysctrl_drv.h"
#include "tdg_drv.h"
#include "tmu_drv.h"
#include "uart_drv.h"
#include "wdog_drv.h"

#include "Math.h"

//三电阻采样或者单电阻采样选择
#define HAL_ONE_SHUNT               (0U)
#define HAL_THREE_SHUNT             (1U)
#define HAL_CURRENT_SAMPLE_MODE     HAL_ONE_SHUNT   

//频率设置
#define HAL_SYSTEM_FREQ                         (160000.0f)                //kHz，系统时钟频率
#define HAL_PWM_CLK_FREQ                        (HAL_SYSTEM_FREQ)          //kHz，PWM时钟频率
#define HAL_HALL_TIM_CLK_FREQ                   (HAL_SYSTEM_FREQ)          //kHz，用过零点计数定时器时钟频率
#define HAL_SWITCH_TIM_CLK_FREQ                 (HAL_SYSTEM_FREQ)          //kHz，用于换向计数定时器时钟频率

#define HAL_PWM_PRESCALER                       (2.0f)
#define HAL_PWM_PRE_FREQ                        (HAL_PWM_CLK_FREQ/(HAL_PWM_PRESCALER))               //kHz，PWM计数器频率,48M


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

#define HAL_PWM_SET_FREQ                        (HAL_PWM_FREQ_20K)
#define HAL_PWM_ALL_COUNT_F                     (HAL_PWM_PRE_FREQ/HAL_PWM_SET_FREQ)
#define HAL_PWM_SET_COUNT_F                     (HAL_PWM_ALL_COUNT_F/2.0f)
#define HAL_PWM_SET_COUNT_U                     (Q32U_)(HAL_PWM_SET_COUNT_F)

//PWM设置
#define HAL_PWM_DEADTIME_TIME                   (1.0f*1.5f)                  //us，死区时间
#define HAL_PWM_DEADTIME_VALUE                  (Q32U_)(HAL_PWM_PRE_FREQ*HAL_PWM_DEADTIME_TIME/1000.0f)


//ADC采样时刻设置
#define HAL_ADC_TRIGGER_TIME1                   (0.15f)
#define HAL_ADC_TRIGGER_TIME2                   (0.35f)
#define HAL_ADC_TRIGGER_TIME3                   (0.50f)

#if(HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
#define HAL_ADC_DELAY_TIME                      (1.0f)                  //us，米勒平台时间
#define HAL_ADC_DELAY_DUTY                      (HAL_ADC_DELAY_TIME*HAL_PWM_SET_FREQ/1000.0f)
#define HAL_ADC_DELAY_VALUE                     (Q16U_)(HAL_ADC_DELAY_DUTY*HAL_PWM_ALL_COUNT_F)

#define HAL_ADC_SAMPLE_TIME                     (4.0f)                  //us，ADC采样时间
#define HAL_ADC_SAMPLE_DUTY                     (HAL_ADC_SAMPLE_TIME*HAL_PWM_SET_FREQ/1000.0f)
#define HAL_ADC_SAMPLE_VALUE                    (Q16U_)(HAL_ADC_SAMPLE_DUTY*HAL_PWM_ALL_COUNT_F)

#define HAL_MAX_DUTY                            (1.0f - (HAL_ADC_DELAY_DUTY + HAL_ADC_SAMPLE_DUTY))
#define HAL_MIN_DUTY                            (HAL_ADC_DELAY_DUTY + HAL_ADC_SAMPLE_DUTY)

#elif(HAL_CURRENT_SAMPLE_MODE == HAL_ONE_SHUNT)
#define HAL_ADC_DELAY_TIME                      (2.0f)                  //us，米勒平台时间
#define HAL_ADC_DELAY_DUTY                      (HAL_ADC_DELAY_TIME*HAL_PWM_SET_FREQ/1000.0f)
#define HAL_ADC_DELAY_VALUE                     (Q16U_)(HAL_ADC_DELAY_DUTY*HAL_PWM_ALL_COUNT_F)

#define HAL_ADC_SAMPLE_TIME                     (2.0f)                  //us，ADC采样时间
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
#define HAL_ADC_CURRENT_GAIN                    (10.0f)                 //相电流采样放大倍数
#define HAL_ADC_CURRENT_RESISTOR                (0.005f)                //Ω，相电流采样电阻
#define HAL_ADC_CURRENT_COEFF                   (1.0f/(HAL_ADC_CURRENT_RESISTOR*HAL_ADC_CURRENT_GAIN))
#define HAL_ADC_CURRENT_MAX                     (HAL_ADC_REF_VOLTAGE_V*HAL_ADC_CURRENT_COEFF)   //A，最大采样电流
#define HAL_ADC_CURRENT_SCALE                   (HAL_ADC_CURRENT_MAX/HAL_ADC_SCALE_BIT)         //A/lsb，电流刻度


//外设
#define HAL_ADC_ID                  ADC0_ID
#define HAL_ADC1_ID                 ADC1_ID
#define HAL_TGD_ID	                TDG0_ID
#define HAL_STIM_ID                 STIM_0
#define HAL_STIM_HALL               STIM_1


#define HAL_MCPWM_ID                MCPWM1_ID
#define HAL_PWM_COUNTER_ID          MCPWM_COUNTER_0

#define HAL_FAULTIN                 MCPWM_INT_FAULT
#define HAL_FAULTIN_PORT            PORT_B
#define HAL_FAULTIN_PIN             GPIO_2
#define HAL_FAULTIN_PINMUX          PTB2_MCPWM1_FLT3
    
#define HAL_PWM_UH_PORT             PORT_E
#define HAL_PWM_UH_PIN              GPIO_8
#define HAL_PWM_UH_PINMUX           PTE8_MCPWM1_CH0
#define HAL_PWM_UH_CHN              MCPWM_CHANNEL_0
    
#define HAL_PWM_UL_PORT             PORT_B
#define HAL_PWM_UL_PIN              GPIO_5
#define HAL_PWM_UL_PINMUX           PTB5_MCPWM1_CH1
#define HAL_PWM_UL_CHN              MCPWM_CHANNEL_1
    
#define HAL_PWM_VH_PORT             PORT_B
#define HAL_PWM_VH_PIN              GPIO_4
#define HAL_PWM_VH_PINMUX           PTB4_MCPWM1_CH2
#define HAL_PWM_VH_CHN              MCPWM_CHANNEL_2
    
#define HAL_PWM_VL_PORT             PORT_C
#define HAL_PWM_VL_PIN              GPIO_3
#define HAL_PWM_VL_PINMUX           PTC3_MCPWM1_CH3
#define HAL_PWM_VL_CHN              MCPWM_CHANNEL_3
    
#define HAL_PWM_WH_PORT             PORT_D
#define HAL_PWM_WH_PIN              GPIO_7
#define HAL_PWM_WH_PINMUX           PTD7_MCPWM1_CH4
#define HAL_PWM_WH_CHN              MCPWM_CHANNEL_4
    
#define HAL_PWM_WL_PORT             PORT_D
#define HAL_PWM_WL_PIN              GPIO_6
#define HAL_PWM_WL_PINMUX           PTD6_MCPWM1_CH5
#define HAL_PWM_WL_CHN              MCPWM_CHANNEL_5
    
#define HAL_PWM_U_PAIR_ID           MCPWM_PAIR_CHANNEL_0
#define HAL_PWM_V_PAIR_ID           MCPWM_PAIR_CHANNEL_1
#define HAL_PWM_W_PAIR_ID           MCPWM_PAIR_CHANNEL_2
    
#define HAL_ADC_VBUS_PORT           PORT_C
#define HAL_ADC_VBUS_PIN            GPIO_14
#define HAL_ADC_VBUS_PINMUX         PTC14_ADC0_CH12
#define HAL_ADC_VBUS_CHN            ADC_P_CH12
    
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

#define HAL_ADC1_VR_PORT            PORT_B
#define HAL_ADC1_VR_PIN             GPIO_14
#define HAL_ADC1_VR_PINMUX          PTB14_ADC1_CH9
#define HAL_ADC1_VR_CHN             ADC_P_CH9
    
#define HAL_ADC1_TEMP_PORT          PORT_B
#define HAL_ADC1_TEMP_PIN           GPIO_15
#define HAL_ADC1_TEMP_PINMUX        PTB15_ADC1_CH14
#define HAL_ADC1_TEMP_CHN           ADC_P_CH14
    
#define HAL_ADC1_BAT_PORT           PORT_B
#define HAL_ADC1_BAT_PIN            GPIO_16
#define HAL_ADC1_BAT_PINMUX         PTB16_ADC1_CH15
#define HAL_ADC1_BAT_CHN            ADC_P_CH15
    
#define HAL_HALLA_PORT              PORT_A
#define HAL_HALLA_PIN               GPIO_10
#define HAL_HALLA_PINMUX            PTA10_GPIO
#define HAL_HALLB_PORT              PORT_A
#define HAL_HALLB_PIN               GPIO_11
#define HAL_HALLB_PINMUX            PTA11_GPIO
#define HAL_HALLC_PORT              PORT_A
#define HAL_HALLC_PIN               GPIO_12
#define HAL_HALLC_PINMUX            PTA12_GPIO

#endif /* MotorHal_cfg_H */
