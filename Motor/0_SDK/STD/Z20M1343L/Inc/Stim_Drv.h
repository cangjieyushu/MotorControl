/**************************************************************************************************/
/**
 * @file      : Stim_Drv.h
 * @brief     : Stim module driver header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef STIM_DRV_H
#define STIM_DRV_H

#include "Common_Drv.h"

/** @defgroup Public_MacroDefinition
 *  @{
 */

/** @} end of Public_MacroDefinition */

/** @defgroup Public_TypeDefinition
 *  @{
 */

/**
 * @brief     Stim mode type definition
 */
typedef enum
{
    STIM_MATCH = 0U,                      /*!< timer operates in match mode. */
    STIM_FREERUN                           /*!< timer operates in freerun mode. */
} Stim_ModeType;

/**
 * @brief     Stim configuration struct definition
 */
typedef struct
{
    Stim_ModeType FreerunMode;          /*!< Configure mode type.
                                                - STIM_MATCH
                                                - STIM_FREERUN*/
    uint32  MatchValue;                 /*!< If timer is running on match mode, when timer counting 
                                                up to this match value, it triggers interrupt and 
                                                timer restart from 0.
                                                On write, timer is clear to 0. */
} Stim_ConfigType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief     Install call back function.
 * 
 * @param[in] CbFun: pointer to callback function.
 * 
 * @return    None
 */
void Stim_InstallCallBackFunc(Isr_CbFuncType * CbFun);

/**
 * @brief     Initialize stim configuration.
 * 
 * @param[in] StimConfigStruct: Stim configuration struct.
 * 
 * @return    None
 */
void Stim_Init(const Stim_ConfigType* StimConfigStruct);

/**
 * @brief     Set match value.
 * 
 * @param[in] MatValue: Stim match value.
 * 
 * @return    None
 */
void Stim_SetMatchValue(uint32 MatValue);

/**
 * @brief     Current value of stim.
 * 
 * @param     None
 * 
 * @return    Value of stim.
 */
uint32 Stim_GetCurrentTimerValue(void);

/**
 * @brief     Enable stim.
 * 
 * @param     None
 * 
 * @return    None

 */
void Stim_Enable(void);

/**
 * @brief     Disable stim.
 * 
 * @param     None
 * 
 * @return    None
 *
 */
void Stim_Disable(void);

/**
 * @brief     Enable/Disable the stim interrupt.
 * 
 * @param[in] IntEnStatus: Enable/Disable function state.
 *            - COMMON_ENABLE:  enable interrupt
 *            - COMMON_DISABLE: disable interrupt
 * 
 * @return    None
 *
 */
void Stim_EnableInt(Common_ControlStateType IntEnStatus);


/**
 * @brief     Checks if the interrupt status flag is set when the timer gets full or matches the
 *            match value.
 * 
 * @param     None
 * 
 * @return    IntStatusFlag: The interrupt status flag.
 * @retval    COMMON_SET.
 * @retval    COMMON_RESET.
 *
 */
Common_IntStatusType Stim_GetIntStatus(void);

/**
 * @brief     Clear the interrupt flag of stim.
 * 
 * @param     None
 * 
 * @return    None
 *
 */
void Stim_ClearInt(void);

/** @} end of group Public_FunctionDeclaration */

#endif /* STIM_DRV_H */
