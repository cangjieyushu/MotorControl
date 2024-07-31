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
                case EM_MOTOR_SPEED_MODE_CLOSELOOP1:
                    {
#if(USER_MOTOR_SENSE_MODE == USER_MOTOR_SENSE_HALL)
                        pMotor->tc_ctrl.Speed = pMotor->hall_ctrl.ElecFreqHz_Filter;
                        Ramp_Cal(&pMotor->tc_ctrl.CurrentRamp);
                        pMotor->foc_ctrl.IdRef = 0.0f;
                        pMotor->foc_ctrl.IqRef = pMotor->tc_ctrl.CurrentRamp.Output;
                        Motor_SpeedSwitchToHigh(pMotor);
#elif(USER_MOTOR_SENSE_MODE == USER_MOTOR_SENSE_RPS)
                        
#else
    #if(USER_MOTOR_START_MODE == USER_MOTOR_START_IF)
                        pMotor->tc_ctrl.Speed = pMotor->flux_ctrl.ElecFreqHz_Filter;
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
    #elif(USER_MOTOR_START_MODE == USER_MOTOR_START_FLUX)
                        pMotor->tc_ctrl.Speed = pMotor->flux_ctrl.ElecFreqHz_Filter;
                        Ramp_Cal(&pMotor->tc_ctrl.CurrentRamp);
                        pMotor->foc_ctrl.IdRef = 0.0f;
                        pMotor->foc_ctrl.IqRef = pMotor->tc_ctrl.CurrentRamp.Output;
                        Motor_SpeedSwitchToHigh(pMotor);
    #endif
#endif
                        break;
                    }
                case EM_MOTOR_SPEED_MODE_CLOSELOOP2:
                    {
#if(USER_MOTOR_SENSE_MODE == USER_MOTOR_SENSE_HALL)
                        pMotor->tc_ctrl.Speed = pMotor->hall_ctrl.ElecFreqHz_Filter;
                        Ramp_Cal(&pMotor->tc_ctrl.CurrentRamp);
                        pMotor->foc_ctrl.IdRef = 0.0f;
                        pMotor->foc_ctrl.IqRef = pMotor->tc_ctrl.CurrentRamp.Output;
                        Motor_SpeedSwitchToHigh(pMotor);
#elif(USER_MOTOR_SENSE_MODE == USER_MOTOR_SENSE_RPS)
                        
#else             
    #if(USER_MOTOR_LOWSPEED_MODE == USER_MOTOR_LOWSPEED_FLUX)
                        pMotor->tc_ctrl.Speed = pMotor->flux_ctrl.ElecFreqHz_Filter;
                        Tc_Cal(&pMotor->tc_ctrl);
                        pMotor->foc_ctrl.IdRef = 0.0f;
                        pMotor->foc_ctrl.IqRef = pMotor->tc_ctrl.IqRef;
                        Motor_SpeedSwitchToHigh(pMotor);
    #endif
#endif
                        break;
                    }
                case EM_MOTOR_SPEED_MODE_CLOSELOOP3:
                    {
#if(USER_MOTOR_SENSE_MODE == USER_MOTOR_SENSE_HALL)
                        pMotor->tc_ctrl.Speed = pMotor->hall_ctrl.ElecFreqHz_Filter;
                        Tc_Cal(&pMotor->tc_ctrl);
                        pMotor->foc_ctrl.IdRef = 0.0f;
                        pMotor->foc_ctrl.IqRef = pMotor->tc_ctrl.IqRef;
                        Motor_SpeedSwitchToLow(pMotor);
#elif(USER_MOTOR_SENSE_MODE == USER_MOTOR_SENSE_RPS)
                        
#else             
    #if(USER_MOTOR_HIGHSPEED_MODE == USER_MOTOR_HIGHSPEED_FLUX)
                        pMotor->tc_ctrl.Speed = pMotor->flux_ctrl.ElecFreqHz_Filter;
                        Tc_Cal(&pMotor->tc_ctrl);
                        pMotor->foc_ctrl.IdRef = 0.0f;
                        pMotor->foc_ctrl.IqRef = pMotor->tc_ctrl.IqRef;
                        Motor_SpeedSwitchToLow(pMotor);
    #elif(USER_MOTOR_HIGHSPEED_MODE == USER_MOTOR_HIGHSPEED_SMO)
                        pMotor->tc_ctrl.Speed = pMotor->smo_ctrl.ElecFreqHz_Filter;
                        Tc_Cal(&pMotor->tc_ctrl);
                        pMotor->foc_ctrl.IdRef = 0.0f;
                        pMotor->foc_ctrl.IqRef = pMotor->tc_ctrl.IqRef;
                        Motor_SpeedSwitchToLow(pMotor);
    #endif
#endif
                        break;
                    }
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

void Hallest_Angle_Cal(ST_MOTOR_TASK* pMotor)
{
    if((pMotor->speed_mode == EM_MOTOR_SPEED_MODE_CLOSELOOP1)
       || (pMotor->speed_mode == EM_MOTOR_SPEED_MODE_CLOSELOOP2))
    {
        Hallest_Low_Speed(&pMotor->hall_ctrl);
    }
    else if(pMotor->speed_mode == EM_MOTOR_SPEED_MODE_CLOSELOOP3)
    {
        Hallest_High_Speed(&pMotor->hall_ctrl);
    }
    else{}
        
    Hallest_Angle_Inc(&pMotor->hall_ctrl, 0x11);
}

void Motor_Foc_Cal(ST_MOTOR_TASK* pMotor)
{
#if(USER_MOTOR_SENSE_MODE == USER_MOTOR_SENSE_HALL)
    Hallest_Angle_Cal(pMotor);
    pMotor->foc_ctrl.AngleRad = pMotor->hall_ctrl.AngleRad;
#elif(USER_MOTOR_SENSE_MODE == USER_MOTOR_SENSE_RPS)
    
#else
    Est_Flux(&pMotor->foc_ctrl, &pMotor->flux_ctrl);
    Est_SMO(&pMotor->foc_ctrl, &pMotor->smo_ctrl);
    switch(pMotor->speed_mode)
    {
    case EM_MOTOR_SPEED_MODE_CLOSELOOP1:
        {
    #if(USER_MOTOR_START_MODE == USER_MOTOR_START_IF)
            Est_IF(&pMotor->if_ctrl, pMotor->flux_ctrl.AngleRad);
            pMotor->foc_ctrl.AngleRad = pMotor->if_ctrl.AngleRad;
    #elif(USER_MOTOR_START_MODE == USER_MOTOR_START_FLUX)
            pMotor->foc_ctrl.AngleRad = pMotor->flux_ctrl.AngleRad;
    #endif
            break;
        }
    case EM_MOTOR_SPEED_MODE_CLOSELOOP2:
        {
    #if(USER_MOTOR_LOWSPEED_MODE == USER_MOTOR_LOWSPEED_FLUX)
            pMotor->foc_ctrl.AngleRad = pMotor->flux_ctrl.AngleRad;
    #endif
            break;
        }
    case EM_MOTOR_SPEED_MODE_CLOSELOOP3:
        {
    #if(USER_MOTOR_HIGHSPEED_MODE == USER_MOTOR_HIGHSPEED_FLUX)
            pMotor->foc_ctrl.AngleRad = pMotor->flux_ctrl.AngleRad;
    #elif(USER_MOTOR_HIGHSPEED_MODE == USER_MOTOR_HIGHSPEED_SMO)
            pMotor->foc_ctrl.AngleRad = pMotor->smo_ctrl.AngleRad;
    #endif
            break;
        }
    default:break;
    }
#endif
    
    Foc_Cal(&pMotor->foc_ctrl);
}

