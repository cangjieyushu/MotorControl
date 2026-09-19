/*
*     File Name :                        math_table_t
*     Library/Module Name :              math
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             查表函数
*/

#ifndef MATH_TABLE_T_H
#define MATH_TABLE_T_H

/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"

/*-------------------------- 2. 宏定义 -----------------------------------*/

/*-------------------------- 3. 枚举/结构体 ------------------------------*/
// 定点一维表（Q14格式）
typedef struct {
    Q32I_ *x;       // 横坐标，Q14
    Q32I_ *y;       // 纵坐标，Q14
    Q32U_ n;
}TABLE_1D_T;

// 定点二维表（列优先存储）
typedef struct {
    Q32I_ *x;       // x方向坐标，Q14，长度 nx
    Q32I_ *y;       // y方向坐标，Q14，长度 ny
    Q32I_ *z;       // 二维数据，Q14，行优先：z[iy * nx + ix] 对应 (x[ix], y[iy])
    Q32U_ nx;
    Q32U_ ny;
}TABLE_2D_T;

/*-------------------------- 4. 外部全局变量声明 --------------------------*/

/*-------------------------- 5. 接口函数声明 ------------------------------*/
Q32I_ TABLE_1D_Inter_T(const TABLE_1D_T* table, Q32I_ x);
Q32I_ TABLE_2D_Inter_T(const TABLE_2D_T* table, Q32I_ x, Q32I_ y);


#endif /* MATH_TABLE_T_H */
