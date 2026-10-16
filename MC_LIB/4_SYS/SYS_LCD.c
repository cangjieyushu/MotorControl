/**************************************************************************************************
*     File Name :                        sys_lcd.c
*     Abstract Description :             ST7796 LCD 显示层
*                                        字模数据在 sys_font.c
*                                        底层 HAL 接口在 hal_lcd.h
**************************************************************************************************/
#include "sys_lcd.h"
#include <string.h>


/*-------------------------- 1. 内部变量 -----------------------------*/
static uint16_t lcd_cache[HW_LCD_CACHE_LINES * HW_LCD_CACHE_WIDTH];
static uint16_t lcd_cache_y_start = 0U;
static uint8_t  lcd_cache_dirty   = 0U;


/*-------------------------- 2. 基础接口 -----------------------------*/
void lcd_write_cmd(uint8_t cmd)
{
    HAL_LCD_Dc_Cmd();
    HAL_LCD_Cs_Low();
    HAL_LCD_SpiRwByte(cmd);
    HAL_LCD_Cs_High();
}

void lcd_write_data(uint8_t data)
{
    HAL_LCD_Dc_Data();
    HAL_LCD_Cs_Low();
    HAL_LCD_SpiRwByte(data);
    HAL_LCD_Cs_High();
}

void lcd_set_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    lcd_write_cmd(0x2AU);
    lcd_write_data((uint8_t)(x1 >> 8));
    lcd_write_data((uint8_t)(x1 & 0xFFU));
    lcd_write_data((uint8_t)(x2 >> 8));
    lcd_write_data((uint8_t)(x2 & 0xFFU));

    lcd_write_cmd(0x2BU);
    lcd_write_data((uint8_t)(y1 >> 8));
    lcd_write_data((uint8_t)(y1 & 0xFFU));
    lcd_write_data((uint8_t)(y2 >> 8));
    lcd_write_data((uint8_t)(y2 & 0xFFU));

    lcd_write_cmd(0x2CU);
}


/*-------------------------- 3. 缓存接口 -----------------------------*/
void lcd_cache_init(void)
{
    uint32_t total = HW_LCD_CACHE_LINES * HW_LCD_CACHE_WIDTH;
    for (uint32_t i = 0U; i < total; i++)
    {
        lcd_cache[i] = 0U;
    }
    lcd_cache_y_start = 0U;
    lcd_cache_dirty   = 0U;
}

void lcd_cache_begin(uint16_t y_start)
{
    lcd_cache_y_start = y_start;
    lcd_cache_dirty   = 0U;
}

void lcd_cache_set_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    if (x >= HW_LCD_WIDTH)
    {
        return;
    }
    if (y < lcd_cache_y_start ||
        y >= lcd_cache_y_start + HW_LCD_CACHE_LINES)
    {
        return;
    }
    uint16_t row = y - lcd_cache_y_start;
    lcd_cache[row * HW_LCD_CACHE_WIDTH + x] = color;
    lcd_cache_dirty = 1U;
}

void lcd_cache_fill(uint16_t color)
{
    uint32_t total = HW_LCD_CACHE_LINES * HW_LCD_CACHE_WIDTH;
    for (uint32_t i = 0U; i < total; i++)
    {
        lcd_cache[i] = color;
    }
    lcd_cache_dirty = 1U;
}

void lcd_cache_flush(void)
{
    if (lcd_cache_dirty == 0U)
    {
        return;
    }

    lcd_set_window(0U, lcd_cache_y_start,
                   HW_LCD_WIDTH - 1U,
                   lcd_cache_y_start + HW_LCD_CACHE_LINES - 1U);

    HAL_LCD_Dc_Data();
    HAL_LCD_Cs_Low();
    HAL_LCD_DmaSendBlock((const uint8_t *)lcd_cache, HW_LCD_CACHE_SIZE);
    HAL_LCD_Cs_High();

    lcd_cache_dirty = 0U;
}


/*-------------------------- 4. 便捷填充 -----------------------------*/
void lcd_fill_color(uint16_t color)
{
    uint32_t total = HW_LCD_CACHE_LINES * HW_LCD_CACHE_WIDTH;
    for (uint32_t i = 0U; i < total; i++)
    {
        lcd_cache[i] = color;
    }

    lcd_set_window(0U, 0U, HW_LCD_WIDTH - 1U, HW_LCD_HEIGHT - 1U);

    HAL_LCD_Dc_Data();
    HAL_LCD_Cs_Low();

    uint32_t bytes = (uint32_t)HW_LCD_WIDTH * HW_LCD_HEIGHT * 2U;
    while (bytes > 0U)
    {
        uint32_t chunk = (bytes > HW_LCD_CACHE_SIZE) ? HW_LCD_CACHE_SIZE : bytes;
        HAL_LCD_DmaSendBlock((const uint8_t *)lcd_cache, chunk);
        bytes -= chunk;
    }

    HAL_LCD_Cs_High();
}

void lcd_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    if (x >= HW_LCD_WIDTH || y >= HW_LCD_HEIGHT)
    {
        return;
    }
    if (x + w > HW_LCD_WIDTH)  { w = HW_LCD_WIDTH  - x; }
    if (y + h > HW_LCD_HEIGHT) { h = HW_LCD_HEIGHT - y; }
    if (w == 0U || h == 0U)
    {
        return;
    }

    for (uint16_t r = 0U; r < HW_LCD_CACHE_LINES; r++)
    {
        for (uint16_t c = 0U; c < w; c++)
        {
            lcd_cache[r * HW_LCD_CACHE_WIDTH + c] = color;
        }
    }

    lcd_set_window(x, y, x + w - 1U, y + h - 1U);
    HAL_LCD_Dc_Data();
    HAL_LCD_Cs_Low();

    uint16_t rows_done = 0U;
    while (rows_done < h)
    {
        uint16_t rows_this = h - rows_done;
        if (rows_this > HW_LCD_CACHE_LINES)
        {
            rows_this = HW_LCD_CACHE_LINES;
        }
        uint32_t bytes = (uint32_t)rows_this * w * 2U;
        HAL_LCD_DmaSendBlock((const uint8_t *)lcd_cache, bytes);
        rows_done += rows_this;
    }

    HAL_LCD_Cs_High();
}


/*-------------------------- 5. 32×32 汉字 ------------------------------*/
void lcd_draw_hz32(uint16_t x, uint16_t y, uint16_t code, uint16_t fg, uint16_t bg)
{
    const uint8_t *hz = hz32_find(code);
    if (hz == 0)
    {
        lcd_fill_rect(x, y, 32U, 32U, bg);
        return;
    }
    if (x + 32U > HW_LCD_WIDTH)  { return; }
    if (y + 32U > HW_LCD_HEIGHT) { return; }

    for (uint16_t row = 0U; row < 32U; row++)
    {
        lcd_cache_begin(y + row);

        /* 先铺背景 */
        for (uint16_t col = 0U; col < 32U; col++)
        {
            lcd_cache_set_pixel(x + col, y + row, bg);
        }

        /* 再叠字模 */
        for (uint16_t col = 0U; col < 32U; col++)
        {
            uint8_t byte = hz[(row >> 3) * 32U + col];
            uint8_t bit  = row & 7U;
            if (byte & (1U << bit))
            {
                lcd_cache_set_pixel(x + col, y + row, fg);
            }
        }

        /* 一行画完立刻 DMA 发（32 像素 = 64 字节） */
        lcd_set_window(x, y + row, x + 31U, y + row);
        HAL_LCD_Dc_Data();
        HAL_LCD_Cs_Low();
        HAL_LCD_DmaSendBlock((const uint8_t *)&lcd_cache[x], 32U * 2U);
        HAL_LCD_Cs_High();
    }
}

void lcd_draw_hz32_str(uint16_t x, uint16_t y, const uint16_t *str, uint16_t fg, uint16_t bg)
{
    uint16_t cx = x;
    while (*str != 0U)
    {
        if (cx + 32U > HW_LCD_WIDTH)
        {
            cx = x;
            y += 56U;
            if (y + 32U > HW_LCD_HEIGHT)
            {
                break;
            }
        }
        lcd_draw_hz32(cx, y, *str, fg, bg);
        cx += 32U;
        str++;
    }
}


/*-------------------------- 6. 16×32 字符 ------------------------------*/
void lcd_draw_hz16x32(uint16_t x, uint16_t y, uint16_t code, uint16_t fg, uint16_t bg)
{
    const uint8_t *hz = hz16x32_find(code);
    if (hz == 0)
    {
        lcd_fill_rect(x, y, 16U, 32U, bg);
        return;
    }
    if (x + 16U > HW_LCD_WIDTH)  { return; }
    if (y + 32U > HW_LCD_HEIGHT) { return; }

    for (uint16_t row = 0U; row < 32U; row++)
    {
        lcd_cache_begin(y + row);

        for (uint16_t col = 0U; col < 16U; col++)
        {
            lcd_cache_set_pixel(x + col, y + row, bg);
        }

        for (uint16_t col = 0U; col < 16U; col++)
        {
            uint8_t byte = hz[(row >> 3) * 16U + col];
            uint8_t bit  = row & 7U;
            if (byte & (1U << bit))
            {
                lcd_cache_set_pixel(x + col, y + row, fg);
            }
        }

        lcd_set_window(x, y + row, x + 15U, y + row);
        HAL_LCD_Dc_Data();
        HAL_LCD_Cs_Low();
        HAL_LCD_DmaSendBlock((const uint8_t *)&lcd_cache[x], 16U * 2U);
        HAL_LCD_Cs_High();
    }
}

void lcd_draw_hz16x32_str(uint16_t x, uint16_t y, const uint16_t *str, uint16_t fg, uint16_t bg)
{
    uint16_t cx = x;
    while (*str != 0U)
    {
        if (cx + 16U > HW_LCD_WIDTH)
        {
            cx = x;
            y += 32U;
            if (y + 32U > HW_LCD_HEIGHT)
            {
                break;
            }
        }
        lcd_draw_hz16x32(cx, y, *str, fg, bg);
        cx += 16U;
        str++;
    }
}


/*-------------------------- 7. ST7796 初始化 ---------------------------*/
static void lcd_reset(void)
{
    HAL_LCD_Rst_High();
    HAL_LCD_DelayMs(10U);
    HAL_LCD_Rst_Low();
    HAL_LCD_DelayMs(20U);
    HAL_LCD_Rst_High();
    HAL_LCD_DelayMs(120U);
}

static void st7796_init(void)
{
    lcd_reset();

    lcd_write_cmd(0x01U);
    HAL_LCD_DelayMs(120U);
    lcd_write_cmd(0x11U);
    HAL_LCD_DelayMs(120U);

    lcd_write_cmd(0x36U);
    lcd_write_data(HW_LCD_MADCTL);

    lcd_write_cmd(0x3AU);
    lcd_write_data(0x55U);

    lcd_write_cmd(0xF0U); lcd_write_data(0xC3U);
    lcd_write_cmd(0xF0U); lcd_write_data(0x96U);
    lcd_write_cmd(0xB4U); lcd_write_data(0x01U);
    lcd_write_cmd(0xB6U);
    lcd_write_data(0x80U);
    lcd_write_data(0x02U);
    lcd_write_data(0x3BU);

    lcd_write_cmd(0xE8U);
    lcd_write_data(0x40U); lcd_write_data(0x8AU);
    lcd_write_data(0x00U); lcd_write_data(0x00U);
    lcd_write_data(0x29U); lcd_write_data(0x19U);
    lcd_write_data(0xA5U); lcd_write_data(0x33U);

    lcd_write_cmd(0xC1U); lcd_write_data(0x06U);
    lcd_write_cmd(0xC2U); lcd_write_data(0xA7U);
    lcd_write_cmd(0xC5U); lcd_write_data(0x18U);
    HAL_LCD_DelayMs(10U);

    lcd_write_cmd(0xE0U);
    lcd_write_data(0xF0U); lcd_write_data(0x09U);
    lcd_write_data(0x0BU); lcd_write_data(0x06U);
    lcd_write_data(0x04U); lcd_write_data(0x15U);
    lcd_write_data(0x2FU); lcd_write_data(0x54U);
    lcd_write_data(0x42U); lcd_write_data(0x3CU);
    lcd_write_data(0x17U); lcd_write_data(0x14U);
    lcd_write_data(0x18U); lcd_write_data(0x1BU);

    lcd_write_cmd(0xE1U);
    lcd_write_data(0xE0U); lcd_write_data(0x09U);
    lcd_write_data(0x0BU); lcd_write_data(0x06U);
    lcd_write_data(0x04U); lcd_write_data(0x03U);
    lcd_write_data(0x2BU); lcd_write_data(0x43U);
    lcd_write_data(0x42U); lcd_write_data(0x3BU);
    lcd_write_data(0x16U); lcd_write_data(0x14U);
    lcd_write_data(0x17U); lcd_write_data(0x1BU);

    lcd_write_cmd(0xF0U); lcd_write_data(0x3CU);
    lcd_write_cmd(0xF0U); lcd_write_data(0x69U);

    HAL_LCD_DelayMs(120U);
    lcd_write_cmd(0x29U);
    HAL_LCD_DelayMs(50U);
}


/*-------------------------- 8. 初始化入口 -----------------------------*/
void lcd_init(void)
{
    lcd_cache_init();
    st7796_init();
    lcd_fill_color(HW_LCD_COLOR_BLACK);
}
