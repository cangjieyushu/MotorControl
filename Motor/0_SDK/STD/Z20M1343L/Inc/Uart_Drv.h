/**************************************************************************************************/
/**
 * @file      : Uart_drv.h
 * @brief     : Uart module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/


#ifndef UART_DRV_H
#define UART_DRV_H

#include "Common_Drv.h"

/** @defgroup Public_MacroDefinition
 *  @{
 */

#define UART_INSTANCE_NUM      (1U)
#define UART_INT_NUM           (16U)

/** @}end of group Public_MacroDefinition */


/** @defgroup Public_TypeDefinition
 *  @{
 */

/**
 *  @brief UART mode type definition
 */
typedef enum
{
    UART_MODE_UART = 0U,                    /*!< UART mode */
    UART_MODE_LIN                           /*!< LIN mode */
} Uart_ModeType;

/**
 *  @brief UART parity type definition
 */
typedef enum
{
    UART_PARITY_NONE = 0U,                  /*!< UART parity none */
    UART_PARITY_ODD,                        /*!< UART parity odd  */
    UART_PARITY_EVEN                        /*!< UART parity even */
} Uart_ParityType;

/**
 *  @brief UART data bits type definition
 */
typedef enum
{
    UART_DATABITS_5 = 0U,                   /*!< UART data bits length: 5 bits */
    UART_DATABITS_6,                        /*!< UART data bits length: 6 bits */
    UART_DATABITS_7,                        /*!< UART data bits length: 7 bits */
    UART_DATABITS_8,                        /*!< UART data bits length: 8 bits */
    UART_DATABITS_9                         /*!< UART data bits length: 9 bits */
} Uart_DataBitsType;

/**
 *  @brief UART stop bits type definition
 */
typedef enum
{
    UART_STOPBITS_1 = 0U,                   /*!< UART stop bits length: 1 bit */
    UART_STOPBITS_1P5_2                     /*!< UART stop bits length: 1.5 or 2 bits */
} Uart_StopBitsType;

/**
 *  @brief UART TX FIFO level type definition
 */
typedef enum
{
    UART_TX_FIFO_EMPTY = 0U,                /*!< UART FIFO empty */
    UART_TX_FIFO_CHAR_2,                    /*!< UART 2 characters in the FIFO */
    UART_TX_FIFO_QUARTER,                   /*!< UART FIFO 1/4 full */
    UART_TX_FIFO_HALF                       /*!< UART FIFO 1/2 full */
} Uart_TxFIFOLevelType;

/**
 *  @brief UART RX FIFO level type definition
 */
typedef enum
{
    UART_RX_FIFO_CHAR_1 = 0U,               /*!< UART 1 character in the FIFO */
    UART_RX_FIFO_QUARTER,                   /*!< UART 1/4 full*/
    UART_RX_FIFO_HALF,                      /*!< UART 1/2 full */
    UART_RX_FIFO_LESS_2                     /*!< UART FIFO 2 less than full */
} Uart_RxFIFOLevelType;

/**
 *  @brief UART IDLE detect length type definition
 */
typedef enum
{
    UART_IDLE_DETECT_LENGTH_1 = 0U,         /*!< UART idle detection length: 1-bit character  */
    UART_IDLE_DETECT_LENGTH_2,              /*!< UART idle detection length: 2-bit characters   */
    UART_IDLE_DETECT_LENGTH_4,              /*!< UART idle detection length: 4-bit characters  */
    UART_IDLE_DETECT_LENGTH_8,              /*!< UART idle detection length: 8-bit characters  */
    UART_IDLE_DETECT_LENGTH_16,             /*!< UART idle detection length: 16-bit characters */
    UART_IDLE_DETECT_LENGTH_32,             /*!< UART idle detection length: 32-bit characters */
    UART_IDLE_DETECT_LENGTH_64,             /*!< UART idle detection length: 64-bit characters */
    UART_IDLE_DETECT_LENGTH_128             /*!< UART idle detection length: 128-bit characters */
} Uart_IdleDetectLengthType;

/**
 *  @brief UART Line status bit type definition
 */
typedef enum
{
    UART_LINESTA_DR = 0U,                   /*!< Data ready */
    UART_LINESTA_OE,                        /*!< Overrun error */
    UART_LINESTA_PE,                        /*!< Parity error */
    UART_LINESTA_FE,                        /*!< Framing Error */
    UART_LINESTA_BI,                        /*!< Break interrupt flag */
    UART_LINESTA_THRE,                      /*!< Transmit holding register empty */
    UART_LINESTA_TEMT,                      /*!< Transmit empty */
    UART_LINESTA_RFE,                       /*!< RCV FIFO error */
    UART_LINESTA_TRANS_ERR,                 /*!< Indicate whether any of 'OE','PE',
                                            'FE','BI' and 'RFE' happens */
    UART_LINESTA_ADDR_RCVD,                 /*!< Address receive */
    UART_LINESTA_ASYNC,                     /*!< async interrupt flag*/
    UART_LINESTA_ALL                        /*!< all line status */
} Uart_LineStatusType;

/**
 *  @brief UART status type definition
 */
typedef enum
{
    UART_STA_BUSY = 0U,                   /*!< UART busy status */
    UART_STA_TFNF,                        /*!< UART tx fifo not full */
    UART_STA_TFE,                         /*!< UART tx fifo empty */
    UART_STA_RFNE,                        /*!< UART receive fifo not empty */
    UART_STA_RFF                          /*!< UART receive fifo full */
} Uart_StatusType;

/**
 *  @brief UART  break detect  type definition
 */
typedef enum
{
    UART_BREAKDETECTLEN_95 = 0U,         /*!< break detect len is 9.5 bits zero */
    UART_BREAKDETECTLEN_105               /*!< break detect len is 10.5 bits zero  */
} Uart_BreakDetectLen;


/**
 *  @brief UART and LIN interrupt type definition
 */
typedef enum
{    
    UART_INT_RBFI = 0U,                         /*!< Received data available interrupt.*/
    UART_INT_TBEI,                              /*!< Transmit holding register empty interrupt */
    UART_INT_LSI,                               /*!< RX line status interrupt*/
    UART_INT_MODEM,                             /*!< CTS interrupt */
    UART_INT_PTIME,                             /*!< Programmable THRE interrupt*/
    UART_INT_ASYNC,                             /*!< stop mode wake up: Async interrupt */
    UART_INT_BYDET,                             /*!< Busy detect interrupt */
    UART_INT_RCVRTO,                            /*!< Character timeout interrupt, it is 
                                                     effective only when enable the fifo */    
    UART_INT_LIN_ERR,                            /*!< LIN COMMON_ERR interrupt.*/
    UART_INT_LIN_WUP_OP_SUCC,                    /*!< LIN wakeup operation success interrupt */
    UART_INT_LIN_HEADER_OP_SUCC,                 /*!< LIN header operation success interrupt*/
    UART_INT_LIN_RSP_OP_SUCC,                    /*!< LIN response operation success interrupt */
    UART_INT_LIN_ALL,                             /*!< All LIN interrupt */
    UART_INT_ALL                                 /*!< All UART interrupt */
} Uart_IntType;

/**
 *  @brief  LIN interrupt status type definition
 */
typedef enum
{    
    UART_LIN_INTSTA_ERR = 0U,                        /*!< LIN error status.*/
    UART_LIN_INTSTA_WUP_OP_SUCC,                     /*!< LIN wakeup success */
    UART_LIN_INTSTA_HEADER_OP_SUCC,                  /*!< LIN header operation success*/
    UART_LIN_INTSTA_RSP_OP_SUCC                      /*!< LIN response operation success */
} Uart_LinIntStatusType;

/**
 *  @brief UART LIN error status type definition
 */
typedef enum
{    
    UART_LIN_ERROR_SYNC = 0U,                    /*!< LIN sync field error.*/
    UART_LIN_ERROR_PID,                          /*!< LIN pid error */
    UART_LIN_ERROR_CHECKSUM,                     /*!< LIN checksum error*/
    UART_LIN_ERROR_TO,                           /*!< LIN timeout error */
    UART_LIN_ERROR_BIT,                          /*!< LIN bit error */
    UART_LIN_ERROR_WUP,                          /*!< LIN wakeup timeout error */
    UART_LIN_ERROR_ALL                           /*!< All the error */
} Uart_LinErrorType;

/**
 *  @brief UART LIN mode type definition
 */
typedef enum
{
    UART_LIN_SLAVE = 0U,                    /*!< work as a LIN slave */
    UART_LIN_MASTER                         /*!< work as a LIN master */
} Uart_LinModeType;

/**
 *  @brief UART LIN checksum type definition
 */
typedef enum
{
    UART_LIN_CHECKSUM_CLASSIC = 0U,         /*!< classic checksum */
    UART_LIN_CHECKSUM_ENHANCED              /*!< enhanced checksum */
} Uart_LinCheckSumType;



/**
 *  @brief UART LIN wakeup timeout action type definition
 */
typedef enum
{
    UART_LIN_WUP_TO_ACT_IGNORE = 0U,           /*!< When dominant pulse which is longer than the high 
                                           threshold, it is not taken as a valid wakeup signal. LIN will ignore 
                                           this signal and detect next valid domininant pulse */
    UART_LIN_WUP_TO_ACT_ERR                   /*!< When dominant pulse which is longer than the high 
                                           threshold, LIN will set the UART_LIN_ERR[WAKEUP_TO_ERR] and 
                                           stop the wakeup operation. If error interrupt is enabled, 
                                           it will generate an interrupt */
} Uart_LinWakeupToActType;

/**
 *  @brief UART Configuration Structure type definition
 */
typedef struct
{
    uint32 BaudRate;                                /*!< baud rate */
    Uart_DataBitsType DataBits;                     /*!< Data size, 5/6/7/8/9 bits */
    Uart_ParityType Parity;                         /*!< Parity Enable */
    Uart_StopBitsType StopBits;                     /*!< Number of stop bits */
    Common_ControlStateType AutoFlowControl;        /*!< Auto flow control enable */
    uint32 OscFreq;                                 /*!< the frequency of the OSC clock source */
} Uart_ConfigType;

/**
 *  @brief UART FIFO Configuration Structure type definition
 */
typedef struct
{
    Common_ControlStateType FiFoEnable;              /*!< Enable/disable FIFO function*/
    Common_ControlStateType TxFiFoReset;             /*!< Reset tx FIFO */
    Common_ControlStateType RxFiFoReset;             /*!< Reset rx FIFO */
    uint8  TxFiFoTrigger;              /*!< Set TX Empty trigger level */
    uint8  RxFiFoTrigger;              /*!< Set RCVR trigger level */
} Uart_FIFOConfigType;

/**
 *  @brief UART idle detect Structure type definition
 */
typedef struct
{
    Common_ControlStateType  Cmd;             /*!< Enable/disable idle detect*/
    Uart_IdleDetectLengthType Len;            /*!< IDLE detect length:
                                               -UART_IDLE_DETECT_LENGTH_1 
                                               -UART_IDLE_DETECT_LENGTH_2
                                               -UART_IDLE_DETECT_LENGTH_4
                                               -UART_IDLE_DETECT_LENGTH_8
                                               -UART_IDLE_DETECT_LENGTH_16
                                               -UART_IDLE_DETECT_LENGTH_32
                                               -UART_IDLE_DETECT_LENGTH_64
                                               -UART_IDLE_DETECT_LENGTH_128 */
} Uart_IdleDetectConfigType;

/**
 *  @brief UART LIN Configuration Structure type definition
 */
typedef struct
{
    uint32 BaudRate;                          /*!< baud rate */
    uint32 OscFreq;                           /*!< the frequency of the OSC clock source */
    Uart_LinModeType Mode;                    /*!< LIN mode */
    Common_ControlStateType AutoSyncEn;       /*!< Auto sync enable flag, if is set to 
                                                     ENABLE, it will detect the baudrate
                                                     through the sync part of header and set 
                                                     the baudrate automatically */
    Common_ControlStateType IdFilterEn;       /*!< Whether enable ID filter when it receives
                                                     header  */
    Common_ControlStateType BitErrorEn;       /*!< Whether enable bit error detection */
    uint8 SampleDelay;                        /*!< Collision sample delay, it is used to detect bit 
                                                     error, it is recommended to be 8 */
} Uart_LinConfigType;

/**
 *  @brief UART LIN header Structure type definition
 */
typedef struct
{
    uint32 Pid;                            /*!< 8-bit PID. 
                                                The default mode is that PID will be calculated 
                                                by hardware (PID_OVRD_EN = 0),  user only needs 
                                                to provide the 6-bit ID, PID will be
                                                calculated by hardware and the bit7 and bit 8 of 
                                                this parameter will be ignored and overwritten by 
                                                hardware.
                                                If PID is calculated by software
                                                (PID_OVRD_EN = 1), user need to provide
                                                 8-bit PID  */
    uint32 BreakLen;                      /*!< break field length */
    uint32 DeleLen;                       /*!< delemiter length */
} Uart_LinHeaderType;

/**
 *  @brief UART LIN header Structure type definition
 */
typedef struct
{
    Uart_LinCheckSumType CheckType;           /*!< Checksum type */
    uint32 Len;                               /*!< Response length exclude checksum */
    uint8 Data[8];                            /*!< The response payload exclude checksum*/
} Uart_LinResponseType;

/**
 *  @brief UART LIN wakeup type definition
 */
typedef struct
{
    uint16 WakeupFreq;                      /*!< Wakeup frequency */
    uint16 WakeupDetThrLow;                 /*!< Wakeup detection low threhold */          
    uint16 WakeupDetThrHigh;                /*!< Wakeup detection high threhold  */
    Uart_LinWakeupToActType ActCmd;         /*!< The action when lin wakeup timeout */
} Uart_LinDetWakeupCfgType;

/**
 * @brief UART interrupt handler array
 */
typedef void (HandlerFuncPtr)(void);

/** @}end of group Public_TypeDefinition */


/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */



/** @defgroup Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief      Initializes the UART
 * @param[in]  UartConfig:  Pointer to a UART configuration structure
 * @return     none
 */
void Uart_Init(const Uart_ConfigType* UartConfigPtr);

/**
 * @brief      UART/LIN enable/disable function
 * @param[in]  Cmd: Enable/Disable function state
                    - COMMON_DISABLE
                    - COMMON_ENABLE
 * @return none
 */
void Uart_Enable( Common_ControlStateType Cmd);

/**
 * @brief      Set UART rts enable 
 * @param[in]  NewState: Enable/Disable function state
 * @return     none
 */
void Uart_EnableRts(Common_ControlStateType NewState);

/**
 * @brief      Reset uart receive fifo
 * @param[in]  none
 * @return     none
 */
void Uart_ResetRxFiFo(void);

/**
 * @brief      Reset uart transmit fifo
 * @param[in]  none
 * @return     none
 */
void Uart_ResetTxFiFo(void);

/**
 * @brief      Enable/Disable debug enable. If enabled, hardware will not clean 
 *             the receiver fifo automatically
 * @param[in]  Cmd: ENABLE/DISABLE
 * @return     none
 */
void Uart_ControlDebugCmd(Common_ControlStateType Cmd);

/**
 * @brief      Enable/Disable UART programmable THRE interrupt mode.
 * @param[in]  cmd:  ENABLE/DISABLE
 *                
 * @return     none
 *
 */
void Uart_EnableProgramTHRE(Common_ControlStateType Cmd);


/**
 * @brief      Config idle detect 
 * @param[in]  ConfigPtr: config idle detect 
 * @return     none
 */
void Uart_ConfigIdleDetect(Uart_IdleDetectConfigType *ConfigPtr);

/**
 * @brief      Config UART sample point, default is 8
 * @param[in]  DelVal: config UART sample point
 * @note       Default sample ratio is 16, sample delay set to 8 means sample 
 *             at the center of data. No special requirements. You are advised to 
 *             retain the default value
 * @return     none
 */
void Uart_SetSampleDelay(uint8 DelVal);

/**
 * @brief      Config Lin readback sample point, default is 8
 * @param[in]  DelVal: config Lin sample point
 * @note       Default sample ratio is 16, sample delay set to 8 means sample 
 *             at the center of data. No special requirements. You are advised to 
 *             retain the default value
 * @return     none
 */
void Uart_LinSetSampleDelay(uint8 DelVal);

/**
 * @brief      Send break function, user can choose the length of break
 * @param[in]  Len:     the length of break
 * @return     Ret:
 * @retval     COMMON_SUCC: break is sent
 * @retval     COMMON_ERR: break length is invalid
 */
Common_ResultStatusType Uart_SendBreak(uint8 Len);

/**
 * @brief      Set UART loopback mode
 * @param[in]  NewState: Enable/Disable function state
 * @return     none
 */
void Uart_SetLoopBackMode(Common_ControlStateType NewState);

/**
 * @brief      Wait for UART busy bit clear
 * @param[in]  Cycle: wait time need user calculation
 * @return     Ret: 
 * @retval     COMMON_SUCC:busy bit is cleared
 * @retval     COMMON_ERR: UART is still busy
 */
Common_ResultStatusType Uart_WaitBusyClear(uint32 Cycle);

/**
 * @brief      Receive one byte data from the UART peripheral
 * @param[in]  none
 * @return     uint8:the received data
 */
uint8 Uart_ReceiveByte(void);

/**
 * @brief      Read received bytes from the RX FIFO
 * @param[in]  Length:  the number of bytes to be read. When call this function,
 *                      the user needs to make sure that the "length" is not
 *                      greater than the number of bytes that is available in
 *                      RX FIFO
 * @param[out] Data:  points to the memory where the data to be stored
 * @return     none
 */
void Uart_ReceiveBytes(uint32 Length, uint8 Data[]);

/**
 * @brief      Empty the RX FIFO. This function reads received data until RX
 *             FIFO is empty
 * @param[in]  none
 * @return     none
 */
void Uart_EmptyRxFifo(void);

/**
 * @brief      Send one byte data to the UART peripheral
 * @param[in]  Data:The data to be sent
 * @return     none
 */
void Uart_SendByte(uint8 Data);

/**
 * @brief      Config UART FIFO function
 * @param[in]  FiFoConfigPtr:Pointer to a FIFO configuration
 * @return     none
 */
void Uart_ConfigFIFO(const Uart_FIFOConfigType* FiFoConfigPtr);

/**
 * @brief      Get UART (UART_USR) status
 * @param[in]  Type: select one status type
                     - UART_STA_BUSY
 *                   - UART_STA_TFNF
 *                   - UART_STA_TFE
 *                   - UART_STA_RFNE
 *                   - UART_STA_RFF
 * @return     UART status:
 * @retval     COMMON_SET: The Type status bit is set
 * @retval     COMMON_RESET:The Type status bit is reset
 */
Common_FlagStatusType Uart_GetStatus(Uart_StatusType Type);

/**
 * @brief      Get current value of Line Status register
* @param[in]   LineStatus:
 *                       - UART_LINESTA_DR
 *                       - UART_LINESTA_OE
 *                       - UART_LINESTA_PE
 *                       - UART_LINESTA_FE
 *                       - UART_LINESTA_BI
 *                       - UART_LINESTA_THRE
 *                       - UART_LINESTA_TEMT
 *                       - UART_LINESTA_RFE
 *                       - UART_LINESTA_TRANS_ERR
 *                       - UART_LINESTA_ADDR_RCVD
 *                       - UART_LINESTA_ALL
 * @return     Common_FlagStatusType:The state value of UART Line Status register
 * @retval     COMMON_SET: The Line status bit is set
 * @retval     COMMON_RESET:The Line status bit is reset
 */
Common_FlagStatusType Uart_GetLineStatus(Uart_LineStatusType LineStatus);

/**
 * @brief      Get current LIN interrupt Status
 * @param[in]  StaType: select one interrupt status
 *                     - UART_LIN_INTSTA_ERR
 *                     - UART_LIN_INTSTA_WUP_OP_SUCC
 *                     - UART_LIN_INTSTA_HEADER_OP_SUCC
 *                     - UART_LIN_INTSTA_RSP_OP_SUCC
 * @note       This api is used to get lin interrupt status when the interrupt is masked
 * @return     Common_IntStatusType:The state value of LIN interrupt status register
 * @retval     COMMON_SET: The Line int status bit is set
 * @retval     COMMON_RESET:The Line int status bit is reset
 */
Common_IntStatusType Uart_LinGetIntStatus(Uart_LinIntStatusType StaType);

/**
 * @brief      Clear LIN interrupt Status
 * @param[in]  StaType: select one interrupt status
 *                     - UART_LIN_INTSTA_ERR
 *                     - UART_LIN_INTSTA_WUP_OP_SUCC
 *                     - UART_LIN_INTSTA_HEADER_OP_SUCC
 *                     - UART_LIN_INTSTA_RSP_OP_SUCC
 * @note       UART_LIN_INTSTA_ERR need call UART_LinClearErrorStatus() to clear
 * @return     none.
 */
void Uart_LinClearIntStatus(Uart_LinIntStatusType StaType);

/**
 * @brief      Clear line status
 * @param[in]  LineStatus:
 *                       - UART_LINESTA_OE
 *                       - UART_LINESTA_PE
 *                       - UART_LINESTA_FE
 *                       - UART_LINESTA_BI
 *                       - UART_LINESTA_RFE
 *                       - UART_LINESTA_TRANS_ERR
 *                       - UART_LINESTA_ADDR_RCVD
 *                       - UART_LINESTA_ASYNC
 *                       - UART_LINESTA_ALL
 * @return     none
 */
void Uart_ClearLineStatusFlag(Uart_LineStatusType LineStatus);


/**
 * @brief      Set Lin break detect len
 * @param[in]  BreakDetLen: break detect len
 *                      - UART_BREAKDETECTLEN_95
 *                      - UART_BREAKDETECTLEN_105
 * @return     None
 */
void Uart_SetBreakDetectLen(Uart_BreakDetectLen BreakDetLen);




/**
 * @brief      Get Lin error status
 * @param[in]  ErrType: Specifies the error status type
 *                      - UART_LIN_ERROR_SYNC
 *                      - UART_LIN_ERROR_PID
 *                      - UART_LIN_ERROR_CHECKSUM
 *                      - UART_LIN_ERROR_TO
 *                      - UART_LIN_ERROR_BIT
 *                      - UART_LIN_ERROR_WUP
 *                      - UART_LIN_ERROR_ALL
 * @return     The state value of LIN error Status register
 * @retval     COMMON_SET: The Lin error status bit is set
 * @retval     COMMON_RESET:The Lin error status bit is reset
 */
Common_IntStatusType Uart_LinGetErrorStatus(Uart_LinErrorType ErrType);

/**
 * @brief      Clear Lin error status
 * @param[in]  ErrType: Specifies the error status type
 *                      - UART_LIN_ERROR_SYNC
 *                      - UART_LIN_ERROR_PID
 *                      - UART_LIN_ERROR_CHECKSUM
 *                      - UART_LIN_ERROR_TO
 *                      - UART_LIN_ERROR_BIT
 *                      - UART_LIN_ERROR_WUP
 *                      - UART_LIN_ERROR_ALL
 * @return     none
 */
void Uart_LinClearErrorStatus(Uart_LinErrorType ErrType);


/**
 * @brief      LIN detect wakeup signal config
 * @param[in]  WupCfgPtr: Pointer to  Wakeup configuration
 * @return     Ret:
 * @retval     COMMON_SUCC: start delect  wakeup signal
 * @retval     COMMON_ERR:UART status is busy
 */
Common_ResultStatusType Uart_LinDetectWakeupSignal(Uart_LinDetWakeupCfgType *WupCfgPtr);

/**
 * @brief      LIN send wakeup signal function
 * @param[in]  WuFreq:the frequency of wakeup counter. 
 *                    Wakeup counter clock frequency = (serial clock freq)/(16 * WDR)
 * @param[in]  Num   :the length of wakeup signal will be calculated as follows
 *                    length = num / wuFreq
 * @return     Ret   :
 * @retval     COMMON_SUCC:start send  wakeup signal
 * @retval     COMMON_ERR :UART status is busy
 */
Common_ResultStatusType Uart_LinSendWakeupSignal(uint16 WuFreq, uint8 Num);

/*
 * @brief      Config the ID filter values for ID filter 0-15. It will config
 *             the ID filter values for ID filter 0 - (idNum-1) in order. The
 *             value to be configured is stored in the memory that idValues points
 *             to.
 * @param[in]  IdNum   :  the number of IDs to be configured. The range is 1-16.
 * @param[in]  IdValues:  a pointer to the ID filter value that will be used to
 *                        config the ID filters. The size of the memory must
 *                        not be smaller than idNum
 * @return     Ret:
 * @retval     COMMON_SUCC:config success
 * @retval     COMMON_ERR :parameter error
 */
Common_ResultStatusType Uart_LinConfigIdFilters(uint8 IdNum,const uint8 IdValues[]);

/**
 * @brief      Enable/Disable ID filters
 * @param[in]  IdIndex:the IDs to be enabled/disabled. The bit0-15 correspond to
 *                     ID filter 0-15. Bit 16 corresponds to the vague ID filter.
 *                     If a bit is 1,the corresponding ID filter is enabled;
 *                     otherwise it is disabled.
 * @return    none
 */
void Uart_LinControlIdFilters(uint32 IdIndex);

/**
 * @brief      Disable the vague ID filter
 * @param[in]  none
 * @return     none
 */
void Uart_LinDisableVagueIdFilter(void);

/**
 * @brief      Enable and config the ID vague filter
 * @param[in]  IdFilterValue: the value of ID filter. Its range is 0 - 0x3F.
 * @param[in]  IdFilterMask : the mask of the vague ID filter. If a bit of
 *                            idFilterMask is 0, this bit in the vague ID filter
 *                            is ignored. Only bit0-5 is valid.
 * @return     none
 */
void Uart_LinEnableVagueIdFilter(uint8 IdFilterValue,uint8 IdFilterMask);

/**
 * @brief      Disable a ID filter
 * @param[in]  IdIndex:  the index of ID filter. It indicates which ID filter
 *                       will be disabled. Its range is 0-15
 * @return     Ret:
 * @retval     COMMON_SUCC:disable filter success
 * @retval     COMMON_ERR :parameter error
 */
Common_ResultStatusType Uart_LinDisableIdFilter(uint32 IdIndex);

/**
 * @brief      Enable a ID filter and config the ID filter value
 * @param[in]  IdIndex:  the index of ID filter. It indicates which ID filter
 *                       will be enabled. Its range is 0-15
 * @param[in]  IdFilterValue:  the value of ID filter.
 * @return     Ret:
 * @retval     COMMON_SUCC:enable filter success
 * @retval     COMMON_ERR :parameter error
 */
Common_ResultStatusType Uart_LinEnableIdFilter(uint8 IdIndex,uint8 IdFilterValue);

/**
 * @brief      install call back function for interrupts 
 * @param[in]  IntType: select the interrupt
 *                      - UART_INT_RBFI
 *                      - UART_INT_TBEI
 *                      - ......
 *                      - UART_INT_LIN_RSP_OP_SUCC
 *                      - UART_INT_LIN_ALL
 *                      - UART_INT_ALL
 * @param[in]  CbFunPtr: pointer to callback function
 * @return     none
 */
void Uart_InstallCallBackFunc(Uart_IntType IntType,Isr_CbFuncType * CbFunPtr);


/**
* @brief       Mask/Unmask the UART interrupt
 *             UART_INT_RCVRTO and UART_INT_RBFI are controlled by the same bit,
 *             so they are masked/unmasked at the same time. But UART_INT_RCVRTO
 *             is only generated when it is in fifo mode and fifo is enabled
 * @param[in]  IntType: select the interrupt
 *                      - UART_INT_RBFI
 *                      - UART_INT_TBEI
 *                      - ......
 *                      - UART_INT_LIN_RSP_OP_SUCC
 *                      - UART_INT_LIN_ALL
 *                      - UART_INT_ALL
 * @param[in]  IntMask:  Enable/Disable Specified interrupt type
                        - COMMON_UNMASK
 *                      - COMMON_MASK
 * @return     none
 */
void Uart_SetIntMask(Uart_IntType IntType, Common_IntMaskType IntMask);

/**
 * @brief      Get UART FIFO status
 * @param[in]  none.
 * @return     Ret:
 * @retval     COMMON_SUCC:fifo is enable
 * @retval     COMMON_ERR :fifo is disable
 */
Common_ControlStateType Uart_GetFifoStatus(void);

/**
 * @brief      Get receive FIFO level
 * @param[in]  none.
 * @return     uint32:The number of valid data entries in the receive FIFO memory.
 */
uint32 Uart_GetRxFiFoLevel(void);

/**
 * @brief       Get transmit FIFO level
  * @param[in]  none.
 * @return      uint32:The number of valid data entries in the transmit FIFO memory.
 */
uint32 Uart_GetTxFiFoLevel(void);


/**
 * @brief      Set DMA transfer enable/disable when character timeout in fifo
 * @param[in]  Cmd: ENABLE/DISABLE
 * @return     none
 */
void Uart_EnableDmaTrigger(Common_ControlStateType Cmd);


/**
 * @brief      Set receive 9 bits data mode 0
 * @param[in]  none
 * @return     none
 */
void Uart_SetRx9BitsMode0Normal(void);

/**
 * @brief      Program the address of  receive 9 bits data, mode 1
 * @param[in]  Addr: Set address
 * @return     none
 */
void Uart_SetRx9BitsMode1Addr(uint8 Addr);

/**
 * @brief      Select 9 bits hardware receive mode 1
 * @param[in]  none
 * @return     none
 */
void Uart_SetRx9BitsMode1Enable(void);

/**
 * @brief      Receive address from the UART peripheral, mode 1
 * @param[in]  none
 * @return     uint16:the received address
 */
uint16 Uart_GetRx9BitsMode1Addr(void);

/**
 * @brief      Receive one byte data from the UART peripheral, mode 1
 * @param[in]  none
 * @return     uint16:The received data
 */
uint16 Uart_GetRx9BitsMode1Data(void);

/**
 * @brief      Program the transmit target address, 9bits, mode 0
 * @param[in]  Addr:  program the address
 * @return     none
 */
void Uart_SetTx9BitsMode0Addr(uint8 Addr);

/**
 * @brief      Set send address bit, mode 0
 * @param[in]  none
 * @return     none
 */
void Uart_Set9BitsMode0SendAddr(void);

/**
 * @brief      Send 9 bits data to the UART peripheral, mode 1
 * @param[in]  Data:  The data to be send
 * @return     none
 */
void Uart_SetTx9BitsMode1Data(uint16 Data);

/**
 * @brief      Config UART in LIN mode
 * @param[in]  ConfigPtr:  points to the configuration of LIN mode
 * @return     none
 */
void Uart_LinConfig(const Uart_LinConfigType *ConfigPtr);

/**
 * @brief      Enable/Disable LIN software calculate PID parity.
 * @param[in]  Cmd:  
 *                -COMMON_ENABLE:software calculate pid
 *                -COMMON_DISABLE:hardware calculate pid,default is hardware calculate.
 * @return     none
 */
void Uart_LinEnableSwCalcPid(Common_ControlStateType Cmd);

/**
 * @brief      Enable/Disable LIN readback detect bit error function.
 * @param[in]  Cmd:  ENABLE/DISABLE
 * @return     none
 */
void Uart_LinEnableBitErrorDetect(Common_ControlStateType Cmd);

/**
 * @brief      Set UART in LIN mode as a LIN master and start to send the header
 * @param[in]  HeaderPtr:  points to the header to be send
 * @return     Ret:
 * @retval     COMMON_SUCC:start send header
 * @retval     COMMON_ERR :UART status is busy
 */
Common_ResultStatusType Uart_LinSendHeader(const Uart_LinHeaderType *HeaderPtr);

/**
 * @brief       This function stops receiving/sending header/response of LIN. 
 * @param[in]   none
 * @return      none
 */
void Uart_LinStopTransmission(void);

/**
 * @brief       If LIN is sending/receiving header/response
 *              this function returns COMMON_SET, otherwise, return COMMON_RESET.
 * @param[in]   none
 * @return      Ret:
 * @retval      COMMON_SET   :UART status is busy
 * @retval      COMMON_RESET :UART transmission is done
 */
Common_FlagStatusType Uart_LinGetTransmissionStatus(void);

/**
 * @brief      Set LIN as a slave and start to receive a header.
 *             FIFO is disabled before it starts to receive a header
 * @param[in]  none
 * @return     Ret:
 * @retval     COMMON_SUCC : it starts to receive header
 * @retval     COMMON_ERR  :  it dose not start to receive header due to UART is busy
 */
Common_ResultStatusType Uart_LinStartReceiveHeader(void);

/**
 * @brief      Read the 6-bit ID(exclude parity bits) of header 
 * @param[in]  none
 * @return     uint8: ID
 */
uint8 Uart_LinGetId(void);

/**
 * @brief      Read the 8-bit PID of header
 * @param[in]  none
 * @return     uint32:ID
 */
uint32 Uart_LinGetPid(void);

/**
 * @brief      start to send a response
 * @param[in]  RspPtr:  Points to response structure to be sent.
 * @return     Ret:
 * @retval     COMMON_SUCC : response starts to send
 * @retval     COMMON_ERR  : response is not sent due to UART is busy
 */
Common_ResultStatusType Uart_LinSendResponse(const Uart_LinResponseType *RspPtr);

/**
 * @brief      start to receive a response
 * @param[in]  Check:  checksum type.
                       - UART_LIN_CHECKSUM_CLASSIC
                       - UART_LIN_CHECKSUM_ENHANCED
 * @param[in]  Len:  response length.
 * @return     Ret:
 * @retval     COMMON_SUCC : it starts to receive response
 * @retval     COMMON_ERR  : it dose not start to receive response due to UART is busy
 */
Common_ResultStatusType Uart_LinStartReceiveResponse(Uart_LinCheckSumType Check,
                                                         uint32 Len);

/**
 * @brief       Add LIN response timeout function
 *              The normal response timeout= (response length(byte) + checksum(1 byte)) * 1.4
 *              If the api is called, 
                timeout = (response length(byte) + checksum(1 byte)) * 1.4 + len(bits)
 * @param[in]   Len: several bits time added to delay LIN response timeout
 * @return      none
 */
void Uart_LinAddResponseTimeout(uint32 Len);

/**
 * @brief      read a response. if a response is received, this function can be
 *             called to get the data of response. This function is called
 *             after UART_LinStartReceiveResponse() and UART_INTSTA_RSP_DONE
 *             status is set.
 * @param[in]  Len:  response length to be read.
 * @param[in]  Data:  points to the memory where the response data to be stored.
 *                    the memory size must not be smaller than len
 * @return     none
 */
void Uart_LinReadResponse(uint32 Len, uint8 Data[]);

/** @}end of group Public_FunctionDeclaration */

#endif /* Uart_Drv_H */
