/***************************************************************************//**
 * @file     i2s_drv.c
 * @brief    I2S module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 ******************************************************************************/

#include "i2s_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup I2S
 *  @brief I2S driver modules
 *  @{
 */

/** @defgroup I2S_Private_Type
 *  @{
 */

/** @} end of group I2S_Private_Type*/

/** @defgroup I2S_Private_Defines
 *  @{
 */

/** @} end of group I2S_Private_Defines */

/** @defgroup I2S_Private_Variables
 *  @{
 */

#define I2S_CHANNEL_NUM             (4U)

static uint32_t i2sIntMaskStatus[I2S_INSTANCE_NUM][I2S_CHANNEL_NUM] = 
{
    {0U,0U,0U,0U}
#if (defined(DEV_Z20K148M))
    ,{0U,0U,0U,0U}
#endif
};

static const uint32_t I2S_IntStatusTable[] = 
{
    0x00000010U,               /*!< I2S  RxFIFO data available interrupt */
    0x00000020U,               /*!< I2S  RxFIFO overrun interrupt */
    0x00000040U,               /*!< I2S  TxFIFO empty interrupt*/
    0x00000080U,               /*!< I2S  TxFIFO overrun interrupt*/
    0x000000F0U                /*!< I2S  all interrupt*/
};

static const uint32_t I2S_IntMaskTable[] = 
{
    0x00000001U,               /*!< I2S  RxFIFO data available interrupt */
    0x00000002U,               /*!< I2S  RxFIFO overrun interrupt */
    0x00000004U,               /*!< I2S  TxFIFO empty interrupt*/
    0x00000008U,               /*!< I2S  TxFIFO overrun interrupt*/
    0x0000000FU                /*!< I2S  all interrupt*/
};

/**
 *  @brief I2S0 and I2S1 instance address array
 */
/*PRQA S 0303 ++*/
static i2s_reg_t *const i2sRegPtr[I2S_INSTANCE_NUM] = 
{
   (i2s_reg_t *)I2S0_BASE_ADDR
#if (defined(DEV_Z20K148M))
   ,(i2s_reg_t *)I2S1_BASE_ADDR
#endif
};
/*PRQA S 0303 --*/

/*PRQA S 0303 ++*/
static i2s_reg_w_t *const i2sRegWPtr[I2S_INSTANCE_NUM] = 
{
   (i2s_reg_w_t *)I2S0_BASE_ADDR
#if (defined(DEV_Z20K148M))
   ,(i2s_reg_w_t *)I2S1_BASE_ADDR
#endif
};
/*PRQA S 0303 --*/

/**
 *  @brief I2S IRQHandler callback function pointer array
 */
static isr_cb_t * i2sIsrCbFunc[I2S_INSTANCE_NUM][I2S_CHANNEL_NUM][I2S_INT_ALL] = 
{
  {{NULL, NULL, NULL, NULL},
   {NULL, NULL, NULL, NULL},
   {NULL, NULL, NULL, NULL},
   {NULL, NULL, NULL, NULL},},
   
#if (defined(DEV_Z20K148M))  
  {{NULL, NULL, NULL, NULL},
   {NULL, NULL, NULL, NULL},
   {NULL, NULL, NULL, NULL},
   {NULL, NULL, NULL, NULL},},
#endif  
};

/** @defgroup I2S_Private_FunctionDeclaration
 *  @{
 */
void I2S0_DriverIRQHandler(void);

#if (defined(DEV_Z20K148M))
void I2S1_DriverIRQHandler(void);
#endif

/** @} end of group I2S_Private_FunctionDeclaration */

/** @defgroup I2S_Public_Functions
 *  @{
 */
/**
 * @brief      I2S interrupt handle
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 *
 * @return none
 *
 */
void I2S_IntHandler(I2S_Id_t i2sId)
{
    uint32_t intStatus;
    uint32_t intType;
    i2s_reg_w_t * I2Sxw = (i2s_reg_w_t *)(i2sRegWPtr[i2sId]);

    uint8_t channelPollNo;

    for(channelPollNo = 0; channelPollNo < I2S_CHANNEL_NUM; channelPollNo++)
    {
        intStatus = I2S_GetAllStatus(i2sId,(I2S_ChannelId_t)channelPollNo);
        /* check enabled interrupt and status interrupt flag */
        intStatus = intStatus & i2sIntMaskStatus[i2sId][channelPollNo];
        /* clear interrupt status */
        I2Sxw->I2S_CHANNEL_REG[channelPollNo].I2S_CHn_INT_CFG = intStatus;
        for(intType = (uint32_t)I2S_RXFIFO_DATA_AVAILIABLE_INT; intType < (uint32_t)I2S_INT_ALL; 
                                                                                         intType++)
        {    
            if((intStatus & I2S_IntStatusTable[intType]) != 0U)
            {
                if(i2sIsrCbFunc[i2sId][channelPollNo][intType] != NULL)
                {
                    /* call the callback function */
                    i2sIsrCbFunc[i2sId][channelPollNo][intType]();
                }
                /* Disable the interrupt if callback function is not setup */
                else
                {
                    I2Sxw->I2S_CHANNEL_REG[channelPollNo].I2S_CHn_INT_CFG  &=
                                                                       (~I2S_IntMaskTable[intType]);
                }

            }
        }  
   
    }
    COMMON_DSB();
}

/**
 * @brief  I2S0 interrupt function
 *
 * @param  none
 *
 * @return none
 *
 */
void I2S0_DriverIRQHandler(void)
{
   I2S_IntHandler(I2S_ID_0);
}

#if (defined(DEV_Z20K148M))
/**
 * @brief  I2S1 interrupt function
 *
 * @param  none
 *
 * @return none
 *
 */
void I2S1_DriverIRQHandler(void)
{
   I2S_IntHandler(I2S_ID_1);
}
#endif

/**
 * @brief      Install call back function
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  channelId:       Select the I2S Channel ID:
 *                                  -Channel0_ID
 *                                  -Channel1_ID
 *                                  -Channel2_ID
 *                                  -Channel3_ID
 * 
 * @param[in]  I2SIntType:      Specified interrupt type.
 *                                  -TXFIFO_OVERRUN_INT
 *                                  -TXFIFO_EMPTY_INT
 *                                  -RXFIFO_OVERRUN_INT
 *                                  -RXFIFO_DATA_AVAILIABLE_INT
 *
 * @param[in]  cbFun:           Pointer to callback function.
 *
 * @return     none
 *
 */
void I2S_InstallCallBackFunc(I2S_Id_t i2sId,I2S_ChannelId_t channelId, I2S_Interrupt_t I2SIntType,isr_cb_t * cbFun)
{
    i2sIsrCbFunc[i2sId][channelId][I2SIntType] = cbFun;
}

/**
 * @brief       Reset all I2S Receiver FIFO contents.
 *              It can only be reset when I2S_RE = 0
 *
 * @param[in]   i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 *
 * @return      function execution result
 *
 */
ResultStatus_t I2S_ResetAllRxfifo(I2S_Id_t i2sId)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    ResultStatus_t res = SUCC;

    if(0U == I2Sx->I2S_CONTROL.I2S_RE)
    {
        I2Sx->I2S_CONTROL.I2S_RXFIFO_RESET = 1U;
    }
    else
    {
        res = ERR;
    }

    return res;
}

/**
 * @brief       Reset all I2S Transmit FIFO contents.
 *              It can only be reset when I2S_TE = 0
 *
 * @param[in]   i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 *
 * @return      function execution result
 *
 */
ResultStatus_t I2S_ResetAllTxfifo(I2S_Id_t i2sId)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    ResultStatus_t res = SUCC;

    if(0U == I2Sx->I2S_CONTROL.I2S_TE)
    {
        I2Sx->I2S_CONTROL.I2S_TXFIFO_RESET = 1U;
    }
    else
    {
        res = ERR;
    }

    return res;
}

/**
 * @brief      Enable or disable the I2S receiver.
 *             It can only be enable when I2S_TE = 0
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  status:          Select the I2S receiver status.
 *                                  -ENABLE
 *                                  -DISABLE
 *
 * @return     function execution result
 *
 */
ResultStatus_t I2S_EnableReceiver(I2S_Id_t i2sId, ControlState_t status)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    ResultStatus_t res = SUCC;

    if(DISABLE == status)
    {
        I2Sx->I2S_CONTROL.I2S_RE = 0U;
    }
    else
    {
        if(0U == I2Sx->I2S_CONTROL.I2S_TE )
        {
            I2Sx->I2S_CONTROL.I2S_RE = 1U;
        }
        else
        {
            res = ERR;
        }
    }

    return res;   
}

/**
 * @brief      Enable or disable the I2S transmitter.
 *             It can only be enable when I2S_RE = 0
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  status:          Select the I2S transmitter status.
 *                                  -ENABLE
 *                                  -DISABLE
 *
 * @return     function execution result
 *
 */
ResultStatus_t I2S_EnableTransmitter( I2S_Id_t i2sId, ControlState_t status)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    ResultStatus_t res = SUCC;

    if(DISABLE == status)
    {
        I2Sx->I2S_CONTROL.I2S_TE = 0U;
    }
    else
    {
        if(0U == I2Sx->I2S_CONTROL.I2S_RE)
        {
            I2Sx->I2S_CONTROL.I2S_TE = 1U;
        }
        else
        {
            res = ERR;
        }
    }

    return res; 
}

/**
 * @brief      Enable I2S Module.
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  status:          Select the I2S Module Status.
 *                                  -ENABLE
 *                                  -DISABLE
 *
 * @return     none
 *
 */
void I2S_Enable(I2S_Id_t i2sId,ControlState_t status)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    if(DISABLE == status)
    {
        I2Sx->I2S_CONTROL.I2S_MODULE_EN = 0U;
    }
    else
    {
        I2Sx->I2S_CONTROL.I2S_MODULE_EN = 1U;
    }
}

/**
 * @brief      Configure the I2S audio master clock divider.
 *             Actual division value is (MCK_DIV+1)*2
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  masterClkDiv:    I2S Master Clock divider.
 *
 * @return none
 *
 */
void I2S_SetMasterClkDiv(I2S_Id_t i2sId,uint8_t masterClkDiv)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    /*clear the default value*/
    I2Sx->I2S_MASTER_CONFIG.MCK_DIV = (uint32_t)(masterClkDiv);
}

/**
 * @brief      Configure the I2S bclk gated cycles.
 *             It can only be configured when I2S_MASTER_EN = 0.The number of bclk cycles should be 
 *             equal to or greater than tx/rx audio resolutions configured from individual channel 
 *             configure register. 
 * 
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  i2sNumBclkGate: I2S gated after the num of bclk cycles:
 *                                  -I2S_NO_BCLK_GATING
 *                                  -I2S_BCLK_GATED_AFTER_12BCLK
 *                                  -I2S_BCLK_GATED_AFTER_16BCLK
 *                                  -I2S_BCLK_GATED_AFTER_20BCLK
 *                                  -I2S_BCLK_GATED_AFTER_24BCLK
 *
 * @return    function execution result
 *
 */
ResultStatus_t I2S_SetGateBclkNum(I2S_Id_t i2sId,I2S_NumBclkGate_t i2sNumBclkGate)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    ResultStatus_t res = SUCC;

    if(0U == I2Sx->I2S_MASTER_CONFIG.I2S_MASTER_EN)
    {
        /*clear the default value*/
        I2Sx->I2S_MASTER_CONFIG.I2S_NUM_BCLK_GATE = (uint32_t)(i2sNumBclkGate);
    }
    else
    {
        res = ERR;
    }

    return res; 
}

/**
 * @brief      Set the I2S number of bclk cycles during left or right word line
 *             It's valid only during I2S master mode, and can only be configured when I2S
 *             I2S_MASTER_EN = 0
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  i2sBclkNum:      I2S number of bclk cycles during left or right word line:
 *                                  -I2S_BCLK_16_CYCLES
 *                                  -I2S_BCLK_24_CYCLES
 *                                  -I2S_BCLK_32_CYCLES
 *
 * @return     function execution result
 *
 */
ResultStatus_t I2S_SetBclkNum(I2S_Id_t i2sId, I2S_BclkNum_t i2sBclkNum)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    ResultStatus_t res = SUCC;

    if(0U == I2Sx->I2S_MASTER_CONFIG.I2S_MASTER_EN)
    {
        I2Sx->I2S_MASTER_CONFIG.I2S_NUM_BCLK = (uint32_t)(i2sBclkNum);
    }
    else
    {
        res = ERR;
    }

    return res; 
}

/**
 * @brief      Select I2S mode as Master or Slave
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  mode:            I2S mode
 *                                  -I2S_MODE_SLAVE:slave mode
 *                                  -I2S_MODE_MASTER:master mode
 *
 * @return     none
 *
 */
void I2S_ModeSelect(I2S_Id_t i2sId, I2S_Mode_t mode)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);

    if(I2S_MODE_SLAVE == mode)
    {
        I2Sx->I2S_MASTER_CONFIG.I2S_MASTER_EN = 0U;
    }
    else
    {
        I2Sx->I2S_MASTER_CONFIG.I2S_MASTER_EN = 1U;
    }
}

/**
 * @brief      Disable I2S Master Mode.
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 *
 * @return     none
 *
 */
void I2S_MasterDisable(I2S_Id_t i2sId)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    I2Sx->I2S_MASTER_CONFIG.I2S_MASTER_EN = 0U;
}

/**
 * @brief      Set actual receive data resolutions.
 *             Configurable audio data resolutions of 12, 16, 20, 24, and 32 bits.
 *             It can only be configured when any of CHn_RX_EN, I2S_RE and I2S_MODULE_EN is 0.
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  channelId:       Select the I2S Channel ID:
 *                                  -Channel0_ID
 *                                  -Channel1_ID
 *                                  -Channel2_ID
 *                                  -Channel3_ID
 * 
 * @param[in]  audioResolution: I2S resolution:
 *                                  -I2S_AUDIO_RESOLUTION_12BIT
 *                                  -I2S_AUDIO_RESOLUTION_16BIT
 *                                  -I2S_AUDIO_RESOLUTION_20BIT
 *                                  -I2S_AUDIO_RESOLUTION_24BIT
 *                                  -I2S_AUDIO_RESOLUTION_32BIT
 *
 * @return     function execution result
 *
 */
ResultStatus_t I2S_SetChannelRxResolution(I2S_Id_t i2sId, I2S_ChannelId_t channelId, 
                                                            I2S_AudioResolution_t audioResolution)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    ResultStatus_t res = SUCC;

    if((0U == I2Sx->I2S_CHANNEL_REG[channelId].I2S_CHn_CFG.RX_EN) || 
                        (0U == I2Sx->I2S_CONTROL.I2S_RE) || (0U == I2Sx->I2S_CONTROL.I2S_MODULE_EN))
    {
        I2Sx->I2S_CHANNEL_REG[channelId].I2S_CHn_CFG.RX_AUDIO_RESOLUTION = (uint32_t)(audioResolution);
    }
    else
    {
        res = ERR;
    }                                                                                                                                                                                         

    return res;
}

/**
 * @brief      Set actual transmit data resolutions.
 *             Configurable audio data resolutions of 12, 16, 20, 24, and 32 bits.
 *             These bits can only be changed when any of TX_EN, I2S_TE and I2S_MODULE_EN is 0.
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  channelId:       Select the I2S Channel ID:
 *                                  -Channel0_ID
 *                                  -Channel1_ID
 *                                  -Channel2_ID
 *                                  -Channel3_ID
 * 
 * @param[in]  audioResolution: I2S resolution:
 *                                  -I2S_AUDIO_RESOLUTION_12BIT
 *                                  -I2S_AUDIO_RESOLUTION_16BIT
 *                                  -I2S_AUDIO_RESOLUTION_20BIT
 *                                  -I2S_AUDIO_RESOLUTION_24BIT
 *                                  -I2S_AUDIO_RESOLUTION_32BIT
 *
 * @return     function execution result
 *
 */
ResultStatus_t I2S_SetChannelTxResolution(I2S_Id_t i2sId, I2S_ChannelId_t channelId, 
                                                            I2S_AudioResolution_t audioResolution)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    ResultStatus_t res = SUCC;

    if((0U == I2Sx->I2S_CHANNEL_REG[channelId].I2S_CHn_CFG.TX_EN) || 
                (0U == I2Sx->I2S_CONTROL.I2S_TE) || (0U == I2Sx->I2S_CONTROL.I2S_MODULE_EN))
    {    
        I2Sx->I2S_CHANNEL_REG[channelId].I2S_CHn_CFG.TX_AUDIO_RESOLUTION = (uint32_t)(audioResolution);
    }
    else
    {
        res = ERR;
    }

    return res;
}

/**
 * @brief      Enable channel receive feature.
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  i2sChannelsConfigStruct: I2S channel feature enable structure.
 *
 * @return     function execution result
 *
 */
ResultStatus_t I2S_EnableChannelRx(I2S_Id_t i2sId, I2S_ChannelsEnableConfig_t i2sChannelsConfigStruct)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    uint8_t channelId;
    ResultStatus_t res = SUCC;
    I2S_Enable(i2sId, ENABLE);

    if((1U == I2Sx->I2S_CONTROL.I2S_RE) && (1U == I2Sx->I2S_CONTROL.I2S_MODULE_EN))
    {
        for(channelId = 0; channelId <I2S_CHANNEL_NUM; channelId++)
        {
            if(I2S_CHANNEL_ENABLE == i2sChannelsConfigStruct.channels[channelId])
            {
                I2Sx->I2S_CHANNEL_REG[channelId].I2S_CHn_CFG.RX_EN = 1U;
            }
            else if(I2S_CHANNEL_DISABLE == i2sChannelsConfigStruct.channels[channelId])
            {
                I2Sx->I2S_CHANNEL_REG[channelId].I2S_CHn_CFG.RX_EN = 0U;
            }
            else
            {
                res = ERR;
            }
        }
    }
    else
    {
        res = ERR;
    }

    return res;
}

/**
 * @brief      Enable channel transmit feature.
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  i2sChannelsConfigStruct: I2S channel feature enable structure.
 *
 * @return     function execution result
 *
 */
ResultStatus_t I2S_EnableChannelTx(I2S_Id_t i2sId, I2S_ChannelsEnableConfig_t i2sChannelsConfigStruct)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    uint8_t channelId;
    ResultStatus_t res = SUCC;
    I2S_Enable(i2sId, ENABLE);

    if((1U == I2Sx->I2S_CONTROL.I2S_TE) && (1U == I2Sx->I2S_CONTROL.I2S_MODULE_EN))
    {
        for(channelId = 0U; channelId < I2S_CHANNEL_NUM; channelId++)
        {
            if(I2S_CHANNEL_ENABLE == i2sChannelsConfigStruct.channels[channelId])
            {
                I2Sx->I2S_CHANNEL_REG[channelId].I2S_CHn_CFG.TX_EN = 1U;
            }
            else if(I2S_CHANNEL_DISABLE == i2sChannelsConfigStruct.channels[channelId])
            {
                I2Sx->I2S_CHANNEL_REG[channelId].I2S_CHn_CFG.TX_EN = 0U;
            }
            else
            {
                res = ERR;
            }
        }
    }
    else
    {
        res = ERR;
    }

    return res;
}

/**
 * @brief      Get specify channel Interrupt Status
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  channelId:       Select the I2S Channel ID:
 *                                  -Channel0_ID
 *                                  -Channel1_ID
 *                                  -Channel2_ID
 *                                  -Channel3_ID
 * 
 * @param[in]  i2sStatus:       Select I2S status type to check:
 *                                  - I2S_STATUS_RX_FULL
 *                                  - I2S_STATUS_RX_OVERRUN
 *                                  - I2S_STATUS_TX_EMPTY
 *                                  - I2S_STATUS_TX_OVERRUN
 *
 * @return     FlagStatus_t
 *              - SET
 *              - RESET
 *
 */
FlagStatus_t I2S_GetStatus(I2S_Id_t i2sId, I2S_ChannelId_t channelId, I2S_Status_t i2sStatus)
{
    uint32_t intBitStatus;
    i2s_reg_w_t * I2Sxw = (i2s_reg_w_t *)(i2sRegWPtr[i2sId]);

    intBitStatus = (((I2Sxw->I2S_CHANNEL_REG[channelId].I2S_CHn_INT_CFG) & 
                                        (0x01UL << (uint32_t)i2sStatus)) >> (uint32_t)i2sStatus);


    return (FlagStatus_t)intBitStatus;
}

/**
 * @brief      Get channel all Interrupt Status
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  channelId:       Select the I2S Channel ID:
 *                                  -Channel0_ID
 *                                  -Channel1_ID
 *                                  -Channel2_ID
 *                                  -Channel3_ID
 *
 * @return     Channel Interrupt Status
 *
 */
uint32_t I2S_GetAllStatus(I2S_Id_t i2sId, I2S_ChannelId_t channelId)
{
    uint32_t chxIntStatus;
    i2s_reg_w_t * I2Sxw = (i2s_reg_w_t *)(i2sRegWPtr[i2sId]);

    chxIntStatus = I2Sxw->I2S_CHANNEL_REG[channelId].I2S_CHn_INT_CFG;

    return chxIntStatus;
}

/**
 * @brief      Enable or disable the I2S interrupt
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  - I2S_ID_0
 *                                  - I2S_ID_1
 * 
 * @param[in]  channelId:       Select the I2S Channel ID:
 *                                  - Channel0_ID
 *                                  - Channel1_ID
 *                                  - Channel2_ID
 *                                  - Channel3_ID
 * 
 * @param[in]  intType:         I2S interrupt type.
 *                                  - I2S_TXFIFO_OVERRUN_INT
 *                                  - I2S_TXFIFO_EMPTY_INT
 *                                  - I2S_RXFIFO_OVERRUN_INT
 *                                  - I2S_RXFIFO_DATA_AVAILIABLE_INT
 *
 * @param[in]  intMask:         MASK/UNMASK
 *
 * @return     none
 *
 */
void I2S_IntMask(I2S_Id_t i2sId, I2S_ChannelId_t channelId, I2S_Interrupt_t intType, 
                                                                    IntMask_t intMask)
{
    i2s_reg_w_t * I2Sxw = (i2s_reg_w_t *)(i2sRegWPtr[i2sId]);

    if(UNMASK == intMask)
    {
        i2sIntMaskStatus[i2sId][channelId] = i2sIntMaskStatus[i2sId][channelId] | \
                                I2S_IntStatusTable[intType] | I2S_IntMaskTable[intType];

        I2Sxw->I2S_CHANNEL_REG[channelId].I2S_CHn_INT_CFG = 
        ((I2Sxw->I2S_CHANNEL_REG[channelId].I2S_CHn_INT_CFG | I2S_IntMaskTable[intType]) & 0xFU);

    }
    else
    {
        I2Sxw->I2S_CHANNEL_REG[channelId].I2S_CHn_INT_CFG = 
        ((I2Sxw->I2S_CHANNEL_REG[channelId].I2S_CHn_INT_CFG & (~I2S_IntMaskTable[intType])) & 0xFU);

        i2sIntMaskStatus[i2sId][channelId] = i2sIntMaskStatus[i2sId][channelId] &
         (~I2S_IntStatusTable[intType]) & (~I2S_IntMaskTable[intType]);
    }   
}

/**
 * @brief      Clear the I2S interrupt
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  - I2S_ID_0
 *                                  - I2S_ID_1
 * 
 * @param[in]  channelId:       Select the I2S Channel ID:
 *                                  - Channel0_ID
 *                                  - Channel1_ID
 *                                  - Channel2_ID
 *                                  - Channel3_ID
 * 
 * @param[in]  intType:         I2S interrupt type.
 *                                  - I2S_TXFIFO_OVERRUN_INT
 *                                  - I2S_TXFIFO_EMPTY_INT
 *                                  - I2S_RXFIFO_OVERRUN_INT
 *                                  - I2S_RXFIFO_DATA_AVAILIABLE_INT
 *
 *
 * @return     none
 *
 */
void I2S_ClearInt(I2S_Id_t i2sId, I2S_ChannelId_t channelId, I2S_Interrupt_t intType)
{
    i2s_reg_w_t * I2Sxw = (i2s_reg_w_t *)(i2sRegWPtr[i2sId]);

    I2Sxw->I2S_CHANNEL_REG[channelId].I2S_CHn_INT_CFG = 
    ((I2Sxw->I2S_CHANNEL_REG[channelId].I2S_CHn_INT_CFG & 0xFU) | I2S_IntStatusTable[intType]);       
}

/**
 * @brief      Reset receive channel fifo.
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  channelId:       Select the I2S Channel ID:
 *                                  -Channel0_ID
 *                                  -Channel1_ID
 *                                  -Channel2_ID
 *                                  -Channel3_ID
 *
 * @return     none
 *
 */
void I2S_ChannelRxfifoReset( I2S_Id_t i2sId, I2S_ChannelId_t channelId)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    I2Sx->I2S_CHANNEL_REG[channelId].I2S_CHn_TRIGGER_LEVEL_CFG.CH_RXFIFO_RESET = 1U;
}

/**
 * @brief      Reset transmit channel fifo.
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  channelId:       Select the I2S Channel ID:
 *                                  -Channel0_ID
 *                                  -Channel1_ID
 *                                  -Channel2_ID
 *                                  -Channel3_ID
 *
 * @return     none
 *
 */
void I2S_ChannelTxfifoReset(I2S_Id_t i2sId, I2S_ChannelId_t channelId)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    I2Sx->I2S_CHANNEL_REG[channelId].I2S_CHn_TRIGGER_LEVEL_CFG.CH_TXFIFO_RESET = 1U;
}

/**
 * @brief      Configure the TXFIFO empty level.
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  channelId:       Select the I2S Channel ID:
 *                                  -Channel0_ID
 *                                  -Channel1_ID
 *                                  -Channel2_ID
 *                                  -Channel3_ID
 *
 * @param[in]  txfifoEmptyTriggerLevel: Configure the I2S TxFIFO Empty Trigger level.
 *                                          - I2S_TRIGGER_LEVEL_DEPTH_0
 *                                          - ......
 *                                          - I2S_TRIGGER_LEVEL_DEPTH_15
 * 
 * @return     none
 *
 */
void I2S_SetChannelTxfifoEmptyTriggerLevel(I2S_Id_t i2sId, I2S_ChannelId_t channelId, 
                                                I2S_FIFOTriggerLevel_t txfifoEmptyTriggerLevel)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    /*clear the default value 0x3*/
    I2Sx->I2S_CHANNEL_REG[channelId].I2S_CHn_TRIGGER_LEVEL_CFG.TXFIFO_EMPTY_TRIG_LEV = (uint32_t)txfifoEmptyTriggerLevel;
}

/**
 * @brief      Configure the RXFIFO full level.
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  channelId:       Select the I2S Channel ID:
 *                                  -Channel0_ID
 *                                  -Channel1_ID
 *                                  -Channel2_ID
 *                                  -Channel3_ID
 *
 * @param[in]  rxfifoEmptyTriggerLevel: Configure the I2S RxFIFO Empty Trigger level.
 *                                          - I2S_TRIGGER_LEVEL_DEPTH_0
 *                                          - ......
 *                                          - I2S_TRIGGER_LEVEL_DEPTH_15
 * 
 * @return     none
 *
 */
void I2S_SetChannelRxfifoFullTriggerLevel(I2S_Id_t i2sId, I2S_ChannelId_t channelId, 
                                                I2S_FIFOTriggerLevel_t rxfifoEmptyTriggerLevel)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    /*clear the default value 0x3*/
    I2Sx->I2S_CHANNEL_REG[channelId].I2S_CHn_TRIGGER_LEVEL_CFG.RXFIFO_FULL_TRIG_LEV = (uint32_t)rxfifoEmptyTriggerLevel;
}

/**
 * @brief      Reset I2S_CYCLE_TX_DATA register to the lowest enabled Transmit channel.
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @return     none
 *
 */
void I2S_CycleTxReset(I2S_Id_t i2sId)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    I2Sx->I2S_CYCLE_TX_RESET.CYCLE_TX_RESET = 1U;
}

/**
 * @brief      Reset I2S_CYCLE_RX_DATA register to the lowest enabled Receive channel.
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @return     none
 *
 */
void I2S_CycleRxReset(I2S_Id_t i2sId)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    I2Sx->I2S_CYCLE_RX_RESET.CYCLE_RX_RESET = 1U;
}

/**
 * @brief      Get the I2S default configuration.
 *
 * @param[out] config: Pointer to a I2S configuration structure.
 * 
 * @return     none
 *
 */
void I2S_GetDefaultConfig(I2S_Config_t *config)
{
    config->audioResolution = I2S_AUDIO_RESOLUTION_32BIT;
    config->i2sChannelsConfigStruct.channels[I2S_CHANNEL0_ID] = I2S_CHANNEL_ENABLE;
    config->i2sChannelsConfigStruct.channels[I2S_CHANNEL1_ID] = I2S_CHANNEL_ENABLE;
    config->i2sChannelsConfigStruct.channels[I2S_CHANNEL2_ID] = I2S_CHANNEL_DISABLE;
    config->i2sChannelsConfigStruct.channels[I2S_CHANNEL3_ID] = I2S_CHANNEL_DISABLE;
    config->i2sBclkNum = I2S_BCLK_32_CYCLES;
    config->i2sNumBclkGate = I2S_NO_BCLK_GATING;
    config->masterClkDiv = 0;
    config->rxfifoFullTriggerLevel = I2S_TRIGGER_LEVEL_DEPTH_15;
    config->txfifoEmptyTriggerLevel = I2S_TRIGGER_LEVEL_DEPTH_0;
}

/**
 * @brief      Initializes the I2S.
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  config: Pointer to a I2S configuration structure.
 * 
 * @return     none
 *
 */
void I2S_Init(I2S_Id_t i2sId, const I2S_Config_t *config)
{
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    uint8_t channelPollNo;

    /* Clear I2S_MODULE_EN enable. */
    I2S_Enable(i2sId,DISABLE);
    /* Clear I2S_MASTER_EN enable. */
    I2S_MasterDisable(i2sId);

    for(channelPollNo = 0; channelPollNo < I2S_CHANNEL_NUM; channelPollNo++)
    {
        /* Clear channel transmit or receiver enable. */
        I2Sx->I2S_CHANNEL_REG[channelPollNo].I2S_CHn_CFG.TX_EN = 0U;
        I2Sx->I2S_CHANNEL_REG[channelPollNo].I2S_CHn_CFG.RX_EN = 0U;

        I2S_SetChannelRxfifoFullTriggerLevel(i2sId, (I2S_ChannelId_t)channelPollNo, 
                                config->rxfifoFullTriggerLevel);
        I2S_SetChannelTxfifoEmptyTriggerLevel(i2sId, (I2S_ChannelId_t)channelPollNo, 
                                                            config->txfifoEmptyTriggerLevel);
                                                           
        (void)I2S_SetChannelRxResolution(i2sId, (I2S_ChannelId_t)channelPollNo, config->audioResolution);
        (void)I2S_SetChannelTxResolution(i2sId, (I2S_ChannelId_t)channelPollNo, config->audioResolution);
        I2S_IntMask(i2sId,(I2S_ChannelId_t)channelPollNo, I2S_INT_ALL, MASK);
    }
    /* I2S_MASTER_EN == 0 can be configured. */
    (void)I2S_SetGateBclkNum(i2sId, config->i2sNumBclkGate);
    (void)I2S_SetBclkNum(i2sId,config->i2sBclkNum);

    I2S_SetMasterClkDiv(i2sId, config->masterClkDiv);
    I2S_ModeSelect(i2sId,config->mode);
    I2S_Enable(i2sId,ENABLE);

}

/**
 * @brief      I2S Transmit data.
 *
 * @param[in]  i2sId:               Select the I2S ID:
 *                                      -I2S_ID_0
 *                                      -I2S_ID_1
 * 
 * @param[in]  channelId:           Select the I2S Channel ID:
 *                                      -Channel0_ID
 *                                      -Channel1_ID
 *                                      -Channel2_ID
 *                                      -Channel3_ID
 * 
 * @param[in]  i2sTransferMode:     Select I2S transfer mode:
 *                                      -I2S_CYCLIC_MODE
 *                                      -I2S_LEFT_CHANNEL_MODE
 *                                      -I2S_LEFT_CHANNEL_MODE
 * 
 * @param[in]  data:                I2S transmit data 
 * 
 * @return     none
 *
 */
void I2S_TransmitData(I2S_Id_t i2sId, I2S_ChannelId_t channelId, I2S_TransferMode_t i2sTransferMode,
                                                                             uint32_t data)
{
    i2s_reg_w_t * I2Sxw = (i2s_reg_w_t *) (i2sRegWPtr[i2sId]);
    i2s_reg_t * I2Sx = (i2s_reg_t *)(i2sRegPtr[i2sId]);
    
    /*Cyclic Transfer Mode*/
    if(I2S_CYCLIC_MODE == i2sTransferMode)
    {
        if((1U == I2Sx->I2S_CONTROL.I2S_TE) && (1U == I2Sx->I2S_CONTROL.I2S_MODULE_EN))
        {
            I2Sxw->I2S_CYCLE_TX_DATA = data;
        }
    }
    /*Left Transfer Mode*/
    else if(I2S_LEFT_CHANNEL_MODE == i2sTransferMode)
    {
        I2Sxw->I2S_CHANNEL_REG[channelId].I2S_CHn_LEFT_DATA = data;
    }
    /*Right Transfer Mode*/
    else
    {
        I2Sxw->I2S_CHANNEL_REG[channelId].I2S_CHn_RIGHT_DATA = data;
    }
}

/**
 * @brief      I2S receive data.
 *
 * @param[in]  i2sId:               Select the I2S ID:
 *                                      -I2S_ID_0
 *                                      -I2S_ID_1
 * 
 * @param[in]  channelId:           Select the I2S Channel ID:
 *                                      -Channel0_ID
 *                                      -Channel1_ID
 *                                      -Channel2_ID
 *                                      -Channel3_ID
 * 
 * @param[in]  i2sTransferMode:     Select I2S transfer mode:
 *                                      -I2S_CYCLIC_MODE
 *                                      -I2S_LEFT_CHANNEL_MODE
 *                                      -I2S_LEFT_CHANNEL_MODE
 * 
 * 
 * @return     data             Received data.
 *
 */
uint32_t I2S_ReceiveData(I2S_Id_t i2sId, I2S_ChannelId_t channelId, 
                                                                I2S_TransferMode_t i2sTransferMode)
{
    uint32_t data;
    i2s_reg_w_t * I2Sxw = (i2s_reg_w_t *) (i2sRegWPtr[i2sId]);
    /*Cyclic Transfer Mode*/
    if(I2S_CYCLIC_MODE == i2sTransferMode)
    {
        data = I2Sxw->I2S_CYCLE_RX_DATA;
    }
    /*Left Transfer Mode*/
    else if(I2S_LEFT_CHANNEL_MODE == i2sTransferMode)
    {
        data = I2Sxw->I2S_CHANNEL_REG[channelId].I2S_CHn_LEFT_DATA ;
    }
    /*Right Transfer Mode*/
    else
    {
        data = I2Sxw->I2S_CHANNEL_REG[channelId].I2S_CHn_RIGHT_DATA ;
    }
    return data;
}
/** @} end of group I2S_Public_Functions */

/** @} end of group I2S_definitions */

/** @} end of group Z20K14XM_Peripheral_Driver */
