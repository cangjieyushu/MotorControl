/**
 * @file    math_pid_t.c
 * @brief   定点 PID 控制器实现（Q14）
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "math_pid_t.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  初始化增量式 PID
 * @param  pPID  增量式 PID 结构体指针
 * @param  init  初始输出
 */
void PID_Inc_Init_T(ST_PID_INC_T* pPID, Q32I_ init)
{
    pPID->O_Q14I_Output     = init;
    pPID->V_Q14I_LastError  = 0;
    pPID->V_Q14I_PrevError  = 0;
    pPID->V_Q28I_Step       = 0;
    pPID->V_Q28I_Output_tmp = Q16I_LFT_14(init);
}

/**
 * @brief  增量式 PID 单帧计算
 * @param  pPID  增量式 PID 结构体指针
 */
void PID_Inc_Cal_T(ST_PID_INC_T* pPID)
{
    Q32I_ Q14I_Error;

    Q14I_Error = pPID->I_Q14I_Rf - pPID->I_Q14I_Fb;

    pPID->V_Q28I_Step = pPID->P_Q14I_Kp * (Q14I_Error - pPID->V_Q14I_LastError)
    + pPID->P_Q14I_Ki * Q14I_Error
    + pPID->P_Q14I_Kd * (Q14I_Error + pPID->V_Q14I_PrevError - 2 * pPID->V_Q14I_LastError);
    pPID->V_Q28I_Step = MATH_SAT_T(pPID->V_Q28I_Step, pPID->P_Q28I_StepMax, pPID->P_Q28I_StepMin);

    pPID->V_Q28I_Output_tmp += pPID->V_Q28I_Step;
    pPID->V_Q28I_Output_tmp = MATH_SAT_T(pPID->V_Q28I_Output_tmp, Q16I_LFT_14(pPID->P_Q14I_OutMax), Q16I_LFT_14(pPID->P_Q14I_OutMin));

    pPID->O_Q14I_Output    = Q32I_RHT_14(pPID->V_Q28I_Output_tmp);
    pPID->V_Q14I_PrevError = pPID->V_Q14I_LastError;
    pPID->V_Q14I_LastError = Q14I_Error;
}

/**
 * @brief  初始化位置式 PID
 * @param  pPID  位置式 PID 结构体指针
 * @param  init  初始输出
 */
void PID_Pos_Init_T(ST_PID_POS_T* pPID, Q32I_ init)
{
    pPID->V_Q14I_Int    = init;
    pPID->O_Q14I_Output = init;
    pPID->V_Q28I_Ui_tmp = Q16I_LFT_14(init);
}

/**
 * @brief  位置式 PID 单帧计算
 * @param  pPID  位置式 PID 结构体指针
 */
void PID_Pos_Cal_T(ST_PID_POS_T* pPID)
{
    Q32I_ Q14I_Error;

    Q14I_Error = pPID->I_Q14I_Rf - pPID->I_Q14I_Fb;

    pPID->V_Q28I_Ui_tmp += pPID->P_Q14I_Ki * Q14I_Error;
    pPID->V_Q28I_Ui_tmp = MATH_SAT_T(pPID->V_Q28I_Ui_tmp, Q16I_LFT_14(pPID->P_Q14I_OutMax), Q16I_LFT_14(pPID->P_Q14I_OutMin));
    pPID->V_Q14I_Int = Q32I_RHT_14(pPID->V_Q28I_Ui_tmp);

    pPID->O_Q14I_Output = Q32I_RHT_14(pPID->P_Q14I_Kp * Q14I_Error) + pPID->V_Q14I_Int;
    pPID->O_Q14I_Output = MATH_SAT_T(pPID->O_Q14I_Output, pPID->P_Q14I_OutMax, pPID->P_Q14I_OutMin);
}

/**
 * @brief  初始化带抗饱和的位置式 PID
 * @param  pPID  抗饱和 PID 结构体指针
 * @param  init  初始输出
 */
void PID_Sat_Init_T(ST_PID_SAT_T* pPID, Q32I_ init)
{
    pPID->O_Q14I_Output = init;
    pPID->V_Q14I_Int    = init;
    pPID->V_Q14I_USat   = 0;
    pPID->V_Q28I_Ui_tmp = Q16I_LFT_14(init);
}

/**
 * @brief  带抗饱和的位置式 PID 单帧计算
 * @param  pPID  抗饱和 PID 结构体指针
 */
void PID_Sat_Cal_T(ST_PID_SAT_T* pPID)
{
    Q32I_ Q14I_Error;
    Q32I_ O_Q14I_Output_tmp;

    Q14I_Error = pPID->I_Q14I_Rf - pPID->I_Q14I_Fb;
    O_Q14I_Output_tmp = 0;

    pPID->V_Q28I_Ui_tmp += pPID->P_Q14I_Ki * Q14I_Error - pPID->P_Q14I_Kc * pPID->V_Q14I_USat;
    pPID->V_Q28I_Ui_tmp = MATH_SAT_T(pPID->V_Q28I_Ui_tmp, Q16I_LFT_14(pPID->P_Q14I_OutMax), Q16I_LFT_14(pPID->P_Q14I_OutMin));
    pPID->V_Q14I_Int = Q32I_RHT_14(pPID->V_Q28I_Ui_tmp);

    O_Q14I_Output_tmp = Q32I_RHT_14(pPID->P_Q14I_Kp * Q14I_Error) + pPID->V_Q14I_Int;
    pPID->O_Q14I_Output = MATH_SAT_T(O_Q14I_Output_tmp, pPID->P_Q14I_OutMax, pPID->P_Q14I_OutMin);
    pPID->V_Q14I_USat   = O_Q14I_Output_tmp - pPID->O_Q14I_Output;
}
