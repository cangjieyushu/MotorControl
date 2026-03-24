/**************************************************************************************************/
/**
 * @file     tdg_drv.h
 * @brief    TDG module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#ifndef TDG_DRV_H
#define TDG_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  TDG
 *  @{
 */

/** @defgroup TDG_Public_Types
 *  @{
 */

/**
 *  @brief TDG ID type definition
 */
typedef enum
{
    TDG0_ID = 0U,                            /*!< TDG0  */
    TDG1_ID,                                 /*!< TDG1  */
}TDG_ID_t;

/**
 *  @brief TDG channel configuration update mode type definition
 */
typedef enum
{
    TDG_UPDATE_IMMEDIATELY = 0U,            /*!< Immediately load configuration 
                                                 afterupdate channel register */
    TDG_UPDATE_MODULATOR,                   /*!< Load configuration when counter 
                                                count up to equal to modulator */
    TDG_UPDATE_DELAY                        /*!<  Load configuration when all
                                               channel complete delay output */
} TDG_UpdateMode_t;

/**
 *  @brief TDG Clock Divide type definition
 */
typedef enum
{
    TDG_CLK_DIVIDE_1 = 0U,                  /*!< TDG Clock Divide by 1*/
    TDG_CLK_DIVIDE_2,                       /*!< TDG Clock Divide by 2*/
    TDG_CLK_DIVIDE_4,                       /*!< TDG Clock Divide by 4*/
    TDG_CLK_DIVIDE_8,                       /*!< TDG Clock Divide by 8*/
    TDG_CLK_DIVIDE_16,                      /*!< TDG Clock Divide by 16*/
    TDG_CLK_DIVIDE_32,                      /*!< TDG Clock Divide by 32*/
    TDG_CLK_DIVIDE_64,                      /*!< TDG Clock Divide by 64*/
    TDG_CLK_DIVIDE_128                      /*!< TDG Clock Divide by 128*/
} TDG_ClkDivide_t;

/**
 *  @brief TDG Count Clear Mode type definition
 */
typedef enum
{
    TDG_CLEAR_MODULATOR = 0U,               /*!< Clear counter when counter
                                                   equal to modulator */
    TDG_CLEAR_DELAY                         /*!< Clear counter when all channel
                                                   complete delay output */
}TDG_CountClearMode_t;

/**
 *  @brief TDG Count Mode type definition
 */
typedef enum
{
    TDG_COUNT_SINGLE = 0U,                  /*!< single loop mode */
    TDG_COUNT_INFINITY                      /*!< infinity loop mode */
}TDG_CountMode_t;

/**
 *  @brief TDG Trig Source type definition
 */
typedef enum
{
    TDG_TRIG_EXTERNAL = 0U,                 /*!< external trig source */
    TDG_TRIG_SW                             /*!< software trig source */
 }TDG_TrigSource_t;

 /**
 *  @brief TDG Channel ID type definition
 */
typedef enum
{
    TDG_CHANNEL_0 = 0U,                     /*!< TDG Channel 0*/
    TDG_CHANNEL_1,                          /*!< TDG Channel 1*/
    TDG_CHANNEL_2,                          /*!< TDG Channel 2*/
    TDG_CHANNEL_3,                          /*!< TDG Channel 3*/
    TDG_CHANNEL_4,                          /*!< TDG Channel 4*/
    TDG_CHANNEL_5                           /*!< TDG Channel 5*/
}TDG_ChannelId_t;

 /**
 *  @brief TDG Interrupt type definition
 */
typedef enum
{
    TDG_INT_CH0 = 0U,                       /*!< channel 0 INT*/
    TDG_INT_CH1,                            /*!< channel 1 INT*/
    TDG_INT_CH2,                            /*!< channel 2 INT*/
    TDG_INT_CH3,                            /*!< channel 3 INT*/
    TDG_INT_CH4,                            /*!< channel 4 INT*/
    TDG_INT_CH5,                            /*!< channel 5 INT*/
    TDG_INT_ERR,                            /*!< Error interrupt*/
    TDG_INT_ALL
}TDG_INT_t;

 /**
 *  @brief TDG Delay Output point ID type definition
 */
typedef enum
{
    TDG_DO_0 = 0U,                          /*!< TDG Delay output 0*/
    TDG_DO_1,                               /*!< TDG Delay output 1*/
    TDG_DO_2,                               /*!< TDG Delay output 2*/
    TDG_DO_3,                               /*!< TDG Delay output 3*/
    TDG_DO_4,                               /*!< TDG Delay output 4*/
    TDG_DO_5,                               /*!< TDG Delay output 5*/
    TDG_DO_6,                               /*!< TDG Delay output 6*/
    TDG_DO_7                                /*!< TDG Delay output 7*/
}TDG_DelayOutputId_t;

/**
 *  @brief TDG init configure struct definition
 */
typedef struct
{
    uint16_t  modVal;                       /*!< modulate value  */
    TDG_CountMode_t countMode;              /*!< count mode */
    TDG_ClkDivide_t clkDivide;              /*!< pre-scale clock source */
    TDG_TrigSource_t trigSource;            /*!< counter trig source */
    TDG_UpdateMode_t updateMode;            /*!< update mode */
    TDG_CountClearMode_t clearMode;         /*!< counter clear mode */
}TDG_InitConfig_t;

/**
 *  @brief TDG delay output configure struct definition
 */
typedef struct
{
    TDG_DelayOutputId_t doId;               /*!< delay output id */

    uint16_t offset;                        /*!< delay output offset */
    ControlState_t cmd;                     /*!< delay output enable  */

}TDG_DelayOutputConfig_t;

/**
 *  @brief TDG Channel configure struct definition
 */
typedef struct
{
    TDG_ChannelId_t channelId;              /*!< channel id */

    uint16_t intDelayVal;                   /*!< delay output complete interrupt delay*/

    uint8_t doNum;                          /* number of delay output point*/

    TDG_DelayOutputConfig_t* doConfig;
}TDG_ChannelConfig_t;


/** @} end of group TDG_Public_Types*/


/** @defgroup TDG_Public_FunctionDeclaration
 *  @brief TDG functions statement
 *  @{
 */

/**
 * @brief       TDG ENABLE/DISABLE FUNCTION
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  cmd: ENABLE/DISABLE
 *
 * @return none
 *
 */
void TDG_Enable(TDG_ID_t tdgId, ControlState_t cmd);

/**
 * @brief       TDG init config function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]    config: init config
 *
 * @return none
 *
 */
void TDG_InitConfig(TDG_ID_t tdgId, const TDG_InitConfig_t * config);

/**
 * @brief       TDG config update mode function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  updateMode:
 *                       -TDG_UPDATE_IMMEDIATELY
 *                       -TDG_UPDATE_MODULATOR
 *                       -TDG_UPDATE_DELAY
 *
 * @return none
 *
 */
void TDG_UpdateModeConfig(TDG_ID_t tdgId, TDG_UpdateMode_t updateMode);

/**
 * @brief       TDG select counter clear mode
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  clearMode:
 *                       -TDG_ClEAR_MODULATOR
 *                       -TDG_CLEAR_DELAY
 *
 * @return none
 *
 */
void TDG_ClearCounterMode(TDG_ID_t tdgId, TDG_CountClearMode_t clearMode);

/**
 * @brief       TDG select count mode
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  countMode:
 *                       -TDG_COUNT_SINGLE
 *                       -TDG_COUNT_INFINITY
 *
 * @return none
 *
 */
void TDG_SelectCountMode(TDG_ID_t tdgId, TDG_CountMode_t countMode);

/**
 * @brief       TDG select trig source
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  trig:
 *                       -TDG_TRIG_EXTERNAL
 *                       -TDG_TRIG_INFINITY
 *
 * @return none
 *
 */
void TDG_SelectTrigMode(TDG_ID_t tdgId, TDG_TrigSource_t trig);

/**
 * @brief   Set this bit to load channel configuration from shadow buffer to register
 *
 * @param[in]  tdgId
 *
 * @return ResultStatus_t 
 *                       - SUCC: Load complete 
 *                       - ERR:load fail
 *
 *
 */
ResultStatus_t TDG_LoadCmd(TDG_ID_t tdgId);

/**
 * @brief      TDG software trig
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 *
 * @return none
 *
 */
void TDG_SoftwareTrig(TDG_ID_t tdgId);

/**
 * @brief      TDG mod value config
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  modValue: Set mod value
 *
 * @return none
 *
 */
void TDG_SetModVal(TDG_ID_t tdgId, uint16_t modValue);

/**
 * @brief      GET TDG mod value
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 *
 * @return mod value
 *
 */
uint16_t TDG_GetModVal(TDG_ID_t tdgId);

/**
 * @brief      GET TDG counter value
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 *
 * @return  uint16_t: The counter value
 *
 */
uint16_t TDG_GetCounterVal(TDG_ID_t tdgId);

/**
 * @brief      TDG pre-scale the count clock source function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  divide:
 *                            -TDG_CLK_DIVIDE_1
 *                            -TDG_CLK_DIVIDE_2
 *                            -TDG_CLK_DIVIDE_4
 *                            -TDG_CLK_DIVIDE_8
 *                            -TDG_CLK_DIVIDE_16
 *                            -TDG_CLK_DIVIDE_32
 *                            -TDG_CLK_DIVIDE_64
 *                            -TDG_CLK_DIVIDE_128
 *
 * @return none
 *
 */
void TDG_DivideClk(TDG_ID_t tdgId, TDG_ClkDivide_t divide);

/**
 * @brief      TDG channel enable/disable
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  channelId: select channel
 * @param[in]  cmd:ENABLE/DISABLE
 *
 * @return none
 *
 */
void TDG_ChannelEnable(TDG_ID_t tdgId, TDG_ChannelId_t channelId, ControlState_t cmd);

/**
 * @brief       TDG INT mask/unmask Function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  intType:    Select interrupt type.
 * @param[in]  intMask:  MASK/UNMASK .
 *
 * @return none
 *
 */
void TDG_IntMask(TDG_ID_t tdgId, TDG_INT_t intType, IntMask_t intMask);

/**
 * @brief       TDG INT status clear Function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  intType:    Select interrupt type.
 *
 * @return none
 *
 */
void TDG_IntClear(TDG_ID_t tdgId, TDG_INT_t intType);

/**
 * @brief       TDG Get INT status Function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  intType:    Select interrupt type.
 *
 * @return intStatus
 *
 */
IntStatus_t TDG_GetIntStatus(TDG_ID_t tdgId, TDG_INT_t intType);

/**
 * @brief       TDG channel delay output complete interrupt delay
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  channelId: select channel
 * @param[in]  delayVal: delay output complete interrupt delay
 *
 * @return none
 *
 */
void TDG_SetIntDelayVal(TDG_ID_t tdgId, TDG_ChannelId_t channelId, uint16_t delayVal);

/**
 * @brief      get TDG delay output complete interrupt delay value
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  channelId: select channel y
 *
 * @return    uint16_t: The delay value
 *
 */
uint16_t TDG_GetChannelIntDelayVal(TDG_ID_t tdgId, TDG_ChannelId_t channelId);

/**
 * @brief       Clear TDG channel delay output function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  channelId: select channel
 *
 * @return none
 *
 */
void TDG_ClearChannelDelayOutput(TDG_ID_t tdgId, TDG_ChannelId_t channelId);

/**
 * @brief       TDG channel delay output enable function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  channelId: select channel
 * @param[in]  doConfig: config delay output 
 *
 * @return none
 *
 */
void TDG_DelayOuputConfig(TDG_ID_t tdgId, TDG_ChannelId_t channelId,
                           const TDG_DelayOutputConfig_t* doConfig);

/**
 * @brief       TDG channel delay output config function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  config: Configuration
 * @param[in]  cmd: 
 *                -ENABLE
 *                -DISABLE
 *
 * @return none
 *
 */
void TDG_ChannelDelayOutputConfig(TDG_ID_t tdgId, const TDG_ChannelConfig_t* config,
                                  ControlState_t cmd);

/**
 * @brief       TDG get interrupt delay config load complete status Function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  channelId:    Select channel type.
 *
 * @return IntStatus_t
 *
 */
IntStatus_t TDG_GetDelayStatus(TDG_ID_t tdgId, TDG_ChannelId_t channelId);

/**
 * @brief      Get TDG delay output offset value
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  channelId: select channel id
 * @param[in]  doId: select delay output id
 *
 * @return    uint16_t: The delay value
 *
 */
uint16_t TDG_GetChannelOffsetVal(TDG_ID_t tdgId, TDG_ChannelId_t channelId, 
                                                  TDG_DelayOutputId_t doId);

/**
 * @brief       TDG get channel number Function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 *
 * @return   uint8_t: The channel number
 *
 */
uint8_t TDG_GetCHNum(TDG_ID_t tdgId);

/**
 * @brief       TDG get delay output point Function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 *
 * @return     uint8_t: The delay output point.
 *
 */
uint8_t TDG_GetDoNum(TDG_ID_t tdgId);

/**
 * @brief      install call back function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  intId: select the interrupt
 * @param[in]  cbFun: pointer to callback function
 *
 * @return     none
 */
void TDG_InstallCallBackFunc(TDG_ID_t tdgId, TDG_INT_t intType, 
                             isr_cb_t * cbFun);


/** @} end of group TDG_Public_FunctionDeclaration */

/** @} end of group TDG  */

/** @} end of group Z20K14XM_Peripheral_Driver */

#endif /* TDG_DRV_H */
