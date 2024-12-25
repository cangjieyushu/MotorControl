/**************************************************************************************************/
/**
 * @file      : Adc_Drv.h
 * @brief     : Adc driver module header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef ADC_DRV_H
#define ADC_DRV_H

#include "Common_Drv.h"

/** @defgroup Public_MacroDefinition
 *  @{
 */

/** @} end of group Public_MacroDefinition */

/** @defgroup Public_TypeDefinition 
 *  @{
 */
/**
 *  @brief Adc Group Type Definition
 */
typedef enum
{
    ADC0_GROUP_0 = 0U,         /*!< Adc group 0 */
    ADC0_GROUP_1               /*!< Adc group 1 */
} Adc_GroupType;

/**
 *  @brief Adc Hardware Average Select Type Definition
 */
typedef enum
{
    ADC_AVGS_DISABLED = 0U,    /*!< ADC average function is disabled, single conversion */
    ADC_AVGS_2,                /*!< the number of ADC conversions which are averaged  is 2 */
    ADC_AVGS_4,                /*!< the number of ADC conversions which are averaged  is 4 */
    ADC_AVGS_8,                /*!< the number of ADC conversions which are averaged  is 8 */
    ADC_AVGS_16                /*!< the number of ADC conversions which are averaged  is 16 */
} Adc_AverageType;

/**
 *  @brief Adc Trigger Mode Type definition
 */
typedef enum
{
    ADC_TRIGGER_LOOP_MODE = 0U,     /*!< Loop mode. */
    ADC_TRIGGER_MAP_MODE,           /*!< Map mode. */
    ADC_TRIGGER_MIX_MODE            /*!< Loop/map mix mode. */
} Adc_TriggerModeType;

/**  
 *  @brief Adc Group0 Cmd Type Definition
 */
typedef enum
{
    ADC_GROUP0_CMD0 = 0U,                /*!< Cmd 0 */
    ADC_GROUP0_CMD1,                     /*!< Cmd 1 */
    ADC_GROUP0_CMD2,                     /*!< Cmd 2 */
    ADC_GROUP0_CMD3,                     /*!< Cmd 3 */
    ADC_GROUP0_CMD4,                     /*!< Cmd 4 */
    ADC_GROUP0_CMD5,                     /*!< Cmd 5 */
    ADC_GROUP0_CMD6,                     /*!< Cmd 6 */
    ADC_GROUP0_CMD7                      /*!< Cmd 7 */
} Adc_Group0CmdType;

/**  
 *  @brief Adc Group0 Map Trigger Cmd Type Definition
 */
typedef enum
{
    ADC_MAP_TRIGGER_CMD0 = 0U,                /*!< Group0 map trigger Cmd 0 */
    ADC_MAP_TRIGGER_CMD1,                     /*!< Group0 map trigger Cmd 1 */
    ADC_MAP_TRIGGER_CMD2                      /*!< Group0 map trigger Cmd 2 */
} Adc_MapTriggerType;

/**  
 *  @brief Adc Group0 Channels (All Channels) Type Definition
 */
typedef enum
{
    ADC_GROUP0_ADC0_CH0 = 0U,                     /*!< External ADC0_CH0 */
    ADC_GROUP0_ADC0_CH1,                          /*!< External ADC0_CH1 */
    ADC_GROUP0_ADC0_CH2,                          /*!< External ADC0_CH2 */
    ADC_GROUP0_ADC0_CH3,                          /*!< External ADC0_CH3 */
    ADC_GROUP0_ADC0_CH4,                          /*!< External ADC0_CH4 */
    ADC_GROUP0_ADC0_CH5,                          /*!< External ADC0_CH5 */
    ADC_GROUP0_ADC0_CH6,                          /*!< External ADC0_CH6 */
    ADC_GROUP0_ADC0_CH7,                          /*!< External ADC0_CH7 */
    ADC_GROUP0_ADC0_CH8,                          /*!< External ADC0_CH8 */
    ADC_GROUP0_VS = 16U,                          /*!< Internal VS */
    ADC_GROUP0_VDDP,                              /*!< Internal VDDP */
    ADC_GROUP0_MON,                               /*!< Internal MON */
    ADC_GROUP0_VSD,                               /*!< Internal VSD */
    ADC_GROUP0_VCP,                               /*!< Internal VCP */
    ADC_GROUP0_VDH,                               /*!< Internal VDH */
    ADC_GROUP0_VDDC_SW,                           /*!< Internal VDDC_SW */
    ADC_GROUP0_PMU_TEMPER,                        /*!< Internal PMU Temper Sensor */
    ADC_GROUP0_GDU_TEMPER,                        /*!< Internal GDU Temper Sensor */
    ADC_GROUP0_LIN_TEMPER,                        /*!< Internal LIN Temper Sensor */
    ADC_GROUP0_GND_REF,                           /*!< Internal GND_REF */
    ADC_GROUP0_PMU_VBG0,                          /*!< Internal PMU VBG0 */
    ADC_GROUP0_ATB,                               /*!< Internal ATB */
    ADC_GROUP0_DAC,                               /*!< Internal 8bit DAC */
    ADC_GROUP0_VDDC_AON,                          /*!< Internal VDDC_AON */
    ADC_GROUP0_VAREF                              /*!< Internal VAREF */
} Adc_Group0ChannelType;

/**  
 *  @brief Adc Group1 Sequences Type Definition
 */
typedef enum
{
    ADC_GROUP1_SEQUENCE0 = 0U,                         /*!< Adc Group1 Sequence0 */
    ADC_GROUP1_SEQUENCE1,                              /*!< Adc Group1 Sequence1 */
    ADC_GROUP1_SEQUENCE2                               /*!< Adc Group1 Sequence2 */
} Adc_Group1SequenceType;

/**  
 *  @brief Adc Group1 Channels (Internal Channels) Type Definition
 */
typedef enum
{
    ADC_GROUP1_VS = 0U,                           /*!< Internal VS */
    ADC_GROUP1_VDDP,                              /*!< Internal VDDP */
    ADC_GROUP1_MON,                               /*!< Internal MON */
    ADC_GROUP1_VSD,                               /*!< Internal VSD */
    ADC_GROUP1_VCP,                               /*!< Internal VCP */
    ADC_GROUP1_VDH,                               /*!< Internal VDH */
    ADC_GROUP1_VDDC_SW,                           /*!< Internal VDDC_SW */
    ADC_GROUP1_PMU_TEMPER,                        /*!< Internal PMU Temper Sensor */
    ADC_GROUP1_GDU_TEMPER,                        /*!< Internal GDU Temper Sensor */
    ADC_GROUP1_LIN_TEMPER,                        /*!< Internal LIN Temper Sensor */
    ADC_GROUP1_GND_REF,                           /*!< Internal GND_REF */
    ADC_GROUP1_PMU_VBG0,                          /*!< Internal PMU VBG0 */
    ADC_GROUP1_ATB,                               /*!< Internal ATB */
    ADC_GROUP1_DAC,                               /*!< Internal 8bit DAC */
    ADC_GROUP1_VDDC_AON,                          /*!< Internal VDDC_AON */
    ADC_GROUP1_VAREF                              /*!< Internal VAREF */
} Adc_Group1ChannelType;

/**  
 *  @brief Adc Internal Channels Can Go Through Buffer Type Definition
 */
typedef enum
{
    ADC_BUFFER_VS = 0U,                           /*!< VS */
    ADC_BUFFER_VDDP,                              /*!< VDDP */
    ADC_BUFFER_MON,                               /*!< MON */
    ADC_BUFFER_VSD,                               /*!< VSD */
    ADC_BUFFER_VCP,                               /*!< VCP */
    ADC_BUFFER_VDH,                               /*!< VDH */
    ADC_BUFFER_VDDC_SW,                           /*!< VDDC_SW */
    ADC_BUFFER_PMU_TEMPER,                        /*!< PMU Temper Sensor */
    ADC_BUFFER_GDU_TEMPER,                        /*!< GDU Temper Sensor */
    ADC_BUFFER_LIN_TEMPER,                        /*!< LIN Temper Sensor */
    ADC_BUFFER_PMU_VBG0 = 11U,                    /*!< PMU VBG0 */
    ADC_BUFFER_ATB,                               /*!< ATB */
    ADC_BUFFER_DAC,                               /*!< 8bit DAC */
    ADC_BUFFER_VDDC_AON,                          /*!< VDDC_AON */
    ADC_BUFFER_PMU_TEMPER_GROUND = 16U,           /*!< PMU Temper Sensor ground */
    ADC_BUFFER_GDU_TEMPER_GROUND,                 /*!< GDU Temper Sensor ground */
    ADC_BUFFER_LIN_TEMPER_GROUND                  /*!< LIN Temper Sensor ground */
} Adc_BufferChannelType;

/**  
 *  @brief Adc Analog Watchdog Channels Filter Coefficient Type Definition
 */
typedef enum
{
    ADC_FILTER_1V2 = 0U,                          /*!< 1/2 weight of current sample */
    ADC_FILTER_1V4,                               /*!< 1/4 weight of current sample */
    ADC_FILTER_1V8,                               /*!< 1/8 weight of current sample */
    ADC_FILTER_1V16                               /*!< 1/16 weight of current sample */
} Adc_FilterCoefficientType;

/**  
 *  @brief Adc Analog Watchdog Channels Type definition
 */
typedef enum
{
    ADC_AWDG_VS = 0U,                           /*!< VS */
    ADC_AWDG_VDDP,                              /*!< VDDP */
    ADC_AWDG_MON,                               /*!< MON */
    ADC_AWDG_VSD,                               /*!< VSD */
    ADC_AWDG_VCP,                               /*!< VCP */
    ADC_AWDG_VDH,                               /*!< VDH */
    ADC_AWDG_VDDC_SW,                           /*!< VDDC_SW */
    ADC_AWDG_PMU_TEMPER,                        /*!< PMU Temper Sensor */
    ADC_AWDG_GDU_TEMPER,                        /*!< GDU Temper Sensor */
    ADC_AWDG_LIN_TEMPER,                        /*!< LIN Temper Sensor */
    ADC_AWDG_VDDC_AON,                          /*!< VDDC_AON */
    ADC_AWDG_USER1,                             /*!< User define channel 1 */
    ADC_AWDG_USER2,                             /*!< User define channel 2 */
    ADC_AWDG_USER3,                             /*!< User define channel 3 */
    ADC_AWDG_USER4                              /*!< User define channel 4 */
} Adc_AwdgChannelType;

/**  
 *  @brief Adc Analog Watchdog Internal Channels Threshold Type definition
 */
typedef enum
{
    ADC_AWDG_VS_OV_L2 = 0U,                     /*!< VS Over Voltage L2 */
    ADC_AWDG_VS_OV_L1,                          /*!< VS Over Voltage L1 */
    ADC_AWDG_VS_UV,                             /*!< VS Under Voltage */
    ADC_AWDG_VDDP_OV,                           /*!< VDDP5V Over Voltage */
    ADC_AWDG_VDDP_UV,                           /*!< VDDP5V Under Voltage */
    ADC_AWDG_MON_OV,                            /*!< HV MON Over Voltage */
    ADC_AWDG_MON_UV,                            /*!< HV MON Under Voltage */
    ADC_AWDG_VSD_OV,                            /*!< VSD Over Voltage */
    ADC_AWDG_VSD_UV,                            /*!< VSD Under Voltage */
    ADC_AWDG_VCP_OV,                            /*!< VCP Over Voltage */
    ADC_AWDG_VCP_UV,                            /*!< VCP Under Voltage */
    ADC_AWDG_VDH_OV,                            /*!< VDH OV */
    ADC_AWDG_VDH_UV,                            /*!< VDH UV */
    ADC_AWDG_VDDC_SW_OV,                        /*!< VDDC1V8 Over Voltage */
    ADC_AWDG_VDDC_SW_UV,                        /*!< VDDC1V8 Under Voltage */
    ADC_AWDG_PMU_OT_WARNING,                    /*!< System OverTemp Warning(PMU) */
    ADC_AWDG_PMU_OT_SHUTDOWN,                   /*!< System OverTemp Shutdown(PMU) */
    ADC_AWDG_GDU_OT_WARNING,                    /*!< GDU OverTemp Warning  */
    ADC_AWDG_GDU_OT_SHUTDOWN,                   /*!< GDU OverTemp Shutdown */
    ADC_AWDG_LIN_OT_WARNING,                    /*!< LIN OverTemp Warning */
    ADC_AWDG_VDDC_AON_OV                        /*!< VDDC AON Over Voltage */
} Adc_AwdgInternalThType;

/**  
 *  @brief Adc Analog Watchdog User Channels Threshold Type definition
 */
typedef enum
{
    ADC_AWDG_USER1_TH = 0U,                     /*!< User define channel 1 threshold */
    ADC_AWDG_USER2_TH,                          /*!< User define channel 2 threshold */
    ADC_AWDG_USER3_TH,                          /*!< User define channel 3 threshold */
    ADC_AWDG_USER4_TH                           /*!< User define channel 4 threshold */
} Adc_AwdgUserThType;

/**  
 *  @brief Adc Analog Watchdog Time Threshold Type definition
 */
typedef enum
{
    ADC_AWDG_MEASURE1 = 0U,                     /*!< 1 measurement */
    ADC_AWDG_MEASURE2,                          /*!< 2 measurement */
    ADC_AWDG_MEASURE4,                          /*!< 4 measurement */
    ADC_AWDG_MEASURE8,                          /*!< 8 measurement */
    ADC_AWDG_MEASURE16,                         /*!< 16 measurement */
    ADC_AWDG_MEASURE32,                         /*!< 32 measurement */
    ADC_AWDG_MEASURE64,                         /*!< 64 measurement */
    ADC_AWDG_MEASURE128                         /*!< 128 measurement */
} Adc_AwdgTimeThType;

/**  
 *  @brief Adc Analog Watchdog Compare Value Select Type definition
 */
typedef enum
{
    ADC_AWDG_SELECT_RAW = 0U,                  /*!< Raw data */
    ADC_AWDG_SELECT_IIR                        /*!< IIR data */
} Adc_AwdgValueSelectType;

/**  
 *  @brief Adc Analog Watchdog Compare Select Type definition
 */
typedef enum
{
    ADC_AWDG_COMPARE_UNDER = 0U,               /*!< Under voltage   */
    ADC_AWDG_COMPARE_OVER                      /*!< Over voltage */
} Adc_AwdgCompareSelectType;

/**
 *  @brief Adc Driver Interrupt definition
 */
typedef enum
{
    ADC_INT_AWDG_UNDER = 0U,  /*!< Analog Watchdog under interrupt Enable */
    ADC_INT_AWDG_OVER,        /*!< Analog Watchdog over interrupt Enable */
    ADC_INT_GRP0_LOOP_SCOM,   /*!< Group0 LOOP Complete Interrupt Enable */
    ADC_INT_GRP0_MAP_SCOM,    /*!< Group0 Map Sequence Complete Interrupt Enable */
    ADC_INT_GRP0_CCOM0,       /*!< Group0 Command0 Complete Interrupt Enable */
    ADC_INT_GRP0_CCOM1,       /*!< Group0 Command1 Complete Interrupt Enable */
    ADC_INT_GRP0_CCOM2,       /*!< Group0 Command2 Complete Interrupt Enable */
    ADC_INT_GRP0_CCOM3,       /*!< Group0 Command3 Complete Interrupt Enable */
    ADC_INT_GRP0_CCOM4,       /*!< Group0 Command4 Complete Interrupt Enable */
    ADC_INT_GRP0_CCOM5,       /*!< Group0 Command5 Complete Interrupt Enable */
    ADC_INT_GRP0_CCOM6,       /*!< Group0 Command6 Complete Interrupt Enable */
    ADC_INT_GRP0_CCOM7,       /*!< Group0 Command7 Complete Interrupt Enable */
    ADC_INT_GRP1_SCOM0,       /*!< Group1 Sequence0 Complete Interrupt Enable */
    ADC_INT_GRP1_SCOM1,       /*!< Group1 Sequence1 Complete Interrupt Enable */
    ADC_INT_GRP1_SCOM2,       /*!< Group1 Sequence2 Complete Interrupt Enable */
    ADC_INT_GRP1_ALL_COM,     /*!< Group1 All Sequence Complete Interrupt Enable */
    ADC_INT_GRP0_LOOP_ABORT,  /*!< Group0 Loop Abort Interrupt Enable */
    ADC_INT_GRP1_LOOP_ABORT,  /*!< Group1 Loop Abort Interrupt Enable */
    ADC_INT_TRIG_CERR,        /*!< Trigger Conflict Error Interrupt Enable */
    ADC_INT_GDU_OT,           /*!< GDU Temperature Sensor Over Shutdown Interrupt Enable */
    ADC_INT_PMU_OT,           /*!< PMU Temperature Sensor Over Shutdown Interrupt Enable */
    ADC_INT_MEAS_TRIG,        /*!< Measure Counter Trig Interrupt Enable  */
    ADC_INT_ALL               /*!< Interrupt Enable All */
} Adc_IntType;

/**
 *  @brief Adc Driver Status definition
 */
typedef enum
{
    ADC_STATUS_DMA_REQ = 0U,     /*!< DMA flag */
    ADC_STATUS_AWDG_FAIL,        /*!< Analog Watchdog nmi flag, indicate VS and LIN over temper live
                                      assert */
    ADC_STATUS_AWDG_UNDER,       /*!< Analog Watchdog under flag */
    ADC_STATUS_AWDG_OVER,        /*!< Analog Watchdog over flag */
    ADC_STATUS_GRP0_LOOP_SCOM,   /*!< Group0 LOOP Complete flag */
    ADC_STATUS_GRP0_MAP_SCOM,    /*!< Group0 Map Sequence Compare flag */
    ADC_STATUS_GRP0_CCOM0,       /*!< Group0 Command0 Complete flag */
    ADC_STATUS_GRP0_CCOM1,       /*!< Group1 Command1 Complete flag */
    ADC_STATUS_GRP0_CCOM2,       /*!< Group2 Command2 Complete flag */
    ADC_STATUS_GRP0_CCOM3,       /*!< Group3 Command3 Complete flag */
    ADC_STATUS_GRP0_CCOM4,       /*!< Group4 Command4 Complete flag */
    ADC_STATUS_GRP0_CCOM5,       /*!< Group5 Command5 Complete flag */
    ADC_STATUS_GRP0_CCOM6,       /*!< Group6 Command6 Complete flag */
    ADC_STATUS_GRP0_CCOM7,       /*!< Group7 Command7 Complete flag */
    ADC_STATUS_GRP1_SCOM0,       /*!< Group1 Sequence0 Complete flag */
    ADC_STATUS_GRP1_SCOM1,       /*!< Group1 Sequence1 Complete flag */
    ADC_STATUS_GRP1_SCOM2,       /*!< Group1 Sequence2 Complete flag */
    ADC_STATUS_GRP1_ALL_COM,     /*!< Group1 All Sequence Complete flag */
    ADC_STATUS_GRP0_LOOP_ABORT,  /*!< Group0 Loop Abort flag */
    ADC_STATUS_GRP1_LOOP_ABORT,  /*!< Group1 Loop Abort flag */
    ADC_STATUS_TRIG_CERR,        /*!< Trigger Conflict Error flag */
    ADC_STATUS_GDU_OT,           /*!< GDU Temperature Sensor Over Shutdown flag */
    ADC_STATUS_PMU_OT,           /*!< PMU Temperature Sensor Over Shutdown flag */
    ADC_STATUS_MEAS_TRIG,        /*!< Measure Counter Trig flag  */
    ADC_STATUS_PMU_DIS,          /*!< PMU Disable ADC Flag */
    ADC_STATUS_GRP0_BUSY,        /*!< Group 0 is Busy Flag */
    ADC_STATUS_GRP1_BUSY,        /*!< Group 1 is Busy Flag */
    ADC_STATUS_SAR_BUSY,         /*!< SAR Logic is Busy Flag */
    ADC_STATUS_PWON,             /*!< Adc Analog part power on Flag */
    ADC_STATUS_ALL               /*!< flag All */
} Adc_StatusType;

/**  
 *  @brief Adc Self Test Voltage Type definition
 */
typedef enum
{
    ADC_SELF_TEST_VOLTAGE_LOW = 0U,               /*!< Low voltage will be sample in self test */
    ADC_SELF_TEST_VOLTAGE_HIGH                    /*!< High voltage will be sample in self test */
} Adc_SelfTestVoltageType;

/**
 *  @brief ADC Temperature Sensor Calibration Type Definition
 */
typedef enum
{
    ADC_TS_CAL_LIN = 0U,               /*!< LIN TS calibration enable */
    ADC_TS_CAL_GDU,                    /*!< GDU TS calibration enable  */
    ADC_TS_CAL_PMU                     /*!< PMU TS calibration enable  */
} Adc_TsCalibrationType;

/**
 *  @brief Adc configuration structure type definition
 */
typedef struct
{
    Common_ControlStateType BufferOffsetEn;    /* Adc Buffer Offset Calibration Enable */
    Common_ControlStateType ClockDividerEn;    /* Function Clock Divider Enable, if enable function
                                                  clock is divided by 2 from bus clock */
    Common_ControlStateType HardWareTriggerEn; /* HardWare Trigger Enable */
    Common_ControlStateType DigitalFastModeEn; /* Digital Fast Mode Enable */
    Common_ControlStateType AnalogFastModeEn;  /* Analog part Fast Mode Enable */
    uint16 StableTime;    /*!< Adc analog part startup to stable time */
} Adc_ConfigType;

/**
 *  @brief Adc Sample Input Time configuration structure type definition
 */
typedef struct
{
    uint16 ExternalTime0; /*!< Sample Input time for External Channel 0. Sample stable time from 
    input to ready for conversion. The time is calculated as (n+3) Function CLKs. The same below. */
    uint16 ExternalTime1; /*!< Sample Input time for External Channel 1. */
    uint16 ExternalTime2; /*!< Sample Input time for External Channel 2. */
    uint16 ExternalTime3; /*!< Sample Input time for External Channel 3. */
    uint16 ExternalTime4; /*!< Sample Input time for External Channel 4. */
    uint16 ExternalTime5; /*!< Sample Input time for External Channel 5. */
    uint16 ExternalTime6; /*!< Sample Input time for External Channel 6. */
    uint16 ExternalTime7; /*!< Sample Input time for External Channel 7. */
    uint16 ExternalTime8; /*!< Sample Input time for External Channel 8. */
    uint16 InternalTime0; /*!< Sample Input time for Internal monitor channels(CH16~CH21) */
    uint16 InternalTime1; /*!< Sample Input time for Internal monitor channels(GNDREF, VAREF, 
                               VDDC_AON, VDDC_SW) */
    uint16 InternalTime2; /*!< Sample Input time for Internal monitor channels(Temper sensor) */
    uint16 InternalTime3; /*!< Sample Input time for Internal monitor channels(BG, DAC) */
    uint16 InternalTime4; /*!< Sample Input time for Internal monitor channels(SenseBUs) */
} Adc_TimeConfigType;


/**
 *  @brief Adc Group0 Configuration Structure Type Definition
 */
typedef struct
{
    Common_ControlStateType DataMask;    /*!< Result read mask, if enabled only can read Data */ 
    Adc_AverageType AverageSelect;       /*!< Hardware average select, select how many Adc 
                                              conversions are averaged to create the Adc result */
    Adc_TriggerModeType TriggerMode;     /*!< Select Adc trigger mode */
    uint16 LoopDepth;                    /*!< Set the depth of loop mode */
    Adc_Group0ChannelType Group0Cmd0;    /* Cmd 0, user could select channel num */
    Adc_Group0ChannelType Group0Cmd1;    /* Cmd 1, user could select channel num */
    Adc_Group0ChannelType Group0Cmd2;    /* Cmd 2, user could select channel num */
    Adc_Group0ChannelType Group0Cmd3;    /* Cmd 3, user could select channel num */
    Adc_Group0ChannelType Group0Cmd4;    /* Cmd 4, user could select channel num */
    Adc_Group0ChannelType Group0Cmd5;    /* Cmd 5, user could select channel num */
    Adc_Group0ChannelType Group0Cmd6;    /* Cmd 6, user could select channel num */
    Adc_Group0ChannelType Group0Cmd7;    /* Cmd 7, user could select channel num */
    Common_ControlStateType MapSelect0;  /* Choose whether to include command 0 in map sequency. 
                                    Does not affect triggering, but affects MAP_SCOM status */
    Common_ControlStateType MapSelect1;  /* Choose whether to include command 1 in map sequency. 
                                    Does not affect triggering, but affects MAP_SCOM status */
    Common_ControlStateType MapSelect2;  /* Choose whether to include command 2 in map sequency. 
                                    Does not affect triggering, but affects MAP_SCOM status */
} Adc_Group0ConfigType;

/**
 *  @brief Adc Analog Watchdog Internal Channel configuration structure type definition
 */
typedef struct
{
    uint16 CompareValue;                 /* Compare Value */
    Adc_AwdgTimeThType TimeThreshold;    /* Time Threshold */
    Adc_AwdgValueSelectType ValueSelect; /* Compare Value Select */
} Adc_AwdgInternalConfigType;

/**
 *  @brief Adc Analog Watchdog User Channel configuration structure type definition
 */
typedef struct
{
    uint16 CompareValue;                     /* Compare Value */
    Adc_AwdgTimeThType TimeThreshold;        /* Time Threshold */
    Adc_AwdgCompareSelectType CompareSelect; /* Compare Over or Under */
    Adc_AwdgValueSelectType ValueSelect;     /* Compare Value Select */
    uint8 ChannelSelect;/* Channel ID selected for this user anawdog, any channel can be selected. 
                     But suggest not select channels already monitored by other analog watchdog */
    Common_ControlStateType AwdgEnable;      /* Analog Watchdog Enable */
} Adc_AwdgUserConfigType;

/**
 *  @brief Adc Measure Trigger configuration structure type definition
 */
typedef struct
{
    uint16 ReloadValue;                     /* Measure Timer Reload Value */
    Common_ControlStateType TriggerEnable;  /* Measure Trigger Output Enable */
} Adc_MeasureConfigType;

/**
 *  @brief Adc Measure Trigger configuration structure type definition
 */
typedef struct
{
    uint8 CapSelect;   /* Cap select, every num indicate a cap is selected in self test */
    Adc_SelfTestVoltageType VoltageSelect;     /* Adc sample VREFH or VREFL select */
    Common_ControlStateType TestEnable;        /* Adc Self Test Mode Enable */
} Adc_SelfTestConfigType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */
/**
 * @brief      Adc Config Self Test Function
 *
 * @param[in]  Config: Pointer to a Self Test configuration structure.
 *
 * @return     None
 *
 */
void Adc_ConfigSelfTest(const Adc_SelfTestConfigType * Config);

/**
 * @brief      Adc Config Measure Timer Function
 *
 * @param[in]  Config: Pointer to a Measure Module configuration structure.
 *
 * @return     None
 *
 */
void Adc_ConfigMeasureTimer(const Adc_MeasureConfigType * Config);

/**
 * @brief      Adc Start Or Stop Measure Timer Function
 *
 * @param[in]  Cmd: Select Disable Or Enable.
 *              - COMMON_DISABLE: Stop measuring timer.
 *              - COMMON_ENABLE: Start measuring timer.
 *
 * @return     None
 *
 */
void Adc_EnableMeasureTimer(Common_ControlStateType Cmd);

/**
 * @brief      Adc Generate Measure Interrupt Or Flag Function
 *
 * @param[in]  None.
 *
 * @return     None
 *
 */
void Adc_GenerateMeasureFlag(void);

/**
 * @brief      Adc Enable Function
 *
 * @param[in]  None.
 *
 * @return     Result Status:
 *              - COMMON_SUCC: Adc Enable Success
 *              - COMMON_ERR: ADC Enable Failed
 */
Common_ResultStatusType Adc_Enable(void);

/**
 * @brief      Adc Disable Function
 *
 * @param[in]  None.
 *
 * @return     None
 *
 */
void Adc_Disable(void);

/**
 * @brief      Adc Software Reset Function
 *
 * @param[in]  None.
 *
 * @return     None
 *
 */
void Adc_ResetSw(void);

/**
 * @brief      Adc Reset(Terminate) Loop For Group Sequence Conversion Function
 *
 * @param[in]  GroupType: Select the Group Type.
 *              - ADC0_GROUP_0
 *              - ADC0_GROUP_1
 *
 * @return     None
 *
 */
void Adc_ResetGroupLoop(Adc_GroupType GroupType);

/**
 * @brief      Adc Software Trigger Loop For Group Sequence Conversion Function
 *
 * @param[in]  GroupType: Select the Group Type.
 *              - ADC0_GROUP_0
 *              - ADC0_GROUP_1
 *
 * @return     None
 *
 */
void Adc_TriggerSwLoop(Adc_GroupType GroupType);

/**
 * @brief      Adc Software Trigger Map For Group0 Conversion Function
 *
 * @param[in]  MapTriggerType: Select the Map Trigger Type.
 *              - ADC_MAP_TRIGGER_CMD0
 *              - ADC_MAP_TRIGGER_CMD1
 *              - ADC_MAP_TRIGGER_CMD2
 *
 * @return     None
 *
 */
void Adc_TriggerSwMap(Adc_MapTriggerType MapTriggerType);

/**
 * @brief      Adc Config Function
 *
 * @param[in]  Config: Pointer to a configuration structure.
 *
 * @return     None
 *
 */
void Adc_Config(const Adc_ConfigType * Config);

/**
 * @brief      Adc Config Sample Input Time Function
 *
 * @param[in]  TimeConfig: Pointer to a Sample Input Time configuration structure.
 *
 * @return     None
 *
 */
void Adc_ConfigSampleTime(const Adc_TimeConfigType * TimeConfig);

/**
 * @brief      Adc Set Channel Buffer Disable Or Enable Function
 *
 * @param[in]  ChannelType: Select the Buffer Channel Type.
 *              - ADC_BUFFER_VS
 *              - ADC_BUFFER_VDDP
 *              - ADC_BUFFER_MON
 *              - ADC_BUFFER_VSD
 *                ...
 *              - ADC_BUFFER_PMU_TEMPER_GROUND
 *              - ADC_BUFFER_GDU_TEMPER_GROUND
 *              - ADC_BUFFER_LIN_TEMPER_GROUND
 * @param[in]  Cmd: Select Disable Or Enable.
 *              - COMMON_DISABLE
 *              - COMMON_ENABLE
 *
 * @return     None
 *
 */
void Adc_EnableChannelBuffer(Adc_BufferChannelType ChannelType, Common_ControlStateType Cmd);

/**
 * @brief      Adc Get Channel Buffer Status Function
 *
 * @param[in]  ChannelType: Select the Buffer Channel Type.
 *              - ADC_BUFFER_VS
 *              - ADC_BUFFER_VDDP
 *              - ADC_BUFFER_MON
 *              - ADC_BUFFER_VSD
 *                ...
 *              - ADC_BUFFER_PMU_TEMPER_GROUND
 *              - ADC_BUFFER_GDU_TEMPER_GROUND
 *              - ADC_BUFFER_LIN_TEMPER_GROUND
 *
 * @return     Common_ControlStateType: Channel Buffer Disable Or Enable.
 *              - COMMON_DISABLE
 *              - COMMON_ENABLE
 */
Common_ControlStateType Adc_GetChannelBufferStatus(Adc_BufferChannelType ChannelType);

/**
 * @brief      Adc Set Buffer Calibration Offset Value Function
 *
 * @param[in]  OffsetValue: Adc buffer calibration offset Value.
 *
 * @return     None
 *
 */
void Adc_SetBufferOffsetValue(sint16 OffsetValue);

/**
 * @brief      Adc Get Buffer Calibration Offset Value Function
 *
 * @param[in]  None.
 *
 * @return     int16: Adc buffer calibration offset Value.
 *
 */
sint16 Adc_GetBufferOffsetValue(void);

/**
 * @brief      Adc Config Group0 Function
 *
 * @param[in]  Group0Config: Pointer to a group0 configuration structure.
 *
 * @return     Result Status:
 *              - COMMON_SUCC: Loop Depth Correct
 *              - COMMON_ERR: Loop Depth Error
 */
Common_ResultStatusType Adc_ConfigGroup0(const Adc_Group0ConfigType * Group0Config);

/**
 * @brief      Adc Get Group0 One Cmd Result Function
 *
 * @param[in]  CmdType: Select Read Group0 Cmd Type.
 *              - ADC_GROUP0_CMD0
 *              - ADC_GROUP0_CMD1
 *              - ADC_GROUP0_CMD2
 *              - ADC_GROUP0_CMD3
 *              - ADC_GROUP0_CMD4
 *              - ADC_GROUP0_CMD5
 *              - ADC_GROUP0_CMD6
 *              - ADC_GROUP0_CMD7
 * @param[out] Result: Pointer to where to store the Result.
 *
 * @return     Result Status:
 *              - COMMON_SUCC: Result Valid
 *              - COMMON_ERR: Result Overrun Or No New Valid Data Available
 */
Common_ResultStatusType Adc_GetGroup0CmdResult(Adc_Group0CmdType CmdType, uint32 * Result);

/**
 * @brief      Adc Get Group0 Cmds Result Function
 *
 * @param[in]  CmdNumber: Select Read Group0 Cmds Number.
 * @param[out] Result: Pointer to where to store the Result.
 *
 * @return     Result Status:
 *              - COMMON_SUCC: Result Valid
 *              - COMMON_ERR: Result Overrun Or No New Valid Data Available Or CmdNumber Error
 */
Common_ResultStatusType Adc_GetGroup0CmdsResult(uint8 CmdNumber, uint32 * Result);

/**
 * @brief      Adc Enable Group1 Sequence Channels Function
 *
 * @param[in]  SequenceType: Select the Group1 Sequence Type.
 *              - ADC_GROUP1_SEQUENCE0
 *              - ADC_GROUP1_SEQUENCE1
 *              - ADC_GROUP1_SEQUENCE2
 * @param[in]  ChannelNumber: Number of enabled channels.
 * @param[in]  ChannelType: Pointing to the set channels type.
 *
 * @return     None
 *
 */
void Adc_EnableGroup1Sequence(Adc_Group1SequenceType SequenceType, uint8 ChannelNumber,
                               const Adc_Group1ChannelType * ChannelType);

/**
 * @brief      Adc Disable Group1 Sequence Channels Function
 *
 * @param[in]  SequenceType: Select the Group1 Sequence Type.
 *              - ADC_GROUP1_SEQUENCE0
 *              - ADC_GROUP1_SEQUENCE1
 *              - ADC_GROUP1_SEQUENCE2
 * @param[in]  ChannelNumber: Number of enabled channels.
 * @param[in]  ChannelType: Pointing to the set channels type.
 *
 * @return     None
 *
 */
void Adc_DisableGroup1Sequence(Adc_Group1SequenceType SequenceType, uint8 ChannelNumber,
                               const Adc_Group1ChannelType * ChannelType);

/**
 * @brief      Adc Get Group1 Sequence Channel Status Function
 *
 * @param[in]  SequenceType: Select the Group1 Sequence Type.
 *              - ADC_GROUP1_SEQUENCE0
 *              - ADC_GROUP1_SEQUENCE1
 *              - ADC_GROUP1_SEQUENCE2
 * @param[in]  ChannelType: Select the Group1 Channel Type.
 *              - ADC_GROUP1_VS
 *              - ADC_GROUP1_VDDP
 *              - ADC_GROUP1_MON
 *                ...
 *              - ADC_GROUP1_DAC
 *              - ADC_GROUP1_VDDC_AON
 *              - ADC_GROUP1_VAREF
 *
 * @return     Common_ControlStateType: Group1 Channel Disable Or Enable.
 *              - COMMON_DISABLE
 *              - COMMON_ENABLE
 */
Common_ControlStateType Adc_GetGroup1SequenceStatus(Adc_Group1SequenceType SequenceType, 
                                                       Adc_Group1ChannelType ChannelType);

/**
 * @brief      Adc Get Group1 One Channel Raw Result Function
 *
 * @param[in]  ChannelType: Select Read Group1 Channel Type.
 *              - ADC_GROUP1_VS
 *              - ADC_GROUP1_VDDP
 *              - ADC_GROUP1_MON
 *                ...
 *              - ADC_GROUP1_DAC
 *              - ADC_GROUP1_VDDC_AON
 *              - ADC_GROUP1_VAREF
 * @param[out] Result: Pointer to where to store the Result.
 *
 * @return     None
 *
 */
void Adc_GetGroup1ChannelRawResult(Adc_Group1ChannelType ChannelType, uint32 * Result);

/**
 * @brief      Adc Get Group1 Channels Raw Result Function
 *
 * @param[in]  CmdNumber: Select Read Group1 Channels Number.
 * @param[out] Result: Pointer to where to store the Result.
 *
 * @return     Result Status:
 *              - COMMON_SUCC: Result Valid
 *              - COMMON_ERR: CmdNumber Error
 */
Common_ResultStatusType Adc_GetGroup1ChannelsRawResult(uint8 CmdNumber, uint32 * Result);

/**
 * @brief      Adc Get Analog Watchdog One Channel Iir Result Function
 *
 * @param[in]  ChannelType: Select Read Analog Watchdog Channel Type.
 *              - ADC_AWDG_VS
 *              - ADC_AWDG_VDDP
 *              - ADC_AWDG_MON
 *                ...
 *              - ADC_AWDG_USER2
 *              - ADC_AWDG_USER3
 *              - ADC_AWDG_USER4
 * @param[out] Result: Pointer to where to store the Result.
 *
 * @return     None
 *
 */
void Adc_GetAwdgChannelIirResult(Adc_AwdgChannelType ChannelType, uint32 * Result);

/**
 * @brief      Adc Get Analog Watchdog Channels Iir Result Function
 *
 * @param[in]  CmdNumber: Select Read Analog Watchdog Channels Number.
 * @param[out] Result: Pointer to where to store the Result.
 *
 * @return     Result Status:
 *              - COMMON_SUCC: Result Valid
 *              - COMMON_ERR: CmdNumber Error
 */
Common_ResultStatusType Adc_GetAwdgChannelsIirResult(uint8 CmdNumber, uint32 * Result);

/**
 * @brief      Adc Set Analog Watchdog One Channel Iir Result Function
 *
 * @param[in]  ChannelType: Select Analog Watchdog Channel Type.
 *              - ADC_AWDG_VS
 *              - ADC_AWDG_VDDP
 *              - ADC_AWDG_MON
 *                ...
 *              - ADC_AWDG_USER2
 *              - ADC_AWDG_USER3
 *              - ADC_AWDG_USER4
 * @param[in]  Result: Result To Set.
 *
 * @return     None
 *
 */
void Adc_SetAwdgChannelIirResult(Adc_AwdgChannelType ChannelType, uint32 Result);

/**
 * @brief      Adc Set Analog Watchdog Channels Iir Result Function
 *
 * @param[in]  CmdNumber: Select Analog Watchdog Channels Number.
 * @param[in]  Result: Pointer to where to store the Result.
 *
 * @return     Result Status:
 *              - COMMON_SUCC: Result Valid
 *              - COMMON_ERR: CmdNumber Error
 */
Common_ResultStatusType Adc_SetAwdgChannelsIirResult(uint8 CmdNumber, uint32 * Result);

/**
 * @brief      Adc Set Analog Watchdog Channel Filter Coefficient B0 Function
 *
 * @param[in]  ChannelType: Select Analog Watchdog Channel Type.
 *              - ADC_AWDG_VS
 *              - ADC_AWDG_VDDP
 *              - ADC_AWDG_MON
 *                ...
 *              - ADC_AWDG_USER2
 *              - ADC_AWDG_USER3
 *              - ADC_AWDG_USER4
 * @param[in]  CoeffType: Select Filter Coefficient Type.
 *              - ADC_FILTER_1V2
 *              - ADC_FILTER_1V4
 *              - ADC_FILTER_1V8
 *              - ADC_FILTER_1V16
 *
 * @return     None
 *
 */
void Adc_SetAwdgChannelFilterCoeff(Adc_AwdgChannelType ChannelType,
                                                        Adc_FilterCoefficientType CoeffType);

/**
 * @brief      Adc Get Analog Watchdog Channel Filter Coefficient B0 Function
 *
 * @param[in]  ChannelType: Select Analog Watchdog Channel Type.
 *              - ADC_AWDG_VS
 *              - ADC_AWDG_VDDP
 *              - ADC_AWDG_MON
 *                ...
 *              - ADC_AWDG_USER2
 *              - ADC_AWDG_USER3
 *              - ADC_AWDG_USER4
 *
 * @return     Adc_FilterCoefficientType: Filter Coefficient Type.
 *              - ADC_FILTER_1V2
 *              - ADC_FILTER_1V4
 *              - ADC_FILTER_1V8
 *              - ADC_FILTER_1V16
 */
Adc_FilterCoefficientType Adc_GetAwdgChannelFilterCoeff(Adc_AwdgChannelType ChannelType);

/**
 * @brief      Adc Config Analog Watchdog Internal Channel Threshold Function
 *
 * @param[in]  InternalType: Select Analog Watchdog Internal Channel Threshold Type.
 *              - ADC_AWDG_VS_OV_L2
 *              - ADC_AWDG_VS_OV_L1
 *              - ADC_AWDG_VS_UV
 *                ...
 *              - ADC_AWDG_GDU_OT_SHUTDOWN
 *              - ADC_AWDG_LIN_OT_WARNING
 *              - ADC_AWDG_VDDC_AON_OV
 * @param[in]  Config: Pointer to a Analog Watchdog Internal Channel Threshold config structure.
 *
 * @return     None
 *
 */
void Adc_ConfigAwdgInternal(Adc_AwdgInternalThType InternalType,
                                              const Adc_AwdgInternalConfigType * Config);

/**
 * @brief      Adc Get Analog Watchdog Internal Compare Select Type Function
 *
 * @param[in]  InternalType: Select Analog Watchdog Internal Channel Threshold Type.
 *              - ADC_AWDG_VS_OV_L2
 *              - ADC_AWDG_VS_OV_L1
 *              - ADC_AWDG_VS_UV
 *                ...
 *              - ADC_AWDG_GDU_OT_SHUTDOWN
 *              - ADC_AWDG_LIN_OT_WARNING
 *              - ADC_AWDG_VDDC_AON_OV
 *
 * @return     Adc_AwdgCompareSelectType: Compare Select Type
 *              - ADC_AWDG_COMPARE_UNDER
 *              - ADC_AWDG_COMPARE_OVER
 */
Adc_AwdgCompareSelectType Adc_GetAwdgInternalCompareType(Adc_AwdgInternalThType InternalType);

/**
 * @brief      Adc Config Analog Watchdog User Channel Threshold Function
 *
 * @param[in]  UserType: Select Analog Watchdog User Channel Threshold Type.
 *              - ADC_AWDG_USER1_TH
 *              - ADC_AWDG_USER2_TH
 *              - ADC_AWDG_USER3_TH
 *              - ADC_AWDG_USER4_TH
 * @param[in]  Config: Pointer to a Analog Watchdog User Channel Threshold config structure.
 *
 * @return     None
 *
 */
void Adc_ConfigAwdgUser(Adc_AwdgUserThType UserType,
                                              const Adc_AwdgUserConfigType * Config);

/**
 * @brief      Adc Get Analog Watchdog Internal Channel Threshold Status Function
 *
 * @param[in]  InternalType: Select Analog Watchdog Internal Channel Threshold Type.
 *              - ADC_AWDG_VS_OV_L2
 *              - ADC_AWDG_VS_OV_L1
 *              - ADC_AWDG_VS_UV
 *                ...
 *              - ADC_AWDG_GDU_OT_SHUTDOWN
 *              - ADC_AWDG_LIN_OT_WARNING
 *              - ADC_AWDG_VDDC_AON_OV
 *
 * @return     Common_FlagStatusType: Status
 *              - COMMON_RESET
 *              - COMMON_SET
 */
Common_FlagStatusType Adc_GetAwdgInternalStatus(Adc_AwdgInternalThType InternalType);

/**
 * @brief      Adc Get Analog Watchdog User Channel Threshold Status Function
 *
 * @param[in]  UserType: Select Analog Watchdog User Channel Threshold Type.
 *              - ADC_AWDG_USER1_TH
 *              - ADC_AWDG_USER2_TH
 *              - ADC_AWDG_USER3_TH
 *              - ADC_AWDG_USER4_TH
 *
 * @return     Common_FlagStatusType: Status
 *              - COMMON_RESET
 *              - COMMON_SET
 */
Common_FlagStatusType Adc_GetAwdgUserStatus(Adc_AwdgUserThType UserType);

/**
 * @brief      Adc Dma Request Command Function
 *
 * @param[in]  Cmd: Select Disable Or Enable.
 *              - COMMON_DISABLE
 *              - COMMON_ENABLE
 *
 * @return     None
 *
 */
void Adc_EnableDmaRequest(Common_ControlStateType Cmd);

/**
 * @brief      Adc Temperature Calibration Command Function
 *
 * @param[in]  Type: Select Temperature Calibration Type.
 *              - ADC_TS_CAL_LIN
 *              - ADC_TS_CAL_GDU
 *              - ADC_TS_CAL_PMU
 * @param[in]  Cmd: Select Disable Or Enable.
 *              - COMMON_DISABLE
 *              - COMMON_ENABLE
 *
 * @return     None
 *
 */
void Adc_EnableTemperatureCalibration(Adc_TsCalibrationType Type, Common_ControlStateType Cmd);

/**
 * @brief      Adc Set Temperature Calibration Offset Value Function
 *
 * @param[in]  Type: Select Temperature Calibration Type.
 *              - ADC_TS_CAL_LIN
 *              - ADC_TS_CAL_GDU
 *              - ADC_TS_CAL_PMU
 * @param[in]  OffsetValue: Adc Temperature calibration offset Value.
 *
 * @return     None
 *
 */
void Adc_SetTemperatureOffsetValue(Adc_TsCalibrationType Type, sint16 OffsetValue);

/**
 * @brief      Adc Get Temperature Calibration Offset Value Function
 *
 * @param[in]  Type: Select Temperature Calibration Type.
 *              - ADC_TS_CAL_LIN
 *              - ADC_TS_CAL_GDU
 *              - ADC_TS_CAL_PMU
 *
 * @return     int16: Adc Temperature calibration offset Value.
 *
 */
sint16 Adc_GetTemperatureOffsetValue(Adc_TsCalibrationType Type);

/**
 * @brief      Adc Get Status Function
 *
 * @param[in]  StatusType: Select Status Type.
 *              - ADC_STATUS_DMA_REQ
 *              - ADC_STATUS_AWDG_NMI
 *              - ADC_STATUS_AWDG_UNDER
 *                ...
 *              - ADC_STATUS_SAR_BUSY
 *              - ADC_STATUS_PWON
 *              - ADC_STATUS_ALL
 *
 * @return     Common_FlagStatusType: Status
 *              - COMMON_RESET
 *              - COMMON_SET
 */
Common_FlagStatusType Adc_GetStatus(Adc_StatusType StatusType);

/**
 * @brief      Adc Set Status Flag Disable Or Enable Function
 *
 * @param[in]  IntType: Select Int type.
 *              - ADC_INT_AWDG_UNDER,
 *              - ADC_INT_AWDG_OVER
 *                ...
 *              - ADC_INT_TRIG_CERR
 *              - ADC_INT_MEAS_TRIG
 *              - ADC_INT_ALL
 * @param[in]  Cmd: Select Disable Or Enable.
 *              - COMMON_DISABLE
 *              - COMMON_ENABLE
 *
 * @return     Result Status:
 *              - COMMON_SUCC: Flag set successfully
 *              - COMMON_ERR: The flag does not need to be set
 */
Common_ResultStatusType Adc_EnableStatusFlag(Adc_IntType IntType, Common_ControlStateType Cmd);

/**
 * @brief      Adc Set INT Mask/Unmask Function
 *
 * @param[in]  IntType: Select Int type.
 *              - ADC_INT_AWDG_UNDER,
 *              - ADC_INT_AWDG_OVER
 *                ...
 *              - ADC_INT_TRIG_CERR
 *              - ADC_INT_MEAS_TRIG
 *              - ADC_INT_ALL
 * @param[in]  IntMask: Mask/Unmask.
 *              - COMMON_UNMASK
 *              - COMMON_MASK
 *
 * @return     None
 *
 */
void Adc_SetIntMask(Adc_IntType IntType, Common_IntMaskType IntMask);

/**
 * @brief      Adc Clear INT Status Function
 *
 * @param[in]  IntType: Select Int type.
 *              - ADC_INT_AWDG_UNDER,
 *              - ADC_INT_AWDG_OVER
 *                ...
 *              - ADC_INT_TRIG_CERR
 *              - ADC_INT_MEAS_TRIG
 *              - ADC_INT_ALL
 *
 * @return     None
 *
 */
void Adc_ClearIntStatus(Adc_IntType IntType);

/**
 * @brief      Adc Get INT status Function
 *
 * @param[in]  IntType: Select Int type.
 *              - ADC_INT_AWDG_UNDER,
 *              - ADC_INT_AWDG_OVER
 *                ...
 *              - ADC_INT_TRIG_CERR
 *              - ADC_INT_MEAS_TRIG
 *              - ADC_INT_ALL
 *
 * @return     IntStatus
 *
 */
Common_IntStatusType Adc_GetIntStatus(Adc_IntType IntType);

/**
 * @brief      Adc install interrupt callback function
 *
 * @param[in]  IntType: Select Int type.
 *              - ADC_INT_AWDG_UNDER,
 *              - ADC_INT_AWDG_OVER
 *                ...
 *              - ADC_INT_TRIG_CERR
 *              - ADC_INT_MEAS_TRIG
 * @param[in]  CbFun: Callback function .
 *
 * @return     None
 *
 */
void Adc_InstallCallBackFunc(Adc_IntType IntType, Isr_CbFuncType * CbFun);

/** @} end of group Public_FunctionDeclaration */

#endif /* ADC_DRV_H */
