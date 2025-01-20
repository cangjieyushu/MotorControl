/**************************************************************************************************
*     File Name :                        MotorHal.h
*     Library/Module Name :              MotorHal
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制HAL层头文件
**************************************************************************************************/
#ifndef MotorHal_H
#define MotorHal_H

#include "MotorHal_cfg.h"

/**********************************************************************************************
Function: MH_ADC_Data_Read_One
Description: 单电阻读取ADC采样数据
Input: 无
Output: 无
Input_Output: ADC数据指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_Data_Read_One(Q32I_* pADC_I1, Q32I_* pADC_I2)
{
    (*pADC_I1) = (Q32I_)(HAL_MOTOR_ADC->JDR1);
    (*pADC_I2) = (Q32I_)(HAL_MOTOR_ADC->JDR2);
}   

/**********************************************************************************************
Function: MH_PWM_Output_Enable
Description: PWM输出通道开通
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWM_Output_Enable(void) 
{
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, 
                        UH_PWM_CHANNEL|UL_PWM_CHANNEL|
                        VH_PWM_CHANNEL|VL_PWM_CHANNEL|
                        WH_PWM_CHANNEL|WL_PWM_CHANNEL);
}

/**********************************************************************************************
Function: MH_PWM_Output_Disable
Description: PWM输出通道关闭
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWM_Output_Disable(void)
{
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, 
                        UH_PWM_CHANNEL|UL_PWM_CHANNEL|
                        VH_PWM_CHANNEL|VL_PWM_CHANNEL|
                        WH_PWM_CHANNEL|WL_PWM_CHANNEL);
}

/**********************************************************************************************
Function: MH_PWM_Duty_Set_One
Description: PWM输出三相占空比输出，带移相
Input: ABC三相占空比，0~0.5对应开始到对称中心，Ta1是上升计数过程中的切换时间点，Ta2是下降计数过程中的切换时间点，
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWM_Duty_Set_One(Q32U_ Ta, Q32U_ Tb, Q32U_ Tc)
{
    HAL_MOTOR_PWM->CCR1 = Ta;
    HAL_MOTOR_PWM->CCR2 = Tb;
    HAL_MOTOR_PWM->CCR3 = Tc;
}

/**********************************************************************************************
Function: MH_ADC_TrigTime_Set
Description: 移相情况下，ADC的采样时刻设置
Input: 0~0.5对应开始到对称中心，ch1是第一次采样时刻，Ta2是第二次采样时刻，
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_TrigTime_Set(Q32U_ Ch1, Q32U_ Ch2)
{
    HAL_MOTOR_PWM->CCR5 = Ch1;
    HAL_MOTOR_PWM->CCR6 = Ch2;
}

#endif /* MotorHal_H */
