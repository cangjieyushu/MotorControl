/**************************************************************************************************/
/**
 * @file      : Wdog_Drv.h
 * @brief     : WDOG module driver header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef WDOG_DRV_H
#define WDOG_DRV_H

#include "Common_Drv.h"

/** @defgroup Public_TypeDefinition 
 *  @{
 */

/**
 *  @brief Wdog test mode type definition
 * Implements : WDOG_Test_Mode_t_Class
 */
typedef enum 
{
    WDOG_TST_MODE0     = 0U,      /*!< Test mode 0 */
    WDOG_TST_MODE1     = 1U,      /*!< Test mode 1 */
    WDOG_TST_NORMAL    = 4U       /*!< Normal mode */
} Wdog_TestModeType;

/**
 * @brief Wdog operate mode configuration structure.
 *
 * This structure configures the wdog operation mode.
 * Implements : WDOG_OperationMode_t_Class
 */
typedef struct 
{
    Common_ControlStateType Stop;           /*!< Stop mode */
    Common_ControlStateType Debug;          /*!< Debug mode */
} Wdog_OperationModeType;

/*!
 * @brief Wdog configuration structure.
 *
 * This structure configures the basic attribute.
 * Implements : WDOG_Config_t_Class
 */
typedef struct 
{
    Common_ControlStateType       WinEnable;       /*!< window mode control 
                                               - ENABLE: enable window mode 
                                               - DISABLE: disable window mode */
    Common_ControlStateType       Stop;            /*!< stop mode control
                                               - ENABLE: counter continue
                                               - DISABLE: counter halt */
    Common_ControlStateType       Debug;           /*!< debug mode control
                                               - ENABLE: counter continue
                                               - DISABLE: counter halt */
    uint16             WindowValue;     /*!< The window value: 16 bits */
    uint16             TimeoutValue;    /*!< The timeout value: 16 bits */
    Wdog_TestModeType      TestMode;        /*!< test mode */
} Wdog_ConfigType;

/**  
 *  @brief Wdog interrupt type definition
 */
typedef enum
{
    WDOG_INT_BEFORERESET = 0U,            /*!< wdog interrupt before reset */
    WDOG_INT_ALL
} Wdog_IntType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Public_MacroDefinition
 *  @{
 */

/** @} end of group Public_MacroDefinition */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */
 
/**
 * @brief      Wdog initializes function
 *
 * @param[in]  InitConfigPtr: Pointer to a wdog configuration structure.
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_Init(const Wdog_ConfigType * InitConfigPtr);

/**
 * @brief      Enable wdog count function
 *
 * @param[in]  none
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_Enable(void);

/**
 * @brief      Disable wdog count function
 *
 * @param[in]  none
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_Disable(void);

/**
 * @brief      Refresh wdog count function
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void Wdog_Refresh(void);

/**
 * @brief      Enable wdog time interval check function
 *
 * @param[in]  none
 *
 * @return none.
 *
 */
Common_ResultStatusType Wdog_EnableTimeIntervalCheck(void);
/**
 * @brief      Get wdog config allow flag status function
 *
 * @param[in]  none
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: Status set.
 * @retval     COMMON_RESET: Status not set 
 *
 */
Common_FlagStatusType Wdog_GetConfigAllowStatus(void);

/**
 * @brief      Set wdog config allow flag function
 *
 * @param[in]  Allow: config update control
 *                    - COMMON_ENABLE: enable config update
 *                    - COMMON_DISABLE: disable config update
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_ControlConfigAllow(Common_ControlStateType Allow);

/**
 * @brief      Enable/disable wdog window mode function
 *
 * @param[in]  WinEnable: window mode control
 *                        - COMMON_ENABLE: enable window mode
 *                        - COMMON_DISABLE: disable window mode
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_ControlWindowMode(Common_ControlStateType WinEnable);

/**
 * @brief      Set wdog window value function
 *
 * @param[in]  WindowValue: window value, 16 bits
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_SetWindowValue(uint16 WindowValue);

/**
 * @brief      Get wdog window register value function
 *
 * @param[in]  none
 *
 * @return     window register value
 *
 */
uint16 Wdog_GetWindowValue(void);

/**
 * @brief      Set wdog timeout value function
 *
 * @param[in]  timeoutValue: timeout value, 16 bits
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_SetTimeoutValue(uint16 TimeoutValue);

/**
 * @brief      Get wdog timeout register value function
 *
 * @param[in]  none
 *
 * @return     timeout register value.
 *
 */
uint16 Wdog_GetTimeoutValue(void);

/**
 * @brief      Configure wdog behavior in stop mode function
 *
 * @param[in]  Cmd: stop mode control
 *                  - COMMON_ENABLE: counter continue in stop mode
 *                  - COMMON_DISABLE: counter halt in stop mode
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_ControlStopMode(Common_ControlStateType Cmd);

/**
 * @brief      Configure wdog behavior in debug mode function
 *
 * @param[in]  Cmd: debug mode control
 *                  - COMMON_ENABLE: counter continue in debug mode
 *                  - COMMON_DISABLE: counter halt in debug mode
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_ControlDebugMode(Common_ControlStateType Cmd);

/**
 * @brief      Set wdog test mode function
 *
 * @param[in]  TestMode: test mode select
 *                       - WDOG_TST_MODE0: test mode 0
 *                       - WDOG_TST_MODE1: test mode 1
 *                       - WDOG_TST_NORMAL: normal mode
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_SetTestMode(Wdog_TestModeType TestMode);

/**
 * @brief      Get wdog test/normal mode function
 *
 * @param[in]  none
 *
 * @return     Wdog_TestModeType
 * @retval     WDOG_TST_MODE0: test mode 0
 * @retval     WDOG_TST_MODE1: test mode 1
 * @retval     WDOG_TST_NORMAL: normal mode
 *
 */
Wdog_TestModeType Wdog_GetTestMode(void);

/**
 * @brief      Get wdog free-running counter function
 *
 * @param[in]  none
 *
 * @return free-running counter value.
 *
 */
uint16 Wdog_GetCounter(void);

/**
 * @brief      Get flag indicates configuration update is completed function
 *
 * @param[in]  none
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: status set
 * @retval     COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Wdog_GetConfigCompletedStatus(void);

/**
 * @brief      Get flag indicates all registers are locked or unlocked function
 *
 * @param[in]  none
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: status set
 * @retval     COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Wdog_GetLockStatus(void);

/**
 * @brief      Get wdog int flag function
 *
 * @param[in]  IntType: int type
 *                      - WDOG_INT_BEFORERESET: int before reset
 *                      - WDOG_INT_ALL: all int type  
 *
 * @return     Common_IntStatusType
 * @retval     COMMON_SET: interrupt assert
 * @retval     COMMON_RESET: interrupt deassert
 *
 */
Common_IntStatusType Wdog_GetIntStatus(Wdog_IntType IntType);

/**
 * @brief      Clear wdog int flag function
 *
 * @param[in]  IntType: int type
 *                      - WDOG_INT_BEFORERESET: int before reset
 *                      - WDOG_INT_ALL: all int type  
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_ClearIntStatus(Wdog_IntType IntType);

/**
 * @brief      Set wdog int mask function
 *
 * @param[in]  IntType: int type
 *                      - WDOG_INT_BEFORERESET: int before reset
 *                      - WDOG_INT_ALL: all int type  
 * @param[in]  IntMask: int mask
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_SetIntMask(Wdog_IntType IntType, Common_IntMaskType IntMask);


/** @} end of group Public_FunctionDeclaration */

#endif  /* WDOG_DRV_H */
