/**************************************************************************************************
* 文件名   : SYS_MENU.c
* 功能     : 菜单业务逻辑（按键处理、页面显示）
* 说明     : 这个文件是"大脑"，负责根据按键切换到不同页面、控制电机、显示状态等
*
* 页面结构：
*   主页面(PAGE_MAIN)          -> 显示工作状态、时间、速度
*   菜单页(PAGE_MENU)          -> 5 个菜单项供选择
*   模式选择(PAGE_MODE_SELECT) -> 出冰 / 出气模式
*   转速调节(PAGE_SPEED_ADJUST)-> 调节电机转速
*   气压调节(PAGE_PRESSURE)    -> 调节气压（0%~100% 步进 20%）
*   时间设置(PAGE_TIME_SET)    -> 设置运行时间
*   密码页(PAGE_PASSWORD)      -> 输入密码
**************************************************************************************************/
#include "sys_menu.h"
#include "sys_lcd.h"
#include "sys_task.h"
#include <string.h>
#include <stdio.h>

/*=====================================================================
 * 第一部分：硬件接口（按键 / 电机 / 继电器 / 报警码）
 *=====================================================================*/

/* 按键编码：每个键给一个唯一编号，方便 switch 判断 */
#define KEY_NONE    0       /* 无按键按下 */
#define KEY_UP      1       /* 上键（冰量+） */
#define KEY_DOWN    2       /* 下键（冰量-） */
#define KEY_MENU    3       /* 菜单键（在不同页面 = 返回上一级） */
#define KEY_OK      4       /* 确认键（在手柄上也可能叫"手柄键"） */


/*---------------------------------------------------------------------
 * 函数：Key_Get
 * 功能：扫描 4 个物理按键，返回按下的键值
 * 原理：软件消抖——连续读到 2 次以上高电平才算按下，避免抖动误触
 *---------------------------------------------------------------------*/
uint8_t Key_Get(void)
{
    /* static 变量：函数退出后值不会丢失，下次进来还在
     * cnt[i]  = 第 i 个键被按住的"时间计数"（10ms 一次，计到 300 = 3 秒算长按）
     * last[i] = 上一次扫描时第 i 个键的电平（0=没按，1=按下） */
    static uint32_t cnt[4]  = {0};
    static uint8_t  last[4] = {0};
    uint8_t lvl[4];             /* 本次扫描 4 个键的当前电平 */
    uint8_t ret = KEY_NONE;     /* 默认返回"无按键" */

    /* 读取 4 个物理按键的当前电平（1=按下，0=松开） */
    lvl[0] = BSP_GPIO_BTN1();
    lvl[1] = BSP_GPIO_BTN0();
    lvl[2] = BSP_GPIO_BTN3();
    lvl[3] = BSP_GPIO_BTN4();

    /* 逐个键做消抖处理 */
    for (uint8_t i = 0; i < 4; i++) {
        if (last[i] == 0U) {                    /* 上一轮该键是"松开"状态 */
            cnt[i]++;                            /* 计时器 +1 */
            if (cnt[i] >= 2U && cnt[i] <= 300U && lvl[i] == 1U) {
                /* 连续 2~300 次都是"按下"，且当前也是按下 -> 认定有效按键 */
                ret = (uint8_t)(i + 1);          /* 返回按键编号：1~4 */
            } else if (cnt[i] > 300U) {
                /* 超过 3 秒（300*10ms）就清零，避免一直卡住 */
                cnt[i] = 0U;
            }
        } else {                                 /* 上一轮该键是"按下"状态 */
            cnt[i] = 0U;                         /* 松开了，计时器清零 */
        }
        last[i] = lvl[i];                        /* 保存本次电平，供下次判断 */
    }
    return ret;   /* 返回按键编号（0 = 无按键） */
}


/* 电机使能：1=启动，0=停止 */
void Motor_Enable(uint8_t enable) { Systask.System_State_Flag.bit.motor_enable = enable; }

/* 继电器使能（控制气阀）：1=打开，0=关闭 */
void Relay_Enable(uint8_t enable) { Systask.System_State_Flag.bit.value_enable = enable; }

/* 获取当前报警码：0=正常，1~9=E1~E9 对应不同故障 */
uint8_t Get_Alarm_Code(void)      { return Systask.V_Q32U_Error_Code; }


/*=====================================================================
 * 第二部分：常量定义
 *=====================================================================*/

/*------------------- 页面编号 -------------------*/
/* 每个页面给一个唯一编号，通过 sys.page 来切换显示 */
#define PAGE_MAIN               0       /* 主界面 */
#define PAGE_MENU               1       /* 菜单页 */
#define PAGE_MODE_SELECT        2       /* 模式选择 */
#define PAGE_SPEED_ADJUST       3       /* 转速调节 */
#define PAGE_TIME_SET           4       /* 时间设置 */
#define PAGE_PASSWORD           6       /* 密码输入 */
#define PAGE_SPEED_LIMIT_PASS   7       /* 转速密码页 */
#define PAGE_PRESSURE           8       /* 气压调节 */

/*------------------- 菜单项编号 -------------------*/
/* 菜单有 5 项，从上到下编号 0~4 */
#define MENU_ITEM_PRESSURE      0       /* 气压调节 */
#define MENU_ITEM_MODE          1       /* 模式选择 */
#define MENU_ITEM_SPEED         2       /* 电机速度调节 */
#define MENU_ITEM_TIME_SET      3       /* 锁定时间设置 */
#define MENU_ITEM_TIME_CLEAR    4       /* 运行时间清除 */
#define MENU_ITEM_COUNT         5       /* 菜单项总数（用于循环/判断边界） */

/*------------------- 密码 -------------------*/
#define PASSWORD_TIME           123     /* 时间设置 / 清除的密码 */
#define PASSWORD_SPEED          5187    /* 解锁 150 转的密码 */

/*------------------- 转速范围 -------------------*/
#define SPEED_MIN               25      /* 最低转速 */
#define SPEED_MAX_NORMAL        100     /* 普通最高转速 */
#define SPEED_MAX_UNLOCK        150     /* 密码解锁后最高转速 */

/*------------------- 气压范围 -------------------*/
#define PRESSURE_MIN            0       /* 气压最小值 0% */
#define PRESSURE_MAX            100     /* 气压最大值 100% */
#define PRESSURE_STEP           20      /* 每次 ±20% */

/*------------------- 时间上限 -------------------*/
#define TIME_MAX_SECONDS        (9999UL * 3600UL + 59UL * 60UL + 59UL)  /* 9999:59:59 */


/*=====================================================================
 * 第三部分：布局常量（屏幕坐标）
 *=====================================================================*/

#define HZ_W        32          /* 一个汉字的宽度 = 32 像素 */
#define HZ_H        32          /* 一个汉字的高度 = 32 像素 */
#define LINE_STEP   56          /* 行间距：32（字高）+ 24（间隔）= 56 */
#define COL_STEP    32          /* 列间距：每个字符占一个 32 像素宽的"槽位" */
#define WORD_GAP    24          /* 词语与词语之间的间隔 24 像素 */
#define TITLE_X     (4 * COL_STEP + WORD_GAP)   /* 4 字标题 + 24 间隔 = 152，数字/状态从这开始 */


/*=====================================================================
 * 第四部分：常用字符串（Unicode 编码数组，都以 0 结尾）
 *=====================================================================*/
/* 说明：每个汉字用一个 16 位 Unicode 编码表示，末尾加 0 表示字符串结束
 * 比如 0x5DE5 = '工'，0x4F5C = '作'……*/

static const uint16_t S_WORK[]      = {0x5DE5,0x4F5C,0x72B6,0x6001, 0};   /* 工作状态 */
static const uint16_t S_NORMAL[]    = {0x6B63,0x5E38, 0};                 /* 正常 */
static const uint16_t S_STOP[]      = {0x505C,0x6B62, 0};                 /* 停止 */
static const uint16_t S_START[]     = {0x542F,0x52A8, 0};                 /* 启动 */
static const uint16_t S_MODE[]      = {0x6A21,0x5F0F,0x9009,0x62E9, 0};   /* 模式选择 */
static const uint16_t S_ICE[]       = {0x51FA,0x51B0,0x6A21,0x5F0F, 0};   /* 出冰模式 */
static const uint16_t S_AIR[]       = {0x51FA,0x6C14,0x6A21,0x5F0F, 0};   /* 出气模式 */
static const uint16_t S_SET_TIME[]  = {0x8BBE,0x7F6E,0x65F6,0x95F4, 0};   /* 设置时间 */
static const uint16_t S_RUN_TIME[]  = {0x8FD0,0x884C,0x65F6,0x95F4, 0};   /* 运行时间 */
static const uint16_t S_SET_SPEED[] = {0x8BBE,0x7F6E,0x901F,0x5EA6, 0};   /* 设置速度 */

/* "password" 8 个英文字母（ASCII 码） */
static const uint16_t S_PASSWORD[]  = {0x0070,0x0061,0x0073,0x0073,
                                       0x0077,0x006F,0x0072,0x0064, 0};

/* 菜单 5 项的中文 */
static const uint16_t S_MENU_0[]    = {0x6C14,0x538B,0x8C03,0x8282, 0};   /* 气压调节 */
static const uint16_t S_MENU_1[]    = {0x6A21,0x5F0F,0x9009,0x62E9, 0};   /* 模式选择 */
static const uint16_t S_MENU_2[]    = {0x7535,0x673A,0x901F,0x5EA6,
                                       0x8C03,0x8282, 0};                 /* 电机速度调节 */
static const uint16_t S_MENU_3[]    = {0x9501,0x5B9A,0x65F6,0x95F4,
                                       0x8BBE,0x7F6E, 0};                 /* 锁定时间设置 */
static const uint16_t S_MENU_4[]    = {0x8FD0,0x884C,0x65F6,0x95F4,
                                       0x6E05,0x9664, 0};                 /* 运行时间清除 */

/* 气压调节页标题 */
static const uint16_t S_PRESSURE[]  = {0x6C14,0x538B,0x8C03,0x8282, 0};   /* 气压调节 */

/* "rpm/min" 7 个字符 */
static const uint16_t S_RPM_CODES[] = {0x0072,0x0070,0x006D,0x002F,       /* r p m / */
                                       0x006D,0x0069,0x006E, 0};          /* m i n */


/*=====================================================================
 * 第五部分：系统状态结构体
 *=====================================================================*/
/* 把系统所有需要记住的变量都放在这个结构体里，管理更清晰 */
typedef struct {
    uint8_t  page;              /* 当前在哪个页面（PAGE_xxx） */
    uint8_t  menu_index;        /* 菜单当前选中第几项（0~4） */
    uint8_t  mode;              /* 0=出冰模式，1=出气模式 */
    uint16_t speed;             /* 电机转速（25/50/75/100/125/150） */
    uint32_t set_time;          /* 设置的总运行时间（秒） */
    uint32_t run_time;          /* 已经运行了多久（秒） */
    uint8_t  work_state;        /* 0=停止，1=启动 */
    uint8_t  pwd_input[4];      /* 密码输入缓存：4 位数字 */
    uint8_t  pwd_index;         /* 密码页当前编辑第几位（0~3） */
    uint8_t  pwd_target;        /* 密码验证成功后跳转到哪个页面 */
    uint8_t  time_index;        /* 时间设置页当前编辑第几位（0~7） */
    uint8_t  pressure;          /* 气压值 0~100 */
    uint8_t  speed_unlocked;    /* 转速解锁标志：0=未解锁，1=已解锁可到 150 */
    uint8_t  alarm_code;        /* 当前报警码，0=正常 */
    uint8_t  need_refresh;      /* 需要重绘标志 */
    uint8_t  full_refresh;      /* 1=整屏重绘，0=只重绘变化的一行 */
} SystemState;

/* 全局只创建一个实例 sys，所有地方都用 sys.xxx 访问 */
static SystemState sys;

static uint16_t tick_10ms = 0;              /* 10ms 计数器，累加到 100 就是 1 秒 */
static uint8_t  last_key  = KEY_NONE;       /* 上一次的按键值，用于边沿检测 */


/*=====================================================================
 * 第六部分：绘制工具函数
 *=====================================================================*/

/*---------------------------------------------------------------------
 * 函数：DrawText
 * 功能：画一串 32×32 汉字
 * 参数：x,y = 起点坐标；txt = Unicode 数组；fg = 前景色；bg = 背景色
 *---------------------------------------------------------------------*/
static void DrawText(uint16_t x, uint16_t y, const uint16_t *txt,
                     uint16_t fg, uint16_t bg)
{
    lcd_draw_hz32_str(x, y, txt, fg, bg);
}


/*---------------------------------------------------------------------
 * 函数：DrawDigit
 * 功能：画一个数字，居中在 32 像素宽的"槽位"里
 * 说明：数字字模只有 16 像素宽，但槽位有 32 像素宽
 *       为了让数字居中，右边偏移 8 像素：(32-16)/2 = 8
 * 参数：slot_x = 槽位左边缘的 x 坐标
 *---------------------------------------------------------------------*/
static void DrawDigit(uint16_t slot_x, uint16_t y, uint8_t d,
                      uint16_t fg, uint16_t bg)
{
    /* '0' 的 ASCII 是 0x30，所以数字 n 对应的编码是 0x30+n */
    lcd_draw_hz16x32(slot_x + 8, y, 0x0030 + (d % 10), fg, bg);
}


/*---------------------------------------------------------------------
 * 函数：DrawChar32
 * 功能：画一个 ASCII 字符，居中在 32 像素宽的槽位里
 * 参数：code = 字符的 ASCII 码（比如 ':' 是 0x3A，'%' 是 0x25）
 *---------------------------------------------------------------------*/
static void DrawChar32(uint16_t slot_x, uint16_t y, uint16_t code,
                       uint16_t fg, uint16_t bg)
{
    lcd_draw_hz16x32(slot_x + 8, y, code, fg, bg);
}


/*---------------------------------------------------------------------
 * 函数：pow10
 * 功能：计算 10 的 n 次方（比如 pow10(3) = 1000）
 * 用途：画数字时取每一位用
 *---------------------------------------------------------------------*/
static uint32_t pow10(uint8_t n)
{
    uint32_t r = 1;
    while (n--) r *= 10;
    return r;
}


/*---------------------------------------------------------------------
 * 函数：DrawUInt
 * 功能：把一个无符号整数按位数画出来
 * 例如：v=100, digits=3 会画 "1 0 0" 三个数字，各占一个槽位
 *---------------------------------------------------------------------*/
static void DrawUInt(uint16_t x, uint16_t y, uint32_t v, uint8_t digits,
                     uint16_t fg, uint16_t bg)
{
    for (uint8_t i = 0; i < digits; i++) {
        /* 取第 i 位数字：比如 v=123，digits=3
         * i=0: (123 / 100) % 10 = 1
         * i=1: (123 /  10) % 10 = 2
         * i=2: (123 /   1) % 10 = 3 */
        uint8_t d = (v / pow10(digits - 1 - i)) % 10;
        DrawDigit(x + i * COL_STEP, y, d, fg, bg);  /* 每个数字右移一个槽位 */
    }
}


/*---------------------------------------------------------------------
 * 函数：DrawTime
 * 功能：画时间 "HH:MM:SS"，共 8 个数字 + 2 个冒号
 * 布局：数字 数字 数字 数字 : 数字 数字 : 数字 数字
 *       槽位0 1  2  3  4 5  6  7 8  9
 *       其中槽位 4 和 7 是冒号，其余是数字
 *---------------------------------------------------------------------*/
static void DrawTime(uint16_t x, uint16_t y, uint32_t seconds,
                     uint16_t fg, uint16_t bg)
{
    /* 把总秒数拆成 时:分:秒 */
    uint32_t h = seconds / 3600;                /* 小时 */
    uint32_t m = (seconds % 3600) / 60;         /* 分钟 */
    uint32_t s = seconds % 60;                  /* 秒 */

    /* 画 4 位小时数字（时千位、时百位、时十位、时个位） */
    DrawDigit (x + 0 * COL_STEP, y, (h / 1000) % 10, fg, bg);
    DrawDigit (x + 1 * COL_STEP, y, (h / 100)  % 10, fg, bg);
    DrawDigit (x + 2 * COL_STEP, y, (h / 10)   % 10, fg, bg);
    DrawDigit (x + 3 * COL_STEP, y,  h         % 10, fg, bg);

    /* 画第一个冒号 */
    DrawChar32(x + 4 * COL_STEP, y, 0x003A, fg, bg);

    /* 画 2 位分钟 */
    DrawDigit (x + 5 * COL_STEP, y, m / 10, fg, bg);
    DrawDigit (x + 6 * COL_STEP, y, m % 10, fg, bg);

    /* 画第二个冒号 */
    DrawChar32(x + 7 * COL_STEP, y, 0x003A, fg, bg);

    /* 画 2 位秒 */
    DrawDigit (x + 8 * COL_STEP, y, s / 10, fg, bg);
    DrawDigit (x + 9 * COL_STEP, y, s % 10, fg, bg);
}


/*---------------------------------------------------------------------
 * 函数：DrawRpmMin
 * 功能：画 "rpm/min" 7 个字符，每个占一个 32 宽槽位
 *---------------------------------------------------------------------*/
static void DrawRpmMin(uint16_t x, uint16_t y, uint16_t fg, uint16_t bg)
{
    for (uint8_t i = 0; i < 7; i++) {
        DrawChar32(x + i * COL_STEP, y, S_RPM_CODES[i], fg, bg);
    }
}


/*=====================================================================
 * 第七部分：页面显示函数（每个页面对应一个 Display_xxx 函数）
 *=====================================================================*/

/*---------------------------------------------------------------------
 * 函数：Display_Main
 * 功能：绘制主界面（整屏重绘）
 * 主界面布局（5 行，每行间隔 56 像素）：
 *   行0: [工作状态] 24 [正常/E1] 24 [停止/启动]   ← 仅"停止/启动"白底黑字
 *   行1: [模式选择] 24 [出冰/出气模式]             ← 选中项白底黑字
 *   行2: [设置时间] 24 [HH:MM:SS]
 *   行3: [运行时间] 24 [HH:MM:SS]
 *   行4: [设置速度] 24 [NNN rpm/min]
 *---------------------------------------------------------------------*/
static void Display_Main(void)
{
    /* 先用黑色清空整个屏幕 */
    lcd_fill_color(LCD_BLACK);

    /*============== 行 0：工作状态 XX 停止/启动 ==============*/
    /* 画"工作状态"4 个字，从 x=0 开始，占 4*32=128 像素 */
    DrawText(0, 0, S_WORK, LCD_WHITE, LCD_BLACK);

    /* 状态词（正常 or E1~E9）放在 x = TITLE_X = 152 处 */
    if (sys.alarm_code == 0) {
        /* 正常：黑底白字，不高亮 */
        DrawText(TITLE_X, 0, S_NORMAL, LCD_WHITE, LCD_BLACK);
    } else {
        /* 报警：白底黑字（用白底矩形覆盖 64 像素宽的槽位） */
        lcd_fill_rect(TITLE_X, 0, 64, HZ_H, LCD_WHITE);
        DrawChar32(TITLE_X,      0, 0x0045,         LCD_BLACK, LCD_WHITE);  /* E */
        DrawDigit (TITLE_X + 32, 0, sys.alarm_code, LCD_BLACK, LCD_WHITE);  /* 数字 */
    }

    /* 停止/启动：x = 152 + 64 + 24 = 240，白底黑字（高亮显示） */
    lcd_fill_rect(TITLE_X + 64 + WORD_GAP, 0, 64, HZ_H, LCD_WHITE);
    DrawText(TITLE_X + 64 + WORD_GAP, 0,
             sys.work_state ? S_START : S_STOP,     /* 启动 or 停止 */
             LCD_BLACK, LCD_WHITE);

    /*============== 行 1：模式选择 XX 模式 ==============*/
    DrawText(0, LINE_STEP, S_MODE, LCD_WHITE, LCD_BLACK);
    lcd_fill_rect(TITLE_X, LINE_STEP, 128, HZ_H, LCD_WHITE);    /* 4 字白底 */
    DrawText(TITLE_X, LINE_STEP,
             sys.mode ? S_AIR : S_ICE,              /* 出气 or 出冰 */
             LCD_BLACK, LCD_WHITE);

    /*============== 行 2：设置时间 HH:MM:SS ==============*/
    DrawText(0, LINE_STEP * 2, S_SET_TIME, LCD_WHITE, LCD_BLACK);
    DrawTime(TITLE_X, LINE_STEP * 2, sys.set_time, LCD_WHITE, LCD_BLACK);

    /*============== 行 3：运行时间 HH:MM:SS ==============*/
    DrawText(0, LINE_STEP * 3, S_RUN_TIME, LCD_WHITE, LCD_BLACK);
    DrawTime(TITLE_X, LINE_STEP * 3, sys.run_time, LCD_WHITE, LCD_BLACK);

    /*============== 行 4：设置速度 NNN rpm/min ==============*/
    DrawText(0, LINE_STEP * 4, S_SET_SPEED, LCD_WHITE, LCD_BLACK);
    /* 3 位数字占 3 个槽位 */
    DrawUInt (TITLE_X, LINE_STEP * 4, sys.speed, 3, LCD_WHITE, LCD_BLACK);
    /* 紧跟着"rpm/min" 7 个字符 */
    DrawRpmMin(TITLE_X + 3 * COL_STEP, LINE_STEP * 4, LCD_WHITE, LCD_BLACK);
}


/*---------------------------------------------------------------------
 * 函数：Display_Main_UpdateRunTime
 * 功能：只重绘"运行时间"那一行
 * 说明：run_time 每秒都在变，如果每秒都整屏重绘会闪
 *       所以单独写一个函数，只画那一行，避免闪烁
 *---------------------------------------------------------------------*/
static void Display_Main_UpdateRunTime(void)
{
    DrawText(0, LINE_STEP * 3, S_RUN_TIME, LCD_WHITE, LCD_BLACK);
    DrawTime(TITLE_X, LINE_STEP * 3, sys.run_time, LCD_WHITE, LCD_BLACK);
}


/*---------------------------------------------------------------------
 * 函数：Display_Menu
 * 功能：绘制菜单页（5 项，选中项白底黑字）
 *---------------------------------------------------------------------*/
static void Display_Menu(void)
{
    /* 菜单 5 项的字符串数组 */
    const uint16_t *items[] = {S_MENU_0, S_MENU_1, S_MENU_2, S_MENU_3, S_MENU_4};

    lcd_fill_color(LCD_BLACK);          /* 整屏清黑 */

    for (uint8_t i = 0; i < MENU_ITEM_COUNT; i++) {     /* 逐项绘制 */
        uint16_t y = i * LINE_STEP;                      /* 第 i 项的 y 坐标 */

        if (i == sys.menu_index) {
            /* 选中项：整行白底黑字（高亮） */
            lcd_fill_rect(0, y, LCD_WIDTH, HZ_H, LCD_WHITE);
            DrawText(0, y, items[i], LCD_BLACK, LCD_WHITE);
        } else {
            /* 未选中项：黑底白字 */
            DrawText(0, y, items[i], LCD_WHITE, LCD_BLACK);
        }
    }
}


/*---------------------------------------------------------------------
 * 函数：Display_Mode_Select
 * 功能：模式选择页（出冰 / 出气 两项，选中项白底黑字）
 *---------------------------------------------------------------------*/
static void Display_Mode_Select(void)
{
    lcd_fill_color(LCD_BLACK);
    uint16_t y1 = LINE_STEP;            /* 第一项 y 坐标 */
    uint16_t y2 = LINE_STEP * 2;        /* 第二项 y 坐标 */

    if (sys.mode == 0) {
        /* 当前是出冰模式 -> 出冰项高亮 */
        lcd_fill_rect(0, y1, LCD_WIDTH, HZ_H, LCD_WHITE);
        DrawText(0, y1, S_ICE, LCD_BLACK, LCD_WHITE);
        DrawText(0, y2, S_AIR, LCD_WHITE, LCD_BLACK);
    } else {
        /* 当前是出气模式 -> 出气项高亮 */
        DrawText(0, y1, S_ICE, LCD_WHITE, LCD_BLACK);
        lcd_fill_rect(0, y2, LCD_WIDTH, HZ_H, LCD_WHITE);
        DrawText(0, y2, S_AIR, LCD_BLACK, LCD_WHITE);
    }
}


/*---------------------------------------------------------------------
 * 函数：Display_Speed_Adjust
 * 功能：转速调节页（3 位数字 + rpm/min）
 * 布局：数字整体白底黑字，居中显示
 *---------------------------------------------------------------------*/
static void Display_Speed_Adjust(void)
{
    lcd_fill_color(LCD_BLACK);

    uint16_t num_x = 3 * COL_STEP;      /* 数字起始 x = 96 */
    uint16_t num_y = LINE_STEP * 2;     /* 数字所在行 y = 112 */

    /* 3 个数字的白底条（3*32=96 像素宽） */
    lcd_fill_rect(num_x, num_y, 3 * COL_STEP, HZ_H, LCD_WHITE);
    /* 白底黑字画数字 */
    DrawUInt(num_x, num_y, sys.speed, 3, LCD_BLACK, LCD_WHITE);

    /* rpm/min 保持黑底白字 */
    DrawRpmMin(6 * COL_STEP, num_y, LCD_WHITE, LCD_BLACK);
}


/*---------------------------------------------------------------------
 * 函数：Display_Time_Set
 * 功能：时间设置页（8 个数字 + 2 个冒号）
 * 说明：当前编辑的数字位白底黑字，其他位黑底白字
 *       8 个数字位对应的槽位：[0,1,2,3, 5,6, 8,9]（跳过冒号位置 4,7）
 *---------------------------------------------------------------------*/
static void Display_Time_Set(void)
{
    lcd_fill_color(LCD_BLACK);

    /* 拆分时间：h=小时，m=分钟，s=秒 */
    uint32_t h = sys.set_time / 3600;
    uint32_t m = (sys.set_time % 3600) / 60;
    uint32_t s = sys.set_time % 60;

    /* 每一位数字放到一个数组里，方便后面循环画 */
    uint8_t d[8] = {
        (h / 1000) % 10, (h / 100) % 10, (h / 10) % 10, h % 10,    /* 时 4 位 */
        m / 10, m % 10,                                             /* 分 2 位 */
        s / 10, s % 10                                              /* 秒 2 位 */
    };

    uint16_t base_x = 1 * COL_STEP;     /* 数字起始 x = 32 */
    uint16_t y      = LINE_STEP * 2;    /* 数字所在行 y */

    /* 8 个数字分别对应屏幕上的哪个槽位 */
    static const uint8_t slot_of_digit[8] = {0, 1, 2, 3, 5, 6, 8, 9};

    for (uint8_t i = 0; i < 8; i++) {
        uint16_t x = base_x + slot_of_digit[i] * COL_STEP;     /* 该位数字的 x */

        if (i == sys.time_index) {
            /* 当前编辑位：白底黑字 */
            lcd_fill_rect(x, y, HZ_W, HZ_H, LCD_WHITE);
            DrawDigit(x, y, d[i], LCD_BLACK, LCD_WHITE);
        } else {
            /* 其他位：黑底白字 */
            lcd_fill_rect(x, y, HZ_W, HZ_H, LCD_BLACK);
            DrawDigit(x, y, d[i], LCD_WHITE, LCD_BLACK);
        }
    }

    /* 两个冒号（位置 4 和 7） */
    DrawChar32(base_x + 4 * COL_STEP, y, 0x003A, LCD_WHITE, LCD_BLACK);
    DrawChar32(base_x + 7 * COL_STEP, y, 0x003A, LCD_WHITE, LCD_BLACK);
}


/*---------------------------------------------------------------------
 * 函数：Display_Password
 * 功能：密码输入页
 * 布局：password + 4 位数字
 * 说明：当前编辑位白底黑字，其他位黑底白字
 *---------------------------------------------------------------------*/
static void Display_Password(void)
{
    lcd_fill_color(LCD_BLACK);

    /* 先画 "password" 8 个字母，各占一个 32 宽槽位 */
    for (uint8_t i = 0; i < 8; i++) {
        DrawChar32(i * COL_STEP, LINE_STEP * 2, S_PASSWORD[i],
                   LCD_WHITE, LCD_BLACK);
    }

    /* 密码位数：时间密码 3 位，转速密码 4 位 */
    uint8_t digits = (sys.pwd_target == PAGE_TIME_SET) ? 3 : 4;

    for (uint8_t i = 0; i < digits; i++) {
        /* 数字从第 10 个槽位开始（前面 8 槽是 password，空 1 槽当间隔） */
        uint16_t x = 10 * COL_STEP + i * COL_STEP;
        uint16_t y = LINE_STEP * 2;

        if (i == sys.pwd_index) {
            /* 当前编辑位：白底黑字 */
            lcd_fill_rect(x, y, HZ_W, HZ_H, LCD_WHITE);
            DrawDigit(x, y, sys.pwd_input[i], LCD_BLACK, LCD_WHITE);
        } else {
            /* 其他位：黑底白字 */
            lcd_fill_rect(x, y, HZ_W, HZ_H, LCD_BLACK);
            DrawDigit(x, y, sys.pwd_input[i], LCD_WHITE, LCD_BLACK);
        }
    }
}


/*---------------------------------------------------------------------
 * 函数：Display_Pressure
 * 功能：气压调节页
 * 布局：
 *   第一行：气压调节（居中）
 *   第二行：NNN %（三位数字 + %，白底黑字，居中）
 *---------------------------------------------------------------------*/
static void Display_Pressure(void)
{
    lcd_fill_color(LCD_BLACK);

    /* 标题居中：(屏幕宽 480 - 4 字 * 32) / 2 = 176 */
    uint16_t title_x = (LCD_WIDTH - 4 * COL_STEP) / 2;
    DrawText(title_x, LINE_STEP, S_PRESSURE, LCD_WHITE, LCD_BLACK);

    /* 数字行居中，4 个槽位（3 数字 + 1 个 %） */
    uint16_t line2_x = (LCD_WIDTH - 4 * COL_STEP) / 2;
    uint16_t line2_y = LINE_STEP * 3;

    /* 白底矩形覆盖 4 个槽位 */
    lcd_fill_rect(line2_x, line2_y, 4 * COL_STEP, HZ_H, LCD_WHITE);

    /* 3 位数字（白底黑字） */
    DrawUInt(line2_x, line2_y, sys.pressure, 3, LCD_BLACK, LCD_WHITE);

    /* 百分号 */
    DrawChar32(line2_x + 3 * COL_STEP, line2_y,
               0x0025, LCD_BLACK, LCD_WHITE);
}


/*=====================================================================
 * 第八部分：按键处理函数
 * 每个页面都有一个 Handle_xxx_Key 函数，专门处理该页面的按键
 *=====================================================================*/

/*---------------------------------------------------------------------
 * 函数：Handle_Main_Key
 * 功能：主页面按键处理
 *   确认键 -> 切换 启动/停止（有报警时禁止启动）
 *   菜单键 -> 进入菜单页
 *---------------------------------------------------------------------*/
static void Handle_Main_Key(uint8_t key)
{
    if (key == KEY_OK) {
        /* 有报警且当前是停止状态 -> 禁止启动 */
        if (sys.alarm_code != 0 && sys.work_state == 0) return;

        /* 切换启停状态 */
        sys.work_state = !sys.work_state;

        if (sys.work_state == 1) {      /* 启动 */
            if (sys.mode == 0) {        /* 出冰模式：电机 + 继电器都开 */
                Motor_Enable(1);
                Relay_Enable(1);
            } else {                    /* 出气模式：只开继电器，电机不动 */
                Motor_Enable(0);
                Relay_Enable(1);
            }
        } else {                        /* 停止 */
            Motor_Enable(0);
            Relay_Enable(0);
        }

        sys.need_refresh = 1;           /* 请求重绘 */
        sys.full_refresh = 1;           /* 整屏重绘（因为状态变了） */
    } else if (key == KEY_MENU) {
        /* 进入菜单页 */
        sys.page = PAGE_MENU;
        sys.menu_index = 0;             /* 光标回到第一项 */
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    }
}


/*---------------------------------------------------------------------
 * 函数：Handle_Menu_Key
 * 功能：菜单页按键处理
 *   上/下 -> 移动光标
 *   确认  -> 进入对应子页面
 *   菜单  -> 返回主页面
 *---------------------------------------------------------------------*/
static void Handle_Menu_Key(uint8_t key)
{
    if (key == KEY_UP) {
        /* 上移光标（不能越界） */
        if (sys.menu_index > 0) sys.menu_index--;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    } else if (key == KEY_DOWN) {
        /* 下移光标（不能越界） */
        if (sys.menu_index < MENU_ITEM_COUNT - 1) sys.menu_index++;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    } else if (key == KEY_OK) {
        /* 进入选中菜单项对应的子页面 */
        switch (sys.menu_index) {
            case MENU_ITEM_PRESSURE: sys.page = PAGE_PRESSURE; break;
            case MENU_ITEM_MODE:     sys.page = PAGE_MODE_SELECT; break;
            case MENU_ITEM_SPEED:    sys.page = PAGE_SPEED_ADJUST; break;
            case MENU_ITEM_TIME_SET:
                /* 进时间设置 -> 先要输入密码 */
                sys.page = PAGE_PASSWORD;
                sys.pwd_target = PAGE_TIME_SET;
                sys.pwd_index = 0;                          /* 从第 0 位开始输入 */
                memset(sys.pwd_input, 0x00, 4);             /* 密码缓冲清零 */
                break;
            case MENU_ITEM_TIME_CLEAR:
                /* 进运行时间清除 -> 也要密码 */
                sys.page = PAGE_PASSWORD;
                sys.pwd_target = PAGE_TIME_SET;
                sys.pwd_index = 0;
                memset(sys.pwd_input, 0x00, 4);
                break;
        }
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    } else if (key == KEY_MENU) {
        /* 从菜单返回主页面 */
        sys.page = PAGE_MAIN;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    }
}


/*---------------------------------------------------------------------
 * 函数：Handle_Pressure_Key
 * 功能：气压调节页按键
 *   上 -> 气压 +20%
 *   下 -> 气压 -20%
 *   确认/菜单 -> 返回菜单
 *---------------------------------------------------------------------*/
static void Handle_Pressure_Key(uint8_t key)
{
    if (key == KEY_UP) {
        /* 加 20%，但不超过 100 */
        if (sys.pressure + PRESSURE_STEP <= PRESSURE_MAX)
            sys.pressure += PRESSURE_STEP;
        else
            sys.pressure = PRESSURE_MAX;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    } else if (key == KEY_DOWN) {
        /* 减 20%，但不少于 0 */
        if (sys.pressure >= PRESSURE_MIN + PRESSURE_STEP)
            sys.pressure -= PRESSURE_STEP;
        else
            sys.pressure = PRESSURE_MIN;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    } else if (key == KEY_OK || key == KEY_MENU) {
        /* 返回菜单 */
        sys.page = PAGE_MENU;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    }
}


/*---------------------------------------------------------------------
 * 函数：Handle_Mode_Select_Key
 * 功能：模式选择页按键
 *   上/下 -> 切换出冰/出气
 *   确认  -> 保存并返回菜单
 *   菜单  -> 直接返回菜单
 *---------------------------------------------------------------------*/
static void Handle_Mode_Select_Key(uint8_t key)
{
    if (key == KEY_UP || key == KEY_DOWN) {
        /* 切换模式：0<->1 */
        sys.mode = !sys.mode;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    } else if (key == KEY_OK) {
        /* 如果当前在运行，立即应用新模式 */
        if (sys.work_state == 1) {
            if (sys.mode == 0) {
                Motor_Enable(1);            /* 出冰：电机开 */
                Relay_Enable(1);
            } else {
                Motor_Enable(0);            /* 出气：电机停 */
                Relay_Enable(1);
            }
        }
        sys.page = PAGE_MENU;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    } else if (key == KEY_MENU) {
        sys.page = PAGE_MENU;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    }
}


/*---------------------------------------------------------------------
 * 函数：Handle_Speed_Adjust_Key
 * 功能：转速调节页按键
 *   上 -> 转速 +25（到 100 时要密码解锁才能继续加）
 *   下 -> 转速 -25
 *   确认/菜单 -> 返回菜单
 *---------------------------------------------------------------------*/
static void Handle_Speed_Adjust_Key(uint8_t key)
{
    if (key == KEY_UP) {
        /* 已经到 100 并且没解锁 -> 弹出密码页 */
        if (sys.speed >= SPEED_MAX_NORMAL && !sys.speed_unlocked) {
            sys.page = PAGE_SPEED_LIMIT_PASS;
            sys.pwd_target = PAGE_SPEED_ADJUST;
            sys.pwd_index = 0;
            memset(sys.pwd_input, 0x00, 4);
        } else {
            /* 正常加 25，不超过最大值 */
            if (sys.speed < SPEED_MAX_UNLOCK) sys.speed += 25;
            if (sys.speed > SPEED_MAX_UNLOCK) sys.speed = SPEED_MAX_UNLOCK;
        }
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    } else if (key == KEY_DOWN) {
        /* 减 25，不低于最小值 */
        if (sys.speed > SPEED_MIN) sys.speed -= 25;
        if (sys.speed < SPEED_MIN) sys.speed = SPEED_MIN;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    } else if (key == KEY_OK || key == KEY_MENU) {
        sys.page = PAGE_MENU;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    }
}


/*---------------------------------------------------------------------
 * 函数：Handle_Time_Set_Key
 * 功能：时间设置页按键
 *   上 -> 当前编辑位 +1（按权值增加秒数）
 *   下 -> 当前编辑位 -1
 *   确认 -> 切到下一个数字位
 *   菜单 -> 返回菜单
 * 说明：用"权值法"改变时间。
 *   time_index=0 -> 时千位，权值 1000*3600 秒
 *   time_index=3 -> 时个位，权值 3600 秒
 *   time_index=7 -> 秒个位，权值 1 秒
 *   这样加超了会自动进位（比如 59 秒 +1 变成 60 秒=1分）
 *---------------------------------------------------------------------*/
static void Handle_Time_Set_Key(uint8_t key)
{
    static const uint32_t weight[8] = {
        1000UL * 3600UL, 100UL * 3600UL, 10UL * 3600UL, 3600UL,
        10UL * 60UL,     60UL,
        10UL,            1UL
    };

    if (key == KEY_UP) {
        /* 加一个权值 */
        uint32_t w = weight[sys.time_index];
        if (sys.set_time + w <= TIME_MAX_SECONDS)
            sys.set_time += w;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    } else if (key == KEY_DOWN) {
        /* 减一个权值（减不了就归零） */
        uint32_t w = weight[sys.time_index];
        if (sys.set_time >= w)
            sys.set_time -= w;
        else
            sys.set_time = 0;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    } else if (key == KEY_OK) {
        /* 光标右移一位，到末尾回到第 0 位 */
        sys.time_index = (sys.time_index + 1) % 8;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    } else if (key == KEY_MENU) {
        sys.page = PAGE_MENU;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    }
}


/*---------------------------------------------------------------------
 * 函数：Handle_Password_Key
 * 功能：密码输入页按键
 *   上 -> 当前位数字 +1（0-9 循环）
 *   下 -> 当前位数字 -1（0-9 循环）
 *   确认 -> 光标右移一位；若已输入完 -> 校验密码
 *   菜单 -> 取消返回菜单
 *---------------------------------------------------------------------*/
static void Handle_Password_Key(uint8_t key)
{
    /* 需要输入的位数：时间密码 3 位，转速密码 4 位 */
    uint8_t max_digit = (sys.pwd_target == PAGE_TIME_SET) ? 3 : 4;

    if (key == KEY_UP) {
        /* 当前位 +1（% 10 保证 9+1 变 0） */
        sys.pwd_input[sys.pwd_index] = (sys.pwd_input[sys.pwd_index] + 1) % 10;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    } else if (key == KEY_DOWN) {
        /* 当前位 -1（+9 再 %10 等价于 -1） */
        sys.pwd_input[sys.pwd_index] = (sys.pwd_input[sys.pwd_index] + 9) % 10;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    } else if (key == KEY_OK) {
        /* 光标右移一位 */
        sys.pwd_index++;

        if (sys.pwd_index >= max_digit) {
            /* 已经输完所有位 -> 校验密码 */
            uint16_t input = 0;
            for (uint8_t i = 0; i < max_digit; i++) {
                /* 把 4 位数字拼成一个整数：比如 1,2,3 -> 123 */
                input = input * 10 + sys.pwd_input[i];
            }

            if (sys.pwd_target == PAGE_TIME_SET) {
                /* 时间密码校验 */
                if (input == PASSWORD_TIME) {
                    sys.page = PAGE_TIME_SET;       /* 正确 -> 进时间设置页 */
                    sys.time_index = 0;
                } else {
                    sys.page = PAGE_MENU;           /* 错误 -> 回菜单 */
                }
            } else if (sys.pwd_target == PAGE_SPEED_ADJUST) {
                /* 转速密码校验 */
                if (input == PASSWORD_SPEED) sys.speed_unlocked = 1;    /* 解锁 */
                sys.page = PAGE_SPEED_ADJUST;                           /* 回转速页 */
            }
            sys.need_refresh = 1;
            sys.full_refresh = 1;
        } else {
            /* 还没输完，继续 */
            sys.need_refresh = 1;
            sys.full_refresh = 1;
        }
    } else if (key == KEY_MENU) {
        /* 取消输入，回菜单 */
        sys.page = PAGE_MENU;
        sys.need_refresh = 1;
        sys.full_refresh = 1;
    }
}


/*=====================================================================
 * 第九部分：系统初始化与 10ms 主循环
 *=====================================================================*/

/*---------------------------------------------------------------------
 * 函数：System_Init
 * 功能：系统初始化，只在 main() 里调用一次
 *       把所有状态变量设置成默认值
 *---------------------------------------------------------------------*/
void System_Init(void)
{
    /* 把 sys 结构体全部清零 */
    memset(&sys, 0, sizeof(sys));

    /* 密码缓冲清零（4 个 0） */
    memset(sys.pwd_input, 0x00, 4);

    /* 设置默认状态 */
    sys.page          = PAGE_MAIN;      /* 从主页面开始 */
    sys.mode          = 0;              /* 默认出冰模式 */
    sys.speed         = 100;            /* 默认 100 转 */
    sys.set_time      = 3 * 3600;       /* 默认 3 小时 */
    sys.time_index    = 0;
    sys.pressure      = 0;              /* 气压默认 0% */
    sys.need_refresh  = 1;              /* 需要重绘 */
    sys.full_refresh  = 1;              /* 整屏重绘 */

    tick_10ms = 0;
    last_key  = KEY_NONE;
}


/*---------------------------------------------------------------------
 * 函数：System_Loop_10ms
 * 功能：10ms 周期任务（在定时器中断或主循环里调用）
 *       每次做三件事：
 *         1. 扫描按键并处理
 *         2. 每秒更新一次运行时间 + 检测报警
 *         3. 按需重绘屏幕
 *---------------------------------------------------------------------*/
void System_Loop_10ms(void)
{
    /*===================== 第 1 步：按键扫描 =====================*/
    uint8_t key = Key_Get();    /* 读按键 */

    /* 边沿检测：只有按键值变化（比如从"无"变"上"）才处理
     * 避免一直按住就重复触发 */
    if (key != KEY_NONE && key != last_key) {
        /* 根据当前页面，调用对应的按键处理函数 */
        switch (sys.page) {
            case PAGE_MAIN:             Handle_Main_Key(key); break;
            case PAGE_MENU:             Handle_Menu_Key(key); break;
            case PAGE_MODE_SELECT:      Handle_Mode_Select_Key(key); break;
            case PAGE_SPEED_ADJUST:     Handle_Speed_Adjust_Key(key); break;
            case PAGE_TIME_SET:         Handle_Time_Set_Key(key); break;
            case PAGE_PASSWORD:         Handle_Password_Key(key); break;
            case PAGE_SPEED_LIMIT_PASS: Handle_Password_Key(key); break;
            case PAGE_PRESSURE:         Handle_Pressure_Key(key); break;
        }
    }
    last_key = key;             /* 记住本次按键，供下次比较 */

    /*===================== 第 2 步：每秒任务 =====================*/
    tick_10ms++;                /* 计数器 +1 */
    if (tick_10ms >= 100) {     /* 累加到 100 就是 1 秒 */
        tick_10ms = 0;          /* 清零重新计数 */

        /* 如果正在运行，运行时间 +1 秒 */
        if (sys.work_state == 1) {
            sys.run_time++;

            /* 运行时间 >= 设定时间 -> 自动停止 */
            if (sys.run_time >= sys.set_time) {
                sys.work_state = 0;
                Motor_Enable(0);
                Relay_Enable(0);
                sys.full_refresh = 1;
            }
            sys.need_refresh = 1;       /* 请求刷新运行时间 */
        }

        /* 检测报警码是否变化 */
        uint8_t alarm = Get_Alarm_Code();
        if (alarm != sys.alarm_code) {
            sys.alarm_code = alarm;
            sys.need_refresh = 1;
            sys.full_refresh = 1;

            /* 出现新报警 -> 强制停止电机和继电器 */
            if (alarm != 0) {
                sys.work_state = 0;
                Motor_Enable(0);
                Relay_Enable(0);
            }
        }
    }

    /*===================== 第 3 步：显示刷新 =====================*/
    if (sys.need_refresh) {
        if (sys.full_refresh) {
            /* 整屏重绘：用于页面切换、状态改变等 */
            switch (sys.page) {
                case PAGE_MAIN:             Display_Main(); break;
                case PAGE_MENU:             Display_Menu(); break;
                case PAGE_MODE_SELECT:      Display_Mode_Select(); break;
                case PAGE_SPEED_ADJUST:     Display_Speed_Adjust(); break;
                case PAGE_TIME_SET:         Display_Time_Set(); break;
                case PAGE_PASSWORD:         Display_Password(); break;
                case PAGE_SPEED_LIMIT_PASS: Display_Password(); break;
                case PAGE_PRESSURE:         Display_Pressure(); break;
            }
            sys.full_refresh = 0;       /* 清标志 */
        } else {
            /* 局部刷新：只重绘运行时间那一行，避免闪屏 */
            if (sys.page == PAGE_MAIN) {
                Display_Main_UpdateRunTime();
            }
        }
        sys.need_refresh = 0;           /* 清标志 */
    }
}