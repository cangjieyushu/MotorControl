/**************************************************************************************************/
/**
 * @file     adc_drv.h
 * @brief    ADC driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef ADC_DRV_H
#define ADC_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  ADC
 *  @{
 */

/** @defgroup ADC_Public_Types 
 *  @{
 */

/**
 *  @brief ADC ID type definition
 */
typedef enum
{
    ADC0_ID = 0U,                           /*!< ADC0  */
    ADC1_ID                                 /*!< ADC1  */
} ADC_ID_t;

/**  
 *  @brief ADC differential type definition
 */
typedef enum
{
    ADC_SINGLE_MODE = 0U,                   /*!< Single-Ended Mode Selected */
    ADC_DIFF_MODE                           /*!< Differential Mode Selected */
} ADC_Differential_t;

/**  
 *  @brief ADC resolution type definition
 */
typedef enum
{
    ADC_RESOLUTION_12BIT = 0U,              /*!< ADC 12-bit resolution */
    ADC_RESOLUTION_10BIT,                   /*!< ADC 10-bit resolution */
    ADC_RESOLUTION_8BIT                     /*!< ADC 8-bit resolution */
} ADC_Resolution_t;

/**  
 *  @brief ADC voltage reference source type definition
 */
typedef enum
{
    ADC_VREF_EXTERNAL = 0U,                 /*!< External Vref_H, Vref_L reference */
    ADC_VREF_INTERNAL                       /*!< Internal Vref_H to 5V, Vref_L to 0V reference */
} ADC_VrefSource_t;

/**  
 *  @brief ADC trigger type definition
 */
typedef enum
{
    ADC_NORMAL_SW_TRIGGER  = 0U,            /*!< ADC normal software trigger mode*/
    ADC_NORMAL_HW_TRIGGER  = 1U,            /*!< ADC normal hardware trigger mode*/
    ADC_TDG_TRIGGER        = 2U             /*!< ADC TDG trigger, need config cmd buf*/
} ADC_TriggerMode_t;

/**  
 *  @brief ADC TDG trigger mode type definition
 */
typedef enum
{
    ADC_LOOP_MODE    = 0U,                  /*!< Loop mode for TDG trigger, loop conversion from 
                                                 CMD0 to CMD5*/
    ADC_MAPPING_MODE = 1U                   /*!< Mapping mode for TDG trigger, one trigger triggers 
                                               one cmd buff*/
} ADC_TDGTriggerMode_t;

/**  
 *  @brief ADC conversion type definition
 */
typedef enum
{
    ADC_CONVERSION_SINGLE = 0U,             /*!< ADC single conversion */
    ADC_CONVERSION_CONTINUOUS               /*!< ADC continuous conversions */
} ADC_Conversion_t;

/**  
 *  @brief ADC Positive channel selection definition
 */
typedef enum
{
    ADC_P_CH0  = 0U,                        /*!< Single mode, channel[0] and vssa */
    ADC_P_CH1  = 1U,                        /*!< Single mode, channel[1] and vssa */
    ADC_P_CH2  = 2U,                        /*!< Single mode, channel[2] and vssa */
    ADC_P_CH3  = 3U,                        /*!< Single mode, channel[3] and vssa */
    ADC_P_CH4  = 4U,                        /*!< Single mode, channel[4] and vssa */
    ADC_P_CH5  = 5U,                        /*!< Single mode, channel[5] and vssa */
    ADC_P_CH6  = 6U,                        /*!< Single mode, channel[6] and vssa */
    ADC_P_CH7  = 7U,                        /*!< Single mode, channel[7] and vssa */
    ADC_P_CH8  = 8U,                        /*!< Single mode, channel[8] and vss */
    ADC_P_CH9  = 9U,                        /*!< Single mode, channel[9] and vss */
    ADC_P_CH10 = 10U,                       /*!< Single mode, channel[10] and vss */
    ADC_P_CH11 = 11U,                       /*!< Single mode, channel[11] and vss */
    ADC_P_CH12 = 12U,                       /*!< Single mode, channel[12] and vss */
    ADC_P_CH13 = 13U,                       /*!< Single mode, channel[13] and vss */
    ADC_P_CH14 = 14U,                       /*!< Single mode, channel[14] and vss */
    ADC_P_CH15 = 15U,                       /*!< Single mode, channel[15] and vss */
    ADC_P_CH16 = 16U,                       /*!< Single mode, channel[16] and vss */
    ADC_P_CH17 = 17U,                       /*!< Single mode, channel[17] and vss */
    ADC_P_CH18 = 18U,                       /*!< Single mode, channel[18] and vss */
    ADC_P_CH19 = 19U,                       /*!< Single mode, channel[19] and vss */
    ADC_P_CH20 = 20U,                       /*!< Internal channel, bandgap */
    ADC_P_CH25 = 25U,                       /*!< Internal channel, cmp dac out */
    ADC_P_CH28 = 28U,                       /*!< Internal channel, ldo_core, only for ADC0 */
    ADC_P_CH29 = 29U,                       /*!< Internal channel, ldo_flash, only for ADC0 */
    ADC_P_CH30 = 30U                        /*!< Internal channel, ldo_clk, only for ADC0 */
} ADC_P_Channel_t;

/**  
 *  @brief ADC Negative channel selection definition
 */
typedef enum
{
    ADC_N_CH0 = 0U,                         /*!< Differential mode, P-channel[0] and N-channel[0] */
    ADC_N_CH1,                              /*!< Differential mode, P-channel[1] and N-channel[1] */
    ADC_N_CH2,                              /*!< Differential mode, P-channel[2] and N-channel[2] */
    ADC_N_VSS,                              /*!< Differential mode, P-channel[3] and N-channel[3] */ 
    ADC_N_NONE                              /*!< Single mode, N-channel donn't need to configure  */
} ADC_N_Channel_t;

/**  
 *  @brief ADC conversion average number type definition
 */
typedef enum
{
    ADC_AVGS_DISABLED = 0U,                 /*!< ADC average function is disabled,the number of ADC 
                                                 conversions is 1*/
    ADC_AVGS_4,                             /*!< the number of ADC conversions which are averaged  
                                                 is 4 */
    ADC_AVGS_8,                             /*!< the number of ADC conversions which are averaged  
                                                 is 8 */
    ADC_AVGS_16,                            /*!< the number of ADC conversions which are averaged  
                                                 is 16 */
    ADC_AVGS_32                             /*!< the number of ADC conversions which are averaged  
                                                 is 32 */
} ADC_Average_t;

/**  
 *  @brief ADC compare mode type definition
 */
typedef enum
{
    ADC_COMPARE_MODE_DISABLED = 0U,         /*!< ADC compare disabled */
    ADC_COMPARE_MODE_LESS_CVL,              /*!< ADC compare less than CVL */
    ADC_COMPARE_MODE_GREATER_CVL,           /*!< ADC compare greater than CVL */
    ADC_COMPARE_MODE_EQUAL_CVL,             /*!< ADC compare equal to CVL */
    ADC_COMPARE_MODE_WITHIN_CVL_CVH,        /*!< ADC compare within range [CVL,CVH] */
    ADC_COMPARE_MODE_OUT_OF_RANGE_CVL_CVH   /*!< ADC compare out of range[0,CVL) U (CVH,FULL] */
} ADC_Compare_t;

/**  
 *  @brief ADC interrupt type definition
 */
typedef enum
{
    ADC_FWM_INT    = 0U,                    /*!< ADC fifo watermark interrupt */
    ADC_FOF_INT    = 1U,                    /*!< ADC fifo overflow interrupt */
    ADC_TCOMP_INT  = 2U,                    /*!< ADC complete interrupt */
    ADC_CMP_INT    = 3U,                    /*!< ADC compare interrupt */
    ADC_TC_ERR_INT = 4U,                    /*!< ADC trigger conflict error interrupt*/
    ADC_INT_ALL    = 5U                     /*!< All ADC interrupt flags */
} ADC_INT_t;

/**  
 *  @brief ADC status type definition
 */
typedef enum
{
    ADC_STATUS_FWM_INT = 0U,                /*!< ADC fifo watermark status */
    ADC_STATUS_FOF_INT,                     /*!< ADC fifo overflow status */
    ADC_STATUS_TCOMP_INT,                   /*!< ADC complete interrupt status */
    ADC_STATUS_CMP_INT,                     /*!< ADC compare interrupt status */
    ADC_STATUS_DMA_REQ,                     /*!< ADC dma request status */
    ADC_STATUS_FIFO_RDY,                    /*!< ADC result fifo ready status */
    ADC_STATUS_ACTIVE = 7U,                 /*!< ADC active status, 0: idle; 1: processing a 
                                                 conversion */
    ADC_STATUS_LOOP_IDLE,                   /*!< ADC loop mode state machine return to idle state */
    ADC_STATUS_TC_ERR_INT                   /*!< ADC trigger conflict error */
} ADC_Status_t;

/**  
 *  @brief ADC iref source type definition
 */
typedef enum
{
    ADC_IREF_SELECT_EXTERNAL = 0U,          /*!< ADC IREF External selected*/
    ADC_IREF_SELECT_INTERNAL                /*!< ADC IREF Internal selected*/
} ADC_IrefSource_t;

/**  
 *  @brief ADC CMD Buffer type definition
 */
typedef enum
{
    ADC_CMD_BUFFER_CMD0 = 0U,               /*!< ADC CMD Buffer CMD0*/
    ADC_CMD_BUFFER_CMD1,                    /*!< ADC CMD Buffer CMD1*/
    ADC_CMD_BUFFER_CMD2,                    /*!< ADC CMD Buffer CMD2*/
    ADC_CMD_BUFFER_CMD3,                    /*!< ADC CMD Buffer CMD3*/
    ADC_CMD_BUFFER_CMD4,                    /*!< ADC CMD Buffer CMD4*/
    ADC_CMD_BUFFER_CMD5                     /*!< ADC CMD Buffer CMD5*/
} ADC_CmdBuffer_t;

/**  
 *  @brief ADC Gain Trim definition
 */
typedef enum
{
    ADC_GAIN_TRIM0 = 0U,                    /*!< ADC Gain Trim1*/
    ADC_GAIN_TRIM1                          /*!< ADC Gain Trim0*/
} ADC_GainTrim_t;


/**  
 *  @brief ADC configure type definition
 */
typedef struct
{
    ADC_Resolution_t adcResolution;      /*!< Configure ADC resolution
                                             - ADC_RESOLUTION_8BIT (0): ADC 8-bit resolution
                                             - ADC_RESOLUTION_10BIT (1): ADC 10-bit resolution
                                             - ADC_RESOLUTION_12BIT (2): ADC 12-bit resolution
                                          */
                                                                                         
    ADC_VrefSource_t adcVrefSource;      /*!< Configure ADC voltage reference source
                                             - ADC_VREF_EXTERNAL (0): External Vref_H, Vref_L
                                                reference
                                             - ADC_VREF_INTERNAL (1): Internal Vref_H to 5V,
                                                Vref_L to 0V reference
                                          */
    ADC_TriggerMode_t adcTriggerMode;    /*!< Configure ADC trigger mode
                                             - ADC_NORMAL_SW_TRIGGER (0): Normal software trigger
                                             - ADC_NORMAL_HW_TRIGGER (1): Normal hardware trigger
                                             - ADC_TDG_TRIGGER (2): TDG trigger
                                          */
    ADC_Conversion_t  adcConversionMode; /*!< Configure ADC conversion mode
                                             - ADC_CONVERSION_SINGLE (0):  single conversion
                                             - ADC_CONVERSION_CONTINUOUS (1):
                                                continuous conversion
                                          */
    ADC_Average_t adcAvgsSelect;         /*!< Configure ADC averages
                                             - ADC_AVGS_DISABLED (0): the number of ADC
                                                conversions which are averaged  is 1
                                             - ADC_AVGS_4 (1): the number of ADC conversions
                                                which are averaged  is 4
                                             - ADC_AVGS_8 (2): the number of ADC conversions
                                                which are averaged  is 8
                                             - ADC_AVGS_16(3): the number of ADC conversions
                                                which are averaged  is 16
                                             - ADC_AVGS_32(4): the number of ADC conversions
                                                which are averaged  is 32
                                          */
    uint32_t      adcSampleTime;         /*!< Set the time interval between two samples when average
      is enabled or in continues mode. Please refer to STS definition in RM to see the constraint */
    uint32_t      adcStableTime;            /*!< Configure ADC Stable time(clock cycles), 
                                                 StableTime*Function_CLK>500ns*/
} ADC_Config_t;

/**  
 *  @brief ADC channel configure type definition
 */
typedef struct
{
    ADC_Differential_t adcDifferentialMode; /*!< Configure ADC differential mode
                                                - ADC_SINGLE_MODE (0): ADC single mode
                                                - ADC_DIFF_MODE (1): ADC differential mode */
    ADC_P_Channel_t    adcChannelP;         /*!< Configure ADC positive channel
                                                - ADC_P_CH0 (0):   ADC Positive channel 0
                                                - ......
                                                - ADC_P_CH21 (21): ADC Positive channel 21 */
    ADC_N_Channel_t    adcChannelN;         /*!< Configure ADC negative channel
                                                - ADC_N_CH0 (0):   ADC Negative channel 0
                                                - ADC_N_CH1 (1):   ADC Negative channel 1
                                                - ADC_N_CH2 (2):   ADC Negative channel 2
                                                - ADC_N_VSS (3):   ADC Negative connected with VSS
                                             */
} ADC_ChannelConfig_t;


/**  
 *  @brief ADC compare configure type definition
 */
typedef struct
{
    ADC_Compare_t      adcCompareMode;      /*!< Configure ADC Compare mode
                                                - ADC_COMPARE_MODE_DISABLED (0): 
                                                     ADC compare mode disabled
                                                - ADC_COMPARE_MODE_LESS_CVL (1): 
                                                     ADC compare mode less then cvl
                                                - ADC_COMPARE_MODE_GREATER_CVL (2): 
                                                     ADC compare mode greater than cvl
                                                - ADC_COMPARE_MODE_EQUAL_CVL (3): 
                                                     ADC compare mode equal to cvl
                                                - ADC_COMPARE_MODE_WITHIN_CVL_CVH (4): 
                                                     ADC compare mode within cvl and cvh
                                                - ADC_COMPARE_MODE_OUT_OF_RANGE_CVL_CVH (5): 
                                                     ADC compare mode out of range cvl and cvh
                                             */
    uint16_t           adcCvl;              /*!< Configure ADC Compare Value Low, which is used in 
                                                 below modes: 
                                                - ADC_COMPARE_MODE_LESS_CVL (1)
                                                - ADC_COMPARE_MODE_GREATER_CVL (2)
                                                - ADC_COMPARE_MODE_EQUAL_CVL (3)
                                                - ADC_COMPARE_MODE_WITHIN_CVL_CVH (4)
                                                - ADC_COMPARE_MODE_OUT_OF_RANGE_CVL_CVH (5)   
                                             */
    uint16_t           adcCvh;              /*!< Configure ADC Compare Value High, which is used in
                                                 below modes:
                                                - ADC_COMPARE_MODE_WITHIN_CVL_CVH (4)
                                                - ADC_COMPARE_MODE_OUT_OF_RANGE_CVL_CVH (5)
                                             */
} ADC_CompareConfig_t;

/**  
 *  @brief ADC TDG Trigger configure struct definition
 */
typedef struct
{
    ADC_TDGTriggerMode_t  adcTDGTrigMode;   /*!< Configure ADC TDG Trigger Mode, which is used in 
                                                 below modes:
                                                - ADC_LOOP_MODE (0)
                                                - ADC_MAPPING_MODE (1)
                                             */
    ADC_P_Channel_t       adcCmd0;          /*!< Configure ADC CMD 0 buff, which is P_channel value:
                                                - ADC_P_CH0 (0):   ADC Positive channel 0
                                                - ......
                                                - ADC_P_CH21 (21): ADC Positive channel 21 
                                              */ 
    ADC_P_Channel_t       adcCmd1;          /*!< Configure ADC CMD 1 buff, which is P_channel value. 
                                                 See adcCmd0*/
    ADC_P_Channel_t       adcCmd2;          /*!< Configure ADC CMD 2 buff, which is P_channel value. 
                                                 See adcCmd0*/
    ADC_P_Channel_t       adcCmd3;          /*!< Configure ADC CMD 3 buff, which is P_channel value. 
                                                 See adcCmd0*/
    ADC_P_Channel_t       adcCmd4;          /*!< Configure ADC CMD 4 buff, which is P_channel value.
                                                 See adcCmd0*/
    ADC_P_Channel_t       adcCmd5;          /*!< Configure ADC CMD 5 buff, which is P_channel value.
                                                 See adcCmd0*/
    uint32_t              loopModeDepth;    /*!< Configure ADC tdg trigger loop mode depth*/
} ADC_TDGTriggerConfig_t;

/**  
 *  @brief ADC conversion result struct definition
 */
typedef union
{
    struct
    {
        uint32_t     data     :12;          /*!<[11:0] Sample result of the conversion*/
        uint32_t     channel  :5;           /*!<[16:12] Channel number of the conversion result*/
        uint32_t     reserved :15;          /*!<[31:17] Reserved*/
    }bf;

    uint32_t adcResult;                     /*!< Adc conversion result register*/
} ADC_Conversion_Result_t;

/** @} end of group ADC_Public_Types*/


/** @defgroup ADC_Public_FunctionDeclaration
 *  @brief ADC functions statement
 *  @{
 */

/**
 * @brief      Adc Software Reset Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     none
 *
 */
void ADC_SoftwareReset(ADC_ID_t adcId);

/**
 * @brief      Adc Initialize Function
 *
 * @param[in]  adcId:         Select the ADC ID:
 *                               - ADC0_ID
 *                               - ADC1_ID
 * @param[in]  adcConfigSet:  Pointer to a ADC configuration structure.
 *
 * @return     none
 *
 */
void ADC_Init(ADC_ID_t adcId, const ADC_Config_t* adcConfigSet);

/**
 * @brief      Adc Enable Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     none
 *
 */
void ADC_Enable(ADC_ID_t adcId);

/**
 * @brief      Adc Disable Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     none
 *
 */
void ADC_Disable(ADC_ID_t adcId);

/**
 * @brief      Adc Channel Configure Function
 *
 * @param[in]  adcId:           Select the ADC ID:
 *                                - ADC0_ID
 *                                - ADC1_ID
 * @param[in]  channelConfig:   Pointer to a ADC channel configuration structure.
 *
 * @return     none
 *
 */
void ADC_ChannelConfig(ADC_ID_t adcId, const ADC_ChannelConfig_t* channelConfig);

/**
 * @brief      Adc TDG Trigger Configure Function
 *
 * @param[in]  adcId:            Select the ADC ID:
 *                                 - ADC0_ID
 *                                 - ADC1_ID
 * @param[in]  triggerConfig:    Pointer to a ADC TDG trigger configuration structure.
 *
 * @return     none
 *
 */
void ADC_TDGTriggerConfig(ADC_ID_t adcId, const ADC_TDGTriggerConfig_t* triggerConfig);

/**
 * @brief      Adc TDG Trigger CMD Interrupt Enable Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @param[in]  cmdId:      CMD identifier:
 *                           - ADC_CMD_BUFFER_CMD0
 *                           - ADC_CMD_BUFFER_CMD1
 *                           - ADC_CMD_BUFFER_CMD2
 *                           - ADC_CMD_BUFFER_CMD3
 *                           - ADC_CMD_BUFFER_CMD4
 *                           - ADC_CMD_BUFFER_CMD5
 *
 * @param[in]  status:     Interrupt Enablement:
 *                           - ENABLE
*                            - DISABLE
 * @return     none
 *
 */
void ADC_TDGTriggerCMDIntEnable(ADC_ID_t adcId, ADC_CmdBuffer_t cmdId, ControlState_t status);

/**
 * @brief      Adc Reset(Terminate) Loop Mode for TDG Trigger Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     none
 *
 */
void ADC_ResetLoopMode(ADC_ID_t adcId);

/**
 * @brief      Adc Dozen Control Function
 *
 * @param[in]  adcId:    Select the ADC ID:
 *                         - ADC0_ID
 *                         - ADC1_ID
 *
 * @param[in]  cmd:      Doze Enablement
 *                         - Enable
 *                         - Disable
 *
 * @return     none
 *
 */
void ADC_DozeControl(ADC_ID_t adcId, ControlState_t cmd);

/**
 * @brief      Adc Compare Configure Function
 *
 * @param[in]  adcId:    Select the ADC ID:
 *                         - ADC0_ID
 *                         - ADC1_ID
 * @param[in]  compareConfig: Pointer to a ADC compare configuration structure.
 *                       adcCompareMode:
 *                                        - ADC_COMPARE_MODE_DISABLED
 *                                        - ADC_COMPARE_MODE_LESS_CVL
 *                                        - ADC_COMPARE_MODE_GREATER_CVL
 *                                        - ADC_COMPARE_MODE_EQUAL_CVL
 *                                        - ADC_COMPARE_MODE_WITHIN_CVL_CVH
 *                                        - ADC_COMPARE_MODE_OUT_OF_RANGE_CVL_CVH.
 *                       adcCvl:         Compare Value Low, which is used in below modes:
 *                                        - ADC_COMPARE_MODE_LESS_CVL
 *                                        - ADC_COMPARE_MODE_GREATER_CVL
 *                                        - ADC_COMPARE_MODE_EQUAL_CVL
 *                                        - ADC_COMPARE_MODE_WITHIN_CVL_CVH
 *                                        - ADC_COMPARE_MODE_OUT_OF_RANGE_CVL_CVH
 *                       adcCvh:         Compare Value High, which is used in below modes:
 *                                        - ADC_COMPARE_MODE_WITHIN_CVL_CVH
 *                                        - ADC_COMPARE_MODE_OUT_OF_RANGE_CVL_CVH
 *
 * @return     none
 *
 */
void ADC_CompareConfig(ADC_ID_t adcId, const ADC_CompareConfig_t* compareConfig);

/**
 * @brief      Adc FIFO Depth Redefine Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 * @param[in]  fifoDepth:  New FIFO Depth Value.
 *
 * @return     none
 *
 */
void ADC_FifoDepthRedefine(ADC_ID_t adcId, uint8_t fifoDepth);

/**
 * @brief      Adc FIFO Watermark Configure Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 * @param[in]  fwmark:     New FIFO Watermark Value.
 *
 * @return     none
 *
 */
void ADC_FifoWatermarkConfig(ADC_ID_t adcId, uint8_t fwmark);

/**
 * @brief      Adc Get FIFO size Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     FIFO size.
 *
 */
uint32_t ADC_GetFifoSize(ADC_ID_t adcId);

/**
 * @brief      Adc Get Data Size in FIFO Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     Data size in FIFO.
 *
 */
uint32_t ADC_GetNumOfFifoData(ADC_ID_t adcId);

/**
 * @brief      Adc Dma Request Command Function
 *
 * @param[in]  adcId:    Select the ADC ID:
 *                         - ADC0_ID
 *                         - ADC1_ID
 * @param[in]  cmd:      DMA Request Enablement
 *                         - Enable
 *                         - Disable.
 *
 * @return     none
 *
 */
void ADC_DmaRequestCmd(ADC_ID_t adcId, ControlState_t cmd);

/**
 * @brief      Adc Software Trigger Control Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     none
 *
 */
void ADC_SoftwareTrigger(ADC_ID_t adcId);

/**
 * @brief      Adc Get Conversion Result Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     Conversion Result
 *
 */
uint32_t ADC_GetConversionResult(ADC_ID_t adcId);

/**
 * @brief      Adc Get Status Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 * @param[in]  statusType: Status Type :
 *                           - ADC_STATUS_FWM_INT
 *                           - ADC_STATUS_FOF_INT
 *                           - ADC_STATUS_TCOMP_INT
 *                           - ADC_STATUS_CMP_INT
 *                           - ADC_STATUS_DMA_REQ
 *                           - ADC_STATUS_FIFO_RDY
 *                           - ADC_STATUS_ACTIVE 
 *                           - ADC_STATUS_LOOP_IDLE
 *                           - ADC_STATUS_ERR_INT
 *
 * @return     status.
 *
 */
FlagStatus_t ADC_GetStatus(ADC_ID_t adcId, ADC_Status_t statusType);

/**
 * @brief      Adc Interrupt Mask Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 * @param[in]  intType:    Interrupt Type :
 *                           - ADC_FWM_INT.
 *                           - ADC_FOF_INT
 *                           - ADC_TCOMP_INT
 *                           - ADC_CMP_INT
 *                           - ADC_ERR_INT
 *                           - ADC_INT_ALL
 * @param[in]  intMask:    Mask Type :
 *                           - UNMASK
 *                           - MASK
 *
 * @return     none.
 *
 */
void ADC_IntMask(ADC_ID_t adcId, ADC_INT_t intType, IntMask_t intMask);

/**
 * @brief      Adc Interrupt Clear Status Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 * @param[in]  intType:    Interrupt Type :
 *                           - ADC_FWM_INT.
 *                           - ADC_FOF_INT
 *                           - ADC_TCOMP_INT
 *                           - ADC_CMP_INT
 *                           - ADC_ERR_INT
 *                           - ADC_INT_ALL
 *
 * @return     none.
 *
 */
void ADC_IntClear(ADC_ID_t adcId, ADC_INT_t intType);

/**
 * @brief      Adc Get Interrupt Status Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 * @param[in]  intType:    Interrupt Type :
 *                           - ADC_FWM_INT
 *                           - ADC_FOF_INT
 *                           - ADC_TCOMP_INT
 *                           - ADC_CMP_INT
 *                           - ADC_ERR_INT
 *
 * @return     none.
 *
 */
FlagStatus_t ADC_GetIntStatus(ADC_ID_t adcId, ADC_INT_t intType);

/**
 * @brief      ADC Set Stable time Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @param[in]  stableTime: 11 bits region, make sure the stable time be over 500ns
 *
 * @return     none
 *
 */
void ADC_SetStableTime(ADC_ID_t adcId, uint32_t stableTime);

/**
 * @brief      Install call back function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 * @param[in]  intType:    Select the interrupt
 *                           -  ADC_FWM_INT.
 *                           -  ADC_FOF_INT
 *                           -  ADC_TCOMP_INT
 *                           -  ADC_CMP_INT
 *                           -  ADC_ERR_INT
 * @param[in]  cbFun:      Pointer to callback function
 *
 * @return     none
 *
 */
void ADC_InstallCallBackFunc(ADC_ID_t adcId, ADC_INT_t intType, isr_cb_t * cbFun);


/** @} end of group ADC_Public_FunctionDeclaration */

/** @} end of group ADC */

/** @} end of group Z20K14XM_Peripheral_Driver */
#endif /* ADC_DRV_H */
