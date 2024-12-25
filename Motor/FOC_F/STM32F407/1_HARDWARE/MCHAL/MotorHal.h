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

Ram_Func void MH_PWM_Output_Enable(void);
Ram_Func void MH_PWM_Output_Disable(void);
Ram_Func void MH_PWM_Duty_Set_Three(float Ta, float Tb, float Tc);

Q32U_ MH_Read_Hall_Count(void);

extern ST_MH_ADC_DATA   Adc_Data;
extern Q32U_ Q32U_ADC_Data_Lsb[20];

#endif /* MotorHal_H */
