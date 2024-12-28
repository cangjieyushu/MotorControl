/**************************************************************************************************
*     File Name :                        MotorTask.h
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机子任务头文件
**************************************************************************************************/
#ifndef MotorTask_H
#define MotorTask_H

#include "Math.h"
#include "MotorHal.h"
#include "MotorSQ.h"
#include "MotorPara.h"

typedef void(*pFUN_HPWMLGPIO_OUT)(Q32U_);
typedef void(*pFUN_HPWMLPWM_OUT)(Q32U_);

/**********************************************************************************************
Function: Motor_Start
Description: 电机启动
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void Motor_Start(void)
{
    Motor.Motor_State_Flag.bit.motor_run_flag = 1U;
}

/**********************************************************************************************
Function: Motor_Stop
Description: 电机停机
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void Motor_Stop(void)
{
    Motor.Motor_State_Flag.bit.motor_run_flag = 0U;
}


/**********************************************************************************************
Function: Motor_Set_Dir
Description: 设置电机运行方向
Input: 0（正转），1（反转）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void Motor_Set_Dir(Q32U_ Dir)
{
    if(Dir == 0)
    {
        Motor.MS_CTRL.DIR_Target = CW;
    }
    else
    {
        Motor.MS_CTRL.DIR_Target = CCW;
    }
}


/**********************************************************************************************
Function: Motor_Read_Dir
Description: 获取电机运行方向
Input: 无
Output: 0（正转），1（反转）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline Q32U_ Motor_Read_Dir(void)
{
    if(Motor.MS_CTRL.DIR_Set == CW)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**********************************************************************************************
Function: Motor_Get_Run_State
Description: 获取电机是否为运行状态
Input: 无
Output: 1,0
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline Q32U_ Motor_Read_Run_State(void)
{
    if(Motor.Motor_Flow == MOTOR_STATE_RUN)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**********************************************************************************************
Function: Motor_Set_Target_Freq
Description: 设置目标占空比
Input: 占空比（0~4095）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void Motor_Set_Target_Freq(Q32U_ Duty)
{
    Motor.MS_CTRL.PWM_CTRL._I_Q14I_duty_vr = Duty;
}

/**********************************************************************************************
Function: Motor_Read_Freq
Description: 读取电机频率
Input: 无
Output: 电机频率
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline Q32U_ Motor_Read_Freq(void)
{
    return Motor.MS_CTRL.FL_Freq.Q16I_Filter_out;
}

/**********************************************************************************************
Function: Motor_Set_Vbus
Description: 设置母线电压值
Input: 母线电压（lsb）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void Motor_Set_Vbus(Q32U_ Vbus_Val)
{
    Motor.MS_CTRL.Q12I_VBUS_VAL = Vbus_Val;
}

/**********************************************************************************************
Function: Motor_Read_Current_Max
Description: 获取相电流最大值，周期为该函数被调用的周期
Input: 无
Output: 相电流最大值
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline Q32U_ Motor_Read_Current_Max(void)
{
    Q32U_ iphase_max_tmp = Motor.Q14I_IPHASE_MAX_PU;
    Motor.Q14I_IPHASE_MAX_PU = 0;
    return iphase_max_tmp;
}

/**********************************************************************************************
Function: Motor_Read_Error
Description: 读取电机故障码
Input: 无
Output: 电机故障码
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline Q32U_ Motor_Read_Error(void)
{
    return Motor.Motor_Error_Flag.all;
}

/**********************************************************************************************
Function: Motor_Clear_Error
Description: 清除电机故障
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void Motor_Clear_Error(void)
{
    Motor.Motor_Error_Flag.all = 0U;
}

/**********************************************************************************************
Function: MotorTask_Freq_Flow
Description: 电机控制速度环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Freq_Flow(ST_MOTOR_TASK* pMotor);
/**********************************************************************************************
Function: MotorTask_Current_Flow
Description: 电机控制电流环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Current_Flow(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: MotorTask_Switch_Flow
Description: 电机控制换向
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Switch_Flow(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: MotorTask_PWM_Start_ADC_Flow
Description: 电机控制首次触发ADC
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_PWM_Start_ADC_Flow(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: MotorTask_Shut_Flow
Description: 电机控制故障关断
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Shut_Flow(ST_MOTOR_TASK* pMotor);

#endif /* MotorTask_H */
