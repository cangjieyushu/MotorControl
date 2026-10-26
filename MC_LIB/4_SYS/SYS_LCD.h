/**
 * @file    sys_lcd.h
 * @brief   LCD 驱动对外接口（协议层 + 显示层）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef SYS_LCD_H
#define SYS_LCD_H

/* ======================== 1. Includes ===================== */
#include "hal_lcd.h"
#include "sys_font.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */
/* ---- 基础接口 ---- */
void lcd_init(void);
void lcd_write_cmd(uint8_t cmd);
void lcd_write_data(uint8_t data);
void lcd_set_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/* ---- 缓存接口 ---- */
void lcd_cache_init(void);
void lcd_cache_begin(uint16_t y_start);
void lcd_cache_set_pixel(uint16_t x, uint16_t y, uint16_t color);
void lcd_cache_fill(uint16_t color);
void lcd_cache_flush(void);

/* ---- 便捷填充 ---- */
void lcd_fill_color(uint16_t color);
void lcd_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

/* ---- 32×32 汉字 ---- */
void lcd_draw_hz32(uint16_t x, uint16_t y, uint16_t code, uint16_t fg, uint16_t bg);
void lcd_draw_hz32_str(uint16_t x, uint16_t y, const uint16_t *str, uint16_t fg, uint16_t bg);

/* ---- 16×32 字符 ---- */
void lcd_draw_hz16x32(uint16_t x, uint16_t y, uint16_t code, uint16_t fg, uint16_t bg);
void lcd_draw_hz16x32_str(uint16_t x, uint16_t y, const uint16_t *str, uint16_t fg, uint16_t bg);

#endif /* SYS_LCD_H */
