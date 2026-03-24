/**************************************************************************************************
*     File Name :                        BSP_GPIO.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             GPIO初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_GPIO.h"

/**********************************************************************************************
Function: BSP_GPIO_Init
Description: GPIO初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_SetBits(SHUTDOWN1_GPIO_Port, SHUTDOWN1_Pin);
    
    GPIO_InitStruct.GPIO_Pin = Start_Stop_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(Start_Stop_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = SHUTDOWN1_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(SHUTDOWN1_GPIO_Port, &GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin = LED0_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = LED1_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);
    GPIO_ResetBits(LED0_GPIO_PORT, LED0_Pin);
    GPIO_ResetBits(LED1_GPIO_PORT, LED1_Pin);
    
    GPIO_InitStruct.GPIO_Pin = KEY0_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = KEY1_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = KEY2_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin   = ADC_U_CURRENT_Pin;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(ADC_U_CURRENT_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin   = ADC_V_CURRENT_Pin;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(ADC_V_CURRENT_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin   = ADC_W_CURRENT_Pin;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(ADC_W_CURRENT_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin   = ADC_VBAT_Pin;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(ADC_VBAT_GPIO_Port, &GPIO_InitStruct);
    

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = UH_PWM_Pin;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(UH_PWM_GPIO_Port,&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = VH_PWM_Pin;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(VH_PWM_GPIO_Port,&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = WH_PWM_Pin;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(WH_PWM_GPIO_Port,&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = UL_PWM_Pin;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(UL_PWM_GPIO_Port,&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = VL_PWM_Pin;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(VL_PWM_GPIO_Port,&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = WL_PWM_Pin;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(WL_PWM_GPIO_Port,&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStruct.GPIO_Pin = BKIN_PWM_Pin;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(BKIN_PWM_GPIO_Port,&GPIO_InitStruct);
    
    GPIO_PinAFConfig(UH_PWM_GPIO_Port, UH_PWM_Pin_Source, GPIO_AF_TIM1);
    GPIO_PinAFConfig(VH_PWM_GPIO_Port, VH_PWM_Pin_Source, GPIO_AF_TIM1);
    GPIO_PinAFConfig(WH_PWM_GPIO_Port, WH_PWM_Pin_Source, GPIO_AF_TIM1);
    GPIO_PinAFConfig(UL_PWM_GPIO_Port, UL_PWM_Pin_Source, GPIO_AF_TIM1);
    GPIO_PinAFConfig(VL_PWM_GPIO_Port, VL_PWM_Pin_Source, GPIO_AF_TIM1);
    GPIO_PinAFConfig(WL_PWM_GPIO_Port, WL_PWM_Pin_Source, GPIO_AF_TIM1);
    GPIO_PinAFConfig(BKIN_PWM_GPIO_Port, BKIN_PWM_Pin_Source, GPIO_AF_TIM1);
    
    
    GPIO_InitStruct.GPIO_Pin = U_HALL_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(U_HALL_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = V_HALL_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(V_HALL_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = W_HALL_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(W_HALL_GPIO_Port, &GPIO_InitStruct);
}

/**********************************************************************************************
Function: BSP_GPIO_Read_SW0_State
Description: 按键0状态读取
Input: 无
Output: 无
Input_Output: 无
Return: 按键0状态
Author: CJYS
***********************************************************************************************/
Q32U_ BSP_GPIO_Read_SW0_State(void)
{
    return (Q32U_)GPIO_ReadInputDataBit(KEY0_GPIO_PORT, KEY0_Pin);
}

/**********************************************************************************************
Function: BSP_GPIO_Read_SW1_State
Description: 按键1状态读取
Input: 无
Output: 无
Input_Output: 无
Return: 按键1状态
Author: CJYS
***********************************************************************************************/
Q32U_ BSP_GPIO_Read_SW1_State(void)
{
    return (Q32U_)GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_Pin);
}

/**********************************************************************************************
Function: BSP_GPIO_Read_SW1_State
Description: 按键2状态读取
Input: 无
Output: 无
Input_Output: 无
Return: 按键2状态
***********************************************************************************************/
Q32U_ BSP_GPIO_Read_SW2_State(void)
{
    return (Q32U_)GPIO_ReadInputDataBit(KEY2_GPIO_PORT, KEY2_Pin);
}
