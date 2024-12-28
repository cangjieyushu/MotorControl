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
    .IF_CTRL.Ramp_Iq.F_Init = MOTOR_IF_IQRAMP_INIT,
    .IF_CTRL.Ramp_Iq.F_Target = MOTOR_IF_IQRAMP_TARGET,
    .IF_CTRL.Ramp_Iq.F_ADDStep = MOTOR_IF_IQRAMP_STEP,
    .IF_CTRL.Ramp_Iq.F_SUBStep = -MOTOR_IF_IQRAMP_STEP,
    .IF_CTRL.Ramp_SRAD.F_Init = MOTOR_IF_ANGLERAMP_INIT,
    .IF_CTRL.Ramp_SRAD.F_Target = MOTOR_IF_ANGLERAMP_TARGET,
    .IF_CTRL.Ramp_SRAD.F_ADDStep = MOTOR_IF_ANGLERAMP_STEP,
    .IF_CTRL.Ramp_SRAD.F_SUBStep = -MOTOR_IF_ANGLERAMP_STEP,
    .IF_CTRL.Ramp_AngleERR.F_ADDStep = MOTOR_VF_ANGLE_ERROR_RAMP_STEP,
    .IF_CTRL.Ramp_AngleERR.F_SUBStep = -MOTOR_VF_ANGLE_ERROR_RAMP_STEP,
    .IF_CTRL._P_F_Ts = MOTOR_HTs, 
    .IF_CTRL._P_F_AngleERRLimit = MOTOR_VF_ANGLE_ERROR,
    
    .VF_CTRL.Ramp_Vq.F_Init = MOTOR_VF_IQRAMP_INIT,
    .VF_CTRL.Ramp_Vq.F_Target = MOTOR_VF_IQRAMP_TARGET,
    .VF_CTRL.Ramp_Vq.F_ADDStep = MOTOR_VF_IQRAMP_STEP,
    .VF_CTRL.Ramp_Vq.F_SUBStep = -MOTOR_VF_IQRAMP_STEP,
    .VF_CTRL.Ramp_SRAD.F_Init = MOTOR_VF_ANGLERAMP_INIT,
    .VF_CTRL.Ramp_SRAD.F_Target = MOTOR_VF_ANGLERAMP_TARGET,
    .VF_CTRL.Ramp_SRAD.F_ADDStep = MOTOR_VF_ANGLERAMP_STEP,
    .VF_CTRL.Ramp_SRAD.F_SUBStep = -MOTOR_VF_ANGLERAMP_STEP,
    .VF_CTRL.Ramp_AngleERR.F_ADDStep = MOTOR_VF_ANGLE_ERROR_RAMP_STEP,
    .VF_CTRL.Ramp_AngleERR.F_SUBStep = -MOTOR_VF_ANGLE_ERROR_RAMP_STEP,
    .VF_CTRL._P_F_Ts = MOTOR_HTs,
    .VF_CTRL._P_F_AngleERRLimit = MOTOR_VF_ANGLE_ERROR,
    
    .SVPWM_CTRL._P_F_MaxDuty = HAL_MAX_DUTY,
    .SVPWM_CTRL._P_F_MinDuty = HAL_MIN_DUTY,
    .SVPWM_CTRL._P_F_ADCSampleDuty = HAL_ADC_SAMPLE_DUTY,
    
    .SRAD_CTRL.PID_SRAD.F_Kp = MOTOR_SPD_KP_GAIN,
    .SRAD_CTRL.PID_SRAD.F_Ki = MOTOR_SPD_KI_GAIN,
    .SRAD_CTRL.PID_SRAD.F_Kd = MOTOR_SPD_KD_GAIN,
    .SRAD_CTRL.PID_SRAD.F_OutMax = MOTOR_SPD_PID_MAX,
    .SRAD_CTRL.PID_SRAD.F_OutMin = MOTOR_SPD_PID_MIN,
    .SRAD_CTRL.PID_WEAK.F_Kp = 0.0f,
    .SRAD_CTRL.PID_WEAK.F_Ki = 0.0f,
    .SRAD_CTRL.PID_WEAK.F_Kd = 0.0f,
    .SRAD_CTRL.PID_WEAK.F_OutMax = 0.0f,
    .SRAD_CTRL.PID_WEAK.F_OutMin = 0.0f,
    .SRAD_CTRL.Ramp_SRAD.F_Target = 0.0f,
    .SRAD_CTRL.Ramp_SRAD.F_ADDStep = MOTOR_CLOSELOOP2_STEP,
    .SRAD_CTRL.Ramp_SRAD.F_SUBStep = -MOTOR_CLOSELOOP2_STEP,
    .SRAD_CTRL._P_F_SRAD_Max = MOTOR_MAX_SRAD,
    .SRAD_CTRL._P_F_SRAD_Min = -MOTOR_MAX_SRAD,
    
    .CURRENT_CTRL.PID_Id.F_Kp = MOTOR_FOC_KP_GAIN,
    .CURRENT_CTRL.PID_Id.F_Ki = MOTOR_FOC_KI_GAIN,
    .CURRENT_CTRL.PID_Id.F_Kd = MOTOR_FOC_KD_GAIN,
    .CURRENT_CTRL.PID_Iq.F_Kp = MOTOR_FOC_KP_GAIN,
    .CURRENT_CTRL.PID_Iq.F_Ki = MOTOR_FOC_KI_GAIN,
    .CURRENT_CTRL.PID_Iq.F_Kd = MOTOR_FOC_KD_GAIN,
    .CURRENT_CTRL._P_F_VsScale = MOTOR_VS_SCALE,

    .FLUX_CTRL.PID_PLL.F_Kp = MOTOR_FLUX_PLL_KP,
    .FLUX_CTRL.PID_PLL.F_Ki = MOTOR_FLUX_PLL_KI,
    .FLUX_CTRL.PID_PLL.F_Kd = MOTOR_FLUX_PLL_KD,
    .FLUX_CTRL.PID_PLL.F_OutMax = MOTOR_FLUX_PLL_MAX,
    .FLUX_CTRL.PID_PLL.F_OutMin = MOTOR_FLUX_PLL_MIN,
    .FLUX_CTRL.FL_SRAD.F_Filter_Coeff = USER_PLL_SPEED_LPF_COEFF,
    .FLUX_CTRL._P_F_Ts = MOTOR_HTs,
    .FLUX_CTRL._P_F_Gamma = MOTOR_FLUX_KT,
    .FLUX_CTRL._P_F_Rs = MOTOR_Rs,
    .FLUX_CTRL._P_F_Ld = MOTOR_Ld,
    .FLUX_CTRL._P_F_Ls = MOTOR_Ls,
    .FLUX_CTRL._P_F_Flux2 = MATH_SQUARE_F(MOTOR_FLUX),
    
    .SMO_CTRL.PID_PLL.F_Kp = MOTOR_SMO_PLL_KP,
    .SMO_CTRL.PID_PLL.F_Ki = MOTOR_SMO_PLL_KI,
    .SMO_CTRL.PID_PLL.F_Kd = MOTOR_SMO_PLL_KD,
    .SMO_CTRL.PID_PLL.F_OutMax = MOTOR_SMO_PLL_MAX,
    .SMO_CTRL.PID_PLL.F_OutMin = MOTOR_SMO_PLL_MIN,
    .SMO_CTRL.FL_SRAD.F_Filter_Coeff = USER_PLL_SPEED_LPF_COEFF,
    .SMO_CTRL._P_F_Ts = MOTOR_HTs,
    .SMO_CTRL._P_F_K1 = MOTOR_SMO_K1,
    .SMO_CTRL._P_F_K2 = MOTOR_SMO_K2,
    .SMO_CTRL._P_F_Rs = MOTOR_Rs,
    .SMO_CTRL._P_F_Ld = MOTOR_Ld,
    .SMO_CTRL._P_F_Lq = MOTOR_Lq,
    .SMO_CTRL._P_F_One_Over_Ld = 1.0f / MOTOR_Ld,
    .SMO_CTRL._P_F_Rs_Over_Ld = MOTOR_Rs / MOTOR_Ld,
    .SMO_CTRL._P_F_Ld_Lq_Over_Ld = (MOTOR_Ld - MOTOR_Lq) / MOTOR_Ld,
    
};

