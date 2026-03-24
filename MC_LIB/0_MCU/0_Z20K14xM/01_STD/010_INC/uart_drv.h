/**************************************************************************************************/
/**
 * @file     uart_drv.h
 * @brief    UART driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#ifndef UART_DRV_H
#define UART_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  UART
 *  @{
 */

/** @defgroup UART_Public_Types
 *  @{
 */

/**
 *  @brief UART ID type definition
 */
typedef enum
{
    UART0_ID = 0U,                          /*!< UART0  */
    UART1_ID,                               /*!< UART1  */
    UART2_ID,                               /*!< UART2  */
    UART3_ID,                               /*!< UART3  */
    UART4_ID,                               /*!< UART4  */
    UART5_ID,                               /*!< UART5  */
} UART_ID_t;

/**
 *  @brief UART mode type definition
 */
typedef enum
{
    UART_MODE_UART = 0U,                    /*!< UART mode */
    UART_MODE_LIN,                          /*!< LIN mode */
} UART_Mode_t;

/**
 *  @brief UART parity type definition
 */
typedef enum
{
    UART_PARITY_NONE = 0U,                  /*!< UART parity none */
    UART_PARITY_ODD,                        /*!< UART parity odd  */
    UART_PARITY_EVEN                        /*!< UART parity even */
} UART_Parity_t;

/**
 *  @brief UART data bits type definition
 */
typedef enum
{
    UART_DATABITS_5 = 0U,           /*!< UART data bits length: 5 bits */
    UART_DATABITS_6,                /*!< UART data bits length: 6 bits */
    UART_DATABITS_7,                /*!< UART data bits length: 7 bits */
    UART_DATABITS_8,                /*!< UART data bits length: 8 bits */
    UART_DATABITS_9                 /*!< UART data bits length: 9 bits */
} UART_DataBits_t;

/**
 *  @brief UART stop bits type definition
 */
typedef enum
{
    UART_STOPBITS_1 = 0U,           /*!< UART stop bits length: 1 bit */
    UART_STOPBITS_1P5_2             /*!< UART stop bits length: 1.5 or 2 bits */
} UART_StopBits_t;

/**
 *  @brief UART TX FIFO level type definition
 */
typedef enum
{
    UART_TX_FIFO_EMPTY = 0U,        /*!< UART FIFO empty */
    UART_TX_FIFO_CHAR_2,            /*!< UART 2 characters in the FIFO */
    UART_TX_FIFO_QUARTER,           /*!< UART FIFO 1/4 full */
    UART_TX_FIFO_HALF               /*!< UART FIFO 1/2 full */
} UART_TxFIFOLvl_t;

/**
 *  @brief UART RX FIFO level type definition
 */
typedef enum
{
    UART_RX_FIFO_CHAR_1 = 0U,       /*!< UART 1 character in the FIFO */
    UART_RX_FIFO_QUARTER,           /*!< UART 1/4 full*/
    UART_RX_FIFO_HALF,              /*!< UART 1/2 full */
    UART_RX_FIFO_LESS_2             /*!< UART FIFO 2 less than full */
} UART_RxFIFOLvl_t;

/**
 *  @brief UART IDLE detect length type definition
 */
typedef enum
{
    UART_IDLE_DETECT_LENGTH_1 = 0U, /*!< UART idle detection length: 1-bit character    */
    UART_IDLE_DETECT_LENGTH_2,      /*!< UART idle detection length: 2-bit characters   */
    UART_IDLE_DETECT_LENGTH_4,      /*!< UART idle detection length: 4-bit characters   */
    UART_IDLE_DETECT_LENGTH_8,      /*!< UART idle detection length: 8-bit characters   */
    UART_IDLE_DETECT_LENGTH_16,     /*!< UART idle detection length: 16-bit characters  */
    UART_IDLE_DETECT_LENGTH_32,     /*!< UART idle detection length: 32-bit characters  */
    UART_IDLE_DETECT_LENGTH_64,     /*!< UART idle detection length: 64-bit characters  */
    UART_IDLE_DETECT_LENGTH_128     /*!< UART idle detection length: 128-bit characters */
} UART_IdleDetectLength_t;

/**
 *  @brief UART Line status bit type definition
 */
typedef enum
{
    UART_LINESTA_DR = 0U,                   /*!< Data ready */
    UART_LINESTA_OE,                        /*!< Overrun error */
    UART_LINESTA_PE,                        /*!< Parity error */
    UART_LINESTA_FE,                        /*!< Framing Error */
    UART_LINESTA_BI,                        /*!< Break interrupt */
    UART_LINESTA_THRE,                      /*!< Transmit holding register empty */
    UART_LINESTA_TEMT,                      /*!< Transmit empty */
    UART_LINESTA_RFE,                       /*!< RCV FIFO error */
    UART_LINESTA_TRANS_ERR,                 /*!< Indicate whether any of 'OE','PE',
                                            'FE','BI' and 'RFE' happens */
    UART_LINESTA_ADDR_RCVD,                 /*!< Address receive */
    UART_LINESTA_ASYNC,                     /*!< async interrupt */
    UART_LINESTA_FIELD_ERR,                 /*!< sync field error */
    UART_LINESTA_PID_ERR,                   /*!< PID error */
    UART_LINESTA_CHECKSUM_ERR,              /*!< checksum error */
    UART_LINESTA_TO_ERR,                    /*!< time out error in LIN mode*/
    UART_LINESTA_HEADER_DONE,               /*!< header done in LIN mode*/
    UART_LINESTA_RSP_DONE                   /*!< response done in LIN mode*/
} UART_LineStatus_t;

/**
 *  @brief UART interrupt type definition
 */
typedef enum
{    
    UART_INT_RBFI = 0U,             /*!< Received data available interrupt.*/
    UART_INT_TBEI,                  /*!< Transmit holding register empty 
                                         interrupt */
    UART_INT_LSI,                   /*!< RX line status interrupt*/
    UART_INT_MODEM,                 /*!< CTS interrupt */
    UART_INT_PTIME,                 /*!< Programmable THRE interrupt */
    UART_INT_BYDET,                 /*!< Busy detect interrupt, cannot be  
                                          masked */
    UART_INT_RCVRTO,                /*!< Character timeout interrupt, it is 
                                        effective only when enable the fifo */
    UART_INT_HEADER_DONE,           /*!< only LIN can generate Header done 
                                         interrupt */
    UART_INT_RSP_DONE,              /*!< only LIN can generate response done 
                                         interrupt */
    UART_INT_ASYNC,                 /*!< stop mode wake up: Async interrupt */
    UART_INT_ALL                    /*!< All the interrupt */
} UART_Int_t;


/**
 *  @brief UART LIN mode type definition
 */
typedef enum
{
    UART_LIN_SLAVE = 0U,            /*!< work as a LIN slave */
    UART_LIN_MASTER,                /*!< work as a LIN master */
} UART_LinMode_t;

/**
 *  @brief UART LIN checksum type definition
 */
typedef enum
{
    UART_LIN_CHECKSUM_CLASSIC = 0U, /*!< classic checksum */
    UART_LIN_CHECKSUM_ENHANCED,     /*!< enhanced checksum */
} UART_LinCheckSum_t;


/**
 *  @brief UART Configuration Structure type definition
 */
typedef struct
{
    uint32_t baudRate;              /*!< baud rate */
    UART_DataBits_t dataBits;       /*!< Data size, 5/6/7/8/9 bits */
    UART_Parity_t parity;           /*!< Parity Enable */
    UART_StopBits_t stopBits;       /*!< Number of stop bits */
    ControlState_t autoFlowControl; /*!< Auto flow control enable */
    uint32_t oscFreq;               /*!< the frequency of the OSC clock source*/
} UART_Config_t;

/**
 *  @brief UART FIFO Configuration Structure type definition
 */
typedef struct
{
    ControlState_t fifoEnable;      /*!< Enable/disable FIFO function*/
    ControlState_t txFifoReset;     /*!< Reset tx FIFO */
    ControlState_t rxFifoReset;     /*!< Reset rx FIFO */
    UART_TxFIFOLvl_t fifoTet;       /*!< Set TX Empty trigger level */
    UART_RxFIFOLvl_t fifoRt;        /*!< Set RCVR trigger level */
} UART_FIFOConfig_t;

/**
 *  @brief UART idle detect Structure type definition
 */
typedef struct
{
    ControlState_t Cmd;             /*!< Enable/disable idle detect*/
    UART_IdleDetectLength_t len;            /*!< IDLE detect length */
} UART_IdleDetectConfig_t;

/**
 *  @brief UART LIN Configuration Structure type definition
 */
typedef struct
{
    uint32_t baudRate;              /*!< baud rate */
    uint32_t oscFreq;               /*!< the frequency of OSC40M crystal*/
    UART_LinMode_t mode;            /*!< LIN mode */
    ControlState_t autoSyncEn;      /*!< auto sync enable flag, if is set to 
                                          ENABLE, it will detect the baudrate
                                         through the sync part of header and set 
                                          the baudrate automatically */
    ControlState_t idFilterEn;      /*!< whether enable ID filter when it
                                             receives header  */
} UART_LinConfig_t;

/**
 *  @brief UART LIN header Structure type definition
 */
typedef struct
{
    uint32_t id;                    /*!< 6-bit ID */
    uint32_t breakLen;              /*!< break field length */
    uint32_t deleLen;               /*!< delemiter length */
} UART_LinHeader_t;

/**
 *  @brief UART LIN header Structure type definition
 */
typedef struct
{
    UART_LinCheckSum_t checkType;   /*!< checksum type */
    uint32_t len;                   /*!< response length exclude checksum */
    uint8_t data[8];                /*!< the response payload exclude checksum*/
} UART_LinResponse_t;



/** @}end of group UART_Public_Types */

/** @defgroup UART_Public_Constants
 *  @{
 */

/** @}end of group UART_Public_Constants */

/** @defgroup UART_Public_Macro
 *  @{
 */

#define UART_NUM      6U
#define UART_INT_NUM  10U

/** @}end of group UART_Public_Macro */

/** @defgroup UART_Public_FunctionDeclaration
 *  @brief UART functions declaration
 *  @{
 */

/**
 * @brief      Initializes the UART
 * @param[in]  uartId:  Select the UART port,should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  uartConfig:  Pointer to a UART configuration structure
 * @return     none
 */
void UART_Init(UART_ID_t uartId, const UART_Config_t* uartConfig);

/**
 * @brief      Set UART rts enable 
 *
 * @param[in]  uartId:  UART peripheral selected, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  newState: Enable/Disable function state
 *
 * @return     none
 *
 */
void UART_RtsEnable(UART_ID_t uartId, ControlState_t newState);

/**
 * @brief      Reset uart receive fifo
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @return     none
 */
void UART_ResetRxFifo(UART_ID_t uartId);

/**
 * @brief      Reset uart transmit fifo
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @return     none
 */
void UART_ResetTxFifo(UART_ID_t uartId);

/**
 * @brief      Enable/Disable debug enable. If enabled, hardware will not clean 
 *             the recevier fifo automaticlly
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 *
 * @param[in]  ControlState_t: ENABLE/DISABLE
 *
 * @return     none
 *
 */
void UART_DebugCmd(UART_ID_t uartId, ControlState_t Cmd);

/**
 * @brief      idle detect config
 *
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 *
 * @param[in]  config: config idle detect 
 *
 * @return     none
 *
 */
void UART_IdleDetectConfig(UART_ID_t uartId,UART_IdleDetectConfig_t *config);

/**
 * @brief      Send break function, user can choose the length of break,
 *             the length should not be less than eleven
 *
 * @param[in]  uartId:  UART peripheral selected, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  len:     the length of break
 *
 * @return     
 *             - SUCC : break is sent
 *             - ERR : break length is invalid
 *
 */
ResultStatus_t UART_SendBreak(UART_ID_t uartId, uint8_t len);

/**
 * @brief      Set UART loopback mode
 * @param[in]  uartId:  UART peripheral selected, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  newState: Enable/Disable function state
 * @return     none
 */
void UART_SetLoopBackMode(UART_ID_t uartId, ControlState_t newState);

/**
 * @brief     Wait for UART busy bit clear
 *
 * @param[in]  uartId:  UART peripheral selected, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  cycle: the software cycles to be waited. User decides how many 
 *                     cycles need to be waited.
 * @return ResultStatus_t 
 *                       - SUCC: busy bit is cleared
 *                       - ERR: UART is still busy
 *
 */
ResultStatus_t UART_WaitBusyClear(UART_ID_t uartId, uint32_t cycle);

/**
 * @brief      Receive one byte data from the UART peripheral
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @return     The received data
 */
uint8_t UART_ReceiveByte(UART_ID_t uartId);

/**
 * @brief      Read received bytes from the RX FIFO
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  length:  the number of bytes to be read. When call this function,
 *                      the user needs to make sure that the "length" is not
 *                      greater than the number of bytes that is available in
 *                      RX FIFO
 * @param[out]  data:  points to the memory where the data to be stored
 *.
 * @return     none
 */
void UART_ReceiveBytes(UART_ID_t uartId,uint32_t length, uint8_t data[]);

/**
 * @brief      Empty the RX FIFO. This function reads received data until RX
 *             FIFO is empty
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 *
 * @return     None
 */
void UART_EmptyRxFifo(UART_ID_t uartId);

/**
 * @brief      Send one byte data to the UART peripheral
 * @param[in]  uartId:  Select the UART port,should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  data:  The data to be sent
 * @return     none
 */
void UART_SendByte(UART_ID_t uartId, uint8_t data);

/**
 * @brief      Config UART FIFO function
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  fifoConfig:  Pointer to a FIFO configuration
 * @return     none
 */
void UART_FIFOConfig(UART_ID_t uartId, const UART_FIFOConfig_t* fifoConfig);

/**
 * @brief      Get current value of Line Status register
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
* @param[in]  lineStatus:
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
 *                       - UART_LINESTA_ASYNC
 *                       - UART_LINESTA_FIELD_ERR
 *                       - UART_LINESTA_PID_ERR
 *                       - UART_LINESTA_CHECKSUM_ERR
 *                       - UART_LINESTA_TO_ERR
 *                       - UART_LINESTA_HEADER_DONE
 *                       - UART_LINESTA_RSP_DONE
 * 
 * @note       This function returns only one line status. However,  once call 
 *             this function, all line status will be cleared. If user
 *             needs to read more than one line status, it is suggested to use 
 *             UART_GetAllLineStatus() to get all line status and handle them 
 *             one by one.
 *
 * @return     The state value of UART Line Status register
 */
FlagStatus_t UART_GetLineStatus(UART_ID_t uartId, UART_LineStatus_t lineStatus);

/**
 * @brief      Get all Line Status 
 *
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * 
 * @note       Once call the function, line status will be cleared
 *
 * @return     The state value of UART Line Status register
 *
 */
uint32_t UART_GetAllLineStatus(UART_ID_t uartId);

/**
 * @brief      Get busy status
 *
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 *
 * @return     The busy Status
 *
 */
FlagStatus_t UART_GetBusyStatus(UART_ID_t uartId);

/**
 * @brief      Get current UART interrupt status, except async status
 *
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  intType: select one interrupt
 *
 * @note       If only need async status, can use UART_GetLineStatus function.
 *             
 * @return     The state value of UART Status register

 */
IntStatus_t UART_GetIntStatus(UART_ID_t uartId, UART_Int_t intType);

/**
 * @brief      Config the ID filter values for ID filter 0-15. It will config
 *             the ID filter values for ID filter 0 - (idNum-1) in order. The
 *             value to be configed is stored in the memory that idValues points
 *             to.
 * @param[in]  uartId:  Select the UART port.It should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  idNum:  the number of IDs to be configured. The range is 1-16.
 * @param[in]  idValues:  a pointer to the ID filter value that will be used to
 *                        config the ID filters. The size of the memory must
 *                        not smaller than idNum
 * @return
 *            - SUCC
 *            - ERR : parameter error
 *
 */
ResultStatus_t UART_LinConfigIdFilters(UART_ID_t uartId, uint8_t idNum,
                                       const uint8_t idValues[]);

/**
 * @brief      Enable/Disable ID filters
 * @param[in]  uartId:  Select the UART port.It should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  ids:  the IDs to be enabled/disabled. The bit0-15 correspond to
 *                   ID filter 0-15. Bit 16 corresponds to the vague ID filter.
 *                   If a bit is 1,the corresponding ID filter is enabled;
 *                   otherwise is disabled.
 * @return    none
 *
 */
void UART_LinIdFiltersCmd(UART_ID_t uartId, uint32_t idIndex);

/**
 * @brief      Disable the vague ID filter
 * @param[in]  uartId:  Select the UART port.It should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @return     none
 *
 */
void UART_LinDisableVagueIdFilter(UART_ID_t uartId);

/**
 * @brief      Enable and config the ID vague filter
 * @param[in]  uartId:  Select the UART port.It should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  idFilterValue:  the value of ID filter. It is range is 0 - 0x3F.
 * @param[in]  idFilterMask:  the mask of the vague ID filter. If a bit of
 *                            idFilterMask is 0, this bit in the vague ID filter
 *                            is ignored. Only bit0-5 is valid.
 * @return     none
 *
 */
void UART_LinEnableVagueIdFilter(UART_ID_t uartId,
                                           uint8_t idFilterValue,
                                           uint8_t idFilterMask);

/**
 * @brief      Disable a ID filter
 * @param[in]  uartId:  Select the UART port.It should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  idIndex:  the index of ID filter. It indicates which ID filter
 *                       will be disabled. Its range is 0-15
 * @return
 *            - SUCC
 *            - ERR : parameter error
 *
 */
ResultStatus_t UART_LinDisableIdFilter(UART_ID_t uartId, uint32_t idIndex);

/**
 * @brief      Enable a ID filter and config the ID filter value
 * @param[in]  uartId:  Select the UART port.It should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  idIndex:  the index of ID filter. It indicates which ID filter
 *                       will be enabled. Its range is 0-15
 * @param[in]  idFilterValue:  the value of ID filter.
 * @return
 *            - SUCC
 *            - ERR : parameter error
 *
 */
ResultStatus_t UART_LinEnableIdFilter(UART_ID_t uartId, uint8_t idIndex,
                                      uint8_t idFilterValue);

/**
 * @brief      install call back function for interrupts 
 *
 * @param[in]  uartId: Select the UART port,should be UART0_ID, UART1_ID,
 *                     UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  intType: select the interrupt
 * @param[in]  cbFun: pointer to callback function
 *
 * @return     none
 */
void UART_InstallCallBackFunc(UART_ID_t uartId, UART_Int_t intType,
                              isr_cb_t * cbFun);

/**
 * @brief      Get line status buffer in interrupt call back functions. The line 
 *             status will be stored into line status buffer in UART_IRQHandler.
 *             If the call back functions which are installed through 
 *             UART_InstallCallBackFunc()  needs to get the line status, please 
 *             use this function instead of UART_GetAllLineStatus or 
 *             UART_GetLineStatus.
 *
 * @param[in]  uartId: Select the UART port,should be UART0_ID, UART1_ID,
 *                     UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 *
 * @return     linestatus
 *
 */
uint32_t UART_GetLineStatusBufForCbf(UART_ID_t uartId);

/**
* @brief     Mask/Unmask the UART interrupt
 *            UART_INT_RCVRTO and UART_INT_RBFI are controlled by the same bit,
 *            so they are masked/unmasked at the same time. But UART_INT_RCVRTO
 *            is only generated when it in fifo mode and fifo is enabled
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  intType:  Specifies the interrupt type
 * @param[in]  intMask:  Enable/Disable Specified interrupt type
 * @return     none
 */
void UART_IntMask(UART_ID_t uartId, UART_Int_t intType, IntMask_t intMask);

/**
 * @brief      Get UART FIFO status
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @return     status
 */
ControlState_t UART_GetFifoStatus(UART_ID_t uartId);

/**
 * @brief      Set receive 9 bits data mode 0
 * @param[in]  uartId: Select the UART port, should be UART0_ID, UART1_ID,
 *                     UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @return     none
 */
void UART_9BitsM0Rx(UART_ID_t uartId);

/**
 * @brief      Program the address of  receive 9 bits data, mode 1
 * @param[in]  uartId: Select the UART port, should be UART0_ID, UART1_ID,
 *                     UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @return     none
 */
void UART_9BitsM1SetAddr(UART_ID_t uartId, uint8_t addr);

/**
 * @brief      Select 9 bits hardware receive mode 1
 * @param[in]  uartId: Select the UART port, should be UART0_ID, UART1_ID,
 *                     UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @return     none
 */
void UART_9BitsHWRecvEnable(UART_ID_t uartId);

/**
 * @brief      Receive address from the UART peripheral, mode 1
 * @param[in]  uartId: Select the UART port, should be UART0_ID, UART1_ID,
 *                     UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @return     the received address
 */
uint16_t UART_9BitsM1RxAddr(UART_ID_t uartId);

/**
 * @brief      Receive one byte data from the UART peripheral, mode 1
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @return     The received data
 */
uint16_t UART_9BitsM1RxData(UART_ID_t uartId);

/**
 * @brief      Program the transmit target address, 9bits, mode 0
 * @param[in]  uartId:  Select the UART port,should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  addr:  program the address
 * @return     none
 */
void UART_9BitsM0SetAddr(UART_ID_t uartId, uint8_t addr);

/**
 * @brief      Set send address bit, mode 0
 * @param[in]  uartId:  Select the UART port,should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @return     none
 */
void UART_9BitsM0SendAddr(UART_ID_t uartId);

/**
 * @brief      Send 9 bits data to the UART peripheral, mode 1
 * @param[in]  uartId:  Select the UART port,should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  data:  The data to be sent
 * @return     none
 */
void UART_9BitsM1TxData(UART_ID_t uartId, uint16_t data);

/**
 * @brief      Config UART in LIN mode
 * @param[in]  uartId:  Select the UART port. It should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  config:  points to the configuration of LIN mode
 * @return     none
 */
void UART_LinConfig(UART_ID_t uartId, const UART_LinConfig_t *config);

/**
 * @brief      Set UART in LIN mode as a LIN master and start to send the header
 * @param[in]  uartId:  Select the UART port.It should be  UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  header:  points to the header to be send
 * @return     status
 *             - SUCC : header is sent
 *             - ERR : header is not sent due to UART is busy
 */
ResultStatus_t UART_LinSendHeader(UART_ID_t uartId, 
                                  const UART_LinHeader_t *header);

/**
 * @brief       This function stops receiving/sending header/response of LIN. 
 *
 * @param[in]   uartId:  Select the UART port.It should be  UART0_ID, UART1_ID,
 *                     UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 *                     
 * @return     none
 */
void UART_LinStopTransmission(UART_ID_t uartId);

/**
 * @brief       If LIN is sending/receiving header/response
 *                this function returns SET, otherwise, return RESET.
 *
 * @param[in]   uartId:  Select the UART port.It should be  UART0_ID, UART1_ID,
 *                     UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 *                     
 * @return     SET/RESET
 */
FlagStatus_t UART_LinGetTransmissionStatus(UART_ID_t uartId);

/**
 * @brief      Set LIN as a slave and start to receive a header.
 *             FIFO is disabled before it starts to receive a header
 *
 * @param[in]  uartId:  Select the UART port.It should be  UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @return     
 *            - SUCC : it starts to receive header
 *            - ERR : it dose not start to receive header due to UART is busy
 */
ResultStatus_t UART_LinStartReceiveHeader(UART_ID_t uartId);

/**
 * @brief      read the 6-bit ID(exclude parity bits) of header
 * @param[in]  uartId:  Select the UART port.UART0_ID, UART1_ID,
 *                     UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @return     ID
 */
uint32_t UART_LinGetId(UART_ID_t uartId);

/**
 * @brief      start to send a response
 * @param[in]  uartId:  Select the UART port.It should be  UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  rsp:  Points to reponse structure to be sent.
 * @return
 *             - SUCC : response is sent
 *             - ERR : resoponse is not sent due to UART is busy

 */
ResultStatus_t UART_LinSendResponse(UART_ID_t uartId,
                                    const UART_LinResponse_t *rsp);

/**
 * @brief      start to receive a response
 * @param[in]  uartId:  Select the UART port.It should be  UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  check:  checksum type.
 * @param[in]  len:  response length.
 * @return
 *            - SUCC : it starts to receive response
 *            - ERR : it dose not start to receive response due to UART is busy
 */
ResultStatus_t UART_LinStartReceiveResponse(UART_ID_t uartId,
                                            UART_LinCheckSum_t check,
                                            uint32_t len);

/**
 * @brief      read a response. if a reponse is received, this function can be
 *             called to get the data of response. This function is called
 *             after UART_LinStartReceiveResponse() and UART_INTSTA_RSP_DONE
 *             status is set.
 * @param[in]  uartId:  Select the UART port.It should be  UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID, UART4_ID, UART5_ID.
 * @param[in]  len:  response length to be read.
 * @param[in]  data:  points to the memory where the response data to be stored.
 *                    the memory size must not be smaller than len
 * @return     none
 */
void UART_LinReadResponse(UART_ID_t uartId, uint32_t len, uint8_t data[]);



/** @}end of group UART_Public_FunctionDeclaration */

/** @}end of group UART  */

/** @}end of group Z20K14XM_Peripheral_Driver */

#endif /* UART_DRV_H */
