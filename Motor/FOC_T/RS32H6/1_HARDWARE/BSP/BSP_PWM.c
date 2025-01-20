/**************************************************************************************************
*     File Name :                        BSP_PWM.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             PWM初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_PWM.h"

/**********************************************************************************************
Function: BSP_PWM_Init
Description: 电机控制用PWM初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_PWM_Init(void)
{
    //如果在启动计数器前写入RCR，则UEV在上溢时发生。
    //SET CNT BASE
    TIM_Set_CounterMode(HAL_MOTOR_PWM, TIM_COUNTERMODE_CENTER_UP);
    TIM_Set_Prescaler(HAL_MOTOR_PWM, (uint32_t)HAL_PWM_PRESCALER);
    TIM_Set_AutoReload(HAL_MOTOR_PWM, (HAL_PWM_SET_COUNT_T-1));
    TIM_Set_RepetitionCounter(HAL_MOTOR_PWM, 1U);

    //CH1 / CH1N
    TIM_Set_OC_Mode(HAL_MOTOR_PWM, UH_PWM_CHANNEL, TIM_OCMODE_PWM2);
    TIM_Set_OC_Polarity(HAL_MOTOR_PWM, UH_PWM_CHANNEL, TIM_OCPOLARITY_HIGH);
    TIM_Set_OC_Polarity(HAL_MOTOR_PWM, UL_PWM_CHANNEL, TIM_OCPOLARITY_HIGH);

    //CH2 / CH2N
    TIM_Set_OC_Mode(HAL_MOTOR_PWM, VH_PWM_CHANNEL, TIM_OCMODE_PWM2);
    TIM_Set_OC_Polarity(HAL_MOTOR_PWM, VH_PWM_CHANNEL, TIM_OCPOLARITY_HIGH);
    TIM_Set_OC_Polarity(HAL_MOTOR_PWM, VL_PWM_CHANNEL, TIM_OCPOLARITY_HIGH);

    //CH3 / CH3N
    TIM_Set_OC_Mode(HAL_MOTOR_PWM, WH_PWM_CHANNEL, TIM_OCMODE_PWM2);
    TIM_Set_OC_Polarity(HAL_MOTOR_PWM, WH_PWM_CHANNEL, TIM_OCPOLARITY_HIGH);
    TIM_Set_OC_Polarity(HAL_MOTOR_PWM, WL_PWM_CHANNEL, TIM_OCPOLARITY_HIGH);
    
    //CH5 / CH6
    TIM_Set_OC_Mode(HAL_MOTOR_PWM, ADC_PWM_CHANNEL_1, TIM_OCMODE_PWM1);
    TIM_Set_OC_Mode(HAL_MOTOR_PWM, ADC_PWM_CHANNEL_2, TIM_OCMODE_PWM1);
    TIM_Set_OC_CompareCH5(HAL_MOTOR_PWM, (Q32U_)(HAL_ADC_TRIGGER_TIME1*HAL_PWM_ALL_COUNT_F));
    TIM_Set_OC_CompareCH6(HAL_MOTOR_PWM, (Q32U_)(HAL_ADC_TRIGGER_TIME2*HAL_PWM_ALL_COUNT_F));
    
    TIM_Enable_OC_Preload(HAL_MOTOR_PWM, UH_PWM_CHANNEL);
    TIM_Enable_OC_Preload(HAL_MOTOR_PWM, VH_PWM_CHANNEL);
    TIM_Enable_OC_Preload(HAL_MOTOR_PWM, WH_PWM_CHANNEL);
    TIM_Enable_OC_Preload(HAL_MOTOR_PWM, ADC_PWM_CHANNEL_1);
    TIM_Enable_OC_Preload(HAL_MOTOR_PWM, ADC_PWM_CHANNEL_2);
    
    TIM_Set_TriggerOutput2(HAL_MOTOR_PWM, TIM_TRGO2_OC5_RISING_OC6_RISING);
    
    /* Set Deadtime */
    TIM_Set_ClockDivision(HAL_MOTOR_PWM, TIM_CLOCKDIVISION_DIV1);
    TIM_Set_OC_DeadTime(HAL_MOTOR_PWM, (0x7FU & HAL_PWM_DEADTIME_VALUE));  //deadtime
    
    /*  BDTR   AF1*/
    /*comp1 out high break*/
    TIM_Config_BRK(HAL_MOTOR_PWM, TIM_BREAK_POLARITY_HIGH, TIM_BREAK_FILTER_FDIV4_N8, TIM_BREAK_AFMODE_INPUT);
    TIM_Disable_BreakInputSource(HAL_MOTOR_PWM,TIM_BREAK_INPUT_BKIN,TIM_AF_BKINE); //BKINE=0
    TIM_Set_BreakInputSourcePolarity(HAL_MOTOR_PWM,TIM_BREAK_INPUT_BKIN,TIM_AF_BKCMP1P,TIM_BKCMP_POLARITY_NoInvert);//BKCMPxP =0
    TIM_Enable_BreakInputSource(HAL_MOTOR_PWM,TIM_BREAK_INPUT_BKIN,TIM_AF_BKCMP1E); //BKCMPxE=1
  
    /*The channel pwm output can be selected to be affected by the brake input*/
    TIM_Enable_Break_Control(HAL_MOTOR_PWM);
    TIM_Set_CH1Break_Invalid(HAL_MOTOR_PWM);
    TIM_Set_CH2Break_Invalid(HAL_MOTOR_PWM);
    TIM_Set_CH3Break_Invalid(HAL_MOTOR_PWM);
    TIM_Disable_AOE(HAL_MOTOR_PWM);//AOE=0 
  
    /**********************************/
	/* Start output signal generation */
	/**********************************/
	/* Enable outputs OC1, OC1N, OC2, OC2N, OC3 and OC3N */
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, ADC_PWM_CHANNEL_1|ADC_PWM_CHANNEL_2);
    
    TIM_Enable_MOE(HAL_MOTOR_PWM);
    TIM_Enable_CEN(HAL_MOTOR_PWM);

    TIM_Enable_IT(HAL_MOTOR_PWM, TIM_DIER_BIE);
    TIM_Enable_IT(HAL_MOTOR_PWM, TIM_DIER_UIE);
}
