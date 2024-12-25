/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_ADC.h"

void BSP_ADC_Init(void)
{
	ADC_Reg_InitTypeDef  ADC_Reg_InitStruct = {0};
	ADC_REG_RankInitTypeDef ADC_REG_RankInitStruct = {0};
    
	ADC_Reg_InitStruct.TriggerSource 	    = ADC_CR2_EXTSEL_SWSTART;                       
	ADC_Reg_InitStruct.Continuous 		    = ADC_CR2_CONT_CONTINUOUS;                              
	ADC_Reg_InitStruct.ScanMode 		    = ADC_CR1_SCAN_ENABLE;                                                                
	ADC_Reg_InitStruct.DataAlignment	    = ADC_CR2_ALIGN_RIGHT;
	ADC_Reg_InitStruct.AnalogWatchDog 	    = ADC_CR1_AWD_DISABLE;
	ADC_Reg_InitStruct.AWDChannelGroup 	    = ADC_AWD_DISABLE;
	ADC_Reg_InitStruct.RegularDiscont	    = ADC_CR1_DISCEN_DISABLE;
	ADC_Reg_InitStruct.RegularDiscontNumber = ADC_CR1_DISCONT_DISABLE;
	ADC_Reg_InitStruct.EOCOption		    = ADC_EOC_OPT_DISABLE;
	ADC_Reg_Init(HAL_MOTOR_ADC,&ADC_Reg_InitStruct);
    
	ADC_REG_RankInitStruct.Length = ADC_SQRL_SCAN_4RANKS;//规则通道个数
	ADC_REG_RankInitStruct.Rank[0].Channel = ADC_VBUS_Channel;
	ADC_REG_RankInitStruct.Rank[0].SamplingTime = ADC_SAMPLINGTIME_48p5CYCLES;
	ADC_REG_RankInitStruct.Rank[1].Channel = ADC_TEMP_Channel;
	ADC_REG_RankInitStruct.Rank[1].SamplingTime = ADC_SAMPLINGTIME_48p5CYCLES;
	ADC_REG_RankInitStruct.Rank[2].Channel = ADC_VR_Channel;
	ADC_REG_RankInitStruct.Rank[2].SamplingTime = ADC_SAMPLINGTIME_48p5CYCLES;
	ADC_REG_RankInitStruct.Rank[3].Channel = ADC_VBG_Channel;
	ADC_REG_RankInitStruct.Rank[3].SamplingTime = ADC_SAMPLINGTIME_48p5CYCLES;
	ADC_REG_RankInit(HAL_MOTOR_ADC,&ADC_REG_RankInitStruct);
    
	ADC_Inj_InitTypeDef  ADC_Inj_InitStruct = {0};
	ADC_INJ_RankInitTypeDef  ADC_INJ_RankInitStruct = {0};
    
	ADC_Inj_InitStruct.TriggerSource  	        = ADC_CR2_JEXTSEL_TIM8_TRGO2;//注入通道触发源
	ADC_Inj_InitStruct.ScanMode    				= ADC_CR1_SCAN_ENABLE;
	ADC_Inj_InitStruct.DataAlignment 			= ADC_CR2_ALIGN_RIGHT;
	ADC_Inj_InitStruct.TrigAuto  				= ADC_CR1_JAUTO_INDEPENDENT;
	ADC_Inj_InitStruct.AnalogWatchDog 			= ADC_CR1_AWD_DISABLE;
	ADC_Inj_InitStruct.AWDChannelGroup			= ADC_AWD_DISABLE;
	ADC_Inj_InitStruct.InjectDiscont			= ADC_CR1_JDISCEN_DISABLE;
	ADC_Inj_InitStruct.EOCOption				= ADC_EOC_OPT_DISABLE;
	ADC_Inj_Init(HAL_MOTOR_ADC, &ADC_Inj_InitStruct);
	
	ADC_INJ_RankInitStruct.Length 				= ADC_JSQRL_SCAN_DISABLE;//注入通道个数
	ADC_INJ_RankInitStruct.Rank[0].Channel  	= ADC_PHASE_Channel;
	ADC_INJ_RankInitStruct.Rank[0].SamplingTime = ADC_SAMPLINGTIME_17p5CYCLES;
	ADC_INJ_RankInit(HAL_MOTOR_ADC, &ADC_INJ_RankInitStruct);
    
    /* Enable ADC */
    ADC_Enable_ADON(HAL_MOTOR_ADC);
    
    /* Enable ADC IT */
    ADC_Enable_IT(HAL_MOTOR_ADC, ADC_CR1_JEOCIE);
	
	/* Clear flag ADC group regular end of unitary conversion */
	ADC_Clear_SR(HAL_MOTOR_ADC,ADC_SR_JEOC);
    
	/* Run ADC self calibration */
	ADC_Trig_CAL(HAL_MOTOR_ADC);
	while (ADC_Get_CAL(HAL_MOTOR_ADC) != 0);
    
	/* Start ADC group regular conversion */
	ADC_Start_SW(HAL_MOTOR_ADC); 

	/*wait flag ADC group regular end of unitary conversion */
	while (ADC_Get_SR(HAL_MOTOR_ADC, ADC_SR_EOC) == 0);
	
	/* Clear flag ADC group regular end of unitary conversion */
	ADC_Clear_SR(HAL_MOTOR_ADC, ADC_SR_EOC);
}
