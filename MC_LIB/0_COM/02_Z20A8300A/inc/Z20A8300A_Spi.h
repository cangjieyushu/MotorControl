/**************************************************************************************************/
/** 
 * @file      : Z20A8300A_Spi.h
 * @brief     : Z20A8300A Spi Communication Header File.
 *                 - Platform: Z20A8300A
 * @version   : V0.7.0
 * @date      : September-2022
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @Copyright : Copyright (c) 2022-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef Z20A8300A_SPI_H
#define Z20A8300A_SPI_H

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

#include "Z20A8300A_Reg.h"
#include "Z20A8300A_Type.h"
#include "Z20A8300A_Config.h"
#include "Z20A8300A_Ctrl.h"
#include "Z20A8300A_Diag.h"
#include "Z20A8300A_If.h"

/** @defgroup Spi_Public_MacroDefinition
 *  @{
 */

/** @} end of Spi_Public_MacroDefinition */

/** @defgroup Spi_Public_TypeDefinition
 *  @{
 */

/** @} end of group Spi_Public_TypeDefinition */

/** @defgroup Spi_Global_VariableDeclaration
 *  @{
 */

/** @} end of group Spi_Global_VariableDeclaration */

/** @defgroup Spi_Public_FunctionDeclaration
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
                                                 uint32_t Data);

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
uint16_t Z20A8300A_WaitingForReceptionAtomic(Z20A8300A_IfType *IfPtr);

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
Z20A8300A_SpiStatusType Z20A8300A_ReceiveFrameAtomic(Z20A8300A_IfType *IfPtr);
   
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
                                                   Z20A8300A_RegisterAddressType Address);

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
                                                    uint32_t Data);

/** @} end of group Spi_Public_FunctionDeclaration */

#ifdef __cplusplus
}
#endif

/** @} end of group Z20A8300A_Spi */

/** @} end of group Z20A8300A_Driver */

#endif /* Z20A8300A_SPI_H */
