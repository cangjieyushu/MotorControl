/**************************************************************************************************/
/**
 * @file      : Srmc_Drv.h
 * @brief     : SRMC module driver header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef SRMC_DRV_H
#define SRMC_DRV_H

#include "Common_Drv.h"

/** @defgroup Public_MacroDefinition
 *  @{
 */

/** @} end of Public_MacroDefinition */

/** @defgroup Public_TypeDefinition
 *  @{
 */

/**
 *  @brief SRMC reset cause type definition
 */
typedef enum
{
    SRMC_RESET_TYPE_POR          = 0x00000001U, /*!< SRMC RESET caused by Power-on 
                                                     Detection Logic */
    SRMC_RESET_TYPE_LVD          = 0x00000002U, /*!< SRMC RESET caused by low voltage detected */
    SRMC_RESET_TYPE_SWAKEUP      = 0x00000004U, /*!< SRMC RESET caused by standby wakeup detected */
    SRMC_RESET_TYPE_STOP_WAKEUP  = 0x00000010U, /*!< SRMC RESET caused by stop wakeup detected */
    SRMC_RESET_TYPE_WDOG         = 0x00000020U, /*!< SRMC RESET caused by Watchdog timer 
                                                     timing out */
    SRMC_RESET_TYPE_LOCKUP       = 0x00000040U, /*!< SRMC RESET caused by ARM core indication of
                                                     a LOCKUP event  */
    SRMC_RESET_TYPE_SW           = 0x00000080U, /*!< SRMC RESET caused by software setting of 
                                                     SYSRESETREQ bit  */
    SRMC_RESET_TYPE_ADM_AP       = 0x00000100U, /*!< SRMC RESET caused by host debugger system
                                                     setting in the ADM-AP control register */
    SRMC_RESET_TYPE_SACKERR      = 0x00004000U, /*!< SRMC RESET caused by peripheral failure
                                                    to acknowledge attempt to enter stop mode */
    SRMC_RESET_TYPE_PIN          = 0x00008000U, /*!< SRMC RESET caused by an active_low level on
                                                     the external RESET pin  */
    SRMC_RESET_TYPE_ALL          = 0x0000C1F7U
} Srmc_ResetCauseType;

/**
 *  @brief SRMC reset Pin Filter definition
 */
typedef enum
{
    SRMC_RESET_PIN_DISABLE_FILTER = 0U,       /*!< SRMC RESET Pin filter disabled  */
    SRMC_RESET_PIN_BUS_CLOCK_FILTER,          /*!< SRMC RESET Pin bus clock filter */
    SRMC_RESET_PIN_LPO_CLOCK_FILTER           /*!< SRMC RESET Pin lpo clock filter */
} Srmc_ResetPinFilterType;

/**
 *  @brief SRMC Interrupt type definition
 */
typedef enum
{
    SRMC_INT_TYPE_STOP_WKUP_RST = 0U,         /*!< SRMC int stop wakeup */
    SRMC_INT_TYPE_WDOG,                       /*!< SRMC int wdog */
    SRMC_INT_TYPE_LOCKUP,                     /*!< SRMC int lockup */
    SRMC_INT_TYPE_SW,                         /*!< SRMC int software */
    SRMC_INT_TYPE_ADM_AP,                     /*!< SRMC int ADM-AP */
    SRMC_INT_TYPE_SACKERR,                    /*!< SRMC int stop ack error */
    SRMC_INT_TYPE_PIN,                        /*!< SRMC int pin */
    SRMC_INT_TYPE_ALL
} Srmc_IntType;

/**
 *  @brief SRMC delay type definition
 */
typedef enum
{
    SRMC_DELAY_8_LPO_CYCLES = 0U,            /*!< SRMC delay 8 lpo cycles  */
    SRMC_DELAY_32_LPO_CYCLES,                /*!< SRMC delay 32 lpo cycles  */
    SRMC_DELAY_128_LPO_CYCLES,               /*!< SRMC delay 128 lpo cycles  */
    SRMC_DELAY_512_LPO_CYCLES                /*!< SRMC delay 512 lpo cycles  */
} Srmc_DelayType;

/**
 *  @brief SRMC power mode type definition
 */
typedef enum
{
    SRMC_POWERMODE_RUN = 0U,                /*!< SRMC run mode  */
    SRMC_POWERMODE_STOP,                    /*!< SRMC stop mode  */
    SRMC_POWERMODE_STANDBY                  /*!< SRMC standby mode  */
} Srmc_PowerModeType;

/**
 *  @brief SRMC stop mode(deep sleep mode) aborted status type definition
 */
typedef enum
{
    SRMC_STOP_SUCCESS = 0U,                /*!< SRMC enter stop mode: success  */
    SRMC_STOP_ABORT                        /*!< SRMC enter stop mode: abort  */
} Srmc_StopModeStatusType;

/**
 *  @brief SRMC software reset type definition
 */
typedef enum
{
    SRMC_SWRST_UART = 0x0U,  /*!< SRMC software reset: UART*/
    SRMC_SWRST_SPI  = 0x1U,  /*!< SRMC software reset: SPI*/
    SRMC_SWRST_ADC  = 0x2U,  /*!< SRMC software reset: ADC*/
    SRMC_SWRST_WDOG = 0x3U,  /*!< SRMC software reset: WDOG*/
    SRMC_SWRST_GDU  = 0x4U   /*!< SRMC software reset: GDU*/
} Srmc_SoftwareResetType;

/**
 *  @brief SRMC wakeup source type definition
 */
typedef enum
{
    SRMC_WUPSRC_IPP_PTA     = 0x0U,  /*!< SRMC wakeup source: PORTA Pin*/
    SRMC_WUPSRC_PMU_VDDFAIL = 0x1U,  /*!< SRMC wakeup source: PMU VDDEXT fail*/
    SRMC_WUPSRC_PMU_HVMON   = 0x2U,  /*!< SRMC wakeup source: PMU high volt monitor*/
    SRMC_WUPSRC_PMU_TIMER   = 0x3U,  /*!< SRMC wakeup source: PMU timer wakeup*/
    SRMC_WUPSRC_LIN_TANS    = 0x4U   /*!< SRMC wakeup source: LIN transceiver*/
} Srmc_WakeupSourceType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief       SRMC trigger software reset to corresponding peripheral.
 *
 * @param[in]   ResetModule:          SRMC software reset type.
 *
 * @return      Software reset status: COMMON_SUCC or COMMON_ERR.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
Common_ResultStatusType Srmc_TriggerSwReset(Srmc_SoftwareResetType ResetModule);

/**
 * @brief       SRMC get software reset flag status, indicating corresponding  
 *              peripheral reset by software.
 *
 * @param[in]   ResetModule:          SRMC software reset type.
 *
 * @return      status.
 *
 */
Common_FlagStatusType Srmc_GetSwResetStatus(Srmc_SoftwareResetType ResetModule);

/**
 * @brief       SRMC clear software reset flag status.
 *
 * @param[in]   ResetModule:          SRMC software reset type.
 *
 * @return      none.
 *
 */
void Srmc_ClearSwResetStatus(Srmc_SoftwareResetType ResetModule);

/**
 * @brief       configure core lockup reset enable/disable.
 *
 * @param[in]   Cmd:          control cmd:   DISABLE; ENABLE.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_CtrlCoreLockupReset(Common_ControlStateType Cmd);

/**
 * @brief       SRMC wakeup source function enable/disable
 *
 * @param[in]   Source:          wakeup source select.
 * @param[in]   Cmd:             enable/disable.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
*/
void Srmc_CtrlWakeupSource(Srmc_WakeupSourceType Source, Common_ControlStateType Cmd);

/**
 * @brief       SRMC get wakeup source status, indicating corresponding wakeup 
 *              source waked up system.
 *
 * @param[in]   Source:          wakeup source select.
 *
 * @return      status.
 *
 */
Common_FlagStatusType Srmc_GetWakeupSourceStatus(Srmc_WakeupSourceType Source);

/**
 * @brief       SRMC clear wakeup source status, indicating corresponding wakeup
 *              source waked up system.
 *
 * @param[in]   Source:          wakeup source select.
 *
 * @return      none.
 *
 */
void Srmc_ClearWakeupSourceStatus(Srmc_WakeupSourceType Source);

/**
 * @brief       configure reset pin filter bus clock width,
 *              actual reset pin bus clock filter width cycle = ClkCycles + 1.
 *
 * @param[in]   ClkCycles:          cycle number.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_ConfigBusClockResetPinFilter(uint8 ClkCycles);

/**
 * @brief       configure how reset pin filter is enabled in stop mode.
 *
 * @param[in]   PinFilter:    only two type used in stop mode, as below:
 *                             - SRMC_RESET_PIN_DISABLE_FILTER;
 *                             - SRMC_RESET_PIN_LPO_CLOCK_FILTER.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_ConfigStopModeResetPinFilter(Srmc_ResetPinFilterType PinFilter);

/**
 * @brief       configure how reset pin filter is enabled in run mode
 *
 * @param[in]   PinFilter:    three type used in run mode, as below:
 *                             - SRMC_RESET_PIN_DISABLE_FILTER
 *                             - SRMC_RESET_PIN_BUS_CLOCK_FILTER
 *                             - SRMC_RESET_PIN_LPO_CLOCK_FILTER
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_ConfigRunModeResetPinFilter(Srmc_ResetPinFilterType PinFilter);

/**
 * @brief       Get the status that if the pointed reset type is the system
 *              reset cause.
 *
 * @param[in]   ResetCause:          reset cause type.
 *
 * @return      status.
 *
 */
Common_FlagStatusType Srmc_GetSystemResetStatus(Srmc_ResetCauseType ResetCause);

/**
 * @brief       Clear the status that if the pointed reset type.
 *
 * @param[in]   ResetCause:          reset cause type.
 *
 * @return      status.
 *
 */
void Srmc_ClearSystemResetStatus(Srmc_ResetCauseType ResetCause);

/**
 * @brief       Get system reset all causes.
 *
 * @param[in]   none.
 *
 * @return      reset cause type(uint32 value): one bit, one cause;
 *              seeing SRMC_ResetCause_t type.
 *
 */
uint32 Srmc_GetSystemResetCause(void);

/**
 * @brief       Unmask/Mask pointed interrupt.
 *
 * @param[in]   IntType:          srmc interrupt source.
 * @param[in]   IntMask:          UNMASK or MASK.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_SetIntMask(Srmc_IntType IntType, Common_IntMaskType IntMask);

/**
 * @brief       Configure max reset delay time from when the interrupt is 
 *              asserted and the system reset occurs.
 *
 * @param[in]   Delay:          delay cycle type.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_ConfigMaxResetDelayTime(Srmc_DelayType Delay);

/**
 * @brief       Configure standby mode entry allowed or not.
 *
 * @param[in]   Cmd:          DISABLE or ENABLE.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_CtrlStandbyMode(Common_ControlStateType Cmd);

/**
 * @brief       Set system enter stop mode(deep sleep mode).
 *
 * @param[in]   AckTimeout: low power mode acknowledge time out.
 * @note        setting ackTimeout to 0 means the stop sequence will wait forever.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_EnterStopMode(uint8 AckTimeout);

/**
 * @brief       Set system enter standby mode.
 *
 * @param[in]   AckTimeout: low power mode acknowledge time out.
 * @note        setting ackTimeout to 0 means the stop sequence will wait forever.
 * 
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_EnterStandbyMode(uint8 AckTimeout);

/**
 * @brief       Get current power mode.
 *
 * @param[in]   none.
 *
 * @return      power mode type.
 *
 */
Srmc_PowerModeType Srmc_GetCurrentPowerMode(void);

/**
 * @brief       Get previous stop mode(deep sleep mode) entry status.
 *
 * @param[in]   none.
 *
 * @return      stop entry status: 
 *              - SRMC_STOP_SUCCESS; 
 *              - SRMC_STOP_ABORT.
 *
 */
Srmc_StopModeStatusType Srmc_GetStopAbortedStatus(void);

/**
 * @brief       Install callback func.
 *
 * @param[in]   IntType: interrupt type id.
 * @param[in]   CbFunc  : callback function pointer.
 *
 * @return      none
 *
 */
void Srmc_InstallCallBackFunc(Isr_CbFuncType * CbFunc);

/** @} end of group Public_FunctionDeclaration */

#endif /* SRMC_DRV_H */
