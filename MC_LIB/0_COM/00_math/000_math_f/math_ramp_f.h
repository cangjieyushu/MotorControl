/**
 * @file    math_ramp_f.h
 * @brief   浮点斜坡函数
 * @author  CJYS
 * @date    2024/1/1
 *
 * 输出以固定步长逼近目标值，上/下斜坡步长独立配置。
 */

#ifndef MATH_RAMP_F_H
#define MATH_RAMP_F_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 浮点斜坡
 */
typedef struct
{
    float O_F_Output;   /**< 当前输出 */

    float P_F_Init;     /**< 初始值 */
    float P_F_Target;   /**< 目标值 */
    float P_F_ADDStep;  /**< 上升步长 */
    float P_F_SUBStep;  /**< 下降步长 */
} ST_RAMP_F;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  初始化斜坡函数
 * @param  pRamp  斜坡结构体指针
 * @param  init   初始输出
 */
__attribute__CCMRAM
void Ramp_Init_F(ST_RAMP_F* pRamp, float init);

/**
 * @brief  执行一帧斜坡逼近
 * @param  pRamp  斜坡结构体指针
 */
__attribute__CCMRAM
void Ramp_Cal_F(ST_RAMP_F* pRamp);

#endif /* MATH_RAMP_F_H */
