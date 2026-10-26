/**
 * @file    math_filter_f.h
 * @brief   浮点滤波器与统计函数
 * @author  CJYS
 * @date    2024/1/1
 *
 * 提供一阶低通/高通滤波器、滑动平均、滑动最大值。
 */

#ifndef MATH_FILTER_F_H
#define MATH_FILTER_F_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 一阶低通滤波器
 */
typedef struct
{
    float I_F_LPF_In;       /**< 输入 */
    float O_F_LPF_Out;      /**< 输出（也是内部状态） */

    float P_F_LPF_Coeff;    /**< 滤波系数 [0,1] */
} ST_LPF_F;

/**
 * @brief 一阶高通滤波器
 */
typedef struct
{
    float I_F_HPF_In;       /**< 输入 */
    float O_F_HPF_Out;      /**< 输出 */
    float V_F_HPF_In_Last;  /**< 上一帧输入 */

    float P_F_HPF_Coeff;    /**< 滤波系数 [0,1] */
} ST_HPF_F;

/**
 * @brief 滑动平均
 */
typedef struct
{
    float I_F_MEAN_In;      /**< 输入 */
    float O_F_MEAN_Out;     /**< 输出（窗口完成时更新） */

    float V_F_MEAN_Tmp;     /**< 累计和 */
    Q32U_ V_Q32U_MEAN_Cnt;  /**< 窗口计数 */

    Q32U_ P_Q32U_MEAN_Num;  /**< 窗口长度 */
} ST_MEAN_F;

/**
 * @brief 滑动最大值
 */
typedef struct
{
    float I_F_MAX_In;       /**< 输入 */
    float O_F_MAX_Out;      /**< 输出（窗口完成时更新） */

    float V_F_MAX_Tmp;      /**< 窗口内当前最大值 */
    Q32U_ V_Q32U_MAX_Cnt;   /**< 窗口计数 */

    Q32U_ P_Q32U_MAX_Num;   /**< 窗口长度 */
} ST_MAX_F;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  初始化低通滤波器
 * @param  pLPF  滤波器结构体指针
 * @param  init  初始输出
 */
__attribute__CCMRAM
void LPF_Init_F(ST_LPF_F* pLPF, float init);

/**
 * @brief  执行一帧低通滤波
 * @param  pLPF  滤波器结构体指针
 */
__attribute__CCMRAM
void LPF_Cal_F(ST_LPF_F* pLPF);

/**
 * @brief  初始化高通滤波器
 * @param  pHPF  滤波器结构体指针
 * @param  init  初始输出
 */
__attribute__CCMRAM
void HPF_Init_F(ST_HPF_F* pHPF, float init);

/**
 * @brief  执行一帧高通滤波
 * @param  pHPF  滤波器结构体指针
 */
__attribute__CCMRAM
void HPF_Cal_F(ST_HPF_F* pHPF);

/**
 * @brief  初始化滑动平均
 * @param  pMEAN  滑动平均结构体指针
 */
__attribute__CCMRAM
void MEAN_Init_F(ST_MEAN_F* pMEAN);

/**
 * @brief  执行一帧滑动平均
 * @param  pMEAN  滑动平均结构体指针
 */
__attribute__CCMRAM
void MEAN_Cal_F(ST_MEAN_F* pMEAN);

/**
 * @brief  初始化滑动最大值
 * @param  pMAX  滑动最大值结构体指针
 */
__attribute__CCMRAM
void MAX_Init_F(ST_MAX_F* pMAX);

/**
 * @brief  执行一帧滑动最大值
 * @param  pMAX  滑动最大值结构体指针
 */
__attribute__CCMRAM
void MAX_Cal_F(ST_MAX_F* pMAX);

#endif /* MATH_FILTER_F_H */
