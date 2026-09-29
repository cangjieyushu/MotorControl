/*
*     File Name :                        mcfoc_task_t
*     Library/Module Name :              mcfoc_t
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机子任务
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "mcfoc_task_t.h"


/*-------------------------- 2. 变量 ---------------------------------*/
static ST_MCFOC_TASK_T* pMCFOC_Task_T[3] = 
{
    &MCFOC_Task_T,
    &MCFOC_Task_T,
    &MCFOC_Task_T
};


typedef void(*pMOTOR_FUN)(ST_MCFOC_TASK_T*);

void MCFOC_Pre_Flow_T(ST_MCFOC_TASK_T* pMotor);
void MCFOC_Init_Flow_T(ST_MCFOC_TASK_T* pMotor);
void MCFOC_Idle_Flow_T(ST_MCFOC_TASK_T* pMotor);
void MCFOC_Boot_Flow_T(ST_MCFOC_TASK_T* pMotor);
void MCFOC_Position_Flow_T(ST_MCFOC_TASK_T* pMotor);
void MCFOC_Run_Flow_T(ST_MCFOC_TASK_T* pMotor);
void MCFOC_Brake_Flow_T(ST_MCFOC_TASK_T* pMotor);

pMOTOR_FUN Motor_Flow_Function_T[MOTOR_STATE_BRAKE+1] =
{
    MCFOC_Pre_Flow_T,
    MCFOC_Init_Flow_T,
    MCFOC_Idle_Flow_T,
    MCFOC_Boot_Flow_T,
    MCFOC_Position_Flow_T,
    MCFOC_Run_Flow_T,
    MCFOC_Brake_Flow_T
};


/*-------------------------- 3. 公有接口实现 -----------------------------*/
#if (MOTOR_SHUNT_MODE == MOTOR_SHUNT_THREE)
static inline void MCFOC_Init_Flow_ADC_Read_Three_T(ST_MCFOC_OFFSET_T* pOFFSET)
{
    Q32U_ adc_data1,adc_data2,adc_data3 = 0;
    
    HM_ADC_Data_Read_Three(&adc_data1, &adc_data2, &adc_data3);
    
    pOFFSET->I_Q12I_Ia_Data = adc_data1;
    pOFFSET->I_Q12I_Ib_Data = adc_data2;
    pOFFSET->I_Q12I_Ic_Data = adc_data3;
}

static inline void MCFOC_Run_Flow_ADC_Read_Three_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    Q32U_ adc_data1,adc_data2,adc_data3 = 0;
    
    HM_ADC_Data_Read_Three(&adc_data1, &adc_data2, &adc_data3);
    
    pPMSMe->I_Q12I_Ia_Data = adc_data1;
    pPMSMe->I_Q12I_Ib_Data = adc_data2;
    pPMSMe->I_Q12I_Ic_Data = adc_data3;
    
    pPMSMe->V_Q14I_Ia = Q16I_LFT_02(pPMSMe->I_Q12I_Ia_Offset - pPMSMe->I_Q12I_Ia_Data);
    pPMSMe->V_Q14I_Ib = Q16I_LFT_02(pPMSMe->I_Q12I_Ib_Offset - pPMSMe->I_Q12I_Ib_Data);
    pPMSMe->V_Q14I_Ic = Q16I_LFT_02(pPMSMe->I_Q12I_Ic_Offset - pPMSMe->I_Q12I_Ic_Data);
    
    MCFOC_ThreeShunt_Current_Cal_T(pSVPWM, pPMSMe);
    MCFOC_SVPWM_Duty_Refactor_T(pSVPWM, pPMSMe);
}

static inline void MCFOC_Run_Flow_PWM_Set_Three_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa)
{    
    MCFOC_PMSM_Ipark_T(pPMSMe);
    MCFOC_SVPWM_ThreeShunt_T(pSVPWM, pPMSMe);
    MCFOC_PMSM_Iclark_T(pPMSMe);
    MCFOC_SVPWM_DeadTime_Compensate_T(pSVPWM, pPMSMe);
    
    HM_PWM_Duty_Set_Three(Q32I_RHT_15(pSVPWM->P_Q32U_PWM_All_Count*pPMSMa->O_Q14I_PWM_Period_Coeff),
                          Q32I_RHT_15(pSVPWM->P_Q32U_PWM_All_Count*(16384 - pSVPWM->O_Q14U_Dutya)),
                          Q32I_RHT_15(pSVPWM->P_Q32U_PWM_All_Count*(16384 - pSVPWM->O_Q14U_Dutyb)),
                          Q32I_RHT_15(pSVPWM->P_Q32U_PWM_All_Count*(16384 - pSVPWM->O_Q14U_Dutyc)));
}
#endif

#if (MOTOR_SHUNT_MODE == MOTOR_SHUNT_ONE)
static inline void MCFOC_Init_Flow_ADC_Read_One_T(ST_MCFOC_OFFSET_T* pOFFSET)
{
    Q32U_ adc_data1,adc_data2 = 0;
    
    HM_ADC_Data_Read_One(&adc_data1, &adc_data2);

    pOFFSET->I_Q12I_Ishunt_Data = (Q32I_)adc_data1;
}

static inline void MCFOC_Run_Flow_ADC_Read_One_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    Q32U_ adc_data1,adc_data2 = 0;
    
    HM_ADC_Data_Read_One(&adc_data1, &adc_data2);
    pPMSMe->I_Q12I_Ishunt_1_Data = (Q32I_)adc_data1;
    pPMSMe->I_Q12I_Ishunt_2_Data = (Q32I_)adc_data2;
    
    pPMSMe->I_Q14I_Ishunt[0] =   Q16I_LFT_02(pPMSMe->I_Q12I_Ishunt_1_Data - pPMSMe->I_Q12I_Ishunt_Offset);
    pPMSMe->I_Q14I_Ishunt[2] = - Q16I_LFT_02(pPMSMe->I_Q12I_Ishunt_2_Data - pPMSMe->I_Q12I_Ishunt_Offset);
    pPMSMe->I_Q14I_Ishunt[1] = - pPMSMe->I_Q14I_Ishunt[0] - pPMSMe->I_Q14I_Ishunt[2];
    
    MCFOC_OneShunt_Current_Cal_T(pSVPWM, pPMSMe);
    MCFOC_SVPWM_Duty_Refactor_T(pSVPWM, pPMSMe);
}

static inline void MCFOC_Run_Flow_PWM_Set_One_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa)
{
    Q32I_ pwm_tmp1,pwm_tmp2,pwm_tmp3,pwm_tmp4,pwm_tmp5,pwm_tmp6,adc_tmp1,adc_tmp2 = 0;
    
    MCFOC_PMSM_Ipark_T(pPMSMe);
    MCFOC_SVPWM_OneShunt_T(pSVPWM, pPMSMe);
    MCFOC_PMSM_Iclark_T(pPMSMe);
    
    pwm_tmp1 = Q32I_RHT_14(pSVPWM->P_Q32U_PWM_All_Count*pSVPWM->O_Q14U_TaUp);
    pwm_tmp2 = Q32I_RHT_14(pSVPWM->P_Q32U_PWM_All_Count*pSVPWM->O_Q14U_TaDn);
    pwm_tmp3 = Q32I_RHT_14(pSVPWM->P_Q32U_PWM_All_Count*pSVPWM->O_Q14U_TbUp);
    pwm_tmp4 = Q32I_RHT_14(pSVPWM->P_Q32U_PWM_All_Count*pSVPWM->O_Q14U_TbDn);
    pwm_tmp5 = Q32I_RHT_14(pSVPWM->P_Q32U_PWM_All_Count*pSVPWM->O_Q14U_TcUp);
    pwm_tmp6 = Q32I_RHT_14(pSVPWM->P_Q32U_PWM_All_Count*pSVPWM->O_Q14U_TcDn);
    adc_tmp1 = Q32I_RHT_14(pSVPWM->P_Q32U_PWM_All_Count*pSVPWM->O_Q14U_ADCTrigTime1);
    adc_tmp2 = Q32I_RHT_14(pSVPWM->P_Q32U_PWM_All_Count*pSVPWM->O_Q14U_ADCTrigTime2);
    
    HM_PWM_Duty_Set_One((Q32U_)pwm_tmp1,(Q32U_)pwm_tmp2,(Q32U_)pwm_tmp3,(Q32U_)pwm_tmp4,(Q32U_)pwm_tmp5,(Q32U_)pwm_tmp6);
    HM_ADC_TrigTime_Set((Q32U_)adc_tmp1,(Q32U_)adc_tmp2);
}
#endif


void MCFOC_Pre_Flow_T(ST_MCFOC_TASK_T* pMotor)
{
    if(pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        MCFOC_Offset_Check_Init_T(&pMotor->MCFOC_Offset);
        
        MCFOC_PMSM_Para_Init_T(&pMotor->PMSM_Elec);
        MCFOC_ALIGN_Init_T(&pMotor->Align_Ctrl);
        MCFOC_IF_Init_T(&pMotor->IF_Ctrl);
        MCFOC_SpeedLoop_Init_T(&pMotor->Freq_Ctrl);
        MCFOC_CurrentLoop_Init_T(&pMotor->Current_Ctrl);
        MCFOC_SVPWM_Init_T(&pMotor->SVPWM_Ctrl);
        
        MCFOC_EST_EMF_Init_T(&pMotor->EMF_Ctrl);
        MCFOC_EST_SMO_Init_T(&pMotor->SMO_Ctrl);
        MCFOC_EST_FLUX_Init_T(&pMotor->FLUX_Ctrl);
        
#if(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_IF)
        pMotor->Motor_Loop_Mode = MOTOR_LOOP_ALIGN;
#elif(MOTOR_OPENLOOP_MODE == MOTOR_OPENLOOP_FLUX)
        pMotor->Motor_Loop_Mode = MOTOR_LOOP_CLOSE;
#endif

        pMotor->Motor_Flow = MOTOR_STATE_INIT;
    }
    else
    {
        pMotor->MCFOC_EST_Freq = 0;
        pMotor->PMSM_Elec.I_Q14I_Ibus = 0;
        pMotor->PMSM_Elec.V_Q14I_Id_Real = 0;
        pMotor->PMSM_Elec.V_Q14I_Iq_Real = 0;
        pMotor->PMSM_Elec.V_Q14I_Ud_Real = 0;
        pMotor->PMSM_Elec.V_Q14I_Uq_Real = 0;
        pMotor->EMF_Ctrl.O_Q14I_EMF_Ealfa = 0;
        pMotor->EMF_Ctrl.O_Q14I_EMF_Ebeta = 0;
        
        HM_PWM_Output_Disable();
    }
}

void MCFOC_Init_Flow_T(ST_MCFOC_TASK_T* pMotor)
{
    if(pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        MCFOC_Init_Flow_ADC_Read(&pMotor->MCFOC_Offset);
        
        switch(MCFOC_Offset_Check(&pMotor->MCFOC_Offset, &pMotor->PMSM_Elec))
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
                pMotor->Motor_Error.Motor_Error_Flag.bit.current_offset = 1U;
                pMotor->Motor_Flow = MOTOR_STATE_PRE;
                break;
            }
            default:break;
        }
    }
    else
    {
        HM_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

void MCFOC_Idle_Flow_T(ST_MCFOC_TASK_T* pMotor)
{
    if(pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        pMotor->Motor_Flow = MOTOR_STATE_BOOT;
    }
    else
    {
        HM_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

void MCFOC_Boot_Flow_T(ST_MCFOC_TASK_T* pMotor)
{
    if(pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        pMotor->Motor_Flow = MOTOR_STATE_POSITION;
    }
    else
    {
        HM_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

void MCFOC_Position_Flow_T(ST_MCFOC_TASK_T* pMotor)
{
    if(pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        pMotor->Motor_Flow = MOTOR_STATE_RUN;
    }
    else
    {
        HM_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

void MCFOC_Run_Flow_T(ST_MCFOC_TASK_T* pMotor)
{
    if(pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        MCFOC_Run_Flow_ADC_Read(&pMotor->SVPWM_Ctrl, &pMotor->PMSM_Elec);
        MCFOC_PMSM_Clark_T(&pMotor->PMSM_Elec);

        MCFOC_EST_EMF_Cal_T(&pMotor->EMF_Ctrl, &pMotor->PMSM_Elec);
        MCFOC_EST_FUNCTION;
        
        if(pMotor->Motor_Loop_Mode == MOTOR_LOOP_ALIGN)
        {
            MCFOC_ALIGN_CurrentLoop_T(&pMotor->Align_Ctrl);
            
            pMotor->PMSM_Elec.TG_Triangle_Est.Q14U_Angle = pMotor->Align_Ctrl.O_Q14I_Align_Angle;
            Math_SinCos_T(&pMotor->PMSM_Elec.TG_Triangle_Est);
        }
        else if(pMotor->Motor_Loop_Mode == MOTOR_LOOP_OPEN)
        {
            pMotor->IF_Ctrl.I_Q14I_IF_Est_Angle = pMotor->MCFOC_EST_TG_Triangle.Q14U_Angle + pMotor->MCFOC_EST_TG_Triangle_Comp.Q14U_Angle;
            MATH_ANGLE_MOD_T(pMotor->IF_Ctrl.I_Q14I_IF_Est_Angle);
            MCFOC_IF_CurrentLoop_T(&pMotor->IF_Ctrl, &pMotor->PMSM_Elec, &pMotor->PMSM_Para);
            
            pMotor->PMSM_Elec.TG_Triangle_Est.Q14U_Angle = pMotor->IF_Ctrl.O_Q14I_IF_Angle;
            Math_SinCos_T(&pMotor->PMSM_Elec.TG_Triangle_Est);

        }
        else if(pMotor->Motor_Loop_Mode == MOTOR_LOOP_CLOSE)
        {
            pMotor->PMSM_Elec.TG_Triangle_Est = pMotor->MCFOC_EST_TG_Triangle;
            pMotor->PMSM_Elec.TG_Triangle_Comp = pMotor->MCFOC_EST_TG_Triangle_Comp;
        }
        
        MCFOC_PMSM_Park_T(&pMotor->PMSM_Elec);
        MCFOC_CurrentLoop_T(&pMotor->Current_Ctrl, &pMotor->PMSM_Elec);
        
        MCFOC_Run_Flow_PWM_Set(&pMotor->SVPWM_Ctrl, &pMotor->PMSM_Elec, &pMotor->PMSM_Para);

        HM_PWM_Output_Enable();
        
    }
    else
    {
        HM_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_BRAKE;
    }
}

void MCFOC_Brake_Flow_T(ST_MCFOC_TASK_T* pMotor)
{
    if(pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        HM_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
    else
    {
        HM_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

void MCFOC_Speed_Flow_T(Q32U_ motor_num)
{
    ST_MCFOC_TASK_T* pMotor = pMCFOC_Task_T[motor_num];

    Motor_Parameter_API_T(pMotor);
    
    MCFOC_PMSM_Para_Adapt_T(&pMotor->PMSM_Filter, &pMotor->PMSM_Elec, &pMotor->PMSM_Para);
    MCFOC_EST_EMF_Adapt_T(&pMotor->EMF_Ctrl, &pMotor->PMSM_Para);
    MCFOC_EST_SMO_Adapt_T(&pMotor->SMO_Ctrl, &pMotor->PMSM_Elec, &pMotor->PMSM_Para);
    MCFOC_EST_FLUX_Adapt_T(&pMotor->FLUX_Ctrl, &pMotor->PMSM_Elec, &pMotor->PMSM_Para);
    MCFOC_SevFiv_Check_T(&pMotor->SVPWM_Ctrl, &pMotor->PMSM_Elec);

    pMotor->Motor_Error.I_Q14U_IsRef_pu = 
    (MATH_SQRTADD_T(pMotor->Current_Ctrl.I_Q14I_IdRef, pMotor->Current_Ctrl.I_Q14I_IqRef));
    pMotor->Motor_Error.I_Q14U_Iphase_A_Max_pu = pMotor->PMSM_Filter.Max_Ia.O_Q14I_MAX_Out;
    pMotor->Motor_Error.I_Q14U_Iphase_B_Max_pu = pMotor->PMSM_Filter.Max_Ib.O_Q14I_MAX_Out;
    pMotor->Motor_Error.I_Q14U_Iphase_C_Max_pu = pMotor->PMSM_Filter.Max_Ic.O_Q14I_MAX_Out;
    pMotor->Motor_Error.I_Q14U_Es_pu = pMotor->PMSM_Filter.Mean_Es.O_Q14I_MEAN_Out;;

    pMotor->Motor_Error.I_Q14U_Vbus_pu = pMotor->PMSM_Elec.O_Q14I_Vbus;
    pMotor->Motor_Error.I_Q14U_Iphase_Max_pu = MATH_MAX_T(pMotor->Motor_Error.I_Q14U_Iphase_A_Max_pu, 
    MATH_MAX_T(pMotor->Motor_Error.I_Q14U_Iphase_B_Max_pu, pMotor->Motor_Error.I_Q14U_Iphase_C_Max_pu));
    pMotor->Motor_Error.I_Q14U_Temp_ADC = 1500;
    pMotor->Motor_Error.I_Q14U_Speed_pu = pMotor->PMSM_Elec.O_Q14I_Freq;
    pMotor->Motor_Error.I_Q14U_Ibus_pu = pMotor->PMSM_Elec.O_Q14I_Ibus_10ms;
    MC_Error_Speed_Flow(&pMotor->Motor_Error, ((pMotor->Motor_Flow >= MOTOR_STATE_BOOT)&&(pMotor->Motor_Flow <= MOTOR_STATE_BRAKE)));
    MC_Error_Speed_Flow_FOC(&pMotor->Motor_Error, ((pMotor->Motor_Flow >= MOTOR_STATE_BOOT)&&(pMotor->Motor_Flow <= MOTOR_STATE_BRAKE)));
    
//FOC转速环任务
    if(pMotor->Motor_Flow == MOTOR_STATE_RUN)
    {
        if(pMotor->Motor_Loop_Mode == MOTOR_LOOP_ALIGN)
        {
            MCFOC_ALIGN_SpeedLoop_T(&pMotor->Align_Ctrl);
            pMotor->Current_Ctrl.I_Q14I_IdRef = pMotor->Align_Ctrl.O_Q14I_Align_IdRef;
            pMotor->Current_Ctrl.I_Q14I_IqRef = 0;
    
            if(pMotor->Align_Ctrl.O_Q32U_Stand_Flag == 1U)
            {
                pMotor->Motor_Loop_Mode = MOTOR_LOOP_OPEN;
            }
        }
        else if(pMotor->Motor_Loop_Mode == MOTOR_LOOP_OPEN)
        {
            MCFOC_IF_SpeedLoop_T(&pMotor->IF_Ctrl, &pMotor->PMSM_Elec);
            pMotor->Current_Ctrl.I_Q14I_IdRef = pMotor->IF_Ctrl.O_Q14I_IF_IdRef;
            pMotor->Current_Ctrl.I_Q14I_IqRef = pMotor->IF_Ctrl.O_Q14I_IF_IqRef;
    
            if(pMotor->IF_Ctrl.O_Q32U_Switch_Flag == 1U)
            {
                Ramp_Init_T(&pMotor->Freq_Ctrl.Ramp_FREQ, pMotor->IF_Ctrl.Ramp_IF_FREQ.O_Q14I_Output);
                PID_Sat_Init_T(&pMotor->Freq_Ctrl.PID_FREQ, pMotor->IF_Ctrl.O_Q14I_IF_IqRef);
                pMotor->Motor_Loop_Mode = MOTOR_LOOP_CLOSE;
            }
        }
        else if(pMotor->Motor_Loop_Mode == MOTOR_LOOP_CLOSE)
        {
            MCFOC_SpeedLoop_T(&pMotor->Freq_Ctrl, &pMotor->PMSM_Elec, &pMotor->PMSM_Para);
            pMotor->Current_Ctrl.I_Q14I_IdRef = pMotor->Freq_Ctrl.O_Q14I_FREQ_IdRef;
            pMotor->Current_Ctrl.I_Q14I_IqRef = pMotor->Freq_Ctrl.O_Q14I_FREQ_IqRef;
        }
    }
    else if(pMotor->Motor_Flow == MOTOR_STATE_BRAKE)
    {
        
    }
}

void MCFOC_Current_Flow_T(Q32U_ motor_num)
{
    ST_MCFOC_TASK_T* pMotor = pMCFOC_Task_T[motor_num];
    
    Q32U_ vbus_tmp = 0U;
    HM_ADC_Data_Read_Vbus(&vbus_tmp);
    
    if(pMotor->Motor_Error.Motor_Error_Flag.all != 0U)
    {
        pMotor->Motor_Flag.bit.motor_enable_flag = 0U;
    }
    
    Motor_Flow_Function_T[pMotor->Motor_Flow](pMotor);
    
    pMotor->PMSM_Filter.Mean_Freq.I_Q14I_MEAN_In = pMotor->MCFOC_EST_Freq;
    pMotor->PMSM_Filter.Mean_Vbus.I_Q14I_MEAN_In = Q16I_LFT_02(vbus_tmp);
    pMotor->PMSM_Filter.Mean_Ibus.I_Q14I_MEAN_In = pMotor->PMSM_Elec.I_Q14I_Ibus;
    pMotor->PMSM_Filter.Mean_Id.I_Q14I_MEAN_In = pMotor->PMSM_Elec.V_Q14I_Id_Real;
    pMotor->PMSM_Filter.Mean_Iq.I_Q14I_MEAN_In = pMotor->PMSM_Elec.V_Q14I_Iq_Real;
    pMotor->PMSM_Filter.Mean_Ud.I_Q14I_MEAN_In = pMotor->PMSM_Elec.V_Q14I_Ud_Real;
    pMotor->PMSM_Filter.Mean_Uq.I_Q14I_MEAN_In = pMotor->PMSM_Elec.V_Q14I_Uq_Real;
    pMotor->PMSM_Filter.Mean_Es.I_Q14I_MEAN_In = MATH_SQRTADD_T(pMotor->EMF_Ctrl.O_Q14I_EMF_Ealfa, pMotor->EMF_Ctrl.O_Q14I_EMF_Ebeta);

    MEAN_Cal_T(&pMotor->PMSM_Filter.Mean_Freq);
    MEAN_Cal_T(&pMotor->PMSM_Filter.Mean_Vbus);
    MEAN_Cal_T(&pMotor->PMSM_Filter.Mean_Ibus);
    MEAN_Cal_T(&pMotor->PMSM_Filter.Mean_Id);
    MEAN_Cal_T(&pMotor->PMSM_Filter.Mean_Iq);
    MEAN_Cal_T(&pMotor->PMSM_Filter.Mean_Ud);
    MEAN_Cal_T(&pMotor->PMSM_Filter.Mean_Uq);
    MEAN_Cal_T(&pMotor->PMSM_Filter.Mean_Es);
    
    MC_Error_Current_Flow(&pMotor->Motor_Error);
}
