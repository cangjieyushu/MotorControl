/**************************************************************************************************
*     File Name :                        SYS_LCD.c
*     Library/Module Name :              SYS
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             ST7567 LCD 驱动源文件（精简优化版）
**************************************************************************************************/
#include "SYS_LCD.h"
#include <string.h>

/* ==================== 内部状态变量 ==================== */
static uint32_t Init_Phase       = 0U;
static uint32_t DMA_Fail_cnt     = 0U;       /* DMA 超时计数器（当前未用于重发，可扩展） */
static uint32_t LCD_Update_Flag  = 0U;       /* 1：有帧缓冲待刷新 */
static uint8_t  current_page     = 0U;       /* 当前待发送的页号（0~7） */

/* ==================== 帧缓冲 ==================== */
uint8_t framebuffer[ST7567_PAGE_NUM][ST7567_WIDTH];

/* ==================== 内部函数声明 ==================== */
static void ST7567_WriteCmd(uint8_t cmd);
static void ST7567_WriteDataBytes(uint8_t *data, uint16_t len);
static void ST7567_SetAddr(uint8_t page, uint8_t column);
static void ST7567_SendDMA(uint8_t *data, uint16_t len, uint8_t is_cmd);

/**********************************************************************************************
 * 函数名   : ST7567_RequestRefresh
 * 功  能   : 请求将 framebuffer 全屏刷新（置标志并复位页计数器）
 * 注  意   : 仅当上一次刷新已完成后才会接受新请求，防止重复启动。
 **********************************************************************************************/
void ST7567_RequestRefresh(void)
{
    if(LCD_Update_Flag == 0U)
    {
        current_page = 0U;
        LCD_Update_Flag = 1U;
    }
}

/**********************************************************************************************
 * 函数名   : ST7567_Init
 * 功  能   : LCD 初始化状态机，需每 10ms 调用一次
 * 说  明   : 内部用静态变量 Init_Phase 分步执行初始化序列，完成后锁定不再动作。
 *            初始化最后会自动请求一次清屏刷新（全白），由后续 ST7567_Refresh 完成。
 **********************************************************************************************/
void ST7567_Init(void)
{
    Init_Phase++;
    switch (Init_Phase)
    {
        case 10:  BSP_SPI_RST(0);           break;  /* 硬件复位拉低 */
        case 20:  BSP_SPI_RST(1);           break;  /* 释放复位 */
        case 30:  ST7567_WriteCmd(0xE2);    break;  /* 软件复位 */
        case 40:  ST7567_WriteCmd(0x2C);    break;  /* 升压1 */
        case 50:  ST7567_WriteCmd(0x2E);    break;  /* 升压2 */
        case 60:  ST7567_WriteCmd(0x2F);    break;  /* 升压3 */
        case 70:
            ST7567_WriteCmd(0xA2);           /* 偏压比 */
            ST7567_WriteCmd(0xC0);           /* 行顺序 */
            ST7567_WriteCmd(0xA0);           /* 列顺序 */
            ST7567_WriteCmd(0x40);           /* 起始行 */
            ST7567_WriteCmd(0x81);           /* 对比度命令 */
            ST7567_WriteCmd(0x1B);           /* 对比度值 */
            ST7567_WriteCmd(0x2F);           /* 电源全开 */
            ST7567_WriteCmd(0xAF);           /* 开显示 */

//            ST7567_WriteCmd(0xE2);               //initialize interal function  
//            ST7567_WriteCmd(0x2F);               //power control(VB,VR,VF=1,1,1)     
//            ST7567_WriteCmd(0x23);               //Regulator resistor select(RR2,RR1,VRR0=0,1,1) 
//            ST7567_WriteCmd(0xA2);               //set LCD bias=1/9(BS=0)        
//            ST7567_WriteCmd(0x81);               //set reference voltage        
//            ST7567_WriteCmd(0x25);               //Set electronic volume (EV) level        
//            ST7567_WriteCmd(0xC8);               //set SHL COM1 to COM64      
//            ST7567_WriteCmd(0xA1);               //ADC select SEG1 to SEG132
//            ST7567_WriteCmd(0x40);               //Initial Display Line        
//            ST7567_WriteCmd(0xA6);               //set reverse display OFF        
//            ST7567_WriteCmd(0xA4);               //set all pixels OFF
//            ST7567_WriteCmd(0xAF);               //turns the display ON
        
            /* 清空帧缓冲（全白）并请求刷新 */
            memset(framebuffer, 0x00, sizeof(framebuffer));
            ST7567_RequestRefresh();         /* 将在后续 ST7567_Refresh 中完成 */
            Init_Phase = 100;                /* 初始化完成 */
            break;
        case 101:
            ST7567_Refresh();
            Init_Phase = 100;                /* 初始化完成 */
            break;
        default:
            break;
    }
}

/**********************************************************************************************
 * 函数名   : ST7567_Refresh
 * 功  能   : LCD 分页刷新状态机，需每 10ms 调用一次
 * 说  明   : 若 LCD_Update_Flag 为 1，则在每次 DMA 空闲时发送一页数据；
 *            全部 8 页发送完成后自动清除标志并释放 CS。
 *            该设计让 CPU 在等待 DMA 期间可执行其他任务。
 * 注  意   : 调用前确保 framebuffer 已准备好。
 **********************************************************************************************/
void ST7567_Refresh(void)
{
    /* ---------- 1. 无刷新请求，清除页计数器 ---------- */
    if (LCD_Update_Flag == 0U)
    {
        current_page = 0U;
        return;
    }
    
    // 在 Refresh 中，如果 DMA 长时间忙（例如 >100次计数），可强制复位 SPI/DMA 并重新初始化当前页
    if (DMA_Fail_cnt > 100U) {
        // 可选：BSP_SPI_Reset()、重新配置 DMA
        DMA_Fail_cnt = 0U;
        current_page = 0U;
        LCD_Update_Flag = 1U;                /* 刷新 */
    }
    
    /* ---------- 2. 等待 DMA 空闲 ---------- */
    if (!SPIH_Tx_DMA_Flag())
    {
        DMA_Fail_cnt++;
        /* 可在此记录错误或扩展超时处理，但不再强制重发 */
        return;
    }

    /* ---------- 3. DMA 空闲，发送当前页 ---------- */
    if (current_page < ST7567_PAGE_NUM)
    {
        /* 开始新一帧的传输时，先拉低 CS（仅第一页） */
        if (current_page == 0U)
        {
            BSP_SPI_CS(0);                     /* 选中 LCD，整个帧传输期间保持低 */
        }

        ST7567_SetAddr(current_page, 0);               /* 设置页/列地址 */
        ST7567_WriteDataBytes(framebuffer[current_page], ST7567_WIDTH);
        current_page++;
    }
    else  /* current_page >= 8，全部页已发出 */
    {
        BSP_SPI_CS(1);                       /* 释放 LCD */
        LCD_Update_Flag = 0U;                /* 刷新完成 */
        current_page = 0U;
    }
}

/**********************************************************************************************
 * 函数名   : ST7567_SendDMA
 * 功  能   : 阻塞式 SPI DMA 发送
 * 参  数   : data   - 数据指针
 *            len    - 字节数
 *            is_cmd - 1: 命令（A0=0），0: 数据（A0=1）
 * 注  意   : 本函数不操作 CS，由上层控制。
 **********************************************************************************************/
static void ST7567_SendDMA(uint8_t *data, uint16_t len, uint8_t is_cmd)
{
    /* 设置 A0（命令/数据） */
    if (is_cmd)
        BSP_SPI_A0(0);
    else
        BSP_SPI_A0(1);

    /* 启动本次 DMA 传输 */
    SPIH_Tx_DMA_Start(data, len);
}

/* ==================== 内部辅助函数 ==================== */
static void ST7567_WriteCmd(uint8_t cmd)
{
    ST7567_SendDMA(&cmd, 1, 1);
}

static void ST7567_WriteDataBytes(uint8_t *data, uint16_t len)
{
    ST7567_SendDMA(data, len, 0);
}

static void ST7567_SetAddr(uint8_t page, uint8_t column)
{
    ST7567_WriteCmd(0xB0 | (page & 0x07));
    ST7567_WriteCmd(0x10 | ((column >> 4) & 0x0F));
    ST7567_WriteCmd(0x00 | (column & 0x0F));
}

/* ============ 汉字字模数据（逐列式，高位在上） ============ */

/* 故障 */
const uint8_t HZK_GuZhang[32] = {
0x00,0x00,0x08,0x20,0x08,0x20,0x08,0x20,0xFF,0xFE,0x08,0x20,0x08,0x20,0x08,0x20,
0x00,0x00,0x10,0x40,0x10,0x40,0x10,0x40,0x10,0x40,0x20,0x80,0x20,0x80,0x40,0x00
}; /* 可替换为实际生成的字模 */

/* 电压 */
const uint8_t HZK_DianYa[32] = {
0x00,0x00,0x1F,0xF8,0x10,0x08,0x10,0x08,0x1F,0xF8,0x10,0x08,0x10,0x08,0x1F,0xF8,
0x00,0x00,0x08,0x20,0x08,0x20,0x08,0x20,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00
}; /* 示例，请按实际字模替换 */

/* 温度 */
const uint8_t HZK_WenDu[32] = {
0x00,0x00,0x1F,0xF8,0x10,0x08,0x10,0x08,0x1F,0xF8,0x00,0x00,0x7F,0xFC,0x40,0x04,
0x00,0x00,0xFF,0xFE,0x00,0x00,0x1F,0xF8,0x10,0x08,0x10,0x08,0x1F,0xF8,0x00,0x00
}; /* 示例，请按实际字模替换 */

/******************************************************************************
 * 函数名   : LCD_PutChinese
 * 功  能   : 在帧缓冲中绘制一个 16x16 汉字（逐列式字模）
 * 说  明   : 直接修改 framebuffer，不进行刷新，最后需调用 ST7567_RequestRefresh()
 * 注  意   : 坐标超出屏幕会自动裁剪；Y 非 8 倍数时内部做跨页移位组合，效率稍低
 ******************************************************************************/
void LCD_PutChinese(uint8_t x, uint8_t y, const uint8_t *bitmap,
                    uint8_t color, uint8_t bgcolor)
{
    uint8_t col, byte_idx;
    uint8_t start_page = y / 8;                /* 起始页 */
    uint8_t bit_offset = y % 8;                /* 页内偏移（0~7） */
    uint8_t color_mask = color ? 0xFF : 0x00;  /* 前景色掩码 */
    uint8_t bg_mask    = bgcolor ? 0xFF : 0x00;/* 背景色掩码 */

    for (col = 0; col < 16; col++)
    {
        uint8_t pos_x = x + col;
        if (pos_x >= ST7567_WIDTH) break;     /* 超出右边界 */

        /* 每一列有两个字节：上位字节（上8点）、下位字节（下8点） */
        uint8_t upper_byte = bitmap[col * 2];
        uint8_t lower_byte = bitmap[col * 2 + 1];

        if (bit_offset == 0)
        {
            /* 完全页对齐情况：直接写入两个相邻页 */
            uint8_t page = start_page;
            if (page < ST7567_PAGE_NUM)
            {
                framebuffer[page][pos_x] = (upper_byte & color_mask) | (~upper_byte & bg_mask);
            }
            page++;
            if (page < ST7567_PAGE_NUM)
            {
                framebuffer[page][pos_x] = (lower_byte & color_mask) | (~lower_byte & bg_mask);
            }
        }
        else
        {
            /* 非对齐情况：需要将字模数据移位后与原有像素合并 */
            uint8_t shift = bit_offset;
            uint8_t inv_shift = 8 - shift;

            /* 将上、下两个字节组合成 16 位图形数据（低位在前，高位在后） */
            uint16_t full_pixel = ((uint16_t)lower_byte << 8) | upper_byte;
            /* 向下移动 bit_offset 位（即原图向上移动，因为屏幕列的高位在上） */
            uint16_t shifted = full_pixel >> shift;

            /* 写入第一页（可能只有部分） */
            uint8_t page = start_page;
            if (page < ST7567_PAGE_NUM)
            {
                uint8_t orig = framebuffer[page][pos_x];
                uint8_t graph_byte = (uint8_t)(shifted & 0xFF);          /* 低8位 */
                /* 根据颜色合成 */
                uint8_t result = (graph_byte & color_mask) | (~graph_byte & bg_mask);
                /* 该页只修改对应位，但为了简单，我们直接整体覆盖（会破坏上下未占满部分） */
                /* 更安全的写法：保留溢出到上页的部分？已由 shift 操作处理 */
                framebuffer[page][pos_x] = result;
            }

            /* 写入第二页 */
            page = start_page + 1;
            if (page < ST7567_PAGE_NUM)
            {
                uint8_t orig = framebuffer[page][pos_x];
                uint8_t graph_byte = (uint8_t)(shifted >> 8);           /* 高8位 */
                uint8_t result = (graph_byte & color_mask) | (~graph_byte & bg_mask);
                framebuffer[page][pos_x] = result;
            }

            /* 如果移位后数据还溢出到第三页（start_page + 2），则需要处理剩余位 */
            if (shift > 0 && (start_page + 2) < ST7567_PAGE_NUM)
            {
                uint8_t page3 = start_page + 2;
                uint8_t graph_byte = (uint8_t)(shifted >> 16);          /* 次高位 */
                uint8_t result = (graph_byte & color_mask) | (~graph_byte & bg_mask);
                framebuffer[page3][pos_x] = result;
            }
        }
    }
}
