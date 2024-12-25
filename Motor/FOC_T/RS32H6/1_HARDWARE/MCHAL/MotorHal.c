/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "MotorHal.h"

void MH_ADC_Data_Read(Q32U_* current, Q32U_* data1, Q32U_* data2, Q32U_* data3)
{
    *current = HAL_MOTOR_ADC->JDR1;
    *data1 = HAL_MOTOR_ADC->JDR2;
    *data2 = HAL_MOTOR_ADC->JDR3;
    *data3 = HAL_MOTOR_ADC->JDR4;
}

void MH_PWM_Freq_Set(Q32U_ count)
{
    TIM_Set_AutoReload(HAL_MOTOR_PWM, (count-1));
}

void MH_HPWM_LPWM_Init(uint32_t count)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    /*TIM8:*/ 
    GPIO_InitStruct.Mode    = GPIO_MODER_MODER_AF;
    GPIO_InitStruct.Pull    = GPIO_PUPDR_Floating;
    GPIO_InitStruct.Speed   = GPIO_OSPEEDR_High;

    GPIO_InitStruct.Alternate = UH_PWM_AF;
    GPIO_InitStruct.Pin = UH_PWM_PIN;			
    GPIO_Init(UH_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = VH_PWM_AF;
    GPIO_InitStruct.Pin = VH_PWM_PIN;			
    GPIO_Init(VH_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = WH_PWM_AF;
    GPIO_InitStruct.Pin = WH_PWM_PIN;			
    GPIO_Init(WH_PWM_GPIO_PORT,&GPIO_InitStruct);
    
    GPIO_InitStruct.Alternate = UL_PWM_AF;
    GPIO_InitStruct.Pin = UL_PWM_PIN;			
    GPIO_Init(UL_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = VL_PWM_AF;
    GPIO_InitStruct.Pin = VL_PWM_PIN;			
    GPIO_Init(VL_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = WL_PWM_AF;
    GPIO_InitStruct.Pin = WL_PWM_PIN;			
    GPIO_Init(WL_PWM_GPIO_PORT,&GPIO_InitStruct);
                        
    TIM_Set_AutoReload(HAL_MOTOR_PWM, (count-1));
    TIM_Set_OC_DeadTime(HAL_MOTOR_PWM, HAL_PWM_DEADTIME_VALUE);  //deadtime
}

void MH_PWM_Output_Enable(void)  // Æô¶¯º¯Êý
{
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, 
                        UH_PWM_CHANNEL|UL_PWM_CHANNEL|
                        VH_PWM_CHANNEL|VL_PWM_CHANNEL|
                        WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Enable_MOE(HAL_MOTOR_PWM);
}
 
void MH_PWM_Output_Disable(void)  // Í£Ö¹º¯Êý
{
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, 
                        UH_PWM_CHANNEL|UL_PWM_CHANNEL|
                        VH_PWM_CHANNEL|VL_PWM_CHANNEL|
                        WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_MOE(HAL_MOTOR_PWM);
}

void MH_HPWM_LPWM_UpVn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|VH_PWM_CHANNEL|VL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, WH_PWM_CHANNEL|WL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_UpWn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_VpWn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_VpUn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|VH_PWM_CHANNEL|VL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, WH_PWM_CHANNEL|WL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_WpUn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_WpVn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_HOpen(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_LOpen(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}

void MH_HPWM_LPWM_Close(void)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}

Q32U_ MH_PWM_Count(void)
{
   return HAL_MOTOR_PWM->CNT;
}

Q32U_ MH_HALL_TIM_Count(void)
{
   return HAL_MOTOR_HALL_TIM->CNT;
}

uint8_t MH_HALL_GPIO_State(void)
{
    return 0;
}
