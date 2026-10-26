/**
 * @file    math_ramp_f.c
 * @brief   浮点斜坡函数实现
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "math_ramp_f.h"

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
void Ramp_Init_F(ST_RAMP_F* pRamp, float init)
{
    pRamp->O_F_Output = init;
}

/**
 * @brief  执行一帧斜坡逼近
 * @param  pRamp  斜坡结构体指针
 */
void Ramp_Cal_F(ST_RAMP_F* pRamp)
{
    if (pRamp->P_F_Target > pRamp->O_F_Output)
    {
        if (pRamp->P_F_Target >
            (pRamp->O_F_Output + pRamp->P_F_ADDStep))
        {
            pRamp->O_F_Output += pRamp->P_F_ADDStep;
        }
        else
        {
            pRamp->O_F_Output = pRamp->P_F_Target;
        }
    }
    else if (pRamp->P_F_Target < pRamp->O_F_Output)
    {
        if (pRamp->P_F_Target <
            (pRamp->O_F_Output + pRamp->P_F_SUBStep))
        {
            pRamp->O_F_Output += pRamp->P_F_SUBStep;
        }
        else
        {
            pRamp->O_F_Output = pRamp->P_F_Target;
        }
    }
    else
    {
        pRamp->O_F_Output = pRamp->P_F_Target;
    }
}
