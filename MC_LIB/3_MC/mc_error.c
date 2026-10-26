/**
 * @file    mc_error.c
 * @brief   电机故障检测与确认实现
 * @author  CJYS
 * @date    2024/1/1
 *
 * 三个层级：
 *   - Speed_Flow  ：1ms 任务，处理慢变保护
 *   - Current_Flow：电流中断任务，处理快变保护
 *   - Short_Flow / Init_Flow：硬件刹车短路计数
 */

/* ======================== 1. Header ======================= */
#include "mc_error.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  1ms 任务：常规电压/电流/温度/速度/功率保护
 * @param  pError        故障结构体指针
 * @param  Q32U_Enable   使能
 */
void MC_Error_Speed_Flow(ST_MOTOR_ERROR* pError, Q32U_ Q32U_Enable)
{
    pError->Over_Voltage.Check_Flag.bit.Enable              = 1U;
    pError->Over_Voltage.Check_Flag.bit.Condition_Set       = (pError->I_Q14U_Vbus_pu >= pError->Over_Voltage.P_Q14I_Check_TL);
    pError->Over_Voltage.Check_Flag.bit.Condition_Clear     = (pError->I_Q14U_Vbus_pu <= pError->Over_Voltage.P_Q14I_Clear_TL);
    pError->Motor_Error_Flag.bit.over_voltage               = Check_Cal(&pError->Over_Voltage, pError->Motor_Error_Flag.bit.over_voltage);

    pError->Low_Voltage.Check_Flag.bit.Enable               = Q32U_Enable;
    pError->Low_Voltage.Check_Flag.bit.Condition_Set        = (pError->I_Q14U_Vbus_pu <= pError->Low_Voltage.P_Q14I_Check_TL);
    pError->Motor_Error_Flag.bit.low_voltage                = Check_Cal(&pError->Low_Voltage, pError->Motor_Error_Flag.bit.low_voltage);

    pError->Over_Current1.Check_Flag.bit.Enable             = Q32U_Enable;
    pError->Over_Current1.Check_Flag.bit.Condition_Set      = (pError->I_Q14U_Iphase_Max_pu >= pError->Over_Current1.P_Q14I_Check_TL);
    pError->Motor_Error_Flag.bit.over_current1              = Check_Cal(&pError->Over_Current1, pError->Motor_Error_Flag.bit.over_current1);

    pError->Over_Current2.Check_Flag.bit.Enable             = Q32U_Enable;
    pError->Over_Current2.Check_Flag.bit.Condition_Set      = (pError->I_Q14U_Iphase_Max_pu >= pError->Over_Current2.P_Q14I_Check_TL);
    pError->Motor_Error_Flag.bit.over_current2              = Check_Cal(&pError->Over_Current2, pError->Motor_Error_Flag.bit.over_current2);

    pError->Over_Current3.Check_Flag.bit.Enable             = Q32U_Enable;
    pError->Over_Current3.Check_Flag.bit.Condition_Set      = (pError->I_Q14U_Iphase_Max_pu >= pError->Over_Current3.P_Q14I_Check_TL);
    pError->Motor_Error_Flag.bit.over_current3              = Check_Cal(&pError->Over_Current3, pError->Motor_Error_Flag.bit.over_current3);

    pError->Over_Temp.Check_Flag.bit.Enable                 = 1U;
    pError->Over_Temp.Check_Flag.bit.Condition_Set          = (pError->I_Q14U_Temp_ADC <= pError->Over_Temp.P_Q14I_Check_TL);
    pError->Over_Temp.Check_Flag.bit.Condition_Clear        = (pError->I_Q14U_Temp_ADC >= pError->Over_Temp.P_Q14I_Clear_TL);
    pError->Motor_Error_Flag.bit.over_temp                  = Check_Cal(&pError->Over_Temp, pError->Motor_Error_Flag.bit.over_temp);

    pError->Low_Temp.Check_Flag.bit.Enable                  = 1U;
    pError->Low_Temp.Check_Flag.bit.Condition_Set           = (pError->I_Q14U_Temp_ADC >= pError->Low_Temp.P_Q14I_Check_TL);
    pError->Low_Temp.Check_Flag.bit.Condition_Clear         = (pError->I_Q14U_Temp_ADC <= pError->Low_Temp.P_Q14I_Clear_TL);
    pError->Motor_Error_Flag.bit.low_temp                   = Check_Cal(&pError->Low_Temp, pError->Motor_Error_Flag.bit.low_temp);

    pError->Over_Speed.Check_Flag.bit.Enable                = Q32U_Enable;
    pError->Over_Speed.Check_Flag.bit.Condition_Set         = (pError->I_Q14U_Speed_pu >= pError->Over_Speed.P_Q14I_Check_TL);
    pError->Motor_Error_Flag.bit.over_speed                 = Check_Cal(&pError->Over_Speed, pError->Motor_Error_Flag.bit.over_speed);

    pError->Low_Speed.Check_Flag.bit.Enable                 = Q32U_Enable;
    pError->Low_Speed.Check_Flag.bit.Condition_Set          = (pError->I_Q14U_Speed_pu <= pError->Low_Speed.P_Q14I_Check_TL);
    pError->Motor_Error_Flag.bit.low_speed                  = Check_Cal(&pError->Low_Speed, pError->Motor_Error_Flag.bit.low_speed);

    pError->Over_Power.Check_Flag.bit.Enable                = Q32U_Enable;
    pError->Over_Power.Check_Flag.bit.Condition_Set         = (pError->I_Q14U_Vbus_pu * pError->I_Q14U_Ibus_pu >= pError->Over_Power.P_Q14I_Check_TL);
    pError->Motor_Error_Flag.bit.over_power                 = Check_Cal(&pError->Over_Power, pError->Motor_Error_Flag.bit.over_power);

    pError->Over_Ibus.Check_Flag.bit.Enable                 = Q32U_Enable;
    pError->Over_Ibus.Check_Flag.bit.Condition_Set          = (pError->I_Q14U_Ibus_pu >= pError->Over_Ibus.P_Q14I_Check_TL);
    pError->Motor_Error_Flag.bit.over_ibus                  = Check_Cal(&pError->Over_Ibus, pError->Motor_Error_Flag.bit.over_ibus);

    pError->Fast_Over_Voltage.Check_Flag.bit.Enable         = 1U;
    pError->Fast_Over_Current.Check_Flag.bit.Enable         = 1U;

    pError->I_Q14U_Iphase_Max_pu = 0U;
}

/**
 * @brief  1ms 任务：FOC 专用保护（缺相 / 堵转 / 失步）
 * @param  pError        故障结构体指针
 * @param  Q32U_Enable   使能
 */
void MC_Error_Speed_Flow_FOC(ST_MOTOR_ERROR* pError, Q32U_ Q32U_Enable)
{
    pError->Phase_Lack_A.Check_Flag.bit.Enable              = Q32U_Enable;
    pError->Phase_Lack_A.Check_Flag.bit.Condition_Set       = ((pError->I_Q14U_Iphase_A_Max_pu <= pError->Phase_Lack_A.P_Q14I_Check_TL) && (pError->I_Q14U_IsRef_pu >= pError->Phase_Lack_A.P_Q14I_Clear_TL));
    pError->Motor_Error_Flag.bit.phase_lack_a               = Check_Cal(&pError->Phase_Lack_A, pError->Motor_Error_Flag.bit.phase_lack_a);

    pError->Phase_Lack_B.Check_Flag.bit.Enable              = Q32U_Enable;
    pError->Phase_Lack_B.Check_Flag.bit.Condition_Set       = ((pError->I_Q14U_Iphase_B_Max_pu <= pError->Phase_Lack_B.P_Q14I_Check_TL) && (pError->I_Q14U_IsRef_pu >= pError->Phase_Lack_B.P_Q14I_Clear_TL));
    pError->Motor_Error_Flag.bit.phase_lack_b               = Check_Cal(&pError->Phase_Lack_B, pError->Motor_Error_Flag.bit.phase_lack_b);

    pError->Phase_Lack_C.Check_Flag.bit.Enable              = Q32U_Enable;
    pError->Phase_Lack_C.Check_Flag.bit.Condition_Set       = ((pError->I_Q14U_Iphase_C_Max_pu <= pError->Phase_Lack_C.P_Q14I_Check_TL) && (pError->I_Q14U_IsRef_pu >= pError->Phase_Lack_C.P_Q14I_Clear_TL));
    pError->Motor_Error_Flag.bit.phase_lack_c               = Check_Cal(&pError->Phase_Lack_C, pError->Motor_Error_Flag.bit.phase_lack_c);

    pError->Rotor_Lock.Check_Flag.bit.Enable                = Q32U_Enable;
    pError->Rotor_Lock.Check_Flag.bit.Condition_Set         = ((pError->I_Q14U_IsRef_pu >= pError->Rotor_Lock.P_Q14I_Check_TL) && (pError->I_Q14U_Speed_pu <= pError->Rotor_Lock.P_Q14I_Clear_TL));
    pError->Motor_Error_Flag.bit.rotor_lock                 = Check_Cal(&pError->Rotor_Lock, pError->Motor_Error_Flag.bit.rotor_lock);

    pError->Loss_Step.Check_Flag.bit.Enable                 = Q32U_Enable;
    pError->Loss_Step.Check_Flag.bit.Condition_Set          = ((pError->I_Q14U_Es_pu <= pError->Loss_Step.P_Q14I_Check_TL) && (pError->I_Q14U_Speed_pu >= pError->Loss_Step.P_Q14I_Clear_TL));
    pError->Motor_Error_Flag.bit.loss_step                  = Check_Cal(&pError->Loss_Step, pError->Motor_Error_Flag.bit.loss_step);
}

/**
 * @brief  电流中断任务：快速过压 / 快速过流
 * @param  pError  故障结构体指针
 */
void MC_Error_Current_Flow(ST_MOTOR_ERROR* pError)
{
    pError->Fast_Over_Voltage.Check_Flag.bit.Condition_Set  = (pError->I_Q14U_Vbus_pu >= pError->Fast_Over_Voltage.P_Q14I_Check_TL);
    pError->Motor_Error_Flag.bit.fast_over_voltage          = Check_Cal(&pError->Fast_Over_Voltage, pError->Motor_Error_Flag.bit.fast_over_voltage);

    pError->Fast_Over_Current.Check_Flag.bit.Condition_Set  = (pError->I_Q14U_Iphase_Max_pu >= pError->Fast_Over_Current.P_Q14I_Check_TL);
    pError->Motor_Error_Flag.bit.fast_over_current          = Check_Cal(&pError->Fast_Over_Current, pError->Motor_Error_Flag.bit.fast_over_current);
}

/**
 * @brief  短路事件记录（硬件刹车触发时调用）
 * @param  pError  故障结构体指针
 */
void MC_Error_Short_Flow(ST_MOTOR_ERROR* pError)
{
    if (pError->V_Q32U_MOS_Error_cnt_Last == pError->V_Q32U_MOS_Error_cnt)
    {
        pError->V_Q32U_MOS_Error_cnt++;
        pError->Motor_Error_Flag.bit.current_short = 1U;
    }
}

/**
 * @brief  1ms 任务：MOS 短路次数累积判断
 * @param  pError  故障结构体指针
 */
void MC_Error_Init_Flow(ST_MOTOR_ERROR* pError)
{
    if (pError->V_Q32U_MOS_Error_cnt >= pError->P_Q32U_MOS_Error_Count)
    {
        pError->Motor_Error_Flag.bit.mos_fault = 1U;
    }
    pError->V_Q32U_MOS_Error_cnt_Last = pError->V_Q32U_MOS_Error_cnt;
}

/**
 * @brief  清除可复位故障并复位确认结构体
 * @param  pError  故障结构体指针
 */
void MC_Error_Clear(ST_MOTOR_ERROR* pError)
{
    pError->Motor_Error_Flag.bit.current_short  = 0U;
    pError->Motor_Error_Flag.bit.current_offset = 0U;
    pError->Motor_Error_Flag.bit.position_error = 0U;
    pError->Motor_Error_Flag.bit.rotor_stall    = 0U;

    pError->Motor_Error_Flag.bit.low_voltage = 0U;

    pError->Motor_Error_Flag.bit.over_current1 = 0U;
    pError->Motor_Error_Flag.bit.over_current2 = 0U;
    pError->Motor_Error_Flag.bit.over_current3 = 0U;

    pError->Motor_Error_Flag.bit.over_speed = 0U;
    pError->Motor_Error_Flag.bit.low_speed  = 0U;

    pError->Motor_Error_Flag.bit.over_power = 0U;
    pError->Motor_Error_Flag.bit.over_ibus  = 0U;

    pError->Motor_Error_Flag.bit.phase_lack_a = 0U;
    pError->Motor_Error_Flag.bit.phase_lack_b = 0U;
    pError->Motor_Error_Flag.bit.phase_lack_c = 0U;
    pError->Motor_Error_Flag.bit.rotor_lock   = 0U;
    pError->Motor_Error_Flag.bit.loss_step    = 0U;

    pError->Motor_Error_Flag.bit.fast_over_voltage = 0U;
    pError->Motor_Error_Flag.bit.fast_over_current = 0U;

    Check_Init(&pError->Low_Voltage);
    Check_Init(&pError->Over_Current1);
    Check_Init(&pError->Over_Current2);
    Check_Init(&pError->Over_Current3);
    Check_Init(&pError->Over_Speed);
    Check_Init(&pError->Low_Speed);
    Check_Init(&pError->Over_Power);
    Check_Init(&pError->Over_Ibus);
    Check_Init(&pError->Phase_Lack_A);
    Check_Init(&pError->Phase_Lack_B);
    Check_Init(&pError->Phase_Lack_C);
    Check_Init(&pError->Rotor_Lock);
    Check_Init(&pError->Loss_Step);
    Check_Init(&pError->Fast_Over_Voltage);
    Check_Init(&pError->Fast_Over_Current);
}
