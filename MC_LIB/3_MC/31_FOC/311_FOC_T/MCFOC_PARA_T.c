/**************************************************************************************************
*     File Name :                        MCFOC_PARA_T.c
*     Library/Module Name :              MCFOC_T
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制参数初始化源文件
**************************************************************************************************/

#include "MCFOC_PARA_T.h"


extern Q32I_ Q14I_Table_Freq[10];
extern Q32I_ Q14I_Table_Current[5];
extern Q32I_ Q14I_Table_Voltage[5];
extern Q32I_ Q14I_Table_Freq_Kp_Coeff[10];
extern Q32I_ Q14I_Table_Freq_Ki_Coeff[10];
extern Q32I_ Q14I_Table_Ibus_Coeff[50];
extern Q32I_ Q14I_Table_Lq_Coeff[10];
extern Q32I_ Q14I_Table_SMO_H1_Coeff[10];
extern Q32I_ Q14I_Table_SMO_PLL_Kp_Coeff[10];
extern Q32I_ Q14I_Table_SMO_PLL_Ki_Coeff[10];
extern Q32I_ Q14I_Table_SMO_Angle[50];
extern Q32I_ Q14I_Table_FLUX_Gamma_Coeff[10];
extern Q32I_ Q14I_Table_FLUX_PLL_Kp_Coeff[10];
extern Q32I_ Q14I_Table_FLUX_PLL_Ki_Coeff[10];
extern Q32I_ Q14I_Table_FLUX_Angle[50];

ST_MOTOR_TASK  Motor_T = 
{
    .PMSM_FILTER_CTRL.Mean_Freq.Q32U_MEAN_Num = 16U,
    .PMSM_FILTER_CTRL.Mean_Vbus.Q32U_MEAN_Num = 16U,
    .PMSM_FILTER_CTRL.Mean_Ibus.Q32U_MEAN_Num = 16U,
    .PMSM_FILTER_CTRL.Mean_Id.Q32U_MEAN_Num = 16U,
    .PMSM_FILTER_CTRL.Mean_Iq.Q32U_MEAN_Num = 16U,
    .PMSM_FILTER_CTRL.Mean_Ud.Q32U_MEAN_Num = 16U,
    .PMSM_FILTER_CTRL.Mean_Uq.Q32U_MEAN_Num = 16U,
    .PMSM_FILTER_CTRL.Mean_Es.Q32U_MEAN_Num = 16U,
    .PMSM_FILTER_CTRL.Mean_Freq.Q32U_MEAN_Bit = 4U,
    .PMSM_FILTER_CTRL.Mean_Vbus.Q32U_MEAN_Bit = 4U,
    .PMSM_FILTER_CTRL.Mean_Ibus.Q32U_MEAN_Bit = 4U,
    .PMSM_FILTER_CTRL.Mean_Id.Q32U_MEAN_Bit = 4U,
    .PMSM_FILTER_CTRL.Mean_Iq.Q32U_MEAN_Bit = 4U,
    .PMSM_FILTER_CTRL.Mean_Ud.Q32U_MEAN_Bit = 4U,
    .PMSM_FILTER_CTRL.Mean_Uq.Q32U_MEAN_Bit = 4U,
    .PMSM_FILTER_CTRL.Mean_Es.Q32U_MEAN_Bit = 4U,
    
    .PMSM_FILTER_CTRL.Max_Ia.Q32U_MAX_Num = 16U,
    .PMSM_FILTER_CTRL.Max_Ib.Q32U_MAX_Num = 16U,
    .PMSM_FILTER_CTRL.Max_Ic.Q32U_MAX_Num = 16U,

    .PMSM_FILTER_CTRL.Mean_Ibus_10ms.Q32U_MEAN_Num = 10U,
    .PMSM_FILTER_CTRL.Mean_Is_1000ms.Q32U_MEAN_Num = 10U,


    .PMSM_ELEC_CTRL._P_Q14I_Modulation_Mode = (Q32I_)(0.666667f*16384.0f),
    .PMSM_ELEC_CTRL._P_Q14I_UsRef_Scale = (Q32I_)(1.01f*16384.0f),
    .PMSM_ELEC_CTRL._P_Q08U_Pre_Period = (Q32I_)(1.0f*256.0f),


    .PMSM_PARA_CTRL.Ramp_PWM_FREQ.Q28I_ADDStep = 16384,
    .PMSM_PARA_CTRL.Ramp_PWM_FREQ.Q28I_SUBStep = -16384,
    .PMSM_PARA_CTRL.Ramp_PWM_FREQ.Q14I_Output = MOTOR_PWM_FREQ_LOW,
    .PMSM_PARA_CTRL.Ramp_PWM_FREQ.Q28I_Output_tmp = MOTOR_PWM_FREQ_LOW*16384,
    .PMSM_PARA_CTRL._P_Q32U_PWM_FREQ_MAX = MOTOR_PWM_FREQ_HIGH,
    .PMSM_PARA_CTRL._P_Q32U_PWM_FREQ_MIN = MOTOR_PWM_FREQ_LOW,
    
    .PMSM_PARA_CTRL.PWM_FREQ_CHECK._P_Q14I_Check_TL = MOTOR_PWM_FREQ_TL,
    .PMSM_PARA_CTRL.PWM_FREQ_CHECK._P_Q32U_Check_Time = 100U,
    .PMSM_PARA_CTRL.PWM_FREQ_CHECK._P_Q14I_Clear_TL = MOTOR_PWM_FREQ_CLR,
    .PMSM_PARA_CTRL.PWM_FREQ_CHECK._P_Q32U_Clear_Time = 100U,
    .PMSM_PARA_CTRL.PWM_FREQ_CHECK.Check_Flag.bit.Clear_Mode = 0U,

    .PMSM_PARA_CTRL._P_Q14I_Rs = Q14I_Rs_PU,
    .PMSM_PARA_CTRL._P_Q14I_Ld = Q14I_Ld_PU,
    .PMSM_PARA_CTRL._P_Q14I_Lq = Q14I_Lq_PU,
    .PMSM_PARA_CTRL._P_Q14I_Ls = Q14I_Ls_PU,
    .PMSM_PARA_CTRL._P_Q14I_Flux = Q14I_FLUX_PU,
    .PMSM_PARA_CTRL._P_Q14I_Ts = Q14I_HTs_PU,

    .PMSM_PARA_CTRL.TAB_Lq_Coeff.x = Q14I_Table_Current,
    .PMSM_PARA_CTRL.TAB_Lq_Coeff.y = Q14I_Table_Lq_Coeff,
    .PMSM_PARA_CTRL.TAB_Lq_Coeff.n = 5U,
    

    .MCFOC_OFFSET._P_Q12U_Offset_Max = CURRENT_OFFSET_MAX_lsb,
    .MCFOC_OFFSET._P_Q12U_Offset_Min = CURRENT_OFFSET_MIN_lsb,
    .MCFOC_OFFSET._P_Q16U_Offset_Check_Count = CURRENT_OFFSET_NUM,
	

    .ALIGN_CTRL.Ramp_Align_Id.Q14I_Target = MOTOR_ALIGN_ID_TARGET,
    .ALIGN_CTRL.Ramp_Align_Id.Q28I_ADDStep = MOTOR_ALIGN_IDRAMP_ADDSTEP,
    .ALIGN_CTRL.Ramp_Align_Angle.Q28I_ADDStep = MOTOR_ALIGN_ANGLERAMP_ADDSTEP,
    .ALIGN_CTRL._P_Q32U_Align_Check_Count = MOTOR_ALIGN_COUNT,


    .IF_CTRL.Ramp_IF_Iq.Q28I_ADDStep = MOTOR_IF_IQRAMP_ADDSTEP,
    .IF_CTRL.Ramp_IF_Iq.Q28I_SUBStep = MOTOR_IF_IQRAMP_SUBSTEP,
    .IF_CTRL.Ramp_IF_FREQ.Q14I_Target = MOTOR_IF_FREQRAMP_TARGET,
    .IF_CTRL.Ramp_IF_FREQ.Q28I_ADDStep = MOTOR_IF_FREQRAMP_ADDSTEP,

    .IF_CTRL._P_Q14I_IF_Iq_Target = MOTOR_IF_IQ_TARGET,
    .IF_CTRL._P_Q14I_IF_Is_Min = MOTOR_IF_IS_MIN,
    .IF_CTRL._P_Q14I_IF_Iq_Min = MOTOR_IF_IQ_MIN,
    .IF_CTRL._P_Q14I_IF_Angle_Err_Limit = MOTOR_IF_ANGLE_ERROR,
    .IF_CTRL._P_Q32U_IF_Angle_Err_Check_Count = MOTOR_IF_SWITCH_COUNT,
    

    .FREQ_CTRL.PID_POWER.Q14I_Kp = (Q32I_)(0.01f*16384.0f),
    .FREQ_CTRL.PID_POWER.Q14I_Ki = (Q32I_)(0.01f*16384.0f),
    .FREQ_CTRL.PID_POWER.Q14I_Kd = (Q32I_)(0.0f*16384.0f),
    .FREQ_CTRL.PID_POWER.Q14I_Kc = (Q32I_)(0.01f*16384.0f),
    .FREQ_CTRL.PID_POWER.Q14I_OutMax = (Q32I_)(1.0f*16384.0f),
    .FREQ_CTRL.PID_POWER.Q14I_OutMin = (Q32I_)(0.1f*16384.0f),

    .FREQ_CTRL._P_Q14I_FREQ_Kp = MOTOR_FREQ_KP_GAIN,
    .FREQ_CTRL._P_Q14I_FREQ_Ki = MOTOR_FREQ_KI_GAIN,
    .FREQ_CTRL.PID_FREQ.Q14I_Kd = MOTOR_FREQ_KD_GAIN,
    .FREQ_CTRL.PID_FREQ.Q14I_Kc = (Q32I_)(0.01f*16384.0f),
    .FREQ_CTRL.PID_FREQ.Q14I_OutMax = MOTOR_FREQ_PID_MAX,
    .FREQ_CTRL.PID_FREQ.Q14I_OutMin = MOTOR_FREQ_PID_MIN,
    .FREQ_CTRL.TAB_FREQ_Kp_Coeff.x = Q14I_Table_Freq,
    .FREQ_CTRL.TAB_FREQ_Kp_Coeff.y = Q14I_Table_Freq_Kp_Coeff,
    .FREQ_CTRL.TAB_FREQ_Kp_Coeff.n = 10U,
    .FREQ_CTRL.TAB_FREQ_Ki_Coeff.x = Q14I_Table_Freq,
    .FREQ_CTRL.TAB_FREQ_Ki_Coeff.y = Q14I_Table_Freq_Ki_Coeff,
    .FREQ_CTRL.TAB_FREQ_Ki_Coeff.n = 10U,

    .FREQ_CTRL.PID_WEAK.Q14I_Kp = (Q32I_)(0.01f*16384.0f),
    .FREQ_CTRL.PID_WEAK.Q14I_Ki = (Q32I_)(0.01f*16384.0f),
    .FREQ_CTRL.PID_WEAK.Q14I_Kd = (Q32I_)(0.0f*16384.0f),
    .FREQ_CTRL.PID_WEAK.Q14I_Kc = (Q32I_)(0.01f*16384.0f),
    .FREQ_CTRL.PID_WEAK.Q14I_OutMax = (Q32I_)(0.0f*16384.0f),
    .FREQ_CTRL.PID_WEAK.Q14I_OutMin = (Q32I_)(-0.125f*16384.0f),

    .FREQ_CTRL.Ramp_FREQ.Q28I_ADDStep = MOTOR_FREQ_RAMP_ADDSTEP,
    .FREQ_CTRL.Ramp_FREQ.Q28I_SUBStep = MOTOR_FREQ_RAMP_SUBSTEP,
    
    .FREQ_CTRL.WEAK_CHECK._P_Q14I_Check_TL = (Q32I_)(0.95f*16384.0f),
    .FREQ_CTRL.WEAK_CHECK._P_Q32U_Check_Time = 100U,
    .FREQ_CTRL.WEAK_CHECK._P_Q14I_Clear_TL = (Q32I_)(0.90f*16384.0f),
    .FREQ_CTRL.WEAK_CHECK._P_Q32U_Clear_Time = 2000U,
    .FREQ_CTRL.WEAK_CHECK._P_Q32U_Check_Count = 10U,
    .FREQ_CTRL.WEAK_CHECK.Check_Flag.bit.Clear_Mode = 1U,
    .FREQ_CTRL._P_Q14I_FREQ_PowerRef = (Q32I_)(1.0f*16384.0f),
    .FREQ_CTRL._P_Q14I_FREQ_IbusRef = (Q32I_)(1.0f*16384.0f),


    .CURRENT_CTRL.PID_Id.Q14I_Kp = MOTOR_CURRENT_KP_GAIN,
    .CURRENT_CTRL.PID_Id.Q14I_Ki = MOTOR_CURRENT_KI_GAIN,
    .CURRENT_CTRL.PID_Id.Q14I_Kd = MOTOR_CURRENT_KD_GAIN,
    .CURRENT_CTRL.PID_Id.Q14I_Kc = (Q32I_)(0.01f*16384.0f),

    .CURRENT_CTRL.PID_Iq.Q14I_Kp = MOTOR_CURRENT_KP_GAIN,
    .CURRENT_CTRL.PID_Iq.Q14I_Ki = MOTOR_CURRENT_KI_GAIN,
    .CURRENT_CTRL.PID_Iq.Q14I_Kd = MOTOR_CURRENT_KD_GAIN,
    .CURRENT_CTRL.PID_Iq.Q14I_Kc = (Q32I_)(0.01f*16384.0f),
    

    .SVPWM_CTRL._P_Q14U_MaxDuty = (Q32I_)(HAL_MAX_DUTY*16384.0f),
    .SVPWM_CTRL._P_Q14U_MidDuty = (Q32I_)(HAL_MID_DUTY*16384.0f),
    .SVPWM_CTRL._P_Q14U_MinDuty = (Q32I_)(HAL_MIN_DUTY*16384.0f),
    .SVPWM_CTRL._P_Q14U_ADCSampleDuty = (Q32I_)(HAL_ADC_SAMPLE_DUTY*16384.0f),
    .SVPWM_CTRL._P_Q32U_PWM_All_Count = (Q32I_)HAL_PWM_ALL_COUNT_F,
    .SVPWM_CTRL._P_Q14U_DeadTimeDuty = (Q32I_)(0.0f*16384.0f),
    .SVPWM_CTRL._P_Q14I_DT_Current_TL = (Q32I_)(0.0f*16384.0f),
    
    .SVPWM_CTRL.FIVE_CHECK._P_Q14I_Check_TL = (Q32I_)(0.75f*16384.0f),
    .SVPWM_CTRL.FIVE_CHECK._P_Q32U_Check_Time = 100U,
    .SVPWM_CTRL.FIVE_CHECK._P_Q14I_Clear_TL = (Q32I_)(0.50f*16384.0f),
    .SVPWM_CTRL.FIVE_CHECK._P_Q32U_Clear_Time = 100U,
    .SVPWM_CTRL.FIVE_CHECK._P_Q32U_Check_Count = 10U,
    .SVPWM_CTRL.FIVE_CHECK.Check_Flag.bit.Clear_Mode = 1U,


    .EMF_CTRL.FL_EMF_Ialfa_err.Q14I_LPF_Coeff = (Q32I_)(0.0025f*16384.0f),
    .EMF_CTRL.FL_EMF_Ibeta_err.Q14I_LPF_Coeff = (Q32I_)(0.0025f*16384.0f),


    .SMO_CTRL.PID_SMO_PLL.Q14I_Kd = MOTOR_SMO_PLL_KD,
    .SMO_CTRL.PID_SMO_PLL.Q14I_OutMax = MOTOR_SMO_PLL_MAX,
    .SMO_CTRL.PID_SMO_PLL.Q14I_OutMin = MOTOR_SMO_PLL_MIN,
    .SMO_CTRL.FL_SMO_FREQ.Q14I_LPF_Coeff = MOTOR_PLL_SPEED_LPF_COEFF,

    .SMO_CTRL._P_Q14I_SMO_H1 = MOTOR_SMO_H1,
    .SMO_CTRL._P_Q14I_SMO_PLL_Kp = MOTOR_SMO_PLL_KP,
    .SMO_CTRL._P_Q14I_SMO_PLL_Ki = MOTOR_SMO_PLL_KI,

    .SMO_CTRL.TAB_SMO_Kp_Coeff.x = Q14I_Table_Freq,
    .SMO_CTRL.TAB_SMO_Kp_Coeff.y = Q14I_Table_SMO_H1_Coeff,
    .SMO_CTRL.TAB_SMO_Kp_Coeff.n = 10U,

    .SMO_CTRL.TAB_SMO_H1_Coeff.x = Q14I_Table_Freq,
    .SMO_CTRL.TAB_SMO_H1_Coeff.y = Q14I_Table_SMO_PLL_Kp_Coeff,
    .SMO_CTRL.TAB_SMO_H1_Coeff.n = 10U,

    .SMO_CTRL.TAB_SMO_Ki_Coeff.x = Q14I_Table_Freq,
    .SMO_CTRL.TAB_SMO_Ki_Coeff.y = Q14I_Table_SMO_PLL_Ki_Coeff,
    .SMO_CTRL.TAB_SMO_Ki_Coeff.n = 10U,

    .SMO_CTRL.TAB_SMO_Angle_Comp.x = Q14I_Table_Freq,
    .SMO_CTRL.TAB_SMO_Angle_Comp.y = Q14I_Table_Current,
    .SMO_CTRL.TAB_SMO_Angle_Comp.z = Q14I_Table_SMO_Angle,
    .SMO_CTRL.TAB_SMO_Angle_Comp.nx = 10U,
    .SMO_CTRL.TAB_SMO_Angle_Comp.ny = 5U,
    

    .FLUX_CTRL.PID_FLUX_PLL.Q14I_Kd = MOTOR_FLUX_PLL_KD,
    .FLUX_CTRL.PID_FLUX_PLL.Q14I_OutMax = MOTOR_FLUX_PLL_MAX,
    .FLUX_CTRL.PID_FLUX_PLL.Q14I_OutMin = MOTOR_FLUX_PLL_MIN,
    .FLUX_CTRL.FL_FLUX_FREQ.Q14I_LPF_Coeff = MOTOR_PLL_SPEED_LPF_COEFF,

    .FLUX_CTRL._P_Q14I_FLUX_Gamma = MOTOR_FLUX_GAMMA,
    .FLUX_CTRL._P_Q14I_FLUX_PLL_Kp = MOTOR_FLUX_PLL_KP,
    .FLUX_CTRL._P_Q14I_FLUX_PLL_Ki = MOTOR_FLUX_PLL_KI,

    .FLUX_CTRL.TAB_FLUX_Gamma_Coeff.x = Q14I_Table_Freq,
    .FLUX_CTRL.TAB_FLUX_Gamma_Coeff.y = Q14I_Table_FLUX_Gamma_Coeff,
    .FLUX_CTRL.TAB_FLUX_Gamma_Coeff.n = 10U,

    .FLUX_CTRL.TAB_FLUX_Kp_Coeff.x = Q14I_Table_Freq,
    .FLUX_CTRL.TAB_FLUX_Kp_Coeff.y = Q14I_Table_FLUX_PLL_Kp_Coeff,
    .FLUX_CTRL.TAB_FLUX_Kp_Coeff.n = 10U,

    .FLUX_CTRL.TAB_FLUX_Ki_Coeff.x = Q14I_Table_Freq,
    .FLUX_CTRL.TAB_FLUX_Ki_Coeff.y = Q14I_Table_FLUX_PLL_Ki_Coeff,
    .FLUX_CTRL.TAB_FLUX_Ki_Coeff.n = 10U,

    .FLUX_CTRL.TAB_FLUX_Angle_Comp.x = Q14I_Table_Freq,
    .FLUX_CTRL.TAB_FLUX_Angle_Comp.y = Q14I_Table_Current,
    .FLUX_CTRL.TAB_FLUX_Angle_Comp.z = Q14I_Table_FLUX_Angle,
    .FLUX_CTRL.TAB_FLUX_Angle_Comp.nx = 10U,
    .FLUX_CTRL.TAB_FLUX_Angle_Comp.ny = 5U,


    .MC_ERR._P_Q32U_MOS_Error_Count = MOS_ERROR_COUNT,
    
    .MC_ERR.Over_Voltage._P_Q14I_Check_TL = OVER_VOLTAGE_PROTECT_LEVEL_TL,
    .MC_ERR.Over_Voltage._P_Q32U_Check_Time = OVER_VOLTAGE_PROTECT_LEVEL_TIME,
    .MC_ERR.Over_Voltage._P_Q14I_Clear_TL = OVER_VOLTAGE_CLEAR_LEVEL_TL,
    .MC_ERR.Over_Voltage._P_Q32U_Clear_Time = OVER_VOLTAGE_CLEAR_LEVEL_TIME,
    .MC_ERR.Over_Voltage._P_Q32U_Check_Count = 1U,
    .MC_ERR.Over_Voltage.Check_Flag.bit.Clear_Mode = 0U,
    
    .MC_ERR.Low_Voltage._P_Q14I_Check_TL = LOW_VOLTAGE_PROTECT_LEVEL_TL,
    .MC_ERR.Low_Voltage._P_Q32U_Check_Time = LOW_VOLTAGE_PROTECT_LEVEL_TIME,
    .MC_ERR.Low_Voltage._P_Q14I_Clear_TL = 0,
    .MC_ERR.Low_Voltage._P_Q32U_Clear_Time = 0U,
    .MC_ERR.Low_Voltage._P_Q32U_Check_Count = 1U,
    .MC_ERR.Low_Voltage.Check_Flag.bit.Clear_Mode = 0U,
    
    .MC_ERR.Over_Current1._P_Q14I_Check_TL = CURRENT_PROTECT_LEVEL_1_TL,
    .MC_ERR.Over_Current1._P_Q32U_Check_Time = CURRENT_PROTECT_LEVEL_1_TIME,
    .MC_ERR.Over_Current1._P_Q14I_Clear_TL = 0,
    .MC_ERR.Over_Current1._P_Q32U_Clear_Time = 0U,
    .MC_ERR.Over_Current1._P_Q32U_Check_Count = 1000U,
    .MC_ERR.Over_Current1.Check_Flag.bit.Clear_Mode = 1U,
    
    .MC_ERR.Over_Current2._P_Q14I_Check_TL = CURRENT_PROTECT_LEVEL_2_TL,
    .MC_ERR.Over_Current2._P_Q32U_Check_Time = CURRENT_PROTECT_LEVEL_2_TIME,
    .MC_ERR.Over_Current2._P_Q14I_Clear_TL = 0,
    .MC_ERR.Over_Current2._P_Q32U_Clear_Time = 0U,
    .MC_ERR.Over_Current2._P_Q32U_Check_Count = 100U,
    .MC_ERR.Over_Current2.Check_Flag.bit.Clear_Mode = 1U,
    
    .MC_ERR.Over_Current3._P_Q14I_Check_TL = CURRENT_PROTECT_LEVEL_3_TL,
    .MC_ERR.Over_Current3._P_Q32U_Check_Time = CURRENT_PROTECT_LEVEL_3_TIME,
    .MC_ERR.Over_Current3._P_Q14I_Clear_TL = 0,
    .MC_ERR.Over_Current3._P_Q32U_Clear_Time = 0U,
    .MC_ERR.Over_Current3._P_Q32U_Check_Count = 10U,
    .MC_ERR.Over_Current3.Check_Flag.bit.Clear_Mode = 1U,
    
    .MC_ERR.Over_Temp._P_Q14I_Check_TL = OVER_TEMP_PROTECT_LEVEL_TL,
    .MC_ERR.Over_Temp._P_Q32U_Check_Time = OVER_TEMP_PROTECT_LEVEL_TIME,
    .MC_ERR.Over_Temp._P_Q14I_Clear_TL = OVER_TEMP_CLEAR_LEVEL_TL,
    .MC_ERR.Over_Temp._P_Q32U_Clear_Time = OVER_TEMP_CLEAR_LEVEL_TIME,
    .MC_ERR.Over_Temp._P_Q32U_Check_Count = 1U,
    .MC_ERR.Over_Temp.Check_Flag.bit.Clear_Mode = 0U,
    
    .MC_ERR.Low_Temp._P_Q14I_Check_TL = LOW_TEMP_PROTECT_LEVEL_TL,
    .MC_ERR.Low_Temp._P_Q32U_Check_Time = LOW_TEMP_PROTECT_LEVEL_TIME,
    .MC_ERR.Low_Temp._P_Q14I_Clear_TL = LOW_TEMP_CLEAR_LEVEL_TL,
    .MC_ERR.Low_Temp._P_Q32U_Clear_Time = LOW_TEMP_CLEAR_LEVEL_TIME,
    .MC_ERR.Low_Temp._P_Q32U_Check_Count = 1U,
    .MC_ERR.Low_Temp.Check_Flag.bit.Clear_Mode = 0U,
    
    .MC_ERR.Over_Speed._P_Q14I_Check_TL = OVER_SPEED_PROTECT_LEVEL_TL,
    .MC_ERR.Over_Speed._P_Q32U_Check_Time = OVER_SPEED_PROTECT_LEVEL_TIME,
    .MC_ERR.Over_Speed._P_Q14I_Clear_TL = 0U,
    .MC_ERR.Over_Speed._P_Q32U_Clear_Time = 0U,
    .MC_ERR.Over_Speed._P_Q32U_Check_Count = 1U,
    .MC_ERR.Over_Speed.Check_Flag.bit.Clear_Mode = 0U,
    
    .MC_ERR.Low_Speed._P_Q14I_Check_TL = LOW_SPEED_PROTECT_LEVEL_TL,
    .MC_ERR.Low_Speed._P_Q32U_Check_Time = LOW_SPEED_PROTECT_LEVEL_TIME,
    .MC_ERR.Low_Speed._P_Q14I_Clear_TL = 0U,
    .MC_ERR.Low_Speed._P_Q32U_Clear_Time = 0U,
    .MC_ERR.Low_Speed._P_Q32U_Check_Count = 1U,
    .MC_ERR.Low_Speed.Check_Flag.bit.Clear_Mode = 0U,
    
    .MC_ERR.Over_Power._P_Q14I_Check_TL = OVER_POWER_PROTECT_LEVEL_TL,
    .MC_ERR.Over_Power._P_Q32U_Check_Time = OVER_POWER_PROTECT_LEVEL_TIME,
    .MC_ERR.Over_Power._P_Q14I_Clear_TL = 0U,
    .MC_ERR.Over_Power._P_Q32U_Clear_Time = 0U,
    .MC_ERR.Over_Power._P_Q32U_Check_Count = 10U,
    .MC_ERR.Over_Power.Check_Flag.bit.Clear_Mode = 1U,
    
    .MC_ERR.Over_Ibus._P_Q14I_Check_TL = OVER_IBUS_PROTECT_LEVEL_TL,
    .MC_ERR.Over_Ibus._P_Q32U_Check_Time = OVER_IBUS_PROTECT_LEVEL_TIME,
    .MC_ERR.Over_Ibus._P_Q14I_Clear_TL = 0,
    .MC_ERR.Over_Ibus._P_Q32U_Clear_Time = 0U,
    .MC_ERR.Over_Ibus._P_Q32U_Check_Count = 10U,
    .MC_ERR.Over_Ibus.Check_Flag.bit.Clear_Mode = 1U,
 
    .MC_ERR.Phase_Lack_A._P_Q14I_Check_TL = PHASE_LACK_IPHASE_PROTECT_LEVEL_TL,
    .MC_ERR.Phase_Lack_A._P_Q32U_Check_Time = PHASE_LACK_PROTECT_LEVEL_TIME,
    .MC_ERR.Phase_Lack_A._P_Q14I_Clear_TL = PHASE_LACK_ISREF_PROTECT_LEVEL_TL,
    .MC_ERR.Phase_Lack_A._P_Q32U_Clear_Time = 0U,
    .MC_ERR.Phase_Lack_A._P_Q32U_Check_Count = 10U,
    .MC_ERR.Phase_Lack_A.Check_Flag.bit.Clear_Mode = 1U,
    
    .MC_ERR.Phase_Lack_B._P_Q14I_Check_TL = PHASE_LACK_IPHASE_PROTECT_LEVEL_TL,
    .MC_ERR.Phase_Lack_B._P_Q32U_Check_Time = PHASE_LACK_PROTECT_LEVEL_TIME,
    .MC_ERR.Phase_Lack_B._P_Q14I_Clear_TL = PHASE_LACK_ISREF_PROTECT_LEVEL_TL,
    .MC_ERR.Phase_Lack_B._P_Q32U_Clear_Time = 0U,
    .MC_ERR.Phase_Lack_B._P_Q32U_Check_Count = 10U,
    .MC_ERR.Phase_Lack_B.Check_Flag.bit.Clear_Mode = 1U,
    
    .MC_ERR.Phase_Lack_C._P_Q14I_Check_TL = PHASE_LACK_IPHASE_PROTECT_LEVEL_TL,
    .MC_ERR.Phase_Lack_C._P_Q32U_Check_Time = PHASE_LACK_PROTECT_LEVEL_TIME,
    .MC_ERR.Phase_Lack_C._P_Q14I_Clear_TL = PHASE_LACK_ISREF_PROTECT_LEVEL_TL,
    .MC_ERR.Phase_Lack_C._P_Q32U_Clear_Time = 0U,
    .MC_ERR.Phase_Lack_C._P_Q32U_Check_Count = 10U,
    .MC_ERR.Phase_Lack_C.Check_Flag.bit.Clear_Mode = 1U,
    
    .MC_ERR.Rotor_Lock._P_Q14I_Check_TL = ROTOR_LOCK_ISREF_PROTECT_LEVEL_TL,
    .MC_ERR.Rotor_Lock._P_Q32U_Check_Time = ROTOR_LOCK_PROTECT_LEVEL_TIME,
    .MC_ERR.Rotor_Lock._P_Q14I_Clear_TL = ROTOR_LOCK_SPEED_PROTECT_LEVEL_TL,
    .MC_ERR.Rotor_Lock._P_Q32U_Clear_Time = 0U,
    .MC_ERR.Rotor_Lock._P_Q32U_Check_Count = 10U,
    .MC_ERR.Rotor_Lock.Check_Flag.bit.Clear_Mode = 1U,
    
    .MC_ERR.Loss_Step._P_Q14I_Check_TL = LOSS_STEP_ES_PROTECT_LEVEL_TL,
    .MC_ERR.Loss_Step._P_Q32U_Check_Time = LOSS_STEP_PROTECT_LEVEL_TIME,
    .MC_ERR.Loss_Step._P_Q14I_Clear_TL = LOSS_STEP_SPEED_PROTECT_LEVEL_TL,
    .MC_ERR.Loss_Step._P_Q32U_Clear_Time = 0U,
    .MC_ERR.Loss_Step._P_Q32U_Check_Count = 10U,
    .MC_ERR.Loss_Step.Check_Flag.bit.Clear_Mode = 1U,
    
    .MC_ERR.Fast_Over_Voltage._P_Q14I_Check_TL = FAST_OVER_VOLTAGE_PROTECT_LEVEL_TL,
    .MC_ERR.Fast_Over_Voltage._P_Q32U_Check_Time = FAST_OVER_VOLTAGE_PROTECT_LEVEL_TIME,
    .MC_ERR.Fast_Over_Voltage._P_Q14I_Clear_TL = 0U,
    .MC_ERR.Fast_Over_Voltage._P_Q32U_Clear_Time = 0U,
    .MC_ERR.Fast_Over_Voltage._P_Q32U_Check_Count = 10U,
    .MC_ERR.Fast_Over_Voltage.Check_Flag.bit.Clear_Mode = 1U,

    .MC_ERR.Fast_Over_Current._P_Q14I_Check_TL = FAST_CURRENT_PROTECT_LEVEL_TL,
    .MC_ERR.Fast_Over_Current._P_Q32U_Check_Time = FAST_CURRENT_PROTECT_LEVEL_TIME,
    .MC_ERR.Fast_Over_Current._P_Q14I_Clear_TL = 0U,
    .MC_ERR.Fast_Over_Current._P_Q32U_Clear_Time = 0U,
    .MC_ERR.Fast_Over_Current._P_Q32U_Check_Count = 10U,
    .MC_ERR.Fast_Over_Current.Check_Flag.bit.Clear_Mode = 1U,

};


//电机参数索引
Q32I_ Q14I_Table_Freq[10] =
{
        0,    819,   1638,   3276,   4915,   6554,   8192,  9830,  13107,  16384,
};
Q32I_ Q14I_Table_Current[5] =
{
     3276,   6554,   9830,  13107,  16384,
};
Q32I_ Q14I_Table_Voltage[5] =
{
     3276,   6554,   9830,  13107,  16384,
};

//转速环参数查表
Q32I_ Q14I_Table_Freq_Kp_Coeff[10] =
{
     1638,   1638,   3276,   3276,   4915,   6554,   8192,  9830,  13107,  16384,
};
Q32I_ Q14I_Table_Freq_Ki_Coeff[10] =
{
      819,    819,   1638,   3276,   4915,   6554,   8192,  9830,  13107,  16384,
};
//母线电流系数查表
Q32I_ Q14I_Table_Ibus_Coeff[50] =
{
    16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,
    16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,
    16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,
    16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,
    16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384
};
//Q轴电感查表
Q32I_ Q14I_Table_Lq_Coeff[10] =
{
    16384,  16384,  16384,  16384,  16384,
};

//SMO观测器参数查表
Q32I_ Q14I_Table_SMO_H1_Coeff[10] =
{
    16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,
};
Q32I_ Q14I_Table_SMO_PLL_Kp_Coeff[10] =
{
    16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,
};
Q32I_ Q14I_Table_SMO_PLL_Ki_Coeff[10] =
{
    16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,
};
Q32I_ Q14I_Table_SMO_Angle[50] =
{
        0,      0,      0,      0,      0,      0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,      0,      0,
};

//磁链观测器参数查表
Q32I_ Q14I_Table_FLUX_Gamma_Coeff[10] =
{
    16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,
};
Q32I_ Q14I_Table_FLUX_PLL_Kp_Coeff[10] =
{
    16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,
};
Q32I_ Q14I_Table_FLUX_PLL_Ki_Coeff[10] =
{
    16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,  16384,
};
Q32I_ Q14I_Table_FLUX_Angle[50] =
{
        0,      0,      0,      0,      0,      0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,      0,      0,
};
