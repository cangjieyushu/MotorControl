/**************************************************************************************************/
/**
 * @file      : Z20K11xM_drv.h
 * @brief     : Drv common module header file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef Z20K11XM_DRV_H
#define Z20K11XM_DRV_H

#include "device_regs.h"
#include "Z20K11xM_cfg.h"

/** @addtogroup  Z20K11X_Periph_Drv
 *  @{
 */

/** @addtogroup  DRV_COMMON
 *  @{
 */

/** @defgroup DRV_Public_Types
 *  @brief DRV type definition
 *  @{
 */

/* Core_definition Processor and Core Peripheral definition */
#include "core_cm0plus.h"                       /*!< Cortex-M0+ processor and core peripherals  */

#if defined ( __ICCARM__ )
    #define START_FUNCTION_DECLARATION_RAMSECTION      __ramfunc
    #define END_FUNCTION_DECLARATION_RAMSECTION     ;
#elif defined  (__ARMCC_VERSION)
    #define START_FUNCTION_DECLARATION_RAMSECTION
    #define END_FUNCTION_DECLARATION_RAMSECTION        __attribute__((section (".code_ram")));
#elif defined (__GNUC__)
    #define START_FUNCTION_DECLARATION_RAMSECTION
    #define END_FUNCTION_DECLARATION_RAMSECTION        __attribute__((section (".code_ram")));
#else 
     #define START_FUNCTION_DECLARATION_RAMSECTION      
     #define END_FUNCTION_DECLARATION_RAMSECTION        ;
#endif
     
#if defined (__ICCARM__)
    #define DISABLE_CHECK_RAMSECTION_FUNCTION_CALL     _Pragma("diag_suppress=Ta022")
    #define ENABLE_CHECK_RAMSECTION_FUNCTION_CALL      _Pragma("diag_default=Ta022")
#else
    #define DISABLE_CHECK_RAMSECTION_FUNCTION_CALL
    #define ENABLE_CHECK_RAMSECTION_FUNCTION_CALL
#endif

/**
 * @brief Control State Type Definition
 */
typedef enum
{
    DISABLE  = 0U,
    ENABLE   = 1U
}ControlState_t;

/**
 * @brief Result status Type definition
 */
typedef enum
{
    SUCC = 0U,
    ERR = 1U,
    BUSY = 2U
}ResultStatus_t;

/**
 * @brief Flag/Int status Type definition
 */
typedef enum
{
    RESET = 0,
    SET = 1
}FlagStatus_t, IntStatus_t;

/**
 * @brief interrupt mask Type definition
 */
typedef enum
{
    UNMASK = 0,
    MASK = 1
}IntMask_t;



/**
 *  @brief ISR callback function type
 */
typedef void (isr_cb_t)(void);


/** @} end of group DRV_Public_Types */


/** @defgroup DRV_Public_Constants
 *  @{
 */

/** @} end of group DRV_Public_Constants */

/** @defgroup DRV_Public_Macro
 *  @{
 */

#ifdef  DEBUG
/**
 * @brief		The CHECK_PARAM macro is used for function's parameters check.
 * 				It is used only if the library is compiled in DEBUG mode.
 * @param[in]	expr: - If expr is false, it calls check_failed() function
 *               which reports the name of the source file and the source
 *               line number of the call that failed.
 *                     - If expr is true, it returns no value.
 * @return  none
 */
void check_failed(uint8_t *file, uint32_t line);
#define CHECK_PARAM(expr) ((expr) ? (void)0 : check_failed((uint8_t *)__FILE__, __LINE__))
#else
#define CHECK_PARAM(expr) ((void)0)
#endif /* DEBUG */

/**
 * @brief Reverse byte order in a word
 */
#if defined (__ICCARM__)
#define REV_BYTES_32(a, b) __asm volatile ("rev %0, %1" : "=r" (b) : "r" (a))
#else
#define REV_BYTES_32(a, b) (b = ((a & 0xFF000000U) >> 24U) | ((a & 0xFF0000U) >> 8U) \
                                | ((a & 0xFF00U) << 8U) | ((a & 0xFFU) << 24U))
#endif

/** @} end of group DRV_Public_Macro */

/** @defgroup DRV_Public_FunctionDeclaration
 *  @brief DRV functions declaration
 *  @{
 */

/**
 * @brief      Delay for some cycles
 *
 * @param[in]  delayCount: the cycles to delay
 *
 * @return     None
 *
 */
#if( DRV_DELAY_FUNC_IN_RAM == 1)
START_FUNCTION_DECLARATION_RAMSECTION
void Drv_Delay(uint32_t delayCount)
END_FUNCTION_DECLARATION_RAMSECTION     /*PRQA S 0605*/
#else
void Drv_Delay(uint32_t delayCount);
#endif

/** @} end of group DRV_Public_FunctionDeclaration */

/** @} end of group DRV_COMMON  */

/** @} end of group Z20K11X_Periph_Drv */

#endif /* Z20K11XM_DRV_H */
