/**
 * @file    math_angle_f.h
 * @brief   浮点三角函数（查表 + 线性插值）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef MATH_ANGLE_F_H
#define MATH_ANGLE_F_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 三角函数输入输出
 */
typedef struct
{
    float F_Angle;      /**< 输入：归一化角度 [0,1) */
    float F_Cos;        /**< 输出：cos(2π·Angle) */
    float F_Sin;        /**< 输出：sin(2π·Angle) */
    float F_ReAngle;    /**< 保留：反向角度 */
} ST_TRIG_F;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  计算正弦与余弦（查表 + 线性插值）
 * @param  pTIG  三角函数结构体指针（含输入角度，输出 sin/cos）
 */
__attribute__CCMRAM
void Math_SinCos_F(ST_TRIG_F* pTIG);

#endif /* MATH_ANGLE_F_H */
