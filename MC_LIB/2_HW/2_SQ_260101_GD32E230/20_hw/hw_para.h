/*
*     File Name :                        hw_para
*     Library/Module Name :              hw
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             硬件电路参数
*/


#ifndef HW_PARA_H
#define HW_PARA_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
//ADC硬件参数设置
#define HAL_ADC_REF_VOLTAGE_V                   (3.3f)                  //V，ADC参考电平
#define HAL_ADC_SCALE_BIT                       (4095.0f)               //lsb，ADC精度


//母线电压采样
#define HAL_ADC_VOLTAGE_RESISTOR_UP             (780.0f)                //母线电压采样上分压电阻
#define HAL_ADC_VOLTAGE_RESISTOR_DOWN           (3.9f)                  //母线电压采样下分压电阻
#define HAL_ADC_VOLTAGE_COEFF                   ((HAL_ADC_VOLTAGE_RESISTOR_UP+HAL_ADC_VOLTAGE_RESISTOR_DOWN)/HAL_ADC_VOLTAGE_RESISTOR_DOWN)
#define HAL_ADC_VOLTAGE_MAX                     (HAL_ADC_REF_VOLTAGE_V*HAL_ADC_VOLTAGE_COEFF)   //V，最大采样电压
#define HAL_ADC_VOLTAGE_SCALE                   (HAL_ADC_VOLTAGE_MAX/HAL_ADC_SCALE_BIT)         //V/lsb，电压刻度


//相电流采样
#define HAL_ADC_CURRENT_OFFSET                  (0.55f)                 //V，电流采样偏置电压
#define HAL_ADC_CURRENT_GAIN                    (15.0f)                 //相电流采样放大倍数
#define HAL_ADC_CURRENT_RESISTOR                (0.005f)                //Ω，相电流采样电阻
#define HAL_ADC_CURRENT_COEFF                   (1.0f/(HAL_ADC_CURRENT_RESISTOR*HAL_ADC_CURRENT_GAIN))
#define HAL_ADC_CURRENT_MAX                     (HAL_ADC_REF_VOLTAGE_V*HAL_ADC_CURRENT_COEFF)   //A，最大采样电流
#define HAL_ADC_CURRENT_SCALE                   (HAL_ADC_CURRENT_MAX/HAL_ADC_SCALE_BIT)         //A/lsb，电流刻度



//HMI参数设置
#define HAL_HMI_DMA_RX_BUF_SIZE                 256     // DMA 线性接收缓冲区大小



//LCD参数设置
#define LCD_DIRECTION_0                         0
#define LCD_DIRECTION_1                         1
#define LCD_DIRECTION_2                         2
#define LCD_DIRECTION_3                         3
#define LCD_DIRECTION_MASK                      LCD_DIRECTION_2        //0：竖屏，1：竖屏翻转，2：横屏，3：横批翻转


#if(LCD_DIRECTION_MASK == LCD_DIRECTION_0)
#define LCD_WIDTH                               320
#define LCD_HEIGHT                              480
#define LCD_MADCTL                              0x40

#elif(LCD_DIRECTION_MASK == LCD_DIRECTION_1)
#define LCD_WIDTH                               320
#define LCD_HEIGHT                              480
#define LCD_MADCTL                              0xC0

#elif(LCD_DIRECTION_MASK == LCD_DIRECTION_2)
#define LCD_WIDTH                               480
#define LCD_HEIGHT                              320
#define LCD_MADCTL                              0x20

#elif(LCD_DIRECTION_MASK == LCD_DIRECTION_3)
#define LCD_WIDTH                               480
#define LCD_HEIGHT                              320
#define LCD_MADCTL                              0xE0

#endif


/* 块缓存：1 行 × 320 像素 × 2 字节 = 640 字节 */
#define LCD_CACHE_LINES                         1
#define LCD_CACHE_WIDTH                         LCD_WIDTH
#define LCD_CACHE_SIZE                          (LCD_CACHE_LINES * LCD_CACHE_WIDTH * 2)


/*============================================================
 *  LCD 颜色修正
 *  根据你的 LCD 模块实测结果，选择一种模式：
 *
 *   0 = 标准 RGB565   （不修正）
 *   1 = R/B 交换      （BGR 模式，红蓝互换）
 *   2 = G/B 交换      （绿蓝互换）
 *   3 = R/G 交换      （红绿互换）
 *   4 = 字节序交换     （高低字节互换）
 *============================================================*/
#define LCD_COLOR_MODE   2      /* ← 改这里 */

#if   LCD_COLOR_MODE == 0
    /* 标准：不做任何处理 */
    #define LCD_COLOR_FIX(c)   ((uint16_t)(c))

#elif LCD_COLOR_MODE == 1
    /* R/B 交换：5位R 与 5位B 对调，G 保持不变 */
    #define LCD_COLOR_FIX(c)   ((uint16_t)( \
        (((c) & 0xF800) >> 11) | \
        ((c)  & 0x07E0)        | \
        (((c) & 0x001F) << 11) \
    ))

#elif LCD_COLOR_MODE == 2
    /* G/B 交换：6位G 与 5位B 对调，R 保持不变
     * 原 G(6位, bit10-5) → 新 B(5位, bit4-0)  取高5位
     * 原 B(5位, bit4-0)  → 新 G(6位, bit10-5) 左移1位 */
    #define LCD_COLOR_FIX(c)   ((uint16_t)( \
        ((c) & 0xF800)          | \
        (((c) & 0x001F) << 6)   | \
        (((c) >> 6) & 0x001F)   \
    ))

#elif LCD_COLOR_MODE == 3
    /* R/G 交换：5位R 与 6位G 对调，B 保持不变
     * 原 G(6位, bit10-5) → 新 R(5位, bit15-11) 取高5位
     * 原 R(5位, bit15-11) → 新 G(6位, bit10-5)  左移1位 */
    #define LCD_COLOR_FIX(c)   ((uint16_t)( \
        ((((c) >> 6) & 0x1F) << 11) | \
        ((((c) >> 11) & 0x1F) << 5) | \
        ((c) & 0x001F)                \
    ))

#elif LCD_COLOR_MODE == 4
    /* 字节序交换：高字节与低字节互换 */
    #define LCD_COLOR_FIX(c)   ((uint16_t)( \
        (((c) & 0x00FF) << 8) | \
        (((c) & 0xFF00) >> 8)   \
    ))

#else
    #error "LCD_COLOR_MODE 取值必须为 0~4"
#endif


//LCD颜色
#define LCD_BLACK       LCD_COLOR_FIX(0x0000)      /* 黑 */
#define LCD_WHITE       LCD_COLOR_FIX(0xFFFF)      /* 白 */
#define LCD_RED         LCD_COLOR_FIX(0xF800)      /* 红 */
#define LCD_GREEN       LCD_COLOR_FIX(0x07E0)      /* 绿 */
#define LCD_BLUE        LCD_COLOR_FIX(0x001F)      /* 蓝 */

#define LCD_YELLOW      LCD_COLOR_FIX(0xFFE0)      /* 黄   (R+G) */
#define LCD_CYAN        LCD_COLOR_FIX(0x07FF)      /* 青   (G+B) */
#define LCD_MAGENTA     LCD_COLOR_FIX(0xF81F)      /* 品红 (R+B) */

#define LCD_GRAY        LCD_COLOR_FIX(0x8410)      /* 中灰 */
#define LCD_DARKGRAY    LCD_COLOR_FIX(0x4208)      /* 暗灰 */
#define LCD_LIGHTGRAY   LCD_COLOR_FIX(0xC618)      /* 亮灰 */

#define LCD_ORANGE      LCD_COLOR_FIX(0xFD20)      /* 橙 */
#define LCD_PURPLE      LCD_COLOR_FIX(0x8010)      /* 紫 */
#define LCD_PINK        LCD_COLOR_FIX(0xF81F)      /* 粉 */
#define LCD_BROWN       LCD_COLOR_FIX(0xA145)      /* 棕 */
#define LCD_NAVY        LCD_COLOR_FIX(0x000F)      /* 深蓝 */
#define LCD_GOLD        LCD_COLOR_FIX(0xFEA0)      /* 金 */


#endif /* HW_PARA_H */
