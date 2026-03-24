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
* File         : rx32h6xx_opamp.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/
#ifndef _rx32h6xx_OPAMP_H
#define _rx32h6xx_OPAMP_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include "rx32h6xx.h"
#include "rx32h6xx_rcc.h"

/*
**********************************************************************************************************
*                         Peripheral Registers_Bits_Definition of OPAMP Module
**********************************************************************************************************
*/

/**********************  Bit definition for OPAMPx register of OPAMP_TypeDef ***********************/
#define  OPAMP_CSR                                      ((uint32_t)0xDFFFF9F3)	
#define  OPAMP_CSR_OPAEN                                ((uint32_t)0x00000001)
#define  OPAMP_CSR_FORCEVP                              ((uint32_t)0x00000002)

#define  OPAMP_CSR_VMSEL                                ((uint32_t)0x0000000C)
#define  OPAMP_CSR_VMSEL_0                              ((uint32_t)0x00000004)
#define  OPAMP_CSR_VMSEL_1                              ((uint32_t)0x00000008)

#define  OPAMP_CSR_OPAHSM                               ((uint32_t)0x00000080)

#define  OPAMP_CSR_TOEXT_EN                             ((uint32_t)0x00000100)
#define  OPAMP_CSR_TOEXT_ENABLE                          OPAMP_CSR_TOEXT_EN
#define  OPAMP_CSR_TOEXT_DISABLE                        ((uint32_t)0x00000000)

#define  OPAMP_CSR_VPSEL                                ((uint32_t)0x00000200)
#define  OPAMP_CSR_VPSEL_P1                             ((uint32_t)0x00000000)
#define  OPAMP_CSR_VPSEL_P2                             ((uint32_t)0x00000200)

#define  OPAMP_CSR_GAIN                                 ((uint32_t)0x0000C000)
#define  OPAMP_CSR_GAIN_0                               ((uint32_t)0x00004000)
#define  OPAMP_CSR_GAIN_1                               ((uint32_t)0x00008000)

#define  OPAMP_CSR_OUTCONNECT                           ((uint32_t)0x00060000)
#define  OPAMP_CSR_OUTCONNECT0                          ((uint32_t)0x00020000)
#define  OPAMP_CSR_OUTCONNECT1                          ((uint32_t)0x00040000)

#define  OPAMP_CSR_TOINT                          			((uint32_t)0x20000000)
#define  OPAMP_CSR_TOINT_ENABLE	                  			((uint32_t)0x20000000)
#define  OPAMP_CSR_TOINT_DISABLE	                  		((uint32_t)0x00000000)

#define  OPAMP_CSR_LOCK                                 ((uint32_t)0x80000000)

#define  OPAMP_BIAS_VOL_EN                              ((uint32_t)0x00000001)
#define  OPAMP_BIAS_GND_EN                              ((uint32_t)0x00000002)

#define  OPAMP_BIAS_VOL_SEL                             ((uint32_t)0x00000004)
#define  OPAMP_BIAS_VOL_SEL_Vref                        ((uint32_t)0x00000004)
#define  OPAMP_BIAS_VOL_SEL_VBG                         ((uint32_t)0x00000000)

#define  OPAMP_BIAS_VBGINT															((uint32_t)0x00000008)
#define  OPAMP_VBGINT_ENABLE														((uint32_t)0x00000008)												
#define  OPAMP_VBGINT_DISABLE														((uint32_t)0x00000000)

#define  OPAMP_VMSEL_NO_CONNECT 												((uint32_t)0x00000000)
#define  OPAMP_VMSEL_VINM															  (                    OPAMP_CSR_VMSEL_0)
#define  OPAMP_VMSEL_FOLLOW															(OPAMP_CSR_VMSEL_1                    )
#define  OPAMP_VMSEL_VINN																(OPAMP_CSR_VMSEL_1 | OPAMP_CSR_VMSEL_0)     //only used for OPA3

#define  OPAMP_MODE_NO_CONNECT     											OPAMP_VMSEL_NO_CONNECT 											
#define  OPAMP_MODE_PGA      														OPAMP_VMSEL_VINM															
#define  OPAMP_MODE_FOLLOW     													OPAMP_VMSEL_FOLLOW														
#define  OPAMP_MODE_OPA																	OPAMP_VMSEL_VINN		

#define  OPAMP_BIAS_NONE     														((uint32_t)0x00000000)
#define  OPAMP_BIAS_GND     														((uint32_t)0x00000000) 											
#define  OPAMP_BIAS_VBG      														((uint32_t)0x00000001)															
#define  OPAMP_BIAS_VREF     														((uint32_t)0x00000002)										

#define  OPAMP_GAIN_NONE                               	(0x00000000UL)						
#define  OPAMP_GAIN_4                               		(0x00000000UL)                        /*!< OPAMP gain 4  */
#define  OPAMP_GAIN_8                               		(                   OPAMP_CSR_GAIN_0) /*!< OPAMP gain 8  */
#define  OPAMP_GAIN_12                              		(OPAMP_CSR_GAIN_1                   ) /*!< OPAMP gain 12 */
#define  OPAMP_GAIN_16                              		(OPAMP_CSR_GAIN_1 | OPAMP_CSR_GAIN_0) /*!< OPAMP gain 16 */

 /*!< OPAMP_CSR_OUTCONNECT  */
#define  OPAMP_OUTCONNECT_NO_CONNECT                    ((uint32_t)0x00000000)															
#define  OPAMP_OUTCONNECT_OUT_TO_GND                    (                       OPAMP_CSR_OUTCONNECT0)
#define  OPAMP_OUTCONNECT_OUT_TO_VIN1                   (OPAMP_CSR_OUTCONNECT1                       )		// used for OPA 1/2/3
#define  OPAMP_OUTCONNECT_OUT_TO_VIN2                   (OPAMP_CSR_OUTCONNECT1 | OPAMP_CSR_OUTCONNECT0)    // used for OPA 1/2



#define  OPAMP_VM_NO_CONNECT                OPAMP_OUTCONNECT_NO_CONNECT 
#define  OPAMP_VM_TO_GND                    OPAMP_OUTCONNECT_OUT_TO_GND 
#define  OPAMP_VM_TO_VIN1                   OPAMP_OUTCONNECT_OUT_TO_VIN1
#define  OPAMP_VM_TO_VIN2                   OPAMP_OUTCONNECT_OUT_TO_VIN2




/** @defgroup OPAMP_EC_INTERNAL_OUPUT_MODE OPAMP internal output mode
  * @{
  */
#define OPAMP_INTERNAL_OUPUT_DISABLED       (0x00000000UL)         	/*!< OPAMP internal output to ADC disabled. */
#define OPAMP_INTERNAL_OUPUT_ENABLED        (0x20000000)    				/*!< OPAMP internal output to ADC enabled.
                                                                             - OPAMP1 internal output is connected to ADC1/Channel15
                                                                             - OPAMP2 internal output is connected to ADC1/Channel16
                                                                             - OPAMP3 internal output is connected to ADC1/Channel17
                                                                           Note: On this STM32 series, all OPAMPx are not available on all devices. Refer to device datasheet for more details */

/** @defgroup OPAMP_EC_HW_DELAYS  Definitions of OPAMP hardware constraints delays
  * @note   Only OPAMP peripheral HW delays are defined in OPAMP driver driver,
  *         not timeout values.
  *         For details on delays values, refer to descriptions in source code
  *         above each literal definition.
  * @{
  */
/* Delay for OPAMP startup time (transition from state disable to enable).    */
/* Note: OPAMP startup time depends on board application environment:         */
/*       impedance connected to OPAMP output.                                 */
/*       The delay below is specified under conditions:                       */
/*        - OPAMP in functional mode follower                                 */
/*        - load impedance of 4kOhm (min), 50pF (max)                         */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tWAKEUP").                                                      */
/* Unit: us                                                                   */
#define OPAMP_DELAY_STARTUP_US         (6)  /*!< Delay for OPAMP startup time */

/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  __REG__ Register basis from which the offset is applied.
  * @param  __REG_OFFSET__ Offset to be applied (unit: number of registers).
  * @retval Register address
  */
#define __OPAMP_PTR_REG_OFFSET(__REG__, __REG_OFFSET__)                        \
  ((uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((__REG_OFFSET__) << 2))))
  
/**
  * @brief  Write a value in OPAMP register
  * @param  __INSTANCE__ OPAMP Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define OPAMP_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG((__INSTANCE__)->__REG__, (__VALUE__))

/**
  * @brief  Read a value in OPAMP register
  * @param  __INSTANCE__ OPAMP Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define OPAMP_ReadReg(__INSTANCE__, __REG__) READ_REG((__INSTANCE__)->__REG__)

typedef struct
{
  uint32_t PGAGain;
  uint32_t FunctionalMode;              /*!< Set OPAMP functional mode by setting internal connections: OPAMP operation in standalone, follower, ...
                                             This parameter can be a value of @ref OPAMP_EC_FUNCTIONAL_MODE
                                             @note If OPAMP is configured in mode PGA, the gain can be configured using function @ref FunctionalMode.
																									* OPAMP_MODE_NO_CONNECT
																									* OPAMP_MODE_PGA      	
																									* OPAMP_MODE_FOLLOW    
																									* OPAMP_MODE_OPA				
                                             This feature can be modified afterwards using unitary function @ref OPAMP1_Set_FunctionalMode(). */

  uint32_t OPAMP_OUTCONNECT;              /*!< Set OPAMP inverting input connection.
                                             This parameter can be a value of @ref OPAMP_CSR_OUTCONNECT.
																									*	OPAMP_VM_NO_CONNECT
																									*	OPAMP_VM_TO_GND    
																									*	OPAMP_VM_TO_VIN1   
																									*	OPAMP_VM_TO_VIN2   
                                             @note OPAMP inverting input is used with OPAMP in mode standalone or PGA with external capacitors for filtering circuit. Otherwise (OPAMP in mode follower), OPAMP inverting input is not used (not connected to GPIO pin), this parameter is discarded.

                                             This feature can be modified afterwards using unitary function @ref OPAMP1_Set_InputInverting(). */
	
	uint32_t VPSEL;													/*!< Set OPAMP noninverting input connection.
                                             This parameter can be a value of @ref OPAMP_CSR_VPSEL.
																									*	OPAMP_CSR_VPSEL_P1 
																									*	OPAMP_CSR_VPSEL_P2    */

	uint32_t TOEXT;													/*!< Set OPAMP output to external IO enable.
                                             This parameter can be a value of @ref OPAMP_CSR_TOEXT_EN.
																									*	OPAMP_CSR_TOEXT_ENABLE
																									*	OPAMP_CSR_TOEXT_DISABLE    */		
																									
	uint32_t TOINT;													/*!< Set OPAMP output to internal ADC/CMP enable.
                                             This parameter only used in OPAMP3 .It can be a value of @ref OPAMP_CSR_TOINT.
																									*	OPAMP_CSR_TOINT_ENABLE
																									*	OPAMP_CSR_TOINT_DISABLE    */								

	
	uint32_t BIASMode;											/*!< Set OPAMP BIAS selection. It was used only when "FunctionalMode == OPAMP_MODE_PGA"
                                             This parameter can be a value of @ref .
																									*	OPAMP_BIAS_VREF
																									*	OPAMP_BIAS_VBG
																									*	OPAMP_BIAS_GND							*/									
} OPAMP_InitTypeDef;

/**
  * @function  OPAMP_Set_FunctionalMode
  * @brief  Set OPAMP functional mode by setting internal connections.
  *         OPAMP operation in standalone, follower, ...
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @param  FunctionalMode:
  *         @arg OPAMP_MODE_NO_CONNECT
  *         @arg OPAMP_MODE_PGA      	
  *         @arg OPAMP_MODE_FOLLOE    
  *         @arg OPAMP_MODE_OPA				 
  * @retval None
  */
__STATIC_INLINE void OPAMP_Set_FunctionalMode(OPAMP_TypeDef *OPAMPx, uint32_t FunctionalMode)
{
  /* Note: Bit OPAMP_CSR_CALON reset to ensure to be in functional mode */
  MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_VMSEL , FunctionalMode);
}

/**
  * @function  OPAMP_Get_FunctionalMode
  * @brief  Get OPAMP functional mode from setting of internal connections.
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @retval Returned value can be one of the following values:
  *         @arg OPAMP_MODE_NO_CONNECT
  *         @arg OPAMP_MODE_PGA      	
  *         @arg OPAMP_MODE_FOLLOE    
  *         @arg OPAMP_MODE_OPA				
  */
__STATIC_INLINE uint32_t OPAMP_Get_FunctionalMode(OPAMP_TypeDef *OPAMPx)
{
  return (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_VMSEL));
}

/**
  * @function  OPAMP_Enable
  * @brief  Enable OPAMP1 instance.
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @retval None
  */
__STATIC_INLINE void OPAMP_Enable(OPAMP_TypeDef *OPAMPx)
{
  SET_BIT(OPAMPx->CSR, OPAMP_CSR_OPAEN);
}

/**
  * @function  OPAMP_Disable
  * @brief  Disable OPAMP instance.
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @retval None
  */
__STATIC_INLINE void OPAMP_Disable(OPAMP_TypeDef *OPAMPx)
{
  CLEAR_BIT(OPAMPx->CSR, OPAMP_CSR_OPAEN);
}

/**
  * @function  OPAMP_Is_Enabled
  * @brief   Get OPAMP instance enable state
  *         (0: OPAMP is disabled, 1: OPAMP is enabled)
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t OPAMP_Is_Enabled(OPAMP_TypeDef *OPAMPx)
{
  return ((READ_BIT(OPAMPx->CSR, OPAMP_CSR_OPAEN) == (OPAMP_CSR_OPAEN)) ? 1UL : 0UL);
}

/**
  * @function  OPAMP_Lock
  * @brief  Lock OPAMP instance.
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @retval None
  */
__STATIC_INLINE void OPAMP_Lock(OPAMP_TypeDef *OPAMPx)
{
  SET_BIT(OPAMPx->CSR, OPAMP_CSR_LOCK);
}

/**
  * @function  OPAMP_Is_Locked
  * @brief  Get OPAMP lock state
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t OPAMP_Is_Locked(OPAMP_TypeDef *OPAMPx)
{
  return ((READ_BIT(OPAMPx->CSR, OPAMP_CSR_LOCK) == (OPAMP_CSR_LOCK)) ? 1UL : 0UL);
}

/**
  * @function  OPAMP_Enable_HSM
  * @brief  Enable OPAMP1 instance.
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @retval None
  */
__STATIC_INLINE void OPAMP_Enable_HSM(OPAMP_TypeDef *OPAMPx)
{
  SET_BIT(OPAMPx->CSR, OPAMP_CSR_OPAHSM);
}

/**
  * @function  OPAMP_Disable_HSM
  * @brief  Disable OPAMP1 instance.
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @retval None
  */
__STATIC_INLINE void OPAMP_Disable_HSM(OPAMP_TypeDef *OPAMPx)
{
  CLEAR_BIT(OPAMPx->CSR, OPAMP_CSR_OPAHSM);
}

/**
  * @function  OPAMP_Set_VM_SEL
  * @brief  Set OPAMP VM SEL MODE.
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
	*	@param	VM_SEL:
	*					OPAMP_VMSEL_NO_CONNECT
	*					OPAMP_VMSEL_VINM
	*					OPAMP_VMSEL_FOLLOE
	*					OPAMP_VMSEL_VINN
  * @retval None.
  */
__STATIC_INLINE void OPAMP_Set_VM_SEL(OPAMP_TypeDef *OPAMPx, uint32_t VM_SEL)
{
	MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_VMSEL, VM_SEL);
}

/**
  * @function  OPAMP_Get_VM_SEL
  * @brief  Get OPAMP VM SEL MODE.
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
	*	@retval	Returned value can be one of the following values:
	*			    @arg OPAMP_VMSEL_NO_CONNECT
	*			    @arg OPAMP_VMSEL_VINM
	*			    @arg OPAMP_VMSEL_FOLLOE
	*			    @arg OPAMP_VMSEL_VINN
  */
__STATIC_INLINE uint32_t OPAMP_Get_VM_SEL(OPAMP_TypeDef *OPAMPx, uint32_t VM_SEL)
{
	return (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_VMSEL));
}

/**
  * @function  OPAMP_Set_OutConnect
  * @brief  Set OPAMP Outconnect SEL MODE.
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
	*	@param	OUT_CONNECT:
	*					@arg OPAMP_VM_NO_CONNECT
	*					@arg OPAMP_VM_TO_GND    
	*					@arg OPAMP_VM_TO_VIN1   
	*					@arg OPAMP_VM_TO_VIN2   
  * @retval None.
  */
__STATIC_INLINE void OPAMP_Set_OutConnect(OPAMP_TypeDef *OPAMPx, uint32_t OUT_CONNECT)
{
	MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_OUTCONNECT, OUT_CONNECT);
}

/**
  * @function  OPAMP_Get_OutConnect
  * @brief  Get OPAMP Outconnect SEL MODE.
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
	*	@retval	Returned value can be one of the following values:
	*			    @arg OPAMP_VM_NO_CONNECT
	*			    @arg OPAMP_VM_TO_GND    
	*			    @arg OPAMP_VM_TO_VIN1   
	*					@arg OPAMP_VM_TO_VIN2   
  */
__STATIC_INLINE uint32_t OPAMP_Get_OutConnect(OPAMP_TypeDef *OPAMPx)
{
	return (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_OUTCONNECT));
}

/**
  * @function  OPAMP_ENABLE_TOEXT
  * @brief  
  * @param  TOEXT:
  *         @arg OPAMP_CSR_TOEXT_ENABLE
  *         @arg OPAMP_CSR_TOEXT_DISABLE
  * @retval None
  */
__STATIC_INLINE void OPAMP_Enable_TOEXT(uint32_t TOEXT)
{
	MODIFY_REG(OPAMP3->CSR, OPAMP_CSR_TOEXT_EN, TOEXT);	
}

/**
  * @function  OPAMP_Set_VP_SEL
  * @brief  VP_SEL. This is only used for OPA3
  * @param  VP_SEL:
	*         @arg OPAMP_CSR_VPSEL_P1
  *         @arg OPAMP_CSR_VPSEL_P2
  * @retval None
  */
__STATIC_INLINE void OPAMP_Set_VP_SEL( uint32_t VP_SEL ) 
{
	MODIFY_REG(OPAMP3->CSR, OPAMP_CSR_VPSEL, VP_SEL);	
}

/**
  * @function  OPAMP_Set_PGAGain
  * @brief  Set OPAMP gain.
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @param  OPAGain:
  *         @arg OPAMP_GAIN_4
  *         @arg OPAMP_GAIN_8 
  *         @arg OPAMP_GAIN_12
  *         @arg OPAMP_GAIN_16   
  * @retval None
  */
__STATIC_INLINE void OPAMP_Set_PGAGain(OPAMP_TypeDef *OPAMPx, uint32_t OPAGain)
{
  MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_GAIN, OPAGain);
}

/**
  * @function  OPAMP_Get_PGAGain
  * @brief  Get OPAMP gain
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @retval Returned value can be one of the following values:
	*					@arg OPAMP_GAIN_4
	*					@arg OPAMP_GAIN_8
	*					@arg OPAMP_GAIN_12
	*					@arg OPAMP_GAIN_16
  */
__STATIC_INLINE uint32_t OPAMP_Get_PGAGain(OPAMP_TypeDef *OPAMPx)
{
	return (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_GAIN));
}

/**
  * @function  OPAMP_ENABLE_TOINT
  * @brief  
  * @param  TOEXT:
  *         @arg OPAMP_CSR_TOINT_ENABLE
  *         @arg OPAMP_CSR_TOINT_DISABLE
  * @retval None
  */
__STATIC_INLINE void OPAMP_Enable_TOINT(uint32_t TOINT)
{
	MODIFY_REG(OPAMP3->CSR, OPAMP_CSR_TOINT, TOINT);
}

/**
  * @function  OPAMP_ENABLE_BIAS_VOL
  * @brief  
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @retval None
  */
__STATIC_INLINE void OPAMP_Enable_BIAS_VOL(OPAMP_TypeDef *OPAMPx)
{
	MODIFY_REG(OPAMPx->BIAS, (OPAMP_BIAS_VOL_EN|OPAMP_BIAS_GND_EN), OPAMP_BIAS_VOL_EN); 
}

/**
  * @function  OPAMP_DISABLE_BIAS_VOL
  * @brief  
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @retval None
  */
__STATIC_INLINE void OPAMP_Disable_BIAS_VOL(OPAMP_TypeDef *OPAMPx)
{
	CLEAR_BIT(OPAMPx->BIAS, OPAMP_BIAS_VOL_EN); 	
}

/**
  * @function  OPAMP_ENABLE_BIAS_GND
  * @brief  
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @retval None
  */
__STATIC_INLINE void OPAMP_Enable_BIAS_GND(OPAMP_TypeDef *OPAMPx)
{
	MODIFY_REG(OPAMPx->BIAS, (OPAMP_BIAS_VOL_EN|OPAMP_BIAS_GND_EN), OPAMP_BIAS_GND_EN); 	
}

/**
  * @function  OPAMP_DISABLE_BIAS_GND
  * @brief  
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @retval None
  */
__STATIC_INLINE void OPAMP_Disable_BIAS_GND(OPAMP_TypeDef *OPAMPx)
{
	CLEAR_BIT(OPAMPx->BIAS, OPAMP_BIAS_GND_EN); 	
}

/**
  * @function  OPAMP_Set_VOL_SEL
  * @brief  
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @param  VP_SEL:
	*         @arg OPAMP_BIAS_VOL_SEL_Vref
  *         @arg OPAMP_BIAS_VOL_SEL_VBG
  * @retval None
  */
__STATIC_INLINE void OPAMP_Set_VOL_SEL(OPAMP_TypeDef *OPAMPx, uint32_t VOL_SEL)
{
	MODIFY_REG(OPAMPx->BIAS, OPAMP_BIAS_VOL_SEL, VOL_SEL);	
}

/**
  * @function  OPAMP_Set_VBGINT
  * @brief  
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @param  VBGINT:
	*         @arg OPAMP_VBGINT_ENABLE
  *         @arg OPAMP_VBGINT_DISABLE
  * @retval None
  */
__STATIC_INLINE void OPAMP_Set_VBGINT(OPAMP_TypeDef *OPAMPx, uint32_t VBGINT)
{
	MODIFY_REG(OPAMPx->BIAS, OPAMP_BIAS_VBGINT, VBGINT);	
}

void OPAMP_DeInit(OPAMP_TypeDef *OPAMPx);
void OPAMP_Init(OPAMP_TypeDef *OPAMPx, OPAMP_InitTypeDef *OPAMP_InitStruct);

#ifdef __cplusplus
}
#endif

#endif /* __rx32h6xx_OPAMP_H__ */
