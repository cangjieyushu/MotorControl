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
* File         : rx32h6xx_rcc.c
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

#include "rx32h6xx.h"
#include "rx32h6xx_rcc.h"
#include "rx32h6xx_flash.h"

/**
***********************************************************************************
*@Function RCC_ClockConfig
*@brief    Config SYSCLK
*@param  RCC_ClkInitStruct: pointer to a RCC_ClkInitTypeDef structure that contains
*         the configuration information for the specified CMU peripheral.
  * @param  SYSCLKSource:
	*         @arg RCC_CFGR_SW_HSI
  *         @arg RCC_CFGR_SW_PLL
  *         @arg RCC_CFGR_SW_LSI
  * @param  PLLSource:
  *         @ref RCC_CFGR_PLLSRC_HSI
  * @param  PLLMUL:
  *         @arg RCC_CFGR_PLLMUL_10x
  *         @arg RCC_CFGR_PLLMUL_12x
	*         @arg RCC_CFGR_PLLMUL_14x
	*         @arg RCC_CFGR_PLLMUL_15x
	*         @arg RCC_CFGR_PLLMUL_16x
	*         @arg RCC_CFGR_PLLMUL_17x
	*         @arg RCC_CFGR_PLLMUL_18x
	*         @arg RCC_CFGR_PLLMUL_19x
  * @param  LATENCY:
  *         @arg FLASH_Latency_0
	*         @arg FLASH_Latency_1
	*         @arg FLASH_Latency_2
  *         @arg FLASH_Latency_3
  * @param  AHBCLKDivider:
	*         @arg RCC_CFGR_HPRE_DIV1  
	*         @arg RCC_CFGR_HPRE_DIV2  
	*         @arg RCC_CFGR_HPRE_DIV4  
	*         @arg RCC_CFGR_HPRE_DIV8  
	*         @arg RCC_CFGR_HPRE_DIV16 
	*         @arg RCC_CFGR_HPRE_DIV64 
	*         @arg RCC_CFGR_HPRE_DIV128
	*         @arg RCC_CFGR_HPRE_DIV256
	*         @arg RCC_CFGR_HPRE_DIV512
	* @param  APB1CLKDivider:
  *         @arg RCC_CFGR_PPRE1_DIV1 
	*         @arg RCC_CFGR_PPRE1_DIV2 
	*         @arg RCC_CFGR_PPRE1_DIV4 
	*         @arg RCC_CFGR_PPRE1_DIV8 
	*         @arg RCC_CFGR_PPRE1_DIV16
	* @param  APB2CLKDivider:
  *         @arg RCC_CFGR_PPRE2_DIV1 
	*         @arg RCC_CFGR_PPRE2_DIV2 
	*         @arg RCC_CFGR_PPRE2_DIV4 
	*         @arg RCC_CFGR_PPRE2_DIV8 
	*         @arg RCC_CFGR_PPRE2_DIV16
	* @param  ADCSource:
	*         @arg RCC_CFGR_ADCCLK_SEL_SYSCLK
  *         @arg RCC_CFGR_ADCCLK_SEL_PLL2	
	* @param  ADCCLKDivider:
	*         @arg RCC_CFGR_ADCPRE_DIV2
  *         @arg RCC_CFGR_ADCPRE_DIV3
	*         @arg RCC_CFGR_ADCPRE_DIV4
	*         @arg RCC_CFGR_ADCPRE_DIV5
	*         @arg RCC_CFGR_ADCPRE_DIV6
	*         @arg RCC_CFGR_ADCPRE_DIV7
	*         @arg RCC_CFGR_ADCPRE_DIV8
* @retval None
***********************************************************************************
  */
void RCC_ClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct)
{
  switch(RCC_ClkInitStruct->SYSCLKSource)
  {    
    case RCC_CFGR_SW_HSI:
      RCC_Enable_HSI();
      while(RCC_Get_HSIRDY() != 1){};
      RCC_Set_SysClkSource(RCC_CFGR_SW_HSI);
      while(RCC_Get_SysClkSource() != RCC_CFGR_SWS_HSI){};
      break;
    case RCC_CFGR_SW_LSI:	
      RCC_Enable_LSI();
      while(RCC_Get_LSIRDY() != 1){};
      RCC_Set_SysClkSource(RCC_CFGR_SW_LSI);  
      while(RCC_Get_SysClkSource() != RCC_CFGR_SWS_LSI){};        
      break;
    case RCC_CFGR_SW_PLL:	
      RCC_Enable_HSI();
      while(RCC_Get_HSIRDY() != 1){};
      FLASH_Set_Latency(RCC_ClkInitStruct->LATENCY);  
			RCC_Set_PLLMUL(RCC_CFGR_PLLMUL_12x);
      RCC_Enable_PLL();
      while(RCC_Get_PLLRDY() != 1){};
      RCC_Set_SysClkSource(RCC_CFGR_SW_PLL); 
      while(RCC_Get_SysClkSource() != RCC_CFGR_SWS_PLL){};        
      break;    
    default:
      RCC_Enable_HSI();
      while(RCC_Get_HSIRDY() != 1){};
      RCC_Set_SysClkSource(RCC_CFGR_SW_HSI);
      while(RCC_Get_SysClkSource() != RCC_CFGR_SWS_HSI){};
      break;
  }
  
  RCC_Set_AHBPrescaler(RCC_ClkInitStruct->AHBCLKDivider);
  RCC_Set_APB1Prescaler(RCC_ClkInitStruct->APB1CLKDivider);
  RCC_Set_APB2Prescaler(RCC_ClkInitStruct->APB2CLKDivider);
	RCC_Set_ADCClkSource(RCC_ClkInitStruct->ADCSource);
  RCC_Set_ADCPrescaler(RCC_ClkInitStruct->ADCCLKDivider);
	
}

/**
***********************************************************************************
	*@Function RCC_Get_PLLClock
	*@brief    Get  PLLClock .
	*@param    none.
	*@retval   PLLClock
***********************************************************************************
  */
uint32_t RCC_Get_PLLClock(void)
{
  uint32_t frequency = 0U;
  uint32_t HSI_VALUE = 8000000;
  if((READ_BIT( RCC->CFGR, RCC_CFGR_PLLMULL)>>18)==0)
  {
    frequency = (HSI_VALUE*((READ_BIT( RCC->CFGR, RCC_CFGR_PLLMULL )>>18)+10) );
  }
  else if((READ_BIT( RCC->CFGR, RCC_CFGR_PLLMULL)>>18)==1)
  {
    frequency = (HSI_VALUE*((READ_BIT( RCC->CFGR, RCC_CFGR_PLLMULL )>>18)+11) );
  }
  else
  {
    frequency = (HSI_VALUE*((READ_BIT( RCC->CFGR, RCC_CFGR_PLLMULL )>>18)+12) );
  }
  return frequency;
}

/**
***********************************************************************************
	*@Function RCC_Get_SystemClock
	*@brief    Get  SystemClock .
	*@param    none.
	*@retval   SystemClock
***********************************************************************************
  */
uint32_t RCC_Get_SystemClock(void)
{
  uint32_t frequency = 0U;
  uint32_t LSI_VALUE = 32000;
  uint32_t HSI_VALUE = 16000000;
  switch( RCC_Get_SysClkSource() )
  {
    case RCC_CFGR_SWS_HSI:
    default:
      frequency = HSI_VALUE;
      break;
    case RCC_CFGR_SWS_LSI:
      frequency = LSI_VALUE;
      break;
    case RCC_CFGR_SWS_PLL:
      frequency = RCC_Get_PLLClock();
      break;
  }
  return frequency;
}

/**
***********************************************************************************
	*@Function RCC_Get_AHBClock
	*@brief    Get  AHBClock .
	*@param    none.
	*@retval   AHBClock
***********************************************************************************
  */
uint32_t RCC_Get_AHBClock(void)
{
  return ( RCC_Get_SystemClock() >> AHBPrescTable[ RCC_Get_AHBPrescaler() >> 4 ]);
}

/**
***********************************************************************************
	*@Function RCC_Get_APB1Clock
	*@brief    Get  APB1Clock .
	*@param    none.
	*@retval   APB1Clock
***********************************************************************************
  */
uint32_t RCC_Get_APB1Clock(void)
{
  return ( RCC_Get_AHBClock() >> APBPrescTable[ RCC_Get_APB1Prescaler() >> 8 ] );
}

/**
***********************************************************************************
	*@Function RCC_Get_APB2Clock
	*@brief    Get  APB2Clock .
	*@param    none.
	*@retval   APB2Clock
***********************************************************************************
  */
uint32_t RCC_Get_APB2Clock(void)
{
  return ( RCC_Get_AHBClock() >> APBPrescTable[ RCC_Get_APB2Prescaler() >> 11 ] );
}
