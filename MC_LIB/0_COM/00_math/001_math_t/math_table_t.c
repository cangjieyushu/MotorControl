/**
 * @file    math_table_t.c
 * @brief   定点查表与线性插值实现（Q14）
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "math_table_t.h"

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
static Q32U_ TABLE_Find_Index_T(const Q32I_* arr, Q32U_ n, Q32I_ val)
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
Q32I_ TABLE_1D_Inter_T(const TABLE_1D_T* table, Q32I_ x)
{
    Q32U_ i;
    Q32I_ x0;
    Q32I_ x1;
    Q32I_ y0;
    Q32I_ y1;

    if (table->n == 0U)
    {
        return 0;
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

    i  = TABLE_Find_Index_T(table->x, table->n, x);
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
Q32I_ TABLE_2D_Inter_T(const TABLE_2D_T* table, Q32I_ x, Q32I_ y)
{
    Q32U_ iy;
    TABLE_1D_T row_y0;
    TABLE_1D_T row_y1;
    TABLE_1D_T col;
    Q32I_ z_y0;
    Q32I_ z_y1;
    Q32I_ y_vals[2];
    Q32I_ z_vals[2];

    iy = TABLE_Find_Index_T(table->y, table->ny, y);

    row_y0.x = table->x;
    row_y0.y = &table->z[iy * table->nx];
    row_y0.n = table->nx;

    row_y1.x = table->x;
    row_y1.y = &table->z[(iy + 1U) * table->nx];
    row_y1.n = table->nx;

    z_y0 = TABLE_1D_Inter_T(&row_y0, x);
    z_y1 = TABLE_1D_Inter_T(&row_y1, x);

    y_vals[0] = table->y[iy];
    y_vals[1] = table->y[iy + 1U];
    z_vals[0] = z_y0;
    z_vals[1] = z_y1;

    col.x = y_vals;
    col.y = z_vals;
    col.n = 2U;

    return TABLE_1D_Inter_T(&col, y);
}
