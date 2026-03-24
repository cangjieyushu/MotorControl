/**************************************************************************************************
*     File Name :                        MCFOC_TASK_T.c
*     Library/Module Name :              MCFOC_T
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机子任务源文件
**************************************************************************************************/

#include "MCFOC_TASK_T.h"

#ifdef MCFOC_CJYS_3
/**********************************************************************************************
Function: MotorTask_Init_Flow_ADC_Read_Three_T
Description: 电机控制初始状态ADC读取
Input: 无
Output: 无
Input_Output: 偏置检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MotorTask_Init_Flow_ADC_Read_Three_T(ST_MCFOC_OFFSET_T* pOFFSET)
{
    Q32U_ adc_data1,adc_data2,adc_data3 = 0;
    
    MH_ADC_Data_Read_Three(&adc_data1, &adc_data2, &adc_data3);
    
    pOFFSET->_I_Q12I_Ia_Data = adc_data1;
    pOFFSET->_I_Q12I_Ib_Data = adc_data2;
    pOFFSET->_I_Q12I_Ic_Data = adc_data3;
}

/**********************************************************************************************
Function: MotorTask_Run_Flow_ADC_Read_Three_T
Description: 电机控制运行状态ADC读取
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MotorTask_Run_Flow_ADC_Read_Three_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    Q32U_ adc_data1,adc_data2,adc_data3 = 0;
    
    MH_ADC_Data_Read_Three(&adc_data1, &adc_data2, &adc_data3);
    
    pPMSMe->_I_Q12I_Ia_Data = adc_data1;
    pPMSMe->_I_Q12I_Ib_Data = adc_data2;
    pPMSMe->_I_Q12I_Ic_Data = adc_data3;
    
    pPMSMe->_V_Q14I_Ia = 4*(pPMSMe->_I_Q12I_Ia_Offset - pPMSMe->_I_Q12I_Ia_Data);
    pPMSMe->_V_Q14I_Ib = 4*(pPMSMe->_I_Q12I_Ib_Offset - pPMSMe->_I_Q12I_Ib_Data);
    pPMSMe->_V_Q14I_Ic = 4*(pPMSMe->_I_Q12I_Ic_Offset - pPMSMe->_I_Q12I_Ic_Data);
    
    MCFOC_ThreeShunt_Current_Cal_T(pSVPWM, pPMSMe);
    MCFOC_Duty_Resolution_T(pSVPWM, pPMSMe);
}

/**********************************************************************************************
Function: MotorTask_Run_Flow_PWM_Set_Three_T
Description: 电机控制运行状态PWM设置
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MotorTask_Run_Flow_PWM_Set_Three_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa)
{    
    MCFOC_Ipark_T(pPMSMe);
    MCFOC_SVPWM_ThreeShunt_T(pSVPWM, pPMSMe);
    MCFOC_Iclark_T(pPMSMe);
    MCFOC_DeadTime_COMP_T(pSVPWM, pPMSMe);
    
    MH_PWM_Duty_Set_Three(Q32I_RHT_15(pSVPWM->_P_Q32U_PWM_All_Count*pPMSMa->_O_Q14I_PWM_Period_Coeff),
                          Q32I_RHT_15(pSVPWM->_P_Q32U_PWM_All_Count*(16384 - pSVPWM->_O_Q14U_Dutya)),
                          Q32I_RHT_15(pSVPWM->_P_Q32U_PWM_All_Count*(16384 - pSVPWM->_O_Q14U_Dutyb)),
                          Q32I_RHT_15(pSVPWM->_P_Q32U_PWM_All_Count*(16384 - pSVPWM->_O_Q14U_Dutyc)));
}
#endif

#ifdef MCFOC_CJYS_1
/**********************************************************************************************
Function: MotorTask_Init_Flow_ADC_Read_One_T
Description: 电机控制初始状态ADC读取
Input: 无
Output: 无
Input_Output: 偏置检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MotorTask_Init_Flow_ADC_Read_One_T(ST_MCFOC_OFFSET_T* pOFFSET)
{
    Q32U_ adc_data1,adc_data2 = 0;
    
    MH_ADC_Data_Read_One(&adc_data1, &adc_data2);

    pOFFSET->_I_Q12I_Ishunt_Data = (Q32I_)adc_data1;
}

/**********************************************************************************************
Function: MotorTask_Run_Flow_ADC_Read_One_T
Description: 电机控制运行状态ADC读取
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MotorTask_Run_Flow_ADC_Read_One_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    Q32U_ adc_data1,adc_data2 = 0;
    
    MH_ADC_Data_Read_One(&adc_data1, &adc_data2);
    pPMSMe->_I_Q12I_Ishunt_1_Data = (Q32I_)adc_data1;
    pPMSMe->_I_Q12I_Ishunt_2_Data = (Q32I_)adc_data2;
    
    pPMSMe->_I_Q14I_Ishunt[0] =   4*(pPMSMe->_I_Q12I_Ishunt_1_Data - pPMSMe->_I_Q12I_Ishunt_Offset);
    pPMSMe->_I_Q14I_Ishunt[2] = - 4*(pPMSMe->_I_Q12I_Ishunt_2_Data - pPMSMe->_I_Q12I_Ishunt_Offset);
    pPMSMe->_I_Q14I_Ishunt[1] = - pPMSMe->_I_Q14I_Ishunt[0] - pPMSMe->_I_Q14I_Ishunt[2];
    
    MCFOC_OneShunt_Current_Cal_T(pSVPWM, pPMSMe);
    MCFOC_Duty_Resolution_T(pSVPWM, pPMSMe);
}

/**********************************************************************************************
Function: MotorTask_Run_Flow_PWM_Set_One_T
Description: 电机控制运行状态PWM设置
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MotorTask_Run_Flow_PWM_Set_One_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa)
{
    Q32I_ pwm_tmp1,pwm_tmp2,pwm_tmp3,pwm_tmp4,pwm_tmp5,pwm_tmp6,adc_tmp1,adc_tmp2 = 0;
    
    MCFOC_Ipark_T(pPMSMe);
    MCFOC_SVPWM_OneShunt_T(pSVPWM, pPMSMe);
    MCFOC_Iclark_T(pPMSMe);
    
    pwm_tmp1 = Q32I_RHT_14(pSVPWM->_P_Q32U_PWM_All_Count*pSVPWM->_O_Q14U_TaUp);
    pwm_tmp2 = Q32I_RHT_14(pSVPWM->_P_Q32U_PWM_All_Count*pSVPWM->_O_Q14U_TaDn);
    pwm_tmp3 = Q32I_RHT_14(pSVPWM->_P_Q32U_PWM_All_Count*pSVPWM->_O_Q14U_TbUp);
    pwm_tmp4 = Q32I_RHT_14(pSVPWM->_P_Q32U_PWM_All_Count*pSVPWM->_O_Q14U_TbDn);
    pwm_tmp5 = Q32I_RHT_14(pSVPWM->_P_Q32U_PWM_All_Count*pSVPWM->_O_Q14U_TcUp);
    pwm_tmp6 = Q32I_RHT_14(pSVPWM->_P_Q32U_PWM_All_Count*pSVPWM->_O_Q14U_TcDn);
    adc_tmp1 = Q32I_RHT_14(pSVPWM->_P_Q32U_PWM_All_Count*pSVPWM->_O_Q14U_ADCTrigTime1);
    adc_tmp2 = Q32I_RHT_14(pSVPWM->_P_Q32U_PWM_All_Count*pSVPWM->_O_Q14U_ADCTrigTime2);
    
    MH_PWM_Duty_Set_One((Q32U_)pwm_tmp1,(Q32U_)pwm_tmp2,(Q32U_)pwm_tmp3,(Q32U_)pwm_tmp4,(Q32U_)pwm_tmp5,(Q32U_)pwm_tmp6);
    MH_ADC_TrigTime_Set((Q32U_)adc_tmp1,(Q32U_)adc_tmp2);
}
#endif

void MotorTask_Pre_Flow_T(ST_MOTOR_TASK* pMotor);
void MotorTask_Init_Flow_T(ST_MOTOR_TASK* pMotor);
void MotorTask_Idle_Flow_T(ST_MOTOR_TASK* pMotor);
void MotorTask_Boot_Flow_T(ST_MOTOR_TASK* pMotor);
void MotorTask_Position_Flow_T(ST_MOTOR_TASK* pMotor);
void MotorTask_Run_Flow_T(ST_MOTOR_TASK* pMotor);
void MotorTask_Brake_Flow_T(ST_MOTOR_TASK* pMotor);

pMOTOR_FUN Motor_Flow_Function_T[MOTOR_STATE_BRAKE+1] =
{
    MotorTask_Pre_Flow_T,
    MotorTask_Init_Flow_T,
    MotorTask_Idle_Flow_T,
    MotorTask_Boot_Flow_T,
    MotorTask_Position_Flow_T,
    MotorTask_Run_Flow_T,
    MotorTask_Brake_Flow_T
};


/**********************************************************************************************
Function: MotorTask_Speed_Flow_T
Description: 电机控制速度环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Speed_Flow_T(ST_MOTOR_TASK* pMotor)
{
    MCFOC_PMSM_Para_Adapt_T(&pMotor->PMSM_FILTER_CTRL, &pMotor->PMSM_ELEC_CTRL, &pMotor->PMSM_PARA_CTRL);
    MCFOC_EST_EMF_Adapt_T(&pMotor->EMF_CTRL, &pMotor->PMSM_PARA_CTRL);
    MCFOC_EST_SMO_Adapt_T(&pMotor->SMO_CTRL, &pMotor->PMSM_ELEC_CTRL, &pMotor->PMSM_PARA_CTRL);
    MCFOC_EST_FLUX_Adapt_T(&pMotor->FLUX_CTRL, &pMotor->PMSM_ELEC_CTRL, &pMotor->PMSM_PARA_CTRL);
    MCFOC_Five_Cal_T(&pMotor->SVPWM_CTRL, &pMotor->PMSM_ELEC_CTRL);

    pMotor->MC_ERR._I_Q14U_IsRef_pu = 
    (MATH_SQADD_T(pMotor->CURRENT_CTRL._I_Q14I_IdRef, pMotor->CURRENT_CTRL._I_Q14I_IqRef));
    pMotor->MC_ERR._I_Q14U_Iphase_A_Max_pu = pMotor->PMSM_FILTER_CTRL.Max_Ia.Q14I_MAX_Out;
    pMotor->MC_ERR._I_Q14U_Iphase_B_Max_pu = pMotor->PMSM_FILTER_CTRL.Max_Ib.Q14I_MAX_Out;
    pMotor->MC_ERR._I_Q14U_Iphase_C_Max_pu = pMotor->PMSM_FILTER_CTRL.Max_Ic.Q14I_MAX_Out;
    pMotor->MC_ERR._I_Q14U_Es_pu = pMotor->PMSM_FILTER_CTRL.Mean_Es.Q14I_MEAN_Out;;

    pMotor->MC_ERR._I_Q14U_Vbus_pu = pMotor->PMSM_ELEC_CTRL._O_Q14I_Vbus;
    pMotor->MC_ERR._I_Q14U_Iphase_Max_pu = MATH_MAX_T(pMotor->MC_ERR._I_Q14U_Iphase_A_Max_pu, 
    MATH_MAX_T(pMotor->MC_ERR._I_Q14U_Iphase_B_Max_pu, pMotor->MC_ERR._I_Q14U_Iphase_C_Max_pu));
    pMotor->MC_ERR._I_Q14U_Temp_ADC = BSP_ADC_DATA_READ_TEMP;
    pMotor->MC_ERR._I_Q14U_Speed_pu = pMotor->PMSM_ELEC_CTRL._O_Q14I_Freq;
    pMotor->MC_ERR._I_Q14U_Ibus_pu = pMotor->PMSM_ELEC_CTRL._O_Q14I_Ibus_10ms;
    MC_Error_Speed_Flow(&pMotor->MC_ERR, ((pMotor->Motor_Flow >= MOTOR_STATE_BOOT)&&(pMotor->Motor_Flow <= MOTOR_STATE_BRAKE)));
    MC_Error_Speed_Flow_FOC(&pMotor->MC_ERR, ((pMotor->Motor_Flow >= MOTOR_STATE_BOOT)&&(pMotor->Motor_Flow <= MOTOR_STATE_BRAKE)));
    
//FOC转速环任务
    if(pMotor->Motor_Flow == MOTOR_STATE_RUN)
    {
        if(pMotor->Motor_Loop_Mode == MOTOR_ALIGNLOOP)
        {
            MCFOC_ALIGN_SpeedLoop_T(&pMotor->ALIGN_CTRL);
            pMotor->CURRENT_CTRL._I_Q14I_IdRef = pMotor->ALIGN_CTRL._O_Q14I_Align_IdRef;
            pMotor->CURRENT_CTRL._I_Q14I_IqRef = 0;
    
            if(pMotor->ALIGN_CTRL._O_Q32U_Stand_Flag == 1U)
            {
                pMotor->Motor_Loop_Mode = MOTOR_OPENLOOP;
            }
        }
        else if(pMotor->Motor_Loop_Mode == MOTOR_OPENLOOP)
        {
            MCFOC_IF_SpeedLoop_T(&pMotor->IF_CTRL, &pMotor->PMSM_ELEC_CTRL);
            pMotor->CURRENT_CTRL._I_Q14I_IdRef = pMotor->IF_CTRL._O_Q14I_IF_IdRef;
            pMotor->CURRENT_CTRL._I_Q14I_IqRef = pMotor->IF_CTRL._O_Q14I_IF_IqRef;
    
            if(pMotor->IF_CTRL._O_Q32U_Switch_Flag == 1U)
            {
                Ramp_Init_T(&pMotor->FREQ_CTRL.Ramp_FREQ, pMotor->IF_CTRL.Ramp_IF_FREQ.Q14I_Output);
                PID_Sat_Init_T(&pMotor->FREQ_CTRL.PID_FREQ, pMotor->IF_CTRL._O_Q14I_IF_IqRef);
                pMotor->Motor_Loop_Mode = MOTOR_CLOSELOOP;
            }
        }
        else if(pMotor->Motor_Loop_Mode == MOTOR_CLOSELOOP)
        {
            MCFOC_SpeedLoop_T(&pMotor->FREQ_CTRL, &pMotor->PMSM_ELEC_CTRL, &pMotor->PMSM_PARA_CTRL);
            pMotor->CURRENT_CTRL._I_Q14I_IdRef = pMotor->FREQ_CTRL._O_Q14I_FREQ_IdRef;
            pMotor->CURRENT_CTRL._I_Q14I_IqRef = pMotor->FREQ_CTRL._O_Q14I_FREQ_IqRef;
        }
    }
    else if(pMotor->Motor_Flow == MOTOR_STATE_BRAKE)
    {
        
    }
}

/**********************************************************************************************
Function: MotorTask_Pre_Flow_T
Description: 电机控制预备状态
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Pre_Flow_T(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
    {
		MCFOC_Offset_Check_Init_T(&pMotor->MCFOC_OFFSET);
        
        MCFOC_PMSM_Para_Init_T(&pMotor->PMSM_ELEC_CTRL);
        MCFOC_ALIGN_Init_T(&pMotor->ALIGN_CTRL);
        MCFOC_IF_Init_T(&pMotor->IF_CTRL);
        MCFOC_SpeedLoop_Init_T(&pMotor->FREQ_CTRL);
        MCFOC_CurrentLoop_Init_T(&pMotor->CURRENT_CTRL);
        MCFOC_SVPWM_Init_T(&pMotor->SVPWM_CTRL);
        
        MCFOC_EST_EMF_Init_T(&pMotor->EMF_CTRL);
        MCFOC_EST_SMO_Init_T(&pMotor->SMO_CTRL);
        MCFOC_EST_FLUX_Init_T(&pMotor->FLUX_CTRL);
        
#if(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_IF)
        pMotor->Motor_Loop_Mode = MOTOR_ALIGNLOOP;
#elif(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_FLUX)
        pMotor->Motor_Loop_Mode = MOTOR_CLOSELOOP;
#endif

        pMotor->Motor_Flow = MOTOR_STATE_INIT;
    }
    else
    {
        pMotor->Motor_EST_Freq = 0;
        pMotor->PMSM_ELEC_CTRL._I_Q14I_Ibus = 0;
        pMotor->PMSM_ELEC_CTRL._V_Q14I_Id_Real = 0;
        pMotor->PMSM_ELEC_CTRL._V_Q14I_Iq_Real = 0;
        pMotor->PMSM_ELEC_CTRL._V_Q14I_Ud_Real = 0;
        pMotor->PMSM_ELEC_CTRL._V_Q14I_Uq_Real = 0;
        pMotor->EMF_CTRL._O_Q14I_EMF_Ealfa = 0;
        pMotor->EMF_CTRL._O_Q14I_EMF_Ebeta = 0;
        
        MH_PWM_Output_Disable();
    }
}

/**********************************************************************************************
Function: MotorTask_Init_Flow_T
Description: 电机控制初始状态
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Init_Flow_T(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
    {
        MotorTask_Init_Flow_ADC_Read(&pMotor->MCFOC_OFFSET);
        
        switch(MCFOC_Offset_Check(&pMotor->MCFOC_OFFSET, &pMotor->PMSM_ELEC_CTRL))
        {
            case ING:
            {
                break;
            }
            case SUCS:
            {
                pMotor->Motor_Flow = MOTOR_STATE_IDLE;
                break;
            }
            case FAIL:
            {
                pMotor->MC_ERR.Motor_Error_Flag.bit.current_offset = 1U;
                pMotor->Motor_Flow = MOTOR_STATE_PRE;
                break;
            }
            default:break;
        }
    }
    else
    {
        MH_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**********************************************************************************************
Function: MotorTask_Idle_Flow_T
Description: 电机控制静止状态
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Idle_Flow_T(ST_MOTOR_TASK* pMotor)
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
Function: MotorTask_Boot_Flow_T
Description: 电机控制自举状态
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Boot_Flow_T(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
    {
        pMotor->Motor_Flow = MOTOR_STATE_POSITION;
    }
    else
    {
        MH_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**********************************************************************************************
Function: MotorTask_Position_Flow_T
Description: 电机控制定位状态
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Position_Flow_T(ST_MOTOR_TASK* pMotor)
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
Function: MotorTask_Run_Flow_T
Description: 电机控制运行状态
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Run_Flow_T(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
    {
        MotorTask_Run_Flow_ADC_Read(&pMotor->SVPWM_CTRL, &pMotor->PMSM_ELEC_CTRL);
        MCFOC_Clark_T(&pMotor->PMSM_ELEC_CTRL);

        MCFOC_EST_EMF_T(&pMotor->EMF_CTRL, &pMotor->PMSM_ELEC_CTRL);
        Motor_EST_FUNCTION;
        
        if(pMotor->Motor_Loop_Mode == MOTOR_ALIGNLOOP)
        {
            MCFOC_ALIGN_CurrentLoop_T(&pMotor->ALIGN_CTRL);
            
            pMotor->PMSM_ELEC_CTRL.TG_Triangle_Est.Q14U_Angle = pMotor->ALIGN_CTRL._O_Q14I_Align_Angle;
            Math_SinCos_T(&pMotor->PMSM_ELEC_CTRL.TG_Triangle_Est);
        }
        else if(pMotor->Motor_Loop_Mode == MOTOR_OPENLOOP)
        {
            pMotor->IF_CTRL._I_Q14I_IF_Est_Angle = pMotor->Motor_EST_TG_Triangle.Q14U_Angle + pMotor->Motor_EST_TG_Triangle_Comp.Q14U_Angle;
            MATH_ANGLE_MOD_T(pMotor->IF_CTRL._I_Q14I_IF_Est_Angle);
            MCFOC_IF_CurrentLoop_T(&pMotor->IF_CTRL, &pMotor->PMSM_ELEC_CTRL, &pMotor->PMSM_PARA_CTRL);
            
            pMotor->PMSM_ELEC_CTRL.TG_Triangle_Est.Q14U_Angle = pMotor->IF_CTRL._O_Q14I_IF_Angle;
            Math_SinCos_T(&pMotor->PMSM_ELEC_CTRL.TG_Triangle_Est);

        }
        else if(pMotor->Motor_Loop_Mode == MOTOR_CLOSELOOP)
        {
            pMotor->PMSM_ELEC_CTRL.TG_Triangle_Est = pMotor->Motor_EST_TG_Triangle;
            pMotor->PMSM_ELEC_CTRL.TG_Triangle_Comp = pMotor->Motor_EST_TG_Triangle_Comp;
        }
        
        MCFOC_Park_T(&pMotor->PMSM_ELEC_CTRL);
        MCFOC_CurrentLoop_T(&pMotor->CURRENT_CTRL, &pMotor->PMSM_ELEC_CTRL);
        
        MotorTask_Run_Flow_PWM_Set(&pMotor->SVPWM_CTRL, &pMotor->PMSM_ELEC_CTRL, &pMotor->PMSM_PARA_CTRL);

        MH_PWM_Output_Enable();
        
    }
    else
    {
        MH_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_BRAKE;
    }
}

/**********************************************************************************************
Function: MotorTask_Brake_Flow_T
Description: 电机控制刹车状态
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Brake_Flow_T(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_State_Flag.bit.motor_run_flag == 1U)
    {
        MH_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
    else
    {
        
    }
}

/**********************************************************************************************
Function: MotorTask_Current_Flow_T
Description: 电机控制电流环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Current_Flow_T(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->MC_ERR.Motor_Error_Flag.all != 0U)
    {
        pMotor->Motor_State_Flag.bit.motor_run_flag = 0U;
    }
    
    Motor_Flow_Function_T[pMotor->Motor_Flow](pMotor);

    pMotor->PMSM_FILTER_CTRL.Mean_Freq.Q14I_MEAN_In = pMotor->Motor_EST_Freq;
    pMotor->PMSM_FILTER_CTRL.Mean_Vbus.Q14I_MEAN_In = 4*BSP_ADC_DATA_READ_VBUS;
    pMotor->PMSM_FILTER_CTRL.Mean_Ibus.Q14I_MEAN_In = pMotor->PMSM_ELEC_CTRL._I_Q14I_Ibus;
    pMotor->PMSM_FILTER_CTRL.Mean_Id.Q14I_MEAN_In = pMotor->PMSM_ELEC_CTRL._V_Q14I_Id_Real;
    pMotor->PMSM_FILTER_CTRL.Mean_Iq.Q14I_MEAN_In = pMotor->PMSM_ELEC_CTRL._V_Q14I_Iq_Real;
    pMotor->PMSM_FILTER_CTRL.Mean_Ud.Q14I_MEAN_In = pMotor->PMSM_ELEC_CTRL._V_Q14I_Ud_Real;
    pMotor->PMSM_FILTER_CTRL.Mean_Uq.Q14I_MEAN_In = pMotor->PMSM_ELEC_CTRL._V_Q14I_Uq_Real;
    pMotor->PMSM_FILTER_CTRL.Mean_Es.Q14I_MEAN_In = MATH_SQADD_T(pMotor->EMF_CTRL._O_Q14I_EMF_Ealfa, pMotor->EMF_CTRL._O_Q14I_EMF_Ebeta);

    MEAN_Cal_T(&pMotor->PMSM_FILTER_CTRL.Mean_Freq);
    MEAN_Cal_T(&pMotor->PMSM_FILTER_CTRL.Mean_Vbus);
    MEAN_Cal_T(&pMotor->PMSM_FILTER_CTRL.Mean_Ibus);
    MEAN_Cal_T(&pMotor->PMSM_FILTER_CTRL.Mean_Id);
    MEAN_Cal_T(&pMotor->PMSM_FILTER_CTRL.Mean_Iq);
    MEAN_Cal_T(&pMotor->PMSM_FILTER_CTRL.Mean_Ud);
    MEAN_Cal_T(&pMotor->PMSM_FILTER_CTRL.Mean_Uq);
    MEAN_Cal_T(&pMotor->PMSM_FILTER_CTRL.Mean_Es);
    
    MC_Error_Current_Flow(&pMotor->MC_ERR);
}

/**********************************************************************************************
Function: MotorTask_Shut_Flow_T
Description: 电机控制故障关断
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Shut_Flow_T(ST_MOTOR_TASK* pMotor)
{
    MH_PWM_Output_Disable();
    MC_Error_Short_Flow(&pMotor->MC_ERR);
}
