/**************************************************************************************************/
/**
 * @file     rtc_drv.h
 * @brief    RTC module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#ifndef RTC_DRV_H
#define RTC_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup   RTC
 *  @{
 */

/** @defgroup RTC_Public_Types
 *  @{
 */

/**
 *  @brief output clock type definition
 */
typedef enum
{
    RTC_SECONDS = 0U,                 /*!< rtc internal seconds counter  */
    RTC_32K_CLK                       /*!< RTC osc32k/lpo32k  */
} RTC_ClkOut_t;

/**
 *  @brief RTC source type definition
 */
typedef enum
{
    RTC_CLK_OSC32K_INT = 0U,     /*!<   internal OSC32K  */
    RTC_CLK_OSC32K_EXT,          /*!<   external OSC32K */
    RTC_CLK_LPO32K               /*!<   lpo32k  */             
} RTC_Clk_t;

/**
 *  @brief RTC interrupt type definition
 */
typedef enum
{
    RTC_INT_OVERFLOW = 0U,       /*!< RTC overflow interrupt*/
    RTC_INT_ALARM,               /*!< RTC alarm interrupt, frequency is 1Hz */
    RTC_INT_SECOND,              /*!< RTC second interrupt */
    RTC_INT_PERIODIC,            /*!< RTC periodic interrupt, frequency is 32kHz */
    RTC_INT_ALL
} RTC_Int_t;

/**
 *  @brief RTC second interrupt mux type definition
 */
typedef enum
{
    RTC_SECOND_1 = 0U,            /*!<  RTC select 1Hz to generate second interrupt */
    RTC_SECOND_64,                /*!<  RTC select 64Hz to generate second interrupt */
    RTC_SECOND_32,                /*!<  RTC select 32Hz to generate second interrupt */
    RTC_SECOND_16,                /*!<  RTC select 16Hz to generate second interrupt */
    RTC_SECOND_8,                 /*!<  RTC select 8Hz to generate second interrupt */
    RTC_SECOND_4,                 /*!<  RTC select 4Hz to generate second interrupt */
    RTC_SECOND_2,                 /*!<  RTC select 2Hz to generate second interrupt */
    RTC_SECOND_128                /*!<  RTC select 128Hz to generate second interrupt */
} RTC_SecondIntMuxSel_t;

/**
 *  @brief RTC frequency compensation direction type definition
 */
typedef enum
{
    RTC_COMP_UP = 0U,      /*!<  compensation direction up,  seconds frequency faster */
    RTC_COMP_DOWN          /*!<  compensation direction down,  seconds frequency  slower */
} RTC_CompDirection_t;

/**
 *  @brief RTC compensation config struct definition
 */
typedef struct
{
    uint8_t delayVal;           /*!< compensation delay value can be [1:255]
                                    how frequently RTC adjust its number of 32.768KHz 
                                    in each second*/
    uint8_t compVal;            /*!< compensation counter value, can be effect till DLY be 0 */
    RTC_CompDirection_t  dir;   /*!< frequency compensation direction */
} RTC_CompConfig_t;

/**
 *  @brief RTC output config struct definition
 */
typedef struct
{
    RTC_SecondIntMuxSel_t freqSel;
    RTC_ClkOut_t    clkOutput;    
} RTC_OutputConfig_t;

/** @} end of group RTC_Public_Types*/


/** @defgroup RTC_Public_FunctionDeclaration
 *  @brief RTC functions statement
 *  @{
 */

/**
 * @brief      RTC enable function
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_Enable(void);

/**
 * @brief      RTC disable function
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_Disable(void);

/**
 * @brief      Software reset all rtc registers except sw_rst bit
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_SWRest(void);

/**
 * @brief       config whether write access to RTC in non-supervisor
 *
 * @param[in]   cmd: ENABLE/DISABLE
 *
 * @return      none
 *
 */
void RTC_SupModeConfig(ControlState_t cmd);

/**
 * @brief       config second interrupt mux function
 *              need to configure this before enable second interrupt
 *
 * @param[in]   muxSel: select frequency to generate second frequency
 *
 * @return      none
 *
 */
void RTC_FreqMuxConfig(RTC_SecondIntMuxSel_t muxSel);

/**
 * @brief       Enable  RTC output clock function, then need to config clock source
 *
 * @param[in]   config: config clock output
 *
 * @return      none
 *
 */
void RTC_OutputConfig(RTC_OutputConfig_t * config);

/**
 * @brief      Enable  RTC output clock function
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_OutputEnable(void);

/**
 * @brief      Disable  RTC output clock function
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_OutputDisable(void);

/**
 * @brief      Enable  RTC periodic counter function, which is count with 32kHz 
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_PeriodicCounterEnable(void);

/**
 * @brief      Disable  RTC periodic counter function
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_PeriodicCounterDisable(void);

/**
 * @brief       Select clock source function. When clock source selected is from crystal, this API
 *              return SUCC means that the CRYSTAL_EN bit is set, but not means that OSC_RDY status
 *              asserts. User should call RTC_GetOSC32KReady API to check if OSC_RDY status asserts.
 *
 * @param[in]   clockSource:RTC clock source
 *
 * @return       
 *              -SUCC:clock config is success
 *              -ERR:clock config is fail
 *
 */
ResultStatus_t RTC_ClkConfig(RTC_Clk_t clockSource);

/**
 * @brief        Set alarm match counter, which also can clear alarm interrupt
 *               it can be written when rtc is enable
 *
 * @param[in]    matchValue:set the match value
 *
 * @return       none
 *
 *****************************************************************************/
void RTC_SetAlarmMatchCounter(uint32_t matchValue);

/**
 * @brief       Get alarm match counter register
 *
 * @param[in]   none
 *
 * @return      alarm match counter value
 *
 *****************************************************************************/
uint32_t RTC_GetAlarmMatchCounter(void);

/**
 * @brief       Set periodic counter start value when rtc is disable
 *
 * @param[in]   counterValue:set the counter start  value
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetPeriodicCounterValue(uint32_t counterValue);

/**
 * @brief       Get periodic counter value
 *
 * @param[in]   none
 *
 * @return      periodic counter value
 *
 *****************************************************************************/
uint32_t RTC_GetPeriodicCounter(void);

/**
 * @brief       Set periodic timer match value
 *
 * @param[in]   matchValue:set the counter match value
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetPeriodicMatchValue(uint32_t matchValue);

/**
 * @brief       Get alarm match counter value
 *
 * @param[in]   none
 *
 * @return      periodic match counter value
 *
 *****************************************************************************/
uint32_t RTC_GetPeriodicMatchCounter(void);

/**
 * @brief        Mask/Unmask the RTC interrupt function
 *
 * @param[in]    intType: select interrupt
 * @param[in]    intMask:Enable/Disable  interrupt
 *
 * @return       none
 *
 *****************************************************************************/
void RTC_IntMask(RTC_Int_t intType, IntMask_t intMask);

/**
 * @brief        Clear RTC interrupt status
 *               Note:Clear RTC overflow flag via writing 0 to one second counter, it 
 *               can be written only when rtc counter is disable
 *               reset match counter to clear alarm int status 
 *
 * @param[in]    intType: rtc interrupt
 *
 * @return       none
 *
 *****************************************************************************/
void RTC_ClearIntStatus(RTC_Int_t intType);

/**
 * @brief        Get RTC interrupt status
 *
 * @param[in]    intType: 
 *                      - RTC_INT_OVERFLOW
 *                      - RTC_INT_ALARM
 *                      - RTC_INT_SECOND
 *                      - RTC_INT_PERIODIC
 *
 * @return       none
 *
 *****************************************************************************/
IntStatus_t RTC_GetIntStatus(RTC_Int_t intType);

/**
 * @brief       Set alarm counter then alarm counter will count from this value
 *              Note: this value can be written when rtc is disable only and
 *              at the same time, written this register can clear overflow flag
 * 
 * @param[in]   countVal: set start value
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetAlarmCounter(uint32_t countVal);

/**
 * @brief       Read the current alarm counter function
 *
 * @param[in]   none
 *
 * @return      current alarm counter
 *
 *****************************************************************************/
uint32_t RTC_GetAlarmCounter(void);

/**
 * @brief       Get the current compensation delay value  function
 *
 * @param[in]   none
 *
 * @return      current compensation delay value
 *
 *****************************************************************************/
uint8_t RTC_GetCurrentCompDelayCVal(void);

/**
 * @brief       Get current compensation counter value  function
 *
 * @param[in]   none
 *
 * @return      current compensation value
 *
 *****************************************************************************/
uint8_t RTC_GetCurrentCompVal(void);

/**
 * @brief       Set compensation delay value function
 *
 * @param[in]   delayVal: delay value
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetCompDelayVal(uint8_t delayVal);

/**
 * @brief       Set frequency compensation direction function
 *
 * @param[in]   freqComp : select frequency compensation direction
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetCompDirection(RTC_CompDirection_t freqComp);

/**
 * @brief       Set compensation counter value function
 *
 * @param[in]   Val: counter value
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetCompVal(uint8_t Val);

/**
 * @brief       Get the current one second counter function
 *
 * @param[in]   none
 *
 * @return      current one second counter
 *
 *****************************************************************************/
uint16_t RTC_GetSecondCounter(void);

/**
 * @brief       Set the one second counter value effective when RTC is disable, write
 *               to one second counter also can clear OVF flag
 *
 * @param[in]   val: counter start from this value
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetSecondCounter(uint16_t val);

/**
 * @brief       Config the compensation  function
 *
 * @param[in]   config: compensation config
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_CompConfig(RTC_CompConfig_t * config);

/**
 * @brief       Disable the compensation  function
 *
 * @param[in]   none
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_CompDisable(void);

/**
 * @brief      Wait the clock source status until it is ready
 *
 * @param[in]  none
 *
 * @return     SUCC -- the clock is ready
 *             ERR -- time out
 *
 */
ResultStatus_t RTC_WaitOSC32KReady(void);

/**
 * @brief      Get the clock source status ready
 *             Please note that the OSC_RDY flag assert will take about 1.4s when select 
 *             RTC_CLK_OSC32K_INT source.
 *
 * @param[in]  none
 *
 * @return     SUCC -- the clock is ready
 *             ERR -- time out
 *
 */
ResultStatus_t RTC_GetOSC32KReady(void);

/**
 * @brief      install call back function
 *
 * @param[in]  intId: select the interrupt
 * @param[in]  cbFun: pointer to callback function
 *
 * @return none
 *
 */
void RTC_InstallCallBackFunc(RTC_Int_t intId,isr_cb_t * cbFun);



/** @} end of group RTC_Public_FunctionDeclaration */

/** @} end of group RTC  */

/** @} end of group Z20K14XM_Peripheral_Driver */

#endif /* RTC_DRV_H */
