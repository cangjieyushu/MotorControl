/**************************************************************************************************/
/**
 * @file      : Platform_Cfg.h
 * @brief     : Z20M1343L platform config header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef PLATFORM_CFG_H
#define PLATFORM_CFG_H

/**
 *  @brief Timeout configuration parameter
*/
#define FLASH_CMD_FUNC_IN_RAM               1U   /* Flash cmd functions are RAM functions */

#define FLASH_TIMEOUT_WAIT_CNT              1440000U   /* Flash timeout value*/
#define FLASH_TIMEOUT_WAIT_CNT_ERASE_ALL    72000000U /* Flash erase timeout value*/
#define FLASH_TIMEOUT_ABORT_WAIT_CNT        300U      /* Flash abort timeout value*/

#define FLASH_PFLASH                             /* P-flash */

#define CLK_WAITCONFIG_CNT                  3500U    /* Clock config counter value*/
#define CLK_TIMEOUT_WAIT_CNT                50000U   /* Clock timeout value*/

#define WDOG_WAITCONFIG_GOING_CNT           0xFFFFFU  /* WDOG config timeout value*/

#define ADC_TIMEOUT_WAIT_CNT_SWRST          10U      /* Adc timeout value */

#define SCM_SRAM_INIT_TIMEOUT_WAIT_CNT      200U     /* SRAM init done timeout waiting value*/

#define SRMC_SW_RESET_WAIT_CNT              50U      /* SRMC software reset waiting value*/

#endif /* PLATFORM_CFG_H */
