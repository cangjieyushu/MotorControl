/**
 * @file    math_ramp_t.h
 * @brief   定点斜坡函数（Q14）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef MATH_RAMP_T_H
#define MATH_RAMP_T_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief Q14 斜坡
 */
typedef struct
{
    Q32I_ O_Q14I_Output;     /**< 当前输出 */

    Q32I_ V_Q28I_Output_tmp; /**< 内部 Q28 中间量 */

    Q32I_ P_Q14I_Init;       /**< 初始值 */
    Q32I_ P_Q14I_Target;     /**< 目标值 */
    Q32I_ P_Q28I_ADDStep;    /**< 上升步长（Q28） */
    Q32I_ P_Q28I_SUBStep;    /**< 下降步长（Q28） */
} ST_RAMP_T;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  初始化斜坡函数
 * @param  pRamp  斜坡结构体指针
 * @param  init   初始输出
 */
__attribute__CCMRAM
void Ramp_Init_T(ST_RAMP_T* pRamp, Q32I_ init);

/**
 * @brief  执行一帧斜坡逼近
 * @param  pRamp  斜坡结构体指针
 */
__attribute__CCMRAM
void Ramp_Cal_T(ST_RAMP_T* pRamp);

#endif /* MATH_RAMP_T_H */
