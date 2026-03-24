/**************************************************************************************************/
/**
 * @file     aes_drv.h
 * @brief    AES driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef AES_DRV_H
#define AES_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  AES
 *  @{
 */

/** @defgroup AES_Public_Types 
 *  @{
 */

/**
 * @brief Structure of AES Driver status return type
 *
 */
typedef enum
{
    AES_STATUS_NO_ERR               = 0x0U,      /*!< No error */
    AES_STATUS_ALG_ERR              = 0x1U,      /*!< Unauthorized algorithm */
    AES_STATUS_KEYSIZE_ALG_ERR      = 0x2U,      /*!< Unauthorized key size for algorithm */
    AES_STATUS_CIPHER_DIRECTION_ERR = 0x3U,      /*!< Unauthorized cipher direction */
    AES_STATUS_MODE_ERR             = 0x4U,      /*!< Unauthorized mode */
    AES_STATUS_ALG_MODE_ERR         = 0x5U,      /*!< Unauthorized algorithm for mode */
    AES_STATUS_DIRECTION_MODE_ERR   = 0x6U,      /*!< Unauthorized direction for mode */
    AES_STATUS_KEYSIZE_MODE_ERR     = 0x7U,      /*!< Unauthorized key size for mode */
    AES_STATUS_UNKNOWN_SETUP_ERR    = 0xFFU,     /*!< Unknown setup error */
    AES_STATUS_TIMEOUT              = 0x100U,    /*!< Function operation timeout */
    AES_STATUS_INPUT_ERROR          = 0x102U,    /*!< Input parameter not supported */
    AES_STATUS_BUSY_ERROR           = 0x103U     /*!< Aes module is busy */
} AES_ErrorStatus_t;

/**
 * @brief AES supported algorithm mode(without steps)
 *
 */
typedef enum
{
    AES_ECB = 0x00U,  /*!< ECB mode */
    AES_CBC = 0x01U,  /*!< CBC mode */
    AES_OFB = 0x02U,  /*!< OFB mode */
    AES_CTR = 0x03U,  /*!< CTR mode */
    AES_CFB = 0x04U,  /*!< CFB mode */
    AES_XTS = 0x07U   /*!< XTS mode */
} AES_AlgorithmMode_t;

/**
 * @brief Defines AES function select type
 *
 */
typedef enum
{
    AES_ENCRYPTION = 0x00U, /*!< AES encryption */
    AES_DECRYPTION = 0x01U  /*!< AES decryption */
} AES_CryptFunction_t;

/** 
 * @brief AES configuration of parameters type definition
 * 
 */
typedef struct {
    AES_AlgorithmMode_t  algorithmMode; /*!< Block cipher mode */
    AES_CryptFunction_t  functionMode;  /*!< Cipher function mode */

    uint8_t  *keyPtr;                /*!< Pointer to the key, which should be in BIG endian mode. 
                                          The key length is 16 bytes except for XTS mode. The key 
                                          length of XTS mode is 32, the first 16 bytes are the tweak 
                                          key, and the last 16 bytes are the data key. */

    uint32_t ivLen;                  /*!< IV length in bytes (except GCM in bits) */
    uint8_t *ivPtr;                  /*!< Pointer to the initial vector, nonce or tweak buffer, 
                                          which should be in BIG endian mode */
} AES_Config_t;

/** @} end of group AES_Public_Types*/


/** @defgroup AES_Public_FunctionDeclaration
 *  @brief AES functions statement
 *  @{
 */

/**
 * @brief      AES Install callback function
 *
 * @param[in]  cbFun: indicate callback function
 *
 * @return     none
 *
 */ 
void AES_InstallCallBackFunc(isr_cb_t * const cbFun);

/**
 * @brief      Initialize a CMAC operation
 *
 * @param[in]  aesConfigStruct: The cipher configuration.
 *
 * @return     None
 * 
 */
void AES_StartCmac(const AES_Config_t *aesConfigStruct);

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
AES_ErrorStatus_t AES_UpdateCmac(const uint8_t *inputDataPtr, uint32_t inputLen);

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
                                 uint8_t *macPtr, uint32_t macLen);

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
                                   uint32_t messageLen, uint8_t *macPtr, uint32_t macLen);

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
                                 uint32_t macLen, uint32_t *verifyResult);

/**
 * @brief      Initialize an encrypt or decrypt operation
 *
 * @param[in]  aesConfigStruct: The cipher configuration.
 *
 * @return     AES_ErrorStatus_t
 * 
 */
AES_ErrorStatus_t AES_StartCrypt(const AES_Config_t *aesConfigStruct);

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
                                  uint32_t inputLen, uint8_t *outputDataPtr);

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
                            uint32_t inputLen, uint8_t *outputDataPtr);

/**
 * @brief      Initialize an GCM operation
 *
 * @param[in]  aesConfigStruct: The cipher configuration, where ivLen is length of 
 *                              initial vector in bits.
 *
 * @return     AES_ErrorStatus_t
 * 
 */
AES_ErrorStatus_t AES_StartGcm(const AES_Config_t *aesConfigStruct);

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
                                   uint32_t aadLen);

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
                                    uint8_t *outputDataPtr);

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
 *                data that has not been processed by AES_UpdateGcmData, rather than the complete 
 *                GCM input data (inputLen must also be the length of the remaining data).
 */
AES_ErrorStatus_t AES_FinishGcm(const AES_Config_t *aesConfigStruct,     
                                const uint8_t *inputDataPtr, uint32_t inputLen, 
                                const uint8_t *aadDataPtr, uint32_t aadLen,
                                uint8_t *outputDataPtr, uint8_t *tagPtr, uint32_t tagLen);

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
                          uint8_t *outputDataPtr, uint8_t *tagPtr, uint32_t tagLen);

/**
 * @brief      Initialize a CCM operation
 *
 * @param[in]  aesConfigStruct: The cipher configuration, where ivLen is length of 
 *                              initial vector in bytes. The length of the iv can be 7~13 bytes.
 * @param[in]  inputLen: Total length of the input data in bytes
 * @param[in]  aadLen: Total length of the AAD data in bytes
 * @param[in]  tagLen: Tag length in bytes, which is 4/6/8/10/12/14/16 bytes.
 *
 * @return     AES_ErrorStatus_t
 * 
 */
AES_ErrorStatus_t AES_StartCcm(const AES_Config_t *aesConfigStruct, uint32_t inputLen, 
                               uint32_t aadLen, uint32_t tagLen);

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
                                   uint32_t aadLen);

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
                                    uint8_t *outputDataPtr);

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
                                uint8_t *tagPtr, uint32_t tagLen);

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
                          uint8_t *outputDataPtr, uint8_t *tagPtr, uint32_t tagLen);

/** @} end of group AES_Public_FunctionDeclaration */

/** @} end of group AES */

/** @} end of group Z20K14XM_Peripheral_Driver */

#endif /* AES_DRV_H */
