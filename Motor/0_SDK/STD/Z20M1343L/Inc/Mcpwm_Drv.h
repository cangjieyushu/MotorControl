/**************************************************************************************************/
/**
 * @file     : Mcpwm_Drv.h
 * @brief    : Mcpwm module driver header file.
 *              - Platform: Z20M1343L
 * @version  : 0.1.0
 * @date     : May-2023
 * @author   : Zhixin Semiconductor
 * @note     : None   
 *   
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef MCPWM_DRV_H
#define MCPWM_DRV_H   

#include "Common_Drv.h"

/** @defgroup Public_TypeDefinition 
 *  @{
 */

/**
 *  @brief MCPWM ID type definition
 */
typedef enum
{
    MCPWM0_ID = 0U,                            /*!< MCPWM  */
} Mcpwm_IdType;

/**
 *  @brief MCPWM Counter ID type definition
 */
typedef enum
{
    MCPWM_COUNTER_0 = 0U,                     /*!< MCPWM Counter 0*/
    MCPWM_COUNTER_1,                          /*!< MCPWM Counter 1*/
    MCPWM_COUNTER_2,                          /*!< MCPWM Counter 2*/
    MCPWM_COUNTER_3                           /*!< MCPWM Counter 3*/
} Mcpwm_CounterIdType;

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
} Mcpwm_ChannelIdType;

/**
 *  @brief MCPWM Pair Channel ID type definition
 */
typedef enum
{
    MCPWM_PAIR_CHANNEL_0 = 0U,    /*!< MCPWM pair 0 control channel0 and channel 1*/
    MCPWM_PAIR_CHANNEL_1,         /*!< MCPWM pair 1 control channel2 and channel 3*/
    MCPWM_PAIR_CHANNEL_2,         /*!< MCPWM pair 2 control channel4 and channel 5*/
    MCPWM_PAIR_CHANNEL_3          /*!< MCPWM pair 3 control channel6 and channel 7*/
} Mcpwm_PairIdType;

/**
 *  @brief MCPWM Clock Source type definition
 */
typedef enum
{
    MCPWM_CLK_DISABLED        = 0U,     /*!< MCPWM Counter Clock is disabled*/
    MCPWM_CLK_SOURCE_CORE     = 1U,     /*!< Core Clock as MCPWM Counter Clock*/
    MCPWM_CLK_SOURCE_EXTERNAL = 3U      /*!< External Clock as MCPWM Counter Clock*/
} Mcpwm_ClkSourceType;

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
} Mcpwm_ClkDivideType;

/**
 *  @brief MCPWM Counter Counting Mode type definition
 */
typedef enum
{
    MCPWM_COUNTING_UP = 0U,                    /*!< MCPWM Up Counting Mode*/
    MCPWM_COUNTING_UP_DOWN                     /*!< MCPWM Up-Down Counting Mode*/
} Mcpwm_CountingModeType;

/**
 *  @brief MCPWM Pulse Polarity type definition 
 */
typedef enum
{
    MCPWM_LOW_PULSE_POL = 0U,         /*!< MCPWM channel output is inactive when counter value over CV value*/
    MCPWM_HIGH_PULSE_POL              /*!< MCPWM channel output is active when counter value over CV value*/
} Mcpwm_Pulse_PolarityType;

/**
 *  @brief MCPWM Active Polarity  type definition
 */
typedef enum
{
    MCPWM_POL_ACTIVE_HIGH = 0U,         /*!<MCPWM channel output polarity  is active high*/
    MCPWM_POL_ACTIVE_LOW                /*!< MCPWM channel output polarity  is active low*/
} Mcpwm_PolarityType;

/**
 * @brief MCPWM Channel Output Status Type definition
 */
typedef enum
{
    MCPWM_OUT_LOW = 0U,               /*!< MCPWM channel output is low */
    MCPWM_OUT_HIGH = 1U               /*!< MCPWM channel output is high*/
} Mcpwm_OutputStatusType;

/**
 *  @brief MCPWM channel value selection for pairs of channel type definition
 */
typedef enum
{
    MCPWM_MAIN_CV = 0U,      /*!< in complementary Mode, CV(n) is used to generate channel(n) PWM output;
                                   channel(n+1) output is complementary with channel(n) */
    MCPWM_SECOND_CV         /*!< in complementary Mode, CV(n+1) is used to generate channel(n) PWM output
                                   channel(n+1) output is complementary with channel(n) */
} Mcpwm_ChannelValueSelType;

/**
 *  @brief MCPWM pulse edge control for pairs of channel type definition
 */
typedef enum
{
    MCPWM_ONE_CV = 0U,             /*!< in complementary Mode, either CV(n) or CV(n+1)is used to set or clear 
                                   channel(n) PWM output,channel(n+1) output is complementary with channel(n)*/
    MCPWM_BOTH_CV                  /*!< in complementary Mode, one of CV(n) and CV(n+1)is used to set
                                   channel(n) PWM output,another is used to clear channel(n) PWM output;
                                   channel(n+1) output is complementary with channel(n)*/
} Mcpwm_PulseEdgeCtrlType;

/**
 *  @brief MCPWM asymmetric PWM output enable for pairs of channel type definition
 */
typedef enum
{
    MCPWM_SYMMETRIC = 0U,  /*!< channel(n) and channel(n+1) are symmetric PWM output in complementary CPWM Mode*/
    MCPWM_ASYMMETRIC       /*!< channel(n) and channel(n+1) are asymmetric PWM output in complementary CPWM Mode*/
} Mcpwm_AsymType;

/**
 *  @brief MCPWM Fault Safe Output Status type definition
 */
typedef enum
{
    MCPWM_SAFE_STATE = 0U,/*!< fault event is on-going, MCPWM output will be safe State,
                                   depend on selected channel safe status value for faultA*/
    MCPWM_TRI_STATE           /*!< fault event is on-going, MCPWM output will be tri-stated*/
} Mcpwm_FaultSafeStateType;

/**
 *  @brief MCPWM Fault Clear Mode type definition
 */
typedef enum
{
    MCPWM_Fault_MANUAL_CLEAR = 0U,/*!< manual fault clear Mode*/
    MCPWM_Fault_AUTO_CLEAR        /*!< automatical fault clear Mode*/
} Mcpwm_FaultClearModeType;

/**
 *  @brief MCPWM CNTINT OUTSWCR register update Mode type definition
 */
typedef enum
{
    MCPWM_UPDATE_SYSTEM_CLK = 0U,     /*!< update on all rising edge of the system clock*/
    MCPWM_UPDATE_PWM_SYN              /*!< update only by PWM synchronization*/
} Mcpwm_RegUpdateModeType;

/**
 *  @brief MCPWM Load Mode type definition
 */
typedef enum
{
    MCPWM_LOAD_MANUAL = 0U,     /*!<  manual load Mode*/
    MCPWM_LOAD_AUTO              /*!< auto load Mode*/
} Mcpwm_LoadModeType;

/**
 *  @brief MCPWM Match Trigger Mode type definition
 */
typedef enum
{
    DISABLE_MODE  = 0U,              /*!< disable mach trigger generation  */
    ENABLE_UP_GENERATE_MODE,         /*!<  enable match trigger only generation on up counting Mode */
    ENABLE_DOWN_GENERATE_MODE,       /*!<  enable match trigger only generation on down counting Mode */
    ENABLE_UP_DOWN_GENERATE_MODE     /*!<  enable match trigger  generation both on up &down counting Mode */
} Mcpwm_MatchTriggerModeType;

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
    MCPWM_INT_ALL
} Mcpwm_IntType;
/**
 *  @brief MCPWM SWCtrl Ouutput Logic Status 
 *
 */
typedef enum
{
    MCPWM_LOGIC_LOW =0U ,             /* Channel out logic is 0  should Config with POL to decide the Output*/
    MCPWM_LOGIC_HIGH                  /* Channel out logic is 1  should Config with POL to decide the Output*/

}Mcpwm_LogicStatusType;


/**
 *  @brief MCPWM software control output Config struct definition
 */
typedef struct
{
    Common_ControlStateType OutputSWCtrlEnable;  /*!< SW control output Cmd: enable/disable*/
    Mcpwm_LogicStatusType OutputLogicStatus;      /*!< SW control Output Logic*/
} Mcpwm_OutputSWCtrlConfigType;

/**
 *  @brief MCPWM fault control channel Config struct definition
 */
typedef struct
{
    Common_ControlStateType FaultInputChannelEnable;  /*!< fault input enable for each fault channel */
    Common_ControlStateType FaultInputFilterEnable;   /*!< fault input filter enable for each fault channel */
    Mcpwm_PolarityType FaultInputPolarity;     /*!< fault input polarity for each fault channel */
} Mcpwm_FaultChannelConfigType;

/**
 *  @brief MCPWM fault control Config struct definition
 */
typedef struct
{
    uint8 FaultFilterValue;              /*!< fault filter value */
    Mcpwm_FaultSafeStateType Status;         /*!< fault safe output status type */
    Mcpwm_FaultClearModeType FaultClearMode; /*!< fault clear Mode type */
    Mcpwm_FaultChannelConfigType* FaultChannelConfig;
                                           /*!< fault Config for all fault channel*/
} Mcpwm_PwmFaultCtrlConfigType;

/**
 *  @brief MCPWM independent PWM output channel Config struct definition
 */
typedef struct
{
    Mcpwm_ChannelIdType ChannelId;           /*!< channel id */
    Common_ControlStateType ChannelOutputEnable;    /*!< channel output enable/disable*/
    Mcpwm_PolarityType Polarity;             /*!< channel output polarity: MCPWM_POL_HIGH; MCPWM_POL_LOW*/
    Mcpwm_Pulse_PolarityType PulsePol;       /*!< channel Pulse polarity*/
    uint16 CompareValue;                 /*!< compare value*/
    Common_LevelType ChannelOffVal;                 /*!< channel output value when counter is off*/
    Mcpwm_MatchTriggerModeType ChannelMatchTrigMode; /*!< channel match trigger Mode DISABLE_MODE/ENABLE_UP_GENERATE_MODE/ENABLE_UP_GENERATE_MODE/ENABLE_UP_DOWN_GENERATE_MODE*/
    Common_ControlStateType FaultCtrlEnable;        /*!< channel fault control enable/disable*/
    Common_ControlStateType CvUpdateEnable;         /*!< enable/disable synchronization of CV(n)*/
    Common_LevelType SafeStatusForFaultA;           /*!< channel safe status value for fault A*/
} Mcpwm_PwmChannelConfigType;

/**
 *  @brief MCPWM independent PWM output global Config struct definition
 */
typedef struct
{
    uint16 CountModVal;                         /*!< mod(max) counter value */
    Mcpwm_CountingModeType CountMode;          /*!< counting Mode: MCPWM_COUNTING_UP;
                                                               MCPWM_COUNTING_UP_DOWN*/
    Mcpwm_PwmChannelConfigType * MainPwmChConfig;/*!< independent pwm Config for main  channel */
    Mcpwm_PwmChannelConfigType * SecondPwmChConfig;/*!< independent pwm Config for second  channel */
} Mcpwm_IndependentPwmConfigType;

/**
 *  @brief MCPWM complementary PWM output channel Config struct definition
 */
typedef struct
{
    Mcpwm_PairIdType PairId;                      /*!< pair id */
    uint16 DeadTimeVal;                       /*!< deadtime value*/
    Mcpwm_PulseEdgeCtrlType Pec;                  /*!< pulse edge control for pairs */
    Mcpwm_ChannelValueSelType CvSel;              /*!< Channel value select for pairs */
    Mcpwm_AsymType Asym;                          /*!< asymmetric PWM output enable for pairs */
    Common_ControlStateType MainChannelOutputEnable;     /*!< main channel output enable/disable for pair*/
    Common_ControlStateType SecondChannelOutputEnable;   /*!< second channel output enable/disable for pair*/
    Mcpwm_PolarityType Polarity;                  /*!< polarity: MCPWM_POL_HIGH; MCPWM_POL_LOW*/
    Mcpwm_Pulse_PolarityType PulsePol;            /*!< channel Pulse polarity*/
    uint16 MainCompareValue;                  /*!< main channel compare value*/
    uint16 SecondCompareValue;                /*!< second channel compare value*/
    Common_LevelType MainChannelOffVal;                  /*!< main channel output value when counter is off*/
    Common_LevelType SecondChannelOffVal;                /*!< second channel output value when counter is off*/
    Mcpwm_MatchTriggerModeType MainChannelMatchTrigMode;  /*!< main channel match trigger Mode DISABLE_MODE/ENABLE_UP_GENERATE_MODE/ENABLE_UP_GENERATE_MODE/ENABLE_UP_DOWN_GENERATE_MODE  */
    Mcpwm_MatchTriggerModeType SecondChannelMatchTrigMode;/*!< second channel match trigger Mode DISABLE_MODE/ENABLE_UP_GENERATE_MODE/ENABLE_DOWN_GENERATE_MODE/ENABLE_UP_DOWN_GENERATE_MODE */
    Common_ControlStateType DeadTimeEnable;              /*!< deadtime function enable/disable for each pair*/
    Common_ControlStateType FaultCtrlEnable;      /*!< fault ctrl function enable/disable for each pair*/
    Common_ControlStateType CvUpdateEnable;                /*!<  enable/disable the synchronization of CV(n) and CV(n+1) for pair*/
    Common_LevelType MainSafeStatusForFaultA;            /*!< main channel(n) safe status value for fault A*/
    Common_LevelType SecondSafeStatusForFaultA;          /*!< second channel(n+1) safe status value for fault A*/
} Mcpwm_CompPwmChannelConfigType;

/**
 *  @brief MCPWM complementary PWM output global Config struct definition
 */
typedef struct
{
    uint16 CountModVal;                     /*!< mod(max) Counter val*/
    Mcpwm_CountingModeType CountMode;               /*!< counting Mode: MCPWM_COUNTING_UP;
                                                               MCPWM_COUNTING_UP_DOWN*/
    Mcpwm_CompPwmChannelConfigType * CPwmChConfig;/*!< complementary pwm Config for each channel*/
} Mcpwm_CompPwmConfigType;

/**
 *  @brief MCPWM reload Config struct definition
 */
typedef struct
{
    Common_ControlStateType HalfCycleEnable;      /*!< for CPWM output, half cycle reload enable/disable*/ 
    Common_ControlStateType FullCycleEnable;      /*!< for CPWM output, full cycle reload enable/disable*/ 
    uint8 LoadFrequency;               /*!< load frequency*/
} Mcpwm_ReloadConfigType;

/** @} end of group Public_TypeDefinition definitions */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */
 
/**
 * @brief       MCPWM Start counter with clock configuration
 *
 * @param[in]  McpwmId:      Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ClkSource:    Select MCPWM clock source:
 *                                  - MCPWM_CLK_SOURCE_CORE
 *                                  - MCPWM_CLK_SOURCE_EXTERNAL
 * @param[in]  Divider:      Select MCPWM clock Divider.
 *
 * @return none
 *
 */
void Mcpwm_ConfigClockSource(Mcpwm_IdType McpwmId, Mcpwm_ClkSourceType ClkSource, 
                     Mcpwm_ClkDivideType Divider);

/**
 * @brief       MCPWM Start counter
 *
 * @param[in]  McpwmId:        Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:      Selected Counter ID.
 *
 * @return none
 *
 */
void Mcpwm_StartCounter(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId);

/**
 * @brief       MCPWM Stop counter
 *
 * @param[in]  McpwmId:        Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:      Selected Counter ID.
 *
 * @return none
 *
 */
void Mcpwm_StopCounter(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId);

/**
 * @brief       MCPWM Start Globale counter
 *
 * @param[in]  McpwmId:        Select the MCPWM ID: MCPWM0_ID.
 *
 * @return none
 *
 */
void Mcpwm_StartGlobalCounter(Mcpwm_IdType McpwmId);

/**
 * @brief       MCPWM Stop Global counter
 *
 * @param[in]  McpwmId:        Select the MCPWM ID: MCPWM0_ID.
 *
 * @return none
 *
 */
void Mcpwm_StopGlobalCounter(Mcpwm_IdType McpwmId);

/**
 * @brief       MCPWM Set Counter Counting Mode Function
 *
 * @param[in]  McpwmId:        Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:      Selected Counter ID.
 * @param[in]  CountingMode:   Counter Counting Mode.
 *
 * @return none
 *
 */
void Mcpwm_SetCountingMode(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId,
                                Mcpwm_CountingModeType CountingMode);

/**
 * @brief       MCPWM Get Counter Value Function
 *
 * @param[in]  McpwmId:        Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:      Selected Counter ID.
 *
 * @return Counter Init Value
 *
 */
uint16 Mcpwm_GetCounterVal(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId);

/**
 * @brief       MCPWM Set Counter Mod(Max) Value Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:  Selected Counter ID.
 * @param[in]  ModVal:     Counter MOD value.
 *
 * @return none
 *
 */
void Mcpwm_SetCounterModVal(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId, uint16 ModVal);

/**
 * @brief       MCPWM Get Counter MOD Value Function
 *
 * @param[in]  McpwmId:        Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:      Selected Counter ID.
 *
 * @return Counter MOD Value
 *
 */
uint16 Mcpwm_GetCounterModVal(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId);

/**
 * @brief       MCPWM Load Counter Init Value Function
 *
 * @param[in]  McpwmId:        Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:      Selected Counter ID.
 *
 * @return none
 *
 */
void Mcpwm_ResetCounter(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId);

/**
 * @brief       MCPWM Set deadtime Value Function
 *
 * @param[in]  McpwmId:     Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:      Select the MCPWM pair ID.
 * @param[in]  DeadTimeVal: Deadtime value, max value is 0xFFF.
 *
 * @return none
 *
 */
void Mcpwm_SetDeadTimeVal(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, uint16 DeadTimeVal);

/**
 * @brief       MCPWM Get deadtime Value Function
 *
 * @param[in]  McpwmId:     Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:      Select the MCPWM pair ID.
 *
 * @return Deadtime Value
 *
 */
uint16 Mcpwm_GetDeadTimeVal(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId);

/**
 * @brief       MCPWM Set MOD Dither  Function
 *
 * @param[in]  McpwmId:      Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:    Selected Counter ID.
 * @param[in]  modDitherVal: Mod dither value, max value is 0x1F.
 *
 * @return none
 *
 */
void Mcpwm_SetModDither(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId, uint8 ModDither);

/**
 * @brief       MCPWM enable channel output Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select Channel Id.
 *
 * @return none
 *
 */
void Mcpwm_EnableChannelOutput(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId);

/**
 * @brief       MCPWM disable channel output Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select Channel Id.
 *
 * @return none
 *
 */
void Mcpwm_DisableChannelOutput(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId);

/**
 * @brief       MCPWM  Get Output Status of selected channel
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select Channel Id.
 *
 * @return    Mcpwm_OutputStatusType: Channel Output Status.  
 * @retval    MCPWM_OUT_LOW         : MCPWM channel output is low .
 * @retval    MCPWM_OUT_HIGH        : MCPWM channel output is high.                        
 *
 */
Mcpwm_OutputStatusType Mcpwm_GetChannelOutputStatus(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId);

/**
 * @brief       MCPWM set channel pulse polarity for selected channel
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select Channel Id.
 * @param[in]  Cpp:        Select pulse polarity.
 *
 * @return none
 *
 */
void Mcpwm_SetChannelPulsePol(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId,
                                Mcpwm_Pulse_PolarityType Cpp);

/**
 * @brief       MCPWM Set  Compare Value Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select channel ID.
 * @param[in]  CVal:    Compare Value.
 *
 * @return none
 *
 */
void Mcpwm_SetChannelCVal(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId, uint16 CVal);

/**
 * @brief       MCPWM Get Compare Value Function
 *
 * @param[in]   McpwmId:      Select the MCPWM ID: MCPWM0_ID.
 * @param[in]   ChannelId:    Select channel ID.
 *
 * @return Compare Value
 *
 */
uint16 Mcpwm_GetChannelCVal(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId);

/**
 * @brief       MCPWM Set  CVal Dither Value Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select channel ID.
 * @param[in]  CvDither:   Compare Value Dither, max value is 0x1F.
 *
 * @return none
 *
 */
void Mcpwm_SetChannelCVDither(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId, uint8 CvDither);

/**
 * @brief       MCPWM Set  channel output value when counter is off
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select channel ID.
 * @param[in]  Level:      Low_level/high_level for channel output.
 *
 * @return none
 *
 */
void Mcpwm_SetChannelOffValue(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId,
                              Common_LevelType Level);

/**
 * @brief       MCPWM set channel output polarity for selected channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId: Select Channel Id.
 * @param[in]  Pol:       Output polarity.
 *
 * @return none
 *
 */
void Mcpwm_SetChannelPolarity(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId,
                                Mcpwm_PolarityType Pol);

/**
 * @brief       MCPWM Set channel match trigger Mode Function
 *
 * @param[in]  McpwmId:      Select the MCPWM ID: MCPWM0_ID .
 * @param[in]  ChannelId:    Select channel id .
 * @param[in]  Mode:          Mcpwm_MatchTriggerModeType: DISABLE_MODE,ENABLE_UP_GENERATE_MODE,ENABLE_DOWN_GENERATE_MODE,ENABLE_UP_DOWN_GENERATE_MODE
 *
 * @return none
 *
 */
void Mcpwm_SetChannelMatchTriggerMode(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId, 
                                Mcpwm_MatchTriggerModeType Mode);

/**
 * @brief       MCPWM Set init trigger Cmd enable/disable Function
 *
 * @param[in]  McpwmId:        Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Cmd:            Enable/disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableInitTrigger(Mcpwm_IdType McpwmId, Common_ControlStateType Cmd);
   
/**
 * @brief       MCPWM Set End trigger Cmd enable/disable Function
 *
 * @param[in]  McpwmId:        Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Cmd:            Enable/disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableEndTrigger(Mcpwm_IdType McpwmId, Common_ControlStateType Cmd);

/**
 * @brief       MCPWM Set  channel output software control value
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select channel ID.
 * @param[in]  LogicStatus:    Logic Status for channel output.
 *
 * Note: Donot Call this function more than one time before PWM synchronization
 * event occur When SYNCOSWC = MCPWM_UPDATE_PWM_SYN.
 *
 * @return none
 *
 */
void Mcpwm_SetChannelOCV(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId,
                               Mcpwm_LogicStatusType  LogicStatus);

/**
 * @brief       MCPWM Set channel output software control enable/disable Function
 *
 * @param[in]  McpwmId:      Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:    Select channel id .
 * @param[in]  Cmd:          Enable/disable.
 *
 * Note: Donot Call this function more than one time before PWM synchronization
 * event occur When SYNCOSWC = MCPWM_UPDATE_PWM_SYN.
 *
 * @return none
 *
 */
void Mcpwm_EnableChannelOC(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId, 
                                Common_ControlStateType Cmd);

/****************************************************************************//**
 * @brief       MCPWM Config  output software control for All channels 
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Config:     Config values.
 *
 * @return none
 *
 *******************************************************************************/
void Mcpwm_ConfigAllOutputSoftwareControl(Mcpwm_IdType McpwmId, uint16 Config);

/**
 * @brief       MCPWM Set combine enable/disable for pairs of channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:    Select pair id .
 * @param[in]  Cmd:       Enable/disable.
 *
 * @return none
 *
 */  
void Mcpwm_EnablePairCombine(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, 
                                Common_ControlStateType Cmd);
                          
/**
 * @brief       MCPWM Select channel value  for pairs of channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:    Select pair id .
 * @param[in]  CvSel:     Select channel value .
 *
 * @return none
 *
 */                         
void Mcpwm_SelPairChannelValue(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, 
                                Mcpwm_ChannelValueSelType CvSel);

/**
 * @brief       MCPWM Set pulse edge control mode for pairs of channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:    Select pair id .
 * @param[in]  Pec:       Pulse Edge Ctrl.
 *
 * @return none
 *
 */
void Mcpwm_SetPairPulseEdgeCtrlMode(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, 
                                Mcpwm_PulseEdgeCtrlType Pec);

/**
 * @brief       MCPWM enable asymmetric PWM output  for pairs of channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:    Select pair id .
 * @param[in]  Asym:      Symmetric/asymmetric.
 *
 * @return none
 *
 */
void Mcpwm_EnablePairAsymmetric(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, 
                                Mcpwm_AsymType Asym);

/**
 * @brief       MCPWM Set enable/disable Synchronization of CV(n) and CV(n+1) for pairs of channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID .
 * @param[in]  PairId:    Select pair id .
 * @param[in]  Cmd:       Enable/disable.
 *
 * @return none
 *
 */
void Mcpwm_EnablePairSynchronization(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, 
                                Common_ControlStateType Cmd);

/**
 * @brief       MCPWM Set deadtime insertion enable/disable for pairs of channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:    Select pair id .
 * @param[in]  Cmd:       Enable/disable.
 *
 * @return none
 *
 */
void Mcpwm_EnablePairDeadtime(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, 
                                Common_ControlStateType Cmd);

/**
 * @brief       MCPWM Set fault control enable/disable for pairs of channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:    Select pair id .
 * @param[in]  Cmd:       Enable/disable.
 *
 * @return none
 *
 */
void Mcpwm_EnablePairFaultCtrl(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, 
                                Common_ControlStateType Cmd);


/**
 * @brief       MCPWM Set fault input filter value
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  FilterVal: Fault input filter value(max value is 0xF, 0 is disabled).
 *
 * @return none
 *
 */
void Mcpwm_SetFaultFilterVal(Mcpwm_IdType McpwmId, uint8 FilterVal);

/**
 * @brief       MCPWM set fault input filter enable/disable for selected input channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Cmd:       Fault input enable/disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableFaultFilter(Mcpwm_IdType McpwmId,Common_ControlStateType Cmd);

/**
 * @brief       MCPWM Set fault output State
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  State:     Safe State / tri-State, if safe State, 
 *                        the safe State is decided by FLTASS.
 *
 * @return none
 *
 */
void Mcpwm_SetFaultOutputState(Mcpwm_IdType McpwmId, Mcpwm_FaultSafeStateType State);

/**
 * @brief       MCPWM Set fault clear Mode
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Mode:      Fault clear Mode.
 *
 * @return none
 *
 */
void Mcpwm_SetFaultClearMode(Mcpwm_IdType McpwmId, Mcpwm_FaultClearModeType Mode);

/**
 * @brief       MCPWM set fault input channel polarity for selected input channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Pol:       Fault input channel polarity.
 *
 * @return none
 *
 */
void Mcpwm_SetFaultInputPolarity(Mcpwm_IdType McpwmId, Mcpwm_PolarityType Pol);

/**
 * @brief       MCPWM set fault input enable/disable for selected input channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Cmd:       Fault input enable/disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableFaultInput(Mcpwm_IdType McpwmId,Common_ControlStateType Cmd);

/**
 * @brief       MCPWM set selected channel safe status value for fault Group A(fault 
                input 0 ).
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId: Select channel Id.
 * @param[in]  Level:     Safe status Level: low Level/high leval.
 *
 * @return none
 *
 */
void Mcpwm_SetChannelSafeStatusValForFaultA(Mcpwm_IdType McpwmId, 
                                            Mcpwm_ChannelIdType ChannelId,
                                            Common_LevelType Level);

/**
 * @brief       MCPWM output software control Config Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select Channel Id.
 * @param[in]  Config:     Software Control Config.
 *
 * @Note: This  function cannot be used when SYNCOSWC = MCPWM_UPDATE_PWM_SYN:
 * OUTSWCR register is updated with its buffer value only by PWM synchronization
 *
 * @return none
 *
 */
void Mcpwm_OutputSWCtrlConfig(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId, 
                            const Mcpwm_OutputSWCtrlConfigType* Config);

/**
 * @brief       MCPWM get match trigger flag Function:when any channel match trigger
 *              is generated, this flag is set by hardware.
 *
 * @param[in]  McpwmId:      Select the MCPWM ID: MCPWM0_ID.
 *
 * @return     Common_FlagStatusType.
 * @retval     COMMON_RESET : Reset state, No channel match trigger is generated. 
 * @retval     COMMON_SET   : Set state, At least one channel match trigger is generated.
 *
 */
Common_FlagStatusType Mcpwm_GetMatchTriggerFlag(Mcpwm_IdType McpwmId);

/**
 * @brief       MCPWM independent PWM channel Config Function
 *
 * @param[in]  McpwmId:         Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelConfig:   Independent PWM Output Channel Config.
 *
 * @return none
 *
 */
void Mcpwm_ConfigIndependentPwmChannel(Mcpwm_IdType McpwmId,  const Mcpwm_PwmChannelConfigType * ChannelConfig);

/**
 * @brief       MCPWM initialise independent PWM output Config Function
 *
 * @param[in]  McpwmId:    Selected the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:  Selected Counter ID.
 * @param[in]  Config:     Independent PWM Output Config.
 *
 * @return none
 *
 */
void Mcpwm_ConfigOutputIndependentPwm(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId,
                                     const Mcpwm_IndependentPwmConfigType * Config);

/**
 * @brief       MCPWM Complementary PWM channel Config Function
 *
 * @param[in]  McpwmId:         Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelConfig:   Complementary PWM Output Channel Config.
 *
 * @return none
 *
 */
void Mcpwm_ConfigComplementaryPwmChannel(Mcpwm_IdType McpwmId, 
                                         const Mcpwm_CompPwmChannelConfigType * ChannelConfig);

/**
 * @brief       MCPWM initialise complementary PWM output Config Function
 *
 * @param[in]  McpwmId:    Selected the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:  Selected Counter ID.
 * @param[in]  Config:     Complementary PWM Output Config.
 *
 * @return none
 *
 */
void Mcpwm_ConfigOutputComplementaryPwm(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId,
                                        const Mcpwm_CompPwmConfigType * Config);

/**
 * @brief   MCPWM initialise fault control Config Function, which used in pwm Mode
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Config:     Fault Control Config.
 *
 * @return none
 *
 */
void Mcpwm_ConfigFaultControl(Mcpwm_IdType McpwmId, const Mcpwm_PwmFaultCtrlConfigType * Config);

/**
 * @brief       MCPWM enable/disable that Software Trigger activate CNT regsister sync
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableSwTrigCntSync(Mcpwm_IdType McpwmId, Common_ControlStateType Cmd);

/**
 * @brief       MCPWM enable/disable that Software Trigger activate wirte buffer regsister sync
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableSwTrigWrBufSync(Mcpwm_IdType McpwmId, Common_ControlStateType Cmd);

/**
 * @brief       MCPWM generate  PWM synchronization software trigger Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 *
 * @return none
 *
 */
void Mcpwm_EnableSyncSoftwareTrigger(Mcpwm_IdType McpwmId);

/**
 * @brief       MCPWM Output Software Control Register update Mode select Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  UpdateMode: Update Mode. 0: update on all rising edge of the system clock
 *                                       1: update only by PWM synchronization
 *
 * @return none
 *
 */
void Mcpwm_SetOswcUpdateMode(Mcpwm_IdType McpwmId, Mcpwm_RegUpdateModeType UpdateMode);

/**
 * @brief       MCPWM CPWM half cycle reload enable/disable Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:  Select counter id for CPWM.
 * @param[in]  Cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableCpwmHalfCycleReload(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId, Common_ControlStateType Cmd);

/**
 * @brief       MCPWM CPWM full cycle reload enable/disable Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:  Select counter id for CPWM.
 * @param[in]  Cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableCpwmFullCycleReload(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId, Common_ControlStateType Cmd);

/**
 * @brief       MCPWM Set reload frequency Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:  Select counter id for CPWM.
 * @param[in]  Freq:       Reload frequency, max is 0x1F.
 *
 * @return none
 *
 */
 void Mcpwm_SetReloadFreq(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId, uint8 Freq);
  
/**
 * @brief       MCPWM Config Reload Param for selected pair of channels Function
 *
 * @param[in]  McpwmId:      Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:    Select counter id .
 * @param[in]  ReloadConfig: Pointer to reload param Config struct.
 *
 * @return none
 *
 */
void Mcpwm_ConfigReloadParam(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId, 
                             const Mcpwm_ReloadConfigType* ReloadConfig);

/**
 * @brief       MCPWM Reload enable Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:     Select pair id for CPWM.
 * @param[in]  Cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableReload(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, Common_ControlStateType Cmd);

 /**
 * @brief       MCPWM Load Mode Select Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Mode:        Select Load Mode:Mcpwm_LOAD_MANUAL,Mcpwm_LOAD_AUTO
 *
 * @return none
 *
 */
void Mcpwm_SetLoadMode(Mcpwm_IdType McpwmId, Mcpwm_LoadModeType Mode);

/**
 * @brief       MCPWM INT mask/unmask Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  IntType:    Select interrupt type.
 * @param[in]  IntMask:    Mask/unmask .
 *
 * @return none
 *
 */
void Mcpwm_SetIntMask(Mcpwm_IdType McpwmId, Mcpwm_IntType IntType, Common_IntMaskType IntMask);

/**
 * @brief       MCPWM INT status clear Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  IntType:    Select interrupt type.
 *
 * @return none
 *
 */
void Mcpwm_ClearInt(Mcpwm_IdType McpwmId, Mcpwm_IntType IntType);

/**
 * @brief       MCPWM Get INT status Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  IntType:    Select interrupt type.
 *
 * @return    IntStatus: interrupt status.
 * @retval    COMMON_RESET : Reset state.
 * @retval    COMMON_SET   : Set state.
 * @note     :MCPWM_INT_ALL is invalid as input
 */
Common_IntStatusType Mcpwm_GetIntStatus(Mcpwm_IdType McpwmId, Mcpwm_IntType IntType);

/**
 * @brief       MCPWM Get Fault detection flag status of fault channel  Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 *
 * @return    IntStatus: interrupt status.
 * @retval    COMMON_RESET : Reset state.
 * @retval    COMMON_SET   : Set state.
 *
 */
Common_IntStatusType Mcpwm_GetFaultStatus(Mcpwm_IdType McpwmId);

/**
 * @brief       MCPWM fault Status clear Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 *
 * @return none
 *
 */
void Mcpwm_ClearFaultStatus(Mcpwm_IdType McpwmId);

/**
 * @brief       MCPWM any channel match trigger flag clear Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 *
 * @return none
 *
 */
void Mcpwm_ClearMatchTriggerFlag(Mcpwm_IdType McpwmId);

 /**
 * @brief       MCPWM install interrupt callback function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  IntType:    Select interrupt type.
 * @param[in]  CbFun:      Callback function .
 *
 * @return none
 * @note     :MCPWM_INT_ALL is invalid as input
 */
void Mcpwm_InstallCallBackFunc(Mcpwm_IdType McpwmId, Mcpwm_IntType IntType, Isr_CbFuncType * CbFun);

/** @} end of group Public_FunctionDeclaration */

#endif /* MCPWM_DRV_H */
