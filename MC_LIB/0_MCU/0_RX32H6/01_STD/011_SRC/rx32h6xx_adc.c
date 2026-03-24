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
* File         : rx32h6xx_adc.c
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

#include "rx32h6xx_adc.h"

/* Private macros ------------------------------------------------------------*/

/**
  * @function  ADC_Reg_StructInit
  * @brief  Set each  ADC_Reg_InitStruct field to default value
  * @param  ADCx :
            @arg ADC Instance
  * @retval 
  */
void ADC_Reg_StructInit(ADC_Reg_InitTypeDef* ADC_Reg_InitStruct)
{
	ADC_Reg_InitStruct->TriggerSource 			= ADC_CR2_EXTSEL_INSOURCE;                       
	ADC_Reg_InitStruct->Continuous 					= ADC_CR2_CONT_SINGLE;                              
	ADC_Reg_InitStruct->ScanMode 						= ADC_CR1_SCAN_DISABLE;                                                                  
	ADC_Reg_InitStruct->DataAlignment 			= ADC_CR2_ALIGN_RIGHT;
	ADC_Reg_InitStruct->AnalogWatchDog 			= ADC_CR1_AWD_DISABLE;
	ADC_Reg_InitStruct->RegularDiscont			= ADC_CR1_DISCEN_DISABLE;
}

/**
  * @function  ADC_Reg_Init
  * @brief  read complete interrupt Flag status of the selected ADC	
  * @param  ADCx :
  *         @arg ADC Instance
  * @param  TriggerSource:
  *         @arg ADC_CR2_EXTSEL_INSOURCE     
  *         @arg ADC_CR2_EXTSEL_TIM8_TRGO2        
  *         @arg ADC_CR2_EXTSEL_TIM8_CC4_CC5  
  *         @arg ADC_CR2_EXTSEL_TIM2_CC3_CC4
  *         @arg ADC_CR2_EXTSEL_TIM2_CC4       
  *         @arg ADC_CR2_EXTSEL_TIM3_CC2      
  *         @arg ADC_CR2_EXTSEL_TIM3_TRGO      
  *         @arg ADC_CR2_EXTSEL_EXTI3       
  *         @arg ADC_CR2_EXTSEL_SWSTART     	
  * @param  Continuous:
  *         @arg ADC_CR2_CONT_SINGLE
  *         @arg ADC_CR2_CONT_CONTINUOUS
  * @param  ScanMode:
  *         @arg ADC_CR1_SCAN_DISABLE
  *         @arg ADC_CR1_SCAN_ENABLE
  * @param  SequencerNbRanks:
  *         @ref ADC_SQRL_SCAN_DISABLE
  *         @ref ADC_SQRL_SCAN_2RANKS 
  *         @ref ADC_SQRL_SCAN_3RANKS 
  *         @ref ADC_SQRL_SCAN_4RANKS 
  *         @ref ADC_SQRL_SCAN_5RANKS 
  *         @ref ADC_SQRL_SCAN_6RANKS 
  *         @ref ADC_SQRL_SCAN_7RANKS 
  *         @ref ADC_SQRL_SCAN_8RANKS  
  * @param  DataAlignment:
  *         @arg ADC_CR2_ALIGN_RIGHT
  *         @arg ADC_CR2_ALIGN_LEFT  
  * @param  AnalogWatchDog:
  *         @arg ADC_CR1_AWD_ENABLE
  *         @arg ADC_CR1_AWD_DISABLE  
  * @param  AWDChannelGroup:
  *         @arg ADC_AWD_DISABLE
  *         @arg ADC_AWD_ALL_CHANNELS_REG
  *         @arg ADC_AWD_ALL_CHANNELS_INJ
  *         @arg ADC_AWD_ALL_CHANNELS_REG_INJ
  *         @arg ADC_AWD_CHANNEL_0_REG 
  *         @arg ADC_AWD_CHANNEL_0_INJ 
  *         @arg ADC_AWD_CHANNEL_0_REG_INJ
  *         @arg ADC_AWD_CHANNEL_1_REG 
  *         @arg ADC_AWD_CHANNEL_1_INJ 
  *         @arg ADC_AWD_CHANNEL_1_REG_INJ
  *         @arg ADC_AWD_CHANNEL_2_REG 
  *         @arg ADC_AWD_CHANNEL_2_INJ 
  *         @arg ADC_AWD_CHANNEL_2_REG_INJ
  *         @arg ADC_AWD_CHANNEL_3_REG 
  *         @arg ADC_AWD_CHANNEL_3_INJ 
  *         @arg ADC_AWD_CHANNEL_3_REG_INJ
  *         @arg ADC_AWD_CHANNEL_4_REG 
  *         @arg ADC_AWD_CHANNEL_4_INJ 
  *         @arg ADC_AWD_CHANNEL_4_REG_INJ
  *         @arg ADC_AWD_CHANNEL_5_REG 
  *         @arg ADC_AWD_CHANNEL_5_INJ 
  *         @arg ADC_AWD_CHANNEL_5_REG_INJ
  *         @arg ADC_AWD_CHANNEL_6_REG 
  *         @arg ADC_AWD_CHANNEL_6_INJ 
  *         @arg ADC_AWD_CHANNEL_6_REG_INJ
  *         @arg ADC_AWD_CHANNEL_7_REG       
  *         @arg ADC_AWD_CHANNEL_7_INJ      
  *         @arg ADC_AWD_CHANNEL_7_REG_INJ  
  *         @arg ADC_AWD_CHANNEL_8_REG       
  *         @arg ADC_AWD_CHANNEL_8_INJ      
  *         @arg ADC_AWD_CHANNEL_8_REG_INJ 
  *         @arg ADC_AWD_CHANNEL_9_REG      
  *         @arg ADC_AWD_CHANNEL_9_INJ       
  *         @arg ADC_AWD_CHANNEL_9_REG_INJ  
  *         @arg ADC_AWD_CHANNEL_10_REG      
  *         @arg ADC_AWD_CHANNEL_10_INJ     
  *         @arg ADC_AWD_CHANNEL_10_REG_INJ       
  *         @arg ADC_AWD_CHANNEL_11_REG      
  *         @arg ADC_AWD_CHANNEL_11_INJ     
  *         @arg ADC_AWD_CHANNEL_11_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_12_REG      
  *         @arg ADC_AWD_CHANNEL_12_INJ     
  *         @arg ADC_AWD_CHANNEL_12_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_13_REG      
  *         @arg ADC_AWD_CHANNEL_13_INJ     
  *         @arg ADC_AWD_CHANNEL_13_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_14_REG      
  *         @arg ADC_AWD_CHANNEL_14_INJ     
  *         @arg ADC_AWD_CHANNEL_14_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_15_REG      
  *         @arg ADC_AWD_CHANNEL_15_INJ     
  *         @arg ADC_AWD_CHANNEL_15_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_16_REG      
  *         @arg ADC_AWD_CHANNEL_16_INJ     
  *         @arg ADC_AWD_CHANNEL_16_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_17_REG      
  *         @arg ADC_AWD_CHANNEL_17_INJ     
  *         @arg ADC_AWD_CHANNEL_17_REG_INJ 
  *         @arg ADC_AWD_CHANNEL_18_REG    
  *         @arg ADC_AWD_CHANNEL_18_INJ    
  *         @arg ADC_AWD_CHANNEL_18_REG_INJ
  *         @arg ADC_AWD_CHANNEL_19_REG    
  *         @arg ADC_AWD_CHANNEL_19_INJ    
  *         @arg ADC_AWD_CHANNEL_19_REG_INJ
  *         @arg ADC_AWD_CHANNEL_20_REG    
  *         @arg ADC_AWD_CHANNEL_20_INJ    
  *         @arg ADC_AWD_CHANNEL_20_REG_INJ
  *         @arg ADC_AWD_CHANNEL_21_REG    
  *         @arg ADC_AWD_CHANNEL_21_INJ    
  *         @arg ADC_AWD_CHANNEL_21_REG_INJ
  *         @arg ADC_AWD_CHANNEL_22_REG    
  *         @arg ADC_AWD_CHANNEL_22_INJ    
  *         @arg ADC_AWD_CHANNEL_22_REG_INJ
  *         @arg ADC_AWD_CHANNEL_23_REG    
  *         @arg ADC_AWD_CHANNEL_23_INJ    
  *         @arg ADC_AWD_CHANNEL_23_REG_INJ  
  * @param  RegularDiscont:
  *         @arg ADC_CR1_DISCEN_ENABLE
  *         @arg ADC_CR1_DISCEN_DISABLE
  * @param  RegularDiscontNumber:
  *         @arg ADC_CR1_DISCONT_DISABLE
  *         @arg ADC_CR1_DISCONT_1RANK
  *         @arg ADC_CR1_DISCONT_2RANKS
  *         @arg ADC_CR1_DISCONT_3RANKS
  *         @arg ADC_CR1_DISCONT_4RANKS
  *         @arg ADC_CR1_DISCONT_5RANKS
  *         @arg ADC_CR1_DISCONT_6RANKS
  *         @arg ADC_CR1_DISCONT_7RANKS
  *         @arg ADC_CR1_DISCONT_8RANKS  
  * @param  EOCOption:
  *         @ref ADC_EOC_OPT_DISABLE
  *         @ref ADC_EOC_OPT_ENABLE	  
  * @retval None .
  */
void ADC_Reg_Init(ADC_TypeDef *ADCx,ADC_Reg_InitTypeDef* ADC_Reg_InitStruct)
{
	ADC_Set_EXTSEL(ADCx, ADC_Reg_InitStruct->TriggerSource);                           /* Set ADC group regular trigger source */
	ADC_Set_CONT(ADCx, ADC_Reg_InitStruct->Continuous);                                /* Set ADC group regular continuous mode */
	ADC_Set_SCAN(ADCx, ADC_Reg_InitStruct->ScanMode);                                  /* Set ADC sacn regular group*/
	ADC_Set_ALIGN(ADCx, ADC_Reg_InitStruct->DataAlignment);                            /* Set ADC conversion data alignment */
	ADC_Set_AWD(ADCx, ADC_Reg_InitStruct->AnalogWatchDog);														 /*Set ADC analog watchdog*/
	ADC_Set_AWDChannels(ADCx,ADC_Reg_InitStruct->AWDChannelGroup);
	ADC_Set_DISCEN(ADCx, ADC_Reg_InitStruct->RegularDiscont);													 /*Set ADC group regular discont */
	ADC_Set_DISCNUM(ADCx, ADC_Reg_InitStruct->RegularDiscontNumber);									 /*Set ADC group regular discont ranks */	
	ADC_Set_EOCOPT(ADCx,ADC_Reg_InitStruct->EOCOption);																	
}

/**
  * @function  ADC_Inj_StructInit
  * @brief  Set each  ADC_Inj_InitStruct field to default value
  * @param  ADCx :
            @arg ADC Instance
  * @retval 
  */
void ADC_Inj_StructInit(ADC_Inj_InitTypeDef* ADC_Inj_InitStruct)
{
	ADC_Inj_InitStruct->TriggerSource 				= ADC_CR2_JEXTSEL_INSOURCE;                                  
	ADC_Inj_InitStruct->ScanMode 							= ADC_CR1_SCAN_DISABLE;                                                                  
	ADC_Inj_InitStruct->DataAlignment 				= ADC_CR2_ALIGN_RIGHT;                          
  ADC_Inj_InitStruct->TrigAuto 							= ADC_CR1_JAUTO_INDEPENDENT;
	ADC_Inj_InitStruct->AnalogWatchDog 				= ADC_CR1_AWD_DISABLE;
	ADC_Inj_InitStruct->InjectDiscont   			= ADC_CR1_JDISCEN_DISABLE;
}

/**
  * @function  ADC_Inj_Init
  * @brief  read complete interrupt Flag status of the selected ADC
  * @param  ADCx :
            @arg ADC Instance
  * @param  TriggerSource:
  *         @arg ADC_CR2_JEXTSEL_INSOURCE         
  *         @arg ADC_CR2_JEXTSEL_TIM8_TRGO1           
  *         @arg ADC_CR2_JEXTSEL_TIM8_CC4           
  *         @arg ADC_CR2_JEXTSEL_TIM2_TRGO        
  *         @arg ADC_CR2_JEXTSEL_TIM2_CC1       
  *         @arg ADC_CR2_JEXTSEL_TIM3_CC4          
  *         @arg ADC_CR2_JEXTSEL_TIM3_CC3       
  *         @arg ADC_CR2_JEXTSEL_EXTI2       
  *         @arg ADC_CR2_JEXTSEL_JSWSTART      
  *         @arg ADC_CR2_JEXTSEL_TIM8_TRGO2      
  *         @arg ADC_CR2_JEXTSEL_TIM8_CC2         
  *         @arg ADC_CR2_JEXTSEL_TIM8_CC5_CC6   
  *         @arg ADC_CR2_JEXTSEL_TIM8_CC4_CC6  
  *         @arg ADC_CR2_JEXTSEL_TIM8_CC4_CC5
  *         @arg ADC_CR2_JEXTSEL_TIM8_CC6    
  *         @arg ADC_CR2_JEXTSEL_TIM15_TRGO	
  * @param  ScanMode:
  *         @arg ADC_CR1_SCAN_DISABLE
  *         @arg ADC_CR1_SCAN_ENABLE
  * @param  DataAlignment:
  *         @arg ADC_CR2_ALIGN_RIGHT
  *         @arg ADC_CR2_ALIGN_LEFT 
  * @param  TrigAuto:
  *         @arg ADC_CR1_JAUTO_INDEPENDENT
  *         @arg ADC_CR1_JAUTO_FROM_REG
  * @param  AnalogWatchDog:
  *         @arg ADC_CR1_AWD_ENABLE
  *         @arg ADC_CR1_AWD_DISABLE
  * @param  AWDChannelGroup:
  *         @arg ADC_AWD_DISABLE
  *         @arg ADC_AWD_ALL_CHANNELS_REG
  *         @arg ADC_AWD_ALL_CHANNELS_INJ
  *         @arg ADC_AWD_ALL_CHANNELS_REG_INJ
  *         @arg ADC_AWD_CHANNEL_0_REG 
  *         @arg ADC_AWD_CHANNEL_0_INJ 
  *         @arg ADC_AWD_CHANNEL_0_REG_INJ
  *         @arg ADC_AWD_CHANNEL_1_REG 
  *         @arg ADC_AWD_CHANNEL_1_INJ 
  *         @arg ADC_AWD_CHANNEL_1_REG_INJ
  *         @arg ADC_AWD_CHANNEL_2_REG 
  *         @arg ADC_AWD_CHANNEL_2_INJ 
  *         @arg ADC_AWD_CHANNEL_2_REG_INJ
  *         @arg ADC_AWD_CHANNEL_3_REG 
  *         @arg ADC_AWD_CHANNEL_3_INJ 
  *         @arg ADC_AWD_CHANNEL_3_REG_INJ
  *         @arg ADC_AWD_CHANNEL_4_REG 
  *         @arg ADC_AWD_CHANNEL_4_INJ 
  *         @arg ADC_AWD_CHANNEL_4_REG_INJ
  *         @arg ADC_AWD_CHANNEL_5_REG 
  *         @arg ADC_AWD_CHANNEL_5_INJ 
  *         @arg ADC_AWD_CHANNEL_5_REG_INJ
  *         @arg ADC_AWD_CHANNEL_6_REG 
  *         @arg ADC_AWD_CHANNEL_6_INJ 
  *         @arg ADC_AWD_CHANNEL_6_REG_INJ
  *         @arg ADC_AWD_CHANNEL_7_REG       
  *         @arg ADC_AWD_CHANNEL_7_INJ      
  *         @arg ADC_AWD_CHANNEL_7_REG_INJ  
  *         @arg ADC_AWD_CHANNEL_8_REG       
  *         @arg ADC_AWD_CHANNEL_8_INJ      
  *         @arg ADC_AWD_CHANNEL_8_REG_INJ 
  *         @arg ADC_AWD_CHANNEL_9_REG      
  *         @arg ADC_AWD_CHANNEL_9_INJ       
  *         @arg ADC_AWD_CHANNEL_9_REG_INJ  
  *         @arg ADC_AWD_CHANNEL_10_REG      
  *         @arg ADC_AWD_CHANNEL_10_INJ     
  *         @arg ADC_AWD_CHANNEL_10_REG_INJ       
  *         @arg ADC_AWD_CHANNEL_11_REG      
  *         @arg ADC_AWD_CHANNEL_11_INJ     
  *         @arg ADC_AWD_CHANNEL_11_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_12_REG      
  *         @arg ADC_AWD_CHANNEL_12_INJ     
  *         @arg ADC_AWD_CHANNEL_12_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_13_REG      
  *         @arg ADC_AWD_CHANNEL_13_INJ     
  *         @arg ADC_AWD_CHANNEL_13_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_14_REG      
  *         @arg ADC_AWD_CHANNEL_14_INJ     
  *         @arg ADC_AWD_CHANNEL_14_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_15_REG      
  *         @arg ADC_AWD_CHANNEL_15_INJ     
  *         @arg ADC_AWD_CHANNEL_15_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_16_REG      
  *         @arg ADC_AWD_CHANNEL_16_INJ     
  *         @arg ADC_AWD_CHANNEL_16_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_17_REG      
  *         @arg ADC_AWD_CHANNEL_17_INJ     
  *         @arg ADC_AWD_CHANNEL_17_REG_INJ 
  *         @arg ADC_AWD_CHANNEL_18_REG    
  *         @arg ADC_AWD_CHANNEL_18_INJ    
  *         @arg ADC_AWD_CHANNEL_18_REG_INJ
  *         @arg ADC_AWD_CHANNEL_19_REG    
  *         @arg ADC_AWD_CHANNEL_19_INJ    
  *         @arg ADC_AWD_CHANNEL_19_REG_INJ
  *         @arg ADC_AWD_CHANNEL_20_REG    
  *         @arg ADC_AWD_CHANNEL_20_INJ    
  *         @arg ADC_AWD_CHANNEL_20_REG_INJ
  *         @arg ADC_AWD_CHANNEL_21_REG    
  *         @arg ADC_AWD_CHANNEL_21_INJ    
  *         @arg ADC_AWD_CHANNEL_21_REG_INJ
  *         @arg ADC_AWD_CHANNEL_22_REG    
  *         @arg ADC_AWD_CHANNEL_22_INJ    
  *         @arg ADC_AWD_CHANNEL_22_REG_INJ
  *         @arg ADC_AWD_CHANNEL_23_REG    
  *         @arg ADC_AWD_CHANNEL_23_INJ    
  *         @arg ADC_AWD_CHANNEL_23_REG_INJ  
  * @param  InjectDiscont:
  *         @arg ADC_CR1_JDISCEN_ENABLE
  *         @arg ADC_CR1_JDISCEN_DISABLE  
  * @param  EOCOption
  *         @ref ADC_EOC_OPT_DISABLE
  *         @ref ADC_EOC_OPT_ENABLE	  
  * @retval None .
  */
void ADC_Inj_Init(ADC_TypeDef *ADCx,ADC_Inj_InitTypeDef* ADC_Inj_InitStruct)
{
	ADC_Set_JEXTSEL(ADCx, ADC_Inj_InitStruct->TriggerSource);                          /* Set ADC group Inj trigger source */
	ADC_Set_SCAN(ADCx, ADC_Inj_InitStruct->ScanMode);                                  /* Set ADC sacn Inj group*/
	ADC_Set_ALIGN(ADCx, ADC_Inj_InitStruct->DataAlignment);                            /* Set ADC conversion data alignment */
  ADC_Set_JAUTO(ADCx, ADC_Inj_InitStruct->TrigAuto);                                 /* Set ADC JAUTO mode*/
	ADC_Set_AWD(ADCx, ADC_Inj_InitStruct->AnalogWatchDog);														 /*Set ADC analog watchdog*/
	ADC_Set_AWDChannels(ADCx,ADC_Inj_InitStruct->AWDChannelGroup);
	ADC_Set_JDISCEN(ADCx, ADC_Inj_InitStruct->InjectDiscont);													 /*Set ADC group inject discont */
	ADC_Set_EOCOPT(ADCx,ADC_Inj_InitStruct->EOCOption);		
}

/**
  * @function  ADC_REG_RankInit
  * @brief  Initial REG Rank of the selected ADC
  * @param  ADCx:
            @arg ADC Instance
  * @param  Length:
  *         @ref ADC_SQRL_SCAN_DISABLE
  *         @ref ADC_SQRL_SCAN_2RANKS
  *         @ref ADC_SQRL_SCAN_3RANKS
  *         @ref ADC_SQRL_SCAN_4RANKS
  *         @ref ADC_SQRL_SCAN_5RANKS
  *         @ref ADC_SQRL_SCAN_6RANKS
  *         @ref ADC_SQRL_SCAN_7RANKS
  *         @ref ADC_SQRL_SCAN_8RANKS
  * @param  Channel:
  *         @ref ADC_CHANNEL_0     
  *         @ref ADC_CHANNEL_1     
  *         @ref ADC_CHANNEL_2     
  *         @ref ADC_CHANNEL_3     
  *         @ref ADC_CHANNEL_4     
  *         @ref ADC_CHANNEL_5     
  *         @ref ADC_CHANNEL_6     
  *         @ref ADC_CHANNEL_7     
  *         @ref ADC_CHANNEL_8     
  *         @ref ADC_CHANNEL_9     
  *         @ref ADC_CHANNEL_10    
  *         @ref ADC_CHANNEL_11    
  *         @ref ADC_CHANNEL_12    
  *         @ref ADC_CHANNEL_13    
  *         @ref ADC_CHANNEL_14    
  *         @ref ADC_CHANNEL_15    
  *         @ref ADC_CHANNEL_16    
  *         @ref ADC_CHANNEL_17    
  *         @ref ADC_CHANNEL_18    
  *         @ref ADC_CHANNEL_19    
  *         @ref ADC_CHANNEL_20    
  *         @ref ADC_CHANNEL_21    
  *         @ref ADC_CHANNEL_22    
  *         @ref ADC_CHANNEL_23    
  *         @ref ADC_CHANNEL_OPA1  
  *         @ref ADC_CHANNEL_OPA2  
  *         @ref ADC_CHANNEL_OPA3  
  *         @ref ADC_CHANNEL_LDO12 
  *         @ref ADC_CHANNEL_CMPSRN
  *         @ref ADC_CHANNEL_VBGINT
  *         @ref ADC_CHANNEL_VREFP 
  *         @ref ADC_CHANNEL_TPS   
  *         @ref ADC_CHANNEL_LDO17 
  * @param  SamplingTime:
  *         @ref ADC_SAMPLINGTIME_2p5CYCLES       
  *         @ref ADC_SAMPLINGTIME_6p5CYCLES        
  *         @ref ADC_SAMPLINGTIME_11p5CYCLES        
  *         @ref ADC_SAMPLINGTIME_17p5CYCLES      
  *         @ref ADC_SAMPLINGTIME_25p5CYCLES       
  *         @ref ADC_SAMPLINGTIME_35p5CYCLES       
  *         @ref ADC_SAMPLINGTIME_48p5CYCLES       
  *         @ref ADC_SAMPLINGTIME_640p5CYCLES   
  * @retval None
  */
void ADC_REG_RankInit(ADC_TypeDef* ADCx,ADC_REG_RankInitTypeDef* ADC_REG_RankInitStruct)
{
  int i,rank;
  rank  = ADC_REG_RankInitStruct->Length >> 20 ;
	if (ADC_Get_ADON(ADCx) == 0) 
	{
		if(ADC_Get_PRGRDY(ADCx))
		{
			ADC_Set_SQRL(ADCx, ADC_REG_RankInitStruct->Length);                                                           /* Set ADC reg scan Length */
			for(i=0; i<=rank; i++)
			{
				if( i < 6 )
				{
					ADC_Set_SQ(ADCx,(ADC_SQR3_REGOFFSET|(i*5)), ADC_REG_RankInitStruct->Rank[i].Channel);                     /* Set reg sequence rank channel */        
				}
				else
				{		
					ADC_Set_SQ(ADCx,(ADC_SQR2_REGOFFSET|((i-6)*5)), ADC_REG_RankInitStruct->Rank[i].Channel);                 /* Set reg sequence rank channel */ 
				}
				ADC_Set_SMPR(ADCx,ADC_REG_RankInitStruct->Rank[i].Channel, ADC_REG_RankInitStruct->Rank[i].SamplingTime);          /* Set channel sampling time */
			}
			ADC_Set_CFGUPD(ADCx);
			while(ADC_Get_CFGUPD(ADCx) == 1);		
		}
	}
}

/**
  * @function  ADC_INJ_RankInit
  * @brief  Initial INJ Rank of the selected ADC
  * @param  ADCx:
            @arg ADC Instance
  * @param  Length:
  *         @ref ADC_JSQRL_SCAN_DISABLE
  *         @ref ADC_JSQRL_SCAN_2RANKS
  *         @ref ADC_JSQRL_SCAN_3RANKS
  *         @ref ADC_JSQRL_SCAN_4RANKS
  * @param  Channel:
  *         @ref ADC_CHANNEL_0     
  *         @ref ADC_CHANNEL_1     
  *         @ref ADC_CHANNEL_2     
  *         @ref ADC_CHANNEL_3     
  *         @ref ADC_CHANNEL_4     
  *         @ref ADC_CHANNEL_5     
  *         @ref ADC_CHANNEL_6     
  *         @ref ADC_CHANNEL_7     
  *         @ref ADC_CHANNEL_8     
  *         @ref ADC_CHANNEL_9     
  *         @ref ADC_CHANNEL_10    
  *         @ref ADC_CHANNEL_11    
  *         @ref ADC_CHANNEL_12    
  *         @ref ADC_CHANNEL_13    
  *         @ref ADC_CHANNEL_14    
  *         @ref ADC_CHANNEL_15    
  *         @ref ADC_CHANNEL_16    
  *         @ref ADC_CHANNEL_17    
  *         @ref ADC_CHANNEL_18    
  *         @ref ADC_CHANNEL_19    
  *         @ref ADC_CHANNEL_20    
  *         @ref ADC_CHANNEL_21    
  *         @ref ADC_CHANNEL_22    
  *         @ref ADC_CHANNEL_23    
  *         @ref ADC_CHANNEL_OPA1  
  *         @ref ADC_CHANNEL_OPA2  
  *         @ref ADC_CHANNEL_OPA3  
  *         @ref ADC_CHANNEL_LDO12 
  *         @ref ADC_CHANNEL_CMPSRN
  *         @ref ADC_CHANNEL_VBGINT
  *         @ref ADC_CHANNEL_VREFP 
  *         @ref ADC_CHANNEL_TPS   
  *         @ref ADC_CHANNEL_LDO17 
  * @param  SamplingTime:
  *         @ref ADC_SAMPLINGTIME_2p5CYCLES      
  *         @ref ADC_SAMPLINGTIME_6p5CYCLES       
  *         @ref ADC_SAMPLINGTIME_11p5CYCLES       
  *         @ref ADC_SAMPLINGTIME_17p5CYCLES     
  *         @ref ADC_SAMPLINGTIME_25p5CYCLES      
  *         @ref ADC_SAMPLINGTIME_35p5CYCLES      
  *         @ref ADC_SAMPLINGTIME_48p5CYCLES      
  *         @ref ADC_SAMPLINGTIME_640p5CYCLES  
  * @retval None
  */
void ADC_INJ_RankInit(ADC_TypeDef* ADCx,ADC_INJ_RankInitTypeDef* ADC_INJ_RankInitStruct)
{
  int i,rank;
  rank  = ADC_INJ_RankInitStruct->Length >> 20 ;
	if (ADC_Get_ADON(ADCx) == 0) 
	{
		if(ADC_Get_PRGRDY(ADCx))
		{
			ADC_Set_JSQRL(ADCx, ADC_INJ_RankInitStruct->Length);                                                            /* Set ADC inj scan Length */
			for(i=0; i<=rank; i++)
			{
				switch(i)
				{
					case 0:
						ADC_Set_JSQ(ADCx,ADC_INJ_RANK_1, ADC_INJ_RankInitStruct->Rank[i].Channel);                                 /* Set inj sequence rank channel */
						break;
					case 1:
						ADC_Set_JSQ(ADCx,ADC_INJ_RANK_2, ADC_INJ_RankInitStruct->Rank[i].Channel);                                 /* Set inj sequence rank channel */
						break;
					case 2:
						ADC_Set_JSQ(ADCx,ADC_INJ_RANK_3, ADC_INJ_RankInitStruct->Rank[i].Channel);                                 /* Set inj sequence rank channel */
						break;
					case 3:
						ADC_Set_JSQ(ADCx,ADC_INJ_RANK_4, ADC_INJ_RankInitStruct->Rank[i].Channel);                                  /* Set inj sequence rank channel */
						break;
					default:break;
				}                                           
				ADC_Set_SMPR(ADCx,ADC_INJ_RankInitStruct->Rank[i].Channel, ADC_INJ_RankInitStruct->Rank[i].SamplingTime);   /* Set channel sampling time */
			} 	
			ADC_Set_CFGUPD(ADCx);
			while(ADC_Get_CFGUPD(ADCx) == 1);
		}
	}   
}

/**
  * @function  ADC_Trig_CAL
  * @brief  Trig CAL of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval None
  */
void ADC_Trig_CAL(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CR2, ADC_CR2_RSTCAL);
  while (ADC_Get_RSTCAL(ADCx) != 0);
  __asm {
		nop;
		nop;
		nop;
   }
  SET_BIT(ADCx->CR2, ADC_CR2_CAL);
  while (ADC_Get_CAL(ADCx) != 0);
}
