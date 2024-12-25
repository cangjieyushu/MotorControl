/****************************************************************************//**
 * @file     platform_cfg.h
 * @brief    Z20K14xM Platform Config Header File.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 *******************************************************************************/

#ifndef PLATFORM_CFG_H
#define PLATFORM_CFG_H

/** \mainpage Z20K14XM configuration

*/
/** \brief Configuration of Z20K14XM
*/
#define FLASH_CMD_FUNC_IN_RAM      1   /* Flash cmd functions are RAM functions */
#define DRV_DELAY_FUNC_IN_RAM      1   /* DRV_Delay function is RAM function */

/* The parameters below are evaluated on sram with core clock frequency of 160MHz and bus clock of
 * 80MHz, compiled with IAR(v8.32, no optimizations). User need to evaluate the value if necessary
 * to be compatible with actual configuration and design purpose. For example, to be aligned with
 * system FDTI requirements, parameters need to be carefully evaluated and tested.
 */
#define ADC_TIMEOUT_WAIT_CNT_SWRST          10U      /* ADC software reset timeout value, \
                                                        this default value is about 675ns */

#define CAN_TIMEOUT_WAIT_CNT_1              5000000U /* CAN timeout value1 when entering freeze \
                                                        mode, this default value represents about \
                                                        562ms waiting for CAN_MCR.FRZACK asserted \
                                                        and about 625ms waiting for CAN_MCR.NOTRDY \
                                                        asserted */
#define CAN_TIMEOUT_WAIT_CNT_2              10000U   /* CAN timeout value2, this default value is \
                                                        about 1.125ms waiting for exiting freeze \
                                                        mode(CAN_MCR.FRZACK deasserted), software \
                                                        reset(CAN_MCR.SOFTRST deasserted) or \
                                                        entering/exiting low power mode \
                                                        (CAN_MCR.LPMACK asserted/deasserted) */
#define CAN_TIMEOUT_WAIT_CNT_3              1000000U /* CAN timeout value3, this default value is \
                                                        about 150ms waiting for MB not busy and \
                                                        about 312.5ms waiting for abort completed */

#define CLK_TIMEOUT_WAIT_CNT                100000U  /* Clock timeout value, this default value \
                                                        is about 31.25ms waiting for clock ready \
                                                        after it enabled*/
#define CLK_TIMEOUT_WAIT_CNT_OSC32K         5000000U /* OSC32K timeout value, this default \
                                                        value is about 1.4687s waiting for OSC32K \
                                                        clock ready*/
#define FLASH_TIMEOUT_WAIT_CNT              300000U   /* Flash timeout value, this default value \
                                                         is about 45ms waiting for all flash \
                                                         commands complete except FLASH_CMD_ERSALL \
                                                         (erase all flash and IFR space)*/
#define FLASH_TIMEOUT_WAIT_CNT_ERASE_ALL    30000000U /* Flash erase timeout value, this default \
                                                         value is about 4.5s waiting for flash 
                                                         command to erase all flash and IFR space \
                                                         completes */
#define FLASH_TIMEOUT_ABORT_WAIT_CNT        300U      /* Flash abort timeout value, this default \
                                                         value is about 0.071ms for flash request \
                                                         to abort a command write sequence */

#define TRNG_TIMEOUT_WAIT_CNT               10000U    /* TRNG operation timeout value when reseed\
                                                         successfully, this default value is about\
                                                         1625us waiting for random data generation */

#define WDOG_WAITCONFIG_GOING_CNT           0xFFFFFU  /* WDOG config timeout value, this default \
                                                         value is about 131.1ms to wait until \
                                                         configuration update is completed */

#define TDG_TIMEOUT_WAIT_CNT                10000U    /* TDG load command timeout value, \
                                                         this default value is about 1.125ms */

#define AES_TIMEOUT_WAIT_CNT                50U       /* AES operation timeout value, \
                                                         this default value is about 5125ns */

#define RTC_WAIT_CNT                        100000U   /* RTC OSC32K from external square wave \
                                                         waiting ready counter, this default value \
                                                         is about 15ms*/
#define RTC_WAIT_CNT_SWRST                  4000U     /* RTC software reset waiting ready counter, \
                                                         this default value is about 0.25ms*/                                                     

#endif /* PLATFORM_CFG_H */
