/**************************************************************************************************/
/**
 * @file      : Z20K11xM_gpio.h
 * @brief     : GPIO driver module header file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef Z20K11XM_GPIO_H
#define Z20K11XM_GPIO_H

#include "Z20K11xM_drv.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
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
    PORT_A = 0U, /*!< PORT_A  */
    PORT_B,      /*!< PORT_B  */
    PORT_C,      /*!< PORT_C  */
    PORT_D,      /*!< PORT_D  */
    PORT_E       /*!< PORT_E  */
} PORT_ID_t;

/**
 *  @brief PORT GPIO Number type definition
 */
typedef enum
{
    GPIO_0 = 0U, /*!< GPIO0 Pin */
    GPIO_1,      /*!< GPIO1 Pin */
    GPIO_2,      /*!< GPIO2 Pin */
    GPIO_3,      /*!< GPIO3 Pin */
    GPIO_4,      /*!< GPIO4 Pin */
    GPIO_5,      /*!< GPIO5 Pin */
    GPIO_6,      /*!< GPIO6 Pin */
    GPIO_7,      /*!< GPIO7 Pin */
    GPIO_8,      /*!< GPIO8 Pin */
    GPIO_9,      /*!< GPIO9 Pin */
    GPIO_10,     /*!< GPIO10 Pin */
    GPIO_11,     /*!< GPIO11 Pin */
    GPIO_12,     /*!< GPIO12 Pin */
    GPIO_13,     /*!< GPIO13 Pin */
    GPIO_14,     /*!< GPIO14 Pin */
    GPIO_15,     /*!< GPIO15 Pin */
    GPIO_16,     /*!< GPIO16 Pin */
    GPIO_17,     /*!< GPIO17 Pin */
    GPIO_18,     /*!< GPIO18 Pin */
    GPIO_19,     /*!< GPIO19 Pin */
    GPIO_20,     /*!< GPIO20 Pin */
    GPIO_21,     /*!< GPIO21 Pin */
    GPIO_22,     /*!< GPIO22 Pin */
    GPIO_23,     /*!< GPIO23 Pin */
    GPIO_24,     /*!< GPIO24 Pin */
    GPIO_25,     /*!< GPIO25 Pin */
    GPIO_26,     /*!< GPIO26 Pin */
    GPIO_27,     /*!< GPIO27 Pin */
    GPIO_28,     /*!< GPIO28 Pin */
    GPIO_29,     /*!< GPIO29 Pin */
    GPIO_30,     /*!< GPIO30 Pin */
    GPIO_31      /*!< GPIO31 Pin */
} PORT_GPIONO_t;

/**
 *  @brief PORT half pins type definition
 */
typedef enum
{
    PORT_LOW_HALF_PINS = 0U, /*!< PORT low  half pins  */
    PORT_HIGH_HALF_PINS      /*!< PORT high half pins  */
} PORT_GlobalPinsControl_t;

/**
 *  @brief PORT pull type definition
 */
typedef enum
{
    PORT_PULL_DISABLED = 0U, /*!< PORT pull none  */
    PORT_PULL_DOWN = 2U,     /*!< PORT pull down  */
    PORT_PULL_UP = 3U        /*!< PORT pull up    */
} PORT_PullConfig_t;

/**
 *  @brief PORT slew rate type definition
 */
typedef enum
{
    PORT_FAST_RATE = 0U, /*!< PORT fast rate  */
    PORT_SLOW_RATE       /*!< PORT slow rate  */
} PORT_SlewRate_t;

/**
 *  @brief PORT interrupt configuration type definition
 */
typedef enum
{
    PORT_ISF_DISABLED = 0U,          /*!< PORT isf disabled  */
    PORT_ISF_DMA_RISING_EDGE = 1U,   /*!< PORT isf dma rising  */
    PORT_ISF_DMA_FALLING_EDGE = 2U,  /*!< PORT isf dma falling */
    PORT_ISF_DMA_BOTH_EDGE = 3U,     /*!< PORT isf dma both */
    PORT_ISF_INT_LOGIC_0 = 8U,       /*!< PORT isf interrupt logic 0 */
    PORT_ISF_INT_RISING_EDGE = 9U,   /*!< PORT isf interrupt rising */
    PORT_ISF_INT_FALLING_EDGE = 10U, /*!< PORT isf interrupt falling */
    PORT_ISF_INT_BOTH_EDGE = 11U,    /*!< PORT isf interrupt both  */
    PORT_ISF_INT_LOGIC_1 = 12U       /*!< PORT isf interrupt logic 1 */
} PORT_IntConfig_t;

/**
 *  @brief PORT driver strength type definition
 */
typedef enum
{
    PORT_LOW_DRIVE_STRENGTH = 0U, /*!< PORT low  drive strength */
    PORT_HIGH_DRIVE_STRENGTH      /*!< PORT high drive strength */
} PORT_DriveStrength_t;

/**
 *  @brief PORT pin configuration struct definition
 */
typedef struct
{
    PORT_PullConfig_t pullConfig;   /*!< Configure pull type:
                                         - PORT_PULL_NONE(0)
                                         - PORT_PULL_DOWN(2)
                                         - PORT_PULL_UP(3)
                                     */
    PORT_SlewRate_t slewRateConfig; /*!< Configure slew rate type
                                         - PORT_FAST_RATE(0)
                                         - PORT_SLOW_RATE(1)
                                     */
    ControlState_t
        passiveFilterConfig; /*!< Configure the enable of the passive filter,
                                  - DISABLE
                                  - ENABLE
                              */
    ControlState_t openDrainConfig; /*!< Configure the enable of the open drain,
                                         - DISABLE
                                         - ENABLE
                                     */
    PORT_DriveStrength_t
        driveStrengthConfig;     /*!< Configure drive strength type,
                                      - PORT_LOW_DRIVE_STRENGTH(0)
                                      - PORT_HIGH_DRIVE_STRENGTH(1)
                                  */
    ControlState_t filterEnable; /*!< Configure the enable of the filter,
                                      - DISABLE
                                      - ENABLE
                                  */
    uint8_t filterConfig;        /*!< Configure filter:0x0-0x1F */
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
    GPIO_INPUT = 0U, /*!< Set GPIO port data direction as input  */
    GPIO_OUTPUT      /*!< Set GPIO port data direction as output */
} GPIO_Dir_t;

/**
 *  @brief GPIO data Input/Output type definition
 */
typedef enum
{
    GPIO_LOW = 0U, /*!< Input/Output low level(0) */
    GPIO_HIGH      /*!< Input/Output low level(1) */
} GPIO_LVL_t;

/** @} end of group GPIO_Public_Types */

/** @defgroup PORT_Pinmux
 *  @{
 */

/**
 *  @brief PORT Pinmux function type definition
 */
typedef enum
{
    PINMUX_FUNCTION_0 = 0U, /*!< PORT pin mux function 0 */
    PINMUX_FUNCTION_1,      /*!< PORT pin mux function 1 */
    PINMUX_FUNCTION_2,      /*!< PORT pin mux function 2 */
    PINMUX_FUNCTION_3,      /*!< PORT pin mux function 3 */
    PINMUX_FUNCTION_4,      /*!< PORT pin mux function 4 */
    PINMUX_FUNCTION_5,      /*!< PORT pin mux function 5 */
    PINMUX_FUNCTION_6,      /*!< PORT pin mux function 6 */
    PINMUX_FUNCTION_7       /*!< PORT pin mux function 7 */
} PORT_PinMuxFunc_t;

/* PTA0 pinmux function */
#define PTA0_ADC0_CH0  PINMUX_FUNCTION_0
#define PTA0_CMP0_IN0  PINMUX_FUNCTION_0
#define PTA0_GPIO      PINMUX_FUNCTION_1
#define PTA0_TIM2_CH1  PINMUX_FUNCTION_2
#define PTA0_I2C1_SCL  PINMUX_FUNCTION_5
#define PTA0_UART0_CTS PINMUX_FUNCTION_6
#define PTA0_TMU_OUT3  PINMUX_FUNCTION_7

/* PTA1 pinmux function */
#define PTA1_ADC0_CH1   PINMUX_FUNCTION_0
#define PTA1_ADC0_N_CH0 PINMUX_FUNCTION_0
#define PTA1_CMP0_IN1   PINMUX_FUNCTION_0
#define PTA1_GPIO       PINMUX_FUNCTION_1
#define PTA1_TIM1_CH1   PINMUX_FUNCTION_2
#define PTA1_I2C1_SDA   PINMUX_FUNCTION_5
#define PTA1_UART0_RTS  PINMUX_FUNCTION_6
#define PTA1_TMU_OUT0   PINMUX_FUNCTION_7

/* PTA2 pinmux function */
#define PTA2_GPIO       PINMUX_FUNCTION_1
#define PTA2_TIM0_CH0   PINMUX_FUNCTION_2
#define PTA2_I2C0_SDA   PINMUX_FUNCTION_3
#define PTA2_EWDT_OUT_b PINMUX_FUNCTION_4
#define PTA2_UART0_RX   PINMUX_FUNCTION_6

/* PTA3 pinmux function */
#define PTA3_GPIO     PINMUX_FUNCTION_1
#define PTA3_TIM0_CH1 PINMUX_FUNCTION_2
#define PTA3_I2C0_SCL PINMUX_FUNCTION_3
#define PTA3_EWDT_IN  PINMUX_FUNCTION_4
#define PTA3_SPI1_SIN PINMUX_FUNCTION_5
#define PTA3_UART0_TX PINMUX_FUNCTION_6

/* PTA4 pinmux function */
#define PTA4_GPIO       PINMUX_FUNCTION_1
#define PTA4_CAN0_RX    PINMUX_FUNCTION_3
#define PTA4_CMP0_OUT   PINMUX_FUNCTION_4
#define PTA4_EWDT_OUT_b PINMUX_FUNCTION_5
#define PTA4_SWD_DIO    PINMUX_FUNCTION_7

/* PTA5 pinmux function */
#define PTA5_GPIO    PINMUX_FUNCTION_1
#define PTA5_TCLK1   PINMUX_FUNCTION_3
#define PTA5_RESET_b PINMUX_FUNCTION_7

/* PTA6 pinmux function */
#define PTA6_ADC0_CH2  PINMUX_FUNCTION_0
#define PTA6_GPIO      PINMUX_FUNCTION_1
#define PTA6_TIM0_FLT1 PINMUX_FUNCTION_2
#define PTA6_SPI1_PCS1 PINMUX_FUNCTION_3
#define PTA6_UART3_RX  PINMUX_FUNCTION_5
#define PTA6_UART1_CTS PINMUX_FUNCTION_6

/* PTA7 pinmux function */
#define PTA7_TM1        PINMUX_FUNCTION_0
#define PTA7_ADC0_CH3   PINMUX_FUNCTION_0
#define PTA7_ADC0_N_CH1 PINMUX_FUNCTION_0
#define PTA7_GPIO       PINMUX_FUNCTION_1
#define PTA7_UART3_TX   PINMUX_FUNCTION_5
#define PTA7_UART1_RTS  PINMUX_FUNCTION_6

/* PTA10 pinmux function */
#define PTA10_XTAL32   PINMUX_FUNCTION_0
#define PTA10_GPIO     PINMUX_FUNCTION_1
#define PTA10_TIM1_CH4 PINMUX_FUNCTION_2
#define PTA10_UART0_RX PINMUX_FUNCTION_3
#define PTA10_CAN0_RX  PINMUX_FUNCTION_4
#define PTA10_SPI1_SCK PINMUX_FUNCTION_5
#define PTA10_UART3_RX PINMUX_FUNCTION_6

/* PTA11 pinmux function */
#define PTA11_EXTAL32  PINMUX_FUNCTION_0
#define PTA11_GPIO     PINMUX_FUNCTION_1
#define PTA11_TIM1_CH5 PINMUX_FUNCTION_2
#define PTA11_UART0_TX PINMUX_FUNCTION_3
#define PTA11_CAN0_TX  PINMUX_FUNCTION_4
#define PTA11_UART3_TX PINMUX_FUNCTION_6

/* PTA12 pinmux function */
#define PTA12_SENSE_BUS PINMUX_FUNCTION_0
#define PTA12_GPIO      PINMUX_FUNCTION_1
#define PTA12_TIM1_CH6  PINMUX_FUNCTION_2
#define PTA12_CAN1_RX   PINMUX_FUNCTION_3
#define PTA12_UART0_RX  PINMUX_FUNCTION_4
#define PTA12_TIM2_CH2  PINMUX_FUNCTION_5

/* PTA13 pinmux function */
#define PTA13_FORCE_BUS PINMUX_FUNCTION_0
#define PTA13_GPIO      PINMUX_FUNCTION_1
#define PTA13_TIM1_CH7  PINMUX_FUNCTION_2
#define PTA13_CAN1_TX   PINMUX_FUNCTION_3
#define PTA13_UART0_TX  PINMUX_FUNCTION_4
#define PTA13_TIM2_CH3  PINMUX_FUNCTION_5

/* PTA15 pinmux function */
#define PTA15_GPIO      PINMUX_FUNCTION_1
#define PTA15_TIM1_CH2  PINMUX_FUNCTION_2
#define PTA15_SPI2_PCS0 PINMUX_FUNCTION_5

/* PTA16 pinmux function */
#define PTA16_GPIO      PINMUX_FUNCTION_1
#define PTA16_TIM1_CH3  PINMUX_FUNCTION_2
#define PTA16_SPI1_PCS1 PINMUX_FUNCTION_5

/* PTB0 pinmux function */
#define PTB0_ADC0_CH4   PINMUX_FUNCTION_0
#define PTB0_GPIO       PINMUX_FUNCTION_1
#define PTB0_UART0_RX   PINMUX_FUNCTION_2
#define PTB0_SPI0_PCS0  PINMUX_FUNCTION_3
#define PTB0_STIM0_ALT3 PINMUX_FUNCTION_4
#define PTB0_CAN0_RX    PINMUX_FUNCTION_5

/* PTB1 pinmux function */
#define PTB1_ADC0_CH5   PINMUX_FUNCTION_0
#define PTB1_ADC0_N_CH2 PINMUX_FUNCTION_0
#define PTB1_GPIO       PINMUX_FUNCTION_1
#define PTB1_UART0_TX   PINMUX_FUNCTION_2
#define PTB1_SPI0_SOUT  PINMUX_FUNCTION_3
#define PTB1_TCLK0      PINMUX_FUNCTION_4
#define PTB1_CAN0_TX    PINMUX_FUNCTION_5

/* PTB2 pinmux function */
#define PTB2_ADC0_CH6 PINMUX_FUNCTION_0
#define PTB2_GPIO     PINMUX_FUNCTION_1
#define PTB2_TIM1_CH0 PINMUX_FUNCTION_2
#define PTB2_SPI0_SCK PINMUX_FUNCTION_3
#define PTB2_TMU_IN3  PINMUX_FUNCTION_6

/* PTB3 pinmux function */
#define PTB3_ADC0_CH7 PINMUX_FUNCTION_0
#define PTB3_GPIO     PINMUX_FUNCTION_1
#define PTB3_TIM1_CH1 PINMUX_FUNCTION_2
#define PTB3_SPI0_SIN PINMUX_FUNCTION_3
#define PTB3_TMU_IN2  PINMUX_FUNCTION_6

/* PTB4 pinmux function */
#define PTB4_ADC0_CH16 PINMUX_FUNCTION_0
#define PTB4_GPIO      PINMUX_FUNCTION_1
#define PTB4_TIM0_CH4  PINMUX_FUNCTION_2
#define PTB4_SPI0_SOUT PINMUX_FUNCTION_3
#define PTB4_TMU_IN1   PINMUX_FUNCTION_6

/* PTB5 pinmux function */
#define PTB5_ADC0_CH17  PINMUX_FUNCTION_0
#define PTB5_GPIO       PINMUX_FUNCTION_1
#define PTB5_TIM0_CH5   PINMUX_FUNCTION_2
#define PTB5_SPI0_PCS1  PINMUX_FUNCTION_3
#define PTB5_SPI0_PCS0  PINMUX_FUNCTION_4
#define PTB5_CLKOUT     PINMUX_FUNCTION_5
#define PTB5_TMU_IN0    PINMUX_FUNCTION_6
#define PTB5_EWDT_OUT_b PINMUX_FUNCTION_7

/* PTB6 pinmux function */
#define PTB6_XTAL     PINMUX_FUNCTION_0
#define PTB6_GPIO     PINMUX_FUNCTION_1
#define PTB6_I2C0_SDA PINMUX_FUNCTION_2

/* PTB7 pinmux function */
#define PTB7_EXTAL    PINMUX_FUNCTION_0
#define PTB7_GPIO     PINMUX_FUNCTION_1
#define PTB7_I2C0_SCL PINMUX_FUNCTION_2

/* PTB12 pinmux function */
#define PTB12_GPIO     PINMUX_FUNCTION_1
#define PTB12_TIM0_CH0 PINMUX_FUNCTION_2
#define PTB12_I2C1_SCL PINMUX_FUNCTION_5

/* PTB13 pinmux function */
#define PTB13_TM0       PINMUX_FUNCTION_0
#define PTB13_GPIO      PINMUX_FUNCTION_1
#define PTB13_TIM0_CH1  PINMUX_FUNCTION_2
#define PTB13_TIM0_FLT1 PINMUX_FUNCTION_3
#define PTB13_CAN1_TX   PINMUX_FUNCTION_4
#define PTB13_I2C1_SDA  PINMUX_FUNCTION_5

/* PTB14 pinmux function */
#define PTB14_GPIO     PINMUX_FUNCTION_1
#define PTB14_TIM0_CH2 PINMUX_FUNCTION_2
#define PTB14_SPI1_SCK PINMUX_FUNCTION_3

/* PTB15 pinmux function */
#define PTB15_GPIO     PINMUX_FUNCTION_1
#define PTB15_TIM0_CH3 PINMUX_FUNCTION_2
#define PTB15_SPI1_SIN PINMUX_FUNCTION_3
#define PTB15_UART2_RX PINMUX_FUNCTION_4

/* PTB16 pinmux function */
#define PTB16_GPIO      PINMUX_FUNCTION_1
#define PTB16_TIM0_CH4  PINMUX_FUNCTION_2
#define PTB16_SPI1_SOUT PINMUX_FUNCTION_3
#define PTB16_UART2_TX  PINMUX_FUNCTION_4

/* PTB17 pinmux function */
#define PTB17_GPIO      PINMUX_FUNCTION_1
#define PTB17_TIM0_CH5  PINMUX_FUNCTION_2
#define PTB17_SPI1_PCS0 PINMUX_FUNCTION_5

/* PTC0 pinmux function */
#define PTC0_ADC0_CH8 PINMUX_FUNCTION_0
#define PTC0_GPIO     PINMUX_FUNCTION_1
#define PTC0_TIM0_CH0 PINMUX_FUNCTION_2
#define PTC0_SPI2_SIN PINMUX_FUNCTION_3
#define PTC0_UART2_RX PINMUX_FUNCTION_5
#define PTC0_TIM1_CH6 PINMUX_FUNCTION_6

/* PTC1 pinmux function */
#define PTC1_ADC0_CH9  PINMUX_FUNCTION_0
#define PTC1_GPIO      PINMUX_FUNCTION_1
#define PTC1_TIM0_CH1  PINMUX_FUNCTION_2
#define PTC1_SPI2_SOUT PINMUX_FUNCTION_3
#define PTC1_UART2_TX  PINMUX_FUNCTION_5
#define PTC1_TIM1_CH7  PINMUX_FUNCTION_6

/* PTC2 pinmux function */
#define PTC2_ADC0_CH10 PINMUX_FUNCTION_0
#define PTC2_CMP0_IN5  PINMUX_FUNCTION_0
#define PTC2_GPIO      PINMUX_FUNCTION_1
#define PTC2_TIM0_CH2  PINMUX_FUNCTION_2
#define PTC2_CAN0_RX   PINMUX_FUNCTION_3
#define PTC2_UART0_RX  PINMUX_FUNCTION_4

/* PTC3 pinmux function */
#define PTC3_ADC0_CH11 PINMUX_FUNCTION_0
#define PTC3_CMP0_IN4  PINMUX_FUNCTION_0
#define PTC3_GPIO      PINMUX_FUNCTION_1
#define PTC3_TIM0_CH3  PINMUX_FUNCTION_2
#define PTC3_CAN0_TX   PINMUX_FUNCTION_3
#define PTC3_UART0_TX  PINMUX_FUNCTION_4

/* PTC4 pinmux function */
#define PTC4_CMP0_IN2 PINMUX_FUNCTION_0
#define PTC4_GPIO     PINMUX_FUNCTION_1
#define PTC4_TIM1_CH0 PINMUX_FUNCTION_2
#define PTC4_EWDT_IN  PINMUX_FUNCTION_5
#define PTC4_SWD_CLK  PINMUX_FUNCTION_7

/* PTC5 pinmux function */
#define PTC5_GPIO     PINMUX_FUNCTION_1
#define PTC5_TIM2_CH0 PINMUX_FUNCTION_2
#define PTC5_SPI1_SIN PINMUX_FUNCTION_5
#define PTC5_NMI_b    PINMUX_FUNCTION_7

/* PTC6 pinmux function */
#define PTC6_GPIO     PINMUX_FUNCTION_1
#define PTC6_UART1_RX PINMUX_FUNCTION_2
#define PTC6_CAN1_RX  PINMUX_FUNCTION_3
#define PTC6_TIM0_CH2 PINMUX_FUNCTION_4

/* PTC7 pinmux function */
#define PTC7_GPIO     PINMUX_FUNCTION_1
#define PTC7_UART1_TX PINMUX_FUNCTION_2
#define PTC7_CAN1_TX  PINMUX_FUNCTION_3
#define PTC7_TIM0_CH3 PINMUX_FUNCTION_4

/* PTC8 pinmux function */
#define PTC8_TM2       PINMUX_FUNCTION_0
#define PTC8_GPIO      PINMUX_FUNCTION_1
#define PTC8_UART1_RX  PINMUX_FUNCTION_2
#define PTC8_TIM1_FLT0 PINMUX_FUNCTION_3
#define PTC8_CAN1_RX   PINMUX_FUNCTION_5
#define PTC8_UART0_CTS PINMUX_FUNCTION_6

/* PTC9 pinmux function */
#define PTC9_TM3       PINMUX_FUNCTION_0
#define PTC9_GPIO      PINMUX_FUNCTION_1
#define PTC9_UART1_TX  PINMUX_FUNCTION_2
#define PTC9_TIM1_FLT1 PINMUX_FUNCTION_3
#define PTC9_CAN1_TX   PINMUX_FUNCTION_5
#define PTC9_UART0_RTS PINMUX_FUNCTION_6

/* PTC14 pinmux function */
#define PTC14_ADC0_CH12 PINMUX_FUNCTION_0
#define PTC14_GPIO      PINMUX_FUNCTION_1
#define PTC14_TIM1_CH2  PINMUX_FUNCTION_2
#define PTC14_SPI2_PCS0 PINMUX_FUNCTION_3
#define PTC14_TIM2_CH4  PINMUX_FUNCTION_4
#define PTC14_SPI0_PCS0 PINMUX_FUNCTION_5
#define PTC14_TMU_IN9   PINMUX_FUNCTION_6

/* PTC15 pinmux function */
#define PTC15_ADC0_CH13 PINMUX_FUNCTION_0
#define PTC15_GPIO      PINMUX_FUNCTION_1
#define PTC15_TIM1_CH3  PINMUX_FUNCTION_2
#define PTC15_SPI2_SCK  PINMUX_FUNCTION_3
#define PTC15_SPI0_SOUT PINMUX_FUNCTION_5
#define PTC15_TMU_IN8   PINMUX_FUNCTION_6

/* PTC16 pinmux function */
#define PTC16_ADC0_CH14 PINMUX_FUNCTION_0
#define PTC16_GPIO      PINMUX_FUNCTION_1
#define PTC16_CAN0_RX   PINMUX_FUNCTION_3
#define PTC16_SPI0_SCK  PINMUX_FUNCTION_4
#define PTC16_TIM0_CH0  PINMUX_FUNCTION_5

/* PTC17 pinmux function */
#define PTC17_ADC0_CH15 PINMUX_FUNCTION_0
#define PTC17_GPIO      PINMUX_FUNCTION_1
#define PTC17_CAN0_TX   PINMUX_FUNCTION_3
#define PTC17_SPI0_SIN  PINMUX_FUNCTION_4
#define PTC17_TIM0_CH1  PINMUX_FUNCTION_5
#define PTC17_SPI2_SIN  PINMUX_FUNCTION_6

/* PTD0 pinmux function */
#define PTD0_CMP0_IN9 PINMUX_FUNCTION_0
#define PTD0_GPIO     PINMUX_FUNCTION_1
#define PTD0_TIM0_CH2 PINMUX_FUNCTION_2
#define PTD0_SPI1_SCK PINMUX_FUNCTION_3
#define PTD0_TIM2_CH0 PINMUX_FUNCTION_4
#define PTD0_CAN0_RX  PINMUX_FUNCTION_5

/* PTD1 pinmux function */
#define PTD1_CMP0_IN8 PINMUX_FUNCTION_0
#define PTD1_GPIO     PINMUX_FUNCTION_1
#define PTD1_TIM0_CH3 PINMUX_FUNCTION_2
#define PTD1_SPI1_SIN PINMUX_FUNCTION_3
#define PTD1_TIM2_CH1 PINMUX_FUNCTION_4
#define PTD1_CAN0_TX  PINMUX_FUNCTION_5
#define PTD1_PMU_req  PINMUX_FUNCTION_6
#define PTD1_TMU_OUT2 PINMUX_FUNCTION_7

/* PTD2 pinmux function */
#define PTD2_GPIO      PINMUX_FUNCTION_1
#define PTD2_TIM1_CH4  PINMUX_FUNCTION_2
#define PTD2_SPI1_SOUT PINMUX_FUNCTION_3
#define PTD2_UART1_RX  PINMUX_FUNCTION_5
#define PTD2_TMU_IN5   PINMUX_FUNCTION_6

/* PTD3 pinmux function */
#define PTD3_GPIO      PINMUX_FUNCTION_1
#define PTD3_TIM1_CH5  PINMUX_FUNCTION_2
#define PTD3_SPI1_PCS0 PINMUX_FUNCTION_3
#define PTD3_CAN1_RX   PINMUX_FUNCTION_4
#define PTD3_UART1_TX  PINMUX_FUNCTION_5
#define PTD3_TMU_IN4   PINMUX_FUNCTION_6
#define PTD3_NMI_b     PINMUX_FUNCTION_7

/* PTD4 pinmux function */
#define PTD4_GPIO PINMUX_FUNCTION_1

/* PTD5 pinmux function */
#define PTD5_GPIO       PINMUX_FUNCTION_1
#define PTD5_TIM2_CH3   PINMUX_FUNCTION_2
#define PTD5_STIM0_ALT2 PINMUX_FUNCTION_3
#define PTD5_TIM2_FLT1  PINMUX_FUNCTION_4
#define PTD5_UART2_RX   PINMUX_FUNCTION_5
#define PTD5_TMU_IN7    PINMUX_FUNCTION_6

/* PTD6 pinmux function */
#define PTD6_CMP0_IN7 PINMUX_FUNCTION_0
#define PTD6_GPIO     PINMUX_FUNCTION_1
#define PTD6_UART2_RX PINMUX_FUNCTION_2
#define PTD6_TIM0_CH6 PINMUX_FUNCTION_5

/* PTD7 pinmux function */
#define PTD7_CMP0_IN6 PINMUX_FUNCTION_0
#define PTD7_GPIO     PINMUX_FUNCTION_1
#define PTD7_UART2_TX PINMUX_FUNCTION_2
#define PTD7_TIM0_CH7 PINMUX_FUNCTION_5
#define PTD7_TIM0_CH0 PINMUX_FUNCTION_6

/* PTD10 pinmux function */
#define PTD10_CMP0_IN13 PINMUX_FUNCTION_0
#define PTD10_GPIO      PINMUX_FUNCTION_1
#define PTD10_TIM2_CH0  PINMUX_FUNCTION_2
#define PTD10_TIM1_CH6  PINMUX_FUNCTION_6

/* PTD11 pinmux function */
#define PTD11_CMP0_IN12 PINMUX_FUNCTION_0
#define PTD11_GPIO      PINMUX_FUNCTION_1
#define PTD11_TIM2_CH1  PINMUX_FUNCTION_2
#define PTD11_UART2_RX  PINMUX_FUNCTION_5
#define PTD11_UART2_CTS PINMUX_FUNCTION_6

/* PTD15 pinmux function */
#define PTD15_GPIO     PINMUX_FUNCTION_1
#define PTD15_TIM0_CH0 PINMUX_FUNCTION_2
#define PTD15_UART0_RX PINMUX_FUNCTION_3
#define PTD15_SPI0_SCK PINMUX_FUNCTION_4
#define PTD15_SPI2_SCK PINMUX_FUNCTION_5
#define PTD15_TMU_OUT1 PINMUX_FUNCTION_7

/* PTD16 pinmux function */
#define PTD16_GPIO     PINMUX_FUNCTION_1
#define PTD16_TIM0_CH1 PINMUX_FUNCTION_2
#define PTD16_UART0_TX PINMUX_FUNCTION_3
#define PTD16_SPI0_SIN PINMUX_FUNCTION_4
#define PTD16_SPI2_SIN PINMUX_FUNCTION_5

/* PTD17 pinmux function */
#define PTD17_GPIO      PINMUX_FUNCTION_1
#define PTD17_UART2_RX  PINMUX_FUNCTION_3
#define PTD17_SPI2_SCK  PINMUX_FUNCTION_5

/* PTE0 pinmux function */
#define PTE0_GPIO      PINMUX_FUNCTION_1
#define PTE0_SPI0_SCK  PINMUX_FUNCTION_2
#define PTE0_TCLK1     PINMUX_FUNCTION_3
#define PTE0_UART3_RX  PINMUX_FUNCTION_4
#define PTE0_SPI1_SOUT PINMUX_FUNCTION_5

/* PTE1 pinmux function */
#define PTE1_GPIO      PINMUX_FUNCTION_1
#define PTE1_SPI0_SIN  PINMUX_FUNCTION_2
#define PTE1_UART3_TX  PINMUX_FUNCTION_4
#define PTE1_SPI1_PCS0 PINMUX_FUNCTION_5
#define PTE1_TIM1_FLT1 PINMUX_FUNCTION_6

/* PTE2 pinmux function */
#define PTE2_GPIO       PINMUX_FUNCTION_1
#define PTE2_SPI0_SOUT  PINMUX_FUNCTION_2
#define PTE2_STIM0_ALT3 PINMUX_FUNCTION_3
#define PTE2_TIM2_CH6   PINMUX_FUNCTION_4
#define PTE2_UART1_RX   PINMUX_FUNCTION_5
#define PTE2_UART1_CTS  PINMUX_FUNCTION_6

/* PTE3 pinmux function */
#define PTE3_GPIO      PINMUX_FUNCTION_1
#define PTE3_TIM0_FLT0 PINMUX_FUNCTION_2
#define PTE3_UART2_RTS PINMUX_FUNCTION_3
#define PTE3_TIM2_FLT0 PINMUX_FUNCTION_4
#define PTE3_SPI2_SOUT PINMUX_FUNCTION_5
#define PTE3_TMU_IN6   PINMUX_FUNCTION_6
#define PTE3_CMP0_OUT  PINMUX_FUNCTION_7

/* PTE6 pinmux function */
#define PTE6_GPIO      PINMUX_FUNCTION_1
#define PTE6_SPI0_PCS0 PINMUX_FUNCTION_2
#define PTE6_TIM2_CH7  PINMUX_FUNCTION_4
#define PTE6_UART1_TX  PINMUX_FUNCTION_5
#define PTE6_UART1_RTS PINMUX_FUNCTION_6

/* PTE7 pinmux function */
#define PTE7_GPIO      PINMUX_FUNCTION_1
#define PTE7_TIM0_CH7  PINMUX_FUNCTION_2
#define PTE7_TIM0_FLT0 PINMUX_FUNCTION_3

/* PTE8 pinmux function */
#define PTE8_CMP0_IN3 PINMUX_FUNCTION_0
#define PTE8_GPIO     PINMUX_FUNCTION_1
#define PTE8_TIM0_CH6 PINMUX_FUNCTION_2
#define PTE8_TCLK2    PINMUX_FUNCTION_5
#define PTE8_EWDT_IN  PINMUX_FUNCTION_7

/* PTE9 pinmux function */
#define PTE9_GPIO      PINMUX_FUNCTION_1
#define PTE9_TIM0_CH7  PINMUX_FUNCTION_2
#define PTE9_UART2_CTS PINMUX_FUNCTION_3
#define PTE9_TIM2_FLT0 PINMUX_FUNCTION_4
#define PTE9_SPI2_PCS1 PINMUX_FUNCTION_5

/* PTE10 pinmux function */
#define PTE10_CMP0_IN11 PINMUX_FUNCTION_0
#define PTE10_GPIO      PINMUX_FUNCTION_1
#define PTE10_CLKOUT    PINMUX_FUNCTION_2
#define PTE10_SPI2_PCS0 PINMUX_FUNCTION_3
#define PTE10_TIM2_CH4  PINMUX_FUNCTION_4
#define PTE10_TIM0_CH2  PINMUX_FUNCTION_5
#define PTE10_TIM2_CH0  PINMUX_FUNCTION_6
#define PTE10_TMU_OUT4  PINMUX_FUNCTION_7

/* PTE11 pinmux function */
#define PTE11_CMP0_IN10  PINMUX_FUNCTION_0
#define PTE11_GPIO       PINMUX_FUNCTION_1
#define PTE11_SPI2_PCS1  PINMUX_FUNCTION_2
#define PTE11_STIM0_ALT1 PINMUX_FUNCTION_3
#define PTE11_TIM2_CH5   PINMUX_FUNCTION_4
#define PTE11_SPI1_SCK   PINMUX_FUNCTION_5
#define PTE11_CAN0_RX    PINMUX_FUNCTION_6
#define PTE11_TMU_OUT5   PINMUX_FUNCTION_7

/* PTE12 pinmux function */
#define PTE12_GPIO      PINMUX_FUNCTION_1
#define PTE12_UART2_TX  PINMUX_FUNCTION_3
#define PTE12_SPI2_SIN  PINMUX_FUNCTION_5
/** @} end of group PORT_Pinmux */

/** @defgroup PORT_Public_FunctionDeclaration
 *  @brief PORT functions declaration
 *  @{
 */
/**
 *  @brief PORT a-e,GPIO 0-31 callback function type
 */
typedef void (*port_cb_t)(PORT_ID_t portId, PORT_GPIONO_t gpioNo);
/**
 * @brief       Configure pins with the same global configuration
 * If a pin is locked, global control will not work on it
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                            PORT_D,PORT_E.
 * @param[in]  pins:        Select the GPIO pins.
 * @param[in]  value:       Set GPIO pin global value.
 *
 * @return none.
 *
 */
void PORT_GlobalPinsConfig(PORT_ID_t portId, uint32_t pins, uint32_t value);

/**
 * @brief       Initialize seleted pin with the given configuration structure.
 *
 *
 * @param[in]  portId:     Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                         PORT_D,PORT_E.
 * @param[in]  gpioNo:     Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  pinConfig:  Pin configuration struct.
 *
 * @return none.
 *
 */
void PORT_PinInit(PORT_ID_t portId, PORT_GPIONO_t gpioNo,
                  const PORT_PinConfig_t *pinConfig);

/**
 * @brief       Configure the pin mux function.
 *
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNo:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  pinMuxFunc:  Pin mux function.
 *
 * @return none.
 *
 */
void PORT_PinmuxConfig(PORT_ID_t portId, PORT_GPIONO_t gpioNo,
                       PORT_PinMuxFunc_t pinMuxFunc);

/**
 * @brief       Configure the pin interrupt
 *
 * @param[in]  portId:     Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                         PORT_D,PORT_E.
 * @param[in]  gpioNo:     Select the GPIO pin,such as GPIO_0~GPIO_31.
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
 *
 */
void PORT_PinIntConfig(PORT_ID_t portId, PORT_GPIONO_t gpioNo,
                       PORT_IntConfig_t intConfig);

/**
 * @brief       Configure the pin pull configuration.
 *
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNo:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  pullConfig:  Pin pull configuration, should be
 *                          PORT_PULL_NONE, PORT_PULL_DOWN and PORT_PULL_UP.
 *
 * @return none.
 *
 */
void PORT_PullConfig(PORT_ID_t portId, PORT_GPIONO_t gpioNo,
                     PORT_PullConfig_t pullConfig);

/**
 * @brief       Configure the pin slew rate configuration.
 *
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNo:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  slewRateConfig:  Pin slew rate configuration, should be
 *                          PORT_FAST_RATE and PORT_SLOW_RATE.
 *
 * @return none.
 *
 */
void PORT_SlewRateConfig(PORT_ID_t portId, PORT_GPIONO_t gpioNo,
                         PORT_SlewRate_t slewRateConfig);

/**
 * @brief       Configure the pin passive filter configuration.
 *
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNo:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  passiveFilterConfig:  Pin passive filter configuration, should be
 *                          DISABLE and ENABLE.
 *
 * @return none.
 *
 */
void PORT_PassiveFilterConfig(PORT_ID_t portId, PORT_GPIONO_t gpioNo,
                              ControlState_t passiveFilterConfig);

/**
 * @brief       Configure the pin open drain configuration.
 *
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNo:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  openDrainConfig:  Pin open drain configuration, should be
 *                          DISABLE and ENABLE.
 *
 * @return none.
 *
 */
void PORT_OpenDrainConfig(PORT_ID_t portId, PORT_GPIONO_t gpioNo,
                          ControlState_t openDrainConfig);

/**
 * @brief       Configure the pin drive strength configuration.
 *
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNo:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  driveStrengthConfig:  Pin drive strength configuration, should
 *                          be PORT_LOW_DRIVE_STRENGTH and
 *                         PORT_HIGH_DRIVE_STRENGTH.
 *
 * @return none.
 *
 */
void PORT_DriveStrengthConfig(PORT_ID_t portId, PORT_GPIONO_t gpioNo,
                              PORT_DriveStrength_t driveStrengthConfig);

/**
 * @brief       Enable/Disable the pin filter .
 *
 * This function enables/disables the pin filter.
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNo:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  filterEnable:  pin filter configuration, should be
                               DISABLE and ENABLE.
 *
 * @return none.
 *
 */
void PORT_FilterCmd(PORT_ID_t portId, PORT_GPIONO_t gpioNo,
                    ControlState_t filterEnable);

/**
 * @brief       Configure the pin filter configuration.
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNo:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]  filterConfig:  pin filter configuration, the value is 0x0 - 0x1F.
 *
 * @return none.
 *
 */
void PORT_FilterConfig(PORT_ID_t portId, PORT_GPIONO_t gpioNo,
                       uint8_t filterConfig);

/**
 * @brief      Port install call back function
 *
 * @param[in]  cbFun: pointer to callback function.
 *
 * @return none
 *
 */
void PORT_InstallCallBackFunc(port_cb_t cbFun);

/**
 * @brief       Get pin interrupt status function
 *
 *
 * @param[in]  portId:      Select the PORT id,such as PORT_A,PORT_B,PORT_C,
 *                          PORT_D,PORT_E.
 * @param[in]  gpioNo:      Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return     Interrupt status of a pin.
 *
 */
FlagStatus_t PORT_GetIntStatus(PORT_ID_t portId, PORT_GPIONO_t gpioNo);

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
uint32_t PORT_GetIntStatusAll(PORT_ID_t portId);

/**
 * @brief       Clear the pin interrupt status function.
 *
 *
 * @param[in]  portId:     Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                         PORT_D, PORT_E.
 * @param[in]  gpioNo:     Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return     none.
 *
 */
void PORT_ClearPinInt(PORT_ID_t portId, PORT_GPIONO_t gpioNo);

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
void PORT_ClearPinsInt(PORT_ID_t portId, uint32_t clrPins);

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
 * @param[in]  gpioNo:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]     dir:   Select  I/O direction of a pin.
 *                       - 0: corresponding pin is set to input
 *                       - 1: corresponding pin is set to output
 *
 * @return none.
 *
 */
void GPIO_SetPinDir(PORT_ID_t port, PORT_GPIONO_t gpioNo, GPIO_Dir_t dir);

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
void GPIO_SetPinsDir(PORT_ID_t port, uint32_t dataDir);

/**
 * @brief        Write a pin with a given value.
 *
 *
 * @param[in]    port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                       PORT_D, PORT_E.
 * @param[in]  gpioNo:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]     val:   Pin value.
 *                    - 0: corresponding pin is set to LOW
 *                    - 1: corresponding pin is set to HIGH
 *
 * @return none.
 *
 */
void GPIO_WritePinOutput(PORT_ID_t port, PORT_GPIONO_t gpioNo, GPIO_LVL_t val);

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
void GPIO_WritePinsOutput(PORT_ID_t port, uint32_t val);

/**
 * @brief        Write a pin to 'Clear' value.
 *
 *
 * @param[in]    port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                       PORT_D, PORT_E.
 * @param[in]  gpioNo:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return none.
 *
 */
void GPIO_ClearPinOutput(PORT_ID_t port, PORT_GPIONO_t gpioNo);

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
void GPIO_ClearPinsOutput(PORT_ID_t port, uint32_t pins);

/**
 * @brief        Write a pin with 'Set' value.
 *
 *
 * @param[in]    port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                       PORT_D, PORT_E.
 * @param[in]  gpioNo:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return none.
 *
 */
void GPIO_SetPinOutput(PORT_ID_t port, PORT_GPIONO_t gpioNo);

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
void GPIO_SetPinsOutput(PORT_ID_t port, uint32_t pins);

/**
 * @brief        Toggle a pin value.
 *
 *
 * @param[in]      port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                         PORT_D, PORT_E.
 * @param[in]    gpioNo:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return none.
 *
 */
void GPIO_TogglePinOutput(PORT_ID_t port, PORT_GPIONO_t gpioNo);

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
void GPIO_TogglePinsOutput(PORT_ID_t port, uint32_t pins);

/**
 * @brief        Read a pin value.
 *
 *
 * @param[in]      port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                         PORT_D, PORT_E.
 * @param[in]    gpioNo:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return       GPIO_HIGH or GPIO_LOW.
 *
 */
GPIO_LVL_t GPIO_ReadPinLevel(PORT_ID_t port, PORT_GPIONO_t gpioNo);

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
uint32_t GPIO_ReadPinsLevel(PORT_ID_t port);

/** @} end of group GPIO_Public_FunctionDeclaration */

/** @defgroup RGPIO_Public_FunctionDeclaration
 *  @brief RGPIO functions declaration
 *  @{
 */
/**
 *  @brief RGPIO functions
 */

/**
 * @brief       Set the pin direction configuration.
 *
 *
 * @param[in]    port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                         PORT_D, PORT_E.
 * @param[in]  gpioNo:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]     dir:   Select  I/O direction of a pin.
 *                       - 0: corresponding pin is set to input
 *                       - 1: corresponding pin is set to output
 *
 * @return none.
 *
 */
void RGPIO_SetPinDir(PORT_ID_t port, PORT_GPIONO_t gpioNo, GPIO_Dir_t dir);

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
void RGPIO_SetPinsDir(PORT_ID_t port, uint32_t dataDir);

/**
 * @brief        Write a pin with a given value.
 *
 *
 * @param[in]    port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                       PORT_D, PORT_E.
 * @param[in]  gpioNo:   Select the RGPIO pin,such as GPIO_0~GPIO_31.
 * @param[in]     val:   Pin value.
 *                    - 0: corresponding pin is set to LOW
 *                    - 1: corresponding pin is set to HIGH
 *
 * @return none.
 *
 */
void RGPIO_WritePinOutput(PORT_ID_t port, PORT_GPIONO_t gpioNo, GPIO_LVL_t val);

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
void RGPIO_WritePinsOutput(PORT_ID_t port, uint32_t val);

/**
 * @brief        Write a pin to 'Clear' value.
 *
 *
 * @param[in]    port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                       PORT_D, PORT_E.
 * @param[in]  gpioNo:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return none.
 *
 */
void RGPIO_ClearPinOutput(PORT_ID_t port, PORT_GPIONO_t gpioNo);

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
void RGPIO_ClearPinsOutput(PORT_ID_t port, uint32_t pins);

/**
 * @brief        Write a pin with 'Set' value.
 *
 *
 * @param[in]    port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                       PORT_D, PORT_E.
 * @param[in]  gpioNo:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return none.
 *
 */
void RGPIO_SetPinOutput(PORT_ID_t port, PORT_GPIONO_t gpioNo);

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

void RGPIO_SetPinsOutput(PORT_ID_t port, uint32_t pins);

/**
 * @brief        Toggle a pin value.
 *
 *
 * @param[in]      port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                         PORT_D, PORT_E.
 * @param[in]    gpioNo:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return none.
 *
 */
void RGPIO_TogglePinOutput(PORT_ID_t port, PORT_GPIONO_t gpioNo);

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
void RGPIO_TogglePinsOutput(PORT_ID_t port, uint32_t pins);

/**
 * @brief        Read a pin value.
 *
 *
 * @param[in]      port:   Select pin PORT ID: PORT_A, PORT_B, PORT_C,
 *                         PORT_D, PORT_E.
 * @param[in]    gpioNo:   Select the GPIO pin,such as GPIO_0~GPIO_31.
 *
 * @return       GPIO_HIGH or GPIO_LOW.
 *
 */
GPIO_LVL_t RGPIO_ReadPinLevel(PORT_ID_t port, PORT_GPIONO_t gpioNo);

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
uint32_t RGPIO_ReadPinsLevel(PORT_ID_t port);

/** @} end of group RGPIO_Public_FunctionDeclaration */

/** @} end of group GPIO */

/** @} end of group Z20K11X_Peripheral_Driver */
#endif /* Z20K11XM_GPIO_H */
