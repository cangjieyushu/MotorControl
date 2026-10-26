/**
 * @file    mcsq_task.c
 * @brief   方波电机任务实现
 * @author  CJYS
 * @date    2024/1/1
 *
 * 状态机各阶段：Pre → Init → Idle → Boot → Position → Run / Brake，
 * 换向算法：Flux / Bemf / Cmp。函数指针数组在 Globals 节定义。
 */

/* ======================== 1. Header ======================= */
#include "hal_mc.h"
#include "mcsq_task.h"
#include "mcsq_para.h"
#include "bsp_mc.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/** @brief 电机状态机函数指针 */
typedef void (*pMOTOR_FUN)(ST_MCSQ_TASK*);
/** @brief 高/低边 PWM 输出函数指针 */
typedef void (*pFUN_HPWMLPWM_SET)(Q32U_);

/* ======================== 4. Globals ====================== */

/**
 * @brief 定位阶段 PWM 输出表：[定位步][方向] -> 输出函数
 *        方向索引与 EM_DIRECTION 一致（CW = 0，CCW = 1）
 */
pFUN_HPWMLPWM_SET POSITION_Set[6][2] = {
    HAL_MC_POSITION_Up, HAL_MC_POSITION_Up,   /* U+ */
    HAL_MC_POSITION_Wn, HAL_MC_POSITION_Vn,   /* W- */
    HAL_MC_POSITION_Vp, HAL_MC_POSITION_Wp,   /* V+ */
    HAL_MC_POSITION_Un, HAL_MC_POSITION_Un,   /* U- */
    HAL_MC_POSITION_Wp, HAL_MC_POSITION_Vp,   /* W+ */
    HAL_MC_POSITION_Vn, HAL_MC_POSITION_Wn,   /* V- */
};

/**
 * @brief 运行阶段 PWM 输出表：[扇区][方向] -> 高/低边输出函数
 *        注释为（正向 / 反向）扇区对应的导通相
 */
pFUN_HPWMLPWM_SET HPWMLPWM_Set[6][2] = {
    HAL_MC_HPWM_LPWM_UpVn, HAL_MC_HPWM_LPWM_UpWn,   /* U+V- */
    HAL_MC_HPWM_LPWM_UpWn, HAL_MC_HPWM_LPWM_UpVn,   /* U+W- */
    HAL_MC_HPWM_LPWM_VpWn, HAL_MC_HPWM_LPWM_WpVn,   /* V+W- */
    HAL_MC_HPWM_LPWM_VpUn, HAL_MC_HPWM_LPWM_WpUn,   /* V+U- */
    HAL_MC_HPWM_LPWM_WpUn, HAL_MC_HPWM_LPWM_VpUn,   /* W+U- */
    HAL_MC_HPWM_LPWM_WpVn, HAL_MC_HPWM_LPWM_VpWn,   /* W+V- */
};

/* ======================== 5. Function Prototypes ========== */

/** @brief 电机任务指针数组（当前仅使用单电机配置） */
static ST_MCSQ_TASK* pMCSQ_Task[3] = {
    &MCSQ_Task,
    &MCSQ_Task,
    &MCSQ_Task
};

void MCSQ_Pre_Flow(ST_MCSQ_TASK* pMotor);
void MCSQ_Init_Flow(ST_MCSQ_TASK* pMotor);
void MCSQ_Idle_Flow(ST_MCSQ_TASK* pMotor);
void MCSQ_Boot_Flow(ST_MCSQ_TASK* pMotor);
void MCSQ_Position_Flow(ST_MCSQ_TASK* pMotor);
void MCSQ_Run_Flow(ST_MCSQ_TASK* pMotor);
void MCSQ_Brake_Flow(ST_MCSQ_TASK* pMotor);

void MCSQ_Switch_Flux_Flow(ST_MCSQ_TASK* pMotor);
void MCSQ_Switch_Bemf_Flow(ST_MCSQ_TASK* pMotor);
void MCSQ_Switch_Cmp_Flow(ST_MCSQ_TASK* pMotor);

/**
 * @brief 状态机分发表：按 EM_MOTOR_STATE 顺序调用对应阶段函数
 *        索引对应关系：PRE / INIT / IDLE / BOOT / POSITION / RUN / BRAKE
 */
pMOTOR_FUN Motor_Flow_Function[MOTOR_STATE_BRAKE + 1U] = {
    MCSQ_Pre_Flow,
    MCSQ_Init_Flow,
    MCSQ_Idle_Flow,
    MCSQ_Boot_Flow,
    MCSQ_Position_Flow,
    MCSQ_Run_Flow,
    MCSQ_Brake_Flow
};

/**
 * @brief 换向算法分发表：按 EM_SWITCH_MATH 顺序调用
 *        索引：FLUX / BEMF / CMP
 */
pMOTOR_FUN Motor_Math_Function[SWITCH_CMP + 1U] = {
    MCSQ_Switch_Flux_Flow,
    MCSQ_Switch_Bemf_Flow,
    MCSQ_Switch_Cmp_Flow
};

/* ======================== 6. Functions ==================== */

/**
 * @brief  电机 Pre 阶段（复位各子模块 / 上电初始化）
 * @param  pMotor  电机任务结构体指针
 */
void MCSQ_Pre_Flow(ST_MCSQ_TASK* pMotor)
{
    if (pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        MC_Error_Init_Flow(&pMotor->Motor_Error);

        HAL_MC_PWM_Preload_Enable();
        HAL_MC_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_Init_PWMCount);
        MCSQ_Init(&pMotor->MCSQ_CTRL);

        HAL_MC_HPWM_LPWM_Close();
        HAL_MC_ADC_Soft_Trigger();
        pMotor->Motor_Flow = MOTOR_STATE_INIT;
    }
    else
    {
        HAL_MC_HPWM_LPWM_Close();
    }
}

/**
 * @brief  电机 Init 阶段（电流偏置检测）
 * @param  pMotor  电机任务结构体指针
 */
void MCSQ_Init_Flow(ST_MCSQ_TASK* pMotor)
{
    if (pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        switch (MCSQ_Offset_Check(&pMotor->MCSQ_CTRL.MCSQ_OFFSET, &pMotor->MCSQ_CTRL.MCSQ_BLDC, pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Iphase_ADC))
        {
            case ING:
            {
                if ((HAL_MC_PWM_Count_Read() + pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_ADC_Solve_Value) < pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_Init_PWMCount)
                {
                    HAL_MC_ADC_Soft_Trigger();
                }
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
        HAL_MC_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_High_PWMCount);
        HAL_MC_HPWM_LPWM_Close();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**
 * @brief  电机 Idle 阶段（顺风检测 / 自举前准备）
 * @param  pMotor  电机任务结构体指针
 */
void MCSQ_Idle_Flow(ST_MCSQ_TASK* pMotor)
{
    Q32U_ Q32U_pwm_count_tmp;

    if (pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        switch (MCSQ_Flying_Check(&pMotor->MCSQ_CTRL.MCSQ_FLYING, &pMotor->MCSQ_CTRL.MCSQ_BLDC, HAL_MC_HALL_TIM_Count_Read()))
        {
            case ING:
            {
                Q32U_pwm_count_tmp = HAL_MC_PWM_Count_Read();
                if ((Q32U_pwm_count_tmp + pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_ADC_Solve_Value) < pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_Init_PWMCount)
                {
                    HAL_MC_ADC_Soft_Trigger();
                }
                break;
            }
            case SUCS:
            {
                HAL_MC_PWM_Preload_Disable();
                MCSQ_Flying_Init(&pMotor->MCSQ_CTRL);
                HAL_MC_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_High_PWMCount);
                HPWMLPWM_Set[pMotor->MCSQ_CTRL.MCSQ_BLDC.Sector][pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set](pMotor->MCSQ_CTRL.PWM_CTRL.O_Q32U_Duty_PWMCount);
                pMotor->Motor_Flow = MOTOR_STATE_RUN;
                break;
            }
            case FAIL:
            {
                HAL_MC_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_Init_PWMCount);
                HAL_MC_ADC_TrigTime_Set(Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BOOT.P_Q14U_Boot_Duty_Set * pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_Init_PWMCount));
                HAL_MC_HPWM_LPWM_LOpen(Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BOOT.P_Q14U_Boot_Duty_Set * pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_Init_PWMCount));
                pMotor->Motor_Flow = MOTOR_STATE_BOOT;
                break;
            }
            default: break;
        }
    }
    else
    {
        HAL_MC_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_High_PWMCount);
        HAL_MC_HPWM_LPWM_Close();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**
 * @brief  电机 Boot 阶段（自举电容充电）
 * @param  pMotor  电机任务结构体指针
 */
void MCSQ_Boot_Flow(ST_MCSQ_TASK* pMotor)
{
    if (pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        switch (MCSQ_Boot_Check(&pMotor->MCSQ_CTRL.MCSQ_BOOT, &pMotor->MCSQ_CTRL.MCSQ_BLDC))
        {
            case ING:
            {
                HAL_MC_HPWM_LPWM_LOpen(Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BOOT.P_Q14U_Boot_Duty_Set * pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_Init_PWMCount));
                break;
            }
            case SUCS:
            {
                pMotor->MCSQ_CTRL.MCSQ_POSITION.V_Q14U_Position_Duty_PWMCount =
                    Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BLDC.P_Q14U_Vbus_Max_pu * pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_Init_PWMCount
                                / pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q14U_Vbus_pu * pMotor->MCSQ_CTRL.MCSQ_POSITION.P_Q14U_Position_Duty_Set);

                HAL_MC_ADC_TrigTime_Set(pMotor->MCSQ_CTRL.MCSQ_POSITION.V_Q14U_Position_Duty_PWMCount - 2U * pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_ADC_Sample_Value);
                POSITION_Set[pMotor->MCSQ_CTRL.MCSQ_POSITION.V_Q32U_Position_cnt][pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set](pMotor->MCSQ_CTRL.MCSQ_POSITION.V_Q14U_Position_Duty_PWMCount);
                pMotor->Motor_Flow = MOTOR_STATE_POSITION;
                break;
            }
            case FAIL:
            {
                break;
            }
            default: break;
        }
    }
    else
    {
        HAL_MC_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_High_PWMCount);
        HAL_MC_HPWM_LPWM_Close();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**
 * @brief  电机 Position 阶段（6 步脉冲定位）
 * @param  pMotor  电机任务结构体指针
 */
void MCSQ_Position_Flow(ST_MCSQ_TASK* pMotor)
{
    if (pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        HAL_MC_HPWM_LPWM_Close();

        switch (MCSQ_Pluse_Positon(&pMotor->MCSQ_CTRL.MCSQ_POSITION, &pMotor->MCSQ_CTRL.MCSQ_BLDC, pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Iphase_ADC))
        {
            case ING:
            {
                POSITION_Set[pMotor->MCSQ_CTRL.MCSQ_POSITION.V_Q32U_Position_cnt][pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set](pMotor->MCSQ_CTRL.MCSQ_POSITION.V_Q14U_Position_Duty_PWMCount);
                break;
            }
            case SUCS:
            {
                HAL_MC_ADC_TrigTime_Set(pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_ADC_Delay_Value);
                HAL_MC_PWM_Preload_Disable();
                HAL_MC_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_Low_PWMCount);
                pMotor->Motor_Flow = MOTOR_STATE_RUN;
                break;
            }
            case FAIL:
            {
                pMotor->Motor_Error.Motor_Error_Flag.bit.position_error = 1U;
                pMotor->Motor_Flow = MOTOR_STATE_PRE;
                break;
            }
            default: break;
        }
    }
    else
    {
        HAL_MC_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_High_PWMCount);
        HAL_MC_HPWM_LPWM_Close();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
}

/**
 * @brief  磁链换向处理
 * @param  pMotor  电机任务结构体指针
 */
void MCSQ_Switch_Flux_Flow(ST_MCSQ_TASK* pMotor)
{
    MCSQ_FLUX(&pMotor->MCSQ_CTRL.MCSQ_FLUX, &pMotor->MCSQ_CTRL.MCSQ_BLDC);
    if (pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow == SQUARE_CROSS_SUCC)
    {
        MCSQ_Freq_Cal(&pMotor->MCSQ_CTRL.MCSQ_BLDC, HAL_MC_HALL_TIM_Count_Read());
        HAL_MC_SWITCH_TIM_Delay(pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_TIM_Delay_Value);
    }
}

/**
 * @brief  BEMF 换向处理
 * @param  pMotor  电机任务结构体指针
 */
void MCSQ_Switch_Bemf_Flow(ST_MCSQ_TASK* pMotor)
{
    MCSQ_BEMF(&pMotor->MCSQ_CTRL.MCSQ_BEMF, &pMotor->MCSQ_CTRL.MCSQ_BLDC);
    if (pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow == SQUARE_CROSS_SUCC)
    {
        MCSQ_Freq_Cal(&pMotor->MCSQ_CTRL.MCSQ_BLDC, HAL_MC_HALL_TIM_Count_Read());
        HAL_MC_SWITCH_TIM_Delay(Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BEMF.P_Q14U_Bemf_Delay_Coeff * pMotor->MCSQ_CTRL.MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_Filter));
    }
}

/**
 * @brief  CMP 换向处理（预留）
 * @param  pMotor  电机任务结构体指针
 */
void MCSQ_Switch_Cmp_Flow(ST_MCSQ_TASK* pMotor)
{
    (void)pMotor;
}

/**
 * @brief  电机 Run 阶段（闭环 / 开环控制、采样、换向）
 * @param  pMotor  电机任务结构体指针
 */
void MCSQ_Run_Flow(ST_MCSQ_TASK* pMotor)
{
    Q32U_ Q32U_pwm_count_tmp;

    if (pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        if (pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Iphase_ADC > pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Iphase_ADC_Offset)
        {
            pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q14U_Iphase_pu = Q16I_LFT_02(pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Iphase_ADC - pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Iphase_ADC_Offset);
        }
        else
        {
            pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q14U_Iphase_pu = 0U;
        }

        if (pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow == SQUARE_DIAG_ING)
        {
            MCSQ_DIAG(&pMotor->MCSQ_CTRL.MCSQ_DIAG, &pMotor->MCSQ_CTRL.MCSQ_BLDC);
        }
        else if (pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow == SQUARE_CROSS_ING)
        {
            Motor_Math_Function[pMotor->MCSQ_CTRL.MCSQ_BLDC.SW_Math](pMotor);
        }

        MCSQ_Ibus_Cal(&pMotor->MCSQ_CTRL);

        Q32U_pwm_count_tmp = HAL_MC_PWM_Count_Read();
        if (((Q32U_pwm_count_tmp + 2U * pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_ADC_Sample_Value) < pMotor->MCSQ_CTRL.PWM_CTRL.O_Q32U_Duty_PWMCount) &&
            ((Q32U_pwm_count_tmp + pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_ADC_Sample_Value + pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_ADC_Solve_Value) < pMotor->MCSQ_CTRL.PWM_CTRL.O_Q32U_PWMCount_Set))
        {
            HAL_MC_ADC_Soft_Trigger();
        }
        else
        {
            pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Iphase.I_Q14I_LPF_In = pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q14U_Iphase_pu;
            LPF_Cal_T(&pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Iphase);

            pMotor->MCSQ_CTRL.PID_Iphase.I_Q14I_Rf = pMotor->MCSQ_CTRL.MCSQ_BLDC.P_Q14U_Iphase_Max_pu;
            pMotor->MCSQ_CTRL.PID_Iphase.I_Q14I_Fb = pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Iphase.O_Q14I_LPF_Out;
            PID_Inc_Cal_T(&pMotor->MCSQ_CTRL.PID_Iphase);
            pMotor->MCSQ_CTRL.PWM_CTRL.I_Q14U_Duty_Iphase = pMotor->MCSQ_CTRL.PID_Iphase.O_Q14I_Output;

            MCSQ_PWM_Freq_Switch(&pMotor->MCSQ_CTRL.PWM_CTRL);

            HAL_MC_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL.O_Q32U_PWMCount_Set);
            HPWMLPWM_Set[pMotor->MCSQ_CTRL.MCSQ_BLDC.Sector][pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set](pMotor->MCSQ_CTRL.PWM_CTRL.O_Q32U_Duty_PWMCount);

            /* 电流中断故障接口 */
            if (pMotor->Motor_Error.I_Q14U_Iphase_Max_pu < pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q14U_Iphase_pu)
            {
                pMotor->Motor_Error.I_Q14U_Iphase_Max_pu = pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q14U_Iphase_pu;
            }
            MC_Error_Current_Flow(&pMotor->Motor_Error);
        }
    }
    else
    {
        HAL_MC_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_High_PWMCount);
        HAL_MC_HPWM_LPWM_Close();
        pMotor->Motor_Flow = MOTOR_STATE_BRAKE;
    }
}

/**
 * @brief  电机 Brake 阶段
 * @param  pMotor  电机任务结构体指针
 */
void MCSQ_Brake_Flow(ST_MCSQ_TASK* pMotor)
{
    if (pMotor->Motor_Flag.bit.motor_enable_flag == 1U)
    {
        HAL_MC_PWM_Freq_Set(pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_Init_PWMCount);
        HAL_MC_HPWM_LPWM_Close();
        pMotor->Motor_Flow = MOTOR_STATE_PRE;
    }
    else
    {
        if (pMotor->MCSQ_CTRL.MCSQ_BRAKE.O_Q32U_Brake_Finish_Flag == 1U)
        {
            pMotor->Motor_Flow = MOTOR_STATE_PRE;
            HAL_MC_HPWM_LPWM_Close();
        }
        else
        {
            HAL_MC_HPWM_LPWM_LOpen(Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BRAKE.O_Q14U_Brake_Duty_Set * pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_High_PWMCount));
        }
    }
}

/**
 * @brief  方波 1ms 任务（状态机 / 保护 / 速度/电流环）
 * @param  motor_num  电机编号
 */
void MCSQ_Speed_Flow(Q32U_ motor_num)
{
    ST_MCSQ_TASK* pMotor = pMCSQ_Task[motor_num];
    Q32U_ vbus;
    Q32U_ temp;

    if (HAL_MC_PWM_Brake_Read())
    {
        HAL_MC_PWM_Brake_Clear();
        MC_Error_Short_Flow(&pMotor->Motor_Error);
    }

    Motor_Parameter_API_SQ(pMotor);

    HAL_MC_ADC_Read_System(&vbus, &temp);
    pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Vbus_ADC.I_Q14I_LPF_In = (Q32I_)vbus;
    pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Temp_ADC.I_Q14I_LPF_In = (Q32I_)temp;
    LPF_Cal_T(&pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Vbus_ADC);
    LPF_Cal_T(&pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Temp_ADC);

    pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q14U_Vbus_pu = Q16I_LFT_02(pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Vbus_ADC.O_Q14I_LPF_Out);

    /* 1ms 故障接口 */
    pMotor->Motor_Error.I_Q14U_Vbus_pu  = pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q14U_Vbus_pu;
    pMotor->Motor_Error.I_Q14U_Speed_pu = pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Freq.O_Q14I_LPF_Out;
    pMotor->Motor_Error.I_Q14U_Ibus_pu  = pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Ibus.O_Q14I_LPF_Out;
    pMotor->Motor_Error.I_Q14U_Temp_ADC = pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Temp_ADC.O_Q14I_LPF_Out;

    MC_Error_Speed_Flow(&pMotor->Motor_Error, ((pMotor->Motor_Flow >= MOTOR_STATE_BOOT) && (pMotor->Motor_Flow <= MOTOR_STATE_BRAKE)));

    if (pMotor->Motor_Flow == MOTOR_STATE_RUN)
    {
        if (pMotor->Motor_Flag.bit.motor_speed_flag == 1U)
        {
            pMotor->MCSQ_CTRL.Ramp_Freq.P_Q14I_Target = Q32I_RHT_14(pMotor->MCSQ_CTRL.PWM_CTRL.I_Q14U_Duty_VR * pMotor->MCSQ_CTRL.PWM_CTRL.P_Q14U_Motor_Freq_Max);

            Ramp_Cal_T(&pMotor->MCSQ_CTRL.Ramp_Freq);

            pMotor->MCSQ_CTRL.PID_Freq.I_Q14I_Rf = pMotor->MCSQ_CTRL.Ramp_Freq.O_Q14I_Output;
            pMotor->MCSQ_CTRL.PID_Freq.I_Q14I_Fb = pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Freq.O_Q14I_LPF_Out;
            PID_Inc_Cal_T(&pMotor->MCSQ_CTRL.PID_Freq);

            pMotor->MCSQ_CTRL.PWM_CTRL.I_Q14U_Duty_Freq = pMotor->MCSQ_CTRL.PID_Freq.O_Q14I_Output;
        }
        else
        {
            pMotor->MCSQ_CTRL.PWM_CTRL.I_Q14U_Duty_Freq = Q32I_RHT_14(pMotor->MCSQ_CTRL.PWM_CTRL.I_Q14U_Duty_VR * pMotor->MCSQ_CTRL.PWM_CTRL.P_Q14U_Duty_Max);
        }

        if (pMotor->Motor_Flag.bit.motor_busA_flag == 1U)
        {
            pMotor->MCSQ_CTRL.PID_Ibus.I_Q14I_Rf = pMotor->MCSQ_CTRL.MCSQ_BLDC.P_Q14U_Ibus_Max_pu;
            pMotor->MCSQ_CTRL.PID_Ibus.I_Q14I_Fb = pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Ibus.O_Q14I_LPF_Out;
            PID_Inc_Cal_T(&pMotor->MCSQ_CTRL.PID_Ibus);

            pMotor->MCSQ_CTRL.PWM_CTRL.I_Q14U_Duty_Ibus = pMotor->MCSQ_CTRL.PID_Ibus.O_Q14I_Output;
        }
        else if (pMotor->Motor_Flag.bit.motor_busP_flag == 1U)
        {
            pMotor->MCSQ_CTRL.PID_Ibus.I_Q14I_Rf = Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BLDC.P_Q14U_Ibus_Max_pu * pMotor->MCSQ_CTRL.MCSQ_BLDC.P_Q14U_Vbus_Max_pu);
            pMotor->MCSQ_CTRL.PID_Ibus.I_Q14I_Fb = Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Ibus.O_Q14I_LPF_Out * pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q14U_Vbus_pu);
            PID_Inc_Cal_T(&pMotor->MCSQ_CTRL.PID_Ibus);

            pMotor->MCSQ_CTRL.PWM_CTRL.I_Q14U_Duty_Ibus = pMotor->MCSQ_CTRL.PID_Ibus.O_Q14I_Output;
        }
        else
        {
            pMotor->MCSQ_CTRL.PWM_CTRL.I_Q14U_Duty_Ibus = pMotor->MCSQ_CTRL.PWM_CTRL.P_Q14U_Duty_Max;
        }

        if (MCSQ_Stall_Check(&pMotor->MCSQ_CTRL.STALL_CTRL, &pMotor->MCSQ_CTRL) == SUCS)
        {
            pMotor->Motor_Error.Motor_Error_Flag.bit.rotor_stall = 1U;
        }
    }
    else if (pMotor->Motor_Flow == MOTOR_STATE_BRAKE)
    {
        MCSQ_Brake(&pMotor->MCSQ_CTRL.MCSQ_BRAKE, &pMotor->MCSQ_CTRL.PWM_CTRL);
    }
}

/**
 * @brief  方波电流中断任务（ADC 采样 / 状态机单步）
 * @param  motor_num  电机编号
 */
void MCSQ_Current_Flow(Q32U_ motor_num)
{
    ST_MCSQ_TASK* pMotor = pMCSQ_Task[motor_num];

    if (pMotor->Motor_Error.Motor_Error_Flag.all != 0U)
    {
        pMotor->Motor_Flag.bit.motor_enable_flag = 0U;
    }

    if (pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set == CW)
    {
        HAL_MC_ADC_Read_Motor(&pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Bemf_ADC_tmp[0],
                              &pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Bemf_ADC_tmp[1],
                              &pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Bemf_ADC_tmp[2],
                              &pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Iphase_ADC);
    }
    else
    {
        HAL_MC_ADC_Read_Motor(&pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Bemf_ADC_tmp[0],
                              &pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Bemf_ADC_tmp[2],
                              &pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Bemf_ADC_tmp[1],
                              &pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Iphase_ADC);
    }

    Motor_Flow_Function[pMotor->Motor_Flow](pMotor);
	
#if (HW_FUN_MC_RTT_ENABLE == 1U)
    JS_RTT_Data[0] = (Q16I_)pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Bemf_ADC_tmp[0];
    JS_RTT_Data[1] = (Q16I_)pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Bemf_ADC_tmp[1];
    JS_RTT_Data[2] = (Q16I_)pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Bemf_ADC_tmp[2];
    JS_RTT_Data[3] = (Q16I_)pMotor->MCSQ_CTRL.MCSQ_BLDC.V_Q12U_Iphase_ADC;
    
    SEGGER_RTT_Write(JS_RTT_Channel, JS_RTT_Data, sizeof(JS_RTT_Data));
#endif
}

/**
 * @brief  方波换向中断任务（推进换向状态）
 * @param  motor_num  电机编号
 */
void MCSQ_Switch_Flow(Q32U_ motor_num)
{
    ST_MCSQ_TASK* pMotor = pMCSQ_Task[motor_num];

    if (pMotor->Motor_Flow == MOTOR_STATE_RUN)
    {
        if (pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow == SQUARE_CROSS_SUCC)
        {
            HAL_MC_SWITCH_TIM_Stop();
            pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow = SQUARE_SWITCH_SUCC;
            pMotor->MCSQ_CTRL.MCSQ_BLDC.Sector = Next_Sector[pMotor->MCSQ_CTRL.MCSQ_BLDC.Sector];
            HPWMLPWM_Set[pMotor->MCSQ_CTRL.MCSQ_BLDC.Sector][pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set](pMotor->MCSQ_CTRL.PWM_CTRL.O_Q32U_Duty_PWMCount);
            HAL_MC_SWITCH_TIM_Delay(pMotor->MCSQ_CTRL.PWM_CTRL.P_Q32U_TIM_Delay_Value);
        }
        else if (pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow == SQUARE_SWITCH_SUCC)
        {
            HAL_MC_SWITCH_TIM_Stop();
            pMotor->MCSQ_CTRL.MCSQ_BLDC.SQ_Flow = SQUARE_DIAG_ING;
        }
    }
    else
    {
        HAL_MC_SWITCH_TIM_Stop();
    }
}

/**
 * @brief  方波 ADC 触发（供硬件定时器调用）
 * @param  motor_num  电机编号
 */
void MCSQ_ADC_Trig_Flow(Q32U_ motor_num)
{
    (void)motor_num;
    HAL_MC_ADC_Soft_Trigger();
}
