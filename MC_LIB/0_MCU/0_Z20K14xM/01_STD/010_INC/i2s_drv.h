/**************************************************************************************************/
/**
 * @file     i2s_drv.h
 * @brief    I2S module driver header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#ifndef I2S_DRV_H
#define I2S_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  I2S
 *  @{
 */

/** @defgroup  I2S_Public_Types
 *  @{
 */

/**
 *  @brief I2S No. type definition
 */
typedef enum
{
    I2S_ID_0 = 0U                                   /*!< I2S0  */
#if (defined(DEV_Z20K148M))
    ,I2S_ID_1                                         /*!< I2S1  */
#endif
} I2S_Id_t;

/**
 *  @brief I2S channel id definition
 */
typedef enum
{
    I2S_CHANNEL0_ID = 0U,                           /*!< I2S Channel0 */
    I2S_CHANNEL1_ID = 1U,                           /*!< I2S Channel1 */
    I2S_CHANNEL2_ID = 2U,                           /*!< I2S Channel2 */
    I2S_CHANNEL3_ID = 3U                            /*!< I2S Channel3 */
} I2S_ChannelId_t;

/**
 *  @brief I2S master and slave type definition
 */
typedef enum
{
    I2S_MODE_SLAVE  = 0,                            /*!< I2S Slave Mode */
    I2S_MODE_MASTER = 1                             /*!< I2S Master Mode */
}I2S_Mode_t;

/**
 *  @brief I2S gate bclk cycles definition
 */
typedef enum
{
    I2S_NO_BCLK_GATING,                             /*!< I2S No Gating */
    I2S_BCLK_GATED_AFTER_12BCLK,                    /*!< I2S gated after the 12 serial bit clock cycles */
    I2S_BCLK_GATED_AFTER_16BCLK,                    /*!< I2S gated after the 16 serial bit clock cycles */
    I2S_BCLK_GATED_AFTER_20BCLK,                    /*!< I2S gated after the 20 serial bit clock cycles */
    I2S_BCLK_GATED_AFTER_24BCLK                     /*!< I2S gated after the 24 serial bit clock cycles */
}I2S_NumBclkGate_t;

/**
 *  @brief I2S bclk cycles definition
 */
typedef enum
{
    I2S_BCLK_16_CYCLES = 0U,                        /*!< I2S left or right word line contains 16 bit clock cycles */
    I2S_BCLK_24_CYCLES = 1U,                        /*!< I2S left or right word line contains 24 bit clock cycles */
    I2S_BCLK_32_CYCLES = 2U                         /*!< I2S left or right word line contains 32 bit clock cycles */
}I2S_BclkNum_t;

/**
 *  @brief I2S audio resolution definition
 */
typedef enum
{
    I2S_AUDIO_RESOLUTION_12BIT = 0x1U,              /*!< I2S 12-bit resolution */
    I2S_AUDIO_RESOLUTION_16BIT = 0x2U,              /*!< I2S 16-bit resolution */
    I2S_AUDIO_RESOLUTION_20BIT = 0x3U,              /*!< I2S 20-bit resolution */
    I2S_AUDIO_RESOLUTION_24BIT = 0x4U,              /*!< I2S 24-bit resolution */
    I2S_AUDIO_RESOLUTION_32BIT = 0x5U               /*!< I2S 32-bit resolution */
}I2S_AudioResolution_t;

/**
 *  @brief I2S FIFO trigger level definition
 */
typedef enum
{
    I2S_TRIGGER_LEVEL_DEPTH_0 = 0U,                 /*!< I2S Trigger Level 0 */
    I2S_TRIGGER_LEVEL_DEPTH_1 = 1U,                 /*!< I2S Trigger Level 1 */
    I2S_TRIGGER_LEVEL_DEPTH_2 = 2U,                 /*!< I2S Trigger Level 2 */
    I2S_TRIGGER_LEVEL_DEPTH_3 = 3U,                 /*!< I2S Trigger Level 3 */
    I2S_TRIGGER_LEVEL_DEPTH_4 = 4U,                 /*!< I2S Trigger Level 4 */
    I2S_TRIGGER_LEVEL_DEPTH_5 = 5U,                 /*!< I2S Trigger Level 5 */ 
    I2S_TRIGGER_LEVEL_DEPTH_6 = 6U,                 /*!< I2S Trigger Level 6 */
    I2S_TRIGGER_LEVEL_DEPTH_7 = 7U,                 /*!< I2S Trigger Level 7 */
    I2S_TRIGGER_LEVEL_DEPTH_8 = 8U,                 /*!< I2S Trigger Level 8 */
    I2S_TRIGGER_LEVEL_DEPTH_9 = 9U,                 /*!< I2S Trigger Level 9 */
    I2S_TRIGGER_LEVEL_DEPTH_10 =10U,                /*!< I2S Trigger Level 10 */
    I2S_TRIGGER_LEVEL_DEPTH_11 =11U,                /*!< I2S Trigger Level 11 */
    I2S_TRIGGER_LEVEL_DEPTH_12 =12U,                /*!< I2S Trigger Level 12 */
    I2S_TRIGGER_LEVEL_DEPTH_13 =13U,                /*!< I2S Trigger Level 13 */
    I2S_TRIGGER_LEVEL_DEPTH_14 =14U,                /*!< I2S Trigger Level 14 */
    I2S_TRIGGER_LEVEL_DEPTH_15 =15U                 /*!< I2S Trigger Level 15 */
}I2S_FIFOTriggerLevel_t;

/**
 *  @brief I2S transfer mode select: cyclic mode, left channel mode, right channel mode.
 */
typedef enum
{
    I2S_CYCLIC_MODE = 0U,                           /*!< I2S Channel Transmit Feature Enable */
    I2S_LEFT_CHANNEL_MODE = 1U,                     /*!< I2S Channel Receive Feature Enable */
    I2S_RIGHT_CHANNEL_MODE = 2U                     /*!< I2S Channel Transmit and Receive Feature Disable */
}I2S_TransferMode_t;

/**
 *  @brief I2S Interrupt typedef
 */
typedef enum
{
    I2S_RXFIFO_DATA_AVAILIABLE_INT = 0U,            /*!< I2S receive fifo data available interrupt */
    I2S_RXFIFO_OVERRUN_INT = 1U,                    /*!< I2S receive fifo overrun interrupt */
    I2S_TXFIFO_EMPTY_INT  =2U,                      /*!< I2S transmit fifo empty interrupt */
    I2S_TXFIFO_OVERRUN_INT = 3U,                    /*!< I2S transmit fifo overrun interrupt */
    I2S_INT_ALL                                     /*!< ALL I2S  */
} I2S_Interrupt_t;

/**
 *  @brief I2S Interrupt status typedef
 */
typedef enum
{
    I2S_STATUS_RX_FULL = 4U,       /*!< I2S RxFIFO Full Trigger Level Reach Status */
    I2S_STATUS_RX_OVERRUN = 5U,    /*!< I2S RxFIFO Full Overrun Status */
    I2S_STATUS_TX_EMPTY = 6U,      /*!< I2S TxFIFO Empty Trigger Level Reach Status */
    I2S_STATUS_TX_OVERRUN = 7U     /*!< I2S TxFIFO Overrun Status */
} I2S_Status_t;

/**
 *  @brief I2S channel feature definition
 */
typedef enum
{
    I2S_CHANNEL_DISABLE = 0U,        /*!< I2S Channel Transmit and Receive Feature Disable */
    I2S_CHANNEL_ENABLE  = 1U         /*!< I2S Channel Transmit and Receive Feature Enable */
}I2S_ChannelEnable_t;

/**
 *  @brief I2S channel feature enable structure definition
 */
typedef struct
{
    I2S_ChannelEnable_t channels[4];                         /*!< I2S Channel0~3 function status */
}I2S_ChannelsEnableConfig_t;

/**
 *  @brief I2S configuration structure typedef
 */
typedef struct
{
    I2S_Mode_t mode;                                                    /*!< Configure I2S mode:
                                                                            - I2S_MODE_SLAVE: I2S Slave Mode Select
                                                                            - I2S_MODE_MASTER: I2S Master Mode Select
                                                                        */
    I2S_NumBclkGate_t i2sNumBclkGate;                                   /*!< Configure I2S gate bclk cycles:
                                                                            - I2S_NO_BCLK_GATING: I2S No Gating
                                                                            - I2S_BCLK_GATED_AFTER_12BCLK: I2S gated after the 12 serial bit clock cycles
                                                                            - I2S_BCLK_GATED_AFTER_16BCLK: I2S gated after the 16 serial bit clock cycles
                                                                            - I2S_BCLK_GATED_AFTER_20BCLK: I2S gated after the 20 serial bit clock cycles
                                                                            - I2S_BCLK_GATED_AFTER_24BCLK: I2S gated after the 24 serial bit clock cycles
                                                                            - I2S_BCLK_GATED_AFTER_32BCLK: I2S gated after the 32 serial bit clock cycles
                                                                        */
    I2S_BclkNum_t    i2sBclkNum;                                        /*!< Configure I2S bclk cycles in left or right word line:
                                                                            - I2S_BCLK_16_CYCLES: word line contains 16 bit clock cycles
                                                                            - I2S_BCLK_24_CYCLES: word line contains 24 bit clock cycles
                                                                            - I2S_BCLK_32_CYCLES: word line contains 32 bit clock cycles
                                                                        */
    uint8_t masterClkDiv;                                               /*!< Configure I2S master clock divider, actual division value is (masterClkDiv+1)*2 */
    I2S_ChannelsEnableConfig_t i2sChannelsConfigStruct;                 /*!< Configure I2S channel0~channel3 transmit or receive function enable:
                                                                        - channelTransmitReceive[0]: I2S channel0 transmit or receive function enable
                                                                        - channelTransmitReceive[1]: I2S channel1 transmit or receive function enable
                                                                        - channelTransmitReceive[2]: I2S channel2 transmit or receive function enable
                                                                        - channelTransmitReceive[3]: I2S channel3 transmit or receive function enable
                                                                        */
    I2S_AudioResolution_t audioResolution;                              /*!< Configure I2S channel resolution:
                                                                            - I2S_AUDIO_RESOLUTION_12BIT: I2S 12 bit audio resolution
                                                                            - I2S_AUDIO_RESOLUTION_16BIT: I2S 16 bit audio resolution
                                                                            - I2S_AUDIO_RESOLUTION_20BIT: I2S 20 bit audio resolution
                                                                            - I2S_AUDIO_RESOLUTION_24BIT: I2S 24 bit audio resolution
                                                                            - I2S_AUDIO_RESOLUTION_32BIT: I2S 32 bit audio resolution
                                                                        */
    I2S_FIFOTriggerLevel_t rxfifoFullTriggerLevel;                      /*!< Configure I2S channel receive FIFO full trigger level:
                                                                            - I2S_TRIGGER_LEVEL_DEPTH_0: I2S receive FIFO trigger level 0
                                                                            ......
                                                                            - I2S_TRIGGER_LEVEL_DEPTH_15: I2S receive FIFO trigger level 15
                                                                        */
    I2S_FIFOTriggerLevel_t txfifoEmptyTriggerLevel;                     /*!< Configure I2S channel transmit FIFO empty trigger level:
                                                                            - I2S_TRIGGER_LEVEL_DEPTH_0: I2S transmit FIFO empty trigger level 0
                                                                            ......
                                                                            - I2S_TRIGGER_LEVEL_DEPTH_15: I2S transmit FIFO empty trigger level 15
                                                                        */
}I2S_Config_t;

/** @} end of group I2S_Public_Types definitions */

/** @defgroup I2S_Public_FunctionDeclaration
 *  @brief I2S function statement
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
void I2S_IntHandler(I2S_Id_t i2sId);

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
void I2S_InstallCallBackFunc(I2S_Id_t i2sId,I2S_ChannelId_t channelId, I2S_Interrupt_t I2SIntType,isr_cb_t * cbFun);

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
ResultStatus_t I2S_ResetAllRxfifo(I2S_Id_t i2sId);

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
ResultStatus_t I2S_ResetAllTxfifo(I2S_Id_t i2sId);

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
ResultStatus_t I2S_EnableReceiver(I2S_Id_t i2sId,ControlState_t status);

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
ResultStatus_t I2S_EnableTransmitter( I2S_Id_t i2sId,ControlState_t status);

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
void I2S_Enable(I2S_Id_t i2sId,ControlState_t status);

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
void I2S_SetMasterClkDiv(I2S_Id_t i2sId,uint8_t masterClkDiv);

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
ResultStatus_t I2S_SetGateBclkNum(I2S_Id_t i2sId,I2S_NumBclkGate_t i2sNumBclkGate);

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
ResultStatus_t I2S_SetBclkNum(I2S_Id_t i2sId,I2S_BclkNum_t i2sBclkNum);

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
void I2S_ModeSelect(I2S_Id_t i2sId,I2S_Mode_t mode);

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
void I2S_MasterDisable(I2S_Id_t i2sId);

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
                                                            I2S_AudioResolution_t audioResolution);

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
                                                            I2S_AudioResolution_t audioResolution);                                                           

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
ResultStatus_t I2S_EnableChannelRx(I2S_Id_t i2sId, I2S_ChannelsEnableConfig_t i2sChannelsConfigStruct);

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
ResultStatus_t I2S_EnableChannelTx(I2S_Id_t i2sId, I2S_ChannelsEnableConfig_t i2sChannelsConfigStruct);

/**
 * @brief      Get Specific Interrupt Status
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
 *                                  - I2S_RXFIFO_FULL_TRIGGER_LEVEL_REACH
 *                                  - I2S_RXFIFO_OVERRUN
 *                                  - I2S_TXFIFO_EMPTY_TRIGGER_LEVEL_REACH
 *                                  - I2S_TXFIFO_OVERRUN
 *
 * @return     FlagStatus_t
 *              - SET
 *              - RESET
 *
 */
FlagStatus_t I2S_GetStatus(I2S_Id_t i2sId,I2S_ChannelId_t channelId,I2S_Status_t i2sStatus);

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
 * @return     Channelx All Interrupt Status
 *
 */
uint32_t I2S_GetAllStatus(I2S_Id_t i2sId,I2S_ChannelId_t channelId);

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
void I2S_IntMask(I2S_Id_t i2sId,I2S_ChannelId_t channelId,I2S_Interrupt_t intType, IntMask_t intMask);

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
void I2S_ClearInt(I2S_Id_t i2sId, I2S_ChannelId_t channelId, I2S_Interrupt_t intType);

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
void I2S_ChannelRxfifoReset( I2S_Id_t i2sId,I2S_ChannelId_t channelId);

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
void I2S_ChannelTxfifoReset(I2S_Id_t i2sId,I2S_ChannelId_t channelId);

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
void I2S_SetChannelTxfifoEmptyTriggerLevel(I2S_Id_t i2sId,I2S_ChannelId_t channelId,I2S_FIFOTriggerLevel_t txfifoEmptyTriggerLevel);

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
void I2S_SetChannelRxfifoFullTriggerLevel(I2S_Id_t i2sId,I2S_ChannelId_t channelId,I2S_FIFOTriggerLevel_t rxfifoEmptyTriggerLevel);

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
void I2S_CycleTxReset(I2S_Id_t i2sId);

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
void I2S_CycleRxReset(I2S_Id_t i2sId);

/**
 * @brief      Get the I2S default configuration.
 *
 * @param[in]  config:          Pointer to a I2S configuration structure.
 * 
 * @return     none
 *
 */
void I2S_GetDefaultConfig(I2S_Config_t *config);

/**
 * @brief      Initializes the I2S.
 *
 * @param[in]  i2sId:           Select the I2S ID:
 *                                  -I2S_ID_0
 *                                  -I2S_ID_1
 * 
 * @param[in]  config:          Pointer to a I2S configuration structure.
 * 
 * @return     none
 *
 */
void I2S_Init(I2S_Id_t i2sId,const I2S_Config_t *config);

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
void I2S_TransmitData(I2S_Id_t i2sId, I2S_ChannelId_t channelId, I2S_TransferMode_t i2sTransferMode, uint32_t data);

/**
 * @brief      I2S Receive data.
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
uint32_t I2S_ReceiveData(I2S_Id_t i2sId, I2S_ChannelId_t channelId, I2S_TransferMode_t i2sTransferMode);
/** @} end of group I2S_Public_FunctionDeclaration */

/** @} end of group I2S  */

/** @} end of group Z20K14XM_Peripheral_Driver */
#endif /* End of I2S_DRV_H*/
