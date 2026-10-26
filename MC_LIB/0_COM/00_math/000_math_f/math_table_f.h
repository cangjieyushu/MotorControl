/**
 * @file    math_table_f.h
 * @brief   浮点查表与线性插值
 * @author  CJYS
 * @date    2024/1/1
 *
 * 一维/二维表结构约定：x 单调递增，y 或 z 与 x/y 坐标对应。
 * 二维表按列优先存储（先 x 后 y）。
 */

#ifndef MATH_TABLE_F_H
#define MATH_TABLE_F_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 浮点一维表
 */
typedef struct
{
    float* x;       /**< 横坐标，长度 n */
    float* y;       /**< 纵坐标，长度 n */
    Q32U_  n;       /**< 元素个数 */
} TABLE_1D_F;

/**
 * @brief 浮点二维表（列优先）
 */
typedef struct
{
    float* x;       /**< x 方向坐标，长度 nx */
    float* y;       /**< y 方向坐标，长度 ny */
    float* z;       /**< 二维数据，nx*ny 个元素 */
    int    nx;      /**< x 方向长度 */
    int    ny;      /**< y 方向长度 */
} TABLE_2D_F;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  一维线性插值
 * @param  table  一维表指针
 * @param  x      输入坐标
 * @return 插值结果（超出范围返回端点值）
 */
__attribute__CCMRAM
float TABLE_1D_Inter_F(const TABLE_1D_F* table, float x);

/**
 * @brief  二维线性插值（先 x 后 y）
 * @param  table  二维表指针
 * @param  x      输入 x 坐标
 * @param  y      输入 y 坐标
 * @return 插值结果（超出范围返回端点值）
 */
__attribute__CCMRAM
float TABLE_2D_Inter_F(const TABLE_2D_F* table, float x, float y);

#endif /* MATH_TABLE_F_H */
