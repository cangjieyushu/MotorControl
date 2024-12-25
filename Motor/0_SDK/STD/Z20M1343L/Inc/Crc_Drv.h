/**************************************************************************************************/
/**
 * @file      : Crc_Drv.h
 * @brief     : CRC module driver header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef CRC_DRV_H
#define CRC_DRV_H

#include "Common_Drv.h"

/** @defgroup Public_MacroDefinition
 * @{ 
 */

/** @} end of Public_MacroDefinition */

/** @defgroup Global_VariableDeclaration
 * @{ 
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_TypeDefinition
 *  @{
 */

/**
 *  @brief CRC mode type definition
 */
typedef enum
{
    CRC_MODE_16BIT = 0U,         /*!< 16-bit CRC protocol mode  */
    CRC_MODE_32BIT               /*!< 32-bit CRC protocol mode  */
} Crc_ModeType;

/**
 *  @brief CRC complement read type definition
 */
typedef enum
{
    CRC_COMPREAD_NO_XOR = 0U,    /*!< No XOR on reading */
    CRC_COMPREAD_INVERT_COMP     /*!< Invert or complement the read value of the CRC Data register */
} Crc_CompReadType;

/**
 *  @brief CRC read type Of transpose type definition
 */
typedef enum
{
    CRC_READ_NO = 0U,            /*!< No transposition */
    CRC_READ_BIT_Y_BYTE_N,       /*!< Bits in bytes are transposed;bytes are not transposed */
    CRC_READ_BIT_Y_BYTE_Y,       /*!< Both bits in bytes and bytes are transposed */
    CRC_READ_BIT_N_BYTE_Y        /*!< Only bytes are transposed;no bits in a byte are transposed */
} Crc_TransposeReadType;

/**
 *  @brief CRC write type Of transpose type definition
 */
typedef enum
{
    CRC_WRITE_NO = 0U,           /*!< No transposition */
    CRC_WRITE_BIT_Y_BYTE_N       /*!< Bits in bytes are transposed; bytes are not transposed */
} Crc_TransposeWriteType;

/**
 *  @brief CRC Configuration Structure type definition
 */
typedef struct
{
    uint32                  SeedValue;           /*!< Write seed values */
    uint32                  Poly;                /*!< Polynomial */
    Crc_CompReadType        ComplementRead;      /*!< CRC complement read mode */
    Crc_ModeType            DataMode;            /*!< CRC calculate mode */
    Crc_TransposeReadType   ReadType;            /*!< CRC read type Of transpose */
    Crc_TransposeWriteType  WriteType;           /*!< CRC write type Of transpose */
} Crc_ConfigType;

/** @} end of group Public_TypeDefinition  */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief            Initialization of CRC.
 *                   In this version of the CRC, if user's configuration write type is CRC_WRITE_NO
 *                   (No Transposition), the actual configuration is bits not transposed, bytes
 *                   transposed. If user's configuration write type is CRC_WRITE_BIT_Y_BYTE_N 
 *                   (bits in bytes transposed, bytes not transposed), the actual configuration 
 *                   is both bits in bytes and bytes transposed. 
 *    
 * @param[in]        ConfigPtr: Pointer to a CRC configuration structure.
 *    
 * @return           Common_ResultStatusType: The result of CRC configuration.      
 * @retval           COMMON_ERR: Fail to config CRC.
 * @retval           COMMON_SUCC: Config CRC successfully.
 *
 */
Common_ResultStatusType Crc_Init(const Crc_ConfigType *ConfigPtr);

/**
 * @brief            CRC calculation in 16 bits mode.
 *
 * @param[in]        DataValue: 8 bits of calculated data.
 * @param[in]        Length: The length of the datavalue array.
 * @param[in]        NewSeed: Sets new CRC calculations.
 *                          - ENABLE: New seed sets and used for new calculation;
 *                          - DISABLE: Seed argument ignored, continues old calculation.
 * @param[in]        SeedValue: New seed if Newseed is enabled, else ignored.
 *
 * @return           16-bit calculation results.
*
*/
uint16 Crc_Calc16Bit(uint8 DataValue[],uint32 Length, 
                          Common_ControlStateType NewSeed, uint32 SeedValue);

/**
 * @brief            CRC calculation in 32 bits mode.
 *
 * @param[in]        DataValue: 8 bits of calculated data.
 * @param[in]        Length: The length of the datavalue array.
 * @param[in]        NewSeed: Sets new CRC calculations.
 *                          - ENABLE: New seed sets and used for new calculation;
 *                          - DISABLE: Seed argument ignored, continues old calculation.
 * @param[in]        SeedValue: New seed if NewSeed is enabled, else ignored.
 *
 * @return           32-bit calculation results.
*
*/
uint32 Crc_Calc32Bit(uint8 DataValue[],uint32 Length, 
                          Common_ControlStateType NewSeed, uint32 SeedValue);

/** @} end of group Public_FunctionDeclaration */

#endif /* CRC_DRV_H */
