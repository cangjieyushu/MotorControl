/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef MotorHal_H
#define MotorHal_H

#include "MotorHal_cfg.h"                     

#define ADC_DATA_READ_U_BEMF        ((Q32U_)0)
#define ADC_DATA_READ_V_BEMF        ((Q32U_)0)
#define ADC_DATA_READ_W_BEMF        ((Q32U_)0)
#define ADC_DATA_READ_CURRENT       ((Q32U_)0)

void MH_ADC_Soft_Trigger(void);

void MH_ADC_Trigger_Delay_Time(Q32U_ count);
void MH_PWM_Freq_Set(Q32U_ count);

void MH_HPWM_LGPIO_Init(Q32U_ count);
void MH_HPWM_LPWM_Init(Q32U_ count);

void MH_HPWM_LGPIO_UpVn(Q32U_ duty);
void MH_HPWM_LGPIO_UpWn(Q32U_ duty);
void MH_HPWM_LGPIO_VpWn(Q32U_ duty);
void MH_HPWM_LGPIO_VpUn(Q32U_ duty);
void MH_HPWM_LGPIO_WpUn(Q32U_ duty);
void MH_HPWM_LGPIO_WpVn(Q32U_ duty);

void MH_HPWM_LGPIO_HOpen(Q32U_ duty);
void MH_HPWM_LGPIO_LOpen(Q32U_ duty);
void MH_HPWM_LGPIO_Close(void);

void MH_HPWM_LPWM_UpVn(Q32U_ duty);
void MH_HPWM_LPWM_UpWn(Q32U_ duty);
void MH_HPWM_LPWM_VpWn(Q32U_ duty);
void MH_HPWM_LPWM_VpUn(Q32U_ duty);
void MH_HPWM_LPWM_WpUn(Q32U_ duty);
void MH_HPWM_LPWM_WpVn(Q32U_ duty);

void MH_HPWM_LPWM_HOpen(Q32U_ duty);
void MH_HPWM_LPWM_LOpen(Q32U_ duty);
void MH_HPWM_LPWM_Close(void);

Q32U_ MH_PWM_Read_Count(void);
Q32U_ MH_HALL_TIM_Read_Count(void);
void MH_Switch_TIM_Delay(Q32U_ count);
void MH_Switch_TIM_Stop(void);

uint8_t MH_HALL_GPIO_State(void);

#endif /* MotorHal_H */
