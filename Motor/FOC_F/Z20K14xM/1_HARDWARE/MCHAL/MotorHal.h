/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef MotorHal_H
#define MotorHal_H

#include "BSP.h"
#include "MotorHal_cfg.h"

typedef struct
{
    float   Ia;
    float   Ib;
    float   Ic;
    
    float   Ishunt_1;
    float   Ishunt_2;
    
    float   Vdc;
}ST_MH_ADC_DATA;

Ram_Func void MH_Read_ADC_Data(ST_MH_ADC_DATA *pADC_DATA);

Ram_Func void MH_PWM_Output_En(bool IsEnabled);

Ram_Func void MH_PWM_Duty_Set_Three(float Ta, float Tb, float Tc);
Ram_Func void MH_PWM_Duty_Set_One(float Ta1, float Ta2, float Tb1, float Tb2, float Tc1, float Tc2);
Ram_Func void MH_ADC_TrigTime_Set(float Ch1, float Ch2);

Ram_Func void MH_DMA0_ClearChannel0Int(void);

Q32U_ MH_Read_Hall_Count(void);

extern ST_MH_ADC_DATA   Adc_Data;
extern Q32U_ Q32U_ADC_Data_Lsb[20];

#endif /* HAL_H */
