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
Function: HM_ADC_Data_Read_Motor
Description: 获取电机采样值
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_ADC_Data_Read_Motor(Q32U_*u_bemf, Q32U_* v_bemf, Q32U_* w_bemf, Q32U_* current)
{
    (*u_bemf) = ((Q32U_)HAL_MOTOR_ADC->JDR1);
    (*v_bemf) = ((Q32U_)HAL_MOTOR_ADC->JDR2);
    (*w_bemf) = ((Q32U_)HAL_MOTOR_ADC->JDR3);
    (*current) = ((Q32U_)HAL_MOTOR_ADC->JDR4);
}

/*
Function: HM_ADC_Data_Read_System
Description: 获取电压温度采样值
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_ADC_Data_Read_System(Q32U_* vbus, Q32U_* temp)
{
    (*vbus) = ((Q32U_)HAL_MOTOR_ADC->DATA1);
    (*temp) = ((Q32U_)HAL_MOTOR_ADC->DATA2);
}

/*
Function: HM_ADC_Soft_Trigger
Description: 软件触发ADC
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_ADC_Soft_Trigger(void)
{
    SET_BIT(HAL_MOTOR_ADC->CR2, ADC_CR2_JSWSTART);
}

/*
Function: HM_ADC_TrigTime_Set
Description: 延迟触发ADC,避开米勒平台
Input: 延迟触发采样计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_ADC_TrigTime_Set(Q32U_ count)
{
    TIM_Set_OC_CompareCH4(HAL_MOTOR_PWM, count);
}

/*
Function: HM_PWM_Freq_Set
Description: 设置载频
Input: PWM载频控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_PWM_Freq_Set(Q32U_ count)
{
    TIM_Set_AutoReload(HAL_MOTOR_PWM, (count-1U));
}

/*
Function: HM_PWM_Preload_Enable
Description: 预装载使能
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_PWM_Preload_Enable(void)
{
    TIM_Enable_OC_Preload(HAL_MOTOR_PWM, UH_PWM_CHANNEL);
    TIM_Enable_OC_Preload(HAL_MOTOR_PWM, VH_PWM_CHANNEL);
    TIM_Enable_OC_Preload(HAL_MOTOR_PWM, WH_PWM_CHANNEL);
    TIM_Enable_OC_Preload(HAL_MOTOR_PWM, ADC_TRIGGER_CHANNEL);
}

/*
Function: HM_PWM_Preload_Disable
Description: 预装载关闭
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_PWM_Preload_Disable(void)
{
    TIM_Disable_OC_Preload(HAL_MOTOR_PWM, UH_PWM_CHANNEL);
    TIM_Disable_OC_Preload(HAL_MOTOR_PWM, VH_PWM_CHANNEL);
    TIM_Disable_OC_Preload(HAL_MOTOR_PWM, WH_PWM_CHANNEL);
    TIM_Disable_OC_Preload(HAL_MOTOR_PWM, ADC_TRIGGER_CHANNEL);
}

/*
Function: HM_POSITION_XX
Description: 定位脉冲，开三管
Input: PWM占空比控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_POSITION_Up(Q32U_ ccr_value)
{
    HAL_MOTOR_PWM->CCR1 = ccr_value;
    HAL_MOTOR_PWM->CCR2 = ccr_value;
    HAL_MOTOR_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
}
static inline void HM_POSITION_Wn(Q32U_ ccr_value)
{
    HAL_MOTOR_PWM->CCR1 = ccr_value;
    HAL_MOTOR_PWM->CCR2 = ccr_value;
    HAL_MOTOR_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL);
}
static inline void HM_POSITION_Vp(Q32U_ ccr_value)
{
    HAL_MOTOR_PWM->CCR1 = ccr_value;
    HAL_MOTOR_PWM->CCR2 = ccr_value;
    HAL_MOTOR_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL);
}
static inline void HM_POSITION_Un(Q32U_ ccr_value)
{
    HAL_MOTOR_PWM->CCR1 = ccr_value;
    HAL_MOTOR_PWM->CCR2 = ccr_value;
    HAL_MOTOR_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}
static inline void HM_POSITION_Wp(Q32U_ ccr_value)
{
    HAL_MOTOR_PWM->CCR1 = ccr_value;
    HAL_MOTOR_PWM->CCR2 = ccr_value;
    HAL_MOTOR_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WL_PWM_CHANNEL);
}
static inline void HM_POSITION_Vn(Q32U_ ccr_value)
{
    HAL_MOTOR_PWM->CCR1 = ccr_value;
    HAL_MOTOR_PWM->CCR2 = ccr_value;
    HAL_MOTOR_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VH_PWM_CHANNEL|WL_PWM_CHANNEL);
}

/*
Function: HM_HPWM_LPWM_XXXX
Description: 同步整流控制，UpVn为导通U上和V下，其他以此类推，HOpen为开三相上关三相下，LOpen为关三相上开三相下,CLOSE为六管全关
Input: PWM占空比控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_HPWM_LPWM_UpVn(Q32U_ ccr_value)
{
    HAL_MOTOR_PWM->CCR1 = ccr_value;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|VH_PWM_CHANNEL|VL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, WH_PWM_CHANNEL|WL_PWM_CHANNEL);
}
static inline void HM_HPWM_LPWM_UpWn(Q32U_ ccr_value)
{
    HAL_MOTOR_PWM->CCR1 = ccr_value;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL);
}
static inline void HM_HPWM_LPWM_VpWn(Q32U_ ccr_value)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = ccr_value;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL);
}
static inline void HM_HPWM_LPWM_VpUn(Q32U_ ccr_value)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = ccr_value;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|VH_PWM_CHANNEL|VL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, WH_PWM_CHANNEL|WL_PWM_CHANNEL);
}
static inline void HM_HPWM_LPWM_WpUn(Q32U_ ccr_value)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL);
}
static inline void HM_HPWM_LPWM_WpVn(Q32U_ ccr_value)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL);
}
static inline void HM_HPWM_LPWM_HOpen(Q32U_ ccr_value)
{
    HAL_MOTOR_PWM->CCR1 = ccr_value;
    HAL_MOTOR_PWM->CCR2 = ccr_value;
    HAL_MOTOR_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}
static inline void HM_HPWM_LPWM_LOpen(Q32U_ ccr_value)
{
    HAL_MOTOR_PWM->CCR1 = ccr_value;
    HAL_MOTOR_PWM->CCR2 = ccr_value;
    HAL_MOTOR_PWM->CCR3 = ccr_value;
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}
static inline void HM_HPWM_LPWM_Close(void)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}

/*
Function: HM_PWM_Count_Read
Description: 读取当前PWM计数器值
Input: 无
Output: 无
Input_Output: 无
Return: PWM计数器值
Author: CJYS
*/
static inline Q32U_ HM_PWM_Count_Read(void)
{
   return (Q32U_)HAL_MOTOR_PWM->CNT;
}

/*
Function: HM_HALL_TIM_Count_Read
Description: 读取当前HALL换向计数器值
Input: 无
Output: 无
Input_Output: 无
Return: ALL换向计数器值
Author: CJYS
*/
static inline Q32U_ HM_HALL_TIM_Count_Read(void)
{
   return (Q32U_)HAL_MOTOR_HALL_TIM->CNT;
}

/*
Function: HM_SWITCH_TIM_Delay
Description: 设置延迟换向计数器值，进入中断
Input: 换向计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_SWITCH_TIM_Delay(Q32U_ ccr_value)
{
    HAL_MOTOR_SWITCH_TIM->CNT = 0U;
    HAL_MOTOR_SWITCH_TIM->CCR1 = (Q32U_)ccr_value;
    SET_BIT(HAL_MOTOR_SWITCH_TIM->CR1, TIM_CR1_CEN);
}

/*
Function: HM_SWITCH_TIM_Stop
Description: 停止延迟换向计数器值，屏蔽中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
static inline void HM_SWITCH_TIM_Stop(void)
{
    CLEAR_BIT(HAL_MOTOR_SWITCH_TIM->CR1, TIM_CR1_CEN);
    HAL_MOTOR_SWITCH_TIM->CNT = 0U;
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
    return (Q32U_)TIM_Get_Flag(HAL_MOTOR_PWM, TIM_SR_BIF);
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
    TIM_Clear_Flag(HAL_MOTOR_PWM, TIM_SR_BIF);
}


#endif /* HAL_MC_H */
