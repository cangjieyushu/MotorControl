/*
*     File Name :                        mcsq_para
*     Library/Module Name :              mcsq
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制参数
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "mcsq_para.h"


/*-------------------------- 2. 变量 ---------------------------------*/
ST_MCSQ_TASK MCSQ_Task = 
{
    .Motor_Flag.bit.motor_speed_flag = SPEED_CLOSE_EN,
    .Motor_Flag.bit.motor_busA_flag = I_BUS_CLOSE_EN,
    .Motor_Flag.bit.motor_busP_flag = P_BUS_CLOSE_EN,
    
    .Motor_API.Max_Speed_rpm = (Q32U_)MOTOR_MAX_SPEED,
    .Motor_API.Min_Speed_rpm = (Q32U_)MOTOR_MIN_SPEED,
    .Motor_API.Max_Iphase_0p01A = 100*(Q32U_)I_BASE,
    .Motor_API.Max_IBus_0p01A = 100*(Q32U_)I_BASE,
    
    .MCSQ_CTRL.MCSQ_BLDC.FL_Iphase.P_Q14I_LPF_Coeff = IPHASE_FILTER_COEFF,
    .MCSQ_CTRL.MCSQ_BLDC.FL_Freq.P_Q14I_LPF_Coeff = FREQ_FILTER_COEFF,
    .MCSQ_CTRL.MCSQ_BLDC.FL_Ibus.P_Q14I_LPF_Coeff = IBUS_FILTER_COEFF,
    .MCSQ_CTRL.MCSQ_BLDC.FL_Vbus_ADC.P_Q14I_LPF_Coeff = VBUS_FILTER_COEFF,
    .MCSQ_CTRL.MCSQ_BLDC.FL_Temp_ADC.P_Q14I_LPF_Coeff = TEMP_FILTER_COEFF,
    
    
    .MCSQ_CTRL.MCSQ_BLDC.Freq_Cal.P_Q32U_Hall_Time_Freq = HAL_HALL_TIM_PRE_FREQ,
    .MCSQ_CTRL.MCSQ_BLDC.Freq_Cal.P_Q32U_Hall_Time_Max_count = HAL_HALL_TIM_MAX_CNT,
    
    .MCSQ_CTRL.MCSQ_BLDC.P_Q14U_Iphase_Max_pu = Q14I_CURRENT_PHASE_PU,
    .MCSQ_CTRL.MCSQ_BLDC.P_Q14U_Ibus_Max_pu = Q14I_CURRENT_BUS_PU,
    .MCSQ_CTRL.MCSQ_BLDC.P_Q14U_Vbus_Max_pu = Q14I_VOLTAGE_PU,
    .MCSQ_CTRL.MCSQ_BLDC.P_Q28U_Freq_Scale = Q28I_FREQ_TO_PU(1U),
    
    
    .MCSQ_CTRL.MCSQ_OFFSET.P_Q12U_Offset_Max = CURRENT_OFFSET_MAX_lsb,
    .MCSQ_CTRL.MCSQ_OFFSET.P_Q12U_Offset_Min = CURRENT_OFFSET_MIN_lsb,
    .MCSQ_CTRL.MCSQ_OFFSET.P_Q16U_Offset_Check_Count = CURRENT_OFFSET_COUNT,
    
    
    .MCSQ_CTRL.MCSQ_FLYING.P_Q32U_Flying_Low_Bemf_TL = FREE_FLYING_TL_lsb,
    .MCSQ_CTRL.MCSQ_FLYING.P_Q16U_Flying_Low_Bemf_Count = FREE_FLYING_COUNT,
    .MCSQ_CTRL.MCSQ_FLYING.P_Q16U_Flying_Fail_Count = FREE_FLYING_FAIL_COUNT,
    .MCSQ_CTRL.MCSQ_FLYING.P_Q16U_Flying_Check_Filter = FREE_FLYING_FILTER,
    
    
    .MCSQ_CTRL.MCSQ_BOOT.P_Q32U_Boot_Low_Bemf_TL = BOOT_CHECK_TL_lsb,
    .MCSQ_CTRL.MCSQ_BOOT.P_Q16U_Boot_Low_Bemf_Count = BOOT_CHECK_COUNT,
    .MCSQ_CTRL.MCSQ_BOOT.P_Q16U_Boot_Fail_Count = BOOT_CHECK_FAIL_COUNT,
    .MCSQ_CTRL.MCSQ_BOOT.P_Q14U_Boot_Duty_Set = BOOT_CHECK_DUTY,
    
    
    .MCSQ_CTRL.MCSQ_POSITION.P_Q12U_Position_Iphase_TL = POSITION_TL_lsb,
    .MCSQ_CTRL.MCSQ_POSITION.P_Q14U_Position_Duty_Set = POSITION_DUTY,
    
    
    .MCSQ_CTRL.MCSQ_BRAKE.Ramp_Brake_Duty.P_Q14I_Init = BRAKE_DUTY_CTRL_MIN,
    .MCSQ_CTRL.MCSQ_BRAKE.Ramp_Brake_Duty.P_Q28I_ADDStep = BRAKE_DUTY_RAMP_ADDSTEP,
    .MCSQ_CTRL.MCSQ_BRAKE.Ramp_Brake_Duty.P_Q28I_SUBStep = BRAKE_DUTY_RAMP_SUBSTEP,
    .MCSQ_CTRL.MCSQ_BRAKE.Ramp_Brake_Duty.P_Q14I_Target = BRAKE_DUTY_CTRL_MAX,
    
    .MCSQ_CTRL.MCSQ_BRAKE.P_Q16U_NoBrake_Count = NO_BRAKE_TIME,
    .MCSQ_CTRL.MCSQ_BRAKE.P_Q16U_SlowBrake_Count = SLOW_BRAKE_TIME,
    .MCSQ_CTRL.MCSQ_BRAKE.P_Q16U_ShortBrake_Count = SHORT_BRAKE_TIME,
    
    
    .MCSQ_CTRL.MCSQ_DIAG.P_Q14U_DIAG_Rise_tl = DIAG_CROSS_RISE_TL,
    .MCSQ_CTRL.MCSQ_DIAG.P_Q14U_DIAG_Fall_tl = DIAG_CROSS_FALL_TL,
    .MCSQ_CTRL.MCSQ_DIAG.P_Q16U_DIAG_Filter_Count = DIAG_CROSS_FILTER,
    
    .MCSQ_CTRL.MCSQ_FLUX.P_Q14U_Flux_Rise_tl = FLUX_CROSS_RISE_TL,
    .MCSQ_CTRL.MCSQ_FLUX.P_Q14U_Flux_Fall_tl = FLUX_CROSS_FALL_TL,
    .MCSQ_CTRL.MCSQ_FLUX.P_Q16U_Flux_Filter_Count = FLUX_CROSS_FILTER,
    .MCSQ_CTRL.MCSQ_FLUX.P_Q14U_Flux_to_Bemf_Freq = FLUX_TO_BEMF_FREQ,
    .MCSQ_CTRL.MCSQ_FLUX.P_Q14U_Flux_to_Bemf_Count = FLUX_TO_BEMF_NUM,
    
    .MCSQ_CTRL.MCSQ_BEMF.P_Q16U_Bemf_Filter_Count = BEMF_CROSS_FILTER,
    .MCSQ_CTRL.MCSQ_BEMF.P_Q14U_Bemf_Delay_Coeff = BEMF_CROSS_DELAY_COEFF,
    .MCSQ_CTRL.MCSQ_BEMF.P_Q14U_Bemf_to_Flux_Freq = BEMF_TO_FLUX_FREQ,
    .MCSQ_CTRL.MCSQ_BEMF.P_Q14U_Bemf_to_Flux_Count = BEMF_TO_FLUX_NUM,
    
    
    .MCSQ_CTRL.PWM_CTRL.Ramp_Duty.P_Q14I_Init = DUTY_CTRL_MIN,
    .MCSQ_CTRL.PWM_CTRL.Ramp_Duty.P_Q28I_ADDStep = DUTY_RAMP_ADDSTEP,
    .MCSQ_CTRL.PWM_CTRL.Ramp_Duty.P_Q28I_SUBStep = DUTY_RAMP_SUBSTEP,
    
    .MCSQ_CTRL.PWM_CTRL.P_Q14U_Low_to_High_Duty = PWM_FREQ_LOW_TO_HIGH_DUTY,
    .MCSQ_CTRL.PWM_CTRL.P_Q14U_High_to_Low_Duty = PWM_FREQ_HIGH_TO_LOW_DUTY,
    .MCSQ_CTRL.PWM_CTRL.P_Q32U_Start_PWMCount = PWM_FREQ_START,
    .MCSQ_CTRL.PWM_CTRL.P_Q32U_Low_PWMCount = PWM_FREQ_LOW,
    .MCSQ_CTRL.PWM_CTRL.P_Q32U_High_PWMCount = PWM_FREQ_HIGH,
    .MCSQ_CTRL.PWM_CTRL.P_Q14U_Duty_Max = DUTY_CTRL_MAX,
    .MCSQ_CTRL.PWM_CTRL.P_Q14U_Duty_Min = DUTY_CTRL_MIN,
    .MCSQ_CTRL.PWM_CTRL.P_Q14U_Motor_Freq_Max = Q14I_MAX_FREQ_PU,
    .MCSQ_CTRL.PWM_CTRL.P_Q14U_Motor_Freq_Min = Q14I_MIN_FREQ_PU,
    
    .MCSQ_CTRL.PWM_CTRL.P_Q32U_ADC_Delay_Value = HAL_ADC_DELAY_VALUE,
    .MCSQ_CTRL.PWM_CTRL.P_Q32U_ADC_Sample_Value = HAL_ADC_SAMPLE_VALUE,
    .MCSQ_CTRL.PWM_CTRL.P_Q32U_ADC_Solve_Value = HAL_ADC_SOLVE_VALUE,
    .MCSQ_CTRL.PWM_CTRL.P_Q32U_TIM_Delay_Value = HAL_SWITCH_DELAY_MIN_VALUE,
    
    
    .MCSQ_CTRL.Ramp_Freq.P_Q14I_Init = Q14I_MIN_FREQ_PU,
    .MCSQ_CTRL.Ramp_Freq.P_Q28I_ADDStep = FREQ_RAMP_ADDSTEP,
    .MCSQ_CTRL.Ramp_Freq.P_Q28I_SUBStep = FREQ_RAMP_SUBSTEP,
    
    .MCSQ_CTRL.PID_Freq.P_Q14I_Kp = FREQ_PID_KP,
    .MCSQ_CTRL.PID_Freq.P_Q14I_Ki = FREQ_PID_KI,
    .MCSQ_CTRL.PID_Freq.P_Q14I_Kd = FREQ_PID_KD,
    .MCSQ_CTRL.PID_Freq.P_Q28I_StepMax = FREQ_PID_STEPMAX,
    .MCSQ_CTRL.PID_Freq.P_Q28I_StepMin = FREQ_PID_STEPMIN,
    .MCSQ_CTRL.PID_Freq.P_Q14I_OutMax = FREQ_PID_OUTMAX,
    .MCSQ_CTRL.PID_Freq.P_Q14I_OutMin = FREQ_PID_OUTMIN,
    
    .MCSQ_CTRL.PID_Ibus.P_Q14I_Kp = IBUS_PID_KP,
    .MCSQ_CTRL.PID_Ibus.P_Q14I_Ki = IBUS_PID_KI,
    .MCSQ_CTRL.PID_Ibus.P_Q14I_Kd = IBUS_PID_KD,
    .MCSQ_CTRL.PID_Ibus.P_Q28I_StepMax = IBUS_PID_STEPMAX,
    .MCSQ_CTRL.PID_Ibus.P_Q28I_StepMin = IBUS_PID_STEPMIN,
    .MCSQ_CTRL.PID_Ibus.P_Q14I_OutMax = IBUS_PID_OUTMAX,
    .MCSQ_CTRL.PID_Ibus.P_Q14I_OutMin = IBUS_PID_OUTMIN,
    
    .MCSQ_CTRL.PID_Iphase.P_Q14I_Kp = IPHASE_PID_KP,
    .MCSQ_CTRL.PID_Iphase.P_Q14I_Ki = IPHASE_PID_KI,
    .MCSQ_CTRL.PID_Iphase.P_Q14I_Kd = IPHASE_PID_KD,
    .MCSQ_CTRL.PID_Iphase.P_Q28I_StepMax = IPHASE_PID_STEPMAX,
    .MCSQ_CTRL.PID_Iphase.P_Q28I_StepMin = IPHASE_PID_STEPMIN,
    .MCSQ_CTRL.PID_Iphase.P_Q14I_OutMax = IPHASE_PID_OUTMAX,
    .MCSQ_CTRL.PID_Iphase.P_Q14I_OutMin = IPHASE_PID_OUTMIN,
    
    
    .MCSQ_CTRL.STALL_CTRL.P_Q16U_Stall_Count = MOTOR_STALL_ERROR_TIME,
    .MCSQ_CTRL.STALL_CTRL.P_Q06U_Stall_Switch_Coeff = MOTOR_STALL_SWITCH_COEFF,
    
    
    .Motor_Error.P_Q32U_MOS_Error_Count = MOS_ERROR_COUNT,
    
    .Motor_Error.Over_Voltage.P_Q14I_Check_TL = OVER_VOLTAGE_PROTECT_LEVEL_TL,
    .Motor_Error.Over_Voltage.P_Q32U_Check_Time = OVER_VOLTAGE_PROTECT_LEVEL_TIME,
    .Motor_Error.Over_Voltage.P_Q14I_Clear_TL = OVER_VOLTAGE_CLEAR_LEVEL_TL,
    .Motor_Error.Over_Voltage.P_Q32U_Clear_Time = OVER_VOLTAGE_CLEAR_LEVEL_TIME,
    .Motor_Error.Over_Voltage.P_Q32U_Check_Count = 1U,
    .Motor_Error.Over_Voltage.Check_Flag.bit.Clear_Mode = 0U,
    
    .Motor_Error.Low_Voltage.P_Q14I_Check_TL = LOW_VOLTAGE_PROTECT_LEVEL_TL,
    .Motor_Error.Low_Voltage.P_Q32U_Check_Time = LOW_VOLTAGE_PROTECT_LEVEL_TIME,
    .Motor_Error.Low_Voltage.P_Q14I_Clear_TL = 0U,
    .Motor_Error.Low_Voltage.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Low_Voltage.P_Q32U_Check_Count = 1U,
    .Motor_Error.Low_Voltage.Check_Flag.bit.Clear_Mode = 0U,
    
    .Motor_Error.Over_Current1.P_Q14I_Check_TL = CURRENT_PROTECT_LEVEL_1_TL,
    .Motor_Error.Over_Current1.P_Q32U_Check_Time = CURRENT_PROTECT_LEVEL_1_TIME,
    .Motor_Error.Over_Current1.P_Q14I_Clear_TL = 0U,
    .Motor_Error.Over_Current1.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Over_Current1.P_Q32U_Check_Count = 1000U,
    .Motor_Error.Over_Current1.Check_Flag.bit.Clear_Mode = 1U,
    
    .Motor_Error.Over_Current2.P_Q14I_Check_TL = CURRENT_PROTECT_LEVEL_2_TL,
    .Motor_Error.Over_Current2.P_Q32U_Check_Time = CURRENT_PROTECT_LEVEL_2_TIME,
    .Motor_Error.Over_Current2.P_Q14I_Clear_TL = 0U,
    .Motor_Error.Over_Current2.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Over_Current2.P_Q32U_Check_Count = 100U,
    .Motor_Error.Over_Current2.Check_Flag.bit.Clear_Mode = 1U,
    
    .Motor_Error.Over_Current3.P_Q14I_Check_TL = CURRENT_PROTECT_LEVEL_3_TL,
    .Motor_Error.Over_Current3.P_Q32U_Check_Time = CURRENT_PROTECT_LEVEL_3_TIME,
    .Motor_Error.Over_Current3.P_Q14I_Clear_TL = 0U,
    .Motor_Error.Over_Current3.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Over_Current3.P_Q32U_Check_Count = 10U,
    .Motor_Error.Over_Current3.Check_Flag.bit.Clear_Mode = 1U,
    
    .Motor_Error.Over_Temp.P_Q14I_Check_TL = OVER_TEMP_PROTECT_LEVEL_TL,
    .Motor_Error.Over_Temp.P_Q32U_Check_Time = OVER_TEMP_PROTECT_LEVEL_TIME,
    .Motor_Error.Over_Temp.P_Q14I_Clear_TL = OVER_TEMP_CLEAR_LEVEL_TL,
    .Motor_Error.Over_Temp.P_Q32U_Clear_Time = OVER_TEMP_CLEAR_LEVEL_TIME,
    .Motor_Error.Over_Temp.P_Q32U_Check_Count = 1U,
    .Motor_Error.Over_Temp.Check_Flag.bit.Clear_Mode = 0U,
    
    .Motor_Error.Low_Temp.P_Q14I_Check_TL = LOW_TEMP_PROTECT_LEVEL_TL,
    .Motor_Error.Low_Temp.P_Q32U_Check_Time = LOW_TEMP_PROTECT_LEVEL_TIME,
    .Motor_Error.Low_Temp.P_Q14I_Clear_TL = LOW_TEMP_CLEAR_LEVEL_TL,
    .Motor_Error.Low_Temp.P_Q32U_Clear_Time = LOW_TEMP_CLEAR_LEVEL_TIME,
    .Motor_Error.Low_Temp.P_Q32U_Check_Count = 1U,
    .Motor_Error.Low_Temp.Check_Flag.bit.Clear_Mode = 0U,
    
    .Motor_Error.Over_Speed.P_Q14I_Check_TL = OVER_SPEED_PROTECT_LEVEL_TL,
    .Motor_Error.Over_Speed.P_Q32U_Check_Time = OVER_SPEED_PROTECT_LEVEL_TIME,
    .Motor_Error.Over_Speed.P_Q14I_Clear_TL = 0U,
    .Motor_Error.Over_Speed.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Over_Speed.P_Q32U_Check_Count = 1U,
    .Motor_Error.Over_Speed.Check_Flag.bit.Clear_Mode = 0U,
    
    .Motor_Error.Low_Speed.P_Q14I_Check_TL = LOW_SPEED_PROTECT_LEVEL_TL,
    .Motor_Error.Low_Speed.P_Q32U_Check_Time = LOW_SPEED_PROTECT_LEVEL_TIME,
    .Motor_Error.Low_Speed.P_Q14I_Clear_TL = 0U,
    .Motor_Error.Low_Speed.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Low_Speed.P_Q32U_Check_Count = 1U,
    .Motor_Error.Low_Speed.Check_Flag.bit.Clear_Mode = 0U,
    
    .Motor_Error.Over_Power.P_Q14I_Check_TL = OVER_POWER_PROTECT_LEVEL_TL,
    .Motor_Error.Over_Power.P_Q32U_Check_Time = OVER_POWER_PROTECT_LEVEL_TIME,
    .Motor_Error.Over_Power.P_Q14I_Clear_TL = 0U,
    .Motor_Error.Over_Power.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Over_Power.P_Q32U_Check_Count = 10U,
    .Motor_Error.Over_Power.Check_Flag.bit.Clear_Mode = 1U,
    
    .Motor_Error.Over_Ibus.P_Q14I_Check_TL = OVER_IBUS_PROTECT_LEVEL_TL,
    .Motor_Error.Over_Ibus.P_Q32U_Check_Time = OVER_IBUS_PROTECT_LEVEL_TIME,
    .Motor_Error.Over_Ibus.P_Q14I_Clear_TL = 0U,
    .Motor_Error.Over_Ibus.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Over_Ibus.P_Q32U_Check_Count = 10U,
    .Motor_Error.Over_Ibus.Check_Flag.bit.Clear_Mode = 1U,
    
    .Motor_Error.Fast_Over_Voltage.P_Q14I_Check_TL = FAST_OVER_VOLTAGE_PROTECT_LEVEL_TL,
    .Motor_Error.Fast_Over_Voltage.P_Q32U_Check_Time = FAST_OVER_VOLTAGE_PROTECT_LEVEL_TIME,
    .Motor_Error.Fast_Over_Voltage.P_Q14I_Clear_TL = 0U,
    .Motor_Error.Fast_Over_Voltage.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Fast_Over_Voltage.P_Q32U_Check_Count = 10U,
    .Motor_Error.Fast_Over_Voltage.Check_Flag.bit.Clear_Mode = 1U,
    
    .Motor_Error.Fast_Over_Current.P_Q14I_Check_TL = FAST_CURRENT_PROTECT_LEVEL_TL,
    .Motor_Error.Fast_Over_Current.P_Q32U_Check_Time = FAST_CURRENT_PROTECT_LEVEL_TIME,
    .Motor_Error.Fast_Over_Current.P_Q14I_Clear_TL = 0U,
    .Motor_Error.Fast_Over_Current.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Fast_Over_Current.P_Q32U_Check_Count = 10U,
    .Motor_Error.Fast_Over_Current.Check_Flag.bit.Clear_Mode = 1U,
};


/*-------------------------- 3. 公有接口实现 -----------------------------*/
void Motor_Parameter_API_SQ(ST_MCSQ_TASK* pMotor)
{
    if(pMotor->Motor_Flag.bit.motor_target_dir == 1U)
    {
        pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Target = CW;
    }
    else
    {
        pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Target = CCW;
    }
    
    if(pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set == CW)
    {
        pMotor->Motor_Flag.bit.motor_real_dir = 1U;
    }
    else
    {
        pMotor->Motor_Flag.bit.motor_real_dir = 0U;
    }
    
    if(pMotor->Motor_Flow == MOTOR_STATE_RUN)
    {
        pMotor->Motor_Flag.bit.motor_running_flag = 1U;
    }
    else
    {
        pMotor->Motor_Flag.bit.motor_running_flag = 0U;
    }
    
    pMotor->MCSQ_CTRL.PWM_CTRL.I_Q14U_Duty_VR = pMotor->Motor_API.Target_Speed_pu;
    pMotor->Motor_API.Real_Speed_pu = pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Freq.O_Q14I_LPF_Out;
    pMotor->Motor_API.Real_Iphase_pu = pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Iphase.O_Q14I_LPF_Out;
    pMotor->Motor_API.Real_Ibus_pu = pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Ibus.O_Q14I_LPF_Out;
}
