/**************************************************************************************************
*     File Name :                        MotorTask.c
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机子任务源文件
**************************************************************************************************/
#include "MotorTask.h"

#if(HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
#define MotorSQ_Offset_Check            MotorSQ_Offset_Check_Three
#define MotorTask_Init_Flow_ADC_Read    MotorTask_Init_Flow_ADC_Read_Three
#define MotorTask_Run_Flow_ADC_Read     MotorTask_Run_Flow_ADC_Read_Three
#define MotorTask_Run_Flow_PWM_Set      MotorTask_Run_Flow_PWM_Set_Three
#else
#define MotorSQ_Offset_Check            MotorSQ_Offset_Check_One
#define MotorTask_Init_Flow_ADC_Read    MotorTask_Init_Flow_ADC_Read_One
#define MotorTask_Run_Flow_ADC_Read     MotorTask_Run_Flow_ADC_Read_One
#define MotorTask_Run_Flow_PWM_Set      MotorTask_Run_Flow_PWM_Set_One
#endif

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
                Ramp_Cal_T(&pMotor->LOOP_CTRL.Align_Ramp);
                pMotor->LOOP_CTRL._V_Q32U_Align_cnt++;
                if(pMotor->LOOP_CTRL._V_Q32U_Align_cnt >= pMotor->LOOP_CTRL._P_Q32U_Align_Time3 + pMotor->LOOP_CTRL._P_Q32U_Align_Time2 + pMotor->LOOP_CTRL._P_Q32U_Align_Time1)
                {
                    pMotor->LOOP_CTRL._V_Q32U_Align_cnt = 0U;
                    pMotor->Motor_Loop_Mode = MOTOR_CLOSELOOP1;
                }
                else if(pMotor->LOOP_CTRL._V_Q32U_Align_cnt >= pMotor->LOOP_CTRL._P_Q32U_Align_Time2 + pMotor->LOOP_CTRL._P_Q32U_Align_Time1)
                {
                    pMotor->CURRENT_CTRL._I_Q14I_IqRef = 0;
                }
                else if(pMotor->LOOP_CTRL._V_Q32U_Align_cnt >= pMotor->LOOP_CTRL._P_Q32U_Align_Time1)
                {
                    pMotor->CURRENT_CTRL._I_Q14I_IqRef = pMotor->LOOP_CTRL.Align_Ramp.Q32I_Output;
                    pMotor->SVPWM_CTRL.TG_Triangle.Q12U_Angle = 0;
                }
                else
                {
                    pMotor->CURRENT_CTRL._I_Q14I_IqRef = pMotor->LOOP_CTRL.Align_Ramp.Q32I_Output;
                    pMotor->SVPWM_CTRL.TG_Triangle.Q12U_Angle = 3072;
                }
                break;
            }
            case MOTOR_OPENLOOP:
            {
#if(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_IF)
                MotorFoc_IF_OPEN_T(&pMotor->IF_CTRL);
                
#elif(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_IF)
                
#elif(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_HFI)
                
#elif(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_FLUX)
                
#endif
                MotorFoc_VF_OPEN_T(&pMotor->VF_CTRL);
                pMotor->CURRENT_CTRL._I_Q14I_IdRef = 0;
                pMotor->CURRENT_CTRL._I_Q14I_IqRef = pMotor->IF_CTRL.Ramp_Iq.Q32I_Output;
                if(++pMotor->LOOP_CTRL._V_Q32U_Open_min_cnt >= pMotor->LOOP_CTRL._P_Q32U_Open_Min_Time)
                {
                    if(pMotor->SRAD_CTRL._I_Q14I_SRAD >= pMotor->LOOP_CTRL._P_F_Open_Switch_SRAD)
                    {
                        if(++pMotor->LOOP_CTRL._V_Q32U_Open_cnt >= pMotor->LOOP_CTRL._P_Q32U_Open_Switch_Time)
                        {
                            pMotor->LOOP_CTRL._V_Q32U_Open_min_cnt = 0U;
                            pMotor->LOOP_CTRL._V_Q32U_Open_cnt = 0U;
                            
                            PID_Pos_Init_T(&pMotor->SRAD_CTRL.PID_SRAD, pMotor->CURRENT_CTRL._I_Q14I_IqRef);
                            Ramp_Init_T(&pMotor->SRAD_CTRL.Ramp_SRAD, pMotor->SRAD_CTRL._I_Q14I_SRAD);
                            
                            pMotor->IF_CTRL.Ramp_AngleERR.Q32I_Init = pMotor->IF_CTRL._O_Q12U_Angle - pMotor->FLUX_CTRL.TG_Triangle.Q12U_Angle;
                            pMotor->Motor_Loop_Mode = MOTOR_CLOSELOOP1;
                        }
                    }
                    else
                    {
                        pMotor->LOOP_CTRL._V_Q32U_Open_cnt = 0U;
                    }
                }
                break;
            }
            case MOTOR_CLOSELOOP1:
            {
                MotorFoc_SRAD_Loop_T(&pMotor->SRAD_CTRL);
                pMotor->CURRENT_CTRL._I_Q14I_IdRef = pMotor->SRAD_CTRL._O_Q14I_IdRef;
                pMotor->CURRENT_CTRL._I_Q14I_IqRef = pMotor->SRAD_CTRL._O_Q14I_IqRef;
                
                pMotor->SRAD_CTRL._I_Q14I_SRAD_Target = pMotor->LOOP_CTRL._P_F_Close1_Target_SRAD;
                pMotor->SRAD_CTRL.Ramp_SRAD.Q32I_ADDStep =  pMotor->LOOP_CTRL._P_F_Close1_SRAD_Step;
                pMotor->SRAD_CTRL.Ramp_SRAD.Q32I_SUBStep = -pMotor->LOOP_CTRL._P_F_Close1_SRAD_Step;
                
//                if(pMotor->SRAD_CTRL._I_Q14I_SRAD >= pMotor->LOOP_CTRL._P_F_Close1_Switch_SRAD)
//                {
//                    if(++pMotor->LOOP_CTRL._V_Q32U_Close1_cnt >= pMotor->LOOP_CTRL._P_Q32U_Close1_Switch_Time)
//                    {
//                        pMotor->LOOP_CTRL._V_Q32U_Close1_cnt = 0;
//                        pMotor->FLUX_CTRL.Est_State_Flag = 1U;
//                        pMotor->SRAD_CTRL.Ramp_SRAD.Q32I_ADDStep =  pMotor->LOOP_CTRL._P_F_Close2_SRAD_Step;
//                        pMotor->SRAD_CTRL.Ramp_SRAD.Q32I_SUBStep = -pMotor->LOOP_CTRL._P_F_Close2_SRAD_Step;
//                        pMotor->Motor_Loop_Mode = MOTOR_CLOSELOOP2;
//                    }
//                }
//                else
//                {
//                    pMotor->LOOP_CTRL._V_Q32U_Close1_cnt = 0;
//                }
                break;
            }
            case MOTOR_CLOSELOOP2:
            {
                MotorFoc_SRAD_Loop_T(&pMotor->SRAD_CTRL);
                pMotor->CURRENT_CTRL._I_Q14I_IdRef = pMotor->SRAD_CTRL._O_Q14I_IdRef;
                pMotor->CURRENT_CTRL._I_Q14I_IqRef = pMotor->SRAD_CTRL._O_Q14I_IqRef;
                break;
            }
            default:break;
        }
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
        MotorFoc_IF_Init_T(&pMotor->IF_CTRL);
        MotorFoc_VF_Init_T(&pMotor->VF_CTRL);
        
        MotorFoc_SVPWM_Init_T(&pMotor->SVPWM_CTRL);
        MotorFoc_SRAD_Init_T(&pMotor->SRAD_CTRL);
        MotorFoc_Current_Init_T(&pMotor->CURRENT_CTRL);
        
        Est_Flux_Init_T(&pMotor->FLUX_CTRL);
        Est_SMO_Init_T(&pMotor->SMO_CTRL);
        
        Ramp_Init_T(&pMotor->LOOP_CTRL.Align_Ramp, pMotor->LOOP_CTRL.Align_Ramp.Q32I_Init);
        pMotor->SVPWM_CTRL.TG_Triangle.Q12U_Angle = 3072;
        Math_SinCos_T(&pMotor->SVPWM_CTRL.TG_Triangle);
        pMotor->Motor_Loop_Mode = MOTOR_ALIGNLOOP;
        
        pMotor->BRAKE_CTRL.Flag.bit.b0_init = 0U;
        
        pMotor->Motor_Flow = MOTOR_STATE_INIT;
    }
    else
    {
        MH_PWM_Output_Disable();
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
        MotorTask_Init_Flow_ADC_Read(&pMotor->MS_OFFSET);
        
        if(MotorSQ_Offset_Check_Init(&pMotor->MS_OFFSET) == SUCS)
        {
            switch(MotorSQ_Offset_Check(&pMotor->MS_OFFSET))
            {
                case ING:
                {
                    break;
                }
                case SUCS:
                {
                    pMotor->SVPWM_CTRL._I_Q12I_Ia_Offset = pMotor->MS_OFFSET._O_Q12I_Ia_Offset;
                    pMotor->SVPWM_CTRL._I_Q12I_Ib_Offset = pMotor->MS_OFFSET._O_Q12I_Ib_Offset;
                    pMotor->SVPWM_CTRL._I_Q12I_Ic_Offset = pMotor->MS_OFFSET._O_Q12I_Ic_Offset;
                    pMotor->SVPWM_CTRL._I_Q12I_Ishunt_1_Offset = pMotor->MS_OFFSET._O_Q12I_Ishunt_1_Offset;
                    pMotor->SVPWM_CTRL._I_Q12I_Ishunt_2_Offset = pMotor->MS_OFFSET._O_Q12I_Ishunt_2_Offset;
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
            MH_PWM_Output_Disable();
        }
    }
    else
    {
        MH_PWM_Output_Disable();
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
        pMotor->Motor_Flow = MOTOR_STATE_BOOT;
    }
    else
    {
        MH_PWM_Output_Disable();
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
            switch(MotorSQ_Boot_Check(&pMotor->MS_BOOT))
            {
                case ING:
                {
//                    MH_HPWM_LPWM_LOpen(Q32I_RHT_12(pMotor->MS_BOOT._P_Q12U_boot_duty*pMotor->MS_CTRL.PWM_CTRL._P_Q14U_start_pwm_freq));
                    break;
                }
                case SUCS:
                {
                    MH_PWM_Output_Disable();
                    pMotor->Motor_Flow = MOTOR_STATE_POSITION;
                    break;
                }
                case FAIL:
                {
                    MH_PWM_Output_Disable();
                    pMotor->Motor_Flow = MOTOR_STATE_PRE;
                    break;
                }
                default:break;
            }
        }
        else
        {
//            MH_HPWM_LPWM_HOpen(Q32I_RHT_12(pMotor->MS_BOOT._P_Q12U_boot_duty*pMotor->MS_CTRL.PWM_CTRL._P_Q14U_start_pwm_freq));
//            MH_ADC_TrigTime_Set(Q32I_RHT_12(pMotor->MS_BOOT._P_Q12U_boot_duty*pMotor->MS_CTRL.PWM_CTRL._P_Q14U_start_pwm_freq));
        }
    }
    else
    {
        MH_PWM_Output_Disable();
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
        pMotor->Motor_Flow = MOTOR_STATE_RUN;
    }
    else
    {
        MH_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
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
        MotorTask_Run_Flow_ADC_Read(&pMotor->SVPWM_CTRL);
        
        MotorFoc_Clark_T(&pMotor->SVPWM_CTRL);
        
        pMotor->FLUX_CTRL._I_Q14I_Ialfa = pMotor->SVPWM_CTRL._O_Q14I_Ialfa;
        pMotor->FLUX_CTRL._I_Q14I_Ibeta = pMotor->SVPWM_CTRL._O_Q14I_Ibeta;
        pMotor->FLUX_CTRL._I_Q14I_Ualfa = pMotor->SVPWM_CTRL._O_Q14I_Ualfa;
        pMotor->FLUX_CTRL._I_Q14I_Ubeta = pMotor->SVPWM_CTRL._O_Q14I_Ubeta;
        Est_Flux_T(&pMotor->FLUX_CTRL);
        
        pMotor->SMO_CTRL._I_Q14I_Ialfa = pMotor->SVPWM_CTRL._O_Q14I_Ialfa;
        pMotor->SMO_CTRL._I_Q14I_Ibeta = pMotor->SVPWM_CTRL._O_Q14I_Ibeta;
        pMotor->SMO_CTRL._I_Q14I_Ualfa = pMotor->SVPWM_CTRL._O_Q14I_Ualfa;
        pMotor->SMO_CTRL._I_Q14I_Ubeta = pMotor->SVPWM_CTRL._O_Q14I_Ubeta;
        Est_SMO_T(&pMotor->SMO_CTRL);
        
        switch(pMotor->Motor_Loop_Mode)
        {
            case MOTOR_ALIGNLOOP:
            {
                Math_SinCos_T(&pMotor->SVPWM_CTRL.TG_Triangle);
                break;
            }
            case MOTOR_OPENLOOP:
            {
                MotorFoc_IF_CURRENT_T(&pMotor->IF_CTRL);
                pMotor->SVPWM_CTRL.TG_Triangle.Q12U_Angle = pMotor->IF_CTRL._O_Q12U_Angle;
                Math_SinCos_T(&pMotor->SVPWM_CTRL.TG_Triangle);
                break;
            }
            case MOTOR_CLOSELOOP1:
            {
                MotorFoc_IF_CLOSE_T(&pMotor->IF_CTRL);
                pMotor->SVPWM_CTRL.TG_Triangle.Q12U_Angle = pMotor->FLUX_CTRL.TG_Triangle.Q12U_Angle + pMotor->IF_CTRL.Ramp_AngleERR.Q32I_Output;
                MATH_ANGLE_MOD_T(pMotor->SVPWM_CTRL.TG_Triangle.Q12U_Angle);
                Math_SinCos_T(&pMotor->SVPWM_CTRL.TG_Triangle);
                break;
            }
            case MOTOR_CLOSELOOP2:
            {
                pMotor->SVPWM_CTRL.TG_Triangle = pMotor->FLUX_CTRL.TG_Triangle;
                break;
            }
            default:break;
        }
        
        MotorFoc_Park_T(&pMotor->SVPWM_CTRL);
        pMotor->CURRENT_CTRL._I_Q14I_Id = pMotor->SVPWM_CTRL._O_Q14I_Id;
        pMotor->CURRENT_CTRL._I_Q14I_Iq = pMotor->SVPWM_CTRL._O_Q14I_Iq;
        MotorFoc_Current_Loop_T(&pMotor->CURRENT_CTRL);
        
        pMotor->SVPWM_CTRL._I_Q14I_Ud = pMotor->CURRENT_CTRL._O_Q14I_Ud;
        pMotor->SVPWM_CTRL._I_Q14I_Uq = pMotor->CURRENT_CTRL._O_Q14I_Uq;
        
//        if(pMotor->Motor_Loop_Mode == MOTOR_OPENLOOP)
//        {
//            MotorFoc_VF_CURRENT_T(&pMotor->VF_CTRL);
//            pMotor->SVPWM_CTRL.TG_Triangle.Q12U_Angle = pMotor->VF_CTRL._O_Q12U_Angle;
//            Math_SinCos_T(&pMotor->SVPWM_CTRL.TG_Triangle);
//            pMotor->SVPWM_CTRL._I_Q14I_Ud = 0;
//            pMotor->SVPWM_CTRL._I_Q14I_Uq = pMotor->VF_CTRL.Ramp_Vq.Q32I_Output;
//        }
        
        MotorFoc_Ipark_T(&pMotor->SVPWM_CTRL);
        
        MotorTask_Run_Flow_PWM_Set(&pMotor->SVPWM_CTRL);
        
        MH_PWM_Output_Enable();
    }
    else
    {
        MH_PWM_Output_Disable();
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
        MH_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
    else
    {
        if(MotorSQ_Brake_Init(&pMotor->BRAKE_CTRL) == SUCS)
        {
//            MH_HPWM_LPWM_LOpen(Q32I_RHT_12(pMotor->BRAKE_CTRL._O_Q12U_brake_duty*pMotor->MS_CTRL.PWM_CTRL._P_Q14U_high_pwm_freq));
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
