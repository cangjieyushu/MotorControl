/**************************************************************************************************/
/**
 * @file      : Z20K11xM_can.h
 * @brief     : CAN driver module header file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef Z20K11XM_CAN_H
#define Z20K11XM_CAN_H

#include "Z20K11xM_drv.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @addtogroup  CAN
 *  @{
 */

/** @defgroup CAN_Public_Types 
 *  @{
 */

/**
 *  @brief CAN ID type definition
 */
typedef enum 
{
    CAN_ID_0 = 0U,    /*!< CAN0 */
#if ( 2U == CAN_INSTANCE_NUM ) 
    CAN_ID_1          /*!< CAN1 */ 
#endif
} CAN_Id_t;

/**
 *  @brief RxFIFO transfer type definition
 */
typedef enum 
{
    CAN_RXFIFO_INTERRUPTS = 0U,    /*!< Use interrupts for RxFIFO. */
    CAN_RXFIFO_DMA                 /*!< Use DMA for RxFIFO. */ 
} CAN_RxfifoTransfer_t;


/**
 *  @brief CAN Message ID type definition
 */
typedef enum 
{
    CAN_MSG_ID_STD = 0U,         /*!< Standard ID*/
    CAN_MSG_ID_EXT               /*!< Extended ID*/
} CAN_MsgId_t;


/**
 *  @brief CAN Rx mask type definition
 */
typedef enum 
{
    CAN_RX_MASK_GLOBAL = 0U,      /*!< Rx global mask*/
    CAN_RX_MASK_INDIVIDUAL        /*!< Rx individual mask*/
} CAN_RxMask_t;

/**
 *  @brief ID filter formats for Rx FIFO type definition
 */
typedef enum 
{
    CAN_RX_FIFO_ID_FORMAT_A = 0U, /*!< One full ID (standard and extended)*/
    CAN_RX_FIFO_ID_FORMAT_B,      /*!< Two full standard IDs or two partial 
                                      14-bit extended IDs*/
    CAN_RX_FIFO_ID_FORMAT_C,      /*!< Four partial 8-bit Standard,extended IDs */
    CAN_RX_FIFO_ID_FORMAT_D       /*!< All frames rejected.*/
} CAN_RxFifoIdFormat_t;

/**
 *  @brief CAN operation mode type definition
 */
typedef enum 
{
    CAN_MODE_NORMAL = 0U,        /*!< Normal mode or user mode */
    CAN_MODE_LISTEN_ONLY,        /*!< Listen-only mode */
    CAN_MODE_LOOPBACK,           /*!< Loop-back mode */
    CAN_MODE_FREEZE,             /*!< Freeze mode */
    CAN_MODE_DISABLE             /*!< Module disable mode */
} CAN_Mode_t;


 
/**
 *  @brief CAN Rx FIFO ID filters number type definition
 */
typedef enum
{
    CAN_RX_FIFO_ID_FILTERS_8   = 0x0,         /*!<   8 Rx FIFO Filters */
    CAN_RX_FIFO_ID_FILTERS_16  = 0x1,         /*!<  16 Rx FIFO Filters */
    CAN_RX_FIFO_ID_FILTERS_24  = 0x2,         /*!<  24 Rx FIFO Filters */
    CAN_RX_FIFO_ID_FILTERS_32  = 0x3,         /*!<  32 Rx FIFO Filters */
    CAN_RX_FIFO_ID_FILTERS_40  = 0x4,         /*!<  40 Rx FIFO Filters */
    CAN_RX_FIFO_ID_FILTERS_48  = 0x5,         /*!<  48 Rx FIFO Filters */
    CAN_RX_FIFO_ID_FILTERS_56  = 0x6,         /*!<  56 Rx FIFO Filters */
    CAN_RX_FIFO_ID_FILTERS_64  = 0x7,         /*!<  64 Rx FIFO Filters */
    CAN_RX_FIFO_ID_FILTERS_72  = 0x8,         /*!<  72 Rx FIFO Filters */
    CAN_RX_FIFO_ID_FILTERS_80  = 0x9,         /*!<  80 Rx FIFO Filters */
    CAN_RX_FIFO_ID_FILTERS_88  = 0xA,         /*!<  88 Rx FIFO Filters */
    CAN_RX_FIFO_ID_FILTERS_96  = 0xB,         /*!<  96 Rx FIFO Filters */
    CAN_RX_FIFO_ID_FILTERS_104 = 0xC,         /*!< 104 Rx FIFO Filters */
    CAN_RX_FIFO_ID_FILTERS_112 = 0xD,         /*!< 112 Rx FIFO Filters */
    CAN_RX_FIFO_ID_FILTERS_120 = 0xE,         /*!< 120 Rx FIFO Filters */
    CAN_RX_FIFO_ID_FILTERS_128 = 0xF          /*!< 128 Rx FIFO Filters */
} CAN_RxFifoIdFilterNum_t;



/**
 *  @brief CAN FD payload size definition
 */
typedef enum
{
    CAN_PAYLOAD_SIZE_8 = 0U,  /*!< CAN FD message buffer payload size in bytes*/
    CAN_PAYLOAD_SIZE_16 ,     /*!< CAN FD message buffer payload size in bytes*/
    CAN_PAYLOAD_SIZE_32 ,     /*!< CAN FD message buffer payload size in bytes*/
    CAN_PAYLOAD_SIZE_64       /*!< CAN FD message buffer payload size in bytes*/
} CAN_FdPayloadSize_t;

/**
 *  @brief CAN tx priority type definition
 */
typedef enum 
{
    CAN_TX_PRI_HIGH_PRI_FIRST = 0U,      /*!< highest-priority mailbox first,
                                              the priority is decided by the 
                                              CAN frame. The lower value has an
                                              higher priority  */
    CAN_TX_PRI_LOW_NUM_MB_FIRST,          /*!< lowest-number mailbox first */
    CAN_TX_PRI_LOCAL_PRI_EN,              /*!< local priority is enabled. The
                                              priority is decided by the local
                                              priority field which is not part
                                              of CAN frame*/
} CAN_TxPriMode_t;

/**
 *  @brief CAN MB code type definition
 */
typedef enum
{
    CAN_MB_RX_INACTIVE    = 0x0, /*!< MB is not active.*/
    CAN_MB_RX_FULL        = 0x2, /*!< MB is full.*/
    CAN_MB_RX_EMPTY       = 0x4, /*!< MB is active and empty.*/
    CAN_MB_RX_OVERRUN     = 0x6, /*!< MB is overwritten into a full buffer.*/
    CAN_MB_RX_RANSWER     = 0xA, /*!< A frame was configured to recognize a 
                                    Remote Request Frame and transmit a Response 
                                    Frame in return.*/
    CAN_MB_TX_INACTIVE    = 0x08, /*!< MB is not active.*/
    CAN_MB_TX_ABORT       = 0x09, /*!< MB is aborted.*/
    CAN_MB_TX_DATA_REMOTE = 0x0C, /*!< MB is a TX Data Frame(MB RTR = 0). or a
                                       remote request frame (MB RTR = 1)*/
    CAN_MB_TX_TANSWER     = 0x0E, /*!< MB is a Tx Response frame from an 
                                      incoming Remote Request frame. */
}CAN_MbCode_t;


/**
 *  @brief CAN interrupt type definition
 */
typedef enum
{    
    CAN_INT_BUS_OFF = 0U,           /*!< CAN interrupt: bus off */
    CAN_INT_ERR = 1U,               /*!< CAN interrupt: error */    
    CAN_INT_TXW = 2U,               /*!< CAN interrupt: TX warning */
    CAN_INT_RXW = 3U,               /*!< CAN interrupt: RX warning */
    CAN_INT_BUS_OFF_DONE = 4U,      /*!< CAN interrupt: bus off done*/
    CAN_INT_ERR_FAST = 5U,          /*!< CAN interrupt: error detected in Data 
                                         Phase of CAN FD frames with BRS bit
                                         set*/
    CAN_INT_SELF_WAKEUP = 6U,       /*!< CAN interrupt: self wake up */
    CAN_INT_RXFIFO_FRAME = 7U,      /*!< CAN interrupt: RX FIFO frame available */
    CAN_INT_RXFIFO_WARNING = 8U,    /*!< CAN interrupt: RX FIFO warning */
    CAN_INT_RXFIFO_OVERFLOW = 9U,   /*!< CAN interrupt: RX FIFO overflow */
    CAN_INT_HOST_MEM_ERR = 10U,     /*!< CAN interrupt: non-correctable errors 
                                         detected in memory reads issued by 
                                         the CPU */
    CAN_INT_CAN_MEM_ERR = 11U,       /*!< CAN interrupt: non-correctable errors 
                                          detected in memory reads issued by 
                                          the CAN */
    CAN_INT_COR_MEM_ERR = 12U,       /*!< CAN interrupt: correctable errors
                                          detected in memory reads  */
    CAN_INT_PN_WAKEUP_MATCH = 13U,   /*!< CAN interrupt: wakeup by match */
    CAN_INT_PN_WAKEUP_TIMEOUT = 14U, /*!< CAN interrupt: wakeup by timeout */
    CAN_INT_MB = 15U,                /*!< CAN interrupt: MB transmission/reception 
                                         completed or RX FIFO related interrupt */
    CAN_INT_ALL =16U                     /*!< CAN all interrupts */
} CAN_Int_t;

/** 
 * @brief CAN Pretended Networking matching schemes
 */
typedef enum
{
    CAN_PN_MATCH_EXACT,   /*!< Match an exact target value. */
    CAN_PN_MATCH_GEQ,     /*!< Match greater than or equal to a specified 
                               target value. */
    CAN_PN_MATCH_LEQ,     /*!< Match less than or equal to a specified target 
                               value. */
    CAN_PN_MATCH_RANGE    /*!< Match inside a range, greater than or equal to a 
                               specified lower limit and smaller than or
                               equal to a specified upper limit. */
} CAN_PnFilterMatch_t;

/** 
 * @brief CAN Pretended Networking filtering combinations
 */
typedef enum
{
    CAN_FILTER_ID,                 /*!< Message ID filtering only */
    CAN_FILTER_ID_PAYLOAD,         /*!< Message ID and payload filtering */
    CAN_FILTER_ID_NTIMES,          /*!< Message ID filtering occurring a 
                                        specified number of times */
    CAN_FILTER_ID_PAYLOAD_NTIMES   /*!< Message ID and payload filtering  
                                        occurring a specified number of times */
} CAN_PnFilterCombination_t;
                                            
/**
 *  @brief CAN error status type definition
 */
typedef enum
{   
    CAN_STATUS_RXWRN = 8U,             /*!< CAN status: Rx Error Warning */
    CAN_STATUS_TXWRN = 9U,             /*!< CAN status: Tx Error Warning */
    CAN_STATUS_STUFF_ERR = 10U,        /*!< CAN status: stuff error */
    CAN_STATUS_FORM_ERR = 11U,         /*!< CAN status: form error */
    CAN_STATUS_CRC_ERR = 12U,          /*!< CAN status: CRC error */
    CAN_STATUS_ACK_ERR = 13U,          /*!< CAN status: ACK error */
    CAN_STATUS_BIT0_ERR = 14U,         /*!< CAN status: bit0 error */
    CAN_STATUS_BIT1_ERR = 15U,         /*!< CAN status: bit1 error */
    CAN_STATUS_ERROVR = 21U,           /*!< CAN status: error overrun */
    CAN_STATUS_STUFF_ERR_FAST = 26U,   /*!< CAN status: stuff error in FD frame 
                                            with the BRS bit set */
    CAN_STATUS_FORM_ERR_FAST = 27U,    /*!< CAN status: form error in FD frame 
                                            with the BRS bit set */
    CAN_STATUS_CRC_ERR_FAST = 28U,     /*!< CAN status: CRC error in FD frame 
                                            with the BRS bit set */
    CAN_STATUS_ACK_ERR_FAST = 29U,     /*!< CAN status: ACK error in FD frame 
                                            with the BRS bit set */
    CAN_STATUS_BIT0_ERR_FAST = 30U,    /*!< CAN status: bit0 error in FD frame 
                                            with the BRS bit set*/
    CAN_STATUS_BIT1_ERR_FAST = 31U,    /*!< CAN status: bit1 error in FD frame 
                                            with the BRS bit set*/    
    CAN_STATUS_ALL = 32U               /*!< CAN all status */
} CAN_Status_t;

/**
 *  @brief CAN State type definition
 */
typedef enum
{    
    CAN_STATE_NOT_SYNC = 0U,       /*!< it is not synchronized to CAN bus*/
    CAN_STATE_IDLE,                /*!< CAN bus is in idle state */
    CAN_STATE_TX,                  /*!< CAN is transmitting */
    CAN_STATE_RX,                  /*!< CAN is receiving */
    CAN_STATE_INVALID,             /*!< this is not a valid state */
} CAN_State_t;

/**
 *  @brief CAN Fault Confinement State definition
 */
typedef enum
{    
    CAN_FAULT_CONF_STATE_ERROR_ACTIVE = 0U,       /*!< CAN Fault Confinement 
                                                       State: error active*/
    CAN_FAULT_CONF_STATE_ERROR_PASSIVE,           /*!< CAN Fault Confinement 
                                                       State: error passive */
    CAN_FAULT_CONF_STATE_BUS_OFF,                 /*!< CAN Fault Confinement 
                                                       State: bus off */

} CAN_FaultConfState_t;

/**
 *  @brief CAN bus off recovery scheme type definition
 */
typedef enum
{    
    CAN_BUS_OFF_RECOV_AUTO = 0U,    /*!< automatic recovering from Bus Off
                                         state occurs according to the CAN 
                                         Specification */
    CAN_BUS_OFF_RECOV_MANUAL = 1U,  /*!< recover from bus off manually */
} CAN_BusOffRecovery_t;

/**
 *  @brief CAN bit timing configuration structures
 */
typedef struct 
{
    uint32_t propSeg;         /*!< Propagation segment*/
    uint32_t phaseSeg1;       /*!< Phase segment 1*/
    uint32_t phaseSeg2;       /*!< Phase segment 2*/
    uint32_t preDivider;      /*!< Clock prescaler division factor*/
    uint32_t rJumpwidth;      /*!< Resync jump width*/
} CAN_BitTiming_t;

/**
 *  @brief CAN RX FIFO ID filter table element structure
 */
typedef struct
{
    FlagStatus_t isRemoteFrame;      /*!< Remote frame*/
    FlagStatus_t isExtendedFrame;    /*!< Extended frame*/
    uint32_t id;             /*!< Rx FIFO ID filter element*/
} CAN_IdFilter_t;

/**
 *  @brief CAN massage info structure
 */
typedef struct
{
    CAN_MsgId_t idType;         /*!< Type of message ID (standard or extended)*/
    uint8_t dataLen;            /*!< Length of Data in Bytes*/
    FlagStatus_t remoteFlag;    /*!< Specifies if the frame is standard or remote */
    ControlState_t fdEn;        /*!< Enable or disable FD*/
    uint8_t fdPadding;          /*!< Set a value for padding. It will be used 
                                      when the data length code (DLC) specifies
                                      a bigger data size than data_length to 
                                      fill the MB */
    ControlState_t brsEn;       /*!< Enable bit rate switch inside a CAN FD 
                                     format frame*/
} CAN_MessageInfo_t;

/** 
 * @brief CAN message buffer structure
 */
typedef struct
{
    uint32_t cs;                        /*!< Code and Status*/
    uint32_t msgId;                     /*!< Message ID*/    
    uint8_t data[64];                   /*!< Data bytes of the CAN message*/
    uint8_t dataLen;                    /*!< Length of data in bytes */    
} CAN_MsgBuf_t;

/** 
 * @brief CAN configuration
 */
typedef struct
{
    uint32_t mbMaxNum;                         /*!< The maximum number of 
                                                    Message Buffers */    
    ControlState_t rxFifoEn;                   /*!< select if use RX FIFO */
    CAN_RxFifoIdFilterNum_t rxFifoIdFilterNum; /*!< The number of RX FIFO ID 
                                               filters needed. It is only valid 
                                                when RXFIFO is enabled */
    CAN_RxfifoTransfer_t transferType;         /*!< Specifies if the Rx FIFO 
                                               uses interrupts or DMA. It is 
                                             only valid when RXFIFO is enabled */
    CAN_Mode_t mode;                           /*!< CAN operation modes */
    CAN_BitTiming_t bitTiming;                 /*!< The bitrate used for 
                                               standard frames or for the 
                                               arbitration phase of FD frames. */
    ControlState_t fdEn;                       /*!< Enable/Disable the 
                                                Flexible Data Rate feature. */
    CAN_FdPayloadSize_t payload0;              /*!< The payload size of the 
                                               mailboxes in region0 specified  
                                               in bytes. It is only valid when 
                                         Flexible data rate feature is enabled*/
    CAN_FdPayloadSize_t payload1;              /*!< The payload size of the 
                                           mailboxes in region1 specified in bytes. 
                                               It is only valid when Flexible 
                                                data rate feature is enabled */    
    CAN_BitTiming_t bitTimingFdData;              /*!< The bitrate used for the 
                                                   data phase of FD frames. It is
                                                   only valid when Flexible data 
                                                  rate feature is enabled */
}CAN_Config_t;

/** 
 * @brief CAN Pretended Networking ID filter
 */
typedef struct
{
    CAN_MsgId_t idType;        /*!< Specifies if the ID is standard or extended. */
    FlagStatus_t remoteFlag;   /*!< Specifies if the frame is data or remote frame. */
    uint32_t id;               /*!< Specifies the ID value. */
} CAN_PnIdFilter_t;

/** 
 * @brief CAN Pretended Networking payload filter
 */
typedef struct
{
    uint8_t dlcLow;       /*!< Specifies the lower limit of the payload size. */
    uint8_t dlcHigh;      /*!< Specifies the upper limit of the payload size. */
    uint8_t payload1[8U]; /*!< Specifies the payload to be matched (for MATCH_EXACT), 
                            the lower limit (for MATCH_GEQ and MATCH_RANGE) or 
                            the upper limit (for MATCH_LEQ). */
    uint8_t payload2[8U]; /*!< Specifies the mask (for MATCH_EXACT) or the upper 
                               limit (for MATCH_RANGE). */
} CAN_PnPayloadFilter_t;

/** 
 * @brief CAN Pretended Networking configuration structure
 */
typedef struct
{
    CAN_PnFilterCombination_t matchScheme; /*!< Defines the filtering scheme used. */
    uint16_t numMatches;                   /*!< The number of matches needed 
                                         before generating an wake up event. */ 
    CAN_PnFilterMatch_t idFilterType;      /*!< Defines the ID filtering scheme. */
    CAN_PnIdFilter_t idFilter1;            /*!< The configuration of the first 
                                           ID filter (match exact / lower 
                                            limit / upper limit). */
    CAN_PnIdFilter_t idFilter2;            /*!< The configuration of the second
                                              ID filter (mask / upper limit). */
    CAN_PnFilterMatch_t payloadFilterType; /*!< Defines the payload filtering scheme. */
    CAN_PnPayloadFilter_t payloadFilter;   /*!< The configuration of the payload filter. */
} CAN_PnMatchConfig_t;


/** 
 * @brief CAN Pretended Networking configuration structure
 */
typedef struct
{
    ControlState_t wakeUpTimeout;        /*!< Specifies if an wake up event is 
                                              triggered on timeout. */
    uint16_t timeout;                    /*!< Defines a timeout value that 
                                             generates an wake up event if 
                                             wakeUpTimeout is true. */
    ControlState_t wakeUpMatch;          /*!< Specifies if an wake up event is 
                                              triggered on match. */
    CAN_PnMatchConfig_t matchConfig;     /*!< configuration for match wakeup event. */
} CAN_PnConfig_t;

/**
 *  @brief CAN MB callback function type
 */
typedef void (*can_mb_cb_t)(uint32_t mbIdx);

/** @} end of group CAN_Public_Types */

/** @defgroup CAN_Public_Constants
 *  @{
 */
#define CAN_MAX_MB_NUM   64U
#define CAN_RAM_SIZE_IN_BYTE      1024
#define CAN_RAM_SIZE_IN_WORD      (CAN_RAM_SIZE_IN_BYTE/4)
#define CAN_ABORT_EN    1U

/** @} end of group CAN_Public_Constants */

/** @defgroup CAN_Public_Macro
 *  @{
 */

/** @} end of group CAN_Public_Macro */

/** @defgroup CAN_Public_FunctionDeclaration
 *  @brief CAN functions declaration
 *  @{
 */

/**
 * @brief      Initializes the CAN peripheral. This function will do soft reset
 *             for CAN module, and initialize CAN with provided parameters. This
 *             function needs to be called first before other config functions.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  config: points to the configuration struct
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_Init(CAN_Id_t id, const CAN_Config_t *config);

/**
 * @brief      Deinit the CAN peripheral. This function disables all CAN 
               interrupts, and disable the CAN
 *
 * @param[in]  id: select the CAN ID
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_Deinit(CAN_Id_t id);

/**
 * @brief      Set operation mode.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mode: select the CAN operation mode
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetOperationMode(CAN_Id_t id, CAN_Mode_t mode);

/**
 * @brief      Disable/Enable self reception.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  ctrl: ENABLE/DISABLE
 *
 * @return      status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetSelfRec(CAN_Id_t id, ControlState_t ctrl);

/**
 * @brief      Select TX Priority mode.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mode: select the CAN TX priority mode
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 */
ResultStatus_t CAN_SelectTxPriorityMode(CAN_Id_t id, CAN_TxPriMode_t mode);

/**
 * @brief      Enable CAN.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_Enable(CAN_Id_t id);

/**
 * @brief      Disable CAN.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_Disable(CAN_Id_t id);

/**
 * @brief      Sets the CAN bit timing for standard frames or the arbitration 
 *             phase of FD frames.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  timeSeg: A pointer to the CAN bit timing settings
 *
 * @return      status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetStdBitTiming(CAN_Id_t id, const CAN_BitTiming_t *timeSeg);

/**
 * @brief      Sets the CAN bit timing for the arbitration phase of FD frames of
 *             CAN.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  timeSeg: A pointer to the CAN bit timing settings
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetFdArbBitTiming(CAN_Id_t id, const CAN_BitTiming_t *timeSeg);

/**
 * @brief      Sets the CAN bit timing for the data phase of FD frames. 
 *             Those time segment values are passed in by the user and are based
 *             on the required baudrate.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  timeSeg: A pointer to the CAN bit timing settings
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetFdDataBitTiming(CAN_Id_t id, 
                                      const CAN_BitTiming_t *timeSeg);

/**
 * @brief      Configure transmit message buffer.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index
 * @param[in]  txInfo: TX MB info
 * @param[in]  msgId: message ID
 * @param[in]  localPrio: the local priority field, if the TX priority mode is
 *                        CAN_TX_PRI_LOCAL_PRI_EN, this parameter indicates the
 *                        local priority.
 *
 * @return     status
 *
 *
 */
ResultStatus_t CAN_ConfigTxMb(CAN_Id_t id, uint8_t mbIdx,
                              const CAN_MessageInfo_t *txInfo, 
                              uint32_t msgId, uint8_t localPrio);

/**
 * @brief      Configures a transmit message buffer for remote frame response
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index
 * @param[in]  txInfo: TX MB info
 * @param[in]  msgId: message ID
 * @param[in]  msgData:  data of the message
 * @param[in]  localPrio: the local priority field, if the TX priority mode is
 *                        CAN_TX_PRI_LOCAL_PRI_EN, this parameter indicates the
 *                        local priority
 *
 * @return     status
 *
 *
 */
ResultStatus_t CAN_ConfigRemoteResponseMb(CAN_Id_t id, uint8_t mbIdx,
                                          const CAN_MessageInfo_t *txInfo, 
                                          uint32_t msgId, const uint8_t *msgData,
                                          uint8_t localPrio);

/**
 * @brief      sends a CAN frame. This function sends a CAN frame using 
 *             a configured message buffer. Before calling this function,
 *             user needs to make sure that the MB to be configured is inactive,
 *             otherwise, it will return BUSY.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index
 * @param[in]  txInfo: TX MB info
 * @param[in]  msgId: message ID
 * @param[in]  msgData:  data of the message
 *
 * @return     status
 *            - SUCC
 *            - ERR: mbIdx is invalid
 *            - BUSY: the MB to be configured is not in inactive status
 *
 */
ResultStatus_t CAN_Send(CAN_Id_t id, uint8_t mbIdx, 
                        const CAN_MessageInfo_t *txInfo,
                        uint32_t msgId, const uint8_t *msgData);

/**
 * @brief      sends a CAN frame when the TX priority mode is CAN_TX_PRI_LOCAL_PRI_EN
 *             This function sends a CAN frame using a configured message buffer.
 *             It also configures the local priority. Before calling this 
 *             function, user needs to make sure that the MB to be configured 
 *             is inactive, otherwise, it will return BUSY.
 *              
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index
 * @param[in]  txInfo: TX MB info
 * @param[in]  msgId: message ID
 * @param[in]  msgData: data of the message
 * @param[in]  localPrio: the local priority field for the MB
 *
 * @return     status
 *            - SUCC
 *            - ERR: mbIdx is invalid
 *            - BUSY: the MB to be configured is not in inactive status
 *
 */
ResultStatus_t CAN_SendwithLocalPrio(CAN_Id_t id, uint8_t mbIdx, 
                                     const CAN_MessageInfo_t *txInfo,
                                     uint32_t msgId, const uint8_t *msgData, 
                                     uint8_t localPrio);

/**
 * @brief      Receive a CAN frame into a configured MB. Before calling this 
 *             function, user needs to make sure that the MB to be configured
 *             is inactive, otherwise, it will return BUSY.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index
 * @param[in]  rxInfo: RX MB info
 * @param[in]  msgId: message ID
 *
 * @return     status
 *            - SUCC
 *            - ERR: mbIdx is invalid
 *            - BUSY: the MB to be configured is not in inactive status
 *
 */
ResultStatus_t CAN_MbReceive(CAN_Id_t id, uint8_t mbIdx, 
                             const CAN_MessageInfo_t *rxInfo, uint32_t msgId);

/**
 * @brief      Configure a Rx message buffer.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index
 * @param[in]  rxInfo: RX MB info
 * @param[in]  msgId: message ID
 *
 * @return     status
 *
 *
 */
ResultStatus_t CAN_ConfigRxMb(CAN_Id_t id, uint8_t mbIdx, 
                              const CAN_MessageInfo_t *rxInfo, uint32_t msgId);

/**
 * @brief      Configure RX FIFO ID filter table elements
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  format: the ID filter format
 * @param[in]  idFilterTable: points to the ID filter table
 *
 * @note 
 *       The number of elements in the ID filter table is defined by the
 *       following formula:
 *       - for format A: the number of Rx FIFO ID filters
 *       - for format B: twice the number of Rx FIFO ID filters
 *       - for format C: four times the number of Rx FIFO ID filters
 *       The user must provide the exact number of elements in order to avoid
 *       any misconfiguration.
 *
 *       Each element in the ID filter table specifies an ID to be used as
 *       acceptance criteria for the FIFO as follows:
 *       - for format A: In the standard frame format, bits 10 to 0 of the ID
 *         are used for frame identification. In the extended frame format, bits
 *         28 to 0 are used.
 *       - for format B: In the standard frame format, bits 10 to 0 of the ID
 *         are used for frame identification. In the extended frame format, only
 *         the 14 most significant bits (28 to 15) of the ID are compared to the
 *         14 most significant bits (28 to 15) of the received ID.
 *       - for format C: In both standard and extended frame formats, only the 8
 *         most significant bits(10 to 3 for standard, 28 to 21 for extended) of
 *         the ID are compared to the 8 most significant bits (10 to 3 for
 *         standard, 28 to 21 for extended) of the received ID.
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_ConfigRxFifo(CAN_Id_t id, CAN_RxFifoIdFormat_t format,
                                const CAN_IdFilter_t *idFilterTable);
                      
/**
 * @brief      Get a message buffer field values.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index
 * @param[in]  msgBuff: point to the address where the message buffer will be stored 
 *
 * @return     status
 *
 *
 */
ResultStatus_t CAN_GetMsgBuff(CAN_Id_t id, uint32_t mbIdx, CAN_MsgBuf_t *msgBuff);

/**
 * @brief      Read a frame in RX FIFO.
 *
 * @param[in]  id: select the CAN ID
 * @param[in-out]  msgBuff: point to the address where the message buffer will
 *                         be stored 
 *
 * @return     none
 *
 *
 */
void CAN_ReadRxFifo(CAN_Id_t id, CAN_MsgBuf_t *msgBuff);

/**
 * @brief      Sets the Rx masking type.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  type: select RX mask type
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetRxMaskType(CAN_Id_t id, CAN_RxMask_t type);

/**
 * @brief      Sets Rx FIFO global mask. It masks the Rx FIFO ID Filter Table
 *             elements that do not have a corresponding individual mask. 
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mask:Mask Value. Its format depends on the RX FIFO id filter format.
               It should be set as follows:
                        
   Format A ID mask: 
   bit31 | bit30 |      bit29 ... 1             | bit0
   RTR   | IDE(0)| IDmask(std:29-19, ext:29-1)  | reserved

   Format B ID mask: 
   bit31 | bit30 |       bit29 ... 16         | bit 15 | bit 14 | bit13 ... 0
   RTR   | IDE   | ID0(std:29-19, ext:29-16)  | RTR    | IDE    | ID1
                                                            (std:13-3, ext:13-0)

   Format C ID mask: 
   bit31...bit 24 | bit23...bit16 |  bit15 ...bit8 | bit7 ... bit0
   IDmask0        | IDmask1       |    IDmask2     |    IDmask3
                        
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetRxFifoGlobalMask(CAN_Id_t id, uint32_t mask);

/**
 * @brief      Sets Rx FIFO individual mask for the specific ID filter table
 *             element
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  elementIdx: ID filter table element index. It indicates which
 *                         filter table element the mask is corresponding to.
 *                         It should not exceeds the MB number that is occupied
 *                         by Rx FIFO.
 * @param[in]  mask:Mask Value. Its format depends on the RX FIFO id filter format.
               It should be set as follows:
                        
   Format A ID mask: 
   bit31 | bit30 |      bit29 ... 1             | bit0
   RTR   | IDE(0)| IDmask(std:29-19, ext:29-1)  | reserved

   Format B ID mask: 
   bit31 | bit30 |       bit29 ... 16           | bit 15 | bit 14 | bit13 ... 0
   RTR   | IDE   | IDmask0(std:29-19, ext:29-16)| RTR    | IDE    | IDmask1
                                                             (std:13-3, ext:13-0)
   In the extended frame format B, IDmask0/IDmask1 corresponds to 
   the 14 most significant bits of the received ID

   Format C ID mask: 
   bit31...bit 24 | bit23...bit16 |  bit15 ...bit8 | bit7 ... bit0
   IDmask0        | IDmask1       |    IDmask2     |    IDmask3
   For format C IDmask corresponds to the 8 most significant bits of the 
    received ID
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetRxFifoIndividualMask(CAN_Id_t id, uint32_t elementIdx, 
                                           uint32_t mask);

/**
 * @brief      Sets the CAN Rx MB global mask (standard or extended) 
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  idType: Standard ID or extended ID
 * @param[in]  mask:Mask Value. 11-bit standard mask or 29-bit extended mask
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetRxMbGlobalMask(CAN_Id_t id, CAN_MsgId_t idType, 
                                     uint32_t mask);
     
/**
 * @brief      Set Rx Message Buffer 14 mask (standard or extended) 
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  idType: Standard ID or extended ID
 * @param[in]  mask:Mask Value. 11-bit standard mask or 29-bit extended mask
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetRxMb14Mask(CAN_Id_t id, CAN_MsgId_t idType, 
                                 uint32_t mask);

/**
 * @brief      Set Rx Message Buffer 15 mask (standard or extended) 
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  idType: Standard ID or extended ID
 * @param[in]  mask:Mask Value. 11-bit standard mask or 29-bit extended mask
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetRxMb15Mask(CAN_Id_t id, CAN_MsgId_t idType, uint32_t mask);

/**
 * @brief      Sets Rx MB individual mask 
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  idType: Standard ID or extended ID
 * @param[in]  mbIdx: MB index. The MB should not be occupied by RX FIFO if RX
 *                    FIFO is enabled, otherwise, it will return ERR.
 * @param[in]  mask:Mask Value. 11-bit standard mask or 29-bit extended mask
 *
 * @return     ResultStatus_t
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetRxMbIndividualMask(CAN_Id_t id, CAN_MsgId_t idType, 
                                         uint32_t mbIdx, uint32_t mask);

/**
 * @brief      Enables the Transceiver Delay Compensation feature in CAN FD mode
 *             and sets the Transceiver Delay Compensation Offset (offset value
 *             to be added to the measured transceiver's loop delay in order to
 *             define the position of the delayed comparison point when bit rate
 *             switching is active).
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  offset: Transceiver Delay Compensation Offset
 *
 * @return    status
 *            - SUCC -- successful
 *            - ERR -- some error
 *
 */
ResultStatus_t CAN_FdTdcEnable(CAN_Id_t id, uint8_t offset);

/**
 * @brief      Disables the Transceiver Delay Compensation feature in CAN FD mode
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    status
 *            - SUCC -- successful
 *            - ERR -- some error
 *
 */
ResultStatus_t CAN_FdTdcDisable(CAN_Id_t id);

/**
 * @brief   Gets the value of the Transceiver Delay Compensation.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return  The value of the transceiver loop delay measured from the transmitted
 *          EDL to R0 transition edge to the respective received one added to 
 *          the TDCOFF value.
 */
uint8_t CAN_GetTdcValue(CAN_Id_t id);

/**
 * @brief Gets the value of the TDC Fail flag.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return  If SET, indicates that the TDC mechanism is out of range, unable to
 *          compensate the transceiver's loop delay and successfully compare the
 *          delayed received bits to the transmitted ones.
 */
FlagStatus_t CAN_GetTdcFail(CAN_Id_t id);
     
/**
 * @brief Clears the TDC Fail flag.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return none
 *
 */
void CAN_ClearTdcFail(CAN_Id_t id);

/**
 * @brief  Set the code of a message buffer
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: Index of the message buffer. It should not be occupied by
 *                    RX FIFO if RX FIFO is enabled, otherwise, it will return 
 *                    ERR.
 * @param[in]  code: the code to be set
 *
 * return  status
 *         - ERR  mbIdx is invalid, can not find the MB
 *         - SUCC 
 */
ResultStatus_t CAN_SetMbCode(CAN_Id_t id, uint32_t mbIdx, CAN_MbCode_t code);
     
/**
 * @brief      Get the code of a message buffer.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: Index of the message buffer. It should not be occupied by
 *                    RX FIFO if RX FIFO is enabled, otherwise, it will return 
 *                    ERR.
 * @param[in]  code: the code will be stored in the memory that pointed by this
 *                   pointer
 *
 * @return     status
 *
 *
 */
ResultStatus_t CAN_GetMbCode(CAN_Id_t id, uint32_t mbIdx, uint32_t *code);

#if(CAN_ABORT_EN == 1U)
/**
 * @brief  Writes the abort code into the CODE field of the requested Tx message
 *         buffer to abort transmission. User needs to check if MB transmission
 *         is aborted or not after this function. It is suggested to use 
 *         CAN_InactiveMb() to abort MB transmission instead of this function.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: Index of the message buffer.It should not be occupied by
 *                    RX FIFO if RX FIFO is enabled, otherwise, it will return 
 *                    ERR.
 *
 * @note  This function is available only when CAN_ABORT_EN = 1U
 * @return  status
 *         - ERR  mbIdx is invalid
 *         - SUCC 
 */
ResultStatus_t CAN_AbortTxMb(CAN_Id_t id, uint32_t mbIdx);
#endif

/**
 * @brief  if a message is received by RX FIFO, this function can get the number 
 *         of the ID filter which the received message hit. It is only valid,
 *         when CAN_IFLAG1[BUF5I] is asserted.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return  The number of the ID filter
 */
uint32_t CAN_GetRxFifoIdHit(CAN_Id_t id);

/**
 * @brief  Enable/Disable global network time mechanism. If enabled, it resets 
 *         the free running timer each time a message is received in message 
 *         buffer 0. This feature provides means to synchronize multiple 
 *         CAN stations with a special "SYNC" message, that is, global 
 *         network time. If Rx FIFO is enabled, the first available mailbox, 
 *         according to CAN_CTRL2[RFFN] setting, is used for timer 
 *         synchronization instead of MB0. 
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  state: ENABLE/DISABLE
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 */
ResultStatus_t CAN_ControlGlobalNetworkTime(CAN_Id_t id, ControlState_t state);

/**
 * @brief  Get the lowest number inactive MB
 *
 * @param[in]  id: select the CAN ID
 *
 * @return  the lowest number inactive MB.
 *          - 0 - 63: the lowest number inactive MB
 *          - 0xFF: it means that there is no inactive MB or it can not be read 
 *               at this moment.
 *          
 */
uint8_t CAN_GetInactiveMb(CAN_Id_t id);

/**
 * @brief  Enable timeout to be a wakeup source for Pretended Networking.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  timeout: timeout value.
 *
 * @return status
 *         - SUCC -- successful
 *         - ERR -- some error
 *
 */
ResultStatus_t CAN_EnablePnTimeoutWakeup(CAN_Id_t id, uint16_t timeout);

/**
 * @brief  Disable timeout to be a wakeup source for Pretended Networking.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_DisablePnTimeoutWakeup(CAN_Id_t id);

/**
 * @brief  Enable and config the wakeup source of receiving matched messages 
 *         for Pretended Networking.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  config: match wakeup config.
 *
 * @return none
 *
 */
ResultStatus_t CAN_EnablePnMatchWakeup(CAN_Id_t id, 
                                       const CAN_PnMatchConfig_t *config);

/**
 * @brief  Disable the wakeup source of receiving matched messages 
 *         for Pretended Networking.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_DisablePnMatchWakeup(CAN_Id_t id);

/**
 * @brief  Enable and Configures Pretended Networking settings.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  pnConfig: Points to the Pretended Networking configuration 
 *                       structure.
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_EnablePn(CAN_Id_t id, const CAN_PnConfig_t *pnConfig);

/**
 * @brief  Disable Pretended Networking settings.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_DisablePn(CAN_Id_t id);

/**
 * @brief      Get a wakeup message buffer field values.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  wmbIdx: wakeup MB index. Its range is 0-3.
 * @param[in]  msgBuff: point to the address where the message buffer will be
 *                      stored. The size is 8 at least. 
 *
 * @return     status
 *
 *
 */
ResultStatus_t CAN_GetWakeupMsgBuff(CAN_Id_t id, uint32_t wmbIdx, 
                                    CAN_MsgBuf_t *msgBuff);

/**
 * @brief  Enable self wakeup function.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  intEn: it indicates if the self wakeup interrupt is enabled.
 *                    If it is required to wake up the chip from stop mode 
 *                    through self wakeup. intEn has to be set to ENABLE.
 * @param[in]  filterEn: it indicates if the low-pass filter is enabled to 
 *                        protect the Rx CAN input from spurious wake up
 * 
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_EnableSelfWakeup(CAN_Id_t id, ControlState_t intEn, 
                                    ControlState_t filterEn);

/**
 * @brief  Disable self wakeup function.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_DisableSelfWakeup(CAN_Id_t id);

/**
 * @brief  Enable enter into doze mode when received entering into wait mode
 *         request.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return none
 *
 */
void CAN_EnableDozeMode(CAN_Id_t id);

/**
 * @brief  Disable enter into doze mode when received entering into wait mode
 *         request.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return none
 *
 */
void CAN_DisableDozeMode(CAN_Id_t id);

/**
 * @brief  config the action when received a remote request frame
 *
 * @param[in]  id: select the CAN ID
 * @param[in] autoResponse: config if remote response frame is transmitted 
 *                          automatically after receiving a remote request frame.
 *                          - ENABLE: The received remote request frame is not
 *                            stored and remote response frame, which is 
 *                            configured through function 
 *                            CAN_ConfigRemoteResponseMb() is transmitted
 *                            automatically
 *                          - DISABLE: remote request frame is stored in the 
 *                            same fashion of a data frame in a RX message 
 *                            buffer, configured through function CAN_MbReceive(),
 *                            no automatic remote response is transmitted.
 *                         if RXFIFO is enabled and used to receive remote 
 *                         request, remote request frame is stored and no 
 *                         automatic remote response is transmitted. 
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_RemoteFrameConfig(CAN_Id_t id, ControlState_t autoResponse);


/**
 * @brief      Install callback function for CAN_INT_BUS_OFF, CAN_INT_ERR,    
               CAN_INT_TXW, CAN_INT_RXW, CAN_INT_BUS_OFF_DONE, CAN_INT_ERR_FAST,
               CAN_INT_WAKEUP, CAN_INT_RXFIFO_FRAME, CAN_INT_RXFIFO_WARNING,
               CAN_INT_RXFIFO_OVERFLOW, CAN_INT_HOST_MEM_ERR, CAN_INT_CAN_MEM_ERR,  
               CAN_INT_COR_MEM_ERR
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  intType: select interrupt type
 * @param[in]  cbFun: indicate callback function
 *
 * @return    none
 *
 */  
void CAN_InstallCallBackFunc(CAN_Id_t id, CAN_Int_t intType, isr_cb_t * cbFun);

/**
 * @brief      Install callback function for  MB interrupt
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbCbf: indicate callback function
 *
 * @return    none
 *
 */ 
void CAN_InstallMbCallBackFunc(CAN_Id_t id, can_mb_cb_t mbCbf);

/**
 * @brief      Interrupt mask/unmask
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  intType: interrupt to be masked/unmasked
 * @param[in]  intMask: MASK/UNMASK
 * @param[in]  mb0t31: if intType is CAN_INT_MB, this parameter selects the MBs
 *                     (MB0-MB31) to be configured. Each bit corresponds a MB
 *                     (bit0 - MB0, bit1 - MB1, ... ,bit31 - MB31). If a bit 
 *                     is 1,it means the corresponding MB to be configured.
 * @param[in]  mb32t63: if intType is CAN_INT_MB, this parameter selects the MBs
 *                     (MB32-MB63) to be configured. Each bit corresponds a MB
 *                     (bit0 - MB32, bit1 - MB33, ... ,bit31 - MB63). If a bit 
 *                     is 1,it means the corresponding MB to be configured.
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_IntMask(CAN_Id_t id, CAN_Int_t intType, IntMask_t intMask, 
                           uint32_t mb0t31, uint32_t mb32t63);
                 
/**
 * @brief       MB Interrupt mask/unmask
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: the MB index
 * @param[in]  intMask: MASK/UNMASK
 *
 * @return     status
 *             -ERR
 *             -SUCC
 *
 */
ResultStatus_t CAN_MbIntMask(CAN_Id_t id, uint32_t mbIdx,IntMask_t intMask);

/**
 * @brief      Clear interrupt
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  intType: select interrupt type
* @param[in]  mb0t31: if intType is CAN_INT_MB, this parameter selects the MBs
 *                     (MB0-MB31) to be configured. Each bit corresponds a MB
 *                     (bit0 - MB0, bit1 - MB1, ... ,bit31 - MB31). If a bit 
 *                     is 1,it means the corresponding MB to be configured.
 *                     For other interrupt type, this parameter can be ignored.
 * @param[in]  mb32t63: if intType is CAN_INT_MB, this parameter selects the MBs
 *                     (MB32-MB63) to be configured. Each bit corresponds a MB
 *                     (bit0 - MB32, bit1 - MB33, ... ,bit31 - MB63). If a bit 
 *                     is 1,it means the corresponding MB to be configured.
 *                     For other interrupt type, this parameter can be ignored.
 *
 * @return    none
 *
 */ 
void CAN_IntClear(CAN_Id_t id, CAN_Int_t intType, uint32_t mb0t31, 
                  uint32_t mb32t63);

/**
 * @brief      Get ESR1 buffer in interrupt call back functions. The ESR1 
 *              will be stored into ESR1 buffer in CAN_IntHandler.
 *            If the call back functions which are installed through 
 *             CAN_InstallCallBackFunc()  needs to get the ESR1 , please use 
 *             this function instead of CAN_GetIntStatus or CAN_GetStatus.
 *
 * @param[in]  id: Select the CAN port,should be CAN0_ID , CAN1_ID
 *
 * @return     ESR1 Buff Value
 *
 */
uint32_t CAN_GetESR1BufForCbf(CAN_Id_t id);

/**
 * @brief      Get CAN status from ESR1 Buff
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  status: the status to be get
 *
 * @return   status
 *           - SET
 *           - RESET
 *
 */ 
FlagStatus_t CAN_GetStatusFromESR1Buf(CAN_Id_t id, CAN_Status_t status);

/**
 * @brief      Get interrupt status
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  intType: select interrupt type
 * @param[in]  mbId: if intType is CAN_INT_MB, this parameter selects the MB
 *                     (MB0-MB63) status to be get
 *
 * @return    status
 *            - SET
 *            - RESET
 *
 */ 
IntStatus_t CAN_GetIntStatus(CAN_Id_t id, CAN_Int_t intType, uint32_t mbId);

/**
 * @brief      Get CAN state
 *
 * @param[in]  id: select the CAN ID
 *
 * @return   CAN state
 *
 */ 
CAN_State_t CAN_GetState(CAN_Id_t id);

/**
 * @brief      Get CAN status
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  status: the status to be get
 *
 * @return   status
 *           - SET
 *           - RESET
 *
 */ 
FlagStatus_t CAN_GetStatus(CAN_Id_t id, CAN_Status_t status);

/**
 * @brief      Clear CAN status
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  status: the status to clear
 *
 * @return   none
 *
 */ 
void CAN_ClearStatus(CAN_Id_t id, CAN_Status_t status);

/**
 * @brief      Get CAN Fault Confinement State
 *
 * @param[in]  id: select the CAN ID
 *
 * @return   CAN  Fault Confinement State
 *
 */ 
CAN_FaultConfState_t CAN_GetFaultConfinementState(CAN_Id_t id);
     
/**
 * @brief     make the MB to inactive status and disable the interrupt of this
 *            MB. The MBs occupied by RX FIFO can not be handle by this function.
 *            If MB is RX MB, it will become CAN_MB_RX_INACTIVE after 
 *            this function; if MB is TX MB, it will become CAN_MB_TX_INACTIVE
 *            or CAN_MB_TX_ABORT after this function.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index
 *
 * @return     status
 *
 *
 */
ResultStatus_t CAN_InactiveMb(CAN_Id_t id, uint8_t mbIdx);

/**
 * @brief     It selects How CAN recovers from bus off state. If 
 *            CAN_BUS_OFF_RECOV_AUTO is selected, automatic recovering from Bus 
 *            Off state occurs according to the CAN Specification. If 
 *            CAN_BUS_OFF_RECOV_MANUAL is selected, user can call 
 *            CAN_RecoverFromBusOffManually() to recover from bus off state.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  recov: It selects how to recover from bus off.

 * @note this function shall be called before entering bus off state. If CAN 
 *       recovers from bus off manually through CAN_RecoverFromBusOffManually(),
 *       and user need to select CAN_BUS_OFF_RECOV_MANUAL for the next time,
 *       this function shall be called again. 
 *
 * @return     none
 *
 *
 */
void CAN_BusOffRecoveryScheme(CAN_Id_t id, CAN_BusOffRecovery_t recov);

/**
 * @brief     Once CAN is in bus off state and bus off recovery scheme is 
 *            CAN_BUS_OFF_RECOV_MANUAL, which is selected through  
 *            CAN_BusOffRecoveryScheme(), call this function can recover from  
 *            bus off state manually.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return     none
 *
 *
 */
void CAN_RecoverFromBusOffManually(CAN_Id_t id);

/** @} end of group CAN_Public_FunctionDeclaration */

/** @} end of group CAN  */

/** @} end of group Z20K11X_Peripheral_Driver */
#endif /* Z20K11XM_CAN_H */
