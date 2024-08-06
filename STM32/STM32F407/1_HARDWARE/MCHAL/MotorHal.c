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

void MH_PWM_Duty_Set(uint16_t uduty, uint16_t vduty, uint16_t wduty)
{
   TIM1->CCR1 = uduty;
   TIM1->CCR2 = vduty;
   TIM1->CCR3 = wduty;
}

void MH_PWM_Duty_Enable(void)  // 启动函数
{
   /*PWM寄存器占空比清零*/
   TIM1->CCR1 = 0;
   TIM1->CCR2 = 0;
   TIM1->CCR3 = 0;
   //使能PWM输出通道OC1/OC1N/OC2/OC2N/OC3/OC3N
   TIM1->CCER|=0x5555;	
}
 
void MH_PWM_Duty_Disable(void)  // 停止函数
{
   /*PWM寄存器占空比清零*/
   TIM1->CCR1 = 0;
   TIM1->CCR2 = 0;
   TIM1->CCR3 = 0;
   //不使能PWM输出通道OC1/OC1N/OC2/OC2N/OC3/OC3N
   TIM1->CCER&=0xAAAA;	
}
