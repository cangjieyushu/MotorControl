/**************************************************************************************************/
/**
 * @file      : Dma_Drv.h
 * @brief     : DMA module driver header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef DMA_DRV_H
#define DMA_DRV_H

#include "Common_Drv.h"

/** @defgroup Public_TypeDefinition 
 *  @{
 */

/**
 *  @brief DMA channel priority type definition
 */
typedef enum 
{
    DMA_CHN_PRIORITY0 = 0U,          /*!< dma channel priority 0, the lowest */
    DMA_CHN_PRIORITY1,               /*!< dma channel priority 1 */
    DMA_CHN_PRIORITY2,               /*!< dma channel priority 2 */
    DMA_CHN_PRIORITY3                /*!< dma channel priority 3, the highest*/
} Dma_ChannelPriorityType;

/**
 *  @brief DMA channel id type definition
 */ 
typedef enum 
{
    DMA_CHANNEL0 = 0U,               /*!< dma channel 0 */
    DMA_CHANNEL1,                    /*!< dma channel 1 */
    DMA_CHANNEL2,                    /*!< dma channel 2 */
    DMA_CHANNEL3                     /*!< dma channel 3 */
} Dma_ChannelType;

/**
 *  @brief DMA transfer size type definition
 */ 
typedef enum 
{
    DMA_TRANSFER_SIZE_1B = 0U,       /*!< dma once transfer size: 1 byte */
    DMA_TRANSFER_SIZE_2B,            /*!< dma once transfer size: 2 bytes */
    DMA_TRANSFER_SIZE_4B             /*!< dma once transfer size: 4 bytes */
} Dma_TransferSizeType;

/**
 *  @brief DMA behavior in debug mode type definition
 */ 
typedef enum 
{
    DMA_DEBUG_CONTINUE = 0U,                /*!< continue transfer in debug mode */
    DMA_DEBUG_HALT                          /*!< halt next transfer in debug mode */
} Dma_DebugBehaviorType;

/**
 *  @brief DMA behavior type definition when error occur
 */ 
typedef enum 
{
    DMA_ERROR_CONTINUE = 0U,                /*!< continue transfer when error occur */
    DMA_ERROR_HALT                          /*!< halt next transfer when error occur */
} Dma_ErrorBehaviorType;

/**
 *  @brief DMA init config type definition
 */ 
typedef struct 
{
    Dma_DebugBehaviorType DmaDebugBehavior;                /*!< dma behavior in debug mode */
    Dma_ErrorBehaviorType DmaErrorBehavior;                /*!< dma behavior in error mode */
} Dma_ConfigType;

/**
 *  @brief DMA interrupt type definition
 */ 
typedef enum
{
    DMA_INT_ERROR           = 0U,                /*!< dma error interrupt */
    DMA_INT_DONE,                                /*!< dma done interrupt */
    DMA_INT_ALL                                  /*!< dma all interrupt */
} Dma_IntType;

/**  
 *  @brief DMA error type definition
 */
typedef enum
{
    DMA_ERROR_PRIORITY      = 0U,               /*!< dma priority error */
    DMA_ERROR_SRCADDR,                          /*!< dma src addr unalign error */
    DMA_ERROR_SRCOFFSET,                        /*!< dma src offset unalign error */
    DMA_ERROR_DESTADDR,                         /*!< dma dest addr unalign error */
    DMA_ERROR_DESTOFFSET,                       /*!< dma dest offset unalign error */
    DMA_ERROR_TRANSFERNUM,                      /*!< dma transfer size unalign error */
    DMA_ERROR_SRCBUS,                           /*!< dma src bus error */
    DMA_ERROR_DESTBUS,                          /*!< dma dest bus error */
    DMA_ERROR_ALL                               /*!< dma all error type */
} Dma_ErrorType;

/**
 *  @brief DMA transfer configuration
 */
typedef struct 
{
    Dma_ChannelType Channel;                      /*!< specifies the channel used for dma transfer */
    Dma_ChannelPriorityType ChannelPriority;      /*!< dma channel priority - only used Fixed priority mode */
    uint32 SrcAddr;                           /*!< address pointing to the source data */
    uint32 DestAddr;                          /*!< address pointing to the destination data */
    sint16 MinorLoopSrcOffset;                 /*!< source address offset in minor loop */ 
    sint16 MinorLoopDestOffset;                /*!< destination address offset in minor loop */
    uint32 TransferByteNum;                   /*!< transfer bytes number in a minor loop */
    Dma_TransferSizeType SrcTransferSize;         /*!< source data transfer size */
    Dma_TransferSizeType DestTransferSize;        /*!< destination data transfer size */
    Common_ControlStateType DisableRequestAfterDoneCmd;  /*!< disable request after done control
                                                           - ENABLE: disable channel request after done 
                                                           - DISABLE: enable channel request after done */
} Dma_TransferConfigType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Public_MacroDefinition
 *  @{
 */

/** @} end of group Public_MacroDefinition */


/** @defgroup Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief      Dma initializes function
 *
 * @param[in]  ConfigPtr:     Pointer to a DMA configuration structure.
 *
 * @return none
 *
 */
void Dma_Init(const Dma_ConfigType * ConfigPtr);

/**
 * @brief      Get dma busy status function
 *
 * @param[in]  none
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: status set
 * @retval     COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Dma_GetDmaBusyStatus(void);

/**
 * @brief      Halt dma function
 *
 * @param[in]  Cmd: halt control
 *                  - COMMON_ENABLE: stall the dma start a new channels for transfer
 *                  - COMMON_DISABLE: dma is not stall
 *
 * @return none.
 *
 */
void Dma_EnableHalt(Common_ControlStateType Cmd);

/**
 * @brief      Get dma halt status function
 *
 * @param[in]  none
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: status set
 * @retval     COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Dma_GetHaltStatus(void);

/**
 * @brief      Enable dma channel request function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return none.
 *
 */
void Dma_EnableChannelRequest(Dma_ChannelType Channel);

/**
 * @brief      Disable dma channel request function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return none.
 *
 */
void Dma_DisableChannelRequest(Dma_ChannelType Channel);

/**
 * @brief      Get dma channel request status function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: status set
 * @retval     COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Dma_GetChannelRequestStatus(Dma_ChannelType Channel);

/**
 * @brief      Set dma channel priority function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * 
 * @param[in]  Priority: dma priority level
 *                              - DMA_CHN_PRIORITY0
 *                              - DMA_CHN_PRIORITY1
 *                              - DMA_CHN_PRIORITY2
 *                              - DMA_CHN_PRIORITY3
 *
 * @return none.
 *
 */
void Dma_SetChannelPriority(Dma_ChannelType Channel, 
                                     Dma_ChannelPriorityType Priority);

/**
 * @brief      Get dma channel priority function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return     Dma_ChannelPriorityType
 * @retval     DMA_CHN_PRIORITY0
 * @retval     DMA_CHN_PRIORITY1
 * @retval     DMA_CHN_PRIORITY2
 * @retval     DMA_CHN_PRIORITY3
 *
 */
Dma_ChannelPriorityType Dma_GetChannelPriority(Dma_ChannelType Channel);

/**
 * @brief      Set dma source address function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Address: dma transfer source address
 *
 * @return none.
 *
 */
void Dma_SetSrcAddr(Dma_ChannelType Channel, uint32 Address);

/**
 * @brief      Get dma source address function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return dma source address.
 *
 */
uint32 Dma_GetSrcAddr(Dma_ChannelType Channel);

/**
 * @brief      Set dma destination address function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Address: dma transfer destination address
 *
 * @return none.
 *
 */
void Dma_SetDestAddr(Dma_ChannelType Channel, uint32 Address);

/**
 * @brief      Get dma destination address function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return dma destination address.
 *
 */
uint32 Dma_GetDestAddr(Dma_ChannelType Channel);

/**
 * @brief      Set dma source address offset in minor loop function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Offset: dma source address offset in minor loop
 *
 * @return none.
 *
 */
void Dma_SetMinorLoopSrcOffset(Dma_ChannelType Channel, sint16 Offset);

/**
 * @brief      Set dma destination address offset in minor loop function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Offset: dma destination address offset in minor loop
 *
 * @return none.
 *
 */
void Dma_SetMinorLoopDestOffset(Dma_ChannelType Channel, sint16 Offset);

/**
 * @brief      Set dma source transfer size function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Size: dma transfer size
 *                              - DMA_TRANSFER_SIZE_1B
 *                              - DMA_TRANSFER_SIZE_2B
 *                              - DMA_TRANSFER_SIZE_4B
 *
 * @return none.
 *
 */
void Dma_SetSrcTransferSize(Dma_ChannelType Channel, 
                                     Dma_TransferSizeType Size);

/**
 * @brief      Set dma destination transfer size function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Size: dma transfer size
 *                              - DMA_TRANSFER_SIZE_1B
 *                              - DMA_TRANSFER_SIZE_2B
 *                              - DMA_TRANSFER_SIZE_4B
 *
 * @return none.
 *
 */
void Dma_SetDestTransferSize(Dma_ChannelType Channel, 
                                      Dma_TransferSizeType Size);

/**
 * @brief      Set dma transfer num of bytes in a minor loop function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Num: dma transfer num of bytes in a minor loop
 *
 * @return none.
 *
 */
void Dma_SetTransferByteNum(Dma_ChannelType Channel, uint32 Num);

/**
 * @brief      Disables/Enables the DMA request after the transfer complete function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Cmd: disable request after done
 *                  - COMMON_ENABLE: disables the DMA request after the transfer complete
 *                  - COMMON_DISABLE: enables the DMA request after the transfer complete
 *
 * @return none.
 *
 */
void Dma_SetDisableRequestAfterDone(Dma_ChannelType Channel, 
                                                Common_ControlStateType Cmd);

/**
 * @brief      Software trigger one channel dma transfer function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return none.
 *
 */
void Dma_TriggerChannelStart(Dma_ChannelType Channel);

/**
 * @brief      Software trigger all channel dma transfer function
 *
 * @param[in]  none
 *
 * @return none.
 *
 */
void Dma_TriggerAllChannelStart(void);

/**
 * @brief      Get one channel hardware DMA request status function
 *
 * @param[in]  Channel: Dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: status set
 * @retval     COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Dma_GetHwRequestStatus(Dma_ChannelType Channel);

/**
 * @brief      Get dma last error status function
 *
 * @param[in]  Error: error type
 *                              - DMA_ERROR_PRIORITY
 *                              - DMA_ERROR_SRCADDR
 *                              - DMA_ERROR_SRCOFFSET
 *                              - DMA_ERROR_DESTADDR
 *                              - DMA_ERROR_DESTOFFSET
 *                              - DMA_ERROR_TRANSFERNUM
 *                              - DMA_ERROR_SRCBUS
 *                              - DMA_ERROR_DESTBUS
 *                              - DMA_ERROR_ALL
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: status set
 * @retval     COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Dma_GetLastErrorStatus(Dma_ErrorType Error);

/**
 * @brief      Get last error channel id function
 *
 * @param[in]  none
 *
 * @return     Dma_ChannelType
 * @retval     DMA_CHANNEL0: dma channel 0 error
 * @retval     DMA_CHANNEL1: dma channel 1 error
 * @retval     DMA_CHANNEL2: dma channel 2 error
 * @retval     DMA_CHANNEL3: dma channel 3 error
 *
 */
Dma_ChannelType Dma_GetLastErrorChannel(void);

/**
 * @brief      Get channel int flag function
 *
 * @param[in]  Channel: Dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  IntType: int type
 *                      - DMA_INT_ERROR: error interrupt
 *                      - DMA_INT_DONE: done interrupt
 *                      - DMA_INT_ALL: all interrupt
 *
 * @return     Common_IntStatusType
 *                      - COMMON_SET: status set
 *                      - COMMON_RESET: status not set
 *
 */
Common_IntStatusType Dma_GetIntStatus(Dma_ChannelType Channel, Dma_IntType IntType);

/**
 * @brief      Clear channel int flag function
 *
 * @param[in]  Channel: dma channel id
 * @param[in]  IntType: int type
 *                      - DMA_INT_ERROR: error interrupt
 *                      - DMA_INT_DONE: done interrupt
 *                      - DMA_INT_ALL: all interrupt
 *
 * @return none.
 *
 */
void Dma_ClearIntStatus(Dma_ChannelType Channel, Dma_IntType IntType);

/**
 * @brief      Clear all channels int flag function
 *
 * @param[in]  IntType: int type
 *                      - DMA_INT_ERROR: error interrupt
 *                      - DMA_INT_DONE: done interrupt
 *                      - DMA_INT_ALL: all interrupt
 *
 * @return none.
 *
 */
void Dma_ClearAllChannelsIntStatus(Dma_IntType IntType);

/**
 * @brief      Get channel done flag function
 *
 * @param[in]  Channel: Dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return     Common_FlagStatusType
 *                              - COMMON_SET: status set
 *                              - COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Dma_GetDoneStatus(Dma_ChannelType Channel);

/**
 * @brief      Clear channel done flag function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return none.
 *
 */
void Dma_ClearDoneStatus(Dma_ChannelType Channel);

/**
 * @brief      Clear all channels done flag function
 *
 * @param[in]  none
 *
 * @return none.
 *
 */
void Dma_ClearAllChannelsDoneStatus(void);

/**
 * @brief      Get channel busy status function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return     Common_FlagStatusType
 *                              - COMMON_SET: status set
 *                              - COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Dma_GetChannelBusyStatus(Dma_ChannelType Channel);

/**
 * @brief      Set channel int mask function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  IntType: int type
 *                      - DMA_INT_ERROR: error interrupt
 *                      - DMA_INT_DONE: done interrupt
 *                      - DMA_INT_ALL: all interrupt
 * @param[in]  IntMask: int mask
 *                      - COMMON_UNMASK: int unmask
 *                      - COMMON_MASK: int mask
 *
 * @return none.
 *
 */
void Dma_SetIntMask(Dma_ChannelType Channel, Dma_IntType IntType, Common_IntMaskType IntMask);

/**
 * @brief      Install callback function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  IntType: select interrupt type
 *                      - DMA_INT_ERROR: error interrupt
 *                      - DMA_INT_DONE: done interrupt
 * @param[in]  CbFun: indicate callback function
 *
 * @return    none
 *
 */ 
void Dma_InstallCallBackFunc(Dma_ChannelType Channel, Dma_IntType IntType, 
                                      Isr_CbFuncType * CbFun);

/**
 * @brief      Dma transfer config function
 *
 * @param[in]  Config:   Pointer to dma transfer configuration structure.
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: command successful excuted
 * @retval     COMMON_ERR: command excution timeout
 *
 */
Common_ResultStatusType Dma_ConfigTransfer(const Dma_TransferConfigType * Config);

/** @} end of group Public_FunctionDeclaration */

#endif  /* DMA_DRV_H */
