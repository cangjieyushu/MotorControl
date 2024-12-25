/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
 
#include "MotorPara.h"

ST_MOTOR_TASK  Motor = 
{
    .Common_Ctrl.Q16U_iphase_offset_max = CURRENT_OFFSET_MAX_lsb,
    .Common_Ctrl.Q16U_iphase_offset_min = CURRENT_OFFSET_MIN_lsb,
    .Common_Ctrl.Q08U_iphase_offset_num = CURRENT_OFFSET_NUM,
    
    .Common_Ctrl.Q16U_position_duty = POSITION_DUTY,
    .Common_Ctrl.Q16U_position_tl = POSITION_TL_lsb,
    .Common_Ctrl.Q32U_hall_tim_freq = HAL_HALL_TIM_PRE_FREQ,
    
    
    .PMSM_Para.MC_HT = MOTOR_HTs,
    .PMSM_Para.MC_LT = MOTOR_LTs,
    .PMSM_Para.MC_U = V_BASE,
    .PMSM_Para.MC_I = I_BASE,
    .PMSM_Para.MC_F = F_BASE,
    .PMSM_Para.MC_W = W_BASE,
    .PMSM_Para.MC_R = R_BASE,
    .PMSM_Para.MC_L = L_BASE,
    .PMSM_Para.MC_P = P_BASE,
    .PMSM_Para.MC_T = T_BASE,
    
    .PMSM_Para.Q14I_Motor_HTs = Q14I_HTs_PU,
    .PMSM_Para.Q14I_Motor_LTs = Q14I_LTs_PU,
    .PMSM_Para.Q14I_Rs = Q14I_Rs_PU,                
    .PMSM_Para.Q14I_Ls = Q14I_Ls_PU,
    .PMSM_Para.Q14I_Ld = Q14I_Ld_PU,
    .PMSM_Para.Q14I_Lq = Q14I_Lq_PU,
    
    .PMSM_Para.Q14I_Flux = Q14I_FLUX_PU,
    .PMSM_Para.Q14I_Flux_2 = Q32I_RHT_14(Q14I_FLUX_PU * Q14I_FLUX_PU),
    
    .PMSM_Para.Q10I_One_Over_Ld = (Q32I_)(MOTOR_Q24_PU / Q14I_Ld_PU),
    .PMSM_Para.Q14I_Rs_Over_Ld = (Q32I_)(MOTOR_Q14_PU * Q14I_Rs_PU / Q14I_Ld_PU),
    .PMSM_Para.Q14I_Ld_Lq_Over_Ld = (Q32I_)(MOTOR_Q14_PU - (MOTOR_Q14_PU * Q14I_Lq_PU / Q14I_Ld_PU)),
    
    
    .FOC_Para.Q14I_VsCoeff = (Q32I_)(MOTOR_Q14_PU * MOTOR_VS_SCALE),
    .FOC_Para.Q12I_ADC_Time = (Q32I_)(HAL_ADC_DELAY_DUTY + HAL_ADC_SAMPLE_DUTY),
    .FOC_Para.Q12I_MaxScale = (Q32I_)(HAL_PWM_DUTY_MAX_U - (HAL_ADC_DELAY_DUTY + HAL_ADC_SAMPLE_DUTY)),
    .FOC_Para.Q12I_MaxDuty = HAL_PWM_DUTY_MAX_U,
    .FOC_Para.Q12I_VTime_1 = (Q32I_)HAL_ADC_SAMPLE_DUTY,
    .FOC_Para.Q12I_VTime_2 = (Q32I_)HAL_ADC_SAMPLE_DUTY,   
    
    
    .SRAD_Ctrl.PidSpd.Q14I_Kp = SPD_KP_GAIN,
    .SRAD_Ctrl.PidSpd.Q14I_Ki = SPD_KI_GAIN,
    .SRAD_Ctrl.PidSpd.Q14I_Kd = SPD_KD_GAIN,
    .SRAD_Ctrl.PidSpd.Q14I_OutMax = SPD_PID_MAX,
    .SRAD_Ctrl.PidSpd.Q14I_OutMin = SPD_PID_MIN,
    
    .SRAD_Ctrl.Q14I_SRAD_Rf = 0,
    .SRAD_Ctrl.SRAD_Max = (Q16I_)Q14I_MAX_SRAD_PU,
    .SRAD_Ctrl.SRAD_Min = -(Q16I_)Q14I_MAX_SRAD_PU,
    .SRAD_Ctrl.SRad_Ramp.Q32I_ADDStep = 0,
    .SRAD_Ctrl.SRad_Ramp.Q32I_SUBStep = 0,
    
    .SRAD_Ctrl.Id_Ramp.Q32I_Init = LOOP0_ID_RAMP_INIT,
    .SRAD_Ctrl.Id_Ramp.Q32I_Target = LOOP0_ID_RAMP_TARGET,
    .SRAD_Ctrl.Id_Ramp.Q32I_ADDStep = LOOP0_ID_RAMP_ADDSTEP,
    .SRAD_Ctrl.Id_Ramp.Q32I_SUBStep = -LOOP0_ID_RAMP_ADDSTEP,
    
    .SRAD_Ctrl.Iq_Ramp.Q32I_Init = LOOP0_IQ_RAMP_INIT,
    .SRAD_Ctrl.Iq_Ramp.Q32I_Target = LOOP0_IQ_RAMP_TARGET,
    .SRAD_Ctrl.Iq_Ramp.Q32I_ADDStep = LOOP0_IQ_RAMP_ADDSTEP,
    .SRAD_Ctrl.Iq_Ramp.Q32I_SUBStep = -LOOP0_IQ_RAMP_ADDSTEP,
    
    .SRAD_Ctrl.SpeedChange0 = LOOP0_SWITCH_SRAD,
    .SRAD_Ctrl.SpeedChangeTime_Num0 = LOOP0_SWITCH_TIME,
    .SRAD_Ctrl.SpeedChange1 = LOOP1_SWITCH_SRAD,
    .SRAD_Ctrl.SpeedChangeTime_Num1 = LOOP1_SWITCH_TIME,
    .SRAD_Ctrl.SpeedChange2 = 0,
    .SRAD_Ctrl.SpeedChangeTime_Num2 = 0,
    .SRAD_Ctrl.SpeedChange3 = LOOP3_SWITCH_SRAD,
    .SRAD_Ctrl.SpeedChangeTime_Num3 = LOOP3_SWITCH_TIME,
    .SRAD_Ctrl.SpeedTarget = LOOP3_SRAD_TARGET,
    .SRAD_Ctrl.SpeedStep1 = LOOP1_SRAD_RAMP_ADDSTEP,
    .SRAD_Ctrl.SpeedStep2 = LOOP2_SRAD_RAMP_ADDSTEP,
    .SRAD_Ctrl.SpeedStep3 = LOOP3_SRAD_RAMP_ADDSTEP,
    
    
    .IF_Ctrl.SRad_Ramp.Q32I_Init = LOOP0_SRAD_RAMP_INIT,
    .IF_Ctrl.SRad_Ramp.Q32I_Target = LOOP0_SRAD_RAMP_TARGET,
    .IF_Ctrl.SRad_Ramp.Q32I_ADDStep = LOOP0_SRAD_RAMP_ADDSTEP,
    .IF_Ctrl.SRad_Ramp.Q32I_SUBStep = -LOOP0_SRAD_RAMP_ADDSTEP,
    
    .IF_Ctrl.AngleError_Ramp.Q32I_Init = 0,
    .IF_Ctrl.AngleError_Ramp.Q32I_Target = 0,
    .IF_Ctrl.AngleError_Ramp.Q32I_ADDStep = LOOP0_ANGLE_ERROR_RAMP_ADDSTEP,
    .IF_Ctrl.AngleError_Ramp.Q32I_SUBStep = -LOOP0_ANGLE_ERROR_RAMP_ADDSTEP,
    
    .IF_Ctrl.AngleRad_Error = LOOP0_RAD_ERROR,
    .IF_Ctrl.AngleRad_time = LOOP0_RAD_TIME,   
    
    
    .WEAK_Ctrl.PidV.Q14I_Kp = WEAK_KP_GAIN,
    .WEAK_Ctrl.PidV.Q14I_Ki = WEAK_KI_GAIN,
    .WEAK_Ctrl.PidV.Q14I_Kd = WEAK_KD_GAIN,
    .WEAK_Ctrl.PidV.Q14I_OutMax = 0,
    .WEAK_Ctrl.PidV.Q14I_OutMin = -MATH_PI_OVER_TWO_U,
    
    
    .Current_Ctrl.PidId.Q14I_Kp = CURRENT_KP_GAIN,
    .Current_Ctrl.PidId.Q14I_Ki = CURRENT_KI_GAIN,
    .Current_Ctrl.PidId.Q14I_Kd = CURRENT_KD_GAIN,
    .Current_Ctrl.PidIq.Q14I_Kp = CURRENT_KP_GAIN,
    .Current_Ctrl.PidIq.Q14I_Ki = CURRENT_KI_GAIN,
    .Current_Ctrl.PidIq.Q14I_Kd = CURRENT_KD_GAIN,             
       
       
    .FLUX_Ctrl.Q14I_Ks = Q32I_RHT_14(EST_FLUX_R_Coeff * Q14I_Rs_PU),                    
    .FLUX_Ctrl.Q14I_Gamma = EST_FLUX_GAMMA,
    .FLUX_Ctrl.PLL_PID.Q14I_Kp = EST_FLUX_PLL_KP,
    .FLUX_Ctrl.PLL_PID.Q14I_Ki = EST_FLUX_PLL_KI,
    .FLUX_Ctrl.PLL_PID.Q14I_Kd = EST_FLUX_PLL_KD,
    .FLUX_Ctrl.PLL_PID.Q14I_OutMax = EST_FLUX_PLL_MAX,
    .FLUX_Ctrl.PLL_PID.Q14I_OutMin = EST_FLUX_PLL_MIN,
    .FLUX_Ctrl.FL_SRAD.Q08I_Filter_Coeff = SRAD_FILTER_COEFF,
    
    
    .SMO_Ctrl.Q14I_K1 = EST_SMO_K1,
    .SMO_Ctrl.Q14I_K2 = EST_SMO_K2,
    .SMO_Ctrl.PLL_PID.Q14I_Kp = EST_SMO_PLL_KP,
    .SMO_Ctrl.PLL_PID.Q14I_Ki = EST_SMO_PLL_KI,
    .SMO_Ctrl.PLL_PID.Q14I_Kd = EST_SMO_PLL_KD,
    .SMO_Ctrl.PLL_PID.Q14I_OutMax = EST_SMO_PLL_MAX,
    .SMO_Ctrl.PLL_PID.Q14I_OutMin = EST_SMO_PLL_MIN,
    .SMO_Ctrl.FL_SRAD.Q08I_Filter_Coeff = SRAD_FILTER_COEFF,
    
};
