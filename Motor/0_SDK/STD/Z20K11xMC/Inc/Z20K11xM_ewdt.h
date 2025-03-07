/**************************************************************************************************/
/**
 * @file      : Z20K11xM_ewdt.h
 * @brief     : EWDT driver module header file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef Z20K11XM_EWDT_H
#define Z20K11XM_EWDT_H

#include "Z20K11xM_drv.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @addtogroup  EWDT
 *  @{
 */

/** @defgroup EWDT_Public_Types
 *  @{
 */

/*!
 * @brief EWDT input pin configuration definition.
 * Implements : EWDT_Input_Status_t_Class
 */
typedef enum
{
    EWM_INPUT_DISABLED = 0U,   /*!< Input pin disabled                */
    EWM_INPUT_ASSERT_LOW = 1U, /*!< Input pin asserts when on low level */
    EWM_INPUT_ASSERT_HIGH = 3U /*!< Input pin asserts when on high level */
} EWDT_InputStatus_t;

/*!
 * @brief EWDT operate mode configuration structure.
 *
 * This structure configures the wdog operation mode.
 * Implements : EWDT_OperationMode_t_Class
 */
typedef struct
{
    ControlState_t wait;  /*!< Wait mode control
                               - ENABLE: counter countinue
                               - DISABLE: counter halt */
    ControlState_t debug; /*!< debug mode control
                               - ENABLE: counter countinue
                               - DISABLE: counter halt */
} EWDT_OperationMode_t;

/*!
 * @brief EWDT configuration structure.
 *
 * This structure configures the basic attribute.
 * Implements : EWDT_Config_t_Class
 */
typedef struct
{
    EWDT_InputStatus_t input;    /*!< input config */
    ControlState_t     wait;     /*!< Wait mode control
                                      - ENABLE: counter countinue
                                      - DISABLE: counter halt */
    ControlState_t debug;        /*!< debug mode control
                                      - ENABLE: counter countinue
                                      - DISABLE: counter halt */
    IntMask_t      intMask;      /*!< int mask */
    uint32_t       cmpLowValue;  /*!< The window value: 32 bits */
    uint32_t       cmpHighValue; /*!< The timeout value: 32 bits */
    ControlState_t enable;       /*!< ewdt control
                                      - ENABLE: enable ewdt
                                      - DISABLE: disable ewdt */
} EWDT_Config_t;

/**
 *  @brief EWDT interrupt type definition
 */
typedef enum
{
    EWDT_INT_OUTPUTASSERT = 0U, /*!< ewdt output assert interrupt */
    EWDT_INT_ALL                /*!< all interrupt */
} EWDT_INT_t;

/** @} end of group EWDT_Public_Types */

/** @defgroup EWDT_Public_Constants
 *  @{
 */

/** @} end of group EWDT_Public_Constants */

/** @defgroup EWDT_Public_Macro
 *  @{
 */

/** @} end of group EWDT_Public_Macro */

/** @defgroup EWDT_Public_FunctionDeclaration
 *  @brief EWDT functions declaration
 *  @{
 */

/**
 * @brief      ewdt Initializes Function
 *
 * @param[in]  ptEWDTInitConfig:     Pointer to a EWDT configuration structure.
 *
 * @return Initializes operate flag
 *
 */
ResultStatus_t EWDT_Init(const EWDT_Config_t *ptEWDTInitConfig);

/**
 * @brief      refresh ewdt count Function
 *
 * @param[in]  none
 *
 * @note       If user has no need to enable irq, in next step user should
 *             disable_irq after calling this function.
 *
 * @return none.
 *
 */
void EWDT_Refresh(void);

/**
 * @brief      get ewdt input pin assertion config Function
 *
 * @param[in]  none
 *
 * @return     input pin assertion config status.
 *
 */
EWDT_InputStatus_t EWDT_GetInputAssertConfig(void);

/**
 * @brief      get ewdt compare low reg value Function
 *
 * @param[in]  none
 *
 * @return compare low reg value.
 *
 */
uint32_t EWDT_GetCompareLowValue(void);

/**
 * @brief      get ewdt compare high reg value Function
 *
 * @param[in]  none
 *
 * @return compare high reg value.
 *
 */
uint32_t EWDT_GetCompareHighValue(void);

/**
 * @brief      get ewdt counter current value Function
 *
 * @param[in]  none
 *
 * @return current counter count value.
 *
 */
uint32_t EWDT_GetCounter(void);

/**
 * @brief      get flag indcates ewdt is enable/disable Function
 *
 * @param[in]  none
 *
 * @return     ewdt enable status.
 *
 */
FlagStatus_t EWDT_GetEnableStatus(void);

/**
 * @brief      get interrupt mask Function
 *
 * @param[in]  intType: int type
 *                      - EWDT_INT_OUTPUTASSERT: ewdt out assert int
 *                      - EWDT_INT_ALL: all int type
 *
 * @return     interrupt mask.
 *
 */
IntMask_t EWDT_GetIntMaskStatus(EWDT_INT_t intType);

/**
 * @brief      clear ewdt interrupt flag Function
 *
 * @param[in]  intType: int type
 *                      - EWDT_INT_OUTPUTASSERT: ewdt out assert int
 *                      - EWDT_INT_ALL: all int type
 *
 * @return none.
 *
 */
void EWDT_ClearIntStatus(EWDT_INT_t intType);

/**
 * @brief      get ewdt int flag Function
 *
 * @param[in]  intType: int type
 *                      - EWDT_INT_OUTPUTASSERT: ewdt out assert int
 *                      - EWDT_INT_ALL: all int type
 *
 * @return whether a int is asserted or not.
 *
 */
IntStatus_t EWDT_GetIntStatus(EWDT_INT_t intType);

/**
 * @brief      Install callback function
 *
 * @param[in]  intType: select interrrupt type
 *                      - EWDT_INT_OUTPUTASSERT: ewdt out assert int
 *                      - EWDT_INT_ALL: all int type
 * @param[in]  cbFun: indicate callback function
 *
 * @return    none
 *
 */
void EWDT_InstallCallBackFunc(EWDT_INT_t intType, isr_cb_t *cbFun);

/** @} end of group EWDT_Public_FunctionDeclaration */

/** @} end of group EWDT  */

/** @} end of group Z20K11X_Peripheral_Driver */

#endif /* Z20K11XM_EWDT_H */
