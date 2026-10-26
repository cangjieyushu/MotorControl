/**
 * @file    math_filter_t.h
 * @brief   定点滤波器与统计函数（Q14）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef MATH_FILTER_T_H
#define MATH_FILTER_T_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief Q14 一阶低通滤波器
 */
typedef struct
{
    Q32I_ I_Q14I_LPF_In;    /**< 输入 */
    Q32I_ O_Q14I_LPF_Out;   /**< 输出 */

    Q32I_ V_Q28I_LPF_Tmp;   /**< 内部 Q28 中间状态 */

    Q32I_ P_Q14I_LPF_Coeff; /**< 滤波系数（Q14） */
} ST_LPF_T;

/**
 * @brief Q14 滑动平均
 */
typedef struct
{
    Q32I_ I_Q14I_MEAN_In;   /**< 输入 */
    Q32I_ O_Q14I_MEAN_Out;  /**< 输出 */

    Q32I_ V_Q14I_MEAN_Tmp;  /**< 累计和 */
    Q32U_ V_Q32U_MEAN_Cnt;  /**< 窗口计数 */

    Q32U_ P_Q32U_MEAN_Num;  /**< 窗口长度 */
    Q32U_ P_Q32U_MEAN_Bit;  /**< 窗口长度对应移位位数 */
} ST_MEAN_T;

/**
 * @brief Q14 滑动最大值
 */
typedef struct
{
    Q32I_ I_Q14I_MAX_In;    /**< 输入 */
    Q32I_ O_Q14I_MAX_Out;   /**< 输出 */

    Q32I_ V_Q14I_MAX_Tmp;   /**< 窗口内当前最大值 */
    Q32U_ V_Q32U_MAX_Cnt;   /**< 窗口计数 */

    Q32U_ P_Q32U_MAX_Num;   /**< 窗口长度 */
} ST_MAX_T;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  初始化 Q14 低通滤波器
 * @param  pLPF  滤波器结构体指针
 * @param  init  初始输出
 */
__attribute__CCMRAM
void LPF_Init_T(ST_LPF_T* pLPF, Q32I_ init);

/**
 * @brief  执行一帧 Q14 低通滤波
 * @param  pLPF  滤波器结构体指针
 */
__attribute__CCMRAM
void LPF_Cal_T(ST_LPF_T* pLPF);

/**
 * @brief  初始化 Q14 滑动平均
 * @param  pMEAN  滑动平均结构体指针
 */
__attribute__CCMRAM
void MEAN_Init_T(ST_MEAN_T* pMEAN);

/**
 * @brief  执行一帧 Q14 滑动平均
 * @param  pMEAN  滑动平均结构体指针
 */
__attribute__CCMRAM
void MEAN_Cal_T(ST_MEAN_T* pMEAN);

/**
 * @brief  初始化 Q14 滑动最大值
 * @param  pMAX  滑动最大值结构体指针
 */
__attribute__CCMRAM
void MAX_Init_T(ST_MAX_T* pMAX);

/**
 * @brief  执行一帧 Q14 滑动最大值
 * @param  pMAX  滑动最大值结构体指针
 */
__attribute__CCMRAM
void MAX_Cal_T(ST_MAX_T* pMAX);

#endif /* MATH_FILTER_T_H */
