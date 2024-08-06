/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
 
#include "MotorPara.h"

ST_MOTOR_TASK  Motor = 
{
    .speed_ctrl.PidSpd.Kp = USER_M1_SPD_KP_GAIN,
    .speed_ctrl.PidSpd.Ki = USER_M1_SPD_KI_GAIN,
    .speed_ctrl.PidSpd.Kd = USER_M1_SPD_KD_GAIN,
    .speed_ctrl.PidSpd.OutMax = USER_M1_SPD_PID_MAX,
    .speed_ctrl.PidSpd.OutMin = USER_M1_SPD_PID_MIN,
    .speed_ctrl.IdRef = 0.0f,
    .speed_ctrl.IqRef = 0.0f,
    
    .speed_ctrl.CurrentRamp.Init = USER_M1_CURRENTRAMP_INIT,
    .speed_ctrl.CurrentRamp.Step = USER_M1_CURRENTRAMP_STEP,
    .speed_ctrl.CurrentRamp.Target = USER_M1_CURRENTRAMP_TARGET,
    .speed_ctrl.SpeedChange = USER_M1_CLOSELOOP1_SPEED,
    .speed_ctrl.SpeedChangeTime_Num = USER_M1_CLOSELOOP1_SWITCH_TIME,
    
    .speed_ctrl.SpeedRef = USER_M1_CLOSELOOP3_SPEED,
    .speed_ctrl.SpeedMax = USER_MOTOR1_MAX_SPEED,
    .speed_ctrl.SpeedMin = -USER_MOTOR1_MAX_SPEED,
    .speed_ctrl.SpdRamp.Step = USER_M1_SPDRAMP_STEP,
    
    .hall_ctrl.Ts = HAL_CURRENT_LOOP_TIME,
    .hall_ctrl.TIM_FreqHz = 0.0f,
    
    /* foc initial */
    .foc_ctrl.VsMaxScale = USER_MAX_VS_MAG_PU,
    .foc_ctrl.PidId.Kp = USER_M1_FOC_KP_GAIN,
    .foc_ctrl.PidId.Ki = USER_M1_FOC_KI_GAIN,
    .foc_ctrl.PidId.Kd = USER_M1_FOC_KD_GAIN,
    .foc_ctrl.PidIq.Kp = USER_M1_FOC_KP_GAIN,
    .foc_ctrl.PidIq.Ki = USER_M1_FOC_KI_GAIN,
    .foc_ctrl.PidIq.Kd = USER_M1_FOC_KD_GAIN,
    .foc_ctrl.MaxScale = USER_PWM_MAXSCALE,
    .foc_ctrl.MinScale = USER_PWM_MINSCALE,
    .foc_ctrl.IdRef = 0.0f,
    .foc_ctrl.IqRef = 0.0f,
    
    .if_ctrl.AngleRadRamp.Init = USER_M1_ANGLERADRAMP_INIT,
    .if_ctrl.AngleRadRamp.Target = USER_M1_ANGLERADRAMP_TARGET,
    .if_ctrl.AngleRadRamp.Step = USER_M1_ANGLERADRAMP_STEP,
    .if_ctrl.AngleRad_Error = USER_M1_ANGLERAD_ERROR,                                                                  
    .if_ctrl.AngleRad_time = USER_M1_ANGLERAD_TIME,                                                                   
                                                                                                     
    .flux_ctrl.Rs = USER_M1_FLUX_R_Coeff * USER_MOTOR1_Rs,                                       
    .flux_ctrl.Ls = USER_MOTOR1_Ls,
    .flux_ctrl.Ts = HAL_CURRENT_LOOP_TIME,
    .flux_ctrl.Ref_Flux_2 = USER_MOTOR1_ROTOR_FLUX * USER_MOTOR1_ROTOR_FLUX,
    .flux_ctrl.Kt = USER_M1_FLUX_KT,
    .flux_ctrl.Pll_Pid.Kp = USER_M1_FLUX_PLL_KP,
    .flux_ctrl.Pll_Pid.Ki = USER_M1_FLUX_PLL_KI,
    .flux_ctrl.Pll_Pid.Kd = USER_M1_FLUX_PLL_KD,
    .flux_ctrl.Pll_Pid.OutMax = USER_M1_FLUX_PLL_MAX,
    .flux_ctrl.Pll_Pid.OutMin = USER_M1_FLUX_PLL_MIN,
    
    .smo_ctrl.Rs = USER_MOTOR1_Rs,
    .smo_ctrl.Ld = USER_MOTOR1_Ld,
    .smo_ctrl.Lq = USER_MOTOR1_Lq,
    .smo_ctrl.One_Over_Ld = 1.0f / USER_MOTOR1_Ld,
    .smo_ctrl.Rs_Over_Ld = USER_MOTOR1_Rs / USER_MOTOR1_Ld,
    .smo_ctrl.Ld_Lq_Over_Ld = (USER_MOTOR1_Ld - USER_MOTOR1_Lq) / USER_MOTOR1_Ld,
    .smo_ctrl.Ts = HAL_CURRENT_LOOP_TIME,
    .smo_ctrl.K1 = USER_M1_SMO_K1,
    .smo_ctrl.K2 = USER_M1_SMO_K2,
    .smo_ctrl.Pll_Pid.Kp = USER_M1_SMO_PLL_KP,
    .smo_ctrl.Pll_Pid.Ki = USER_M1_SMO_PLL_KI,
    .smo_ctrl.Pll_Pid.Kd = USER_M1_SMO_PLL_KD,
    .smo_ctrl.Pll_Pid.OutMax = USER_M1_SMO_PLL_MAX,
    .smo_ctrl.Pll_Pid.OutMin = USER_M1_SMO_PLL_MIN,

    .brake_ctrl.BrakeTime = USER_M1_BRAKE_MAX_TIME,
    .brake_ctrl.CurrentFilterTime = USER_M1_BRAKE_CURRENT_FILTER,
    .brake_ctrl.MinBrakeCurrent = USER_M1_BRAKE_CURRENT_TL,
};

