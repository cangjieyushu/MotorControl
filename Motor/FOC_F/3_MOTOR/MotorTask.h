/**************************************************************************************************
*     File Name :                        MotorTask.h
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机子任务头文件
**************************************************************************************************/
#ifndef MotorTask_H
#define MotorTask_H

#include "MotorPara.h"
#include "MotorHal.h"
    
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
Input: 1.0f（正转），-1.0f（反转）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void Motor_Set_Dir(float Dir)
{
    Motor.SRAD_CTRL._I_F_DIR_Target = Dir;
    Motor.IF_CTRL._I_F_DIR_Target = Dir;
    Motor.VF_CTRL._I_F_DIR_Target = Dir;
}

/**********************************************************************************************
Function: Motor_Read_Dir
Description: 获取电机运行方向
Input: 无
Output: 1.0f（正转），-1.0f（反转）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline float Motor_Read_Dir(void)
{
    return Motor.SRAD_CTRL._O_F_DIR_Set;
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
Function: Motor_Set_Target_SRAD
Description: 设置电机转速
Input: 电机转速（电角速度，弧度制）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void Motor_Set_Target_SRAD(float SRAD)
{
    Motor.SRAD_CTRL._I_F_SRAD_Target = SRAD;
}

/**********************************************************************************************
Function: Motor_Read_SRAD
Description: 读取电机转速
Input: 无
Output: 电机转速（电角速度，弧度制）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline float Motor_Read_SRAD(void)
{
    return Motor.SRAD_CTRL._I_F_SRAD;
}

/**********************************************************************************************
Function: Motor_Set_Vbus
Description: 设置FOC算法的母线电压值
Input: 母线电压（V）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void Motor_Set_Vbus(float Vbus_Val)
{
    Motor.SVPWM_CTRL._I_F_Vbus = Vbus_Val;
    Motor.SVPWM_CTRL._I_F_One_Over_Vbus = 1.0f/Vbus_Val;
    Motor.SRAD_CTRL._I_F_Vbus = Vbus_Val;
    Motor.CURRENT_CTRL._I_F_Vbus = Vbus_Val;
}

/**********************************************************************************************
Function: Motor_Read_Current_Max
Description: 获取相电流最大值，周期为该函数被调用的周期
Input: 无
Output: 相电流最大值（A）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline float Motor_Read_Current_Max(void)
{
    float iphase_max_tmp = Motor.F_Iphase_Max;
    Motor.F_Iphase_Max = 0.0f;
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
Function: MotorTask_SRAD_Flow
Description: 电机控制速度环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_SRAD_Flow(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: MotorTask_Current_Flow
Description: 电机控制电流环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorTask_Current_Flow(ST_MOTOR_TASK* pMotor);

#endif /* MotorTask_H */
