/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef MotorHal_H
#define MotorHal_H

#include "MotorHal_cfg.h"   

#define ADC_DATA_READ_CURRENT            (HAL_MOTOR_ADC->JDR1)

__STATIC_INLINE void MH_PWM_Duty_Set(Q32U_ Ta, Q32U_ Tb, Q32U_ Tc)
{
    HAL_MOTOR_PWM->CCR1 = Ta;
    HAL_MOTOR_PWM->CCR2 = Tb;
    HAL_MOTOR_PWM->CCR3 = Tc;
}

__STATIC_INLINE void MH_ADC_Soft_Trigger(void)
{
    SET_BIT(HAL_MOTOR_ADC->CR2, ADC_CR2_JSWSTART);
}

__STATIC_INLINE void MH_PWM_ADC_Set(Q32U_ count1, Q32U_ count2)
{
    HAL_MOTOR_PWM->CCR5 = count1;
    HAL_MOTOR_PWM->CCR6 = count2;
}

void MH_ADC_Data_Read(Q32U_* current, Q32U_* data1, Q32U_* data2, Q32U_* data3);

void MH_PWM_Freq_Set(Q32U_ count);
    
void MH_HPWM_LPWM_Init(Q32U_ count);

void MH_PWM_Output_Enable(void);
void MH_PWM_Output_Disable(void);

void MH_HPWM_LPWM_UpVn(Q32U_ duty);
void MH_HPWM_LPWM_UpWn(Q32U_ duty);
void MH_HPWM_LPWM_VpWn(Q32U_ duty);
void MH_HPWM_LPWM_VpUn(Q32U_ duty);
void MH_HPWM_LPWM_WpUn(Q32U_ duty);
void MH_HPWM_LPWM_WpVn(Q32U_ duty);

void MH_HPWM_LPWM_HOpen(Q32U_ duty);
void MH_HPWM_LPWM_LOpen(Q32U_ duty);
void MH_HPWM_LPWM_Close(void);

Q32U_ MH_PWM_Count(void);
Q32U_ MH_HALL_TIM_Count(void);

uint8_t MH_HALL_GPIO_State(void);

#endif /* MotorHal_H */
