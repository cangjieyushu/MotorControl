/**************************************************************************************************
*     File Name :                        MotorHal.c
*     Library/Module Name :              MotorHal
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制HAL层源文件
**************************************************************************************************/
#include "MotorHal.h"

ST_MH_ADC_DATA  Adc_Data;

Q32U_ Q32U_ADC_Data_Lsb[20] = {0};

/**********************************************************************************************
Function: MH_Read_ADC_Data
Description: 读取ADC采样数据
Input: 无
Output: 无
Input_Output: ADC数据指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MH_Read_ADC_Data(ST_MH_ADC_DATA *pADC_DATA)
{
    Q32U_ADC_Data_Lsb[0] = ADC1->JDR1;
    Q32U_ADC_Data_Lsb[1] = ADC1->JDR2;
    Q32U_ADC_Data_Lsb[2] = ADC1->JDR3;
    
    pADC_DATA->Ia = (float)Q32U_ADC_Data_Lsb[0];
    pADC_DATA->Ib = (float)Q32U_ADC_Data_Lsb[1];
    pADC_DATA->Ic = (float)Q32U_ADC_Data_Lsb[2];
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
Ram_Func void MH_PWM_Output_Enable(void) 
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
Ram_Func void MH_PWM_Output_Disable(void)
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
Ram_Func void MH_PWM_Duty_Set_Three(float Ta, float Tb, float Tc)
{
	TIM1->CCR1 = (Q32U_)(Ta*HAL_PWM_ALL_COUNT_F);
    TIM1->CCR2 = (Q32U_)(Tb*HAL_PWM_ALL_COUNT_F);
    TIM1->CCR3 = (Q32U_)(Tc*HAL_PWM_ALL_COUNT_F);
}

/**********************************************************************************************
Function: MH_Read_Hall_Count
Description: 读取用于HALL电平
Input: 无
Output: 无
Input_Output: 无
Return: HALL电平
Author: CJYS
***********************************************************************************************/
Q32U_ MH_Read_Hall_State(void)
{
    return ((GPIOH->IDR&(GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10))>>10);
}

/**********************************************************************************************
Function: MH_Read_Hall_Count
Description: 读取用于HALL换向计数器的当前值
Input: 无
Output: 无
Input_Output: 无
Return: 计数器值
Author: CJYS
***********************************************************************************************/
Q32U_ MH_Read_Hall_Count(void)
{
   return TIM2->CNT;
}

