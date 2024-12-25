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
* File         : rx32h6xx_wdg.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/
#ifndef __rx32h6xx_WDG_H__
#define __rx32h6xx_WDG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rx32h6xx.h"

/** @defgroup WDG
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup IWDG_Exported_Constants IWDG Exported Constants
  * @{
  */

/******************************************************************************/
/*                                                                            */
/*                        Independent WATCHDOG (IWDG)                         */
/*                                                                            */
/******************************************************************************/
#define IWDG_KEY_RELOAD                      0x0000AAAA               /*!< IWDG Reload Counter Enable   */
#define IWDG_KEY_ENABLE                      0x0000CCCC               /*!< IWDG Peripheral Enable       */
#define IWDG_KEY_WR_ACCESS_ENABLE            0x00005555               /*!< IWDG KR Write Access Enable  */
#define IWDG_KEY_WR_ACCESS_DISABLE           0x00000000               /*!< IWDG KR Write Access Disable */

/*******************  Bit definition for IWDG_KR register  ********************/      /*!< 0x0000FFFF */
#define IWDG_KR_KEY_Pos                     (0U)
#define IWDG_KR_KEY_Msk                     (0xFFFFU << IWDG_KR_KEY_Pos)       /*!< 0x0000FFFF */
#define IWDG_KR_KEY                         IWDG_KR_KEY_Msk                    /*!< Key value (write only, read 0000h) */

/*******************  Bit definition for IWDG_PR register  ********************/
#define IWDG_PR_PR_Pos                      (0U)
#define IWDG_PR_PR_Msk                      (0x7U << IWDG_PR_PR_Pos)           /*!< 0x00000007 */
#define IWDG_PR_PR                          IWDG_PR_PR_Msk                     /*!< PR[2:0] (Prescaler divider) */
#define IWDG_PR_PR_0                        (0x1U << IWDG_PR_PR_Pos)           /*!< 0x00000001 */
#define IWDG_PR_PR_1                        (0x2U << IWDG_PR_PR_Pos)           /*!< 0x00000002 */
#define IWDG_PR_PR_2                        (0x4U << IWDG_PR_PR_Pos)           /*!< 0x00000004 */                                                                          

/*******************  Bit definition for IWDG_RLR register  *******************/
#define IWDG_RLR_RL_Pos                     (0U)
#define IWDG_RLR_RL_Msk                     (0xFFFU << IWDG_RLR_RL_Pos)        /*!< 0x00000FFF */
#define IWDG_RLR_RL                         IWDG_RLR_RL_Msk                    /*!< Watchdog counter reload value */

/*******************  Bit definition for IWDG_SR register  ********************/
#define IWDG_SR_SR                           0x00000003                               
#define IWDG_SR_PVU_Pos                     (0U)
#define IWDG_SR_PVU_Msk                     (0x1U << IWDG_SR_PVU_Pos)          /*!< 0x00000001 */
#define IWDG_SR_PVU                         IWDG_SR_PVU_Msk                    /*!< Watchdog prescaler value update */
#define IWDG_SR_RVU_Pos                     (1U)
#define IWDG_SR_RVU_Msk                     (0x1U << IWDG_SR_RVU_Pos)          /*!< 0x00000002 */
#define IWDG_SR_RVU                         IWDG_SR_RVU_Msk                    /*!< Watchdog counter reload value update */

/** @defgroup IWDG_EC_PRESCALER  Prescaler Divider
  */
#define IWDG_PRESCALER_4                0x00000000U                           /*!< Divider by 4   */
#define IWDG_PRESCALER_8                (IWDG_PR_PR_0)                        /*!< Divider by 8   */
#define IWDG_PRESCALER_16               (IWDG_PR_PR_1)                        /*!< Divider by 16  */
#define IWDG_PRESCALER_32               (IWDG_PR_PR_1 | IWDG_PR_PR_0)         /*!< Divider by 32  */
#define IWDG_PRESCALER_64               (IWDG_PR_PR_2)                        /*!< Divider by 64  */
#define IWDG_PRESCALER_128              (IWDG_PR_PR_2 | IWDG_PR_PR_0)         /*!< Divider by 128 */
#define IWDG_PRESCALER_256              (IWDG_PR_PR_2 | IWDG_PR_PR_1)         /*!< Divider by 256 */

/**
  * @brief  Write a value in IWDG register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define IWDG_WriteReg(__REG__, __VALUE__) WRITE_REG(IWDG->__REG__, (__VALUE__))

/**
  * @brief  Read a value in IWDG register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define IWDG_ReadReg(__REG__) READ_REG(IWDG->__REG__)

/**
  * @function  IWDG_Enable
  * @brief  Start the Independent Watchdog
  * @param  IWDGx:
            @arg IWDG Instance
  * @retval None
  */
__STATIC_INLINE void IWDG_Enable(IWDG_TypeDef *IWDGx)
{
  WRITE_REG(IWDG->KR, IWDG_KEY_ENABLE);
}

/**
  * @function  IWDG_Reload_Counter
  * @brief Reloads IWDG counter with value defined in the reload register
  * @param  IWDGx:
            @arg IWDG Instance
  * @retval None
  */
__STATIC_INLINE void IWDG_Reload_Counter(IWDG_TypeDef *IWDGx)
{
  WRITE_REG(IWDG->KR, IWDG_KEY_RELOAD);
}

/**
  * @function  IWDG_Enable_WriteAccess
  * @brief  Enable write access to IWDG_PR, IWDG_RLR and IWDG_WINR registers
  * @param  IWDGx:
            @arg IWDG Instance
  * @retval None
  */
__STATIC_INLINE void IWDG_Enable_WriteAccess(IWDG_TypeDef *IWDGx)
{
  WRITE_REG(IWDG->KR, IWDG_KEY_WR_ACCESS_ENABLE);
}

/**
  * @function  IWDG_Disable_WriteAccess
  * @brief  Disable write access to IWDG_PR, IWDG_RLR and IWDG_WINR registers
  * @param  IWDGx:
            @arg IWDG Instance
  * @retval None
  */
__STATIC_INLINE void IWDG_Disable_WriteAccess(IWDG_TypeDef *IWDGx)
{
  WRITE_REG(IWDG->KR, IWDG_KEY_WR_ACCESS_DISABLE);
}

/**
  * @function  IWDG_Set_Prescaler
  * @brief  Select the prescaler of the IWDG
  * @param  IWDGx:
            @arg IWDG Instance
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref IWDG_PRESCALER_4
  *         @arg @ref IWDG_PRESCALER_8
  *         @arg @ref IWDG_PRESCALER_16
  *         @arg @ref IWDG_PRESCALER_32
  *         @arg @ref IWDG_PRESCALER_64
  *         @arg @ref IWDG_PRESCALER_128
  *         @arg @ref IWDG_PRESCALER_256
  * @retval None
  */
__STATIC_INLINE void IWDG_Set_Prescaler(IWDG_TypeDef *IWDGx, uint32_t Prescaler)
{
  WRITE_REG(IWDGx->PR, Prescaler);
}

/**
  * @function  IWDG_Get_Prescaler
  * @brief  Get the selected prescaler of the IWDG
  * @param  IWDGx:
            @arg IWDG Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref IWDG_PRESCALER_4
  *         @arg @ref IWDG_PRESCALER_8
  *         @arg @ref IWDG_PRESCALER_16
  *         @arg @ref IWDG_PRESCALER_32
  *         @arg @ref IWDG_PRESCALER_64
  *         @arg @ref IWDG_PRESCALER_128
  *         @arg @ref IWDG_PRESCALER_256
  */
__STATIC_INLINE uint32_t IWDG_Get_Prescaler(IWDG_TypeDef *IWDGx)
{
  return (uint32_t)(READ_REG(IWDGx->PR));
}

/**
  * @function  IWDG_Set_ReloadCounter
  * @brief  Specify the IWDG down-counter reload value
  * @param  IWDGx:
            @arg IWDG Instance
  * @param  Counter Value between Min_Data=0 and Max_Data=0x0FFF
  * @retval None
  */
__STATIC_INLINE void IWDG_Set_ReloadCounter(IWDG_TypeDef *IWDGx, uint32_t Counter)
{
  WRITE_REG(IWDGx->RLR, Counter);
}

/**
  * @function  IWDG_Get_ReloadCounter
  * @brief  Get the specified IWDG down-counter reload value
  * @param  IWDGx:
            @arg IWDG Instance
  * @retval Value between Min_Data=0 and Max_Data=0x0FFF
  */
__STATIC_INLINE uint32_t IWDG_Get_ReloadCounter(IWDG_TypeDef *IWDGx)
{
  return (uint32_t)(READ_REG(IWDGx->RLR));
}

/**
***********************************************************************************
*@Function IWDG_Get_Flag
*@brief    Get IWDG Flag.
*@param  IWDGx IWDG Instance
*@param1   Flag:
*          @arg  IWDG_SR_PVU
*          @arg  IWDG_SR_RVU
*@retval State of bit (1 or 0).
***********************************************************************************
  */
__STATIC_INLINE uint32_t IWDG_Get_Flag(IWDG_TypeDef *IWDGx, uint32_t Flag)
{	
	return (READ_BIT(IWDGx->SR, Flag) == (Flag));
}

/**
  * @brief  Check if all flags Prescaler, Reload & Window Value Update are reset or not
  * @rmtoll SR           PVU           IWDG_Is_Ready\n
  *         SR           RVU           IWDG_Is_Ready
  * @param  IWDGx IWDG Instance
  * @retval State of bits (1 or 0).
  */
__STATIC_INLINE uint32_t IWDG_Is_Ready(IWDG_TypeDef *IWDGx)
{
  return (READ_BIT(IWDGx->SR, IWDG_SR_PVU | IWDG_SR_RVU) == 0U);
}

typedef struct
{
  uint32_t Prescaler; 
  uint32_t Counter;
} IWDG_InitTypeDef;

/* Exported functions --------------------------------------------------------*/

void IWDG_Initial(IWDG_InitTypeDef *IWDG_InitStruct);

#ifdef __cplusplus
}
#endif

#endif /* __rx32h6xx_PWR_H__ */

