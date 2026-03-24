/**************************************************************************************************
*     File Name :                        MATH_TABLE_T.c
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             查表函数
**************************************************************************************************/

#include "MATH_TABLE_T.h"


// 二分查找，返回索引 i 使得 arr[i] <= val <= arr[i+1]（若 val 超出范围则返回边界索引）// 定点版本
static Q32U_ TABLE_Find_Index_T(const Q32I_* arr, Q32U_ n, Q32I_ val)
{
    if (val <= arr[0]) return 0;
    if (val >= arr[n-1]) return n-2;
    Q32U_ lo = 0, hi = n-1;
    while (lo <= hi) {
        Q32U_ mid = (lo + hi) / 2;
        if (val < arr[mid]) {
            hi = mid - 1;
        } else if (val > arr[mid+1]) {
            lo = mid + 1;
        } else {
            return mid;
        }
    }
    return 0;
}

Q32I_ TABLE_1D_Inter_T(const TABLE_1D_T* table, Q32I_ x)
{
    if (table->n == 0) return 0;
    if (table->n == 1) return table->y[0];

    // 输入超出范围：直接返回边界值
    if (x <= table->x[0]) return table->y[0];
    if (x >= table->x[table->n - 1]) return table->y[table->n - 1];
    
    Q32U_ i = TABLE_Find_Index_T(table->x, table->n, x);
    Q32I_ x0 = table->x[i];
    Q32I_ x1 = table->x[i+1];
    Q32I_ y0 = table->y[i];
    Q32I_ y1 = table->y[i+1];

    if (x1 == x0) return y0;

    // 使用64位中间结果防止溢出
    Q32I_ num = (x - x0) * (y1 - y0);
    Q32I_ den = x1 - x0;
    // 除法结果自动为Q14格式： (num/den) 是Q14
    Q32I_ delta = (num / den);
    return y0 + delta;
}

Q32I_ TABLE_2D_Inter_T(const TABLE_2D_T* table, Q32I_ x, Q32I_ y)
{
    Q32U_ ix = TABLE_Find_Index_T(table->x, table->nx, x);
    Q32U_ iy = TABLE_Find_Index_T(table->y, table->ny, y);

    TABLE_1D_T row_y0, row_y1;
    row_y0.x = table->x;
    row_y0.y = &table->z[iy * table->nx];
    row_y0.n = table->nx;

    row_y1.x = table->x;
    row_y1.y = &table->z[(iy+1) * table->nx];
    row_y1.n = table->nx;

    Q32I_ z_y0 = TABLE_1D_Inter_T(&row_y0, x);
    Q32I_ z_y1 = TABLE_1D_Inter_T(&row_y1, x);

    Q32I_ y_vals[2] = {table->y[iy], table->y[iy+1]};
    Q32I_ z_vals[2] = {z_y0, z_y1};
    TABLE_1D_T col;
    col.x = y_vals;
    col.y = z_vals;
    col.n = 2;

    return TABLE_1D_Inter_T(&col, y);
}
