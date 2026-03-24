/**************************************************************************************************/
/**
 * @file     spi_drv.c
 * @brief    SPI module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#include "spi_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */
/** @defgroup SPI
 *  @brief SPI driver modules
 *  @{
 */

/** @defgroup SPI_Private_Types
 *  @{
 */

/** @} end of group SPI_Private_Types */

/** @defgroup SPI_Private_Defines
 *  @{
 */

#define SPI_NUM     (4U)

/** @} end of group SPI_Private_Defines */

/** @defgroup SPI_Private_Variables
 *  @{
 */
/**
 *  @brief SPI ISR callback function pointer array
 */
static isr_cb_t * spiIsrCb[SPI_NUM][SPI_INT_ALL] =
{
    {NULL,NULL,NULL,NULL,NULL},
    {NULL,NULL,NULL,NULL,NULL},
    {NULL,NULL,NULL,NULL,NULL},
    {NULL,NULL,NULL,NULL,NULL}
};

/**
 *  @brief SPI0 SPI1 SPI2 address array
 */
/*PRQA S 0303 ++*/
static spi_reg_t * const spiRegPtr[SPI_NUM] =
{
    (spi_reg_t *)SPI0_BASE_ADDR,   /*!< SPI0 base address */
    (spi_reg_t *)SPI1_BASE_ADDR,   /*!< SPI1 base address */
    (spi_reg_t *)SPI2_BASE_ADDR,   /*!< SPI2 base address */
    (spi_reg_t *)SPI3_BASE_ADDR    /*!< SPI3 base address */
};

static spi_reg_w_t * const spiRegWPtr[SPI_NUM] =
{
    (spi_reg_w_t *)SPI0_BASE_ADDR,   /*!< SPI0 base address */
    (spi_reg_w_t *)SPI1_BASE_ADDR,   /*!< SPI1 base address */
    (spi_reg_w_t *)SPI2_BASE_ADDR,   /*!< SPI2 base address */
    (spi_reg_w_t *)SPI3_BASE_ADDR    /*!< SPI3 base address */
};
/*PRQA S 0303 --*/
/**
 *  @brief SPI Interrupt Mask  array
 */
static const uint32_t spiIntMaskTable[ ] =
{
    0x00000001U,   /*!< Transmit FIFO empty interrupt */
    0x00000002U,   /*!< Transmit FIFO overflow interrupt*/
    0x00000004U,   /*!< Receive FIFO underflow interrupt */
    0x00000008U,   /*!< Received FIFO overflow interrupt */
    0x00000010U,   /*!< Received FIFO full interrupt */
    0x0000001FU    /*!< All the interrupt */
};

/** @} end of group SPI_Private_Variables */

/** @defgroup SPI_Global_Variables
 *  @{
 */

/** @} end of group SPI_Global_Variables */

/** @defgroup SPI_Private_FunctionDeclaration
 *  @{
 */
 void SPI0_Txe_DriverIRQHandler(void);
 void SPI0_Txo_DriverIRQHandler(void);
 void SPI0_Rxf_DriverIRQHandler(void);
 void SPI0_Rxo_DriverIRQHandler(void);
 void SPI0_Rxu_DriverIRQHandler(void);
 void SPI1_Txe_DriverIRQHandler(void);
 void SPI1_Txo_DriverIRQHandler(void);
 void SPI1_Rxf_DriverIRQHandler(void);
 void SPI1_Rxo_DriverIRQHandler(void);
 void SPI1_Rxu_DriverIRQHandler(void);
 void SPI2_Txe_DriverIRQHandler(void);
 void SPI2_Txo_DriverIRQHandler(void);
 void SPI2_Rxf_DriverIRQHandler(void);
 void SPI2_Rxo_DriverIRQHandler(void);
 void SPI2_Rxu_DriverIRQHandler(void);
 void SPI3_Txe_DriverIRQHandler(void);
 void SPI3_Txo_DriverIRQHandler(void);
 void SPI3_Rxf_DriverIRQHandler(void);
 void SPI3_Rxo_DriverIRQHandler(void);
 void SPI3_Rxu_DriverIRQHandler(void);

/** @} end of group SPI_Private_FunctionDeclaration */

/** @defgroup SPI_Private_Functions
 *  @{
 */

/**
 * @brief  SPI txe interrupt handler.
 *
 * @param  None.
 *
 * @return None.
 *
 */
static void SPI_Txe_Handler(SPI_Id_t spiId)
{
    uint32_t intStatus;
    spi_reg_t * SPIx = (spi_reg_t *)(spiRegPtr[spiId]);
    spi_reg_w_t * SPIxw = (spi_reg_w_t *)(spiRegWPtr[spiId]);

    /* Read the interrupt status */
    intStatus = SPIxw->SPI_ISR;

    if((intStatus & spiIntMaskTable[SPI_INT_TXE]) != 0U)
    {
        if(spiIsrCb[spiId][SPI_INT_TXE] != NULL)
        {
            spiIsrCb[spiId][SPI_INT_TXE]();
        }
        /* Mask this interrupt */
        else
        {
            SPIx->SPI_IER.TXEIE = 0U;
        }    
    }
    COMMON_DSB();
}

/**
 * @brief  SPI txo interrupt handler.
 *
 * @param  None.
 *
 * @return None.
 *
 */
static void SPI_Txo_Handler(SPI_Id_t spiId)
{
    uint32_t intStatus;
    volatile uint32_t dummyData;
    spi_reg_t * SPIx = (spi_reg_t *)(spiRegPtr[spiId]);
    spi_reg_w_t * SPIxw = (spi_reg_w_t *)(spiRegWPtr[spiId]);

    /* Read the interrupt status */
    intStatus = SPIxw->SPI_ISR;
    /* Dummy read to clear tx fifo overflow interrupt */
    dummyData = SPIx->SPI_TXOICR.TXOICR;
    if((intStatus & spiIntMaskTable[SPI_INT_TXO]) != 0U)
    {
        if(spiIsrCb[spiId][SPI_INT_TXO] != NULL)
        {
            spiIsrCb[spiId][SPI_INT_TXO]();
        }
        /* Mask this interrupt */
        else
        {
            SPIx->SPI_IER.TXOIE = 0U;
        }
    }
    COMMON_DSB();
}

/**
 * @brief      SPI rxf interrupt handler.
 *
 * @param  None.
 *
 * @return None.
 *
 */
static void SPI_Rxf_Handler(SPI_Id_t spiId)
{
    uint32_t intStatus;
    spi_reg_t * SPIx = (spi_reg_t *)(spiRegPtr[spiId]);
    spi_reg_w_t * SPIxw = (spi_reg_w_t *)(spiRegWPtr[spiId]);

    /* Read the interrupt status */
    intStatus = SPIxw->SPI_ISR;

    if((intStatus & spiIntMaskTable[SPI_INT_RXF]) != 0U)
    {
        if(spiIsrCb[spiId][SPI_INT_RXF] != NULL)
        {
            spiIsrCb[spiId][SPI_INT_RXF]();
        }
        /* Mask this interrupt */
        else
        {
            SPIx->SPI_IER.RXFIE = 0U;
        }
    }
    COMMON_DSB();
}
/**
 * @brief  SPI rxu interrupt handler.
 *
 * @param  None.
 *
 * @return None.
 *
 */
static void SPI_Rxu_Handler(SPI_Id_t spiId)
{
    uint32_t intStatus;
    volatile uint32_t dummyData;
    spi_reg_t * SPIx = (spi_reg_t *)(spiRegPtr[spiId]);
    spi_reg_w_t * SPIxw = (spi_reg_w_t *)(spiRegWPtr[spiId]);

    /* Read the interrupt status */
    intStatus = SPIxw->SPI_ISR;
    /* Dummy read to clear rx fifo underflow interrupt */
    dummyData = SPIx->SPI_RXUICR.RXUICR;
    
    if((intStatus & spiIntMaskTable[SPI_INT_RXU]) != 0U)
    {
        if(spiIsrCb[spiId][SPI_INT_RXU] != NULL)
        {
            spiIsrCb[spiId][SPI_INT_RXU]();
        }
        /* Mask this interrupt */
        else
        {
            SPIx->SPI_IER.RXUIE = 0U;
        }
    }
    COMMON_DSB();
}
/**
 * @brief  SPI rxo interrupt handler.
 *
 * @param  None.
 *
 * @return None.
 *
 */
static void SPI_Rxo_Handler(SPI_Id_t spiId)
{
    uint32_t intStatus;
    volatile uint32_t dummyData;
    spi_reg_t * SPIx = (spi_reg_t *)(spiRegPtr[spiId]);
    spi_reg_w_t * SPIxw = (spi_reg_w_t *)(spiRegWPtr[spiId]);

    /* Read the interrupt status */
    intStatus = SPIxw->SPI_ISR;
    /* Dummy read to clear rx fifo overflow interrupt */
    dummyData = SPIx->SPI_RXOICR.RXOICR;
        
    if((intStatus & spiIntMaskTable[SPI_INT_RXO]) != 0U)
    {
        if(spiIsrCb[spiId][SPI_INT_RXO] != NULL)
        {
            spiIsrCb[spiId][SPI_INT_RXO]();
        }
        /* Mask this interrupt */
        else
        {
            SPIx->SPI_IER.RXOIE = 0U;
        }
    }
    COMMON_DSB();
}
/**
 * @brief  SPI0 txe interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI0_Txe_DriverIRQHandler(void)
{
    SPI_Txe_Handler(SPI_ID_0);
}

/**
 * @brief  SPI0 txo interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI0_Txo_DriverIRQHandler(void)
{
    SPI_Txo_Handler(SPI_ID_0);
}

/**
 * @brief  SPI0 rxf interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI0_Rxf_DriverIRQHandler(void)
{
    SPI_Rxf_Handler(SPI_ID_0);
}

/**
 * @brief  SPI0 rxu interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI0_Rxu_DriverIRQHandler(void)
{
    SPI_Rxu_Handler(SPI_ID_0);
}

/**
 * @brief  SPI0 rxo interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 **/
 void SPI0_Rxo_DriverIRQHandler(void)
{
    SPI_Rxo_Handler(SPI_ID_0);
}

/**
 * @brief  SPI1 txe interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI1_Txe_DriverIRQHandler(void)
{
    SPI_Txe_Handler(SPI_ID_1);
}

/**
 * @brief  SPI1 txo interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI1_Txo_DriverIRQHandler(void)
{
    SPI_Txo_Handler(SPI_ID_1);
}

/**
 * @brief  SPI1 rxf interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI1_Rxf_DriverIRQHandler(void)
{
    SPI_Rxf_Handler(SPI_ID_1);
}

/**
 * @brief  SPI1 rxu interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI1_Rxu_DriverIRQHandler(void)
{
    SPI_Rxu_Handler(SPI_ID_1);
}

/**
 * @brief  SPI1 rxo interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI1_Rxo_DriverIRQHandler(void)
{
    SPI_Rxo_Handler(SPI_ID_1);
}

/**
 * @brief  SPI2 txe interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI2_Txe_DriverIRQHandler(void)
{
    SPI_Txe_Handler(SPI_ID_2);
}

/**
 * @brief  SPI2 txo interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI2_Txo_DriverIRQHandler(void)
{
    SPI_Txo_Handler(SPI_ID_2);
}

/**
 * @brief  SPI2 rxf interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI2_Rxf_DriverIRQHandler(void)
{
    SPI_Rxf_Handler(SPI_ID_2);
}

/**
 * @brief  SPI2 rxu interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI2_Rxu_DriverIRQHandler(void)
{
    SPI_Rxu_Handler(SPI_ID_2);
}
/**
 * @brief  SPI2 rxo interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI2_Rxo_DriverIRQHandler(void)
{
    SPI_Rxo_Handler(SPI_ID_2);
}
/**
 * @brief  SPI3 txe interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI3_Txe_DriverIRQHandler(void)
{
    SPI_Txe_Handler(SPI_ID_3);
}

/**
 * @brief  SPI3 txo interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI3_Txo_DriverIRQHandler(void)
{
    SPI_Txo_Handler(SPI_ID_3);
}
/**
 * @brief  SPI3 rxf interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI3_Rxf_DriverIRQHandler(void)
{
    SPI_Rxf_Handler(SPI_ID_3);
}

/**
 * @brief  SPI3 rxu interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI3_Rxu_DriverIRQHandler(void)
{
    SPI_Rxu_Handler(SPI_ID_3);
}

/**
 * @brief  SPI3 rxo interrupt function.
 *
 * @param  None.
 *
 * @return None.
 *
 */
 void SPI3_Rxo_DriverIRQHandler(void)
{
    SPI_Rxo_Handler(SPI_ID_3);
}

/** @} end of group SPI_Private_Functions */

/** @defgroup SPI_Public_Functions
 *  @{
 */

/**
 * @brief      Initializes the SPI .
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI_ID_0, SPI_ID_1, SPI_ID_2.
 * @param[in]  spiConfigStruct:  Pointer to a SPI configuration structure.
 *
 * @return none.
 *
 */
void SPI_Init(SPI_Id_t spiNo, const SPI_Config_t * spiConfigStruct)
{
    spi_reg_t * SPIx = (spi_reg_t *)(spiRegPtr[spiNo]);

    if(NULL != spiConfigStruct)
    {
        SPIx->SPI_CTRLR0.MST_MODE = (uint32_t)spiConfigStruct->mode;
        /* Set SPI clock divider */
        SPIx->SPI_BAUDR.SCKDV = spiConfigStruct->clkDivider;
        /* Set data frame size */
        SPIx->SPI_CTRLR0.DFS_32 = spiConfigStruct->dataSize-1U;
        /* Set serial clock phase */
        SPIx->SPI_CTRLR0.SCPH = (uint32_t)spiConfigStruct->clkPhase;
        /* et clock polarity */
        SPIx->SPI_CTRLR0.SCPOL = (uint32_t)spiConfigStruct->clkPolarity;
        /* Set transfer mode */
        SPIx->SPI_CTRLR0.TMOD = (uint32_t)spiConfigStruct->transMode;
        /* Set transmit FIFO threshold level */
        SPIx->SPI_FTLR.TFT = (uint32_t)spiConfigStruct->transFifoThr;
        /* Set receive FIFO threshold level */
        SPIx->SPI_FTLR.RFT = (uint32_t)spiConfigStruct->recvFifoThr;
    }
}


/**
 * @brief      Initializes the SPI DMA.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI_ID_0, SPI_ID_1, SPI_ID_2.
 * @param[in]  dmaConfigStruct:  Pointer to a SPI Master DMA configuration structure.
 *
 * @return none.
 *
 */
void SPI_DmaConfig(SPI_Id_t spiNo, const SPI_DmaLvl_t * dmaConfigStruct)
{
    spi_reg_t * SPIx = (spi_reg_t *)(spiRegPtr[spiNo]);

    if(NULL != dmaConfigStruct)
    {
         /* Set transmit request level */
        SPIx->SPI_DMATDLR.DMATDL = dmaConfigStruct->dmaTransReqLevel;
        /* Set receive request level */
        SPIx->SPI_DMARDLR.DMARDL = dmaConfigStruct->dmaRecvReqLevel;
    }
}

/**
 * @brief      Enable the SPI.
 *
 * @param[in]  spiNo:  Select the SPI port,should be SPI_ID_0,SPI_ID_1,SPI_ID_2.
 *
 * @return none.
 *
 */
void SPI_Enable(SPI_Id_t spiNo)
{
    spi_reg_t * SPIx = (spi_reg_t *)(spiRegPtr[spiNo]);

    /* Enable/Disable the SPI */
    SPIx->SPI_SSENR.SPI_EN = 1U;
}


/**
 * @brief      Disable the SPI.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI_ID_0,SPI_ID_1, SPI_ID_2.
 *
 * @return none.
 *
 */
void SPI_Disable(SPI_Id_t spiNo)
{
    spi_reg_t * SPIx = (spi_reg_t *)(spiRegPtr[spiNo]);

    /* Enable/Disable the SPI */
    SPIx->SPI_SSENR.SPI_EN = 0U;
}

/**
 * @brief      Set Master data frame number.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI_ID_0, SPI_ID_1, SPI_ID_2.
 * @param[in]  frameNum: data frame number, should <= 0xFFFF.
 *
 * @return none.
 *
 * This function only used in Receive only and EEPROM transfer mode.
 */
void SPI_SetDataFrameNum(SPI_Id_t spiNo, uint32_t frameNum)
{
    spi_reg_t * SPIx = (spi_reg_t *)(spiRegPtr[spiNo]);

    if(frameNum > 0U)
    {
        SPIx->SPI_CTRLR1.NDF = frameNum - 1U;
    }
    else
    {  
        SPIx->SPI_CTRLR1.NDF = 0U;
    }
}

/**
 * @brief      Enable or disable the SPI DMA function.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI_ID_1,SPI_ID_1, SPI_ID_2.
 * @param[in]  transmitDmaCtrl: Transmit DMA Enable/Disable function state
 * @param[in]  rcvDmaCtrl: Receive DMA Enable/Disable function state.
 *
 * @return none.
 *
 */
void SPI_DmaCmd(SPI_Id_t spiNo, ControlState_t transmitDmaCtrl,
                ControlState_t rcvDmaCtrl)
{
    spi_reg_t * SPIx = (spi_reg_t *)(spiRegPtr[spiNo]);

    /* Enable/Disable transmit DMA */
    SPIx->SPI_DMACR.TDMAE = (uint32_t)transmitDmaCtrl;
    /* Enable/Disable receive DMA */
    SPIx->SPI_DMACR.RDMAE = (uint32_t)rcvDmaCtrl;
}

/**
 * @brief      Select SPI slave.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI_ID_0, SPI_ID_1, SPI_ID_2
 *
 * @return none.
 *
 */
void SPI_SelectSlave(SPI_Id_t spiNo, SPI_SelectSlave_t chipSelect)
{
    spi_reg_t * SPIx = (spi_reg_t *)(spiRegPtr[spiNo]);

    SPIx->SPI_SSENR.SER = (uint32_t)chipSelect;
}

/**
 * @brief      Send  data.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI_ID_0, SPI_ID_1, SPI_ID_2.
 * @param[in]  data:  The data to be send.
 *
 * @return     none.
 *
 */
void SPI_SendData(SPI_Id_t spiNo, uint32_t data)
{
    spi_reg_w_t * SPIxw = (spi_reg_w_t *)(spiRegWPtr[spiNo]);

    /* Send data */
    SPIxw->SPI_DR_LOW = data;
}

/**
 * @brief      Receive data.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI_ID_0, SPI_ID_1, SPI_ID_2.
 *
 * @return The received data.
 *
 */
uint32_t SPI_ReceiveData(SPI_Id_t spiNo)
{
    spi_reg_w_t * SPIxw = (spi_reg_w_t *)(spiRegWPtr[spiNo]);

    return ((uint32_t)SPIxw->SPI_DR_LOW);
}

/**
 * @brief      Get transmit FIFO level.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI_ID_0, SPI_ID_1, SPI_ID_2.
 *
 * @return     The number of valid data entries in the transmit FIFO memory.
 */
uint32_t SPI_GetTxFifoLevel(SPI_Id_t spiNo)
{
    spi_reg_t * SPIx = (spi_reg_t *)(spiRegPtr[spiNo]);

    return (SPIx->SPI_FLR.TXTFL);
}

/**
 * @brief      Get receive FIFO level.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI_ID_0, SPI_ID_1, SPI_ID_2.
 *
 * @return The number of valid data entries in the receive FIFO memory.
 *
 */
uint32_t SPI_GetRxFifoLevel(SPI_Id_t spiNo)
{
    spi_reg_t * SPIx = (spi_reg_t *)(spiRegPtr[spiNo]);

    return (SPIx->SPI_FLR.RXTFL);
}


/**
 * @brief      Check whether status flag is set or not for given status type.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI_ID_0, SPI_ID_1, SPI_ID_2.
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
FlagStatus_t SPI_GetStatus(SPI_Id_t spiNo, SPI_Status_t spiStatus)
{
    uint32_t intBitStatus;
    spi_reg_w_t * SPIxw = (spi_reg_w_t *)(spiRegWPtr[spiNo]);

    intBitStatus = (((SPIxw->SPI_SR)&(0x01UL << (uint32_t)spiStatus))
                                  >> (uint32_t)spiStatus);
    return (FlagStatus_t)intBitStatus;
}


/**
 * @brief      Check whether interrupt status flag is set or not for given
 *             interrupt type.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI_ID_0, SPI_ID_1, SPI_ID_2.
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
FlagStatus_t SPI_GetIntStatus(SPI_Id_t spiNo, SPI_Int_t intType)
{
    uint32_t intBitStatus;
    spi_reg_w_t * SPIxw = (spi_reg_w_t *)(spiRegWPtr[spiNo]);

    intBitStatus = (((SPIxw->SPI_ISR)&(0x01UL << (uint32_t)intType))
                                  >> (uint32_t)intType);
    return (FlagStatus_t)intBitStatus;
}

/**
 * @brief      Check whether  raw interrupt status flag is set or not for
 *             given interrupt type.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI_ID_0, SPI_ID_1, SPI_ID_2.
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
FlagStatus_t SPI_GetRawIntStatus(SPI_Id_t spiNo, SPI_RawInt_t intType)
{
    uint32_t intBitStatus;
    spi_reg_w_t * SPIxw = (spi_reg_w_t *)(spiRegWPtr[spiNo]);

    intBitStatus = (((SPIxw->SPI_ISR)&(0x01UL << ((uint32_t)intType+16UL)))
                                  >> ((uint32_t)intType+16UL));
    return (FlagStatus_t)intBitStatus;
}

/**
 * @brief      Mask/Unmask specified  interrupt type.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI_ID_0, SPI_ID_1, SPI_ID_2.
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
void SPI_IntMask(SPI_Id_t spiNo, SPI_Int_t intType, IntMask_t intMask)
{
    spi_reg_w_t * SPIxw = (spi_reg_w_t *)(spiRegWPtr[spiNo]);

    if(MASK == intMask)
    {
        SPIxw->SPI_IER &= (~ spiIntMaskTable[intType]);
    }
    else
    {
        SPIxw->SPI_IER |= spiIntMaskTable[intType];
    }
}

/**
 * @brief      Clear all interrupt status flags.
 *
 * @param[in]  spiNo:  Select the SPI id, should be SPI_ID_0,SPI_ID_1, SPI_ID_2.
 * @param[in]  intType:  Specified interrupt type.
 *             - SPI_INT_TXO
 *             - SPI_INT_RXU
 *             - SPI_INT_RXO
 *             - SPI_INT_ALL
 *
 * @return none.
 *
 */
void SPI_ClearInt(SPI_Id_t spiNo, SPI_Int_t intType)
{
    spi_reg_t * SPIx = (spi_reg_t *)(spiRegPtr[spiNo]);
    volatile uint32_t dummyData = 0U;

     switch(intType)
    {
        case SPI_INT_TXO:
            /* Dummy read to clear interrupt */
            dummyData = SPIx->SPI_TXOICR.TXOICR;
            break;
        case SPI_INT_RXO:
            /* Dummy read to clear interrupt */
            dummyData = SPIx->SPI_RXOICR.RXOICR;
            break;
        case SPI_INT_RXU:
            /* Dummy read to clear interrupt */
            dummyData = SPIx->SPI_RXUICR.RXUICR;
            break;
        case SPI_INT_ALL:
            /* Dummy read to clear interrupt */
            dummyData = SPIx->SPI_ICR.ICR;
            break;
        default:
            /* Do nothing */
            break;
    }
}

/**
 * @brief      install call back function.
 *
 * @param[in]  intId: select the interrupt.
 * @param[in]  cbFun: pointer to callback function.
 *
 * @return none.
 *
 */
void SPI_InstallCallbackFunc(SPI_Id_t spiId, SPI_Int_t intId, isr_cb_t * cbFun)
{
    spiIsrCb[spiId][intId] = cbFun;
}

/** @} end of group SPI_Public_Functions */

/** @} end of group SPI */

/** @} end of group Z20K14XM_Peripheral_Driver */
