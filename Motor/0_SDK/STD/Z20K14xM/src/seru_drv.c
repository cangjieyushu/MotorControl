/**************************************************************************************************/
/**
 * @file     seru_drv.c
 * @brief    SERU module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "seru_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup SERU SERU
 *  @brief SERU driver modules
 *  @{
 */

/** @defgroup SERU_Private_Type
 *  @{
 */

/*@} end of group SERU_Private_Type*/

/** @defgroup SERU_Private_Defines
 *  @{
 */
#define CHANNEL_NUM         (17U)                                 /*!< SERU total channel number*/
#define SERU_CONFIG_KEY     (0x7F1A2dFEU)                         /*!< SERU Config Mode Key*/
#define SERU_NORMAL_KEY     (0x6CC92DD9U)                         /*!< SERU Normal Mode Key*/

/*PRQA S 0303 ++*/
static seru_reg_t *const seruRegPtr = (seru_reg_t *) SERU_BASE_ADDR;         /*!< SERU Register */
static seru_reg_w_t *const seruRegWPtr = (seru_reg_w_t *) SERU_BASE_ADDR;    /*!< SERU Word Register */
/*PRQA S 0303 --*/
/*@} end of group SERU_Private_Defines */

/** @defgroup SERU_Private_Variables
 *  @{
 */

/**
 *  @brief SERU Channel Error ISR callback function pointer array
 */
static cherr_cb_t *seruChErrCbFunc[CHANNEL_NUM] = 
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

/**
 *  @brief SERU Parity Error ISR callback function
 */
static isr_cb_t *seruPErrCbFunc=NULL;

/**
 *  @brief SERU software error generate channel array
 */
static const uint32_t seru_SoftwareErrGenCH[ ] = 
{
    0x00000001U,   /*!< Software error generate channel0 */
    0x00000002U,   /*!< Software error generate channel1*/
    0x00000004U,   /*!< Software error generate channel2 */
    0x00000007U,   /*!< All software error generate channels */
};


/**
 *  @brief SERU FFI channel array
 */
static const uint32_t seru_FFICh[ ] = 
{
    0x00000001U,   /*!< Fake Fault Injection on channel0 */
    0x00000002U,   /*!< Fake Fault Injection on channel1*/
    0x00000004U,   /*!< Fake Fault Injection on channel2 */
    0x00000008U,   /*!< Fake Fault Injection on channel3 */
    0x00000010U,   /*!< Fake Fault Injection on channel4 */
    0x00000020U,   /*!< Fake Fault Injection on channel5 */
    0x00000040U,   /*!< Fake Fault Injection on channel6 */
    0x00000080U,   /*!< Fake Fault Injection on channel7 */
    0x00000100U,   /*!< Fake Fault Injection on channel8 */
    0x00000200U,   /*!< Fake Fault Injection on channel9 */
    0x00000400U,   /*!< Fake Fault Injection on channel10 */
    0x00000800U,   /*!< Fake Fault Injection on channel11 */
    0x00001000U,   /*!< Fake Fault Injection on channel12 */
    0x00002000U,   /*!< Fake Fault Injection on channel13 */
    0x00004000U,   /*!< Fake Fault Injection on channel14 */
    0x00008000U,   /*!< Fake Fault Injection on channel15 */
    0x00010000U,   /*!< Fake Fault Injection on channel16 */
    0x0001FFFFU,   /*!< Fake Fault Injection on all channels */
};
/*@} end of group SERU_Private_Variables */

/** @defgroup SERU_Global_Variables
 *  @{
 */

/*@} end of group SERU_Global_Variables */

/** @defgroup SERU_Private_FunctionDeclaration
 *  @{
 */

void SERU_ParityErr_DriverIRQHandler(void);
void SERU_ChErr_DriverIRQHandler(void);
/*@} end of group SERU_Private_FunctionDeclaration */

/** @defgroup SERU_Private_Functions
 *  @{
 */

/**
 * @brief      SERU Parity Error interrupt handler
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
static void SERU_ParityErr_Handler(void)
{

    /* clear parity error interrupt status */
    seruRegWPtr->SERU_INTF = 0x1U;

    if(seruPErrCbFunc != NULL)
    {
        seruPErrCbFunc();
    }

    COMMON_DSB();
}

/**
 * @brief      SERU channel Error interrupt handler
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
static void SERU_ChErr_Handler(void)
{
    uint32_t intStatus;
    uint32_t chNo;

    for(chNo = (uint32_t)SERU_CHANNEL_0; chNo < (uint32_t)CHANNEL_NUM; chNo++)
    {
        intStatus = seruRegWPtr->SERU_CH_FLAG & (1UL << chNo);

        if(intStatus != 0UL)
        {
            /* clear channel interrupt status */
            seruRegWPtr->SERU_CH_FLAG = intStatus;

            if(seruChErrCbFunc[chNo]!= NULL)
            {
                seruChErrCbFunc[chNo]((SERU_ChannelNO_t)chNo);
            }
        }  
    }

    COMMON_DSB();
}

/**
 * @brief      SERU Parity Error Interrupt Handler.
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void SERU_ParityErr_DriverIRQHandler(void)
{
    SERU_ParityErr_Handler( );
}

/**
 * @brief      SERU channel error interrupt handler.
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void SERU_ChErr_DriverIRQHandler(void)
{
    SERU_ChErr_Handler( );
}
/*@} end of group SERU_Private_Functions */

/** @defgroup SERU_Public_Functions
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
void SERU_GetDefaultConfig(SERU_ChannelConfig_t *seruConfig)
{
    seruConfig->resetType = SERU_SEL_RST_NORMAL;
    seruConfig->resetDelay = SERU_RST_DELAY_NO;
    
    seruConfig->FFIEnable = DISABLE;
    seruConfig->resetEnable = DISABLE;
    seruConfig->eoutEnable = DISABLE;
    seruConfig->intType = SERU_SEL_INT_NORMAL;
    seruConfig->intEnable = ENABLE;
    seruConfig->channelEnable = ENABLE;
    seruConfig->channelNo = SERU_CHANNEL_0;
    seruConfig->polaritySel = SERU_EOUT0_HIGH_EOUT1_LOW;
}

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
SERU_Mode_t SERU_QueryMode(void)
{
    uint32_t seruMode = seruRegPtr->SERU_CSR.CFG_MODE;
    return ((seruMode != 0U) ? SERU_CONFIG_MODE : SERU_NORMAL_MODE);
}

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
void SERU_Init(const SERU_ChannelConfig_t *channelConfig)
{
    SERU_EnterMode(SERU_CONFIG_MODE);

    seruRegPtr->SERU_CFG_CHn[channelConfig->channelNo].CH_EOUT_CFG = (uint32_t)(channelConfig->eoutEnable);
    seruRegPtr->SERU_CFG_CHn[channelConfig->channelNo].CH_INT_TYP = (uint32_t)(channelConfig->intType);
    seruRegPtr->SERU_CFG_CHn[channelConfig->channelNo].CH_INT_CFG = (uint32_t)(channelConfig->intEnable);
    seruRegPtr->SERU_CFG_CHn[channelConfig->channelNo].CH_RESET_TYP = (uint32_t)(channelConfig->resetType);
    seruRegPtr->SERU_CFG_CHn[channelConfig->channelNo].CH_RESET_DLY = (uint32_t)(channelConfig->resetDelay);
    seruRegPtr->SERU_CFG_CHn[channelConfig->channelNo].CH_RESET_CFG = (uint32_t)(channelConfig->resetEnable);
    seruRegPtr->SERU_CSR.EOUT_PS= (uint32_t)(channelConfig->polaritySel);

    if(DISABLE == channelConfig->FFIEnable)
    {
        seruRegWPtr->SERU_CH_FFI &= ~(((uint32_t)1U << (uint32_t)channelConfig->channelNo));
    }
    else
    {
        seruRegWPtr->SERU_CH_FFI |= ((uint32_t)1U <<(uint32_t)channelConfig->channelNo);
    }
    seruRegPtr->SERU_CFG_CHn[channelConfig->channelNo].CH_EN = (uint32_t)(channelConfig->channelEnable);

    SERU_EnterMode(SERU_NORMAL_MODE);
}

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
void SERU_FFIEnable(ControlState_t ffiCmd)
{
    SERU_EnterMode(SERU_CONFIG_MODE);
    seruRegPtr->SERU_CSR.FFI_EN = (uint32_t)ffiCmd;
    SERU_EnterMode(SERU_NORMAL_MODE);
}

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
void SERU_EoutEnable(SERU_ErrorOutputNum_t eoutNum, SERU_ControlEoutMode_t eoutMode)
{
    SERU_EnterMode(SERU_CONFIG_MODE);
    if(SERU_EOUT0_EN == eoutNum)
    {
        seruRegPtr->SERU_CSR.EOUT0_IO_EN = (uint32_t)eoutMode;
    }

    if(SERU_EOUT1_EN == eoutNum)
    {
        seruRegPtr->SERU_CSR.EOUT1_IO_EN = (uint32_t)eoutMode;
    }
    SERU_EnterMode(SERU_NORMAL_MODE);
}

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
void SERU_SetEoutPolarity(SERU_SelectEoutPolarity_t polarityValue)
{

    SERU_EnterMode(SERU_CONFIG_MODE);
    seruRegPtr->SERU_CSR.EOUT_PS = (uint32_t)polarityValue;
    SERU_EnterMode(SERU_NORMAL_MODE);

}

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
void SERU_ParityErrorIntEnable(ControlState_t intCmd)
{
    SERU_EnterMode(SERU_CONFIG_MODE);
    seruRegPtr->SERU_CSR.CRPAR_INT_EN = (uint32_t)intCmd;
    SERU_EnterMode(SERU_NORMAL_MODE);
}

/**
 * @brief      Read Register Parity Error Flag
 *
 * @param[in]  None.
 *
 * @return     Parity Error Flag
 *               - RESET: No configuration register parity mismatch event occurred.
 *               - SET: Configuration register parity mismatch event occurred.
 *
 */
FlagStatus_t SERU_ReadParityErrorFlag(void)
{
    return (seruRegPtr->SERU_INTF.S_CRPAR_ERR != 0U)? SET:RESET;
}

/**
 * @brief      Clear register parity error flag
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void SERU_ClearParityErrorFlag(void)
{
    seruRegPtr->SERU_INTF.S_CRPAR_ERR = 0x1U;
}

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
void SERU_EnterMode(SERU_Mode_t seruMode)
{
    if(SERU_CONFIG_MODE == seruMode)
    {
        seruRegWPtr->SERU_CFG_KEY = SERU_CONFIG_KEY;
    }
    
    if(SERU_NORMAL_MODE == seruMode)
    {
        seruRegWPtr->SERU_CFG_KEY = SERU_NORMAL_KEY;
    }
}

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
void  SERU_SetFFIChannel(SERU_ChannelNO_t chNo, ControlState_t chCtrl)
{
    if(DISABLE == chCtrl)
    {
        seruRegWPtr->SERU_CH_FFI &= (~seru_FFICh[chNo]);
    }
    else
    {
        seruRegWPtr->SERU_CH_FFI |= seru_FFICh[chNo];
    }
}

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
void  SERU_SWErrGenerate(SERU_SoftwareErrCh_t errCh, ControlState_t chCtrl)
{
    if(DISABLE == chCtrl)
    {
        seruRegWPtr->SERU_SWERR_GNT &= (~seru_SoftwareErrGenCH[errCh]);
    }
    else
    {
        seruRegWPtr->SERU_SWERR_GNT |= seru_SoftwareErrGenCH[errCh];
    }
}

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
void  SERU_SetChannelEnable(SERU_ChannelNO_t chNo, ControlState_t chCtrl)
{
    SERU_EnterMode(SERU_CONFIG_MODE);
    seruRegPtr->SERU_CFG_CHn[chNo].CH_EN = (uint32_t)chCtrl;
    SERU_EnterMode(SERU_NORMAL_MODE);
}

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
void  SERU_SetChannelIntEnable(SERU_ChannelNO_t chNo, ControlState_t chCtrl)
{
    SERU_EnterMode(SERU_CONFIG_MODE);
    seruRegPtr->SERU_CFG_CHn[chNo].CH_INT_CFG = (uint32_t)chCtrl;
    SERU_EnterMode(SERU_NORMAL_MODE);
}

/**
 * @brief      Read channel error flag
 *
 * @param[in]  None.
 *
 * @return     Channel which generates error flag.
 *
 */
uint32_t  SERU_GetChannelErrFlag(void)
{
    return seruRegWPtr->SERU_CH_FLAG;
}

/**
 * @brief      Clear channel error flag
 *
 * @param[in]  clearFlag: Writing 1 to clear this bit.
 *
 * @return     None.
 *
 */
void  SERU_ClearChannelErrFlag(uint32_t clearFlag)
{
    seruRegWPtr->SERU_CH_FLAG = clearFlag;
}

/**
 * @brief      SERU install channel error callback func
 *
 * @param[in]  chNo: SERU channel No.
 * @param[in]  cbFun: Callback function pointer.
 *
 * @return     None.
 *
 */
void SERU_InstallChannelErrCallbackFunc(SERU_ChannelNO_t chNo, cherr_cb_t * cbFun)
{
    seruChErrCbFunc[chNo]= cbFun;
}

/**
 * @brief      SERU install parity error callback function
 *
 * @param[in]  parityErrCb: Callback function pointer.
 *
 * @return     None.
 *
 */
void SERU_InstallParityErrCallbackFunc(isr_cb_t *parityErrCb)
{
    seruPErrCbFunc = parityErrCb;
}

/*@} end of group SERU_Public_Functions */

/*@} end of group SERU_definitions */

/*@} end of group Z20K14XM_Peripheral_Driver */
