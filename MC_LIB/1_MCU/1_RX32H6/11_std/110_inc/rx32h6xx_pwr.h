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
* File         : rx32h6xx_pwr.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/
#ifndef __rx32h6xx_PWR_H__
#define __rx32h6xx_PWR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rx32h6xx.h"

/******************************************************************************/
/*                                                                            */
/*                             Power Control                                  */
/*                                                                            */
/******************************************************************************/
#if defined(PWR)

/** @defgroup PWR
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */

/********************  Bit definition for PWR_CR1 register  ********************/
#define PWR_CR1_LPMS_Pos                     (0U)
#define PWR_CR1_LPMS_Msk                     (0x3U << PWR_CR1_LPMS_Pos)          /*!< 0x00000001 */
#define PWR_CR1_LPMS                         PWR_CR1_LPMS_Msk                    /*!< Low-Power Deepsleep */
#define PWR_CR1_LPMS_0                       ((uint32_t)0x00000000U)             /*!< STOP 0 */
#define PWR_CR1_LPMS_1                       ((uint32_t)0x00000001U)             /*!< STOP 1 */
#define PWR_CR1_LPMS_3                       ((uint32_t)0x00000003U)             /*!< STANDBY */

#define PWR_CR1_DBP_Pos                      (8U)
#define PWR_CR1_DBP_Msk                      (0x1U << PWR_CR1_DBP_Pos)          /*!< 0x00000001 */
#define PWR_CR1_DBP                          PWR_CR1_DBP_Msk                    /*!< Low-Power Deepsleep */

/*******************  Bit definition for PWR_CR2 register  ********************/
#define PWR_CR2_PVDE_Pos                     (0U)
#define PWR_CR2_PVDE_Msk                     (0x1U << PWR_CR2_PVDE_Pos)          /*!< 0x00000010 */
#define PWR_CR2_PVDE                         PWR_CR2_PVDE_Msk                    /*!< Power Voltage Detector Enable */
              
#define PWR_CR2_PLS_Pos                      (1U)
#define PWR_CR2_PLS_Msk                      (0x7U << PWR_CR2_PLS_Pos)           /*!< 0x000000E0 */
#define PWR_CR2_PLS                          PWR_CR2_PLS_Msk                     /*!< PLS[2:0] bits (PVD Level Selection) */

#define PWR_CR2_PLS_2V2                        0x00<<1
#define PWR_CR2_PLS_2V3                        0x01<<1
#define PWR_CR2_PLS_2V4                        0x02<<1
#define PWR_CR2_PLS_2V5                        0x03<<1
#define PWR_CR2_PLS_2V6                        0x04<<1
#define PWR_CR2_PLS_2V7                        0x05<<1
#define PWR_CR2_PLS_2V8                        0x06<<1
#define PWR_CR2_PLS_2V9                        0x07<<1

/*******************  Bit definition for PWR_CR3 register  ********************/
#define PWR_CR3_EWUP1_Pos                   (0U)
#define PWR_CR3_EWUP1_Msk                   (0x1U << PWR_CR3_EWUP1_Pos)         /*!< 0x00000001 */
#define PWR_CR3_EWUP1                       PWR_CR3_EWUP1_Msk                   
#define PWR_CR3_EIWUL_Pos                   (15U)
#define PWR_CR3_EIWUL_Msk                   (0x1U << PWR_CR3_EIWUL_Pos)         /*!< 0x00000100 */
#define PWR_CR3_EIWUL                       PWR_CR3_EIWUL_Msk                   

/*******************  Bit definition for PWR_CR4 register  ********************/
#define PWR_CR4_WP1_Pos                     (0U)
#define PWR_CR4_WP1_Msk                     (0x1U << PWR_CR4_WP1_Pos)         /*!< 0x00000001 */
#define PWR_CR4_WP1                         PWR_CR4_WP1_Msk                   

/*******************  Bit definition for PWR_SR register  ********************/
#define PWR_SR_WUF1_Pos                     (0U)
#define PWR_SR_WUF1_Msk                     (0x1U << PWR_SR_WUF1_Pos)         /*!< 0x00000100 */
#define PWR_SR_WUF1                         PWR_SR_WUF1_Msk                   
#define PWR_SR_SBF_Pos                      (8U)
#define PWR_SR_SBF_Msk                      (0x1U << PWR_SR_SBF_Pos)         /*!< 0x00000100 */
#define PWR_SR_SBF                          PWR_SR_SBF_Msk                  
#define PWR_SR_WUFI_Pos                     (15U)
#define PWR_SR_WUFI_Msk                     (0x1U << PWR_SR_WUFI_Pos)         /*!< 0x00000100 */
#define PWR_SR_WUFI                         PWR_SR_WUFI_Msk      

/*******************  Bit definition for PWR_SR2 register  ********************/

#define PWR_SR2_PVDO_Pos                    (11U)
#define PWR_SR2_PVDO_Msk                    (0x1U << PWR_SR2_PVDO_Pos)         /*!< 0x00000004 */
#define PWR_SR2_PVDO                        PWR_SR2_PVDO_Msk           

/*******************  Bit definition for PWR_SCR register  ********************/
#define PWR_SCR_CWUF1_Pos                     (0U)
#define PWR_SCR_CWUF1_Msk                     (0x1U << PWR_SCR_CWUF1_Pos)         /*!< 0x00000100 */
#define PWR_SCR_CWUF1                         PWR_SCR_CWUF1_Msk                   
#define PWR_SCR_CSBF_Pos                      (8U)
#define PWR_SCR_CSBF_Msk                      (0x1U << PWR_SCR_CSBF_Pos)         /*!< 0x00000100 */
#define PWR_SCR_CSBF                          PWR_SCR_CSBF_Msk                   
#define PWR_SCR_CWUFI_Pos                     (15U)
#define PWR_SCR_CWUFI_Msk                     (0x1U << PWR_SCR_CWUFI_Pos)         /*!< 0x00000100 */
#define PWR_SCR_CWUFI                         PWR_SCR_CWUFI_Msk                   

/** @defgroup PWR_EC_MODE_PWR Mode Power
  * @{
  */
#define PWR_MODE_STOP_MAINREGU             (PWR_CR1_LPMS_0)                    /*!< Enter Stop mode when the CPU enters deepsleep */
#define PWR_MODE_STOP_LPREGU               (PWR_CR1_LPMS_1)                  /*!< Enter Stop mode (with low power Regulator ON) when the CPU enters deepsleep */
#define PWR_MODE_STANDBY                   (PWR_CR1_LPMS_3)                  /*!< Enter Standby mode when the CPU enters deepsleep */

/** @defgroup PWR_EC_REGU_MODE_DS_MODE  Regulator Mode In Deep Sleep Mode
 * @{
 */
#define PWR_REGU_DSMODE_MAIN        0x00000000U           /*!< Voltage Regulator in main mode during deepsleep mode */
#define PWR_REGU_DSMODE_LOW_POWER   (PWR_CR_LPDS)         /*!< Voltage Regulator in low-power mode during deepsleep mode */

/** @defgroup PWR_EC_PVDLEVEL Power Voltage Detector Level
  * @{
  */
#define PWR_PVDLEVEL_0                  (PWR_CR2_PLS_LEV0)      /*!< Voltage threshold detected by PVD 2.2 V */
#define PWR_PVDLEVEL_1                  (PWR_CR2_PLS_LEV1)      /*!< Voltage threshold detected by PVD 2.3 V */
#define PWR_PVDLEVEL_2                  (PWR_CR2_PLS_LEV2)      /*!< Voltage threshold detected by PVD 2.4 V */
#define PWR_PVDLEVEL_3                  (PWR_CR2_PLS_LEV3)      /*!< Voltage threshold detected by PVD 2.5 V */
#define PWR_PVDLEVEL_4                  (PWR_CR2_PLS_LEV4)      /*!< Voltage threshold detected by PVD 2.6 V */
#define PWR_PVDLEVEL_5                  (PWR_CR2_PLS_LEV5)      /*!< Voltage threshold detected by PVD 2.7 V */
#define PWR_PVDLEVEL_6                  (PWR_CR2_PLS_LEV6)      /*!< Voltage threshold detected by PVD 2.8 V */
#define PWR_PVDLEVEL_7                  (PWR_CR2_PLS_LEV7)      /*!< Voltage threshold detected by PVD 2.9 V */

/** @defgroup PWR_EC_WAKEUP_PIN  Wakeup Pins
  * @{
  */
#define PWR_WAKEUP_PIN1                 (PWR_CR3_EWUP1)         /*!< WKUP pin 1 : PD4 */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWR_Exported_Macros PWR Exported Macros
  * @{
  */

/** @defgroup PWR_EM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in PWR register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define PWR_WriteReg(__REG__, __VALUE__) WRITE_REG(PWR->__REG__, (__VALUE__))

/**
  * @brief  Read a value in PWR register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define PWR_ReadReg(__REG__) READ_REG(PWR->__REG__)

#define PWR_STOPEntry_WFI      ((uint8_t)0x01)
#define PWR_STOPEntry_WFE      ((uint8_t)0x02)
#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPEntry_WFI))  || (((ENTRY) == PWR_STOPEntry_WFE)) 

/**
  * @function  PWR_Enable_BkUpAccess
  * @brief  Enable access to the backup domain
  * @param  None
  * @retval None
  */
__STATIC_INLINE void PWR_Enable_BkUpAccess(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @function  PWR_Disable_BkUpAccess
  * @brief  Disable access to the backup domain
  * @param  None
  * @retval None
  */
__STATIC_INLINE void PWR_Disable_BkUpAccess(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @function  PWR_Get_BkUpAccess
  * @brief  Check if the backup domain is enabled
  * @param  None
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t PWR_Get_BkUpAccess(void)
{
  return (READ_BIT(PWR->CR1, PWR_CR1_DBP) == (PWR_CR1_DBP));
}

/**
  * @function  PWR_Set_PowerMode
  * @brief  Set Power Down mode when CPU enters deepsleep
  * @param  PDMode :
  *         @arg PWR_MODE_STOP_MAINREGU
  *         @arg PWR_MODE_STOP_LPREGU
  *         @arg PWR_MODE_STANDBY
  * @retval None
  */
__STATIC_INLINE void PWR_Set_PowerMode(uint32_t PDMode)
{
  MODIFY_REG(PWR->CR1, (PWR_CR1_LPMS), PDMode);
}

/**
  * @function  PWR_Get_PowerMode
  * @brief  Get Power Down mode when CPU enters deepsleep
  * @param  None
  * @retval Returned value can be one of the following values:
  *         @arg PWR_MODE_STOP_MAINREGU
  *         @arg PWR_MODE_STOP_LPREGU
  *         @arg PWR_MODE_STANDBY
  */
__STATIC_INLINE uint32_t PWR_Get_PowerMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, (PWR_CR1_LPMS)));
}

/**
  * @function  PWR_Set_PVDLevel
  * @rmtoll CR    PLS       PWR_SetPVDLevel
  * @param  PVDLevel 
  *         @arg PWR_CR2_PLS_2V2
  *         @arg PWR_CR2_PLS_2V3
  *         @arg PWR_CR2_PLS_2V4
  *         @arg PWR_CR2_PLS_2V5
  *         @arg PWR_CR2_PLS_2V6
  *         @arg PWR_CR2_PLS_2V7
  *         @arg PWR_CR2_PLS_2V8
  *         @arg PWR_CR2_PLS_2V9
  * @retval None
  */
__STATIC_INLINE void PWR_Set_PVDLevel(uint32_t PVDLevel)
{
  MODIFY_REG(PWR->CR2, PWR_CR2_PLS, PVDLevel);
}

/**
  * @function  PWR_Get_PVDLevel
  * @brief  Get the voltage threshold detection
  * @param  None
  * @retval Returned value can be one of the following values:
  *         @arg PWR_CR2_PLS_2V2
  *         @arg PWR_CR2_PLS_2V3
  *         @arg PWR_CR2_PLS_2V4
  *         @arg PWR_CR2_PLS_2V5
  *         @arg PWR_CR2_PLS_2V6
  *         @arg PWR_CR2_PLS_2V7
  *         @arg PWR_CR2_PLS_2V8
  *         @arg PWR_CR2_PLS_2V9
  */
__STATIC_INLINE uint32_t PWR_Get_PVDLevel(void)
{
  return (uint32_t)(READ_BIT(PWR->CR2, PWR_CR2_PLS));
}

/**
  * @function  PWR_Enable_PVD
  * @brief  Enable Power Voltage Detector
  * @param  None
  * @retval None
  */
__STATIC_INLINE void PWR_Enable_PVD(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @function  PWR_Disable_PVD
  * @brief  Disable Power Voltage Detector
  * @param  None
  * @retval None
  */
__STATIC_INLINE void PWR_Disable_PVD(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR2_PVDE);
}

/**
  * @function  PWR_Get_PVD
  * @brief  Check if Power Voltage Detector is enabled
  * @param  None
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t PWR_Get_PVD(void)
{
  return (READ_BIT(PWR->CR1, PWR_CR2_PVDE) == (PWR_CR2_PVDE));
}

/**
  * @function  PWR_Enable_WakeUpPin
  * @brief  Enable the WakeUp PINx functionality
  * @param  WakeUpPin :
  *         @arg PWR_WAKEUP_PIN1
  * @retval None
  */
__STATIC_INLINE void PWR_Enable_WakeUpPin(uint32_t WakeUpPin)
{
  SET_BIT(PWR->CR3, WakeUpPin);
}

/**
  * @function  PWR_Disable_WakeUpPin
  * @brief  Disable the WakeUp PINx functionality
  * @param  WakeUpPin :
  *         @arg PWR_WAKEUP_PIN1
  * @retval None
  */
__STATIC_INLINE void PWR_Disable_WakeUpPin(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->CR3, WakeUpPin);
}

/**
  * @function  PWR_Get_WakeUpPin
  * @brief  Check if the WakeUp PINx functionality is enabled
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg PWR_WAKEUP_PIN1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t PWR_Get_WakeUpPin(uint32_t WakeUpPin)
{
  return (READ_BIT(PWR->CR3, WakeUpPin) == (WakeUpPin));
}


/**
  * @brief  Get Flag
  * @param  Flag :
  *         @arg @ref PWR_SR_WUF1
  *         @arg @ref PWR_SR_SBF
  *         @arg @ref PWR_SR_WUFI
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t PWR_Get_Flag(uint32_t Flag)
{
  return (READ_BIT(PWR->SR, Flag) == (Flag));
}

/**
  * @brief  Get PVDO Flag
  * @param  Flag :
  *         @arg @ref PWR_SR2_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t PWR_Get_Flag_PVDO(uint32_t Flag)
{
  return (READ_BIT(PWR->SR2, Flag) == (Flag));
}

/**
  * @brief  Clear Flag
  * @rmtoll CSR   WUF       PWR_Clear_Flag
  * @param  Flag :
  *         @arg @ref PWR_SCR_CSBF
  *         @arg @ref PWR_SCR_CWUF1
  *         @arg @ref PWR_SCR_CWUFI
  * @retval None.
  */
__STATIC_INLINE void PWR_Clear_Flag(uint32_t Flag)
{
  SET_BIT(PWR->SCR, Flag);
}

/* Exported functions --------------------------------------------------------*/

void PWR_Enter_STOP_Mode(void);
void PWR_Enter_STOP_LPREGUMode(void);
void PWR_Enter_STANDBYMode(void);
void PWR_Enter_SLEEP_NOW_Mode(void);
void PWR_Enter_SLEEP_ON_EXIT_Mode(void);

#endif /* defined(PWR) */

#ifdef __cplusplus
}
#endif

#endif /* __rx32h6xx_PWR_H__ */

