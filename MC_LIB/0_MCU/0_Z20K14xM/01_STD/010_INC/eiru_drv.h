/**************************************************************************************************/
/**
 * @file     eiru_drv.h
 * @brief    EIRU driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef EIRU_DRV_H
#define EIRU_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  EIRU
 *  @{
 */

/** @defgroup EIRU_Public_Types 
 *  @{
 */
/**
 *  @brief EIRU SRAM ECC error mask definition
 */
#define EIRU_SRAM_ECC_ERR_SINGLEBIT_MASK 0x20000000U    /*!< SRAM ECC single bit error */
#define EIRU_SRAM_ECC_ERR_MULTIBIT_MASK  0x40000000U    /*!< SRAM ECC multi bit error */
#define EIRU_SRAM_ECC_ERR_OVERRUN_MASK   0x80000000U    /*!< SRAM ECC error overrun */    
#define EIRU_SRAM_ECC_ERR_ALL_MASK       0xE0000000U     /*!< all SRAM ECC error status */

/** 
 *  @brief SRAM ID type definition
 */
typedef enum
{
    EIRU_SRAM_0 = 0U,                     /*!< SRAM0  */
    EIRU_SRAM_1                           /*!< SRAM1  */ 
} EIRU_Sram_t;

/**
 *  @brief EIRU master definition
 */
typedef enum
{
    EIRU_MASTER_CORE = 0U,  /*!< Master: CPU */
    EIRU_MASTER_DEBUGGER,   /*!< Master: DEBUGGER */
    EIRU_MASTER_DMA,        /*!< Master: DMA */
} EIRU_Master_t;

/**
 *  @brief EIRU access size definition
 */
typedef enum
{
    EIRU_ACC_SIZE_8BIT = 0U,   /*!< access size: 8 bits */
    EIRU_ACC_SIZE_16BIT,       /*!< access size: 16 bits */
    EIRU_ACC_SIZE_32BIT        /*!< access size: 32 bits */
} EIRU_AccessSize_t;

/**
 *  @brief EIRU access type definition
 */
typedef enum
{
    EIRU_ACC_TYPE_OPCODE = 0U,   /*!< access type: opcode fetch */
    EIRU_ACC_TYPE_DATA           /*!< access type: data access */
} EIRU_AccessType_t;

/**
 *  @brief EIRU access mode definition
 */
typedef enum
{
    EIRU_ACC_MODE_USER = 0U,   /*!< access mode: user */
    EIRU_ACC_MODE_PRIVIL       /*!< access mode: privileged */
} EIRU_AccessMode_t;

/**
 *  @brief EIRU ECC bit mask definition
 */
typedef enum
{
    ECC_MASK_BIT_0 = 0U,           /*!< ECC bit 0 mask */
    ECC_MASK_BIT_1,                /*!< ECC bit 1 mask */
    ECC_MASK_BIT_2,                /*!< ECC bit 2 mask */
    ECC_MASK_BIT_3,                /*!< ECC bit 3 mask */
    ECC_MASK_BIT_4,                /*!< ECC bit 4 mask */
    ECC_MASK_BIT_5,                /*!< ECC bit 5 mask */
    ECC_MASK_BIT_6,                /*!< ECC bit 6 mask */
    ECC_MASK_BIT_ALL               /*!< ECC all bits */
} EIRU_EccMaskBit_t;

/**
 *  @brief EIRU ECC Mask/Unmask definition
 */
typedef enum
{
    EIRU_INJECTION_MASK = 0U,           /*!< ECC Mask definition*/
    EIRU_INJECTION_UNMASK = 1U,         /*!< ECC Unmask definition*/
} EIRU_InjectionMask_t;

/**
 *  @brief EIRU data bit mask definition
 */
typedef enum
{
    DATA_MASK_BIT_0 = 0U,         /*!< Data bit 0 mask */
    DATA_MASK_BIT_1,              /*!< Data bit 1 mask */
    DATA_MASK_BIT_2,              /*!< Data bit 2 mask */
    DATA_MASK_BIT_3,              /*!< Data bit 3 mask */
    DATA_MASK_BIT_4,              /*!< Data bit 4 mask */
    DATA_MASK_BIT_5,              /*!< Data bit 5 mask */
    DATA_MASK_BIT_6,              /*!< Data bit 6 mask */
    DATA_MASK_BIT_7,              /*!< Data bit 7 mask */
    DATA_MASK_BIT_8,              /*!< Data bit 8 mask */
    DATA_MASK_BIT_9,              /*!< Data bit 9 mask */
    DATA_MASK_BIT_10,             /*!< Data bit 10 mask */
    DATA_MASK_BIT_11,             /*!< Data bit 11 mask */
    DATA_MASK_BIT_12,             /*!< Data bit 12 mask */
    DATA_MASK_BIT_13,             /*!< Data bit 13 mask */
    DATA_MASK_BIT_14,             /*!< Data bit 14 mask */
    DATA_MASK_BIT_15,             /*!< Data bit 15 mask */
    DATA_MASK_BIT_16,             /*!< Data bit 16 mask */
    DATA_MASK_BIT_17,             /*!< Data bit 17 mask */
    DATA_MASK_BIT_18,             /*!< Data bit 18 mask */
    DATA_MASK_BIT_19,             /*!< Data bit 19 mask */
    DATA_MASK_BIT_20,             /*!< Data bit 20 mask */
    DATA_MASK_BIT_21,             /*!< Data bit 21 mask */
    DATA_MASK_BIT_22,             /*!< Data bit 22 mask */
    DATA_MASK_BIT_23,             /*!< Data bit 23 mask */
    DATA_MASK_BIT_24,             /*!< Data bit 24 mask */
    DATA_MASK_BIT_25,             /*!< Data bit 25 mask */
    DATA_MASK_BIT_26,             /*!< Data bit 26 mask */
    DATA_MASK_BIT_27,             /*!< Data bit 27 mask */
    DATA_MASK_BIT_28,             /*!< Data bit 28 mask */
    DATA_MASK_BIT_29,             /*!< Data bit 29 mask */
    DATA_MASK_BIT_30,             /*!< Data bit 30 mask */
    DATA_MASK_BIT_31,             /*!< Data bit 31 mask */
    DATA_MASK_BIT_ALL             /*!< Data all bits */
} EIRU_DataBitMask_t;

/**
 *  @brief EIRU SRAM config struct definition
 */
typedef struct
{
    uint32_t eeiAddress;                    /*!< EIRU ECC error injection address */
    ControlState_t eccErrInjectEnable;      /*!< EIRU ECC error injection enable */
    ControlState_t readEccDisable;          /*!< Disable ECC error report when an ECC error occurred on SRAM read access */
    ControlState_t writeEccDisable;         /*!< Disable ECC check bit being calculated when writing a data to SRAM*/
    ControlState_t singleBitDisable;        /*!< Disable single bit ECC when accesses SRAM */
    ControlState_t multiBitDisable;         /*!< Enable/disable multi bit ECC when accesses SRAM */
 }EIRU_SramEccConfig_t;

/**
 *  @brief EIRU SRAM ECC error cause struct definition
 */
typedef struct
{
    uint32_t errFaultAddr;             /*!< The access address that caused ECC error */
    uint32_t errFaultData;             /*!< The fault data  */
    EIRU_Master_t errFaultMaster;      /*!< Indicates error caused by which master.*/
    EIRU_AccessSize_t errFaultSize;    /*!< Indicates error caused by  what size of access.*/
    EIRU_AccessType_t accessType;      /*!< Indicates error caused by which type of access.*/
    EIRU_AccessMode_t accessMode;      /*!< Indicates error caused in which mode */
} EIRU_SramEccErrCause_t;

/** @} end of group EIRU_Public_Types */

/** @defgroup EIRU_Public_Constants
 *  @{
 */

/** @} end of group EIRU_Public_Constants */

/** @defgroup EIRU_Public_Macro
 *  @{
 */

/** @} end of group EIRU_Public_Macro */

/** @defgroup EIRU_Public_FunctionDeclaration
 *  @brief EIRU functions declaration
 *  @{
 */
/**
 * @brief      Sets the ecc configuration structure to default values.
 *
 * @param[out]  eccConfig: A pointer to the ecc configuration structure.
 *
 * @return     none
 *
 */
void EIRU_EccGetDefaultConfig(EIRU_SramEccConfig_t * eccConfig);

/**
 * @brief      config SRAM ECC. SRAM ECC is enabled by default. ECC config can  
 *             be changed through this function.
 *
 * @param[in]  sram: select which SRAM to config:
                    - EIRU_SRAM_0
                    - EIRU_SRAM_1

 * @param[in]  eccConfig: points to the struct that stores the parameters. 
 *
 * @return     none
 *
 */
void EIRU_Init(EIRU_Sram_t sram, const EIRU_SramEccConfig_t * eccConfig);

/**
 * @brief      Set ECC error injection address
 *
 * @param[in]  eeiAddress: ECC error injection address.
 *
 * @return     none
 *
 * @note       Only bit[31:2] of the address takes affect as [1:0] are reserved.
               Refer to RM  for more information.
 */
void EIRU_SetErrInjectAddress(uint32_t eeiAddress);

/**
 * @brief      Sram ECC read control.
 *
 * @param[in]  sram: select which SRAM to config:
                     - EIRU_SRAM_0
                     - EIRU_SRAM_1
 * @param[in]  newStatus: Sram ECC read status :
 *                   - ENABLE: Sram ECC read disable
 *                   - DISABLE: Sram ECC read enable
 *
 * @return     none
 *
 */
void EIRU_SetReadDisable(EIRU_Sram_t sram, ControlState_t newStatus);

/**
 * @brief      Sram ECC write control.
 *
 * @param[in]  sram: select which SRAM to config:
                     - EIRU_SRAM_0
                     - EIRU_SRAM_1
 * @param[in]  newStatus: Sram ECC write status:
 *                 - ENABLE: Sram ECC write disable
 *                 - DISABLE: Sram ECC write enable
 *
 * @return     none
 *
 */
void EIRU_SetWriteDisable(EIRU_Sram_t sram, ControlState_t newStatus);

/**
 * @brief      Sram ECC single bit control.
 *
 * @param[in]  sram: select which SRAM to config:
                     - EIRU_SRAM_0
                     - EIRU_SRAM_1
 * @param[in]  newStatus: Sram ECC single bit status :
 *                 - ENABLE: Sram ECC single bit disable
 *                 - DISABLE: Sram ECC single bit enable
 *
 * @return     none
 *
 */
void EIRU_SetSingleBitDisable(EIRU_Sram_t sram, ControlState_t newStatus);

/**
 * @brief      Sram ECC multi bit control.
 *
 * @param[in]  sram: select which SRAM to config:
                     - EIRU_SRAM_0
                     - EIRU_SRAM_1
 * @param[in]  newStatus: Sram ECC multi bit status :
 *                 - ENABLE: Sram ECC multi bit disable
 *                 - DISABLE: Sram ECC multi bit enable
 *
 * @return     none
 *
 */
void EIRU_SetMultiBitDisable(EIRU_Sram_t sram, ControlState_t newStatus);

/**
 * @brief      ECC error injection enable
 *
 * @param[in]  sram: select which SRAM to config:
                     - EIRU_SRAM_0
                     - EIRU_SRAM_1
 * @param[in]  newStatus: Sram ECC err injection enable :
 *                 - ENABLE: ECC err injection enable 
 *                 - DISABLE: ECC err injection disable
 
 * @return     none
 *
 */
void EIRU_ErrInjectEnable(EIRU_Sram_t sram, ControlState_t newStatus);

/**
 * @brief      Clear All ECC Mask Bits 
 *
 * @param[in]  sram: select which SRAM to config:
                     - EIRU_SRAM_0
                     - EIRU_SRAM_1
 *
 * @return     none
 *
 */
void EIRU_ClearEccInjectBits(EIRU_Sram_t sram);

/**
 * @brief      Set ECC Injection Bit
 *
 * @param[in]  sram: select which SRAM to config:
                     - EIRU_SRAM_0
                     - EIRU_SRAM_1
 * @param[in]  eccBit: set the error injection bit
 * @param[in]  eccBitMask: Mask/Unmask error injection bit
                     - EIRU_InjectionMask_t
                     - EIRU_INJECTION_UNMASK
 * @return     none
 *
 */
void EIRU_SetEccInjectBit(EIRU_Sram_t sram, EIRU_EccMaskBit_t eccBit, 
                                                           EIRU_InjectionMask_t eccBitMask);

/**
 * @brief      Set ECC data injection bit
 *
 * @param[in]  sram: select which SRAM to config:
                     - EIRU_SRAM_0
                     - EIRU_SRAM_1
 * @param[in]  dataBit: set the data injection bit
 * @param[in]  dataBitMask: Mask/Unmask data injection bit
                     - EIRU_InjectionMask_t
                     - EIRU_INJECTION_UNMASK
 * @return     none
 *
 */
void EIRU_SetDataInjectBit(EIRU_Sram_t sram, EIRU_DataBitMask_t dataBit,
                                                          EIRU_InjectionMask_t dataBitMask);

/**
 * @brief      Clear All Data Mask Bits 
 *
 * @param[in]  sram: select which SRAM to config:
                     - EIRU_SRAM_0
                     - EIRU_SRAM_1
 *
 * @return     none
 *
 */
void EIRU_ClearDataInjectBits(EIRU_Sram_t sram);

/**
 * @brief      Get SRAM ECC error cause
 *
  * @param[in]  sram: select which SRAM to config:
                     - EIRU_SRAM_0
                     - EIRU_SRAM_1
 * @param[in]  cause: the cause of SRAM ERR error will be stored in the struct 
 *                    that is pointed by this parameter. 
 *
 * @return none
 *
 */
void EIRU_GetSramEccErrCause(EIRU_Sram_t sram, 
                                         EIRU_SramEccErrCause_t *cause);

/**
 * @brief      Get SRAM ECC error status
 *
 * @param[in]  sram: select which SRAM to config:
                     - EIRU_SRAM_0
                     - EIRU_SRAM_1
 * @param[in]  errMask: select the mask of error to get :
 *               - EIRU_SRAM_ECC_ERR_SINGLEBIT_MASK
 *               - EIRU_SRAM_ECC_ERR_MULTIBIT_MASK
 *               - EIRU_SRAM_ECC_ERR_OVERRUN_MASK
 *               - EIRU_SRAM_ECC_ERR_ALL_MASK
 *
 * @return    Error status :
 *               - RESET: the error status is not set
 *               - SET: the error status is set
 *
 */
FlagStatus_t EIRU_GetSramEccErrStatus(EIRU_Sram_t sram, uint32_t errMask);
/**
 * @brief      Clear SRAM ECC error status
 *
 * @param[in]  sram: select which SRAM to config:
                     - EIRU_SRAM_0
                     - EIRU_SRAM_1
* @param[in]  errMask: select the mask of error to clear :
 *               - EIRU_SRAM_ECC_ERR_SINGLEBIT_MASK
 *               - EIRU_SRAM_ECC_ERR_MULTIBIT_MASK
 *               - EIRU_SRAM_ECC_ERR_OVERRUN_MASK
 *               - EIRU_SRAM_ECC_ERR_ALL_MASK
 *
 * @return none
 *
 */
void EIRU_ClearSramEccErrStatus(EIRU_Sram_t sram, uint32_t errMask);

/** @} end of group EIRU_Public_FunctionDeclaration */

/** @} end of group EIRU  */

/** @} end of group Z20K14XM_Peripheral_Driver */
#endif /* EIRU_DRV_H */
