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
    MotorFoc_SVPWM_Init_F(&pMotor->SVPWM_CTRL);
    MotorFoc_SRAD_Init_F(&pMotor->SRAD_CTRL);
    MotorFoc_Current_Init_F(&pMotor->CURRENT_CTRL);
    Est_Flux_Init_F(&pMotor->FLUX_CTRL);
    Est_SMO_Init_F(&pMotor->SMO_CTRL);
    
    Ramp_Init_F(&pMotor->LOOP_CTRL.Align_Ramp, pMotor->LOOP_CTRL.Align_Ramp.F_Init);
    pMotor->SVPWM_CTRL.TG_Triangle.F_Angle = 1.5f*MATH_PI_F;
    Math_SinCos_F(&pMotor->SVPWM_CTRL.TG_Triangle);
    pMotor->Motor_Loop_Mode = MOTOR_ALIGNLOOP;
    
//    pMotor->Motor_Loop_Mode = MOTOR_OPENLOOP;
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
        pMotor->SRAD_CTRL._I_F_SRAD = pMotor->FLUX_CTRL.FL_SRAD.F_Filter_out;
        switch(pMotor->Motor_Loop_Mode)
        {
            case MOTOR_ALIGNLOOP:
            {
                Ramp_Cal_F(&pMotor->LOOP_CTRL.Align_Ramp);
                pMotor->LOOP_CTRL._V_Q32U_Align_cnt++;
                if(pMotor->LOOP_CTRL._V_Q32U_Align_cnt >= pMotor->LOOP_CTRL._P_Q32U_Align_Time3 + pMotor->LOOP_CTRL._P_Q32U_Align_Time2 + pMotor->LOOP_CTRL._P_Q32U_Align_Time1)
                {
                    pMotor->LOOP_CTRL._V_Q32U_Align_cnt = 0U;
                    pMotor->Motor_Loop_Mode = MOTOR_CLOSELOOP1;
                }
                else if(pMotor->LOOP_CTRL._V_Q32U_Align_cnt >= pMotor->LOOP_CTRL._P_Q32U_Align_Time2 + pMotor->LOOP_CTRL._P_Q32U_Align_Time1)
                {
                    pMotor->CURRENT_CTRL._I_F_IqRef = 0.0f;
                }
                else if(pMotor->LOOP_CTRL._V_Q32U_Align_cnt >= pMotor->LOOP_CTRL._P_Q32U_Align_Time1)
                {
                    pMotor->CURRENT_CTRL._I_F_IqRef = pMotor->LOOP_CTRL.Align_Ramp.F_Output;
                    pMotor->SVPWM_CTRL.TG_Triangle.F_Angle = MATH_2PI_F;
                }
                else
                {
                    pMotor->CURRENT_CTRL._I_F_IqRef = pMotor->LOOP_CTRL.Align_Ramp.F_Output;
                    pMotor->SVPWM_CTRL.TG_Triangle.F_Angle = 1.5f*MATH_PI_F;
                }
                break;
            }
            case MOTOR_OPENLOOP:
            {
                MotorFoc_VF_OPEN_F(&pMotor->VF_CTRL);
                MotorFoc_IF_OPEN_F(&pMotor->IF_CTRL);
                pMotor->CURRENT_CTRL._I_F_IdRef = 0;
                pMotor->CURRENT_CTRL._I_F_IqRef = pMotor->IF_CTRL.Ramp_Iq.F_Output;
                break;
            }
            case MOTOR_CLOSELOOP1:
            {
                MotorFoc_SRAD_Loop_F(&pMotor->SRAD_CTRL);
                pMotor->CURRENT_CTRL._I_F_IdRef = pMotor->SRAD_CTRL._O_F_IdRef;
                pMotor->CURRENT_CTRL._I_F_IqRef = pMotor->SRAD_CTRL._O_F_IqRef;
                
                pMotor->SRAD_CTRL._I_F_SRAD_Target = pMotor->LOOP_CTRL._P_F_Close1_Target_SRAD;
                pMotor->SRAD_CTRL.Ramp_SRAD.F_ADDStep =  pMotor->LOOP_CTRL._P_F_Close1_SRAD_Step;
                pMotor->SRAD_CTRL.Ramp_SRAD.F_SUBStep = -pMotor->LOOP_CTRL._P_F_Close1_SRAD_Step;
                
                if(pMotor->SRAD_CTRL._I_F_SRAD >= pMotor->LOOP_CTRL._P_F_Close1_Switch_SRAD)
                {
                    if(++pMotor->LOOP_CTRL._V_Q32U_Close1_cnt >= pMotor->LOOP_CTRL._P_Q32U_Close1_Switch_Time)
                    {
                        pMotor->LOOP_CTRL._V_Q32U_Close1_cnt = 0;
                        pMotor->FLUX_CTRL.Est_State_Flag = 1U;
                        pMotor->SRAD_CTRL.Ramp_SRAD.F_ADDStep =  pMotor->LOOP_CTRL._P_F_Close2_SRAD_Step;
                        pMotor->SRAD_CTRL.Ramp_SRAD.F_SUBStep = -pMotor->LOOP_CTRL._P_F_Close2_SRAD_Step;
                        pMotor->Motor_Loop_Mode = MOTOR_CLOSELOOP2;
                    }
                }
                else
                {
                    pMotor->LOOP_CTRL._V_Q32U_Close1_cnt = 0;
                }
                break;
            }
            case MOTOR_CLOSELOOP2:
            {
                MotorFoc_SRAD_Loop_F(&pMotor->SRAD_CTRL);
                pMotor->CURRENT_CTRL._I_F_IdRef = pMotor->SRAD_CTRL._O_F_IdRef;
                pMotor->CURRENT_CTRL._I_F_IqRef = pMotor->SRAD_CTRL._O_F_IqRef;
                break;
            }
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
            break;
        }
        case MOTOR_STATE_INIT:
        {
            static uint32_t cnt = 0U;
#if(HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                if(++cnt > 20U)
                {
                    cnt = 0U;
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
                cnt = 0U;
            }
            
#else
            
            if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
            {
                if(++cnt > 20U)
                {
                    cnt = 0U;
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
                cnt = 0U;
            }
#endif
            break;
        }
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
            break;
        }
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
            break;
        }
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
            break;
        }
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
                
                pMotor->SMO_CTRL._I_F_Ialfa = pMotor->SVPWM_CTRL._O_F_Ialfa;
                pMotor->SMO_CTRL._I_F_Ibeta = pMotor->SVPWM_CTRL._O_F_Ibeta;
                pMotor->SMO_CTRL._I_F_Ualfa = pMotor->SVPWM_CTRL._O_F_Ualfa;
                pMotor->SMO_CTRL._I_F_Ubeta = pMotor->SVPWM_CTRL._O_F_Ubeta;
                Est_SMO_F(&pMotor->SMO_CTRL);
                
                switch(pMotor->Motor_Loop_Mode)
                {
                    case MOTOR_ALIGNLOOP:
                    {
                        Math_SinCos_F(&pMotor->SVPWM_CTRL.TG_Triangle);
                        break;
                    }
                    case MOTOR_OPENLOOP:
                    {
                        MotorFoc_IF_CURRENT_F(&pMotor->IF_CTRL);
                        pMotor->SVPWM_CTRL.TG_Triangle.F_Angle = pMotor->IF_CTRL._O_F_Angle;
                        Math_SinCos_F(&pMotor->SVPWM_CTRL.TG_Triangle);
                        break;
                    }
                    case MOTOR_CLOSELOOP1:
                    {
                        pMotor->SVPWM_CTRL.TG_Triangle = pMotor->FLUX_CTRL.TG_Triangle;
                        break;
                    }
                    case MOTOR_CLOSELOOP2:
                    {
                        pMotor->SVPWM_CTRL.TG_Triangle = pMotor->FLUX_CTRL.TG_Triangle;
                        break;
                    }
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
            break;
        }
        case MOTOR_STATE_BRAKE:
        {
            break;
        }
        default:break;
    }
}
