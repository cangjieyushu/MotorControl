/**************************************************************************************************/
/**
 * @file      : Spi_Drv.h
 * @brief     : SPI module driver header file.
 *              - Platform: Z20M1343L
 * @version   : V0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef SPI_DRV_H
#define SPI_DRV_H

#include "Common_Drv.h"

/** @addtogroup Public_MacroDefinition
 *  @{
 */

/** @} end of Public_MacroDefinition */
/** @defgroup Public_TypeDefinition
 *  @{
 */

/**
 *  @brief Serial spi mode define
 */

typedef enum
{
    SPI_MODE_SLAVE = 0U, /*!< Slave mode */
    SPI_MODE_MASTER      /*!< Master mode */
} Spi_ModeType;

/**
 *  @brief Serial clock phase type define
 */
typedef enum
{
    SPI_CLK_PHASE_FIRST = 0U, /*!< Serial clock toggles at the first edge */
    SPI_CLK_PHASE_SECOND      /*!< Serial clock toggles at the second edge */
} Spi_ClkPhaseType;

/**
 *  @brief Serial clock polarity type define
 */
typedef enum
{
    SPI_CLK_INACTIVE_LOW = 0U, /*!< Inactive state of serial clock is low */
    SPI_CLK_INACTIVE_HIGH      /*!< Inactive state of serial clock is high */
} Spi_ClkPolarType;

/**
 *  @brief Transfer mode type define
 */
typedef enum
{
    SPI_TMOD_TR = 0U, /*!< Transmit & receive */
    SPI_TMOD_TO,      /*!< Transmit only */
    SPI_TMOD_RO       /*!< Receive only */
} Spi_TransModeType;

/**
 *  @brief SPI status bit type definition
 */
typedef enum
{
    SPI_STATUS_BUSY = 0U, /*!< SPI busy flag */
    SPI_STATUS_TFNF,      /*!< Transmit FIFO not full */
    SPI_STATUS_TFE,       /*!< Transmit FIFO empty */
    SPI_STATUS_RFNE,      /*!< Receive FIFO not empty */
    SPI_STATUS_RFF,       /*!< Receive FIFO full */
    SPI_STATUS_TXE,       /*!< Transmission Error */
    SPI_STATUS_ALL        /*!< All the Status */
} Spi_StatusType;

/**
 *  @brief SPI interrupt definition
 */
typedef enum
{
    SPI_INT_TXE = 0U, /*!< Transmit FIFO empty interrupt */
    SPI_INT_TXO,      /*!< Transmit FIFO overflow interrupt*/
    SPI_INT_RXU,      /*!< Receive FIFO underflow interrupt */
    SPI_INT_RXO,      /*!< Received FIFO overflow interrupt */
    SPI_INT_RXF,      /*!< Received FIFO full interrupt */
    SPI_INT_ARXD,     /*!< Async rx done interrupt */
    SPI_INT_ALL       /*!< All the interrupts */
} Spi_IntType;

/**
 *  @brief SPI raw interrupt definition
 */
typedef enum
{
    SPI_RAW_INT_TXE = 0U, /*!< Transmit FIFO empty interrupt */
    SPI_RAW_INT_TXO,      /*!< Transmit FIFO overflow interrupt*/
    SPI_RAW_INT_RXU,      /*!< Receive FIFO underflow interrupt */
    SPI_RAW_INT_RXO,      /*!< Received FIFO overflow interrupt */
    SPI_RAW_INT_RXF,      /*!< Received FIFO full interrupt */
    SPI_RAW_INT_ARXD,     /*!< Async rx done interrupt */
    SPI_RAW_INT_ALL       /*!< All the interrupts */
} Spi_RawIntType;

/**
 *  @brief SPI slave select type definition
 */
typedef enum
{
    SPI_SS_DISABLE = 0U, /*!< Select neither */
    SPI_SS_PCS0,         /*!< Select PCS0 */
    SPI_SS_PCS1,         /*!< Select PCS1 */
    SPI_SS_ALL           /*!< Select both */
} Spi_SelectSlaveType;

/**
 *  @brief SPI transmit/receive direction type definition
 */
typedef enum
{
    SPI_MSB = 0U, /*!< MSB first transmit  */
    SPI_LSB       /*!< LSB first transmit  */
} Spi_TransmitDirType;

/**
 *  @brief SPI Configuration Structure type definition
 */
typedef struct
{
    Spi_ModeType Mode;            /*!< SPI mode
                                     - SPI_MODE_SLAVE:slave mode
                                     - SPI_MODE_MASTER:master mode */
    uint32 DataSize;              /*!< Configures data frame size
                                     - Size of 4 to 32 bits */
    Spi_ClkPhaseType ClkPhase;    /*!< Serial clock phase
                                     - SPI_CLK_PHASE_FIRST:  first edge
                                     - SPI_CLK_PHASE_SECOND: second edge */
    Spi_ClkPolarType ClkPolarity; /*!< Serial clock polarity
                                     - SPI_CLK_INACTIVE_LOW:  low inactive
                                     - SPI_CLK_INACTIVE_HIGH: high inactive */
    Spi_TransModeType TransMode;  /*!< Transfer mode
                                     - SPI_TMOD_TR: transmit & receive
                                     - SPI_TMOD_TO: transmit only
                                     - SPI_TMOD_RO: receive  only */
    uint32 ClkDivider;   /*!< Clock Divider.The frequency of the sclk_out is derived
                            from the following equation: Fsclk_out = Fspi_clk/SCKDV */
    uint32 TransFifoThr; /*!< Transmit FIFO threshold level, the valid range is 0 - 3 */
    uint32 RecvFifoThr;  /*!< Receive  FIFO threshold level, the valid range is 0 - 3 */
    Spi_TransmitDirType Dir;      /*!< transfer direction */
} Spi_ConfigType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */
/**
 * @brief      Initialize the SPI. This API can only be called when the SPI device is disabled.
 * @param[in]  ConfigPtr:  Pointer to a SPI configuration structure.
 * @return     None.
 */
void Spi_Init(const Spi_ConfigType *ConfigPtr);

/**
 * @brief      Enable the SPI.
 * @param      None.
 * @return     None.
 */
void Spi_Enable(void);

/**
 * @brief      Disable the SPI.
 * @param      None.
 * @return     None.
 */
void Spi_Disable(void);

/**
 * @brief      Set master data frame number. Only used in receive mode.
 * @param[in]  FrameNum: data frame number, should <= 0xFFFF.
 * @return     None.
 */
void Spi_SetDataFrameNum(uint32 FrameNum);

/**
 * @brief      Select SPI slave.
 * @param[in]  ChipSelect:  Select the slave.
 * @return     None.
 */
void Spi_SelectSlave(Spi_SelectSlaveType ChipSelect);

/**
 * @brief      Enable or disable delay from the PCS assertion to the first SCK edge in master.
 * @param[in]  DelayCtrl:
 *             - COMMON_DISABLE: pcs2sck function disable
 *             - COMMON_ENABLE : pcs2sck function enable
 * @return     None.
 */
void Spi_EnableSignalDelay(Common_ControlStateType DelayCtrl);

/**
 * @brief      Configure delay from the PCS assertion to the first SCK edge in master.
 * @param[in]  DelayTime: The delay is equal to (PCSSCK) cycles of the SPI
 *                       functional clock and The minimum delay is 2 cycle.
 * @return     None.
 */
void Spi_ConfigSignalDelay(uint32 DelayTime);

/**
 * @brief      Enable or Disable Continue Transmit Mode.
 * @param[in]  ContinueCtrl:
 *             - COMMON_DISABLE: ss_n will be deassert between frame and next_frame
 *             - COMMON_ENABLE : ss_n will keep assert between frame and next_frame
 * @return     None.
 */
void Spi_EnableContinueMode(Common_ControlStateType ContinueCtrl);

/**
 * @brief      Send data.
 * @param[in]  Data:  The data to be send.
 * @return     None.
 */
void Spi_SendData(uint32 Data);

/**
 * @brief      Receive data.
 * @param      None.
 * @return     The received data.
 */
uint32 Spi_ReceiveData(void);

/**
 * @brief      Enable or Disable Txd accelerate method in slave mode.
 * @param[in]  SpeedSelect:
 *             - COMMON_DISABLE: slave txd is in legacy method
 *             - COMMON_ENABLE : slave txd is in accelerate method
 * @return     None.
 */
void Spi_SetTxdAccelerateMethod(Common_ControlStateType SpeedSelect);

/**
 * @brief      Configure receive data (rxd) sample delay in master mode.
 * @param[in]  DelayTime: Value represents a single spi_clk delay on the sample of the rxd signal.
 *                        Maximum value is 31 cycles.
 * @return     None.
 */
void Spi_ConfigRxdSampleDelay(uint32 DelayTime);

/**
 * @brief      Configure SPI transmit/receive direction. 
 *             This API can only be called when the SPI device is disabled.
 * @param[in]  Dir:  Specified transmit/receive direction.
 *             - SPI_MSB:  Most significant bit first
 *             - SPI_LSB:  Least significant bit first
 * @return     None.
 */
void Spi_ConfigTransmitDir(Spi_TransmitDirType Dir);

/**
 * @brief      Get transmit FIFO level.
 * @param      None.
 * @return     uint32: The number of valid data entries in the transmit FIFO memory.
 */
uint32 Spi_GetTxFifoLevel(void);

/**
 * @brief      Get receive FIFO level.
 * @param      None.
 * @return     The number of valid data entries in the receive FIFO memory.
 */
uint32 Spi_GetRxFifoLevel(void);

/**
 * @brief      Reset transmit FIFO. Clear the full/empty, address, counter and data of TX FIFO.
 *             This API can only be called when the SPI device is disabled.
 * @param      None.
 * @return     None.
 */
void Spi_ResetTxFifo(void);

/**
 * @brief      Reset receive FIFO. Clear the full/empty, address, counter and data of RX FIFO.
 *             This API can only be called when the SPI device is disabled.
 * @param      None.
 * @return     None.
 */
void Spi_ResetRxFifo(void);

/**
 * @brief      Check whether status flag is set or not for given status type.
 * @param[in]  SpiStatus:  Specified status type.
 *             - SPI_STATUS_BUSY
 *             - SPI_STATUS_TFNF
 *             - SPI_STATUS_TFE
 *             - SPI_STATUS_RFNE
 *             - SPI_STATUS_RFF
 *             - SPI_STATUS_TXE
 * @return     Common_FlagStatusType: The state value of SPI Status register.
 *             - COMMON_SET
 *             - COMMON_RESET
 */
Common_FlagStatusType Spi_GetStatus(Spi_StatusType SpiStatus);

/**
 * @brief      Check whether interrupt status flag is set or not for given interrupt type.
 * @param[in]  IntType:  Specified interrupt type.
 *             - SPI_INT_TXE
 *             - SPI_INT_TXO
 *             - SPI_INT_RXU
 *             - SPI_INT_RXO
 *             - SPI_INT_RXF
 *             - SPI_INT_ARXD
 * @return     Common_FlagStatusType: The state flag of interrupt Status register.
 *             - COMMON_SET
 *             - COMMON_RESET
 */
Common_FlagStatusType Spi_GetIntStatus(Spi_IntType IntType);

/**
 * @brief      Check whether  raw interrupt status flag is set or not for given interrupt type.
 * @param[in]  IntType:  Specified interrupt type.
 *             - SPI_RAW_INT_TXE
 *             - SPI_RAW_INT_TXO
 *             - SPI_RAW_INT_RXU
 *             - SPI_RAW_INT_RXO
 *             - SPI_RAW_INT_RXF
 *             - SPI_RAW_INT_ARXD
 * @return     Common_FlagStatusType: The state flag of interrupt Status register.
 *             - COMMON_SET
 *             - COMMON_RESET
 */
Common_FlagStatusType Spi_GetRawIntStatus(Spi_RawIntType IntType);

/**
 * @brief      Mask/Unmask specified  interrupt type.
 * @param[in]  IntType:  Specified interrupt type.
 *             - SPI_INT_TXE
 *             - SPI_INT_TXO
 *             - SPI_INT_RXU
 *             - SPI_INT_RXO
 *             - SPI_INT_RXF
 *             - SPI_INT_ARXD
 *             - SPI_INT_ALL
 * @param[in]  IntMask:  Interrupt mask/unmask type.
 *             - COMMON_MASK: 0
 *             - COMMON_UNMASK: 1
 * 
 * @note       Async rx done interrupt can not be masked in hardware, but callback function call
 *             can be masked.
 * 
 * @return     None.
 */
void Spi_SetIntMask(Spi_IntType IntType, Common_IntMaskType IntMask);

/**
 * @brief      Clear all interrupt status flags.
 * @param[in]  IntType:  Specified interrupt type.
 *             - SPI_INT_TXO
 *             - SPI_INT_RXU
 *             - SPI_INT_RXO
 *             - SPI_INT_ARXD
 *             - SPI_INT_ALL
 * @return     None.
 */
void Spi_ClearInt(Spi_IntType IntType);

/**
 * @brief      install call back function.
 * @param[in]  IntId:  Select the interrupt. SPI_INT_ALL is invalid.
 * @param[in]  CbFun:  Pointer to callback function.
 * @return     None.
 */
void Spi_InstallCallbackFunc(Spi_IntType IntId, Isr_CbFuncType *CbFun);

/** @} end of group Public_FunctionDeclaration */

#endif /* SPI_DRV_H */
