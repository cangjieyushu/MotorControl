/**************************************************************************************************
*     File Name :                        MotorHal.h
*     Library/Module Name :              MotorHal
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制HAL层头文件
**************************************************************************************************/
#ifndef MotorHal_H
#define MotorHal_H

#include "BSP.h"
#include "HAL_CFG.h"

/**********************************************************************************************
Function: MH_ADC_Data_Read_Three
Description: 三电阻读取ADC采样数据
Input: 无
Output: 无
Input_Output: ADC数据指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_Data_Read_Three(Q32U_* pADC_Ia, Q32U_* pADC_Ib ,Q32U_* pADC_Ic)
{
    (*pADC_Ia) = (Q32U_)ADC1->JDR1;
    (*pADC_Ib) = (Q32U_)ADC1->JDR2;
    (*pADC_Ic) = (Q32U_)ADC1->JDR3;
}

/**********************************************************************************************
Function: MH_ADC_Data_Read_One
Description: 单电阻读取ADC采样数据
Input: 无
Output: 无
Input_Output: ADC数据指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_Data_Read_One(Q32U_* pADC_I1, Q32U_* pADC_I2)
{
    
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
    TIM1->CCER |= 0x5555;
    TIM1->BDTR |= TIM_BDTR_MOE;
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
    TIM1->CCR1 = 0;
    TIM1->CCR2 = 0;
    TIM1->CCR3 = 0;
    TIM1->CCER &= 0xAAAA;
    TIM1->BDTR &= (Q16U_)~TIM_BDTR_MOE;
}

/**********************************************************************************************
Function: MH_PWM_Duty_Set_Three
Description: PWM输出三相占空比输出
Input: ABC三相切换时间点，0~0.5对应开始到对称中心
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWM_Duty_Set_Three(Q32U_ PWM_Count, Q32U_ Ta, Q32U_ Tb, Q32U_ Tc)
{
    TIM1->ARR = PWM_Count;
	TIM1->CCR1 = Ta;
    TIM1->CCR2 = Tb;
    TIM1->CCR3 = Tc;
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
static inline void MH_PWM_Duty_Set_One(Q32U_ Ta1, Q32U_ Ta2, Q32U_ Tb1, Q32U_ Tb2, Q32U_ Tc1, Q32U_ Tc2)
{
    
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

}

/**********************************************************************************************
Function: MH_Hall_State_Read
Description: 读取用于HALL电平
Input: 无
Output: 无
Input_Output: 无
Return: HALL电平
Author: CJYS
***********************************************************************************************/
static inline Q32U_ MH_Hall_State_Read(void)
{
    return ((GPIOH->IDR&(GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10))>>10);
}

/**********************************************************************************************
Function: MH_Hall_TIM_Count_Read
Description: 读取用于HALL换向计数器的当前值
Input: 无
Output: 无
Input_Output: 无
Return: 计数器值
Author: CJYS
***********************************************************************************************/
static inline Q32U_ MH_Hall_TIM_Count_Read(void)
{
   return TIM2->CNT;
}

#endif /* MotorHal_H */
