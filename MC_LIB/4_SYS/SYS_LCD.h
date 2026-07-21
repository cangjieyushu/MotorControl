/**************************************************************************************************
*     File Name :                        SYS_LCD.h
*     Library/Module Name :              SYS
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             ST7567 LCD 驱动头文件（精简版）
**************************************************************************************************/
#ifndef SYS_LCD_H
#define SYS_LCD_H


#include "SYSTASK.h"
#include "UARTS.h"


#define ST7567_WIDTH          128
#define ST7567_HEIGHT         64
#define ST7567_PAGE_NUM       8


extern uint8_t framebuffer[ST7567_PAGE_NUM][ST7567_WIDTH];


void ST7567_Init(void);       /* 初始化状态机，需周期性调用 */
void ST7567_Refresh(void);    /* 分页刷新状态机，需周期性调用（10ms） */


/* ==================== 汉字显示 API ==================== */

/**
 * @brief  在帧缓冲中绘制一个 16x16 汉字
 * @param  x       左上角 X 坐标（0 ~ 127）
 * @param  y       左上角 Y 坐标（0 ~ 63），建议为 8 的倍数，否则性能略降
 * @param  bitmap  字模数据指针，16x16 点阵，32 字节逐列式，高位在上
 * @param  color   前景色：1 = 点亮像素（黑色），0 = 熄灭（白色）
 * @param  bgcolor 背景色：1 = 点亮（黑色背景），0 = 熄灭（白色背景）
 */
void LCD_PutChinese(uint8_t x, uint8_t y, const uint8_t *bitmap,
                    uint8_t color, uint8_t bgcolor);

/* 汉字字模声明（示例：故障、电压、温度） */
extern const uint8_t HZK_GuZhang[32];  /* 故障 */
extern const uint8_t HZK_DianYa[32];   /* 电压 */
extern const uint8_t HZK_WenDu[32];    /* 温度 */

#endif