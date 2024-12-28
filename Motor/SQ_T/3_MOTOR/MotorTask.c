/**************************************************************************************************
*     File Name :                        MotorTask.c
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机子任务源文件
**************************************************************************************************/
#include "MotorTask.h"

#if(SYS_RECTIFICAITON == 0)
#define pFUN_PWM_OUTPUT     HPWMLGPIO_SET
#define pPWM_SET_INIT       MH_HPWM_LGPIO_Init
#else
#define pFUN_PWM_OUTPUT     HPWMLPWM_SET
#define pPWM_SET_INIT       MH_HPWM_LPWM_Init
#endif

pFUN_HPWMLGPIO_OUT HPWMLGPIO_SET[6][2] =
{
    MH_HPWM_LGPIO_UpVn, MH_HPWM_LGPIO_UpWn,//U+V-
    MH_HPWM_LGPIO_UpWn, MH_HPWM_LGPIO_UpVn,//U+W-
    MH_HPWM_LGPIO_VpWn, MH_HPWM_LGPIO_WpVn,//V+W-
    MH_HPWM_LGPIO_VpUn, MH_HPWM_LGPIO_WpUn,//V+U-
    MH_HPWM_LGPIO_WpUn, MH_HPWM_LGPIO_VpUn,//W+U-
    MH_HPWM_LGPIO_WpVn, MH_HPWM_LGPIO_VpWn,//W+V-
};

pFUN_HPWMLPWM_OUT HPWMLPWM_SET[6][2] =
{
    MH_HPWM_LPWM_UpVn, MH_HPWM_LPWM_UpWn,//U+V-
    MH_HPWM_LPWM_UpWn, MH_HPWM_LPWM_UpVn,//U+W-
    MH_HPWM_LPWM_VpWn, MH_HPWM_LPWM_WpVn,//V+W-
    MH_HPWM_LPWM_VpUn, MH_HPWM_LPWM_WpUn,//V+U-
    MH_HPWM_LPWM_WpUn, MH_HPWM_LPWM_VpUn,//W+U-
    MH_HPWM_LPWM_WpVn, MH_HPWM_LPWM_VpWn,//W+V-
};

/**********************************************************************************************
Function: MotorTask_Freq_Flow
Description: 电机控制速度环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Freq_Flow(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_Flow == MOTOR_STATE_RUN)
    {
#if(SPEED_CLOSE_EN == 1)
        pMotor->MS_CTRL.Ramp_Freq.Q32I_Target = Q32I_RHT_14(pMotor->MS_CTRL.PWM_CTRL._I_Q14I_duty_vr
        *(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_motor_freq_max - pMotor->MS_CTRL.PWM_CTRL._P_Q14U_motor_freq_min)
                                              + Q16I_LFT_14(pMotor->MS_CTRL.PWM_CTRL._P_Q14U_motor_freq_min));
        
        Ramp_Cal(&pMotor->MS_CTRL.Ramp_Freq);
        
        pMotor->MS_CTRL.PID_Freq.Q14I_Rf = pMotor->MS_CTRL.Ramp_Freq.Q32I_Output;
        pMotor->MS_CTRL.PID_Freq.Q14I_Fb = pMotor->MS_CTRL.FL_Freq.Q16I_Filter_out;
        PID_Inc_Cal(&pMotor->MS_CTRL.PID_Freq);
        
        pMotor->MS_CTRL.PWM_CTRL._I_Q12I_duty_freq = pMotor->MS_CTRL.PID_Freq.Q14I_Output;
#else
        pMotor->MS_CTRL.PWM_CTRL._I_Q12I_duty_freq = Q32I_RHT_14(pMotor->MS_CTRL.PWM_CTRL._I_Q14I_duty_vr
        *(pMotor->MS_CTRL.PWM_CTRL._P_Q12U_duty_max - pMotor->MS_CTRL.PWM_CTRL._P_Q12U_duty_min)
        + Q16I_LFT_15(pMotor->MS_CTRL.PWM_CTRL._P_Q12U_duty_min));
#endif          
        
#if(IBUS_CLOSE_EN == 1)
        pMotor->MS_CTRL.PID_Ibus.Q14I_Rf = pMotor->MS_CTRL.Q14U_ibus_max_pu;;
        pMotor->MS_CTRL.PID_Ibus.Q14I_Fb = pMotor->MS_CTRL.FL_Ibus.Q16I_Filter_out;
        PID_Inc_Cal(&pMotor->MS_CTRL.PID_Ibus);
        
        pMotor->MS_CTRL.PWM_CTRL._I_Q12I_duty_ibus = pMotor->MS_CTRL.PID_Ibus.Q14I_Output;
#elif(IBUS_CLOSE_EN == 2)
        pMotor->MS_CTRL.PID_Ibus.Q14I_Rf = Q32I_RHT_14(pMotor->MS_CTRL.Q14U_ibus_max_pu
        *pMotor->MS_CTRL.Q14U_vbus_max_pu);
        pMotor->MS_CTRL.PID_Ibus.Q14I_Fb = Q32I_RHT_14(pMotor->MS_CTRL.FL_Ibus.Q16I_Filter_out
        *Q14I_VOLTAGE_LSB_TO_PU(pMotor->MS_CTRL.Q12I_VBUS_VAL));
        PID_Inc_Cal(&pMotor->MS_CTRL.PID_Ibus);
        
        pMotor->MS_CTRL.PWM_CTRL._I_Q12I_duty_ibus = pMotor->MS_CTRL.PID_Ibus.Q14I_Output;
        
#else
        pMotor->MS_CTRL.PWM_CTRL._I_Q12I_duty_ibus = pMotor->MS_CTRL.PWM_CTRL._P_Q12U_duty_max;
#endif   
        
        pMotor->Motor_Error_Flag.bit.motor_stall = MotorSQ_Stall_Check(&pMotor->MS_CTRL.STALL_CTRL, &pMotor->MS_CTRL);
    }
    else if(pMotor->Motor_Flow == MOTOR_STATE_BRAKE)
    {
        if(MotorSQ_Brake_Init(&pMotor->BRAKE_CTRL, &pMotor->MS_CTRL) == SUCC)
        {
            if(MotorSQ_Brake(&pMotor->BRAKE_CTRL, &pMotor->MS_CTRL) == SUCC)
            {
                pMotor->Motor_Flow = MOTOR_STATE_PRE;
            }
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
Ram_Func void MotorTask_Current_Flow(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_Error_Flag.all != 0U)
    {
        pMotor->Motor_State_Flag.bit.motor_run_flag = 0U;
    }
    
    switch(pMotor->Motor_Flow)
    {
        case MOTOR_STATE_PRE:
        {
            MH_HPWM_LPWM_Init(PWM_FREQ_START);
            MH_HPWM_LPWM_Close();
            MotorSQ_Init(&pMotor->MS_CTRL);
            pMotor->Motor_Flow = MOTOR_STATE_INIT;
        }break;
        case MOTOR_STATE_INIT:
        {
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                if(MotorSQ_Offset_Check_Init(&pMotor->MS_OFFSET) == SUCC)
                {
                    pMotor->MS_OFFSET._I_Q12I_IPHASE_ADC = ADC_DATA_READ_CURRENT;
                    switch(MotorSQ_Offset_Check(&pMotor->MS_OFFSET))
                    {
                        case ING:
                        {
                            MH_ADC_Soft_Trigger();
                        }break;
                        case SUCC:
                        {
                            pMotor->MS_CTRL.Q12I_IPHASE_OFFSET = pMotor->MS_OFFSET._O_Q12I_IPHASE_OFFSET;
                            pMotor->Motor_Flow = MOTOR_STATE_IDLE;
                        }break;
                        case FAIL:
                        {
                            pMotor->Motor_Error_Flag.bit.current_offset = 1U;
                            pMotor->Motor_Flow = MOTOR_STATE_PRE;
                        }break;
                        default:break;
                    }
                }
                else
                {
                    MH_HPWM_LPWM_Close();
                    MH_ADC_Soft_Trigger();
                }
            }
        }break;
        case MOTOR_STATE_IDLE:
        {
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                if(MotorSQ_Flying_Check_Init(&pMotor->MS_FLYING) == SUCC)
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

                    pMotor->MS_CTRL.FREQ_CAL._I_Q32U_time_count = MH_HALL_TIM_Read_Count();
                    switch(MotorSQ_Flying_Check(&pMotor->MS_FLYING, &pMotor->MS_CTRL.FREQ_CAL, &pMotor->MS_CTRL))
                    {
                        case ING:
                        {
                            MH_ADC_Soft_Trigger();
                        }break;
                        case SUCC:
                        {
                            MotorSQ_Flying_Init(&pMotor->MS_CTRL, &pMotor->MS_FLYING);
                            pPWM_SET_INIT(PWM_FREQ_HIGH);
                            pFUN_PWM_OUTPUT[pMotor->MS_CTRL.Sector][pMotor->MS_CTRL.DIR_Set](pMotor->MS_CTRL.PWM_CTRL._O_Q16U_duty_final_val);
                            MH_Switch_TIM_Delay(HAL_TIM_DELAY_VALUE);
                            pMotor->Motor_Flow = MOTOR_STATE_RUN;
                        }break;
                        case FAIL:
                        {
                            pMotor->Motor_Flow = MOTOR_STATE_BOOT;
                        }break;
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
                pMotor->Motor_Flow = MOTOR_STATE_PRE;
            }
        }break;
        case MOTOR_STATE_BOOT:
        {
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                if(MotorSQ_Boot_Check_Init(&pMotor->MS_BOOT) == SUCC)
                {
                    pMotor->MS_BOOT._I_Q12I_BEMF_U_ADC = ADC_DATA_READ_U_BEMF;
                    pMotor->MS_BOOT._I_Q12I_BEMF_V_ADC = ADC_DATA_READ_V_BEMF;
                    pMotor->MS_BOOT._I_Q12I_BEMF_W_ADC = ADC_DATA_READ_W_BEMF;

                    switch(MotorSQ_Boot_Check(&pMotor->MS_BOOT))
                    {
                        case ING:
                        {
                            MH_HPWM_LPWM_LOpen(Q32I_RHT_12(pMotor->MS_BOOT._P_Q12U_boot_duty*PWM_FREQ_START));
                        }break;
                        case SUCC:
                        {
                            MH_HPWM_LPWM_Close();
                            pMotor->Motor_Flow = MOTOR_STATE_POSITION;
                        }break;
                        case FAIL:
                        {
                            MH_HPWM_LPWM_Close();
                            pMotor->Motor_Flow = MOTOR_STATE_PRE;
                        }break;
                        default:break;
                    }
                }
                else
                {
                    MH_HPWM_LPWM_Init(PWM_FREQ_START);
                    MH_HPWM_LPWM_HOpen(Q32I_RHT_12(pMotor->MS_BOOT._P_Q12U_boot_duty*PWM_FREQ_START));
                    MH_ADC_Trigger_Delay_Time(Q32I_RHT_12(pMotor->MS_BOOT._P_Q12U_boot_duty*PWM_FREQ_START));
                }
            }
            else
            {
                pMotor->Motor_Flow = MOTOR_STATE_PRE;
            }
        }break;
        case MOTOR_STATE_POSITION:
        {
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                MH_HPWM_LPWM_Close();
                pMotor->MS_POSITION._V_Q12U_duty_set = Q32I_RHT_12(pMotor->MS_POSITION._P_Q12U_vbus_max_val
                *PWM_FREQ_START/pMotor->MS_CTRL.Q12I_VBUS_VAL*pMotor->MS_POSITION._P_Q12U_position_duty);
                
                if(MotorSQ_Pluse_Positon_Init(&pMotor->MS_POSITION) == SUCC)
                {
                    pMotor->MS_POSITION._I_Q12I_Position_Current_VAL[pMotor->MS_POSITION._V_Q32U_cnt] = ADC_DATA_READ_CURRENT;
                    
                    switch(MotorSQ_Pluse_Positon(&pMotor->MS_POSITION, &pMotor->MS_CTRL))
                    {
                        case ING:
                        {
                            HPWMLPWM_SET[pMotor->MS_POSITION._V_Q32U_cnt][pMotor->MS_CTRL.DIR_Set](pMotor->MS_POSITION._V_Q12U_duty_set);
                        }break;
                        case SUCC:
                        {
                            pPWM_SET_INIT(PWM_FREQ_LOW);
                            MH_ADC_Trigger_Delay_Time(HAL_ADC_DELAY_VALUE);
                            pMotor->Motor_Flow = MOTOR_STATE_RUN;
                        }break;
                        case FAIL:
                        {
                            pMotor->Motor_Error_Flag.bit.position_error = 1U;
                            MH_HPWM_LPWM_Close();
                            pMotor->Motor_Flow = MOTOR_STATE_PRE;
                        }break;
                        default:break;
                    }
                }
                else
                {
                    HPWMLPWM_SET[0][pMotor->MS_CTRL.DIR_Set](pMotor->MS_POSITION._V_Q12U_duty_set);
                    MH_ADC_Trigger_Delay_Time(pMotor->MS_POSITION._V_Q12U_duty_set - (HAL_ADC_SAMPLE_VALUE));
                }
            }
            else
            {
                pMotor->Motor_Flow = MOTOR_STATE_PRE;
            }
        }break;
        case MOTOR_STATE_RUN:
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
                    pMotor->MS_CTRL.Q14I_IPHASE_PU = Q14I_CURRENT_LSB_TO_PU(pMotor->MS_CTRL.Q12I_IPHASE_ADC - pMotor->MS_CTRL.Q12I_IPHASE_OFFSET);
                }
                else
                {
                    pMotor->MS_CTRL.Q14I_IPHASE_PU = 0U;
                }
                
                if(pMotor->MS_CTRL.SQ_Flow == SQUARE_DIAG_ING)
                {
                    MotorSQ_DIAG_Zero_Cross(&pMotor->MS_CTRL.MS_DIAG, &pMotor->MS_CTRL);
                }
                else if(pMotor->MS_CTRL.SQ_Flow == SQUARE_CROSS_ING)
                {
                    switch(pMotor->MS_CTRL.SW_Math)
                    {
                        case SWITCH_CURRENT:
                        {
                            MotorSQ_CURRENT_Zero_Cross(&pMotor->MS_CTRL.MS_CURRENT, &pMotor->MS_CTRL);
                            if(pMotor->MS_CTRL.SQ_Flow == SQUARE_CROSS_SUCC)
                            {
                                pMotor->MS_CTRL.FREQ_CAL._I_Q32U_time_count = MH_HALL_TIM_Read_Count();
                                MotorSQ_Freq_Cal(&pMotor->MS_CTRL.FREQ_CAL, &pMotor->MS_CTRL);
                                MH_Switch_TIM_Delay(HAL_TIM_DELAY_VALUE);
                                pMotor->MS_CTRL.SQ_Flow = SQUARE_SWITCH_ING;
                            }
                        }break;
                        case SWITCH_FLUX:
                        {
                            MotorSQ_FLUX_Zero_Cross(&pMotor->MS_CTRL.MS_FLUX, &pMotor->MS_CTRL);
                            if(pMotor->MS_CTRL.SQ_Flow == SQUARE_CROSS_SUCC)
                            {
                                pMotor->MS_CTRL.FREQ_CAL._I_Q32U_time_count = MH_HALL_TIM_Read_Count();
                                MotorSQ_Freq_Cal(&pMotor->MS_CTRL.FREQ_CAL, &pMotor->MS_CTRL);
                                MH_Switch_TIM_Delay(HAL_TIM_DELAY_VALUE);
                                pMotor->MS_CTRL.SQ_Flow = SQUARE_SWITCH_ING;
                            }
                        }break;
                        case SWITCH_BEMF:
                        {
                            MotorSQ_BEMF_Zero_Cross(&pMotor->MS_CTRL.MS_BEMF, &pMotor->MS_CTRL);
                            if(pMotor->MS_CTRL.SQ_Flow == SQUARE_CROSS_SUCC)
                            {
                                pMotor->MS_CTRL.FREQ_CAL._I_Q32U_time_count = MH_HALL_TIM_Read_Count();
                                MotorSQ_Freq_Cal(&pMotor->MS_CTRL.FREQ_CAL, &pMotor->MS_CTRL);
                                MH_Switch_TIM_Delay(Q32I_RHT_06(pMotor->MS_CTRL.MS_BEMF._P_Q06U_coeff
                                *(pMotor->MS_CTRL.FREQ_CAL._O_Q32U_60_degree_cnt)));
                                pMotor->MS_CTRL.SQ_Flow = SQUARE_SWITCH_ING;
                            }
                        }break;
                        case SWITCH_CMP:
                        {
                            
                        }break;
                        default:break;
                    }
                }
                
                MotorSQ_Ibus_Cal(&pMotor->MS_CTRL);
                
                if(MH_PWM_Read_Count() + HAL_ADC_SOLVE_VALUE < pMotor->MS_CTRL.PWM_CTRL._O_Q16U_duty_final_val)
                {
                    MH_ADC_Soft_Trigger();
                }
                else
                {
                    pMotor->MS_CTRL.FL_Iphase.Q16I_Filter_in = pMotor->MS_CTRL.Q14I_IPHASE_PU;
                    Filter_Cal(&pMotor->MS_CTRL.FL_Iphase);
#if(IPHASE_CLOSE_EN == 1)  
                    pMotor->MS_CTRL.PID_Iphase.Q14I_Rf = pMotor->MS_CTRL.Q14U_iphase_max_pu;
                    pMotor->MS_CTRL.PID_Iphase.Q14I_Fb = pMotor->MS_CTRL.FL_Iphase.Q16I_Filter_out;
                    PID_Inc_Cal(&pMotor->MS_CTRL.PID_Iphase);
                    pMotor->MS_CTRL.PWM_CTRL._I_Q12I_duty_iphase = pMotor->MS_CTRL.PID_Iphase.Q14I_Output;
#else
                    pMotor->MS_CTRL.PWM_CTRL._I_Q12I_duty_iphase = pMotor->MS_CTRL.PWM_CTRL._P_Q12U_duty_max;
#endif                
                    
                    MotorSQ_PWM_Freq_Switch(&pMotor->MS_CTRL.PWM_CTRL);
                    
                    MH_PWM_Freq_Set(pMotor->MS_CTRL.PWM_CTRL._O_Q16U_arr_set);
                    pFUN_PWM_OUTPUT[pMotor->MS_CTRL.Sector][pMotor->MS_CTRL.DIR_Set](pMotor->MS_CTRL.PWM_CTRL._O_Q16U_duty_final_val);
                    
                    if(pMotor->Q14I_IPHASE_MAX_PU < pMotor->Q14I_IPHASE_MAX_PU)
                    {
                        pMotor->Q14I_IPHASE_MAX_PU= pMotor->Q14I_IPHASE_MAX_PU;
                    }
                }
            }
            else
            {
                MH_HPWM_LPWM_Close();
#if(BRAKE_EN == 0)
                pMotor->Motor_Flow = MOTOR_STATE_PRE;
#else
                MH_HPWM_LPWM_Init(PWM_FREQ_HIGH);
                pMotor->Motor_Flow = MOTOR_STATE_BRAKE;
#endif
            }
        }break;
        case MOTOR_STATE_BRAKE:
        {
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                pMotor->Motor_Flow = MOTOR_STATE_IDLE;
            }
            else
            {
                pMotor->MS_CTRL.Q12I_IPHASE_ADC = ADC_DATA_READ_CURRENT;
                if(pMotor->MS_CTRL.Q12I_IPHASE_ADC < pMotor->MS_CTRL.Q12I_IPHASE_OFFSET)
                {
                    pMotor->MS_CTRL.Q14I_IPHASE_PU =  Q14I_CURRENT_LSB_TO_PU(pMotor->MS_CTRL.Q12I_IPHASE_OFFSET - pMotor->MS_CTRL.Q12I_IPHASE_ADC);
                }
                else
                {
                    pMotor->MS_CTRL.Q14I_IPHASE_PU = 0U;
                }
                MH_HPWM_LPWM_LOpen(pMotor->BRAKE_CTRL._O_Q12U_brake_duty);
            }
        }break;
        default:break;
    }
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
        if(pMotor->MS_CTRL.SQ_Flow == SQUARE_SWITCH_ING)
        {
            MH_Switch_TIM_Stop();
            pMotor->MS_CTRL.SQ_Flow = SQUARE_SWITCH_SUCC;
            pMotor->MS_CTRL.Sector = Next_Sector[pMotor->MS_CTRL.Sector];
            pFUN_PWM_OUTPUT[pMotor->MS_CTRL.Sector][pMotor->MS_CTRL.DIR_Set](pMotor->MS_CTRL.PWM_CTRL._O_Q16U_duty_final_val);
            MH_Switch_TIM_Delay(HAL_TIM_DELAY_VALUE);
        }
        else if(pMotor->MS_CTRL.SQ_Flow == SQUARE_SWITCH_SUCC)
        {
            pMotor->MS_CTRL.SQ_Flow = SQUARE_DIAG_ING;
            MH_Switch_TIM_Stop();
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
}
