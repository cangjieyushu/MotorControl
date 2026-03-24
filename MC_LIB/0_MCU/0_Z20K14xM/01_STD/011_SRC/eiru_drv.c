/**************************************************************************************************/
/**
 * @file     eiru_drv.c
 * @brief    EIRU module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#include "eiru_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup EIRU
 *  @brief EIRU driver modules
 *  @{
 */


/** @defgroup EIRU_Private_Defines
 *  @{
 */
/*PRQA S 0303 ++*/
static eiru_reg_t *const eiruRegPtr = (eiru_reg_t *) EIRU_BASE_ADDR;         /*!< EIRU Register */
static eiru_reg_w_t *const eiruRegWPtr = (eiru_reg_w_t *) EIRU_BASE_ADDR;    /*!< EIRU word Register */
/*PRQA S 0303 --*/
/** @} end of group EIRU_Private_Defines */

/** @defgroup EIRU_Private_Variables
 *  @{
 */
     
/**
 *  @brief ECC bit mask array
 */

 static const uint32_t EIRU_EccBitMask[]=
 {
    0x00000001U,        /*!< ECC bit 0 mask */
    0x00000002U,        /*!< ECC bit 1 mask */
    0x00000004U,        /*!< ECC bit 2 mask */
    0x00000008U,        /*!< ECC bit 3 mask */
    0x00000010U,        /*!< ECC bit 4 mask */
    0x00000020U,        /*!< ECC bit 5 mask */
    0x00000040U,        /*!< ECC bit 6 mask */
    0x0000007FU         /*!< ECC all bits */
 };

 /**
 *  @brief Data bit mask array
 */

 static const uint32_t EIRU_RdataBitMask[]=
 {
    0x00000001U,         /*!< Data bit 0 mask */
    0x00000002U,         /*!< Data bit 1 mask */
    0x00000004U,         /*!< Data bit 2 mask */
    0x00000008U,         /*!< Data bit 3 mask */
    0x00000010U,         /*!< Data bit 4 mask */
    0x00000020U,         /*!< Data bit 5 mask */
    0x00000040U,         /*!< Data bit 6 mask */
    0x00000080U,         /*!< Data bit 7 mask */
    0x00000100U,         /*!< Data bit 8 mask */
    0x00000200U,         /*!< Data bit 9 mask */
    0x00000400U,         /*!< Data bit 10 mask */
    0x00000800U,         /*!< Data bit 11 mask */
    0x00001000U,         /*!< Data bit 12 mask */
    0x00002000U,         /*!< Data bit 13 mask */
    0x00004000U,         /*!< Data bit 14 mask */
    0x00008000U,         /*!< Data bit 15 mask */
    0x00010000U,         /*!< Data bit 16 mask */
    0x00020000U,         /*!< Data bit 17 mask */
    0x00040000U,         /*!< Data bit 18 mask */
    0x00080000U,         /*!< Data bit 19 mask */
    0x00100000U,         /*!< Data bit 20 mask */
    0x00200000U,         /*!< Data bit 21 mask */
    0x00400000U,         /*!< Data bit 22 mask */
    0x00800000U,         /*!< Data bit 23 mask */
    0x01000000U,         /*!< Data bit 24 mask */
    0x02000000U,         /*!< Data bit 25 mask */
    0x04000000U,         /*!< Data bit 26 mask */
    0x08000000U,         /*!< Data bit 27 mask */
    0x10000000U,         /*!< Data bit 28 mask */
    0x20000000U,         /*!< Data bit 29 mask */
    0x40000000U,         /*!< Data bit 30 mask */
    0x80000000U,         /*!< Data bit 31 mask */
    0xFFFFFFFFU          /*!< Data all bits */
 };

/** @} end of group EIRU_Private_Variables */

/** @defgroup EIRU_Global_Variables
 *  @{
 */

/** @} end of group EIRU_Global_Variables */

/** @defgroup EIRU_Private_FunctionDeclaration
 *  @{
 */

/** @} end of group EIRU_Private_FunctionDeclaration */

/** @defgroup EIRU_Private_Functions
 *  @{
 */


/** @} end of group EIRU_Private_Functions */

/** @defgroup EIRU_Public_Functions
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
void EIRU_EccGetDefaultConfig(EIRU_SramEccConfig_t * eccConfig)
{
    /* By default the ecc error injection address is 0xffffffff*/
    eccConfig->eccErrInjectEnable = DISABLE;
    eccConfig->eeiAddress = 0x0U;
    
    eccConfig->readEccDisable = DISABLE;
    eccConfig->writeEccDisable = DISABLE;
    eccConfig->singleBitDisable = DISABLE;
    eccConfig->multiBitDisable = DISABLE;
}

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
void EIRU_Init(EIRU_Sram_t sram, const EIRU_SramEccConfig_t * eccConfig)
{
    if(eiruRegPtr->EIRU_CR.LOCK != 0U)
    {
        eiruRegWPtr->EIRU_CR = 0x5C000000U;
    }
    eiruRegWPtr->EIRU_EEIADDR = eccConfig->eeiAddress;

    if(EIRU_SRAM_0 == sram)
    {   
        eiruRegPtr->EIRU_CR.SRAM0_EEI_EN = (uint32_t)eccConfig->eccErrInjectEnable;
        eiruRegPtr->EIRU_CR.SRAM0_ER_DIS = (uint32_t)eccConfig->readEccDisable;
        eiruRegPtr->EIRU_CR.SRAM0_EW_DIS = (uint32_t)eccConfig->writeEccDisable;
        eiruRegPtr->EIRU_CR.SRAM0_ESB_DIS = (uint32_t)eccConfig->singleBitDisable ;
        eiruRegPtr->EIRU_CR.SRAM0_EMB_DIS = (uint32_t)eccConfig->multiBitDisable;
    }
    else /* EIRU_SRAM_1 == sram */
    {
        eiruRegPtr->EIRU_CR.SRAM1_EEI_EN = (uint32_t)eccConfig->eccErrInjectEnable;
        eiruRegPtr->EIRU_CR.SRAM1_ER_DIS = (uint32_t)eccConfig->readEccDisable;
        eiruRegPtr->EIRU_CR.SRAM1_EW_DIS = (uint32_t)eccConfig->writeEccDisable;
        eiruRegPtr->EIRU_CR.SRAM1_ESB_DIS = (uint32_t)eccConfig->singleBitDisable;
        eiruRegPtr->EIRU_CR.SRAM1_EMB_DIS = (uint32_t)eccConfig->multiBitDisable;
    }

    eiruRegPtr->EIRU_CR.LOCK = 1U;
}

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
void EIRU_SetErrInjectAddress(uint32_t eeiAddress)
{
    eiruRegWPtr->EIRU_EEIADDR = eeiAddress;
}

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
void EIRU_SetReadDisable(EIRU_Sram_t sram, ControlState_t newStatus)
{
    if(eiruRegPtr->EIRU_CR.LOCK != 0U)
    {
        eiruRegWPtr->EIRU_CR = 0x5C000000U;
    }

    if(EIRU_SRAM_0 == sram)
    {
        eiruRegPtr->EIRU_CR.SRAM0_ER_DIS = (uint32_t)newStatus;
    }
    else /* EIRU_SRAM_1 == sram */
    {
        eiruRegPtr->EIRU_CR.SRAM1_ER_DIS = (uint32_t)newStatus;
    }

    eiruRegPtr->EIRU_CR.LOCK = 1U;
}

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
void EIRU_SetWriteDisable(EIRU_Sram_t sram, ControlState_t newStatus)
{
    if(eiruRegPtr->EIRU_CR.LOCK != 0U)
    {
        eiruRegWPtr->EIRU_CR = 0x5C000000U;
    }

    if(EIRU_SRAM_0 == sram)
    {
        eiruRegPtr->EIRU_CR.SRAM0_EW_DIS = (uint32_t)newStatus;
    }
    else /* EIRU_SRAM_1 == sram */
    {
        eiruRegPtr->EIRU_CR.SRAM1_EW_DIS = (uint32_t)newStatus;
    }

    eiruRegPtr->EIRU_CR.LOCK = 1U;
}

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
void EIRU_SetSingleBitDisable(EIRU_Sram_t sram, ControlState_t newStatus)
{
    if(eiruRegPtr->EIRU_CR.LOCK != 0U)
    {
        eiruRegWPtr->EIRU_CR = 0x5C000000U;
    }

    if(EIRU_SRAM_0 == sram)
    {
        eiruRegPtr->EIRU_CR.SRAM0_ESB_DIS = (uint32_t)newStatus;
    }
    else /*EIRU_SRAM_1 == sram*/
    {
        eiruRegPtr->EIRU_CR.SRAM1_ESB_DIS = (uint32_t)newStatus;
    }
   
    eiruRegPtr->EIRU_CR.LOCK = 1U;
}

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
void EIRU_SetMultiBitDisable(EIRU_Sram_t sram, ControlState_t newStatus)
{
    if(eiruRegPtr->EIRU_CR.LOCK != 0U)
    {
        eiruRegWPtr->EIRU_CR = 0x5C000000U;
    }

    if(EIRU_SRAM_0 == sram)
    {
        eiruRegPtr->EIRU_CR.SRAM0_EMB_DIS = (uint32_t)newStatus;
    }
    else /* EIRU_SRAM_1 == sram */
    {
        eiruRegPtr->EIRU_CR.SRAM1_EMB_DIS = (uint32_t)newStatus;
    }

    eiruRegPtr->EIRU_CR.LOCK = 1U;
}

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
void EIRU_ErrInjectEnable(EIRU_Sram_t sram, ControlState_t newStatus)
{
    if(eiruRegPtr->EIRU_CR.LOCK != 0U)
    {
        eiruRegWPtr->EIRU_CR = 0x5C000000U;
    }

    if(EIRU_SRAM_0 == sram)
    {
        eiruRegPtr->EIRU_CR.SRAM0_EEI_EN = (uint32_t)newStatus;
    }
    else /* EIRU_SRAM_1 == sram */
    {
        eiruRegPtr->EIRU_CR.SRAM1_EEI_EN = (uint32_t)newStatus;
    }

    eiruRegPtr->EIRU_CR.LOCK = 1U;
}

/**
 * @brief      Set ECC Injection Bit
 *
 * @param[in]  sram: select which SRAM to config:
                     - EIRU_SRAM_0
                     - EIRU_SRAM_1
 * @param[in]  eccBit: set the error injection bit
 * @param[in]  eccBitMask: Mask/Unmask error injection bit
                     - EIRU_INJECTION_MASK
                     - EIRU_INJECTION_UNMASK
 * @return     none
 *
 */
void EIRU_SetEccInjectBit(EIRU_Sram_t sram, EIRU_EccMaskBit_t eccBit, 
                                                           EIRU_InjectionMask_t eccBitMask)
{
    if(EIRU_INJECTION_MASK == eccBitMask)
    {
        eiruRegWPtr->EIRU_SRAMn_SC[sram].EIRU_SRAMn_ECCMASK &= 
                                                 (~EIRU_EccBitMask[eccBit]);
    }
    else /* EIRU_INJECTION_UNMASK == eccBitMask */
    {
        eiruRegWPtr->EIRU_SRAMn_SC[sram].EIRU_SRAMn_ECCMASK |= 
                                                    EIRU_EccBitMask[eccBit];
    }
}

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
void EIRU_ClearEccInjectBits(EIRU_Sram_t sram)
{

    eiruRegWPtr->EIRU_SRAMn_SC[sram].EIRU_SRAMn_ECCMASK = 0x0U;
}

/**
 * @brief      Set ECC data injection bit
 *
 * @param[in]  sram: select which SRAM to config:
                     - EIRU_SRAM_0
                     - EIRU_SRAM_1
 * @param[in]  dataBit: set the data injection bit
 * @param[in]  dataBitMask: Mask/Unmask data injection bit
                     - EIRU_INJECTION_MASK
                     - EIRU_INJECTION_UNMASK
 * @return     none
 *
 */
void EIRU_SetDataInjectBit(EIRU_Sram_t sram, EIRU_DataBitMask_t dataBit,
                                                          EIRU_InjectionMask_t dataBitMask)
{
    if(EIRU_INJECTION_MASK == dataBitMask)
    {
        eiruRegWPtr->EIRU_SRAMn_SC[sram].EIRU_SRAMn_DATAMASK &= 
                                                 (~EIRU_RdataBitMask[dataBit]);
    }
    else /* EIRU_INJECTION_UNMASK == dataBitMask*/
    {
        eiruRegWPtr->EIRU_SRAMn_SC[sram].EIRU_SRAMn_DATAMASK |= 
                                                 EIRU_RdataBitMask[dataBit];
    }
}

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
void EIRU_ClearDataInjectBits(EIRU_Sram_t sram)
{

    eiruRegWPtr->EIRU_SRAMn_SC[sram].EIRU_SRAMn_DATAMASK = 0;
}

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
                                         EIRU_SramEccErrCause_t *cause)
{
        cause->errFaultAddr = eiruRegWPtr->EIRU_SRAMn_SC[sram].EIRU_SRAMn_FADDR;
        cause->errFaultData = eiruRegWPtr->EIRU_SRAMn_SC[sram].EIRU_SRAMn_FDATA;
        cause->errFaultMaster = (EIRU_Master_t)(eiruRegPtr->EIRU_SRAMn_SC[sram].
                                                         EIRU_SRAMn_EESR.EFMST);
        cause->errFaultSize = (EIRU_AccessSize_t)(eiruRegPtr->EIRU_SRAMn_SC[sram].
                                                        EIRU_SRAMn_EESR.EFSIZE);
        cause->accessType = (((eiruRegWPtr->EIRU_SRAMn_SC[sram].EIRU_SRAMn_EESR)&
               0x00000001UL) == 0U)? EIRU_ACC_TYPE_OPCODE : EIRU_ACC_TYPE_DATA;
        cause->accessMode = (((eiruRegWPtr->EIRU_SRAMn_SC[sram].EIRU_SRAMn_EESR)&
               0x00000002UL) == 0U)? EIRU_ACC_MODE_USER : EIRU_ACC_MODE_PRIVIL;
}

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
FlagStatus_t EIRU_GetSramEccErrStatus(EIRU_Sram_t sram, uint32_t errMask)
{
    return ((eiruRegWPtr->EIRU_SRAMn_SC[sram].EIRU_SRAMn_EESR & 
                                        (uint32_t)errMask) != 0U)? SET : RESET;
}

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
void EIRU_ClearSramEccErrStatus(EIRU_Sram_t sram, uint32_t errMask)
{
    eiruRegWPtr->EIRU_SRAMn_SC[sram].EIRU_SRAMn_EESR = (uint32_t)errMask; 
}

/*@} end of group EIRU_Public_Functions */

/*@} end of group EIRU_definitions */

/*@} end of group Z20K14XM_Peripheral_Driver */
