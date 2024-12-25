/**************************************************************************************************/
/**
 * @file     tim_drv.h
 * @brief    TIM driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef TIM_DRV_H
#define TIM_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  TIM
 *  @{
 */

/** @defgroup TIM_Public_Types 
 *  @{
 */

/**
 *  @brief TIM ID type definition
 */
typedef enum
{
    TIM0_ID = 0U,                            /*!< TIM0  */
    TIM1_ID,                                 /*!< TIM1  */
    TIM2_ID,                                 /*!< TIM2  */
    TIM3_ID                                  /*!< TIM3  */
} TIM_ID_t;

/**
 *  @brief TIM Channel ID type definition
 */
typedef enum
{
    TIM_CHANNEL_0 = 0U,                      /*!< TIM Channel 0*/
    TIM_CHANNEL_1,                           /*!< TIM Channel 1*/
    TIM_CHANNEL_2,                           /*!< TIM Channel 2*/
    TIM_CHANNEL_3,                           /*!< TIM Channel 3*/
    TIM_CHANNEL_4,                           /*!< TIM Channel 4*/
    TIM_CHANNEL_5,                           /*!< TIM Channel 5*/
    TIM_CHANNEL_6,                           /*!< TIM Channel 6*/
    TIM_CHANNEL_7                            /*!< TIM Channel 7*/
} TIM_ChannelId_t;

/**
 *  @brief TIM Pair Channel ID type definition
 */
typedef enum
{
    TIM_PAIR_CHANNEL_0 = 0U,    /*!< TIM pair 0 control channel0 and channel 1*/
    TIM_PAIR_CHANNEL_1,         /*!< TIM pair 1 control channel2 and channel 3*/
    TIM_PAIR_CHANNEL_2,         /*!< TIM pair 2 control channel4 and channel 5*/
    TIM_PAIR_CHANNEL_3          /*!< TIM pair 3 control channel6 and channel 7*/
} TIM_PairId_t;

/**
 *  @brief TIM Clock Source type definition
 */
typedef enum
{
    TIM_CLK_SOURCE_SYSTEM   = 1U,     /*!< System Clock as TIM Counter Clock*/
    TIM_CLK_SOURCE_FUNCTION = 2U,     /*!< Function Clock as TIM Counter Clock*/
    TIM_CLK_SOURCE_EXTERNAL = 3U      /*!< External Clock as TIM Counter Clock*/
} TIM_ClkSource_t;

/**
 *  @brief TIM Clock Divide type definition
 */
typedef enum
{
    TIM_CLK_DIVIDE_1 = 0U,                  /*!< TIM Clock Divide by 1*/
    TIM_CLK_DIVIDE_2,                       /*!< TIM Clock Divide by 2*/
    TIM_CLK_DIVIDE_4,                       /*!< TIM Clock Divide by 4*/
    TIM_CLK_DIVIDE_8,                       /*!< TIM Clock Divide by 8*/
    TIM_CLK_DIVIDE_16,                      /*!< TIM Clock Divide by 16*/
    TIM_CLK_DIVIDE_32,                      /*!< TIM Clock Divide by 32*/
    TIM_CLK_DIVIDE_64,                      /*!< TIM Clock Divide by 64*/
    TIM_CLK_DIVIDE_128                      /*!< TIM Clock Divide by 128*/
} TIM_ClkDivide_t;

/**
 *  @brief TIM Counter Counting Mode type definition
 */
typedef enum
{
    TIM_COUNTING_UP = 0U,                    /*!< TIM Up Counting Mode*/
    TIM_COUNTING_UP_DOWN                     /*!< TIM Up-Down Counting Mode*/
} TIM_CountingMode_t;

/**
 *  @brief TIM Channel Work Mode type definition
 */
typedef enum
{
    TIM_MODE_NONE = 0U,                         /*!< TIM channel mode: disabled*/
    TIM_MODE_INPUT_CAPTURE,                     /*!< TIM channel mode: input capture */
    TIM_MODE_DUAL_EDGE_CAPTURE,                 /*!< TIM channel mode: dual edge capture*/
    TIM_MODE_OUTPUT_COMPARE,                    /*!< TIM channel mode: output compare */
    TIM_MODE_EGDE_ALIGNED_PWM,                  /*!< TIM channel mode: edge-aligned pwm */
    TIM_MODE_CENTER_ALIGNED_PWM,                /*!< TIM channel mode: center-aligned pwm */
    TIM_MODE_COMPLEMENTARY_PWM                  /*!< TIM channel mode: complementary pwm */
} TIM_ChannelWorkMode_t;

/**
 *  @brief TIM Edge-Alignment Mode type definition
 */
typedef enum
{
    TIM_INPUT_DISABLED = 0U,                    /*!< TIM input capture disabled*/
    TIM_INPUT_EDGE_RISING,                      /*!< TIM input capture only on rising edge*/
    TIM_INPUT_EDGE_FAILING,                     /*!< TIM input capture only on failing edge*/
    TIM_INPUT_EDGE_BOTH                         /*!< TIM input capture both on rising and failing edge*/
} TIM_EdgeAlignmentMode_t;

/**
 *  @brief TIM Output Mode type definition
 */
typedef enum
{
    TIM_OUTPUT_NO_CHANGE = 0U,                 /*!< TIM output no change on match*/
    TIM_OUTPUT_TOGGLE,                         /*!< TIM output toggle on match*/
    TIM_OUTPUT_INACTIVE_STATE,                 /*!< TIM output inactive state on match*/
    TIM_OUTPUT_ACTIVE_STATE                    /*!< TIM output active state on match*/
} TIM_OutputMode_t;

/**
 *  @brief TIM PWM mode type definition
 */
typedef enum
{
    TIM_PWM_DISABLED = 0U,                     /*!< TIM pwm: disabled*/
    TIM_PWM_LOW_TRUE_PULSE,                    /*!< TIM pwm: force output to active state on match*/
    TIM_PWM_HIGH_TRUE_PULSE                    /*!< TIM pwm: force output to inactive state on match*/
} TIM_PwmMode_t;

/**
 *  @brief TIM Polarity type definition
 */
typedef enum
{
    TIM_POL_HIGH = 0U,                /*!< TIM channel output polarity is high:
                                          Logic 0 is inactive state;
                                          Logic 1 is active state;            */
    TIM_POL_LOW                       /*!< TIM channel output polarity is low:
                                          Logic 1 is inactive state;
                                          Logic 0 is active state;            */
} TIM_Polarity_t;

/**
 *  @brief TIM Dual Edge Capture Mode type definition
 */
typedef enum
{
    TIM_ONE_PULSE_CAPTURE = 0U,       /*!< one pulse capture in dual edge capture mode*/
    TIM_CONTINUOUS_PULSE_CAPTURE      /*!< continuous pulse capture in dual edge capture mode*/
} TIM_DualEdgeCaptureMode_t;

/**
 *  @brief TIM Signal Measurement type definition
 */
typedef enum
{
    TIM_MEASURE_SIGNAL_PERIOD = 0U,   /*!< signal period measurement*/
    TIM_MEASURE_SIGNAL_PULSE_WIDTH    /*!< signal pulse width measurement*/
} TIM_SignalMeasurement_t;


/**
 *  @brief TIM channel input filter type definition, only available for channel 0/1/2/3
 */
typedef enum
{
    TIM_INPUT_FILTER_DISABLED = 0U,   /*!< the channel input filter: disabled*/
    TIM_INPUT_FILTER_1,               /*!< the channel input filter: 1*/
    TIM_INPUT_FILTER_2,               /*!< the channel input filter: 2*/
    TIM_INPUT_FILTER_3,               /*!< the channel input filter: 3*/
    TIM_INPUT_FILTER_4,               /*!< the channel input filter: 4*/
    TIM_INPUT_FILTER_5,               /*!< the channel input filter: 5*/
    TIM_INPUT_FILTER_6,               /*!< the channel input filter: 6*/
    TIM_INPUT_FILTER_7,               /*!< the channel input filter: 7*/
    TIM_INPUT_FILTER_8,               /*!< the channel input filter: 8*/
    TIM_INPUT_FILTER_9,               /*!< the channel input filter: 9*/
    TIM_INPUT_FILTER_10,              /*!< the channel input filter: 10*/
    TIM_INPUT_FILTER_11,              /*!< the channel input filter: 11*/
    TIM_INPUT_FILTER_12,              /*!< the channel input filter: 12*/
    TIM_INPUT_FILTER_13,              /*!< the channel input filter: 13*/
    TIM_INPUT_FILTER_14,              /*!< the channel input filter: 14*/
    TIM_INPUT_FILTER_15               /*!< the channel input filter: 15*/
} TIM_Filter_t;

/**
 *  @brief TIM deadtime prescaler type define
 */
typedef enum
{
    TIM_PRESCALER_1 = 1U,            /*!< divided the system clock by 1*/
    TIM_PRESCALER_4,                 /*!< divided the system clock by 4*/
    TIM_PRESCALER_16                 /*!< divided the system clock by 16*/
} TIM_DeadtimePrescaler_t;

/**
 *  @brief TIM fault input ID type define
 */
typedef enum
{
    TIM_FAULT_CHANNEL_0 = 0U,         /*!< fault input 0*/
    TIM_FAULT_CHANNEL_1,              /*!< fault input 1*/
    TIM_FAULT_CHANNEL_ALL
} TIM_FaultChannelId_t;

/**
 *  @brief TIM Fault Safe Output Status type definition
 */
typedef enum
{
    TIM_LOW_STATE = 0U,    /*!< fault event is on-going, TIM output is low, inactive state*/
    TIM_TRI_STATE         /*!< fault event is on-going, TIM output is high, tri-stated*/
} TIM_FaultSafeState_t;

/**
 *  @brief TIM Fault Clear Mode type definition
 */
typedef enum
{
    TIM_Fault_MANUAL_CLEAR = 0U,/*!< manual fault clear mode*/
    TIM_Fault_AUTO_CLEAR        /*!< automatical fault clear mode*/
} TIM_FaultClearMode_t;

/**
 *  @brief TIM CNTINT OUTSWCR register update Mode type definition
 */
typedef enum
{
    TIM_UPDATE_SYSTEM_CLK = 0U,     /*!< update on all rising edge of the system clock*/
    TIM_UPDATE_PWM_SYN              /*!< update only by PWM synchronization*/
} TIM_RegUpdateMode_t;

/**
 *  @brief TIM Reload Mode type definition
 */
typedef enum
{
    TIM_RELOAD_FULL_CYCLE = 0U,   /*!< full cycle reload opportunity, when TIM 
                                       counter reaches the value of MOD       */
    TIM_RELOAD_HALF_CYCLE,        /*!< half cycle reload opportunity, when HCSEL
                                       enabled and TIM reaches the value of HCV*/
    TIM_RELOAD_CHANNEL_MATCH      /*!< channel match reload opportunity, when CHnSel
                                       is enabled and TIM counter reaches the value of CCV(n)*/    
} TIM_ReloadMode_t;

/**
 *  @brief TIM Interrupt type definition
 */
typedef enum
{
    TIM_INT_CH0 = 0U,                /*!< channel 0 INT*/
    TIM_INT_CH1,                     /*!< channel 1 INT*/
    TIM_INT_CH2,                     /*!< channel 2 INT*/
    TIM_INT_CH3,                     /*!< channel 3 INT*/
    TIM_INT_CH4,                     /*!< channel 4 INT*/
    TIM_INT_CH5,                     /*!< channel 5 INT*/
    TIM_INT_CH6,                     /*!< channel 6 INT*/
    TIM_INT_CH7,                     /*!< channel 7 INT*/
    TIM_INT_RLD,                     /*!< reload INT*/
    TIM_INT_TO,                      /*!< timer overflow INT*/
    TIM_INT_FAULT,                   /*!< fault INT*/
    TIM_INT_ALL
} TIM_INT_t;

/**
 *  @brief TIM input capture channel config struct definition
 */    
typedef struct
{
    TIM_ChannelId_t channelId;          /*!< channel id */
    TIM_EdgeAlignmentMode_t edgeConfig; /*!< edge-alignment mode */
    TIM_Filter_t filter;                /*!< filter config */
    ControlState_t resetEnable;         /*!< enable function that counter reset 
                                             when capture counter to CCV */
} TIM_InputChannelConfig_t;

/**
 *  @brief TIM input capture global config struct definition
 */ 
typedef struct
{
    uint8_t numChannels;                      /*!< channel number*/
    uint16_t maxCounterVal;                   /*!< max counter value*/
    TIM_InputChannelConfig_t * inputChConfig; /*!< input config for every channel*/
} TIM_InputCaptureConfig_t;

/**
 *  @brief TIM dual edge capture channel config struct definition
 */
typedef struct
{
    TIM_PairId_t pairId;                      /*!< pair id */
    TIM_EdgeAlignmentMode_t mainEdgeConfig;   /*!< main channel edge alignment mode*/
    TIM_EdgeAlignmentMode_t secondEdgeConfig; /*!< second channel edge alignment mode*/
    TIM_Filter_t filter;                      /*!< filter config*/
    TIM_DualEdgeCaptureMode_t captureMode;    /*!< capture mode: one pulse; continuous*/
} TIM_DualEdgeChannelConfig_t;

/**
 *  @brief TIM dual edge capture global config struct definition
 */
typedef struct
{
    uint8_t numPairs;                     /*!< pair number */
    uint16_t maxCounterVal;               /*!< max counter value */
    TIM_DualEdgeChannelConfig_t * config; /*!< dual edge config for each channel */
} TIM_DualEdgeCaptureConfig_t;

/**
 *  @brief TIM output compare channel config struct definition
 */
typedef struct
{
    TIM_ChannelId_t channelId;       /*!< channel id */
    TIM_OutputMode_t outputMode;     /*!< output mode: 
                                                      - no change; 
                                                      - toggle; 
                                                      - inactive; 
                                                      - active
                                      */
    TIM_Polarity_t polarity;         /*!< polarity: 
                                                   - TIM_POL_HIGH; 
                                                   - TIM_POL_LOW
                                      */
    uint16_t compareValue;           /*!< compare value*/
    Level_t initValue;               /*!< init output value*/
} TIM_OutputCompareChannelConfig_t;

/**
 *  @brief TIM output compare global config struct definition
 */
typedef struct
{
    uint8_t numChannels;                           /*!< channel number */
    uint16_t maxCounterVal;                        /*!< max counter value */
    ControlState_t initTriggerEnable;              /*!< init trigger cmd: enable/disable*/
    ControlState_t faultCtrlChannelEnable;         /*!< fault ctrl function enable/disable for each pair*/ 
    TIM_OutputCompareChannelConfig_t* outputConfig;/*!< output config for each channel*/
} TIM_OutputCompareConfig_t;

/**
 *  @brief TIM software control output config struct definition
 */
typedef struct
{
    TIM_Polarity_t polarity;            /*!< polarity: TIM_POL_HIGH; TIM_POL_LOW */
    ControlState_t outputSWCtrlEnable;  /*!< SW control output cmd: enable/disable*/
    ControlState_t complementaryEnable; /*!< Complementary mode cmd: enable/disable */
    Level_t outputSWCtrlVal;            /*!< SW control output value*/
} TIM_OutputSWCtrlConfig_t;

/**
 *  @brief TIM fault control channel config struct definition
 */
typedef struct
{
    ControlState_t faultInputChannelEnable;  /*!< fault input enable for each fault channel */
    ControlState_t faultInputFilterEnable;   /*!< fault input filter enable for each fault channel */
    TIM_Polarity_t faultInputPolarity;       /*!< fault input polarity for each fault channel */
} TIM_FaultChannelConfig_t;

/**
 *  @brief TIM fault control config struct definition
 */
typedef struct
{
    ControlState_t faultCtrlEnable;      /*!< fault control func enable */
    TIM_Filter_t faultFilterValue;       /*!< fault filter value */
    TIM_FaultSafeState_t status;         /*!< fault safe output status type */
    TIM_FaultClearMode_t faultClearMode; /*!< fault clear mode type */
    TIM_FaultChannelConfig_t faultChannelConfig[TIM_FAULT_CHANNEL_ALL];
                                         /*!< fault config for all fault channel*/
} TIM_PwmFaultCtrlConfig_t;

/**
 *  @brief TIM PWM output channel config struct definition
 */
typedef struct
{
    TIM_ChannelId_t channelId;    /*!< channel id */
    TIM_PwmMode_t pwmModeConfig;  /*!< pwm mode: disable; low-true-pulse; high-true-pulse*/
    TIM_Polarity_t polarity;      /*!< polarity: TIM_POL_HIGH; TIM_POL_LOW*/
    uint16_t compareValue;        /*!< compare value*/
    ControlState_t faultCtrlChannelEnable; /*!< fault ctrl function enable/disable for each channel*/
    ControlState_t ccvUpdateEnable;          /*!< ccv sync function enable/disable for each channel*/
} TIM_PwmChannelConfig_t;

/**
 *  @brief TIM PWM output global config struct definition
 */
typedef struct
{
    uint8_t numChannels;                 /*!< channel number */
    uint16_t minCounterVal;              /*!< min counter value */
    uint16_t maxCounterVal;              /*!< max counter value */
    TIM_PwmChannelConfig_t * pwmChConfig;/*!< pwm config for each channel */
} TIM_PwmConfig_t;

/**
 *  @brief TIM complementary PWM output channel config struct definition
 */
typedef struct
{
    TIM_PairId_t pairId;                   /*!< pair id */
    TIM_PwmMode_t pwmModeConfig;           /*!< pwm mode: disable; low-true-pulse; high-true-pulse*/
    TIM_Polarity_t polarity;               /*!< polarity: TIM_POL_HIGH; TIM_POL_LOW*/
    uint16_t mainCompareValue;             /*!< main channel compare value*/
    uint16_t secondCompareValue;           /*!< second channel compare value*/
    ControlState_t deadtimeEnable;         /*!< deadtime function enable/disable for each pair*/
    ControlState_t faultCtrlChannelEnable; /*!< fault ctrl function enable/disable for each pair*/
    ControlState_t ccvUpdateEnable;          /*!< ccv sync function enable/disable for each pair*/
} TIM_CompPwmChannelConfig_t;

/**
 *  @brief TIM complementary PWM output global config struct definition
 */
typedef struct
{
    uint8_t numPairs;                         /*!< pair id */
    uint16_t minCounterVal;                   /*!< min Counter val*/
    uint16_t maxCounterVal;                   /*!< max Counter val*/
    TIM_DeadtimePrescaler_t deadTimePrescaler;/*!< deadtime prescaler*/
    uint8_t deadTimeVal;                      /*!< deadtime value*/
    TIM_CompPwmChannelConfig_t * cPwmChConfig;/*!< complementary pwm config for each channel*/
} TIM_CompPwmConfig_t;

/**
 *  @brief TIM channel config for channel match reload mode
 */
typedef struct
{
    TIM_ChannelId_t channelId;              /*!< channel id */
    ControlState_t channelMatchEnable;      /*!< channel match function Enable*/
} TIM_ChannelMatchConfig_t;

/**
 *  @brief TIM reload config struct definition
 */
typedef struct
{
    TIM_ReloadMode_t reloadMode;                    /*!< reload mode: 
                                                      - full cycle; 
                                                      - half cycle; 
                                                      - channel match */
    uint8_t loadFrequency;                        /*!< load frequency  */
    uint8_t numChannels;                          /*!< channel number */
    TIM_ChannelMatchConfig_t * channelMatchConfig;/*!< point to channel match config*/
} TIM_ReloadConfig_t;

/**
 *  @brief TIM register sync config struct define
 */
typedef struct
{
    TIM_RegUpdateMode_t  countInitSync;           /*!< Configure CNTINIT sync*/
    TIM_RegUpdateMode_t  outswcSync;            /*!< Configure OUTSWC sync*/
    ControlState_t       syncSWTriggerEnable;   /*!< Enable/Disable software trigger sync*/
    ControlState_t       syncReloadEnable;      /*!< Enable/Disable reload sync*/
    TIM_ReloadConfig_t * reloadConfig;          /*!< Configure reload params*/
} TIM_PwmSyncConfig_t;

/** @} end of group TIM_Public_Types definitions */

/** @defgroup TIM_Public_Constants
 *  @{
 */ 


/** @} end of group TIM_Public_Constants */

/** @defgroup TIM_Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief       TIM WriteProtection Enable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return none
 *
 */
void TIM_WriteProtectionEnable(TIM_ID_t timId);

/**
 * @brief       TIM WriteProtection Disable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return none
 *
 */
void TIM_WriteProtectionDisable(TIM_ID_t timId);


/**
 * @brief       Init TIMER Counter with initial value and max value
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  initialVal:   Counter init value.
 * @param[in]  maxVal:       Counter max value, also named mod value.
 *
 * @return none
 *
 */
void TIM_InitCounter(TIM_ID_t timId, uint16_t initialVal, uint16_t maxVal);


/**
 * @brief       TIM Start counter with clock configuration
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  clkSource:    Select TIM clock source:
 *                                  - TIM_CLK_SOURCE_SYSTEM
 *                                  - TIM_CLK_SOURCE_FUNCTION
 *                                  - TIM_CLK_SOURCE_EXTERNAL
 * @param[in]  divider:      Select TIM clock divider.
 *
 * @return none
 *
 */
void TIM_StartCounter(TIM_ID_t timId, TIM_ClkSource_t clkSource, 
                     TIM_ClkDivide_t divider);

/**
 * @brief       TIM Stop counter
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return none
 *
 */
void TIM_StopCounter(TIM_ID_t timId);

/**
 * @brief       TIM Set Counter Init Value Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  initialVal:   Counter init value.
 *
 * @return none
 *
 */
void TIM_SetCounterInitialVal(TIM_ID_t timId, uint16_t initialVal);

/**
 * @brief       TIM Load Counter Init Value Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return none
 *
 */
void TIM_LoadCounterInitialVal(TIM_ID_t timId);

/**
 * @brief       TIM Get Counter Init Value Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return Counter Init Value
 *
 */
uint16_t TIM_GetCounterInitialVal(TIM_ID_t timId);

/**
 * @brief       TIM Set Counter Mod Value Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  modVal:   Counter MOD value.
 *
 * @return none
 *
 */
void TIM_SetCounterModVal(TIM_ID_t timId, uint16_t modVal);

/**
 * @brief       TIM Get Counter MOD Value Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return Counter MOD Value
 *
 */
uint16_t TIM_GetCounterModVal(TIM_ID_t timId);

/**
 * @brief       TIM Set  Capture and Compare Value Function
 *
 * @param[in]  timId:      Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:  Select channel ID.
 * @param[in]  ccVal:      Capture and Compare Value.
 *
 * @return none
 *
 */
void TIM_SetCCVal(TIM_ID_t timId, TIM_ChannelId_t channelId, uint16_t ccVal);

/**
 * @brief       TIM Get Capture and Compare Value Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:    Select channel ID.
 *
 * @return Capture and Compare Value
 *
 */
uint16_t TIM_GetCCVal(TIM_ID_t timId, TIM_ChannelId_t channelId);

/**
 * @brief       TIM Set  Half Cycle Value Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  hcVal:    Half Cycle value.
 *
 * @return none
 *
 */
void TIM_SetHCVal(TIM_ID_t timId, uint16_t hcVal);

/**
 * @brief       TIM Get Half Cycle Value Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return Half Cycle Value
 *
 */
uint16_t TIM_GetHCVal(TIM_ID_t timId);

/**
 * @brief       TIM Set  Output Software Control Register Function
 *
 * @param[in]  timId:     Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  swCtrlCmd: Output Software Control Cmd.
 *
 * @return none
 *
 */
void TIM_SetOutputSwControl(TIM_ID_t timId, uint8_t swCtrlCmd);

/**
 * @brief       TIM Set  Output Software Control Value Register Function
 *
 * @param[in]  timId:     Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  swCtrlVal: Output Software Control value.
 *
 * @return none
 *
 */
void TIM_SetOutputSwCtrlVal(TIM_ID_t timId, uint8_t swCtrlVal);

/**
 * @brief       TIM Get Output Software Control Register Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return     Output Software Control Cmd.
 *
 */
uint8_t TIM_GetOutputSwControl(TIM_ID_t timId);

/**
 * @brief       TIM Get Output Software Control Register Value Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return     Output Software Control Cmd.
 *
 */
uint8_t TIM_GetOutputSwCtrlVal(TIM_ID_t timId);

/**
 * @brief       TIM 16-bit Counter Counting Mode Config Function
 *
 * @param[in]  timId:     Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  countMode: Counting Mode Param. 0: TIM Up Counting Mode. 
 *                                             1: TIM Up-Down Counting Mode.
 *
 * @return none
 *
 */
void TIM_CountingModeConfig(TIM_ID_t timId, TIM_CountingMode_t countMode);

/**
 * @brief       TIM Initialize the channels output Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return none
 *
 */
void TIM_InitChannelsOutput(TIM_ID_t timId);

/**
 * @brief       TIM initialise input capture mode config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  config:   Input Capture Config.
 *
 * @return none
 *
 */
void TIM_InputCaptureInit(TIM_ID_t timId, const TIM_InputCaptureConfig_t * config);

/**
 * @brief       TIM initialise dual edge capture mode config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  config:   Dual Edge Capture Config.
 *
 * @return none
 *
 */
void TIM_DualEdgeCaptureInit(TIM_ID_t timId, const TIM_DualEdgeCaptureConfig_t * config);

/**
 * @brief       TIM initialise output compare mode config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  config:   Output Compare Config.
 *
 * @return none
 *
 */
void TIM_OutputCompareInit(TIM_ID_t timId, const TIM_OutputCompareConfig_t * config);

/**
 * @brief       TIM output software control config Function
 *
 * @param[in]  timId:      Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:  Select Channel Id.
 * @param[in]  config:     Software Control Config.
 *
 * @return none
 *
 */
void TIM_OutputSWCtrlConfig(TIM_ID_t timId, TIM_ChannelId_t channelId, 
                            const TIM_OutputSWCtrlConfig_t* config);

/**
 * @brief       TIM enable channel output Function
 *
 * @param[in]  timId:      Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:  Select Channel Id.
 *
 * @return none
 *
 */
void TIM_ChannelOutputEnable(TIM_ID_t timId, TIM_ChannelId_t channelId);

/**
 * @brief       TIM disable channel output Function
 *
 * @param[in]  timId:      Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:  Select Channel Id.
 *
 * @return none
 *
 */
void TIM_ChannelOutputDisable(TIM_ID_t timId, TIM_ChannelId_t channelId);

/**
 * @brief       TIM Set match trigger cmd enable/disable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:    Select channel id .
 * @param[in]  cmd:          Enable/disable.
 *
 * @return none
 *
 */
void TIM_ChannelMatchTriggerCmd(TIM_ID_t timId, TIM_ChannelId_t channelId, 
                                ControlState_t cmd);

/**
 * @brief       TIM Set init trigger cmd enable/disable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  cmd:          Enable/disable.
 *
 * @return none
 *
 */
void TIM_InitTriggerCmd(TIM_ID_t timId, ControlState_t cmd);

/**
 * @brief       TIM get match trigger flag Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return flag status
 *
 */
FlagStatus_t TIM_GetMatchTriggerFlag(TIM_ID_t timId);

/**
 * @brief       TIM initialise center-aligned PWM output config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  config:   Center-aligned PWM Output Config.
 *
 * @return none
 *
 */
void TIM_OutputCenterAlignedPwmConfig(TIM_ID_t timId, const TIM_PwmConfig_t * config);

/**
 * @brief       TIM initialise edge-aligned PWM output config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  config:   Edge-aligned PWM Output Config.
 *
 * @return none
 *
 */
void TIM_OutputEdgeAlignedPwmConfig(TIM_ID_t timId, const TIM_PwmConfig_t * config);

/**
 * @brief       TIM initialise complementary PWM output config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  config:   Complementary PWM Output Config.
 *
 * @return none
 *
 */
void TIM_OutputComplementaryPwmConfig(TIM_ID_t timId, const TIM_CompPwmConfig_t * config);

/**
 * @brief   TIM initialise fault control config Function, which used in pwm mode
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  config:   Fault Control Config.
 *
 * @return none
 *
 */
void TIM_FaultControlConfig(TIM_ID_t timId, const TIM_PwmFaultCtrlConfig_t * config);

/**
 * @brief       TIM initialise fault control config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  cmd:      Enable/Disable.
 *
 * @return none
 *
 */
void TIM_FaultControlCmd(TIM_ID_t timId, ControlState_t cmd);

/**
 * @brief       TIM Software Trigger Sync Config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  cmd:      Enable/Disable.
 *
 * @return none
 *
 */
void TIM_SWTriggerSyncCmd(TIM_ID_t timId, ControlState_t cmd);

/**
 * @brief       TIM Reload Sync Config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  cmd:      Enable/Disable.
 *
 * @return none
 *
 */
void TIM_ReloadSyncCmd(TIM_ID_t timId, ControlState_t cmd);

/**
 * @brief       TIM PWM synchronization software trigger Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return none
 *
 */
void TIM_SyncSoftwareTrigger(TIM_ID_t timId);

/**
 * @brief       TIM CNTINT update mode select Function
 *
 * @param[in]  timId:       Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  updateMode:  Update mode.
 *
 * @return none
 *
 */
void TIM_CNTINTUpdateModeSelect(TIM_ID_t timId, TIM_RegUpdateMode_t updateMode);

/**
 * @brief       TIM Output Software Control Register update mode select Function
 *
 * @param[in]  timId:       Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  updateMode:  Update mode.
 *
 * @return none
 *
 */
void TIM_OSWCUpdateModeSelect(TIM_ID_t timId, TIM_RegUpdateMode_t updateMode);

/**
 * @brief       Enable/Disable TIM CCV register update function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:    Select channel id .
 * @param[in]  cmd:          Enable/disable.
 *
 * @return none
 *
 */
void TIM_CCVUpdateCmd(TIM_ID_t timId, TIM_ChannelId_t channelId, ControlState_t cmd);

/**
 * @brief       TIM Output Software Control Register update mode select Function
 *
 * @param[in]  timId:       Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  updateMode:  Update mode.
 *
 * @return none
 *
 */
void TIM_ReloadParamConfig(TIM_ID_t timId, const TIM_ReloadConfig_t* reloadConfig);

/**
 * @brief       TIM Set channel match reload cmd enable/disable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:    Select channel id .
 * @param[in]  cmd:          Enable/disable.
 *
 * @return none
 *
 */
void TIM_ChannelMatchReloadCmd(TIM_ID_t timId, TIM_ChannelId_t channelId, 
                                ControlState_t cmd);

/**
 * @brief       TIM PWM Sync Configure Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  syncConfig:   Pointer to sync configure struct.
 *
 * @return none
 *
 */
void TIM_SyncConfig(TIM_ID_t timId, const TIM_PwmSyncConfig_t* syncConfig);

/**
 * @brief       TIM INT DMA enable/disable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:    Select channel ID.
 * @param[in]  cmd:          Enable/disable.
 *
 * @return none
 *
 */
void TIM_DMACtrl(TIM_ID_t timId, TIM_ChannelId_t channelId, ControlState_t cmd);

/**
 * @brief       TIM INT mask/unmask Function
 *
 * @param[in]  timId:      Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  intType:    Select interrupt type.
 * @param[in]  intMask:    Mask/unmask.
 *
 * @return none
 *
 */
void TIM_IntMask(TIM_ID_t timId, TIM_INT_t intType, IntMask_t intMask);

/**
 * @brief       TIM INT status clear Function
 *
 * @param[in]  timId:      Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  intType:    Select interrupt type.
 *
 * @return none
 *
 */
void TIM_IntClear(TIM_ID_t timId, TIM_INT_t intType);

/**
 * @brief       TIM Get INT status Function
 *
 * @param[in]  timId:      Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  intType:    Select interrupt type.
 *
 * @return intstatus
 *
 */
IntStatus_t TIM_GetIntStatus(TIM_ID_t timId, TIM_INT_t intType);

/**
 * @brief       TIM Get Fault detection flag status of fault channel  Function
 *
 * @param[in]  timId:     Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId: Select fault input channel:TIM_FAULT_CHANNEL_0,.. .
 *
 * @return intstatus
 *
 */
IntStatus_t TIM_GetFaultStatus(TIM_ID_t timId, TIM_FaultChannelId_t channelId);

/**
 * @brief       TIM fault status clear Function
 *
 * @param[in]  timId:      Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  intType:    Select interrupt type.
 *
 * @return none
 *
 */
void TIM_FaultStatusClear(TIM_ID_t timId, TIM_FaultChannelId_t channelId);

/**
 * @brief       TIM match trigger clear Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return none
 *
 */
void TIM_MatchTriggerClear(TIM_ID_t timId);

/**
 * @brief       TIM INT mask/unmask Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  intType:  Select interrupt type.
 * @param[in]  cbFun:    Callback function .
 *
 * @return none
 *
 */
void TIM_InstallCallBackFunc(TIM_ID_t timId, TIM_INT_t intType, isr_cb_t * cbFun);

/** @} end of group TIM_Public_FunctionDeclaration */

/** @} end of group TIM */

/** @} end of group Z20K14XM_Peripheral_Driver */
#endif /* TIM_DRV_H */
