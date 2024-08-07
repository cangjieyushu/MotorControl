/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef MotorHal_H
#define MotorHal_H

#include <stdint.h>
#include "BSP_DMA.h"
#include "BSP_PWM.h"
#include "MotorFoc.h"

void MH_ADC_Data_Read(uint16_t* udata, uint16_t* vdata, uint16_t* wdata, uint16_t* oth);

void MH_PWM_Duty_Set(float uduty, float vduty, float wduty);
void MH_PWM_Duty_Enable(void);
void MH_PWM_Duty_Disable(void);

#endif /* MotorHal_H */
