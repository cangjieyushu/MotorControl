/**************************************************************************************************
*     File Name :                        MCSQ_TASK.c
*     Library/Module Name :              MCSQ
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机子任务源文件
**************************************************************************************************/

#include "MCSQ_TASK.h"


void MotorTask_Pre_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Init_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Idle_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Boot_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Position_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Run_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Brake_Flow(ST_MOTOR_TASK* pMotor);

pMOTOR_FUN Motor_Flow_Function[MOTOR_STATE_BRAKE+1] =
{
    MotorTask_Pre_Flow,
    MotorTask_Init_Flow,
    MotorTask_Idle_Flow,
    MotorTask_Boot_Flow,
    MotorTask_Position_Flow,
    MotorTask_Run_Flow,
    MotorTask_Brake_Flow
};


void MotorTask_Switch_Flux_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Switch_Bemf_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Switch_Cmp_Flow(ST_MOTOR_TASK* pMotor);

pMOTOR_FUN Motor_Math_Function[SWITCH_CMP+1] = 
{
    MotorTask_Switch_Flux_Flow,
    MotorTask_Switch_Bemf_Flow,
    MotorTask_Switch_Cmp_Flow
};


pFUN_HPWMLPWM_SET POSITION_Set[6][2] =
{
    MH_POSITION_Up, MH_POSITION_Up,//U+
    MH_POSITION_Wn, MH_POSITION_Vn,//W-
    MH_POSITION_Vp, MH_POSITION_Wp,//V+
    MH_POSITION_Un, MH_POSITION_Un,//U-
    MH_POSITION_Wp, MH_POSITION_Vp,//W+
    MH_POSITION_Vn, MH_POSITION_Wn,//V-
};

pFUN_HPWMLPWM_SET HPWMLPWM_Set[6][2] =
{
    MH_HPWM_LPWM_UpVn, MH_HPWM_LPWM_UpWn,//U+V-
    MH_HPWM_LPWM_UpWn, MH_HPWM_LPWM_UpVn,//U+W-
    MH_HPWM_LPWM_VpWn, MH_HPWM_LPWM_WpVn,//V+W-
    MH_HPWM_LPWM_VpUn, MH_HPWM_LPWM_WpUn,//V+U-
    MH_HPWM_LPWM_WpUn, MH_HPWM_LPWM_VpUn,//W+U-
    MH_HPWM_LPWM_WpVn, MH_HPWM_LPWM_VpWn,//W+V-
};


/**********************************************************************************************
Function: MotorTask_Speed_Flow
Description: 电机控制速度环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Speed_Flow(ST_MOTOR_TASK* pMotor)
{
    pMotor->MC_ERR._I_Q14U_Temp_ADC = ADC_DATA_READ_TEMP;
    pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Vbus_ADC = ADC_DATA_READ_VBUS;
    
    pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q14U_Vbus_pu = 4*pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Vbus_ADC;
    
    pMotor->MC_ERR._I_Q14U_Vbus_pu = pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q14U_Vbus_pu;
    pMotor->MC_ERR._I_Q14U_Speed_pu = pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Freq.Q14I_LPF_Out;
    pMotor->MC_ERR._I_Q14U_Ibus_pu = pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Ibus.Q14I_LPF_Out;
    MC_Error_Speed_Flow(&pMotor->MC_ERR, ((pMotor->Motor_Flow >= MOTOR_STATE_BOOT)&&(pMotor->Motor_Flow <= MOTOR_STATE_BRAKE)));
    pMotor->MC_ERR._I_Q14U_Iphase_Max_pu = 0U;
    
    if(pMotor->Motor_Flow == MOTOR_STATE_RUN)
    {
        if(pMotor->Motor_State_Flag.bit.motor_speed_flag == 1U)
        {
            pMotor->MCSQ_CTRL.Ramp_Freq.Q14I_Target = Q32I_RHT_14(pMotor->MCSQ_CTRL.PWM_CTRL._I_Q14U_Duty_VR*pMotor->MCSQ_CTRL.PWM_CTRL._P_Q14U_Motor_Freq_Max);
            
            Ramp_Cal_T(&pMotor->MCSQ_CTRL.Ramp_Freq);
            
            pMotor->MCSQ_CTRL.PID_Freq.Q14I_Rf = pMotor->MCSQ_CTRL.Ramp_Freq.Q14I_Output;
            pMotor->MCSQ_CTRL.PID_Freq.Q14I_Fb = pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Freq.Q14I_LPF_Out;
            PID_Inc_Cal_T(&pMotor->MCSQ_CTRL.PID_Freq);
            
            pMotor->MCSQ_CTRL.PWM_CTRL._I_Q14U_Duty_Freq = pMotor->MCSQ_CTRL.PID_Freq.Q14I_Output;
        }
        else
        {
            pMotor->MCSQ_CTRL.PWM_CTRL._I_Q14U_Duty_Freq = Q32I_RHT_14(pMotor->MCSQ_CTRL.PWM_CTRL._I_Q14U_Duty_VR*pMotor->MCSQ_CTRL.PWM_CTRL._P_Q14U_Duty_Max);
        }
        
        if(pMotor->Motor_State_Flag.bit.motor_busA_flag == 1U)
        {
            pMotor->MCSQ_CTRL.PID_Ibus.Q14I_Rf = pMotor->MCSQ_CTRL.MCSQ_BLDC._P_Q14U_Ibus_Max_pu;;
            pMotor->MCSQ_CTRL.PID_Ibus.Q14I_Fb = pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Ibus.Q14I_LPF_Out;
            PID_Inc_Cal_T(&pMotor->MCSQ_CTRL.PID_Ibus);
            
            pMotor->MCSQ_CTRL.PWM_CTRL._I_Q14U_Duty_Ibus = pMotor->MCSQ_CTRL.PID_Ibus.Q14I_Output;
        }
        else if(pMotor->Motor_State_Flag.bit.motor_busP_flag == 1U)
        {
        
            pMotor->MCSQ_CTRL.PID_Ibus.Q14I_Rf = Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BLDC._P_Q14U_Ibus_Max_pu*pMotor->MCSQ_CTRL.MCSQ_BLDC._P_Q14U_Vbus_Max_pu);
            pMotor->MCSQ_CTRL.PID_Ibus.Q14I_Fb = Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Ibus.Q14I_LPF_Out*pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q14U_Vbus_pu);
            PID_Inc_Cal_T(&pMotor->MCSQ_CTRL.PID_Ibus);
            
            pMotor->MCSQ_CTRL.PWM_CTRL._I_Q14U_Duty_Ibus = pMotor->MCSQ_CTRL.PID_Ibus.Q14I_Output;
        }
        else
        {
            pMotor->MCSQ_CTRL.PWM_CTRL._I_Q14U_Duty_Ibus = pMotor->MCSQ_CTRL.PWM_CTRL._P_Q14U_Duty_Max;
        }
        
        if(MCSQ_Stall_Check(&pMotor->MCSQ_CTRL.STALL_CTRL, &pMotor->MCSQ_CTRL) == SUCS)
        {
            pMotor->MC_ERR.Motor_Error_Flag.bit.rotor_stall = 1U;
        }
    }
    else if(pMotor->Motor_Flow == MOTOR_STATE_BRAKE)
    {
        MCSQ_Brake(&pMotor->MCSQ_CTRL.MCSQ_BRAKE);
    }
}

/**********************************************************************************************
Function: MotorTask_Pre_Flow
Description: 电机控制预备状态
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Pre_Flow(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
    {
        if(pMotor->MC_ERR._V_Q32U_MOS_Error_cnt >= pMotor->MC_ERR._P_Q32U_MOS_Error_Count)
        {
            pMotor->MC_ERR.Motor_Error_Flag.bit.mos_fault = 1U;
        }
        
        MH_PWM_Preload_Enable();
        MH_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_Start_PWMCount);
        MCSQ_Init(&pMotor->MCSQ_CTRL);
        
        MH_HPWM_LPWM_Close();
        MH_ADC_Soft_Trigger();
        pMotor->Motor_Flow = MOTOR_STATE_INIT;
    }
    else
    {
        MH_HPWM_LPWM_Close();
    }
}

/**********************************************************************************************
Function: MotorTask_Init_Flow
Description: 电机控制初始状态
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Init_Flow(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
    {
        switch(MCSQ_Offset_Check(&pMotor->MCSQ_CTRL.MCSQ_OFFSET, &pMotor->MCSQ_CTRL.MCSQ_BLDC, ADC_DATA_READ_CURRENT))
        {
            case ING:
            {
                if(MH_PWM_Count_Read() + pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_ADC_Solve_Value < pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_Start_PWMCount)
                {
                    MH_ADC_Soft_Trigger();
                }
                break;
            }
            case SUCS:
            {
                pMotor->Motor_Flow = MOTOR_STATE_IDLE;
                break;
            }
            case FAIL:
            {
                pMotor->MC_ERR.Motor_Error_Flag.bit.current_offset = 1U;
                pMotor->Motor_Flow = MOTOR_STATE_PRE;
                break;
            }
            default:break;
        }
    }
    else
    {
        MH_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_High_PWMCount);
        MH_HPWM_LPWM_Close();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**********************************************************************************************
Function: MotorTask_Idle_Flow
Description: 电机控制静止状态
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Idle_Flow(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
    {
        if(pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set == CW)
        {
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Bemf_ADC_tmp[0] = ADC_DATA_READ_U_BEMF;
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Bemf_ADC_tmp[1] = ADC_DATA_READ_V_BEMF;
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Bemf_ADC_tmp[2] = ADC_DATA_READ_W_BEMF;
        }
        else
        {
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Bemf_ADC_tmp[0] = ADC_DATA_READ_U_BEMF;
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Bemf_ADC_tmp[1] = ADC_DATA_READ_W_BEMF;
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Bemf_ADC_tmp[2] = ADC_DATA_READ_V_BEMF;
        }

        switch(MCSQ_Flying_Check(&pMotor->MCSQ_CTRL.MCSQ_FLYING, &pMotor->MCSQ_CTRL.MCSQ_BLDC, MH_HALL_TIM_Count_Read()))
        {
            case ING:
            {
                Q32U_ Q32U_pwm_count_tmp = MH_PWM_Count_Read();
                if(Q32U_pwm_count_tmp + pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_ADC_Solve_Value < pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_Start_PWMCount)
                {
                    MH_ADC_Soft_Trigger();
                }
                break;
            }
            case SUCS:
            {
                MCSQ_Flying_Init(&pMotor->MCSQ_CTRL);
                MH_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_High_PWMCount);
                HPWMLPWM_Set[pMotor->MCSQ_CTRL.MCSQ_BLDC.Sector][pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set](pMotor->MCSQ_CTRL.PWM_CTRL._O_Q32U_Duty_PWMCount);
                pMotor->Motor_Flow = MOTOR_STATE_RUN;
                break;
            }
            case FAIL:
            {
                MH_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_Start_PWMCount);
                MH_ADC_TrigTime_Set(Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BOOT._P_Q14U_Boot_Duty_Set*pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_Start_PWMCount));
                MH_HPWM_LPWM_HOpen(Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BOOT._P_Q14U_Boot_Duty_Set*pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_Start_PWMCount));
                pMotor->Motor_Flow = MOTOR_STATE_BOOT;
                break;
            }
            default:break;
        }
    }
    else
    {
        MH_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_High_PWMCount);
        MH_HPWM_LPWM_Close();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**********************************************************************************************
Function: MotorTask_Boot_Flow
Description: 电机控制自举状态
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Boot_Flow(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
    {
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Bemf_ADC_tmp[0] = ADC_DATA_READ_U_BEMF;
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Bemf_ADC_tmp[1] = ADC_DATA_READ_V_BEMF;
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Bemf_ADC_tmp[2] = ADC_DATA_READ_W_BEMF;

            switch(MCSQ_Boot_Check(&pMotor->MCSQ_CTRL.MCSQ_BOOT, &pMotor->MCSQ_CTRL.MCSQ_BLDC))
            {
                case ING:
                {
                    MH_HPWM_LPWM_LOpen(Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BOOT._P_Q14U_Boot_Duty_Set*pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_Start_PWMCount));
                    break;
                }
                case SUCS:
                {
                    pMotor->MCSQ_CTRL.MCSQ_POSITION._V_Q14U_Position_Duty_PWMCount = Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BLDC._P_Q14U_Vbus_Max_pu
                    *pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_Start_PWMCount/pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q14U_Vbus_pu*pMotor->MCSQ_CTRL.MCSQ_POSITION._P_Q14U_Position_Duty_Set);
                    
                    MH_ADC_TrigTime_Set(pMotor->MCSQ_CTRL.MCSQ_POSITION._V_Q14U_Position_Duty_PWMCount - pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_ADC_Sample_Value);
                    POSITION_Set[pMotor->MCSQ_CTRL.MCSQ_POSITION._V_Q32U_Position_cnt][pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set](pMotor->MCSQ_CTRL.MCSQ_POSITION._V_Q14U_Position_Duty_PWMCount);
                    pMotor->Motor_Flow = MOTOR_STATE_POSITION;
                    break;
                }
                case FAIL:
                {
                    break;
                }
                default:break;
            }
    }
    else
    {
        MH_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_High_PWMCount);
        MH_HPWM_LPWM_Close();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**********************************************************************************************
Function: MotorTask_Position_Flow
Description: 电机控制定位状态
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Position_Flow(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
    {
        MH_HPWM_LPWM_Close();
        
        switch(MCSQ_Pluse_Positon(&pMotor->MCSQ_CTRL.MCSQ_POSITION, &pMotor->MCSQ_CTRL.MCSQ_BLDC, ADC_DATA_READ_CURRENT))
        {
            case ING:
            {
                POSITION_Set[pMotor->MCSQ_CTRL.MCSQ_POSITION._V_Q32U_Position_cnt][pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set](pMotor->MCSQ_CTRL.MCSQ_POSITION._V_Q14U_Position_Duty_PWMCount);
                break;
            }
            case SUCS:
            {
                MH_ADC_TrigTime_Set(pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_ADC_Delay_Value);
                MH_PWM_Preload_Disable();
                MH_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_Low_PWMCount);
                pMotor->Motor_Flow = MOTOR_STATE_RUN;
                break;
            }
            case FAIL:
            {
                pMotor->MC_ERR.Motor_Error_Flag.bit.position_error = 1U;
                pMotor->Motor_Flow = MOTOR_STATE_PRE;
                break;
            }
            default:break;
        }
    }
    else
    {
        MH_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_High_PWMCount);
        MH_HPWM_LPWM_Close();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**********************************************************************************************
Function: MotorTask_Switch_Flux_Flow
Description: 电机控制磁链换向
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Switch_Flux_Flow(ST_MOTOR_TASK* pMotor)
{
    MCSQ_FLUX(&pMotor->MCSQ_CTRL.MCSQ_FLUX, &pMotor->MCSQ_CTRL.MCSQ_BLDC);
    if(pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow == SQUARE_CROSS_SUCC)
    {
        MCSQ_Freq_Cal(&pMotor->MCSQ_CTRL.MCSQ_BLDC.Freq_Cal, &pMotor->MCSQ_CTRL, MH_HALL_TIM_Count_Read());
        MH_Switch_TIM_Delay(pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_Tim_Delay_Value);
    }
}
 
/**********************************************************************************************
Function: MotorTask_Switch_Bemf_Flow
Description: 电机控制过零换向
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Switch_Bemf_Flow(ST_MOTOR_TASK* pMotor)
{
    MCSQ_BEMF(&pMotor->MCSQ_CTRL.MCSQ_BEMF, &pMotor->MCSQ_CTRL.MCSQ_BLDC);
    if(pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow == SQUARE_CROSS_SUCC)
    {
        MCSQ_Freq_Cal(&pMotor->MCSQ_CTRL.MCSQ_BLDC.Freq_Cal, &pMotor->MCSQ_CTRL, MH_HALL_TIM_Count_Read());
        MH_Switch_TIM_Delay(Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BEMF._P_Q14U_Bemf_Delay_Coeff*pMotor->MCSQ_CTRL.MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_Filter));
    }
}
 
/**********************************************************************************************
Function: MotorTask_Switch_Cmp_Flow
Description: 电机控制比较换向
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Switch_Cmp_Flow(ST_MOTOR_TASK* pMotor)
{
    
}

/**********************************************************************************************
Function: MotorTask_Run_Flow
Description: 电机控制运行状态
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Run_Flow(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
    {
        if(pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set == CW)
        {
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Bemf_ADC_tmp[0] = ADC_DATA_READ_U_BEMF;
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Bemf_ADC_tmp[1] = ADC_DATA_READ_V_BEMF;
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Bemf_ADC_tmp[2] = ADC_DATA_READ_W_BEMF;
        }
        else
        {
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Bemf_ADC_tmp[0] = ADC_DATA_READ_U_BEMF;
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Bemf_ADC_tmp[1] = ADC_DATA_READ_W_BEMF;
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Bemf_ADC_tmp[2] = ADC_DATA_READ_V_BEMF;
        }
        pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Iphase_ADC = ADC_DATA_READ_CURRENT;
        
        if(pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Iphase_ADC > pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Iphase_ADC_Offset)
        {
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q14U_Iphase_pu = 4*(pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Iphase_ADC - pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q12U_Iphase_ADC_Offset);
        }
        else
        {
            pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q14U_Iphase_pu = 0;
        }
        
        if(pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow == SQUARE_DIAG_ING)
        {
            MCSQ_DIAG(&pMotor->MCSQ_CTRL.MCSQ_DIAG, &pMotor->MCSQ_CTRL.MCSQ_BLDC);
        }
        else if(pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow == SQUARE_CROSS_ING)
        {
            Motor_Math_Function[pMotor->MCSQ_CTRL.MCSQ_BLDC.SW_Math](pMotor);
        }
        
        MCSQ_Ibus_Cal(&pMotor->MCSQ_CTRL);

        Q32U_ Q32U_pwm_count_tmp = MH_PWM_Count_Read();
        if((Q32U_pwm_count_tmp + pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_ADC_Sample_Value < pMotor->MCSQ_CTRL.PWM_CTRL._O_Q32U_Duty_PWMCount)
        && (Q32U_pwm_count_tmp + pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_ADC_Solve_Value < pMotor->MCSQ_CTRL.PWM_CTRL._O_Q32U_PWMCount_Set))
        {
            MH_ADC_Soft_Trigger();
        }
        else
        {
            pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Iphase.Q14I_LPF_In = pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q14U_Iphase_pu;
            LPF_Cal_T(&pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Iphase);
            
            pMotor->MCSQ_CTRL.PID_Iphase.Q14I_Rf = pMotor->MCSQ_CTRL.MCSQ_BLDC._P_Q14U_Iphase_Max_pu;
            pMotor->MCSQ_CTRL.PID_Iphase.Q14I_Fb = pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Iphase.Q14I_LPF_Out;
            PID_Inc_Cal_T(&pMotor->MCSQ_CTRL.PID_Iphase);
            pMotor->MCSQ_CTRL.PWM_CTRL._I_Q14U_Duty_Iphase = pMotor->MCSQ_CTRL.PID_Iphase.Q14I_Output;
            
            MCSQ_PWM_Freq_Switch(&pMotor->MCSQ_CTRL.PWM_CTRL);
            
            MH_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL._O_Q32U_PWMCount_Set);
            HPWMLPWM_Set[pMotor->MCSQ_CTRL.MCSQ_BLDC.Sector][pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set](pMotor->MCSQ_CTRL.PWM_CTRL._O_Q32U_Duty_PWMCount);
            
            if(pMotor->MC_ERR._I_Q14U_Iphase_Max_pu < pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q14U_Iphase_pu)
            {
                pMotor->MC_ERR._I_Q14U_Iphase_Max_pu = pMotor->MCSQ_CTRL.MCSQ_BLDC._V_Q14U_Iphase_pu;
            }
            MC_Error_Current_Flow(&pMotor->MC_ERR);
        }
    }
    else
    {
        MH_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_High_PWMCount);
        MH_HPWM_LPWM_Close();
        pMotor->Motor_Flow = MOTOR_STATE_BRAKE;
    }
}

/**********************************************************************************************
Function: MotorTask_Brake_Flow
Description: 电机控制刹车状态
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Brake_Flow(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
    {
        MH_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_High_PWMCount);
        MH_HPWM_LPWM_Close();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
    else
    {
        if(pMotor->MCSQ_CTRL.MCSQ_BRAKE._O_Q32U_Brake_Finish_Flag == 1U)
        {
            MH_HPWM_LPWM_LOpen(Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BRAKE._O_Q14U_Brake_Duty_Set*pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_High_PWMCount));
        }
        else
        {
            pMotor->Motor_Flow = MOTOR_STATE_PRE;
            MH_HPWM_LPWM_Close();
        }
    }
}

/**********************************************************************************************
Function: MotorTask_Current_Flow
Description: 电机控制电流环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Current_Flow(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->MC_ERR.Motor_Error_Flag.all != 0U)
    {
        pMotor->Motor_State_Flag.bit.motor_run_flag = 0U;
    }
    
    Motor_Flow_Function[pMotor->Motor_Flow](pMotor);
}

/**********************************************************************************************
Function: MotorTask_Switch_Flow
Description: 电机控制换向
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Switch_Flow(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_Flow == MOTOR_STATE_RUN)
    {
        if(pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow == SQUARE_CROSS_SUCC)
        {
            MH_Switch_TIM_Stop();
            pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow = SQUARE_SWITCH_SUCC;
            pMotor->MCSQ_CTRL.MCSQ_BLDC.Sector = Next_Sector[pMotor->MCSQ_CTRL.MCSQ_BLDC.Sector];
            HPWMLPWM_Set[pMotor->MCSQ_CTRL.MCSQ_BLDC.Sector][pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set](pMotor->MCSQ_CTRL.PWM_CTRL._O_Q32U_Duty_PWMCount);
            MH_Switch_TIM_Delay(pMotor->MCSQ_CTRL.PWM_CTRL._P_Q32U_Tim_Delay_Value);
        }
        else if(pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow == SQUARE_SWITCH_SUCC)
        {
            MH_Switch_TIM_Stop();
            pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow = SQUARE_DIAG_ING;
        }
    }
    else
    {
        MH_Switch_TIM_Stop();
    }
}

/**********************************************************************************************
Function: MotorTask_PWM_Start_ADC_Flow
Description: 电机控制首次触发ADC
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_PWM_Start_ADC_Flow(ST_MOTOR_TASK* pMotor)
{
    MH_ADC_Soft_Trigger();
}

/**********************************************************************************************
Function: MotorTask_Shut_Flow
Description: 电机控制故障关断
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Shut_Flow(ST_MOTOR_TASK* pMotor)
{
    MH_HPWM_LPWM_Close();
    MC_Error_Short_Flow(&pMotor->MC_ERR);
}
