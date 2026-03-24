/**************************************************************************************************/
/**
 * @file     srmc_drv.h
 * @brief    SRMC driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef SRMC_DRV_H
#define SRMC_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SRMC
 *  @{
 */

/** @defgroup SRMC_Public_Types 
 *  @{
 */

/**
 *  @brief SRMC reset cause type definition
 */
typedef enum
{
    SRMC_RESET_TYPE_STB_WAKEUP  = 0x00000001U,    /*!< SRMC RESET by Standby wakeup detected  */
    SRMC_RESET_TYPE_LVD         = 0x00000002U,    /*!< SRMC RESET by Low Voltage detected  */
    SRMC_RESET_TYPE_LOC         = 0x00000004U,    /*!< SRMC RESET by Loss of External Clock  */
    SRMC_RESET_TYPE_WDOG        = 0x00000020U,    /*!< SRMC RESET by Watchdog Timer Timing Out  */
    SRMC_RESET_TYPE_PIN         = 0x00000040U,    /*!< SRMC RESET by an Active_low Level on 
                                                        the External RESET Pin  */
    SRMC_RESET_TYPE_POR         = 0x00000080U,    /*!< SRMC RESET by Power-on Detection Logic  */
    SRMC_RESET_TYPE_LOCKUP      = 0x00000200U,    /*!< SRMC RESET by ARM Core Indication of 
                                                        a LOCKUP event  */
    SRMC_RESET_TYPE_SW          = 0x00000400U,    /*!< SRMC RESET by Software Setting of 
                                                        SYSRESETREQ bit  */
    SRMC_RESET_TYPE_MDM_AP      = 0x00000800U,    /*!< SRMC RESET by Host Debugger System Setting
                                                        in the MDM-AP Control Register  */
    SRMC_RESET_TYPE_SERU_COLD   = 0x00001000U,    /*!< SRMC RESET by SERU Cold Reset Request */
    SRMC_RESET_TYPE_SERU_SYS    = 0x00002000U,    /*!< SRMC RESET by SERU System Reset Request */
    SRMC_RESET_TYPE_SACKERR     = 0x00008000U,    /*!< SRMC RESET by Fail to ACK attempt to 
                                                        Enter Stop Mode */
    SRMC_RESET_TYPE_ALL         = 0x0000BEE7U
} SRMC_ResetCause_t;

/**
 *  @brief SRMC reset Pin Filter definition
 */
typedef enum
{
    SRMC_RESET_PIN_DISABLE_FILTER = 0U,       /*!< SRMC RESET Pin filter disabled  */
    SRMC_RESET_PIN_BUS_CLOCK_FILTER,          /*!< SRMC RESET Pin bus clock filter */
    SRMC_RESET_PIN_LPO_CLOCK_FILTER           /*!< SRMC RESET Pin lpo clock filter */
} SRMC_ResetPinFilter_t;

/**
 *  @brief SRMC Interrupt type definition
 */
typedef enum
{
    SRMC_INT_TYPE_LOC = 0U,                   /*!< SRMC int loc  */
    SRMC_INT_TYPE_WDOG,                       /*!< SRMC int wdog  */
    SRMC_INT_TYPE_PIN,                        /*!< SRMC int pin  */
    SRMC_INT_TYPE_LOCKUP,                     /*!< SRMC int lockup  */
    SRMC_INT_TYPE_SW,                         /*!< SRMC int software */
    SRMC_INT_TYPE_SERU_COLD,                  /*!< SRMC int SERU Cold Reset Request*/
    SRMC_INT_TYPE_SERU_SYS,                   /*!< SRMC int SERU System Reset Request */
    SRMC_INT_TYPE_SACKERR,                    /*!< SRMC int stop ack error  */
    SRMC_INT_TYPE_ALL
} SRMC_Int_t;

/**
 *  @brief SRMC delay type definition
 */
typedef enum
{
    SRMC_DELAY_8_LPO_CYCLES = 0U,            /*!< SRMC delay 8 lpo cycles  */
    SRMC_DELAY_32_LPO_CYCLES,                /*!< SRMC delay 32 lpo cycles  */
    SRMC_DELAY_128_LPO_CYCLES,               /*!< SRMC delay 128 lpo cycles  */
    SRMC_DELAY_512_LPO_CYCLES                /*!< SRMC delay 512 lpo cycles  */
} SRMC_Delay_t;

/**
 *  @brief SRMC powermode type definition
 */
typedef enum
{
    SRMC_POWERMODE_RUN = 0U,                /*!< SRMC run mode  */
    SRMC_POWERMODE_WAIT,                    /*!< SRMC wait mode  */
    SRMC_POWERMODE_STOP,                    /*!< SRMC stop mode  */
    SRMC_POWERMODE_STANDBY                  /*!< SRMC standby mode  */
} SRMC_PowerMode_t;

/**
 *  @brief SRMC stop mode(deep sleep mode) aborted status type definition
 */
typedef enum
{
    SRMC_STOP_SUCCESS = 0U,                /*!< SRMC enter stop mode: success  */
    SRMC_STOP_ABORT                        /*!< SRMC enter stop mode: abort  */
} SRMC_StopModeStatus_t;

/**
 *  @brief SRMC wakeup source type definition
 */
typedef enum
{
    SRMC_WUPSRC_PTD0  = 0x0U,  /*!< SRMC wakeup source: PTD0 pin */
    SRMC_WUPSRC_PTD1  = 0x1U,  /*!< SRMC wakeup source: PTD1 pin*/
    SRMC_WUPSRC_PTA4  = 0x2U,  /*!< SRMC wakeup source: PTA4 pin*/
    SRMC_WUPSRC_PTC4  = 0x4U,  /*!< SRMC wakeup source: PTC4 pin*/
    SRMC_WUPSRC_PTC5  = 0x5U,  /*!< SRMC wakeup source: PTC5 pin*/
    SRMC_WUPSRC_PTE0  = 0x6U,  /*!< SRMC wakeup source: PTE0 pin*/
    SRMC_WUPSRC_PTE1  = 0x7U,  /*!< SRMC wakeup source: PTE1 pin*/
    SRMC_WUPSRC_PTE11 = 0x8U,  /*!< SRMC wakeup source: PTE11 pin*/
    SRMC_WUPSRC_PTE13 = 0x9U,  /*!< SRMC wakeup source: PTE13 pin*/
    SRMC_WUPSRC_PTE15 = 0xAU,  /*!< SRMC wakeup source: PTE15 pin*/
    SRMC_WUPSRC_PTE16 = 0xBU,  /*!< SRMC wakeup source: PTE16 pin*/
    SRMC_WUPSRC_PTA8  = 0xCU,  /*!< SRMC wakeup source: PTA8 pin*/
    SRMC_WUPSRC_PTA9  = 0xDU,  /*!< SRMC wakeup source: PTA9 pin*/
    SRMC_WUPSRC_PTA25 = 0xEU,  /*!< SRMC wakeup source: PTA25 pin*/
    SRMC_WUPSRC_PMU   = 0xFU,  /*!< SRMC wakeup source: PMU */
    SRMC_WUPSRC_RTC   = 0x10U  /*!< SRMC wakeup source: RTC */
} SRMC_WakeupSource_t;

/**
 *  @brief SRMC wakeup source polarity type definition
 */
typedef enum
{
    SRMC_WUPPL_LOW    = 0x0U,  /*!< SRMC wakeup source polarity: active low */
    SRMC_WUPPL_HIGH   = 0x1U   /*!< SRMC wakeup source polarity: active high */
}SRMC_WakePolarity_t;

/** @} end of group SRMC_Public_Types */

/** @defgroup SRMC_Public_FunctionDeclaration
 *  @brief SRMC functions declaration
 *  @{
 */
/**
 * @brief       Configure core lockup reset enable/disable
 *
 * @param[in]  cmd:          control cmd:   DISABLE; ENABLE.
 *
 * @return none
 *
 */
void SRMC_CoreLockupResetCtrl(ControlState_t cmd);

/**
 * @brief       SRMC wakeup source polarity config
 *
 * @param[in]  source:          wakeup source select.
 * @param[in]  polarity:        active polarity.
 *                              - SRMC_WUPPL_LOW
 *                              - SRMC_WUPPL_HIGH
 *
 * @return none
 *
 */
void SRMC_WakeupSourceConfig(SRMC_WakeupSource_t source, SRMC_WakePolarity_t polarity);

/**
 * @brief       SRMC wakeup source function enable/disable
 *
 * @param[in]  source:          wakeup source select.
 * @param[in]  cmd:             enable/disable.
 *
 * @return none
 *
 */
void SRMC_WakeupSourceCtrl(SRMC_WakeupSource_t source, ControlState_t cmd);

/**
 * @brief       SRMC get wakeup source status, indicating corresponding wakeup 
 *              source waked up system
 *
 * @param[in]  source:          wakeup source select.
 *
 * @return status
 *
 */
FlagStatus_t SRMC_GetWakeupSourceStatus(SRMC_WakeupSource_t source);

/**
 * @brief       SRMC clear wakeup source status, indicating corresponding wakeup 
 *              source waked up system
 *
 * @param[in]  source:          wakeup source select.
 *
 * @return none
 *
 */
void SRMC_ClearWakeupSourceStatus(SRMC_WakeupSource_t source);

/**
 * @brief       configure reset pin filter bus clock width,
 *              actual reset pin bus clock filter width cycle = clkCycles + 1
 *
 * @param[in]  clkCycles:          cycle number.
 *
 * @return none
 *
 */
void SRMC_ResetPinFilterBusClockConfig(uint8_t clkCycles);

/**
 * @brief       configure how reset pin filter is enabled in stop mode
 *
 * @param[in]  filterType:    only two type used in stop mode, as below
 *                                  - SRMC_RESET_PIN_DISABLE_FILTER
 *                                  - SRMC_RESET_PIN_LPO_CLOCK_FILTER
 *
 * @return none
 *
 */
void SRMC_ResetPinFilterInStopMode(SRMC_ResetPinFilter_t filterType);

/**
 * @brief       configure how reset pin filter is enabled in run and wait mode
 *
 * @param[in]  filterType:    three type used in run and wait mode, as below
 *                                 - SRMC_RESET_PIN_DISABLE_FILTER
 *                                 - SRMC_RESET_PIN_BUS_CLOCK_FILTER
 *                                 - SRMC_RESET_PIN_LPO_CLOCK_FILTER
 *
 * @return none
 *
 */
void SRMC_ResetPinFilterInRunAndWaitMode(SRMC_ResetPinFilter_t filterType);

/**
 * @brief       Get the status that if the pointed reset type is the system
 *              reset cause.
 *
 * @param[in]  resetCauseType:          reset cause type.
 *
 * @return     status
 *
 */
FlagStatus_t SRMC_GetSystemResetStatus(SRMC_ResetCause_t resetCauseType);

/**
 * @brief       Clear the status that if the pointed reset type.
 *
 * @param[in]  resetCauseType:          reset cause type.
 *
 * @return     status
 *
 */
void SRMC_ClearSystemResetStatus(SRMC_ResetCause_t resetCauseType);

/**
 * @brief       Get system reset all causes
 *
 * @param[in]  none
 *
 * @return     reset cause type(uint32 value): one bit, one cause;
 *             seeing SRMC_ResetCause_t type; 
 *
 */
uint32_t SRMC_GetSystemResetCause(void);

/**
 * @brief       Unmask/Mask pointed interrupt
 *
 * @param[in]  intType:          srmc interrupt source.
 * @param[in]  intMask:          UNMASK or MASK.
 *
 * @return     none
 *
 */
void SRMC_IntMask(SRMC_Int_t intType, IntMask_t intMask);

/**
 * @brief       Configure max reset delay time from when the interrupt is 
 *              asserted and the system reset occurs.
 *
 * @param[in]  delayType:          delay cycle type.
 *
 * @return     none
 *
 */
void SRMC_MaxResetDelayTimeConfig(SRMC_Delay_t delayType);

/**
 * @brief       Configure standby mode entry allowed or not
 *
 * @param[in]  cmd:          DISABLE or ENABLE.
 *
 * @return     none
 *
 */
void SRMC_AllowStandbyMode(ControlState_t cmd);

/**
 * @brief       Set system enter wait mode
 *
 * @param[in]  none
 * 
 * @return     none
 *
 */
void SRMC_EnterWaitMode(void);

/**
 * @brief       Set system enter stop mode(deep sleep mode)
 *
 * @param[in]  ackTimeout: stop mode(deep sleep mode) acknowledge time out
 * @note       setting ackTimeout to 0 means the stop sequence will wait forever
 *
 * @return     none
 *
 */
void SRMC_EnterStopMode(uint8_t ackTimeout);

/**
 * @brief       Set system enter standby mode
 *
 * @param[in]  ackTimeout: low power mode acknowledge time out. 
 * @note       setting ackTimeout to 0 means the stop sequence will wait forever
 * 
 * @return     none
 *
 */
void SRMC_EnterStandbyMode(uint8_t ackTimeout);

/**
 * @brief       Get current power mode
 *
 * @param[in]  none
 *
 * @return     power mode type
 *
 */
SRMC_PowerMode_t SRMC_GetCurrentPowerMode(void);

/**
 * @brief       Get previous stop mode(deep sleep mode) entry status
 *
 * @param[in]  none
 *
 * @return     stop entry status: 
 *                               - SRMC_STOP_SUCCESS; 
 *                               - SRMC_STOP_ABORT.
 *
 */
SRMC_StopModeStatus_t SRMC_GetStopAbortedStatus(void);

/**
 * @brief       install callback function
 *
 * @param[in]  cbFun  : callback function pointer
 *
 * @return     stop entry status: 
 *                               - SRMC_STOP_SUCCESS;
 *                               - SRMC_STOP_ABORT.
 *
 */
void SRMC_InstallCallBackFunc(isr_cb_t * cbFun);

/** @} end of group SRMC_Public_FunctionDeclaration */

/** @} end of group SRMC */

/** @} end of group Z20K14XM_Peripheral_Driver */
#endif /* SRMC_DRV_H */
