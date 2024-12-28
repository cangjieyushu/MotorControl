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

/**********************************************************************************************
Function: MH_Read_ADC_Data
Description: 读取ADC采样数据
Input: 无
Output: 无
Input_Output: ADC数据指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MH_Read_ADC_Data(ST_MH_ADC_DATA *pADC_DATA);

/**********************************************************************************************
Function: MH_PWM_Output_En
Description: PWM输出通道开通或关闭
Input: 使能或关闭，true or false
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MH_PWM_Output_En(bool IsEnabled);

/**********************************************************************************************
Function: MH_PWM_Duty_Set_Three
Description: PWM输出三相占空比输出
Input: ABC三相切换时间点，0~0.5对应开始到对称中心
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MH_PWM_Duty_Set_Three(float Ta, float Tb, float Tc);

/**********************************************************************************************
Function: MH_PWM_Duty_Set_One
Description: PWM输出三相占空比输出，带移相
Input: ABC三相占空比，0~0.5对应开始到对称中心，Ta1是上升计数过程中的切换时间点，Ta2是下降计数过程中的切换时间点，
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MH_PWM_Duty_Set_One(float Ta1, float Ta2, float Tb1, float Tb2, float Tc1, float Tc2);

/**********************************************************************************************
Function: MH_ADC_TrigTime_Set
Description: 移相情况下，ADC的采样时刻设置
Input: 0~0.5对应开始到对称中心，ch1是第一次采样时刻，Ta2是第二次采样时刻，
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MH_ADC_TrigTime_Set(float Ch1, float Ch2);

/**********************************************************************************************
Function: MH_DMA0_ClearChannel0Int
Description: DMA的0号通道中断标志位清除
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MH_DMA0_ClearChannel0Int(void);

/**********************************************************************************************
Function: MH_Read_Hall_Count
Description: 读取用于HALL换向计数器的当前值
Input: 无
Output: 无
Input_Output: 无
Return: 计数器值
Author: CJYS
***********************************************************************************************/
Q32U_ MH_Read_Hall_Count(void);

extern ST_MH_ADC_DATA   Adc_Data;
extern Q32U_ Q32U_ADC_Data_Lsb[20];

#endif /* HAL_H */
