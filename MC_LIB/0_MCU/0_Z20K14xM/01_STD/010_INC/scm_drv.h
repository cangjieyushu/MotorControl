/**************************************************************************************************/
/**
 * @file     scm_drv.h
 * @brief    SCM driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef SCM_DRV_H
#define SCM_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SCM
 *  @{
 */

/** @defgroup SCM_Public_Types 
 *  @{
 */

/**  
 *  @brief SCM interrupt type definition
 */
typedef enum
{
    SCM_CCACHE_BE_INT         = 0U,               /*!< Cache write buffer error interrupt */
    SCM_FPU_INEXACT_INT       = 1U,               /*!< FPU inexat interrupt */
    SCM_FPU_OVERFLOW_INT      = 2U,               /*!< FPU overflow interrupt */
    SCM_FPU_UNDERFLOW_INT     = 3U,               /*!< FPU underflow interrupt */
    SCM_FPU_INVALIDOP_INT     = 4U,               /*!< FPU invalidop interrupt */
    SCM_FPU_DIVZERO_INT       = 5U,               /*!< FPU divzero interrupt */
    SCM_FPU_DENORMALIN_INT    = 6U,               /*!< FPU denormalin interrupt */
    SCM_INT_ALL               = 7U                /*!< All  interrupt */
} SCM_Int_t;

/**  
 *  @brief SCM software trigger type definition
 */
typedef enum
{
    SCM_SWTRIG0    = 1U,                   /*!< SWTRIG0 */
    SCM_SWTRIG1    = 2U,                   /*!< SWTRIG1 */
    SCM_SWTRIG2    = 4U,                   /*!< SWTRIG2 */
    SCM_SWTRIG3    = 8U                    /*!< SWTRIG3 */
} SCM_SwTrig_t;

/**
 *  @brief SRAM type definition
 */
typedef enum
{
    SCM_SRAML_TYPE    = 0U,                   /*!< SRAML */
    SCM_SRAMU_TYPE    = 1U                    /*!< SRAMU */
} SCM_Sram_t;

/**  
 *  @brief Timer type definition
 */
typedef enum
{
    SCM_TIM0_TYPE       = 0U,               /*!< PWM0 */
    SCM_TIM1_TYPE       = 1U,               /*!< PWM1 */
    SCM_TIM2_TYPE       = 2U,               /*!< PWM2 */
    SCM_TIM3_TYPE       = 3U,               /*!< PWM3 */
    SCM_MCPWM0_TYPE     = 4U,               /*!< MCPWM0 */
    SCM_MCPWM1_TYPE     = 5U                /*!< MCPWM1 */
} SCM_Timer_t;

/**  
 *  @brief Timer clock source definition
 */
typedef enum
{
    SCM_TCLK0_TYPE       = 0U,               /*!< Timer Clock source 0 */
    SCM_TCLK1_TYPE       = 1U,               /*!< Timer Clock source 1 */
    SCM_TCLK2_TYPE       = 2U                /*!< Timer Clock source 2 */
} SCM_TimerClockSource_t;

/**  
 *  @brief ADC channel select type definition
 */
typedef enum
{
    SCM_ADC1CH15_TYPE       = 0U,               /*!< ADC1 Channel15 Select */
    SCM_ADC1CH14_TYPE       = 1U,               /*!< ADC1 Channel14 Select */
    SCM_ADC0CH9_TYPE        = 2U,               /*!< ADC0 Channel9 Select */
    SCM_ADC0CH8_TYPE        = 3U                /*!< ADC0 Channel8 Select */
} SCM_AdcChannelSelect_t;

/**  
 *  @brief ADC mux select type definition
 */
typedef enum
{
    SCM_ADCMUX0_TYPE       = 0U,               /*!< ADC mux function0 */
    SCM_ADCMUX1_TYPE       = 1U                /*!< ADC mux function1 */
} SCM_AdcMuxSelect_t;


/**  
 *  @brief Data Flash Size definition
 */
typedef enum
{
    SCM_DFSIZE16K_TYPE       = 0U,               /*!< 16K */
    SCM_DFSIZE32K_TYPE       = 1U,               /*!< 32K */
    SCM_DFSIZE64K_TYPE       = 2U,               /*!< 64K */
    SCM_DFSIZE128K_TYPE      = 3U                /*!< 128K */
} SCM_DataFlashSize_t;

/**  
 *  @brief Program Flash Size definition
 */
typedef enum
{
    SCM_PFSIZE256K_TYPE       = 0U,               /*!< 256 */
    SCM_PFSIZE512K_TYPE       = 1U,               /*!< 512K */
    SCM_PFSIZE1M_TYPE         = 2U,               /*!< 1M */
    SCM_PFSIZE2M_TYPE         = 3U                /*!< 2M */
} SCM_ProgramFlashSize_t;

/**  
 *  @brief RAM Size definition
 */
typedef enum
{
    SCM_SRAMSIZE0_TYPE       = 0U,               /*!< sraml 0K, sramu 32K */
    SCM_SRAMSIZE1_TYPE       = 1U,               /*!< sraml 0K, sramu 64K */
    SCM_SRAMSIZE2_TYPE       = 2U,               /*!< sraml 0K, sramu 128K */
    SCM_SRAMSIZE3_TYPE       = 3U                /*!< sraml 128K, sramu 128K */
} SCM_SramSize_t;

/**  
 *  @brief Cache Size definition
 */
typedef enum
{
    SCM_CACHESIZE2K_TYPE       = 3U,               /*!< 2K */
    SCM_CACHESIZE4K_TYPE       = 4U                /*!< 4K */
} SCM_CacheSize_t;

/**  
 *  @brief Unique Identification definition
 */
typedef enum
{
    SCM_UNIQUE0_TYPE       = 0U,               /*!< UID_31_0 */
    SCM_UNIQUE1_TYPE       = 1U,               /*!< UID_63_32 */
    SCM_UNIQUE2_TYPE       = 2U,               /*!< UID_95_64 */
    SCM_UNIQUE3_TYPE       = 3U                /*!< UID_127_96 */
} SCM_UniqueId_t;

/**
 *  @brief SCM device ID struct definition
 */
typedef struct
{   
    uint8_t packageId;     /*!< Package ID*/
    uint8_t featureId;     /*!< Feature ID*/
    uint8_t RevisionId;    /*!< Revision ID*/
    uint8_t familyId;      /*!< Family ID*/
    uint8_t subFamilyId;   /*!< Sub Family ID*/
    uint8_t seriesId;      /*!< Series ID*/
    uint8_t memSizeId;     /*!< Memory size ID*/
}SCM_DeviceId_t;
/** @} end of group SCM_Public_Types */


/** @defgroup SCM_Public_FunctionDeclaration
 *  @brief SCM functions declaration
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
void SCM_IntMask(SCM_Int_t intType, IntMask_t intMask);


/**
 * @brief      install callback func
 *
 * @param[in]  intType: interrupt type id
 * @param[in]  cbFun  : callback function pointer
 *
 * @return     None
 *
 */
void SCM_InstallCallBackFunc(SCM_Int_t intType,isr_cb_t * cbFun);

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
void SCM_SwTrig(SCM_SwTrig_t swTrigType);

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
void SCM_ClearSwTrig(SCM_SwTrig_t swTrigType);

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
void SCM_CacheEnable(ControlState_t cacheCtrl);

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
void SCM_ParityFaultEnable(ControlState_t parityFaultCtrl);

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
void SCM_ParityMissEnable(ControlState_t parityMissCtrl);

/**
 * @brief      Cache Clear
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void SCM_CacheClr(void);

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
void SCM_TimerInputSelect(SCM_Timer_t timeType, SCM_TimerClockSource_t clkSource);

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
void SCM_AdcChannelMuxSelect(SCM_AdcChannelSelect_t chType, SCM_AdcMuxSelect_t muxSource);


/**
 * @brief      Get Cache BE Address
 *
 * @param[in]  None
 *
 * @return     Address Information
 *
 */
uint32_t SCM_GetBEAddress(void);

/**
 * @brief      Get Cache BE Data
 *
 * @param[in]  None
 *
 * @return     Data Information
 *
 */
uint32_t SCM_GetBEData(void);

/**
 * @brief      Get Data Flash Size
 *
 * @param[in]  None
 *
 * @return     Data Flash Size
 *
 */
SCM_DataFlashSize_t SCM_GetDataFlashSize(void);

/**
 * @brief      Get Program Flash Size
 *
 * @param[in]  None
 *
 * @return     Program Flash Size
 *
 */
SCM_ProgramFlashSize_t SCM_GetProgramFlashSize(void);

/**
 * @brief      Get SRAM Size
 *
 * @param[in]  None
 *
 * @return     SRAM Flash Size
 *
 */
SCM_SramSize_t SCM_GetSramSize(void);

/**
 * @brief      Get Cache Size
 *
 * @param[in]  None
 *
 * @return     Cache Size
 *
 */
SCM_CacheSize_t SCM_GetCacheSize(void);

/**
 * @brief      Get Device ID
 *
 * @param[in]  none
 *
 * @return     Device ID
 *
 */
SCM_DeviceId_t SCM_GetDeviceId(void);

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
uint32_t SCM_GetUniqueId(SCM_UniqueId_t idType);


/** @} end of group SCM_Public_FunctionDeclaration */

/** @} end of group SCM  */

/** @} end of group Z20K14XM_Peripheral_Driver */

#endif  /* SCM_DRV_H */
