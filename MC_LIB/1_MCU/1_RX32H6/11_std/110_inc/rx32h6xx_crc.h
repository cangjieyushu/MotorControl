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
* File         : rx32h6xx_crc.h
* By           : RX_SD_Team
* Description  : Only rx32h6xx
*********************************************************************************************************
*/
#ifndef __rx32h6xx_CRC_H__
#define __rx32h6xx_CRC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rx32h6xx.h"

/******************************************************************************/
/*                                                                            */
/*                       CRC calculation unit (CRC)                           */
/*                                                                            */
/******************************************************************************/

#if defined(CRC)

/** @defgroup CRC  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/*******************  Bit definition for CRC_DR register  *********************/
#define CRC_DR_DR_Pos                       (0U)
#define CRC_DR_DR_Msk                       (0xFFFFFFFFU << CRC_DR_DR_Pos)     /*!< 0xFFFFFFFF */
#define CRC_DR_DR                           CRC_DR_DR_Msk                      /*!< Data register bits */

/*******************  Bit definition for CRC_IDR register  ********************/
#define CRC_IDR_IDR_Pos                     (0U)
#define CRC_IDR_IDR_Msk                     (0xFFU << CRC_IDR_IDR_Pos)         /*!< 0x000000FF */
#define CRC_IDR_IDR                         CRC_IDR_IDR_Msk                    /*!< General-purpose 8-bit data register bits */

/********************  Bit definition for CRC_CR register  ********************/
#define CRC_CR_RESET_Pos                    (0U)
#define CRC_CR_RESET_Msk                    (0x1U << CRC_CR_RESET_Pos)         /*!< 0x00000001 */
#define CRC_CR_RESET                        CRC_CR_RESET_Msk                   /*!< RESET bit */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup CRC_Exported_Macros CRC Exported Macros  */

/** @defgroup CRC_EM_WRITE_READ Common Write and read registers Macros  */

/**
  * @brief  Write a value in CRC register
  * @param  __INSTANCE__ CRC Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define CRC_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in CRC register
  * @param  __INSTANCE__ CRC Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define CRC_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)


/**
  * @brief  Reset the CRC calculation unit.
  * @rmtoll CRC_Reset_CRCCalculationUnit
  * @param  CRCx CRC Instance
  * @retval None
  */
__STATIC_INLINE void CRC_Reset_CRCCalculationUnit(CRC_TypeDef *CRCx)
{
  WRITE_REG(CRCx->CR, CRC_CR_RESET);
}

/**
  * @brief  Write given 32-bit data to the CRC calculator
  * @rmtoll CRC_Write_Data32
  * @param  CRCx CRC Instance
  * @param  InData value to be provided to CRC calculator between between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void CRC_Write_Data32(CRC_TypeDef *CRCx, uint32_t InData)
{
  WRITE_REG(CRCx->DR, InData);
}

/**
  * @brief  Return current CRC calculation result. 32 bits value is returned.
  * @rmtoll CRC_Read_Data32
  * @param  CRCx CRC Instance
  * @retval Current CRC calculation result as stored in CRC_DR register (32 bits).
  */
__STATIC_INLINE uint32_t CRC_Read_Data32(CRC_TypeDef *CRCx)
{
  return (uint32_t)(READ_REG(CRCx->DR));
}

/**
  * @brief  Return data stored in the Independent Data(IDR) register.
  * @note   This register can be used as a temporary storage location for one byte.
  * @rmtoll CRC_Read_IDR
  * @param  CRCx CRC Instance
  * @retval Value stored in CRC_IDR register (General-purpose 8-bit data register).
  */
__STATIC_INLINE uint32_t CRC_Read_IDR(CRC_TypeDef *CRCx)
{
  return (uint32_t)(READ_REG(CRCx->IDR));
}

/**
  * @brief  Store data in the Independent Data(IDR) register.
  * @note   This register can be used as a temporary storage location for one byte.
  * @rmtoll CRC_Write_IDR
  * @param  CRCx CRC Instance
  * @param  InData value to be stored in CRC_IDR register (8-bit) between between Min_Data=0 and Max_Data=0xFF
  * @retval None
  */
__STATIC_INLINE void CRC_Write_IDR(CRC_TypeDef *CRCx, uint32_t InData)
{
  *((uint8_t __IO *)(&CRCx->IDR)) = (uint8_t) InData;
}


/* Exported functions --------------------------------------------------------*/
/** @defgroup CRC_Exported_Functions CRC Exported Functions  */

/** @defgroup CRC_EF_Configuration CRC Configuration functions  */

void CRC_DeInit(CRC_TypeDef *CRCx);


#endif /* defined(CRC) */

#ifdef __cplusplus
}
#endif

#endif /* __rx32h6xx_CRC_H__ */

