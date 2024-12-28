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
    MotorFoc_IF_Init_F(&pMotor->IF_CTRL);
    MotorFoc_VF_Init_F(&pMotor->VF_CTRL);
    MotorFoc_SRAD_Init_F(&pMotor->SRAD_CTRL);
    MotorFoc_Current_Init_F(&pMotor->CURRENT_CTRL);
    Est_Flux_Init_F(&pMotor->FLUX_CTRL);
    Est_SMO_Init_F(&pMotor->SMO_CTRL);
    
    pMotor->Motor_Loop_Mode = MOTOR_OPENLOOP;
}

/**********************************************************************************************
Function: MotorTask_SRAD_Flow
Description: 电机控制速度环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_SRAD_Flow(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_Flow == MOTOR_STATE_RUN)
    {
        pMotor->SRAD_CTRL._I_F_SRAD = pMotor->FLUX_CTRL.FL_SRAD.F_Filter_out;
        switch(pMotor->Motor_Loop_Mode)
        {
        case MOTOR_ALIGNLOOP:
            {
                
            }break;
        case MOTOR_OPENLOOP:
            {
                MotorFoc_IF_OPEN_F(&pMotor->IF_CTRL);
                pMotor->CURRENT_CTRL._I_F_IdRef = 0.0f;
                pMotor->CURRENT_CTRL._I_F_IqRef = pMotor->IF_CTRL._I_F_DIR_Target*pMotor->IF_CTRL.Ramp_Iq.F_Output;
                if(pMotor->SRAD_CTRL._I_F_SRAD >= 30.0f)
                {
                    if(++pMotor->flow_cnt >= 200)
                    {
                        PID_Pos_Init_F(&pMotor->SRAD_CTRL.PID_SRAD, pMotor->CURRENT_CTRL._I_F_IqRef);
                        Ramp_Init_F(&pMotor->SRAD_CTRL.Ramp_SRAD, pMotor->SRAD_CTRL._I_F_SRAD + 1.0f);
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
                MotorFoc_SRAD_Loop_F(&pMotor->SRAD_CTRL);
                pMotor->CURRENT_CTRL._I_F_IdRef = pMotor->SRAD_CTRL._O_F_IdRef;
                pMotor->CURRENT_CTRL._I_F_IqRef = pMotor->SRAD_CTRL._O_F_IqRef;
            }break;
        case MOTOR_CLOSELOOP2:
            {
                MotorFoc_SRAD_Loop_F(&pMotor->SRAD_CTRL);
                pMotor->CURRENT_CTRL._I_F_IdRef = pMotor->SRAD_CTRL._O_F_IdRef;
                pMotor->CURRENT_CTRL._I_F_IqRef = pMotor->SRAD_CTRL._O_F_IqRef;
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
                    pMotor->SVPWM_CTRL._I_F_Ia_Offset /= 20.0f;
                    pMotor->SVPWM_CTRL._I_F_Ib_Offset /= 20.0f;
                    pMotor->SVPWM_CTRL._I_F_Ic_Offset /= 20.0f;
                    pMotor->Motor_Flow = MOTOR_STATE_IDLE;
                }
                else
                {
                    pMotor->SVPWM_CTRL._I_F_Ia_Offset += pMotor->SVPWM_CTRL._I_F_Ia_Data;
                    pMotor->SVPWM_CTRL._I_F_Ib_Offset += pMotor->SVPWM_CTRL._I_F_Ib_Data;
                    pMotor->SVPWM_CTRL._I_F_Ic_Offset += pMotor->SVPWM_CTRL._I_F_Ic_Data;
                }
            }
            else
            {
                pMotor->SVPWM_CTRL._I_F_Ia_Offset = 0.0f;
                pMotor->SVPWM_CTRL._I_F_Ib_Offset = 0.0f;
                pMotor->SVPWM_CTRL._I_F_Ic_Offset = 0.0f;
                cnt = 0;
            }
                
#else
                
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                if(++cnt > 20)
                {
                    cnt = 0;
                    pMotor->SVPWM_CTRL._I_F_Ishunt_1_Offset /= 20.0f;
                    pMotor->SVPWM_CTRL._I_F_Ishunt_2_Offset /= 20.0f;
                    pMotor->Motor_Flow = MOTOR_STATE_IDLE;
                }
                else
                {
                    pMotor->SVPWM_CTRL._I_F_Ishunt_1_Offset += pMotor->SVPWM_CTRL._I_F_Ishunt_1_Data;
                    pMotor->SVPWM_CTRL._I_F_Ishunt_2_Offset += pMotor->SVPWM_CTRL._I_F_Ishunt_2_Data;
                }
            }
            else
            {
                pMotor->SVPWM_CTRL._I_F_Ishunt_1_Offset = 0.0f;
                pMotor->SVPWM_CTRL._I_F_Ishunt_2_Offset = 0.0f;
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
                MotorFoc_Clark_F(&pMotor->SVPWM_CTRL);
                
                pMotor->FLUX_CTRL._I_F_Ialfa = pMotor->SVPWM_CTRL._O_F_Ialfa;
                pMotor->FLUX_CTRL._I_F_Ibeta = pMotor->SVPWM_CTRL._O_F_Ibeta;
                pMotor->FLUX_CTRL._I_F_IdRef = pMotor->SRAD_CTRL._O_F_IdRef;
                pMotor->FLUX_CTRL._I_F_Ualfa = pMotor->SVPWM_CTRL._O_F_Ualfa;
                pMotor->FLUX_CTRL._I_F_Ubeta = pMotor->SVPWM_CTRL._O_F_Ubeta;
                Est_Flux_F(&pMotor->FLUX_CTRL);
                
//                pMotor->SMO_CTRL._I_F_Ialfa = pMotor->SVPWM_CTRL._O_F_Ialfa;
//                pMotor->SMO_CTRL._I_F_Ibeta = pMotor->SVPWM_CTRL._O_F_Ibeta;
//                pMotor->SMO_CTRL._I_F_Ualfa = pMotor->SVPWM_CTRL._O_F_Ualfa;
//                pMotor->SMO_CTRL._I_F_Ubeta = pMotor->SVPWM_CTRL._O_F_Ubeta;
//                Est_SMO_F(&pMotor->SMO_CTRL);
                
                switch(pMotor->Motor_Loop_Mode)
                {
                case MOTOR_ALIGNLOOP:
                    {
                        
                    }break;
                case MOTOR_OPENLOOP:
                    {
                        pMotor->SVPWM_CTRL.TG_Triangle = pMotor->FLUX_CTRL.TG_Triangle;
//                        MotorFoc_IF_CURRENT_F(&pMotor->IF_CTRL);
//                        pMotor->SVPWM_CTRL.TG_Triangle.F_Angle = pMotor->IF_CTRL._O_F_Angle;
//                        pMotor->SVPWM_CTRL.TG_Triangle.F_Sin = Math_Sin_F(pMotor->SVPWM_CTRL.TG_Triangle.F_Angle);
//                        pMotor->SVPWM_CTRL.TG_Triangle.F_Cos = Math_Cos_F(pMotor->SVPWM_CTRL.TG_Triangle.F_Angle);
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
                
                MotorFoc_Park_F(&pMotor->SVPWM_CTRL);
                pMotor->CURRENT_CTRL._I_F_Id = pMotor->SVPWM_CTRL._O_F_Id;
                pMotor->CURRENT_CTRL._I_F_Iq = pMotor->SVPWM_CTRL._O_F_Iq;
                MotorFoc_Current_Loop_F(&pMotor->CURRENT_CTRL);
                
                pMotor->SVPWM_CTRL._I_F_Ud = pMotor->CURRENT_CTRL._O_F_Ud;
                pMotor->SVPWM_CTRL._I_F_Uq = pMotor->CURRENT_CTRL._O_F_Uq;
                MotorFoc_Ipark_F(&pMotor->SVPWM_CTRL);
                
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
