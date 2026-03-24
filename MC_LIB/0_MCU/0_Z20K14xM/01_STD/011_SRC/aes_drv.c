/**************************************************************************************************/
/**
 * @file     aes_drv.c
 * @brief    AES module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "aes_drv.h"


/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup AES
 *  @brief AES driver modules
 *  @{
 */

/** @defgroup AES_Private_Type
 *  @{
 */

/**
 * @brief  AES operation mode configuration type
 *
 */
typedef enum
{
    AES_ECB_INIT       = 0x00U,          /*!< ECB init */
    AES_ECB_UPDATE     = 0x01U,          /*!< ECB update */
    AES_CBC_INIT       = 0x10U,          /*!< CBC init */
    AES_CBC_UPDATE     = 0x11U,          /*!< CBC update */
    AES_OFB_INIT       = 0x20U,          /*!< OFB init */
    AES_OFB_UPDATE     = 0x21U,          /*!< OFB update */
    AES_CTR_INIT       = 0x30U,          /*!< CTR init */
    AES_CTR_UPDATE     = 0x31U,          /*!< CTR update */
    AES_CFB_INIT       = 0x40U,          /*!< CFB init */
    AES_CFB_UPDATE     = 0x41U,          /*!< CFB update */
    AES_GCM_INIT       = 0x50U,          /*!< GCM init */
    AES_GCM_GHASH      = 0x51U,          /*!< GCM ghash */
    AES_GCM_UPDATE     = 0x52U,          /*!< GCM update */
    AES_GCM_FINISH_IV  = 0x53U,          /*!< GCM finish with iv */
    AES_GCM_FINISH     = 0x54U,          /*!< GCM finish */
    AES_CCM_INIT       = 0x60U,          /*!< CCM init */
    AES_CCM_MAC        = 0x61U,          /*!< CCM mac */
    AES_CCM_UPDATE     = 0x62U,          /*!< CCM update */
    AES_CCM_FINISH     = 0x63U,          /*!< CCM finish */
    AES_XTS_TWEAK_ENC  = 0x70U,          /*!< XTS tweak enc */
    AES_XTS_INIT       = 0x71U,          /*!< XTS init */
    AES_XTS_UPDATE     = 0x72U,          /*!< XTS update */
    AES_CMAC_INIT      = 0x80U,          /*!< CMAC init */
    AES_CMAC_UPDATE    = 0x81U,          /*!< CMAC update */
    AES_CMAC_FINISH_K1 = 0x82U,          /*!< CMAC finish K1 */
    AES_CMAC_FINISH_K2 = 0x83U           /*!< CMAC finish K2 */
} AES_OptMode_t;

/** @} end of group AES_Private_Type*/

/** @defgroup AES_Private_Defines
 *  @{
 */
#define AES_CMAC_PADDING_BYTE_MASK (0x80U)
#define AES_UTIL_REV(in, out)       __asm volatile("REV %0, %1" :"=r"((out)) :"r"((in)))
/** @} end of group AES_Private_Defines */

/** @defgroup AES_Private_Variables
 *  @{
 */
/*PRQA S 0303 ++*/
static aes_reg_t *const aesRegPtr = (aes_reg_t *) AES_BASE_ADDR;
static aes_reg_w_t *const aesRegWPtr = (aes_reg_w_t *) AES_BASE_ADDR;
/*PRQA S 0303 --*/

static FlagStatus_t aesCmacAlignedFlag = RESET;
static FlagStatus_t aesGcmAadEndFlag = SET;
static FlagStatus_t aesGcmDataAlignedFlag = RESET;
static FlagStatus_t aesCcmAadStartFlag = SET;
static FlagStatus_t aesCcmAadEndFlag = SET;
static FlagStatus_t aesCcmDataAlignedFlag = RESET;

static uint32_t aesGcmAadLen;
static uint32_t aesGcmDataLen;

/**
 * @brief AES ISR callBack Vector structure 
 */
static isr_cb_t * aesIsrCb = NULL;

/** @} end of group AES_Private_Variables */

/** @defgroup AES_Global_Variables
 *  @{
 */

/** @} end of group AES_Global_Variables */

/** @defgroup AES_Private_FunctionDeclaration
 *  @{
 */

void AES_DriverIRQHandler(void);
static void AES_CopyDataBlock(const uint8_t *dataInPtr, uint8_t *dataOutPtr, uint8_t dataLen);
static void AES_WriteKey(const uint8_t *keyPtr);
static void AES_WriteInitVector(const uint8_t *ivPtr);
static void AES_WriteGcmInitVector(const uint8_t *ivPtr);
static void AES_WriteData(const uint8_t *inputDataPtr);
static void AES_ReadData(uint8_t *outputDataPtr, uint32_t dataLen);
static void AES_Configure(AES_OptMode_t optMode, 
                          AES_CryptFunction_t functionMode, uint32_t blockSize);
static AES_ErrorStatus_t AES_StartOperation(void);
static AES_ErrorStatus_t AES_ProcessGcmCcmData(const uint8_t *inputDataPtr, AES_OptMode_t optMode, 
                                              AES_CryptFunction_t functionMode, uint32_t blockSize);
static AES_ErrorStatus_t AES_GetStatus(void);
static AES_ErrorStatus_t AES_Start96BitsIvGcm(const AES_Config_t *aesConfigStruct);
static AES_ErrorStatus_t AES_StartNon96BitsIvGcm(const AES_Config_t *aesConfigStruct);
static AES_ErrorStatus_t AES_CheckCcmLengthPara(uint32_t ivLen, uint32_t inputLen, uint32_t tagLen);
static AES_ErrorStatus_t AES_GenerateInitBlock(const AES_Config_t *aesConfigStruct, 
                                                uint32_t inputLen, uint32_t aadLen, 
                                                uint32_t tagLen, uint8_t *ctrB0Ptr, uint8_t *b0Ptr);
static bool AES_CompareData(const uint8_t *expectedDataPtr, 
                                            uint8_t *generatedDataPtr, uint32_t dataLen);

/** @} end of group AES_Private_FunctionDeclaration */

/** @defgroup AES_Private_Functions
 *  @{
 */

/**
 * @brief      AES done interrupt handle
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void AES_DriverIRQHandler(void)
{
    if ((1U == aesRegPtr->AES_STATUS.R) && (aesIsrCb != NULL))
    {
        aesIsrCb();
    }

    COMMON_DSB();
}

/**
 * @brief     Copy the data block.
 *
 * @param[in] dataInPtr: The pointer to the input data
 * @param[in] dataOutPtr: The pointer to the output data
 * @param[in] dataLen: Length in bytes to be copied
 *
 * @return    None
 * 
 */
static void AES_CopyDataBlock(const uint8_t *dataInPtr, uint8_t *dataOutPtr, uint8_t dataLen)
{
    uint8_t count;

    if(((NULL != dataInPtr) || (0U == dataLen)) && ((NULL != dataOutPtr) || (0U == dataLen)))
    {
        for (count = 0U; count < dataLen; count++)
        {
            dataOutPtr[count] = dataInPtr[count];
        }
    }
}

/**
 * @brief     Write the key for AES operation.
 *
 * @param[in] keyPtr: Pointer to the value of the key to be written into AES module
 *
 * @return    None
 * 
 */
static void AES_WriteKey(const uint8_t *keyPtr)
{
    volatile uint8_t *dataReg = (volatile uint8_t *)&(aesRegWPtr->AES_KEY0);
    uint8_t loop;

    if(NULL != keyPtr)
    {
        for(loop = 0U; loop < 16U; loop++)
        {
            dataReg[loop] = keyPtr[15U - loop];
        }
    }
}

/**
 * @brief     Write the initial vector for AES operation
 *
 * @param[in] ivPtr: Pointer to the value of the initial vector to be written into AES module
 *
 * @return    None
 * 
 */
static void AES_WriteInitVector(const uint8_t *ivPtr)
{
    volatile uint8_t *dataReg = (volatile uint8_t *)&(aesRegWPtr->AES_IV0);
    uint8_t loop;

    if(NULL != ivPtr)
    {
        for(loop = 0U; loop < 16U; loop++)
        {
            dataReg[loop] = ivPtr[15U - loop];
        }
    }
}

/**
 * @brief     Write the GCM initial vector for AES operation
 *
 * @param[in] ivPtr: Pointer to the value of the GCM initial vector to be written into AES module
 *
 * @return    None
 * 
 */
static void AES_WriteGcmInitVector(const uint8_t *ivPtr)
{
    volatile uint8_t *dataReg = (volatile uint8_t *)&(aesRegWPtr->AES_IV0);
    uint8_t loop;

    if(NULL != ivPtr)
    {
        for(loop = 0U; loop < 16U; loop++)
        {
            if (loop < 4U)
            {
                dataReg[loop] = 0U;
            }
            else
            {
                dataReg[loop] = ivPtr[15U - loop];
            }
        }
    }
}

/**
 * @brief     Write the input data for AES operation
 *
 * @param[in] inputDataPtr: Pointer to the value of the input data to be written into AES module
 *
 * @return    None
 */
static void AES_WriteData(const uint8_t *inputDataPtr)
{
    volatile uint8_t *dataReg = (volatile uint8_t *)&(aesRegWPtr->AES_DATA_I0);
    uint8_t loop;

    if(NULL != inputDataPtr)
    {
        /* Write the input data value into the AES data input registers */
        for(loop = 0U; loop < 16U; loop++)
        {
            dataReg[loop] = inputDataPtr[15U - loop];
        }
    }
}

/**
 * @brief     Read the output data of AES operation
 *
 * @param[in] outputDataPtr: Pointer to the value of the output data
 * @param[in] dataLen: Data length in bytes
 *
 * @return    None
 * 
 */
static void AES_ReadData(uint8_t *outputDataPtr, uint32_t dataLen)
{
    uint8_t loop;
    uint32_t tempData[4U] = {0U};

    if(NULL != outputDataPtr)
    {
        AES_UTIL_REV(aesRegWPtr->AES_DATA_O3, tempData[0]);
        AES_UTIL_REV(aesRegWPtr->AES_DATA_O2, tempData[1]);
        AES_UTIL_REV(aesRegWPtr->AES_DATA_O1, tempData[2]);
        AES_UTIL_REV(aesRegWPtr->AES_DATA_O0, tempData[3]);

        /* Read the output data value from the AES data output registers */
        for(loop = 0U; loop < dataLen; loop++)
        {
            outputDataPtr[loop] = ((uint8_t*)tempData)[loop];
        }
    }
}

/**
 * @brief     Configure the AES operation
 *
 * @param[in] optMode: AES operation mode
 * @param[in] functionMode: AES encryption or decryption
 * @param[in] blockSize: Block size in bits
 *
 * @return    None
 * 
 */
static void AES_Configure(AES_OptMode_t optMode, 
                          AES_CryptFunction_t functionMode, uint32_t blockSize)
{
    uint32_t configData = 0U;

    configData = ((uint32_t)functionMode & 1U) | (((uint32_t)optMode & 0xFFU) << 8U) | 
                                                                    ((blockSize & 0xFFU) << 16U);
    aesRegWPtr->AES_CONFIG = configData;
}

/**
 * @brief     Start an AES operation
 *
 * @param[in] None
 *
 * @return    AES_ErrorStatus_t
 * 
 */
static AES_ErrorStatus_t AES_StartOperation(void)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;

    if (1U != aesRegPtr->AES_STATUS.R)
    {
        ret = AES_STATUS_BUSY_ERROR;
    }
    else
    {
        /* Start the AES operation */
        aesRegWPtr->AES_CONTROL = 1U;

        /* Get AES module status */
        ret = AES_GetStatus();
    }

    return ret;
}

/**
 * @brief     Process GCM or CCM data
 *
 * @param[in] inputDataPtr: Pointer to the data to be processed
 * @param[in] optMode: AES operation mode
 * @param[in] functionMode: AES encryption or decryption
 * @param[in] blockSize: Block size in bits
 * 
 * @return    AES_ErrorStatus_t
 * 
 */
static AES_ErrorStatus_t AES_ProcessGcmCcmData(const uint8_t *inputDataPtr, AES_OptMode_t optMode, 
                                               AES_CryptFunction_t functionMode, uint32_t blockSize)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;

    /* Write the input data for the operation */
    AES_WriteData(inputDataPtr);

    /* Setup the configuration for the operation */
    AES_Configure(optMode, functionMode, blockSize);

    /* Trigger the start of the operation */
    ret = AES_StartOperation();

    return ret;
}

/**
 * @brief     Get the execution status of an AES operation
 *
 * @param[in] None
 *
 * @return    AES_ErrorStatus_t
 * 
 */
static AES_ErrorStatus_t AES_GetStatus(void)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;
    uint32_t timeoutValue = 0U;

    while((0U == aesRegPtr->AES_STATUS.R) && (timeoutValue < AES_TIMEOUT_WAIT_CNT))
    {
        timeoutValue++;
    }
    
    if(1U == aesRegPtr->AES_STATUS.R)
    {
        ret = (AES_ErrorStatus_t)aesRegPtr->AES_STATUS.ERR;
    }
    else
    {
        ret = AES_STATUS_TIMEOUT;
    }

    return ret;
}

/**
 * @brief      Initialize an GCM operation with 96-bits initial vector
 *
 * @param[in]  aesConfigStruct: The cipher configuration, where ivLen is length of 
 *                              initial vector in bits.
 *
 * @return     AES_ErrorStatus_t
 * 
 */
static AES_ErrorStatus_t AES_Start96BitsIvGcm(const AES_Config_t *aesConfigStruct)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;

    if((NULL != aesConfigStruct->keyPtr) && (NULL != aesConfigStruct->ivPtr))
    {
        /* Write the key for the operation */
        AES_WriteKey(aesConfigStruct->keyPtr);

        /* Write the GCM initial vector for the operation */
        AES_WriteGcmInitVector(aesConfigStruct->ivPtr);

        /* Setup the configuration for the operation */
        AES_Configure(AES_GCM_INIT, aesConfigStruct->functionMode, 0x80U);

        /* Start an AES operation */
        ret = AES_StartOperation();
    }
    else
    {
        ret = AES_STATUS_INPUT_ERROR;
    }

    return ret; 
}

/**
 * @brief      Initialize an GCM operation with non-96-bits initial vector
 *
 * @param[in]  aesConfigStruct: The cipher configuration, where ivLen is length of 
 *                              initial vector in bits.
 *
 * @return     AES_ErrorStatus_t
 * 
 */
static AES_ErrorStatus_t AES_StartNon96BitsIvGcm(const AES_Config_t *aesConfigStruct)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;
    uint32_t countBlock;
    uint8_t loop;
    uint32_t blockNum = (aesConfigStruct->ivLen) / 128U;
    uint32_t lastBlockLength = (uint8_t)((aesConfigStruct->ivLen) % 128U);
    uint8_t bytesNum = (uint8_t)(lastBlockLength / 8U);
    uint8_t lastByteLength = (uint8_t)(lastBlockLength % 8U);
    uint8_t lastDataCopy[16U] = {0U};
    uint8_t lenAsInput[16U] = {0U};

    if((NULL != aesConfigStruct->keyPtr) && (NULL != aesConfigStruct->ivPtr) && 
                                (96U != aesConfigStruct->ivLen) && (0U != aesConfigStruct->ivLen))
    {
        /* Write the key for the operation */
        AES_WriteKey(aesConfigStruct->keyPtr);
        /* Setup the configuration for the operation */
        AES_Configure(AES_GCM_INIT, aesConfigStruct->functionMode, 0x80U);
        ret =  AES_StartOperation();
        
        if (AES_STATUS_NO_ERR == ret)
        {
            for(countBlock = 0U; countBlock < blockNum; countBlock++)
            {
                ret = AES_ProcessGcmCcmData(&aesConfigStruct->ivPtr[16U * countBlock], 
                                            AES_GCM_GHASH, aesConfigStruct->functionMode, 0x80U);
                if(AES_STATUS_NO_ERR != ret)
                {
                    break;
                }
            }

            if((AES_STATUS_NO_ERR == ret) && (0U != lastBlockLength))
            {
                /* Copy the last data block */
                AES_CopyDataBlock(&aesConfigStruct->ivPtr[16U * countBlock], 
                                                                    lastDataCopy, bytesNum);
                lastDataCopy[bytesNum] = aesConfigStruct->ivPtr[16U * countBlock + bytesNum] & 
                                                                    ((1U << lastByteLength) - 1U);
                ret = AES_ProcessGcmCcmData(lastDataCopy, AES_GCM_GHASH, 
                                                            aesConfigStruct->functionMode, 0x80U);
            }

            if(AES_STATUS_NO_ERR == ret)
            {
                /* Process length data via GHASH */
                for (loop = 12U; loop < 16U; loop++)
                {
                    lenAsInput[loop] = ((const uint8_t*)(&aesConfigStruct->ivLen))[15U - loop];
                }
                ret = AES_ProcessGcmCcmData(lenAsInput, AES_GCM_GHASH, 
                                                            aesConfigStruct->functionMode, 0x80U);
            }

            if(AES_STATUS_NO_ERR == ret)
            {
                /* Setup the configuration for the operation */
                AES_Configure(AES_GCM_FINISH_IV, aesConfigStruct->functionMode, 0x80U);

                /* Trigger the start of the operation */
                ret = AES_StartOperation();
            }
        }
    }
    else
    {
        ret = AES_STATUS_INPUT_ERROR;
    }

    return ret;
}

/**
 * @brief     Check length parameters for CCM to generate B0 and CtrB0 
 *
 * @param[in] ivLen: The length of the IV in bytes
 * @param[in] inputLen: The length of the input data in bytes
 * @param[in] tagLen: The length of the tag in bytes
 *
 * @return    AES_ErrorStatus_t   

 */
static AES_ErrorStatus_t AES_CheckCcmLengthPara(uint32_t ivLen, uint32_t inputLen, uint32_t tagLen)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;
    uint32_t tempLen = 15U - ivLen;

    /* ivLen is an element of   {7, 8, 9, 10, 11, 12, 13}
     * tagLen is an element of  {4, 6, 8, 10, 12, 14, 16}
     */
    if ((ivLen < 7U) || (ivLen > 13U))
    {
        ret = AES_STATUS_INPUT_ERROR;
    }

    if (((tempLen == 2U) && (inputLen > 0xFFFFU)) || ((tempLen == 3U) && (inputLen > 0xFFFFFFU)))
    {
        ret = AES_STATUS_INPUT_ERROR;
    }

    if ((tagLen < 4U) || (tagLen > 16U))
    {
        ret = AES_STATUS_INPUT_ERROR;
    }

    return ret;
}

/**
 * @brief      Generate initial CtrB0 and B0 block for CCM
 *
 * @param[in]  aesConfigStruct: The cipher configuration, where ivLen is length of 
 *                              initial vector in bytes.
 * @param[in]  inputLen: Total length of the input data in bytes
 * @param[in]  aadLen: Total length of the AAD data in bytes
 * @param[in]  tagLen: Tag length in bytes
 * @param[out] ctrB0Ptr: Pointer to the CtrB0 Block
 * @param[out] b0Ptr: Pointer to the B0 Block
 *
 * @return     AES_ErrorStatus_t
 * 
 */
static AES_ErrorStatus_t AES_GenerateInitBlock(const AES_Config_t *aesConfigStruct, 
                                                uint32_t inputLen, uint32_t aadLen, 
                                                uint32_t tagLen, uint8_t *ctrB0Ptr, uint8_t *b0Ptr)
{
    uint8_t loop;
    AES_ErrorStatus_t ret = AES_CheckCcmLengthPara(aesConfigStruct->ivLen, inputLen, tagLen);

    if(AES_STATUS_NO_ERR == ret)
    {
        b0Ptr[0U] = (14U - (uint8_t)aesConfigStruct->ivLen) | 
                            ((((uint8_t)tagLen - 2U) / 2U) << 3U) | ((uint8_t)(aadLen > 0U) << 6U);
        ctrB0Ptr[0U] = (14U - (uint8_t)aesConfigStruct->ivLen);

        for (loop = 0U; loop < aesConfigStruct->ivLen; loop++)
        {
            b0Ptr[loop + 1U] = aesConfigStruct->ivPtr[loop];
            ctrB0Ptr[loop + 1U] = aesConfigStruct->ivPtr[loop];
        }

        for (loop = 15U; loop > aesConfigStruct->ivLen; loop--)
        {
            b0Ptr[loop] = (uint8_t)((inputLen >> (8U * (15U - loop))) & 0xFFU);
        }
    }

    return ret;
}                

/**
 * @brief      Compare generated data by AES with expected data
 *
 * @param[in]  expectedDataPtr: Pointer to the expected data
 * @param[in]  generatedDataPtr: Pointer to the generated data
 * @param[in]  dataLen: Compare length in bytes
 *
 * @return     bool
 * @retval     true or false
 */
static bool AES_CompareData(const uint8_t *expectedDataPtr, 
                                            uint8_t *generatedDataPtr, uint32_t dataLen)
{
    uint32_t count;
    bool ret = true;

    if((NULL != expectedDataPtr) && (NULL != generatedDataPtr))
    {
        for(count = 0U; count < dataLen ; count++)
        {
            /*8-bitwise compare*/
            if (0U != (generatedDataPtr[count] ^ expectedDataPtr[count]))
            {
                ret = false;
                break;
            }
        }
    }
    else
    {
        ret = false;
    }

    return ret;
}

/** @} end of group AES_Private_Functions */

/** @defgroup AES_Public_Functions
 *  @{
 */

/**
 * @brief      AES Install callback function
 *
 * @param[in]  cbFun: indicate callback function
 *
 * @return    none
 *
 */ 
void AES_InstallCallBackFunc(isr_cb_t * const cbFun)
{
    aesIsrCb = cbFun;
}

/**
 * @brief      Initialize a CMAC operation
 *
 * @param[in]  aesConfigStruct: The cipher configuration.
 *
 * @return     None
 * 
 */
void AES_StartCmac(const AES_Config_t *aesConfigStruct)
{
    if(NULL != aesConfigStruct->keyPtr)
    {
        aesCmacAlignedFlag = SET;

        /* Write the key for the operation */
        AES_WriteKey(aesConfigStruct->keyPtr);

        /* Setup the configuration for the operation */
        AES_Configure(AES_CMAC_INIT, AES_ENCRYPTION, 0x80U);
    }
}

/**
 * @brief      Update data for CMAC operation
 *
 * @param[in]  inputDataPtr: Pointer to the input data block, which should be in 
                             BIG endian mode( NULL pointer will not be supported ).
 * @param[in]  inputLen: Data length in bytes. 
 * 
 * @return     AES_ErrorStatus_t
 * 
 * @note       Data that are not 16-bytes aligned is supported only for the last update 
 *             operation, and there shall not be new input data in finish operation in that case
 */
AES_ErrorStatus_t AES_UpdateCmac(const uint8_t *inputDataPtr, uint32_t inputLen)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;
    uint32_t blockNum = (inputLen / 16U);
    uint32_t countBlock;
    uint8_t lastDataLength = (uint8_t)(inputLen % 16U);
    uint8_t lastDataCopy[16U] = {0U};

    if ((RESET == aesCmacAlignedFlag) || (NULL == inputDataPtr) || (0U == inputLen))
    {
        ret = AES_STATUS_INPUT_ERROR;
    }
    else
    {
        for(countBlock = 0U; countBlock < blockNum; countBlock++)
        {
            ret = AES_StartOperation();
            if(AES_STATUS_NO_ERR != ret)
            {
                break;
            }
            AES_WriteData(&inputDataPtr[16U * countBlock]);
            AES_Configure(AES_CMAC_UPDATE, AES_ENCRYPTION, 0x80U);
        }

        if((AES_STATUS_NO_ERR == ret) && (0U != lastDataLength))
        {
            /* Set CMAC aligned flag to RESET, indicating that no CMAC data can be fed any more */
            aesCmacAlignedFlag = RESET;

            ret = AES_StartOperation();
            if(AES_STATUS_NO_ERR == ret)
            {
                AES_CopyDataBlock(&inputDataPtr[16U * countBlock], lastDataCopy, lastDataLength);
                lastDataCopy[lastDataLength] = AES_CMAC_PADDING_BYTE_MASK;
                AES_WriteData(lastDataCopy);
            }
            AES_Configure(AES_CMAC_UPDATE, AES_ENCRYPTION, 0x80U);
        }
    }
    return ret;
}

/**
 * @brief      Finish a CMAC operation
 *
 * @param[in]  inputDataPtr: Pointer to the input data block, which should be in BIG endian mode
 * @param[in]  inputLen: Data length in bytes
 * @param[out] macPtr: Pointer to the generated MAC
 * @param[in]  macLen: Length of the required MAC in bytes
 *
 * @return     AES_ErrorStatus_t
 * 
 */
AES_ErrorStatus_t AES_FinishCmac(const uint8_t *inputDataPtr, uint32_t inputLen, 
                                 uint8_t *macPtr, uint32_t macLen)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;
    AES_OptMode_t optMode;

    if((16U >= macLen) && (NULL != macPtr) && (0U != macLen))
    {
        if (0U != inputLen)
        {
            ret = AES_UpdateCmac(inputDataPtr, inputLen);
        }

        if (AES_STATUS_NO_ERR == ret)
        {
            if (SET == aesCmacAlignedFlag)
            {
                optMode = AES_CMAC_FINISH_K1;
            }
            else
            {
                optMode = AES_CMAC_FINISH_K2;
            }

            AES_Configure(optMode, AES_ENCRYPTION, 0x80U);
            ret = AES_StartOperation();
            if(AES_STATUS_NO_ERR == ret)
            {
                /* Read out the MAC output value */
                AES_ReadData(macPtr, macLen);
            }
        }
    }
    else
    {
        ret = AES_STATUS_INPUT_ERROR;
    }
    
    return ret;
}

/**
 * @brief      CMAC generation operation
 *
 * @param[in]  aesConfigStruct: The cipher configuration.
 * @param[in]  message: Pointer to the given message, which should be in 
                        BIG endian mode( NULL pointer will not be supported ).
 * @param[in]  messageLen: Length of the whole given message for CMAC operation in bytes
 * @param[out] macPtr: Pointer to the generated MAC
 * @param[in]  macLen: Length of the required MAC in bytes
 *
 * @return     AES_ErrorStatus_t
 * 
 */                                 
AES_ErrorStatus_t AES_GenerateCmac(const AES_Config_t *aesConfigStruct, const uint8_t *message, 
                                   uint32_t messageLen, uint8_t *macPtr, uint32_t macLen)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;

    /* Init the CMAC operation */
    AES_StartCmac(aesConfigStruct);
    
    /* Update data for CMAC operation */
    ret = AES_UpdateCmac(message, messageLen);

    if(AES_STATUS_NO_ERR == ret)
    {
        /* Finish the CMAC operation */
        ret = AES_FinishCmac(NULL, 0U, macPtr, macLen);
    } 
   
    return ret;
}

/**
 * @brief      CMAC verification operation
 * 
 * @param[in]  aesConfigStruct: The cipher configuration.
 * @param[in]  message: Pointer to the given message, which should be in 
                        BIG endian mode( NULL pointer will not be supported ).
 * @param[in]  messageLen: Length of the whole given message for CMAC operation in bytes
 * @param[in]  macPtr: Pointer to the MAC for verification
 * @param[in]  macLen: Length of the MAC to be verified in bytes
 * @param[out] verifyResult: Pointer to space storing the result of the MAC verify operation
 *
 * @return     AES_ErrorStatus_t
 * 
 */
AES_ErrorStatus_t AES_VerifyCmac(const AES_Config_t *aesConfigStruct, const uint8_t *message, 
                                 uint32_t messageLen, const uint8_t *macPtr, 
                                 uint32_t macLen, uint32_t *verifyResult)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;
    uint8_t generatedMac[16U] = {0U};

    /*Generate the MAC data*/
    ret = AES_GenerateCmac(aesConfigStruct, message, messageLen, generatedMac, macLen);

    if(AES_STATUS_NO_ERR == ret)
    {
        /*Verify the MAC data*/
        *verifyResult = (uint32_t)AES_CompareData(macPtr, generatedMac, macLen);
    }
    
    return ret;
}

/**
 * @brief      Initialize an encrypt or decrypt operation
 *
 * @param[in]  aesConfigStruct: The cipher configuration.
 *
 * @return     AES_ErrorStatus_t
 * 
 */
AES_ErrorStatus_t AES_StartCrypt(const AES_Config_t *aesConfigStruct)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;
    uint8_t optMode;

    if((NULL == aesConfigStruct) || (NULL == aesConfigStruct->keyPtr) || 
                ((AES_ECB != aesConfigStruct->algorithmMode) && (NULL == aesConfigStruct->ivPtr)))
    {
        ret = AES_STATUS_INPUT_ERROR;
    }
    else
    {
        optMode = ((uint8_t)(aesConfigStruct->algorithmMode) << 4U);

        /* Write the key for the operation */
        AES_WriteKey(aesConfigStruct->keyPtr);
        /* Write the initial vector for the operation(not needed for ECB mode) */
        if(AES_ECB_INIT != (AES_OptMode_t)optMode)
        {
            AES_WriteInitVector(aesConfigStruct->ivPtr);
        }
        /* Setup the configuration for the operation */
        AES_Configure((AES_OptMode_t)optMode, aesConfigStruct->functionMode, 0x80U);

        if(AES_XTS_TWEAK_ENC == (AES_OptMode_t)optMode)
        {
            ret = AES_StartOperation();
            if (AES_STATUS_NO_ERR == ret)
            {
                /* Write XTS data key for the operation */
                AES_WriteKey(&aesConfigStruct->keyPtr[16U]);
                /* Setup the configuration for XTS operation */
                AES_Configure(AES_XTS_INIT, aesConfigStruct->functionMode, 0x80U);
            }
        }
    }

    return ret;
}

/**
 * @brief      Update data for an encrypt or decrypt operation
 *
 * @param[in]  aesConfigStruct: The cipher configuration.
 * @param[in]  inputDataPtr: Pointer to the input data block, which should be in BIG endian mode
 * @param[in]  inputLen: Data length in bytes, it should be 16 bytes aligned
 * @param[out] outputDataPtr: Pointer to the output data block
 *
 * @return     AES_ErrorStatus_t
 * 
 */
AES_ErrorStatus_t AES_UpdateCrypt(const AES_Config_t *aesConfigStruct, const uint8_t *inputDataPtr, 
                                  uint32_t inputLen, uint8_t *outputDataPtr)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;
    uint8_t optMode;
    uint32_t blockNum;
    uint32_t countBlock;

    if((NULL != aesConfigStruct) && (0U != inputLen) && 
                                    (NULL != inputDataPtr) && (NULL != outputDataPtr))
    {
        optMode = (((uint8_t)aesConfigStruct->algorithmMode << 4U) + 1U);
        if (AES_XTS == aesConfigStruct->algorithmMode)
        {
            /* Set operation mode to XTS_UPDATE */
            optMode += 1U;
        }

        if(0U == (inputLen % 16U))
        {
            blockNum = inputLen / 16U;
            /* Process the input data */
            for(countBlock = 0U; countBlock < blockNum; countBlock++)
            {
                /* Write the input data for the operation */
                AES_WriteData(&inputDataPtr[16U * countBlock]);
                /* Trigger the start of the operation */
                ret = AES_StartOperation();
                if(AES_STATUS_NO_ERR == ret)
                {
                    /* Read out the output value */
                    AES_ReadData(&outputDataPtr[16U * countBlock], 16U);
                    /* Setup the configuration for the next operation */
                    AES_Configure((AES_OptMode_t)optMode, aesConfigStruct->functionMode, 0x80U);
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            ret = AES_STATUS_INPUT_ERROR;
        }
    }
    else
    {
        ret = AES_STATUS_INPUT_ERROR;
    }
    return ret;
}

/**
 * @brief      AES encrypt or decrypt operation
 *
 * @param[in]  aesConfigStruct: The cipher configuration.
 * @param[in]  inputDataPtr: Pointer to the input data block, which should be in BIG endian mode
 * @param[in]  inputLen: Data length in bytes, it should be 16 bytes aligned
 * @param[out] outputDataPtr: Pointer to the output data block
 *
 * @return     AES_ErrorStatus_t
 * 
 */
AES_ErrorStatus_t AES_Crypt(const AES_Config_t *aesConfigStruct, const uint8_t *inputDataPtr, 
                            uint32_t inputLen, uint8_t *outputDataPtr)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;

    ret = AES_StartCrypt(aesConfigStruct);

    if (AES_STATUS_NO_ERR == ret)
    {
        ret = AES_UpdateCrypt(aesConfigStruct, inputDataPtr, inputLen, outputDataPtr);
    }

    return ret;
}

/**
 * @brief      Initialize an GCM operation
 *
 * @param[in]  aesConfigStruct: The cipher configuration, where ivLen is length of 
 *                              initial vector in bits.
 *
 * @return     AES_ErrorStatus_t
 * 
 */
AES_ErrorStatus_t AES_StartGcm(const AES_Config_t *aesConfigStruct)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;

    aesGcmAadEndFlag = RESET;
    aesGcmDataAlignedFlag = SET;

    aesGcmAadLen = 0U;
    aesGcmDataLen = 0U;

    if (96U == aesConfigStruct->ivLen)
    {
        ret = AES_Start96BitsIvGcm(aesConfigStruct);
    }
    else
    {
        ret = AES_StartNon96BitsIvGcm(aesConfigStruct);
    }
    
    return ret;
}

/**
 * @brief      Update GCM AAD data
 *
 * @param[in]  aesConfigStruct: The cipher configuration.
 * @param[in]  aadDataPtr: Pointer to the AAD data block, which should be in BIG endian mode
 * @param[in]  aadLen: AAD data length in bytes
 *
 * @return     AES_ErrorStatus_t
 * 
 * @note       1) AAD data that are not 16-bytes aligned is supported only for 
 *                the last update AAD operation, and there shall not be new AAD data in 
 *                finish operation in that case.
 *             2) This GCM AAD update function (also in GCM finish function) cannot be 
 *                called again after AES_UpdateGcmData is called.
 */
AES_ErrorStatus_t AES_UpdateGcmAad(const AES_Config_t *aesConfigStruct, const uint8_t *aadDataPtr, 
                                   uint32_t aadLen)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;
    uint32_t blockNum = aadLen / 16U;
    uint32_t countBlock;
    uint8_t lastDataLength = (uint8_t)(aadLen % 16U);
    uint8_t lastDataCopy[16U] = {0U};

    if ((SET == aesGcmAadEndFlag) || (NULL == aesConfigStruct) ||
                                        (NULL == aadDataPtr) || (0U == aadLen))
    {
        ret = AES_STATUS_INPUT_ERROR;
    }
    else
    {
        /* Process the AAD data */
        for(countBlock = 0U; countBlock < blockNum; countBlock++)
        {
            aesGcmAadLen += 16U;

            ret = AES_ProcessGcmCcmData(&aadDataPtr[16U * countBlock], AES_GCM_GHASH, 
                                            aesConfigStruct->functionMode, 0x80U);
            if(AES_STATUS_NO_ERR != ret)
            {
                break;
            }
        }
        
        if((AES_STATUS_NO_ERR == ret) && (0U != lastDataLength))
        {
            /* Set AAD end flag to SET, indicating that no AAD data can be fed any more */
            aesGcmAadEndFlag = SET;

            aesGcmAadLen += lastDataLength;

            /* Copy the last data block */
            AES_CopyDataBlock(&aadDataPtr[16U * countBlock], lastDataCopy, lastDataLength);

            ret = AES_ProcessGcmCcmData(lastDataCopy, AES_GCM_GHASH, 
                                                            aesConfigStruct->functionMode, 0x80U);
        }
    }

    return ret;
}
                                                   
/**
 * @brief      Update GCM message data
 *
 * @param[in]  aesConfigStruct: The cipher configuration.
 * @param[in]  inputDataPtr: Pointer to the input data block, which should be in BIG endian mode
 * @param[in]  inputLen: Data length in bytes
 * @param[out] outputDataPtr: Pointer to the output data block
 *
 * @return     AES_ErrorStatus_t
 * 
 * @note       1) GCM data that are not 16-bytes aligned is supported only for the last update 
 *                operation, and there shall not be new input data in finish operation in that case.
 *             2) Once this GCM data update function is called, it means that all GCM AAD data has 
 *                been updated and the function AES_UpdateGcmAad cannot be called again.
 *             3) In the case of note 2), AAD data should no longer be transferred to the 
 *                function AES_FinishGcm (aadDataPtr should be NULL pointer).
 */
AES_ErrorStatus_t AES_UpdateGcmData(const AES_Config_t *aesConfigStruct, 
                                    const uint8_t *inputDataPtr, uint32_t inputLen, 
                                    uint8_t *outputDataPtr)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;
    uint32_t blockNum = (inputLen / 16U);
    uint32_t countBlock;
    uint8_t lastDataLength = (uint8_t)(inputLen % 16U);
    uint8_t lastDataCopy[16U] = {0U};

    /* Set AAD end flag to SET, indicating that no AAD data can be fed any more */
    aesGcmAadEndFlag = SET;
    
    if ((RESET == aesGcmDataAlignedFlag) || (NULL == aesConfigStruct) ||
                            (NULL == inputDataPtr) || (NULL == outputDataPtr) || (0U == inputLen))
    {
        ret = AES_STATUS_INPUT_ERROR;
    }
    else
    {
        /* Process the input data */
        for(countBlock = 0U; countBlock < blockNum; countBlock++)
        {
            aesGcmDataLen += 16U;
            
            ret = AES_ProcessGcmCcmData(&inputDataPtr[16U * countBlock], AES_GCM_UPDATE, 
                                            aesConfigStruct->functionMode, 0x80U);
            if(AES_STATUS_NO_ERR == ret)
            {
                /* Read out the output value */
                AES_ReadData(&outputDataPtr[16U * countBlock], 16U);
            }
            else
            {
                break;
            }
        }

        if((AES_STATUS_NO_ERR == ret) && (0U != lastDataLength))
        {
            /* Set data aligned flag to RESET, indicating that no GCM data can be fed any more */
            aesGcmDataAlignedFlag = RESET;

            aesGcmDataLen += lastDataLength;

            /*Copy the last data block*/
            AES_CopyDataBlock(&inputDataPtr[16U * countBlock], lastDataCopy, lastDataLength);

            ret = AES_ProcessGcmCcmData(lastDataCopy, AES_GCM_UPDATE, 
                                    aesConfigStruct->functionMode, 8U * (uint32_t)lastDataLength);
            if(AES_STATUS_NO_ERR == ret)
            {
                /* Read out the output value */
                AES_ReadData(&outputDataPtr[16U * countBlock], lastDataLength);
            }
        }
    }

    return ret;
}

/**
 * @brief     Finish a GCM operation and read out the text data and tag
 *
 * @param[in]  aesConfigStruct: The cipher configuration.
 * @param[in]  inputDataPtr: Pointer to the input data, which should be in BIG endian mode
 * @param[in]  inputLen: Length of the input data in bytes
 * @param[in]  aadDataPtr: Pointer to the AAD data, which should be in BIG endian mode
 * @param[in]  aadLen: Length of the AAD data in bytes
 * @param[out] outputDataPtr: Pointer to the output data
 * @param[out] tagPtr: Pointer to the calculated tag
 * @param[in]  tagLen: Tag length in bytes
 *
 * @return     AES_ErrorStatus_t
 * 
 * @note       1) Once the function AES_UpdateGcmData is called, AAD data should no longer be 
 *                transferred to this GCM finish function(aadDataPtr should be NULL pointer).
 *             2) The inputDataPtr transferred to this function must be the remaining part of the 
    *             data that has not been processed by AES_UpdateGcmData, rather than the complete 
    *             GCM input data (inputLen must also be the length of the remaining data).
 */
AES_ErrorStatus_t AES_FinishGcm(const AES_Config_t *aesConfigStruct,     
                                const uint8_t *inputDataPtr, uint32_t inputLen, 
                                const uint8_t *aadDataPtr, uint32_t aadLen,
                                uint8_t *outputDataPtr, uint8_t *tagPtr, uint32_t tagLen)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;
    uint8_t lenAsInput[16U] = {0U};
    uint8_t loop;
    uint64_t aadLen_bits;
    uint64_t msgLen_bits;

    if((16U >= tagLen) && (NULL != tagPtr) && (0U != tagLen))
    {
        /* process AAD data */
        if (0U != aadLen)
        {
            ret = AES_UpdateGcmAad(aesConfigStruct, aadDataPtr, aadLen);
        }

        /* process input text data */
        if((0U != inputLen) && (AES_STATUS_NO_ERR == ret))
        {
            ret = AES_UpdateGcmData(aesConfigStruct, inputDataPtr, inputLen, outputDataPtr);
        }

        if(AES_STATUS_NO_ERR == ret)
        {
            aadLen_bits = ((uint64_t)aesGcmAadLen * 8U);
            msgLen_bits = ((uint64_t)aesGcmDataLen * 8U);

            /* Process length data via GHASH */
            for (loop = 0U; loop < 8U; loop++)
            {
                lenAsInput[loop] = ((uint8_t*)(&aadLen_bits))[7U - loop];
                lenAsInput[loop + 8U] = ((uint8_t*)(&msgLen_bits))[7U - loop];
            }

            ret = AES_ProcessGcmCcmData(lenAsInput, AES_GCM_GHASH, 
                                                            aesConfigStruct->functionMode, 0x80U);

            if(AES_STATUS_NO_ERR == ret)
            {
                AES_Configure(AES_GCM_FINISH, aesConfigStruct->functionMode, 0x80U);

                ret = AES_StartOperation();
                if(AES_STATUS_NO_ERR == ret)
                {
                    /* Read out the tag output value */
                    AES_ReadData(tagPtr, tagLen);
                }
            }
        }
    }
    else
    {
        ret = AES_STATUS_INPUT_ERROR;
    }

    return ret;
}

/**
 * @brief      GCM operation
 *
 * @param[in]  aesConfigStruct: The cipher configuration, where ivLen is length of 
 *                              initial vector in bits.
 * @param[in]  inputDataPtr: Pointer to the input data, which should be in BIG endian mode
 * @param[in]  inputLen: Length of the input data in bytes
 * @param[in]  aadDataPtr: Pointer to the AAD data, which should be in BIG endian mode
 * @param[in]  aadLen: Length of the AAD data in bytes
 * @param[out] outputDataPtr: Pointer to the output data
 * @param[out] tagPtr: Pointer to the calculated tag
 * @param[in]  tagLen: Tag length in bytes
 *
 * @return     AES_ErrorStatus_t
 * 
 */
AES_ErrorStatus_t AES_Gcm(const AES_Config_t *aesConfigStruct, const uint8_t *inputDataPtr, 
                          uint32_t inputLen, const uint8_t *aadDataPtr, uint32_t aadLen, 
                          uint8_t *outputDataPtr, uint8_t *tagPtr, uint32_t tagLen)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;

    /* Init the AES operation */
    ret = AES_StartGcm(aesConfigStruct);

    /* process AAD data */
    if((0U != aadLen) && (AES_STATUS_NO_ERR == ret))
    {
        ret = AES_UpdateGcmAad(aesConfigStruct, aadDataPtr, aadLen);
    }

    /* process input text data */
    if((0U != inputLen) && (AES_STATUS_NO_ERR == ret))
    {
        ret = AES_UpdateGcmData(aesConfigStruct, inputDataPtr, inputLen, outputDataPtr);
    }  

    if(AES_STATUS_NO_ERR == ret)
    {
        /* finish gcm operation and read out the output data and tag */
        ret = AES_FinishGcm(aesConfigStruct, NULL, 0U, NULL, 0U, outputDataPtr, tagPtr, tagLen);
    }
    
    return ret;
}

/**
 * @brief      Initialize a CCM operation
 *
 * @param[in]  aesConfigStruct: The cipher configuration, where ivLen is length of 
*                               initial vector in bytes. The length of the iv can be 7~13 bytes.
 * @param[in]  inputLen: Total length of the input data in bytes
 * @param[in]  aadLen: Total length of the AAD data in bytes
 * @param[in]  tagLen: Tag length in bytes, which is 4/6/8/10/12/14/16 bytes.
 *
 * @return     AES_ErrorStatus_t
 * 
 */
AES_ErrorStatus_t AES_StartCcm(const AES_Config_t *aesConfigStruct, uint32_t inputLen, 
                               uint32_t aadLen, uint32_t tagLen)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;
    uint8_t ctrB0[16U] = {0U};
    uint8_t b0[16U] = {0U};

    if((NULL != aesConfigStruct) && (NULL != aesConfigStruct->keyPtr) && 
                            (NULL != aesConfigStruct->ivPtr) && (0U != aesConfigStruct->ivLen))
    {
        aesCcmAadStartFlag = SET;
        aesCcmAadEndFlag = RESET;
        aesCcmDataAlignedFlag = SET;

        /* Write the key for the operation */
        AES_WriteKey(aesConfigStruct->keyPtr);

        /* Generate initial CtrB0 and B0 block */
        ret = AES_GenerateInitBlock(aesConfigStruct, inputLen, aadLen, tagLen, ctrB0, b0);

        if(AES_STATUS_NO_ERR == ret)
        {
            /* Write CtrB0 to IV reg */
            AES_WriteInitVector(ctrB0);

            /* Process B0 for CCM init */
            ret = AES_ProcessGcmCcmData(b0, AES_CCM_INIT, aesConfigStruct->functionMode, 0x80U);   
        }
    }
    else
    {
        ret = AES_STATUS_INPUT_ERROR;
    }

    return ret;
}

/**
 * @brief      The authenticated encryption/decryption update AAD function for CCM cipher mode.
 *
 * @param[in]  aesConfigStruct: The cipher configuration, where ivLen is length of 
 *                              initial vector in bytes.
 * @param[in]  aadDataPtr: Pointer to the AAD data block, which should be in BIG endian mode
 * @param[in]  aadLen: AAD data length in bytes
 *
 * @return     AES_ErrorStatus_t
 * 
 * @note       1) To simplify the design, this function can only be called once
 *                during the entire CCM protocol computation.
 *             2) If there is no AAD, that is, aadLen is equal to 0, it does not
 *                need to call this function.
 *             3) This CCM AAD update function (also in CCM finish function) cannot be 
 *                called after AES_UpdateCcmData is called.
 */
AES_ErrorStatus_t AES_UpdateCcmAad(const AES_Config_t *aesConfigStruct, const uint8_t *aadDataPtr, 
                                   uint32_t aadLen)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;
    uint32_t blockNum;
    uint32_t countBlock, count;
    uint8_t lastDataLength;
    uint8_t firstDataBlock[16U] = {0U};
    uint8_t lastDataCopy[16U] = {0U};
    uint32_t padLen = 0U;
    uint32_t tempLen;
    const uint8_t *dataPtr;

    if ((RESET == aesCcmAadEndFlag) && (NULL != aesConfigStruct) && 
                                                        (NULL != aadDataPtr) && (0U != aadLen))
    {
        if (SET == aesCcmAadStartFlag)
        {
            if (0xFF00U > aadLen)
            {
                firstDataBlock[0] = (uint8_t)(aadLen >> 8U);
                firstDataBlock[1] = (uint8_t)(aadLen & 0xFFU);
                padLen = 2U;
            }
            else
            {
                firstDataBlock[0] = 0xFFU;
                firstDataBlock[1] = 0xFEU;
                firstDataBlock[2] = (uint8_t)(aadLen >> 24U);
                firstDataBlock[3] = (uint8_t)((aadLen >> 16U) & 0xFFU);
                firstDataBlock[4] = (uint8_t)((aadLen >> 8U) & 0xFFU);
                firstDataBlock[5] = (uint8_t)(aadLen & 0xFFU);
                padLen = 6U;
            }
        }

        if (aadLen < (16U - padLen))
        {
            tempLen = aadLen;
            blockNum = 0U;
            lastDataLength = 0U;
            aesCcmAadEndFlag = SET;
        }
        else
        {
            tempLen = (16U - padLen);
            blockNum = ((aadLen + padLen) / 16U) - 1U;
            lastDataLength = (uint8_t)((aadLen + padLen)  % 16U);
        }

        for(count = 0U; count < tempLen; count++)
        {
            firstDataBlock[padLen + count] = aadDataPtr[count];
        }

        /* Process first data block */
        ret = AES_ProcessGcmCcmData(firstDataBlock, AES_CCM_MAC, 
                                                            aesConfigStruct->functionMode, 0x80U);
        
        if(AES_STATUS_NO_ERR == ret)
        {
            dataPtr = &aadDataPtr[count];
            for(countBlock = 0U; countBlock < blockNum; countBlock++)
            {
                ret = AES_ProcessGcmCcmData(&dataPtr[16U * countBlock], AES_CCM_MAC, 
                                                aesConfigStruct->functionMode, 0x80U);
                if(AES_STATUS_NO_ERR != ret)
                {
                    break;
                }
            }
        }

        if((AES_STATUS_NO_ERR == ret) && (0U != lastDataLength))
        {
            aesCcmAadEndFlag = SET;

            /* Copy the last data block */
            AES_CopyDataBlock(&dataPtr[16U * countBlock], lastDataCopy, lastDataLength);
            /* Process last data block */
            ret = AES_ProcessGcmCcmData(lastDataCopy, AES_CCM_MAC, 
                                                            aesConfigStruct->functionMode, 0x80U);
        }
    }
    else
    {
        ret = AES_STATUS_INPUT_ERROR;
    }

    aesCcmAadStartFlag = RESET;
    return ret;
}

/**
 * @brief      Update CCM message data
 *
 * @param[in]  aesConfigStruct: The cipher configuration, where ivLen is length of 
 *                              initial vector in bytes.
 * @param[in]  inputDataPtr: Pointer to the input data block, which should be in BIG endian mode
 * @param[in]  inputLen: Data length in bytes
 * @param[out] outputDataPtr: Pointer to the output data block
 *
 * @return     AES_ErrorStatus_t
 * 
 * @note       1) CCM data that are not 16-bytes aligned is supported only for the last update 
 *                operation, and there shall not be new input data in finish operation in that case
 *             2) Once this CCM data update function is called, it means that all CCM AAD data has 
 *                been updated and the function AES_UpdateCcmAad cannot be called again.
 *             3) In the case of note 2), AAD data should no longer be transferred to the 
 *                function AES_FinishCcm (aadDataPtr should be NULL pointer).
 */
AES_ErrorStatus_t AES_UpdateCcmData(const AES_Config_t *aesConfigStruct, 
                                    const uint8_t *inputDataPtr, uint32_t inputLen, 
                                    uint8_t *outputDataPtr)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;
    uint32_t blockNum = (inputLen / 16U);
    uint32_t countBlock;
    uint8_t lastDataLength = (uint8_t)(inputLen % 16U);
    uint8_t lastDataCopy[16U] = {0U};

    /* Set AAD end flag to SET, indicating that no AAD data can be fed any more */
    aesCcmAadEndFlag = SET;
    
    if ((RESET == aesCcmDataAlignedFlag) || (NULL == aesConfigStruct) || 
                            (NULL == inputDataPtr) || (NULL == outputDataPtr) || (0U == inputLen))
    {
        ret = AES_STATUS_INPUT_ERROR;
    }
    else
    {
        /* Process the input data */
        for(countBlock = 0U; countBlock < blockNum; countBlock++)
        {
            ret = AES_ProcessGcmCcmData(&inputDataPtr[16U * countBlock], AES_CCM_UPDATE, 
                                            aesConfigStruct->functionMode, 0x80U);
            if(AES_STATUS_NO_ERR == ret)
            {
                /* Read out the output value */
                AES_ReadData(&outputDataPtr[16U * countBlock], 16U);
            }
            else
            {
                break;
            }
        }

        if((AES_STATUS_NO_ERR == ret) && (0U != lastDataLength))
        {
            /* Set data aligned flag to RESET, indicating that no CCM data can be fed any more */
            aesCcmDataAlignedFlag = RESET;
            
            /*Copy the last data block*/
            AES_CopyDataBlock(&inputDataPtr[16U * countBlock], lastDataCopy, lastDataLength);
            ret = AES_ProcessGcmCcmData(lastDataCopy, AES_CCM_UPDATE, 
                                    aesConfigStruct->functionMode, 8U * (uint32_t)lastDataLength);
            if(AES_STATUS_NO_ERR == ret)
            {
                /* Read out the output value */
                AES_ReadData(&outputDataPtr[16U * countBlock], lastDataLength);
            }
        }
    }

    return ret;
}

/**
 * @brief     Finish a CCM operation and read out the text data and tag
 *
 * @param[in]  aesConfigStruct: The cipher configuration, where ivLen is length of 
 *                              initial vector in bytes.
 * @param[in]  inputDataPtr: Pointer to the input data, which should be in BIG endian mode
 * @param[in]  inputLen: Length of the input data in bytes
 * @param[in]  aadDataPtr: Pointer to the AAD data, which should be in BIG endian mode
 * @param[in]  aadLen: Length of the AAD data in bytes
 * @param[out] outputDataPtr: Pointer to the output data
 * @param[out] tagPtr: Pointer to the calculated tag
 * @param[in]  tagLen: Tag length in bytes, which is 4/6/8/10/12/14/16 bytes.
 *
 * @return    AES_ErrorStatus_t
 * 
 * @note       1) Once the function AES_UpdateCcmData is called, AAD data should no longer be 
 *                transferred to this CCM finish function(aadDataPtr should be NULL pointer).
 *             2) The inputDataPtr transferred to this function must be the remaining part of the 
 *                data that has not been processed by AES_UpdateCcmData, rather than the complete 
 *                CCM input data (inputLen must also be the length of the remaining data).
 */                           
AES_ErrorStatus_t AES_FinishCcm(const AES_Config_t *aesConfigStruct, const uint8_t *inputDataPtr, 
                                uint32_t inputLen, const uint8_t *aadDataPtr, 
                                uint32_t aadLen, uint8_t *outputDataPtr, 
                                uint8_t *tagPtr, uint32_t tagLen)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;

    if((16U >= tagLen) && (NULL != tagPtr) && (0U != tagLen))
    {
        /* process AAD data */
        if (0U != aadLen)
        {
            ret = AES_UpdateCcmAad(aesConfigStruct, aadDataPtr, aadLen);
        }

        /* process input text data */
        if((0U != inputLen) && (AES_STATUS_NO_ERR == ret))
        {
            ret = AES_UpdateCcmData(aesConfigStruct, inputDataPtr, inputLen, outputDataPtr);
        }

        if(AES_STATUS_NO_ERR == ret)
        {
            AES_Configure(AES_CCM_FINISH, aesConfigStruct->functionMode, 0x80U);

            ret = AES_StartOperation();
            if(AES_STATUS_NO_ERR == ret)
            {
                /* Read out the tag output value */
                AES_ReadData(tagPtr, tagLen);
            }
        }
    }
    else
    {
        ret = AES_STATUS_INPUT_ERROR;
    }

    return ret;
}  

/**
 * @brief      CCM operation, only single call mode is supported for CCM
 *
 * @param[in]  aesConfigStruct: The cipher configuration, where ivLen is length of 
 *                              initial vector in bytes. The length of the iv can be 7~13 bytes.
 * @param[in]  inputDataPtr: Pointer to the input data, which should be in BIG endian mode
 * @param[in]  inputLen: Length of the input data in bytes
 * @param[in]  aadDataPtr: Pointer to the AAD data, which should be in BIG endian mode
 * @param[in]  aadLen: Length of the AAD data in bytes
 * @param[out] outputDataPtr: Pointer to the output data
 * @param[out] tagPtr: Pointer to the calculated tag
 * @param[in]  tagLen: Tag length in bytes, which is 4/6/8/10/12/14/16 bytes.
 *
 * @return     AES_ErrorStatus_t
 * 
 */
AES_ErrorStatus_t AES_Ccm(const AES_Config_t *aesConfigStruct, const uint8_t *inputDataPtr, 
                          uint32_t inputLen, const uint8_t *aadDataPtr, uint32_t aadLen, 
                          uint8_t *outputDataPtr, uint8_t *tagPtr, uint32_t tagLen)
{
    AES_ErrorStatus_t ret = AES_STATUS_NO_ERR;

    /* Init the AES operation */
    ret = AES_StartCcm(aesConfigStruct, inputLen, aadLen, tagLen);

    /* process AAD data */
    if((0U != aadLen) && (AES_STATUS_NO_ERR == ret))
    {
        ret = AES_UpdateCcmAad(aesConfigStruct, aadDataPtr, aadLen);
    }

    /* process input text data */
    if((0U != inputLen) && (AES_STATUS_NO_ERR == ret))
    {
        ret = AES_UpdateCcmData(aesConfigStruct, inputDataPtr, inputLen, outputDataPtr);
    }  

    if(AES_STATUS_NO_ERR == ret)
    {
        /* finish ccm operation and read out the output data and tag */
        ret = AES_FinishCcm(aesConfigStruct, NULL, 0U, NULL, 0U, outputDataPtr, tagPtr, tagLen);
    }
    
    return ret;
}

/** @} end of group AES_Public_Functions */

/** @} end of group AES */

/** @} end of group Z20K14XM_Peripheral_Driver */
