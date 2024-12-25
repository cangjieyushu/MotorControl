/**************************************************************************************************/
/**
 * @file     gpio_drv.h
 * @brief    GPIO driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#ifndef GPIO_DRV_H
#define GPIO_DRV_H

#include "common_drv.h"
/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  GPIO
 *  @{
 */

/** @defgroup PORT_Public_Types
 *  @{
 */

 /**
 *  @brief PORT ID type definition
 */
typedef enum
{
    PORT_A = 0U,                      /*!< PORT_A  */
    PORT_B,                           /*!< PORT_B  */
    PORT_C,                           /*!< PORT_C  */
    PORT_D,                           /*!< PORT_D  */
    PORT_E                            /*!< PORT_E  */
} PORT_Id_t;

/**
 *  @brief PORT GPIO Number type definition
 */
typedef enum
{
    GPIO_0 = 0U,                      /*!< GPIO0 Pin */
    GPIO_1,                           /*!< GPIO1 Pin */
    GPIO_2,                           /*!< GPIO2 Pin */
    GPIO_3,                           /*!< GPIO3 Pin */
    GPIO_4,                           /*!< GPIO4 Pin */
    GPIO_5,                           /*!< GPIO5 Pin */
    GPIO_6,                           /*!< GPIO6 Pin */
    GPIO_7,                           /*!< GPIO7 Pin */
    GPIO_8,                           /*!< GPIO8 Pin */
    GPIO_9,                           /*!< GPIO9 Pin */
    GPIO_10,                          /*!< GPIO10 Pin */
    GPIO_11,                          /*!< GPIO11 Pin */
    GPIO_12,                          /*!< GPIO12 Pin */
    GPIO_13,                          /*!< GPIO13 Pin */
    GPIO_14,                          /*!< GPIO14 Pin */
    GPIO_15,                          /*!< GPIO15 Pin */
    GPIO_16,                          /*!< GPIO16 Pin */
    GPIO_17,                          /*!< GPIO17 Pin */
    GPIO_18,                          /*!< GPIO18 Pin */
    GPIO_19,                          /*!< GPIO19 Pin */
    GPIO_20,                          /*!< GPIO20 Pin */
    GPIO_21,                          /*!< GPIO21 Pin */
    GPIO_22,                          /*!< GPIO22 Pin */
    GPIO_23,                          /*!< GPIO23 Pin */
    GPIO_24,                          /*!< GPIO24 Pin */
    GPIO_25,                          /*!< GPIO25 Pin */
    GPIO_26,                          /*!< GPIO26 Pin */
    GPIO_27,                          /*!< GPIO27 Pin */
    GPIO_28,                          /*!< GPIO28 Pin */
    GPIO_29,                          /*!< GPIO29 Pin */
    GPIO_30,                          /*!< GPIO30 Pin */
    GPIO_31                           /*!< GPIO31 Pin */
} PORT_GpioNum_t;

/**
 *  @brief PORT half pins type definition
 */
typedef enum
{
    PORT_LOW_HALF_PINS = 0U,          /*!< PORT low  half pins */
    PORT_HIGH_HALF_PINS               /*!< PORT high half pins */
} PORT_GlobalPinsControl_t;

/**
 *  @brief PORT pull type definition
 */
typedef enum
{
    PORT_PULL_DISABLED = 0U,          /*!< PORT pull none */
    PORT_PULL_DOWN     = 2U,          /*!< PORT pull down */
    PORT_PULL_UP       = 3U,          /*!< PORT pull up   */
} PORT_PullConfig_t;

/**
 *  @brief PORT slew rate type definition
 */
typedef enum
{
    PORT_FAST_RATE = 0U,              /*!< PORT fast rate */
    PORT_SLOW_RATE                    /*!< PORT slow rate */
} PORT_SlewRate_t;

/**
 *  @brief PORT interrupt configuration type definition
 */
typedef enum
{
    PORT_ISF_DISABLED = 0U,                /*!< PORT isf disabled          */
    PORT_ISF_DMA_RISING_EDGE = 1U,         /*!< PORT isf dma rising        */
    PORT_ISF_DMA_FALLING_EDGE = 2U,        /*!< PORT isf dma falling       */
    PORT_ISF_DMA_BOTH_EDGE = 3U,           /*!< PORT isf dma both          */
    PORT_ISF_INT_LOGIC_0 = 8U,             /*!< PORT isf interrupt logic 0 */
    PORT_ISF_INT_RISING_EDGE = 9U,         /*!< PORT isf interrupt rising  */
    PORT_ISF_INT_FALLING_EDGE = 10U,       /*!< PORT isf interrupt falling */
    PORT_ISF_INT_BOTH_EDGE = 11U,          /*!< PORT isf interrupt both    */
    PORT_ISF_INT_LOGIC_1 = 12U,            /*!< PORT isf interrupt logic 1 */
} PORT_IntConfig_t;


/**
 *  @brief PORT pin configuration struct definition
 */
typedef struct
{
    PORT_PullConfig_t    pullConfig;           /*!< Configure pull type:
                                                    - PORT_PULL_DISABLE(0)
                                                    - PORT_PULL_DOWN(2)
                                                    - PORT_PULL_UP(3)
                                                */
    PORT_SlewRate_t      slewRateConfig;       /*!< Configure slew rate type:
                                                    - PORT_FAST_RATE(0)
                                                    - PORT_SLOW_RATE(1)
                                                */
    ControlState_t       passiveFilterConfig;  /*!< Configure the enable of the passive filter,
                                                    - DISABLE
                                                    - ENABLE
                                                */
    ControlState_t       openDrainConfig;      /*!< Configure the enable of the open drain,
                                                    - DISABLE
                                                    - ENABLE
                                                */

                                               
    ControlState_t       filterEnable;         /*!< Configure the enable of the filter,
                                                    - DISABLE
                                                    - ENABLE
                                                */
    uint8_t              filterConfig;         /*!< Configure filter:0x0-0x1F */
} PORT_PinConfig_t;

/** @} end of group PORT_Public_Types */


/** @defgroup GPIO_Public_Types
 *  @{
 */
/**
 *  @brief GPIO data direction type definition
 */
typedef enum
{
  GPIO_INPUT = 0U,                    /*!< Set GPIO port data direction as input  */
  GPIO_OUTPUT                         /*!< Set GPIO port data direction as output */
} GPIO_Dir_t;

/**
 *  @brief GPIO data Input/Output type definition
 */
typedef enum
{
  GPIO_LOW = 0U,                      /*!< Input/Output low level(0) */
  GPIO_HIGH                           /*!< Input/Output low level(1) */
} GPIO_Level_t;

/** @} end of group GPIO_Public_Types */

/** @defgroup PORT_Pinmux
 *  @{
 */

/**
 *  @brief PORT Pinmux function type definition
 */
typedef enum
{
    PINMUX_FUNCTION_0 = 0U,           /*!< PORT pin mux function 0 define */
    PINMUX_FUNCTION_1,                /*!< PORT pin mux function 1 define */
    PINMUX_FUNCTION_2,                /*!< PORT pin mux function 2 define */
    PINMUX_FUNCTION_3,                /*!< PORT pin mux function 3 define */
    PINMUX_FUNCTION_4,                /*!< PORT pin mux function 4 define */
    PINMUX_FUNCTION_5,                /*!< PORT pin mux function 5 define */
    PINMUX_FUNCTION_6,                /*!< PORT pin mux function 6 define */
    PINMUX_FUNCTION_7                 /*!< PORT pin mux function 7 define */
} PORT_PinMuxFunc_t;

/* PTA0 pinmux function definition */
#define PTA0_ADC0_CH0                         PINMUX_FUNCTION_0 
#define PTA0_CMP0_IN0                         PINMUX_FUNCTION_0 
#define PTA0_GPIO                             PINMUX_FUNCTION_1 
#define PTA0_TIM2_CH7                         PINMUX_FUNCTION_2 
#define PTA0_I2C0_SCL                         PINMUX_FUNCTION_3 
#define PTA0_PMU_REQ                          PINMUX_FUNCTION_4 
#define PTA0_I2C1_SCL                         PINMUX_FUNCTION_5 
#define PTA0_UART0_CTS                        PINMUX_FUNCTION_6 
#define PTA0_TMU_OUT3                         PINMUX_FUNCTION_7 

/* PTA1 pinmux function definition */
#define PTA1_ADC0_CH1                         PINMUX_FUNCTION_0 
#define PTA1_ADC0_N_CH0                       PINMUX_FUNCTION_0 
#define PTA1_CMP0_IN1                         PINMUX_FUNCTION_0 
#define PTA1_GPIO                             PINMUX_FUNCTION_1 
#define PTA1_TIM1_CH1                         PINMUX_FUNCTION_2 
#define PTA1_I2C0_SDA                         PINMUX_FUNCTION_3 
#define PTA1_I2C1_SDA                         PINMUX_FUNCTION_5 
#define PTA1_UART0_RTS                        PINMUX_FUNCTION_6 
#define PTA1_TMU_OUT0                         PINMUX_FUNCTION_7 

/* PTA2 pinmux function definition */
#define PTA2_ADC1_CH0                         PINMUX_FUNCTION_0 
#define PTA2_GPIO                             PINMUX_FUNCTION_1 
#define PTA2_TIM3_CH0                         PINMUX_FUNCTION_2 
#define PTA2_I2C0_SDA                         PINMUX_FUNCTION_3 
#define PTA2_EWDT_OUT_b                       PINMUX_FUNCTION_4 
#define PTA2_MCPWM0_FLT2                      PINMUX_FUNCTION_5 
#define PTA2_UART0_RX                         PINMUX_FUNCTION_6 
#define PTA2_SPI1_SCK                         PINMUX_FUNCTION_7 

/* PTA3 pinmux function definition */
#define PTA3_ADC1_CH1                         PINMUX_FUNCTION_0 
#define PTA3_ADC1_N_CH0                       PINMUX_FUNCTION_0 
#define PTA3_GPIO                             PINMUX_FUNCTION_1 
#define PTA3_TIM3_CH1                         PINMUX_FUNCTION_2 
#define PTA3_I2C0_SCL                         PINMUX_FUNCTION_3 
#define PTA3_EWDT_IN                          PINMUX_FUNCTION_4 
#define PTA3_MCPWM0_FLT3                      PINMUX_FUNCTION_5 
#define PTA3_UART0_TX                         PINMUX_FUNCTION_6 
#define PTA3_SPI1_SIN                         PINMUX_FUNCTION_7 

/* PTA4 pinmux function definition */
#define PTA4_GPIO                             PINMUX_FUNCTION_1 
#define PTA4_CAN0_RX                          PINMUX_FUNCTION_3 
#define PTA4_CMP0_OUT                         PINMUX_FUNCTION_4 
#define PTA4_EWDT_OUT_b                       PINMUX_FUNCTION_5 
#define PTA4_JTAG_TMS                         PINMUX_FUNCTION_7 
#define PTA4_SWD_DIO                          PINMUX_FUNCTION_7 

/* PTA5 pinmux function definition */
#define PTA5_GPIO                             PINMUX_FUNCTION_1 
#define PTA5_TCLK1                            PINMUX_FUNCTION_3 
#define PTA5_RESET_b                          PINMUX_FUNCTION_7 

/* PTA6 pinmux function definition */
#define PTA6_ADC0_CH2                         PINMUX_FUNCTION_0 
#define PTA6_GPIO                             PINMUX_FUNCTION_1 
#define PTA6_TIM0_FLT1                        PINMUX_FUNCTION_2 
#define PTA6_SPI1_PCS1                        PINMUX_FUNCTION_3 
#define PTA6_CAN5_TX                          PINMUX_FUNCTION_5 
#define PTA6_UART1_CTS                        PINMUX_FUNCTION_6 
#define PTA6_UART3_RX                         PINMUX_FUNCTION_7 

/* PTA7 pinmux function definition */
#define PTA7_ADC0_CH3                         PINMUX_FUNCTION_0 
#define PTA7_ADC0_N_CH1                       PINMUX_FUNCTION_0 
#define PTA7_GPIO                             PINMUX_FUNCTION_1 
#define PTA7_SPI0_PCS1                        PINMUX_FUNCTION_3 
#define PTA7_CAN5_RX                          PINMUX_FUNCTION_5 
#define PTA7_UART1_RTS                        PINMUX_FUNCTION_6 
#define PTA7_UART3_TX                         PINMUX_FUNCTION_7 

/* PTA8 pinmux function definition */
#define PTA8_GPIO                             PINMUX_FUNCTION_1 
#define PTA8_UART2_RX                         PINMUX_FUNCTION_2 
#define PTA8_SPI2_SOUT                        PINMUX_FUNCTION_3 
#define PTA8_CAN5_RX                          PINMUX_FUNCTION_4 

/* PTA9 pinmux function definition */
#define PTA9_GPIO                             PINMUX_FUNCTION_1 
#define PTA9_UART2_TX                         PINMUX_FUNCTION_2 
#define PTA9_SPI2_PCS0                        PINMUX_FUNCTION_3 
#define PTA9_CAN5_TX                          PINMUX_FUNCTION_4 

/* PTA10 pinmux function definition */
#define PTA10_XTAL32                          PINMUX_FUNCTION_0 
#define PTA10_GPIO                            PINMUX_FUNCTION_1 
#define PTA10_TIM1_CH4                        PINMUX_FUNCTION_2 
#define PTA10_CAN0_RX                         PINMUX_FUNCTION_3 
#define PTA10_MCPWM0_CH5                      PINMUX_FUNCTION_4 
#define PTA10_UART0_RX                        PINMUX_FUNCTION_5 
#define PTA10_SPI1_SCK                        PINMUX_FUNCTION_6 
#define PTA10_CAN5_RX                         PINMUX_FUNCTION_7 

/* PTA11 pinmux function definition */
#define PTA11_EXTAL32                         PINMUX_FUNCTION_0 
#define PTA11_GPIO                            PINMUX_FUNCTION_1 
#define PTA11_TIM1_CH5                        PINMUX_FUNCTION_2 
#define PTA11_CAN0_TX                         PINMUX_FUNCTION_3 
#define PTA11_MCPWM0_CH4                      PINMUX_FUNCTION_4 
#define PTA11_UART0_TX                        PINMUX_FUNCTION_5 
#define PTA11_STIM0_ALT1                      PINMUX_FUNCTION_6 
#define PTA11_CAN5_TX                         PINMUX_FUNCTION_7 

/* PTA12 pinmux function definition */
#define PTA12_GPIO                            PINMUX_FUNCTION_1 
#define PTA12_TIM1_CH6                        PINMUX_FUNCTION_2 
#define PTA12_CAN1_RX                         PINMUX_FUNCTION_3 
#define PTA12_MCPWM0_CH3                      PINMUX_FUNCTION_4 
#define PTA12_UART0_RX                        PINMUX_FUNCTION_5 
#define PTA12_TIM2_CH2                        PINMUX_FUNCTION_6 
#define PTA12_TRACE_D2                        PINMUX_FUNCTION_7 

/* PTA13 pinmux function definition */
#define PTA13_GPIO                            PINMUX_FUNCTION_1 
#define PTA13_TIM1_CH7                        PINMUX_FUNCTION_2 
#define PTA13_CAN1_TX                         PINMUX_FUNCTION_3 
#define PTA13_MCPWM0_CH2                      PINMUX_FUNCTION_4 
#define PTA13_UART0_TX                        PINMUX_FUNCTION_5 
#define PTA13_TIM2_CH3                        PINMUX_FUNCTION_6 
#define PTA13_TRACE_D1                        PINMUX_FUNCTION_7 

/* PTA14 pinmux function definition */
#define PTA14_GPIO                            PINMUX_FUNCTION_1 
#define PTA14_TIM0_FLT0                       PINMUX_FUNCTION_2 
#define PTA14_TIM3_FLT1                       PINMUX_FUNCTION_3 
#define PTA14_EWDT_IN                         PINMUX_FUNCTION_4 
#define PTA14_TIM1_FLT0                       PINMUX_FUNCTION_6 

/* PTA15 pinmux function definition */
#define PTA15_ADC1_CH12                       PINMUX_FUNCTION_0 
#define PTA15_GPIO                            PINMUX_FUNCTION_1 
#define PTA15_TIM1_CH2                        PINMUX_FUNCTION_2 
#define PTA15_SPI3_PCS0                       PINMUX_FUNCTION_5 
#define PTA15_I2S0_SCLK                       PINMUX_FUNCTION_7 

/* PTA16 pinmux function definition */
#define PTA16_ADC1_CH13                       PINMUX_FUNCTION_0 
#define PTA16_GPIO                            PINMUX_FUNCTION_1 
#define PTA16_TIM1_CH3                        PINMUX_FUNCTION_2 
#define PTA16_SPI3_SOUT                       PINMUX_FUNCTION_5 
#define PTA16_I2S0_WS                         PINMUX_FUNCTION_7 

/* PTA17 pinmux function definition */
#define PTA17_GPIO                            PINMUX_FUNCTION_1 
#define PTA17_TIM0_CH6                        PINMUX_FUNCTION_2 
#define PTA17_TIM3_FLT0                       PINMUX_FUNCTION_3 
#define PTA17_EWDT_OUT_b                      PINMUX_FUNCTION_4 
#define PTA17_MCPWM1_FLT0                     PINMUX_FUNCTION_5 
#define PTA17_MII_RX_CLK                      PINMUX_FUNCTION_6 
#define PTA17_I2S1_SD3                        PINMUX_FUNCTION_7 

/* PTA25 pinmux function definition */
#define PTA25_GPIO                            PINMUX_FUNCTION_1 
#define PTA25_TIM3_CH0                        PINMUX_FUNCTION_5 
#define PTA25_CAN6_RX                         PINMUX_FUNCTION_6 

/* PTA26 pinmux function definition */
#define PTA26_GPIO                            PINMUX_FUNCTION_1 
#define PTA26_SPI1_PCS0                       PINMUX_FUNCTION_3 
#define PTA26_SPI0_PCS0                       PINMUX_FUNCTION_4 

/* PTA27 pinmux function definition */
#define PTA27_GPIO                            PINMUX_FUNCTION_1 
#define PTA27_SPI1_SOUT                       PINMUX_FUNCTION_3 
#define PTA27_UART0_TX                        PINMUX_FUNCTION_4 
#define PTA27_CAN0_TX                         PINMUX_FUNCTION_5 

/* PTA28 pinmux function definition */
#define PTA28_GPIO                            PINMUX_FUNCTION_1 
#define PTA28_SPI1_SCK                        PINMUX_FUNCTION_3 
#define PTA28_UART0_RX                        PINMUX_FUNCTION_4 
#define PTA28_CAN0_RX                         PINMUX_FUNCTION_5 

/* PTA29 pinmux function definition */
#define PTA29_GPIO                            PINMUX_FUNCTION_1 
#define PTA29_CAN6_TX                         PINMUX_FUNCTION_2 
#define PTA29_UART2_TX                        PINMUX_FUNCTION_4 
#define PTA29_SPI1_SIN                        PINMUX_FUNCTION_5 

/* PTA30 pinmux function definition */
#define PTA30_GPIO                            PINMUX_FUNCTION_1 
#define PTA30_CAN6_RX                         PINMUX_FUNCTION_2 
#define PTA30_UART2_RX                        PINMUX_FUNCTION_3 
#define PTA30_SPI0_SOUT                       PINMUX_FUNCTION_4 

/* PTA31 pinmux function definition */
#define PTA31_GPIO                            PINMUX_FUNCTION_1 
#define PTA31_SPI0_PCS1                       PINMUX_FUNCTION_4 

/* PTB0 pinmux function definition */
#define PTB0_ADC0_CH4                         PINMUX_FUNCTION_0 
#define PTB0_ADC1_CH14                        PINMUX_FUNCTION_0 
#define PTB0_GPIO                             PINMUX_FUNCTION_1 
#define PTB0_UART0_RX                         PINMUX_FUNCTION_2 
#define PTB0_SPI0_PCS0                        PINMUX_FUNCTION_3 
#define PTB0_STIM0_ALT3                       PINMUX_FUNCTION_4 
#define PTB0_CAN0_RX                          PINMUX_FUNCTION_5 
#define PTB0_MCPWM0_CH4                       PINMUX_FUNCTION_6 

/* PTB1 pinmux function definition */
#define PTB1_ADC0_CH5                         PINMUX_FUNCTION_0 
#define PTB1_ADC0_N_CH2                       PINMUX_FUNCTION_0 
#define PTB1_ADC1_CH15                        PINMUX_FUNCTION_0 
#define PTB1_GPIO                             PINMUX_FUNCTION_1 
#define PTB1_UART0_TX                         PINMUX_FUNCTION_2 
#define PTB1_SPI0_SOUT                        PINMUX_FUNCTION_3 
#define PTB1_TCLK0                            PINMUX_FUNCTION_4 
#define PTB1_CAN0_TX                          PINMUX_FUNCTION_5 
#define PTB1_MCPWM0_CH2                       PINMUX_FUNCTION_6 

/* PTB2 pinmux function definition */
#define PTB2_ADC0_CH6                         PINMUX_FUNCTION_0 
#define PTB2_GPIO                             PINMUX_FUNCTION_1 
#define PTB2_TIM1_CH0                         PINMUX_FUNCTION_2 
#define PTB2_SPI0_SCK                         PINMUX_FUNCTION_3 
#define PTB2_CAN2_RX                          PINMUX_FUNCTION_4 
#define PTB2_MCPWM1_FLT3                      PINMUX_FUNCTION_5 
#define PTB2_TMU_IN3                          PINMUX_FUNCTION_6 

/* PTB3 pinmux function definition */
#define PTB3_ADC0_CH7                         PINMUX_FUNCTION_0 
#define PTB3_GPIO                             PINMUX_FUNCTION_1 
#define PTB3_TIM1_CH1                         PINMUX_FUNCTION_2 
#define PTB3_SPI0_SIN                         PINMUX_FUNCTION_3 
#define PTB3_CAN2_TX                          PINMUX_FUNCTION_4 
#define PTB3_MCPWM1_FLT2                      PINMUX_FUNCTION_5 
#define PTB3_TMU_IN2                          PINMUX_FUNCTION_6 

/* PTB4 pinmux function definition */
#define PTB4_GPIO                             PINMUX_FUNCTION_1 
#define PTB4_TIM0_CH4                         PINMUX_FUNCTION_2 
#define PTB4_SPI0_SOUT                        PINMUX_FUNCTION_3 
#define PTB4_MCPWM1_CH2                       PINMUX_FUNCTION_5 
#define PTB4_TMU_IN1                          PINMUX_FUNCTION_6 
#define PTB4_CLKOUT                           PINMUX_FUNCTION_7 

/* PTB5 pinmux function definition */
#define PTB5_GPIO                             PINMUX_FUNCTION_1 
#define PTB5_TIM0_CH5                         PINMUX_FUNCTION_2 
#define PTB5_SPI0_PCS1                        PINMUX_FUNCTION_3 
#define PTB5_SPI0_PCS0                        PINMUX_FUNCTION_4 
#define PTB5_MCPWM1_CH1                       PINMUX_FUNCTION_5 
#define PTB5_TMU_IN0                          PINMUX_FUNCTION_6 
#define PTB5_EWDT_OUT_b                       PINMUX_FUNCTION_7 

/* PTB6 pinmux function definition */
#define PTB6_XTAL                             PINMUX_FUNCTION_0 
#define PTB6_GPIO                             PINMUX_FUNCTION_1 
#define PTB6_I2C0_SDA                         PINMUX_FUNCTION_2 
#define PTB6_UART5_RX                         PINMUX_FUNCTION_3 

/* PTB7 pinmux function definition */
#define PTB7_EXTAL                            PINMUX_FUNCTION_0 
#define PTB7_GPIO                             PINMUX_FUNCTION_1 
#define PTB7_I2C0_SCL                         PINMUX_FUNCTION_2 
#define PTB7_UART5_TX                         PINMUX_FUNCTION_3 

/* PTB8 pinmux function definition */
#define PTB8_GPIO                             PINMUX_FUNCTION_1 
#define PTB8_TIM3_CH0                         PINMUX_FUNCTION_2 
#define PTB8_SPI3_SCK                         PINMUX_FUNCTION_5 
#define PTB8_I2S0_SD3                         PINMUX_FUNCTION_7 

/* PTB9 pinmux function definition */
#define PTB9_GPIO                             PINMUX_FUNCTION_1 
#define PTB9_TIM3_CH1                         PINMUX_FUNCTION_2 
#define PTB9_I2C0_SCL                         PINMUX_FUNCTION_3 
#define PTB9_SPI3_SIN                         PINMUX_FUNCTION_5 
#define PTB9_I2S0_SD2                         PINMUX_FUNCTION_7 

/* PTB10 pinmux function definition */
#define PTB10_GPIO                            PINMUX_FUNCTION_1 
#define PTB10_TIM3_CH2                        PINMUX_FUNCTION_2 
#define PTB10_I2C0_SDA                        PINMUX_FUNCTION_3 
#define PTB10_CAN6_TX                         PINMUX_FUNCTION_4 
#define PTB10_SPI3_SOUT                       PINMUX_FUNCTION_5 
#define PTB10_I2S0_SD1                        PINMUX_FUNCTION_7 

/* PTB11 pinmux function definition */
#define PTB11_GPIO                            PINMUX_FUNCTION_1 
#define PTB11_TIM3_CH3                        PINMUX_FUNCTION_2 
#define PTB11_CAN6_RX                         PINMUX_FUNCTION_4 
#define PTB11_SPI3_PCS0                       PINMUX_FUNCTION_5 
#define PTB11_I2S0_SD0                        PINMUX_FUNCTION_7 

/* PTB12 pinmux function definition */
#define PTB12_ADC1_CH7                        PINMUX_FUNCTION_0 
#define PTB12_GPIO                            PINMUX_FUNCTION_1 
#define PTB12_TIM0_CH0                        PINMUX_FUNCTION_2 
#define PTB12_TIM3_FLT1                       PINMUX_FUNCTION_3 
#define PTB12_CAN5_TX                         PINMUX_FUNCTION_4 
#define PTB12_I2C1_SCL                        PINMUX_FUNCTION_5 
#define PTB12_UART5_RX                        PINMUX_FUNCTION_6 

/* PTB13 pinmux function definition */
#define PTB13_ADC1_CH8                        PINMUX_FUNCTION_0 
#define PTB13_ADC0_CH8                        PINMUX_FUNCTION_0 
#define PTB13_GPIO                            PINMUX_FUNCTION_1 
#define PTB13_TIM0_CH1                        PINMUX_FUNCTION_2 
#define PTB13_TIM0_FLT1                       PINMUX_FUNCTION_3 
#define PTB13_CAN1_TX                         PINMUX_FUNCTION_4 
#define PTB13_I2C1_SDA                        PINMUX_FUNCTION_5 
#define PTB13_CAN2_TX                         PINMUX_FUNCTION_6 

/* PTB14 pinmux function definition */
#define PTB14_ADC1_CH9                        PINMUX_FUNCTION_0 
#define PTB14_ADC0_CH9                        PINMUX_FUNCTION_0 
#define PTB14_GPIO                            PINMUX_FUNCTION_1 
#define PTB14_TIM0_CH2                        PINMUX_FUNCTION_2 
#define PTB14_SPI1_SCK                        PINMUX_FUNCTION_3 
#define PTB14_UART5_TX                        PINMUX_FUNCTION_6 
#define PTB14_I2S1_SCLK                       PINMUX_FUNCTION_7 

/* PTB15 pinmux function definition */
#define PTB15_ADC1_CH14                       PINMUX_FUNCTION_0 
#define PTB15_GPIO                            PINMUX_FUNCTION_1 
#define PTB15_TIM0_CH3                        PINMUX_FUNCTION_2 
#define PTB15_SPI1_SIN                        PINMUX_FUNCTION_3 
#define PTB15_CAN3_TX                         PINMUX_FUNCTION_4 
#define PTB15_MII_TXER                        PINMUX_FUNCTION_5 
#define PTB15_UART5_RX                        PINMUX_FUNCTION_6 
#define PTB15_I2S1_SD0                        PINMUX_FUNCTION_7 

/* PTB16 pinmux function definition */
#define PTB16_ADC1_CH15                       PINMUX_FUNCTION_0 
#define PTB16_GPIO                            PINMUX_FUNCTION_1 
#define PTB16_TIM0_CH4                        PINMUX_FUNCTION_2 
#define PTB16_SPI1_SOUT                       PINMUX_FUNCTION_3 
#define PTB16_CAN3_RX                         PINMUX_FUNCTION_4 
#define PTB16_UART4_TX                        PINMUX_FUNCTION_5 
#define PTB16_MII_RMII_MDC                    PINMUX_FUNCTION_6 
#define PTB16_I2S1_SD1                        PINMUX_FUNCTION_7 

/* PTB17 pinmux function definition */
#define PTB17_GPIO                            PINMUX_FUNCTION_1 
#define PTB17_TIM0_CH5                        PINMUX_FUNCTION_2 
#define PTB17_SPI1_PCS0                       PINMUX_FUNCTION_3 
#define PTB17_MCPWM1_FLT1                     PINMUX_FUNCTION_4 
#define PTB17_UART4_RX                        PINMUX_FUNCTION_5 
#define PTB17_MII_RMII_MDIO                   PINMUX_FUNCTION_6 
#define PTB17_I2S1_SD2                        PINMUX_FUNCTION_7 

/* PTB18 pinmux function definition */
#define PTB18_ADC0_CH16                       PINMUX_FUNCTION_0 
#define PTB18_GPIO                            PINMUX_FUNCTION_1 
#define PTB18_SPI1_PCS1                       PINMUX_FUNCTION_4 
#define PTB18_SPI3_PCS0                       PINMUX_FUNCTION_5 
#define PTB18_TIM2_FLT1                       PINMUX_FUNCTION_6 

/* PTB20 pinmux function definition */
#define PTB20_ADC0_CH17                       PINMUX_FUNCTION_0 
#define PTB20_GPIO                            PINMUX_FUNCTION_1 
#define PTB20_UART4_TX                        PINMUX_FUNCTION_2 
#define PTB20_SPI3_SOUT                       PINMUX_FUNCTION_5 
#define PTB20_TIM2_CH2                        PINMUX_FUNCTION_6 

/* PTB21 pinmux function definition */
#define PTB21_ADC0_CH18                       PINMUX_FUNCTION_0 
#define PTB21_GPIO                            PINMUX_FUNCTION_1 
#define PTB21_UART4_RX                        PINMUX_FUNCTION_2 
#define PTB21_SPI3_SIN                        PINMUX_FUNCTION_5 
#define PTB21_TIM2_CH3                        PINMUX_FUNCTION_6 

/* PTB22 pinmux function definition */
#define PTB22_ADC0_CH19                       PINMUX_FUNCTION_0 
#define PTB22_GPIO                            PINMUX_FUNCTION_1 
#define PTB22_UART1_TX                        PINMUX_FUNCTION_5 

/* PTB23 pinmux function definition */
#define PTB23_GPIO                            PINMUX_FUNCTION_1 
#define PTB23_UART1_RX                        PINMUX_FUNCTION_3 

/* PTB25 pinmux function definition */
#define PTB25_GPIO                            PINMUX_FUNCTION_1 
#define PTB25_SPI2_PCS0                       PINMUX_FUNCTION_5 

/* PTB27 pinmux function definition */
#define PTB27_GPIO                            PINMUX_FUNCTION_1 
#define PTB27_CAN7_RX                         PINMUX_FUNCTION_3 
#define PTB27_SPI2_SOUT                       PINMUX_FUNCTION_5 

/* PTB28 pinmux function definition */
#define PTB28_GPIO                            PINMUX_FUNCTION_1 
#define PTB28_CAN7_TX                         PINMUX_FUNCTION_3 
#define PTB28_SPI2_SIN                        PINMUX_FUNCTION_5 

/* PTB29 pinmux function definition */
#define PTB29_GPIO                            PINMUX_FUNCTION_1 
#define PTB29_SPI2_SCK                        PINMUX_FUNCTION_5 

/* PTC0 pinmux function definition */
#define PTC0_ADC0_CH8                         PINMUX_FUNCTION_0 
#define PTC0_GPIO                             PINMUX_FUNCTION_1 
#define PTC0_TIM0_CH0                         PINMUX_FUNCTION_2 
#define PTC0_SPI2_SIN                         PINMUX_FUNCTION_3 
#define PTC0_CAN4_RX                          PINMUX_FUNCTION_4 
#define PTC0_UART2_RX                         PINMUX_FUNCTION_5 
#define PTC0_TIM1_CH6                         PINMUX_FUNCTION_6 

/* PTC1 pinmux function definition */
#define PTC1_ADC0_CH9                         PINMUX_FUNCTION_0 
#define PTC1_GPIO                             PINMUX_FUNCTION_1 
#define PTC1_TIM0_CH1                         PINMUX_FUNCTION_2 
#define PTC1_SPI2_SOUT                        PINMUX_FUNCTION_3 
#define PTC1_CAN4_TX                          PINMUX_FUNCTION_4 
#define PTC1_UART2_TX                         PINMUX_FUNCTION_5 
#define PTC1_TIM1_CH7                         PINMUX_FUNCTION_6 

/* PTC2 pinmux function definition */
#define PTC2_ADC0_CH10                        PINMUX_FUNCTION_0 
#define PTC2_CMP0_IN5                         PINMUX_FUNCTION_0 
#define PTC2_GPIO                             PINMUX_FUNCTION_1 
#define PTC2_TIM0_CH2                         PINMUX_FUNCTION_2 
#define PTC2_CAN0_RX                          PINMUX_FUNCTION_3 
#define PTC2_UART0_RX                         PINMUX_FUNCTION_4 
#define PTC2_SPI2_PCS1                        PINMUX_FUNCTION_6 

/* PTC3 pinmux function definition */
#define PTC3_ADC0_CH11                        PINMUX_FUNCTION_0 
#define PTC3_CMP0_IN4                         PINMUX_FUNCTION_0 
#define PTC3_GPIO                             PINMUX_FUNCTION_1 
#define PTC3_TIM0_CH3                         PINMUX_FUNCTION_2 
#define PTC3_CAN0_TX                          PINMUX_FUNCTION_3 
#define PTC3_UART0_TX                         PINMUX_FUNCTION_4 
#define PTC3_MCPWM1_CH3                       PINMUX_FUNCTION_5 

/* PTC4 pinmux function definition */
#define PTC4_CMP0_IN2                         PINMUX_FUNCTION_0 
#define PTC4_GPIO                             PINMUX_FUNCTION_1 
#define PTC4_TIM1_CH0                         PINMUX_FUNCTION_2 
#define PTC4_RTC_CLKOUT                       PINMUX_FUNCTION_3 
#define PTC4_EWDT_IN                          PINMUX_FUNCTION_5 
#define PTC4_JTAG_TCLK                        PINMUX_FUNCTION_7 
#define PTC4_SWD_CLK                          PINMUX_FUNCTION_7 

/* PTC5 pinmux function definition */
#define PTC5_GPIO                             PINMUX_FUNCTION_1 
#define PTC5_TIM2_CH0                         PINMUX_FUNCTION_2 
#define PTC5_RTC_CLKOUT                       PINMUX_FUNCTION_3 
#define PTC5_TIM2_CH6                         PINMUX_FUNCTION_4 
#define PTC5_SPI1_SIN                         PINMUX_FUNCTION_5 
#define PTC5_JTAG_TDI                         PINMUX_FUNCTION_7 

/* PTC6 pinmux function definition */
#define PTC6_ADC1_CH4                         PINMUX_FUNCTION_0 
#define PTC6_GPIO                             PINMUX_FUNCTION_1 
#define PTC6_UART1_RX                         PINMUX_FUNCTION_2 
#define PTC6_CAN1_RX                          PINMUX_FUNCTION_3 
#define PTC6_TIM0_CH2                         PINMUX_FUNCTION_4 
#define PTC6_MCPWM0_CH7                       PINMUX_FUNCTION_5 
#define PTC6_TIM3_CH2                         PINMUX_FUNCTION_6 

/* PTC7 pinmux function definition */
#define PTC7_ADC1_CH5                         PINMUX_FUNCTION_0 
#define PTC7_ADC1_N_CH2                       PINMUX_FUNCTION_0 
#define PTC7_GPIO                             PINMUX_FUNCTION_1 
#define PTC7_UART1_TX                         PINMUX_FUNCTION_2 
#define PTC7_CAN1_TX                          PINMUX_FUNCTION_3 
#define PTC7_TIM0_CH3                         PINMUX_FUNCTION_4 
#define PTC7_MCPWM0_CH6                       PINMUX_FUNCTION_5 
#define PTC7_TIM3_CH3                         PINMUX_FUNCTION_6 

/* PTC8 pinmux function definition */
#define PTC8_GPIO                             PINMUX_FUNCTION_1 
#define PTC8_UART1_RX                         PINMUX_FUNCTION_2 
#define PTC8_TIM1_FLT0                        PINMUX_FUNCTION_3 
#define PTC8_MCPWM1_CH6                       PINMUX_FUNCTION_4 
#define PTC8_CAN1_RX                          PINMUX_FUNCTION_5 
#define PTC8_UART0_CTS                        PINMUX_FUNCTION_6 
#define PTC8_CAN4_RX                          PINMUX_FUNCTION_7 

/* PTC9 pinmux function definition */
#define PTC9_GPIO                             PINMUX_FUNCTION_1 
#define PTC9_UART1_TX                         PINMUX_FUNCTION_2 
#define PTC9_TIM1_FLT1                        PINMUX_FUNCTION_3 
#define PTC9_MCPWM1_CH7                       PINMUX_FUNCTION_4 
#define PTC9_CAN1_TX                          PINMUX_FUNCTION_5 
#define PTC9_UART0_RTS                        PINMUX_FUNCTION_6 
#define PTC9_CAN4_TX                          PINMUX_FUNCTION_7 

/* PTC10 pinmux function definition */
#define PTC10_GPIO                            PINMUX_FUNCTION_1 
#define PTC10_TIM3_CH4                        PINMUX_FUNCTION_2 
#define PTC10_MCPWM1_FLT2                     PINMUX_FUNCTION_4 
#define PTC10_CAN7_RX                         PINMUX_FUNCTION_5 
#define PTC10_TMU_IN11                        PINMUX_FUNCTION_6 
#define PTC10_MII_RMII_RXDV                   PINMUX_FUNCTION_7 

/* PTC11 pinmux function definition */
#define PTC11_GPIO                            PINMUX_FUNCTION_1 
#define PTC11_TIM3_CH5                        PINMUX_FUNCTION_2 
#define PTC11_MCPWM1_FLT3                     PINMUX_FUNCTION_4 
#define PTC11_CAN7_TX                         PINMUX_FUNCTION_5 
#define PTC11_TMU_IN10                        PINMUX_FUNCTION_6 
#define PTC11_MII_RMII_RXER                   PINMUX_FUNCTION_7 

/* PTC12 pinmux function definition */
#define PTC12_GPIO                            PINMUX_FUNCTION_1 
#define PTC12_TIM3_CH6                        PINMUX_FUNCTION_2 
#define PTC12_TIM2_CH6                        PINMUX_FUNCTION_3 
#define PTC12_UART2_CTS                       PINMUX_FUNCTION_4 
#define PTC12_MII_CRS                         PINMUX_FUNCTION_7 

/* PTC13 pinmux function definition */
#define PTC13_GPIO                            PINMUX_FUNCTION_1 
#define PTC13_TIM3_CH7                        PINMUX_FUNCTION_2 
#define PTC13_TIM2_CH7                        PINMUX_FUNCTION_3 
#define PTC13_UART2_RTS                       PINMUX_FUNCTION_4 
#define PTC13_MII_COL                         PINMUX_FUNCTION_7 

/* PTC14 pinmux function definition */
#define PTC14_ADC0_CH12                       PINMUX_FUNCTION_0 
#define PTC14_GPIO                            PINMUX_FUNCTION_1 
#define PTC14_TIM1_CH2                        PINMUX_FUNCTION_2 
#define PTC14_SPI2_PCS0                       PINMUX_FUNCTION_3 
#define PTC14_UART3_RX                        PINMUX_FUNCTION_4 
#define PTC14_SPI0_PCS0                       PINMUX_FUNCTION_5 
#define PTC14_TMU_IN9                         PINMUX_FUNCTION_6 
#define PTC14_MCPWM1_FLT1                     PINMUX_FUNCTION_7 

/* PTC15 pinmux function definition */
#define PTC15_ADC0_CH13                       PINMUX_FUNCTION_0 
#define PTC15_GPIO                            PINMUX_FUNCTION_1 
#define PTC15_TIM1_CH3                        PINMUX_FUNCTION_2 
#define PTC15_SPI2_SCK                        PINMUX_FUNCTION_3 
#define PTC15_UART3_TX                        PINMUX_FUNCTION_4 
#define PTC15_SPI0_SOUT                       PINMUX_FUNCTION_5 
#define PTC15_TMU_IN8                         PINMUX_FUNCTION_6 
#define PTC15_MCPWM1_FLT0                     PINMUX_FUNCTION_7 

/* PTC16 pinmux function definition */
#define PTC16_ADC0_CH14                       PINMUX_FUNCTION_0 
#define PTC16_GPIO                            PINMUX_FUNCTION_1 
#define PTC16_TIM1_CH4                        PINMUX_FUNCTION_2 
#define PTC16_CAN0_RX                         PINMUX_FUNCTION_3 
#define PTC16_SPI0_SCK                        PINMUX_FUNCTION_4 
#define PTC16_TIM0_CH0                        PINMUX_FUNCTION_5 
#define PTC16_MCPWM1_CH7                      PINMUX_FUNCTION_7 

/* PTC17 pinmux function definition */
#define PTC17_ADC0_CH15                       PINMUX_FUNCTION_0 
#define PTC17_GPIO                            PINMUX_FUNCTION_1 
#define PTC17_TIM1_CH5                        PINMUX_FUNCTION_2 
#define PTC17_CAN0_TX                         PINMUX_FUNCTION_3 
#define PTC17_SPI0_SIN                        PINMUX_FUNCTION_4 
#define PTC17_TIM0_CH1                        PINMUX_FUNCTION_5 
#define PTC17_SPI2_SIN                        PINMUX_FUNCTION_6 
#define PTC17_MCPWM1_CH6                      PINMUX_FUNCTION_7 

/* PTC19 pinmux function definition */
#define PTC19_GPIO                            PINMUX_FUNCTION_1 
#define PTC19_SPI2_PCS1                       PINMUX_FUNCTION_6 

/* PTC23 pinmux function definition */
#define PTC23_GPIO                            PINMUX_FUNCTION_1 
#define PTC23_SPI0_SCK                        PINMUX_FUNCTION_2 

/* PTC27 pinmux function definition */
#define PTC27_GPIO                            PINMUX_FUNCTION_1 

/* PTC28 pinmux function definition */
#define PTC28_GPIO                            PINMUX_FUNCTION_1 

/* PTC29 pinmux function definition */
#define PTC29_GPIO                            PINMUX_FUNCTION_1 
#define PTC29_I2C0_SCL                        PINMUX_FUNCTION_4 

/* PTC30 pinmux function definition */
#define PTC30_GPIO                            PINMUX_FUNCTION_1 
#define PTC30_MCPWM1_CH3                      PINMUX_FUNCTION_4 

/* PTC31 pinmux function definition */
#define PTC31_GPIO                            PINMUX_FUNCTION_1 
#define PTC31_I2C0_SDA                        PINMUX_FUNCTION_4 

/* PTD0 pinmux function definition */
#define PTD0_CMP0_IN11                        PINMUX_FUNCTION_0 
#define PTD0_GPIO                             PINMUX_FUNCTION_1 
#define PTD0_TIM0_CH2                         PINMUX_FUNCTION_2 
#define PTD0_SPI1_SCK                         PINMUX_FUNCTION_3 
#define PTD0_TIM2_CH5                         PINMUX_FUNCTION_4 
#define PTD0_MCPWM0_FLT1                      PINMUX_FUNCTION_5 
#define PTD0_TMU_OUT1                         PINMUX_FUNCTION_6 
#define PTD0_EOUT0                            PINMUX_FUNCTION_7 

/* PTD1 pinmux function definition */
#define PTD1_CMP0_IN10                        PINMUX_FUNCTION_0 
#define PTD1_GPIO                             PINMUX_FUNCTION_1 
#define PTD1_TIM0_CH3                         PINMUX_FUNCTION_2 
#define PTD1_SPI1_SIN                         PINMUX_FUNCTION_3 
#define PTD1_TIM2_CH1                         PINMUX_FUNCTION_4 
#define PTD1_MCPWM0_FLT0                      PINMUX_FUNCTION_5 
#define PTD1_CAN0_TX                          PINMUX_FUNCTION_6 
#define PTD1_TMU_OUT2                         PINMUX_FUNCTION_7 

/* PTD2 pinmux function definition */
#define PTD2_ADC1_CH2                         PINMUX_FUNCTION_0 
#define PTD2_GPIO                             PINMUX_FUNCTION_1 
#define PTD2_TIM3_CH4                         PINMUX_FUNCTION_2 
#define PTD2_SPI1_SOUT                        PINMUX_FUNCTION_3 
#define PTD2_CAN5_RX                          PINMUX_FUNCTION_4 
#define PTD2_UART1_RX                         PINMUX_FUNCTION_5 
#define PTD2_TMU_IN5                          PINMUX_FUNCTION_6 

/* PTD3 pinmux function definition */
#define PTD3_ADC1_CH3                         PINMUX_FUNCTION_0 
#define PTD3_ADC1_N_CH1                       PINMUX_FUNCTION_0 
#define PTD3_GPIO                             PINMUX_FUNCTION_1 
#define PTD3_TIM3_CH5                         PINMUX_FUNCTION_2 
#define PTD3_SPI1_PCS0                        PINMUX_FUNCTION_3 
#define PTD3_CAN1_RX                          PINMUX_FUNCTION_4 
#define PTD3_UART1_TX                         PINMUX_FUNCTION_5 
#define PTD3_TMU_IN4                          PINMUX_FUNCTION_6 
#define PTD3_NMI_b                            PINMUX_FUNCTION_7 

/* PTD4 pinmux function definition */
#define PTD4_ADC1_CH6                         PINMUX_FUNCTION_0 
#define PTD4_GPIO                             PINMUX_FUNCTION_1 
#define PTD4_TIM0_CH2                         PINMUX_FUNCTION_2 
#define PTD4_TIM1_CH0                         PINMUX_FUNCTION_3 
#define PTD4_TIM2_FLT1                        PINMUX_FUNCTION_4 
#define PTD4_CAN2_RX                          PINMUX_FUNCTION_6 
#define PTD4_I2S1_WS                          PINMUX_FUNCTION_7 

/* PTD5 pinmux function definition */
#define PTD5_GPIO                             PINMUX_FUNCTION_1 
#define PTD5_TIM2_CH3                         PINMUX_FUNCTION_2 
#define PTD5_STIM0_ALT2                       PINMUX_FUNCTION_3 
#define PTD5_TIM2_FLT1                        PINMUX_FUNCTION_4 
#define PTD5_UART2_RX                         PINMUX_FUNCTION_5 
#define PTD5_TMU_IN7                          PINMUX_FUNCTION_6 

/* PTD6 pinmux function definition */
#define PTD6_CMP0_IN7                         PINMUX_FUNCTION_0 
#define PTD6_GPIO                             PINMUX_FUNCTION_1 
#define PTD6_UART2_RX                         PINMUX_FUNCTION_2 
#define PTD6_CAN3_RX                          PINMUX_FUNCTION_3 
#define PTD6_RTC_CLKOUT                       PINMUX_FUNCTION_4 
#define PTD6_TIM0_CH6                         PINMUX_FUNCTION_5 
#define PTD6_MCPWM1_CH5                       PINMUX_FUNCTION_7 

/* PTD7 pinmux function definition */
#define PTD7_CMP0_IN6                         PINMUX_FUNCTION_0 
#define PTD7_GPIO                             PINMUX_FUNCTION_1 
#define PTD7_UART2_TX                         PINMUX_FUNCTION_2 
#define PTD7_CAN3_TX                          PINMUX_FUNCTION_3 
#define PTD7_TIM0_CH7                         PINMUX_FUNCTION_5 
#define PTD7_TIM0_CH0                         PINMUX_FUNCTION_6 
#define PTD7_MCPWM1_CH4                       PINMUX_FUNCTION_7 

/* PTD8 pinmux function definition */
#define PTD8_GPIO                             PINMUX_FUNCTION_1 
#define PTD8_CAN6_RX                          PINMUX_FUNCTION_3 
#define PTD8_SPI3_PCS1                        PINMUX_FUNCTION_5 
#define PTD8_TIM1_CH4                         PINMUX_FUNCTION_6 
#define PTD8_MII_RMII_RXD0                    PINMUX_FUNCTION_7 

/* PTD9 pinmux function definition */
#define PTD9_GPIO                             PINMUX_FUNCTION_1 
#define PTD9_CAN6_TX                          PINMUX_FUNCTION_3 
#define PTD9_I2S0_SD3                         PINMUX_FUNCTION_4 
#define PTD9_SPI3_SCK                         PINMUX_FUNCTION_5 
#define PTD9_TIM1_CH5                         PINMUX_FUNCTION_6 
#define PTD9_MII_RMII_RXD1                    PINMUX_FUNCTION_7 

/* PTD10 pinmux function definition */
#define PTD10_GPIO                            PINMUX_FUNCTION_1 
#define PTD10_TIM2_CH0                        PINMUX_FUNCTION_2 
#define PTD10_I2S0_SD2                        PINMUX_FUNCTION_4 
#define PTD10_SPI3_SIN                        PINMUX_FUNCTION_5 
#define PTD10_CLKOUT                          PINMUX_FUNCTION_6 
#define PTD10_MII_RMII_RXD2                   PINMUX_FUNCTION_7 

/* PTD11 pinmux function definition */
#define PTD11_CMP0_IN12                       PINMUX_FUNCTION_0 
#define PTD11_GPIO                            PINMUX_FUNCTION_1 
#define PTD11_TIM2_CH1                        PINMUX_FUNCTION_2 
#define PTD11_CAN5_RX                         PINMUX_FUNCTION_3 
#define PTD11_I2S0_SD1                        PINMUX_FUNCTION_4 
#define PTD11_SPI3_SOUT                       PINMUX_FUNCTION_5 
#define PTD11_UART2_CTS                       PINMUX_FUNCTION_6 
#define PTD11_MII_RMII_RXD3                   PINMUX_FUNCTION_7 

/* PTD12 pinmux function definition */
#define PTD12_GPIO                            PINMUX_FUNCTION_1 
#define PTD12_TIM2_CH2                        PINMUX_FUNCTION_2 
#define PTD12_CAN5_TX                         PINMUX_FUNCTION_3 
#define PTD12_I2S0_SD0                        PINMUX_FUNCTION_4 
#define PTD12_SPI3_PCS0                       PINMUX_FUNCTION_5 
#define PTD12_UART2_RTS                       PINMUX_FUNCTION_6 
#define PTD12_MII_RMII_TXCLK                  PINMUX_FUNCTION_7 

/* PTD13 pinmux function definition */
#define PTD13_GPIO                            PINMUX_FUNCTION_1 
#define PTD13_TIM2_CH4                        PINMUX_FUNCTION_2 
#define PTD13_UART1_RX                        PINMUX_FUNCTION_3 
#define PTD13_I2S0_SCLK                       PINMUX_FUNCTION_4 
#define PTD13_SPI3_SCK                        PINMUX_FUNCTION_5 
#define PTD13_MII_RMII_TXEN                   PINMUX_FUNCTION_6 
#define PTD13_RTC_CLKOUT                      PINMUX_FUNCTION_7 

/* PTD14 pinmux function definition */
#define PTD14_GPIO                            PINMUX_FUNCTION_1 
#define PTD14_TIM2_CH5                        PINMUX_FUNCTION_2 
#define PTD14_UART1_TX                        PINMUX_FUNCTION_3 
#define PTD14_I2S0_WS                         PINMUX_FUNCTION_4 
#define PTD14_MII_RMII_TXD0                   PINMUX_FUNCTION_6 
#define PTD14_CLKOUT                          PINMUX_FUNCTION_7 

/* PTD15 pinmux function definition */
#define PTD15_GPIO                            PINMUX_FUNCTION_1 
#define PTD15_TIM0_CH0                        PINMUX_FUNCTION_2 
#define PTD15_TCLK2                           PINMUX_FUNCTION_3 
#define PTD15_SPI0_SCK                        PINMUX_FUNCTION_4 
#define PTD15_CAN3_RX                         PINMUX_FUNCTION_5 
#define PTD15_TIM2_CH3                        PINMUX_FUNCTION_6 
#define PTD15_TMU_OUT1                        PINMUX_FUNCTION_7 

/* PTD16 pinmux function definition */
#define PTD16_GPIO                            PINMUX_FUNCTION_1 
#define PTD16_TIM0_CH1                        PINMUX_FUNCTION_2 
#define PTD16_CLKOUT                          PINMUX_FUNCTION_3 
#define PTD16_SPI0_SIN                        PINMUX_FUNCTION_4 
#define PTD16_CAN3_TX                         PINMUX_FUNCTION_5 
#define PTD16_TIM2_CH0                        PINMUX_FUNCTION_6 
#define PTD16_EWDT_IN                         PINMUX_FUNCTION_7 

/* PTD17 pinmux function definition */
#define PTD17_GPIO                            PINMUX_FUNCTION_1 
#define PTD17_UART2_RX                        PINMUX_FUNCTION_3 
#define PTD17_MCPWM1_FLT2                     PINMUX_FUNCTION_4 
#define PTD17_CAN4_RX                         PINMUX_FUNCTION_5 
#define PTD17_MII_RMII_TXD1                   PINMUX_FUNCTION_6 

/* PTD18 pinmux function definition */
#define PTD18_ADC1_CH16                       PINMUX_FUNCTION_0 
#define PTD18_GPIO                            PINMUX_FUNCTION_1 
#define PTD18_CAN7_TX                         PINMUX_FUNCTION_4 

/* PTD19 pinmux function definition */
#define PTD19_ADC1_CH17                       PINMUX_FUNCTION_0 
#define PTD19_GPIO                            PINMUX_FUNCTION_1 
#define PTD19_CAN7_RX                         PINMUX_FUNCTION_4 

/* PTD22 pinmux function definition */
#define PTD22_ADC1_CH18                       PINMUX_FUNCTION_0 
#define PTD22_GPIO                            PINMUX_FUNCTION_1 
#define PTD22_CAN5_RX                         PINMUX_FUNCTION_4 

/* PTD23 pinmux function definition */
#define PTD23_ADC1_CH19                       PINMUX_FUNCTION_0 
#define PTD23_GPIO                            PINMUX_FUNCTION_1 
#define PTD23_CAN5_TX                         PINMUX_FUNCTION_4 
#define PTD23_I2C1_SDA                        PINMUX_FUNCTION_5 

/* PTD24 pinmux function definition */
#define PTD24_GPIO                            PINMUX_FUNCTION_1 
#define PTD24_I2C1_SCL                        PINMUX_FUNCTION_5 

/* PTD27 pinmux function definition */
#define PTD27_GPIO                            PINMUX_FUNCTION_1 
#define PTD27_CAN3_TX                         PINMUX_FUNCTION_4 

/* PTD28 pinmux function definition */
#define PTD28_GPIO                            PINMUX_FUNCTION_1 
#define PTD28_CAN3_RX                         PINMUX_FUNCTION_4 

/* PTD29 pinmux function definition */
#define PTD29_GPIO                            PINMUX_FUNCTION_1 
#define PTD29_CAN2_TX                         PINMUX_FUNCTION_4 

/* PTD30 pinmux function definition */
#define PTD30_GPIO                            PINMUX_FUNCTION_1 
#define PTD30_CAN2_RX                         PINMUX_FUNCTION_4 

/* PTE0 pinmux function definition */
#define PTE0_GPIO                             PINMUX_FUNCTION_1 
#define PTE0_SPI0_SCK                         PINMUX_FUNCTION_2 
#define PTE0_TCLK1                            PINMUX_FUNCTION_3 
#define PTE0_UART3_RX                         PINMUX_FUNCTION_4 
#define PTE0_SPI1_SOUT                        PINMUX_FUNCTION_5 
#define PTE0_JTAG_TDO                         PINMUX_FUNCTION_7 
#define PTE0_TRACE_SWO                        PINMUX_FUNCTION_7 

/* PTE1 pinmux function definition */
#define PTE1_GPIO                             PINMUX_FUNCTION_1 
#define PTE1_SPI0_SIN                         PINMUX_FUNCTION_2 
#define PTE1_UART3_TX                         PINMUX_FUNCTION_4 
#define PTE1_SPI1_PCS0                        PINMUX_FUNCTION_5 
#define PTE1_TIM1_FLT1                        PINMUX_FUNCTION_6 
#define PTE1_TRACE_D3                         PINMUX_FUNCTION_7 

/* PTE2 pinmux function definition */
#define PTE2_ADC1_CH10                        PINMUX_FUNCTION_0 
#define PTE2_GPIO                             PINMUX_FUNCTION_1 
#define PTE2_SPI0_SOUT                        PINMUX_FUNCTION_2 
#define PTE2_MCPWM0_CH1                       PINMUX_FUNCTION_3 
#define PTE2_TIM3_CH6                         PINMUX_FUNCTION_4 
#define PTE2_UART4_TX                         PINMUX_FUNCTION_5 
#define PTE2_UART1_CTS                        PINMUX_FUNCTION_6 
#define PTE2_TRACE_D0                         PINMUX_FUNCTION_7 

/* PTE3 pinmux function definition */
#define PTE3_GPIO                             PINMUX_FUNCTION_1 
#define PTE3_TIM0_FLT0                        PINMUX_FUNCTION_2 
#define PTE3_UART2_RTS                        PINMUX_FUNCTION_3 
#define PTE3_TIM2_FLT0                        PINMUX_FUNCTION_4 
#define PTE3_SPI2_SOUT                        PINMUX_FUNCTION_5 
#define PTE3_TMU_IN6                          PINMUX_FUNCTION_6 
#define PTE3_CMP0_OUT                         PINMUX_FUNCTION_7 

/* PTE6 pinmux function definition */
#define PTE6_ADC1_CH11                        PINMUX_FUNCTION_0 
#define PTE6_GPIO                             PINMUX_FUNCTION_1 
#define PTE6_SPI0_PCS0                        PINMUX_FUNCTION_2 
#define PTE6_MCPWM0_CH0                       PINMUX_FUNCTION_3 
#define PTE6_TIM3_CH7                         PINMUX_FUNCTION_4 
#define PTE6_UART4_RX                         PINMUX_FUNCTION_5 
#define PTE6_UART1_RTS                        PINMUX_FUNCTION_6 
#define PTE6_TRACE_CLKOUT                     PINMUX_FUNCTION_7 

/* PTE7 pinmux function definition */
#define PTE7_GPIO                             PINMUX_FUNCTION_1 
#define PTE7_TIM0_CH7                         PINMUX_FUNCTION_2 
#define PTE7_TIM0_FLT0                        PINMUX_FUNCTION_3 
#define PTE7_MCPWM1_CH5                       PINMUX_FUNCTION_4 
#define PTE7_TIM3_FLT0                        PINMUX_FUNCTION_5 
#define PTE7_UART5_TX                         PINMUX_FUNCTION_6 

/* PTE8 pinmux function definition */
#define PTE8_CMP0_IN3                         PINMUX_FUNCTION_0 
#define PTE8_GPIO                             PINMUX_FUNCTION_1 
#define PTE8_TIM0_CH6                         PINMUX_FUNCTION_2 
#define PTE8_MCPWM1_CH0                       PINMUX_FUNCTION_4 
#define PTE8_TCLK2                            PINMUX_FUNCTION_5 
#define PTE8_SPI2_SCK                         PINMUX_FUNCTION_6 
#define PTE8_EWDT_IN                          PINMUX_FUNCTION_7 

/* PTE9 pinmux function definition */
#define PTE9_GPIO                             PINMUX_FUNCTION_1 
#define PTE9_TIM0_CH7                         PINMUX_FUNCTION_2 
#define PTE9_UART2_CTS                        PINMUX_FUNCTION_3 
#define PTE9_TIM2_FLT0                        PINMUX_FUNCTION_4 
#define PTE9_SPI2_PCS1                        PINMUX_FUNCTION_5 
#define PTE9_TIM2_CH2                         PINMUX_FUNCTION_6 
#define PTE9_TMU_OUT4                         PINMUX_FUNCTION_7 

/* PTE11 pinmux function definition */
#define PTE11_GPIO                            PINMUX_FUNCTION_1 
#define PTE11_SPI2_PCS0                       PINMUX_FUNCTION_2 
#define PTE11_TMU_OUT5                        PINMUX_FUNCTION_3 
#define PTE11_TIM2_CH4                        PINMUX_FUNCTION_4 
#define PTE11_MCPWM0_CH5                      PINMUX_FUNCTION_5 
#define PTE11_CAN0_RX                         PINMUX_FUNCTION_6 
#define PTE11_EOUT1                           PINMUX_FUNCTION_7 

/* PTE12 pinmux function definition */
#define PTE12_GPIO                            PINMUX_FUNCTION_1 
#define PTE12_UART2_TX                        PINMUX_FUNCTION_3 
#define PTE12_MCPWM1_FLT3                     PINMUX_FUNCTION_4 
#define PTE12_CAN4_TX                         PINMUX_FUNCTION_5 
#define PTE12_MII_RMII_TXD2                   PINMUX_FUNCTION_6 

/* PTE13 pinmux function definition */
#define PTE13_GPIO                            PINMUX_FUNCTION_1 
#define PTE13_SPI2_PCS1                       PINMUX_FUNCTION_3 
#define PTE13_TIM2_FLT0                       PINMUX_FUNCTION_4 
#define PTE13_TIM3_CH1                        PINMUX_FUNCTION_5 
#define PTE13_CAN6_TX                         PINMUX_FUNCTION_6 

/* PTE14 pinmux function definition */
#define PTE14_GPIO                            PINMUX_FUNCTION_1 
#define PTE14_TIM0_FLT1                       PINMUX_FUNCTION_2 
#define PTE14_TIM2_FLT1                       PINMUX_FUNCTION_4 
#define PTE14_MII_RMII_TXD3                   PINMUX_FUNCTION_6 

/* PTE15 pinmux function definition */
#define PTE15_CMP0_IN9                        PINMUX_FUNCTION_0 
#define PTE15_GPIO                            PINMUX_FUNCTION_1 
#define PTE15_UART1_CTS                       PINMUX_FUNCTION_2 
#define PTE15_SPI2_SCK                        PINMUX_FUNCTION_3 
#define PTE15_TIM2_CH6                        PINMUX_FUNCTION_4 
#define PTE15_UART4_RX                        PINMUX_FUNCTION_5 
#define PTE15_TMU_OUT6                        PINMUX_FUNCTION_7 

/* PTE16 pinmux function definition */
#define PTE16_CMP0_IN8                        PINMUX_FUNCTION_0 
#define PTE16_GPIO                            PINMUX_FUNCTION_1 
#define PTE16_UART1_RTS                       PINMUX_FUNCTION_2 
#define PTE16_SPI2_SIN                        PINMUX_FUNCTION_3 
#define PTE16_TIM2_CH7                        PINMUX_FUNCTION_4 
#define PTE16_UART4_TX                        PINMUX_FUNCTION_5 
#define PTE16_TMU_OUT7                        PINMUX_FUNCTION_7 

/* PTE19 pinmux function definition */
#define PTE19_GPIO                            PINMUX_FUNCTION_1 
#define PTE19_CAN4_TX                         PINMUX_FUNCTION_3 
#define PTE19_UART5_TX                        PINMUX_FUNCTION_4 
#define PTE19_I2S1_SD0                        PINMUX_FUNCTION_7 

/* PTE20 pinmux function definition */
#define PTE20_GPIO                            PINMUX_FUNCTION_1 
#define PTE20_CAN4_RX                         PINMUX_FUNCTION_3 
#define PTE20_UART5_RX                        PINMUX_FUNCTION_4 
#define PTE20_I2S1_SD1                        PINMUX_FUNCTION_7 

/* PTE21 pinmux function definition */
#define PTE21_GPIO                            PINMUX_FUNCTION_1 
#define PTE21_CAN7_TX                         PINMUX_FUNCTION_3 
#define PTE21_I2S1_SD2                        PINMUX_FUNCTION_7 

/* PTE22 pinmux function definition */
#define PTE22_GPIO                            PINMUX_FUNCTION_1 
#define PTE22_CAN7_RX                         PINMUX_FUNCTION_3 
#define PTE22_TIM0_CH7                        PINMUX_FUNCTION_6 
#define PTE22_I2S1_SD3                        PINMUX_FUNCTION_7 

/* PTE23 pinmux function definition */
#define PTE23_GPIO                            PINMUX_FUNCTION_1 
#define PTE23_TIM0_CH6                        PINMUX_FUNCTION_6 
#define PTE23_I2S1_SCLK                       PINMUX_FUNCTION_7 

/* PTE24 pinmux function definition */
#define PTE24_GPIO                            PINMUX_FUNCTION_1 
#define PTE24_CAN2_TX                         PINMUX_FUNCTION_3 
#define PTE24_UART3_TX                        PINMUX_FUNCTION_4 
#define PTE24_TIM0_CH5                        PINMUX_FUNCTION_6 
#define PTE24_I2S1_WS                         PINMUX_FUNCTION_7 

/* PTE25 pinmux function definition */
#define PTE25_GPIO                            PINMUX_FUNCTION_1 
#define PTE25_CAN2_RX                         PINMUX_FUNCTION_3 
#define PTE25_UART3_RX                        PINMUX_FUNCTION_4 
#define PTE25_TIM0_CH4                        PINMUX_FUNCTION_6 
/** @} end of group PORT_Pinmux */

/** @defgroup PORT_Public_FunctionDeclaration
 *  @brief PORT functions declaration
 *  @{
 */
/**
 *  @brief port a-e,gpio 0-31 callback function type
 */
typedef void (*port_cb_t)(PORT_Id_t portId, PORT_GpioNum_t gpioNum);

/****************************************************************************//**
 * @brief       Configure pins with the same global configuration
 * If a pin is locked, global control will not work on it
 *
 * @param[in]  portId:        Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                            PORT_D,PORT_E.
 * @param[in]   pins:        Select the GPIO pins.
 * @param[in]  value:        Set GPIO pin global value.
 *
 * @return none.
 *
 */
void PORT_GlobalPinsConfig(PORT_Id_t portId, uint32_t pins, uint32_t value);

/**
 * @brief       Initialize seleted pin with the given configuration structure.
 *
 *
 * @param[in]  portId:     Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                         PORT_D,PORT_E.
 * @param[in]  gpioNum:     Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  pinConfig:  Pin configuration struct.
 *
 * @return none.
 *
 */
void PORT_PinInit(PORT_Id_t portId, PORT_GpioNum_t gpioNum,
                  const PORT_PinConfig_t* pinConfig);

/**
 * @brief       Configure the pin mux function.
 *
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNum:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  pinMuxFunc:  Pin mux function.
 *
 * @return none.
 *
 */
void PORT_PinmuxConfig(PORT_Id_t portId, PORT_GpioNum_t gpioNum,
                       PORT_PinMuxFunc_t pinMuxFunc);

/**
 * @brief       Configure the pin interrupt configuration.
 *
 *
 * @param[in]  portId:     Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                         PORT_D,PORT_E.
 * @param[in]  gpioNum:     Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  intConfig:  Pin interrupt configuration.
 *                         - PORT_ISF_DISABLED(0)
 *                         - PORT_ISF_DMA_RISING_EDGE(1)
 *                         - PORT_ISF_DMA_FALLING_EDGE(2)
 *                         - PORT_ISF_DMA_BOTH_EDGE(3)
 *                         - PORT_ISF_INT_LOGIC_0(8)
 *                         - PORT_ISF_INT_RISING_EDGE(9)
 *                         - PORT_ISF_INT_FALLING_EDGE(10)
 *                         - PORT_ISF_INT_BOTH_EDGE(11)
 *                         - PORT_ISF_INT_LOGIC_1(12)
 *
 * @return none.
 */
void PORT_PinIntConfig(PORT_Id_t portId, PORT_GpioNum_t gpioNum,
                       PORT_IntConfig_t intConfig);

/**
 * @brief       Configure the pin pull configuration.
 *
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNum:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  pullConfig:  Pin pull configuration, should be
 *                          PORT_PULL_NONE, PORT_PULL_DOWN and PORT_PULL_UP.
 *
 * @return none.
 *
 */
void PORT_PullConfig(PORT_Id_t portId, PORT_GpioNum_t gpioNum,
                     PORT_PullConfig_t pullConfig);

/**
 * @brief       Configure the pin slew rate configuration.
 *
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNum:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  slewRateConfig:  Pin slew rate configuration, should be
 *                          PORT_FAST_RATE and PORT_SLOW_RATE.
 *
 * @return none.
 *
 */
void PORT_SlewRateConfig(PORT_Id_t portId, PORT_GpioNum_t gpioNum,
                         PORT_SlewRate_t slewRateConfig);

/**
 * @brief       Configure the pin passive filter configuration.
 *
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNum:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  passiveFilterConfig:  Pin passive filter configuration, should be
 *                          DISABLE and ENABLE.
 *
 * @return none.
 *
 */
void PORT_PassiveFilterConfig(PORT_Id_t portId, PORT_GpioNum_t gpioNum,
                              ControlState_t passiveFilterConfig);

/**
 * @brief       Configure the pin open drain configuration.
 *
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNum:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  openDrainConfig:  Pin open drain configuration, should be
 *                          DISABLE and ENABLE.
 *
 * @return none.
 *
 */
void PORT_OpenDrainConfig(PORT_Id_t portId, PORT_GpioNum_t gpioNum,
                          ControlState_t openDrainConfig);

/**
 * @brief       Enable/Disable the pin filter .
 *
 * This function enables/disables the pin filter.
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNum:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  filterEnable:  Filter configuration, should be
 *                          DISABLE and ENABLE.
 *
 * @return none.
 *
 */
void PORT_FilterCmd(PORT_Id_t portId, PORT_GpioNum_t gpioNum,
                       ControlState_t filterEnable);

/**
 * @brief       Configure the pin filter configuration.
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNum:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  filterConfig:  pin filter configuration, the value is 0x0 - 0x1F.
 *
 * @return none.
 *
 */
void PORT_FilterConfig(PORT_Id_t portId, PORT_GpioNum_t gpioNum,
                       uint8_t filterConfig);

/**
 * @brief      Port install call back function
 *
 * @param[in]  cbFun: pointer to callback function.
 *
 * @return none
 *
 */
void PORT_InstallCallbackFunc(port_cb_t cbFun);

/**
 * @brief       Get pin interrupt status function
 *
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNum:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return     Interrupt status of a pin.
 *
 */
FlagStatus_t PORT_GetIntStatus(PORT_Id_t portId, PORT_GpioNum_t gpioNum);

/**
 * @brief       Get all pins interrupt status of a Port.
 *
 *
 * @param[in]  portId:     Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                         PORT_D,PORT_E.
 *
 * @return     All Pins interrupt status of a Port.
 *
 */
uint32_t PORT_GetIntStatusAll(PORT_Id_t portId);

/**
 * @brief       Clear the pin interrupt status function.
 *
 *
 * @param[in]  portId:     Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                         PORT_D, PORT_E.
 * @param[in]  gpioNum:     Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return     none.
 *
 */
void PORT_ClearPinInt(PORT_Id_t portId, PORT_GpioNum_t gpioNum);

/**
 * @brief       Clear all pins interrupt status function.
 *
 *
 * @param[in]  portId:     Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                         PORT_D, PORT_E.
 * @param[in]  clrPins:    Select pins no, a bit is a pin, bit0-gpio0,...
 *
 * @return     none.
 *
 */
void PORT_ClearPinsInt(PORT_Id_t portId, uint32_t clrPins);

/** @} end of group PORT_Public_FunctionDeclaration */

/** @defgroup GPIO_Public_FunctionDeclaration
 *  @brief GPIO functions declaration
 *  @{
 */

/**
 *  @brief GPIO functions
 */

/**
 * @brief       Set the pin direction configuration.
 *
 *
 * @param[in]    port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                         PORT_D, PORT_E.
 * @param[in]  gpioNum:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]     dir:   Select  I/O direction of a pin.
 *                       - 0: corresponding pin is set to input
 *                       - 1: corresponding pin is set to output
 *
 * @return none.
 *
 */
void GPIO_SetPinDir(PORT_Id_t port, PORT_GpioNum_t gpioNum, GPIO_Dir_t dir);

/**
 * @brief       Set the direction configuration for all pins.
 *
 *
 * @param[in]        port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                           PORT_D, PORT_E.
 * @param[in]     dataDir:   Select I/O directions.
 *                           - 0: corresponding pin is set to input
 *                           - 1: corresponding pin is set to output
 *
 * @return none.
 *
 */
void GPIO_SetPinsDir(PORT_Id_t port, uint32_t dataDir);

/**
 * @brief        Write a pin with a given value.
 *
 *
 * @param[in]    port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                       PORT_D, PORT_E.
 * @param[in]  gpioNum:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]     val:   Pin value.
 *                    - 0: corresponding pin is set to LOW
 *                    - 1: corresponding pin is set to HIGH
 *
 * @return none.
 *
 */
void GPIO_WritePinOutput(PORT_Id_t port, PORT_GpioNum_t gpioNum, GPIO_Level_t val);

/**
 * @brief        Write  pins  with the given value.
 *
 *
 * @param[in]    port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                       PORT_D, PORT_E.
 * @param[in]     val:   Pin value.
 *                    - 0: corresponding pin is set to LOW
 *                    - 1: corresponding pin is set to HIGH
 *
 * @return none.
 *
 */
void GPIO_WritePinsOutput(PORT_Id_t port, uint32_t val);

/**
 * @brief        Write a pin to 'Clear' value.
 *
 *
 * @param[in]    port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                       PORT_D, PORT_E.
 * @param[in]  gpioNum:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return none.
 *
 */
void GPIO_ClearPinOutput(PORT_Id_t port, PORT_GpioNum_t gpioNum);

/**
 * @brief        Write pins to 'Clear' value
 *
 *
 * @param[in]    port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                       PORT_D, PORT_E.
 * @param[in]    pins:   Clean the GPIO pins.
 *
 * @return none.
 *
 */
void GPIO_ClearPinsOutput(PORT_Id_t port, uint32_t pins);

/**
 * @brief        Write a pin with 'Set' value.
 *
 *
 * @param[in]    port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                       PORT_D, PORT_E.
 * @param[in]  gpioNum:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return none.
 *
 */
void GPIO_SetPinOutput(PORT_Id_t port, PORT_GpioNum_t gpioNum);

/**
 * @brief        Write  pins with 'Set' value.
 *
 *
 * @param[in]    port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                       PORT_D, PORT_E.
 * @param[in]    pins:   Set the GPIO pins.
 *
 * @return none.
 *
 */
void GPIO_SetPinsOutput(PORT_Id_t port, uint32_t pins);

/**
 * @brief        Toggle a pin value.
 *
 *
 * @param[in]      port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                         PORT_D, PORT_E.
 * @param[in]    gpioNum:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return none.
 *
 */
void GPIO_TogglePinOutput(PORT_Id_t port, PORT_GpioNum_t gpioNum);

/**
 * @brief        Toggle pins value.
 *
 *
 * @param[in]    port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                       PORT_D, PORT_E.
 * @param[in]    pins:   Toggle the GPIO pins.
 *
 * @return none.
 *
 */
void GPIO_TogglePinsOutput(PORT_Id_t port, uint32_t pins);

/**
 * @brief        Read a pin value.
 *
 *
 * @param[in]      port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                         PORT_D, PORT_E.
 * @param[in]    gpioNum:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return       GPIO_HIGH or GPIO_LOW.
 *
 */
GPIO_Level_t GPIO_ReadPinLevel(PORT_Id_t port, PORT_GpioNum_t gpioNum);

/**
 * @brief        Read  pins value.
 *
 *
 * @param[in]      port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                         PORT_D, PORT_E.
 *
 * @return        Pins value.
 *
 */
uint32_t GPIO_ReadPinsLevel(PORT_Id_t port);

/** @} end of group GPIO_Public_FunctionDeclaration */

/** @} end of group GPIO */

/** @} end of group Z20K14XM_Peripheral_Driver */
#endif /* GPIO_DRV_H */
