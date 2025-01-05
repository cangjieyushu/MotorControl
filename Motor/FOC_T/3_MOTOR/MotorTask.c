/**************************************************************************************************
*     File Name :                        MotorTask.c
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机子任务源文件
**************************************************************************************************/
#include "MotorTask.h"

/**********************************************************************************************
Function: MotorFoc_Init_F
Description: 电机控制参数初始化
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_Init_F(ST_MOTOR_TASK* pMotor)
{
    MotorFoc_IF_Init_T(&pMotor->IF_CTRL);
    MotorFoc_VF_Init_T(&pMotor->VF_CTRL);
    MotorFoc_SVPWM_Init_T(&pMotor->SVPWM_CTRL);
    MotorFoc_SRAD_Init_T(&pMotor->SRAD_CTRL);
    MotorFoc_Current_Init_T(&pMotor->CURRENT_CTRL);
    Est_Flux_Init_T(&pMotor->FLUX_CTRL);
    Est_SMO_Init_T(&pMotor->SMO_CTRL);
    
    pMotor->Motor_Loop_Mode = MOTOR_OPENLOOP;
}

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
        pMotor->SRAD_CTRL._I_Q14I_SRAD = pMotor->FLUX_CTRL.FL_SRAD.Q16I_Filter_out;
        switch(pMotor->Motor_Loop_Mode)
        {
        case MOTOR_ALIGNLOOP:
            {
                
            }break;
        case MOTOR_OPENLOOP:
            {
                MotorFoc_IF_OPEN_T(&pMotor->IF_CTRL);
                pMotor->CURRENT_CTRL._I_Q14I_IdRef = 0.0f;
                pMotor->CURRENT_CTRL._I_Q14I_IqRef = pMotor->IF_CTRL._I_Q14I_DIR_Target*pMotor->IF_CTRL.Ramp_Iq.Q32I_Output;
                if(pMotor->SRAD_CTRL._I_Q14I_SRAD >= 30)
                {
                    if(++pMotor->flow_cnt >= 200)
                    {
                        PID_Pos_Init_T(&pMotor->SRAD_CTRL.PID_SRAD, pMotor->CURRENT_CTRL._I_Q14I_IqRef);
                        Ramp_Init_T(&pMotor->SRAD_CTRL.Ramp_SRAD, pMotor->SRAD_CTRL._I_Q14I_SRAD + 10);
                        pMotor->Motor_Loop_Mode = MOTOR_CLOSELOOP1;
                    }
                }
                else
                {
                    pMotor->flow_cnt = 0;
                }
            }break;
        case MOTOR_CLOSELOOP1:
            {
                MotorFoc_SRAD_Loop_T(&pMotor->SRAD_CTRL);
                pMotor->CURRENT_CTRL._I_Q14I_IdRef = pMotor->SRAD_CTRL._O_Q14I_IdRef;
                pMotor->CURRENT_CTRL._I_Q14I_IqRef = pMotor->SRAD_CTRL._O_Q14I_IqRef;
            }break;
        case MOTOR_CLOSELOOP2:
            {
                MotorFoc_SRAD_Loop_T(&pMotor->SRAD_CTRL);
                pMotor->CURRENT_CTRL._I_Q14I_IdRef = pMotor->SRAD_CTRL._O_Q14I_IdRef;
                pMotor->CURRENT_CTRL._I_Q14I_IqRef = pMotor->SRAD_CTRL._O_Q14I_IqRef;
            }break;
        default:break;
        }
    }
    else if(pMotor->Motor_Flow == MOTOR_STATE_BRAKE)
    {
        
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
            pMotor->Motor_State_Flag.bit.pwm_output_flag = 0U;
            MotorFoc_Init_F(pMotor);
            pMotor->Motor_Flow = MOTOR_STATE_INIT;
        }break;
    case MOTOR_STATE_INIT:
        {
            static uint32_t cnt = 0;
#if(HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                if(++cnt > 20)
                {
                    cnt = 0;
                    pMotor->SVPWM_CTRL._I_Q14I_Ia_Offset /= 20.0f;
                    pMotor->SVPWM_CTRL._I_Q14I_Ib_Offset /= 20.0f;
                    pMotor->SVPWM_CTRL._I_Q14I_Ic_Offset /= 20.0f;
                    pMotor->Motor_Flow = MOTOR_STATE_IDLE;
                }
                else
                {
                    pMotor->SVPWM_CTRL._I_Q14I_Ia_Offset += pMotor->SVPWM_CTRL._I_Q14I_Ia_Data;
                    pMotor->SVPWM_CTRL._I_Q14I_Ib_Offset += pMotor->SVPWM_CTRL._I_Q14I_Ib_Data;
                    pMotor->SVPWM_CTRL._I_Q14I_Ic_Offset += pMotor->SVPWM_CTRL._I_Q14I_Ic_Data;
                }
            }
            else
            {
                pMotor->SVPWM_CTRL._I_Q14I_Ia_Offset = 0.0f;
                pMotor->SVPWM_CTRL._I_Q14I_Ib_Offset = 0.0f;
                pMotor->SVPWM_CTRL._I_Q14I_Ic_Offset = 0.0f;
                cnt = 0;
            }
                
#else
                
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                if(++cnt > 20)
                {
                    cnt = 0;
                    pMotor->SVPWM_CTRL._I_Q14I_Ishunt_1_Offset /= 20.0f;
                    pMotor->SVPWM_CTRL._I_Q14I_Ishunt_2_Offset /= 20.0f;
                    pMotor->Motor_Flow = MOTOR_STATE_IDLE;
                }
                else
                {
                    pMotor->SVPWM_CTRL._I_Q14I_Ishunt_1_Offset += pMotor->SVPWM_CTRL._I_Q14I_Ishunt_1_Data;
                    pMotor->SVPWM_CTRL._I_Q14I_Ishunt_2_Offset += pMotor->SVPWM_CTRL._I_Q14I_Ishunt_2_Data;
                }
            }
            else
            {
                pMotor->SVPWM_CTRL._I_Q14I_Ishunt_1_Offset = 0.0f;
                pMotor->SVPWM_CTRL._I_Q14I_Ishunt_2_Offset = 0.0f;
                cnt = 0;
            }
#endif
        }break;
    case MOTOR_STATE_IDLE:
        {
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                pMotor->Motor_Flow = MOTOR_STATE_BOOT;
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
                pMotor->Motor_Flow = MOTOR_STATE_POSITION;
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
                pMotor->Motor_Flow = MOTOR_STATE_RUN;
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
                MotorFoc_Clark_T(&pMotor->SVPWM_CTRL);
                
                pMotor->FLUX_CTRL._I_Q14I_Ialfa = pMotor->SVPWM_CTRL._O_Q14I_Ialfa;
                pMotor->FLUX_CTRL._I_Q14I_Ibeta = pMotor->SVPWM_CTRL._O_Q14I_Ibeta;
                pMotor->FLUX_CTRL._I_Q14I_IdRef = pMotor->SRAD_CTRL._O_Q14I_IdRef;
                pMotor->FLUX_CTRL._I_Q14I_Ualfa = pMotor->SVPWM_CTRL._O_Q14I_Ualfa;
                pMotor->FLUX_CTRL._I_Q14I_Ubeta = pMotor->SVPWM_CTRL._O_Q14I_Ubeta;
                Est_Flux_T(&pMotor->FLUX_CTRL);
                
                switch(pMotor->Motor_Loop_Mode)
                {
                case MOTOR_ALIGNLOOP:
                    {
                        
                    }break;
                case MOTOR_OPENLOOP:
                    {
                        pMotor->SVPWM_CTRL.TG_Triangle = pMotor->FLUX_CTRL.TG_Triangle;
                    }break;
                case MOTOR_CLOSELOOP1:
                    {
                        pMotor->SVPWM_CTRL.TG_Triangle = pMotor->FLUX_CTRL.TG_Triangle;
                    }break;
                case MOTOR_CLOSELOOP2:
                    {
                        pMotor->SVPWM_CTRL.TG_Triangle = pMotor->FLUX_CTRL.TG_Triangle;
                    }break;
                default:break;
                }
                
                MotorFoc_Park_T(&pMotor->SVPWM_CTRL);
                pMotor->CURRENT_CTRL._I_Q14I_Id = pMotor->SVPWM_CTRL._O_Q14I_Id;
                pMotor->CURRENT_CTRL._I_Q14I_Iq = pMotor->SVPWM_CTRL._O_Q14I_Iq;
                MotorFoc_Current_Loop_T(&pMotor->CURRENT_CTRL);
                
                pMotor->SVPWM_CTRL._I_Q14I_Ud = pMotor->CURRENT_CTRL._O_Q14I_Ud;
                pMotor->SVPWM_CTRL._I_Q14I_Uq = pMotor->CURRENT_CTRL._O_Q14I_Uq;
                MotorFoc_Ipark_T(&pMotor->SVPWM_CTRL);
                
                pMotor->Motor_State_Flag.bit.pwm_output_flag = 1U;
            }
            else
            {
                pMotor->Motor_State_Flag.bit.pwm_output_flag = 0U;
                pMotor->Motor_Flow = MOTOR_STATE_PRE;
            }
        }break;
    case MOTOR_STATE_BRAKE:
        {
            
        }break;
    default:break;
    }
}
