/**************************************************************************************************
*     File Name :                        MATH_TABLE_T.h
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             查表函数
**************************************************************************************************/

#ifndef MATH_TABLE_T_H
#define MATH_TABLE_T_H


#include "MATH.h"


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
    Q32I_ *z;       // 二维数据，Q14，列优先
    Q32U_ nx;
    Q32U_ ny;
}TABLE_2D_T;


Q32I_ TABLE_1D_Inter_T(const TABLE_1D_T* table, Q32I_ x);
Q32I_ TABLE_2D_Inter_T(const TABLE_2D_T* table, Q32I_ x, Q32I_ y);


#endif /* MATH_TABLE_T_H */
