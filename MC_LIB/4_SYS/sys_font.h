/**
 * @file    sys_font.h
 * @brief   字模数据对外接口声明
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef SYS_FONT_H
#define SYS_FONT_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_lcd.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */
/* 32×32 汉字：每字 128 字节 */
typedef struct{
    Q16U_           code;           /* 汉字 Unicode 编码 */
    const Q08U_    *data;           /* 指向 128 字节点阵数据的指针 */
} ST_HZ32_T;

/* 16×32 字符：每字 64 字节（数字/字母/符号）*/
typedef struct{
    Q16U_           code;           /* 字符 ASCII 码 */
    const Q08U_    *data;           /* 指向 64 字节点阵数据的指针 */
} ST_HZ16X32_T;

/* ======================== 4. Globals ====================== */
/* 32×32 汉字字模表（定义在 sys_font.c 中）*/
extern const ST_HZ32_T      hz32_table[];
extern const Q16U_          hz32_count;

/* 16×32 ASCII 字模表（定义在 sys_font.c 中）*/
extern const ST_HZ16X32_T   hz16x32_table[];
extern const Q16U_          hz16x32_count;

/* ======================== 5. Function Prototypes ========== */
const Q08U_ *hz32_find(Q16U_ code);

const Q08U_ *hz16x32_find(Q16U_ code);

#endif /* SYS_FONT_H */
