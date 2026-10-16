/**************************************************************************************************
*     File Name :                        hw_lcd
*     Library/Module Name :              hw
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             LCD 硬件参数配置头文件
*
*     包含内容：
*       1. 屏幕方向（竖屏 / 横屏 / 翻转）
*       2. 屏幕分辨率（自动根据方向算出宽高）
*       3. 1 行缓存大小
*       4. 颜色修正（解决 RGB/BGR、字节序问题）
*       5. 常用颜色常量
*       6. 颜色工具宏
*
*     使用说明：
*       - 修改屏幕方向，只改 HW_LCD_DIRECTION_MASK
*       - 修改颜色显示不对，只改 HW_LCD_COLOR_MODE
*       - 其他宏不需要动
**************************************************************************************************/
#ifndef HW_LCD_H
#define HW_LCD_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"


/*-------------------------- 2. 屏幕方向 ---------------------------------*/
/* 取值：
 *     HW_LCD_DIRECTION_0 : 竖屏        （320 × 480）
 *     HW_LCD_DIRECTION_1 : 竖屏翻转    （320 × 480）
 *     HW_LCD_DIRECTION_2 : 横屏        （480 × 320）
 *     HW_LCD_DIRECTION_3 : 横屏翻转    （480 × 320）
 *
 * 说明：
 *     - 方向由 ST7796 的 MADCTL（0x36）寄存器控制
 *     - 不同 LCD 排线方向会导致 0/2 或 1/3 反了，如果屏幕显示方向
 *       与预期不符，试一下相邻的那个值
 */
#define HW_LCD_DIRECTION_0              (0U)    /* 竖屏 */
#define HW_LCD_DIRECTION_1              (1U)    /* 竖屏翻转 */
#define HW_LCD_DIRECTION_2              (2U)    /* 横屏 */
#define HW_LCD_DIRECTION_3              (3U)    /* 横屏翻转 */

#define HW_LCD_DIRECTION_MASK           HW_LCD_DIRECTION_2    /* ★ 改这里切换方向 */


/*-------------------------- 3. 屏幕分辨率（根据方向自动决定） ------------*/
/* 说明：
 *     - HW_LCD_WIDTH  = 水平方向像素数
 *     - HW_LCD_HEIGHT = 垂直方向像素数
 *     - HW_LCD_MADCTL = 写入 0x36 寄存器的值
 *       各 bit 含义（ST7796）：
 *         MY  bit7 : 行地址顺序
 *         MX  bit6 : 列地址顺序
 *         MV  bit5 : 行列交换（0=竖屏，1=横屏）
 *         ML  bit4 : 垂直刷新方向
 *         BGR bit3 : RGB/BGR 顺序
 *         MH  bit2 : 水平刷新方向
 */
#if   (HW_LCD_DIRECTION_MASK == HW_LCD_DIRECTION_0)
    #define HW_LCD_WIDTH                (320U)
    #define HW_LCD_HEIGHT               (480U)
    #define HW_LCD_MADCTL               (0x40U)     /* 竖屏 */
#elif (HW_LCD_DIRECTION_MASK == HW_LCD_DIRECTION_1)
    #define HW_LCD_WIDTH                (320U)
    #define HW_LCD_HEIGHT               (480U)
    #define HW_LCD_MADCTL               (0xC0U)     /* 竖屏翻转 */
#elif (HW_LCD_DIRECTION_MASK == HW_LCD_DIRECTION_2)
    #define HW_LCD_WIDTH                (480U)
    #define HW_LCD_HEIGHT               (320U)
    #define HW_LCD_MADCTL               (0x20U)     /* 横屏 */
#elif (HW_LCD_DIRECTION_MASK == HW_LCD_DIRECTION_3)
    #define HW_LCD_WIDTH                (480U)
    #define HW_LCD_HEIGHT               (320U)
    #define HW_LCD_MADCTL               (0xE0U)     /* 横屏翻转 */
#else
    #error "HW_LCD_DIRECTION_MASK 取值必须为 0~3"
#endif


/*-------------------------- 4. 缓存大小 ---------------------------------*/
/* 说明：
 *     屏幕驱动采用"1 行缓存"方案（省 RAM）。
 *     HW_LCD_CACHE_LINES = 1 时，缓存只装 1 行像素。
 *     每行像素 = HW_LCD_WIDTH 个，每个像素 2 字节（RGB565）。
 *
 * 当前大小（横屏 480 宽）：1 × 480 × 2 = 960 字节
 * 竖屏 320 宽：            1 × 320 × 2 = 640 字节
 */
#define HW_LCD_CACHE_LINES              (1U)
#define HW_LCD_CACHE_WIDTH              (HW_LCD_WIDTH)
#define HW_LCD_CACHE_SIZE               (HW_LCD_CACHE_LINES * HW_LCD_CACHE_WIDTH * 2U)


/*-------------------------- 5. 颜色修正 ---------------------------------*/
/* 为什么需要修正？
 *     标准 RGB565 的颜色格式是：
 *         bit[15:11] = R (5 位)
 *         bit[10:5]  = G (6 位)
 *         bit[4:0]   = B (5 位)
 *
 *     但不同的 LCD 模块排线/驱动芯片可能有差异：
 *         - 有些模块 G 和 B 通道接反了
 *         - 有些模块 R 和 B 通道接反了
 *         - 有些模块需要交换高低字节
 *     如果显示的颜色不对（比如白色变成黄色），就需要打开修正。
 *
 * 各种模式说明：
 *     HW_LCD_COLOR_MODE = 0 : 标准 RGB565，不做任何处理
 *     HW_LCD_COLOR_MODE = 1 : R/B 交换（红蓝互换）
 *     HW_LCD_COLOR_MODE = 2 : G/B 交换（绿蓝互换）  ← 当前使用
 *     HW_LCD_COLOR_MODE = 3 : R/G 交换（红绿互换）
 *     HW_LCD_COLOR_MODE = 4 : 字节序交换（高低字节互换）
 *
 * 调试方法：
 *     先写 HW_LCD_COLOR_FIX(0xFFFFU) 显示白色。
 *     - 显示白色   → 模式正确
 *     - 显示黄色   → G/B 反了，改用模式 2
 *     - 显示青色   → R/B 反了，改用模式 1
 *     - 显示品红   → R/G 反了，改用模式 3
 */
#define HW_LCD_COLOR_MODE               (2U)    /* ★ 改这里切换修正模式 */

#if   (HW_LCD_COLOR_MODE == 0U)
    /* 标准 RGB565：原样输出 */
    #define HW_LCD_COLOR_FIX(c)   ((uint16_t)(c))

#elif (HW_LCD_COLOR_MODE == 1U)
    /* R/B 交换：
     *   原 R (bit15-11) → 新 B (bit4-0)   右移 11 位
     *   原 G (bit10-5)  → 不变
     *   原 B (bit4-0)   → 新 R (bit15-11) 左移 11 位 */
    #define HW_LCD_COLOR_FIX(c)   ((uint16_t)( \
        (((c) & 0xF800U) >> 11) | \
        ( (c) & 0x07E0U)        | \
        (((c) & 0x001FU) << 11)   \
    ))

#elif (HW_LCD_COLOR_MODE == 2U)
    /* G/B 交换：
     *   原 R (bit15-11) → 不变
     *   原 G (bit10-5)  → 新 B (bit4-0)   取高 5 位（右移 6 位）
     *   原 B (bit4-0)   → 新 G (bit10-5)  左移 6 位 */
    #define HW_LCD_COLOR_FIX(c)   ((uint16_t)( \
        ( (c) & 0xF800U)          | \
        (((c) & 0x001FU) << 6)    | \
        (((c) >> 6)     & 0x001FU)  \
    ))

#elif (HW_LCD_COLOR_MODE == 3U)
    /* R/G 交换：
     *   原 R (bit15-11) → 新 G (bit10-5)  右移 6 位后取低 5 位
     *   原 G (bit10-5)  → 新 R (bit15-11) 右移 6 位后取高 5 位
     *   原 B (bit4-0)   → 不变 */
    #define HW_LCD_COLOR_FIX(c)   ((uint16_t)( \
        ((((c) >> 6)  & 0x1FU) << 11) | \
        ((((c) >> 11) & 0x1FU) << 5)  | \
        ( (c) & 0x001FU)                \
    ))

#elif (HW_LCD_COLOR_MODE == 4U)
    /* 字节序交换：高字节和低字节互换 */
    #define HW_LCD_COLOR_FIX(c)   ((uint16_t)( \
        (((c) & 0x00FFU) << 8) | \
        (((c) & 0xFF00U) >> 8)   \
    ))

#else
    #error "HW_LCD_COLOR_MODE 取值必须为 0~4"
#endif


/*-------------------------- 6. 常用颜色常量 -----------------------------*/
/* 说明：
 *     所有颜色都经过 HW_LCD_COLOR_FIX() 修正，可以直接传给 LCD 绘制函数。
 *     未修正的原始 RGB565 值写在括号里。
 */
/* ---- 基础色 ---- */
#define HW_LCD_COLOR_BLACK      HW_LCD_COLOR_FIX(0x0000U)   /* 黑  (0,0,0) */
#define HW_LCD_COLOR_WHITE      HW_LCD_COLOR_FIX(0xFFFFU)   /* 白  (255,255,255) */
#define HW_LCD_COLOR_RED        HW_LCD_COLOR_FIX(0xF800U)   /* 红  (255,0,0) */
#define HW_LCD_COLOR_GREEN      HW_LCD_COLOR_FIX(0x07E0U)   /* 绿  (0,255,0) */
#define HW_LCD_COLOR_BLUE       HW_LCD_COLOR_FIX(0x001FU)   /* 蓝  (0,0,255) */

/* ---- 合成色 ---- */
#define HW_LCD_COLOR_YELLOW     HW_LCD_COLOR_FIX(0xFFE0U)   /* 黄  = 红 + 绿 */
#define HW_LCD_COLOR_CYAN       HW_LCD_COLOR_FIX(0x07FFU)   /* 青  = 绿 + 蓝 */
#define HW_LCD_COLOR_MAGENTA    HW_LCD_COLOR_FIX(0xF81FU)   /* 品红 = 红 + 蓝 */

/* ---- 灰色系 ---- */
#define HW_LCD_COLOR_GRAY       HW_LCD_COLOR_FIX(0x8410U)   /* 中灰 */
#define HW_LCD_COLOR_DARKGRAY   HW_LCD_COLOR_FIX(0x4208U)   /* 暗灰 */
#define HW_LCD_COLOR_LIGHTGRAY  HW_LCD_COLOR_FIX(0xC618U)   /* 亮灰 */

/* ---- 扩展色 ---- */
#define HW_LCD_COLOR_ORANGE     HW_LCD_COLOR_FIX(0xFD20U)   /* 橙 */
#define HW_LCD_COLOR_PURPLE     HW_LCD_COLOR_FIX(0x8010U)   /* 紫 */
#define HW_LCD_COLOR_PINK       HW_LCD_COLOR_FIX(0xF81FU)   /* 粉（同品红） */
#define HW_LCD_COLOR_BROWN      HW_LCD_COLOR_FIX(0xA145U)   /* 棕 */
#define HW_LCD_COLOR_NAVY       HW_LCD_COLOR_FIX(0x000FU)   /* 深蓝 */
#define HW_LCD_COLOR_GOLD       HW_LCD_COLOR_FIX(0xFEA0U)   /* 金 */


/*-------------------------- 7. 颜色工具宏 -------------------------------*/
/* 说明：
 *     需要手动合成颜色时用这些宏，比如：
 *         uint16_t my_color = HW_LCD_RGB565(31U, 32U, 15U);
 */

/* 把 R(5位) G(6位) B(5位) 合成标准 RGB565 值 */
#define HW_LCD_RGB565(r, g, b)      ((uint16_t)((((r) & 0x1FU) << 11) | \
                                                (((g) & 0x3FU) << 5)  | \
                                                ( (b) & 0x1FU)))

/* 从 RGB565 值里取分量（未修正的原始值） */
#define HW_LCD_RGB565_GET_R(c)      ((uint8_t)((((c) >> 11) & 0x1FU) << 3))
#define HW_LCD_RGB565_GET_G(c)      ((uint8_t)((((c) >> 5)  & 0x3FU) << 2))
#define HW_LCD_RGB565_GET_B(c)      ((uint8_t)(( (c)        & 0x1FU) << 3))


#endif /* HW_LCD_H */
