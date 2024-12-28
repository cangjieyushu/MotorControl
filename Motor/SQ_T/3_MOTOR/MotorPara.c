/**************************************************************************************************
*     File Name :                        MotorPara.c
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制参数初始化源文件
**************************************************************************************************/
 
#include "MotorPara.h"

ST_MOTOR_TASK  Motor = 
{
    .MS_OFFSET._P_Q16U_offset_max = CURRENT_OFFSET_MAX_lsb,
    .MS_OFFSET._P_Q16U_offset_min = CURRENT_OFFSET_MIN_lsb,
    .MS_OFFSET._P_Q16U_check_num = CURRENT_OFFSET_NUM,
    
    .MS_FLYING._P_Q16U_check_tl = FREE_FLYING_TL,
    .MS_FLYING._P_Q16U_check_num = FREE_FLYING_NUM,
    .MS_FLYING._P_Q16U_flying_filter = FREE_FLYING_FILTER,
    .MS_FLYING._P_Q16U_flying_time = FREE_FLYING_TIME,
    .MS_FLYING._P_Q12U_vbus_max_val = (Q32U_)(MOTOR_VOLTAGE_V/HAL_ADC_VOLTAGE_SCALE),
    
    .MS_BOOT._P_Q16U_boot_tl = BOOT_CHECK_TL_lsb,
    .MS_BOOT._P_Q16U_boot_num = BOOT_CHECK_NUM,
    .MS_BOOT._P_Q16U_boot_time = BOOT_CHECK_TIME,
    .MS_BOOT._P_Q12U_boot_duty = BOOT_CHECK_DUTY,
    
    .MS_POSITION._P_Q16U_position_tl = POSITION_TL_lsb,
    .MS_POSITION._P_Q12U_position_duty = POSITION_DUTY,
    .MS_POSITION._P_Q12U_vbus_max_val = (Q32U_)(MOTOR_VOLTAGE_V/HAL_ADC_VOLTAGE_SCALE),

    .BRAKE_CTRL.Ramp_Brake_Duty.Q32I_Init = BRAKE_DUTY_CTRL_MIN,
    .BRAKE_CTRL.Ramp_Brake_Duty.Q32I_ADDStep = BRAKE_DUTY_RAMP_ADDSTEP,
    .BRAKE_CTRL.Ramp_Brake_Duty.Q32I_SUBStep = BRAKE_DUTY_RAMP_SUBSTEP,
    .BRAKE_CTRL.Ramp_Brake_Duty.Q32I_Target = BRAKE_DUTY_CTRL_MAX,
    .BRAKE_CTRL._P_Q16U_no_time = NO_BRAKE_TIME,
    .BRAKE_CTRL._P_Q16U_slow_time = SLOW_BRAKE_TIME,
    .BRAKE_CTRL._P_Q16U_short_time = SHORT_BRAKE_TIME,
    .BRAKE_CTRL._P_Q12U_duty_max = HAL_PWM_DUTY_MAX,
    
    .MS_CTRL.MS_DIAG._P_Q06U_rise_tl = DIAG_CROSS_RISE_TL,
    .MS_CTRL.MS_DIAG._P_Q06U_fall_tl = DIAG_CROSS_FALL_TL,
    .MS_CTRL.MS_DIAG._P_Q08U_filter = DIAG_CROSS_FILTER,
    .MS_CTRL.MS_DIAG._P_Q16U_current_filter = CURRENT_CROSS_DIAG_FILTER,
    
    .MS_CTRL.MS_CURRENT._P_Q06U_rise_tl = CURRENT_CROSS_RISE_TL,
    .MS_CTRL.MS_CURRENT._P_Q06U_fall_tl = CURRENT_CROSS_FALL_TL,
    .MS_CTRL.MS_CURRENT._P_Q08U_filter = CURRENT_CROSS_FILTER,
    .MS_CTRL.MS_CURRENT._P_Q16U_current_filter = CURRENT_CROSS_FAIL_FILTER,
    .MS_CTRL.MS_CURRENT._P_Q14U_to_flux_freq = CURRENT_TO_FLUX_FREQ,
    .MS_CTRL.MS_CURRENT._P_Q16U_to_flux_num = CURRENT_TO_FLUX_NUM,
    
    .MS_CTRL.MS_FLUX._P_Q06U_rise_tl = FLUX_CROSS_RISE_TL,
    .MS_CTRL.MS_FLUX._P_Q06U_fall_tl = FLUX_CROSS_FALL_TL,
    .MS_CTRL.MS_FLUX._P_Q08U_filter = FLUX_CROSS_FILTER,
    .MS_CTRL.MS_FLUX._P_Q14U_to_current_freq = FLUX_TO_CURRENT_FREQ,
    .MS_CTRL.MS_FLUX._P_Q16U_to_current_num = FLUX_TO_CURRENT_NUM,
    .MS_CTRL.MS_FLUX._P_Q14U_to_bemf_freq = FLUX_TO_BEMF_FREQ,
    .MS_CTRL.MS_FLUX._P_Q12U_to_bemf_duty = FLUX_TO_BEMF_DUTY,
    .MS_CTRL.MS_FLUX._P_Q16U_to_bemf_num = FLUX_TO_BEMF_NUM,
    
    .MS_CTRL.MS_BEMF._P_Q08U_filter = BEMF_CROSS_FILTER,
    .MS_CTRL.MS_BEMF._P_Q06U_coeff = BEMF_CROSS_DELAY_COEFF,
    .MS_CTRL.MS_BEMF._P_Q14U_to_flux_freq = BEMF_TO_FLUX_FREQ,
    .MS_CTRL.MS_BEMF._P_Q12U_to_flux_duty = BEMF_TO_FLUX_DUTY,
    .MS_CTRL.MS_BEMF._P_Q16U_to_flux_num = BEMF_TO_FLUX_NUM,
    
    .MS_CTRL.FREQ_CAL._P_Q32U_hall_tim_freq = HAL_HALL_TIM_PRE_FREQ,
    .MS_CTRL.FREQ_CAL._P_Q32U_hall_tim_max_cnt = 0xFFFFFFFFU,
 
    .MS_CTRL.PWM_CTRL.Ramp_Duty.Q32I_Init = DUTY_CTRL_MIN,
    .MS_CTRL.PWM_CTRL.Ramp_Duty.Q32I_ADDStep = DUTY_RAMP_ADDSTEP,
    .MS_CTRL.PWM_CTRL.Ramp_Duty.Q32I_SUBStep = DUTY_RAMP_SUBSTEP,
    
    .MS_CTRL.PWM_CTRL._P_Q12U_low_to_high_duty = PWM_FREQ_LOW_TO_HIGH_DUTY,
    .MS_CTRL.PWM_CTRL._P_Q12U_high_to_low_duty = PWM_FREQ_HIGH_TO_LOW_DUTY,
    .MS_CTRL.PWM_CTRL._P_Q14U_low_pwm_freq = PWM_FREQ_LOW,
    .MS_CTRL.PWM_CTRL._P_Q14U_high_pwm_freq = PWM_FREQ_HIGH,
    .MS_CTRL.PWM_CTRL._P_Q12U_duty_max = DUTY_CTRL_MAX,
    .MS_CTRL.PWM_CTRL._P_Q12U_duty_min = DUTY_CTRL_MIN,
    .MS_CTRL.PWM_CTRL._P_Q14U_motor_freq_max = Q14I_FREQ_MOTOR_TO_PU(MOTOR_MAX_FREQ),
    .MS_CTRL.PWM_CTRL._P_Q14U_motor_freq_min = Q14I_FREQ_MOTOR_TO_PU(MOTOR_MIN_FREQ),
    
    .MS_CTRL.STALL_CTRL._P_Q16U_current_error_time = MOTOR_STALL_CURRENT_ERROR_TIME,
    .MS_CTRL.STALL_CTRL._P_Q16U_error_time = MOTOR_STALL_ERROR_TIME,
    .MS_CTRL.STALL_CTRL._P_Q06U_switch_coeff = MOTOR_STALL_SWITCH_COEFF,
    
    .MS_CTRL.Ramp_Freq.Q32I_Init = Q14I_FREQ_MOTOR_TO_PU(MOTOR_MIN_FREQ),
    .MS_CTRL.Ramp_Freq.Q32I_ADDStep = FREQ_RAMP_ADDSTEP,
    .MS_CTRL.Ramp_Freq.Q32I_SUBStep = FREQ_RAMP_SUBSTEP,
    
    .MS_CTRL.Q14U_iphase_max_pu = IPHSAE_PID_RF,
    .MS_CTRL.Q14U_ibus_max_pu = IBUS_PID_RF,
    .MS_CTRL.Q14U_ibrake_max_pu = IBRAKE_PID_RF,
    .MS_CTRL.Q14U_vbus_max_pu = Q14I_VOLTAGE_MOTOR_TO_PU(MOTOR_VOLTAGE_V),

    .MS_CTRL.FL_Iphase.Q08I_Filter_Coeff = IPHASE_FILTER_COEFF,
    .MS_CTRL.FL_Freq.Q08I_Filter_Coeff = FREQ_FILTER_COEFF,
    .MS_CTRL.FL_Ibus.Q08I_Filter_Coeff = IBUS_FILTER_COEFF,
    .MS_CTRL.FL_Ibrake.Q08I_Filter_Coeff = IBRAKE_FILTER_COEFF,
    
    .MS_CTRL.PID_Iphase.Q14I_Kp = IPHASE_PID_KP,
    .MS_CTRL.PID_Iphase.Q14I_Ki = IPHASE_PID_KI,
    .MS_CTRL.PID_Iphase.Q14I_Kd = IPHASE_PID_KD,
    .MS_CTRL.PID_Iphase.Q14I_StepMax = IPHASE_PID_STEPMAX,
    .MS_CTRL.PID_Iphase.Q14I_StepMin = IPHASE_PID_STEPMIN,
    .MS_CTRL.PID_Iphase.Q14I_OutMax = IPHASE_PID_OUTMAX,
    .MS_CTRL.PID_Iphase.Q14I_OutMin = IPHASE_PID_OUTMIN,
    
    .MS_CTRL.PID_Freq.Q14I_Kp = FREQ_PID_KP,
    .MS_CTRL.PID_Freq.Q14I_Ki = FREQ_PID_KI,
    .MS_CTRL.PID_Freq.Q14I_Kd = FREQ_PID_KD,
    .MS_CTRL.PID_Freq.Q14I_StepMax = FREQ_PID_STEPMAX,
    .MS_CTRL.PID_Freq.Q14I_StepMin = FREQ_PID_STEPMIN,
    .MS_CTRL.PID_Freq.Q14I_OutMax = FREQ_PID_OUTMAX,
    .MS_CTRL.PID_Freq.Q14I_OutMin = FREQ_PID_OUTMIN,
    
    .MS_CTRL.PID_Ibus.Q14I_Kp = IBUS_PID_KP,
    .MS_CTRL.PID_Ibus.Q14I_Ki = IBUS_PID_KI,
    .MS_CTRL.PID_Ibus.Q14I_Kd = IBUS_PID_KD,
    .MS_CTRL.PID_Ibus.Q14I_StepMax = IBUS_PID_STEPMAX,
    .MS_CTRL.PID_Ibus.Q14I_StepMin = IBUS_PID_STEPMIN,
    .MS_CTRL.PID_Ibus.Q14I_OutMax = IBUS_PID_OUTMAX,
    .MS_CTRL.PID_Ibus.Q14I_OutMin = IBUS_PID_OUTMIN,
    
    .MS_CTRL.PID_Ibrake.Q14I_Kp = IBRAKE_PID_KP,
    .MS_CTRL.PID_Ibrake.Q14I_Ki = IBRAKE_PID_KI,
    .MS_CTRL.PID_Ibrake.Q14I_Kd = IBRAKE_PID_KD,
    .MS_CTRL.PID_Ibrake.Q14I_StepMax = IBRAKE_PID_STEPMAX,
    .MS_CTRL.PID_Ibrake.Q14I_StepMin = IBRAKE_PID_STEPMIN,
    .MS_CTRL.PID_Ibrake.Q14I_OutMax = IBRAKE_PID_OUTMAX,
    .MS_CTRL.PID_Ibrake.Q14I_OutMin = IBRAKE_PID_OUTMIN,
    
};
