/**************************************************************************************************/
/**
 * @file     scm_drv.c
 * @brief    SCM module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "scm_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup SCM
 *  @brief SCM driver modules
 *  @{
 */

/** @defgroup SCM_Private_Defines
 *  @{
 */
/*PRQA S 0303 ++*/
static scm_reg_t *const scmRegPtr = (scm_reg_t *) SCM_BASE_ADDR;        /*!< SCM Register */
static scm_reg_w_t *const scmRegWPtr = (scm_reg_w_t *) SCM_BASE_ADDR;   /*!< SCM Word Register */
/*PRQA S 0303 --*/
/** @} end of group SCM_Private_Defines */

/** @defgroup SCM_Global_Variables
 *  @{
 */
static const uint32_t SCM_IntStatusTable[] = 
{
    0x00010000U,               /*!< CACHE_BE_INT status mask*/
    0x01000000U,               /*!< FPU_INEXACT_INT status mask*/
    0x02000000U,               /*!< FPU_OVERFLOW_INT status mask*/
    0x04000000U,               /*!< FPU_UNDERFLOW_INT status mask*/
    0x08000000U,               /*!< FPU_INVALIDOP_INT status mask*/
    0x10000000U,               /*!< FPU_DIVZERO_INT status mask*/
    0x20000000U,               /*!< FPU_DENORMALIN_INT status mask*/
    0x3F018000U                 /*!< SCM All INT status mask*/
};

static const uint32_t SCM_IntMaskTable[] = 
{
    0x00010000U,               /*!< CACHE_BE_INT enable mask*/
    0x01000000U,               /*!< FPU_INEXACT_INT enable mask*/
    0x02000000U,               /*!< FPU_OVERFLOW_INT enable mask*/
    0x04000000U,               /*!< FPU_UNDERFLOW_INT enable mask*/
    0x08000000U,               /*!< FPU_INVALIDOP_INT enable mask*/
    0x10000000U,               /*!< FPU_DIVZERO_INT enable mask*/
    0x20000000U,               /*!< FPU_DENORMALIN_INT enable mask*/
    0x3F018000U                /*!< SCM All INT enable mask*/
};

static uint32_t scmIntMaskStatus = 0;

static isr_cb_t * scmIsrCbFunc[SCM_INT_ALL]= {NULL,NULL,NULL,NULL,NULL,NULL,NULL};
/** @} end of group SCM_Global_Variables */

/** @defgroup SCM_Private_FunctionDeclaration
 *  @{
 */
void SCM_FpuErr_DriverIRQHandler(void);
void SCM_CacheErr_DriverIRQHandler(void);

/** @} end of group SCM_Private_FunctionDeclaration */

/** @defgroup SCM_Private_Functions
 *  @{
 */
/**
 * @brief      SCM FPU Error interrupt handler
 *
 * @param[in]  none
 *
 * @return none
 *
 */
static void SCM_IntHandler(void)
{
    uint32_t intStatus;

    /* get interrupt status */
    intStatus = scmRegWPtr->SCM_MISCSTAT1;
    /* only check enabled interrupts */
    intStatus = intStatus & scmIntMaskStatus;
    /* clear interrupt status */
    scmRegWPtr->SCM_MISCSTAT1 = intStatus;

    /* Inexact Interrupt */
    if((intStatus & SCM_IntStatusTable[SCM_FPU_INEXACT_INT]) != 0U)
    {
        if(scmIsrCbFunc[SCM_FPU_INEXACT_INT] != NULL)
        {
             /* call the callback function */
             scmIsrCbFunc[SCM_FPU_INEXACT_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            scmRegPtr->SCM_MISCCTL1.FPU_INEXACT_INT_EN = 0U;
        }
    }

    /* Overflow Interrupt */
    if((intStatus & SCM_IntStatusTable[SCM_FPU_OVERFLOW_INT]) != 0U)
    {
        if(scmIsrCbFunc[SCM_FPU_OVERFLOW_INT] != NULL)
        {
             /* call the callback function */
             scmIsrCbFunc[SCM_FPU_OVERFLOW_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            scmRegPtr->SCM_MISCCTL1.FPU_OVERFLOW_INT_EN = 0U;
        }
    }

    /* Underflow Interrupt */
    if((intStatus & SCM_IntStatusTable[SCM_FPU_UNDERFLOW_INT]) != 0U)
    {
        if(scmIsrCbFunc[SCM_FPU_UNDERFLOW_INT] != NULL)
        {
             /* call the callback function */
             scmIsrCbFunc[SCM_FPU_UNDERFLOW_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            scmRegPtr->SCM_MISCCTL1.FPU_UNDERFLOW_INT_EN = 0U;
        }
    }

    /* Invalidop Interrupt */
    if((intStatus & SCM_IntStatusTable[SCM_FPU_INVALIDOP_INT]) != 0U)
    {
        if(scmIsrCbFunc[SCM_FPU_INVALIDOP_INT] != NULL)
        {
             /* call the callback function */
             scmIsrCbFunc[SCM_FPU_INVALIDOP_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            scmRegPtr->SCM_MISCCTL1.FPU_INVALIDOP_INT_EN = 0U;
        }
    }

    /* Divzero Interrupt */
    if((intStatus & SCM_IntStatusTable[SCM_FPU_DIVZERO_INT]) != 0U)
    {
        if(scmIsrCbFunc[SCM_FPU_DIVZERO_INT] != NULL)
        {
             /* call the callback function */
             scmIsrCbFunc[SCM_FPU_DIVZERO_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            scmRegPtr->SCM_MISCCTL1.FPU_DIVZERO_INT_EN = 0U;
        }
    }

    /* DENORMALIN Interrupt */
    if((intStatus & SCM_IntStatusTable[SCM_FPU_DENORMALIN_INT]) != 0U)
    {
        if(scmIsrCbFunc[SCM_FPU_DENORMALIN_INT] != NULL)
        {
             /* call the callback function */
             scmIsrCbFunc[SCM_FPU_DENORMALIN_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            scmRegPtr->SCM_MISCCTL1.FPU_DENORMALIN_INT_EN = 0U;
        }
    }

    /* Bit error Interrupt */
    if((intStatus & SCM_IntStatusTable[SCM_CCACHE_BE_INT]) != 0U)
    {
        if(scmIsrCbFunc[SCM_CCACHE_BE_INT] != NULL)
        {
             /* call the callback function */
             scmIsrCbFunc[SCM_CCACHE_BE_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            scmRegPtr->SCM_MISCCTL1.CCACHE_BE_INT_EN = 0U;
        }
    }
    
    COMMON_DSB();
}

/**
 * @brief      SERU Parity Error Interrupt Handler.
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void SCM_FpuErr_DriverIRQHandler(void)
{
    SCM_IntHandler();
}

/**
 * @brief      SERU channel error interrupt handler.
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void SCM_CacheErr_DriverIRQHandler(void)
{
    SCM_IntHandler();
}

/** @} end of group SCM_Private_Functions */

/** @defgroup SCM_Public_Functions
 *  @{
 */

/**
 * @brief      Mask/Unmask specified  interrupt type.
 *
 * @param[in]  intType:  Specified interrupt type.
 *             - CACHE_BE_INT
  *              FPU_INEXACT_INT
 *             - FPU_OVERFLOW_INT
 *             - FPU_UNDERFLOW_INT
 *             - FPU_INVALIDOP_INT
  *            - FPU_DIVZERO_INT
 *             - FPU_DENORMALIN_INT
 *             - SCM_INT_ALL
 * @param[in]  intMask:  Interrupt mask/unmask type.
 *             - MASK: 1
 *             - UNMASK: 0
 *
 * @return none.
 *
 */
void SCM_IntMask(SCM_Int_t intType, IntMask_t intMask)
{

    if(MASK == intMask)
    {
        scmRegWPtr->SCM_MISCCTL1 &= (~ SCM_IntMaskTable[intType]);
        scmIntMaskStatus &= (~ SCM_IntStatusTable[intType]);
    }
    else
    {
        scmRegWPtr->SCM_MISCCTL1 |= SCM_IntMaskTable[intType];
        scmIntMaskStatus |= SCM_IntStatusTable[intType];
    }
}


/**
 * @brief      install callback func
 *
 * @param[in]  intType: interrupt type id
 * @param[in]  cbFun  : callback function pointer
 *
 * @return     None
 *
 */
void SCM_InstallCallBackFunc(SCM_Int_t intType,isr_cb_t * cbFun)
{
    scmIsrCbFunc[intType] = cbFun;
}


/**
 * @brief      Software Trigger To TMU
 *
 * @param[in]  swTrigType: software trigger type
                        - SCM_SWTRIG0
                        - SCM_SWTRIG1
                        - SCM_SWTRIG2
                        - SCM_SWTRIG3
 *
 * @return     None
 *
 */
void SCM_SwTrig(SCM_SwTrig_t swTrigType)
{
    switch (swTrigType)
    {
    case SCM_SWTRIG0:
        scmRegPtr->SCM_MISCCTL1.SWTRIG0 = 1U;
        break;
    case SCM_SWTRIG1:
        scmRegPtr->SCM_MISCCTL1.SWTRIG1 = 1U;
        break;
    case SCM_SWTRIG2:
        scmRegPtr->SCM_MISCCTL1.SWTRIG2 = 1U;
        break;
    case SCM_SWTRIG3:
        scmRegPtr->SCM_MISCCTL1.SWTRIG3 = 1U;
        break;
    
    default:
        /* Do nothing */
        break;
    }
}

/**
 * @brief      Clear Software Trigger To TMU
 *
 * @param[in]  swTrigType: software trigger type
                        - SCM_SWTRIG0
                        - SCM_SWTRIG1
                        - SCM_SWTRIG2
                        - SCM_SWTRIG3
 *
 * @return     None
 *
 */
void SCM_ClearSwTrig(SCM_SwTrig_t swTrigType)
{
    switch (swTrigType)
    {
    case SCM_SWTRIG0:
        scmRegPtr->SCM_MISCCTL1.SWTRIG0 = 0U;
        break;
    case SCM_SWTRIG1:
        scmRegPtr->SCM_MISCCTL1.SWTRIG1 = 0U;
        break;
    case SCM_SWTRIG2:
        scmRegPtr->SCM_MISCCTL1.SWTRIG2 = 0U;
        break;
    case SCM_SWTRIG3:
        scmRegPtr->SCM_MISCCTL1.SWTRIG3 = 0U;
        break;
    
    default:
        /* Do nothing */
        break;
    }
}

/**
 * @brief      Cache Enablement
 *
 * @param[in]  cacheCtrl: Disable or enable cache
 *                     - DISABLE
 *                     - ENABLE 
 *
 * @return     None
 *
 */
void SCM_CacheEnable(ControlState_t cacheCtrl)
{
    uint32_t cacheDisable;

    if (DISABLE == cacheCtrl)
    {
        cacheDisable = 1U;
    }
    else
    {
        cacheDisable = 0U;
    }
    
    scmRegPtr->SCM_MISCCTL1.CACHE_DIS = cacheDisable;
}

/**
 * @brief      Cache Parity Fault Enablement
 *
 * @param[in]  parityFaultCtrl: Disable or enable parity fault
 *                     - DISABLE
 *                     - ENABLE
 *
 * @return     None
 *
 */
void SCM_ParityFaultEnable(ControlState_t parityFaultCtrl)
{

    scmRegPtr->SCM_MISCCTL1.CCACHE_PARITY_FAULT_EN = (uint32_t)parityFaultCtrl;
}

/**
 * @brief      Cache Parity Miss Enablement.
 *             It is recommended to enable this feature when cache is enabled
 *
 * @param[in]  parityMissCtrl: Disable or enable parity miss
 *                     - DISABLE
 *                     - ENABLE
 *
 * @return     None
 *
 */
void SCM_ParityMissEnable(ControlState_t parityMissCtrl)
{

    scmRegPtr->SCM_MISCCTL1.CCACHE_PARITY_MISS_EN = (uint32_t)parityMissCtrl;
}

/**
 * @brief      Cache Clear
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void SCM_CacheClr(void)
{
    /* Perform Cache clear */
    scmRegPtr->SCM_MISCCTL1.CCACHE_CLR = 1U;
    /* Perform Cache clear disable*/
    scmRegPtr->SCM_MISCCTL1.CCACHE_CLR = 0U;
}

/**
 * @brief      Timer Input Clock Select
 *
 * @param[in]  timeType: Timer type
 *                     - SCM_TIM0_TYPE
 *                     - SCM_TIM1_TYPE
 *                     - SCM_TIM2_TYPE
 *                     - SCM_TIM3_TYPE
 *                     - SCM_MCPWM0_TYPE
 *                     - SCM_MCPWM1_TYPE

 * @param[in]  clkSource: Clock source
 *                     - SCM_TCLK0_TYPE
 *                     - SCM_TCLK1_TYPE
 *                     - SCM_TCLK2_TYPE
 *
 * @return     None
 *
 */
void SCM_TimerInputSelect(SCM_Timer_t timeType, SCM_TimerClockSource_t clkSource)
{
    switch(timeType)
    {
        case SCM_TIM0_TYPE:
            scmRegPtr->SCM_MISCCTL2.TIM0_TCLK_SEL = (uint32_t)clkSource;
            break;
        case SCM_TIM1_TYPE:
            scmRegPtr->SCM_MISCCTL2.TIM1_TCLK_SEL = (uint32_t)clkSource;
            break;
        case SCM_TIM2_TYPE:
            scmRegPtr->SCM_MISCCTL2.TIM2_TCLK_SEL = (uint32_t)clkSource;
            break;
        case SCM_TIM3_TYPE:
            scmRegPtr->SCM_MISCCTL2.TIM3_TCLK_SEL = (uint32_t)clkSource;
            break;
        case SCM_MCPWM0_TYPE:
            scmRegPtr->SCM_MISCCTL2.MCPWM0_TCLK_SEL = (uint32_t)clkSource;
            break;
        case SCM_MCPWM1_TYPE:
            scmRegPtr->SCM_MISCCTL2.MCPWM1_TCLK_SEL = (uint32_t)clkSource;
            break;
        default:
        /* Intentionally Empty */
            break;
    }
}

/**
 * @brief      ADC Channel Mux Select
 *
 * @param[in]  chType: Channel select type
 *                     - SCM_ADC1CH15_TYPE
 *                     - SCM_ADC1CH14_TYPE
 *                     - SCM_ADC0CH9_TYPE
 *                     - SCM_ADC0CH8_TYPE

 * @param[in]  muxSource: Mux select type
 *                     - SCM_ADCMUX0_TYPE
 *                     - SCM_ADCMUX1_TYPE
 *
 * @return     None
 *
 */
void SCM_AdcChannelMuxSelect(SCM_AdcChannelSelect_t chType, SCM_AdcMuxSelect_t muxSource)
{
    switch(chType)
    {
        case SCM_ADC1CH15_TYPE:
            scmRegPtr->SCM_MISCCTL2.ADC1_CH15_SEL = (uint32_t)muxSource;
            break;
        case SCM_ADC1CH14_TYPE:
            scmRegPtr->SCM_MISCCTL2.ADC1_CH14_SEL = (uint32_t)muxSource;
            break;
        case SCM_ADC0CH9_TYPE:
            scmRegPtr->SCM_MISCCTL2.ADC0_CH9_SEL = (uint32_t)muxSource;
            break;
        case SCM_ADC0CH8_TYPE:
            scmRegPtr->SCM_MISCCTL2.ADC0_CH8_SEL = (uint32_t)muxSource;
            break;
        default:
        /* Intentionally Empty */
            break;
    }
}

/**
 * @brief      Get Cache BE Address
 *
 * @param[in]  None
 *
 * @return     Address Information
 *
 */
uint32_t SCM_GetBEAddress(void)
{

    return (uint32_t)scmRegWPtr->SCM_MISCDATA1;
}

/**
 * @brief      Get Cache BE Data
 *
 * @param[in]  None
 *
 * @return     Data Information
 *
 */
uint32_t SCM_GetBEData(void)
{

    return (uint32_t)scmRegWPtr->SCM_MISCDATA2;
}

/**
 * @brief      Get Data Flash Size
 *
 * @param[in]  None
 *
 * @return     Data Flash Size
 *
 */
SCM_DataFlashSize_t SCM_GetDataFlashSize(void)
{

    return (SCM_DataFlashSize_t)scmRegPtr->SCM_FLSCFG.DFSIZE;
}

/**
 * @brief      Get Program Flash Size
 *
 * @param[in]  None
 *
 * @return     Program Flash Size
 *
 */
SCM_ProgramFlashSize_t SCM_GetProgramFlashSize(void)
{

    return (SCM_ProgramFlashSize_t)scmRegPtr->SCM_FLSCFG.PFSIZE;
}

/**
 * @brief      Get SRAM Size
 *
 * @param[in]  None
 *
 * @return     SRAM Flash Size
 *
 */
SCM_SramSize_t SCM_GetSramSize(void)
{

    return (SCM_SramSize_t)scmRegPtr->SCM_RAMCFG.RAMSIZE;
}

/**
 * @brief      Get Cache Size
 *
 * @param[in]  None
 *
 * @return     Cache Size
 *
 */
SCM_CacheSize_t SCM_GetCacheSize(void)
{

    return (SCM_CacheSize_t)scmRegPtr->SCM_RAMCFG.CACHESIZE;
}

/**
 * @brief      Get Device ID
 *
 * @param[in]  none
 *
 * @return     Device ID
 *
 */   
SCM_DeviceId_t SCM_GetDeviceId(void)
{
    SCM_DeviceId_t devId;

    devId.packageId = (uint8_t)(scmRegPtr->SCM_DEVID.PACKAGE_ID);
    devId.featureId = (uint8_t)(scmRegPtr->SCM_DEVID.FEATURE_ID);
    devId.RevisionId = (uint8_t)(scmRegPtr->SCM_DEVID.REV_ID);
    devId.familyId = (uint8_t)(scmRegPtr->SCM_DEVID.FAMILY_ID);
    devId.subFamilyId = (uint8_t)(scmRegPtr->SCM_DEVID.SUBFAMILY_ID);
    devId.seriesId = (uint8_t)(scmRegPtr->SCM_DEVID.SERIES_ID);
    devId.memSizeId = (uint8_t)(scmRegPtr->SCM_DEVID.MEMSIZE_ID);
    
    return devId;
}

/**
 * @brief      Get Unique Identification 0
 *
 * @param[in]  idType : Unique ID type
 *                   - SCM_UNIQUE0_TYPE
 *                   - SCM_UNIQUE1_TYPE
 *                   - SCM_UNIQUE2_TYPE
 *                   - SCM_UNIQUE3_TYPE
 *
 * @return     Unique IDx
 *
 */
uint32_t SCM_GetUniqueId(SCM_UniqueId_t idType)
{
    uint32_t uniqueID = 0U;

    switch(idType)
    {
        case SCM_UNIQUE0_TYPE:
            uniqueID = scmRegWPtr->SCM_UNIQUE0;
            break;
        case SCM_UNIQUE1_TYPE:
            uniqueID = scmRegWPtr->SCM_UNIQUE1;
            break;
        case SCM_UNIQUE2_TYPE:
            uniqueID = scmRegWPtr->SCM_UNIQUE2;
            break;
        case SCM_UNIQUE3_TYPE:
            uniqueID = scmRegWPtr->SCM_UNIQUE3;
            break;
        default:
        /* Intentionally Empty */
            break;
    }

    return uniqueID;
}

/** @} end of group SCM_Public_Functions */

/** @} end of group SCM driver modules */

/** @} end of group Z20K14XM_Peripheral_Driver */
