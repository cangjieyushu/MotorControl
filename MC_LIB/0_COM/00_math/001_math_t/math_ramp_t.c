/**
 * @file    math_ramp_t.c
 * @brief   定点斜坡函数实现（Q14）
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "math_ramp_t.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  初始化斜坡函数
 * @param  pRamp  斜坡结构体指针
 * @param  init   初始输出
 */
void Ramp_Init_T(ST_RAMP_T* pRamp, Q32I_ init)
{
    pRamp->O_Q14I_Output     = init;
    pRamp->V_Q28I_Output_tmp = Q16I_LFT_14(init);
}

/**
 * @brief  执行一帧斜坡逼近
 * @param  pRamp  斜坡结构体指针
 */
void Ramp_Cal_T(ST_RAMP_T* pRamp)
{
    Q32I_ Q28I_Target_tmp;

    Q28I_Target_tmp = Q16I_LFT_14(pRamp->P_Q14I_Target);

    if (Q28I_Target_tmp > pRamp->V_Q28I_Output_tmp)
    {
        if (Q28I_Target_tmp >
            (pRamp->V_Q28I_Output_tmp + pRamp->P_Q28I_ADDStep))
        {
            pRamp->V_Q28I_Output_tmp += pRamp->P_Q28I_ADDStep;
        }
        else
        {
            pRamp->V_Q28I_Output_tmp = Q28I_Target_tmp;
        }
    }
    else if (Q28I_Target_tmp < pRamp->V_Q28I_Output_tmp)
    {
        if (Q28I_Target_tmp <
            (pRamp->V_Q28I_Output_tmp + pRamp->P_Q28I_SUBStep))
        {
            pRamp->V_Q28I_Output_tmp += pRamp->P_Q28I_SUBStep;
        }
        else
        {
            pRamp->V_Q28I_Output_tmp = Q28I_Target_tmp;
        }
    }
    else
    {
        pRamp->V_Q28I_Output_tmp = Q28I_Target_tmp;
    }

    pRamp->O_Q14I_Output = Q32I_RHT_14(pRamp->V_Q28I_Output_tmp);
}
