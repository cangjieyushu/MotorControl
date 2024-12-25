/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "MotorHal.h"

ST_MH_ADC_DATA  Adc_Data;

Q32U_ Q32U_ADC_Data_Lsb[20] = {0};

Ram_Func void MH_Read_ADC_Data(ST_MH_ADC_DATA* pAdc_Data)
{
    Q32U_ADC_Data_Lsb[0] = ADC1->JDR1;
    Q32U_ADC_Data_Lsb[1] = ADC1->JDR2;
    Q32U_ADC_Data_Lsb[2] = ADC1->JDR3;
    
    pAdc_Data->Ia = (float)Q32U_ADC_Data_Lsb[0];
    pAdc_Data->Ib = (float)Q32U_ADC_Data_Lsb[1];
    pAdc_Data->Ic = (float)Q32U_ADC_Data_Lsb[2];
}


Ram_Func void MH_PWM_Output_Enable(void)
{
    TIM1->CCER |= 0x5555;
    TIM1->BDTR |= TIM_BDTR_MOE;
}
 
Ram_Func void MH_PWM_Output_Disable(void)
{
    TIM1->CCR1 = 0;
    TIM1->CCR2 = 0;
    TIM1->CCR3 = 0;
    TIM1->CCER &= 0xAAAA;
    TIM1->BDTR &= (Q16U_)~TIM_BDTR_MOE;
}

Ram_Func void MH_PWM_Duty_Set_Three(float Ta, float Tb, float Tc)
{
	TIM1->CCR1 = (Q32U_)(Ta*HAL_PWM_ALL_COUNT_F);
    TIM1->CCR2 = (Q32U_)(Tb*HAL_PWM_ALL_COUNT_F);
    TIM1->CCR3 = (Q32U_)(Tc*HAL_PWM_ALL_COUNT_F);
}

Q32U_ MH_Read_Hall_Count(void)
{
    return ((GPIOH->IDR&(GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10))>>10);
}

Q32U_ MH_HALL_TIM_Count(void)
{
   return TIM2->CNT;
}
