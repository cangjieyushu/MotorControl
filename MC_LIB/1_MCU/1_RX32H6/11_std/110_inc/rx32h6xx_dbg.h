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
* File         : rx32h6xx_dbg.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/
#ifndef _rx32h6xx_DBG_H
#define _rx32h6xx_DBG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rx32h6xx.h"

/*******************  Bit definition for DBGMCU_CR_DBG register  *********************/
#define DBGMCU_CR_DBG_SLEEP                 BIT0
#define DBGMCU_CR_DBG_STOP                  BIT1
#define DBGMCU_CR_DBG_STANDBY               BIT2
#define DBGMCU_CR_DBG_IWDG_STOP             BIT8
#define DBGMCU_CR_DBG_TIM2_STOP             BIT11
#define DBGMCU_CR_DBG_TIM3_STOP             BIT12
#define DBGMCU_CR_DBG_TIM8_STOP             BIT17
#define DBGMCU_CR_DBG_TIM6_STOP             BIT19
#define DBGMCU_CR_DBG_TIM7_STOP             BIT20
#define DBGMCU_CR_DBG_TIM15_STOP            BIT24


/**
  * @brief  DBGMCU_CR_DBG_SLEEP.
  * @rmtoll CR          SLEEP           DBGMCU_Enable_SLEEP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Enable_SLEEP(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  DBGMCU_CR_DBG_SLEEP.
  * @rmtoll CR          SLEEP           DBGMCU_Disable_SLEEP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Disable_SLEEP(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  DBGMCU_CR_DBG_STOP.
  * @rmtoll CR          STOP           DBGMCU_Enable_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Enable_STOP(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  DBGMCU_CR_DBG_STOP.
  * @rmtoll CR          STOP           DBGMCU_Disable_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Disable_STOP(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  DBGMCU_CR_DBG_STANDBY.
  * @rmtoll CR          STANDBY           DBGMCU_Enable_STANDBY
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Enable_STANDBY(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  DBGMCU_CR_DBG_STANDBY.
  * @rmtoll CR          STANDBY           DBGMCU_Disable_STANDBY
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Disable_STANDBY(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  DBGMCU_CR_DBG_IWDG_STOP.
  * @rmtoll CR          IWDG_STOP           DBGMCU_Enable_IWDG_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Enable_IWDG_STOP(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_IWDG_STOP);
}

/**
  * @brief  DBGMCU_CR_DBG_IWDG_STOP.
  * @rmtoll CR          IWDG_STOP           DBGMCU_Disable_IWDG_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Disable_IWDG_STOP(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_IWDG_STOP);
}


/**
  * @brief  DBGMCU_CR_DBG_TIM2_STOP.
  * @rmtoll CR          TIM2_STOP           DBGMCU_Enable_TIM2_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Enable_TIM2_STOP(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_TIM2_STOP);
}

/**
  * @brief  DBGMCU_CR_DBG_TIM2_STOP.
  * @rmtoll CR          TIM2_STOP           DBGMCU_Disable_TIM2_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Disable_TIM2_STOP(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_TIM2_STOP);
}


/**
  * @brief  DBGMCU_CR_DBG_TIM3_STOP.
  * @rmtoll CR          TIM3_STOP           DBGMCU_Enable_TIM3_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Enable_TIM3_STOP(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_TIM3_STOP);
}

/**
  * @brief  DBGMCU_CR_DBG_TIM3_STOP.
  * @rmtoll CR          TIM3_STOP           DBGMCU_Disable_TIM3_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Disable_TIM3_STOP(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_TIM3_STOP);
}


/**
  * @brief  DBGMCU_CR_DBG_TIM8_STOP.
  * @rmtoll CR          TIM8_STOP           DBGMCU_Enable_TIM8_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Enable_TIM8_STOP(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_TIM8_STOP);
}

/**
  * @brief  DBGMCU_CR_DBG_TIM8_STOP.
  * @rmtoll CR          TIM8_STOP           DBGMCU_Disable_TIM8_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Disable_TIM8_STOP(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_TIM8_STOP);
}


/**
  * @brief  DBGMCU_CR_DBG_TIM6_STOP.
  * @rmtoll CR          TIM6_STOP           DBGMCU_Enable_TIM6_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Enable_TIM6_STOP(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_TIM6_STOP);
}

/**
  * @brief  DBGMCU_CR_DBG_TIM6_STOP.
  * @rmtoll CR          TIM6_STOP           DBGMCU_Disable_TIM6_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Disable_TIM6_STOP(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_TIM6_STOP);
}

/**
  * @brief  DBGMCU_CR_DBG_TIM7_STOP.
  * @rmtoll CR          TIM7_STOP           DBGMCU_Enable_TIM7_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Enable_TIM7_STOP(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_TIM7_STOP);
}

/**
  * @brief  DBGMCU_CR_DBG_TIM7_STOP.
  * @rmtoll CR          TIM7_STOP           DBGMCU_Disable_TIM7_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Disable_TIM7_STOP(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_TIM7_STOP);
}


/**
  * @brief  DBGMCU_CR_DBG_TIM15_STOP.
  * @rmtoll CR          TIM15_STOP           DBGMCU_Enable_TIM15_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Enable_TIM15_STOP(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_TIM15_STOP);
}

/**
  * @brief  DBGMCU_CR_DBG_TIM15_STOP.
  * @rmtoll CR          TIM15_STOP           DBGMCU_Disable_TIM15_STOP
  * @param  None
  * @retval None
  */
__STATIC_INLINE void DBGMCU_Disable_TIM15_STOP(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_TIM15_STOP);
}



#ifdef __cplusplus
}
#endif

#endif /* __rx32h6xx_DBG_H__ */

