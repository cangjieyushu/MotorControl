/**************************************************************************************************/
/**
 * @file      : Z20K11xM_crc.c
 * @brief     : CRC module driver file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Z20K11xM_crc.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */
/** @defgroup CRC
 *  @brief CRC driver modules
 *  @{
 */

/** @defgroup CRC_Private_Type
 *  @{
 */

/** @} end of group CRC_Private_Type*/

/** @defgroup CRC_Private_Defines
 *  @{
 */
#define CRC_WRITE_DATA                                                          \
    (0U) /*!< Writes to the CRC data register are data values */
#define CRC_WRITE_SEED                                                          \
    (1U) /*!< Writes to the CRC data register are seed values */
#define CRC_WRITE_BIT_Y_BYTE_Y                                                 \
    (2U) /*!< Both bits in bytes and bytes are transposed */
#define CRC_WRITE_BIT_N_BYTE_Y                                                 \
    (3U) /*!< Only bytes are transposed; no bits in a byte are transposed */

/** @} end of group CRC_Private_Defines */
/** @defgroup CRC_Private_Variables
 *  @{
 */
/**
 *  @brief CRC address array
 */
/*PRQA S 0303 ++*/
static crc_reg_w_t *const crcRegWPtr = (crc_reg_w_t *)CRC_BASE_ADDR;
static crc_reg_t *const crcRegPtr = (crc_reg_t *)CRC_BASE_ADDR;
/*PRQA S 0303 --*/
/** @}end of group CRC_Private_Variables */

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
 * @param[in]    crcCfgStruct:  Pointer to a CRC configuration structure.
 *
 * @return       none.
 *
 */
void CRC_Init(const CRC_Config_t *crcCfgStruct)
{
    if (crcCfgStruct != NULL)
    {
        crcRegPtr->CRC_CTRL.MODE = (uint32_t)(crcCfgStruct->dataMode);
        crcRegPtr->CRC_CTRL.CR = (uint32_t)(crcCfgStruct->complementRead);
        if ((uint32_t)CRC_MODE_16BIT == crcRegPtr->CRC_CTRL.MODE)
        {
            crcRegPtr->CRC_POLY.LPHW = (uint32_t)(crcCfgStruct->poly);
        }
        else
        {
            crcRegWPtr->CRC_POLY = (uint32_t)(crcCfgStruct->poly);
        }

        if (CRC_WRITE_NO == crcCfgStruct->writeType)
        {
            crcRegPtr->CRC_CTRL.WT = CRC_WRITE_BIT_N_BYTE_Y;
        }
        else
        {
            crcRegPtr->CRC_CTRL.WT = CRC_WRITE_BIT_Y_BYTE_Y;
        }
        crcRegPtr->CRC_CTRL.RT = (uint32_t)(crcCfgStruct->readType);
        crcRegPtr->CRC_CTRL.WS = (uint32_t)CRC_WRITE_SEED;
        crcRegWPtr->CRC_DATA = crcCfgStruct->seedValue;
    }
}

/**
 * @brief            CRC calculation of 16 bits.
 *
 *
 * @param[in]        dataValue: 8 bits of calculated data
 * @param[in]        length: the length of the array
 * @param[in]        newSeed: Sets new CRC calculations
 *                          - ENABLE: New seed sets and used for new calculation
 *                          - DISABLE:Seed argument ignored, continues old
 * calculation
 * @param[in]        seedValue: new seed if newSeed is enabled,else ignored
 *
 * @return           16-bit calculation results
 *
 */

uint16_t CRC_CalcCRC16bit(uint8_t dataValue[], uint32_t length,
                          ControlState_t newSeed, uint32_t seedValue)
{
    uint16_t ret;
    uint32_t index = 0U;
    uint32_t readTypeVal;
    uint32_t data32;
    uint32_t len;

    len = length;
    if (ENABLE == newSeed)
    {
        crcRegPtr->CRC_CTRL.WS = (uint32_t)CRC_WRITE_SEED;
        crcRegWPtr->CRC_DATA = seedValue;
    }

    crcRegPtr->CRC_CTRL.WS = (uint32_t)CRC_WRITE_DATA;

    while (len >= 4U)
    {
        data32 = ((uint32_t)dataValue[index]) |
                 ((uint32_t)dataValue[index + 1UL] << 8U) |
                 ((uint32_t)dataValue[index + 2UL] << 16U) |
                 ((uint32_t)dataValue[index + 3UL] << 24U);
        *(uint32_t volatile *)(&(crcRegWPtr->CRC_DATA)) = data32;
        len -= 4U;
        index += 4U;
        
    }

    while (len > 0U)
    {
        *(uint8_t volatile *)(&(crcRegWPtr->CRC_DATA)) =
            *(uint8_t *)(&dataValue[index]);
        len -= 1U;
        index += 1U;
    }

    readTypeVal = crcRegPtr->CRC_CTRL.RT; /* Misra improvement */

    if ((((uint32_t)CRC_READ_NO) == readTypeVal) ||
        (((uint32_t)CRC_READ_BIT_Y_BYTE_N) == readTypeVal))
    {
        ret = (uint16_t)(crcRegWPtr->CRC_DATA);
    }
    else
    {
        ret = (uint16_t)(crcRegWPtr->CRC_DATA >> 16);
    }

    return ret;
}

/**
 * @brief            CRC calculation of 32 bits
 *
 *
 * @param[in]        dataValue: 8 bits of calculated data
 * @param[in]        length: the length of the array
 * @param[in]        newSeed: Sets new CRC calculations
 *                          - ENABLE: New seed sets and used for new calculation
 *                          - DISABLE:Seed argument ignored, continues old
 * calculation
 * @param[in]        seedValue: new seed if newSeed is enabled,else ignored
 *
 * @return           32-bit calculation results
 *
 */
uint32_t CRC_CalcCRC32bit(uint8_t  dataValue[], uint32_t length,
                          ControlState_t newSeed, uint32_t seedValue)
{
    uint32_t index = 0U;
    uint32_t data32;
    uint32_t len;

    len = length;

    if (ENABLE == newSeed)
    {
        crcRegPtr->CRC_CTRL.WS = (uint32_t)CRC_WRITE_SEED;
        crcRegWPtr->CRC_DATA = seedValue;
    }

    crcRegPtr->CRC_CTRL.WS = (uint32_t)CRC_WRITE_DATA;

    while (len >= 4U)
    {
        data32 = ((uint32_t)dataValue[index]) |
                 ((uint32_t)dataValue[index + 1UL] << 8U) |
                 ((uint32_t)dataValue[index + 2UL] << 16U) |
                 ((uint32_t)dataValue[index + 3UL] << 24U);
        *(uint32_t volatile *)(&(crcRegWPtr->CRC_DATA)) = data32;
        index += 4U;
        len -= 4U;
    }

    while (len > 0U)
    {
        *(uint8_t volatile *)(&(crcRegWPtr->CRC_DATA)) =
            *(uint8_t *)(&dataValue[index]);
        len -= 1U;
        index += 1U;
    }

    return crcRegWPtr->CRC_DATA;
}

/** @} end of group CRC_Public_FunctionDeclaration */

/** @} end of group CRC  */

/** @} end of group Z20K11X_Peripheral_Driver */
