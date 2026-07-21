/**************************************************************************************************
*     File Name :                        MCH.h
*     Library/Module Name :              MCH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制HAL层头文件
**************************************************************************************************/
#ifndef MCH_H
#define MCH_H


#include "BSP.h"
#include "HAL_CFG.h"


#define ADC_DATA_READ_U_BEMF        ((Q32U_)ADC_IDATA0)
#define ADC_DATA_READ_V_BEMF        ((Q32U_)ADC_IDATA1)
#define ADC_DATA_READ_W_BEMF        ((Q32U_)ADC_IDATA2)
#define ADC_DATA_READ_CURRENT       ((Q32U_)ADC_IDATA3)


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
    ADC_CTL1 |= ADC_CTL1_SWICST;
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
    TIMER_CH3CV(HAL_MOTOR_PWM) = count;
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
    TIMER_CAR(HAL_MOTOR_PWM) = (count-1);
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
    TIMER_CHCTL0(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL0_CH0COMSEN|TIMER_CHCTL0_CH1COMSEN);
    TIMER_CHCTL1(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL1_CH2COMSEN|TIMER_CHCTL1_CH3COMSEN);
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
    TIMER_CHCTL0(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL0_CH0COMSEN|TIMER_CHCTL0_CH1COMSEN));
    TIMER_CHCTL1(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL1_CH2COMSEN|TIMER_CHCTL1_CH3COMSEN));
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
    TIMER_CH0CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH1CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH2CV(HAL_MOTOR_PWM) = duty;
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2EN));
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2NEN);
}
static inline void MH_POSITION_Wn(Q32U_ duty)
{
    TIMER_CH0CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH1CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH2CV(HAL_MOTOR_PWM) = duty;
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2EN));
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2NEN);
}
static inline void MH_POSITION_Vp(Q32U_ duty)
{
    TIMER_CH0CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH1CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH2CV(HAL_MOTOR_PWM) = duty;
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2EN));
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2NEN);
}
static inline void MH_POSITION_Un(Q32U_ duty)
{
    TIMER_CH0CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH1CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH2CV(HAL_MOTOR_PWM) = duty;
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2EN);
}
static inline void MH_POSITION_Wp(Q32U_ duty)
{
    TIMER_CH0CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH1CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH2CV(HAL_MOTOR_PWM) = duty;
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2EN);
}
static inline void MH_POSITION_Vn(Q32U_ duty)
{
    TIMER_CH0CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH1CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH2CV(HAL_MOTOR_PWM) = duty;
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2EN);
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
    TIMER_CH0CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH1CV(HAL_MOTOR_PWM) = 0U;
    TIMER_CH2CV(HAL_MOTOR_PWM) = 0U;
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH2EN|TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH1NEN);
}
static inline void MH_HPWM_LPWM_UpWn(Q32U_ duty)
{
    TIMER_CH0CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH1CV(HAL_MOTOR_PWM) = 0U;
    TIMER_CH2CV(HAL_MOTOR_PWM) = 0U;
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH1NEN));
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH2EN|TIMER_CHCTL2_CH2NEN);
}
static inline void MH_HPWM_LPWM_VpWn(Q32U_ duty)
{
    TIMER_CH0CV(HAL_MOTOR_PWM) = 0U;
    TIMER_CH1CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH2CV(HAL_MOTOR_PWM) = 0U;
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH0NEN));
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2EN|TIMER_CHCTL2_CH2NEN);
}
static inline void MH_HPWM_LPWM_VpUn(Q32U_ duty)
{
    TIMER_CH0CV(HAL_MOTOR_PWM) = 0U;
    TIMER_CH1CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH2CV(HAL_MOTOR_PWM) = 0U;
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH2EN|TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH1NEN);
}
static inline void MH_HPWM_LPWM_WpUn(Q32U_ duty)
{
    TIMER_CH0CV(HAL_MOTOR_PWM) = 0U;
    TIMER_CH1CV(HAL_MOTOR_PWM) = 0U;
    TIMER_CH2CV(HAL_MOTOR_PWM) = duty;
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH1NEN));
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH2EN|TIMER_CHCTL2_CH2NEN);
}
static inline void MH_HPWM_LPWM_WpVn(Q32U_ duty)
{
    TIMER_CH0CV(HAL_MOTOR_PWM) = 0U;
    TIMER_CH1CV(HAL_MOTOR_PWM) = 0U;
    TIMER_CH2CV(HAL_MOTOR_PWM) = duty;
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH0NEN));
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2EN|TIMER_CHCTL2_CH2NEN);
}
static inline void MH_HPWM_LPWM_HOpen(Q32U_ duty)
{
    TIMER_CH0CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH1CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH2CV(HAL_MOTOR_PWM) = duty;
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2EN);
}
static inline void MH_HPWM_LPWM_LOpen(Q32U_ duty)
{
    TIMER_CH0CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH1CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH2CV(HAL_MOTOR_PWM) = duty;
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2EN));
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2NEN);
}
static inline void MH_HPWM_LPWM_Open(Q32U_ duty)
{
    TIMER_CH0CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH1CV(HAL_MOTOR_PWM) = duty;
    TIMER_CH2CV(HAL_MOTOR_PWM) = duty;
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2EN);
    TIMER_CHCTL2(HAL_MOTOR_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2NEN);
}
static inline void MH_HPWM_LPWM_Close(void)
{
    TIMER_CH0CV(HAL_MOTOR_PWM) = 0U;
    TIMER_CH1CV(HAL_MOTOR_PWM) = 0U;
    TIMER_CH2CV(HAL_MOTOR_PWM) = 0U;
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2EN
                                            |TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2NEN));
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
   return TIMER_CNT(HAL_MOTOR_PWM);
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
   return TIMER_CNT(HAL_MOTOR_HALL_TIM);
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
    TIMER_CNT(HAL_MOTOR_SWITCH_TIM) = 0U;
    TIMER_CH0CV(HAL_MOTOR_SWITCH_TIM) = (Q32U_)count;
    TIMER_CTL0(HAL_MOTOR_SWITCH_TIM) |= (Q32U_)TIMER_CTL0_CEN;
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
    TIMER_CTL0(HAL_MOTOR_SWITCH_TIM) &= ~(Q32U_)TIMER_CTL0_CEN;
    TIMER_CNT(HAL_MOTOR_SWITCH_TIM) = 0U;
}

#endif /* MCH_H */
