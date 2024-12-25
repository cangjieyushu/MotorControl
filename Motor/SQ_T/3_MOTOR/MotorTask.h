/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef MotorTask_H
#define MotorTask_H

#include "MotorHal.h"
#include "MotorSQ.h"
#include "MotorPara.h"

typedef void(*pFUN_HPWMLGPIO_OUT)(Q32U_);
typedef void(*pFUN_HPWMLPWM_OUT)(Q32U_);

__STATIC_INLINE void Motor_Start(void)
{
    Motor.Motor_State_Flag.bit.motor_run_flag = 1U;
}

__STATIC_INLINE void Motor_Stop(void)
{
    Motor.Motor_State_Flag.bit.motor_run_flag = 0U;
}

__STATIC_INLINE void Motor_Set_Dir(Q32U_ Dir)
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

__STATIC_INLINE Q32U_ Motor_Read_Dir(void)
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

__STATIC_INLINE Q32U_ Motor_Read_Run_State(void)
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

__STATIC_INLINE void Motor_Set_Target_Freq(Q32U_ Duty)
{
    Motor.MS_CTRL.PWM_CTRL._I_Q14I_duty_vr = Duty;
}

__STATIC_INLINE void Motor_Set_Vbus(Q32U_ Vbus_Val)
{
    Motor.MS_CTRL.Q12I_VBUS_VAL = Vbus_Val;
}

__STATIC_INLINE Q32U_ Motor_Read_Freq(void)
{
    return Motor.MS_CTRL.FL_Freq.Q16I_Filter_out;
}

__STATIC_INLINE Q32U_ Motor_Read_Current_Max(void)
{
    Q32U_ iphase_max_tmp = Motor.Q14I_IPHASE_MAX_PU;
    Motor.Q14I_IPHASE_MAX_PU = 0;
    return iphase_max_tmp;
}

__STATIC_INLINE Q08U_ Motor_Read_Error(void)
{
    return Motor.Motor_Error_Flag.all;
}

__STATIC_INLINE void Motor_Clear_Error(void)
{
    Motor.Motor_Error_Flag.all = 0U;
}

void MotorTask_Speed_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Current_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Switch_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_PWM_Start_ADC_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Shut_Flow(ST_MOTOR_TASK* pMotor);

#endif /* MotorTask_H */
