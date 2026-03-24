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
* File         : rx32h6xx_cmp.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/
#ifndef __rx32h6xx_CMP_H__
#define __rx32h6xx_CMP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rx32h6xx.h"

/******************************************************************************/
/*                                                                            */
/*                      Analog CMParators (CMP)                             */
/*                                                                            */
/******************************************************************************/
/**********************  Bit definition for CMP_CxCR register  ****************/
#define CMP_CxCR_EN                ((uint32_t)0x00000001)

#define CMP_CxCR_CH_EN             ((uint32_t)0x00000002)

#define CMP_CxCR_RIE               ((uint32_t)0x00000004)
#define CMP_CxCR_FIE               ((uint32_t)0x00000008)

#define CMP_CxCR_INM_SEL         ((uint32_t)0x00000070)
#define CMP_INM_SEL_N1           ((uint32_t)0x00000000)
#define CMP_INM_SEL_N2           ((uint32_t)0x00000010)     // (CMP1 only)
#define CMP_INM_SEL_N3           ((uint32_t)0x00000020)     // (CMP1 only)      
#define CMP_INM_SEL_SRN_Center   ((uint32_t)0x00000030)     // (CMP1 only) 
#define CMP_INM_SEL_CRV          ((uint32_t)0x00000040)


#define CMP_CxCR_INP_SEL              ((uint32_t)0x00000180)
#define CMP_INP_SEL_P1                ((uint32_t)0x00000000)
#define CMP_INP_SEL_P2                ((uint32_t)0x00000080)
#define CMP_INP_SEL_P3_CMP1           ((uint32_t)0x00000100)    
#define CMP_INP_SEL_OPA2_out_CMP2     ((uint32_t)0x00000100)
#define CMP_INP_SEL_OPA1_out_CMP1     ((uint32_t)0x00000180)    
#define CMP_INP_SEL_OPA3_out_CMP2     ((uint32_t)0x00000180)

#define CMP_CxCR_BASEN                ((uint32_t)0x00000200)
#define CMP_CxCR_CH_DIS               ((uint32_t)0x00000400)
#define CMP_CxCR_CH_DIS_BLANKING      ((uint32_t)0x00000800)

#define CMP_CxCR_OFLT                 ((uint32_t)0x00007000)
#define CMP_CxCR_OFLT_DIV1            ((uint32_t)0x00000000)
#define CMP_CxCR_OFLT_DIV32           ((uint32_t)0x00001000)
#define CMP_CxCR_OFLT_DIV64           ((uint32_t)0x00002000)
#define CMP_CxCR_OFLT_DIV128          ((uint32_t)0x00003000)
#define CMP_CxCR_OFLT_DIV256          ((uint32_t)0x00004000)
#define CMP_CxCR_OFLT_DIV512          ((uint32_t)0x00005000)
#define CMP_CxCR_OFLT_DIV1024         ((uint32_t)0x00006000)
#define CMP_CxCR_OFLT_DIV2048         ((uint32_t)0x00007000)


#define CMP_CxCR_POL               ((uint32_t)0x00008000)
#define CMP_CxCR_POL_Positive   	 ((uint32_t)0x00000000) 
#define CMP_CxCR_POL_Negative    	 ((uint32_t)0x00008000) 

#define CMP_CxCR_RHYST             ((uint32_t)0x00030000)
#define CMP_CxCR_RHYST_0mV         ((uint32_t)0x00000000)
#define CMP_CxCR_RHYST_20mV        ((uint32_t)0x00010000)
#define CMP_CxCR_RHYST_40mV        ((uint32_t)0x00020000)
#define CMP_CxCR_RHYST_60mV        ((uint32_t)0x00030000)

#define CMP_CxCR_CMP_BAS_EN_OPA    ((uint32_t)0x00040000)

#define CMP_CxCR_BLANKING_SEL              ((uint32_t)0x00380000)
#define CMP_CxCR_BLANKING_SEL_NoBlanking   ((uint32_t)0x00000000)
#define CMP_CxCR_BLANKING_SEL_TIM2_OC4     ((uint32_t)0x00080000)
#define CMP_CxCR_BLANKING_SEL_TIM2_OC3     ((uint32_t)0x00100000)
#define CMP_CxCR_BLANKING_SEL_TIM3_OC3     ((uint32_t)0x00180000)
#define CMP_CxCR_BLANKING_SEL_TIM8_OC5     ((uint32_t)0x00200000)
#define CMP_CxCR_BLANKING_SEL_TIM8_OC4     ((uint32_t)0x00280000)
#define CMP_CxCR_BLANKING_SEL_TIM15_OC1    ((uint32_t)0x00300000)
#define CMP_CxCR_BLANKING_SEL_TIM15_OC2    ((uint32_t)0x00380000)

#define CMP_CxCR_HIE               ((uint32_t)0x00400000)
#define CMP_CxCR_LIE               ((uint32_t)0x00800000)

#define CMP_CxCR_FHYST             ((uint32_t)0x03000000)
#define CMP_CxCR_FHYST_0mV         ((uint32_t)0x00000000)
#define CMP_CxCR_FHYST_20mV        ((uint32_t)0x01000000)
#define CMP_CxCR_FHYST_40mV        ((uint32_t)0x02000000)
#define CMP_CxCR_FHYST_60mV        ((uint32_t)0x03000000)

#define CMP_CxCR_HIF               ((uint32_t)0x04000000)

#define CMP_CxCR_RIF               ((uint32_t)0x08000000)
#define CMP_CxCR_FIF               ((uint32_t)0x10000000)

#define CMP_CxCR_LIF               ((uint32_t)0x20000000)

#define CMP_CxCR_OUT               ((uint32_t)0x40000000)
#define CMP_CxCR_OUT_Low        	 ((uint32_t)0x00000000) 
#define CMP_CxCR_OUT_High       	 ((uint32_t)0x40000000) 

#define CMP_CxCR_LOCK              ((uint32_t)0x80000000)
#define CMP_CxCR_LOCK_RW         	 ((uint32_t)0x00000000) 
#define CMP_CxCR_LOCK_R         	 ((uint32_t)0x80000000) 

#define CMP_RGxCAL_PADJ                ((uint32_t)0x0000000F)
#define CMP_RGxCAL_PEN                 ((uint32_t)0x00000010)
#define CMP_RGxCAL_NEN                 ((uint32_t)0x00000020)
#define CMP_RGxCAL_NADJ                ((uint32_t)0x00000F00)

#define CMP_CR1_SRN_EN               ((uint32_t)0x00000001)
#define CMP_CR1_SRN_Dout             ((uint32_t)0x00000002)
#define CMP_CR1_CRV_LOCK             ((uint32_t)0x00000004)
#define CMP_CR1_SRN_BAS_EN           ((uint32_t)0x00000008)

#define CMP_CR2_CRV_SRC_1            ((uint32_t)0x00000000)
#define CMP_CR2_CRV_SRC_2p5          ((uint32_t)0x00000001)
#define CMP_CR2_CRV_EN               ((uint32_t)0x00000002)
#define CMP_CR2_CRV_LOCK             ((uint32_t)0x00000004)

#define CMP_CR2_CRV_SEL      ((uint32_t)0x000000F8)
#define CMP_CRV_SEL_1_32     ((uint32_t)0x00000000)
#define CMP_CRV_SEL_2_32     ((uint32_t)0x00000008)
#define CMP_CRV_SEL_3_32     ((uint32_t)0x00000010)
#define CMP_CRV_SEL_4_32     ((uint32_t)0x00000018)
#define CMP_CRV_SEL_5_32     ((uint32_t)0x00000020)
#define CMP_CRV_SEL_6_32     ((uint32_t)0x00000028)
#define CMP_CRV_SEL_7_32     ((uint32_t)0x00000030)
#define CMP_CRV_SEL_8_32     ((uint32_t)0x00000038)
#define CMP_CRV_SEL_9_32     ((uint32_t)0x00000040)
#define CMP_CRV_SEL_10_32    ((uint32_t)0x00000048)
#define CMP_CRV_SEL_11_32    ((uint32_t)0x00000050)
#define CMP_CRV_SEL_12_32    ((uint32_t)0x00000058)
#define CMP_CRV_SEL_13_32    ((uint32_t)0x00000060)
#define CMP_CRV_SEL_14_32    ((uint32_t)0x00000068)
#define CMP_CRV_SEL_15_32    ((uint32_t)0x00000070)
#define CMP_CRV_SEL_16_32    ((uint32_t)0x00000078)
#define CMP_CRV_SEL_17_32    ((uint32_t)0x00000080)
#define CMP_CRV_SEL_18_32    ((uint32_t)0x00000088)
#define CMP_CRV_SEL_19_32    ((uint32_t)0x00000090)
#define CMP_CRV_SEL_20_32    ((uint32_t)0x00000098)
#define CMP_CRV_SEL_21_32    ((uint32_t)0x000000A0)
#define CMP_CRV_SEL_22_32    ((uint32_t)0x000000A8)
#define CMP_CRV_SEL_23_32    ((uint32_t)0x000000B0)
#define CMP_CRV_SEL_24_32    ((uint32_t)0x000000B8)
#define CMP_CRV_SEL_25_32    ((uint32_t)0x000000C0)
#define CMP_CRV_SEL_26_32    ((uint32_t)0x000000C8)
#define CMP_CRV_SEL_27_32    ((uint32_t)0x000000D0)
#define CMP_CRV_SEL_28_32    ((uint32_t)0x000000D8)
#define CMP_CRV_SEL_29_32    ((uint32_t)0x000000E0)
#define CMP_CRV_SEL_30_32    ((uint32_t)0x000000E8)
#define CMP_CRV_SEL_31_32    ((uint32_t)0x000000F0)
#define CMP_CRV_SEL_32_32    ((uint32_t)0x000000F8)


#define CMP_CRV_BAS_EN          ((uint32_t)0x00002000)


/* constant -------------------------------------------------------------*/

/**
  * @brief  Structure definition of some features of CMP instance.
  */
typedef struct
{
	uint32_t Pol;	    /** @arg CMP_CxCR_POL_Positive
                        @arg CMP_CxCR_POL_Negative ********/
	uint32_t Rhyst;   /** @arg CMP_CxCR_RHYST_0mV
                        @arg CMP_CxCR_RHYST_20mV
                        @arg CMP_CxCR_RHYST_40mV
                        @arg CMP_CxCR_RHYST_60mV ********/
	uint32_t Fhyst;   /** @arg CMP_CxCR_FHYST_0mV
                        @arg CMP_CxCR_FHYST_20mV
                        @arg CMP_CxCR_FHYST_40mV
                        @arg CMP_CxCR_FHYST_60mV ********/
	uint32_t INP_Sel; /** @arg CMP_INP_SEL_P1           
						            @arg CMP_INP_SEL_P2           
	                      @arg CMP_INP_SEL_P3_CMP1      
	                      @arg CMP_INP_SEL_OPA2_out_CMP2
	                      @arg CMP_INP_SEL_OPA1_out_CMP1
	                      @arg CMP_INP_SEL_OPA3_out_CMP2********/
	uint32_t INM_Sel; /** @arg CMP_INM_SEL_N1 
						            @arg CMP_INM_SEL_N2 
	                      @arg CMP_INM_SEL_N3 
                        @arg CMP_INM_SEL_SRN_Center
                        @arg CMP_INM_SEL_CRV********/
  uint32_t OFLT;		/** @arg CMP_CxCR_OFLT_DIV1    
						            @arg CMP_CxCR_OFLT_DIV32   
	                      @arg CMP_CxCR_OFLT_DIV64   
                        @arg CMP_CxCR_OFLT_DIV128  
                        @arg CMP_CxCR_OFLT_DIV256  						
                        @arg CMP_CxCR_OFLT_DIV512  
                        @arg CMP_CxCR_OFLT_DIV1024 
                        @arg CMP_CxCR_OFLT_DIV2048 ********/
 	uint32_t CRV_SEL; /**  @arg CMP_CRV_SEL_1_32 
                         @arg CMP_CRV_SEL_2_32 
                         @arg CMP_CRV_SEL_3_32 
                         @arg CMP_CRV_SEL_4_32 
                         @arg CMP_CRV_SEL_5_32 
                         @arg CMP_CRV_SEL_6_32 
                         @arg CMP_CRV_SEL_7_32 
                         @arg CMP_CRV_SEL_8_32 
                         @arg CMP_CRV_SEL_9_32 
                         @arg CMP_CRV_SEL_10_32
                         @arg CMP_CRV_SEL_11_32
                         @arg CMP_CRV_SEL_12_32
                         @arg CMP_CRV_SEL_13_32
                         @arg CMP_CRV_SEL_14_32
                         @arg CMP_CRV_SEL_15_32 
					               @arg CMP_CRV_SEL_16_32
					               @arg CMP_CRV_SEL_17_32
					               @arg CMP_CRV_SEL_18_32
					               @arg CMP_CRV_SEL_19_32
					               @arg CMP_CRV_SEL_20_32
					               @arg CMP_CRV_SEL_21_32
					               @arg CMP_CRV_SEL_22_32
					               @arg CMP_CRV_SEL_23_32
					               @arg CMP_CRV_SEL_24_32
					               @arg CMP_CRV_SEL_25_32
					               @arg CMP_CRV_SEL_26_32
					               @arg CMP_CRV_SEL_27_32
					               @arg CMP_CRV_SEL_28_32
					               @arg CMP_CRV_SEL_29_32
					               @arg CMP_CRV_SEL_30_32
					               @arg CMP_CRV_SEL_31_32
                         @arg CMP_CRV_SEL_32_32********/
	FunctionalState CRV_En;	  /** @arg ENABLE
								                @arg DISABLE ********/
	uint32_t CRV_Src;         /** @arg CRV_VREFBUF
		                            @arg VBG(1V)********/
                        
	uint32_t CR1_SRN;         /** @arg ENABLE
								                @arg DISABLE ********/          
 }CMP_InitTypeDef;  

/**
  * @function  CMP_Enable
  * @brief  Enable EN of the selected CMP
  * @param  COMPx:
  *         @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Enable(COMP_TypeDef *COMPx)
{
	SET_BIT(COMPx->CR,CMP_CxCR_EN);     
}

/**
  * @function  CMP_Disable
  * @brief  Disable EN of the selected CMP
  * @param  COMPx:
  *         @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Disable(COMP_TypeDef *COMPx)
{
	CLEAR_BIT(COMPx->CR,CMP_CxCR_EN);  
}

/**
  * @function  CMP_Set_POL
  * @brief  Set POL of the selected CMP
  * @param  COMPx:
            @arg CMP Instance
  * @param  Continuous:
  *         @arg CMP_CxCR_POL_Positive
  *         @arg CMP_CxCR_POL_Negative
  * @retval None
  */
__STATIC_INLINE void CMP_Set_POL(COMP_TypeDef *COMPx, uint32_t Pol)
{
  MODIFY_REG(COMPx->CR, CMP_CxCR_POL, Pol);
}

/**
  * @function  CMP_Read_OUT
  * @brief  Get OUT Status of the selected CMP
  * @param  COMPx:
            @arg CMP Instance
  * @retval 0 is low output, 1 is high output
  */
__STATIC_INLINE uint32_t CMP_Read_OUT(COMP_TypeDef *COMPx)
{
  return (READ_BIT(COMPx->CR, CMP_CxCR_OUT) == (CMP_CxCR_OUT));
}

/**
  * @function  CMP_Enable_Lock
  * @brief  CR LOCK of the selected CMP
  * @param  COMPx:
            @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Enable_Lock(COMP_TypeDef *COMPx)
{
  SET_BIT(COMPx->CR, CMP_CxCR_LOCK);
}

/**
  * @function  CMP_Enable_CR1Lock
  * @brief  CR1 LOCK of the selected CMP
  * @param  COMPx:
            @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Enable_CR1Lock(void)
{
  SET_BIT(COMP->CR1, CMP_CR1_CRV_LOCK);
}

/**
  * @function  CMP_Enable_CR2Lock
  * @brief  CR LOCK of the selected CMP
  * @param  COMPx:
            @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Enable_CR2Lock(void)
{
  SET_BIT(COMP->CR2, CMP_CR2_CRV_LOCK);
}
/**
***********************************************************************************
*@Function CMP_Enable_IT
*@brief    Enable Interrupt of the selected CMP
*@param1   COMPx:
*           @arg CMP Instance
*@param1   Flag:
*          @arg  CMP_CxCR_RIE
*          @arg  CMP_CxCR_FIE
*          @arg  CMP_CxCR_HIE
*          @arg  CMP_CxCR_LIE
*@retval State of bit (1 or 0).
***********************************************************************************
  */
__STATIC_INLINE void CMP_Enable_IT(COMP_TypeDef *COMPx, uint32_t IT)
{
	SET_BIT(COMPx->CR, IT );
}

/**
***********************************************************************************
*@Function CMP_Disable_IT
*@brief    Disable Interrupt of the selected CMP
*@param1   COMPx:
*           @arg CMP Instance
*@param1   Flag:
*          @arg  CMP_CxCR_RIE
*          @arg  CMP_CxCR_FIE
*          @arg  CMP_CxCR_HIE
*          @arg  CMP_CxCR_LIE
*@retval State of bit (1 or 0).
***********************************************************************************
  */
__STATIC_INLINE void CMP_Disable_IT(COMP_TypeDef *COMPx, uint32_t IT)
{
	CLEAR_BIT(COMPx->CR, IT );
}

/**
***********************************************************************************
*@Function CMP_Clear_Flag
*@brief    Clear CMP Flag.
*@param1   COMPx:
*           @arg CMP Instance
*@param1   Flag:
*          @arg  CMP_CxCR_RIF
*          @arg  CMP_CxCR_FIF
*          @arg  CMP_CxCR_HIF
*          @arg  CMP_CxCR_LIF
*@retval State of bit (1 or 0).
***********************************************************************************
  */
__STATIC_INLINE void CMP_Clear_Flag(COMP_TypeDef *COMPx, uint32_t Flag)
{
	CLEAR_BIT(COMPx->CR, Flag);
}

/**
***********************************************************************************
*@Function CMP_Get_Flag
*@brief    Get CMP Flag.
*@param1   COMPx:
*           @arg CMP Instance
*@param1   Flag:
*          @arg  CMP_CxCR_RIF
*          @arg  CMP_CxCR_FIF
*          @arg  CMP_CxCR_HIF
*          @arg  CMP_CxCR_LIF
*@retval State of bit (1 or 0).
***********************************************************************************
  */
__STATIC_INLINE uint32_t CMP_Get_Flag(COMP_TypeDef *COMPx, uint32_t Flag)
{
    return (READ_BIT(COMPx->CR, Flag) == (Flag));
}

/**
  * @function  CMP_Set_RHYST
  * @brief  Set RHYST of the selected CMP
  * @param  COMPx:
            @arg CMP Instance
  * @param  Continuous:
  *         @arg CMP_CxCR_RHYST_0mV
  *         @arg CMP_CxCR_RHYST_20mV
  *         @arg CMP_CxCR_RHYST_40mV
  *         @arg CMP_CxCR_RHYST_60mV
  * @retval None
  */
__STATIC_INLINE void CMP_Set_RHYST(COMP_TypeDef *COMPx, uint32_t Rhyst)
{
  MODIFY_REG(COMPx->CR, CMP_CxCR_RHYST, Rhyst);
}

/**
  * @function  CMP_Set_FHYST
  * @brief  Set FHYST of the selected CMP
  * @param  COMPx:
            @arg CMP Instance
  * @param  Continuous:
  *         @arg CMP_CxCR_FHYST_0mV 
  *         @arg CMP_CxCR_FHYST_20mV
  *         @arg CMP_CxCR_FHYST_40mV
  *         @arg CMP_CxCR_FHYST_60mV
  * @retval None
  */
__STATIC_INLINE void CMP_Set_FHYST(COMP_TypeDef *COMPx, uint32_t Fhyst)
{
  MODIFY_REG(COMPx->CR, CMP_CxCR_FHYST, Fhyst);
}

/**
  * @function  CMP_Set_INNSEL
  * @brief  Set INNSEL of the selected CMP
  * @param  COMPx:
            @arg CMP Instance
  * @param  Innsel:
  *         @arg CMP_INM_SEL_N1        
  *         @arg CMP_INM_SEL_N2        
  *         @arg CMP_INM_SEL_N3               
  *         @arg CMP_INM_SEL_SRN_Center
  *         @arg CMP_INM_SEL_CRV       
  * @retval None
  */
__STATIC_INLINE void CMP_Set_INNSEL(COMP_TypeDef *COMPx, uint32_t Innsel)
{
  MODIFY_REG(COMPx->CR, CMP_CxCR_INM_SEL, Innsel);
}

/**
  * @function  CMP_Set_INPSEL
  * @brief  Set INNSEL of the selected CMP
  * @param  COMPx:
            @arg CMP Instance
  * @param  Continuous:
  *         @arg CMP_INP_SEL_P1           
  *         @arg CMP_INP_SEL_P2           
  *         @arg CMP_INP_SEL_P3_CMP1      
  *         @arg CMP_INP_SEL_OPA2_out_CMP2
  *         @arg CMP_INP_SEL_OPA1_out_CMP1
  *         @arg CMP_INP_SEL_OPA3_out_CMP2
  * @retval None
  */
__STATIC_INLINE void CMP_Set_INPSEL(COMP_TypeDef *COMPx, uint32_t Inpsel)
{
  MODIFY_REG(COMPx->CR, CMP_CxCR_INP_SEL, Inpsel);
}

/**
  * @function  CMP_Set_BLANKING
  * @brief  Set Blanking of the selected CMP
  * @param  COMPx:
            @arg CMP Instance
  * @param  Continuous:
  *         @arg CMP_CxCR_BLANKING_SEL_NoBlanking
  *         @arg CMP_CxCR_BLANKING_SEL_TIM2_OC4  
  *         @arg CMP_CxCR_BLANKING_SEL_TIM2_OC3  
  *         @arg CMP_CxCR_BLANKING_SEL_TIM3_OC3  
  *         @arg CMP_CxCR_BLANKING_SEL_TIM8_OC5  
  *         @arg CMP_CxCR_BLANKING_SEL_TIM8_OC4  
  *         @arg CMP_CxCR_BLANKING_SEL_TIM15_OC1  
  *         @arg CMP_CxCR_BLANKING_SEL_TIM15_OC2

  * @retval None
  */
__STATIC_INLINE void CMP_Set_BLANKING(COMP_TypeDef *COMPx, uint32_t Blanking)
{
  MODIFY_REG(COMPx->CR, CMP_CxCR_BLANKING_SEL, Blanking);
}

/**
  * @function  CMP_Set_PADJ_DATA
  * @brief  Set  PADJ_DATA of the selected CMP
  * @param  ADCx:
            @arg CMP Instance
  * @param  offest:
  *         @ref offest
  * @retval None
  */
__STATIC_INLINE void CMP_Set_PADJ_DATA(COMP_TypeDef *COMPx, uint32_t offest)
{
  MODIFY_REG(COMPx->CAL, CMP_RGxCAL_PADJ, offest);
}

/**
  * @function  CMP_Read_PADJ_DATA
  * @brief  Get value of PADJ_DATA of the selected CMP
  * @param  COMPx:
            @arg CMP Instance
  * @retval offest of PADJ_DATA
  */
__STATIC_INLINE uint32_t CMP_Read_PADJ_DATA(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CAL, CMP_RGxCAL_PADJ));
}


/**
  * @function  CMP_Set_NADJ_DATA
  * @brief  Set  NADJ_DATA of the selected CMP
  * @param  ADCx:
            @arg CMP Instance
  * @param  offest:
  *         @ref offest
  * @retval None
  */
__STATIC_INLINE void CMP_Set_NADJ_DATA(COMP_TypeDef *COMPx, uint32_t offest)
{
  MODIFY_REG(COMPx->CAL, CMP_RGxCAL_NADJ, offest);
}

/**
  * @function  CMP_Get_NADJ_DATA
  * @brief  Get value of NADJ_DATA of the selected CMP
  * @param  COMPx:
            @arg CMP Instance
  * @retval offest of NADJ_DATA
  */
__STATIC_INLINE uint32_t CMP_Get_NADJ_DATA(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CAL, CMP_RGxCAL_NADJ));
}

/**
  * @function  CMP_Enable_CALP
  * @brief  Enable PEN of the selected CMP
  * @param  COMPx:
  *          @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Enable_CALP(COMP_TypeDef *COMPx)
{
	SET_BIT(COMPx->CAL,CMP_RGxCAL_PEN);      
}

/**
  * @function  CMP_Disable_PEN
  * @brief  Disable PEN of the selected CMP
  * @param  COMPx:
  *         @arg CMP Instance 
  * @retval None
  */
__STATIC_INLINE void CMP_Disable_CALP(COMP_TypeDef *COMPx)
{
	CLEAR_BIT(COMPx->CAL,CMP_RGxCAL_PEN); 
}

/**
  * @function  CMP_Enable_CALN
  * @brief  Enable NEN of the selected CMP
  * @param  COMPx:
  *         @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Enable_CALN(COMP_TypeDef *COMPx)
{
	SET_BIT(COMPx->CAL,CMP_RGxCAL_NEN);      
}

/**
  * @function  CMP_Disable_CALN
  * @brief  Disable NEN of the selected CMP
  * @param  COMPx:
  *         @arg CMP Instance 
  * @retval None
  */
__STATIC_INLINE void CMP_Disable_CALN(COMP_TypeDef *COMPx)
{
	CLEAR_BIT(COMPx->CAL,CMP_RGxCAL_NEN); 
}

/**
  * @function  CMP_CH_BLANK_Enable
  * @brief  Enable the CMP change chanel blank
  * @param  COMPx:
  *         @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Enable_CHBLANK(COMP_TypeDef *COMPx)
{
	SET_BIT(COMPx->CR,CMP_CxCR_CH_EN);     
}

/**
  * @function  CMP_CH_BLANK_Disable
  * @brief  Disable the CMP change chanel blank
  * @param  COMPx:
  *         @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Disable_CHBLANK(COMP_TypeDef *COMPx)
{
	CLEAR_BIT(COMPx->CR,CMP_CxCR_CH_EN);  
}

/**
  * @function  CMP_BAS_Enable
  * @brief  Enable the ADC/OPA/SRN/CRV sampling blank
  * @param  COMPx:
  *         @arg CMP Instance
  * @param  Continuous:
  *         @arg CMP_CxCR_BASEN
  *         @arg CMP_CxCR_CMP_BAS_EN_OPA
  * @retval None
  */
__STATIC_INLINE void CMP_Enable_BAS(COMP_TypeDef *COMPx,uint32_t bas_select)
{
	SET_BIT(COMPx->CR,bas_select);     
}


/**
  * @function  CMP_Enable_SRNBAS
  * @brief  Enable CMP SRNBAS
  * @param  None
  * @retval None
  */
__STATIC_INLINE void CMP_Enable_SRNBAS(void)
{
	SET_BIT(COMP->CR1,CMP_CR1_SRN_BAS_EN);     
}


/**
  * @function  CMP_Enable_CRVBAS
  * @brief  Enable CMP CRVBAS
  * @param  None
  * @retval None
  */
__STATIC_INLINE void CMP_Enable_CRVBAS(void )
{
	SET_BIT(COMP->CR2,CMP_CRV_BAS_EN);     
}

/**
  * @function  CMP_BAS_Disable
  * @brief  Disable the ADC/OPA/SRN/CRV sampling blank
  * @param  COMPx:
  *         @arg CMP Instance
  * @param  Continuous:
  *         @arg CMP_CxCR_BASEN
  *         @arg CMP_CxCR_CMP_BAS_EN_OPA
  * @retval None
  */
__STATIC_INLINE void CMP_Disable_BAS(COMP_TypeDef *COMPx,uint32_t bas_select)
{
	CLEAR_BIT(COMPx->CR,bas_select);  
}


/**
  * @function  CMP_Disable_SRNBAS
  * @brief  Disable CMP SRNBAS
  * @param  None
  * @retval None
  */
__STATIC_INLINE void CMP_Disable_SRNBAS(void)
{
	CLEAR_BIT(COMP->CR1,CMP_CR1_SRN_BAS_EN);     
}


/**
  * @function  CMP_Disable_CRVBAS
  * @brief  Disable CMP CRVBAS
  * @param  None
  * @retval None
  */
__STATIC_INLINE void CMP_Disable_CRVBAS(void )
{
	CLEAR_BIT(COMP->CR2,CMP_CRV_BAS_EN);     
}

/**
  * @function  CMP_CH_DIS_Enable
  * @brief  Enable the p end of the CMP  switches over to actively close chanel
  * @param  COMPx:
  *         @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Enable_CHDIS(COMP_TypeDef *COMPx)
{
	SET_BIT(COMPx->CR,CMP_CxCR_CH_DIS);     
}

/**
  * @function  CMP_CH_DIS_Disable
  * @brief  Disable the p end of the CMP  switches over to actively close chanel
  * @param  COMPx:
  *         @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Disable_CHDIS(COMP_TypeDef *COMPx)
{
	CLEAR_BIT(COMPx->CR,CMP_CxCR_CH_DIS);  
}

/**
  * @function  CMP_CxCR_CHDIS_BLK_Enable
  * @brief  Enable EN of the CMP change chanel blank
  * @param  COMPx:
  *         @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Enable_CHDISBLK(COMP_TypeDef *COMPx)
{
	SET_BIT(COMPx->CR,CMP_CxCR_CH_DIS_BLANKING);     
}

/**
  * @function  CMP_CxCR_CHDIS_BLK_Disable
  * @brief  Disable EN of the CMP change chanel blank
  * @param  COMPx:
  *         @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Disable_CHDISBLK(COMP_TypeDef *COMPx)
{
	CLEAR_BIT(COMPx->CR,CMP_CxCR_CH_DIS_BLANKING);  
}

/**
  * @function  CMP_SRN_Enable
  * @brief  Enable the CMP SRN
  * @param  COMPx:
  *         @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Enable_SRN(void)
{
	SET_BIT(COMP->CR1,CMP_CR1_SRN_EN);     
}

/**
  * @function  CMP_SRN_Disable
  * @brief  Disable the CMP SRN
  * @param  COMPx:
  *         @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Disable_SRN(void)
{
	CLEAR_BIT(COMP->CR1,CMP_CR1_SRN_EN);     
}

/**
  * @function  CMP_SRNdout_Enable
  * @brief  Enable the CMP SRN_dout
  * @param  COMPx:
  *         @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Enable_SRNdout(void)
{
	SET_BIT(COMP->CR1,CMP_CR1_SRN_Dout);     
}

/**
  * @function  CMP_SRNdout_Disable
  * @brief  Disable the CMP SRN_dout
  * @param  COMPx:
  *         @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Disable_SRNdout(void)
{
	CLEAR_BIT(COMP->CR1,CMP_CR1_SRN_Dout);     
}

/**
  * @function  CMP_CRV_Enable
  * @brief  Enable the CMP CRV
  * @param  COMPx:
  *         @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Enable_CRV(void)
{
	SET_BIT(COMP->CR2,CMP_CR2_CRV_EN);     
}

/**
  * @function  CMP_CRV_Disable
  * @brief  Disable the CMP CRV
  * @param  COMPx:
  *         @arg CMP Instance
  * @retval None
  */
__STATIC_INLINE void CMP_Disable_CRV(void)
{
	CLEAR_BIT(COMP->CR2,CMP_CR2_CRV_EN);     
}

/**
***********************************************************************************
*@Function CMP_Set_CH1VSEL
*@brief    SET CMP_CR2_CRV_SEL.
*@param   val:
*         @arg   CMP_CRV_SEL_1_32 
*         @arg   CMP_CRV_SEL_2_32 
*         @arg   CMP_CRV_SEL_3_32 
*         @arg   CMP_CRV_SEL_4_32 
*         @arg   CMP_CRV_SEL_5_32 
*         @arg   CMP_CRV_SEL_6_32 
*         @arg   CMP_CRV_SEL_7_32 
*         @arg   CMP_CRV_SEL_8_32 
*         @arg   CMP_CRV_SEL_9_32 
*         @arg   CMP_CRV_SEL_10_32
*         @arg   CMP_CRV_SEL_11_32
*         @arg   CMP_CRV_SEL_12_32
*         @arg   CMP_CRV_SEL_13_32
*         @arg   CMP_CRV_SEL_14_32
*         @arg   CMP_CRV_SEL_15_32
*         @arg   CMP_CRV_SEL_16_32
*         @arg   CMP_CRV_SEL_17_32
*         @arg   CMP_CRV_SEL_18_32
*         @arg   CMP_CRV_SEL_19_32
*         @arg   CMP_CRV_SEL_20_32
*         @arg   CMP_CRV_SEL_21_32
*         @arg   CMP_CRV_SEL_22_32
*         @arg   CMP_CRV_SEL_23_32
*         @arg   CMP_CRV_SEL_24_32
*         @arg   CMP_CRV_SEL_25_32
*         @arg   CMP_CRV_SEL_26_32
*         @arg   CMP_CRV_SEL_27_32
*         @arg   CMP_CRV_SEL_28_32
*         @arg   CMP_CRV_SEL_29_32
*         @arg   CMP_CRV_SEL_30_32
*         @arg   CMP_CRV_SEL_31_32
*         @arg   CMP_CRV_SEL_32_32
***********************************************************************************
  */
__STATIC_INLINE void CMP_Set_CRV1SEL(uint32_t val)
{
	MODIFY_REG(COMP->CR2,  CMP_CR2_CRV_SEL , val );
}

/**
***********************************************************************************
*@Function CMP_Set_CH2VSEL
*@brief    SET CMP_CR2_CRV_SEL.
*@param   val:
*         @arg   CMP_CRV_SEL_1_32 
*         @arg   CMP_CRV_SEL_2_32 
*         @arg   CMP_CRV_SEL_3_32 
*         @arg   CMP_CRV_SEL_4_32 
*         @arg   CMP_CRV_SEL_5_32 
*         @arg   CMP_CRV_SEL_6_32 
*         @arg   CMP_CRV_SEL_7_32 
*         @arg   CMP_CRV_SEL_8_32 
*         @arg   CMP_CRV_SEL_9_32 
*         @arg   CMP_CRV_SEL_10_32
*         @arg   CMP_CRV_SEL_11_32
*         @arg   CMP_CRV_SEL_12_32
*         @arg   CMP_CRV_SEL_13_32
*         @arg   CMP_CRV_SEL_14_32
*         @arg   CMP_CRV_SEL_15_32
*         @arg   CMP_CRV_SEL_16_32
*         @arg   CMP_CRV_SEL_17_32
*         @arg   CMP_CRV_SEL_18_32
*         @arg   CMP_CRV_SEL_19_32
*         @arg   CMP_CRV_SEL_20_32
*         @arg   CMP_CRV_SEL_21_32
*         @arg   CMP_CRV_SEL_22_32
*         @arg   CMP_CRV_SEL_23_32
*         @arg   CMP_CRV_SEL_24_32
*         @arg   CMP_CRV_SEL_25_32
*         @arg   CMP_CRV_SEL_26_32
*         @arg   CMP_CRV_SEL_27_32
*         @arg   CMP_CRV_SEL_28_32
*         @arg   CMP_CRV_SEL_29_32
*         @arg   CMP_CRV_SEL_30_32
*         @arg   CMP_CRV_SEL_31_32
*         @arg   CMP_CRV_SEL_32_32
***********************************************************************************
  */
__STATIC_INLINE void CMP_Set_CRV2SEL(uint32_t val)
{
	MODIFY_REG(COMP->CR2,  CMP_CR2_CRV_SEL << 5 , val << 5);
}
 
 
 
/** @defgroup FLASH_Exported_Functions   */

void CMP_Init(COMP_TypeDef *COMPx, CMP_InitTypeDef *CMP_InitStruct);


#ifdef __cplusplus
}
#endif

#endif /* __rx32h6xx_CMP_H__ */

