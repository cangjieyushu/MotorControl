/**************************************************************************************************/
/**
 * @file      : platform_cfg.h
 * @brief     : Z20K11xM Platform Config Header File.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef PLATFORM_CFG_H
#define PLATFORM_CFG_H

/** \mainpage Z20K11xM configuration

*/
/** \brief Configuration of Z20K11xM
*/
#define FLASH_CMD_FUNC_IN_RAM      1   /* Flash cmd functions are RAM functions */
#define DRV_DELAY_FUNC_IN_RAM      1   /* DRV_Delay function is RAM function */

#define ADC_TIMEOUT_WAIT_CNT_SWRST          10U      /* ADC software reset timeout value*/

#define CAN_TIMEOUT_WAIT_CNT_1              5000000U /* CAN timeout value1*/
#define CAN_TIMEOUT_WAIT_CNT_2              10000U   /* CAN timeout value2*/
#define CAN_TIMEOUT_WAIT_CNT_3              1000000U /* CAN timeout value3*/

#define CLK_WAITCONFIG_CNT                  3500U    /* Clock config counter value*/
#define CLK_TIMEOUT_WAIT_CNT                100000U  /* Clock timeout value*/
#define CLK_TIMEOUT_WAIT_CNT_OSC32K         5000000U /* OSC32K timeout value*/

#define FLASH_TIMEOUT_WAIT_CNT              100000U   /* Flash timeout value*/
#define FLASH_TIMEOUT_WAIT_CNT_ERASE_ALL    10000000U /* Flash erase timeout value*/
#define FLASH_TIMEOUT_ABORT_WAIT_CNT        100U      /* Flash abort timeout value*/

#define HWDIV_TIMEOUT_WAIT_CNT              10000U    /* HWDIV timeout value*/

#define WDOG_WAITCONFIG_GOING_CNT           0xFFFFFU  /* WDOG config timeout value*/

#define TDG_TIMEOUT_WAIT_CNT              10000U

#endif /* DEVICE_CFG_H */
