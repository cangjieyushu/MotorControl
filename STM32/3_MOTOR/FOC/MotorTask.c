/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#include "MotorTask.h"
#include "MotorPara.h"

void Motor_SpeedSwitchToHigh(ST_MOTOR_TASK* pMotor)
{
#if(USER_MOTOR_MODE == USER_MOTOR_SENSE_HALL)
    if(MATH_ABS(pMotor->speed_ctrl.Speed) > pMotor->speed_ctrl.SpeedChange)
    {
        if(++pMotor->flow_cnt > pMotor->speed_ctrl.SpeedChangeTime_Num)
        {
            pMotor->flow_cnt = 0U;
            Ramp_Init(&pMotor->speed_ctrl.SpdRamp, (pMotor->speed_ctrl.Speed+5.0f));
            PID_POS_Init(&pMotor->speed_ctrl.PidSpd, pMotor->current_ctrl.IqRef);
            pMotor->speed_mode = MOTOR_SPEED_MODE_HIGHSPEED;
        }
    }
    else
    {
        pMotor->flow_cnt = 0U;
    }
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSE_RPS)
                        
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSELESS_FLUX)
    if(MATH_ABS(pMotor->speed_ctrl.Speed) > pMotor->speed_ctrl.SpeedChange)
    {
        if(++pMotor->flow_cnt > pMotor->speed_ctrl.SpeedChangeTime_Num)
        {
            pMotor->flow_cnt = 0U;
            Ramp_Init(&pMotor->speed_ctrl.SpdRamp, (pMotor->speed_ctrl.Speed+5.0f));
            PID_POS_Init(&pMotor->speed_ctrl.PidSpd, pMotor->current_ctrl.IqRef);
            pMotor->speed_mode = MOTOR_SPEED_MODE_HIGHSPEED;
        }
    }
    else
    {
        pMotor->flow_cnt = 0U;
    }
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSELESS_SVC)
    if(MATH_ABS(pMotor->speed_ctrl.Speed) > pMotor->speed_ctrl.SpeedChange)
    {
        if(++pMotor->flow_cnt > pMotor->speed_ctrl.SpeedChangeTime_Num)
        {
            pMotor->flow_cnt = 0U;
            Ramp_Init(&pMotor->speed_ctrl.SpdRamp, (pMotor->speed_ctrl.Speed+5.0f));
            PID_POS_Init(&pMotor->speed_ctrl.PidSpd, pMotor->current_ctrl.IqRef);
            pMotor->speed_mode = MOTOR_SPEED_MODE_HIGHSPEED;
        }
    }
    else
    {
        pMotor->flow_cnt = 0U;
    }
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSELESS_SMO)
    if(MATH_ABS(pMotor->speed_ctrl.Speed) > pMotor->speed_ctrl.SpeedChange)
    {
        if(pMotor->if_ctrl.IF_Success_Flag == 1U)
        {
            pMotor->if_ctrl.IF_Success_Flag = 0U;
            Ramp_Init(&pMotor->speed_ctrl.SpdRamp, (pMotor->speed_ctrl.Speed+5.0f));
            PID_POS_Init(&pMotor->speed_ctrl.PidSpd, pMotor->current_ctrl.IqRef);
            pMotor->speed_mode = MOTOR_SPEED_MODE_HIGHSPEED;
        }
    }
#endif
}

void Motor_SpeedSwitchToLow(ST_MOTOR_TASK* pMotor)
{
#if(USER_MOTOR_MODE == USER_MOTOR_SENSE_HALL)
    if(MATH_ABS(pMotor->speed_ctrl.Speed) < pMotor->speed_ctrl.SpeedChange)
    {
        if(++pMotor->flow_cnt > pMotor->speed_ctrl.SpeedChangeTime_Num)
        {
            pMotor->flow_cnt = 0U;
            Ramp_Init(&pMotor->speed_ctrl.CurrentRamp, pMotor->speed_ctrl.CurrentRamp.Init);
            pMotor->speed_mode = MOTOR_SPEED_MODE_LOWSPEED;
        }
    }
    else
    {
        pMotor->flow_cnt = 0U;
    }
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSE_RPS)
    
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSELESS_SMO)
    if(MATH_ABS(pMotor->speed_ctrl.Speed) < pMotor->speed_ctrl.SpeedChange)
    {
        if(++pMotor->flow_cnt > pMotor->speed_ctrl.SpeedChangeTime_Num)
        {
            pMotor->flow_cnt = 0U;
            Ramp_Init(&pMotor->speed_ctrl.CurrentRamp, pMotor->speed_ctrl.CurrentRamp.Init);
            pMotor->speed_mode = MOTOR_SPEED_MODE_LOWSPEED;
        }
    }
    else
    {
        pMotor->flow_cnt = 0U;
    }
#endif
}

void MotorTask_MTPA_WEAK(ST_MOTOR_TASK* pMotor)
{
    MotorFoc_Speed_Loop(&pMotor->speed_ctrl);
#if(USER_MOTOR_MTPA_EN == 1U)
    MTPA_Control(&pMotor->pmsm_para, &pMotor->speed_ctrl, &pMotor->mtpa_ctrl);
#else
    pMotor->mtpa_ctrl.IdRef = 0.0f;
    pMotor->mtpa_ctrl.IqRef = pMotor->speed_ctrl.IqRef;

#endif
#if(USER_MOTOR_FLUX_EN == 1U)
    WEAK_Control(&pMotor->foc_para, &pMotor->speed_ctrl, &pMotor->mtpa_ctrl, &pMotor->weak_ctrl);
#else
    pMotor->weak_ctrl.IdRef = pMotor->mtpa_ctrl.IdRef;
    pMotor->weak_ctrl.IqRef = pMotor->mtpa_ctrl.IqRef;
#endif
    pMotor->current_ctrl.IdRef = pMotor->weak_ctrl.IdRef;
    pMotor->current_ctrl.IqRef = pMotor->weak_ctrl.IqRef;
}

void MotorTask_Speed_Flow(ST_MOTOR_TASK* pMotor)
{
    switch(pMotor->state_flow)
    {
        case MOTOR_STATE_IDLE:
        {
            if(pMotor->state_flag.BIT.motor_run == 1U)
            {
                pMotor->state_flow = MOTOR_STATE_BOOT;
            }
            else
            {
                pMotor->state_flag.BIT.PWM_output_en = 0U;
            }
            break;
        }
        case MOTOR_STATE_BOOT:
        {
            if(pMotor->state_flag.BIT.motor_run == 1U)
            {
                pMotor->state_flow = MOTOR_STATE_POSITION;
            }
            break;
        }
        case MOTOR_STATE_POSITION:
        {
            if(pMotor->state_flag.BIT.motor_run == 1U)
            {
                MotorPara_TargetDir_Change(pMotor);
                Ramp_Init(&pMotor->speed_ctrl.CurrentRamp, pMotor->speed_ctrl.CurrentRamp.Init);
                PID_POS_Init(&pMotor->current_ctrl.PidId, 0.0f);
                PID_POS_Init(&pMotor->current_ctrl.PidIq, 0.0f);
                
                WEAK_Init(&pMotor->weak_ctrl);
                
                Est_IF_Init(&pMotor->if_ctrl);
                Est_Flux_Init(&pMotor->flux_ctrl);
                Est_SVC_Init(&pMotor->svc_ctrl);
                Est_SMO_Init(&pMotor->smo_ctrl);
                Est_Hall_Init(&pMotor->hall_ctrl);
                
                pMotor->speed_mode = MOTOR_SPEED_MODE_START;
                pMotor->state_flow = MOTOR_STATE_RUN;
            }
            break;
        }

        case MOTOR_STATE_RUN:
        {
            if(pMotor->state_flag.BIT.motor_run == 1U)
            { 
                MotorPara_TargetDir_Change(pMotor);
#if(USER_MOTOR_MODE == USER_MOTOR_SENSE_HALL)
                pMotor->speed_ctrl.Speed = pMotor->hall_ctrl.AngleSpeed_Filter;
                switch(pMotor->speed_mode)
                {
                    case MOTOR_SPEED_MODE_START:
                    {
                        pMotor->speed_ctrl.Speed = pMotor->hall_ctrl.AngleSpeed_Filter;
                        Ramp_Control(&pMotor->speed_ctrl.CurrentRamp);
                        pMotor->current_ctrl.IdRef = 0.0f;
                        pMotor->current_ctrl.IqRef = pMotor->speed_ctrl.CurrentRamp.Output;
                        Motor_SpeedSwitchToHigh(pMotor);
                    }break;
                    case MOTOR_SPEED_MODE_LOWSPEED:
                    {
                        Ramp_Control(&pMotor->speed_ctrl.CurrentRamp);
                        pMotor->current_ctrl.IdRef = 0.0f;
                        pMotor->current_ctrl.IqRef = pMotor->speed_ctrl.CurrentRamp.Output;
                        Motor_SpeedSwitchToHigh(pMotor);
                    }break;
                    case MOTOR_SPEED_MODE_HIGHSPEED:
                    {
                        MotorTask_MTPA_WEAK(pMotor);
                        Motor_SpeedSwitchToLow(pMotor);
                    }break;
                    default:break;
                }
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSE_RPS)
                        
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSELESS_FLUX)
                pMotor->speed_ctrl.Speed = pMotor->flux_ctrl.AngleSpeed_Filter;
                switch(pMotor->speed_mode)
                {
                    case MOTOR_SPEED_MODE_START:
                    {
                        Ramp_Control(&pMotor->speed_ctrl.CurrentRamp);
                        pMotor->current_ctrl.IdRef = 0.0f;
                        pMotor->current_ctrl.IqRef = pMotor->speed_ctrl.CurrentRamp.Output;
                        Motor_SpeedSwitchToHigh(pMotor);
                    }break;
                    case MOTOR_SPEED_MODE_LOWSPEED:
                    {
                    }break;
                    case MOTOR_SPEED_MODE_HIGHSPEED:
                    {
                        MotorTask_MTPA_WEAK(pMotor);
                    }break;
                    default:break;
                }                    
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSELESS_SVC)
                pMotor->speed_ctrl.Speed = pMotor->svc_ctrl.AngleSpeed_Filter;
                switch(pMotor->speed_mode)
                {
                    case MOTOR_SPEED_MODE_START:
                    {
                        Ramp_Control(&pMotor->speed_ctrl.CurrentRamp);
                        pMotor->current_ctrl.IdRef = 0.0f;
                        pMotor->current_ctrl.IqRef = pMotor->speed_ctrl.CurrentRamp.Output;
                        Motor_SpeedSwitchToHigh(pMotor);
                    }break;
                    case MOTOR_SPEED_MODE_LOWSPEED:
                    {
                    }break;
                    case MOTOR_SPEED_MODE_HIGHSPEED:
                    {
                        MotorTask_MTPA_WEAK(pMotor);
                    }break;
                    default:break;
                }
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSELESS_SMO)
                pMotor->speed_ctrl.Speed = pMotor->smo_ctrl.AngleSpeed_Filter;
                switch(pMotor->speed_mode)
                {
                    case MOTOR_SPEED_MODE_START:
                    {
                        Ramp_Control(&pMotor->speed_ctrl.CurrentRamp);
                        Ramp_Control(&pMotor->if_ctrl.AngleRadRamp);
                        pMotor->current_ctrl.IdRef = 0.0f;
                        pMotor->current_ctrl.IqRef = pMotor->speed_ctrl.CurrentRamp.Output;
                        Motor_SpeedSwitchToHigh(pMotor);
                    }break;
                    case MOTOR_SPEED_MODE_LOWSPEED:
                    {
                    }break;
                    case MOTOR_SPEED_MODE_HIGHSPEED:
                    {
                        MotorTask_MTPA_WEAK(pMotor);
                    }break;
                    default:break;
                }
#endif
                pMotor->state_flag.BIT.PWM_output_en = 1U; 
            }
            else
            {
                pMotor->flow_cnt = 0U;
                pMotor->speed_mode = MOTOR_SPEED_MODE_START;
                pMotor->brake_ctrl.Brake_En = 1;
                pMotor->state_flow = MOTOR_STATE_BRAKE;
            }
            break;
        }
        case MOTOR_STATE_BRAKE:
        {
            Motor_Brake_Control(&pMotor->brake_ctrl, &pMotor->foc_para);
            if(pMotor->brake_ctrl.Brake_Finish_Flag == 1U)
            {
                pMotor->brake_ctrl.Brake_Finish_Flag = 0U;
                pMotor->flow_cnt = 0U;
                pMotor->state_flag.BIT.PWM_output_en = 0U;
                pMotor->state_flow = MOTOR_STATE_IDLE;
            }
            else
            {
                pMotor->state_flag.BIT.PWM_output_en = 1U;
            }
            break;
        }
    default:break;
    }
}

void MotorTask_ADC_Handle(ST_FOC_PARAMETER* pFocPara)
{
    pFocPara->Ia = (float)((pFocPara->Ia_offset - pFocPara->Ia_data)*HAL_ADC_FULL_SCALE_CURRENT);
    pFocPara->Ib = (float)((pFocPara->Ib_offset - pFocPara->Ib_data)*HAL_ADC_FULL_SCALE_CURRENT);
    pFocPara->Ic = (float)((pFocPara->Ic_offset - pFocPara->Ic_data)*HAL_ADC_FULL_SCALE_CURRENT);
    pFocPara->Vbat = (float)(pFocPara->Vbat_data*HAL_ADC_SCALE_VOLTAGE);
}

void MotorTask_GPIO_Flow(ST_MOTOR_TASK* pMotor)
{
    pMotor->hall_ctrl.HallSwitchCount = MH_HALL_TIM_Count();
    pMotor->hall_ctrl.HallCurrentLevel = MH_HALL_GPIO_State();
    switch(pMotor->speed_mode)
    {
        case MOTOR_SPEED_MODE_START:
        case MOTOR_SPEED_MODE_LOWSPEED:
        {
            Est_Hall_Low_Speed(&pMotor->hall_ctrl);
        }break;
        case MOTOR_SPEED_MODE_HIGHSPEED:
        {
            Est_Hall_High_Speed(&pMotor->hall_ctrl);
        }break;
        default:break;
    }
    Est_Hall_Speed_Cal(&pMotor->hall_ctrl);
    pMotor->hall_ctrl.HallLastLevel = pMotor->hall_ctrl.HallCurrentLevel;
}

void MotorTask_Current_Flow(ST_MOTOR_TASK* pMotor)
{
    MotorTask_ADC_Handle(&pMotor->foc_para);
    
    Clark_Transform(&pMotor->foc_para);
    switch(pMotor->speed_mode)
    {
        case MOTOR_SPEED_MODE_START:
        case MOTOR_SPEED_MODE_LOWSPEED:
        {
            pMotor->hall_ctrl.AngleRad = pMotor->hall_ctrl.AngleRad_Hall;
        }break;
        case MOTOR_SPEED_MODE_HIGHSPEED:
        {
            Est_Hall_Angle_Inc(&pMotor->hall_ctrl, MH_HALL_TIM_Count());
        }break;
        default:break;
    }
#if(USER_MOTOR_MODE == USER_MOTOR_SENSE_HALL)
    if(pMotor->speed_mode == MOTOR_SPEED_MODE_HIGHSPEED)
    {
        Est_Hall_Angle_Inc(&pMotor->hall_ctrl, MH_HALL_TIM_Count());
    }
    pMotor->foc_para.AngleRad = pMotor->hall_ctrl.AngleRad;
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSE_RPS)
                        
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSELESS_FLUX)
    switch(pMotor->speed_mode)
    {
        case MOTOR_SPEED_MODE_START:
        case MOTOR_SPEED_MODE_LOWSPEED:
        {
            
        }break;
        case MOTOR_SPEED_MODE_HIGHSPEED:
        {
            
        }break;
        default:break;
    }
    Est_Flux(&pMotor->pmsm_para, &pMotor->foc_para, &pMotor->current_ctrl, &pMotor->flux_ctrl);
    pMotor->foc_para.AngleRad = pMotor->flux_ctrl.AngleRad;  
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSELESS_SVC)
    switch(pMotor->speed_mode)
    {
        case MOTOR_SPEED_MODE_START:
        case MOTOR_SPEED_MODE_LOWSPEED:
        {
            
        }break;
        case MOTOR_SPEED_MODE_HIGHSPEED:
        {
            
        }break;
        default:break;
    }
    Est_SVC(&pMotor->pmsm_para, &pMotor->foc_para, &pMotor->current_ctrl, &pMotor->svc_ctrl);
    pMotor->foc_para.AngleRad = pMotor->svc_ctrl.AngleRad;  
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSELESS_SMO)
    Est_SMO(&pMotor->pmsm_para, &pMotor->foc_para, &pMotor->current_ctrl, &pMotor->smo_ctrl);
    
    switch(pMotor->speed_mode)
    {
        case MOTOR_SPEED_MODE_START:
        {
            Est_IF(&pMotor->if_ctrl, pMotor->flux_ctrl.AngleRad);
            pMotor->foc_para.AngleRad = pMotor->if_ctrl.AngleRad;
        }break;
        case MOTOR_SPEED_MODE_LOWSPEED:
        {
        }break;
        case MOTOR_SPEED_MODE_HIGHSPEED:
        {
            pMotor->foc_para.AngleRad = pMotor->smo_ctrl.AngleRad;
        }break;
        default:break;
    }
#endif
    
    MotorFoc_Current_Loop(&pMotor->foc_para, &pMotor->current_ctrl);
}

