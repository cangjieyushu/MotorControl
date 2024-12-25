/**************************************************************************************************/
/**
 * @file      : Ctimer_Drv.h
 * @brief     : Ctimer driver module header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef CTIMER_DRV_H
#define CTIMER_DRV_H

#include "Common_Drv.h"

/** @defgroup Public_MacroDefinition
 *  @{
 */

/** @} end of group Public_MacroDefinition */

/** @defgroup Public_TypeDefinition 
 *  @{
 */
/**
 *  @brief Ctimer capture timer unit type definition
 */
typedef enum
{
    CTIMER_UNIT_0 = 0U,        /*!< Capture timer unit 0. */
    CTIMER_UNIT_1,             /*!< Capture timer unit 1. */
    CTIMER_UNIT_2              /*!< Capture timer unit 2. */
} Ctimer_CaptureUnitType;

/**
 *  @brief Ctimer channel selection for UNIT1 type definition
 */
typedef enum
{
    CTIMER_CHANNEL_1 = 0U,     /*!< Select channel input [1]. */
    CTIMER_CHANNEL_2,          /*!< Select channel input [2]. */
    CTIMER_CHANNEL_3           /*!< Select channel input [3]. */
} Ctimer_ChannelSelectionType;

/**
 *  @brief Ctimer channel filter type definition
 */
typedef enum
{
    CTIMER_FILTER_DISABLE = 0U,    /*!< Filter disabled */
    CTIMER_FILTER_1,               /*!< 1 cycle glitch filter out */
    CTIMER_FILTER_2,               /*!< 2 cycle glitch filter out */
    CTIMER_FILTER_3,               /*!< 3 cycle glitch filter out */
    CTIMER_FILTER_4,               /*!< 4 cycle glitch filter out */
    CTIMER_FILTER_5,               /*!< 5 cycle glitch filter out */
    CTIMER_FILTER_6,               /*!< 6 cycle glitch filter out */
    CTIMER_FILTER_7,               /*!< 7 cycle glitch filter out */
    CTIMER_FILTER_8,               /*!< 8 cycle glitch filter out */
    CTIMER_FILTER_9,               /*!< 9 cycle glitch filter out */
    CTIMER_FILTER_10,              /*!< 10 cycle glitch filter out */
    CTIMER_FILTER_11,              /*!< 11 cycle glitch filter out */
    CTIMER_FILTER_12,              /*!< 12 cycle glitch filter out */
    CTIMER_FILTER_13,              /*!< 13 cycle glitch filter out */
    CTIMER_FILTER_14,              /*!< 14 cycle glitch filter out */
    CTIMER_FILTER_15               /*!< 15 cycle glitch filter out */
} Ctimer_ChannelFilterType;

/**
 *  @brief Ctimer bridge control mode type definition
 */
typedef enum
{
    CTIMER_EDGE_DISABLE = 0U,         /*!< Disabled */
    CTIMER_EDGE_RISING,               /*!< Rising edge */
    CTIMER_EDGE_FALLING,              /*!< Falling edge */
    CTIMER_EDGE_DUAL                  /*!< Dual edge */
} Ctimer_EdgeType;

/**
 *  @brief Ctimer driver shutdown definition
 */
typedef enum
{
    CTIMER_INT_RISING_UNIT_0 = 0U, /*!< Interrupt Enable on rising edge of channel input to UNIT0 */
    CTIMER_INT_RISING_UNIT_1,      /*!< Interrupt Enable on rising edge of channel input to UNIT1 */
    CTIMER_INT_RISING_UNIT_2,      /*!< Interrupt Enable on rising edge of channel input to UNIT2 */
    CTIMER_INT_FALLING_UNIT_0,   /*!< Interrupt Enable on falling edge of channel input to UNIT0 */
    CTIMER_INT_FALLING_UNIT_1,   /*!< Interrupt Enable on falling edge of channel input to UNIT1 */
    CTIMER_INT_FALLING_UNIT_2,   /*!< Interrupt Enable on falling edge of channel input to UNIT2 */
    CTIMER_INT_OVERFLOW_UNIT_0,  /*!< Interrupt Enable on overflow of channel input to UNIT0 */
    CTIMER_INT_OVERFLOW_UNIT_1,  /*!< Interrupt Enable on overflow of channel input to UNIT1 */
    CTIMER_INT_OVERFLOW_UNIT_2,  /*!< Interrupt Enable on overflow of channel input to UNIT2 */
    CTIMER_INT_ALL               /*!< Interrupt Enable All */
} Ctimer_IntType;


/**
 *  @brief Ctimer unit configuration structure type definition
 */
typedef struct
{
    Ctimer_CaptureUnitType UnitType;    /*!< Capture timer unit type */ 
    Ctimer_EdgeType DetectMode;         /*!< Detect Input Edge Mode */
    Ctimer_EdgeType ClearMode;          /*!< Clear Input Edge Mode */
    uint16 OverflowValue;               /*!< Overflow Value */
} Ctimer_UnitConfigType;

/**
 *  @brief Ctimer configuration structure type definition
 */
typedef struct
{
    Ctimer_ChannelFilterType FilterType;       /*!< Channel filter type */ 
    Ctimer_ChannelSelectionType ChannelType;   /*!< Channel selection for UNIT1 type */
    uint8 UnitNumber;                          /*!< Unit Number */
    const Ctimer_UnitConfigType * UnitConfig;  /*!< unit configuration structure */
} Ctimer_ConfigType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief      Ctimer Config Function
 *
 * @param[in]  Config: Pointer to a configuration structure.
 *
 * @return     None
 *
 */
void Ctimer_Config(const Ctimer_ConfigType * Config);

/**
 * @brief      Module Enable Function
 *
 * @param[in]  None.
 *
 * @return     None
 *
 */
void Ctimer_Enable(void);

/**
 * @brief      Module Disable Function
 *
 * @param[in]  None.
 *
 * @return     None
 *
 */
void Ctimer_Disable(void);

/**
 * @brief      Set Channel Filter Function
 *
 * @param[in]  FilterType: Select channel filter type.
 *              - CTIMER_FILTER_DISABLE
 *              - CTIMER_FILTER_1
 *              - CTIMER_FILTER_2
 *              - CTIMER_FILTER_3
 *              - CTIMER_FILTER_4
 *              - CTIMER_FILTER_5
 *              - CTIMER_FILTER_6
 *              - CTIMER_FILTER_7
 *              - CTIMER_FILTER_8
 *              - CTIMER_FILTER_9
 *              - CTIMER_FILTER_10
 *              - CTIMER_FILTER_11
 *              - CTIMER_FILTER_12
 *              - CTIMER_FILTER_13
 *              - CTIMER_FILTER_14
 *              - CTIMER_FILTER_15
 *
 * @return     None
 *
 */
void Ctimer_SetChannelFilter(Ctimer_ChannelFilterType FilterType);

/**
 * @brief      Select Channel For Unit1 Function
 *
 * @param[in]  ChannelType: Select channel type.
 *              - CTIMER_CHANNEL_1
 *              - CTIMER_CHANNEL_2
 *              - CTIMER_CHANNEL_3
 *
 * @return     None
 *
 */
void Ctimer_SelectUnit1Channel(Ctimer_ChannelSelectionType ChannelType);

/**
 * @brief      Detect Input Edge Mode Function
 *
 * @param[in]  UnitType: Select Unit type.
 *              - CTIMER_UNIT_0
 *              - CTIMER_UNIT_1
 *              - CTIMER_UNIT_2
 * @param[in]  EdgeType: Select Edge type.
 *              - CTIMER_EDGE_DISABLE
 *              - CTIMER_EDGE_RISING
 *              - CTIMER_EDGE_FALLING
 *              - CTIMER_EDGE_DUAL
 *
 * @return     None
 *
 */
void Ctimer_DetectEdgeMode(Ctimer_CaptureUnitType UnitType, Ctimer_EdgeType EdgeType);

/**
 * @brief      Clear Input Edge Mode Function
 *
 * @param[in]  UnitType: Select Unit type.
 *              - CTIMER_UNIT_0
 *              - CTIMER_UNIT_1
 *              - CTIMER_UNIT_2
 * @param[in]  EdgeType: Select Edge type.
 *              - CTIMER_EDGE_DISABLE
 *              - CTIMER_EDGE_RISING
 *              - CTIMER_EDGE_FALLING
 *              - CTIMER_EDGE_DUAL
 *
 * @return     None
 *
 */
void Ctimer_TimerClearMode(Ctimer_CaptureUnitType UnitType, Ctimer_EdgeType EdgeType);

/**
 * @brief      Set Overflow Value Function
 *
 * @param[in]  UnitType: Select Unit type.
 *              - CTIMER_UNIT_0
 *              - CTIMER_UNIT_1
 *              - CTIMER_UNIT_2
 * @param[in]  Value: Overflow Value.
 *
 * @return     None
 *
 */
void Ctimer_SetOverflowValue(Ctimer_CaptureUnitType UnitType, uint16 Value);

/**
 * @brief      Get Rising Edge Capture Value Function
 *
 * @param[in]  UnitType: Select Unit type.
 *              - CTIMER_UNIT_0
 *              - CTIMER_UNIT_1
 *              - CTIMER_UNIT_2
 *
 * @return     uint16: Capture Value.
 *
 */
uint16 Ctimer_GetRisingCaptureValue(Ctimer_CaptureUnitType UnitType);

/**
 * @brief      Get Falling Edge Capture Value Function
 *
 * @param[in]  UnitType: Select Unit type.
 *              - CTIMER_UNIT_0
 *              - CTIMER_UNIT_1
 *              - CTIMER_UNIT_2
 *
 * @return     uint16: Capture Value.
 *
 */
uint16 Ctimer_GetFallingCaptureValue(Ctimer_CaptureUnitType UnitType);

/**
 * @brief      Ctimer Set INT Mask/Unmask Function
 *
 * @param[in]  IntType: Select Int type.
 *              - CTIMER_INT_RISING_UNIT_0
 *              - CTIMER_INT_RISING_UNIT_1
 *              - CTIMER_INT_RISING_UNIT_2
 *              - CTIMER_INT_FALLING_UNIT_0
 *              - CTIMER_INT_FALLING_UNIT_1
 *              - CTIMER_INT_FALLING_UNIT_2
 *              - CTIMER_INT_OVERFLOW_UNIT_0
 *              - CTIMER_INT_OVERFLOW_UNIT_1
 *              - CTIMER_INT_OVERFLOW_UNIT_2
 *              - CTIMER_INT_ALL
 * @param[in]  IntMask: Mask/Unmask.
 *              - COMMON_UNMASK
 *              - COMMON_MASK
 *
 * @return     None
 *
 */
void Ctimer_SetIntMask(Ctimer_IntType IntType, Common_IntMaskType IntMask);

/**
 * @brief      Ctimer Clear INT Status Function
 *
 * @param[in]  IntType: Select Int type.
 *              - CTIMER_INT_RISING_UNIT_0
 *              - CTIMER_INT_RISING_UNIT_1
 *              - CTIMER_INT_RISING_UNIT_2
 *              - CTIMER_INT_FALLING_UNIT_0
 *              - CTIMER_INT_FALLING_UNIT_1
 *              - CTIMER_INT_FALLING_UNIT_2
 *              - CTIMER_INT_OVERFLOW_UNIT_0
 *              - CTIMER_INT_OVERFLOW_UNIT_1
 *              - CTIMER_INT_OVERFLOW_UNIT_2
 *              - CTIMER_INT_ALL
 *
 * @return     None
 *
 */
void Ctimer_ClearIntStatus(Ctimer_IntType IntType);

/**
 * @brief      Ctimer Get INT status Function
 *
 * @param[in]  IntType: Select Int type.
 *              - CTIMER_INT_RISING_UNIT_0
 *              - CTIMER_INT_RISING_UNIT_1
 *              - CTIMER_INT_RISING_UNIT_2
 *              - CTIMER_INT_FALLING_UNIT_0
 *              - CTIMER_INT_FALLING_UNIT_1
 *              - CTIMER_INT_FALLING_UNIT_2
 *              - CTIMER_INT_OVERFLOW_UNIT_0
 *              - CTIMER_INT_OVERFLOW_UNIT_1
 *              - CTIMER_INT_OVERFLOW_UNIT_2
 *              - CTIMER_INT_ALL
 *
 * @return     IntStatus
 *              - COMMON_RESET
 *              - COMMON_SET
 *
 */
Common_IntStatusType Ctimer_GetIntStatus(Ctimer_IntType IntType);

/**
 * @brief      Ctimer install interrupt callback function
 *
 * @param[in]  IntType: Select Int type.
 *              - CTIMER_INT_RISING_UNIT_0
 *              - CTIMER_INT_RISING_UNIT_1
 *              - CTIMER_INT_RISING_UNIT_2
 *              - CTIMER_INT_FALLING_UNIT_0
 *              - CTIMER_INT_FALLING_UNIT_1
 *              - CTIMER_INT_FALLING_UNIT_2
 *              - CTIMER_INT_OVERFLOW_UNIT_0
 *              - CTIMER_INT_OVERFLOW_UNIT_1
 *              - CTIMER_INT_OVERFLOW_UNIT_2
 * @param[in]  CbFun: Callback function .
 *
 * @return     None
 * @note       CTIMER_INT_ALL is invalid as input 
 */
void Ctimer_InstallCallBackFunc(Ctimer_IntType IntType, Isr_CbFuncType * CbFun);

/** @} end of group Public_FunctionDeclaration */

#endif /* CTIMER_DRV_H */

