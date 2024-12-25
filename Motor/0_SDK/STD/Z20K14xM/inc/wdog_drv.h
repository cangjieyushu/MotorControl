/**************************************************************************************************/
/**
 * @file     wdog_drv.h
 * @brief    WDOG driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef WDOG_DRV_H
#define WDOG_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  WDOG
 *  @{
 */

/** @defgroup WDOG_Public_Types 
 *  @{
 */

/*! @brief WDOG clock source type definition
 * Implements : WDOG_Clk_Source_t_Class
 */
typedef enum 
{
    WDOG_LPO_CLOCK     = 0U,       /*!< LPO clock */
    WDOG_BUS_CLOCK = 1U,                /*!< Bus clock */
    WDOG_OSC_CLOCK = 3U                 /*!< OSC clock */
} WDOG_ClkSource_t;

/*! @brief WDOG test mode type definition
 * Implements : WDOG_Test_Mode_t_Class
 */
typedef enum 
{
    WDOG_TST_MODE0     = 0U,      /*!< Test mode 0 */
    WDOG_TST_MODE1,               /*!< Test mode 1 */
    WDOG_TST_MODE2,               /*!< Test mode 2 */
    WDOG_TST_MODE3,               /*!< Test mode 2 */
    WDOG_TST_NORMAL               /*!< normal mode */
} WDOG_TestMode_t;

/*!
 * @brief WDOG operate mode configuration structure.
 *
 * This structure configures the wdog operation mode.
 * Implements : WDOG_OperationMode_t_Class
 */
typedef struct 
{
    ControlState_t wait;           /*!< Wait mode */
    ControlState_t stop;           /*!< Stop mode */
    ControlState_t debug;          /*!< Debug mode */
} WDOG_OperationMode_t;

/*!
 * @brief WDOG configuration structure.
 *
 * This structure configures the basic attribute.
 * Implements : WDOG_Config_t_Class
 */
typedef struct 
{
    ControlState_t       winEnable;       /*!< window mode control 
                                               - ENABLE: enable window mode 
                                               - DISABLE: disable window mode */
    ControlState_t       wait;            /*!< wait mode control 
                                               - ENABLE: counter countinue
                                               - DISABLE: counter halt */
    ControlState_t       stop;            /*!< stop mode control
                                               - ENABLE: counter countinue
                                               - DISABLE: counter halt */
    ControlState_t       debug;           /*!< debug mode control
                                               - ENABLE: counter countinue
                                               - DISABLE: counter halt */
    uint32_t             windowValue;     /*!< The window value: 32 bits */
    uint32_t             timeoutValue;    /*!< The timeout value: 32 bits */
    WDOG_ClkSource_t     clkSource;       /*!< The clock source of the WDOG */
    WDOG_TestMode_t      testMode;        /*!< test mode */
} WDOG_Config_t;

/**  
 *  @brief WDOG interrupt type definition
 */
typedef enum
{
    WDOG_INT_BEFORERESET = 0U,            /*!< wdog interrupt before reset */
    WDOG_INT_ALL
} WDOG_INT_t;

/** @} end of group WDOG_Public_Types */

/** @defgroup WDOG_Public_Constants
 *  @{
 */

/** @} end of group WDOG_Public_Constants */

/** @defgroup WDOG_Public_Macro
 *  @{
 */

/** @} end of group WDOG_Public_Macro */


/** @defgroup WDOG_Public_FunctionDeclaration
 *  @brief WDOG functions declaration
 *  @{
 */
 
/**
 * @brief      wdog Initializes Function
 *
 * @param[in]  ptWDOGInitConfig:     Pointer to a WDOG configuration structure.
 *
 * @return     Initializes operate flag
 *
 */
ResultStatus_t WDOG_Init(const WDOG_Config_t * ptWDOGInitConfig);

/**
 * @brief      enable wdog count Function
 *
 * @param[in]  none
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_Enable(void);

/**
 * @brief      disable wdog count Function
 *
 * @param[in]  none
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_Disable(void);

/**
 * @brief      refresh wdog count Function
 *
 * @param[in]  none
 *
 * @return none.
 *
 */
void WDOG_Refresh(void);

/**
 * @brief      get wdog config allow flag status Function
 *
 * @param[in]  none
 *
 * @return     busy status.
 *
 */
FlagStatus_t WDOG_GetConfigAllowStatus(void);

/**
 * @brief      set wdog config allow flag Function
 *
 * @param[in]  allow: config update control
 *                    - ENABLE: enable config update
 *                    - DISABLE: disbale config update
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_ConfigAllowControl(ControlState_t allow);

/**
 * @brief      enable/disbale wdog window mode Function
 *
 * @param[in]  winEnable: window mode control
 *                        - ENABLE: enable window mode
 *                        - DISABLE: disbale window mode
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_WindowModeControl(ControlState_t winEnable);

/**
 * @brief      set wdog window value Function
 *
 * @param[in]  windowValue: window value, 32 bits
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_SetWindowValue(uint32_t windowValue);

/**
 * @brief      get wdog window register value Function
 *
 * @param[in]  none
 *
 * @return window register value.
 *
 */
uint32_t WDOG_GetWindowValue(void);

/**
 * @brief      set wdog clock source Function
 *
 * @param[in]  clkSource: clock source
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_SetClockSource(WDOG_ClkSource_t clkSource);

/**
 * @brief      set wdog timeout value Function
 *
 * @param[in]  timeoutValue: timeout value, 32 bits
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_SetTimeoutValue(uint32_t timeoutValue);

/**
 * @brief      get wdog timeout register value Function
 *
 * @param[in]  none
 *
 * @return timeout register value.
 *
 */
uint32_t WDOG_GetTimeoutValue(void);

/**
 * @brief      configure wdog behavior in stop mode Function
 *
 * @param[in]  cmd: stop mode control
 *                  - ENABLE: counter continue in stop mode
 *                  - DISABLE: counter halt in stop mode
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_StopModeControl(ControlState_t cmd);

/**
 * @brief      configure wdog behavior in wait mode Function
 *
 * @param[in]  cmd: wait mode control
 *                  - ENABLE: counter continue in wait mode
 *                  - DISABLE: counter halt in wait mode
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_WaitModeControl(ControlState_t cmd);

/**
 * @brief      configure wdog behavior in debug mode Function
 *
 * @param[in]  cmd: debug mode control
 *                  - ENABLE: counter continue in debug mode
 *                  - DISABLE: counter halt in debug mode
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_DebugModeControl(ControlState_t cmd);

/**
 * @brief      set wdog test mode Function
 *
 * @param[in]  testMode: test/normal mode
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_SetTestMode(WDOG_TestMode_t testMode);

/**
 * @brief      get wdog test/normal mode Function
 *
 * @param[in]  none
 *
 * @return test/normal mode.
 *
 */
WDOG_TestMode_t WDOG_GetTestMode(void);

/**
 * @brief      get wdog free-running counter Function
 *
 * @param[in]  none
 *
 * @return free-running counter value.
 *
 */
uint32_t WDOG_GetCounter(void);

/**
 * @brief      get flag indcates configuration update is completed Function
 *
 * @param[in]  none
 *
 * @return     configuration update completed status.
 *
 */
FlagStatus_t WDOG_GetConfigCompletedStatus(void);

/**
 * @brief      get Flag indcates all registers are locked or unlocked Function
 *
 * @param[in]  none
 *
 * @return     lock Flag.
 *
 */
FlagStatus_t WDOG_GetLockStatus(void);

/**
 * @brief      get WDOG int flag Function
 *
 * @param[in]  intType: int type
 *                      - WDOG_INT_BEFORERESET: int befor reset
 *                      - WDOG_INT_ALL: all int type  
 *
 * @return whether a int is asserted or not.
 *
 */
IntStatus_t WDOG_GetIntStatus(WDOG_INT_t intType);

/**
 * @brief      clear wdog int flag Function
 *
 * @param[in]  none 
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_ClearIntStatus(void);

/**
 * @brief      set wdog int mask Function
 *
 * @param[in]  intType: int type
 *                      - WDOG_INT_BEFORERESET: int befor reset
 *                      - WDOG_INT_ALL: all int type  
 * @param[in]  intMask: int mask
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_IntMask(WDOG_INT_t intType, IntMask_t intMask);

/**
 * @brief      Install callback function
 *
 * @param[in]  intType: select interrrupt type
 *                      - WDOG_INT_BEFORERESET: int befor reset
 * @param[in]  cbFun: indicate callback function
 *
 * @return    none
 *
 */
void WDOG_InstallCallBackFunc(WDOG_INT_t intType, isr_cb_t * cbFun);

/** @} end of group WDOG_Public_FunctionDeclaration */

/** @} end of group WDOG  */

/** @} end of group Z20K14XM_Peripheral_Driver */

#endif  /* WDOG_DRV_H */
