/**************************************************************************************************/
/**
 * @file      : Crc_Drv.c
 * @brief     : CRC module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Crc_Drv.h"

/** @defgroup Private_TypeDefinition
 *  @{
 */
/** @} end of group Private_TypeDefinition*/

/** @defgroup Global_VariableDefinition
 *  @{
 */

 /** @} end of group Global_VariableDefinition */
 
/** @defgroup Private_MacroDefinition
 * @{ 
 */
#define CRC_WRITE_UNLOCK  (0x5c000000U)
#define CRC_WRITE_LOCK    (1U)
#define CRC_WRITE_DATA                                                         \
    (0U)         /*!< Writes to the CRC data register are data values. */
#define CRC_WRITE_SEED                                                         \
    (1U)         /*!< Writes to the CRC data register are seed values. */
#define CRC_WRITE_BIT_Y_BYTE_Y                                                 \
    (2U)         /*!< Both bits in bytes and bytes are transposed. */
#define CRC_WRITE_BIT_N_BYTE_Y                                                 \
    (3U)        /*!< Only bytes are transposed; no bits in a byte are transposed. */

/** @} end of group Private_MacroDefinition */

/** @defgroup Private_VariableDefinition
 * @{ 
 */

/*PRQA S 0303 ++*/
static Reg_Crc_WType   *const Crc_RegWPtr = (Reg_Crc_WType *) CRC_BASE_ADDR;
static Reg_Crc_BfType  *const Crc_RegBfPtr  = (Reg_Crc_BfType *) CRC_BASE_ADDR;
/*PRQA S 0303 --*/

/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 * @{ 
 */

/** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 * @{ 
 */

/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
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
Common_ResultStatusType Crc_Init(const Crc_ConfigType *ConfigPtr)
{
    Common_ResultStatusType Ret = COMMON_ERR;

    if(NULL_PTR != ConfigPtr)
    {
        if(CRC_WRITE_LOCK == Crc_RegBfPtr->CRC_CTRL.LOCK)
        {
            Crc_RegWPtr->CRC_CTRL = CRC_WRITE_UNLOCK;
        }
        Crc_RegBfPtr->CRC_CTRL.MODE = (uint32)(ConfigPtr->DataMode);
        Crc_RegBfPtr->CRC_CTRL.CR = (uint32)(ConfigPtr->ComplementRead);
    
        if((uint32)CRC_MODE_16BIT == Crc_RegBfPtr->CRC_CTRL.MODE)
        {
            Crc_RegBfPtr->CRC_POLY.LPHW = (uint32)(ConfigPtr->Poly);
        }
        else
        {
            Crc_RegWPtr->CRC_POLY = (uint32)(ConfigPtr->Poly);
        }

        if(CRC_WRITE_NO == ConfigPtr->WriteType)
        {
            Crc_RegBfPtr->CRC_CTRL.WT = CRC_WRITE_BIT_N_BYTE_Y;
        }
        else
        {
            Crc_RegBfPtr->CRC_CTRL.WT = CRC_WRITE_BIT_Y_BYTE_Y;
        }

        Crc_RegBfPtr->CRC_CTRL.RT = (uint32)(ConfigPtr->ReadType);
        Crc_RegBfPtr->CRC_CTRL.WS = (uint32)CRC_WRITE_SEED;
        Crc_RegWPtr->CRC_DATA = ConfigPtr->SeedValue;
        Crc_RegBfPtr->CRC_CTRL.LOCK = CRC_WRITE_LOCK;
        Ret = COMMON_SUCC;
    }
    return Ret;
}

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
uint16 Crc_Calc16Bit(uint8 DataValue[], uint32 Length, 
                          Common_ControlStateType NewSeed, uint32 SeedValue)
{
    uint16 CrcData = 0U;
    uint32 Index = 0U;
    uint32 ReadTypeVal = 0U;
    uint32 Data32 = 0U; 
    
    if(CRC_WRITE_LOCK == Crc_RegBfPtr->CRC_CTRL.LOCK)
    {
        Crc_RegWPtr->CRC_CTRL = CRC_WRITE_UNLOCK;
    }

    if(COMMON_ENABLE == NewSeed)
    {
        Crc_RegBfPtr->CRC_CTRL.WS = (uint32)CRC_WRITE_SEED;
        Crc_RegWPtr->CRC_DATA = SeedValue;
    }
    
    Crc_RegBfPtr->CRC_CTRL.WS = (uint32)CRC_WRITE_DATA;
    
    while(Length >= 4U)
    {
        Data32 = ((uint32)DataValue[Index])
            |((uint32)DataValue[Index+1UL]<<8U)
            |((uint32)DataValue[Index+2UL]<<16U)
            |((uint32)DataValue[Index+3UL]<<24U);
        *(uint32 volatile *)(&(Crc_RegWPtr->CRC_DATA)) = Data32;
        Index += 4U;
        Length -= 4U;
    }

    while(Length > 0U)
    {
        *(uint8 volatile *)(&(Crc_RegWPtr->CRC_DATA)) = *(uint8 *)(&DataValue[Index]);
        Length -= 1U;
        Index += 1U;
    }
    
    ReadTypeVal = Crc_RegBfPtr->CRC_CTRL.RT; 
    
    if((((uint32)CRC_READ_NO) == ReadTypeVal) ||
        (((uint32)CRC_READ_BIT_Y_BYTE_N) == ReadTypeVal))
    {
        CrcData = (uint16)(Crc_RegWPtr->CRC_DATA);
    }
    else
    {
        CrcData = (uint16)(Crc_RegWPtr->CRC_DATA>>16U);
    }
    Crc_RegBfPtr->CRC_CTRL.LOCK = CRC_WRITE_LOCK;
    return CrcData;
}

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
uint32 Crc_Calc32Bit(uint8 DataValue[], uint32 Length,
                          Common_ControlStateType NewSeed, uint32 SeedValue)
{
    uint32 Index = 0U;
    uint32 Data32 = 0U; 

    if(CRC_WRITE_LOCK == Crc_RegBfPtr->CRC_CTRL.LOCK)
    {
        Crc_RegWPtr->CRC_CTRL = CRC_WRITE_UNLOCK;
    }

    if(COMMON_ENABLE == NewSeed)
    {
        Crc_RegBfPtr->CRC_CTRL.WS = (uint32)CRC_WRITE_SEED;
        Crc_RegWPtr->CRC_DATA = SeedValue;
    }
    
    Crc_RegBfPtr->CRC_CTRL.WS = (uint32)CRC_WRITE_DATA;
    
    while(Length >= 4U)
    {
        Data32 = ((uint32)DataValue[Index])
            |((uint32)DataValue[Index+1UL]<<8U)
            |((uint32)DataValue[Index+2UL]<<16U)
            |((uint32)DataValue[Index+3UL]<<24U);
        *(uint32 volatile *)(&(Crc_RegWPtr->CRC_DATA)) = Data32;
        Index += 4U;
        Length -= 4U;
    }

    while(Length > 0U)
    {
        *(uint8 volatile *)(&(Crc_RegWPtr->CRC_DATA)) = *(uint8 *)(&DataValue[Index]);
        Length -= 1U;
        Index += 1U;
    }

    Crc_RegBfPtr->CRC_CTRL.LOCK = CRC_WRITE_LOCK;
    return Crc_RegWPtr->CRC_DATA;
}

/** @} end of group Public_FunctionDefinition */
