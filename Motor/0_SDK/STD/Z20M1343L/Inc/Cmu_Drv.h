/**************************************************************************************************/
/**
 * @file      : Cmu_Drv.h
 * @brief     : CMU driver module header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef CMU_DRV_H
#define CMU_DRV_H

#include "Common_Drv.h"

/** @defgroup Public_MacroDefinition
 *  @{
 */

/** @} end of Public_MacroDefinition */

/** @defgroup Public_TypeDefinition
 *  @{
 */

/**
 *  @brief CMU Monitor type definition
 */
typedef enum 
{
    CMU_MONITOR_FRO48M = 0U,    /*!< FRO48M Monitor: use OSC24M as reference clock */
    CMU_MONITOR_OSC24M = 1U     /*!< OSC24M Monitor: use FRO48M as reference clock */
} Cmu_MonitorType;

/**
 *  @brief CMU state type definition
 */
typedef enum 
{
    CMU_STATE_UPDATABLE = 0U,     /*!< CMU configuration can be updated */
    CMU_STATE_LOCKED    = 1U,     /*!< CMU configuration is locked*/
    CMU_STATE_RUNNING   = 2U      /*!< CMU is running */
} Cmu_StateType;

/**
 *  @brief CMU measure complete status type definition
 */
typedef enum 
{
    CMU_MEASURE_COMPLETED   = 0U,    /*!< CMU measure completed */
    CMU_MEASURE_UNCOMPLETED = 1U     /*!< CMU measure uncompleted*/
} Cmu_MeasureCompleteType;

/**
 *  @brief CMU interrupt type definition
 */
typedef enum
{    
    CMU_INT_LOW  = 0U,   /*!< CMU interrupt: frequency below low Threshold */
    CMU_INT_HIGH = 1U,   /*!< CMU interrupt: frequency above high Threshold */    
    CMU_INT_ALL          /*!< CMU all interrupts */
} Cmu_IntType;

/** 
 *  @brief CMU monitor mode config struct
 */
typedef struct
{
    Common_ControlStateType BelowLowIntEn;   /*!< Specifies if frequency   
                                                  Below Low Threshold Interrupt 
                                                  is enabled/disabled. */
    Common_ControlStateType AboveHighIntEn;  /*!< Specifies if frequency 
                                                  Above High Threshold Interrupt  
                                                  is enabled/disabled. */
    uint32 MonitorWindow;      /*!< Specifies the monitor window */
    uint32 IntLowThreshold;    /*!< Specifies the low threshold for interrupt */
    uint32 IntHighThreshold;   /*!< Specifies the high threshold for interrupt */
} Cmu_MonitorModeConfigType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief       Initializes the monitor mode of CMU peripheral. 
 *
 * @param[in]   MonitorConfig: points to the monitorMode configuration struct
 *
 * @return      none
 *
 */
void Cmu_InitMonitorMode(const Cmu_MonitorModeConfigType *MonitorConfig);

/**
 * @brief       Initializes the measure mode of CMU peripheral. 
 *
 * @param[in]   MonitorWin: the monitor window value
 *
 * @return      none
 *
 */
void Cmu_InitMeasureMode(uint32 MonitorWin);

/**
 * @brief       Enable the CMU. 
 *
 * @param[in]   Monitor: Select monitor to be enabled
 *
 * @return      none
 *
 */
void Cmu_Enable(Cmu_MonitorType Monitor);

/**
 * @brief       Disable the CMU. 
 *
 * @param[in]   none
 *
 * @return      none
 *
 */
void Cmu_Disable(void);

/**
 * @brief       Start the measure mode. 
 *
 * @param[in]   none
 *
 * @return      none
 *
 */
void Cmu_StartMeasure(void);

/**
 * @brief       Get the measure complete status. 
 *
 * @param[in]   none
 *
 * @return      measure status
 * @retval      CMU_MEASURE_COMPLETED: measure completed
 * @retval      CMU_MEASURE_UNCOMPLETED: measure uncompleted
 *
 */
Cmu_MeasureCompleteType Cmu_GetMeasureCompleteStatus(void);

/**
 * @brief       Read measure result when CMU is working in measure mode. User 
 *              needs to make sure the measure is completed before calling this 
 *              function, otherwise, the return value is incorrect.
 *
 * @param[in]   none
 *
 * @return      measure result
 *
 */
uint32 Cmu_ReadMeasureResult(void);
     
/**
 * @brief       Get the CMU state. 
 *
 * @param[in]   none
 *
 * @return      the CMU state
 * @retval      CMU_STATE_UPDATABLE: CMU configuration can be updated
 * @retval      CMU_STATE_LOCKED:    CMU configuration is locked
 * @retval      CMU_STATE_RUNNING:   CMU is running 
 *
 */
Cmu_StateType Cmu_GetState(void);
     
/**
 * @brief       Mask/Unmask interrupt
 *
 * @param[in]   IntType: select interrupt type
 * @param[in]   IntMask: MASK/UNMASK
 *
 * @return      none
 *
 */
void Cmu_SetIntMask(Cmu_IntType IntType, Common_IntMaskType IntMask);

/**
 * @brief       Clear interrupt.
 *
 * @param[in]   IntType: select interrupt type
 *
 * @return      none
 *
 */
void Cmu_ClearIntFlag(Cmu_IntType IntType);

/**
 * @brief       Get interrupt status
 *
 * @param[in]   IntType: select interrupt type
 *
 * @return      interrupt status
 * @retval      SET: The interrupt flag is set
 * @retval      RESET: The interrupt flag is clear
 *
 */
Common_IntStatusType Cmu_GetIntStatus(Cmu_IntType IntType);

/** @} end of group Public_FunctionDeclaration */

#endif /* CMU_DRV_H */
