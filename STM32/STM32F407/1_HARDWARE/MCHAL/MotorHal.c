/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "MotorHal.h"

void MH_ADC_Data_Read(uint16_t* udata, uint16_t* vdata, uint16_t* wdata, uint16_t* oth)
{
    *udata = ADC1->JDR1;
    *vdata = ADC1->JDR2;
    *wdata = ADC1->JDR3;
    *oth = ADC1->JDR4;
}

void MH_PWM_Duty_Set(float uduty, float vduty, float wduty)
{
    uint16_t utmp = 0;
    uint16_t vtmp = 0;
    uint16_t wtmp = 0;
    utmp = (uint16_t)(HAL_PWM_MAX_COUNTER_2*uduty);
    vtmp = (uint16_t)(HAL_PWM_MAX_COUNTER_2*vduty);
    wtmp = (uint16_t)(HAL_PWM_MAX_COUNTER_2*wduty);
    TIM1->CCR1 = utmp;
    TIM1->CCR2 = vtmp;
    TIM1->CCR3 = wtmp;
}

void MH_PWM_Duty_Enable(void)  // Æô¶¯º¯Êý
{
    TIM1->CCER|=0x5555;	
    TIM1->BDTR |= TIM_BDTR_MOE;
}
 
void MH_PWM_Duty_Disable(void)  // Í£Ö¹º¯Êý
{
    TIM1->CCR1 = 0;
    TIM1->CCR2 = 0;
    TIM1->CCR3 = 0;
    TIM1->CCER&=0xAAAA;	
    TIM1->BDTR &= (uint16_t)~TIM_BDTR_MOE;
}

uint32_t MH_HALL_TIM_Count(void)
{
   return TIM2->CNT;
}

uint8_t MH_HALL_GPIO_State(void)
{
    return ((GPIOH->IDR&(GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10))>>10);
}
