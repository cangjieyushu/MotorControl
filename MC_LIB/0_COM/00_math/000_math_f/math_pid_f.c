/**
 * @file    math_pid_f.c
 * @brief   浮点 PID 控制器实现
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "math_pid_f.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  初始化位置式 PID
 * @param  pPID  PID 结构体指针
 * @param  init  初始输出
 */
void PID_Pos_Init_F(ST_PID_POS_F* pPID, float init)
{
    pPID->O_F_Output = init;
    pPID->V_F_Int    = init;
}

/**
 * @brief  位置式 PID 单帧计算
 * @param  pPID  PID 结构体指针
 */
void PID_Pos_Cal_F(ST_PID_POS_F* pPID)
{
    float F_Error;

    F_Error = pPID->I_F_Rf - pPID->I_F_Fb;

    pPID->V_F_Int += pPID->P_F_Ki * F_Error;
    pPID->V_F_Int = MATH_SAT_F(pPID->V_F_Int, pPID->P_F_OutMax, pPID->P_F_OutMin);

    pPID->O_F_Output = pPID->P_F_Kp * F_Error + pPID->V_F_Int;
    pPID->O_F_Output = MATH_SAT_F(pPID->O_F_Output, pPID->P_F_OutMax, pPID->P_F_OutMin);
}

/**
 * @brief  初始化带抗饱和的位置式 PID
 * @param  pPID  PID 结构体指针
 * @param  init  初始输出
 */
void PID_Sat_Init_F(ST_PID_SAT_F* pPID, float init)
{
    pPID->O_F_Output = init;
    pPID->V_F_Int    = init;
    pPID->V_F_USat   = 0.0f;
}

/**
 * @brief  带抗饱和的位置式 PID 单帧计算
 * @param  pPID  PID 结构体指针
 */
void PID_Sat_Cal_F(ST_PID_SAT_F* pPID)
{
    float F_Error;
    float F_Output_tmp;

    F_Error = pPID->I_F_Rf - pPID->I_F_Fb;
    F_Output_tmp = 0.0f;

    pPID->V_F_Int += pPID->P_F_Ki * F_Error -
                     pPID->P_F_Kc * pPID->V_F_USat;

    F_Output_tmp     = pPID->P_F_Kp * F_Error + pPID->V_F_Int;
    pPID->O_F_Output = MATH_SAT_F(F_Output_tmp, pPID->P_F_OutMax, pPID->P_F_OutMin);
    pPID->V_F_USat   = F_Output_tmp - pPID->O_F_Output;
}
