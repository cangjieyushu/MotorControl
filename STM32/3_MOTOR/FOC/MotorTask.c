/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#include "MotorTask.h"

void Motor_SpeedSwitchToHigh(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->tc_ctrl.Speed > pMotor->tc_ctrl.SpeedChange)
    {
        if(++pMotor->flow_cnt > pMotor->tc_ctrl.SpeedChangeTime_Num)
        {
            pMotor->flow_cnt = 0U;
            Ramp_Init(&pMotor->tc_ctrl.SpdRamp, (pMotor->tc_ctrl.Speed+5.0f));
            PID_POS_Init(&pMotor->tc_ctrl.PidSpd, pMotor->foc_ctrl.IqRef);
            pMotor->speed_mode = EM_MOTOR_SPEED_MODE_CLOSELOOP3;
        }
    }
    else
    {
        pMotor->flow_cnt = 0U;
    }
}

void Motor_SpeedSwitchToLow(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->tc_ctrl.Speed < pMotor->tc_ctrl.SpeedChange)
    {
        if(++pMotor->flow_cnt > pMotor->tc_ctrl.SpeedChangeTime_Num)
        {
            pMotor->flow_cnt = 0U;
            Ramp_Init(&pMotor->tc_ctrl.CurrentRamp, pMotor->tc_ctrl.CurrentRamp.Init);
            pMotor->speed_mode = EM_MOTOR_SPEED_MODE_CLOSELOOP2;
        }
    }
    else
    {
        pMotor->flow_cnt = 0U;
    }
}

void Motor_Task_Flow(ST_MOTOR_TASK* pMotor)
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
                Ramp_Init(&pMotor->tc_ctrl.CurrentRamp, pMotor->tc_ctrl.CurrentRamp.Init);
                PID_POS_Init(&pMotor->foc_ctrl.PidId, 0.0f);
                PID_POS_Init(&pMotor->foc_ctrl.PidIq, 0.0f);
                
                Est_IF_Init(&pMotor->if_ctrl);
                Est_Flux_Init(&pMotor->flux_ctrl);
                Est_SMO_Init(&pMotor->smo_ctrl);
                Hallest_Init(&pMotor->hall_ctrl);
                
                pMotor->speed_mode = EM_MOTOR_SPEED_MODE_CLOSELOOP1;
                pMotor->state_flow = MOTOR_STATE_RUN;
            }
            break;
        }
    case MOTOR_STATE_RUN:
        {
            if(pMotor->state_flag.BIT.motor_run == 1U)
            { 
                switch(pMotor->speed_mode)
                {
#if(USER_MOTOR_MODE == USER_MOTOR_SENSE_HALL)
                    case EM_MOTOR_SPEED_MODE_CLOSELOOP1:
                    {
                        pMotor->tc_ctrl.Speed = pMotor->hall_ctrl.ElecFreqHz_Filter;
                        Ramp_Cal(&pMotor->tc_ctrl.CurrentRamp);
                        pMotor->foc_ctrl.IdRef = 0.0f;
                        pMotor->foc_ctrl.IqRef = pMotor->tc_ctrl.CurrentRamp.Output;
                        Motor_SpeedSwitchToHigh(pMotor);
                    }break;
                    case EM_MOTOR_SPEED_MODE_CLOSELOOP2:
                    {
                        pMotor->tc_ctrl.Speed = pMotor->hall_ctrl.ElecFreqHz_Filter;
                        Ramp_Cal(&pMotor->tc_ctrl.CurrentRamp);
                        pMotor->foc_ctrl.IdRef = 0.0f;
                        pMotor->foc_ctrl.IqRef = pMotor->tc_ctrl.CurrentRamp.Output;
                        Motor_SpeedSwitchToHigh(pMotor);
                    }break;
                    case EM_MOTOR_SPEED_MODE_CLOSELOOP3:
                    {
                        pMotor->tc_ctrl.Speed = pMotor->hall_ctrl.ElecFreqHz_Filter;
                        Tc_Cal(&pMotor->tc_ctrl);
#if(USER_MOTOR_MTPA_EN == 1U)
                        MTPA_Control(&pMotor->mtpa_ctrl, &pMotor->foc_ctrl, &pMotor->tc_ctrl);
#else
                        pMotor->mtpa_ctrl.IdRef = 0.0f;
                        pMotor->mtpa_ctrl.IqRef = pMotor->tc_ctrl.IqRef;

#endif
#if(USER_MOTOR_FLUX_EN == 1U)
                        WEAK_Control(&pMotor->weak_ctrl, &pMotor->mtpa_ctrl, &pMotor->foc_ctrl, &pMotor->tc_ctrl);
#else
                        pMotor->weak_ctrl.IdRef = pMotor->mtpa_ctrl.IdRef;
                        pMotor->weak_ctrl.IqRef = pMotor->mtpa_ctrl.IqRef;
#endif
                        pMotor->foc_ctrl.IdRef = pMotor->weak_ctrl.IdRef;
                        pMotor->foc_ctrl.IqRef = pMotor->weak_ctrl.IqRef;
                        Motor_SpeedSwitchToLow(pMotor);
                    }break;
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSE_RPS)
                        
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSELESS_FLUX)
                    case EM_MOTOR_SPEED_MODE_CLOSELOOP1:
                    {
                        pMotor->tc_ctrl.Speed = pMotor->flux_ctrl.ElecFreqHz_Filter;
                        Ramp_Cal(&pMotor->tc_ctrl.CurrentRamp);
                        pMotor->foc_ctrl.IdRef = 0.0f;
                        pMotor->foc_ctrl.IqRef = pMotor->tc_ctrl.CurrentRamp.Output;
                        Motor_SpeedSwitchToHigh(pMotor);
                    }break;
                    case EM_MOTOR_SPEED_MODE_CLOSELOOP2:
                    {
                    }break;
                    case EM_MOTOR_SPEED_MODE_CLOSELOOP3:
                    {
                        pMotor->tc_ctrl.Speed = pMotor->flux_ctrl.ElecFreqHz_Filter;
                        Tc_Cal(&pMotor->tc_ctrl);
#if(USER_MOTOR_MTPA_EN == 1U)
                        MTPA_Control(&pMotor->mtpa_ctrl, &pMotor->foc_ctrl, &pMotor->tc_ctrl);
#els
                        pMotor->mtpa_ctrl.IdRef = 0.0f;
                        pMotor->mtpa_ctrl.IqRef = pMotor->tc_ctrl.IqRef;

#endif
#if(USER_MOTOR_FLUX_EN == 1U)
                        WEAK_Control(&pMotor->weak_ctrl, &pMotor->mtpa_ctrl, &pMotor->foc_ctrl, &pMotor->tc_ctrl);
#else
                        pMotor->weak_ctrl.IdRef = pMotor->mtpa_ctrl.IdRef;
                        pMotor->weak_ctrl.IqRef = pMotor->mtpa_ctrl.IqRef;
#endif
                        pMotor->foc_ctrl.IdRef = pMotor->weak_ctrl.IdRef;
                        pMotor->foc_ctrl.IqRef = pMotor->weak_ctrl.IqRef;
                    }break;
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSELESS_SMO)
                    case EM_MOTOR_SPEED_MODE_CLOSELOOP1:
                    {
                        pMotor->tc_ctrl.Speed = pMotor->smo_ctrl.ElecFreqHz_Filter;
                        Ramp_Cal(&pMotor->tc_ctrl.CurrentRamp);
                        Ramp_Cal(&pMotor->if_ctrl.AngleRadRamp);
                        pMotor->foc_ctrl.IdRef = 0.0f;
                        pMotor->foc_ctrl.IqRef = pMotor->tc_ctrl.CurrentRamp.Output;
                        if(pMotor->if_ctrl.IF_Success_Flag == 1U)
                        {
                            Ramp_Init(&pMotor->tc_ctrl.SpdRamp, (pMotor->tc_ctrl.Speed+5.0f));
                            PID_POS_Init(&pMotor->tc_ctrl.PidSpd, pMotor->foc_ctrl.IqRef);
                            pMotor->speed_mode = EM_MOTOR_SPEED_MODE_CLOSELOOP2;
                        }
                    }break;
                    case EM_MOTOR_SPEED_MODE_CLOSELOOP2:
                    {
                    }break;
                    case EM_MOTOR_SPEED_MODE_CLOSELOOP3:
                    {
                        pMotor->tc_ctrl.Speed = pMotor->smo_ctrl.ElecFreqHz_Filter;
                        Tc_Cal(&pMotor->tc_ctrl);
#if(USER_MOTOR_MTPA_EN == 1U)
                        MTPA_Control(&pMotor->mtpa_ctrl, &pMotor->foc_ctrl, &pMotor->tc_ctrl);
#else
                        pMotor->mtpa_ctrl.IdRef = 0.0f;
                        pMotor->mtpa_ctrl.IqRef = pMotor->tc_ctrl.IqRef;

#endif
#if(USER_MOTOR_FLUX_EN == 1U)
                        WEAK_Control(&pMotor->weak_ctrl, &pMotor->mtpa_ctrl, &pMotor->foc_ctrl, &pMotor->tc_ctrl);
#else
                        pMotor->weak_ctrl.IdRef = pMotor->mtpa_ctrl.IdRef;
                        pMotor->weak_ctrl.IqRef = pMotor->mtpa_ctrl.IqRef;
#endif
                        pMotor->foc_ctrl.IdRef = pMotor->weak_ctrl.IdRef;
                        pMotor->foc_ctrl.IqRef = pMotor->weak_ctrl.IqRef;
                    }break;
#endif
                    default:break;
                }
                pMotor->state_flag.BIT.PWM_output_en = 1U; 
            }
            else
            {
                pMotor->flow_cnt = 0U;
                pMotor->speed_mode = EM_MOTOR_SPEED_MODE_CLOSELOOP1;
                pMotor->brake_ctrl.Brake_En = 1;
                pMotor->state_flow = MOTOR_STATE_BRAKE;
            }
            break;
        }
    case MOTOR_STATE_BRAKE:
        {
            Motor_Brake_Control(&pMotor->brake_ctrl, &pMotor->foc_ctrl);
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

void Motor_Foc_Cal(ST_MOTOR_TASK* pMotor)
{
#if(USER_MOTOR_MODE == USER_MOTOR_SENSE_HALL)
    Clark_Transform(&pMotor->foc_ctrl);
    
    switch(pMotor->speed_mode)
    {
        case EM_MOTOR_SPEED_MODE_CLOSELOOP1:
        case EM_MOTOR_SPEED_MODE_CLOSELOOP2:
        {
            Hallest_Low_Speed(&pMotor->hall_ctrl);
        }break;
        case EM_MOTOR_SPEED_MODE_CLOSELOOP3:
        {
            Hallest_High_Speed(&pMotor->hall_ctrl);
        }break;
        default:break;
    }
    Hallest_Angle_Inc(&pMotor->hall_ctrl, 0x11);
    pMotor->foc_ctrl.AngleRad = pMotor->hall_ctrl.AngleRad;
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSE_RPS)
                        
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSELESS_FLUX)
    switch(pMotor->speed_mode)
    {
        case EM_MOTOR_SPEED_MODE_CLOSELOOP1:
        case EM_MOTOR_SPEED_MODE_CLOSELOOP2:
        {
            Hallest_Low_Speed(&pMotor->hall_ctrl);
        }break;
        case EM_MOTOR_SPEED_MODE_CLOSELOOP3:
        {
            Hallest_High_Speed(&pMotor->hall_ctrl);
        }break;
        default:break;
    }
    Est_Flux(&pMotor->foc_ctrl, &pMotor->flux_ctrl);
    pMotor->foc_ctrl.AngleRad = pMotor->flux_ctrl.AngleRad;
    
#elif(USER_MOTOR_MODE == USER_MOTOR_SENSELESS_SMO)
    Est_SMO(&pMotor->foc_ctrl, &pMotor->smo_ctrl);
    
    switch(pMotor->speed_mode)
    {
        case EM_MOTOR_SPEED_MODE_CLOSELOOP1:
        {
            Est_IF(&pMotor->if_ctrl, pMotor->flux_ctrl.AngleRad);
            pMotor->foc_ctrl.AngleRad = pMotor->if_ctrl.AngleRad;
        }break;
        case EM_MOTOR_SPEED_MODE_CLOSELOOP2:
        {
        }break;
        case EM_MOTOR_SPEED_MODE_CLOSELOOP3:
        {
            pMotor->foc_ctrl.AngleRad = pMotor->smo_ctrl.AngleRad;
        }break;
        default:break;
    }
#endif
    
    Foc_Cal(&pMotor->foc_ctrl);
}

