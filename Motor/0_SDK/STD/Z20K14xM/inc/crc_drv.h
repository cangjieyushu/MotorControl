/**************************************************************************************************/
/**
 * @file     crc_drv.h
 * @brief    CRC driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#ifndef CRC_DRV_H
#define CRC_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  CRC
 *  @{
 */

/** @defgroup CRC_Public_Types
 *  @{
 */

/**
 *  @brief CRC mode type definition
 */

typedef enum
{
    CRC_MODE_16BIT = 0U,          /*!< 16-bit CRC protocol mode  */
    CRC_MODE_32BIT                /*!< 32-bit CRC protocol mode  */
} CRC_Mode_t;

/**
 *  @brief CRC write value type definition
 */
typedef enum
{
    CRC_WRITE_DATA = 0U,         /*!< Writes to the CRC data register are data values  */
    CRC_WRITE_SEED               /*!< Writes to the CRC data register are seed values */
} CRC_Data_t;

/**
 *  @brief CRC complement read type definition
 */
typedef enum
{
    CRC_COMPREAD_NO_XOR = 0U,       /*!< No XOR on reading */
    CRC_COMPREAD_INVERT_COMP        /*!< Invert or complement the read value of the CRC Data register */
} CRC_CompRead_t;

/**
 *  @brief CRC read type Of transpose type definition
 */
typedef enum
{
    CRC_READ_NO = 0U,          /*!< No transposition */
    CRC_READ_BIT_Y_BYTE_N,     /*!< Bits in bytes are transposed;bytes are not transposed */
    CRC_READ_BIT_Y_BYTE_Y,     /*!< Both bits in bytes and bytes are transposed */
    CRC_READ_BIT_N_BYTE_Y      /*!< Only bytes are transposed;no bits in a byte are transposed */
} CRC_TransposeRead_t;

/**
 *  @brief CRC write type Of transpose type definition
 */
typedef enum
{
    CRC_WRITE_NO = 0U,          /*!< No transposition */
    CRC_WRITE_BIT_Y_BYTE_N      /*!< Bits in bytes are transposed; bytes are not transposed */
} CRC_TransposeWrite_t;

/**
 *  @brief CRC Configuration Structure type definition
 */
typedef struct
{
    uint32_t              seedValue;           /*!< Write seed values */
    uint32_t              poly;                /*!< Polynomial */
    CRC_CompRead_t        complementRead;      /*!< CRC complement read
                                                    - CRC_COMPREAD_NO_XOR: No XOR on reading
                                                    - CRC_COMPREAD_INVERT_COMP: Invert or complement the read value of the CRC Data register */
    CRC_Mode_t            dataMode;            /*!< CRC protocol mode
                                                    - CRC_MODE_16BIT: 16-bit CRC protocol mode
                                                    - CRC_MODE_32BIT: 32-bit CRC protocol mode */
    CRC_TransposeRead_t    readType;           /*!< CRC read type Of transpose
                                                    - CRC_READ_NO: No transposition
                                                    - CRC_READ_BIT_Y_BYTE_N: Bits in bytes are transposed; bytes are not transposed
                                                    - CRC_READ_BIT_Y_BYTE_Y: Both bits in bytes and bytes are transposed
                                                    - CRC_READ_BIT_N_BYTE_Y: Only bytes are transposed; no bits in a byte are transposed */
    CRC_TransposeWrite_t   writeType;          /*!< CRC write type Of transpose
                                                    - CRC_WRITE_NO: No transposition
                                                    - CRC_WRITE_BIT_Y_BYTE_N: Bits in bytes are transposed; bytes are not transposed
                                                    - CRC_WRITE_BIT_Y_BYTE_Y: Both bits in bytes and bytes are transposed
                                                    - CRC_WRITE_BIT_N_BYTE_Y: Only bytes are transposed; no bits in a byte are transposed */
} CRC_Config_t;

/** @} end of group CRC_Public_Types  */


/** @defgroup CRC_Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief        Initialization of CRC.
 * In this version of the CRC, user configuration write type is CRC_WRITE_NO
 * (No Transposition),the actual configuration is: bit no transposed, BYTE 
 * transposed.
 * User configuration write type is CRC_WRITE_BIT_Y_BYTE_N (Bits in bytes are
 * transposed; bytes are not transposed),the actual configuration is: both bits
 * in bytes and bytes are transposed. 
 *
 * @param[in]    crcConfigStruct:  Pointer to a CRC configuration structure.          
 *
 * @return       SUCC: Initialization success.
 *               ERR: Initialization failure.
 *
 */
ResultStatus_t CRC_Init(const CRC_Config_t *crcConfigStruct);

/**
 * @brief            CRC calculation of 16 bits.
 *
 *
 * @param[in]        dataValue: 8 bits of calculated data
 * @param[in]        length: the length of the array
 * @param[in]        newSeed: Sets new CRC calculations
 *                          - ENABLE: New seed sets and used for new calculation
 *                          - DISABLE:Seed argument ignored, continues old calculation
 * @param[in]        seedValue: new seed if newSeed is enabled,else ignored
 *
 * @return           16-bit calculation results
 *
 */
uint16_t CRC_CalcCRC16bit(uint8_t dataValue[],uint32_t length, 
                          ControlState_t newSeed, uint32_t seedValue);

/**
 * @brief            CRC calculation of 32 bits
 *
 *
 * @param[in]        dataValue: 8 bits of calculated data
 * @param[in]        length: the length of the array
 * @param[in]        newSeed: Sets new CRC calculations
 *                          - ENABLE: New seed sets and used for new calculation
 *                          - DISABLE:Seed argument ignored, continues old calculation
 * @param[in]        seedValue: new seed if newSeed is enabled,else ignored
 *
 * @return           32-bit calculation results
 *
 */
uint32_t CRC_CalcCRC32bit(uint8_t dataValue[],uint32_t length, 
                          ControlState_t newSeed, uint32_t seedValue);

/** @} end of group CRC_Public_FunctionDeclaration */


/** @} end of group CRC */

/** @} end of group Z20K14XM_Peripheral_Driver */

#endif /* CRC_DRV_H */
