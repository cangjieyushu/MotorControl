/**************************************************************************************************/
/** 
 * @file      : Z20A8300A_Spi.c
 * @brief     : Z20A8300A Spi Communication Source File.
 *                 - Platform: Z20A8300A
 * @version   : V0.7.0
 * @date      : September-2022
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @Copyright : Copyright (c) 2022-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
/** @addtogroup Z20A8300A_Driver
 *  @{
 */

/** @addtogroup Z20A8300A_Spi
 *  @brief Z20A8300A Spi Read/Write Register API.
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "Z20A8300A_Spi.h"

/** @defgroup Spi_Private_MacroDefinition
 *  @{
 */

#define Z20A8300A_UNLOCK_PROTECTION_ADDRESS                  0x001BU

/** @} end of Spi_Private_MacroDefinition */

/** @defgroup Spi_Private_TypeDefinition
 *  @{
 */

/** @} end of group Spi_Private_TypeDefinition */

/** @defgroup Spi_Global_VariableDefinition
 *  @{
 */

/** @} end of group Spi_Global_VariableDefinition */

/** @defgroup Spi_Private_VariableDefinition
 *  @{
 */

/** @} end of group Spi_Private_VariableDefinition */

/** @defgroup Spi_Private_FunctionDeclaration
 *  @{
 */

/** @} end of group Spi_Private_FunctionDeclaration */

/** @defgroup Spi_Private_FunctionDefinition
 *  @{
 */

/** @} end of group Spi_Private_FunctionDefinition */

/** @defgroup Spi_Public_FunctionDefinition
 *  @{
 */

/**
 * @brief      Z20A8300A Send Frame Atomic
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct point
 * @param[in]  Address: register address
 * @param[in]  WR: WR_READ or WR_WRITE
 * @param[in]  Data: data field
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_SendFrameAtomic(Z20A8300A_IfType *IfPtr,
                                                  Z20A8300A_RegisterAddressType Address,
                                                  Z20A8300A_ReadWriteBitType WR,
                                                  uint32_t Data)
{
    Z20A8300A_SpiStatusType SpiStatus;
    Z20A8300A_Assert(IfPtr->SpiSendCallBack == NULL);
    
    /* clear buff */
    IfPtr->TxFrame.DB             = 0U;        
    /* set send address */
    IfPtr->TxFrame.BITS.ADDRESS  = (uint32_t)Address;
    /* read data */
    IfPtr->TxFrame.BITS.WR       = (uint32_t)WR;
    /* calc parity */
    IfPtr->TxFrame.BITS.DATA     = Data;
    
    if(0U == Z20A8300A_ParityCheck16((uint16_t)IfPtr->TxFrame.DB))
    {
        IfPtr->TxFrame.BITS.PARITY = 1U;
    }
    
    /* spi send */
    if(0U == IfPtr->SpiSendCallBack((uint16_t)IfPtr->TxFrame.DB))
    {
        SpiStatus = Z20A8300A_ERR_SEND;
    }
    else
    {
        SpiStatus = Z20A8300A_ERR_OK;
    }
    
    return SpiStatus;
}

/**
 * @brief      Z20A8300A Waiting For Reception Atomic
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct point
 *
 * @return     uint16_t
 * @retval     0: timeout
 * @retval     1: data received
 *
 */
uint16_t Z20A8300A_WaitingForReceptionAtomic(Z20A8300A_IfType *IfPtr)
{
    Z20A8300A_Assert(IfPtr->SpiWaitingForReceptionCallBack == NULL);
    return IfPtr->SpiWaitingForReceptionCallBack();
}

/**
 * @brief      Z20A8300A Receive Frame Atomic
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct point
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_ReceiveFrameAtomic(Z20A8300A_IfType *IfPtr)
{
    Z20A8300A_SpiStatusType SpiStatus;
    Z20A8300A_Assert(IfPtr->SpiReceiveCallBack == NULL);
    
    /* get receive data */
    IfPtr->RxFrame.DB = IfPtr->SpiReceiveCallBack();   
    /* calc parity */
    if(1U == Z20A8300A_ParityCheck16((uint16_t)IfPtr->RxFrame.DB))
    {
        SpiStatus = Z20A8300A_ERR_OK;
    }
    else
    {
        SpiStatus = Z20A8300A_ERR_PARITY;
    }
    
    return SpiStatus;
}
   
/**
 * @brief      Z20A8300A Receive Data Block
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct point
 * @param[in]  Address: register address
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_ReadDataRegister(Z20A8300A_IfType *IfPtr,
                                                   Z20A8300A_RegisterAddressType Address)
{
    Z20A8300A_SpiStatusType SpiStatus;
    Z20A8300A_Assert(IfPtr->SpiSendCallBack == NULL);
    Z20A8300A_Assert(IfPtr->SpiWaitingForReceptionCallBack == NULL);
    Z20A8300A_Assert(IfPtr->SpiReceiveCallBack == NULL);
    
    /* clear buff */
    IfPtr->TxFrame.DB            = 0U;
    /* set send address */
    IfPtr->TxFrame.BITS.ADDRESS  = (uint32_t)Address;
    /*!< read data */
    IfPtr->TxFrame.BITS.WR       = (uint32_t)Z20A8300A_WR_READ;
    IfPtr->TxFrame.BITS.DATA     = 0U;
    
    /* calc parity */
    if(0U == Z20A8300A_ParityCheck16((uint16_t)IfPtr->TxFrame.DB))
    {
        IfPtr->TxFrame.BITS.PARITY = 1U;
    }
    
    /* spi send */
    if(0U == IfPtr->SpiSendCallBack((uint16_t)IfPtr->TxFrame.DB))
    {
        SpiStatus = Z20A8300A_ERR_SEND;
    }
    else
    {
        /* wait for receive */
        if(1U == IfPtr->SpiWaitingForReceptionCallBack())    
        {
            /* get receive data */
            IfPtr->RxFrame.DB = IfPtr->SpiReceiveCallBack();   
            
            /* calc parity */
            if(1U == Z20A8300A_ParityCheck16((uint16_t)IfPtr->RxFrame.DB))
            {
                SpiStatus = Z20A8300A_ERR_OK;
            }
            else
            {
                SpiStatus = Z20A8300A_ERR_PARITY;
            }
        }
        else
        {
            SpiStatus = Z20A8300A_ERR_OVER_TIME;
        }
    }
    
    return SpiStatus;
}

/**
 * @brief      Z20A8300A Write Data Block
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct point
 * @param[in]  Address: register address
 * @param[in]  Data: data field
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_WriteDataRegister(Z20A8300A_IfType *IfPtr,
                                                    Z20A8300A_RegisterAddressType Address,
                                                    uint32_t Data)
{
    Z20A8300A_SpiStatusType SpiStatus;
    Z20A8300A_Assert(IfPtr->SpiSendCallBack == NULL);
    Z20A8300A_Assert(IfPtr->SpiWaitingForReceptionCallBack == NULL);
    Z20A8300A_Assert(IfPtr->SpiReceiveCallBack == NULL);
    
    /* clear buff */
    IfPtr->TxFrame.DB           = 0U;            
    /* set send address */
    IfPtr->TxFrame.BITS.ADDRESS = (uint32_t)Address;
    /* write data */
    IfPtr->TxFrame.BITS.WR      = (uint32_t)Z20A8300A_WR_WRITE;
    /* set send data */
    IfPtr->TxFrame.BITS.DATA    = Data;
    
    /* calc parity */
    if(0U == Z20A8300A_ParityCheck16((uint16_t)IfPtr->TxFrame.DB))
    {
        IfPtr->TxFrame.BITS.PARITY = 1U;
    }
    /* spi send */
    if(0U == IfPtr->SpiSendCallBack((uint16_t)IfPtr->TxFrame.DB))
    {
        SpiStatus = Z20A8300A_ERR_SEND;
    }
    else 
    {
        /* wait for receive */
        if(1U == IfPtr->SpiWaitingForReceptionCallBack())    
        {
            IfPtr->RxFrame.DB = IfPtr->SpiReceiveCallBack();
            /* calc parity */
            if(1U == Z20A8300A_ParityCheck16((uint16_t)IfPtr->RxFrame.DB))
            {
                if((Address >= Z20A8300A_DIAG0_ADDRESS && Address <= Z20A8300A_DIAG2_ADDRESS) || 
                   (Address == (Z20A8300A_RegisterAddressType)Z20A8300A_UNLOCK_PROTECTION_ADDRESS))
                {
                    /* read only register return*/
                    /* Specific instructions return */
                    SpiStatus =  Z20A8300A_ERR_OK;            
                }
                else
                {
                    /* Read written data */
                    SpiStatus = Z20A8300A_ReadDataRegister(IfPtr,Address);
                    if(Z20A8300A_ERR_OK == SpiStatus)
                    {
                        /* written and read is the same*/
                        if(IfPtr->RxFrame.BITS.DATA == Data)
                        {
                             SpiStatus =  Z20A8300A_ERR_OK;
                        }
                        else
                        {
                            SpiStatus = Z20A8300A_ERR_WRITE;
                        }
                    }
                }
            }
            else
            {
                SpiStatus = Z20A8300A_ERR_PARITY;
            }
        }
        else
        {
            SpiStatus =  Z20A8300A_ERR_OVER_TIME;
        }
    }
    
    return SpiStatus;
}

/** @} end of group Spi_Public_FunctionDefinition */

#ifdef __cplusplus
}
#endif

/** @} end of group Z20A8300A_Spi */

/** @} end of group Z20A8300A_Driver */
