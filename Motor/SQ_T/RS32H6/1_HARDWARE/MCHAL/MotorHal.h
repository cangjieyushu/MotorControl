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

#define ADC_DATA_READ_U_BEMF        ((Q32U_)HAL_MOTOR_ADC->JDR1)
#define ADC_DATA_READ_V_BEMF        ((Q32U_)HAL_MOTOR_ADC->JDR2)
#define ADC_DATA_READ_W_BEMF        ((Q32U_)HAL_MOTOR_ADC->JDR3)
#define ADC_DATA_READ_CURRENT       ((Q32U_)HAL_MOTOR_ADC->JDR4)

/**********************************************************************************************
Function: MH_ADC_Soft_Trigger
Description: 软件触发ADC
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void MH_ADC_Soft_Trigger(void);

/**********************************************************************************************
Function: MH_ADC_Trigger_Delay_Time
Description: 延迟触发ADC,避开米勒平台
Input: 延迟触发采样计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void MH_ADC_Trigger_Delay_Time(Q32U_ count);

/**********************************************************************************************
Function: MH_PWM_Freq_Set
Description: 设置载频
Input: PWM载频控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void MH_PWM_Freq_Set(Q32U_ count);

/**********************************************************************************************
Function: MH_HPWM_LGPIO_Init
Description: 非同步整流初始化
Input: PWM载频控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void MH_HPWM_LGPIO_Init(Q32U_ count);

/**********************************************************************************************
Function: MH_HPWM_LPWM_Init
Description: 同步整流初始化
Input: PWM载频控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void MH_HPWM_LPWM_Init(Q32U_ count);

/**********************************************************************************************
Function: MH_HPWM_LGPIO_XXXX
Description: 非同步整流控制，UpVn为导通U上和V下，其他以此类推，HOpen为开三相上关三相下，LOpen为关三相上开三相下,CLOSE为六管全关
Input: PWM占空比控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void MH_HPWM_LGPIO_UpVn(Q32U_ duty);
void MH_HPWM_LGPIO_UpWn(Q32U_ duty);
void MH_HPWM_LGPIO_VpWn(Q32U_ duty);
void MH_HPWM_LGPIO_VpUn(Q32U_ duty);
void MH_HPWM_LGPIO_WpUn(Q32U_ duty);
void MH_HPWM_LGPIO_WpVn(Q32U_ duty);
void MH_HPWM_LGPIO_HOpen(Q32U_ duty);
void MH_HPWM_LGPIO_LOpen(Q32U_ duty);
void MH_HPWM_LGPIO_Close(void);

/**********************************************************************************************
Function: MH_HPWM_LPWM_XXXX
Description: 同步整流控制，UpVn为导通U上和V下，其他以此类推，HOpen为开三相上关三相下，LOpen为关三相上开三相下,CLOSE为六管全关
Input: PWM占空比控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void MH_HPWM_LPWM_UpVn(Q32U_ duty);
void MH_HPWM_LPWM_UpWn(Q32U_ duty);
void MH_HPWM_LPWM_VpWn(Q32U_ duty);
void MH_HPWM_LPWM_VpUn(Q32U_ duty);
void MH_HPWM_LPWM_WpUn(Q32U_ duty);
void MH_HPWM_LPWM_WpVn(Q32U_ duty);
void MH_HPWM_LPWM_HOpen(Q32U_ duty);
void MH_HPWM_LPWM_LOpen(Q32U_ duty);
void MH_HPWM_LPWM_Close(void);

/**********************************************************************************************
Function: MH_PWM_Read_Count
Description: 读取当前PWM计数器值
Input: 无
Output: 无
Input_Output: 无
Return: PWM计数器值
Author: CJYS
***********************************************************************************************/
Q32U_ MH_PWM_Read_Count(void);

/**********************************************************************************************
Function: MH_HALL_TIM_Read_Count
Description: 读取当前HALL换向计数器值
Input: 无
Output: 无
Input_Output: 无
Return: ALL换向计数器值
Author: CJYS
***********************************************************************************************/
Q32U_ MH_HALL_TIM_Read_Count(void);

/**********************************************************************************************
Function: MH_Switch_TIM_Delay
Description: 设置延迟换向计数器值，进入中断
Input: 换向计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void MH_Switch_TIM_Delay(Q32U_ count);

/**********************************************************************************************
Function: MH_Switch_TIM_Stop
Description: 停止延迟换向计数器值，屏蔽中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void MH_Switch_TIM_Stop(void);

#endif /* MotorHal_H */
