/**
 * @file    math_pid_t.h
 * @brief   定点 PID 控制器（Q14）
 * @author  CJYS
 * @date    2024/1/1
 *
 * 提供增量式、位置式、带抗饱和的位置式三种定点 PID。
 * 系数与状态均为 Q14/Q28 定点。
 */

#ifndef MATH_PID_T_H
#define MATH_PID_T_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 增量式 PID（Q14）
 */
typedef struct
{
    Q32I_ I_Q14I_Rf;         /**< 给定值 */
    Q32I_ I_Q14I_Fb;         /**< 反馈值 */
    Q32I_ O_Q14I_Output;     /**< 输出 */

    Q32I_ V_Q14I_LastError;  /**< 上一帧误差 */
    Q32I_ V_Q14I_PrevError;  /**< 上上帧误差 */
    Q32I_ V_Q28I_Step;       /**< 本帧增量（Q28） */
    Q32I_ V_Q28I_Output_tmp; /**< 输出中间量（Q28） */

    Q32I_ P_Q14I_Kp;         /**< 比例系数 */
    Q32I_ P_Q14I_Ki;         /**< 积分系数 */
    Q32I_ P_Q14I_Kd;         /**< 微分系数 */
    Q32I_ P_Q28I_StepMax;    /**< 单帧增量上限 */
    Q32I_ P_Q28I_StepMin;    /**< 单帧增量下限 */
    Q32I_ P_Q14I_OutMax;     /**< 输出上限 */
    Q32I_ P_Q14I_OutMin;     /**< 输出下限 */
} ST_PID_INC_T;

/**
 * @brief 位置式 PID（Q14）
 */
typedef struct
{
    Q32I_ I_Q14I_Rf;         /**< 给定值 */
    Q32I_ I_Q14I_Fb;         /**< 反馈值 */
    Q32I_ O_Q14I_Output;     /**< 输出 */

    Q32I_ V_Q14I_Int;        /**< 积分项 */
    Q32I_ V_Q28I_Ui_tmp;     /**< 积分中间量（Q28） */

    Q32I_ P_Q14I_Kp;         /**< 比例系数 */
    Q32I_ P_Q14I_Ki;         /**< 积分系数 */
    Q32I_ P_Q14I_Kd;         /**< 微分系数（当前实现未使用） */
    Q32I_ P_Q14I_OutMax;     /**< 输出上限 */
    Q32I_ P_Q14I_OutMin;     /**< 输出下限 */
} ST_PID_POS_T;

/**
 * @brief 带抗饱和的位置式 PID（Q14）
 */
typedef struct
{
    Q32I_ I_Q14I_Rf;         /**< 给定值 */
    Q32I_ I_Q14I_Fb;         /**< 反馈值 */
    Q32I_ O_Q14I_Output;     /**< 输出 */

    Q32I_ V_Q14I_Int;        /**< 积分项 */
    Q32I_ V_Q28I_Ui_tmp;     /**< 积分中间量（Q28） */
    Q32I_ V_Q14I_USat;       /**< 未饱和输出 - 饱和输出 */

    Q32I_ P_Q14I_Kp;         /**< 比例系数 */
    Q32I_ P_Q14I_Ki;         /**< 积分系数 */
    Q32I_ P_Q14I_Kd;         /**< 微分系数（当前实现未使用） */
    Q32I_ P_Q14I_Kc;         /**< 抗饱和增益 */
    Q32I_ P_Q14I_OutMax;     /**< 输出上限 */
    Q32I_ P_Q14I_OutMin;     /**< 输出下限 */
} ST_PID_SAT_T;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  初始化增量式 PID
 * @param  pPID  增量式 PID 结构体指针
 * @param  init  初始输出
 */
__attribute__CCMRAM
void PID_Inc_Init_T(ST_PID_INC_T* pPID, Q32I_ init);

/**
 * @brief  增量式 PID 单帧计算
 * @param  pPID  增量式 PID 结构体指针
 */
__attribute__CCMRAM
void PID_Inc_Cal_T(ST_PID_INC_T* pPID);

/**
 * @brief  初始化位置式 PID
 * @param  pPID  位置式 PID 结构体指针
 * @param  init  初始输出
 */
__attribute__CCMRAM
void PID_Pos_Init_T(ST_PID_POS_T* pPID, Q32I_ init);

/**
 * @brief  位置式 PID 单帧计算
 * @param  pPID  位置式 PID 结构体指针
 */
__attribute__CCMRAM
void PID_Pos_Cal_T(ST_PID_POS_T* pPID);

/**
 * @brief  初始化带抗饱和的位置式 PID
 * @param  pPID  抗饱和 PID 结构体指针
 * @param  init  初始输出
 */
__attribute__CCMRAM
void PID_Sat_Init_T(ST_PID_SAT_T* pPID, Q32I_ init);

/**
 * @brief  带抗饱和的位置式 PID 单帧计算
 * @param  pPID  抗饱和 PID 结构体指针
 */
__attribute__CCMRAM
void PID_Sat_Cal_T(ST_PID_SAT_T* pPID);

#endif /* MATH_PID_T_H */
