/**
 * @file    math_pid_f.h
 * @brief   浮点 PID 控制器
 * @author  CJYS
 * @date    2024/1/1
 *
 * 提供位置式 PID 与带抗积分饱和的位置式 PID（Sat）。
 */

#ifndef MATH_PID_F_H
#define MATH_PID_F_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 位置式 PID
 */
typedef struct
{
    float I_F_Rf;       /**< 给定值 */
    float I_F_Fb;       /**< 反馈值 */
    float O_F_Output;   /**< 输出 */

    float V_F_Int;      /**< 积分项 */

    float P_F_Kp;       /**< 比例系数 */
    float P_F_Ki;       /**< 积分系数 */
    float P_F_Kd;       /**< 微分系数（当前实现未使用） */
    float P_F_OutMax;   /**< 输出上限 */
    float P_F_OutMin;   /**< 输出下限 */
} ST_PID_POS_F;

/**
 * @brief 带抗饱和的位置式 PID
 */
typedef struct
{
    float I_F_Rf;       /**< 给定值 */
    float I_F_Fb;       /**< 反馈值 */
    float O_F_Output;   /**< 输出 */

    float V_F_Int;      /**< 积分项 */
    float V_F_USat;     /**< 未饱和输出 - 饱和输出 */

    float P_F_Kp;       /**< 比例系数 */
    float P_F_Ki;       /**< 积分系数 */
    float P_F_Kd;       /**< 微分系数（当前实现未使用） */
    float P_F_Kc;       /**< 抗饱和增益 */
    float P_F_OutMax;   /**< 输出上限 */
    float P_F_OutMin;   /**< 输出下限 */
} ST_PID_SAT_F;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  初始化位置式 PID
 * @param  pPID  PID 结构体指针
 * @param  init  初始输出
 */
__attribute__CCMRAM
void PID_Pos_Init_F(ST_PID_POS_F* pPID, float init);

/**
 * @brief  位置式 PID 单帧计算
 * @param  pPID  PID 结构体指针
 */
__attribute__CCMRAM
void PID_Pos_Cal_F(ST_PID_POS_F* pPID);

/**
 * @brief  初始化带抗饱和的位置式 PID
 * @param  pPID  PID 结构体指针
 * @param  init  初始输出
 */
__attribute__CCMRAM
void PID_Sat_Init_F(ST_PID_SAT_F* pPID, float init);

/**
 * @brief  带抗饱和的位置式 PID 单帧计算
 * @param  pPID  PID 结构体指针
 */
__attribute__CCMRAM
void PID_Sat_Cal_F(ST_PID_SAT_F* pPID);

#endif /* MATH_PID_F_H */
