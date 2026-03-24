/**************************************************************************************************
*     File Name :                        MCH.h
*     Library/Module Name :              MCH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制HAL层头文件
**************************************************************************************************/
#ifndef MCH_H
#define MCH_H

#include "HAL_CFG.h"

#define ADC_DATA_READ_U_BEMF        ((Q32U_)HAL_MOTOR_ADC->JDR1)
#define ADC_DATA_READ_V_BEMF        ((Q32U_)HAL_MOTOR_ADC->JDR2)
#define ADC_DATA_READ_W_BEMF        ((Q32U_)HAL_MOTOR_ADC->JDR3)
#define ADC_DATA_READ_CURRENT       ((Q32U_)HAL_MOTOR_ADC->JDR4)

#define ADC_DATA_READ_VBUS          ((Q32U_)HAL_MOTOR_ADC->DATA1)
#define ADC_DATA_READ_TEMP          ((Q32U_)HAL_MOTOR_ADC->DATA2)

/**********************************************************************************************
Function: MH_ADC_Soft_Trigger
Description: 软件触发ADC
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_Soft_Trigger(void)
{
    SET_BIT(HAL_MOTOR_ADC->CR2, ADC_CR2_JSWSTART);
}

/**********************************************************************************************
Function: MH_ADC_TrigTime_Set
Description: 延迟触发ADC,避开米勒平台
Input: 延迟触发采样计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_TrigTime_Set(Q32U_ count)
{
    TIM_Set_OC_CompareCH4(HAL_MOTOR_PWM, count);
}

/**********************************************************************************************
Function: MH_PWM_Freq_Set
Description: 设置载频
Input: PWM载频控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWM_Freq_Set(Q32U_ count)
{
    TIM_Set_AutoReload(HAL_MOTOR_PWM, (count-1));
}

/**********************************************************************************************
Function: MH_PWM_Preload_Enable
Description: 预装载使能
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWM_Preload_Enable(void)
{
    TIM_Enable_OC_Preload(HAL_MOTOR_PWM, UH_PWM_CHANNEL);
    TIM_Enable_OC_Preload(HAL_MOTOR_PWM, VH_PWM_CHANNEL);
    TIM_Enable_OC_Preload(HAL_MOTOR_PWM, WH_PWM_CHANNEL);
    TIM_Enable_OC_Preload(HAL_MOTOR_PWM, ADC_TRIGGER_CHANNEL);
}

/**********************************************************************************************
Function: MH_PWM_Preload_Disable
Description: 预装载关闭
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWM_Preload_Disable(void)
{
    TIM_Disable_OC_Preload(HAL_MOTOR_PWM, UH_PWM_CHANNEL);
    TIM_Disable_OC_Preload(HAL_MOTOR_PWM, VH_PWM_CHANNEL);
    TIM_Disable_OC_Preload(HAL_MOTOR_PWM, WH_PWM_CHANNEL);
    TIM_Disable_OC_Preload(HAL_MOTOR_PWM, ADC_TRIGGER_CHANNEL);
}

/**********************************************************************************************
Function: MH_POSITION_XX
Description: 定位脉冲，开三管
Input: PWM占空比控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_POSITION_Up(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
}
static inline void MH_POSITION_Wn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL);
}
static inline void MH_POSITION_Vp(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL);
}
static inline void MH_POSITION_Un(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}
static inline void MH_POSITION_Wp(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WL_PWM_CHANNEL);
}
static inline void MH_POSITION_Vn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VH_PWM_CHANNEL|WL_PWM_CHANNEL);
}

/**********************************************************************************************
Function: MH_HPWM_LPWM_XXXX
Description: 同步整流控制，UpVn为导通U上和V下，其他以此类推，HOpen为开三相上关三相下，LOpen为关三相上开三相下,CLOSE为六管全关
Input: PWM占空比控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_HPWM_LPWM_UpVn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|VH_PWM_CHANNEL|VL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, WH_PWM_CHANNEL|WL_PWM_CHANNEL);
}
static inline void MH_HPWM_LPWM_UpWn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL);
}
static inline void MH_HPWM_LPWM_VpWn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL);
}
static inline void MH_HPWM_LPWM_VpUn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|VH_PWM_CHANNEL|VL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, WH_PWM_CHANNEL|WL_PWM_CHANNEL);
}
static inline void MH_HPWM_LPWM_WpUn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL);
}
static inline void MH_HPWM_LPWM_WpVn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL);
}
static inline void MH_HPWM_LPWM_HOpen(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}
static inline void MH_HPWM_LPWM_LOpen(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}
static inline void MH_HPWM_LPWM_Close(void)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}

/**********************************************************************************************
Function: MH_PWM_Count_Read
Description: 读取当前PWM计数器值
Input: 无
Output: 无
Input_Output: 无
Return: PWM计数器值
Author: CJYS
***********************************************************************************************/
static inline Q32U_ MH_PWM_Count_Read(void)
{
   return HAL_MOTOR_PWM->CNT;
}

/**********************************************************************************************
Function: MH_HALL_TIM_Count_Read
Description: 读取当前HALL换向计数器值
Input: 无
Output: 无
Input_Output: 无
Return: ALL换向计数器值
Author: CJYS
***********************************************************************************************/
static inline Q32U_ MH_HALL_TIM_Count_Read(void)
{
   return HAL_MOTOR_HALL_TIM->CNT;
}

/**********************************************************************************************
Function: MH_Switch_TIM_Delay
Description: 设置延迟换向计数器值，进入中断
Input: 换向计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_Switch_TIM_Delay(Q32U_ count)
{
    HAL_MOTOR_SWITCH_TIM->CNT = 0U;
    HAL_MOTOR_SWITCH_TIM->CCR1 = (Q32U_)count;
    SET_BIT(HAL_MOTOR_SWITCH_TIM->CR1, TIM_CR1_CEN);
}

/**********************************************************************************************
Function: MH_Switch_TIM_Stop
Description: 停止延迟换向计数器值，屏蔽中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_Switch_TIM_Stop(void)
{
    CLEAR_BIT(HAL_MOTOR_SWITCH_TIM->CR1, TIM_CR1_CEN);
    HAL_MOTOR_SWITCH_TIM->CNT = 0U;
}

#endif /* MCH_H */
