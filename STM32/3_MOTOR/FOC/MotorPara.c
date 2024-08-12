/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
 
#include "MotorPara.h"

ST_MOTOR_TASK  Motor = 
{
    .pmsm_para.Ts = HAL_CURRENT_LOOP_TIME,
    .pmsm_para.Rs = USER_MOTOR1_Rs,                
    .pmsm_para.Ls = USER_MOTOR1_Ls,
    .pmsm_para.Ld = USER_MOTOR1_Ld,
    .pmsm_para.Lq = USER_MOTOR1_Lq,
    .pmsm_para.Flux = USER_MOTOR1_ROTOR_FLUX,
    .pmsm_para.Flux_2 = USER_MOTOR1_ROTOR_FLUX * USER_MOTOR1_ROTOR_FLUX,
    .pmsm_para.One_Over_Ld = 1.0f / USER_MOTOR1_Ld,
    .pmsm_para.Rs_Over_Ld = USER_MOTOR1_Rs / USER_MOTOR1_Ld,
    .pmsm_para.Ld_Lq_Over_Ld = (USER_MOTOR1_Ld - USER_MOTOR1_Lq) / USER_MOTOR1_Ld,
    .pmsm_para.Eight_Lq_Ld_2 = 8.0f * (USER_MOTOR1_Lq - USER_MOTOR1_Ld) * (USER_MOTOR1_Lq - USER_MOTOR1_Ld),
    .pmsm_para.One_Over_Lq_Ld_Over_4 = 0.25f / (USER_MOTOR1_Lq - USER_MOTOR1_Ld),
    
    .foc_para.VsMaxScale = USER_MAX_VS_MAG_PU,
    
    .speed_ctrl.PidSpd.Kp = USER_M1_SPD_KP_GAIN,
    .speed_ctrl.PidSpd.Ki = USER_M1_SPD_KI_GAIN,
    .speed_ctrl.PidSpd.Kd = USER_M1_SPD_KD_GAIN,
    .speed_ctrl.PidSpd.OutMax = USER_M1_SPD_PID_MAX,
    .speed_ctrl.PidSpd.OutMin = USER_M1_SPD_PID_MIN,
    
    .speed_ctrl.CurrentRamp.Init = USER_M1_CURRENTRAMP_INIT,
    .speed_ctrl.CurrentRamp.Step = USER_M1_CURRENTRAMP_STEP,
    .speed_ctrl.CurrentRamp.Target = USER_M1_CURRENTRAMP_TARGET,
    .speed_ctrl.SpeedChange = USER_M1_CLOSELOOP1_SPEED,
    .speed_ctrl.SpeedChangeTime_Num = USER_M1_CLOSELOOP1_SWITCH_TIME,
    
    .speed_ctrl.SpeedRef = USER_M1_CLOSELOOP3_SPEED,
    .speed_ctrl.SpeedMax = USER_MOTOR1_MAX_SPEED,
    .speed_ctrl.SpeedMin = -USER_MOTOR1_MAX_SPEED,
    .speed_ctrl.SpdRamp.Step = USER_M1_SPDRAMP_STEP,
    
    .weak_ctrl.PidV.Kp = USER_M1_WEAK_KP_GAIN,
    .weak_ctrl.PidV.Ki = USER_M1_WEAK_KI_GAIN,
    .weak_ctrl.PidV.Kd = USER_M1_WEAK_KD_GAIN,
    .weak_ctrl.PidV.OutMax = 0.0f,
    .weak_ctrl.PidV.OutMin = -MATH_PI_OVER_TWO,
    
    .current_ctrl.PidId.Kp = USER_M1_FOC_KP_GAIN,
    .current_ctrl.PidId.Ki = USER_M1_FOC_KI_GAIN,
    .current_ctrl.PidId.Kd = USER_M1_FOC_KD_GAIN,
    .current_ctrl.PidIq.Kp = USER_M1_FOC_KP_GAIN,
    .current_ctrl.PidIq.Ki = USER_M1_FOC_KI_GAIN,
    .current_ctrl.PidIq.Kd = USER_M1_FOC_KD_GAIN,
    .current_ctrl.MaxScale = USER_PWM_MAXSCALE,
    .current_ctrl.MinScale = USER_PWM_MINSCALE,
    
    .brake_ctrl.BrakeTime = USER_M1_BRAKE_MAX_TIME,
    .brake_ctrl.CurrentFilterTime = USER_M1_BRAKE_CURRENT_FILTER,
    .brake_ctrl.MinBrakeCurrent = USER_M1_BRAKE_CURRENT_TL,
    
    .if_ctrl.AngleRadRamp.Init = USER_M1_ANGLERADRAMP_INIT,
    .if_ctrl.AngleRadRamp.Target = USER_M1_ANGLERADRAMP_TARGET,
    .if_ctrl.AngleRadRamp.Step = USER_M1_ANGLERADRAMP_STEP,
    .if_ctrl.AngleRad_Error = USER_M1_ANGLERAD_ERROR,
    .if_ctrl.AngleRad_time = USER_M1_ANGLERAD_TIME,                                           
                                                                                                     
    .flux_ctrl.Ks = USER_M1_FLUX_R_Coeff * USER_MOTOR1_Rs,                    
    .flux_ctrl.Kt = USER_M1_FLUX_KT,
    .flux_ctrl.Pll_Pid.Kp = USER_M1_FLUX_PLL_KP,
    .flux_ctrl.Pll_Pid.Ki = USER_M1_FLUX_PLL_KI,
    .flux_ctrl.Pll_Pid.Kd = USER_M1_FLUX_PLL_KD,
    .flux_ctrl.Pll_Pid.OutMax = USER_M1_FLUX_PLL_MAX,
    .flux_ctrl.Pll_Pid.OutMin = USER_M1_FLUX_PLL_MIN,
    
    .svc_ctrl.SpeedLimit = 0.01f*MATH_2PI*USER_MOTOR1_MAX_SPEED,
    .svc_ctrl.Lambda = 2.0f,
    .svc_ctrl.Alpha = 0.1f*MATH_2PI*USER_MOTOR1_MAX_SPEED,
    
    .smo_ctrl.K1 = USER_M1_SMO_K1,
    .smo_ctrl.K2 = USER_M1_SMO_K2,
    .smo_ctrl.Pll_Pid.Kp = USER_M1_SMO_PLL_KP,
    .smo_ctrl.Pll_Pid.Ki = USER_M1_SMO_PLL_KI,
    .smo_ctrl.Pll_Pid.Kd = USER_M1_SMO_PLL_KD,
    .smo_ctrl.Pll_Pid.OutMax = USER_M1_SMO_PLL_MAX,
    .smo_ctrl.Pll_Pid.OutMin = USER_M1_SMO_PLL_MIN,

    .hall_ctrl.TIM_FreqHz = HAL_TIM_SWITCH_FREQ,
};

void MotorPara_TargetDir_Change(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->speed_ctrl.SpeedRef > 0.0f)
    {
        pMotor->foc_para.TargetDir = 1.0f;
    }
    else
    {
        pMotor->foc_para.TargetDir = -1.0f;
    }
    
    pMotor->speed_ctrl.CurrentRamp.Init = pMotor->foc_para.TargetDir*USER_M1_CURRENTRAMP_INIT;
    pMotor->speed_ctrl.CurrentRamp.Target = pMotor->foc_para.TargetDir*USER_M1_CURRENTRAMP_TARGET;

    pMotor->if_ctrl.AngleRadRamp.Init = pMotor->foc_para.TargetDir*USER_M1_ANGLERADRAMP_INIT;
    pMotor->if_ctrl.AngleRadRamp.Target = pMotor->foc_para.TargetDir*USER_M1_ANGLERADRAMP_TARGET;
};
