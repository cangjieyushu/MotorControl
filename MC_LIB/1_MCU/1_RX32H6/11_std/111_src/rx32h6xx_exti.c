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
* File         : rx32h6xx_exti.c
* By           : RX_SD_Team
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

#include "rx32h6xx_exti.h"

/**
  * @brief  De-initialize the EXTI registers to their default reset values.
  * @retval An ErrorStatus enumeration value:
  *         @arg @ref SUCCESS: EXTI registers are de-initialized
  *         @arg @ref ERROR: not applicable
  */
void EXTI_DeInit(void)
{
  /* Interrupt mask register set to default reset values */
  EXTI_WriteReg(IMR,   0x00000000U);
  /* Event mask register set to default reset values */
  EXTI_WriteReg(EMR,   0x00000000U);
  /* Rising Trigger selection register set to default reset values */
  EXTI_WriteReg(RTSR,  0x00000000U);
  /* Falling Trigger selection register set to default reset values */
  EXTI_WriteReg(FTSR,  0x00000000U);
  /* Software interrupt event register set to default reset values */
  EXTI_WriteReg(SWIER, 0x00000000U);
  /* Pending register clear */
  EXTI_WriteReg(PR,    0x000FFFFFU);

}

/**
  * @brief  Set each @ref EXTI_InitTypeDef field to default value.
  * @param  EXTI_InitStruct Pointer to a @ref EXTI_InitTypeDef structure.
  * @retval None
  */
void EXTI_StructInit(EXTI_InitTypeDef *EXTI_InitStruct)
{
  EXTI_InitStruct->Line           = EXTI_LINE_NONE;
  EXTI_InitStruct->LineCommand    = DISABLE;
  EXTI_InitStruct->Mode           = EXTI_MODE_IT;
  EXTI_InitStruct->Trigger        = EXTI_TRIGGER_FALLING;
}

/**
  * @brief  Initialize the EXTI registers according to the specified parameters in EXTI_InitStruct.
  * @param  EXTI_InitStruct pointer to a @ref EXTI_InitTypeDef structure.
  * @param  Line This parameter can be one of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @param  LineCommand This parameter can be one of the following values:
  *         @arg @ref ENABLE
  *         @arg @ref DISABLE  
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref EXTI_MODE_IT
  *         @arg @ref EXTI_MODE_EVENT 
  *         @arg @ref EXTI_MODE_IT_EVENT 
  * @param  Trigger This parameter can be one of the following values:
  *         @arg @ref EXTI_TRIGGER_RISING
  *         @arg @ref EXTI_TRIGGER_FALLING 
  *         @arg @ref EXTI_TRIGGER_RISING_FALLING 
  * @retval None.
  */
void EXTI_Init(EXTI_InitTypeDef *EXTI_InitStruct)
{
  /* ENABLE LineCommand */
  if (EXTI_InitStruct->LineCommand != DISABLE)
  {
    /* Configure EXTI Lines in range from 0 to 31 */
    if (EXTI_InitStruct->Line != EXTI_LINE_NONE)
    {
      switch (EXTI_InitStruct->Mode)
      {
        case EXTI_MODE_IT:
          /* First Disable Event on provided Lines */
          EXTI_Disable_Event(EXTI_InitStruct->Line);
          /* Then Enable IT on provided Lines */
          EXTI_Enable_IT(EXTI_InitStruct->Line);
          break;
        case EXTI_MODE_EVENT:
          /* First Disable IT on provided Lines */
          EXTI_Disable_IT(EXTI_InitStruct->Line);
          /* Then Enable Event on provided Lines */
          EXTI_Enable_Event(EXTI_InitStruct->Line);
          break;
        case EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          EXTI_Enable_IT(EXTI_InitStruct->Line);
          EXTI_Enable_Event(EXTI_InitStruct->Line);
          break;
        default:
          /* First Disable Event on provided Lines */
          EXTI_Disable_Event(EXTI_InitStruct->Line);
          /* Then Enable IT on provided Lines */
          EXTI_Enable_IT(EXTI_InitStruct->Line);
          break;
      }
      if (EXTI_InitStruct->Trigger != EXTI_TRIGGER_NONE)
      {
        switch (EXTI_InitStruct->Trigger)
        {
          case EXTI_TRIGGER_RISING:
            /* First Disable Falling Trigger on provided Lines */
            EXTI_Disable_FallingTrig(EXTI_InitStruct->Line);
            /* Then Enable Rising Trigger on provided Lines */
            EXTI_Enable_RisingTrig(EXTI_InitStruct->Line);
            break;
          case EXTI_TRIGGER_FALLING:
            /* First Disable Rising Trigger on provided Lines */
            EXTI_Disable_RisingTrig(EXTI_InitStruct->Line);
            /* Then Enable Falling Trigger on provided Lines */
            EXTI_Enable_FallingTrig(EXTI_InitStruct->Line);
            break;
          case EXTI_TRIGGER_RISING_FALLING:
            EXTI_Enable_RisingTrig(EXTI_InitStruct->Line);
            EXTI_Enable_FallingTrig(EXTI_InitStruct->Line);
            break;
          default:
            /* First Disable Falling Trigger on provided Lines */
            EXTI_Disable_FallingTrig(EXTI_InitStruct->Line);
            /* Then Enable Rising Trigger on provided Lines */
            EXTI_Enable_RisingTrig(EXTI_InitStruct->Line);
            break;
        }
      }
    }
  }
  /* DISABLE LineCommand */
  else
  {
    /* De-configure EXTI Lines in range from 0 to 31 */
    EXTI_Disable_IT(EXTI_InitStruct->Line);
    EXTI_Disable_Event(EXTI_InitStruct->Line);
  }
}

