/**
 * @file    math_table_t.h
 * @brief   定点查表与线性插值（Q14）
 * @author  CJYS
 * @date    2024/1/1
 *
 * 一维/二维表结构约定：x 单调递增，y 或 z 与 x/y 坐标对应。
 * 二维表按列优先存储（先 x 后 y）。
 */

#ifndef MATH_TABLE_T_H
#define MATH_TABLE_T_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief Q14 一维表
 */
typedef struct
{
    Q32I_* x;       /**< 横坐标，长度 n */
    Q32I_* y;       /**< 纵坐标，长度 n */
    Q32U_  n;       /**< 元素个数 */
} TABLE_1D_T;

/**
 * @brief Q14 二维表（列优先）
 */
typedef struct
{
    Q32I_* x;       /**< x 方向坐标，长度 nx */
    Q32I_* y;       /**< y 方向坐标，长度 ny */
    Q32I_* z;       /**< 二维数据，nx*ny 个元素 */
    Q32U_  nx;      /**< x 方向长度 */
    Q32U_  ny;      /**< y 方向长度 */
} TABLE_2D_T;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  一维线性插值
 * @param  table  一维表指针
 * @param  x      输入坐标
 * @return 插值结果（超出范围返回端点值）
 */
__attribute__CCMRAM
Q32I_ TABLE_1D_Inter_T(const TABLE_1D_T* table, Q32I_ x);

/**
 * @brief  二维线性插值（先 x 后 y）
 * @param  table  二维表指针
 * @param  x      输入 x 坐标
 * @param  y      输入 y 坐标
 * @return 插值结果（超出范围返回端点值）
 */
__attribute__CCMRAM
Q32I_ TABLE_2D_Inter_T(const TABLE_2D_T* table, Q32I_ x, Q32I_ y);

#endif /* MATH_TABLE_T_H */
