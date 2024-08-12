/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_PWM.h"

void BSP_PWM_Init(void)
{	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;	
    TIM_BDTRInitTypeDef TIM1_BDTRInitStructure;
    
    TIM_Cmd(TIM1,ENABLE);

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;                     // 1分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;     // 互补中心对称
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;                                    // Timer clock = sysclock /(TIM_Prescaler+1) = 168M
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = (uint8_t)HAL_CURRENT_LOOP_RATE;
    TIM_TimeBaseInitStructure.TIM_Period = HAL_PWM_MAX_COUNTER;                     // Period = (TIM counter clock / TIM output clock) - 1 = 20K
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);
        
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                               // pwm模式
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;                      // TIM_OCNPolarity_High 
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCNIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    TIM_OC1Init(TIM1,&TIM_OCInitStructure);
    TIM_OC2Init(TIM1,&TIM_OCInitStructure);
    TIM_OC3Init(TIM1,&TIM_OCInitStructure);
    
    TIM_OCInitStructure.TIM_Pulse = HAL_ADC_SAMPLE_VALUE;
    TIM_OC4Init(TIM1,&TIM_OCInitStructure);
    TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_OC4Ref);
    
    TIM1_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
    TIM1_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
    TIM1_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF; 
    TIM1_BDTRInitStructure.TIM_DeadTime = HAL_PWM_DEADTIME_VALUE;
    TIM1_BDTRInitStructure.TIM_Break = TIM_Break_Enable;                    // 过流立即停车，封锁PWM  TIM_Break_Disable TIM_Break_Enable
    TIM1_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
    TIM1_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;  
    TIM_BDTRConfig(TIM1, &TIM1_BDTRInitStructure);
    
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //清中断标志位
    TIM_ITConfig(TIM1,TIM_IT_Update, ENABLE); //打开中断 
    
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);  //清中断标志位
    TIM_ITConfig(TIM1,TIM_IT_CC4, ENABLE); //打开中断 

    TIM_ClearITPendingBit(TIM1, TIM_IT_Break);  //清中断标志位
    TIM_ITConfig(TIM1,TIM_IT_Break, ENABLE); //打开中断

    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1,ENABLE);	
    
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0; 
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInitStructure.TIM_Period = 0xFFFFFFFF;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
    
    TIM_Cmd(TIM2,ENABLE);
}
