/**************************************************************************************************/
/**
 * @file      : Spi_Drv.c
 * @brief     : SPI module driver header file.
 *              - Platform: Z20M1343L
 * @version   : V0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Spi_Drv.h"

/** @defgroup Private_MacroDefinition
 *  @{
 */

/** @} end of Private_MacroDefinition */

/** @defgroup Private_TypeDefinition
 *  @{
 */

/** @} end of group Private_TypeDefinition */

/** @defgroup Global_VariableDefinition
 *  @{
 */

/** @} end of group Global_VariableDefinition */

/** @defgroup Private_VariableDefinition
 *  @{
 */
/**
 *  @brief SPI ISR callback function pointer array
 */
static Isr_CbFuncType *Spi_IsrCbFuncPtr[SPI_INT_ALL] = 
                            {NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR};

/**
 *  @brief SPI register address
 */
/*PRQA S 0303 ++*/
static Reg_Spi_BfType *const Spi_RegBfPtr = (Reg_Spi_BfType *)SPI_BASE_ADDR;
static Reg_Spi_WType *const Spi_RegWPtr = (Reg_Spi_WType *)SPI_BASE_ADDR;
/*PRQA S 0303 --*/

/**
 *  @brief SPI interrupt mask array
 */
static const uint32 Spi_IntMaskTable[] =
{
        0x00000001U, /*!< Transmit FIFO empty interrupt */
        0x00000002U, /*!< Transmit FIFO overflow interrupt*/
        0x00000004U, /*!< Receive FIFO underflow interrupt */
        0x00000008U, /*!< Receive FIFO overflow interrupt */
        0x00000010U, /*!< Receive FIFO full interrupt */
        0x00000040U, /*!< Async rx done interrupt */
        0x0000005FU  /*!< All the interrupts */
};
/**
 *  @brief SPI interrupt clear array
 */
static const uint32 Spi_IntClearTable[] =
{
        0x00000000U, /*!< Do nothing */
        0x00000004U, /*!< Clear transmit FIFO overflow interrupt*/
        0x00000001U, /*!< Clear receive FIFO underflow interrupt */
        0x00000002U, /*!< Clear receive FIFO overflow interrupt */
        0x00000000U, /*!< Do nothing */
        0x00000010U, /*!< Clear async rx done interrupt */
        0x00000017U  /*!< Clear all the interrupts */
};

/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */
void Spi_DriverIrqHandler(void);

/** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 *  @{
 */

/**
 * @brief  SPI interrupt handler.
 * @param  None.
 * @return None.
 */
void Spi_DriverIrqHandler(void)
{
    uint32 IntStatus;
    uint32 IntType;

    /* Read the interrupt status */
    IntStatus = Spi_RegWPtr->SPI_ISR;
    /* Only check enabled interrupts */
    IntStatus &= Spi_RegWPtr->SPI_IMR;

    /* Try to clear async rx done interrupt as workaround, since this interrupt is indicated by
       ARXDIR and not effected by ARXDIE in hardware */
    Spi_RegWPtr->SPI_ICR = Spi_IntClearTable[SPI_INT_ARXD];

    for (IntType = (uint32)SPI_INT_TXE; IntType < (uint32)SPI_INT_ALL; IntType++)
    {
        if ((IntStatus & Spi_IntMaskTable[IntType]) != 0U)
        {
            /* Clear the interrupt status */
            Spi_RegWPtr->SPI_ICR = Spi_IntClearTable[IntType];
            if (NULL_PTR != Spi_IsrCbFuncPtr[IntType])
            {
                Spi_IsrCbFuncPtr[IntType]();
            }
            /* Mask this interrupt */
            else
            {
                Spi_RegWPtr->SPI_IMR &= (~Spi_IntMaskTable[IntType]);
            }
        }
    }
}

/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
 *  @{
 */

/**
 * @brief      Initialize the SPI. This API can only be called when the SPI device is disabled.
 * @param[in]  ConfigPtr:  Pointer to a SPI configuration structure.
 * @return     None.
 */
void Spi_Init(const Spi_ConfigType *ConfigPtr)
{
    if (NULL_PTR != ConfigPtr)
    {
        /* Set SPI master or slave mode */
        Spi_RegBfPtr->SPI_CTRLR0.MST_MODE = (uint32)ConfigPtr->Mode;
        /* Set SPI clock divider */
        Spi_RegBfPtr->SPI_BAUDR.SCKDV = ConfigPtr->ClkDivider;
        /* Set data frame size */
        Spi_RegBfPtr->SPI_CTRLR0.DFS_32 = ConfigPtr->DataSize - 1U;
        /* Set serial clock phase */
        Spi_RegBfPtr->SPI_CTRLR0.SCPH = (uint32)ConfigPtr->ClkPhase;
        /* Set clock polarity */
        Spi_RegBfPtr->SPI_CTRLR0.SCPOL = (uint32)ConfigPtr->ClkPolarity;
        /* Set transfer mode */
        Spi_RegBfPtr->SPI_CTRLR0.TMOD = (uint32)ConfigPtr->TransMode;
        /* Set transmit FIFO threshold level */
        Spi_RegBfPtr->SPI_FTLR.TFT = (uint32)ConfigPtr->TransFifoThr;
        /* Set receive FIFO threshold level */
        Spi_RegBfPtr->SPI_FTLR.RFT = (uint32)ConfigPtr->RecvFifoThr;
        /* Set SPI transfer direction */
        Spi_RegBfPtr->SPI_CTRLR0.LSB = (uint32)ConfigPtr->Dir;
    }
}

/**
 * @brief      Enable the SPI.
 * @param      None.
 * @return     None.
 */
void Spi_Enable(void)
{
    Spi_RegBfPtr->SPI_SPIENR.SPI_EN = 1U;
}

/**
 * @brief      Disable the SPI.
 * @param      None.
 * @return     None.
 */
void Spi_Disable(void)
{
    Spi_RegBfPtr->SPI_SPIENR.SPI_EN = 0U;
}

/**
 * @brief      Set master data frame number. Only used in receive mode.
 * @param[in]  FrameNum: data frame number, should <= 0xFFFF.
 * @return     None.
 */
void Spi_SetDataFrameNum(uint32 FrameNum)
{
    if (FrameNum > 0U)
    {
        /* The actual number of frames transferred is NDF+1 */
        Spi_RegBfPtr->SPI_CTRLR1.NDF = FrameNum - 1U;
    }
    else
    {
        Spi_RegBfPtr->SPI_CTRLR1.NDF = 0U;
    }
}

/**
 * @brief      Select SPI slave.
 * @param[in]  ChipSelect:  Select the slave.
 * @return     None.
 */
void Spi_SelectSlave(Spi_SelectSlaveType ChipSelect)
{
    Spi_RegBfPtr->SPI_SPIENR.SER = (uint32)(ChipSelect);
}

/**
 * @brief      Enable or disable delay from the PCS assertion to the first SCK edge in master.
 * @param[in]  DelayCtrl:
 *             - COMMON_DISABLE: pcs2sck function disable
 *             - COMMON_ENABLE : pcs2sck function enable
 * @return     None.
 */
void Spi_EnableSignalDelay(Common_ControlStateType DelayCtrl)
{
    Spi_RegBfPtr->SPI_CTRL2.PCS2SCK_EN = (uint32)DelayCtrl;
}

/**
 * @brief      Configure delay from the PCS assertion to the first SCK edge in master.
 * @param[in]  DelayTime: The delay is equal to (PCSSCK) cycles of the SPI
 *                       functional clock and The minimum delay is 2 cycle.
 * @return     None.
 */
void Spi_ConfigSignalDelay(uint32 DelayTime)
{
    Spi_RegBfPtr->SPI_CTRL2.PCS2SCK = DelayTime;
}

/**
 * @brief      Enable or Disable Continue Transmit Mode.
 * @param[in]  ContinueCtrl:
 *             - COMMON_DISABLE: ss_n will be deassert between frame and next_frame
 *             - COMMON_ENABLE : ss_n will keep assert between frame and next_frame
 * @return     None.
 */
void Spi_EnableContinueMode(Common_ControlStateType ContinueCtrl)
{
    Spi_RegBfPtr->SPI_CTRL2.CONTINUE_MODE = (uint32)ContinueCtrl;
}

/**
 * @brief      Send data.
 * @param[in]  Data:  The data to be send.
 * @return     None.
 */
void Spi_SendData(uint32 Data)
{
    /* Send data */
    Spi_RegWPtr->SPI_DR_LOW = Data;
}

/**
 * @brief      Receive data.
 * @param      None.
 * @return     The received data.
 */
uint32 Spi_ReceiveData(void)
{
    return (uint32)Spi_RegWPtr->SPI_DR_LOW;
}

/**
 * @brief      Enable or Disable Txd accelerate method in slave mode.
 * @param[in]  SpeedSelect:
 *             - COMMON_DISABLE: slave txd is in legacy method
 *             - COMMON_ENABLE : slave txd is in accelerate method
 * @return     None.
 */
void Spi_SetTxdAccelerateMethod(Common_ControlStateType SpeedSelect)
{
    Spi_RegBfPtr->SPI_CTRL2.SLV_TXD_ACCELERATE = (uint32)SpeedSelect;
}

/**
 * @brief      Configure receive data (rxd) sample delay in master mode.
 * @param[in]  DelayTime: Value represents a single spi_clk delay on the sample of the rxd signal.
 *                        Maximum value is 31 cycles.
 * @return     None.
 */
void Spi_ConfigRxdSampleDelay(uint32 DelayTime)
{
    Spi_RegBfPtr->SPI_RXSDR.RX_SAMPLE_DLY = DelayTime;
}

/**
 * @brief      Configure SPI transmit/receive direction. 
 *             This API can only be called when the SPI device is disabled.
 * @param[in]  Dir:  Specified transmit/receive direction.
 *             - SPI_MSB:  Most significant bit first
 *             - SPI_LSB:  Least significant bit first
 * @return     None.
 */
void Spi_ConfigTransmitDir(Spi_TransmitDirType Dir)
{
    Spi_RegBfPtr->SPI_CTRLR0.LSB = (uint32)Dir;
}

/**
 * @brief      Get transmit FIFO level.
 * @param      None.
 * @return     uint32: The number of valid data entries in the transmit FIFO memory.
 */
uint32 Spi_GetTxFifoLevel(void)
{
    return Spi_RegBfPtr->SPI_FLR.TXTFL;
}

/**
 * @brief      Get receive FIFO level.
 * @param      None.
 * @return     The number of valid data entries in the receive FIFO memory.
 */
uint32 Spi_GetRxFifoLevel(void)
{
    return Spi_RegBfPtr->SPI_FLR.RXTFL;
}

/**
 * @brief      Reset transmit FIFO. Clear the full/empty, address, counter and data of TX FIFO.
 *             This API can only be called when the SPI device is disabled.
 * @param      None.
 * @return     None.
 */
void Spi_ResetTxFifo(void)
{
    Spi_RegBfPtr->SPI_CTRLR0.TXFRST = 1U;
}

/**
 * @brief      Reset receive FIFO. Clear the full/empty, address, counter and data of RX FIFO.
 *             This API can only be called when the SPI device is disabled.
 * @param      None.
 * @return     None.
 */
void Spi_ResetRxFifo(void)
{
    Spi_RegBfPtr->SPI_CTRLR0.RXFRST = 1U;
}

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
Common_FlagStatusType Spi_GetStatus(Spi_StatusType SpiStatus)
{
    uint32 IntBitStatus;
    IntBitStatus = (Spi_RegWPtr->SPI_SR >> (uint32)SpiStatus) & 0x1U;
    return (Common_FlagStatusType)IntBitStatus;
}

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
Common_FlagStatusType Spi_GetIntStatus(Spi_IntType IntType)
{
    uint32 IntBitStatus;
    IntBitStatus = (Spi_RegWPtr->SPI_ISR >> (uint32)IntType) & 0x1U;
    return (Common_FlagStatusType)IntBitStatus;
}

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
Common_FlagStatusType Spi_GetRawIntStatus(Spi_RawIntType IntType)
{
    uint32 IntBitStatus;
    IntBitStatus = (Spi_RegWPtr->SPI_ISR >> ((uint32)IntType + 16U)) & 0x1U;
    return (Common_FlagStatusType)IntBitStatus;
}

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
void Spi_SetIntMask(Spi_IntType IntType, Common_IntMaskType IntMask)
{
    if (COMMON_MASK == IntMask)
    {
        Spi_RegWPtr->SPI_IMR &= (~Spi_IntMaskTable[IntType]);
    }
    else
    {
        Spi_RegWPtr->SPI_IMR |= Spi_IntMaskTable[IntType];
    }
}

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
void Spi_ClearInt(Spi_IntType IntType)
{
    Spi_RegWPtr->SPI_ICR = Spi_IntClearTable[IntType];
}

/**
 * @brief      install call back function.
 * @param[in]  IntId:  Select the interrupt. SPI_INT_ALL is invalid.
 * @param[in]  CbFun:  Pointer to callback function.
 * @return     None.
 */
void Spi_InstallCallbackFunc(Spi_IntType IntId, Isr_CbFuncType *CbFun)
{
    if (IntId < SPI_INT_ALL)
    {
        Spi_IsrCbFuncPtr[IntId] = CbFun;
    }
}

/** @} end of group Public_FunctionDefinition */
