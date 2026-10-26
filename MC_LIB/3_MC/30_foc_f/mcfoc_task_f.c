/**
 * @file    mcfoc_task_f.c
 * @brief   FOC 电机子任务实现（浮点）
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "hal_mc.h"
#include "mcfoc_task_f.h"
#include "mcfoc_para_f.h"
#include "bsp_mc.h"

/* ======================== 2. Defines ====================== */
#if (HW_FUN_MC_MOTOR_SHUNT_MODE == HW_FUN_MC_MOTOR_SHUNT_THREE)
#define MCFOC_Offset_Check              MCFOC_Offset_Check_Three_F
#define MCFOC_Init_Flow_ADC_Read        MCFOC_Init_Flow_ADC_Read_Three_F
#define MCFOC_Run_Flow_ADC_Read         MCFOC_Run_Flow_ADC_Read_Three_F
#define MCFOC_Run_Flow_PWM_Set          MCFOC_Run_Flow_PWM_Set_Three_F
#elif (HW_FUN_MC_MOTOR_SHUNT_MODE == HW_FUN_MC_MOTOR_SHUNT_ONE)
#define MCFOC_Offset_Check              MCFOC_Offset_Check_One_F
#define MCFOC_Init_Flow_ADC_Read        MCFOC_Init_Flow_ADC_Read_One_F
#define MCFOC_Run_Flow_ADC_Read         MCFOC_Run_Flow_ADC_Read_One_F
#define MCFOC_Run_Flow_PWM_Set          MCFOC_Run_Flow_PWM_Set_One_F
#endif

#if (HW_FUN_MC_MOTOR_EST_MODE == HW_FUN_MC_MOTOR_EST_SMO)
#define MCFOC_EST_FUNCTION              MCFOC_EST_SMO_Cal_F(&pMotor->SMO_Ctrl, &pMotor->PMSM_Elec);
#define MCFOC_EST_Freq                  SMO_Ctrl.FL_SMO_FREQ.O_F_LPF_Out
#define MCFOC_EST_TG_Triangle           SMO_Ctrl.TG_SMO_Triangle
#define MCFOC_EST_TG_Triangle_Comp      SMO_Ctrl.TG_SMO_Triangle_Comp
#elif (HW_FUN_MC_MOTOR_EST_MODE == HW_FUN_MC_MOTOR_EST_FLUX)
#define MCFOC_EST_FUNCTION              MCFOC_EST_FLUX_Cal_F(&pMotor->FLUX_Ctrl, &pMotor->PMSM_Elec);
#define MCFOC_EST_Freq                  FLUX_Ctrl.FL_FLUX_FREQ.O_F_LPF_Out
#define MCFOC_EST_TG_Triangle           FLUX_Ctrl.TG_FLUX_Triangle
#define MCFOC_EST_TG_Triangle_Comp      FLUX_Ctrl.TG_FLUX_Triangle_Comp
#endif

/* ======================== 3. Typedefs ===================== */

/** @brief 电机状态机函数指针 */
typedef void (*pMOTOR_FUN)(ST_MCFOC_TASK_F*);

/* ======================== 4. Globals ====================== */

/** @brief 电机任务指针数组（当前仅使用单电机配置） */
static ST_MCFOC_TASK_F* pMCFOC_Task_F[3] = {
    &MCFOC_Task_F,
    &MCFOC_Task_F,
    &MCFOC_Task_F
};

/* ======================== 5. Function Prototypes ========== */
void MCFOC_Pre_Flow_F(ST_MCFOC_TASK_F* pMotor);
void MCFOC_Init_Flow_F(ST_MCFOC_TASK_F* pMotor);
void MCFOC_Idle_Flow_F(ST_MCFOC_TASK_F* pMotor);
void MCFOC_Boot_Flow_F(ST_MCFOC_TASK_F* pMotor);
void MCFOC_Position_Flow_F(ST_MCFOC_TASK_F* pMotor);
__attribute__CCMRAM
void MCFOC_Run_Flow_F(ST_MCFOC_TASK_F* pMotor);
void MCFOC_Brake_Flow_F(ST_MCFOC_TASK_F* pMotor);

/** @brief 状态机分发表：按 EM_MOTOR_STATE 顺序调用对应阶段函数 */
pMOTOR_FUN Motor_Flow_Function_F[MOTOR_STATE_BRAKE + 1] = {
    MCFOC_Pre_Flow_F,
    MCFOC_Init_Flow_F,
    MCFOC_Idle_Flow_F,
    MCFOC_Boot_Flow_F,
    MCFOC_Position_Flow_F,
    MCFOC_Run_Flow_F,
    MCFOC_Brake_Flow_F
};

/* ======================== 6. Functions ==================== */

#if (HW_FUN_MC_MOTOR_SHUNT_MODE == HW_FUN_MC_MOTOR_SHUNT_THREE)

/**
 * @brief  Init 阶段 ADC 读取（三相采样）
 * @param  pOFFSET  偏置结构体指针
 */
static inline void MCFOC_Init_Flow_ADC_Read_Three_F(ST_MCFOC_OFFSET_F* pOFFSET)
{
    Q32U_ adc_data1, adc_data2, adc_data3 = 0;

    HAL_MC_ADC_Read_Three(&adc_data1, &adc_data2, &adc_data3);

    pOFFSET->I_Q12I_Ia_Data = adc_data1;
    pOFFSET->I_Q12I_Ib_Data = adc_data2;
    pOFFSET->I_Q12I_Ic_Data = adc_data3;
}

/**
 * @brief  Run 阶段 ADC 读取（三相采样）
 * @param  pSVPWM  SVPWM 结构体指针
 * @param  pPMSMe  电机电气量指针
 */
static inline void MCFOC_Run_Flow_ADC_Read_Three_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe)
{
    Q32U_ adc_data1, adc_data2, adc_data3 = 0;

    HAL_MC_ADC_Read_Three(&adc_data1, &adc_data2, &adc_data3);

    pPMSMe->I_Q12I_Ia_Data = adc_data1;
    pPMSMe->I_Q12I_Ib_Data = adc_data2;
    pPMSMe->I_Q12I_Ic_Data = adc_data3;

    pPMSMe->V_F_Ia  = 0.0002442f * ((float)(pPMSMe->I_Q12I_Ia_Offset - pPMSMe->I_Q12I_Ia_Data));
    pPMSMe->V_F_Ib  = 0.0002442f * ((float)(pPMSMe->I_Q12I_Ib_Offset - pPMSMe->I_Q12I_Ib_Data));
    pPMSMe->V_F_Ic  = 0.0002442f * ((float)(pPMSMe->I_Q12I_Ic_Offset - pPMSMe->I_Q12I_Ic_Data));

    MCFOC_ThreeShunt_Current_Cal_F(pSVPWM, pPMSMe);
    MCFOC_SVPWM_Duty_Refactor_F(pSVPWM, pPMSMe);
}

/**
 * @brief  Run 阶段 PWM 输出（三相采样）
 * @param  pSVPWM  SVPWM 结构体指针
 * @param  pPMSMe  电机电气量指针
 * @param  pPMSMa  电机参数运行量指针
 */
static inline void MCFOC_Run_Flow_PWM_Set_Three_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa)
{
    MCFOC_PMSM_Ipark_F(pPMSMe);
    MCFOC_SVPWM_ThreeShunt_F(pSVPWM, pPMSMe);
    MCFOC_PMSM_Iclark_F(pPMSMe);
    MCFOC_SVPWM_DeadTime_Compensate_F(pSVPWM, pPMSMe);

    HAL_MC_PWM_Duty_Set_Three((Q32U_)(0.5f * pSVPWM->P_F_PWM_All_Count * pPMSMa->O_F_PWM_Period_Coeff),
                              (Q32U_)(0.5f * pSVPWM->P_F_PWM_All_Count * pSVPWM->O_F_Dutya),
                              (Q32U_)(0.5f * pSVPWM->P_F_PWM_All_Count * pSVPWM->O_F_Dutyb),
                              (Q32U_)(0.5f * pSVPWM->P_F_PWM_All_Count * pSVPWM->O_F_Dutyc));
}
#endif

#if (HW_FUN_MC_MOTOR_SHUNT_MODE == HW_FUN_MC_MOTOR_SHUNT_ONE)

/**
 * @brief  Init 阶段 ADC 读取（单电阻采样）
 * @param  pOFFSET  偏置结构体指针
 */
static inline void MCFOC_Init_Flow_ADC_Read_One_F(ST_MCFOC_OFFSET_F* pOFFSET)
{
    Q32U_ adc_data1, adc_data2 = 0;

    HAL_MC_ADC_Read_One(&adc_data1, &adc_data2);

    pOFFSET->I_Q12I_Ishunt_Data = (Q32I_)adc_data1;
}

/**
 * @brief  Run 阶段 ADC 读取（单电阻采样）
 * @param  pSVPWM  SVPWM 结构体指针
 * @param  pPMSMe  电机电气量指针
 */
static inline void MCFOC_Run_Flow_ADC_Read_One_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe)
{
    Q32U_ adc_data1, adc_data2 = 0;

    HAL_MC_ADC_Read_One(&adc_data1, &adc_data2);
    pPMSMe->I_Q12I_Ishunt_1_Data = (Q32I_)adc_data1;
    pPMSMe->I_Q12I_Ishunt_2_Data = (Q32I_)adc_data2;

    pPMSMe->I_F_Ishunt[0] =  0.0002442f * ((float)(pPMSMe->I_Q12I_Ishunt_1_Data - pPMSMe->I_Q12I_Ishunt_Offset));
    pPMSMe->I_F_Ishunt[2] = -0.0002442f * ((float)(pPMSMe->I_Q12I_Ishunt_2_Data - pPMSMe->I_Q12I_Ishunt_Offset));
    pPMSMe->I_F_Ishunt[1] = -pPMSMe->I_F_Ishunt[0] - pPMSMe->I_F_Ishunt[2];

    MCFOC_OneShunt_Current_Cal_F(pSVPWM, pPMSMe);
    MCFOC_SVPWM_Duty_Refactor_F(pSVPWM, pPMSMe);
}

/**
 * @brief  Run 阶段 PWM 输出（单电阻采样）
 * @param  pSVPWM  SVPWM 结构体指针
 * @param  pPMSMe  电机电气量指针
 * @param  pPMSMa  电机参数运行量指针
 */
static inline void MCFOC_Run_Flow_PWM_Set_One_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa)
{
    float pwm_tmp1, pwm_tmp2, pwm_tmp3, pwm_tmp4, pwm_tmp5, pwm_tmp6, adc_tmp1, adc_tmp2 = 0.0f;

    MCFOC_PMSM_Ipark_F(pPMSMe);
    MCFOC_SVPWM_OneShunt_F(pSVPWM, pPMSMe);
    MCFOC_PMSM_Iclark_F(pPMSMe);

    pwm_tmp1 = pSVPWM->P_F_PWM_All_Count * pSVPWM->O_F_TaUp;
    pwm_tmp2 = pSVPWM->P_F_PWM_All_Count * pSVPWM->O_F_TaDn;
    pwm_tmp3 = pSVPWM->P_F_PWM_All_Count * pSVPWM->O_F_TbUp;
    pwm_tmp4 = pSVPWM->P_F_PWM_All_Count * pSVPWM->O_F_TbDn;
    pwm_tmp5 = pSVPWM->P_F_PWM_All_Count * pSVPWM->O_F_TcUp;
    pwm_tmp6 = pSVPWM->P_F_PWM_All_Count * pSVPWM->O_F_TcDn;
    adc_tmp1 = pSVPWM->P_F_PWM_All_Count * pSVPWM->O_F_ADCTrigTime1;
    adc_tmp2 = pSVPWM->P_F_PWM_All_Count * pSVPWM->O_F_ADCTrigTime2;

    HAL_MC_PWM_Duty_Set_One((Q32U_)pwm_tmp1, (Q32U_)pwm_tmp2, (Q32U_)pwm_tmp3, (Q32U_)pwm_tmp4, (Q32U_)pwm_tmp5, (Q32U_)pwm_tmp6);
    HAL_MC_ADC_TrigTime_Set_One((Q32U_)adc_tmp1, (Q32U_)adc_tmp2);
}
#endif

/**
 * @brief  电机 Pre 阶段（复位 / 上电初始化）
 * @param  pMotor  电机任务结构体指针
 */
void MCFOC_Pre_Flow_F(ST_MCFOC_TASK_F* pMotor)
{
    if (pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        MC_Error_Init_Flow(&pMotor->Motor_Error);

        MCFOC_Offset_Check_Init_F(&pMotor->MCFOC_Offset);

        MCFOC_PMSM_Para_Init_F(&pMotor->PMSM_Elec);
        MCFOC_ALIGN_Init_F(&pMotor->Align_Ctrl);
        MCFOC_IF_Init_F(&pMotor->IF_Ctrl);
        MCFOC_SpeedLoop_Init_F(&pMotor->Freq_Ctrl);
        MCFOC_CurrentLoop_Init_F(&pMotor->Current_Ctrl);
        MCFOC_SVPWM_Init_F(&pMotor->SVPWM_Ctrl);

        MCFOC_EST_EMF_Init_F(&pMotor->EMF_Ctrl);
        MCFOC_EST_SMO_Init_F(&pMotor->SMO_Ctrl);
        MCFOC_EST_FLUX_Init_F(&pMotor->FLUX_Ctrl);

        pMotor->Motor_Loop_Mode = MOTOR_LOOP_ALIGN;

        pMotor->Motor_Flow = MOTOR_STATE_INIT;
    }
    else
    {
        pMotor->MCFOC_EST_Freq               = 0.0f;
        pMotor->PMSM_Elec.I_F_Ibus           = 0.0f;
        pMotor->PMSM_Elec.V_F_Id_Real        = 0.0f;
        pMotor->PMSM_Elec.V_F_Iq_Real        = 0.0f;
        pMotor->PMSM_Elec.V_F_Ud_Real        = 0.0f;
        pMotor->PMSM_Elec.V_F_Uq_Real        = 0.0f;
        pMotor->EMF_Ctrl.O_F_EMF_Ealfa       = 0.0f;
        pMotor->EMF_Ctrl.O_F_EMF_Ebeta       = 0.0f;

        HAL_MC_PWM_Output_Disable();
    }
}

/**
 * @brief  电机 Init 阶段（电流偏置检测）
 * @param  pMotor  电机任务结构体指针
 */
void MCFOC_Init_Flow_F(ST_MCFOC_TASK_F* pMotor)
{
    if (pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        MCFOC_Init_Flow_ADC_Read(&pMotor->MCFOC_Offset);

        switch (MCFOC_Offset_Check(&pMotor->MCFOC_Offset, &pMotor->PMSM_Elec))
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
            default: break;
        }
    }
    else
    {
        HAL_MC_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**
 * @brief  电机 Idle 阶段
 * @param  pMotor  电机任务结构体指针
 */
void MCFOC_Idle_Flow_F(ST_MCFOC_TASK_F* pMotor)
{
    if (pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        pMotor->Motor_Flow = MOTOR_STATE_BOOT;
    }
    else
    {
        HAL_MC_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**
 * @brief  电机 Boot 阶段（自举）
 * @param  pMotor  电机任务结构体指针
 */
void MCFOC_Boot_Flow_F(ST_MCFOC_TASK_F* pMotor)
{
    if (pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        pMotor->Motor_Flow = MOTOR_STATE_POSITION;
    }
    else
    {
        HAL_MC_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**
 * @brief  电机 Position 阶段（定位）
 * @param  pMotor  电机任务结构体指针
 */
void MCFOC_Position_Flow_F(ST_MCFOC_TASK_F* pMotor)
{
    if (pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        pMotor->Motor_Flow = MOTOR_STATE_RUN;
    }
    else
    {
        HAL_MC_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**
 * @brief  电机 Run 阶段（电流中断主体）
 * @param  pMotor  电机任务结构体指针
 */
void MCFOC_Run_Flow_F(ST_MCFOC_TASK_F* pMotor)
{
    if (pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        MCFOC_Run_Flow_ADC_Read(&pMotor->SVPWM_Ctrl, &pMotor->PMSM_Elec);
        MCFOC_PMSM_Clark_F(&pMotor->PMSM_Elec);

        MCFOC_EST_EMF_Cal_F(&pMotor->EMF_Ctrl, &pMotor->PMSM_Elec);
        MCFOC_EST_FUNCTION;

        if (pMotor->Motor_Loop_Mode == MOTOR_LOOP_ALIGN)
        {
            MCFOC_ALIGN_CurrentLoop_F(&pMotor->Align_Ctrl);

            pMotor->PMSM_Elec.TG_Triangle_Est.F_Angle = pMotor->Align_Ctrl.O_F_Align_Angle;
            Math_SinCos_F(&pMotor->PMSM_Elec.TG_Triangle_Est);
        }
        else if (pMotor->Motor_Loop_Mode == MOTOR_LOOP_OPEN)
        {
            pMotor->IF_Ctrl.I_F_IF_Est_Angle = pMotor->MCFOC_EST_TG_Triangle.F_Angle + pMotor->MCFOC_EST_TG_Triangle_Comp.F_Angle;
            MATH_ANGLE_MOD_F(pMotor->IF_Ctrl.I_F_IF_Est_Angle);
            MCFOC_IF_CurrentLoop_F(&pMotor->IF_Ctrl, &pMotor->PMSM_Elec, &pMotor->PMSM_Para);

            pMotor->PMSM_Elec.TG_Triangle_Est.F_Angle = pMotor->IF_Ctrl.O_F_IF_Angle;
            Math_SinCos_F(&pMotor->PMSM_Elec.TG_Triangle_Est);
        }
        else if (pMotor->Motor_Loop_Mode == MOTOR_LOOP_CLOSE)
        {
            pMotor->PMSM_Elec.TG_Triangle_Est  = pMotor->MCFOC_EST_TG_Triangle;
            pMotor->PMSM_Elec.TG_Triangle_Comp = pMotor->MCFOC_EST_TG_Triangle_Comp;
        }

        MCFOC_PMSM_Park_F(&pMotor->PMSM_Elec);
        MCFOC_CurrentLoop_F(&pMotor->Current_Ctrl, &pMotor->PMSM_Elec);
        
        MCFOC_Run_Flow_PWM_Set(&pMotor->SVPWM_Ctrl, &pMotor->PMSM_Elec, &pMotor->PMSM_Para);

        HAL_MC_PWM_Output_Enable();
    }
    else
    {
        HAL_MC_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_BRAKE;
    }
}

/**
 * @brief  电机 Brake 阶段
 * @param  pMotor  电机任务结构体指针
 */
void MCFOC_Brake_Flow_F(ST_MCFOC_TASK_F* pMotor)
{
    if (pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        HAL_MC_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
    else
    {
        HAL_MC_PWM_Output_Disable();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**
 * @brief  FOC 速度环任务（1ms）
 * @param  motor_num  电机编号
 */
void MCFOC_Speed_Flow_F(Q32U_ motor_num)
{
    ST_MCFOC_TASK_F* pMotor = pMCFOC_Task_F[motor_num];

    Q32U_ temp_tmp = 0U;
    HAL_MC_ADC_Read_Temp(&temp_tmp);

    Motor_Parameter_API_F(pMotor);

    MCFOC_PMSM_Para_Adapt_F(&pMotor->PMSM_Filter, &pMotor->PMSM_Elec, &pMotor->PMSM_Para);
    MCFOC_EST_EMF_Adapt_F(&pMotor->EMF_Ctrl, &pMotor->PMSM_Para);
    MCFOC_EST_SMO_Adapt_F(&pMotor->SMO_Ctrl, &pMotor->PMSM_Elec, &pMotor->PMSM_Para);
    MCFOC_EST_FLUX_Adapt_F(&pMotor->FLUX_Ctrl, &pMotor->PMSM_Elec, &pMotor->PMSM_Para);
    MCFOC_SevFiv_Check_F(&pMotor->SVPWM_Ctrl, &pMotor->PMSM_Elec);

    pMotor->Motor_Error.I_Q14U_IsRef_pu          = (Q32I_)(Q14U_MAX_F * MATH_SQRTADD_F(pMotor->Current_Ctrl.I_F_IdRef, pMotor->Current_Ctrl.I_F_IqRef));
    pMotor->Motor_Error.I_Q14U_Iphase_A_Max_pu   = (Q32I_)(Q14U_MAX_F * pMotor->PMSM_Filter.Max_Ia.O_F_MAX_Out);
    pMotor->Motor_Error.I_Q14U_Iphase_B_Max_pu   = (Q32I_)(Q14U_MAX_F * pMotor->PMSM_Filter.Max_Ib.O_F_MAX_Out);
    pMotor->Motor_Error.I_Q14U_Iphase_C_Max_pu   = (Q32I_)(Q14U_MAX_F * pMotor->PMSM_Filter.Max_Ic.O_F_MAX_Out);
    pMotor->Motor_Error.I_Q14U_Es_pu             = (Q32I_)(Q14U_MAX_F * pMotor->PMSM_Filter.Mean_Es.O_F_MEAN_Out);

    pMotor->Motor_Error.I_Q14U_Vbus_pu           = (Q32I_)(Q14U_MAX_F * pMotor->PMSM_Elec.O_F_Vbus);
    pMotor->Motor_Error.I_Q14U_Iphase_Max_pu     = MATH_MAX_T(pMotor->Motor_Error.I_Q14U_Iphase_A_Max_pu, MATH_MAX_T(pMotor->Motor_Error.I_Q14U_Iphase_B_Max_pu, pMotor->Motor_Error.I_Q14U_Iphase_C_Max_pu));
    pMotor->Motor_Error.I_Q14U_Temp_ADC          = temp_tmp;
    pMotor->Motor_Error.I_Q14U_Speed_pu          = (Q32I_)(Q14U_MAX_F * MATH_ABS_F(pMotor->PMSM_Elec.O_F_Freq));
    pMotor->Motor_Error.I_Q14U_Ibus_pu           = (Q32I_)(Q14U_MAX_F * pMotor->PMSM_Elec.O_F_Ibus_10ms);
    /* 当前屏蔽 1ms 故障任务，改用中断内快速故障 */
//    MC_Error_Speed_Flow(&pMotor->Motor_Error, ((pMotor->Motor_Flow >= MOTOR_STATE_BOOT) && (pMotor->Motor_Flow <= MOTOR_STATE_BRAKE))); */
//    MC_Error_Speed_Flow_FOC(&pMotor->Motor_Error, ((pMotor->Motor_Flow >= MOTOR_STATE_BOOT) && (pMotor->Motor_Flow <= MOTOR_STATE_BRAKE))); */

    if (HAL_MC_PWM_Brake_Read())
    {
        HAL_MC_PWM_Brake_Clear();
        MC_Error_Short_Flow(&pMotor->Motor_Error);
    }

    /* FOC 转速环任务 */
    if (pMotor->Motor_Flow == MOTOR_STATE_RUN)
    {
        if (pMotor->Motor_Loop_Mode == MOTOR_LOOP_ALIGN)
        {
            MCFOC_ALIGN_SpeedLoop_F(&pMotor->Align_Ctrl);
            pMotor->Current_Ctrl.I_F_IdRef = pMotor->Align_Ctrl.O_F_Align_IdRef;
            pMotor->Current_Ctrl.I_F_IqRef = 0.0f;

            if (pMotor->Align_Ctrl.O_Q32U_Stand_Flag == 1U)
            {
#if (HW_FUN_MC_MOTOR_OPENLOOP_MODE == HW_FUN_MC_MOTOR_OPENLOOP_IF)
                pMotor->Motor_Loop_Mode = MOTOR_LOOP_OPEN;
#elif (HW_FUN_MC_MOTOR_OPENLOOP_MODE == HW_FUN_MC_MOTOR_OPENLOOP_FLUX)
                pMotor->Motor_Loop_Mode = MOTOR_LOOP_CLOSE;
#endif
            }
        }
        else if (pMotor->Motor_Loop_Mode == MOTOR_LOOP_OPEN)
        {
            MCFOC_IF_SpeedLoop_F(&pMotor->IF_Ctrl, &pMotor->PMSM_Elec);
            pMotor->Current_Ctrl.I_F_IdRef = pMotor->IF_Ctrl.O_F_IF_IdRef;
            pMotor->Current_Ctrl.I_F_IqRef = pMotor->IF_Ctrl.O_F_IF_IqRef;

            if (pMotor->IF_Ctrl.O_Q32U_Switch_Flag == 1U)
            {
                Ramp_Init_F(&pMotor->Freq_Ctrl.Ramp_FREQ, pMotor->IF_Ctrl.Ramp_IF_FREQ.O_F_Output);
                PID_Sat_Init_F(&pMotor->Freq_Ctrl.PID_FREQ, pMotor->IF_Ctrl.O_F_IF_IqRef);
                pMotor->Motor_Loop_Mode = MOTOR_LOOP_CLOSE;
            }
        }
        else if (pMotor->Motor_Loop_Mode == MOTOR_LOOP_CLOSE)
        {
            MCFOC_SpeedLoop_F(&pMotor->Freq_Ctrl, &pMotor->PMSM_Elec, &pMotor->PMSM_Para);
            pMotor->Current_Ctrl.I_F_IdRef = pMotor->Freq_Ctrl.O_F_FREQ_IdRef;
            pMotor->Current_Ctrl.I_F_IqRef = pMotor->Freq_Ctrl.O_F_FREQ_IqRef;
        }
    }
    else if (pMotor->Motor_Flow == MOTOR_STATE_BRAKE)
    {
        /* 刹车阶段暂不处理 */
    }
}

/**
 * @brief  FOC 电流中断任务（PWM 周期）
 * @param  motor_num  电机编号
 */
void MCFOC_Current_Flow_F(Q32U_ motor_num)
{
    ST_MCFOC_TASK_F* pMotor = pMCFOC_Task_F[motor_num];

    Q32U_ vbus_tmp = 0U;
    HAL_MC_ADC_Read_Vbus(&vbus_tmp);

    if (pMotor->Motor_Error.Motor_Error_Flag.all != 0U)
    {
        pMotor->Motor_Flag.bit.motor_enable_flag = 0U;
    }

    Motor_Flow_Function_F[pMotor->Motor_Flow](pMotor);
    
    pMotor->PMSM_Filter.Mean_Freq.I_F_MEAN_In = pMotor->MCFOC_EST_Freq;
    pMotor->PMSM_Filter.Mean_Vbus.I_F_MEAN_In = 0.0002442f * ((float)vbus_tmp);
    pMotor->PMSM_Filter.Mean_Ibus.I_F_MEAN_In = MATH_ABS_F(pMotor->PMSM_Elec.I_F_Ibus);
    pMotor->PMSM_Filter.Mean_Id.I_F_MEAN_In   = pMotor->PMSM_Elec.V_F_Id_Real;
    pMotor->PMSM_Filter.Mean_Iq.I_F_MEAN_In   = pMotor->PMSM_Elec.V_F_Iq_Real;
    pMotor->PMSM_Filter.Mean_Ud.I_F_MEAN_In   = pMotor->PMSM_Elec.V_F_Ud_Real;
    pMotor->PMSM_Filter.Mean_Uq.I_F_MEAN_In   = pMotor->PMSM_Elec.V_F_Uq_Real;
    pMotor->PMSM_Filter.Mean_Es.I_F_MEAN_In   = MATH_SQRTADD_F(pMotor->EMF_Ctrl.O_F_EMF_Ealfa, pMotor->EMF_Ctrl.O_F_EMF_Ebeta);

    MEAN_Cal_F(&pMotor->PMSM_Filter.Mean_Freq);
    MEAN_Cal_F(&pMotor->PMSM_Filter.Mean_Vbus);
    MEAN_Cal_F(&pMotor->PMSM_Filter.Mean_Ibus);
    MEAN_Cal_F(&pMotor->PMSM_Filter.Mean_Id);
    MEAN_Cal_F(&pMotor->PMSM_Filter.Mean_Iq);
    MEAN_Cal_F(&pMotor->PMSM_Filter.Mean_Ud);
    MEAN_Cal_F(&pMotor->PMSM_Filter.Mean_Uq);
    MEAN_Cal_F(&pMotor->PMSM_Filter.Mean_Es);

    MC_Error_Current_Flow(&pMotor->Motor_Error);
    
#if (HW_FUN_MC_RTT_ENABLE == 1U)
    JS_RTT_Data[0] = (Q16I_)(1000.0f * HW_ADC_CURRENT_MAX * pMotor->PMSM_Elec.V_F_Ia);
    JS_RTT_Data[1] = (Q16I_)(1000.0f * HW_ADC_CURRENT_MAX * pMotor->PMSM_Elec.V_F_Ib);
    JS_RTT_Data[2] = (Q16I_)(1000.0f * HW_ADC_CURRENT_MAX * pMotor->PMSM_Elec.V_F_Ic);
    JS_RTT_Data[3] = (Q16I_)(16384.0f * pMotor->PMSM_Elec.TG_Triangle_Est.F_Angle);
    
    SEGGER_RTT_Write(JS_RTT_Channel, JS_RTT_Data, sizeof(JS_RTT_Data));
#endif
}
