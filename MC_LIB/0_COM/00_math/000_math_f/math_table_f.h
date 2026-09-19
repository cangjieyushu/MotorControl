/*
*     File Name :                        math_table_f
*     Library/Module Name :              math
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             查表函数
*/


#ifndef MATH_TABLE_F_H
#define MATH_TABLE_F_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
// 浮点一维表
typedef struct {
    float *x;       // 横坐标数组（单调递增）
    float *y;       // 纵坐标数组
    Q32U_ n;        // 点数
}TABLE_1D_F;

// 浮点二维表（列优先存储）
typedef struct {
    float *x;       // x方向坐标（单调递增），长度 nx
    float *y;       // y方向坐标（单调递增），长度 ny
    float *z;       // 二维数据，行优先：z[iy * nx + ix] 对应 (x[ix], y[iy])
    int nx;
    int ny;
}TABLE_2D_F;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
float TABLE_1D_Inter_F(const TABLE_1D_F* table, float x);
float TABLE_2D_Inter_F(const TABLE_2D_F* table, float x, float y);


#endif /* MATH_TABLE_F_H */
