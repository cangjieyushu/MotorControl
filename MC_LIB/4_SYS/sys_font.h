/**************************************************************************************************
*     File Name :                        sys_font
*     Library/Module Name :              sys
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             字模数据对外接口声明
*                                        其他 .c 文件 include 本文件即可访问字模表
**************************************************************************************************/
#ifndef SYS_FONT_H
#define SYS_FONT_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_lcd.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
/* 32×32 汉字：每字 128 字节 */
typedef struct {
    Q16U_           code;           /* 汉字 Unicode 编码 */
    const Q08U_    *data;           /* 指向 128 字节点阵数据的指针 */
} ST_HZ32_T;

/* 16×32 字符：每字 64 字节（数字/字母/符号）*/
typedef struct {
    Q16U_           code;           /* 字符 ASCII 码 */
    const Q08U_    *data;           /* 指向 64 字节点阵数据的指针 */
} ST_HZ16X32_T;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/
/* 32×32 汉字字模表（定义在 sys_font.c 中）*/
extern const ST_HZ32_T      hz32_table[];
extern const Q16U_          hz32_count;

/* 16×32 ASCII 字模表（定义在 sys_font.c 中）*/
extern const ST_HZ16X32_T   hz16x32_table[];
extern const Q16U_          hz16x32_count;


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: hz32_find
Description: 在 32×32 字模表中查找指定编码
Input: code - Unicode 编码
Return: 找到返回数据指针；找不到返回 0
Author: CJYS
*/
const Q08U_ *hz32_find(Q16U_ code);

/*
Function: hz16x32_find
Description: 在 16×32 字模表中查找指定编码
Input: code - ASCII 编码
Return: 找到返回数据指针；找不到返回 0
Author: CJYS
*/
const Q08U_ *hz16x32_find(Q16U_ code);


#endif /* SYS_FONT_H */
