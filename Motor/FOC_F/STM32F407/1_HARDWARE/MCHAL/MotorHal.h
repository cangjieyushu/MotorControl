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
Function: MH_PWM_Output_Enable
Description: PWM输出通道开通
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MH_PWM_Output_Enable(void);

/**********************************************************************************************
Function: MH_PWM_Output_Disable
Description: PWM输出通道关闭
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MH_PWM_Output_Disable(void);

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
Function: MH_Read_Hall_Count
Description: 读取用于HALL电平
Input: 无
Output: 无
Input_Output: 无
Return: HALL电平
Author: CJYS
***********************************************************************************************/
Q32U_ MH_Read_Hall_State(void);

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

#endif /* MotorHal_H */
