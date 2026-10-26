/**
 * @file    math_table_f.c
 * @brief   浮点查表与线性插值实现
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "math_table_f.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  折半查找：返回 x 落在表中的左索引区间
 * @param  arr  单调递增数组
 * @param  n    数组长度
 * @param  val  待查找值
 * @return 左索引（0..n-2），n<2 时返回 0
 */
static Q32U_ TABLE_Find_Index_F(const float* arr, Q32U_ n, float val)
{
    Q32U_ lo;
    Q32U_ hi;
    Q32U_ mid;

    if (n < 2U)
    {
        return 0U;
    }
    if (val <= arr[0])
    {
        return 0U;
    }
    if (val >= arr[n - 1U])
    {
        return n - 2U;
    }

    lo = 0U;
    hi = n - 1U;
    while (lo < hi)
    {
        mid = (lo + hi) / 2U;
        if (arr[mid] < val)
        {
            lo = mid + 1U;
        }
        else
        {
            hi = mid;
        }
    }
    return (lo > 0U) ? (lo - 1U) : 0U;
}

/**
 * @brief  一维线性插值
 * @param  table  一维表指针
 * @param  x      输入坐标
 * @return 插值结果（超出范围返回端点值）
 */
float TABLE_1D_Inter_F(const TABLE_1D_F* table, float x)
{
    Q32U_ i;
    float x0;
    float x1;
    float y0;
    float y1;

    if (table->n == 0U)
    {
        return 0.0f;
    }
    if (table->n == 1U)
    {
        return table->y[0];
    }

    if (x <= table->x[0])
    {
        return table->y[0];
    }
    if (x >= table->x[table->n - 1U])
    {
        return table->y[table->n - 1U];
    }

    i  = TABLE_Find_Index_F(table->x, table->n, x);
    x0 = table->x[i];
    x1 = table->x[i + 1U];
    y0 = table->y[i];
    y1 = table->y[i + 1U];

    if (x1 == x0)
    {
        return y0;
    }
    
    return y0 + (x - x0) * (y1 - y0) / (x1 - x0);
}

/**
 * @brief  二维线性插值（先 x 后 y）
 * @param  table  二维表指针
 * @param  x      输入 x 坐标
 * @param  y      输入 y 坐标
 * @return 插值结果（超出范围返回端点值）
 */
float TABLE_2D_Inter_F(const TABLE_2D_F* table, float x, float y)
{
    Q32U_ iy;
    TABLE_1D_F row_y0;
    TABLE_1D_F row_y1;
    TABLE_1D_F col;
    float z_y0;
    float z_y1;
    float y_vals[2];
    float z_vals[2];

    iy = TABLE_Find_Index_F(table->y, (Q32U_)table->ny, y);

    row_y0.x = table->x;
    row_y0.y = &table->z[(Q32U_)iy * (Q32U_)table->nx];
    row_y0.n = (Q32U_)table->nx;

    row_y1.x = table->x;
    row_y1.y = &table->z[((Q32U_)iy + 1U) * (Q32U_)table->nx];
    row_y1.n = (Q32U_)table->nx;

    z_y0 = TABLE_1D_Inter_F(&row_y0, x);
    z_y1 = TABLE_1D_Inter_F(&row_y1, x);

    y_vals[0] = table->y[iy];
    y_vals[1] = table->y[iy + 1U];
    z_vals[0] = z_y0;
    z_vals[1] = z_y1;

    col.x = y_vals;
    col.y = z_vals;
    col.n = 2U;

    return TABLE_1D_Inter_F(&col, y);
}
