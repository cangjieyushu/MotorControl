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
#elif(HAL_CURRENT_SAMPLE_MODE == HAL_ONE_SHUNT)
#define MotorSQ_Offset_Check            MotorSQ_Offset_Check_One
#define MotorTask_Init_Flow_ADC_Read    MotorTask_Init_Flow_ADC_Read_One
#define MotorTask_Run_Flow_ADC_Read     MotorTask_Run_Flow_ADC_Read_One
#define MotorTask_Run_Flow_PWM_Set      MotorTask_Run_Flow_PWM_Set_One
#endif

#if(MOTOR_EST_MODE == MOTOR_EST_FLUX)
#define Motor_EST                       FLUX_CTRL
#elif(MOTOR_EST_MODE == MOTOR_EST_SMO)
#define Motor_EST                       SMO_CTRL
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

void MotorTask_AlignLoop_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_OpenLoop_Flow(ST_MOTOR_TASK* pMotor);
void MotorTask_CloseLoop_Flow(ST_MOTOR_TASK* pMotor);

pMOTOR_FUN Motor_Loop_Flow_Function[MOTOR_CLOSELOOP+1] =
{
    MotorTask_AlignLoop_Flow,
    MotorTask_OpenLoop_Flow,
    MotorTask_CloseLoop_Flow
};

/**********************************************************************************************
Function: MotorTask_AlignLoop_Flow
Description: 电机控制强拖定位
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_AlignLoop_Flow(ST_MOTOR_TASK* pMotor)
{
    Ramp_Cal_F(&pMotor->LOOP_CTRL.Align_Ramp);
    pMotor->LOOP_CTRL._V_Q32U_Align_cnt++;
    if(pMotor->LOOP_CTRL._V_Q32U_Align_cnt == 0U)
    {
        pMotor->SVPWM_CTRL.TG_Triangle.F_Angle = 1.5f*MATH_PI_F;
        Ramp_Init_F(&pMotor->LOOP_CTRL.Align_Ramp, pMotor->LOOP_CTRL.Align_Ramp.F_Init);
        pMotor->CURRENT_CTRL._I_F_IdRef = pMotor->LOOP_CTRL.Align_Ramp.F_Output;
    }
    else if(pMotor->LOOP_CTRL._V_Q32U_Align_cnt == pMotor->LOOP_CTRL._P_Q32U_Align_Time1)
    {
        pMotor->SVPWM_CTRL.TG_Triangle.F_Angle = 0.0f*MATH_PI_F;
        pMotor->CURRENT_CTRL._I_F_IdRef = pMotor->LOOP_CTRL.Align_Ramp.F_Output;
    }
    else if(pMotor->LOOP_CTRL._V_Q32U_Align_cnt == pMotor->LOOP_CTRL._P_Q32U_Align_Time1 + pMotor->LOOP_CTRL._P_Q32U_Align_Time2)
    {
        pMotor->CURRENT_CTRL._I_F_IdRef = 0.0f;
    }
    else if(pMotor->LOOP_CTRL._V_Q32U_Align_cnt == pMotor->LOOP_CTRL._P_Q32U_Align_Time1 + pMotor->LOOP_CTRL._P_Q32U_Align_Time2 + pMotor->LOOP_CTRL._P_Q32U_Align_Time3)
    {
        pMotor->LOOP_CTRL._V_Q32U_Align_cnt = 0U;
        pMotor->Motor_Loop_Mode = MOTOR_OPENLOOP;
    }
    else{}
}

/**********************************************************************************************
Function: MotorTask_OpenLoop_Flow
Description: 电机控制开环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_OpenLoop_Flow(ST_MOTOR_TASK* pMotor)
{
#if(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_IF)
    pMotor->SRAD_CTRL._I_F_SRAD = pMotor->Motor_EST.FL_SRAD.F_Filter_out;
        
    MotorFoc_IF_OPEN_F(&pMotor->IF_CTRL);
    pMotor->CURRENT_CTRL._I_F_IdRef = 0.0f;
    pMotor->CURRENT_CTRL._I_F_IqRef = pMotor->IF_CTRL.Ramp_Iq.F_Output;
    
    if(++pMotor->LOOP_CTRL._V_Q32U_Open_min_cnt >= pMotor->LOOP_CTRL._P_Q32U_Open_Min_Time)
    {
        if(pMotor->SRAD_CTRL._I_F_SRAD >= pMotor->LOOP_CTRL._P_F_Open_Switch_SRAD)
        {
            if(++pMotor->LOOP_CTRL._V_Q32U_Open_cnt >= pMotor->LOOP_CTRL._P_Q32U_Open_Switch_Time)
            {
                pMotor->LOOP_CTRL._V_Q32U_Open_min_cnt = 0U;
                pMotor->LOOP_CTRL._V_Q32U_Open_cnt = 0U;
                
                PID_Pos_Init_F(&pMotor->SRAD_CTRL.PID_SRAD, pMotor->CURRENT_CTRL._I_F_IqRef);
                Ramp_Init_F(&pMotor->SRAD_CTRL.Ramp_SRAD, pMotor->SRAD_CTRL._I_F_SRAD);
                
                pMotor->IF_CTRL.Ramp_AngleERR.F_Init = pMotor->IF_CTRL._O_F_Angle - pMotor->Motor_EST.TG_Triangle.F_Angle;
                pMotor->Motor_Loop_Mode = MOTOR_CLOSELOOP;
            }
        }
        else
        {
            pMotor->LOOP_CTRL._V_Q32U_Open_cnt = 0U;
        }
    }
    
#elif(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_VF)
    pMotor->SRAD_CTRL._I_F_SRAD = pMotor->Motor_EST.FL_SRAD.F_Filter_out;
    
    MotorFoc_VF_OPEN_F(&pMotor->VF_CTRL);
    
    if(++pMotor->LOOP_CTRL._V_Q32U_Open_min_cnt >= pMotor->LOOP_CTRL._P_Q32U_Open_Min_Time)
    {
        if(pMotor->SRAD_CTRL._I_F_SRAD >= pMotor->LOOP_CTRL._P_F_Open_Switch_SRAD)
        {
            if(++pMotor->LOOP_CTRL._V_Q32U_Open_cnt >= pMotor->LOOP_CTRL._P_Q32U_Open_Switch_Time)
            {
                pMotor->LOOP_CTRL._V_Q32U_Open_min_cnt = 0U;
                pMotor->LOOP_CTRL._V_Q32U_Open_cnt = 0U;
                
                PID_Pos_Init_F(&pMotor->SRAD_CTRL.PID_SRAD, pMotor->CURRENT_CTRL._I_F_IqRef);
                Ramp_Init_F(&pMotor->SRAD_CTRL.Ramp_SRAD, pMotor->SRAD_CTRL._I_F_SRAD);
                
                pMotor->IF_CTRL.Ramp_AngleERR.F_Init = pMotor->IF_CTRL._O_F_Angle - pMotor->Motor_EST.TG_Triangle.F_Angle;
                pMotor->Motor_Loop_Mode = MOTOR_CLOSELOOP;
            }
        }
        else
        {
            pMotor->LOOP_CTRL._V_Q32U_Open_cnt = 0U;
        }
    }
    
#elif(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_HFI)
    pMotor->SRAD_CTRL._I_F_SRAD = pMotor->Motor_EST.FL_SRAD.F_Filter_out;
    
    Est_HFI_State_F(&pMotor->HFI_CTRL);
    if(pMotor->HFI_CTRL._V_Q32U_Flag_En ==1U)
    {
        pMotor->SRAD_CTRL._I_F_SRAD_Target = pMotor->HFI_CTRL._P_F_Target;
        MotorFoc_SRAD_Loop_F(&pMotor->SRAD_CTRL);
        pMotor->CURRENT_CTRL._I_F_IdRef = pMotor->SRAD_CTRL._O_F_IdRef;
        pMotor->CURRENT_CTRL._I_F_IqRef = pMotor->SRAD_CTRL._O_F_IqRef;
    }
    else
    {
        pMotor->CURRENT_CTRL._I_F_IdRef = 0.0f;
        pMotor->CURRENT_CTRL._I_F_IqRef = 0.0f;
    }
    
#elif(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_FLUX)
    pMotor->SRAD_CTRL._I_F_SRAD = pMotor->FLUX_CTRL.FL_SRAD.F_Filter_out;
    MotorFoc_IF_OPEN_F(&pMotor->IF_CTRL);
    pMotor->CURRENT_CTRL._I_F_IdRef = 0.0f;
    pMotor->CURRENT_CTRL._I_F_IqRef = pMotor->IF_CTRL.Ramp_Iq.F_Output;
    
    if(pMotor->SRAD_CTRL._I_F_SRAD >= pMotor->LOOP_CTRL._P_F_Open_Switch_SRAD)
    {
        if(++pMotor->LOOP_CTRL._V_Q32U_Open_cnt >= pMotor->LOOP_CTRL._P_Q32U_Open_Switch_Time)
        {
            pMotor->LOOP_CTRL._V_Q32U_Open_cnt = 0U;
            
            pMotor->Motor_Loop_Mode = MOTOR_CLOSELOOP;
        }
    }
    else
    {
        pMotor->LOOP_CTRL._V_Q32U_Open_cnt = 0U;
    }
    
#endif
    
}

/**********************************************************************************************
Function: MotorTask_CloseLoop_Flow
Description: 电机控制闭环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_CloseLoop_Flow(ST_MOTOR_TASK* pMotor)
{
    pMotor->SRAD_CTRL._I_F_SRAD = pMotor->Motor_EST.FL_SRAD.F_Filter_out;
    pMotor->FLUX_CTRL.Est_State_Flag = 1U;
    MotorFoc_SRAD_Loop_F(&pMotor->SRAD_CTRL);
    pMotor->CURRENT_CTRL._I_F_IdRef = pMotor->SRAD_CTRL._O_F_IdRef;
    pMotor->CURRENT_CTRL._I_F_IqRef = pMotor->SRAD_CTRL._O_F_IqRef;
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
        Motor_Loop_Flow_Function[pMotor->Motor_Loop_Mode](pMotor);
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
        pMotor->LOOP_CTRL._V_Q32U_Align_cnt = 0U;
        pMotor->LOOP_CTRL._V_Q32U_Open_cnt = 0U;
        pMotor->LOOP_CTRL._V_Q32U_Open_min_cnt = 0U;
        pMotor->LOOP_CTRL._V_Q32U_Close_cnt = 0U;
		
        MotorFoc_IF_Init_F(&pMotor->IF_CTRL);
        MotorFoc_VF_Init_F(&pMotor->VF_CTRL);
        
        MotorFoc_SVPWM_Init_F(&pMotor->SVPWM_CTRL);
        MotorFoc_SRAD_Init_F(&pMotor->SRAD_CTRL);
        MotorFoc_Current_Init_F(&pMotor->CURRENT_CTRL);
        
        Est_HFI_Init_F(&pMotor->HFI_CTRL);
        Est_Flux_Init_F(&pMotor->FLUX_CTRL);
        Est_SMO_Init_F(&pMotor->SMO_CTRL);
        
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
//        pMotor->Motor_Flow = MOTOR_STATE_BOOT;
        pMotor->Motor_Flow = MOTOR_STATE_RUN;
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
Function: MotorTask_Current_AlignLoop_Flow
Description: 电机控制强拖定位
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Current_AlignLoop_Flow(ST_MOTOR_TASK* pMotor)
{
    Math_SinCos_F(&pMotor->SVPWM_CTRL.TG_Triangle);
    
    MotorFoc_Park_F(&pMotor->SVPWM_CTRL);
    pMotor->CURRENT_CTRL._I_F_Id = pMotor->SVPWM_CTRL._O_F_Id;
    pMotor->CURRENT_CTRL._I_F_Iq = pMotor->SVPWM_CTRL._O_F_Iq;
    MotorFoc_Current_Loop_F(&pMotor->CURRENT_CTRL);
    
    pMotor->SVPWM_CTRL._I_F_Ud = pMotor->CURRENT_CTRL._O_F_Ud;
    pMotor->SVPWM_CTRL._I_F_Uq = pMotor->CURRENT_CTRL._O_F_Uq;
}

/**********************************************************************************************
Function: MotorTask_Current_OpenLoop_Flow
Description: 电机控制开环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Current_OpenLoop_Flow(ST_MOTOR_TASK* pMotor)
{
    
#if(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_IF)
    MotorFoc_IF_CURRENT_F(&pMotor->IF_CTRL);
    pMotor->SVPWM_CTRL.TG_Triangle.F_Angle = pMotor->IF_CTRL._O_F_Angle;
    Math_SinCos_F(&pMotor->SVPWM_CTRL.TG_Triangle);
    
    MotorFoc_Park_F(&pMotor->SVPWM_CTRL);
    pMotor->CURRENT_CTRL._I_F_Id = pMotor->SVPWM_CTRL._O_F_Id;
    pMotor->CURRENT_CTRL._I_F_Iq = pMotor->SVPWM_CTRL._O_F_Iq;
    MotorFoc_Current_Loop_F(&pMotor->CURRENT_CTRL);
    
    pMotor->SVPWM_CTRL._I_F_Ud = pMotor->CURRENT_CTRL._O_F_Ud;
    pMotor->SVPWM_CTRL._I_F_Uq = pMotor->CURRENT_CTRL._O_F_Uq;
    
#elif(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_VF)
    MotorFoc_VF_CURRENT_F(&pMotor->VF_CTRL);
    pMotor->SVPWM_CTRL.TG_Triangle.F_Angle = pMotor->VF_CTRL._O_F_Angle;
    Math_SinCos_F(&pMotor->SVPWM_CTRL.TG_Triangle);
    
    pMotor->SVPWM_CTRL._I_F_Ud = 0;
    pMotor->SVPWM_CTRL._I_F_Uq = pMotor->VF_CTRL.Ramp_Vq.F_Output;
    
#elif(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_HFI)
    pMotor->HFI_CTRL._I_F_Ialfa = pMotor->SVPWM_CTRL._O_F_Ialfa;
    pMotor->HFI_CTRL._I_F_Ibeta = pMotor->SVPWM_CTRL._O_F_Ibeta;
    Est_HFI_F(&pMotor->HFI_CTRL);
    
    pMotor->SVPWM_CTRL.TG_Triangle.F_Angle = pMotor->HFI_CTRL.TG_Triangle.F_Angle;
    MATH_ANGLE_MOD_F(pMotor->SVPWM_CTRL.TG_Triangle.F_Angle);
    Math_SinCos_F(&pMotor->SVPWM_CTRL.TG_Triangle);
    pMotor->SVPWM_CTRL._O_F_Ialfa = pMotor->HFI_CTRL._O_F_Ialfa;
    pMotor->SVPWM_CTRL._O_F_Ibeta = pMotor->HFI_CTRL._O_F_Ibeta;
    
    MotorFoc_Park_F(&pMotor->SVPWM_CTRL);
    pMotor->CURRENT_CTRL._I_F_Id = pMotor->SVPWM_CTRL._O_F_Id;
    pMotor->CURRENT_CTRL._I_F_Iq = pMotor->SVPWM_CTRL._O_F_Iq;
    MotorFoc_HFI_Current_Loop_F(&pMotor->CURRENT_CTRL, pMotor->HFI_CTRL._P_F_Udq_Coeff);
    pMotor->HFI_CTRL._I_F_Id = pMotor->SVPWM_CTRL._O_F_Id;
        
    pMotor->SVPWM_CTRL._I_F_Ud = pMotor->CURRENT_CTRL._O_F_Ud;
    pMotor->SVPWM_CTRL._I_F_Uq = pMotor->CURRENT_CTRL._O_F_Uq;
    
    MotorFoc_Ipark_F(&pMotor->SVPWM_CTRL);
    
    pMotor->SVPWM_CTRL._I_F_Ud = pMotor->HFI_CTRL._V_F_NS_Ud_Ref_Sign*pMotor->CURRENT_CTRL._O_F_Ud + pMotor->HFI_CTRL._O_F_Ud_HFI;
    pMotor->SVPWM_CTRL._I_F_Uq = pMotor->CURRENT_CTRL._O_F_Uq;
    
#elif(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_FLUX)
    pMotor->SVPWM_CTRL.TG_Triangle = pMotor->Motor_EST.TG_Triangle;
    
    MotorFoc_Park_F(&pMotor->SVPWM_CTRL);
    pMotor->CURRENT_CTRL._I_F_Id = pMotor->SVPWM_CTRL._O_F_Id;
    pMotor->CURRENT_CTRL._I_F_Iq = pMotor->SVPWM_CTRL._O_F_Iq;
    MotorFoc_Current_Loop_F(&pMotor->CURRENT_CTRL);
    
    pMotor->SVPWM_CTRL._I_F_Ud = pMotor->CURRENT_CTRL._O_F_Ud;
    pMotor->SVPWM_CTRL._I_F_Uq = pMotor->CURRENT_CTRL._O_F_Uq;
    
#endif
    
}

/**********************************************************************************************
Function: MotorTask_Current_CloseLoop_Flow
Description: 电机控制闭环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Current_CloseLoop_Flow(ST_MOTOR_TASK* pMotor)
{
#if(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_IF)
    MotorFoc_IF_CLOSE_F(&pMotor->IF_CTRL);
    pMotor->SVPWM_CTRL.TG_Triangle.F_Angle = pMotor->Motor_EST.TG_Triangle.F_Angle + pMotor->IF_CTRL.Ramp_AngleERR.F_Output;
    
#elif(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_VF)
    MotorFoc_VF_CLOSE_F(&pMotor->VF_CTRL);
    pMotor->SVPWM_CTRL.TG_Triangle.F_Angle = pMotor->Motor_EST.TG_Triangle.F_Angle + pMotor->VF_CTRL.Ramp_AngleERR.F_Output;
    
#else
    pMotor->SVPWM_CTRL.TG_Triangle = pMotor->Motor_EST.TG_Triangle;
    
#endif
    
    MATH_ANGLE_MOD_F(pMotor->SVPWM_CTRL.TG_Triangle.F_Angle);
    Math_SinCos_F(&pMotor->SVPWM_CTRL.TG_Triangle);
    
    MotorFoc_Park_F(&pMotor->SVPWM_CTRL);
    pMotor->CURRENT_CTRL._I_F_Id = pMotor->SVPWM_CTRL._O_F_Id;
    pMotor->CURRENT_CTRL._I_F_Iq = pMotor->SVPWM_CTRL._O_F_Iq;
    MotorFoc_Current_Loop_F(&pMotor->CURRENT_CTRL);
    
    pMotor->SVPWM_CTRL._I_F_Ud = pMotor->CURRENT_CTRL._O_F_Ud;
    pMotor->SVPWM_CTRL._I_F_Uq = pMotor->CURRENT_CTRL._O_F_Uq;
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
        MotorFoc_Clark_F(&pMotor->SVPWM_CTRL);
        
        if(pMotor->Motor_Loop_Mode == MOTOR_ALIGNLOOP)
        {
            MotorTask_Current_AlignLoop_Flow(pMotor);
        }
        else if(pMotor->Motor_Loop_Mode == MOTOR_OPENLOOP)
        {
            MotorTask_Current_OpenLoop_Flow(pMotor);
        }
        
#if(MOTOR_EST_MODE == MOTOR_EST_FLUX)
        pMotor->FLUX_CTRL._I_F_Ialfa = pMotor->SVPWM_CTRL._O_F_Ialfa;
        pMotor->FLUX_CTRL._I_F_Ibeta = pMotor->SVPWM_CTRL._O_F_Ibeta;
        pMotor->FLUX_CTRL._I_F_Ualfa = pMotor->SVPWM_CTRL._O_F_Ualfa;
        pMotor->FLUX_CTRL._I_F_Ubeta = pMotor->SVPWM_CTRL._O_F_Ubeta;
        Est_Flux_F(&pMotor->FLUX_CTRL);
        
#elif(MOTOR_EST_MODE == MOTOR_EST_SMO)
        pMotor->SMO_CTRL._I_F_Ialfa = pMotor->SVPWM_CTRL._O_F_Ialfa;
        pMotor->SMO_CTRL._I_F_Ibeta = pMotor->SVPWM_CTRL._O_F_Ibeta;
        pMotor->SMO_CTRL._I_F_Ualfa = pMotor->SVPWM_CTRL._O_F_Ualfa;
        pMotor->SMO_CTRL._I_F_Ubeta = pMotor->SVPWM_CTRL._O_F_Ubeta;
        Est_SMO_F(&pMotor->SMO_CTRL);
        
#endif
        
        if(pMotor->Motor_Loop_Mode == MOTOR_CLOSELOOP)
        {
            MotorTask_Current_CloseLoop_Flow(pMotor);
        }
        
        MotorFoc_Ipark_F(&pMotor->SVPWM_CTRL);
        
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
//    MH_HPWM_LPWM_Close();
//    pMotor->Q32U_MOS_Error_cnt++;
    pMotor->Motor_Error_Flag.bit.current_short = 1U;
}
