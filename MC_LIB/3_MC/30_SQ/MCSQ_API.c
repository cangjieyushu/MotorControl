/**************************************************************************************************
*     File Name :                        MCSQ_API_H.c
*     Library/Module Name :              MCSQ
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制接口源文件
**************************************************************************************************/

#include "MCSQ_API.h"


/************************************电机控制接口函数*****************************************/

/**********************************************************************************************
Function: Motor_Start
Description: 电机启动
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Start(ST_MOTOR_TASK* pMotor)
{
    pMotor->Motor_State_Flag.bit.motor_run_flag = 1U;
}

/**********************************************************************************************
Function: Motor_Stop
Description: 电机停机
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Stop(ST_MOTOR_TASK* pMotor)
{
    pMotor->Motor_State_Flag.bit.motor_run_flag = 0U;
}

/**********************************************************************************************
Function: Motor_Set_Dir
Description: 设置电机运行方向
Input:  1（正转），-1（反转）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Set_Dir(ST_MOTOR_TASK* pMotor, Q32I_ Dir)
{
    EM_DIRECTION Dir_tmp = CW;
    if(Dir == -1)
    {
        Dir_tmp = CCW;
    }
    pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Target = Dir_tmp;
}

/**********************************************************************************************
Function: Motor_Read_Dir
Description: 获取电机运行方向
Input: 无
Output: 1（正转），-1（反转）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32I_ Motor_Read_Dir(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set == CW)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

/**********************************************************************************************
Function: Motor_Get_Run_State
Description: 获取电机是否为运行状态
Input: 无
Output: 1,0
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ Motor_Read_Run_State(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_Flow == MOTOR_STATE_RUN)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**********************************************************************************************
Function: Motor_Set_Target_Speed
Description: 设置电机转速
Input: 电机转速（rpm）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Set_Target_Speed(ST_MOTOR_TASK* pMotor, Q32I_ Speed)
{
    if(Speed < ((Q32I_)MOTOR_MIN_SPEED))
    {
        Speed = (Q32I_)MOTOR_MIN_SPEED;
    }
    else if(Speed > ((Q32I_)MOTOR_MAX_SPEED))
    {
        Speed = (Q32I_)MOTOR_MAX_SPEED;
    }
    pMotor->MCSQ_CTRL.PWM_CTRL._I_Q14U_Duty_VR = Q16I_LFT_14(Speed)/((Q32I_)MOTOR_MAX_SPEED);
}

/**********************************************************************************************
Function: Motor_Read_Speed
Description: 读取电机转速
Input: 无
Output: 电机转速（rpm）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ Motor_Read_Speed(ST_MOTOR_TASK* pMotor)
{
    return Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Freq.Q14I_LPF_Out*((Q32I_)MOTOR_MAX_SPEED));
}

/**********************************************************************************************
Function: Motor_Read_Current
Description: 读取电机相电流
Input: 无
Output: 电机电流（0.01A）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ Motor_Read_Current(ST_MOTOR_TASK* pMotor)
{
    return Q32I_RHT_14(100*pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Iphase.Q14I_LPF_Out*((Q32I_)MOTOR_CURRENT_PHASE_A));
}

/**********************************************************************************************
Function: Motor_Read_Bus
Description: 读取电机母线电流
Input: 无
Output: 电机电流（0.01A）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ Motor_Read_Bus(ST_MOTOR_TASK* pMotor)
{
    return Q32I_RHT_14(100*pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Ibus.Q14I_LPF_Out*((Q32I_)MOTOR_CURRENT_PHASE_A));
}

/**********************************************************************************************
Function: Motor_Read_Error
Description: 读取电机故障码
Input: 无
Output: 电机故障码
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ Motor_Read_Error(ST_MOTOR_TASK* pMotor)
{
    return pMotor->MC_ERR.Motor_Error_Flag.all;
}

/**********************************************************************************************
Function: Motor_Clear_Error
Description: 清除电机故障
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Clear_Error(ST_MOTOR_TASK* pMotor)
{
    MC_Error_Clear(&pMotor->MC_ERR);
}



void Motor_NULL_API(ST_MOTOR_TASK* pMotor, float val);
void Motor_Position_Duty_API00(ST_MOTOR_TASK* pMotor, float val);
void Motor_DIAG_Rise_tl_API10(ST_MOTOR_TASK* pMotor, float val);
void Motor_DIAG_Fall_tl_API11(ST_MOTOR_TASK* pMotor, float val);
void Motor_Flux_Rise_tl_API20(ST_MOTOR_TASK* pMotor, float val);
void Motor_Flux_Fall_tl_API21(ST_MOTOR_TASK* pMotor, float val);
void Motor_Bemf_Delay_Coeff_API30(ST_MOTOR_TASK* pMotor, float val);
void Motor_Freq_Step_API40(ST_MOTOR_TASK* pMotor, float val);
void Motor_Duty_Step_API41(ST_MOTOR_TASK* pMotor, float val);
void Motor_Freq_Kp_API50(ST_MOTOR_TASK* pMotor, float val);
void Motor_Freq_Ki_API51(ST_MOTOR_TASK* pMotor, float val);
void Motor_Freq_Kd_API52(ST_MOTOR_TASK* pMotor, float val);
void Motor_Freq_PID_STEP_API53(ST_MOTOR_TASK* pMotor, float val);
void Motor_Ibus_Kp_API60(ST_MOTOR_TASK* pMotor, float val);
void Motor_Ibus_Ki_API61(ST_MOTOR_TASK* pMotor, float val);
void Motor_Ibus_Kd_API62(ST_MOTOR_TASK* pMotor, float val);
void Motor_Ibus_PID_STEP_API63(ST_MOTOR_TASK* pMotor, float val);
void Motor_Iphase_Kp_API70(ST_MOTOR_TASK* pMotor, float val);
void Motor_Iphase_Ki_API71(ST_MOTOR_TASK* pMotor, float val);
void Motor_Iphase_Kd_API72(ST_MOTOR_TASK* pMotor, float val);
void Motor_Iphase_PID_STEP_API73(ST_MOTOR_TASK* pMotor, float val);



pMOTOR_API Motor_API_Function[256U] =
{
    Motor_Position_Duty_API00,      Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,                 Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,
    Motor_DIAG_Rise_tl_API10,       Motor_DIAG_Fall_tl_API11,   Motor_NULL_API,             Motor_NULL_API,                 Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,
    Motor_Flux_Rise_tl_API20,       Motor_Flux_Fall_tl_API21,   Motor_NULL_API,             Motor_NULL_API,                 Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,
    Motor_Bemf_Delay_Coeff_API30,   Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,                 Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,
    Motor_Freq_Step_API40,          Motor_Duty_Step_API41,      Motor_NULL_API,             Motor_NULL_API,                 Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,
    Motor_Freq_Kp_API50,            Motor_Freq_Ki_API51,        Motor_Freq_Kd_API52,        Motor_Freq_PID_STEP_API53,      Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,
    Motor_Ibus_Kp_API60,            Motor_Ibus_Ki_API61,        Motor_Ibus_Kd_API62,        Motor_Ibus_PID_STEP_API63,      Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,
    Motor_Iphase_Kp_API70,          Motor_Iphase_Ki_API71,      Motor_Iphase_Kd_API72,      Motor_Iphase_PID_STEP_API73,    Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,             Motor_NULL_API,
};

void Motor_NULL_API(ST_MOTOR_TASK* pMotor, float val)
{
    
}

void Motor_Position_Duty_API00(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.MCSQ_POSITION._P_Q14U_Position_Duty_Set = Q14I_DUTY_TO_PU(val);
}

void Motor_DIAG_Rise_tl_API10(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.MCSQ_DIAG._P_Q14U_DIAG_Rise_tl = (Q32I_)(val * MOTOR_Q14_PU);
}

void Motor_DIAG_Fall_tl_API11(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.MCSQ_DIAG._P_Q14U_DIAG_Fall_tl = (Q32I_)(val * MOTOR_Q14_PU);
}

void Motor_Flux_Rise_tl_API20(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.MCSQ_FLUX._P_Q14U_Flux_Rise_tl = (Q32I_)(val * MOTOR_Q14_PU);
}

void Motor_Flux_Fall_tl_API21(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.MCSQ_FLUX._P_Q14U_Flux_Fall_tl = (Q32I_)(val * MOTOR_Q14_PU);
}

void Motor_Bemf_Delay_Coeff_API30(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.MCSQ_BEMF._P_Q14U_Bemf_Delay_Coeff = (Q32I_)(val * MOTOR_Q14_PU)/6;
}

void Motor_Freq_Step_API40(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.Ramp_Freq.Q28I_ADDStep = Q28I_FREQ_TO_PU(val * MOTOR_MAX_FREQ);
    pMotor->MCSQ_CTRL.Ramp_Freq.Q28I_SUBStep = -pMotor->MCSQ_CTRL.Ramp_Freq.Q28I_ADDStep;
}

void Motor_Duty_Step_API41(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.PWM_CTRL.Ramp_Duty.Q28I_ADDStep = Q28I_DUTY_TO_PU(val);
    pMotor->MCSQ_CTRL.PWM_CTRL.Ramp_Duty.Q28I_SUBStep = -pMotor->MCSQ_CTRL.PWM_CTRL.Ramp_Duty.Q28I_ADDStep;
}

void Motor_Freq_Kp_API50(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.PID_Freq.Q14I_Kp = (Q32I_)(val * MOTOR_Q14_PU);
}

void Motor_Freq_Ki_API51(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.PID_Freq.Q14I_Ki = (Q32I_)(val * MOTOR_Q14_PU);
}

void Motor_Freq_Kd_API52(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.PID_Freq.Q14I_Kd = (Q32I_)(val * MOTOR_Q14_PU);
}

void Motor_Freq_PID_STEP_API53(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.PID_Freq.Q28I_StepMax = Q28I_DUTY_TO_PU(val);
    pMotor->MCSQ_CTRL.PID_Freq.Q28I_StepMin = -pMotor->MCSQ_CTRL.PID_Freq.Q28I_StepMax;
}

void Motor_Ibus_Kp_API60(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.PID_Ibus.Q14I_Kp = (Q32I_)(val * MOTOR_Q14_PU);
}

void Motor_Ibus_Ki_API61(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.PID_Ibus.Q14I_Ki = (Q32I_)(val * MOTOR_Q14_PU);
}

void Motor_Ibus_Kd_API62(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.PID_Ibus.Q14I_Kd = (Q32I_)(val * MOTOR_Q14_PU);
}

void Motor_Ibus_PID_STEP_API63(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.PID_Ibus.Q28I_StepMax = Q28I_DUTY_TO_PU(val);
    pMotor->MCSQ_CTRL.PID_Ibus.Q28I_StepMin = -pMotor->MCSQ_CTRL.PID_Ibus.Q28I_StepMax;
}

void Motor_Iphase_Kp_API70(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.PID_Iphase.Q14I_Kp = (Q32I_)(val * MOTOR_Q14_PU);
}

void Motor_Iphase_Ki_API71(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.PID_Iphase.Q14I_Ki = (Q32I_)(val * MOTOR_Q14_PU);
}

void Motor_Iphase_Kd_API72(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.PID_Iphase.Q14I_Kd = (Q32I_)(val * MOTOR_Q14_PU);
}

void Motor_Iphase_PID_STEP_API73(ST_MOTOR_TASK* pMotor, float val)
{
    pMotor->MCSQ_CTRL.PID_Iphase.Q28I_StepMax = Q28I_DUTY_TO_PU(val);
    pMotor->MCSQ_CTRL.PID_Iphase.Q28I_StepMin = -pMotor->MCSQ_CTRL.PID_Iphase.Q28I_StepMax;
}
