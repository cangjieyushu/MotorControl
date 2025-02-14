/**************************************************************************************************
*     File Name :                        MotorTask.c
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机子任务源文件
**************************************************************************************************/
#include "MotorTask.h"

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
    
void MotorTask_Switch_Current_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Switch_Flux_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Switch_Bemf_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Switch_Cmp_Flow(ST_MOTOR_TASK* pMotor);

pMOTOR_FUN Motor_Math_Function[SWITCH_CMP+1] = 
{
    MotorTask_Switch_Flux_Flow,
    MotorTask_Switch_Bemf_Flow,
    MotorTask_Switch_Cmp_Flow
};

void MotorTask_Diag_Ing_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Cross_Ing_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Cross_Succ_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_Switch_Succ_Flow(ST_MOTOR_TASK* pMotor);

pMOTOR_FUN Motor_Switch_Function[SQUARE_SWITCH_SUCC+1] = 
{
    MotorTask_Diag_Ing_Flow,
    MotorTask_Cross_Ing_Flow,
    MotorTask_Cross_Succ_Flow,
    MotorTask_Switch_Succ_Flow
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
    if(pMotor->Motor_Flow == MOTOR_STATE_RUN)
    {
        if(pMotor->Motor_State_Flag.bit.motor_speed_flag == 1U)
        {
            pMotor->MS_CTRL.Ramp_Freq.Q32I_Target = Q32I_RHT_14(pMotor->MS_CTRL.PWM_CTRL._I_Q14I_duty_vr
            *(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_motor_freq_max - pMotor->MS_CTRL.PWM_CTRL._P_Q14U_motor_freq_min)
            + Q16I_LFT_14(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_motor_freq_min));
            
            Ramp_Cal_T(&pMotor->MS_CTRL.Ramp_Freq);
            
            pMotor->MS_CTRL.PID_Freq.Q14I_Rf = pMotor->MS_CTRL.Ramp_Freq.Q32I_Output;
            pMotor->MS_CTRL.PID_Freq.Q14I_Fb = pMotor->MS_CTRL.FL_Freq.Q16I_Filter_out;
            PID_Inc_Cal_T(&pMotor->MS_CTRL.PID_Freq);
            
            pMotor->MS_CTRL.PWM_CTRL._I_Q12I_duty_freq = pMotor->MS_CTRL.PID_Freq.Q14I_Output;
        }
        else
        {
            pMotor->MS_CTRL.PWM_CTRL._I_Q12I_duty_freq = Q32I_RHT_14(pMotor->MS_CTRL.PWM_CTRL._I_Q14I_duty_vr
            *(pMotor->MS_CTRL.PWM_CTRL._P_Q12U_duty_max - pMotor->MS_CTRL.PWM_CTRL._P_Q12U_duty_min)
            + Q16I_LFT_14(pMotor->MS_CTRL.PWM_CTRL._P_Q12U_duty_min));
        }
        
        if(pMotor->Motor_State_Flag.bit.motor_busA_flag == 1U)
        {
            pMotor->MS_CTRL.PID_Ibus.Q14I_Rf = pMotor->MS_CTRL.Q14U_ibus_max_pu;;
            pMotor->MS_CTRL.PID_Ibus.Q14I_Fb = pMotor->MS_CTRL.FL_Ibus.Q16I_Filter_out;
            PID_Inc_Cal_T(&pMotor->MS_CTRL.PID_Ibus);
            
            pMotor->MS_CTRL.PWM_CTRL._I_Q12I_duty_ibus = pMotor->MS_CTRL.PID_Ibus.Q14I_Output;
        }
        else if(pMotor->Motor_State_Flag.bit.motor_busP_flag == 1U)
        {
        
            pMotor->MS_CTRL.PID_Ibus.Q14I_Rf = Q32I_RHT_14(pMotor->MS_CTRL.Q14U_ibus_max_pu*pMotor->MS_CTRL.Q14U_vbus_max_pu);
            pMotor->MS_CTRL.PID_Ibus.Q14I_Fb = Q32I_RHT_14(pMotor->MS_CTRL.FL_Ibus.Q16I_Filter_out*pMotor->MS_CTRL.Q12I_VBUS_PU);
            PID_Inc_Cal_T(&pMotor->MS_CTRL.PID_Ibus);
            
            pMotor->MS_CTRL.PWM_CTRL._I_Q12I_duty_ibus = pMotor->MS_CTRL.PID_Ibus.Q14I_Output;
        }
        else
        {
            pMotor->MS_CTRL.PWM_CTRL._I_Q12I_duty_ibus = pMotor->MS_CTRL.PWM_CTRL._P_Q12U_duty_max;
        }
        
        pMotor->Motor_Error_Flag.bit.motor_stall = MotorSQ_Stall_Check(&pMotor->MS_CTRL.STALL_CTRL, &pMotor->MS_CTRL);
    }
    else if(pMotor->Motor_Flow == MOTOR_STATE_BRAKE)
    {
        if(MotorSQ_Brake(&pMotor->BRAKE_CTRL) == SUCS)
        {
            pMotor->Motor_Flow = MOTOR_STATE_PRE;
        }
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
        MH_PWM_Preload_Enable();
        MH_PWM_Freq_Set(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_start_pwm_freq);
        MotorSQ_Init(&pMotor->MS_CTRL);
        pMotor->BRAKE_CTRL.Flag.bit.b0_init = 0U;
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
        if(pMotor->Q32U_MOS_Error_cnt >= 3U)
        {
            pMotor->Motor_Error_Flag.bit.mos_fault = 1U;
        }
    
        if(MotorSQ_Offset_Check_Init(&pMotor->MS_OFFSET) == SUCS)
        {
            pMotor->MS_OFFSET._I_Q12I_IPHASE_ADC = ADC_DATA_READ_CURRENT;
            switch(MotorSQ_Offset_Check(&pMotor->MS_OFFSET))
            {
                case ING:
                {
                    MH_ADC_Soft_Trigger();
                    break;
                }
                case SUCS:
                {
                    pMotor->MS_CTRL.Q12I_IPHASE_OFFSET = pMotor->MS_OFFSET._O_Q12I_IPHASE_OFFSET;
                    pMotor->Motor_Flow = MOTOR_STATE_IDLE;
                    break;
                }
                case FAIL:
                {
                    pMotor->Motor_Error_Flag.bit.current_offset = 1U;
                    pMotor->Motor_Flow = MOTOR_STATE_PRE;
                    break;
                }
                default:break;
            }
        }
        else
        {
            MH_HPWM_LPWM_Close();
            MH_ADC_Soft_Trigger();
        }
    }
    else
    {
        MH_PWM_Freq_Set(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_high_pwm_freq);
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
        if(MotorSQ_Flying_Check_Init(&pMotor->MS_FLYING) == SUCS)
        {
            if(pMotor->MS_CTRL.DIR_Set == CW)
            {
                pMotor->MS_FLYING._I_Q12I_BEMF_U_ADC = ADC_DATA_READ_U_BEMF;
                pMotor->MS_FLYING._I_Q12I_BEMF_V_ADC = ADC_DATA_READ_V_BEMF;
                pMotor->MS_FLYING._I_Q12I_BEMF_W_ADC = ADC_DATA_READ_W_BEMF;
            }
            else
            {
                pMotor->MS_FLYING._I_Q12I_BEMF_U_ADC = ADC_DATA_READ_U_BEMF;
                pMotor->MS_FLYING._I_Q12I_BEMF_V_ADC = ADC_DATA_READ_W_BEMF;
                pMotor->MS_FLYING._I_Q12I_BEMF_W_ADC = ADC_DATA_READ_V_BEMF;
            }

            pMotor->MS_CTRL.FREQ_CAL._I_Q32U_time_count = MH_HALL_TIM_Count_Read();
            switch(MotorSQ_Flying_Check(&pMotor->MS_FLYING, &pMotor->MS_CTRL.FREQ_CAL, &pMotor->MS_CTRL))
            {
                case ING:
                {
                    MH_ADC_Soft_Trigger();
                    break;
                }
                case SUCS:
                {
                    MotorSQ_Flying_Init(&pMotor->MS_CTRL, &pMotor->MS_FLYING);
                    MH_PWM_Freq_Set(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_high_pwm_freq);
                    HPWMLPWM_Set[pMotor->MS_CTRL.Sector][pMotor->MS_CTRL.DIR_Set](pMotor->MS_CTRL.PWM_CTRL._O_Q16U_duty_final_val);
                    pMotor->Motor_Flow = MOTOR_STATE_RUN;
                    break;
                }
                case FAIL:
                {
                    pMotor->Motor_Flow = MOTOR_STATE_BOOT;
                    break;
                }
                default:break;
            }
        }
        else
        {
            MH_HPWM_LPWM_Close();
            MH_ADC_Soft_Trigger();
        }
    }
    else
    {
        MH_PWM_Freq_Set(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_high_pwm_freq);
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
        if(MotorSQ_Boot_Check_Init(&pMotor->MS_BOOT) == SUCS)
        {
            pMotor->MS_BOOT._I_Q12I_BEMF_U_ADC = ADC_DATA_READ_U_BEMF;
            pMotor->MS_BOOT._I_Q12I_BEMF_V_ADC = ADC_DATA_READ_V_BEMF;
            pMotor->MS_BOOT._I_Q12I_BEMF_W_ADC = ADC_DATA_READ_W_BEMF;

            switch(MotorSQ_Boot_Check(&pMotor->MS_BOOT))
            {
                case ING:
                {
                    MH_HPWM_LPWM_LOpen(Q32I_RHT_12(pMotor->MS_BOOT._P_Q12U_boot_duty*pMotor->MS_CTRL.PWM_CTRL._P_Q14U_start_pwm_freq));
                    break;
                }
                case SUCS:
                {
                    MH_HPWM_LPWM_Close();
                    pMotor->Motor_Flow = MOTOR_STATE_POSITION;
                    break;
                }
                case FAIL:
                {
                    MH_HPWM_LPWM_Close();
                    pMotor->Motor_Flow = MOTOR_STATE_PRE;
                    break;
                }
                default:break;
            }
        }
        else
        {
            MH_PWM_Freq_Set(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_start_pwm_freq);
            MH_HPWM_LPWM_HOpen(Q32I_RHT_12(pMotor->MS_BOOT._P_Q12U_boot_duty*pMotor->MS_CTRL.PWM_CTRL._P_Q14U_start_pwm_freq));
            MH_ADC_TrigTime_Set(Q32I_RHT_12(pMotor->MS_BOOT._P_Q12U_boot_duty*pMotor->MS_CTRL.PWM_CTRL._P_Q14U_start_pwm_freq));
        }
    }
    else
    {
        MH_PWM_Freq_Set(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_high_pwm_freq);
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
        pMotor->MS_POSITION._V_Q12U_duty_set = Q32I_RHT_12(pMotor->MS_POSITION._P_Q12U_vbus_max_val
        *pMotor->MS_CTRL.PWM_CTRL._P_Q14U_start_pwm_freq/pMotor->MS_CTRL.Q12I_VBUS_VAL*pMotor->MS_POSITION._P_Q12U_position_duty);
        
        if(MotorSQ_Pluse_Positon_Init(&pMotor->MS_POSITION) == SUCS)
        {
            pMotor->MS_POSITION._I_Q12I_Position_Current_VAL[pMotor->MS_POSITION._V_Q32U_cnt] = ADC_DATA_READ_CURRENT;
            
            switch(MotorSQ_Pluse_Positon(&pMotor->MS_POSITION, &pMotor->MS_CTRL))
            {
                case ING:
                {
                    POSITION_Set[pMotor->MS_POSITION._V_Q32U_cnt][pMotor->MS_CTRL.DIR_Set](pMotor->MS_POSITION._V_Q12U_duty_set);
                    break;
                }
                case SUCS:
                {
                    MH_PWM_Preload_Disable();
                    MH_PWM_Freq_Set(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_low_pwm_freq);
                    MH_ADC_TrigTime_Set(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_adc_delay_value);
                    pMotor->Motor_Flow = MOTOR_STATE_RUN;
                    break;
                }
                case FAIL:
                {
                    pMotor->Motor_Error_Flag.bit.position_error = 1U;
                    pMotor->Motor_Flow = MOTOR_STATE_PRE;
                    break;
                }
                default:break;
            }
        }
        else
        {
            POSITION_Set[0][pMotor->MS_CTRL.DIR_Set](pMotor->MS_POSITION._V_Q12U_duty_set);
            MH_ADC_TrigTime_Set(pMotor->MS_POSITION._V_Q12U_duty_set - 2*pMotor->MS_CTRL.PWM_CTRL._P_Q14U_adc_sample_value);
        }
    }
    else
    {
        MH_PWM_Freq_Set(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_high_pwm_freq);
        MH_HPWM_LPWM_Close();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**********************************************************************************************
Function: MotorTask_Diag_Ing_Flow
Description: 电机控制续流检测
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Diag_Ing_Flow(ST_MOTOR_TASK* pMotor)
{
    MotorSQ_DIAG_Zero_Cross(&pMotor->MS_CTRL.MS_DIAG, &pMotor->MS_CTRL);
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
    MotorSQ_FLUX_Zero_Cross(&pMotor->MS_CTRL.MS_FLUX, &pMotor->MS_CTRL);
    if(pMotor->MS_CTRL.SQ_Flow == SQUARE_CROSS_SUCC)
    {
        pMotor->MS_CTRL.FREQ_CAL._I_Q32U_time_count = MH_HALL_TIM_Count_Read();
        MotorSQ_Freq_Cal(&pMotor->MS_CTRL.FREQ_CAL, &pMotor->MS_CTRL);
        MH_Switch_TIM_Delay(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_tim_delay_min_value);
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
    MotorSQ_BEMF_Zero_Cross(&pMotor->MS_CTRL.MS_BEMF, &pMotor->MS_CTRL);
    if(pMotor->MS_CTRL.SQ_Flow == SQUARE_CROSS_SUCC)
    {
        pMotor->MS_CTRL.FREQ_CAL._I_Q32U_time_count = MH_HALL_TIM_Count_Read();
        MotorSQ_Freq_Cal(&pMotor->MS_CTRL.FREQ_CAL, &pMotor->MS_CTRL);
        MH_Switch_TIM_Delay(Q32I_RHT_06(pMotor->MS_CTRL.MS_BEMF._P_Q06U_coeff*pMotor->MS_CTRL.FREQ_CAL._O_Q32U_60_degree_cnt));
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
Function: MotorTask_Cross_Ing_Flow
Description: 电机控制过零检测
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Cross_Ing_Flow(ST_MOTOR_TASK* pMotor)
{
    Motor_Math_Function[pMotor->MS_CTRL.SW_Math](pMotor);
}

/**********************************************************************************************
Function: MotorTask_Cross_Succ_Flow
Description: 电机控制过零成功
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Cross_Succ_Flow(ST_MOTOR_TASK* pMotor)
{
    MH_Switch_TIM_Stop();
    pMotor->MS_CTRL.SQ_Flow = SQUARE_SWITCH_SUCC;
    pMotor->MS_CTRL.Sector = Next_Sector[pMotor->MS_CTRL.Sector];
    HPWMLPWM_Set[pMotor->MS_CTRL.Sector][pMotor->MS_CTRL.DIR_Set](pMotor->MS_CTRL.PWM_CTRL._O_Q16U_duty_final_val);
    MH_Switch_TIM_Delay(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_tim_delay_min_value);
}

/**********************************************************************************************
Function: MotorTask_Switch_Succ_Flow
Description: 电机控制切换成功
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Switch_Succ_Flow(ST_MOTOR_TASK* pMotor)
{
    pMotor->MS_CTRL.SQ_Flow = SQUARE_DIAG_ING;
    MH_Switch_TIM_Stop();
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
        if(pMotor->MS_CTRL.DIR_Set == CW)
        {
            pMotor->MS_CTRL.Q12I_BEMF_ADC_tmp[0] = ADC_DATA_READ_U_BEMF;
            pMotor->MS_CTRL.Q12I_BEMF_ADC_tmp[1] = ADC_DATA_READ_V_BEMF;
            pMotor->MS_CTRL.Q12I_BEMF_ADC_tmp[2] = ADC_DATA_READ_W_BEMF;
        }
        else
        {
            pMotor->MS_CTRL.Q12I_BEMF_ADC_tmp[0] = ADC_DATA_READ_U_BEMF;
            pMotor->MS_CTRL.Q12I_BEMF_ADC_tmp[1] = ADC_DATA_READ_W_BEMF;
            pMotor->MS_CTRL.Q12I_BEMF_ADC_tmp[2] = ADC_DATA_READ_V_BEMF;
        }
        pMotor->MS_CTRL.Q12I_IPHASE_ADC = ADC_DATA_READ_CURRENT;
        
        if(pMotor->MS_CTRL.Q12I_IPHASE_ADC > pMotor->MS_CTRL.Q12I_IPHASE_OFFSET)
        {
            pMotor->MS_CTRL.Q14I_IPHASE_PU = Q32I_RHT_10(pMotor->MS_CTRL._P_Q32U_Current_Scale
            *(pMotor->MS_CTRL.Q12I_IPHASE_ADC - pMotor->MS_CTRL.Q12I_IPHASE_OFFSET));
        }
        else
        {
            pMotor->MS_CTRL.Q14I_IPHASE_PU = 0U;
        }
        
        Motor_Switch_Function[pMotor->MS_CTRL.SQ_Flow](pMotor);
        
        MotorSQ_Ibus_Cal(&pMotor->MS_CTRL);

        Q32U_ Q32U_pwm_count_tmp = MH_PWM_Count_Read();
        if((Q32U_pwm_count_tmp + pMotor->MS_CTRL.PWM_CTRL._P_Q14U_adc_sample_value < pMotor->MS_CTRL.PWM_CTRL._O_Q16U_duty_final_val)
        && (Q32U_pwm_count_tmp + pMotor->MS_CTRL.PWM_CTRL._P_Q14U_adc_solve_value < pMotor->MS_CTRL.PWM_CTRL._O_Q16U_arr_set))
        {
            MH_ADC_Soft_Trigger();
        }
        else
        {
            pMotor->MS_CTRL.FL_Iphase.Q16I_Filter_in = pMotor->MS_CTRL.Q14I_IPHASE_PU;
            Filter_Cal_T(&pMotor->MS_CTRL.FL_Iphase);
            
            pMotor->MS_CTRL.PID_Iphase.Q14I_Rf = pMotor->MS_CTRL.Q14U_iphase_max_pu;
            pMotor->MS_CTRL.PID_Iphase.Q14I_Fb = pMotor->MS_CTRL.FL_Iphase.Q16I_Filter_out;
            PID_Inc_Cal_T(&pMotor->MS_CTRL.PID_Iphase);
            pMotor->MS_CTRL.PWM_CTRL._I_Q12I_duty_iphase = pMotor->MS_CTRL.PID_Iphase.Q14I_Output;
            
            MotorSQ_PWM_Freq_Switch(&pMotor->MS_CTRL.PWM_CTRL);
            
            MH_PWM_Freq_Set(pMotor->MS_CTRL.PWM_CTRL._O_Q16U_arr_set);
            HPWMLPWM_Set[pMotor->MS_CTRL.Sector][pMotor->MS_CTRL.DIR_Set](pMotor->MS_CTRL.PWM_CTRL._O_Q16U_duty_final_val);
            
            if(pMotor->Q14I_IPHASE_MAX_PU < pMotor->Q14I_IPHASE_MAX_PU)
            {
                pMotor->Q14I_IPHASE_MAX_PU = pMotor->Q14I_IPHASE_MAX_PU;
            }
        }
    }
    else
    {
        MH_PWM_Freq_Set(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_high_pwm_freq);
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
        MH_PWM_Freq_Set(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_high_pwm_freq);
        MH_HPWM_LPWM_Close();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
    else
    {
        if(MotorSQ_Brake_Init(&pMotor->BRAKE_CTRL) == SUCS)
        {
            MH_HPWM_LPWM_LOpen(Q32I_RHT_12(pMotor->BRAKE_CTRL._O_Q12U_brake_duty*pMotor->MS_CTRL.PWM_CTRL._P_Q14U_high_pwm_freq));
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
    if(pMotor->Motor_Error_Flag.all != 0U)
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
        Motor_Switch_Function[pMotor->MS_CTRL.SQ_Flow](pMotor);
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
    pMotor->Q32U_MOS_Error_cnt++;
    pMotor->Motor_Error_Flag.bit.current_short = 1U;
}
