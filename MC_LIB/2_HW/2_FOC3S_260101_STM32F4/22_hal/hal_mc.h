/*
*     File Name :                        hal_mc
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制HAL
*/


#ifndef HAL_MC_H
#define HAL_MC_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_clk.h"
#include "hw_map.h"
#include "hw_para.h"
#include "bsp_adc.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: HM_ADC_Data_Read_Vbus
Description: 获取电压采样值
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_ADC_Data_Read_Vbus(Q32U_* vbus)
{
    (*vbus) = (Q32U_)HAL_MOTOR_ADC->JDR4;
}

/*
Function: HM_ADC_Data_Read_Temp
Description: 获取温度采样值
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_ADC_Data_Read_Temp(Q32U_* temp)
{
    (*temp) = BSP_ADC_SYSTEM_BUFFER[0];
}

/*
Function: HM_ADC_Data_Read_Three
Description: 三电阻读取ADC采样数据
Input: 无
Output: 无
Input_Output: ADC数据指针
Return: 无
Author: CJYS
*/
static inline void HM_ADC_Data_Read_Three(Q32U_* pADC_Ia, Q32U_* pADC_Ib ,Q32U_* pADC_Ic)
{
    (*pADC_Ia) = (Q32U_)HAL_MOTOR_ADC->JDR1;
    (*pADC_Ib) = (Q32U_)HAL_MOTOR_ADC->JDR2;
    (*pADC_Ic) = (Q32U_)HAL_MOTOR_ADC->JDR3;
}

/*
Function: HM_ADC_Data_Read_One
Description: 单电阻读取ADC采样数据
Input: 无
Output: 无
Input_Output: ADC数据指针
Return: 无
Author: CJYS
*/
static inline void HM_ADC_Data_Read_One(Q32U_* pADC_I1, Q32U_* pADC_I2)
{
    
}

/*
Function: HM_PWM_Output_Enable
Description: PWM输出通道开通
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_PWM_Output_Enable(void) 
{
    HAL_MOTOR_PWM->CCER |= 0x5555;
    HAL_MOTOR_PWM->BDTR |= TIM_BDTR_MOE;
}

/*
Function: HM_PWM_Output_Disable
Description: PWM输出通道关闭
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_PWM_Output_Disable(void)
{
    HAL_MOTOR_PWM->CCR1 = 0;
    HAL_MOTOR_PWM->CCR2 = 0;
    HAL_MOTOR_PWM->CCR3 = 0;
    HAL_MOTOR_PWM->CCER &= 0xAAAA;
    HAL_MOTOR_PWM->BDTR &= (Q16U_)~TIM_BDTR_MOE;
}

/*
Function: HM_PWM_Duty_Set_Three
Description: PWM输出三相占空比输出
Input: ABC三相切换时间点，0~0.5对应开始到对称中心
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_PWM_Duty_Set_Three(Q32U_ PWM_Count, Q32U_ Ta, Q32U_ Tb, Q32U_ Tc)
{
    HAL_MOTOR_PWM->ARR = PWM_Count - 1U;
    HAL_MOTOR_PWM->CCR1 = Ta;
    HAL_MOTOR_PWM->CCR2 = Tb;
    HAL_MOTOR_PWM->CCR3 = Tc;
}

/*
Function: HM_PWM_Duty_Set_One
Description: PWM输出三相占空比输出，带移相
Input: ABC三相占空比，0~0.5对应开始到对称中心，Ta1是上升计数过程中的切换时间点，Ta2是下降计数过程中的切换时间点，
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_PWM_Duty_Set_One(Q32U_ Ta1, Q32U_ Ta2, Q32U_ Tb1, Q32U_ Tb2, Q32U_ Tc1, Q32U_ Tc2)
{
    
}

/*
Function: HM_ADC_TrigTime_Set
Description: 移相情况下，ADC的采样时刻设置
Input: 0~0.5对应开始到对称中心，ch1是第一次采样时刻，Ch2是第二次采样时刻，
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_ADC_TrigTime_Set(Q32U_ Ch1, Q32U_ Ch2)
{

}

/*
Function: HM_Read_PWM_Brake_Flag
Description: 读取刹车标志位
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline Q32U_ HM_Read_PWM_Brake_Flag(void)
{
    return (TIM_GetFlagStatus(HAL_MOTOR_PWM, TIM_FLAG_Break) != RESET) ? 1U : 0U;
}

/*
Function: HM_Clear_PWM_Brake_Flag
Description: 清除刹车标志位
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_Clear_PWM_Brake_Flag(void)
{
    TIM_ClearFlag(HAL_MOTOR_PWM, TIM_FLAG_Break);
}


#endif /* HAL_MC_H */
