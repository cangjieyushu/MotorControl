/**************************************************************************************************
* 文件名   : SYS_LCD.h
* 功能     : LCD 驱动的对外接口声明（头文件）
* 说明     : 这个文件只做"声明"，不做具体实现。其他 .c 文件 include 它就能调用 LCD 相关函数
**************************************************************************************************/
#ifndef SYS_LCD_H        /* 防止头文件被重复 include 的固定写法 */
#define SYS_LCD_H

#include "bsp.h"        /* 引入板级支持包，里面有 SPI、GPIO 等底层定义 */

/*=====================================================================
 * 一、基础接口（LCD 初始化 / 写命令 / 写数据 / 设置窗口）
 *=====================================================================*/

/* LCD 初始化：上电时调用一次，完成缓存清零 + ST7796 寄存器配置 + 清屏 */
void lcd_init(void);

/* 向 LCD 写一个"命令字节"（DC 引脚拉低）
 * LCD 内部有很多寄存器，通过命令来配置。比如 0x2A 是设置列地址 */
void lcd_write_cmd(uint8_t cmd);

/* 向 LCD 写一个"数据字节"（DC 引脚拉高）
 * 命令后面跟的参数、像素颜色数据，都走这个函数 */
void lcd_write_data(uint8_t data);

/* 设置 LCD 的显示窗口（一个矩形区域）
 * x1,y1 = 左上角坐标；x2,y2 = 右下角坐标
 * 设置好窗口后，后续写入的像素会按从左到右、从上到下的顺序自动填充 */
void lcd_set_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);


/*=====================================================================
 * 二、DMA 接口（大数据用 DMA 传输，省 CPU）
 *=====================================================================*/

/* 用 DMA 发送一块数据（阻塞式：函数返回时数据一定发送完了）
 * data = 要发送的数据首地址；len = 字节数 */
void lcd_dma_send_block(const uint8_t *data, uint32_t len);

/* 自动拆块发送：如果要发的数据超过缓存大小，自动拆成多块依次发送 */
void lcd_dma_send_bytes(const uint8_t *data, uint32_t len);

/* 等待上一次 DMA 传输完成（阻塞等待） */
void lcd_dma_wait(void);


/*=====================================================================
 * 三、缓存接口（把要显示的内容先画到内存，再一次性发给 LCD）
 *=====================================================================*/

/* 缓存初始化：全部清零 */
void lcd_cache_init(void);

/* 告诉缓存：接下来要操作哪一行（y 坐标）
 * 每次画一行新像素前，要先调用这个函数 */
void lcd_cache_begin(uint16_t y_start);

/* 往缓存里写一个像素（x,y 是屏幕绝对坐标，color 是 RGB565 颜色） */
void lcd_cache_set_pixel(uint16_t x, uint16_t y, uint16_t color);

/* 用单一颜色填满整个缓存（只改内存，不发给 LCD） */
void lcd_cache_fill(uint16_t color);

/* 把缓存里的内容通过 DMA 发给 LCD（真正让屏幕上出现图案） */
void lcd_cache_flush(void);


/*=====================================================================
 * 四、便捷填充（整屏 / 矩形）
 *=====================================================================*/

/* 用单一颜色填充整个屏幕 */
void lcd_fill_color(uint16_t color);

/* 画一个实心矩形：左上角(x,y)，宽 w，高 h，颜色 color */
void lcd_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);


/*=====================================================================
 * 五、16×16 汉字接口（小字，一般不用，保留）
 *=====================================================================*/

/* 字模表项结构体：一个汉字用 "Unicode 编码 + 32 字节点阵数据" 表示 */
typedef struct {
    uint16_t code;          /* 汉字的 Unicode 编码，比如 '你' 是 0x4F60 */
    const uint8_t *data;    /* 指向 32 字节字模数据的指针 */
} hz16_t;

/* 绘制一个 16×16 汉字（不是重点，注释略） */
void lcd_draw_hz16(uint16_t x, uint16_t y, uint16_t code,
                   uint16_t color, uint16_t bg);

/* 绘制一串 16×16 汉字 */
void lcd_draw_hz16_str(uint16_t x, uint16_t y, const uint16_t *str,
                       uint16_t color, uint16_t bg);


/*=====================================================================
 * 六、32×32 汉字接口（大字，主界面用这个）
 *=====================================================================*/

/* 字模表项结构体：一个 32×32 汉字用 128 字节表示 */
typedef struct {
    uint16_t code;          /* 汉字 Unicode 编码 */
    const uint8_t *data;    /* 指向 128 字节点阵数据的指针 */
} hz32_t;

/* 字模表（在 SYS_LCD.c 中定义）：
 * 里面存了所有用到的汉字 "编码 -> 数据" 的对应关系 */
extern const hz32_t   hz32_table[];
extern const uint16_t hz32_count;       /* 表里有多少个汉字 */

/* 根据 Unicode 编码查找字模数据；找不到返回 0 */
const uint8_t *hz32_find(uint16_t code);

/* 绘制一个 32×32 汉字：
 * x,y   = 左上角坐标
 * code  = 汉字 Unicode 编码
 * fg    = 前景色（字的颜色）
 * bg    = 背景色 */
void lcd_draw_hz32(uint16_t x, uint16_t y, uint16_t code,
                   uint16_t fg, uint16_t bg);

/* 绘制一串 32×32 汉字（以 0 结尾的 Unicode 数组） */
void lcd_draw_hz32_str(uint16_t x, uint16_t y, const uint16_t *str,
                       uint16_t fg, uint16_t bg);


/*=====================================================================
 * 七、16×32 字符接口（数字、字母、符号）
 *=====================================================================*/

/* 字模表项结构体：一个 16×32 字符用 64 字节表示 */
typedef struct {
    uint16_t code;          /* 字符 ASCII 码，比如 '0' 是 0x30 */
    const uint8_t *data;    /* 指向 64 字节点阵数据的指针 */
} hz16x32_t;

extern const hz16x32_t hz16x32_table[];
extern const uint16_t  hz16x32_count;
const uint8_t *hz16x32_find(uint16_t code);

/* 绘制一个 16×32 字符（数字/字母/符号） */
void lcd_draw_hz16x32(uint16_t x, uint16_t y, uint16_t code,
                      uint16_t fg, uint16_t bg);

/* 绘制一串 16×32 字符 */
void lcd_draw_hz16x32_str(uint16_t x, uint16_t y, const uint16_t *str,
                          uint16_t fg, uint16_t bg);


/*=====================================================================
 * 八、滚动显示接口（不用可以忽略）
 *=====================================================================*/

/* 初始化一行滚动显示 */
void scroll_init(const uint16_t *text, uint16_t x, uint16_t y,
                 uint16_t color, uint16_t bg);

/* 设置所有滚动行的速度 */
void scroll_set_all_speed(uint8_t rows);

/* 设置单独某一行的滚动速度 */
void scroll_set_line_speed(uint8_t line, uint8_t rows);

/* 10ms 任务，在定时器里循环调用 */
void scroll_task_10ms(void);

#endif /* SYS_LCD_H */