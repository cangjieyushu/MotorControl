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
* File         : rx32h6xx_opamp.c
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

#include "rx32h6xx_opamp.h"

/**
  * @function  OPAMP_DeInit
  * @brief  De-initialize registers of the selected OPAMP instance
  *         to their default reset values.
  * @param  OPAMPx:
  *         @arg OPAMP Instance
  * @retval None.
  */
void OPAMP_DeInit(OPAMP_TypeDef *OPAMPx)
{
  RCC_Enable_APB2RST(RCC_APB2RSTR_SYSCFGRST);
  RCC_Disable_APB2RST(RCC_APB2RSTR_SYSCFGRST);
}

/**
  * @function  OPAMP_StructInit
  * @brief  Set each @ref OPAMP_InitTypeDef field to default value.
  * @param  OPAMP_InitStruct pointer to a @ref OPAMP_InitTypeDef structure
  *                         whose fields will be set to default values.
  * @retval None
  */
void OPAMP_StructInit(OPAMP_InitTypeDef *OPAMP_InitStruct)
{
  OPAMP_InitStruct->FunctionalMode    	= OPAMP_MODE_FOLLOW;
  OPAMP_InitStruct->OPAMP_OUTCONNECT    = OPAMP_VM_NO_CONNECT;
  OPAMP_InitStruct->BIASMode            = OPAMP_BIAS_GND;
  OPAMP_InitStruct->PGAGain             = OPAMP_GAIN_4;
  OPAMP_InitStruct->TOEXT               = OPAMP_CSR_TOEXT_DISABLE;
  OPAMP_InitStruct->VPSEL               = OPAMP_CSR_VPSEL_P1;
}

/**
  * @function  OPAMP_Init
  * @brief  Initialize some features of OPAMP instance.
  * @param  OPAMPx:
  *         @arg OPAMP1
  *         @arg OPAMP2
  *         @arg OPAMP3
  * @param  FunctionalMode:
  *         @arg OPAMP_MODE_NO_CONNECT
  *         @arg OPAMP_MODE_PGA      	
  *         @arg OPAMP_MODE_FOLLOW    
  *         @arg OPAMP_MODE_OPA	
  * @param  OPAMP_OUTCONNECT:
  *         @arg OPAMP_VM_NO_CONNECT 
  *         @arg OPAMP_VM_TO_GND     
  *         @arg OPAMP_VM_TO_VIN1    
  *         @arg OPAMP_VM_TO_VIN2    
  * @param  BIASMode:
  *         @arg OPAMP_BIAS_GND 
  *         @arg OPAMP_BIAS_VBG 
  *         @arg OPAMP_BIAS_VREF
  * @param  PGAGain:
  *         @arg OPAMP_GAIN_4 
  *         @arg OPAMP_GAIN_8 
  *         @arg OPAMP_GAIN_12
  *         @arg OPAMP_GAIN_16
  * @param  TOEXT:
  *         @arg OPAMP_CSR_TOEXT_ENABLE 
  *         @arg OPAMP_CSR_TOEXT_DISABLE
  * @param  VPSEL:
  *         @arg OPAMP_CSR_VPSEL_P1
  *         @arg OPAMP_CSR_VPSEL_P2
  * @param  OPAMP_InitStruct Pointer to a @ref OPAMP_InitTypeDef structure
  * @retval None.
  */
void OPAMP_Init(OPAMP_TypeDef *OPAMPx, OPAMP_InitTypeDef *OPAMP_InitStruct)
{
  if( OPAMP_Is_Locked(OPAMPx) == 0U)
  {
    if (OPAMP_InitStruct->FunctionalMode == OPAMP_MODE_PGA)
    { 
			switch(OPAMP_InitStruct->BIASMode)
			{
				case 0:
					OPAMP_Enable_BIAS_GND(OPAMPx);
					OPAMP_Disable_BIAS_VOL(OPAMPx);
					break;
				case 1:
					OPAMP_Disable_BIAS_GND(OPAMPx);
					OPAMP_Enable_BIAS_VOL(OPAMPx);
					OPAMP_Set_VBGINT(OPAMPx, OPAMP_VBGINT_ENABLE);
					OPAMP_Set_VOL_SEL(OPAMPx,OPAMP_BIAS_VOL_SEL_VBG);                  
					break;
				case 2:
					OPAMP_Disable_BIAS_GND(OPAMPx);
					OPAMP_Enable_BIAS_VOL(OPAMPx);
					OPAMP_Set_VOL_SEL(OPAMPx,OPAMP_BIAS_VOL_SEL_Vref);  
					break;
			}
      MODIFY_REG(OPAMPx->CSR,
                   OPAMP_CSR_GAIN
                   | OPAMP_CSR_VMSEL
									 | OPAMP_CSR_OUTCONNECT
                   ,
                    OPAMP_InitStruct->PGAGain
                   | OPAMP_InitStruct->FunctionalMode
                   | OPAMP_InitStruct->OPAMP_OUTCONNECT
                  );
      if(OPAMPx==OPAMP3)
      {
        OPAMP_Set_VP_SEL(OPAMP_InitStruct->VPSEL);
        OPAMP_Enable_TOEXT(OPAMP_InitStruct->TOEXT);
        OPAMP_Enable_TOINT(OPAMP_InitStruct->TOINT);
      }
    }
		
		else if(OPAMP_InitStruct->FunctionalMode == OPAMP_MODE_OPA)
		{
			OPAMP_Disable_BIAS_GND(OPAMPx);
			OPAMP_Disable_BIAS_VOL(OPAMPx);
			MODIFY_REG(OPAMPx->CSR,
										OPAMP_CSR_VMSEL
									 | OPAMP_CSR_OUTCONNECT
									 ,
										OPAMP_InitStruct->FunctionalMode
									 | OPAMP_InitStruct->OPAMP_OUTCONNECT
									);
			if(OPAMPx==OPAMP3)
      {
        OPAMP_Set_VP_SEL(OPAMP_InitStruct->VPSEL);
        OPAMP_Enable_TOEXT(OPAMP_InitStruct->TOEXT);
        OPAMP_Enable_TOINT(OPAMP_InitStruct->TOINT);
      }
		}
		
	
    else
    {
			OPAMP_Disable_BIAS_GND(OPAMPx);
			OPAMP_Disable_BIAS_VOL(OPAMPx);
      MODIFY_REG(OPAMPx->CSR,
                    OPAMP_CSR_VMSEL
									 | OPAMP_CSR_OUTCONNECT
                   ,
                    OPAMP_InitStruct->FunctionalMode
                   | OPAMP_InitStruct->OPAMP_OUTCONNECT
                  );
			if(OPAMPx==OPAMP3)
      {
        OPAMP_Set_VP_SEL(OPAMP_InitStruct->VPSEL);
        OPAMP_Enable_TOEXT(OPAMP_InitStruct->TOEXT);
        OPAMP_Enable_TOINT(OPAMP_InitStruct->TOINT);
      }
		}
	}
}
