/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "MotorHal.h"

void MH_ADC_Soft_Trigger(void)
{
//    SET_BIT(HAL_MOTOR_ADC->CR2, ADC_CR2_JSWSTART);
}

void MH_ADC_Trigger_Delay_Time(Q32U_ count)
{
//    TIM_Set_OC_CompareCH4(HAL_MOTOR_PWM, time);
}

void MH_PWM_Freq_Set(Q32U_ count)
{
//    TIM_Set_AutoReload(HAL_MOTOR_PWM, (count-1));
}

void MH_HPWM_LGPIO_Init(Q32U_ count)
{
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//    
//    /*TIM8:*/ 
//    GPIO_InitStruct.Mode    = GPIO_MODER_MODER_AF;
//    GPIO_InitStruct.Pull    = GPIO_PUPDR_Floating;
//    GPIO_InitStruct.Speed   = GPIO_OSPEEDR_High;
//
//    GPIO_InitStruct.Alternate = UH_PWM_AF;
//    GPIO_InitStruct.Pin = UH_PWM_PIN;			
//    GPIO_Init(UH_PWM_GPIO_PORT,&GPIO_InitStruct);
//    GPIO_InitStruct.Alternate = VH_PWM_AF;
//    GPIO_InitStruct.Pin = VH_PWM_PIN;			
//    GPIO_Init(VH_PWM_GPIO_PORT,&GPIO_InitStruct);
//    GPIO_InitStruct.Alternate = WH_PWM_AF;
//    GPIO_InitStruct.Pin = WH_PWM_PIN;			
//    GPIO_Init(WH_PWM_GPIO_PORT,&GPIO_InitStruct);
//
//    GPIO_InitStruct.Mode    = GPIO_MODER_MODER_Output;
//    GPIO_InitStruct.Pull    = GPIO_PUPDR_Floating;
//    GPIO_InitStruct.Speed   = GPIO_OSPEEDR_High;
//    GPIO_InitStruct.Alternate = GPIO_AF0;
//    GPIO_InitStruct.Pin = UL_PWM_PIN;			
//    GPIO_Init(UL_PWM_GPIO_PORT,&GPIO_InitStruct);
//    GPIO_InitStruct.Alternate = GPIO_AF0;
//    GPIO_InitStruct.Pin = VL_PWM_PIN;			
//    GPIO_Init(VL_PWM_GPIO_PORT,&GPIO_InitStruct);
//    GPIO_InitStruct.Alternate = GPIO_AF0;
//    GPIO_InitStruct.Pin = WL_PWM_PIN;			
//    GPIO_Init(WL_PWM_GPIO_PORT,&GPIO_InitStruct);
//    
//    TIM_Set_AutoReload(HAL_MOTOR_PWM, (count-1));
//    TIM_Set_OC_DeadTime(HAL_MOTOR_PWM, 0);  //deadtime
}

void MH_HPWM_LPWM_Init(Q32U_ count)
{
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//    
//    /*TIM8:*/ 
//    GPIO_InitStruct.Mode    = GPIO_MODER_MODER_AF;
//    GPIO_InitStruct.Pull    = GPIO_PUPDR_Floating;
//    GPIO_InitStruct.Speed   = GPIO_OSPEEDR_High;
//
//    GPIO_InitStruct.Alternate = UH_PWM_AF;
//    GPIO_InitStruct.Pin = UH_PWM_PIN;			
//    GPIO_Init(UH_PWM_GPIO_PORT,&GPIO_InitStruct);
//    GPIO_InitStruct.Alternate = VH_PWM_AF;
//    GPIO_InitStruct.Pin = VH_PWM_PIN;			
//    GPIO_Init(VH_PWM_GPIO_PORT,&GPIO_InitStruct);
//    GPIO_InitStruct.Alternate = WH_PWM_AF;
//    GPIO_InitStruct.Pin = WH_PWM_PIN;			
//    GPIO_Init(WH_PWM_GPIO_PORT,&GPIO_InitStruct);
//    
//    GPIO_InitStruct.Alternate = UL_PWM_AF;
//    GPIO_InitStruct.Pin = UL_PWM_PIN;			
//    GPIO_Init(UL_PWM_GPIO_PORT,&GPIO_InitStruct);
//    GPIO_InitStruct.Alternate = VL_PWM_AF;
//    GPIO_InitStruct.Pin = VL_PWM_PIN;			
//    GPIO_Init(VL_PWM_GPIO_PORT,&GPIO_InitStruct);
//    GPIO_InitStruct.Alternate = WL_PWM_AF;
//    GPIO_InitStruct.Pin = WL_PWM_PIN;			
//    GPIO_Init(WL_PWM_GPIO_PORT,&GPIO_InitStruct);
//                        
//    TIM_Set_AutoReload(HAL_MOTOR_PWM, (count-1));
//    TIM_Set_OC_DeadTime(HAL_MOTOR_PWM, HAL_PWM_DEADTIME_VALUE);  //deadtime
}

void MH_HPWM_LGPIO_UpVn(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = duty;
//    HAL_MOTOR_PWM->CCR2 = 0U;
//    HAL_MOTOR_PWM->CCR3 = 0U;
//    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL);
//    GPIO_Reset_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
//    GPIO_Set_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
//    GPIO_Reset_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}

void MH_HPWM_LGPIO_UpWn(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = duty;
//    HAL_MOTOR_PWM->CCR2 = 0U;
//    HAL_MOTOR_PWM->CCR3 = 0U;
//    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL);
//    GPIO_Reset_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
//    GPIO_Reset_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
//    GPIO_Set_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}

void MH_HPWM_LGPIO_VpWn(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = 0U;
//    HAL_MOTOR_PWM->CCR2 = duty;
//    HAL_MOTOR_PWM->CCR3 = 0U;
//    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL);
//    GPIO_Reset_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
//    GPIO_Reset_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
//    GPIO_Set_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}

void MH_HPWM_LGPIO_VpUn(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = 0U;
//    HAL_MOTOR_PWM->CCR2 = duty;
//    HAL_MOTOR_PWM->CCR3 = 0U;
//    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL);
//    GPIO_Set_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
//    GPIO_Reset_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
//    GPIO_Reset_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}

void MH_HPWM_LGPIO_WpUn(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = 0U;
//    HAL_MOTOR_PWM->CCR2 = 0U;
//    HAL_MOTOR_PWM->CCR3 = duty;
//    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, WH_PWM_CHANNEL);
//    GPIO_Set_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
//    GPIO_Reset_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
//    GPIO_Reset_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}

void MH_HPWM_LGPIO_WpVn(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = 0U;
//    HAL_MOTOR_PWM->CCR2 = 0U;
//    HAL_MOTOR_PWM->CCR3 = duty;
//    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, WH_PWM_CHANNEL);
//    GPIO_Reset_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
//    GPIO_Set_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
//    GPIO_Reset_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}

void MH_HPWM_LGPIO_HOpen(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = duty;
//    HAL_MOTOR_PWM->CCR2 = duty;
//    HAL_MOTOR_PWM->CCR3 = duty;
//    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
//    GPIO_Reset_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
//    GPIO_Reset_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
//    GPIO_Reset_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}

void MH_HPWM_LGPIO_LOpen(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = 0U;
//    HAL_MOTOR_PWM->CCR2 = 0U;
//    HAL_MOTOR_PWM->CCR3 = 0U;
//    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
//    GPIO_Set_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
//    GPIO_Set_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
//    GPIO_Set_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}

void MH_HPWM_LGPIO_Close(void)
{
//    HAL_MOTOR_PWM->CCR1 = 0U;
//    HAL_MOTOR_PWM->CCR2 = 0U;
//    HAL_MOTOR_PWM->CCR3 = 0U;
//    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
//    GPIO_Reset_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
//    GPIO_Reset_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
//    GPIO_Reset_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}

void MH_HPWM_LPWM_UpVn(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = duty;
//    HAL_MOTOR_PWM->CCR2 = 0U;
//    HAL_MOTOR_PWM->CCR3 = 0U;
//    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|VH_PWM_CHANNEL|VL_PWM_CHANNEL);
//    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, WH_PWM_CHANNEL|WL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_UpWn(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = duty;
//    HAL_MOTOR_PWM->CCR2 = 0U;
//    HAL_MOTOR_PWM->CCR3 = 0U;
//    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
//    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_VpWn(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = 0U;
//    HAL_MOTOR_PWM->CCR2 = duty;
//    HAL_MOTOR_PWM->CCR3 = 0U;
//    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
//    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_VpUn(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = 0U;
//    HAL_MOTOR_PWM->CCR2 = duty;
//    HAL_MOTOR_PWM->CCR3 = 0U;
//    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|VH_PWM_CHANNEL|VL_PWM_CHANNEL);
//    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, WH_PWM_CHANNEL|WL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_WpUn(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = 0U;
//    HAL_MOTOR_PWM->CCR2 = 0U;
//    HAL_MOTOR_PWM->CCR3 = duty;
//    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
//    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_WpVn(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = 0U;
//    HAL_MOTOR_PWM->CCR2 = 0U;
//    HAL_MOTOR_PWM->CCR3 = duty;
//    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
//    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_HOpen(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = duty;
//    HAL_MOTOR_PWM->CCR2 = duty;
//    HAL_MOTOR_PWM->CCR3 = duty;
//    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
//    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_LOpen(Q32U_ duty)
{
//    HAL_MOTOR_PWM->CCR1 = duty;
//    HAL_MOTOR_PWM->CCR2 = duty;
//    HAL_MOTOR_PWM->CCR3 = duty;
//    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
//    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_Close(void)
{
//    HAL_MOTOR_PWM->CCR1 = 0U;
//    HAL_MOTOR_PWM->CCR2 = 0U;
//    HAL_MOTOR_PWM->CCR3 = 0U;
//    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
//    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}

Q32U_ MH_PWM_Read_Count(void)
{
//   return HAL_MOTOR_PWM->CNT;
   return 0;
}

Q32U_ MH_HALL_TIM_Read_Count(void)
{
//   return HAL_MOTOR_HALL_TIM->CNT;
   return 0;
}

void MH_Switch_TIM_Delay(Q32U_ count)
{
//    HAL_MOTOR_SWITCH_TIM->CNT = 0U;
//    HAL_MOTOR_SWITCH_TIM->ARR = (Q32U_)count;
//    SET_BIT(HAL_MOTOR_SWITCH_TIM->CR1, TIM_CR1_CEN);
}

void MH_Switch_TIM_Stop(void)
{
//    CLEAR_BIT(HAL_MOTOR_SWITCH_TIM->CR1, TIM_CR1_CEN);
//    HAL_MOTOR_SWITCH_TIM->CNT = 0U;
}

uint8_t MH_HALL_GPIO_State(void)
{
    return 0;
}
