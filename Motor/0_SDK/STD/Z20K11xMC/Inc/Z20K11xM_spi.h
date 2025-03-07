/**************************************************************************************************/
/**
 * @file      : Z20K11xM_spi.h
 * @brief     : SPI module driver header file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef Z20K11XM_SPI_H
#define Z20K11XM_SPI_H

#include "Z20K11xM_drv.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SPI
 *  @{
 */

/** @defgroup SPI_Public_Types
 *  @{
 */
/**
 *  @brief Serial spi mode define
 */
typedef enum
{
    SPI_MODE_SLAVE = 0U, /*!< Slave mode */
    SPI_MODE_MASTER      /*!< Master mode */
} SPI_Mode_t;

/**
 *  @brief Serial clock phase type define
 */
typedef enum
{
    SPI_CLK_PHASE_FIRST = 0U, /*!< Serial clock toggles at the first edge */
    SPI_CLK_PHASE_SECOND      /*!< Serial clock toggles at the second edge */
} SPI_ClkPhase_t;

/**
 *  @brief Serial clock polarity type define
 */
typedef enum
{
    SPI_CLK_INACTIVE_LOW = 0U, /*!< Inactive state of serial clock is low */
    SPI_CLK_INACTIVE_HIGH      /*!< Inactive state of serial clock is high */
} SPI_ClkPolar_t;

/**
 *  @brief Transfer mode type define
 */
typedef enum
{
    SPI_TMOD_TR = 0U, /*!< Transmit & receive */
    SPI_TMOD_TO,      /*!< Transmit only */
    SPI_TMOD_RO       /*!< Receive only */
} SPI_TransMode_t;

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
} SPI_Status_t;

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
    SPI_INT_ALL       /*!< All the interrupt */
} SPI_Int_t;

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
    SPI_RAW_INT_ALL       /*!< All the interrupt */
} SPI_RawInt_t;

/**
 *  @brief SPI slave select type definition
 */
typedef enum
{
    SPI_SS_DISABLE = 0U, /*!< Disable slave select */
    SPI_SS_PCS0,         /*!< Select PCS0 */
    SPI_SS_PCS1,         /*!< Select PCS1 */
    SPI_SS_ALL           /*!< Select all */
} SPI_SelectSlave_t;

/**
 *  @brief SPI all ID type definition
 */
typedef enum
{
    SPI0_ID = 0U, /*!< SPI0 ID define */
    SPI1_ID,      /*!< SPI1 ID define */
#if (SPI_INSTANCE_NUM == 3)
    SPI2_ID /*!< SPI2 ID define */
#endif
} SPI_ID_t;

/**
 *  @brief SPI Master Configuration Structure type definition
 */
typedef struct
{
    SPI_Mode_t mode;            /*!< SPI mode
                                     - SPI_MODE_SLAVE:slave mode
                                     - SPI_MODE_MASTER:master mode */
    uint32_t dataSize;          /*!< Configures data frame size
                                     - Size of 4 to 32 bits */
    SPI_ClkPhase_t clkPhase;    /*!< Serial clock phase
                                     - SPI_CLK_PHASE_FIRST:  first edge
                                     - SPI_CLK_PHASE_SECOND: second edge */
    SPI_ClkPolar_t clkPolarity; /*!< Serial clock polarity
                                     - SPI_CLK_INACTIVE_LOW:  low inactive
                                     - SPI_CLK_INACTIVE_HIGH: high inactive */
    SPI_TransMode_t transMode;  /*!< Transfer mode
                                     - SPI_TMOD_TR: transmit & receive
                                     - SPI_TMOD_TO: transmit only
                                     - SPI_TMOD_RO: receive  only */
    uint16_t clkDivider;   /*!< Clock Divider.The frequency of the sclk_out is
                              derived   from the following equation: Fsclk_out =
                              Fssi_clk/SCKDV */
    uint32_t transFifoThr; /*!< Transmit FIFO threshold level, the valid range
                              is 0 - 3 */
    uint32_t recvFifoThr; /*!< Receive  FIFO threshold level, the valid range is
                             0 - 3 */
} SPI_Config_t;

/**
 *  @brief SPI DMA request FIFO level Configuration Structure type definition
 */
typedef struct
{
    uint32_t
        dmaTransReqLevel; /*!< Transmit data level,the valid range is 0 - 3 */
    uint32_t
        dmaRecvReqLevel; /*!< Receive  data level,the valid range is 0 - 3 */
} SPI_DmaLvl_t;
/** @} end of group SPI_Public_Types  */

/** @defgroup SPI_Public_FunctionDeclaration
 *  @brief SPI functions declaration
 *  @{
 */

/**
 * @brief      Enable the SPI.
 *
 * @param[in]  spiNo:  Select the SPI port,should be SPI0_ID,SPI1_ID, SPI2_ID.
 *
 * @return none.
 *
 */
void SPI_Enable(SPI_ID_t spiNo);

/**
 * @brief      Disable the SPI.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI0_ID,SPI1_ID, SPI2_ID.
 *
 * @return none.
 *
 */
void SPI_Disable(SPI_ID_t spiNo);

/**
 * @brief      Enable or disable the SPI DMA function.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI1_ID,SPI1_ID, SPI2_ID.
 * @param[in]  transmitDmaCtrl: Transmit DMA Enable/Disable function state
 * @param[in]  rcvDmaCtrl: Receive DMA Enable/Disable function state
 *
 * @return none.
 *
 */
void SPI_DmaCmd(SPI_ID_t spiNo, ControlState_t transmitDmaCtrl,
                ControlState_t rcvDmaCtrl);

/**
 * @brief      Clear all interrupt status flags.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI0_ID,SPI1_ID, SPI2_ID.
 * @param[in]  intType:  Specified interrupt type.
 *             - SPI_INT_TXO
 *             - SPI_INT_RXU
 *             - SPI_INT_RXO
 *             - SPI_INT_ALL
 *
 * @return none.
 *
 */
uint32_t SPI_ClearInt(SPI_ID_t spiNo, SPI_Int_t intType);

/**
 * @brief      Initializes the SPI .
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI0_ID, SPI1_ID, SPI2_ID.
 * @param[in]  spiCfgStruct:  Pointer to a SPI configuration structure.
 *
 * @return none.
 *
 */
void SPI_Init(SPI_ID_t spiNo, const SPI_Config_t *spiCfgStruct);
/**
 * @brief      Initializes the SPI  DMA.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI0_ID, SPI1_ID, SPI2_ID.
 * @param[in]  dmaCfgStruct:  Pointer to a SPI Master DMA configuration
 * structure.
 *
 * @return none.
 *
 */
void SPI_DmaConfig(SPI_ID_t spiNo, SPI_DmaLvl_t *dmaCfgStruct);

/**
 * @brief      Select SPI slave.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI0_ID, SPI1_ID, SPI2_ID
 *
 * @return none.
 *
 */
void SPI_SelectSlave(SPI_ID_t spiNo, SPI_SelectSlave_t chipSelect);

/**
 * @brief      Set Master data frame number.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI0_ID, SPI1_ID, SPI2_ID.
 * @param[in]  frameNum: data frame number, should <= 0xFFFF.
 *
 * @return none.
 *
 * This function only used in Receive only transfer mode.
 */
void SPI_SetDataFrameNum(SPI_ID_t spiNo, uint32_t frameNum);

/**
 * @brief      Send  data.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI0_ID, SPI1_ID, SPI2_ID.
 * @param[in]  data:  The data to be send.
 *
 * @return     none.
 *
 */
void SPI_SendData(SPI_ID_t spiNo, uint32_t data);

/**
 * @brief      Check whether  raw interrupt status flag is set or not for
 *             given interrupt type.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI0_ID, SPI1_ID, SPI2_ID.
 * @param[in]  intType:  Specified interrupt type.
 *             - SPI_RAW_INT_TXE
 *             - SPI_RAW_INT_TXO
 *             - SPI_RAW_INT_RXU
 *             - SPI_RAW_INT_RXO
 *             - SPI_RAW_INT_RXF
 * @return     The state flag of interrupt Status register.
 *             - SET
 *             - RESET
 *
 */
FlagStatus_t SPI_GetRawIntStatus(SPI_ID_t spiNo, SPI_RawInt_t intType);

/**
 * @brief      Receive data.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI0_ID, SPI1_ID, SPI2_ID.
 *
 * @return The received data.
 *
 */
uint32_t SPI_ReceiveData(SPI_ID_t spiNo);

/**
 * @brief      Master get transmit FIFO level.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI0_ID, SPI1_ID, SPI2_ID.
 *
 * @return     The number of valid data entries in the transmit FIFO memory.
 *
 */
uint32_t SPI_GetTxFifoLevel(SPI_ID_t spiNo);

/**
 * @brief      Get receive FIFO level.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI0_ID, SPI1_ID, SPI2_ID.
 *
 * @return The number of valid data entries in the receive FIFO memory.
 *
 */
uint32_t SPI_GetRxFifoLevel(SPI_ID_t spiNo);

/**
 * @brief      Check whether status flag is set or not for given status type.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI0_ID, SPI1_ID, SPI2_ID.
 * @param[in]  spiStatus:  Specified status type.
 *             - SPI_STATUS_BUSY
 *             - SPI_STATUS_TFNF
 *             - SPI_STATUS_TFE
 *             - SPI_STATUS_RFNE
 *             - SPI_STATUS_RFF
 *             - SPI_STATUS_TXE
 *
 * @return     The state value of SPI Status register.
 *             - SET
 *             - RESET
 *
 */
FlagStatus_t SPI_GetStatus(SPI_ID_t spiNo, SPI_Status_t spiStatus);

/**
 * @brief      Check whether interrupt status flag is set or not for given
 *             interrupt type.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI0_ID, SPI1_ID, SPI2_ID.
 * @param[in]  intType:  Specified interrupt type.
 *             - SPI_INT_TXE
 *             - SPI_INT_TXO
 *             - SPI_INT_RXU
 *             - SPI_INT_RXO
 *             - SPI_INT_RXF
 * @return     The state flag of interrupt Status register.
 *             - SET
 *             - RESET
 *
 */
FlagStatus_t SPI_GetIntStatus(SPI_ID_t spiNo, SPI_Int_t intType);

/**
 * @brief      Mask/Unmask specified  interrupt type.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI0_ID, SPI1_ID, SPI2_ID.
 * @param[in]  intType:  Specified interrupt type.
 *             - SPI_INT_TXE
 *             - SPI_INT_TXO
 *             - SPI_INT_RXU
 *             - SPI_INT_RXO
 *             - SPI_INT_RXF
 *             - SPI_INT_ALL
 * @param[in]  intMask:  Interrupt mask/unmask type.
 *             - SPI_INT_MASK: 0
 *             - SPI_INT_UNMASK: 1
 *
 * @return none.
 *
 */
void SPI_IntMask(SPI_ID_t spiNo, SPI_Int_t intType, IntMask_t intMask);

/**
 * @brief      install call back function.
 *
 * @param[in]  intId: select the interrupt.
 * @param[in]  cbFun: pointer to callback function.
 *
 * @return none.
 *
 */
void SPI_InstallCallBackFunc(SPI_ID_t spiId, SPI_Int_t intId, isr_cb_t *cbFun);

/** @} end of group SPI_Public_FunctionDeclaration */

/** @} end of group SPI  */

/** @} end of group Z20K11X_Peripheral_Driver */

#endif /* Z20K11XM_SPI_H */
