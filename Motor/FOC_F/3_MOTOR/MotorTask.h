/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef MotorTask_H
#define MotorTask_H

#include "Math.h"
#include "MotorHal.h"
#include "MotorEst.h"
#include "MotorFoc.h"
#include "MotorPara.h"
    
static inline void Motor_Start(void)
{
    Motor.Motor_State_Flag.bit.motor_run_flag = 1U;
}

static inline void Motor_Stop(void)
{
    Motor.Motor_State_Flag.bit.motor_run_flag = 0U;
}

static inline Q32U_ Motor_Get_Run_State(void)
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

static inline void Motor_Set_Dir(float Dir)
{
    Motor.SRAD_CTRL._I_F_DIR_Target = Dir;
    Motor.IF_CTRL._I_F_DIR_Target = Dir;
    Motor.VF_CTRL._I_F_DIR_Target = Dir;
}

static inline float Motor_Get_Dir(void)
{
    return Motor.SRAD_CTRL._O_F_DIR_Set;
}

static inline void Motor_Set_Target_SRAD(float SRAD)
{
    Motor.SRAD_CTRL._I_F_SRAD_Target = SRAD;
}

static inline void Motor_Set_Vbus(float Vbus_Val)
{
    Motor.SVPWM_CTRL._I_F_Vbus = Vbus_Val;
    Motor.SVPWM_CTRL._I_F_One_Over_Vbus = 1.0f/Vbus_Val;
    Motor.SRAD_CTRL._I_F_Vbus = Vbus_Val;
    Motor.CURRENT_CTRL._I_F_Vbus = Vbus_Val;
}

static inline float Motor_Read_Current_Max(void)
{
    float iphase_max_tmp = Motor.F_Iphase_Max;
    Motor.F_Iphase_Max = 0.0f;
    return iphase_max_tmp;
}

static inline float Motor_Read_SRAD(void)
{
    return Motor.SRAD_CTRL._I_F_SRAD;
}

static inline Q32U_ Motor_Read_Error(void)
{
    return Motor.Motor_Error_Flag.all;
}

static inline void Motor_Clear_Error(void)
{
    Motor.Motor_Error_Flag.all = 0U;
}

void MotorTask_SRAD_Flow(ST_MOTOR_TASK* pMotor);
Ram_Func void MotorTask_Current_Flow(ST_MOTOR_TASK* pMotor);

#endif /* MotorTask_H */
