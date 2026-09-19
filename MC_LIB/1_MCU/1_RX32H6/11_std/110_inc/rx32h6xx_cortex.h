/*********************************************************************************************
Copyright <2024> <Icore Technology (Nanjing)  Co.,Ltd>
All Rights Reserved,
Redistribution and use in source and binary forms, with or without modification, are permitted
provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this list of
conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or other materials provided 
with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors may be used to 
endorse or promote products derived from this software without specific prior written
permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS 
OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
OF THE POSSIBILITY OF SUCH DAMAGE.
**********************************************************************************************/

/*
*********************************************************************************************************
*                                              rx32h6xx
*                                           Library Function
*
*                                   Copyright 2024, RX Tech, Corp.
*                                        All Rights Reserved
*
*
* Project      : rx32h6xx
* File         : rx32h6xx_cortex.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __rx32h6xx_CORTEX_H
#define __rx32h6xx_CORTEX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "rx32h6xx.h"

/** @defgroup CORTEX_LL CORTEX
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup CORTEX_LL_Exported_Constants CORTEX Exported Constants
  * @{
  */

/** @defgroup CORTEX_LL_EC_CLKSOURCE_HCLK SYSTICK Clock Source
  * @{
  */
#define SYSTICK_CLKSOURCE_HCLK_DIV8     0x00000000U                 /*!< AHB clock divided by 8 selected as SysTick clock source.*/
#define SYSTICK_CLKSOURCE_HCLK          SysTick_CTRL_CLKSOURCE_Msk  /*!< AHB clock selected as SysTick clock source. */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_FAULT Handler Fault type
  * @{
  */
#define HANDLER_FAULT_USG               SCB_SHCSR_USGFAULTENA_Msk              /*!< Usage fault */
#define HANDLER_FAULT_BUS               SCB_SHCSR_BUSFAULTENA_Msk              /*!< Bus fault */
#define HANDLER_FAULT_MEM               SCB_SHCSR_MEMFAULTENA_Msk              /*!< Memory management fault */
/**
  * @}
  */

#if __MPU_PRESENT

/** @defgroup CORTEX_LL_EC_CTRL_HFNMI_PRIVDEF MPU Control
  * @{
  */
#define MPU_CTRL_HFNMI_PRIVDEF_NONE     0x00000000U                                       /*!< Disable NMI and privileged SW access */
#define MPU_CTRL_HARDFAULT_NMI          MPU_CTRL_HFNMIENA_Msk                             /*!< Enables the operation of MPU during hard fault, NMI, and FAULTMASK handlers */
#define MPU_CTRL_PRIVILEGED_DEFAULT     MPU_CTRL_PRIVDEFENA_Msk                           /*!< Enable privileged software access to default memory map */
#define MPU_CTRL_HFNMI_PRIVDEF          (MPU_CTRL_HFNMIENA_Msk | MPU_CTRL_PRIVDEFENA_Msk) /*!< Enable NMI and privileged SW access */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_REGION MPU Region Number
  * @{
  */
#define MPU_REGION_NUMBER0              0x00U /*!< REGION Number 0 */
#define MPU_REGION_NUMBER1              0x01U /*!< REGION Number 1 */
#define MPU_REGION_NUMBER2              0x02U /*!< REGION Number 2 */
#define MPU_REGION_NUMBER3              0x03U /*!< REGION Number 3 */
#define MPU_REGION_NUMBER4              0x04U /*!< REGION Number 4 */
#define MPU_REGION_NUMBER5              0x05U /*!< REGION Number 5 */
#define MPU_REGION_NUMBER6              0x06U /*!< REGION Number 6 */
#define MPU_REGION_NUMBER7              0x07U /*!< REGION Number 7 */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_REGION_SIZE MPU Region Size
  * @{
  */
#define MPU_REGION_SIZE_32B             (0x04U << MPU_RASR_SIZE_Pos) /*!< 32B Size of the MPU protection region */
#define MPU_REGION_SIZE_64B             (0x05U << MPU_RASR_SIZE_Pos) /*!< 64B Size of the MPU protection region */
#define MPU_REGION_SIZE_128B            (0x06U << MPU_RASR_SIZE_Pos) /*!< 128B Size of the MPU protection region */
#define MPU_REGION_SIZE_256B            (0x07U << MPU_RASR_SIZE_Pos) /*!< 256B Size of the MPU protection region */
#define MPU_REGION_SIZE_512B            (0x08U << MPU_RASR_SIZE_Pos) /*!< 512B Size of the MPU protection region */
#define MPU_REGION_SIZE_1KB             (0x09U << MPU_RASR_SIZE_Pos) /*!< 1KB Size of the MPU protection region */
#define MPU_REGION_SIZE_2KB             (0x0AU << MPU_RASR_SIZE_Pos) /*!< 2KB Size of the MPU protection region */
#define MPU_REGION_SIZE_4KB             (0x0BU << MPU_RASR_SIZE_Pos) /*!< 4KB Size of the MPU protection region */
#define MPU_REGION_SIZE_8KB             (0x0CU << MPU_RASR_SIZE_Pos) /*!< 8KB Size of the MPU protection region */
#define MPU_REGION_SIZE_16KB            (0x0DU << MPU_RASR_SIZE_Pos) /*!< 16KB Size of the MPU protection region */
#define MPU_REGION_SIZE_32KB            (0x0EU << MPU_RASR_SIZE_Pos) /*!< 32KB Size of the MPU protection region */
#define MPU_REGION_SIZE_64KB            (0x0FU << MPU_RASR_SIZE_Pos) /*!< 64KB Size of the MPU protection region */
#define MPU_REGION_SIZE_128KB           (0x10U << MPU_RASR_SIZE_Pos) /*!< 128KB Size of the MPU protection region */
#define MPU_REGION_SIZE_256KB           (0x11U << MPU_RASR_SIZE_Pos) /*!< 256KB Size of the MPU protection region */
#define MPU_REGION_SIZE_512KB           (0x12U << MPU_RASR_SIZE_Pos) /*!< 512KB Size of the MPU protection region */
#define MPU_REGION_SIZE_1MB             (0x13U << MPU_RASR_SIZE_Pos) /*!< 1MB Size of the MPU protection region */
#define MPU_REGION_SIZE_2MB             (0x14U << MPU_RASR_SIZE_Pos) /*!< 2MB Size of the MPU protection region */
#define MPU_REGION_SIZE_4MB             (0x15U << MPU_RASR_SIZE_Pos) /*!< 4MB Size of the MPU protection region */
#define MPU_REGION_SIZE_8MB             (0x16U << MPU_RASR_SIZE_Pos) /*!< 8MB Size of the MPU protection region */
#define MPU_REGION_SIZE_16MB            (0x17U << MPU_RASR_SIZE_Pos) /*!< 16MB Size of the MPU protection region */
#define MPU_REGION_SIZE_32MB            (0x18U << MPU_RASR_SIZE_Pos) /*!< 32MB Size of the MPU protection region */
#define MPU_REGION_SIZE_64MB            (0x19U << MPU_RASR_SIZE_Pos) /*!< 64MB Size of the MPU protection region */
#define MPU_REGION_SIZE_128MB           (0x1AU << MPU_RASR_SIZE_Pos) /*!< 128MB Size of the MPU protection region */
#define MPU_REGION_SIZE_256MB           (0x1BU << MPU_RASR_SIZE_Pos) /*!< 256MB Size of the MPU protection region */
#define MPU_REGION_SIZE_512MB           (0x1CU << MPU_RASR_SIZE_Pos) /*!< 512MB Size of the MPU protection region */
#define MPU_REGION_SIZE_1GB             (0x1DU << MPU_RASR_SIZE_Pos) /*!< 1GB Size of the MPU protection region */
#define MPU_REGION_SIZE_2GB             (0x1EU << MPU_RASR_SIZE_Pos) /*!< 2GB Size of the MPU protection region */
#define MPU_REGION_SIZE_4GB             (0x1FU << MPU_RASR_SIZE_Pos) /*!< 4GB Size of the MPU protection region */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_REGION_PRIVILEDGES MPU Region Privileges
  * @{
  */
#define MPU_REGION_NO_ACCESS            (0x00U << MPU_RASR_AP_Pos) /*!< No access*/
#define MPU_REGION_PRIV_RW              (0x01U << MPU_RASR_AP_Pos) /*!< RW privileged (privileged access only)*/
#define MPU_REGION_PRIV_RW_URO          (0x02U << MPU_RASR_AP_Pos) /*!< RW privileged - RO user (Write in a user program generates a fault) */
#define MPU_REGION_FULL_ACCESS          (0x03U << MPU_RASR_AP_Pos) /*!< RW privileged & user (Full access) */
#define MPU_REGION_PRIV_RO              (0x05U << MPU_RASR_AP_Pos) /*!< RO privileged (privileged read only)*/
#define MPU_REGION_PRIV_RO_URO          (0x06U << MPU_RASR_AP_Pos) /*!< RO privileged & user (read only) */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_TEX MPU TEX Level
  * @{
  */
#define MPU_TEX_LEVEL0                  (0x00U << MPU_RASR_TEX_Pos) /*!< b000 for TEX bits */
#define MPU_TEX_LEVEL1                  (0x01U << MPU_RASR_TEX_Pos) /*!< b001 for TEX bits */
#define MPU_TEX_LEVEL2                  (0x02U << MPU_RASR_TEX_Pos) /*!< b010 for TEX bits */
#define MPU_TEX_LEVEL4                  (0x04U << MPU_RASR_TEX_Pos) /*!< b100 for TEX bits */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_INSTRUCTION_ACCESS MPU Instruction Access
  * @{
  */
#define MPU_INSTRUCTION_ACCESS_ENABLE   0x00U            /*!< Instruction fetches enabled */
#define MPU_INSTRUCTION_ACCESS_DISABLE  MPU_RASR_XN_Msk  /*!< Instruction fetches disabled*/
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_SHAREABLE_ACCESS MPU Shareable Access
  * @{
  */
#define MPU_ACCESS_SHAREABLE            MPU_RASR_S_Msk   /*!< Shareable memory attribute */
#define MPU_ACCESS_NOT_SHAREABLE        0x00U            /*!< Not Shareable memory attribute */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_CACHEABLE_ACCESS MPU Cacheable Access
  * @{
  */
#define MPU_ACCESS_CACHEABLE            MPU_RASR_C_Msk   /*!< Cacheable memory attribute */
#define MPU_ACCESS_NOT_CACHEABLE        0x00U            /*!< Not Cacheable memory attribute */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_BUFFERABLE_ACCESS MPU Bufferable Access
  * @{
  */
#define MPU_ACCESS_BUFFERABLE           MPU_RASR_B_Msk   /*!< Bufferable memory attribute */
#define MPU_ACCESS_NOT_BUFFERABLE       0x00U            /*!< Not Bufferable memory attribute */
/**
  * @}
  */
#endif /* __MPU_PRESENT */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup CORTEX_LL_Exported_Functions CORTEX Exported Functions
  * @{
  */

/** @defgroup CORTEX_LL_EF_SYSTICK SYSTICK
  * @{
  */

/**
  * @brief  This function checks if the Systick counter flag is active or not.
  * @note   It can be used in timeout function on application side.
  * @rmtoll STK_CTRL     COUNTFLAG     SYSTICK_IsActiveCounterFlag
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t SYSTICK_IsActiveCounterFlag(void)
{
  return ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == (SysTick_CTRL_COUNTFLAG_Msk));
}

/**
  * @brief  Configures the SysTick clock source
  * @rmtoll STK_CTRL     CLKSOURCE     SYSTICK_SetClkSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref SYSTICK_CLKSOURCE_HCLK_DIV8
  *         @arg @ref SYSTICK_CLKSOURCE_HCLK
  * @retval None
  */
__STATIC_INLINE void SYSTICK_SetClkSource(uint32_t Source)
{
  if (Source == SYSTICK_CLKSOURCE_HCLK)
  {
    SET_BIT(SysTick->CTRL, SYSTICK_CLKSOURCE_HCLK);
  }
  else
  {
    CLEAR_BIT(SysTick->CTRL, SYSTICK_CLKSOURCE_HCLK);
  }
}

/**
  * @brief  Get the SysTick clock source
  * @rmtoll STK_CTRL     CLKSOURCE     SYSTICK_GetClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref SYSTICK_CLKSOURCE_HCLK_DIV8
  *         @arg @ref SYSTICK_CLKSOURCE_HCLK
  */
__STATIC_INLINE uint32_t SYSTICK_GetClkSource(void)
{
  return READ_BIT(SysTick->CTRL, SYSTICK_CLKSOURCE_HCLK);
}

/**
  * @brief  Enable SysTick exception request
  * @rmtoll STK_CTRL     TICKINT       SYSTICK_EnableIT
  * @retval None
  */
__STATIC_INLINE void SYSTICK_EnableIT(void)
{
  SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief  Disable SysTick exception request
  * @rmtoll STK_CTRL     TICKINT       SYSTICK_DisableIT
  * @retval None
  */
__STATIC_INLINE void SYSTICK_DisableIT(void)
{
  CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief  Checks if the SYSTICK interrupt is enabled or disabled.
  * @rmtoll STK_CTRL     TICKINT       SYSTICK_IsEnabledIT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t SYSTICK_IsEnabledIT(void)
{
  return (READ_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk) == (SysTick_CTRL_TICKINT_Msk));
}

/**
  * @}
  */

/** @defgroup CORTEX_LL_EF_LOW_POWER_MODE LOW POWER MODE
  * @{
  */

/**
  * @brief  Processor uses sleep as its low power mode
  * @rmtoll SCB_SCR      SLEEPDEEP     LPM_EnableSleep
  * @retval None
  */
__STATIC_INLINE void LPM_EnableSleep(void)
{
  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief  Processor uses deep sleep as its low power mode
  * @rmtoll SCB_SCR      SLEEPDEEP     LPM_EnableDeepSleep
  * @retval None
  */
__STATIC_INLINE void LPM_EnableDeepSleep(void)
{
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief  Configures sleep-on-exit when returning from Handler mode to Thread mode.
  * @note   Setting this bit to 1 enables an interrupt-driven application to avoid returning to an
  *         empty main application.
  * @rmtoll SCB_SCR      SLEEPONEXIT   LPM_EnableSleepOnExit
  * @retval None
  */
__STATIC_INLINE void LPM_EnableSleepOnExit(void)
{
  /* Set SLEEPONEXIT bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}

/**
  * @brief  Do not sleep when returning to Thread mode.
  * @rmtoll SCB_SCR      SLEEPONEXIT   LPM_DisableSleepOnExit
  * @retval None
  */
__STATIC_INLINE void LPM_DisableSleepOnExit(void)
{
  /* Clear SLEEPONEXIT bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}

/**
  * @brief  Enabled events and all interrupts, including disabled interrupts, can wakeup the
  *         processor.
  * @rmtoll SCB_SCR      SEVEONPEND    LPM_EnableEventOnPend
  * @retval None
  */
__STATIC_INLINE void LPM_EnableEventOnPend(void)
{
  /* Set SEVEONPEND bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}

/**
  * @brief  Only enabled interrupts or events can wakeup the processor, disabled interrupts are
  *         excluded
  * @rmtoll SCB_SCR      SEVEONPEND    LPM_DisableEventOnPend
  * @retval None
  */
__STATIC_INLINE void LPM_DisableEventOnPend(void)
{
  /* Clear SEVEONPEND bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}

/**
  * @}
  */

/** @defgroup CORTEX_LL_EF_HANDLER HANDLER
  * @{
  */

/**
  * @brief  Enable a fault in System handler control register (SHCSR)
  * @rmtoll SCB_SHCSR    MEMFAULTENA   HANDLER_EnableFault
  * @param  Fault This parameter can be a combination of the following values:
  *         @arg @ref HANDLER_FAULT_USG
  *         @arg @ref HANDLER_FAULT_BUS
  *         @arg @ref HANDLER_FAULT_MEM
  * @retval None
  */
__STATIC_INLINE void HANDLER_EnableFault(uint32_t Fault)
{
  /* Enable the system handler fault */
  SET_BIT(SCB->SHCSR, Fault);
}

/**
  * @brief  Disable a fault in System handler control register (SHCSR)
  * @rmtoll SCB_SHCSR    MEMFAULTENA   HANDLER_DisableFault
  * @param  Fault This parameter can be a combination of the following values:
  *         @arg @ref HANDLER_FAULT_USG
  *         @arg @ref HANDLER_FAULT_BUS
  *         @arg @ref HANDLER_FAULT_MEM
  * @retval None
  */
__STATIC_INLINE void HANDLER_DisableFault(uint32_t Fault)
{
  /* Disable the system handler fault */
  CLEAR_BIT(SCB->SHCSR, Fault);
}

/**
  * @}
  */

/** @defgroup CORTEX_LL_EF_MCU_INFO MCU INFO
  * @{
  */

/**
  * @brief  Get Implementer code
  * @rmtoll SCB_CPUID    IMPLEMENTER   CPUID_GetImplementer
  * @retval Value should be equal to 0x41 for ARM
  */
__STATIC_INLINE uint32_t CPUID_GetImplementer(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_IMPLEMENTER_Msk) >> SCB_CPUID_IMPLEMENTER_Pos);
}

/**
  * @brief  Get Variant number (The r value in the rnpn product revision identifier)
  * @rmtoll SCB_CPUID    VARIANT       CPUID_GetVariant
  * @retval Value between 0 and 255 (0x1: revision 1, 0x2: revision 2)
  */
__STATIC_INLINE uint32_t CPUID_GetVariant(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_VARIANT_Msk) >> SCB_CPUID_VARIANT_Pos);
}

/**
  * @brief  Get Constant number
  * @rmtoll SCB_CPUID    ARCHITECTURE  CPUID_GetConstant
  * @retval Value should be equal to 0xF for Cortex-M3 devices
  */
__STATIC_INLINE uint32_t CPUID_GetConstant(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_ARCHITECTURE_Msk) >> SCB_CPUID_ARCHITECTURE_Pos);
}

/**
  * @brief  Get Part number
  * @rmtoll SCB_CPUID    PARTNO        CPUID_GetParNo
  * @retval Value should be equal to 0xC23 for Cortex-M3
  */
__STATIC_INLINE uint32_t CPUID_GetParNo(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_PARTNO_Msk) >> SCB_CPUID_PARTNO_Pos);
}

/**
  * @brief  Get Revision number (The p value in the rnpn product revision identifier, indicates patch release)
  * @rmtoll SCB_CPUID    REVISION      CPUID_GetRevision
  * @retval Value between 0 and 255 (0x0: patch 0, 0x1: patch 1)
  */
__STATIC_INLINE uint32_t CPUID_GetRevision(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_REVISION_Msk) >> SCB_CPUID_REVISION_Pos);
}

/**
  * @}
  */

#if __MPU_PRESENT
/** @defgroup CORTEX_LL_EF_MPU MPU
  * @{
  */

/**
  * @brief  Enable MPU with input options
  * @rmtoll MPU_CTRL     ENABLE        MPU_Enable
  * @param  Options This parameter can be one of the following values:
  *         @arg @ref MPU_CTRL_HFNMI_PRIVDEF_NONE
  *         @arg @ref MPU_CTRL_HARDFAULT_NMI
  *         @arg @ref MPU_CTRL_PRIVILEGED_DEFAULT
  *         @arg @ref MPU_CTRL_HFNMI_PRIVDEF
  * @retval None
  */
__STATIC_INLINE void MPU_Enable(uint32_t Options)
{
  /* Enable the MPU*/
  WRITE_REG(MPU->CTRL, (MPU_CTRL_ENABLE_Msk | Options));
  /* Ensure MPU settings take effects */
  __DSB();
  /* Sequence instruction fetches using update settings */
  __ISB();
}

/**
  * @brief  Disable MPU
  * @rmtoll MPU_CTRL     ENABLE        MPU_Disable
  * @retval None
  */
__STATIC_INLINE void MPU_Disable(void)
{
  /* Make sure outstanding transfers are done */
  __DMB();
  /* Disable MPU*/
  WRITE_REG(MPU->CTRL, 0U);
}

/**
  * @brief  Check if MPU is enabled or not
  * @rmtoll MPU_CTRL     ENABLE        MPU_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MPU_IsEnabled(void)
{
  return (READ_BIT(MPU->CTRL, MPU_CTRL_ENABLE_Msk) == (MPU_CTRL_ENABLE_Msk));
}

/**
  * @brief  Enable a MPU region
  * @rmtoll MPU_RASR     ENABLE        MPU_EnableRegion
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref MPU_REGION_NUMBER0
  *         @arg @ref MPU_REGION_NUMBER1
  *         @arg @ref MPU_REGION_NUMBER2
  *         @arg @ref MPU_REGION_NUMBER3
  *         @arg @ref MPU_REGION_NUMBER4
  *         @arg @ref MPU_REGION_NUMBER5
  *         @arg @ref MPU_REGION_NUMBER6
  *         @arg @ref MPU_REGION_NUMBER7
  * @retval None
  */
__STATIC_INLINE void MPU_EnableRegion(uint32_t Region)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);
  /* Enable the MPU region */
  SET_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
}

/**
  * @brief  Configure and enable a region
  * @rmtoll MPU_RNR      REGION        MPU_ConfigRegion\n
  *         MPU_RBAR     REGION        MPU_ConfigRegion\n
  *         MPU_RBAR     ADDR          MPU_ConfigRegion\n
  *         MPU_RASR     XN            MPU_ConfigRegion\n
  *         MPU_RASR     AP            MPU_ConfigRegion\n
  *         MPU_RASR     S             MPU_ConfigRegion\n
  *         MPU_RASR     C             MPU_ConfigRegion\n
  *         MPU_RASR     B             MPU_ConfigRegion\n
  *         MPU_RASR     SIZE          MPU_ConfigRegion
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref MPU_REGION_NUMBER0
  *         @arg @ref MPU_REGION_NUMBER1
  *         @arg @ref MPU_REGION_NUMBER2
  *         @arg @ref MPU_REGION_NUMBER3
  *         @arg @ref MPU_REGION_NUMBER4
  *         @arg @ref MPU_REGION_NUMBER5
  *         @arg @ref MPU_REGION_NUMBER6
  *         @arg @ref MPU_REGION_NUMBER7
  * @param  Address Value of region base address
  * @param  SubRegionDisable Sub-region disable value between Min_Data = 0x00 and Max_Data = 0xFF
  * @param  Attributes This parameter can be a combination of the following values:
  *         @arg @ref MPU_REGION_SIZE_32B or @ref MPU_REGION_SIZE_64B or @ref MPU_REGION_SIZE_128B or @ref MPU_REGION_SIZE_256B or @ref MPU_REGION_SIZE_512B
  *           or @ref MPU_REGION_SIZE_1KB or @ref MPU_REGION_SIZE_2KB or @ref MPU_REGION_SIZE_4KB or @ref MPU_REGION_SIZE_8KB or @ref MPU_REGION_SIZE_16KB
  *           or @ref MPU_REGION_SIZE_32KB or @ref MPU_REGION_SIZE_64KB or @ref MPU_REGION_SIZE_128KB or @ref MPU_REGION_SIZE_256KB or @ref MPU_REGION_SIZE_512KB
  *           or @ref MPU_REGION_SIZE_1MB or @ref MPU_REGION_SIZE_2MB or @ref MPU_REGION_SIZE_4MB or @ref MPU_REGION_SIZE_8MB or @ref MPU_REGION_SIZE_16MB
  *           or @ref MPU_REGION_SIZE_32MB or @ref MPU_REGION_SIZE_64MB or @ref MPU_REGION_SIZE_128MB or @ref MPU_REGION_SIZE_256MB or @ref MPU_REGION_SIZE_512MB
  *           or @ref MPU_REGION_SIZE_1GB or @ref MPU_REGION_SIZE_2GB or @ref MPU_REGION_SIZE_4GB
  *         @arg @ref MPU_REGION_NO_ACCESS or @ref MPU_REGION_PRIV_RW or @ref MPU_REGION_PRIV_RW_URO or @ref MPU_REGION_FULL_ACCESS
  *           or @ref MPU_REGION_PRIV_RO or @ref MPU_REGION_PRIV_RO_URO
  *         @arg @ref MPU_TEX_LEVEL0 or @ref MPU_TEX_LEVEL1 or @ref MPU_TEX_LEVEL2 or @ref MPU_TEX_LEVEL4
  *         @arg @ref MPU_INSTRUCTION_ACCESS_ENABLE or  @ref MPU_INSTRUCTION_ACCESS_DISABLE
  *         @arg @ref MPU_ACCESS_SHAREABLE or @ref MPU_ACCESS_NOT_SHAREABLE
  *         @arg @ref MPU_ACCESS_CACHEABLE or @ref MPU_ACCESS_NOT_CACHEABLE
  *         @arg @ref MPU_ACCESS_BUFFERABLE or @ref MPU_ACCESS_NOT_BUFFERABLE
  * @retval None
  */
__STATIC_INLINE void MPU_ConfigRegion(uint32_t Region, uint32_t SubRegionDisable, uint32_t Address, uint32_t Attributes)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);
  /* Set base address */
  WRITE_REG(MPU->RBAR, (Address & 0xFFFFFFE0U));
  /* Configure MPU */
  WRITE_REG(MPU->RASR, (MPU_RASR_ENABLE_Msk | Attributes | SubRegionDisable << MPU_RASR_SRD_Pos));
}

/**
  * @brief  Disable a region
  * @rmtoll MPU_RNR      REGION        MPU_DisableRegion\n
  *         MPU_RASR     ENABLE        MPU_DisableRegion
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref MPU_REGION_NUMBER0
  *         @arg @ref MPU_REGION_NUMBER1
  *         @arg @ref MPU_REGION_NUMBER2
  *         @arg @ref MPU_REGION_NUMBER3
  *         @arg @ref MPU_REGION_NUMBER4
  *         @arg @ref MPU_REGION_NUMBER5
  *         @arg @ref MPU_REGION_NUMBER6
  *         @arg @ref MPU_REGION_NUMBER7
  * @retval None
  */
__STATIC_INLINE void MPU_DisableRegion(uint32_t Region)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);
  /* Disable the MPU region */
  CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
}

/**
  * @}
  */

#endif /* __MPU_PRESENT */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
