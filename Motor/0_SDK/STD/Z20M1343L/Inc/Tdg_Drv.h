/**************************************************************************************************/
/**
 * @file      : Tdg_Drv.h
 * @brief     : TDG module driver header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef TDG_DRV_H
#define TDG_DRV_H

#include "Common_Drv.h"

/** @defgroup Public_TypeDefinition
 *  @{
 */

/**
 *  @brief TDG Trig Source type definition
 */
typedef enum
{
    TDG_TRIG_PWM_INIT0 = 0U,                       /*!< PWM init trigger source0 */
    TDG_TRIG_PWM_INIT1 = 1U,                       /*!< PWM init trigger source1 */
    TDG_TRIG_PWM_INIT2 = 2U,                       /*!< PWM init trigger source2 */
    TDG_TRIG_PWM_CV0 = 6U,                         /*!< PWM cv trigger source0 */
    TDG_TRIG_PWM_CV1 = 7U,                         /*!< PWM cv trigger source1 */
    TDG_TRIG_PWM_CV2 = 8U,                         /*!< PWM cv trigger source2 */
    TDG_TRIG_PWM_CV3 = 9U,                         /*!< PWM cv trigger source3 */
    TDG_TRIG_PWM_CV4 = 10U,                        /*!< PWM cv trigger source4 */
    TDG_TRIG_PWM_CV5 = 11U,                        /*!< PWM cv trigger source5 */
    TDG_TRIG_SW0 = 12U,                            /*!< software trigger source0 */
    TDG_TRIG_SW1 = 13U,                            /*!< software trigger source1 */
    TDG_TRIG_SW2 = 14U                             /*!< software trigger source2 */
} Tdg_TriggerSourceType;

 /**
 *  @brief TDG Channel ID type definition
 */
typedef enum
{
    TDG_CHANNEL_0 = 0U,                     /*!< TDG Channel 0*/
    TDG_CHANNEL_1,                          /*!< TDG Channel 1*/
    TDG_CHANNEL_2                           /*!< TDG Channel 2*/
} Tdg_ChannelIdType;

 /**
 *  @brief TDG Software Trigger ID type definition
 */
typedef enum
{
    TDG_SOFTWARE_TRIGGER_0 = 0U,                     /*!< TDG Software Trigger 0*/
    TDG_SOFTWARE_TRIGGER_1,                          /*!< TDG Software Trigger 1*/
    TDG_SOFTWARE_TRIGGER_2                           /*!< TDG Software Trigger 2*/
} Tdg_SoftwareTriggerIdType;

 /**
 *  @brief TDG skip cycle type definition
 */
typedef enum
{
    TDG_SC_0 = 0U,                          /*!< TDG skip 0 cycle*/
    TDG_SC_1,                               /*!< TDG skip 1 cycle*/
    TDG_SC_2,                               /*!< TDG skip 2 cycle*/
    TDG_SC_3                                /*!< TDG skip 3 cycle*/
} Tdg_SkipCycleType;

 /**
 *  @brief TDG counter status type definition
 */
typedef enum
{
    TDG_COUNTER_STOPPED = 0U,                          /*!< TDG counter stopped*/
    TDG_COUNTER_RUNNING                                /*!< TDG counter running*/
} Tdg_CounterStatusType;

/** @} end of group Public_TypeDefinition*/

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_MacroDefinition
 *  @{
 */

/** @}end of group Public_MacroDefinition */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief      TDG enable/disable function
 *
 * @param[in]  Cmd: Common_ControlStateType
 *                     - COMMON_ENABLE: tdg enable
 *                     - COMMON_DISABLE: tdg disable
 *
 * @return     None
 */
void Tdg_Enable(Common_ControlStateType Cmd);

/**
 * @brief      TDG select trigger source 
 *
 * @param[in]  ChannelId: Tdg_ChannelIdType
 *                        - TDG_CHANNEL_0
 *                        - TDG_CHANNEL_1
 *                        - TDG_CHANNEL_2
 * @param[in]  Trig: Tdg_TrigSourceType
 *                       -TDG_TRIG_PWM_INIT0
 *                       -TDG_TRIG_PWM_INIT1
 *                       -TDG_TRIG_PWM_INIT2
 *                       -TDG_TRIG_PWM_CV0
 *                       -TDG_TRIG_PWM_CV1
 *                       -TDG_TRIG_PWM_CV2
 *                       -TDG_TRIG_PWM_CV3
 *                       -TDG_TRIG_PWM_CV4
 *                       -TDG_TRIG_PWM_CV5
 *                       -TDG_TRIG_SW0
 *                       -TDG_TRIG_SW1
 *                       -TDG_TRIG_SW2
 *
 * @return     None
 *
 */
void Tdg_SelectTriggerSource(Tdg_ChannelIdType ChannelId, Tdg_TriggerSourceType Trig);

/**
 * @brief      TDG software trigger 
 *
 * @param[in]  SwTrigId: Tdg_SoftwareTriggerIdType
 *                        - TDG_SOFTWARE_TRIGGER_0
 *                        - TDG_SOFTWARE_TRIGGER_1
 *                        - TDG_SOFTWARE_TRIGGER_2
 *
 * @return     None
 *
 */
void Tdg_SoftwareTrigger(Tdg_SoftwareTriggerIdType SwTrigId);

/**
 * @brief      TDG absolute delay time value config
 *
 * @param[in]  ChannelId: Tdg_ChannelIdType
 *                        - TDG_CHANNEL_0
 *                        - TDG_CHANNEL_1
 *                        - TDG_CHANNEL_2
 * @param[in]  TimeValue: uint16
 *
 * @return none
 *
 */
void Tdg_SetTimeValue(Tdg_ChannelIdType ChannelId, uint16 TimeValue);

/**
 * @brief      Get TDG absolute delay time value
 *
 * @param[in]  ChannelId: Tdg_ChannelIdType
 *                        - TDG_CHANNEL_0
 *                        - TDG_CHANNEL_1
 *                        - TDG_CHANNEL_2
 *
 * @return time value
 *
 */
uint16 Tdg_GetTimeValue(Tdg_ChannelIdType ChannelId);

/**
 * @brief      TDG channel enable/disable
 *
 * @param[in]  ChannelId: Tdg_ChannelIdType
 *                        - TDG_CHANNEL_0
 *                        - TDG_CHANNEL_1
 *                        - TDG_CHANNEL_2
 * @param[in]  Cmd: Common_ControlStateType
 *                        - COMMON_ENABLE: tdg channel enable
 *                        - COMMON_DISABLE: tdg channel disable
 *
 * @return none
 *
 */
void Tdg_EnableChannel(Tdg_ChannelIdType ChannelId, Common_ControlStateType Cmd);

/**
 * @brief       TDG skip cycle config
 *
 * @param[in]  SkipCycle: Tdg_SkipCycleType
 *                              - TDG_SC_0
 *                              - TDG_SC_1
 *                              - TDG_SC_2
 *                              - TDG_SC_3
 *
 * @return none
 *
 */
void Tdg_SetSkipCycleValue(Tdg_SkipCycleType SkipCycle);

/**
 * @brief      Get TDG skip cycle number
 *
 * @param[in]  none
 *
 * @return    Tdg_SkipCycleType
 *                           - TDG_SC_0
 *                           - TDG_SC_1
 *                           - TDG_SC_2
 *                           - TDG_SC_3                       
 *
 */
Tdg_SkipCycleType Tdg_GetSkipCycleValue(void);

/**
 * @brief      Get TDG channel counter value
 *
 * @param[in]  ChannelId: Tdg_ChannelIdType
 *                        - TDG_CHANNEL_0
 *                        - TDG_CHANNEL_1
 *                        - TDG_CHANNEL_2
 *
 * @return counter value
 *
 */
uint16 Tdg_GetCounterValue(Tdg_ChannelIdType ChannelId);

/**
 * @brief      Get TDG channel counter status
 *
 * @param[in]  ChannelId: Tdg_ChannelIdType
 *                        - TDG_CHANNEL_0
 *                        - TDG_CHANNEL_1
 *                        - TDG_CHANNEL_2
 *
 * @return     Tdg_CounterStatusType
 *                        - TDG_COUNTER_STOPPED
 *                        - TDG_COUNTER_RUNNING
 *
 */
Tdg_CounterStatusType Tdg_GetCounterStatus(Tdg_ChannelIdType ChannelId);

/**
 * @brief      Clear TDG channel counter overflow flag
 *
 * @param[in]  ChannelId: Tdg_ChannelIdType
 *                        - TDG_CHANNEL_0
 *                        - TDG_CHANNEL_1
 *                        - TDG_CHANNEL_2
 *
 * @return none
 *
 */
void Tdg_ClearOverflowFlag(Tdg_ChannelIdType ChannelId);


/** @} end of group Public_FunctionDeclaration */

#endif /* TDG_DRV_H */
