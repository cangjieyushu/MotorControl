/**************************************************************************************************
*     File Name :                        MATH_TABLE_F.c
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             查表函数
**************************************************************************************************/

#include "MATH_TABLE_F.h"


// 二分查找，返回索引 i 使得 arr[i] <= val <= arr[i+1]（若 val 超出范围则返回边界索引）
static Q32U_ TABLE_Find_Index_F(const float* arr, Q32U_ n, float val)
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
    return 0; // 不会执行到这里
}

float TABLE_1D_Inter_F(const TABLE_1D_F* table, float x)
{
    if (table->n == 0) return 0.0f;
    if (table->n == 1) return table->y[0];

    // 输入超出范围：直接返回边界值
    if (x <= table->x[0]) return table->y[0];
    if (x >= table->x[table->n - 1]) return table->y[table->n - 1];
    
    Q32U_ i = TABLE_Find_Index_F(table->x, table->n, x);
    float x0 = table->x[i];
    float x1 = table->x[i+1];
    float y0 = table->y[i];
    float y1 = table->y[i+1];

    if (x1 == x0) return y0; // 避免除以零
    float t = (x - x0) / (x1 - x0);
    return y0 + t * (y1 - y0);
}

float TABLE_2D_Inter_F(const TABLE_2D_F* table, float x, float y)
{
    // 找到x和y所在的区间索引
    Q32U_ ix = TABLE_Find_Index_F(table->x, table->nx, x);
    Q32U_ iy = TABLE_Find_Index_F(table->y, table->ny, y);

    // 构建两个一维表用于x方向插值（固定y = y[iy] 和 y = y[iy+1]）
    TABLE_1D_F row_y0, row_y1;
    row_y0.x = table->x;
    row_y0.y = &table->z[iy * table->nx];     // 第iy行（y固定）的z值连续
    row_y0.n = table->nx;

    row_y1.x = table->x;
    row_y1.y = &table->z[(iy+1) * table->nx]; // 第iy+1行
    row_y1.n = table->nx;

    // 在x方向插值得到两个中间值
    float z_y0 = TABLE_1D_Inter_F(&row_y0, x);
    float z_y1 = TABLE_1D_Inter_F(&row_y1, x);

    // 构建一个一维表用于y方向插值（只有两个点）
    float y_vals[2] = {table->y[iy], table->y[iy+1]};
    float z_vals[2] = {z_y0, z_y1};
    TABLE_1D_F col;
    col.x = y_vals;
    col.y = z_vals;
    col.n = 2;

    // 在y方向插值得到最终结果
    return TABLE_1D_Inter_F(&col, y);
}
