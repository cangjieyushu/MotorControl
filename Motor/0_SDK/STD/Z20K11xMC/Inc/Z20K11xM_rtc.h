/**************************************************************************************************/
/**
 * @file      : Z20K11xM_rtc.h
 * @brief     : RTC module driver header file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef Z20K11XM_RTC_H__
#define Z20K11XM_RTC_H__

#include "Z20K11xM_drv.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @addtogroup  	RTC
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
}RTC_ClkOut_t;

/**
 *  @brief RTC source type definition
 */
typedef enum
{
    RTC_CLK_DISABLE = 0U,   /*!<  clock source disable  */
    RTC_CLK_OSC32K_INT,     /*!<   crystal: OSC clock comes 
                                    from crystal oscillator  */
    RTC_CLK_LPO32K,         /*!<   lpo32k  */
    RTC_CLK_OSC32K_EXT      /*!<   external source: OSC clock comes 
                                    from a external square wave clock source */
}RTC_Clk_t;

/**
 *  @brief RTC status type definition,second interrupt has no flag bit
 */
typedef enum
{
    RTC_STATUS_OVF = 0U,          /*!<  RTC overflow flag*/
    RTC_STATUS_ALARM_MATCH,       /*!<  RTC alarm match flag*/
    RTC_STATUS_SECONGD            /*!<  RTC seconds interrupt flag  */
}RTC_Status_t;

/**
 *  @brief RTC interrupt type definition
 */
typedef enum
{
    RTC_INT_OVERFLOW = 0U,        /*!< RTC overflow interrupt*/
    RTC_INT_ALARM,                /*!< RTC alarm interrupt */
    RTC_INT_SECOND,               /*!< RTC second interrupt */
    RTC_INT_ALL
}RTC_Int_t;

/**
 *  @brief RTC second interrupt mux type definition
 */
typedef enum
{
    RTC_SECOND_1 = 0U,    /*!<  RTC select 1Hz to generate second interrupt */
    RTC_SECOND_64,        /*!<  RTC select 64Hz to generate second interrupt */
    RTC_SECOND_32,        /*!<  RTC select 32Hz to generate second interrupt */
    RTC_SECOND_16,        /*!<  RTC select 16Hz to generate second interrupt */
    RTC_SECOND_8,         /*!<  RTC select 8Hz to generate second interrupt */
    RTC_SECOND_4,         /*!<  RTC select 4Hz to generate second interrupt */
    RTC_SECOND_2,         /*!<  RTC select 2Hz to generate second interrupt */
    RTC_SECOND_128        /*!<  RTC select 128Hz to generate second interrupt*/
}RTC_SecondIntMuxSel_t;

/**
 *  @brief RTC frequency compensation direction type definition
 */
typedef enum
{
    RTC_COMP_UP = 0U,   /*!<  compensation direction up,  
                                    seconds frequency faster */
    RTC_COMP_DOWN       /*!<  compensation direction down,  
                                    seconds frequency  slower */
}RTC_CompDirection_t;

/**
 *  @brief RTC compensation config struct definition
 */
typedef struct
{
    uint8_t delayVal;    /*!<  compensation delay value can be [1:256]
                          how frequently RTC adjust its number of 32.768KHz 
                          in each second*/
    uint8_t compVal;               /*!<  cempensation counter value, 
                                         can be effect till DLY be 0  */
    RTC_CompDirection_t  dir;      /*!< frequency compensation direction */
}RTC_CompConfig_t;

/**
 *  @brief RTC output config struct definition
 */
typedef struct
{
    RTC_SecondIntMuxSel_t freqSel;
    RTC_ClkOut_t    clkOutput;    
}RTC_OutputConfig_t;

/** @} end of group RTC_Public_Types*/


/** @defgroup RTC_Public_FunctionDeclaration
 *  @brief RTC functions statement
 *  @{
 */

/**
 * @brief      RTC enable functioin
 *
 * @param[in]  none
 *
 * @return     none
 */
void RTC_Enable(void);

/**
 * @brief      RTC disable functioin
 *
 * @param[in]  none
 *
 * @return     none
 */
void RTC_Disable(void);

 /**
 * @brief      RTC OSC clock disable functioin
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_OSCDisable(void);

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
 * @brief      config whether write access to RTC in non-supervisor
 *
 * @param[in]  cmd: ENABLE/DISABLE
 *
 * @return none
 *
 */
void RTC_SupModeConfig(ControlState_t cmd);

/**
 * @brief      config second interrupt mux function
 *
 * @param[in]  muxSel: select frequency to generate second frequency
 *
 * @return none
 *
 */
void RTC_FreqMuxConfig(RTC_SecondIntMuxSel_t muxSel);

/**
 * @brief       Config RTC clcok source
 *
 * @param[in]   config:config clock output
 *
 * @return none
 *
 */
void RTC_OutputConfig(RTC_OutputConfig_t const * config);

/**
 * @brief      Enable  RTC output clock function after output config
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void RTC_OutputEnable(void);

/**
 * @brief      Disable  RTC output clock function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void RTC_OutputDisable(void);

/**
 * @brief        Select RTC clock source function, 
 *              suggest select clock source before enable RTC clock
 *
 * @param[in]   clockSource:RTC clock source
 *
 * @return       
 *           -SUCC:clock config is success
 *           -ERR:clock config is fail
 *
 */
ResultStatus_t RTC_ClkConfig(RTC_Clk_t clockSource);

/**
 * @brief       Set match counter register which also can clear alarm interrupt
 *
 * @param[in]   counterValue:set the counter value
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetMatchCounter(uint32_t counterValue);

/**
 * @brief        Get match counter register
 *
 * @param[in]   none
 *
 * @return      match counter
 *
 *****************************************************************************/
uint32_t RTC_GetMatchCounter(void);

/**
 * @brief        Mask/Unmask the RTC interrupt funtion
 *
 * @param[in]     intType: select interrupt
 * @param[in]     intMask:Enable/Disable  interrupt
 *
 * @return       none
 *
 *****************************************************************************/
void RTC_IntMask(RTC_Int_t intType, IntMask_t intMask);

/**
 * @brief        RTC Get alarm match status Function
 *
 * @param[in]    none
 *
 * @return       intstatus
 *
 */
IntStatus_t RTC_GetAlarmMatchStatus(void);

/**
 * @brief       Get  second interrupt status Function
 *
 * @param[in]    none
 *
 * @return       intstatus
 *
 */
IntStatus_t RTC_GetSecondStatus(void);

/**
 * @brief       RTC Get alarm overflow status Function
 *
 * @param[in]    none
 *
 * @return       intstatus
 *
 */
IntStatus_t RTC_GetAlarmOVFStatus(void);

/**
 * @brief        Clear RTC overflow interrupt function after disable RTC
 *
 * @param[in]    countVal: set alarm counter value
 *
 * @return       none
 *
 *****************************************************************************/
void RTC_ClearOVF(uint32_t countVal);

/**
 * @brief        Clear RTC seconds interrupt flag function
 *
 * @param[in]    none
 *
 * @return       none
 *
 *****************************************************************************/
void RTC_ClearSecondsFlag(void);

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
 * @param[in]   delayVal: compensation delay value
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
 * @param[in]   Val: compensation counter value
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
 * @brief       Config the compensation  function
 *
 * @param[in]   config: compensation config
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_CompConfig(RTC_CompConfig_t const *config);

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

/** @} end of group Z20K11X_Peripheral_Driver */

#endif /* __Z20K11XM_RTC_H__ */
