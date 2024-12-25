/**************************************************************************************************/
/**
 * @file     cmu_drv.h
 * @brief    CMU driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef CMU_DRV_H
#define CMU_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  CMU
 *  @{
 */

/** @defgroup CMU_Public_Types 
 *  @{
 */

/**
 *  @brief CMU ID type definition
 */
typedef enum 
{
    CMU_ID_0 = 0U,    /*!< CMU0: use FIRC64M clock to monitor Bus clock */
    CMU_ID_1 = 1U,    /*!< CMU1: use OSC40M clock to monitor FIRC64M clock */
    CMU_ID_2 = 2U,    /*!< CMU2: use OSC40M clock to monitor LPO32K clock */
} CMU_Id_t;

/**
 *  @brief CMU state type definition
 */
typedef enum 
{
    CMU_STATE_UPDATABLE = 0U,    /*!< CMU configuration can be updated */
    CMU_STATE_LOCKED = 1U,       /*!< CMU configuration is locked*/
    CMU_STATE_RUNNING = 2U,      /*!< CMU is running */
} CMU_State_t;

/**
 *  @brief CMU interrupt type definition
 */
typedef enum
{    
    CMU_INT_BELOW_LOW_THRE = 0U,    /*!< CMU interrupt: frequency below low
                                          Threshold */
    CMU_INT_ABOVE_HIGH_THRE = 1U,   /*!< CMU interrupt: frequency above high
                                          Threshold */    
    CMU_INT_ALL                      /*!< CMU all interrupts */
} CMU_Int_t;

/** 
 *  @brief CMU monitor mode config struct
 */
typedef struct
{
    ControlState_t belowLowThresholdIntEn;     /*!< Specifies if frequency Below  
                                                  Low Threshold Interrupt is 
                                                  enabled/disabled. */
    ControlState_t aboveHighThresholdIntEn;    /*!< Specifies if frequency above
                                                  high Threshold Interrupt is 
                                                  enabled/disabled. */
    ControlState_t belowLowThresholdResetEn;   /*!< Specifies if frequency Below  
                                                  Low Threshold Reset is 
                                                  enabled/disabled. */
    ControlState_t aboveHighThresholdResetEn;  /*!< Specifies if frequency above
                                                  high Threshold Reset is 
                                                  enabled/disabled. */
    uint32_t monitorWindow;    /*!< Specifies the monitor window */
    uint32_t intLowThreshold;  /*!< Specifies the low threshold for interrupt */
    uint32_t intHighThreshold; /*!< Specifies the high threshold for interrupt */
    uint32_t resetLowThreshold;  /*!< Specifies the low threshold for reset */
    uint32_t resetHighThreshold; /*!< Specifies the high threshold for reset */
} CMU_MonitorModeConfig_t;


/** @} end of group CMU_Public_Types */

/** @defgroup CMU_Public_Constants
 *  @{
 */


/** @} end of group CMU_Public_Constants */

/** @defgroup CMU_Public_Macro
 *  @{
 */

/** @} end of group CMU_Public_Macro */

/** @defgroup CMU_Public_FunctionDeclaration
 *  @brief CMU functions declaration
 *  @{
 */

/**
 * @brief      Initializes the monitor mode of CMU peripheral. 
 *
 * @param[in]  id: select the CMU ID
 * @param[in]  config: points to the monitorMode configuration struct
 *
 * @return     none
 *
 */
void CMU_MonitorModeInit(CMU_Id_t id, const CMU_MonitorModeConfig_t *config);

/**
 * @brief      Initializes the measure mode of CMU peripheral. 
 *
 * @param[in]  id: select the CMU ID
 * @param[in]  monitorWin: the monitor window value
 *
 * @return     none
 *
 */
void CMU_MeasureModeInit(CMU_Id_t id, uint32_t monitorWin);

/**
 * @brief      Enable the CMU. 
 *
 * @param[in]  id: select the CMU ID
 *
 * @return     none
 *
 */
void CMU_Enable(CMU_Id_t id);

/**
 * @brief      Disable the CMU. 
 *
 * @param[in]  id: select the CMU ID
 *
 * @return     none
 *
 */
void CMU_Disable(CMU_Id_t id);

/**
 * @brief      Start the measure mode. 
 *
 * @param[in]  id: select the CMU ID
 *
 * @return     none
 *
 */
void CMU_StartMeasure(CMU_Id_t id);

/**
 * @brief      Get the measure complete status. 
 *
 * @param[in]  id: select the CMU ID
 *
 * @return     - SET: measure is completed
 *             - RESET: measure is not completed
 *
 */
FlagStatus_t CMU_GetMeasureCompleteStatus(CMU_Id_t id);

/**
 * @brief      Read measure result when CMU is working in measure mode. User 
 *             needs to make sure the measure is completed before calling this 
 *             function, otherwise, the return value is incorrect.
 *
 * @param[in]  id: select the CMU ID
 *
 * @return     measure result
 *
 */
uint32_t CMU_ReadMeasureResult(CMU_Id_t id);
     
/**
 * @brief      Get the CMU state. 
 *
 * @param[in]  id: select the CMU ID
 *
 * @return     the CMU state
 *
 */
CMU_State_t CMU_GetState(CMU_Id_t id);
     
/**
 * @brief      Mask/Unmask interrupt
 *
 * @param[in]  id: select the CMU ID
 * @param[in]  intType: select interrupt type
 * @param[in]  intMask: MASK/UNMASK
 *
 * @return    none
 *
 */
void CMU_IntMask(CMU_Id_t id, CMU_Int_t intType, IntMask_t intMask);

/**
 * @brief      Clear interrupt
 *
 * @param[in]  id: select the CMU ID
 * @param[in]  intType: select interrupt type
 *
 * @return    none
 *
 */
void CMU_IntClear(CMU_Id_t id, CMU_Int_t intType);

/**
 * @brief      Get interrupt status
 *
 * @param[in]  id: select the CMU ID
 * @param[in]  intType: select interrupt type
 *
 * @return    
 *          - SET
 *          - RESET
 *
 */
IntStatus_t CMU_GetIntStatus(CMU_Id_t id, CMU_Int_t intType);

/**
 * @brief      Install cmu interrupt callback function
 *
 * @param[in]  id: select the CMU ID
 * @param[in]  intType: select interrupt type 
 * @param[in]  cbFun: indicate callback function
 *
 * @return    none
 *
 */ 
void CMU_InstallCallBackFunc(CMU_Id_t id, CMU_Int_t intType, 
                             isr_cb_t * const cbFun);

/** @} end of group CMU_Public_FunctionDeclaration */

/** @} end of group CMU  */

/** @} end of group Z20K14XM_Peripheral_Driver */
#endif /* CMU_DRV_H */
