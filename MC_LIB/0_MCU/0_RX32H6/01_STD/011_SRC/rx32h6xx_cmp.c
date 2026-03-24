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
* File         : rx32h6xx_cmp.c
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

#include "rx32h6xx_cmp.h"

/**
***********************************************************************************
*@Function CMP_Init
*@brief    Initial of COMPx
*@param1   COMPx
*@param2  CMP_InitStruct
*@param Pol:
*	        @arg CMP_CxCR_POL_Positive
*	        @arg CMP_CxCR_POL_Negative
*@param OFLT:
*	         @arg CMP_CxCR_OFLT_DIV1    
*	         @arg CMP_CxCR_OFLT_DIV32   
*	         @arg CMP_CxCR_OFLT_DIV64   
*	         @arg CMP_CxCR_OFLT_DIV128  
*	         @arg CMP_CxCR_OFLT_DIV256  
*	         @arg CMP_CxCR_OFLT_DIV512  
*	         @arg CMP_CxCR_OFLT_DIV1024 
*	         @arg CMP_CxCR_OFLT_DIV2048 
*@param Rhyst:
*	        @arg CMP_CxCR_RHYST_0mV
*	        @arg CMP_CxCR_RHYST_20mV
*         @arg CMP_CxCR_RHYST_40mV
*	        @arg CMP_CxCR_RHYST_60mV
*@param Fhyst:
*	        @arg CMP_CxCR_FHYST_0mV
*	        @arg CMP_CxCR_FHYST_20mV
*	        @arg CMP_CxCR_FHYST_40mV
*	        @arg CMP_CxCR_FHYST_60mV
*@param INP_Sel:        
*	        @arg CMP_INP_SEL_P1           
*         @arg CMP_INP_SEL_P2           
*         @arg CMP_INP_SEL_P3_CMP1      
*	        @arg CMP_INP_SEL_OPA2_out_CMP2
*	        @arg CMP_INP_SEL_OPA1_out_CMP1
*         @arg CMP_INP_SEL_OPA3_out_CMP2
*@param INN_Sel:
*	        @arg CMP_INM_SEL_N1        
*	        @arg CMP_INM_SEL_N2        
*	        @arg CMP_INM_SEL_N3        
*	        @arg CMP_INM_SEL_SRN_Center
*	        @arg CMP_INM_SEL_CRV       
***********************************************************************************
  */
void CMP_Init(COMP_TypeDef *COMPx, CMP_InitTypeDef *CMP_InitStruct)
{ 
	MODIFY_REG(COMPx->CR, (CMP_CxCR_POL | CMP_CxCR_RHYST | CMP_CxCR_FHYST),\
							(CMP_InitStruct->Pol | CMP_InitStruct->Rhyst | CMP_InitStruct->Fhyst));
	
	MODIFY_REG(COMPx->CR, CMP_CxCR_INM_SEL | CMP_CxCR_INP_SEL,\
							( CMP_InitStruct->INM_Sel | CMP_InitStruct->INP_Sel ));
	
	MODIFY_REG(COMPx->CR, CMP_CxCR_OFLT ,\
							( CMP_InitStruct->OFLT ));
  
  	MODIFY_REG(COMP->CR2, CMP_CR2_CRV_EN | CMP_CR2_CRV_SRC_2p5 ,\
  ( CMP_InitStruct->CRV_En<<1 | CMP_InitStruct->CRV_Src ));
  
  if(COMPx == COMP1)
  {
  	MODIFY_REG(COMP->CR2, CMP_CR2_CRV_SEL ,CMP_InitStruct->CRV_SEL);
  }
  else
  {
  	MODIFY_REG(COMP->CR2, CMP_CR2_CRV_SEL << 5 ,CMP_InitStruct->CRV_SEL << 5);
  }
  	MODIFY_REG(COMP->CR1, CMP_CR1_SRN_EN ,CMP_InitStruct->CR1_SRN);
}



