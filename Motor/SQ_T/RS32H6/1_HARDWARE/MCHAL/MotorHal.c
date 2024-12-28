/**************************************************************************************************
*     File Name :                        MotorHal.c
*     Library/Module Name :              MotorHal
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制HAL层源文件
**************************************************************************************************/
#include "MotorHal.h"

/**********************************************************************************************
Function: MH_ADC_Soft_Trigger
Description: 软件触发ADC
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void MH_ADC_Soft_Trigger(void)
{
    SET_BIT(HAL_MOTOR_ADC->CR2, ADC_CR2_JSWSTART);
}

/**********************************************************************************************
Function: MH_ADC_Trigger_Delay_Time
Description: 延迟触发ADC,避开米勒平台
Input: 延迟触发采样计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void MH_ADC_Trigger_Delay_Time(Q32U_ count)
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
void MH_PWM_Freq_Set(Q32U_ count)
{
    TIM_Set_AutoReload(HAL_MOTOR_PWM, (count-1));
}

/**********************************************************************************************
Function: MH_HPWM_LGPIO_Init
Description: 非同步整流初始化
Input: PWM载频控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void MH_HPWM_LGPIO_Init(Q32U_ count)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    /*TIM8:*/ 
    GPIO_InitStruct.Mode    = GPIO_MODER_MODER_AF;
    GPIO_InitStruct.Pull    = GPIO_PUPDR_Floating;
    GPIO_InitStruct.Speed   = GPIO_OSPEEDR_High;

    GPIO_InitStruct.Alternate = UH_PWM_AF;
    GPIO_InitStruct.Pin = UH_PWM_PIN;			
    GPIO_Init(UH_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = VH_PWM_AF;
    GPIO_InitStruct.Pin = VH_PWM_PIN;			
    GPIO_Init(VH_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = WH_PWM_AF;
    GPIO_InitStruct.Pin = WH_PWM_PIN;			
    GPIO_Init(WH_PWM_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.Mode    = GPIO_MODER_MODER_Output;
    GPIO_InitStruct.Pull    = GPIO_PUPDR_Floating;
    GPIO_InitStruct.Speed   = GPIO_OSPEEDR_High;
    GPIO_InitStruct.Alternate = GPIO_AF0;
    GPIO_InitStruct.Pin = UL_PWM_PIN;			
    GPIO_Init(UL_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = GPIO_AF0;
    GPIO_InitStruct.Pin = VL_PWM_PIN;			
    GPIO_Init(VL_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = GPIO_AF0;
    GPIO_InitStruct.Pin = WL_PWM_PIN;			
    GPIO_Init(WL_PWM_GPIO_PORT,&GPIO_InitStruct);
    
    TIM_Set_AutoReload(HAL_MOTOR_PWM, (count-1));
    TIM_Set_OC_DeadTime(HAL_MOTOR_PWM, 0);  //deadtime
}

/**********************************************************************************************
Function: MH_HPWM_LPWM_Init
Description: 同步整流初始化
Input: PWM载频控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void MH_HPWM_LPWM_Init(Q32U_ count)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    /*TIM8:*/ 
    GPIO_InitStruct.Mode    = GPIO_MODER_MODER_AF;
    GPIO_InitStruct.Pull    = GPIO_PUPDR_Floating;
    GPIO_InitStruct.Speed   = GPIO_OSPEEDR_High;

    GPIO_InitStruct.Alternate = UH_PWM_AF;
    GPIO_InitStruct.Pin = UH_PWM_PIN;			
    GPIO_Init(UH_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = VH_PWM_AF;
    GPIO_InitStruct.Pin = VH_PWM_PIN;			
    GPIO_Init(VH_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = WH_PWM_AF;
    GPIO_InitStruct.Pin = WH_PWM_PIN;			
    GPIO_Init(WH_PWM_GPIO_PORT,&GPIO_InitStruct);
    
    GPIO_InitStruct.Alternate = UL_PWM_AF;
    GPIO_InitStruct.Pin = UL_PWM_PIN;			
    GPIO_Init(UL_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = VL_PWM_AF;
    GPIO_InitStruct.Pin = VL_PWM_PIN;			
    GPIO_Init(VL_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = WL_PWM_AF;
    GPIO_InitStruct.Pin = WL_PWM_PIN;			
    GPIO_Init(WL_PWM_GPIO_PORT,&GPIO_InitStruct);
                        
    TIM_Set_AutoReload(HAL_MOTOR_PWM, (count-1));
    TIM_Set_OC_DeadTime(HAL_MOTOR_PWM, HAL_PWM_DEADTIME_VALUE);  //deadtime
}

/**********************************************************************************************
Function: MH_HPWM_LGPIO_XXXX
Description: 非同步整流控制，UpVn为导通U上和V下，其他以此类推，HOpen为开三相上关三相下，LOpen为关三相上开三相下,CLOSE为六管全关
Input: PWM占空比控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void MH_HPWM_LGPIO_UpVn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL);
    GPIO_Reset_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
    GPIO_Set_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
    GPIO_Reset_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}
void MH_HPWM_LGPIO_UpWn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL);
    GPIO_Reset_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
    GPIO_Reset_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
    GPIO_Set_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}
void MH_HPWM_LGPIO_VpWn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL);
    GPIO_Reset_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
    GPIO_Reset_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
    GPIO_Set_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}
void MH_HPWM_LGPIO_VpUn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL);
    GPIO_Set_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
    GPIO_Reset_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
    GPIO_Reset_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}
void MH_HPWM_LGPIO_WpUn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, WH_PWM_CHANNEL);
    GPIO_Set_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
    GPIO_Reset_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
    GPIO_Reset_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}
void MH_HPWM_LGPIO_WpVn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, WH_PWM_CHANNEL);
    GPIO_Reset_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
    GPIO_Set_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
    GPIO_Reset_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}
void MH_HPWM_LGPIO_HOpen(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    GPIO_Reset_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
    GPIO_Reset_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
    GPIO_Reset_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}
void MH_HPWM_LGPIO_LOpen(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    GPIO_Set_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
    GPIO_Set_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
    GPIO_Set_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
}
void MH_HPWM_LGPIO_Close(void)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    GPIO_Reset_OutputPin(UL_PWM_GPIO_PORT, UL_PWM_PIN);
    GPIO_Reset_OutputPin(VL_PWM_GPIO_PORT, VL_PWM_PIN);
    GPIO_Reset_OutputPin(WL_PWM_GPIO_PORT, WL_PWM_PIN);
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
void MH_HPWM_LPWM_UpVn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|VH_PWM_CHANNEL|VL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, WH_PWM_CHANNEL|WL_PWM_CHANNEL);
}
void MH_HPWM_LPWM_UpWn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL);
}
void MH_HPWM_LPWM_VpWn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL);
}
void MH_HPWM_LPWM_VpUn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|VH_PWM_CHANNEL|VL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, WH_PWM_CHANNEL|WL_PWM_CHANNEL);
}
void MH_HPWM_LPWM_WpUn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL);
}
void MH_HPWM_LPWM_WpVn(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, VH_PWM_CHANNEL|VL_PWM_CHANNEL|WH_PWM_CHANNEL|WL_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|UL_PWM_CHANNEL);
}
void MH_HPWM_LPWM_HOpen(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}
void MH_HPWM_LPWM_LOpen(Q32U_ duty)
{
    HAL_MOTOR_PWM->CCR1 = duty;
    HAL_MOTOR_PWM->CCR2 = duty;
    HAL_MOTOR_PWM->CCR3 = duty;
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Enable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}
void MH_HPWM_LPWM_Close(void)
{
    HAL_MOTOR_PWM->CCR1 = 0U;
    HAL_MOTOR_PWM->CCR2 = 0U;
    HAL_MOTOR_PWM->CCR3 = 0U;
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UH_PWM_CHANNEL|VH_PWM_CHANNEL|WH_PWM_CHANNEL);
    TIM_Disable_CC_Channel(HAL_MOTOR_PWM, UL_PWM_CHANNEL|VL_PWM_CHANNEL|WL_PWM_CHANNEL);
}

/**********************************************************************************************
Function: MH_PWM_Read_Count
Description: 读取当前PWM计数器值
Input: 无
Output: 无
Input_Output: 无
Return: PWM计数器值
Author: CJYS
***********************************************************************************************/
Q32U_ MH_PWM_Read_Count(void)
{
   return HAL_MOTOR_PWM->CNT;
}

/**********************************************************************************************
Function: MH_HALL_TIM_Read_Count
Description: 读取当前HALL换向计数器值
Input: 无
Output: 无
Input_Output: 无
Return: ALL换向计数器值
Author: CJYS
***********************************************************************************************/
Q32U_ MH_HALL_TIM_Read_Count(void)
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
void MH_Switch_TIM_Delay(Q32U_ count)
{
    HAL_MOTOR_SWITCH_TIM->CNT = 0U;
    HAL_MOTOR_SWITCH_TIM->ARR = (Q32U_)count;
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
void MH_Switch_TIM_Stop(void)
{
    CLEAR_BIT(HAL_MOTOR_SWITCH_TIM->CR1, TIM_CR1_CEN);
    HAL_MOTOR_SWITCH_TIM->CNT = 0U;
}

