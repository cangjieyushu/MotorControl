/**************************************************************************************************/
/**
 * @file     mcpwm_drv.h
 * @brief    MCPWM driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef MCPWM_DRV_H
#define MCPWM_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  MCPWM
 *  @{
 */

/** @defgroup MCPWM_Public_Types 
 *  @{
 */

/**
 *  @brief MCPWM ID type definition
 */
typedef enum
{
    MCPWM0_ID = 0U,                            /*!< MCPWM0  */
    MCPWM1_ID                                  /*!< MCPWM1  */
} MCPWM_ID_t;

/**
 *  @brief MCPWM Counter ID type definition
 */
typedef enum
{
    MCPWM_COUNTER_0 = 0U,                     /*!< MCPWM Counter 0*/
    MCPWM_COUNTER_1,                          /*!< MCPWM Counter 1*/
    MCPWM_COUNTER_2,                          /*!< MCPWM Counter 2*/
    MCPWM_COUNTER_3                           /*!< MCPWM Counter 3*/
} MCPWM_CounterId_t;

/**
 *  @brief MCPWM Channel ID type definition
 */
typedef enum
{
    MCPWM_CHANNEL_0 = 0U,                      /*!< MCPWM Channel 0*/
    MCPWM_CHANNEL_1,                           /*!< MCPWM Channel 1*/
    MCPWM_CHANNEL_2,                           /*!< MCPWM Channel 2*/
    MCPWM_CHANNEL_3,                           /*!< MCPWM Channel 3*/
    MCPWM_CHANNEL_4,                           /*!< MCPWM Channel 4*/
    MCPWM_CHANNEL_5,                           /*!< MCPWM Channel 5*/
    MCPWM_CHANNEL_6,                           /*!< MCPWM Channel 6*/
    MCPWM_CHANNEL_7                            /*!< MCPWM Channel 7*/
} MCPWM_ChannelId_t;

/**
 *  @brief MCPWM Pair Channel ID type definition
 */
typedef enum
{
    MCPWM_PAIR_CHANNEL_0 = 0U,    /*!< MCPWM pair 0 control channel0 and channel 1*/
    MCPWM_PAIR_CHANNEL_1,         /*!< MCPWM pair 1 control channel2 and channel 3*/
    MCPWM_PAIR_CHANNEL_2,         /*!< MCPWM pair 2 control channel4 and channel 5*/
    MCPWM_PAIR_CHANNEL_3          /*!< MCPWM pair 3 control channel6 and channel 7*/
} MCPWM_PairId_t;

/**
 *  @brief MCPWM Clock Source type definition
 */
typedef enum
{
    MCPWM_CLK_DISABLED        = 0U,     /*!< MCPWM Counter Clock is disabled*/
    MCPWM_CLK_SOURCE_SYSTEM   = 1U,     /*!< System Clock as MCPWM Counter Clock*/
    MCPWM_CLK_SOURCE_FUNCTION = 2U,     /*!< Function Clock as MCPWM Counter Clock*/
    MCPWM_CLK_SOURCE_EXTERNAL = 3U      /*!< External Clock as MCPWM Counter Clock*/
} MCPWM_ClkSource_t;

/**
 *  @brief MCPWM Clock Divide type definition
 */
typedef enum
{
    MCPWM_CLK_DIVIDE_1 = 0U,                  /*!< MCPWM Clock Divide by 1*/
    MCPWM_CLK_DIVIDE_2,                       /*!< MCPWM Clock Divide by 2*/
    MCPWM_CLK_DIVIDE_4,                       /*!< MCPWM Clock Divide by 4*/
    MCPWM_CLK_DIVIDE_8,                       /*!< MCPWM Clock Divide by 8*/
    MCPWM_CLK_DIVIDE_16,                      /*!< MCPWM Clock Divide by 16*/
    MCPWM_CLK_DIVIDE_32,                      /*!< MCPWM Clock Divide by 32*/
    MCPWM_CLK_DIVIDE_64,                      /*!< MCPWM Clock Divide by 64*/
    MCPWM_CLK_DIVIDE_128                      /*!< MCPWM Clock Divide by 128*/
} MCPWM_ClkDivide_t;

/**
 *  @brief MCPWM Counter Counting Mode type definition
 */
typedef enum
{
    MCPWM_COUNTING_UP = 0U,                    /*!< MCPWM Up Counting Mode*/
    MCPWM_COUNTING_UP_DOWN                     /*!< MCPWM Up-Down Counting Mode*/
} MCPWM_CountingMode_t;

/**
 *  @brief MCPWM Pulse Polarity type definition
 */
typedef enum
{
    MCPWM_LOW_PULSE_POL = 0U,         /*!< MCPWM channel output is low pulse polarity*/
    MCPWM_HIGH_PULSE_POL              /*!< MCPWM channel output is high pulse polarity*/
} MCPWM_PulsePolarity_t;

/**
 *  @brief MCPWM Polarity type definition
 */
typedef enum
{
    MCPWM_POL_LOW = 0U,                /*!< MCPWM channel output polarity:
                                          Logic 0 is inactive state;
                                          Logic 1 is active state;*/
    MCPWM_POL_HIGH                     /*!< MCPWM channel output polarity:
                                          Logic 0 is active state;
                                          Logic 1 is inactive state;*/
} MCPWM_Polarity_t;

/**
 *  @brief MCPWM pulse edge control for pairs of channel type definition
 */
typedef enum
{
    MCPWM_MAIN_CV = 0U,      /*!< in complementary mode, CV(n) is used to generate channel(n) PWM output;
                                   channel(n+1) output is complementary with channel(n) */
    MCPWM_SECOND_CV,          /*!< in complementary mode, CV(n+1) is used to generate channel(n) PWM output
                                   channel(n+1) output is complementary with channel(n) */
    MCPWM_BOTH_CV             /*!< in complementary mode, CV(n) is used to set
                                   channel(n) PWM output and CV(n+1) is used to clear channel(n) PWM output;
                                   channel(n+1) output is complementary with channel(n)*/
} MCPWM_PulseEdgeCtrl_t;

/**
 *  @brief MCPWM asymmetric PWM output enable for pairs of channel type definition
 */
typedef enum
{
    MCPWM_SYMMETRIC = 0U,  /*!< channel(n) and channel(n+1) are symmetric PWM output in complementary CPWM mode*/
    MCPWM_ASYMMETRIC       /*!< channel(n) and channel(n+1) are asymmetric PWM output in complementary CPWM mode*/
} MCPWM_Asym_t;

/**
 *  @brief MCPWM fault input ID type define
 */
typedef enum
{
    MCPWM_FAULT_CHANNEL_0 = 0U,         /*!< MCPWM fault input 0*/
    MCPWM_FAULT_CHANNEL_1,              /*!< MCPWM fault input 1*/
    MCPWM_FAULT_CHANNEL_2,              /*!< MCPWM fault input 2*/
    MCPWM_FAULT_CHANNEL_3               /*!< MCPWM fault input 3*/
} MCPWM_FaultChannelId_t;

/**
 *  @brief MCPWM Fault Safe Output Status type definition
 */
typedef enum
{
    MCPWM_INACTIVE_STATE = 0U,/*!< fault event is on-going, MCPWM output will be inactive state,
                                   depend on selected channel safe status value for faultA/B*/
    MCPWM_TRI_STATE           /*!< fault event is on-going, MCPWM output will be tri-stated*/
} MCPWM_FaultSafeState_t;

/**
 *  @brief MCPWM Fault Clear Mode type definition
 */
typedef enum
{
    MCPWM_Fault_MANUAL_CLEAR = 0U,/*!< manual fault clear mode*/
    MCPWM_Fault_AUTO_CLEAR        /*!< automatical fault clear mode*/
} MCPWM_FaultClearMode_t;

/**
 *  @brief MCPWM CNTINT OUTSWCR register update Mode type definition
 */
typedef enum
{
    MCPWM_UPDATE_SYSTEM_CLK = 0U,     /*!< update on all rising edge of the system clock*/
    MCPWM_UPDATE_PWM_SYN              /*!< update only by PWM synchronization*/
} MCPWM_RegUpdateMode_t;

/**
 *  @brief MCPWM Interrupt type definition
 */
typedef enum
{
    MCPWM_INT_CH0 = 0U,                /*!< channel 0 INT*/
    MCPWM_INT_CH1,                     /*!< channel 1 INT*/
    MCPWM_INT_CH2,                     /*!< channel 2 INT*/
    MCPWM_INT_CH3,                     /*!< channel 3 INT*/
    MCPWM_INT_CH4,                     /*!< channel 4 INT*/
    MCPWM_INT_CH5,                     /*!< channel 5 INT*/
    MCPWM_INT_CH6,                     /*!< channel 6 INT*/
    MCPWM_INT_CH7,                     /*!< channel 7 INT*/
    MCPWM_INT_RLD0,                    /*!< reload0 INT*/
    MCPWM_INT_RLD1,                    /*!< reload1 INT*/
    MCPWM_INT_RLD2,                    /*!< reload2 INT*/
    MCPWM_INT_RLD3,                    /*!< reload3 INT*/
    MCPWM_INT_TO0,                     /*!< counter0 overflow INT*/
    MCPWM_INT_TO1,                     /*!< counter1 overflow INT*/
    MCPWM_INT_TO2,                     /*!< counter2 overflow INT*/
    MCPWM_INT_TO3,                     /*!< counter3 overflow INT*/
    MCPWM_INT_FAULT,                   /*!< fault INT*/
    MCPWM_INT_ALL                      /*!< all INT*/
} MCPWM_INT_t;


/**
 *  @brief MCPWM software control output config struct definition
 */
typedef struct
{
    ControlState_t outputSWCtrlEnable;  /*!< SW control output cmd: enable/disable*/
    Level_t outputSWCtrlVal;            /*!< SW control output value*/
} MCPWM_OutputSWCtrlConfig_t;

/**
 *  @brief MCPWM fault control channel config struct definition
 */
typedef struct
{
    MCPWM_FaultChannelId_t inputChannel;    /*!< input channel id */
    ControlState_t faultInputChannelEnable;  /*!< fault input enable for each fault channel */
    ControlState_t faultInputFilterEnable;   /*!< fault input filter enable for each fault channel */
    MCPWM_Polarity_t faultInputPolarity;     /*!< fault input polarity for each fault channel */
} MCPWM_FaultChannelConfig_t;

/**
 *  @brief MCPWM fault control config struct definition
 */
typedef struct
{
    uint8_t numFaultInputChannels;         /*!< fault input channel number */
    uint8_t faultFilterValue;              /*!< fault filter value */
    MCPWM_FaultSafeState_t status;         /*!< fault safe output status type */
    MCPWM_FaultClearMode_t faultClearMode; /*!< fault clear mode type */
    MCPWM_FaultChannelConfig_t* faultChannelConfig;
                                           /*!< fault config for all fault channel*/
} MCPWM_PwmFaultCtrlConfig_t;

/**
 *  @brief MCPWM independent PWM output channel config struct definition
 */
typedef struct
{
    MCPWM_ChannelId_t channelId;           /*!< channel id */
    ControlState_t channelOutputEnable;    /*!< channel output enable/disable*/
    MCPWM_Polarity_t polarity;             /*!< channel output polarity: MCPWM_POL_HIGH; MCPWM_POL_LOW*/
    MCPWM_PulsePolarity_t pulsePol;       /*!< channel Pulse polarity*/
    uint16_t compareValue;                 /*!< compare value*/
    Level_t channelOffVal;                 /*!< channel output value when counter is off*/
    ControlState_t channelMatchTrigEnable; /*!< channel match trigger enable/disable*/
    ControlState_t faultCtrlEnable;        /*!< channel fault control enable/disable*/
    ControlState_t CVUpdateEnable;         /*!< enable/disable synchronization of CV(n)*/
    Level_t safeStatusForFaultA;           /*!< channel safe status value for fault A*/
    Level_t safeStatusForFaultB;           /*!< channel safe status value for fault B*/
} MCPWM_PwmChannelConfig_t;

/**
 *  @brief MCPWM PWM output global config struct definition
 */
typedef struct
{

    uint16_t countModVal;                /*!< mod(max) counter value */
    MCPWM_CountingMode_t countMode;          /*!< counting mode: MCPWM_COUNTING_UP;
                                                               MCPWM_COUNTING_UP_DOWN*/
    MCPWM_PwmChannelConfig_t * MainPwmChConfig;  /*!< independent pwm config for main channel */
    MCPWM_PwmChannelConfig_t * SecondPwmChConfig;/*!< independent pwm config for second channel */
} MCPWM_PwmConfig_t;

/**
 *  @brief MCPWM complementary PWM output channel config struct definition
 */
typedef struct
{
    MCPWM_PairId_t pairId;                      /*!< pair id */
    uint16_t deadTimeVal;                       /*!< deadtime value*/
    MCPWM_PulseEdgeCtrl_t pec;                  /*!< pulse edge control for pairs */
    MCPWM_Asym_t asym;                          /*!< asymmetric PWM output enable for pairs */
    ControlState_t mainChannelOutputEnable;     /*!< main channel output enable/disable for pair*/
    ControlState_t secondChannelOutputEnable;   /*!< second channel output enable/disable for pair*/
    MCPWM_Polarity_t polarity;                  /*!< polarity: MCPWM_POL_HIGH; MCPWM_POL_LOW*/
    MCPWM_PulsePolarity_t pulsePol;            /*!< channel Pulse polarity*/
    uint16_t mainCompareValue;                  /*!< main channel compare value*/
    uint16_t secondCompareValue;                /*!< second channel compare value*/
    Level_t mainChannelOffVal;                  /*!< main channel output value when counter is off*/
    Level_t secondChannelOffVal;                /*!< second channel output value when counter is off*/
    ControlState_t mainChannelMatchTrigEnable;  /*!< main channel match trigger enable/disable*/
    ControlState_t secondChannelMatchTrigEnable;/*!< second channel match trigger enable/disable*/
    ControlState_t deadTimeEnable;              /*!< deadtime function enable/disable for each pair*/
    ControlState_t faultCtrlEnable;      /*!< fault ctrl function enable/disable for each pair*/
    ControlState_t CVUpdateEnable;                /*!<  enable/disable the synchronization of CV(n) and CV(n+1) for pair*/
    Level_t mainSafeStatusForFaultA;            /*!< main channel(n) safe status value for fault A*/
    Level_t secondSafeStatusForFaultA;          /*!< second channel(n+1) safe status value for fault A*/
    Level_t mainSafeStatusForFaultB;            /*!< main channel(n) safe status value for fault B*/
    Level_t secondSafeStatusForFaultB;          /*!< second channel(n+1) safe status value for fault B*/
} MCPWM_CompPwmChannelConfig_t;

/**
 *  @brief MCPWM complementary PWM output global config struct definition
 */
typedef struct
{
    uint16_t countModVal;                     /*!< mod(max) Counter val*/
    MCPWM_CountingMode_t countMode;               /*!< counting mode: MCPWM_COUNTING_UP;
                                                               MCPWM_COUNTING_UP_DOWN*/
    MCPWM_CompPwmChannelConfig_t * cPwmChConfig;/*!< complementary pwm config for each channel*/
} MCPWM_CompPwmConfig_t;

/**
 *  @brief MCPWM reload config struct definition
 */
typedef struct
{
    ControlState_t halfCycleEnable;      /*!< for CPWM output, half cycle reload enable/disable*/ 
    ControlState_t fullCycleEnable;      /*!< for CPWM output, full cycle reload enable/disable*/ 
    uint8_t loadFrequency;               /*!< load frequency*/
} MCPWM_ReloadConfig_t;

/** @} end of group MCPWM_Public_Types definitions */

/** @defgroup MCPWM_Public_Constants
 *  @{
 */ 


/** @} end of group MCPWM_Public_Constants */

/** @defgroup MCPWM_Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief       MCPWM WriteProtection Enable Function
 *
 * @param[in]  mcpwmId:        Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 *
 * @return none
 *
 */
void MCPWM_WriteProtectionEnable(MCPWM_ID_t mcpwmId);

/**
 * @brief       MCPWM WriteProtection Disable Function
 *
 * @param[in]  mcpwmId:        Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 *
 * @return none
 *
 */
void MCPWM_WriteProtectionDisable(MCPWM_ID_t mcpwmId);

/**
 * @brief       MCPWM Start counter with clock configuration
 *
 * @param[in]  mcpwmId:      Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  clkSource:    Select MCPWM clock source:
 *                                  - MCPWM_CLK_SOURCE_SYSTEM
                                    - MCPWM_CLK_SOURCE_FUNCTION
 *                                  - MCPWM_CLK_SOURCE_EXTERNAL
 * @param[in]  divider:      Select MCPWM clock divider.
 *
 * @return none
 *
 */
void MCPWM_ClockSourceConfig(MCPWM_ID_t mcpwmId, MCPWM_ClkSource_t clkSource, 
                     MCPWM_ClkDivide_t divider);

/**
 * @brief       MCPWM Start counter
 *
 * @param[in]  mcpwmId:        Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  counterId:      Selected Counter ID.
 *
 * @return none
 *
 */
void MCPWM_StartCounter(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId);

/**
 * @brief       MCPWM Stop counter
 *
 * @param[in]  mcpwmId:        Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  counterId:      Selected Counter ID.
 *
 * @return none
 *
 */
void MCPWM_StopCounter(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId);

/**
 * @brief       MCPWM Start Globale counter
 *
 * @param[in]  mcpwmId:        Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 *
 * @return none
 *
 */
void MCPWM_StartGlobalCounter(MCPWM_ID_t mcpwmId);

/**
 * @brief       MCPWM Stop Global counter
 *
 * @param[in]  mcpwmId:        Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 *
 * @return none
 *
 */
void MCPWM_StopGlobalCounter(MCPWM_ID_t mcpwmId);

/**
 * @brief       MCPWM Set Counter Counting Mode Function
 *
 * @param[in]  mcpwmId:        Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  counterId:      Selected Counter ID.
 * @param[in]  countingMode:   Counter Counting Mode.
 *
 * @return none
 *
 */
void MCPWM_SetCountingMode(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId,
                                MCPWM_CountingMode_t countingMode);

/**
 * @brief       MCPWM Get Counter Value Function
 *
 * @param[in]  mcpwmId:        Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  counterId:      Selected Counter ID.
 *
 * @return Counter Init Value
 *
 */
uint16_t MCPWM_GetCounterVal(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId);

/**
 * @brief       MCPWM Set Counter Mod(Max) Value Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  counterId:  Selected Counter ID.
 * @param[in]  modVal:     Counter MOD value.
 *
 * @return none
 *
 */
void MCPWM_SetCounterModVal(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId, uint16_t modVal);

/**
 * @brief       MCPWM Get Counter MOD Value Function
 *
 * @param[in]  mcpwmId:        Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  counterId:      Selected Counter ID.
 *
 * @return Counter MOD Value
 *
 */
uint16_t MCPWM_GetCounterModVal(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId);

/**
 * @brief       MCPWM Load Counter Init Value Function
 *
 * @param[in]  mcpwmId:        Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  counterId:      Selected Counter ID.
 *
 * @return none
 *
 */
void MCPWM_ResetCounter(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId);

/**
 * @brief       MCPWM Set deadtime Value Function
 *
 * @param[in]  mcpwmId:     Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  pairId:      Select the MCPWM pair ID.
 * @param[in]  deadtimeVal: Deadtime value, max value is 0xFFF.
 *
 * @return none
 *
 */
void MCPWM_SetDeadtimeVal(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, uint16_t deadtimeVal);

/**
 * @brief       MCPWM Get deadtime Value Function
 *
 * @param[in]  mcpwmId:     Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  pairId:      Select the MCPWM pair ID.
 *
 * @return Deadtime Value
 *
 */
uint16_t MCPWM_GetDeadtimeVal(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId);

/**
 * @brief       MCPWM Set MOD Dither  Function
 *
 * @param[in]  mcpwmId:      Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  counterId:    Selected Counter ID.
 * @param[in]  modDitherVal: Mod dither value, max value is 0x1F.
 *
 * @return none
 *
 */
void MCPWM_SetModDither(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId, uint8_t modDither);

/**
 * @brief       MCPWM enable channel output Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:  Select Channel Id.
 *
 * @return none
 *
 */
void MCPWM_ChannelOutputEnable(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId);

/**
 * @brief       MCPWM disable channel output Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:  Select Channel Id.
 *
 * @return none
 *
 */
void MCPWM_ChannelOutputDisable(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId);

/**
 * @brief       MCPWM DMA function enable/disable for selected channel
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  channelId:  Select Channel Id.
 * @param[in]  cmd:        Enable/disable.
 *
 * @return none
 *
 */
void MCPWM_DMACmd(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId,
                                ControlState_t cmd);

/**
 * @brief       MCPWM set channel pulse polarity for selected channel
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:  Select Channel Id.
 * @param[in]  cpp:        Select pulse polarity.
 *
 * @return none
 *
 */
void MCPWM_SetChannelPulsePol(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId,
                                MCPWM_PulsePolarity_t cpp);

/**
 * @brief       MCPWM Set  Compare Value Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:  Select channel ID.
 * @param[in]  cVal:    Compare Value.
 *
 * @return none
 *
 */
void MCPWM_SetChannelCVal(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId, uint16_t cVal);

/**
 * @brief       MCPWM Get Compare Value Function
 *
 * @param[in]   mcpwmId:      Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]   channelId:    Select channel ID.
 *
 * @return Compare Value
 *
 */
uint16_t MCPWM_GetChannelCVal(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId);

/**
 * @brief       MCPWM Set  CVal Dither Value Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:  Select channel ID.
 * @param[in]  cvDither:   Compare Value Dither, max value is 0x1F.
 *
 * @return none
 *
 */
void MCPWM_SetChannelCVDither(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId, uint8_t cvDither);

/**
 * @brief       MCPWM Set  channel output value when counter is off
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:  Select channel ID.
 * @param[in]  level:      Low_level/high_level for channel output.
 *
 * @return none
 *
 */
void MCPWM_SetChannelOffValue(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId,
                              Level_t level);

/**
 * @brief       MCPWM set channel output polarity for selected channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId: Select Channel Id.
 * @param[in]  pol:       Output polarity.
 *
 * @return none
 *
 */
void MCPWM_SetChannelPolarity(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId,
                                MCPWM_Polarity_t pol);

/**
 * @brief       MCPWM Set channel match trigger cmd enable/disable Function
 *
 * @param[in]  mcpwmId:      Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:    Select channel id .
 * @param[in]  cmd:          Enable/disable.
 *
 * @return none
 *
 */
void MCPWM_ChannelMatchTriggerCmd(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId, 
                                ControlState_t cmd);

/**
 * @brief       MCPWM Set init trigger cmd enable/disable Function
 *
 * @param[in]  mcpwmId:        Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  cmd:            Enable/disable.
 *
 * @return none
 *
 */
void MCPWM_InitTriggerCmd(MCPWM_ID_t mcpwmId, ControlState_t cmd);

/**
 * @brief       MCPWM Set  channel output software control value
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:  Select channel ID.
 * @param[in]  level:      Low_level/high_level for channel output.
 *
 * @Note: Donot Call this function more than one time before PWM synchronization
 * event occur When SYNCOSWC = MCPWM_UPDATE_PWM_SYN.
 *
 * @return none
 *
 */
void MCPWM_SetChannelOCV(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId,
                              Level_t level);

/**
 * @brief       MCPWM Set channel output software control enable/disable Function
 *
 * @param[in]  mcpwmId:      Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:    Select channel id .
 * @param[in]  cmd:          Enable/disable.
 *
 * @Note: Donot Call this function more than one time before PWM synchronization
 * event occur When SYNCOSWC = MCPWM_UPDATE_PWM_SYN.
 *
 * @return none
 *
 */
void MCPWM_ChannelOCCmd(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId, 
                                ControlState_t cmd);

/**
 * @brief       MCPWM Config  output software control for All channels 
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Config:     Config values.
 *
 * @return none
 *
 */
void MCPWM_ConfigAllOutputSoftwareControl(MCPWM_ID_t mcpwmId, uint16_t Config);

/**
 * @brief       MCPWM Set combine enable/disable for pairs of channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  pairId:    Select pair id .
 * @param[in]  cmd:       Enable/disable.
 *
 * @return none
 *
 */
void MCPWM_PairCombineCmd(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, 
                                ControlState_t cmd);

/**
 * @brief       MCPWM Set pulse edge control for pairs of channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  pairId:    Select pair id .
 * @param[in]  pec:       Pulse Edge Ctrl.
 *
 * @return none
 *
 */
void MCPWM_SetPairPulseEdgeCtrl(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, 
                                MCPWM_PulseEdgeCtrl_t pec);

/**
 * @brief       MCPWM Set asymmetric PWM output enable for pairs of channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  pairId:    Select pair id .
 * @param[in]  asym:      Symmetric/asymmetric.
 *
 * @return none
 *
 */
void MCPWM_PairAsymmetricCmd(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, 
                                MCPWM_Asym_t asym);

/**
 * @brief       MCPWM Set Synchronization enable/disable for pairs of channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  pairId:    Select pair id .
 * @param[in]  cmd:       Enable/disable.
 *
 * @return none
 *
 */
void MCPWM_PairSynchronizationCmd(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, 
                                ControlState_t cmd);

/**
 * @brief       MCPWM Set deadtime insertion enable/disable for pairs of channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  pairId:    Select pair id .
 * @param[in]  cmd:       Enable/disable.
 *
 * @return none
 *
 */
void MCPWM_PairDeadtimeCmd(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, 
                                ControlState_t cmd);

/**
 * @brief       MCPWM Set fault control enable/disable for pairs of channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  pairId:    Select pair id .
 * @param[in]  cmd:       Enable/disable.
 *
 * @return none
 *
 */
void MCPWM_PairFaultCtrlCmd(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, 
                                ControlState_t cmd);


/**
 * @brief       MCPWM Set fault input filter value
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  filterVal: Fault input filter value(max value is 0xF, 0 is disabled).
 *
 * @return none
 *
 */
void MCPWM_SetFaultFilterVal(MCPWM_ID_t mcpwmId, uint8_t filterVal);

/**
 * @brief       MCPWM set fault input filter enable/disable for selected input channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  inputId:   Select fault input channel Id.
 * @param[in]  cmd:       Fault input enable/disable.
 *
 * @return none
 *
 */
void MCPWM_FaultFilterCmd(MCPWM_ID_t mcpwmId, MCPWM_FaultChannelId_t inputId,
                                ControlState_t cmd);

/**
 * @brief       MCPWM Set fault output state
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  state:     Inactive state / tri-state, if inactive state, 
 *                        the safe state is decided by FLTASS and FLTBSS.
 *
 * @return none
 *
 */
void MCPWM_SetFaultOutputState(MCPWM_ID_t mcpwmId, MCPWM_FaultSafeState_t state);

/**
 * @brief       MCPWM Set fault clear mode
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  mode:      Fault clear mode.
 *
 * @return none
 *
 */
void MCPWM_SetFaultClearMode(MCPWM_ID_t mcpwmId, MCPWM_FaultClearMode_t mode);

/**
 * @brief       MCPWM set fault input channel polarity for selected input channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  inputId:   Select fault input channel Id.
 * @param[in]  pol:       Fault input channel polarity.
 *
 * @return none
 *
 */
void MCPWM_SetFaultInputPolarity(MCPWM_ID_t mcpwmId, MCPWM_FaultChannelId_t inputId,
                                MCPWM_Polarity_t pol);

/**
 * @brief       MCPWM set fault input enable/disable for selected input channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  inputId:   Select fault input channel Id.
 * @param[in]  cmd:       Fault input enable/disable.
 *
 * @return none
 *
 */
void MCPWM_FaultInputCmd(MCPWM_ID_t mcpwmId, MCPWM_FaultChannelId_t inputId,
                                ControlState_t cmd);

/**
 * @brief       MCPWM set selected channel safe status value for fault Group A(fault 
                input 0 and fault input 1).
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId: Select channel Id.
 * @param[in]  level:     Safe status level: low level/high leval.
 *
 * @return none
 *
 */
void MCPWM_SetChannelSafeStatusValForFaultA(MCPWM_ID_t mcpwmId, 
                                            MCPWM_ChannelId_t channelId,
                                            Level_t level);

/**
 * @brief       MCPWM set selected channel safe status value for fault Group B(fault 
                input 2 and fault input 3).
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  channelId: Select channel Id.
 * @param[in]  level:     Safe status level: low level/high leval.
 *
 * @return none
 *
 */
void MCPWM_SetChannelSafeStatusValForFaultB(MCPWM_ID_t mcpwmId,    /* PRQA S 0777,0779*/
                                            MCPWM_ChannelId_t channelId,
                                            Level_t level);

/**
 * @brief       MCPWM output software control config Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  channelId:  Select Channel Id.
 * @param[in]  config:     Software Control Config.
 *
 * @Note: This  function cannot be used when SYNCOSWC = MCPWM_UPDATE_PWM_SYN:
 * OUTSWCR register is updated with its buffer value only by PWM synchronization
 *
 * @return none
 *
 */
void MCPWM_OutputSWCtrlConfig(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId, 
                            const MCPWM_OutputSWCtrlConfig_t* config);

/**
 * @brief       MCPWM get match trigger flag Function:when any channel match trigger
 *              is generated, this flag is set by hardware.
 *
 * @param[in]  mcpwmId:      Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 *
 * @return     FlagStatus_t: 0: No channel match trigger is generated. 
 *                           1: At least one channel match trigger is generated.
 *
 */
FlagStatus_t MCPWM_GetMatchTriggerFlag(MCPWM_ID_t mcpwmId);

/**
 * @brief       MCPWM independent PWM channel config Function
 *
 * @param[in]  mcpwmId:         Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  channelConfig:   Independent PWM Output Channel Config.
 *
 * @return none
 *
 */
void MCPWM_IndependentPwmChannelConfig(MCPWM_ID_t mcpwmId, const MCPWM_PwmChannelConfig_t * channelConfig);

/**
 * @brief       MCPWM initialise independent PWM output config Function
 *
 * @param[in]  mcpwmId:    Selected the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  counterId:  Selected Counter ID.
 * @param[in]  config:     Independent PWM Output Config.
 *
 * @return none
 *
 */
void MCPWM_OutputIndependentPwmConfig(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId,
                                      const MCPWM_PwmConfig_t * config);

/**
 * @brief       MCPWM Complementary PWM channel config Function
 *
 * @param[in]  mcpwmId:         Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  channelConfig:   Complementary PWM Output Channel Config.
 *
 * @return none
 *
 */
void MCPWM_ComplementaryPwmChannelConfig(MCPWM_ID_t mcpwmId, 
                                         const MCPWM_CompPwmChannelConfig_t * channelConfig);

/**
 * @brief       MCPWM initialise complementary PWM output config Function
 *
 * @param[in]  mcpwmId:    Selected the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  counterId:  Selected Counter ID.
 * @param[in]  config:     Complementary PWM Output Config.
 *
 * @return none
 *
 */
void MCPWM_OutputComplementaryPwmConfig(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId,
                                        const MCPWM_CompPwmConfig_t * config);

/**
 * @brief   MCPWM initialise fault control config Function, which used in pwm mode
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  config:     Fault Control Config.
 *
 * @return none
 *
 */
void MCPWM_FaultControlConfig(MCPWM_ID_t mcpwmId, const MCPWM_PwmFaultCtrlConfig_t * config);

/**
 * @brief       MCPWM enable/disable that Software Trigger activate CNT regsister sync
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void MCPWM_SWTrigCNTSyncCmd(MCPWM_ID_t mcpwmId, ControlState_t cmd);

/**
 * @brief       MCPWM enable/disable that Software Trigger activate wirte buffer regsister sync
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void MCPWM_SWTrigWRBUFSyncCmd(MCPWM_ID_t mcpwmId, ControlState_t cmd);

/**
 * @brief       MCPWM PWM synchronization software trigger Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 *
 * @return none
 *
 */
void MCPWM_SyncSoftwareTrigger(MCPWM_ID_t mcpwmId);

/**
 * @brief       MCPWM Output Software Control Register update mode select Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  updateMode: Update mode. 0: update on all rising edge of the system clock
 *                                       1: update only by PWM synchronization
 *
 * @return none
 *
 */
void MCPWM_OSWCUpdateModeSelect(MCPWM_ID_t mcpwmId, MCPWM_RegUpdateMode_t updateMode);

/**
 * @brief       MCPWM CPWM half cycle reload enable/disable Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  counterId:  Select counter id for CPWM.
 * @param[in]  cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void MCPWM_CPWMHalfCycleReloadCmd(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId, ControlState_t cmd);

/**
 * @brief       MCPWM CPWM full cycle reload enable/disable Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  counterId:  Select counter id for CPWM.
 * @param[in]  cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void MCPWM_CPWMFullCycleReloadCmd(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId, ControlState_t cmd);

/**
 * @brief       MCPWM Set reload frequency Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  counterId:  Select counter id for CPWM.
 * @param[in]  freq:       Reload frequency, max is 0x1F.
 *
 * @return none
 *
 */
void MCPWM_SetReloadFreq(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId, uint8_t freq);

/**
 * @brief       MCPWM Config Reload Param for selected pair of channels Function
 *
 * @param[in]  mcpwmId:      Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  counterId:    Select counter id .
 * @param[in]  reloadConfig: Pointer to reload param config struct.
 *
 * @return none
 *
 */
void MCPWM_ReloadParamConfig(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId, 
                             const MCPWM_ReloadConfig_t* reloadConfig);

/**
 * @brief       MCPWM Reload Sync Config Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  pairId:     Select pair id for CPWM.
 * @param[in]  cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void MCPWM_ReloadEnable(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, ControlState_t cmd);

/**
 * @brief       MCPWM INT mask/unmask Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  intType:    Select interrupt type.
 * @param[in]  intMask:    Mask/unmask .
 *
 * @return none
 *
 */
void MCPWM_IntMask(MCPWM_ID_t mcpwmId, MCPWM_INT_t intType, IntMask_t intMask);

/**
 * @brief       MCPWM INT status clear Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  intType:    Select interrupt type.
 *
 * @return none
 *
 */
void MCPWM_IntClear(MCPWM_ID_t mcpwmId, MCPWM_INT_t intType);

/**
 * @brief       MCPWM Get INT status Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  intType:    Select interrupt type.
 *
 * @return intstatus
 *
 */
IntStatus_t MCPWM_GetIntStatus(MCPWM_ID_t mcpwmId, MCPWM_INT_t intType);

/**
 * @brief       MCPWM Get Fault detection flag status of fault channel  Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  channelId:  Select fault input channel:TIM_FAULT_CHANNEL_0,.. .
 *
 * @return     IntStatus_t
 *
 */
IntStatus_t MCPWM_GetFaultStatus(MCPWM_ID_t mcpwmId, MCPWM_FaultChannelId_t inputId);

/**
 * @brief       MCPWM fault status clear Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  intType:    Select interrupt type.
 *
 * @return none
 *
 */
void MCPWM_FaultStatusClear(MCPWM_ID_t mcpwmId, MCPWM_FaultChannelId_t inputId);

/**
 * @brief       MCPWM any channel match trigger flag clear Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 *
 * @return none
 *
 */
void MCPWM_MatchTriggerFlagClear(MCPWM_ID_t mcpwmId);

/**
 * @brief       MCPWM install interrupt callback function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  intType:    Select interrupt type.
 * @param[in]  cbFun:      Callback function .
 *
 * @return none
 *
 */
void MCPWM_InstallCallBackFunc(MCPWM_ID_t mcpwmId, MCPWM_INT_t intType, isr_cb_t * cbFun);

/** @} end of group MCPWM_Public_FunctionDeclaration */

/** @} end of group MCPWM */

/** @} end of group Z20K14XM_Peripheral_Driver */
#endif /* MCPWM_DRV_H */
