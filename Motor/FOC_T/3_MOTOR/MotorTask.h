/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef MotorTask_H
#define MotorTask_H

#include "MotorHal.h"
#include "MotorFoc.h"
#include "MotorPara.h"

typedef void(*pFUN_HPWMLPWM_OUT)(Q32U_);

__STATIC_INLINE void Motor_Start(void)
{
    Motor.Motor_State_Flag.bit.motor_run_flag = 1U;
}

__STATIC_INLINE void Motor_Stop(void)
{
    Motor.Motor_State_Flag.bit.motor_run_flag = 0U;
}

__STATIC_INLINE Q32U_ Motor_Get_Run_State(void)
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
__STATIC_INLINE void Motor_Set_Target_Freq(Q32I_ Duty)
{
    Motor.SRAD_Ctrl.Q14I_SRAD_Rf = Q32I_RHT_14(Duty*(Q14I_MAX_SRAD_PU - Q14I_MIN_SRAD_PU)) + Q14I_MIN_SRAD_PU;
}

__STATIC_INLINE void Motor_Set_Vbus(Q32I_ Vbus_Val)
{
    Motor.FOC_Para.Q14I_Vbus = Q14I_VOLTAGE_LSB_TO_PU(Vbus_Val);
}

__STATIC_INLINE Q32U_ Motor_Read_Current_Max(void)
{
    Q32U_ iphase_max_tmp = Motor.FOC_Para.Q14I_IPHASE_MAX;
    Motor.FOC_Para.Q14I_IPHASE_MAX = 0;
    return iphase_max_tmp;
}

__STATIC_INLINE Q32I_ Motor_Read_Freq(void)
{
    return Motor.SRAD_Ctrl.Q14I_SRAD_Fb;
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
void MotorTask_Update_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Shut_Down_Flow(ST_MOTOR_TASK* pMotor);

#endif /* MotorTask_H */
