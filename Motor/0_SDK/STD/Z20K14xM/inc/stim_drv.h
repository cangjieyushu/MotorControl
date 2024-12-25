/**************************************************************************************************/
/**
 * @file     stim_drv.h
 * @brief    STIM driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#ifndef STIM_DRV_H
#define STIM_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  STIM
 *  @{
 */

/** @defgroup STIM_Public_Types
 *  @{
 */

/**
 *  @brief STIM number type definition
 */
typedef enum
{
    STIM_0 = 0U,                               /*!< STIM_0 */
    STIM_1,                                    /*!< STIM_1 */
    STIM_2,                                    /*!< STIM_2 */
    STIM_3,                                    /*!< STIM_3 */
    STIM_NUM_ALL
} STIM_No_t;

/**
 *  @brief STIM clock source type definition
 */
typedef enum
{
    STIM_FUNCTION_CLOCK = 0U,            /*!< Select stim function clock as counter clock source. */
    STIM_SRC_BUS_CLOCK,                  /*!< Select bus clock as counter clock source. */
    STIM_SRC_OSC40M,                     /*!< Select OSC40M as counter clock source. */
    STIM_SRC_LPO32K                      /*!< Select LPO32K as counter clock source. */
} STIM_ClkSrc_t;

/**
 *  @brief STIM prescaler divider factor and glitch filter value type definition
 */
typedef enum
{
    STIM_DIV_2 = 0U,                    /*!< divide the system clock by 2 as counter clock; 
                                             glitch filter don't support this configuration. */
    STIM_DIV_4_FILTER_1,                /*!< divide the system clock by 4 as counter clock; 
                                             pulse width less than 1 system clock period will be 
                                             filtered as glitch. */
    STIM_DIV_8_FILTER_3,                /*!< divide the system clock by 8 as counter clock; 
                                             pulse width less than 3 system clock period will be 
                                             filtered as glitch. */
    STIM_DIV_16_FILTER_7,               /*!< divide the system clock by 16 as counter clock; 
                                             pulse width less than 7 system clock period will be 
                                             filtered as glitch. */
    STIM_DIV_32_FILTER_15,              /*!< divide the system clock by 32 as counter clock;
                                             pulse width less than 15 system clock period will be 
                                             filtered as glitch. */
    STIM_DIV_64_FILTER_31,              /*!< divide the system clock by 64 as counter clock; 
                                             pulse width less than 31 system clock period will be 
                                             filtered as glitch. */
    STIM_DIV_128_FILTER_63,             /*!< divide the system clock by 128 as counter clock; 
                                             pulse width less than 63 system clock period will be 
                                             filtered as glitch. */
    STIM_DIV_256_FILTER_127,            /*!< divide the system clock by 256 as counter clock; 
                                            pulse width less than 127 system clock period will be 
                                            filtered as glitch. */
    STIM_DIV_512_FILTER_255,            /*!< divide the system clock by 512 as counter clock; 
                                             pulse width less than 255 system clock period will be 
                                             filtered as glitch. */
    STIM_DIV_1024_FILTER_511,           /*!< divide the system clock by 1024 as counter clock;
                                             pulse width less than 511 system clock period will be 
                                             filtered as glitch. */
    STIM_DIV_2048_FILTER_1023,          /*!< divide the system clock by 2048 as counter clock; 
                                             pulse width less than 1023 system clock period will
                                              be filtered as glitch. */
    STIM_DIV_4096_FILTER_2047,          /*!< divide the system clock by 4096 as counter clock; 
                                             pulse width less than 2047 system clock period will be
                                              filtered as glitch. */
    STIM_DIV_8192_FILTER_4095,          /*!< divide the system clock by 8192 as counter clock;
                                             pulse width less than 4095 system clock period will be
                                              filtered as glitch. */
    STIM_DIV_16384_FILTER_8191,         /*!< divide the system clock by 16384 as counter clock; 
                                             pulse width less than 8191 system clock period will be 
                                             filtered as glitch. */
    STIM_DIV_32768_FILTER_16383,        /*!< divide the system clock by 32768 as counter clock; 
                                             pulse width less than 16383 system clock period will be
                                             filtered as glitch. */
    STIM_DIV_65536_FILTER_32767         /*!< divide the system clock by 65536 as counter clock; 
                                             pulse width less than 32767 system clock period will be
                                             filtered as glitch. */
} STIM_PsOrFilter_t;

/**
 *  @brief STIM input pin polarity type definition
 */
typedef enum
{
    STIM_ACTIVE_HIGH = 0U,                     /*!< input pin polarity is active high. */
    STIM_ACTIVE_LOW                            /*!< input pin polarity is acitve low. */
} STIM_PinPolarity_t;

/**
 *  @brief STIM input pin source type definition
 */
typedef enum
{
    STIM_PIN_0 = 0U,            /*!< input pin 0 is selected.Input pin 0 resource is come from TMU*/
    STIM_PIN_1,                 /*!< input pin 1 is selected.Input pin 1 is from pads */
    STIM_PIN_2,                 /*!< input pin 2 is selected.Input pin 2 is from pads */
    STIM_PIN_3                  /*!< input pin 3 is selected.Input pin 3 is from pads */
} STIM_PinSrc_t;

/**
 *  @brief STIM mode type definition
 */
typedef enum
{
    STIM_FREE_COUNT = 0U,                      /*!< counter operates in free counting mode. */
    STIM_PULSE_COUNT                           /*!< counter operates in pulse counting mode. */
} STIM_Mode_t;

/**
 *  @brief STIM counter reset disable on match type definition
 */
typedef enum
{
    STIM_INCREASE_FROM_0 = 0U, /*!< stim counter reset and increments from 0 when counter match. */
    STIM_INCREASE_CONTINUE     /*!< stim counter continue to increment when counter match. */
} STIM_CountReset_t;

/**
 *  @brief STIM interrupt type definition
 */
typedef enum
{
    STIM_INT = 0U,                             /*!< Interrupt */
    STIM_INT_ALL
} STIM_Int_t;

/**
 *  @brief STIM configuration struct definition
 */
typedef struct
{
    STIM_Mode_t workMode;                   /*!< Configure mode type.
                                                  - STIM_FREE_COUNT
                                                  - STIM_PULSE_COUNT*/
    uint32_t  compareValue;                 /*!< When the counter is enabled, updating the related 
                                               CV register by software will reset the corresponding
                                               counter value and counter restart to count from 0. */
    STIM_CountReset_t  countResetMode;      /*!< This defines whether counter reset when counter 
                                                 matches the compare value.
                                                  - STIM_INCREASE_FROM_0: stim counter reset and 
                                                              increments from 0 when counter match.
                                                  - STIM_INCREASE_CONTINUE: stim counter continue 
                                                              to increment when counter match.*/
    STIM_ClkSrc_t  clockSource;           /*!< Select which clock source as counter system clock. */
    STIM_PinSrc_t  pinSource;             /*!< Input pin source was selected as input pulse for 
                                               pulse counting mode. */
    STIM_PinPolarity_t  pinPolarity;      /*!< Input pin polarity was selected for pulse counting 
                                              mode.In free counting mode,counter increments on the 
                                              rising edge of divided clock source. */
    STIM_PsOrFilter_t  prescalerOrFilterValue; /*!< In pulse counting mode, if PSEN is enabled, 
                                                    PSDIV can not be configured as 0, otherwise 
                                                    will get unpredictable result.
                                                  - In free counting mode: PSDIV is used as the 
                                                                           clock divider factor.
                                                  - In pulse counting mode: PSDIV is used as the
                                                                            glitch filter value. */
    ControlState_t  prescalerMode;              /*!< Prescaler enable/disable.
                                                  - In free counting mode, PSEN is used to
                                                    enable the prescaler.
                                                  - In pulse counting mode, PSEN is used to
                                                    enable the glitch filter.*/
} STIM_Config_t;

/** @} end of group STIM_Public_Types */

/** @defgroup STIM_Public_Macro
 *  @{
 */

/** @} end of group STIM_Public_Macro */

/** @defgroup STIM_Public_FunctionDeclaration
 *  @brief STIM functions declaration
 *  @{
 */

/**
 * @brief      Install call back function
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 * @param[in]  intType: Select the interrupt.
 *             - STIM_INT
 * @param[in]  cbFun: pointer to callback function.
 *
 * @return     none
 *
 */
void STIM_InstallCallBackFunc(STIM_No_t stimNo, STIM_Int_t intType,
                               isr_cb_t * cbFun);
/**
 * @brief      Initialize STIM configuration
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 * @param[in]  stimConfigStruct: Stim configuration struct.
 *
 * @return     none
 *
 */
void STIM_Init(STIM_No_t stimNo, const STIM_Config_t* stimConfigStruct);

/**
 * @brief      Set compare value 
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 * @param[in]  compareValue: Stim compare value.
 *
 * @return     none
 *
 */
void STIM_SetCompareValue(STIM_No_t stimNo, uint32_t compareValue);

/**
 * @brief      Current Value of stim
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 *
 * @return     value of stim
 *
 */
uint32_t STIM_GetCurrentCounterValue(STIM_No_t stimNo);

/**
 * @brief      Enable stim
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *             STIM_3.
 *
 * @return     none
 *
 */
void STIM_Enable(STIM_No_t stimNo);

/**
 * @brief      Disable stim
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *             STIM_3.
 *
 * @return     none
 *
 */
void STIM_Disable(STIM_No_t stimNo);

/**
 * @brief       Enable/Disable the stim interrupt
 *
 * @param[in]   stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                      STIM_3.
 * @param[in]   newState: Enable/Disable function state.
 *             - ENABLE: enable interrupt
 *             - DISABLE: disable interrupt
 *
 * @return      none
 *
 */
void STIM_IntCmd(STIM_No_t stimNo, ControlState_t newState);

/**
 * @brief      Enable or disable the STIM DMA function.
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 * @param[in]  newState: Enable/Disable function state.
 *             - ENABLE: enable DMA request
 *             - DISABLE: disable DMA request
 *
 * @return     none
 *
 */
void STIM_DmaCmd(STIM_No_t stimNo, ControlState_t newState);

/**
 * @brief      Checks if the status flag is set when the counter matches the
 *             compare value
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 *
 * @return     The status flag.
 *             - SET
 *             - RESET
 *
 */
FlagStatus_t STIM_GetStatus(STIM_No_t stimNo);

/**
 * @brief      Clear the interrupt of stim
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 *
 * @return     none
 *
 */
void STIM_ClearInt(STIM_No_t stimNo);

/** @} end of group STIM_Public_FunctionDeclaration */

/** @} end of group STIM */

/** @} end of group Z20K14XM_Peripheral_Driver */

#endif /* STIM_DRV_H */
