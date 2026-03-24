/**************************************************************************************************/
/**
 * @file     seru_drv.h
 * @brief    SERU driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef SERU_DRV_H
#define SERU_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SERU
 *  @{
 */

/** @defgroup SERU_Public_Types 
 *  @{
 */

/**
 *  @brief SERU mode type definition
 */
typedef enum
{
    SERU_NORMAL_MODE  = 0U,    /*!< In normal mode  */
    SERU_CONFIG_MODE           /*!< In config mode  */
} SERU_Mode_t;

/**
 *  @brief Error output type definition
 */
typedef enum
{
    SERU_EOUT0_EN  = 0U,    /*!< EOUT0 to external pin  */
    SERU_EOUT1_EN           /*!< EOUT1 to external pin  */
} SERU_ErrorOutputNum_t;

/**
 *  @brief EOUT bypass PORT control or not definition
 */
typedef enum
{
    SERU_EOUT_PORT      = 0U,    /*!< EOUT is controlled by PORT ALT selection to output  */
    SERU_EOUT_EXTERNAL           /*!< EOUT is bypassed PORT control to output external pin directly */
} SERU_ControlEoutMode_t;

/**
 *  @brief EOUT Polarity Selection definition
 */
typedef enum
{
    SERU_EOUT0_HIGH_EOUT1_LOW = 0U,     /*!< EOUT1 is low, and EOUT0 is high as default */
    SERU_EOUT0_LOW_EOUT1_HIGH           /*!< EOUT1 is high, and EOUT0 is low as default */
} SERU_SelectEoutPolarity_t;

/**
 *  @brief software error generate channel definition
 */
typedef enum
{
    SERU_SWERR_CH0 = 0U,     /*!< software error generate channel 0 */
    SERU_SWERR_CH1,          /*!< software error generate channel 1 */
    SERU_SWERR_CH2           /*!< software error generate channel 2 */
} SERU_SoftwareErrCh_t;

/**
 *  @brief delay for reset generation type definition
 */
typedef enum
{
    SERU_RST_DELAY_NO = 0U,     /*!< No delay for reset generation */
    SERU_RST_DELAY_32,          /*!< 2048 seru_clk cycle for reset delay (32us) */
    SERU_RST_DELAY_64,          /*!< 4096 seru_clk cycle for reset delay (64us) */
    SERU_RST_DELAY_128          /*!< 8192 seru_clk cycle for reset delay (128us) */
} SERU_ResetDelay_t;

/**
 *  @brief select RESET type definition
 */
typedef enum
{
    SERU_SEL_RST_NORMAL = 0U,     /*!< Normal reset is selected */
    SERU_SEL_RST_COLD             /*!< Cold reset is selected */
} SERU_SelectReset_t;

/**
 *  @brief SERU channel No. type definition
 */
typedef enum
{
    SERU_CHANNEL_0 = 0U,      /*!< Channel 0 is selected */
    SERU_CHANNEL_1,           /*!< Channel 1 is selected */
    SERU_CHANNEL_2,           /*!< Channel 2 is selected */
    SERU_CHANNEL_3,           /*!< Channel 3 is selected */
    SERU_CHANNEL_4,           /*!< Channel 4 is selected */
    SERU_CHANNEL_5,           /*!< Channel 5 is selected */
    SERU_CHANNEL_6,           /*!< Channel 6 is selected */
    SERU_CHANNEL_8 = 8U,      /*!< Channel 8 is selected */
    SERU_CHANNEL_9,           /*!< Channel 9 is selected */
    SERU_CHANNEL_10,          /*!< Channel 10 is selected */
    SERU_CHANNEL_11,          /*!< Channel 11 is selected */
    SERU_CHANNEL_12,          /*!< Channel 12 is selected */
    SERU_CHANNEL_13,          /*!< Channel 13 is selected */
    SERU_CHANNEL_14,          /*!< Channel 14 is selected */
    SERU_CHANNEL_16 = 16U     /*!< Channel 16 is selected */
} SERU_ChannelNO_t;

/**
 *  @brief  Interrupt type definition
 */
typedef enum
{
    SERU_SEL_INT_NORMAL = 0U,     /*!< Normal interrupt is selected*/
    SERU_SEL_INT_NMI              /*!< NMI is selected */
} SERU_Int_t;

/**
 *  @brief seru channel 0-16 callback function type
 */
typedef void (cherr_cb_t)(SERU_ChannelNO_t seruCh);


/**  
 *  @brief SERU channel configure type definition
 */
typedef struct
{
    SERU_SelectReset_t    resetType;          /*!< Configure SERU RESET type
                                                 - SERU_SEL_RST_NORMAL (0): Normal reset is selected
                                                 - SERU_SEL_RST_COLD   (1): Cold reset is selected */
    
    SERU_ResetDelay_t     resetDelay;              /*!< Configure reset generation delay
                                                 - SERU_RST_DELAY_NO (0) : no delay for reset generation
                                                 - SERU_RST_DELAY_32 (1) : 2048 seru_clk cycle for reset delay (32us) 
                                                 - SERU_RST_DELAY_64 (2) : 4096 seru_clk cycle for reset delay (64us)
                                                 - SERU_RST_DELAY_128 (3): 8192 seru_clk cycle for reset delay (128us) */
    
    
    ControlState_t        FFIEnable;          /*!< Enable or disable fake fault injection
                                                 - DISABLE (0): no action
                                                 - ENABLE  (1): Fake fault injection at corresponding fault */
    
    
    ControlState_t        resetEnable;        /*!< Enable or disable RESET generation
                                                 - DISABLE (0): Error input on this channel  does not generate reset
                                                 - ENABLE  (1): Error input on this channel generates reset */
        
    ControlState_t        eoutEnable;          /*!< Enable or disable EOUT report
                                                 - DISABLE (0): Error input on this channel does not generate EOUT fault state
                                                 - ENABLE  (1):  Error input on this channel generates EOUT fault state */
    
    SERU_Int_t            intType;            /*!< Set INT type
                                                 - SERU_SEL_INT_NORMAL (0): Nornal interrupt is selected
                                                 - SERU_SEL_INT_NMI (1)   :  NMI is selected */
    
    ControlState_t        intEnable;          /*!< Enable or disable INT generation
                                                 - DISABLE (0): Error input on this channel  does not generate interrupt
                                                 - ENABLE  (1): Error input on this channel  generates interrupt */
    
    ControlState_t        channelEnable;      /*!< Enable or disable channel
                                                 - DISABLE (0): Channel is disabled, no respond for error generation
                                                 - ENABLE  (1): Channel is enabled */
    SERU_ChannelNO_t      channelNo;          /*!< channel number
                                                 - SERU_CHANNEL_0: Channel 0
                                                 - SERU_CHANNEL_1: Channel 1 
                                                 - ***
                                                 - SERU_CHANNEL_16: Channel 16*/
    SERU_SelectEoutPolarity_t  polaritySel;     /*!< default value selection for EOUT 
                                                 - SERU_EOUT0_HIGH_EOUT1_LOW (0): EOUT1 is low, and EOUT0 is high
                                                 - SERU_EOUT0_LOW_EOUT1_HIGH  (1): EOUT1 is high, and EOUT0 is low */
} SERU_ChannelConfig_t;

/** @} end of group SERU_Public_Types */

/** @defgroup SERU_Public_FunctionDeclaration
 *  @brief SERU functions declaration
 *  @{
 */

/**
 * @brief      Sets the SERU configuration structure to default values.
 *
 * @param[out]  seruConfig: A pointer to the ecc configuration structure.
 *
 * @return     none
 *
 */
void SERU_GetDefaultConfig(SERU_ChannelConfig_t * seruConfig);

/**
 * @brief      Query SERU mode
 *
 *  If SERU is in normal mode, SERU_CSR[7:0] and SERU_CFG_CHx[7:0] are 
 *  not writable.
 *  If SERU is in config mode, SERU_CSR[7:0] and SERU_CFG_CHx[7:0] are
 *  writable.
 *
 * @param[in]  None.
 *
 * @return     SERU Mode Status:
                 - SERU_CONFIG_MODE : SERU is in config mode.
 *               - SERU_NORMAL_MODE : SERU is in normal mode.
 *
 */
SERU_Mode_t SERU_QueryMode(void);

/**
 * @brief      config SERU, channel configuration can be changed through this function.
 *
 * @param[in]  channelConfig: points to the struct that stores the parameters.
 *
 * @return     none
 *
 * @note       If user expects a reset when OSC40M loss of clock is detected
 *             using channel 8, SERU_CFG_CH8.CH_RESET_TYP should be set to
 *             SERU_SEL_RST_COLD.
 *             If user expects a normal or cold reset when a low-power mode
 *             is detected using channel 4, SERU_CFG_CHn4[CH_INT_CFG]
 *             should be set to 0.
 *             If user expects interrupts when a low-power mode is detected
 *             using channel 4, SERU_CFG_CH4[CH_RESET_CFG] should be set to 0.
 *             Refer to RM for more information.
 *             
 */
void SERU_Init(const SERU_ChannelConfig_t *channelConfig);

/**
 * @brief        Enable or disable Fake fault injection
 *
 *  Only SERU is in config mode, this function can be used.
 *
 * @param[in]    ffiCmd: Control Fake fault injection
 *                      - DISABLE: Disable Fake fault injection.
 *                      - ENABLE : Enable Fake fault injection.
 *
 * @return       None
 *
 */
void SERU_FFIEnable(ControlState_t ffiCmd);

/**
 * @brief        EOUT bypass PORT control or not
 *
 * @param[in]    eoutNum : Select error output
 *                         - SERU_EOUT0_EN: Enable EOUT0
 *                         - SERU_EOUT1_EN: Enable EOUT1
 *
 * @param[in]    eoutMode: Control error output mode
 *                         - SERU_EOUT_PORT    : EOUT is controlled by PORT ALT
 *                           selection to output.
 *                         - SERU_EOUT_EXTERNAL: EOUT is bypassed PORT control
                             to output external pin directly.
 *
 * @return       None
 *
 */
void SERU_EoutEnable(SERU_ErrorOutputNum_t eoutNum, SERU_ControlEoutMode_t eoutMode);

/**
 * @brief      Default Value Selection for EOUT (in the case of no fault
 *             generation)
 *
 * @param[in]  polarityValue: EOUT Polarity Selection
 *                            - SERU_EOUT0_HIGH_EOUT1_LOW: EOUT1 is low, EOUT0
 *                              is high as default.
 *                            - SERU_EOUT0_LOW_EOUT1_HIGH: EOUT0 is low, EOUT1
 *                              is high as default.
 *
 * @return       None
 *
 */
void SERU_SetEoutPolarity(SERU_SelectEoutPolarity_t polarityValue);

/**
 * @brief      SERU internal error flag will be set if the mismatch of 
 *             configuration register parity is detected
 *
 * @param[in]  intCmd: Control register parity error int enable
 *                     - DISABLE: SERU internal error interrupt is disabled
 *                     - ENABLE : SERU internal error interrupt is enabled
 *
 * @return       None
 *
 */
void SERU_ParityErrorIntEnable(ControlState_t intCmd);

/**
 * @brief      Read Register Parity Error Flag
 *
 * @param[in]  None.
 *
 * @return     Parity Error Flag
 *               - RESET: No configuration register parity mismatch event occured.
 *               - SET: Configuration register parity mismatch event occured.
 *
 */
FlagStatus_t SERU_ReadParityErrorFlag(void);

/**
 * @brief      Clear register parity error flag
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void SERU_ClearParityErrorFlag(void);

/**
 * @brief      Configure SERU mode
 *
 *  Set SERU to config mode or return to normal mode
 *
 * @param[in]  seruMode: Select SERU mode
 *                       - SERU_CONFIG_MODE : SERU is in config mode.
 *                       - SERU_NORMAL_MODE : SERU is in normal mode.
 *
 * @return     None. 
 *
 */
void SERU_EnterMode(SERU_Mode_t seruMode);

/**
 * @brief      Select software error generate channel
 *
 * @param[in]  errCh : Select  channel.
 *                     - SERU_SWERR_CH0: Software error generate on channel 0
 *                     - SERU_SWERR_CH1: Software error generate on channel 1
 *                     - SERU_SWERR_CH2: Software error generate on channel 2
 * @param[in]   chCtrl: Disable or enable channel.
 *                     - DISABLE: No action or software error cancelled
 *                     - ENABLE : Generate software error
 *
 * @return     None.
 *
 */
void SERU_SWErrGenerate(SERU_SoftwareErrCh_t errCh, ControlState_t chCtrl);

/**
 * @brief      Set fake fault injection at corresponding channel
 *
 * @param[in]  chNo : channel number.
 * @param[in]  chCtrl: Disable or enable channel.
 *                     - DISABLE: No fake fault injection on channel
 *                     - ENABLE : Generate fake fault injection on channel
 *
 * @return     none
 *
 */
void SERU_SetFFIChannel(SERU_ChannelNO_t chNo, ControlState_t chCtrl);

/**
 * @brief     Channel enable, no response for error generate when disable
 *
 * @param[in]  chNo : channel number.
 * @param[in]  chCtrl: Disable or enable channel.
 *                     - DISABLE: Disable channel
 *                     - ENABLE : Enable channel
 *
 * @return     None
 *
 */
void  SERU_SetChannelEnable(SERU_ChannelNO_t chNo, ControlState_t chCtrl);

/**
 * @brief     Channel interrupt enable
 *
 * @param[in]  chNo : channel number.
 * @param[in]  chCtrl: Disable or enable channel interrupt.
 *                     - DISABLE: Disable channel interrupt
 *                     - ENABLE : Enable channel interrupt
 *
 * @return     None
 *
 * @note       If user expects a normal or cold reset when a low-power mode
 *             is detected using channel 4, SERU_CFG_CHn4[CH_INT_CFG]
 *             should be set to 0.
 *             If user expects interrupts when a low-power mode is detected
 *             using channel 4, SERU_CFG_CH4[CH_RESET_CFG] should be set to 0.
 *             Refer to RM for more information.
 *
 */
void  SERU_SetChannelIntEnable(SERU_ChannelNO_t chNo, ControlState_t chCtrl);

/**
 * @brief      Read channel error flag
 *
 * @param[in]  None.
 *
 * @return     Channel which generates error flag.
 *
 */
uint32_t SERU_GetChannelErrFlag(void);

/**
 * @brief      Clear channel error flag
 *
 * @param[in]  clearFlag: Writing 1 to clear this bit.
 *
 * @return     None.
 *
 */

void SERU_ClearChannelErrFlag(uint32_t clearFlag);

/**
 * @brief      SERU install channel error callback func
 *
 * @param[in]  chNo: SERU channel No.
 * @param[in]  cbFun: Callback function pointer.
 *
 * @return     None.
 *
 */
void SERU_InstallChannelErrCallbackFunc(SERU_ChannelNO_t chNo, cherr_cb_t * cbFun);

/**
 * @brief      SERU install parity error callback function
 *
 * @param[in]  parityErrCb: Callback function pointer.
 *
 * @return     None.
 *
 */
void SERU_InstallParityErrCallbackFunc(isr_cb_t *parityErrCb);


/** @} end of group SERU_Public_FunctionDeclaration */

/** @} end of group SERU */

/** @} end of group Z20K14XM_Peripheral_Driver */
#endif /* SERU_DRV_H */
