/**
 * @file    math_angle_t.h
 * @brief   定点三角函数（查表）
 * @author  CJYS
 * @date    2024/1/1
 *
 * 角度为 Q14 定点（0..2π 映射到 0..16383），sin/cos 返回 Q14。
 */

#ifndef MATH_ANGLE_T_H
#define MATH_ANGLE_T_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 定点三角函数输入输出
 */
typedef struct
{
    Q32I_ Q14U_Angle;    /**< 输入：Q14 角度 */
    Q32I_ Q14I_Cos;      /**< 输出：Q14 cos */
    Q32I_ Q14I_Sin;      /**< 输出：Q14 sin */
    Q32I_ Q14U_ReAngle;  /**< 保留：反向角度 */
} ST_TRIG_T;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  计算 Q14 sin / cos
 * @param  pTIG  三角函数结构体指针（含输入角度，输出 sin/cos）
 */
__attribute__CCMRAM
void Math_SinCos_T(ST_TRIG_T* pTIG);

#endif /* MATH_ANGLE_T_H */
