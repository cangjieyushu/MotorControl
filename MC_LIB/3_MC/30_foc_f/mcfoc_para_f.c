/*
*     File Name :                        mcfoc_para_f
*     Library/Module Name :              mcfoc_f
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制参数初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "mcfoc_para_f.h"


/*-------------------------- 2. 变量 ---------------------------------*/
extern float F_Table_Current[5];
extern float F_Table_Freq[10];

extern float F_Table_Freq_Kp_Coeff[10];
extern float F_Table_Freq_Ki_Coeff[10];
extern float F_Table_Lq_Coeff[10];

extern float F_Table_SMO_H1_Coeff[10];
extern float F_Table_SMO_PLL_Kp_Coeff[10];
extern float F_Table_SMO_PLL_Ki_Coeff[10];
extern float F_Table_SMO_Angle[50];

extern float F_Table_FLUX_Gamma_Coeff[10];
extern float F_Table_FLUX_PLL_Kp_Coeff[10];
extern float F_Table_FLUX_PLL_Ki_Coeff[10];
extern float F_Table_FLUX_Angle[50];


ST_MCFOC_TASK_F MCFOC_Task_F = 
{
    .Motor_API.Max_Speed_rpm = (Q32U_)MOTOR_MAX_SPEED,
    .Motor_API.Min_Speed_rpm = (Q32U_)MOTOR_MIN_SPEED,
    .Motor_API.Max_Iphase_0p01A = 100*(Q32U_)I_BASE,
    .Motor_API.Max_IBus_0p01A = 100*(Q32U_)I_BASE,

    .PMSM_Filter.Mean_Freq.P_Q32U_MEAN_Num = 16U,
    .PMSM_Filter.Mean_Vbus.P_Q32U_MEAN_Num = 16U,
    .PMSM_Filter.Mean_Ibus.P_Q32U_MEAN_Num = 16U,
    .PMSM_Filter.Mean_Id.P_Q32U_MEAN_Num = 16U,
    .PMSM_Filter.Mean_Iq.P_Q32U_MEAN_Num = 16U,
    .PMSM_Filter.Mean_Ud.P_Q32U_MEAN_Num = 16U,
    .PMSM_Filter.Mean_Uq.P_Q32U_MEAN_Num = 16U,
    .PMSM_Filter.Mean_Es.P_Q32U_MEAN_Num = 16U,
    
    .PMSM_Filter.Max_Ia.P_Q32U_MAX_Num = 16U,
    .PMSM_Filter.Max_Ib.P_Q32U_MAX_Num = 16U,
    .PMSM_Filter.Max_Ic.P_Q32U_MAX_Num = 16U,

    .PMSM_Filter.Mean_Ibus_10ms.P_Q32U_MEAN_Num = 10U,
    .PMSM_Filter.Mean_Is_1000ms.P_Q32U_MEAN_Num = 10U,


    .PMSM_Elec.P_F_Modulation_Mode = 0.666667f,
    .PMSM_Elec.P_F_UsRef_Scale = 1.01f,
    .PMSM_Elec.P_F_Pre_Period = 1.0f,


    .PMSM_Para.Ramp_PWM_FREQ.P_F_ADDStep = 1.0f,
    .PMSM_Para.Ramp_PWM_FREQ.P_F_SUBStep = -1.0f,
    .PMSM_Para.Ramp_PWM_FREQ.O_F_Output = MOTOR_PWM_FREQ_HIGH,
    .PMSM_Para.P_F_PWM_FREQ_MAX = MOTOR_PWM_FREQ_HIGH,
    .PMSM_Para.P_F_PWM_FREQ_MIN = MOTOR_PWM_FREQ_LOW,
    
    .PMSM_Para.PWM_FREQ_CHECK.P_F_Check_TL = MOTOR_PWM_FREQ_TL,
    .PMSM_Para.PWM_FREQ_CHECK.P_Q32U_Check_Time = 100U,
    .PMSM_Para.PWM_FREQ_CHECK.P_F_Clear_TL = MOTOR_PWM_FREQ_CLR,
    .PMSM_Para.PWM_FREQ_CHECK.P_Q32U_Clear_Time = 100U,
    .PMSM_Para.PWM_FREQ_CHECK.Check_Flag.bit.Clear_Mode = 0U,

    .PMSM_Para.P_F_Rs = Rs_PU,
    .PMSM_Para.P_F_Ld = Ld_PU,
    .PMSM_Para.P_F_Lq = Lq_PU,
    .PMSM_Para.P_F_Ls = Ls_PU,
    .PMSM_Para.P_F_Flux = FLUX_PU,
    .PMSM_Para.P_F_Ts = HTs_PU,

    .PMSM_Para.TAB_Lq_Coeff.x = F_Table_Current,
    .PMSM_Para.TAB_Lq_Coeff.y = F_Table_Lq_Coeff,
    .PMSM_Para.TAB_Lq_Coeff.n = 5U,
    

    .MCFOC_Offset.P_Q12U_Offset_Max = CURRENT_OFFSET_MAX_lsb,
    .MCFOC_Offset.P_Q12U_Offset_Min = CURRENT_OFFSET_MIN_lsb,
    .MCFOC_Offset.P_Q16U_Offset_Check_Count = CURRENT_OFFSET_NUM,


    .Align_Ctrl.Ramp_Align_Id.P_F_Target = MOTOR_ALIGN_ID_TARGET,
    .Align_Ctrl.Ramp_Align_Id.P_F_ADDStep = MOTOR_ALIGN_IDRAMP_ADDSTEP,
    .Align_Ctrl.Ramp_Align_Angle.P_F_ADDStep = MOTOR_ALIGN_ANGLERAMP_ADDSTEP,
    .Align_Ctrl.P_Q32U_Align_Check_Count = MOTOR_ALIGN_COUNT,

    .IF_Ctrl.FL_Active_Power.P_F_HPF_Coeff = 0.9f,
    .IF_Ctrl.PID_Reactive_Power.P_F_Kp = 0.001f,
    .IF_Ctrl.PID_Reactive_Power.P_F_Ki = 0.001f,
    .IF_Ctrl.PID_Reactive_Power.P_F_Kd = 0.00f,
    .IF_Ctrl.Ramp_IF_Iq.P_F_Target = MOTOR_IF_IQRAMP_TARGET,
    .IF_Ctrl.Ramp_IF_Iq.P_F_ADDStep = MOTOR_IF_IQRAMP_ADDSTEP,
    .IF_Ctrl.Ramp_IF_FREQ.P_F_Target = MOTOR_IF_FREQRAMP_TARGET,
    .IF_Ctrl.Ramp_IF_FREQ.P_F_ADDStep = MOTOR_IF_FREQRAMP_ADDSTEP,
    
    .IF_Ctrl.P_F_IF_Freq_Add_Step0 = MOTOR_IF_FREQRAMP_ADDSTEP,
    .IF_Ctrl.P_F_IF_Freq_Add_Step1 = 2.0f*MOTOR_IF_FREQRAMP_ADDSTEP,
    .IF_Ctrl.P_F_IF_Freq_Add_Step2 = 3.0f*MOTOR_IF_FREQRAMP_ADDSTEP,
    .IF_Ctrl.P_F_IF_Freq_TL1 = 0.2f*MOTOR_IF_FREQRAMP_TARGET,
    .IF_Ctrl.P_F_IF_Freq_TL2 = 0.6f*MOTOR_IF_FREQRAMP_TARGET,

    .IF_Ctrl.P_F_IF_Angle_Err_Limit = MOTOR_IF_ANGLE_ERROR,
    .IF_Ctrl.P_F_IF_Q_Coeff = 0.1f,
    .IF_Ctrl.P_Q32U_IF_Angle_Err_Check_Count = MOTOR_IF_SWITCH_COUNT,
    
    .Freq_Ctrl.PID_POWER.P_F_Kp = 0.00f,
    .Freq_Ctrl.PID_POWER.P_F_Ki = 0.00f,
    .Freq_Ctrl.PID_POWER.P_F_Kd = 0.0f,
    .Freq_Ctrl.PID_POWER.P_F_Kc = 0.01f,
    .Freq_Ctrl.PID_POWER.P_F_OutMax = 1.0f,
    .Freq_Ctrl.PID_POWER.P_F_OutMin = 0.1f,

    .Freq_Ctrl.P_F_FREQ_Kp = MOTOR_FREQ_KP_GAIN,
    .Freq_Ctrl.P_F_FREQ_Ki = MOTOR_FREQ_KI_GAIN,
    .Freq_Ctrl.PID_FREQ.P_F_Kd = MOTOR_FREQ_KD_GAIN,
    .Freq_Ctrl.PID_FREQ.P_F_Kc = 0.01f,
    .Freq_Ctrl.PID_FREQ.P_F_OutMax = MOTOR_FREQ_PID_MAX,
    .Freq_Ctrl.PID_FREQ.P_F_OutMin = MOTOR_FREQ_PID_MIN,
    .Freq_Ctrl.TAB_FREQ_Kp_Coeff.x = F_Table_Freq,
    .Freq_Ctrl.TAB_FREQ_Kp_Coeff.y = F_Table_Freq_Kp_Coeff,
    .Freq_Ctrl.TAB_FREQ_Kp_Coeff.n = 10U,
    .Freq_Ctrl.TAB_FREQ_Ki_Coeff.x = F_Table_Freq,
    .Freq_Ctrl.TAB_FREQ_Ki_Coeff.y = F_Table_Freq_Ki_Coeff,
    .Freq_Ctrl.TAB_FREQ_Ki_Coeff.n = 10U,

    .Freq_Ctrl.PID_WEAK.P_F_Kp = 0.01f,
    .Freq_Ctrl.PID_WEAK.P_F_Ki = 0.01f,
    .Freq_Ctrl.PID_WEAK.P_F_Kd = 0.0f,
    .Freq_Ctrl.PID_WEAK.P_F_Kc = 0.01f,
    .Freq_Ctrl.PID_WEAK.P_F_OutMax = 0.0f,
    .Freq_Ctrl.PID_WEAK.P_F_OutMin = -0.125f,

    .Freq_Ctrl.Ramp_FREQ.P_F_ADDStep = MOTOR_FREQ_RAMP_ADDSTEP,
    .Freq_Ctrl.Ramp_FREQ.P_F_SUBStep = MOTOR_FREQ_RAMP_SUBSTEP,
    
    .Freq_Ctrl.WEAK_CHECK.P_F_Check_TL = 2.00f,
    .Freq_Ctrl.WEAK_CHECK.P_Q32U_Check_Time = 100U,
    .Freq_Ctrl.WEAK_CHECK.P_F_Clear_TL = 0.9f,
    .Freq_Ctrl.WEAK_CHECK.P_Q32U_Clear_Time = 2000U,
    .Freq_Ctrl.WEAK_CHECK.P_Q32U_Check_Count = 10U,
    .Freq_Ctrl.WEAK_CHECK.Check_Flag.bit.Clear_Mode = 1U,
    .Freq_Ctrl.P_F_FREQ_PowerRef = 1.0f,
    .Freq_Ctrl.P_F_FREQ_IbusRef = 1.0f,


    .Current_Ctrl.PID_Id.P_F_Kp = MOTOR_CURRENT_KP_GAIN,
    .Current_Ctrl.PID_Id.P_F_Ki = MOTOR_CURRENT_KI_GAIN,
    .Current_Ctrl.PID_Id.P_F_Kd = MOTOR_CURRENT_KD_GAIN,
    .Current_Ctrl.PID_Id.P_F_Kc = 0.01f,

    .Current_Ctrl.PID_Iq.P_F_Kp = MOTOR_CURRENT_KP_GAIN,
    .Current_Ctrl.PID_Iq.P_F_Ki = MOTOR_CURRENT_KI_GAIN,
    .Current_Ctrl.PID_Iq.P_F_Kd = MOTOR_CURRENT_KD_GAIN,
    .Current_Ctrl.PID_Iq.P_F_Kc = 0.01f,
    

    .SVPWM_Ctrl.P_F_MaxDuty = HAL_MAX_DUTY,
    .SVPWM_Ctrl.P_F_MidDuty = HAL_MID_DUTY,
    .SVPWM_Ctrl.P_F_MinDuty = HAL_MIN_DUTY,
    .SVPWM_Ctrl.P_F_ADCSampleDuty = HAL_ADC_SAMPLE_DUTY,
    .SVPWM_Ctrl.P_F_PWM_All_Count = HAL_PWM_ALL_VALUE_F,
    .SVPWM_Ctrl.P_F_DeadTimeDuty = 0.0f,
    .SVPWM_Ctrl.P_F_DT_Current_TL = 0.0f,
    
    .SVPWM_Ctrl.FIVE_CHECK.P_F_Check_TL = 2.00f,
    .SVPWM_Ctrl.FIVE_CHECK.P_Q32U_Check_Time = 100U,
    .SVPWM_Ctrl.FIVE_CHECK.P_F_Clear_TL = 0.50f,
    .SVPWM_Ctrl.FIVE_CHECK.P_Q32U_Clear_Time = 100U,
    .SVPWM_Ctrl.FIVE_CHECK.P_Q32U_Check_Count = 10U,
    .SVPWM_Ctrl.FIVE_CHECK.Check_Flag.bit.Clear_Mode = 1U,


    .EMF_Ctrl.FL_EMF_Ialfa_err.P_F_LPF_Coeff = 0.0025f,
    .EMF_Ctrl.FL_EMF_Ibeta_err.P_F_LPF_Coeff = 0.0025f,


    .SMO_Ctrl.PID_SMO_PLL.P_F_Kd = MOTOR_SMO_PLL_KD,
    .SMO_Ctrl.PID_SMO_PLL.P_F_OutMax = MOTOR_SMO_PLL_MAX,
    .SMO_Ctrl.PID_SMO_PLL.P_F_OutMin = MOTOR_SMO_PLL_MIN,
    .SMO_Ctrl.FL_SMO_FREQ.P_F_LPF_Coeff = MOTOR_PLL_SPEED_LPF_COEFF,

    .SMO_Ctrl.P_F_SMO_H1 = MOTOR_SMO_H1,
    .SMO_Ctrl.P_F_SMO_PLL_Kp = MOTOR_SMO_PLL_KP,
    .SMO_Ctrl.P_F_SMO_PLL_Ki = MOTOR_SMO_PLL_KI,
    
    .SMO_Ctrl.TAB_SMO_H1_Coeff.x = F_Table_Freq,
    .SMO_Ctrl.TAB_SMO_H1_Coeff.y = F_Table_SMO_H1_Coeff,
    .SMO_Ctrl.TAB_SMO_H1_Coeff.n = 10U,
    
    .SMO_Ctrl.TAB_SMO_Kp_Coeff.x = F_Table_Freq,
    .SMO_Ctrl.TAB_SMO_Kp_Coeff.y = F_Table_SMO_PLL_Kp_Coeff,
    .SMO_Ctrl.TAB_SMO_Kp_Coeff.n = 10U,
    
    .SMO_Ctrl.TAB_SMO_Ki_Coeff.x = F_Table_Freq,
    .SMO_Ctrl.TAB_SMO_Ki_Coeff.y = F_Table_SMO_PLL_Ki_Coeff,
    .SMO_Ctrl.TAB_SMO_Ki_Coeff.n = 10U,

    .SMO_Ctrl.TAB_SMO_Angle_Comp.x = F_Table_Freq,
    .SMO_Ctrl.TAB_SMO_Angle_Comp.y = F_Table_Current,
    .SMO_Ctrl.TAB_SMO_Angle_Comp.z = F_Table_SMO_Angle,
    .SMO_Ctrl.TAB_SMO_Angle_Comp.nx = 10U,
    .SMO_Ctrl.TAB_SMO_Angle_Comp.ny = 5U,
    

    .FLUX_Ctrl.PID_FLUX_PLL.P_F_Kd = MOTOR_FLUX_PLL_KD,
    .FLUX_Ctrl.PID_FLUX_PLL.P_F_OutMax = MOTOR_FLUX_PLL_MAX,
    .FLUX_Ctrl.PID_FLUX_PLL.P_F_OutMin = MOTOR_FLUX_PLL_MIN,
    .FLUX_Ctrl.FL_FLUX_FREQ.P_F_LPF_Coeff = MOTOR_PLL_SPEED_LPF_COEFF,

    .FLUX_Ctrl.P_F_FLUX_Gamma = MOTOR_FLUX_GAMMA,
    .FLUX_Ctrl.P_F_FLUX_PLL_Kp = MOTOR_FLUX_PLL_KP,
    .FLUX_Ctrl.P_F_FLUX_PLL_Ki = MOTOR_FLUX_PLL_KI,

    .FLUX_Ctrl.TAB_FLUX_Gamma_Coeff.x = F_Table_Freq,
    .FLUX_Ctrl.TAB_FLUX_Gamma_Coeff.y = F_Table_FLUX_Gamma_Coeff,
    .FLUX_Ctrl.TAB_FLUX_Gamma_Coeff.n = 10U,

    .FLUX_Ctrl.TAB_FLUX_Kp_Coeff.x = F_Table_Freq,
    .FLUX_Ctrl.TAB_FLUX_Kp_Coeff.y = F_Table_FLUX_PLL_Kp_Coeff,
    .FLUX_Ctrl.TAB_FLUX_Kp_Coeff.n = 10U,

    .FLUX_Ctrl.TAB_FLUX_Ki_Coeff.x = F_Table_Freq,
    .FLUX_Ctrl.TAB_FLUX_Ki_Coeff.y = F_Table_FLUX_PLL_Ki_Coeff,
    .FLUX_Ctrl.TAB_FLUX_Ki_Coeff.n = 10U,

    .FLUX_Ctrl.TAB_FLUX_Angle_Comp.x = F_Table_Freq,
    .FLUX_Ctrl.TAB_FLUX_Angle_Comp.y = F_Table_Current,
    .FLUX_Ctrl.TAB_FLUX_Angle_Comp.z = F_Table_FLUX_Angle,
    .FLUX_Ctrl.TAB_FLUX_Angle_Comp.nx = 10U,
    .FLUX_Ctrl.TAB_FLUX_Angle_Comp.ny = 5U,


    .Motor_Error.P_Q32U_MOS_Error_Count = MOS_ERROR_COUNT,
    
    .Motor_Error.Over_Voltage.P_Q14I_Check_TL = OVER_VOLTAGE_PROTECT_LEVEL_TL,
    .Motor_Error.Over_Voltage.P_Q32U_Check_Time = OVER_VOLTAGE_PROTECT_LEVEL_TIME,
    .Motor_Error.Over_Voltage.P_Q14I_Clear_TL = OVER_VOLTAGE_CLEAR_LEVEL_TL,
    .Motor_Error.Over_Voltage.P_Q32U_Clear_Time = OVER_VOLTAGE_CLEAR_LEVEL_TIME,
    .Motor_Error.Over_Voltage.P_Q32U_Check_Count = 1U,
    .Motor_Error.Over_Voltage.Check_Flag.bit.Clear_Mode = 0U,
    
    .Motor_Error.Low_Voltage.P_Q14I_Check_TL = LOW_VOLTAGE_PROTECT_LEVEL_TL,
    .Motor_Error.Low_Voltage.P_Q32U_Check_Time = LOW_VOLTAGE_PROTECT_LEVEL_TIME,
    .Motor_Error.Low_Voltage.P_Q14I_Clear_TL = 0,
    .Motor_Error.Low_Voltage.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Low_Voltage.P_Q32U_Check_Count = 1U,
    .Motor_Error.Low_Voltage.Check_Flag.bit.Clear_Mode = 0U,
    
    .Motor_Error.Over_Current1.P_Q14I_Check_TL = CURRENT_PROTECT_LEVEL_1_TL,
    .Motor_Error.Over_Current1.P_Q32U_Check_Time = CURRENT_PROTECT_LEVEL_1_TIME,
    .Motor_Error.Over_Current1.P_Q14I_Clear_TL = 0,
    .Motor_Error.Over_Current1.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Over_Current1.P_Q32U_Check_Count = 1000U,
    .Motor_Error.Over_Current1.Check_Flag.bit.Clear_Mode = 1U,
    
    .Motor_Error.Over_Current2.P_Q14I_Check_TL = CURRENT_PROTECT_LEVEL_2_TL,
    .Motor_Error.Over_Current2.P_Q32U_Check_Time = CURRENT_PROTECT_LEVEL_2_TIME,
    .Motor_Error.Over_Current2.P_Q14I_Clear_TL = 0,
    .Motor_Error.Over_Current2.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Over_Current2.P_Q32U_Check_Count = 100U,
    .Motor_Error.Over_Current2.Check_Flag.bit.Clear_Mode = 1U,
    
    .Motor_Error.Over_Current3.P_Q14I_Check_TL = CURRENT_PROTECT_LEVEL_3_TL,
    .Motor_Error.Over_Current3.P_Q32U_Check_Time = CURRENT_PROTECT_LEVEL_3_TIME,
    .Motor_Error.Over_Current3.P_Q14I_Clear_TL = 0,
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
    .Motor_Error.Over_Ibus.P_Q14I_Clear_TL = 0,
    .Motor_Error.Over_Ibus.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Over_Ibus.P_Q32U_Check_Count = 10U,
    .Motor_Error.Over_Ibus.Check_Flag.bit.Clear_Mode = 1U,
 
    .Motor_Error.Phase_Lack_A.P_Q14I_Check_TL = PHASE_LACK_IPHASE_PROTECT_LEVEL_TL,
    .Motor_Error.Phase_Lack_A.P_Q32U_Check_Time = PHASE_LACK_PROTECT_LEVEL_TIME,
    .Motor_Error.Phase_Lack_A.P_Q14I_Clear_TL = PHASE_LACK_ISREF_PROTECT_LEVEL_TL,
    .Motor_Error.Phase_Lack_A.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Phase_Lack_A.P_Q32U_Check_Count = 10U,
    .Motor_Error.Phase_Lack_A.Check_Flag.bit.Clear_Mode = 1U,
    
    .Motor_Error.Phase_Lack_B.P_Q14I_Check_TL = PHASE_LACK_IPHASE_PROTECT_LEVEL_TL,
    .Motor_Error.Phase_Lack_B.P_Q32U_Check_Time = PHASE_LACK_PROTECT_LEVEL_TIME,
    .Motor_Error.Phase_Lack_B.P_Q14I_Clear_TL = PHASE_LACK_ISREF_PROTECT_LEVEL_TL,
    .Motor_Error.Phase_Lack_B.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Phase_Lack_B.P_Q32U_Check_Count = 10U,
    .Motor_Error.Phase_Lack_B.Check_Flag.bit.Clear_Mode = 1U,
    
    .Motor_Error.Phase_Lack_C.P_Q14I_Check_TL = PHASE_LACK_IPHASE_PROTECT_LEVEL_TL,
    .Motor_Error.Phase_Lack_C.P_Q32U_Check_Time = PHASE_LACK_PROTECT_LEVEL_TIME,
    .Motor_Error.Phase_Lack_C.P_Q14I_Clear_TL = PHASE_LACK_ISREF_PROTECT_LEVEL_TL,
    .Motor_Error.Phase_Lack_C.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Phase_Lack_C.P_Q32U_Check_Count = 10U,
    .Motor_Error.Phase_Lack_C.Check_Flag.bit.Clear_Mode = 1U,
    
    .Motor_Error.Rotor_Lock.P_Q14I_Check_TL = ROTOR_LOCK_ISREF_PROTECT_LEVEL_TL,
    .Motor_Error.Rotor_Lock.P_Q32U_Check_Time = ROTOR_LOCK_PROTECT_LEVEL_TIME,
    .Motor_Error.Rotor_Lock.P_Q14I_Clear_TL = ROTOR_LOCK_SPEED_PROTECT_LEVEL_TL,
    .Motor_Error.Rotor_Lock.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Rotor_Lock.P_Q32U_Check_Count = 10U,
    .Motor_Error.Rotor_Lock.Check_Flag.bit.Clear_Mode = 1U,
    
    .Motor_Error.Loss_Step.P_Q14I_Check_TL = LOSS_STEP_ES_PROTECT_LEVEL_TL,
    .Motor_Error.Loss_Step.P_Q32U_Check_Time = LOSS_STEP_PROTECT_LEVEL_TIME,
    .Motor_Error.Loss_Step.P_Q14I_Clear_TL = LOSS_STEP_SPEED_PROTECT_LEVEL_TL,
    .Motor_Error.Loss_Step.P_Q32U_Clear_Time = 0U,
    .Motor_Error.Loss_Step.P_Q32U_Check_Count = 10U,
    .Motor_Error.Loss_Step.Check_Flag.bit.Clear_Mode = 1U,
    
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


//电机参数索引
float F_Table_Current[5] =
{
    0.20f,  0.40f,  0.60f,  0.80f,  1.00f
};
float F_Table_Freq[10] =
{
    0.00f,  0.05f,  0.10f,  0.20f,  0.30f,  0.40f,  0.50f,  0.60f,  0.80f,  1.00f
};


//转速环参数查表
float F_Table_Freq_Kp_Coeff[10] =
{
    0.10f,  0.10f,  0.20f,  0.20f,  0.30f,  0.40f,  0.50f,  0.60f,  0.80f,  1.00f
};
float F_Table_Freq_Ki_Coeff[10] =
{
    0.05f,  0.05f,  0.10f,  0.20f,  0.30f,  0.40f,  0.50f,  0.60f,  0.80f,  1.00f
};
//Q轴电感查表
float F_Table_Lq_Coeff[10] =
{
    1.00f,  1.00f,  1.00f,  1.00f,  1.00f
};

//SMO观测器参数查表
float F_Table_SMO_H1_Coeff[10] =
{
    1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f
};
float F_Table_SMO_PLL_Kp_Coeff[10] =
{
    1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f
};
float F_Table_SMO_PLL_Ki_Coeff[10] =
{
    1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f
};
float F_Table_SMO_Angle[50] =
{
    0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
    0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
    0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
    0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
    0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
};

//磁链观测器参数查表
float F_Table_FLUX_Gamma_Coeff[10] =
{
    1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f
};
float F_Table_FLUX_PLL_Kp_Coeff[10] =
{
    1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f
};
float F_Table_FLUX_PLL_Ki_Coeff[10] =
{
    1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f,  1.00f
};
float F_Table_FLUX_Angle[50] =
{
    0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
    0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
    0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
    0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
    0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
};


/*-------------------------- 3. 公有接口实现 -----------------------------*/
void Motor_Parameter_API_F(ST_MCFOC_TASK_F* pMotor)
{
    if(pMotor->Motor_Flag.bit.motor_target_dir == 1U)
    {
        pMotor->PMSM_Elec.I_F_DIR_Target = 1.0f;
    }
    else
    {
        pMotor->PMSM_Elec.I_F_DIR_Target = -1.0f;
    }
    
    if(pMotor->PMSM_Elec.O_F_Freq >= 0.0f)
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
    
    pMotor->Freq_Ctrl.I_F_FREQ_Target = (float)pMotor->Motor_API.Target_Speed_pu / 16384.0f;
    pMotor->Motor_API.Real_Speed_pu = (Q32I_)(pMotor->PMSM_Elec.O_F_Freq * 16384.0f);
    pMotor->Motor_API.Real_Iphase_pu = (Q32I_)(pMotor->PMSM_Elec.O_F_Is * 16384.0f);
    pMotor->Motor_API.Real_Ibus_pu = (Q32I_)(pMotor->PMSM_Elec.O_F_Ibus_10ms * 16384.0f);
}
