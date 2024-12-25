/**************************************************************************************************/
/**
 * @file     i2c_drv.h
 * @brief    I2C module driver header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#ifndef I2C_DRV_H
#define I2C_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  I2C
 *  @{
 */

/** @defgroup  I2C_Public_Types
 *  @{
 */

/**
 *  @brief I2C master and slave type definition
 */
typedef enum
{
    I2C_MASTER = 0U,                             /*!< I2C master mode define.*/
    I2C_SLAVE                                    /*!< I2C slave mode define.*/
} I2C_Mode_t;

/**
 *  @brief I2C speed type definition
 */
typedef enum
{
    I2C_SPEED_STANDARD = 1U,                      /*!< I2C standard speed define.(0 to 100 Kb/s)*/
    I2C_SPEED_FAST = 2U,                          /*!< I2C fast speed define.(up to 400 Kb/s)*/
    I2C_SPEED_HIGH = 3U,                          /*!< I2C high speed define.(up to 1.6 Mb/s)*/
    I2C_SPEED_FAST_PLUS = 6U                      /*!< I2C fast mode plus define.(up to 1000 Kb/s)*/
} I2C_Speed_t;

/**
 *  @brief I2C address type definition
 */
typedef enum
{
    I2C_ADDR_BITS_7 = 0U,                         /*!< I2C 7 bits address mode define.*/
    I2C_ADDR_BITS_10                              /*!< I2C 10 bits address mode define.*/
} I2C_Addr_t;

/**
 *  @brief I2C restart and stop type definition
 */
typedef enum
{
    I2C_RESTART_AND_STOP_DISABLE = 0U,  /*!< No RESTART and STOP signals are generated. */
    I2C_STOP_EN,                     /*!< A STOP is issued after the byte is sent or received. */
    I2C_RESTART_EN                   /*!< A RESTART is issued before the byte is sent or received.*/
} I2C_RestartStop_t;

/**
 *  @brief I2C stop_detect if addressed type definition
 */
typedef enum
{
    I2C_SLV_STOP_DET_WHE_ADDRESSED = 0U,  /*!< In slave mode:I2C generates the STOP_DETECT interrupt 
                                               flag no matter slave address match or not. */
    I2C_SLV_STOP_DET_ADDRESSED            /*!< In slave mode:I2C generates the STOP_DETECT 
                                               interrupt flag only slave address matches*/
} I2C_StopDetAddressed_t;

/**
 *  @brief I2C stop_detect if master active type definition
 */
typedef enum
{
    I2C_MST_STOP_DET_WHE_ACTIVE = 0U,     /*!< In master mode:I2C generates the STOP_DETECT 
                                               interrupt flag no matter master's state. */
    I2C_MST_STOP_DET_ACTIVE               /*!< In master mode:I2C generates the STOP_DETECT 
                                               interrupt flag only when I2C master is active.*/
} I2C_StopDetActive_t;

/**
 *  @brief I2C generates slave data nack type definition
 */
typedef enum
{
    I2C_GEN_NACK_OR_ACK_NORMAL = 0U,      /*!< I2C generates NACK/ACK normally.*/
    I2C_GEN_NACK_AFTER_RCV                /*!< I2C generates NACK after data byte is received.Then 
                                               this data will be aborted,not pushed into RX FIFO. */
} I2C_GenSlvDataNack_t;

/**
 *  @brief I2C choose different transfer address type definition
 */
typedef enum
{
    I2C_DEST_ADDR = 0U,                 /*!< I2C transfers DEST_ADDR normally.*/
    I2C_GEN_CALL_ADDR = 2U,             /*!< I2C will launch a General Call (transfer data is 0x00), 
                                             only writes may be performed.Any read option will 
                                             result asserting ERROR_ABORT flag. */
    I2C_START_BYTE = 3U,                /*!< I2C transfers START BYTE (transfer data is 0x01), 
                                             should no slave ack. */
} I2C_MstCmdSelect_t;

/**
 *  @brief I2C generation of the TXFIFO_EMPTY interrupt type definition
 */
typedef enum
{
    I2C_TX_BUFFER = 0U,              /*!< When TXFIFO_EMPTY_EN = 0: This bit is set to 1 when the
                                        transmit buffer is at or below the threshold value set 
                                        in the I2C_TXFIFO_WATER_MARK register.*/
    I2C_TX_DATA_PATH                 /*!< When TXFIFO_EMPTY_EN = 1: This bit is set to 1 when the
                                        transmit buffer is at or below the threshold value set in
                                        the I2C_TXFIFO_WATER_MARK register and the transmission of
                                        the address/data from the internal shift register for the 
                                        most recently popped command is completed. */
} I2C_TxEmptyCtrl_t;

/**
 *  @brief I2C interrupt type definition
 */
typedef enum
{
    I2C_INT_GEN_CALL = 0U,    /*!< A General Call address is received and it is acknowledged. */
    I2C_INT_TX_OVER,          /*!< Transmit FIFO above TX FIFO depth and CPU attempts to issue 
                                 another I2C command by writing to the I2C_COMMAND_DATA register. */
    I2C_INT_ERROR_ABORT,      /*!< Error abort interrupt. */
    I2C_INT_ACTIVITY,         /*!< I2C activity interrupt. There are four ways to clear it:
                                    - Disabling the I2C module
                                    - Writing 1 to the I2C_STATUS0[ACTIVITY]
                                    - Writing 0 to the I2C_INT_ENABLE[I2C_ACTIVITY_DET_IE]
                                    - System reset */
    I2C_INT_STOP_DET,         /*!< A STOP signal generated interrupt. */
    I2C_INT_START_DET,        /*!< A START or RESTART signal generated interrupt. */
    I2C_INT_RD_REQ,           /*!< Slave read request interrupt. */
    I2C_INT_RX_DONE,          /*!< The transmission done interrupt,only valid for I2C as a slave
                                   transmitter. */
    I2C_INT_RX_UNDER,         /*!< Receive FIFO underflow interrupt. */
    I2C_INT_RX_OVER,          /*!< Received FIFO overflow interrupt. */
    I2C_INT_RESTART_DET,      /*!< A RESTART signal generated interrupt,operating in slave mode and 
                                   the slave is the addressed slave. */
    I2C_INT_SCL_STUCK_AT_LOW,   /*!< SCL stuck at low interrupt. */
    I2C_INT_RX_FULL,            /*!< Received FIFO full interrupt. */
    I2C_INT_TX_EMPTY,           /*!< Transmit FIFO empty interrupt.
                                    - When TXFIFO_EMPTY_EN = 0: 
                                    This bit is set to 1 when the transmit buffer is at or below the
                                    threshold value set in the I2C_TXFIFO_WATER_MARK register.
                                    - When TXFIFO_EMPTY_EN = 1:
                                    This bit is set to 1 when the transmit buffer is at or below the
                                    threshold value set in the I2C_TXFIFO_WATER_MARK register and 
                                    the transmission of the address/data from the internal shift 
                                    register for the most recently popped command is completed. */
    I2C_INT_ALL                 /*!< All the interrupt. */
} I2C_Int_t;

/**
 *  @brief I2C status type definition
 */
typedef enum
{
    I2C_MST_ACTIVITY = 0U,            /*!< When master is not under idle bit, this bit will be set 1.
                                            - 0: means MASTER FSM is idle
                                            - 1: means MASTER FSM is not idle */
    I2C_SLV_ACTIVITY,                 /*!< When slave is not under idle bit, this bit will be set 1.
                                            - 0: means SLAVE FSM is idle
                                            - 1: means SLAVE FSM is not idle */
    I2C_TXFIFO_EMPTY_MASTER_HOLD,     /*!< This bit indicates Tx FIFO is empty, and the the previous
                                           transferred command does not have Stop bit,so master hold
                                           the bus. */
    I2C_TXFIFO_EMPTY_SLAVE_HOLD,      /*!< This bit indicates when the Tx FIFO is empty, slave will
                                           hold the bus until slave TX FIFO has data to Transmit for
                                           the read request. */
    I2C_RXFIFO_FULL_MASTER_HOLD,      /*!< This bit indicates RX FIFO is full and receive new data,
                                           so master will hold the bus. */
    I2C_RXFIFO_FULL_SLAVE_HOLD,       /*!< This bit indicates RX FIFO is full and receive new data,
                                           so slave will hold the bus. */
    I2C_STATUS_TFNF,                  /*!< Transmit FIFO not full,means TX FIFO still has one or
                                           more empty locations. */
    I2C_STATUS_TFE,                   /*!< Transmit FIFO empty,means TX FIFO is completely empty. */
    I2C_STATUS_RFNE,                  /*!< Receive FIFO not empty.When RX FIFO has one or more 
                                           entries already. This bit will be set to 1. */
    I2C_STATUS_RFF,                   /*!< Receive FIFO full.When RX FIFO is completely full, 
                                           this bit will be set 1. */
    I2C_SDA_ERR_RECOVER_STUCK_LOW,    /*!< SDA error recover from sticking at low phase.This bit is 
                                       set when SDA fail to recover,and still stuck at low phase. */
    I2C_SLAVE_IS_DISABLED_UNDER_ACT,  /*!< Slave is disabled under active state.When read as 1, 
                                           it means slave is potentially disabled during slave 
                                           transfer phase. */
    I2C_SLAVE_RX_DATA_DISCARD,        /*!< Slave receive data discard.When read as 1, it means I2C
                                           slave is aborted with at least one data byte from I2C
                                           transfer due to MODULE_EN from 1 to 0. */
    I2C_ENABLE,                       /*!< I2C enable flag.
                                            - 0: means I2C is disable
                                            - 1: means I2C is enabled */
} I2C_Status_t;

/**
 *  @brief I2C tx abort Source type definition
 */
typedef enum
{
    I2C_ERR_GEN_CALL_NO_ACK = 0U,       /*!< I2C in master mode sent a General Call and no slave 
                                            on the bus acknowledged the General Call. */
    I2C_ERR_GEN_CALL_READ,              /*!< I2C in master mode sent a General Call but the user
                                            programmed the byte following the General Call to be
                                            a read from the bus */
    I2C_ERR_START_BYTE_ACK_DET,         /*!< Master has sent a START Byte and the START Byte was
                                            acknowledged (wrong behavior) */
    I2C_ERR_SBYTE_NORSTRT,              /*!< The start is disabled and the user is trying to send 
                                            a START Byte */
    I2C_ERR_H_NO_RSTRT,                 /*!< The restart is disabled and the user is trying to use 
                                            the master to transfer data in high speed mode. */
    I2C_ERR_H_MCODE_ACK_DET,            /*!< Master is in High Speed mode and the High Speed 
                                            Master code was acknowledged (wrong behavior). */
    I2C_ERR_7BIT_ADDR_NO_ACK,           /*!< Master is in 7-bit addressing mode and the address 
                                            sent was not acknowledged by any slave */
    I2C_ERR_10BIT_ADDR1_NO_ACK,         /*!< Master is in 10-bit address mode and the first 10-bit
                                            address byte was not acknowledged by any slave. */
    I2C_ERR_10BIT_ADDR2_NO_ACK,         /*!< Master is in 10-bit address mode and the second 
                                            address byte of the 10-bit address was not 
                                            acknowledged by any slave. */
    I2C_ERR_10BIT_READ_NO_RSTRT,        /*!< Will assert 1 when read 10 bit under EN_RESTART = 0. */
    I2C_ERR_DATA_NO_ACK,                /*!< This is a master-mode only bit. Master has received 
                                            an acknowledgement for the address, but when it sent
                                            data byte(s) following the address, it did not 
                                            receive an acknowledge from the remote slave(s). */
    I2C_ERR_MASTER_LOST,                /*!< Master has lost arbitration, or if 
                                               I2C_ERROR_STATUS[13] is also set, then the slave 
                                               transmitter has lost arbitration. */
    I2C_ERR_MASTER_DIS,                 /*!< User tries to initiate a Master operation with the 
                                            Master mode disabled */
    I2C_ERR_SLAVE_ARBLOST,              /*!< Slave lost the bus while transmitting data to a 
                                            remote master.I2C_ERROR_STATUS[14] is set at the same
                                            time. */
    I2C_ERR_MASTER_ABRT,                /*!< This is a master-mode-only bit. Master has detected 
                                            the transfer abort. */
    I2C_ERR_SLAVE_READ_REQ,             /*!< When the processor side responds to a slave mode 
                                            request for data to be transmitted to a remote master 
                                            and user writes a 1 in CMD_MASTER_DIRECTION (bit 8) 
                                            of I2C_COMMAND_REG register. */
    I2C_ERR_SLAVE_FLUSH_TXFIFO,         /*!< Slave has received a read command and some data 
                                            exists in the TX FIFO so the slave issues a 
                                            ERROR_ABORT interrupt to flush old data in TX FIFO. */
    I2C_ERR_SDA_LOW_TIMEOUT,            /*!< SDA stuck at low and timeout error. */
} I2C_ErrorStatus_t;

/**
 *  @brief I2C No. type definition
 */
typedef enum
{
    I2C0_ID = 0U,                                           /*!< I2C0 port define */
#if (I2C_INSTANCE_NUM == 2)
    I2C1_ID                                                 /*!< I2C1 port define */
#endif
} I2C_Id_t;

/**
 *  @brief I2C Configuration Structure type definition
 */
typedef struct
{
    I2C_Mode_t masterSlaveMode;         /*!< Specifies the I2C mode.
                                            - I2C_MASTER: I2C master enable
                                            - I2C_SLAVE: I2C slave enable*/
    I2C_Speed_t speedMode;              /*!< Specifies the I2C speed mode.
                                            - I2C_SPEED_STANDARD: standard speed (0 to 100 Kb/s)
                                            - I2C_SPEED_FAST: fast speed (<= 400 Kb/s)
                                            - I2C_SPEED_HIGH: high speed (<= 1.6 Mb/s)
                                            - I2C_SPEED_FAST_PLUS: fast plus speed(<= 1000 Kb/s) */
    I2C_Addr_t addrBitMode;             /*!< I2C start its transfer in 7 or 10 bits address mode
                                            - I2C_ADDR_BITS_7: 7 bits address mode
                                            - I2C_ADDR_BITS_10: 10 bits address mode */
    uint32_t ownSlaveAddr;              /*!< Slave address when the I2C is operating as a slave.
                                             This parameter can be a 7-bit or 10-bit address. */
    ControlState_t restart;             /*!< Determines whether RESTART conditions may be sent when 
                                            acting as a master.
                                            - ENABLE: enable RESTART condition
                                            - DISABLE: disable RESTART condition
                                            When the RESTART is disabled, the I2C module master is 
                                            incapable of performing the following functions:
                                            - Sending a START BYTE
                                            - Performing any high-speed mode operation
                                            - Performing direction changes in combined format mode
                                            - Performing a read operation with a 10-bit address */
} I2C_Config_t;

/**
 *  @brief I2C FIFO threshold level type definition
 */
typedef struct
{
    uint32_t recvFifoThr;            /*!< Receive FIFO threshold level,the valid range is 0 - 3. */
    uint32_t transmitFifoThr;        /*!< Transmit FIFO threshold level,the valid range is 0 - 3. */
} I2C_FifoConfig_t;

/**
 *  @brief I2C SDA hold time type definition
 */
typedef struct
{
    uint32_t sdaReceiveHoldTime;   /*!< Sets the required SDA hold time in units of I2C function 
                                        clock period, when I2C module acts as a receiver. 
                                        SDA data hold time after SCL negedge. */
    uint32_t sdaTransmitHoldTime;  /*!< Sets the required SDA hold time in units of I2C function 
                                        clock period, when I2C module acts as a transmitter.
                                        SDA data hold time after SCL negedge. */
} I2C_SdaHoldTime_t;

/**
 *  @brief I2C DMA request FIFO level type definition
 */
typedef struct
{
    uint32_t i2cDmaTransmitReqLevel;      /*!< DMA transmit data level, the valid range is 0 - 3 */
    uint32_t i2cDmaRecvReqLevel;          /*!< DMA Receive data level, the valid range is 0 - 3 */
} I2C_DmaConfig_t;

/**
 *  @brief I2C SCL timing config definition
 */
typedef struct
{
    I2C_Speed_t speedMode;              /*!< Specifies the I2C speed mode.
                                            - I2C_SPEED_STANDARD: standard speed (0 to 100 Kb/s)
                                            - I2C_SPEED_FAST: fast speed (up to 400 Kb/s)
                                            - I2C_SPEED_HIGH: high speed (up to 1.6 Mb/s)
                                            - I2C_SPEED_FAST_PLUS: fast plus speed(up to 1000 Kb/s) 
                                        */
    uint32_t i2cSclHighCount;           /*!< I2C Clock SCL High Count, Sets the high count in units
                                            of I2C functional clock period,The SCL actual high time 
                                            phase equals highCount+spikeCount+7.
                                        */
    uint32_t i2cSclLowCount;            /*!< Sets the low count in units of I2C functional clock 
                                            period, The SCL actual low time phase equals lowCount+1.
                                        */
    uint32_t i2cSpikeLengthCount;       /*!< Configure spike filter count in units of I2C functional 
                                            clock period. 
                                        */
} I2C_SclTiming_t;
/** @} end of group I2C_Public_Types definitions */

/** @defgroup I2C_Public_Constants
 *  @{
 */

/** @} end of group I2C_Public_Constants definitions*/


/** @defgroup I2C_Public_Macro
 *  @{
 */

/** @} end of group I2C_Public_Macro */

/** @defgroup I2C_Public_FunctionDeclaration
 *  @brief I2C function statement
 *  @{
 */
/**
 * @brief      Install call back function
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C0_ID.
 * @param[in]  intId: Specified interrupt type.
 *             - I2C_INT_GEN_CALL
 *             - I2C_INT_TX_OVER
 *             - I2C_INT_ERROR_ABORT
 *             - I2C_INT_ACTIVITY
 *             - I2C_INT_STOP_DET
 *             - I2C_INT_START_DET
 *             - I2C_INT_RD_REQ
 *             - I2C_INT_RX_DONE
 *             - I2C_INT_RX_UNDER
 *             - I2C_INT_RX_OVER
 *             - I2C_INT_RESTART_DET
 *             - I2C_INT_SCL_STUCK_AT_LOW
 *             - I2C_INT_RX_FULL
 *             - I2C_INT_TX_EMPTY
 *             - I2C_INT_ALL
 *
 * @param[in]  cbFun: Pointer to callback function.
 *
 * @return none
 *
 */
void I2C_InstallCallBackFunc(I2C_Id_t i2cNo, I2C_Int_t intId,
                              isr_cb_t * cbFun);

/**
 * @brief      Initializes the I2C
 * Under the premise that the crystal oscillator is OSC40M, speed mode selects
 * standard speed and the default data transfer rate is 100 Kb/s. Speed mode
 * selects fast speed and the default data transfer rate is 400 Kb/s.Speed mode
 * selects fast plus speed and the default data transfer rate is 1 Mb/s.
 *
 * Under the premise that the crystal oscillator is FIRC64M,speed mode selects
 * high speed and the default data transfer rate is 1.6 Mb/s.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  i2cConfigStruct: Pointer to a I2C configuration structure.
 *
 * @return none
 *
 */
void I2C_Init(I2C_Id_t i2cNo, const I2C_Config_t* i2cConfigStruct);

/**
 * @brief      Configure SCL High Count
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  speedMode: Speed mode types.
 *             - I2C_SPEED_STANDARD:I2C standard speed define.(0 to 100 Kb/s)
 *             - I2C_SPEED_FAST:I2C fast speed define.(up to 400 Kb/s)
 *             - I2C_SPEED_HIGH:I2C high speed define.(up to 1.6 Mb/s)
 *             - I2C_SPEED_FAST_PLUS:I2C fast mode plus define.(up to 1000 Kb/s)
 *
 * @return none
 *
 */
void I2C_SclHighCount(I2C_Id_t i2cNo, I2C_Speed_t speedMode);

/**
 * @brief      Configure SCL Low Count
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  speedMode: Speed mode types.
 *             - I2C_SPEED_STANDARD:I2C standard speed define.(0 to 100 Kb/s)
 *             - I2C_SPEED_FAST:I2C fast speed define.(up to 400 Kb/s)
 *             - I2C_SPEED_HIGH:I2C high speed define.(up to 1.6 Mb/s)
 *             - I2C_SPEED_FAST_PLUS:I2C fast mode plus define.(up to 1000 Kb/s)
 *
 * @return none
 *
 */
void I2C_SclLowCount(I2C_Id_t i2cNo, I2C_Speed_t speedMode);

/**
 * @brief      Configure Spike Suppression Limit
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  speedMode: Speed mode types.
 *             - I2C_SPEED_STANDARD:I2C standard speed define.(0 to 100 Kb/s)
 *             - I2C_SPEED_FAST:I2C fast speed define.(up to 400 Kb/s)
 *             - I2C_SPEED_HIGH:I2C high speed define.(up to 1.6 Mb/s)
 *             - I2C_SPEED_FAST_PLUS:I2C fast mode plus define.(up to 1000 Kb/s)
 *
 * @return none
 *
 */
void I2C_LimitSpikeSuppression(I2C_Id_t i2cNo, I2C_Speed_t speedMode);

/**
 * @brief      Set the target address .
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  targetAddr: The target address for any master transaction.
 *
 * @return none
 *
 */
void I2C_SetTargetAddr(I2C_Id_t i2cNo, uint32_t targetAddr);

/**
 * @brief      Set the value of the I2C high speed mode master code
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  value: High speed mode master code.
 *
 * @return none
 *
 */
void I2C_SetMasterModeCodeAddr(I2C_Id_t i2cNo, uint32_t value);

/**
 * @brief      Issues the STOP_DETECT interrupt if addressed in slave mode
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  stopDetAddressedType: Specified types.
 *             - I2C_SLV_STOP_DET_WHE_ADDRESSED:I2C issues the STOP_DETECT
 *               irrespective of whether it is addressed or not.
 *             - I2C_SLV_STOP_DEF_ADDRESSED:I2C issues the STOP_DETECT interrupt
 *               only when it is addressed.
 *
 * @return none
 *
 */
void I2C_StopDetIfAddressed(I2C_Id_t i2cNo,
                            I2C_StopDetAddressed_t stopDetAddressedType);

/**
 * @brief      Issues the STOP_DETECT interrupt if master active
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  stopDetMstActiveType: Specified types.
 *             - I2C_MST_STOP_DET_WHE_ACTIVE:I2C issues the STOP_DETECT
 *               irrespective of whether the master is active.
 *             - I2C_MST_STOP_DEF_ACTIVE:I2C issues the STOP_DETECT interrupt
 *               only when the master is active.
 *
 * @return none
 *
 */
void I2C_StopDetIfMstActive(I2C_Id_t i2cNo,
                            I2C_StopDetActive_t stopDetMstActiveType);

/**
 * @brief      Control the generation of the TXFIFO_EMPTY interrupt,
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  txEmptyType: Specified tx empty type.
 *            - I2C_TX_BUFFER:transmit buffer is at or below the threshold 
 *              value set in the TXFIFO_WATER_MARK register.
 *            - I2C_TX_DATA_PATH:transmit buffer is at or below the threshold 
 *              value set in the TXFIFO_WATER_MARK register and the transmission 
 *              of the address/data from the internal shift register for the 
 *              most recently popped command is completed.
 *
 * @return none
 *
 */
void I2C_TxEmptyCtrl(I2C_Id_t i2cNo, I2C_TxEmptyCtrl_t txEmptyType);

/**
 * @brief      Control whether I2C module should hold the bus when the Rx FIFO
 *             is physically full to its RXFIFO_DEPTH
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  newState: Enable/Disable function state.
 *             - ENABLE: Hold the bus when the Rx FIFO is physically full to its
 *               RXFIFO_DEPTH.
 *             - DISABLE: When Rx FIFO's RXFIFO_DEPTH is physically full,
 *               the bus is not hold.
 *
 * @return none
 *
 */
void I2C_HoldBusCmd(I2C_Id_t i2cNo, ControlState_t newState);

/**
 * @brief      Initializes the I2C DMA
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  i2cDmaConfig: Pointer to a I2C DMA configuration structure.
 *
 * @return none
 *
 */
void I2C_DmaConfig(I2C_Id_t i2cNo, const I2C_DmaConfig_t* i2cDmaConfig);

/**
 * @brief      Enable/disable I2C DMA function.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  transmitDmaCtrl: Transmit DMA Enable/Disable function state.
 * @param[in]  rcvDmaCtrl: Receive DMA Enable/Disable function state.
 *
 * @return none
 *
 */
void I2C_DmaCmd(I2C_Id_t i2cNo, ControlState_t transmitDmaCtrl,
                ControlState_t rcvDmaCtrl);

/**
 * @brief      Set I2C SDA Transmit hold time
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  i2cSdaTxHoldTime: Pointer to a I2C SDA Tx hold time structure.
 *
 * @return none
 *
 */
void I2C_SetSdaTxHoldTime(I2C_Id_t i2cNo,
                          const I2C_SdaHoldTime_t* i2cSdaTxHoldTime);

/**
 * @brief      Set I2C SDA Receive hold time
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  i2cSdaRxHoldTime: Pointer to a I2C SDA Rx hold time structure.
 *
 * @return none
 *
 */
void I2C_SetSdaRxHoldTime(I2C_Id_t i2cNo,
                          const I2C_SdaHoldTime_t* i2cSdaRxHoldTime);

/**
 * @brief      SCL stuck at low timeout
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  timeOut: SCL stuck at low time of duration.
 *             I2C module generates the SCL_STUCK_AT_LOW interrupt to indicate
 *             SCL stuck at low if it detects the SCL stuck at low for the
 *             I2C_SCL_LOW_TIMEOUT in units of I2C function clock period.
 *
 * @return none
 *
 */
void I2C_SetSclHoldLowTimeout(I2C_Id_t i2cNo, uint32_t timeOut);

/**
 * @brief      SDA stuck at low timeout
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  timeOut: SDA stuck at low time of duration.
 *             I2C module initiates the recovery of SDA line through enabling 
 *             the SDA_RECOVER_EN bit if it detects the SDA stuck at low for the 
 *             I2C_SDA_LOW_TIMEOUT in units of I2C function clock period.
 *
 * @return none
 *
 */
void I2C_SetSdaHoldLowTimeout(I2C_Id_t i2cNo, uint32_t timeOut);

/**
 * @brief      Enable I2C .
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @return none
 *
 */
void I2C_Enable(I2C_Id_t i2cNo);

/**
 * @brief      Disable I2C .
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @return none
 *
 */
void I2C_Disable(I2C_Id_t i2cNo);

/**
 * @brief      I2C bus recover feature in master mode
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  newState: Enable/Disable function state.
 *            - ENABLE: Means bus recover feature is enable.
 *            - DISABLE: Means bus recover feature is disabled.
 *
 * @return none
 *
 */
void I2C_MstBusRecover(I2C_Id_t i2cNo, ControlState_t newState);

/**
 * @brief      I2C SDA recover feature
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  newState: Enable/Disable function state.
 *            - ENABLE: Means SDA recover feature is enable.
 *            - DISABLE: Means SDA recover feature is disabled.
 *
 * @return none
 *
 */
void I2C_SdaRecover(I2C_Id_t i2cNo, ControlState_t newState);

/**
 * @brief       Block or not block the transmission of data on I2C bus
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  newState: Enable/Disable function state
 *          - ENABLE: Blocks the transmission of data on I2C bus even if
 *                    Tx FIFO has data to transmit.
 *          - DISABLE: The transmission of data starts on I2C bus automatically,
 *                     as soon as the first data is available in the Tx FIFO.
 *
 * @return none
 *
 */
void I2C_TxCmdBlock(I2C_Id_t i2cNo, ControlState_t newState);

/**
 * @brief      Enable/Disable transfer abort .
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  newState: Enable/Disable function state
 *             - ENABLE: ABORT operation in progress.
 *             - DISABLE: ABORT not initiated or ABORT done.
 *
 * @return none
 *
 */
void I2C_TxAbortCmd(I2C_Id_t i2cNo, ControlState_t newState);

/**
 * @brief      Configure the FIFO threshold level.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  fifoConfig: Pointer to FIFO type structure.
 *
 * @return none
 *
 */
void I2C_FIFOConfig(I2C_Id_t i2cNo, const I2C_FifoConfig_t* fifoConfig);

/**
 * @brief      Get transmit FIFO level
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @return     The number of valid data entries in the transmit FIFO memory.
 *
 */
uint32_t I2C_GetTxFifoLevel(I2C_Id_t i2cNo);

/**
 * @brief      Get receive FIFO level
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @return     The number of valid data entries in the receive FIFO memory.
 *
 */
uint32_t I2C_GetRxFifoLevel(I2C_Id_t i2cNo);

/**
 * @brief      I2C master selects transfer address function.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  transAddrType:transfer address types
 *             - I2C_DEST_ADDR
 *             - I2C_GEN_CALL_ADDR
 *             - I2C_START_BYTE
 *
 * @return none
 *
 */
void I2C_MstCmdSelect(I2C_Id_t i2cNo, I2C_MstCmdSelect_t transAddrType);

/**
 * @brief      Enable/disable I2C general call ACK function.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  newState: Enable/Disable function state
 *           - ENABLE: I2C responses with a ACK when it receives a general call.
 *           - DISABLE: No ACK the general call and doesn't generate general 
 *                      call interrupt.
 *
 * @return none
 *
 */
void I2C_GeneralCallAckCmd(I2C_Id_t i2cNo, ControlState_t newState);

/**
 * @brief      Generate a NACK for the data part of a transfer when i2c is
 *             acting as a slave receiver
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  genNack: general call ACK/NACK type.
 *          - I2C_GEN_NACK_AFTER_RCV:I2C generates NACK after data byte received.
 *          - I2C_GEN_NACK_OR_ACK_NORMAL:I2C generates NACK/ACK normally.
 *
 * @return none
 *
 */
void I2C_SlvDataNackGen(I2C_Id_t i2cNo, I2C_GenSlvDataNack_t genNack);

/**
 * @brief      Send one byte when i2c as a master.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  restartStopType: Specified restart,Stop type.
 *             - I2C_RESTART_AND_STOP_DISABLE
 *             - I2C_STOP_EN
 *             - I2C_RESTART_EN
 * @param[in]  data: The data to be send.
 *
 * @return none
 *
 */
void I2C_MasterSendByte(I2C_Id_t i2cNo, I2C_RestartStop_t restartStopType,
                        uint8_t data);

/**
 * @brief      Send one byte when i2c as a slave.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @param[in]  data: The data to be send.
 *
 * @return none
 *
 */
void I2C_SlaveSendByte(I2C_Id_t i2cNo, uint8_t data);

/**
 * @brief     Master read/write request.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  restartStopType: Specified restart,Stop type.
 *             - I2C_RESTART_AND_STOP_DISABLE
 *             - I2C_STOP_EN
 *             - I2C_RESTART_EN
 *
 * @return none
 *
 */
void I2C_MasterReadCmd(I2C_Id_t i2cNo, I2C_RestartStop_t restartStopType);

/**
 * @brief     I2C read one byte .
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @return The received data
 *
 */
uint16_t I2C_ReceiveByte(I2C_Id_t i2cNo);

/**
 * @brief      Set sda setup time when i2c is acting as a slave transmitter.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  length: The length of setup time is calculated using
 *                     [(SDA_SETUP_TIMING - 1) * (i2c function clock period)].
 *
 * @return none
 *
 */
void I2C_SetSdaSetupTime(I2C_Id_t i2cNo, uint8_t length);

/**
 * @brief      Enable/Disable specified interrupt type
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  intType:  Specified interrupt type.
 *             - I2C_INT_GEN_CALL
 *             - I2C_INT_TX_OVER
 *             - I2C_INT_ERROR_ABORT
 *             - I2C_INT_ACTIVITY
 *             - I2C_INT_STOP_DET
 *             - I2C_INT_START_DET
 *             - I2C_INT_RD_REQ
 *             - I2C_INT_RX_DONE
 *             - I2C_INT_RX_UNDER
 *             - I2C_INT_RX_OVER
 *             - I2C_INT_RESTART_DET
 *             - I2C_INT_SCL_STUCK_AT_LOW
 *             - I2C_INT_RX_FULL
 *             - I2C_INT_TX_EMPTY
 *             - I2C_INT_ALL
 *
 * @param[in]  newState:  Interrupt enable/disable type.
 *             - ENABLE: enable interrupt
 *             - DISABLE: disable interrupt
 *
 * @return  none
 *
 */
void I2C_IntCmd(I2C_Id_t i2cNo, I2C_Int_t intType, ControlState_t newState);

/**
 * @brief      Check whether interrupt status flag is set or not for given
 *             interrupt type
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  intType:  Specified interrupt type.
 *             - I2C_INT_GEN_CALL
 *             - I2C_INT_TX_OVER
 *             - I2C_INT_ERROR_ABORT
 *             - I2C_INT_ACTIVITY
 *             - I2C_INT_STOP_DET
 *             - I2C_INT_START_DET
 *             - I2C_INT_RD_REQ
 *             - I2C_INT_RX_DONE
 *             - I2C_INT_RX_UNDER
 *             - I2C_INT_RX_OVER
 *             - I2C_INT_RESTART_DET
 *             - I2C_INT_SCL_STUCK_AT_LOW
 *             - I2C_INT_RX_FULL
 *             - I2C_INT_TX_EMPTY
 *
 * @return     The status flag of interrupt status register.
 *             - SET
 *             - RESET
 *
 */
FlagStatus_t I2C_GetIntStatus(I2C_Id_t i2cNo, I2C_Int_t intType);

/**
 * @brief      Check whether error status flag is set or not
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  errorType:  Specified abort type.
 *             - I2C_ERR_GEN_CALL_NO_ACK
 *             - I2C_ERR_GEN_CALL_READ
 *             - I2C_ERR_START_BYTE_ACK_DET
 *             - I2C_ERR_SBYTE_NORSTRT
 *             - I2C_ERR_H_NO_RSTRT
 *             - I2C_ERR_H_MCODE_ACK_DET
 *             - I2C_ERR_7BIT_ADDR_NO_ACK
 *             - I2C_ERR_10BIT_ADDR1_NO_ACK
 *             - I2C_ERR_10BIT_ADDR2_NO_ACK
 *             - I2C_ERR_10BIT_READ_NO_RSTRT
 *             - I2C_ERR_DATA_NO_ACK
 *             - I2C_ERR_MASTER_LOST
 *             - I2C_ERR_MASTER_DIS
 *             - I2C_ERR_SLAVE_ARBLOST
 *             - I2C_ERR_MASTER_ABRT
 *             - I2C_ERR_SLAVE_READ_REQ
 *             - I2C_ERR_SLAVE_FLUSH_TXFIFO
 *             - I2C_ERR_SDA_LOW_TIMEOUT
 *
 * @return     The status flag of error status register.
 *             - SET
 *             - RESET
 *
 */
FlagStatus_t I2C_GetErrorStatus(I2C_Id_t i2cNo, I2C_ErrorStatus_t errorType);

/**
 * @brief      Clear specified interrupt type
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  intType:  Specified interrupt type.
 *             - I2C_INT_GEN_CALL
 *             - I2C_INT_TX_OVER
 *             - I2C_INT_ERROR_ABORT
 *             - I2C_INT_ACTIVITY
 *             - I2C_INT_STOP_DET
 *             - I2C_INT_START_DET
 *             - I2C_INT_RD_REQ
 *             - I2C_INT_RX_DONE
 *             - I2C_INT_RX_UNDER
 *             - I2C_INT_RX_OVER
 *             - I2C_INT_RESTART_DET
 *             - I2C_INT_SCL_STUCK_AT_LOW
 *             - I2C_INT_ALL
 *
 * @return none
 *
 */
void I2C_ClearInt(I2C_Id_t i2cNo, I2C_Int_t intType);

/**
 * @brief     Clear all error status .
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @return none
 *
 */
void I2C_ClearErrorStatusAll(I2C_Id_t i2cNo);

/**
 * @brief     The number of Tx FIFO data Master-Transmitter commands that
 *            are flushed due to ERROR_ABORT or SlaveTransmitter interrupt.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @return     The error flush count.
 *
 */
uint32_t I2C_ErrorFlushCount(I2C_Id_t i2cNo);

/**
 * @brief      Check whether status flag is set or not for given status type
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  statusType:  Specified status type.
 *             - I2C_MST_ACTIVITY
 *             - I2C_SLV_ACTIVITY
 *             - I2C_TXFIFO_EMPTY_MASTER_HOLD
 *             - I2C_TXFIFO_EMPTY_SLAVE_HOLD
 *             - I2C_RXFIFO_FULL_MASTER_HOLD
 *             - I2C_RXFIFO_FULL_SLAVE_HOLD
 *             - I2C_STATUS_TFNF
 *             - I2C_STATUS_TFE,
 *             - I2C_STATUS_RFNE,
 *             - I2C_STATUS_RFF,
 *             - I2C_SDA_ERR_RECOVER_STUCK_LOW,
 *             - I2C_SLAVE_IS_DISABLED_UNDER_ACT
 *             - I2C_SLAVE_RX_DATA_DISCARD
 *             - I2C_ENABLE
 *
 * @return     The status flag of I2C status register.
 *             - SET
 *             - RESET
 *
 */
FlagStatus_t I2C_GetStatus(I2C_Id_t i2cNo, I2C_Status_t statusType);

/**
 * @brief      Configure speed mode and SCL timing. This function is to configure speed mode and
 *             custom data transfer rate and duty cycle with any clock source supported.
 *             This function need to be called after I2C_Init().
 * 
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  sclTimingConfig: Pointer to a SCL timing configuration structure.
 * 
 * @return     SUCC: The SCL timing configuration is successfully configured.
 *             ERR:  The SCL timing configuration is configured while I2C is enabled or speed mode
 *                   is invalid.
 */
ResultStatus_t I2C_ConfigSclTiming(I2C_Id_t i2cNo, I2C_SclTiming_t * sclTimingConfig);

/** @} end of group I2C_Public_FunctionDeclaration */

/** @} end of group I2C  */

/** @} end of group Z20K14XM_Peripheral_Driver */

#endif /* End of I2C_DRV_H*/
