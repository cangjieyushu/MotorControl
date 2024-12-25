/**************************************************************************************************/
/**
 * @file      : Gpio_Drv.h
 * @brief     : GPIO module driver header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef GPIO_DRV_H
#define GPIO_DRV_H

#include "Common_Drv.h"

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */
/** @defgroup Public_TypeDefinition
 *  @{
 */
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
    GPIO_15                           /*!< GPIO15 Pin */
} Port_GpioNumType;

/**
 *  @brief PORT pull type definition
 */
typedef enum
{
    PORT_PULL_DISABLED = 0U,          /*!< PORT pull none */
    PORT_PULL_DOWN     = 2U,          /*!< PORT pull down */
    PORT_PULL_UP       = 3U           /*!< PORT pull up   */
} Port_PullType;

/**
 *  @brief PORT slew rate type definition
 */
typedef enum
{
    PORT_FAST_RATE = 0U,              /*!< PORT fast rate */
    PORT_SLOW_RATE                    /*!< PORT slow rate */
} Port_SlewRateType;

/**
 *  @brief PORT interrupt configuration type definition
 */
typedef enum
{
    PORT_ISF_DISABLED = 0U,                /*!< PORT isf disabled          */
    PORT_ISF_INT_LOGIC_0 = 8U,             /*!< PORT isf interrupt logic 0 */
    PORT_ISF_INT_RISING_EDGE = 9U,         /*!< PORT isf interrupt rising  */
    PORT_ISF_INT_FALLING_EDGE = 10U,       /*!< PORT isf interrupt falling */
    PORT_ISF_INT_BOTH_EDGE = 11U,          /*!< PORT isf interrupt both    */
    PORT_ISF_INT_LOGIC_1 = 12U             /*!< PORT isf interrupt logic 1 */
} Port_IntConfigType;

/**
 *  @brief PORT Pinmux function type definition
 */
typedef enum
{
    PINMUX_FUNCTION_0 = 0U,           /*!< PORT pin mux function 0 */
    PINMUX_FUNCTION_1,                /*!< PORT pin mux function 1 */
    PINMUX_FUNCTION_2,                /*!< PORT pin mux function 2 */
    PINMUX_FUNCTION_3,                /*!< PORT pin mux function 3 */
    PINMUX_FUNCTION_4,                /*!< PORT pin mux function 4 */
    PINMUX_FUNCTION_5,                /*!< PORT pin mux function 5 */
    PINMUX_FUNCTION_6,                /*!< PORT pin mux function 6 */
    PINMUX_FUNCTION_7                 /*!< PORT pin mux function 7 */
} Port_PinMuxFuncType;

/**
 *  @brief PORT pin configuration struct definition
 */
typedef struct
{
    Port_PullType                 PullConfig;       /*!< Configure pull type:
                                                       - PORT_PULL_DISABLE(0)
                                                       - PORT_PULL_DOWN(2)
                                                       - PORT_PULL_UP(3)
                                                    */
    Port_SlewRateType             SlewRateConfig;  /*!< Configure slew rate type:
                                                        - PORT_FAST_RATE(0)
                                                        - PORT_SLOW_RATE(1)
                                                     */
    Common_ControlStateType       OpenDrainConfig;  /*!< Configure the enable of the open drain,
                                                        - COMMON_DISABLE
                                                        - COMMON_ENABLE
                                                    */
    Common_ControlStateType       FilterEnable;  /*!< Configure the enable of the filter,
                                                     - COMMON_DISABLE
                                                     - COMMON_ENABLE
                                                  */
    uint8                         FilterConfig;  /*!< Configure filter:0x0-0x1F */
} Port_PinConfigType;

/**
 *  @brief GPIO data direction type definition
 */
typedef enum
{
    GPIO_INPUT = 0U,                    /*!< Set GPIO Port data direction as input  */
    GPIO_OUTPUT                         /*!< Set GPIO Port data direction as output */
} Gpio_DirType;

/**
 *  @brief GPIO data Input/Output type definition
 */
typedef enum
{
    GPIO_LOW = 0U,                      /*!< Input/Output low level(0) */
    GPIO_HIGH                           /*!< Input/Output low level(1) */
} Gpio_LevelType;

/** @} end of group Public_TypeDefinition */

/** @addtogroup Public_MacroDefinition
 *  @{
 */

/* PTA0 pinmux function definition */
#define PTA0_GPIO                             PINMUX_FUNCTION_1 
#define PTA0_SPI_SCLK                         PINMUX_FUNCTION_2 
#define PTA0_TIM_CHI0                         PINMUX_FUNCTION_3 
#define PTA0_MCPWM_CHO2                       PINMUX_FUNCTION_4 
#define PTA0_NMI_b                            PINMUX_FUNCTION_7 

/* PTA1 pinmux function definition */
#define PTA1_GPIO                             PINMUX_FUNCTION_1 
#define PTA1_SPI_SOUT                         PINMUX_FUNCTION_2 
#define PTA1_TIM_CHI1                         PINMUX_FUNCTION_3 
#define PTA1_MCPWM_CHO3                       PINMUX_FUNCTION_4 
#define PTA1_CLKOUT                           PINMUX_FUNCTION_5 

/* PTA2 pinmux function definition */
#define PTA2_GPIO                             PINMUX_FUNCTION_1 
#define PTA2_SPI_SIN                          PINMUX_FUNCTION_2 
#define PTA2_TIM_CHI2                         PINMUX_FUNCTION_3 
#define PTA2_MCPWM_CHO6                       PINMUX_FUNCTION_4 

/* PTA3 pinmux function definition */
#define PTA3_GPIO                             PINMUX_FUNCTION_1 
#define PTA3_SPI_CS0                          PINMUX_FUNCTION_2  
#define PTA3_TIM_CHI1                         PINMUX_FUNCTION_3 
#define PTA3_MCPWM_CHO0                       PINMUX_FUNCTION_4 

/* PTA4 pinmux function definition */
#define PTA4_GPIO                             PINMUX_FUNCTION_1 
#define PTA4_TIM_CHI3                         PINMUX_FUNCTION_3 
#define PTA4_MCPWM_EXTCLK                     PINMUX_FUNCTION_4 
#define PTA4_SWD_DIO                          PINMUX_FUNCTION_7 

/* PTA5 pinmux function definition */
#define PTA5_GPIO                             PINMUX_FUNCTION_1 
#define PTA5_TIM_CHI0                         PINMUX_FUNCTION_3 
#define PTA5_MCPWM_CHO7                       PINMUX_FUNCTION_4 
#define PTA5_MCPWM_FLT                        PINMUX_FUNCTION_5 
#define PTA5_SWD_CLK                          PINMUX_FUNCTION_7 

/* PTA6 pinmux function definition */
#define PTA6_GPIO                             PINMUX_FUNCTION_1 
#define PTA6_SPI_SIN                          PINMUX_FUNCTION_2 
#define PTA6_TIM_CHI1                         PINMUX_FUNCTION_3 
#define PTA6_MCPWM_EXTCLK                     PINMUX_FUNCTION_4 
#define PTA6_MCPWM_FLT                        PINMUX_FUNCTION_5 
#define PTA6_UART_TX                          PINMUX_FUNCTION_7 

/* PTA7 pinmux function definition */
#define PTA7_GPIO                             PINMUX_FUNCTION_1 
#define PTA7_SPI_SCLK                         PINMUX_FUNCTION_2 
#define PTA7_TIM_CHI1                         PINMUX_FUNCTION_3 
#define PTA7_MCPWM_CHO1                       PINMUX_FUNCTION_4 
#define PTA7_MCPWM_FLT                        PINMUX_FUNCTION_5 
#define PTA7_NMI_b                            PINMUX_FUNCTION_7 

/* PTA8 pinmux function definition */
#define PTA8_ADC_CH0                          PINMUX_FUNCTION_0 
#define PTA8_GPIO                             PINMUX_FUNCTION_1 
#define PTA8_SPI_SOUT                         PINMUX_FUNCTION_2 
#define PTA8_TIM_CHI2                         PINMUX_FUNCTION_3 
#define PTA8_MCPWM_CHO1                       PINMUX_FUNCTION_4 
#define PTA8_MCPWM_EXTCLK                     PINMUX_FUNCTION_5 

/* PTA9 pinmux function definition */
#define PTA9_ADC_CH2                          PINMUX_FUNCTION_0 
#define PTA9_GPIO                             PINMUX_FUNCTION_1 
#define PTA9_SPI_CS1                          PINMUX_FUNCTION_2 
#define PTA9_TIM_CHI1                         PINMUX_FUNCTION_3 
#define PTA9_MCPWM_CHO4                       PINMUX_FUNCTION_4 
#define PTA9_MCPWM_EXTCLK                     PINMUX_FUNCTION_5 

/* PTA10 pinmux function definition */
#define PTA10_ADC_CH3                         PINMUX_FUNCTION_0 
#define PTA10_GPIO                            PINMUX_FUNCTION_1 
#define PTA10_SPI_SIN                         PINMUX_FUNCTION_2 
#define PTA10_TIM_CHI1                        PINMUX_FUNCTION_3 
#define PTA10_MCPWM_CHO5                      PINMUX_FUNCTION_4 
#define PTA10_CLKOUT                          PINMUX_FUNCTION_5 
#define PTA10_UART_RX                         PINMUX_FUNCTION_7 

/* PTA11 pinmux function definition */
#define PTA11_ADC_CH4_EXTAL                   PINMUX_FUNCTION_0 
#define PTA11_GPIO                            PINMUX_FUNCTION_1 
#define PTA11_TIM_CHI0                        PINMUX_FUNCTION_3 
#define PTA11_MCPWM_CHO2                      PINMUX_FUNCTION_4 

/* PTA12 pinmux function definition */
#define PTA12_ADC_CH5_XTAL                    PINMUX_FUNCTION_0 
#define PTA12_GPIO                            PINMUX_FUNCTION_1 
#define PTA12_TIM_CHI2                        PINMUX_FUNCTION_3 
#define PTA12_MCPWM_CHO4                      PINMUX_FUNCTION_4 

/* PTA13 pinmux function definition */
#define PTA13_ADC_CH6                         PINMUX_FUNCTION_0 
#define PTA13_GPIO                            PINMUX_FUNCTION_1 
#define PTA13_SPI_CS1                         PINMUX_FUNCTION_2 
#define PTA13_TIM_CHI3                        PINMUX_FUNCTION_3 
#define PTA13_MCPWM_CHO7                      PINMUX_FUNCTION_4 

/* PTA14 pinmux function definition */
#define PTA14_ADC_CH7                         PINMUX_FUNCTION_0 
#define PTA14_GPIO                            PINMUX_FUNCTION_1 
#define PTA14_SPI_SIN                         PINMUX_FUNCTION_2 
#define PTA14_MCPWM_FLT                       PINMUX_FUNCTION_5 

/* PTA15 pinmux function definition */
#define PTA15_ADC_CH8                         PINMUX_FUNCTION_0 
#define PTA15_GPIO                            PINMUX_FUNCTION_1 
#define PTA15_TIM_CHI1                        PINMUX_FUNCTION_3 
#define PTA15_MCPWM_CHO0                      PINMUX_FUNCTION_4 
#define PTA15_MCPWM_FLT                       PINMUX_FUNCTION_5  
/** @} end of group Public_MacroDefinition */


/** @defgroup Public_FunctionDeclaration
 *  @{
 */
/**
 *  @brief gpio 0-15 callback function type
 */
typedef void (*Port_CallbackType)(Port_GpioNumType GpioNum);

/**
 * @brief        Lock or unlock pin pcr register.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    LockCtrl: COMMON_DISABLE or COMMON_ENABLE.
 *
 * @return none.
 *
 */
void Port_LockPin(Port_GpioNumType GpioNum, Common_ControlStateType LockCtrl);

/**
 * @brief        Configure pins with the same global configuration
 * If a pin is locked, global control will not work on it
 *
 * @param[in]    Pins: Select the GPIO pins.
 * @param[in]    Value: Set GPIO pin global value.
 *
 * @return none.
 *
 */
void Port_ConfigGlobalPins(uint32 Pins, uint32 Value);

/**
 * @brief        Initialize seleted pin with the given configuration structure.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    ConfigPtr: Pin configuration struct.
 *
 * @return none.
 *
 */
void Port_InitPin(Port_GpioNumType GpioNum, const Port_PinConfigType* ConfigPtr);

/**
 * @brief        Configure the pin mux function.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    PinMuxFunc: Pin mux function.
 *
 * @return none.
 *
 */
void Port_ConfigPinmux(Port_GpioNumType GpioNum, Port_PinMuxFuncType PinMuxFunc);

/**
 * @brief        Configure the pin interrupt configuration.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    IntConfig: Pin interrupt configuration.
 *                         - PORT_ISF_DISABLED(0)
 *                         - PORT_ISF_INT_LOGIC_0(8)
 *                         - PORT_ISF_INT_RISING_EDGE(9)
 *                         - PORT_ISF_INT_FALLING_EDGE(10)
 *                         - PORT_ISF_INT_BOTH_EDGE(11)
 *                         - PORT_ISF_INT_LOGIC_1(12)
 *
 * @return none.
 */
void Port_ConfigPinInt(Port_GpioNumType GpioNum, Port_IntConfigType IntConfig);

/**
 * @brief        Configure the pin pull configuration.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    PullConfig: Pin pull configuration, should be
 *                          PORT_PULL_NONE, PORT_PULL_DOWN and PORT_PULL_UP.
 *
 * @return none.
 *
 */
void Port_ConfigPull(Port_GpioNumType GpioNum, Port_PullType PullConfig);

/**
 * @brief        Configure the pin slew rate configuration.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    SlewRateCtrl: Pin slew rate configuration, should be PORT_FAST_RATE and 
 *                             PORT_SLOW_RATE.
 *
 * @return none.
 *
 */
void Port_ConfigSlewRate(Port_GpioNumType GpioNum, Port_SlewRateType SlewRateCtrl);

/**
 * @brief        Enable/Disable the pin filter .
 *
 * This function enables/disables the pin filter.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    FilterCtrl: Filter configuration, should be DISABLE and ENABLE.
 *
 * @return none.
 *
 */
void Port_EnableFilter(Port_GpioNumType GpioNum, Common_ControlStateType FilterCtrl);

/**
 * @brief        Configure the pin filter.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    FilterValue: Pin filter configuration, the value is 0x0 - 0x1F.
 *
 * @return none.
 *
 */
void Port_ConfigFilter(Port_GpioNumType GpioNum, uint8 FilterValue);
/**
 * @brief        Enable or disable the pin open drain mode.
 *
 * This function configures the pin open drain.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    OpenDrainCtrl: Pin open drain configuration, should be COMMON_DISABLE and 
 *                              COMMON_ENABLE 
 *                             
 *
 * @return none.
 *
 */
void Port_EnableOpenDrainMode(Port_GpioNumType GpioNum,
                         Common_ControlStateType OpenDrainCtrl);
/**
 * @brief        Port install call back function
 *
 * @param[in]    CbFun: Pointer to callback function.
 *
 * @return none
 *
 */
void Port_InstallCallbackFunc(Port_CallbackType CbFun);

/**
 * @brief        Get pin interrupt status function
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 *
 * @return     Interrupt status of a pin.
 *
 */
Common_FlagStatusType Port_GetIntStatus(Port_GpioNumType GpioNum);

/**
 * @brief       Get all pins interrupt status of Port A.
 *
 * @return     All Pins interrupt status of a Port.
 *
 */
uint32 Port_GetAllPinsIntStatus(void);

/**
 * @brief        Clear the pin interrupt status function.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 *
 * @return      none.
 *
 */
void Port_ClearPinInt(Port_GpioNumType GpioNum);

/**
 * @brief        Clear all pins interrupt status function.
 *
 * @param[in]    ClrPins: Select pins no, a bit is a pin, bit0-gpio0,...
 *
 * @return     none.
 *
 */
void Port_ClearPinsInt(uint32 ClrPins);

/**
 * @brief        Set the pin direction configuration.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    Direction: Select I/O direction of a pin.
 *                       - 0: corresponding pin is set to input
 *                       - 1: corresponding pin is set to output
 *
 * @return none.
 *
 */
void Gpio_SetPinDir(Port_GpioNumType GpioNum, Gpio_DirType Direction);

/**
 * @brief        Set the direction configuration for all pins.
 *
 * @param[in]    PinsDir: Select I/O directions.
 *                        - 0: corresponding pin is set to input
 *                        - 1: corresponding pin is set to output
 *
 * @return none.
 *
 */
void Gpio_SetPinsDir(uint32 PinsDir);

/**
 * @brief        Write a pin with a given value.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    Level: Pin value.
 *                     - 0: corresponding pin is set to LOW
 *                     - 1: corresponding pin is set to HIGH
 *
 * @return none.
 *
 */
void Gpio_WritePinOutput(Port_GpioNumType GpioNum, Gpio_LevelType Level);

/**
 * @brief        Write  pins  with the given value.
 *
 * @param[in]    Value: Pins value.
 *                     - 0: corresponding pin is set to LOW
 *                     - 1: corresponding pin is set to HIGH
 *
 * @return none.
 *
 */
void Gpio_WritePinsOutput(uint32 Value);

/**
 * @brief      Write a pin to 'Clear' value.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 *
 * @return none.
 *
 */
void Gpio_ClearPinOutput(Port_GpioNumType GpioNum);

/**
 * @brief        Write pins to 'Clear' value
 *
 * @param[in]    Pins: Clean the GPIO pins.
 *
 * @return none.
 *
 */
void Gpio_ClearPinsOutput(uint32 Pins);

/**
 * @brief        Write a pin with 'Set' value.
 *
 * @param[in] GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 *
 * @return none.
 *
 */
void Gpio_SetPinOutput(Port_GpioNumType GpioNum);

/**
 * @brief        Write  pins with 'Set' value.
 *
 * @param[in]    Pins: Set the GPIO pins.
 *
 * @return none.
 *
 */
void Gpio_SetPinsOutput(uint32 Pins);

/**
 * @brief        Toggle a pin value.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 *
 * @return none.
 *
 */
void Gpio_TogglePinOutput(Port_GpioNumType GpioNum);

/**
 * @brief        Toggle pins value.
 *
 * @param[in]    Pins: Toggle the GPIO pins.
 *
 * @return none.
 *
 */
void Gpio_TogglePinsOutput(uint32 Pins);

/**
 * @brief       Read a pin value.
 *
 * @param[in]   GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 *
 * @return      GPIO_HIGH or GPIO_LOW.
 *
 */
Gpio_LevelType Gpio_ReadPinLevel(Port_GpioNumType GpioNum);

/**
 * @brief        Read  pins value.
 *
 * @param[in]    None.
 *
 * @return       Pins value.
 *
 */
uint32 Gpio_ReadPinsLevel(void);

/** @} end of group Public_FunctionDeclaration */

#endif /* GPIO_DRV_H */
