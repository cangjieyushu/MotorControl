/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#include "MotorTask.h"

pFUN_HPWMLPWM_OUT HPWMLPWM_SET[6][2] =
{
    MH_HPWM_LPWM_UpVn, MH_HPWM_LPWM_UpWn,//U+V-
    MH_HPWM_LPWM_UpWn, MH_HPWM_LPWM_UpVn,//U+W-
    MH_HPWM_LPWM_VpWn, MH_HPWM_LPWM_WpVn,//V+W-
    MH_HPWM_LPWM_VpUn, MH_HPWM_LPWM_WpUn,//V+U-
    MH_HPWM_LPWM_WpUn, MH_HPWM_LPWM_VpUn,//W+U-
    MH_HPWM_LPWM_WpVn, MH_HPWM_LPWM_VpWn,//W+V-
};

void MotorTask_Init(ST_MOTOR_TASK* pMotor)
{
    pMotor->ADC_Read_Flow = ADC_FIRST_READ;
    pMotor->FOC_Para.Q12I_I_Data[0] = 0;
    pMotor->FOC_Para.Q12I_I_Data[1] = 0;
    pMotor->FOC_Para.Q12I_I_Data[2] = 0;
    pMotor->FOC_Para.Q12I_I_Data[3] = 0;
    
    pMotor->Motor_Speed_Mode = OPENLOOP;
    MotorFoc_WEAK_Init(&pMotor->WEAK_Ctrl);
    MotorFoc_IF_Init(&pMotor->IF_Ctrl);
    MotorFoc_Flux_Init(&pMotor->FLUX_Ctrl);
    MotorFoc_SMO_Init(&pMotor->SMO_Ctrl);
    MotorFoc_Speed_Init(&pMotor->SRAD_Ctrl);
    MotorFoc_Current_Init(&pMotor->Current_Ctrl);
    
    pMotor->Current_Ctrl.Q12I_TADC_1 = (HAL_PWM_DUTY_30_PERCENT);
    pMotor->Current_Ctrl.Q12I_TADC_2 = (HAL_PWM_DUTY_60_PERCENT);
}

void MotorTask_Speed_Flow(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_Error_Flag.all != 0U)
    {
        pMotor->Motor_State_Flag.bit.motor_run_flag = 0U;
    }
    
    switch(pMotor->Motor_Flow)
    {
        case MOTOR_STATE_INIT:
        {
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                pMotor->Motor_State_Flag.bit.para_init_flag = 1U;
                if(pMotor->Common_Ctrl.Motor_Flag.bit.current_offset_Succ == 1U)
                {
                    MotorTask_Init(pMotor);
                    MH_HPWM_LPWM_Init((Q32U_)HAL_PWM_INIT_SET);
                    MH_PWM_Output_Enable();
                    pMotor->Motor_Flow = MOTOR_STATE_RUN;
                }
                if(pMotor->Common_Ctrl.Motor_Flag.bit.current_offset_Fail == 1U)
                {
                    MotorTask_Init(pMotor);
                    MH_HPWM_LPWM_Init((Q32U_)HAL_PWM_INIT_SET);
                    pMotor->Motor_Error_Flag.bit.current_offset = 1U;
                    pMotor->Motor_Flow = MOTOR_STATE_INIT;
                }
            }
            else
            {
                pMotor->Common_Ctrl.Motor_Flag.all = 0U;
                pMotor->Motor_State_Flag.bit.para_init_flag = 0U;
            }
        }break;
        case MOTOR_STATE_IDLE:
        {
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                if(pMotor->Common_Ctrl.Motor_Flag.bit.free_flying_Succ == 1U)
                {
                    pMotor->Motor_Flow = MOTOR_STATE_RUN;
                }
                if(pMotor->Common_Ctrl.Motor_Flag.bit.free_flying_Fail == 1U)
                {
                    pMotor->Motor_Flow = MOTOR_STATE_MOS;
                }
            }
            else
            {
                pMotor->Motor_Flow = MOTOR_STATE_INIT;
            }
        }break;
        case MOTOR_STATE_MOS:
        {
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                if(pMotor->Common_Ctrl.Motor_Flag.bit.mos_check_Succ == 1U)
                {
                    pMotor->Motor_Flow = MOTOR_STATE_BOOT;
                }
                if(pMotor->Common_Ctrl.Motor_Flag.bit.mos_check_Fail == 1U)
                {
                    pMotor->Motor_Error_Flag.bit.mos_fault = 1U;
                    pMotor->Motor_Flow = MOTOR_STATE_INIT;
                }
            }
            else
            {
                pMotor->Motor_Flow = MOTOR_STATE_INIT;
            }
        }break;
        case MOTOR_STATE_BOOT:
        {
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                if(pMotor->Common_Ctrl.Motor_Flag.bit.motor_standby_Succ == 1U)
                {
                    pMotor->Motor_Flow = MOTOR_STATE_POSITION;
                }
                if(pMotor->Common_Ctrl.Motor_Flag.bit.motor_standby_Fail == 1U)
                {
                    pMotor->Motor_Flow = MOTOR_STATE_INIT;
                }
            }
            else
            {
                pMotor->Motor_Flow = MOTOR_STATE_INIT;
            }
        }break;
        case MOTOR_STATE_POSITION:
        {
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                if(pMotor->Common_Ctrl.Motor_Flag.bit.motor_position_Succ == 1U)
                {
                    pMotor->Motor_Flow = MOTOR_STATE_RUN;
                }
                if(pMotor->Common_Ctrl.Motor_Flag.bit.motor_position_Fail == 1U)
                {
                    pMotor->Motor_Flow = MOTOR_STATE_INIT;
                }
            }
            else
            {
                pMotor->Motor_Flow = MOTOR_STATE_INIT;
            }
        }break;

        case MOTOR_STATE_RUN:
        {
#if(USER_MOTOR_SPEED_MODE == USER_MOTOR_SPEED_FLUX)
            pMotor->SRAD_Ctrl.Q14I_SRAD_Fb = pMotor->FLUX_Ctrl.FL_SRAD.Q16I_Filter_out;
#elif(USER_MOTOR_SPEED_MODE == USER_MOTOR_SPEED_SMO)
            pMotor->SRAD_Ctrl.Q14I_SRAD_Fb = pMotor->SMO_Ctrl.FL_SRAD.Q16I_Filter_out;
#endif
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                switch(pMotor->Motor_Speed_Mode)
                {
                    case OPENLOOP:
                    {
                        Ramp_Cal(&pMotor->IF_Ctrl.SRad_Ramp);
                        Ramp_Cal(&pMotor->SRAD_Ctrl.Iq_Ramp);
                        
                        pMotor->Current_Ctrl.Q14I_IdRef = pMotor->SRAD_Ctrl.Id_Ramp.Q32I_Init;
                        pMotor->Current_Ctrl.Q14I_IqRef = pMotor->SRAD_Ctrl.Iq_Ramp.Q32I_Output;
    
                        if(MATH_ABS_U(pMotor->IF_Ctrl.Est_AngleRad - pMotor->IF_Ctrl.Angle.Q12U_Angle)
                        < (pMotor->IF_Ctrl.AngleRad_Error + MATH_PI_OVER_TWO_U))
                        {
                            if(++pMotor->IF_Ctrl.AngleRad_cnt > pMotor->IF_Ctrl.AngleRad_time)
                            {
                                pMotor->IF_Ctrl.IF_Success_Flag = 1U;
                            }
                        }
                        else
                        {
                            pMotor->IF_Ctrl.AngleRad_cnt = 0U;
                        }
                        
                        if((pMotor->IF_Ctrl.IF_Success_Flag == 1U)
                        && (pMotor->SRAD_Ctrl.Q14I_SRAD_Fb >  pMotor->SRAD_Ctrl.SpeedChange0))
                        {
                            if(++pMotor->flow_cnt >  pMotor->SRAD_Ctrl.SpeedChangeTime_Num0)
                            {
                                pMotor->flow_cnt = 0;
                                pMotor->SRAD_Ctrl.SRad_Ramp.Q32I_ADDStep = pMotor->SRAD_Ctrl.SpeedStep1,
                                pMotor->SRAD_Ctrl.SRad_Ramp.Q32I_SUBStep = -pMotor->SRAD_Ctrl.SpeedStep1,
                                Ramp_Init(&pMotor->SRAD_Ctrl.SRad_Ramp, pMotor->SRAD_Ctrl.Q14I_SRAD_Fb+5);
                                PID_Pos_Init(&pMotor->SRAD_Ctrl.PidSpd, pMotor->Current_Ctrl.Q14I_IqRef);
                                pMotor->Motor_Speed_Mode = CLOSELOOP_INIT;
                            }
                        }
                        else
                        {
                            pMotor->flow_cnt = 0;
                        }
                    }break;
                    case CLOSELOOP_INIT:
                    {
                        Ramp_Cal(&pMotor->SRAD_Ctrl.Id_Ramp);
                        MotorFoc_Speed_Loop(&pMotor->SRAD_Ctrl);
                
                        pMotor->Current_Ctrl.Q14I_IdRef = pMotor->SRAD_Ctrl.Id_Ramp.Q32I_Output;
                        pMotor->Current_Ctrl.Q14I_IqRef = pMotor->SRAD_Ctrl.Q14I_IqRef;
                        
                        if((pMotor->IF_Ctrl.AngleError_Ramp.Q32I_Output == 0) && (pMotor->Current_Ctrl.Q14I_IdRef == 0)
                        && (pMotor->SRAD_Ctrl.Q14I_SRAD_Fb > pMotor->SRAD_Ctrl.SpeedChange1))
                        {
                            if(++pMotor->flow_cnt >  pMotor->SRAD_Ctrl.SpeedChangeTime_Num1)
                            {
                                pMotor->flow_cnt = 0;
                                pMotor->SRAD_Ctrl.SRad_Ramp.Q32I_ADDStep = pMotor->SRAD_Ctrl.SpeedStep2,
                                pMotor->SRAD_Ctrl.SRad_Ramp.Q32I_SUBStep = -pMotor->SRAD_Ctrl.SpeedStep2,
                                pMotor->Motor_Speed_Mode = CLOSELOOP_RUN;
                            }
                        }
                        else
                        {
                            pMotor->flow_cnt = 0;
                        }
                        
                    }break;
                    case CLOSELOOP_RUN:
                    {
                        MotorFoc_Speed_Loop(&pMotor->SRAD_Ctrl);
                
                        pMotor->Current_Ctrl.Q14I_IdRef = 0;
                        pMotor->Current_Ctrl.Q14I_IqRef = pMotor->SRAD_Ctrl.Q14I_IqRef;
                    }break;
                    case CLOSELOOP_END:
                    {
                        pMotor->Motor_Speed_Mode = CLOSELOOP_RUN;
                    }break;
                    default:
                        break;
                }
                pMotor->Motor_State_Flag.bit.pwm_output_flag = 1U;
            }
            else
            {
#if(CLOSELOOP3_EN == 0)
                pMotor->flow_cnt = 0;
                pMotor->Motor_State_Flag.bit.pwm_output_flag = 0U;
        
                MH_HPWM_LPWM_Close();
#if(BRAKE_EN == 0)
                pMotor->Motor_Flow = MOTOR_STATE_INIT;
#else
                pMotor->Motor_Flow = MOTOR_STATE_BRAKE;
#endif
                
#else
                if(pMotor->Motor_Speed_Mode != CLOSELOOP_END)
                {
                    pMotor->SRAD_Ctrl.SRad_Ramp.Q32I_ADDStep = pMotor->SRAD_Ctrl.SpeedStep3,
                    pMotor->SRAD_Ctrl.SRad_Ramp.Q32I_SUBStep = -pMotor->SRAD_Ctrl.SpeedStep3,
                    pMotor->Motor_Speed_Mode = CLOSELOOP_END;
                }
                else
                {
                    pMotor->SRAD_Ctrl.Q14I_SRAD_Rf = pMotor->SRAD_Ctrl.SpeedTarget;
                    MotorFoc_Speed_Loop(&pMotor->SRAD_Ctrl);
            
                    pMotor->Current_Ctrl.Q14I_IdRef = 0;
                    pMotor->Current_Ctrl.Q14I_IqRef = pMotor->SRAD_Ctrl.Q14I_IqRef;
                }
                
                if(pMotor->SRAD_Ctrl.Q14I_SRAD_Fb < pMotor->SRAD_Ctrl.SpeedChange3)
                {
                    if(++pMotor->flow_cnt >  pMotor->SRAD_Ctrl.SpeedChangeTime_Num3)
                    {
                        pMotor->flow_cnt = 0;
                        pMotor->Motor_State_Flag.BIT.pwm_output_flag = 0U;
                
                        MH_HPWM_LPWM_Close();
#if(BRAKE_EN == 0)
                        pMotor->Motor_Flow = MOTOR_STATE_INIT;
#else
                        pMotor->Motor_Flow = MOTOR_STATE_BRAKE;
#endif
                    }
                }
                else
                {
                    pMotor->flow_cnt = 0;
                }
#endif           
            }
        }break;
        case MOTOR_STATE_BRAKE:
        {
            
        }break;
    default:break;
    }
}

void MotorTask_ADC_Handle(ST_MOTOR_TASK* pMotor)
{
    pMotor->FOC_Para.Q12I_I_Data[3] = (Q16I_)ADC_DATA_READ_CURRENT;
}

void MotorTask_Current_Flow(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_Flow == MOTOR_STATE_RUN)
    {
        if(pMotor->ADC_Read_Flow == ADC_FIRST_READ)
        {
            pMotor->FOC_Para.Q12I_I_Data[1] = (Q16I_)ADC_DATA_READ_CURRENT;
            pMotor->ADC_Read_Flow = ADC_SECND_READ;
        }
        else if(pMotor->ADC_Read_Flow == ADC_SECND_READ)
        {
            pMotor->FOC_Para.Q12I_I_Data[0] = (Q16I_)ADC_DATA_READ_CURRENT;
            pMotor->ADC_Read_Flow = PWM_DUTY_DNDATE;
        }
    }
}

void MotorTask_Update_Flow(ST_MOTOR_TASK* pMotor)
{
    switch(pMotor->Motor_Flow)
    {
        case MOTOR_STATE_INIT:
        {
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                if(pMotor->Motor_State_Flag.bit.para_init_flag == 1U)
                {
                    MotorTask_ADC_Handle(pMotor);
                    if((pMotor->Common_Ctrl.Motor_Flag.bit.current_offset_Succ == 0U)
                    && (pMotor->Common_Ctrl.Motor_Flag.bit.current_offset_Fail == 0U))
                    {   
                        Motor_Current_Offset_Check(&pMotor->Common_Ctrl, &pMotor->FOC_Para);
                        if(pMotor->Common_Ctrl.Motor_Flag.bit.current_offset_Succ == 1U)
                        {
                            pMotor->FOC_Para.Q12I_I_Offset = Q14I_CURRENT_LSB_TO_PU(pMotor->FOC_Para.Q12I_I_Offset);
                        }
                    }
                }
            }
            else
            {
                MH_HPWM_LPWM_Close();
            }
        }break;
        case MOTOR_STATE_IDLE:
        {
            MotorTask_ADC_Handle(pMotor);
            if((pMotor->Common_Ctrl.Motor_Flag.bit.free_flying_Succ == 0U)
            && (pMotor->Common_Ctrl.Motor_Flag.bit.free_flying_Fail == 0U))
            {
                MH_ADC_Soft_Trigger();
            }
            MH_HPWM_LPWM_Close();
        }break;
        case MOTOR_STATE_MOS:
        {
            MotorTask_ADC_Handle(pMotor);
            if((pMotor->Common_Ctrl.Motor_Flag.bit.mos_check_Succ == 0U)
            && (pMotor->Common_Ctrl.Motor_Flag.bit.mos_check_Fail == 0U))
            {
                
            }
            if((pMotor->Common_Ctrl.Motor_Flag.bit.mos_check_Succ == 0U)
            && (pMotor->Common_Ctrl.Motor_Flag.bit.mos_check_Fail == 0U))
            {
                
            }
            else
            {
                MH_HPWM_LPWM_Close();
            }
        }break;
        case MOTOR_STATE_BOOT:
        {
            MotorTask_ADC_Handle(pMotor);
            if((pMotor->Common_Ctrl.Motor_Flag.bit.motor_standby_Succ == 0U)
            && (pMotor->Common_Ctrl.Motor_Flag.bit.motor_standby_Fail == 0U))
            {
                
            }
            if((pMotor->Common_Ctrl.Motor_Flag.bit.motor_standby_Succ == 0U)
            && (pMotor->Common_Ctrl.Motor_Flag.bit.motor_standby_Fail == 0U))
            {
                
            }
            else
            {
                MH_HPWM_LPWM_Close();
            }
        }break;
        case MOTOR_STATE_POSITION:
        {
            
        }break;
        case MOTOR_STATE_RUN:
        {
            if(pMotor->ADC_Read_Flow == PWM_DUTY_DNDATE)
            {
                pMotor->FOC_Para.Q12I_I_Data[0] = Q14I_CURRENT_LSB_TO_PU(pMotor->FOC_Para.Q12I_I_Data[0]);
                pMotor->FOC_Para.Q12I_I_Data[1] = Q14I_CURRENT_LSB_TO_PU(pMotor->FOC_Para.Q12I_I_Data[1]);
                MotorFoc_Simple_Cal(&pMotor->FOC_Para);
                
                MotorFoc_Flux_Control(&pMotor->PMSM_Para, &pMotor->FOC_Para, &pMotor->FLUX_Ctrl);
                MotorFoc_SMO_Control(&pMotor->PMSM_Para, &pMotor->FOC_Para, &pMotor->SMO_Ctrl);
                
                if(pMotor->Motor_State_Flag.bit.pwm_output_flag == 1U)
                {
#if(USER_MOTOR_SPEED_MODE == USER_MOTOR_SPEED_FLUX)
                    switch(pMotor->Motor_Speed_Mode)
                    {
                        case OPENLOOP:
                        {
                            pMotor->IF_Ctrl.Est_AngleRad = pMotor->FLUX_Ctrl.Angle.Q12U_Angle;
                            MotorFoc_IF_Control(&pMotor->PMSM_Para, &pMotor->IF_Ctrl);
                            Ramp_Init(&pMotor->IF_Ctrl.AngleError_Ramp, (pMotor->IF_Ctrl.Est_AngleRad - pMotor->IF_Ctrl.Angle.Q12U_Angle));
                            pMotor->FOC_Para.Angle = pMotor->IF_Ctrl.Angle;
                        }break;
                        case CLOSELOOP_INIT:
                        {
                            Ramp_Cal(&pMotor->IF_Ctrl.AngleError_Ramp);
                            pMotor->IF_Ctrl.Angle.Q12U_Angle = pMotor->FLUX_Ctrl.Angle.Q12U_Angle - pMotor->IF_Ctrl.AngleError_Ramp.Q32I_Output;
                            MATH_ANGLE_MOD_U(pMotor->IF_Ctrl.Angle.Q12U_Angle);
                            Math_SinCos(&pMotor->IF_Ctrl.Angle);
                            pMotor->FOC_Para.Angle = pMotor->IF_Ctrl.Angle;
                        }break;
                        case CLOSELOOP_RUN:
                        {
                            pMotor->FOC_Para.Angle = pMotor->FLUX_Ctrl.Angle;
                        }break;
                        case CLOSELOOP_END:
                        {
                            pMotor->FOC_Para.Angle = pMotor->FLUX_Ctrl.Angle;
                        }break;
                        default:
                            break;
                    }
#elif(USER_MOTOR_SPEED_MODE == USER_MOTOR_SPEED_SMO)
                    switch(pMotor->Motor_Speed_Mode)
                    {
                        case OPENLOOP:
                        {
                            pMotor->IF_Ctrl.Est_AngleRad = pMotor->SMO_Ctrl.Angle.Q12U_Angle;
                            MotorFoc_IF_Control(&pMotor->PMSM_Para, &pMotor->IF_Ctrl);
                            Ramp_Init(&pMotor->IF_Ctrl.AngleError_Ramp, (pMotor->IF_Ctrl.Est_AngleRad - pMotor->IF_Ctrl.Angle.Q12U_Angle));
                            pMotor->FOC_Para.Angle = pMotor->IF_Ctrl.Angle;
                        }break;
                        case CLOSELOOP_INIT:
                        {
                            Ramp_Cal(&pMotor->IF_Ctrl.AngleError_Ramp);
                            pMotor->IF_Ctrl.Angle.Q12U_Angle = pMotor->SMO_Ctrl.Angle.Q12U_Angle - pMotor->IF_Ctrl.AngleError_Ramp.Q32I_Output;
                            MATH_ANGLE_MOD_U(pMotor->IF_Ctrl.Angle.Q12U_Angle);
                            Math_SinCos(&pMotor->IF_Ctrl.Angle);
                            pMotor->FOC_Para.Angle = pMotor->IF_Ctrl.Angle;
                        }break;
                        case CLOSELOOP_RUN:
                        {
                            pMotor->FOC_Para.Angle = pMotor->SMO_Ctrl.Angle;
                        }break;
                        case CLOSELOOP_END:
                        {
                            pMotor->FOC_Para.Angle = pMotor->SMO_Ctrl.Angle;
                        }break;
                        default:
                            break;
                    }
#endif
                    MotorFoc_Current_Loop(&pMotor->FOC_Para, &pMotor->Current_Ctrl);
                }
                    
                MH_PWM_Duty_Set(Q32I_RHT_12(pMotor->Current_Ctrl.Q12I_TaDn*HAL_PWM_INIT_SET), 
                                Q32I_RHT_12(pMotor->Current_Ctrl.Q12I_TbDn*HAL_PWM_INIT_SET), 
                                Q32I_RHT_12(pMotor->Current_Ctrl.Q12I_TcDn*HAL_PWM_INIT_SET));
                
                MH_PWM_ADC_Set(Q32I_RHT_12(pMotor->Current_Ctrl.Q12I_TADC_1*HAL_PWM_INIT_SET), 
                                Q32I_RHT_12(pMotor->Current_Ctrl.Q12I_TADC_2*HAL_PWM_INIT_SET));
                
                pMotor->ADC_Read_Flow = ADC_FIRST_READ;
            }
            else
            {
                MH_PWM_Duty_Set(Q32I_RHT_12(pMotor->Current_Ctrl.Q12I_TaUp*HAL_PWM_INIT_SET), 
                                Q32I_RHT_12(pMotor->Current_Ctrl.Q12I_TbUp*HAL_PWM_INIT_SET), 
                                Q32I_RHT_12(pMotor->Current_Ctrl.Q12I_TcUp*HAL_PWM_INIT_SET));
            }
            if(pMotor->Motor_State_Flag.bit.pwm_output_flag == 1U)
            {
                MH_PWM_Output_Enable();
            }
            else
            {
                MH_PWM_Output_Disable();
            }
        }break;
        case MOTOR_STATE_BRAKE:
        {
#if(SLOW_BRAKE_EN == 0)
            MH_HPWM_LPWM_LOpen(0U);
#else
            MotorTask_Brake_ADC_Handle(pMotor);
            MH_HPWM_LPWM_LOpen(100U);
#endif
        }break;
        default:break;
    }
}

void MotorTask_Shut_Down_Flow(ST_MOTOR_TASK* pMotor)
{
    MH_HPWM_LPWM_Close();
}
