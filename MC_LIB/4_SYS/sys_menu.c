/**
 * @file    sys_menu.c
 * @brief   菜单业务逻辑（按键处理、页面显示）
 *          采用旧工程完整逻辑，命名遵循新工程规范
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "sys_menu.h"
#include "sys_lcd.h"
#include "sys_task.h"
#include <string.h>

/* ======================== 2. Defines ====================== */

/* ---- 键值编码 ---- */
#define MENU_KEY_NONE           (0U)
#define MENU_KEY_UP             (1U)
#define MENU_KEY_DOWN           (2U)
#define MENU_KEY_MENU           (3U)
#define MENU_KEY_OK             (4U)

/* ---- 页面编号 ---- */
#define PAGE_MAIN               (0U)
#define PAGE_MENU               (1U)
#define PAGE_MODE_SELECT        (2U)
#define PAGE_SPEED_ADJUST       (3U)
#define PAGE_TIME_SET           (4U)
#define PAGE_PASSWORD           (6U)
#define PAGE_SPEED_LIMIT_PASS   (7U)
#define PAGE_PRESSURE           (8U)
#define PAGE_MESSAGE            (9U)    /* 通用提示页 */

/* ---- 菜单项编号 ---- */
#define MENU_ITEM_PRESSURE      (0U)
#define MENU_ITEM_MODE          (1U)
#define MENU_ITEM_SPEED         (2U)
#define MENU_ITEM_TIME_SET      (3U)
#define MENU_ITEM_TIME_CLEAR    (4U)
#define MENU_ITEM_COUNT         (5U)

/* ---- 密码 ---- */
#define MENU_PASSWORD_TIME      (123U)
#define MENU_PASSWORD_SPEED     (5187U)

/* ---- 密码用途 ---- */
#define PWD_ACTION_SET_TIME     (0U)
#define PWD_ACTION_CLEAR_TIME   (1U)
#define PWD_ACTION_UNLOCK_SPEED (2U)

/* ---- 转速范围 ---- */
#define MENU_SPEED_MIN          (25U)
#define MENU_SPEED_MAX_NORMAL   (100U)
#define MENU_SPEED_MAX_UNLOCK   (150U)

/* ---- 气压范围 ---- */
#define MENU_PRESSURE_MIN       (0U)
#define MENU_PRESSURE_MAX       (100U)
#define MENU_PRESSURE_STEP      (20U)

/* ---- 时间上限 ---- */
#define MENU_TIME_MAX_SECONDS   (9999UL * 3600UL + 59UL * 60UL + 59UL)

/* ---- 状态语义（与旧工程一致）---- */
#define STATE_STOP              (0U)    /* 停止 */
#define STATE_RUN               (1U)    /* 启动 */
#define MODE_AIR                (0U)    /* 出气（电机停） */
#define MODE_ICE                (1U)    /* 出冰（电机转） */

/* ---- 提示类型 ---- */
#define MSG_PWD_OK              (0U)
#define MSG_PWD_ERR             (1U)
#define MSG_SET_OK              (2U)
#define MSG_SET_CANCEL          (3U)
#define MSG_CLR_OK              (4U)
#define MSG_CLR_CANCEL          (5U)

/* ---- 布局常量 ---- */
#define MENU_HZ_W               (32U)
#define MENU_HZ_H               (32U)
#define MENU_LINE_STEP          (56U)
#define MENU_COL_STEP           (32U)
#define MENU_WORD_GAP           (24U)
#define MENU_TITLE_X            (4U * MENU_COL_STEP + MENU_WORD_GAP)

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 菜单系统运行状态
 */
typedef struct {
    Q08U_  page;
    Q08U_  menu_index;
    Q08U_  mode;                /* MODE_ICE / MODE_AIR */
    Q16U_  speed;
    Q32U_  set_time;
    Q32U_  run_time;
    Q08U_  work_state;          /* STATE_RUN / STATE_STOP */
    Q08U_  pwd_input[4];
    Q08U_  pwd_index;
    Q08U_  pwd_action;          /* PWD_ACTION_* */
    Q08U_  time_index;
    Q08U_  pressure;
    Q08U_  speed_unlocked;
    Q08U_  alarm_code;
    Q08U_  need_refresh;
    Q08U_  full_refresh;

    /* 备份值 */
    Q16U_  backup_speed;
    Q08U_  backup_mode;
    Q08U_  backup_pressure;
    Q32U_  backup_set_time;

    /* 提示页 */
    Q08U_  msg_type;            /* MSG_* */
    Q08U_  msg_return_page;     /* 返回页 */
} ST_MENU_STATE;

/* ======================== 4. Globals ====================== */

/* ---- 字符串 ---- */
static const Q16U_ S_WORK[]      = {0x5DE5U, 0x4F5CU, 0x72B6U, 0x6001U, 0U};
static const Q16U_ S_NORMAL[]    = {0x6B63U, 0x5E38U, 0U};
static const Q16U_ S_STOP[]      = {0x505CU, 0x6B62U, 0U};
static const Q16U_ S_START[]     = {0x542FU, 0x52A8U, 0U};
static const Q16U_ S_MODE[]      = {0x6A21U, 0x5F0FU, 0x9009U, 0x62E9U, 0U};
static const Q16U_ S_ICE[]       = {0x51FAU, 0x51B0U, 0x6A21U, 0x5F0FU, 0U};
static const Q16U_ S_AIR[]       = {0x51FAU, 0x6C14U, 0x6A21U, 0x5F0FU, 0U};
static const Q16U_ S_SET_TIME[]  = {0x8BBEU, 0x7F6EU, 0x65F6U, 0x95F4U, 0U};
static const Q16U_ S_RUN_TIME[]  = {0x8FD0U, 0x884CU, 0x65F6U, 0x95F4U, 0U};
static const Q16U_ S_SET_SPEED[] = {0x8BBEU, 0x7F6EU, 0x901FU, 0x5EA6U, 0U};
static const Q16U_ S_PASSWORD[]  = {0x0070U, 0x0061U, 0x0073U, 0x0073U,
                                    0x0077U, 0x006FU, 0x0072U, 0x0064U, 0U};
static const Q16U_ S_MENU_0[]    = {0x6C14U, 0x538BU, 0x8C03U, 0x8282U, 0U};
static const Q16U_ S_MENU_1[]    = {0x6A21U, 0x5F0FU, 0x9009U, 0x62E9U, 0U};
static const Q16U_ S_MENU_2[]    = {0x7535U, 0x673AU, 0x901FU, 0x5EA6U, 0x8C03U, 0x8282U, 0U};
static const Q16U_ S_MENU_3[]    = {0x9501U, 0x5B9AU, 0x65F6U, 0x95F4U, 0x8BBEU, 0x7F6EU, 0U};
static const Q16U_ S_MENU_4[]    = {0x8FD0U, 0x884CU, 0x65F6U, 0x95F4U, 0x6E05U, 0x9664U, 0U};
static const Q16U_ S_PRESSURE[]  = {0x6C14U, 0x538BU, 0x8C03U, 0x8282U, 0U};
static const Q16U_ S_RPM_CODES[] = {0x0072U, 0x0070U, 0x006DU, 0x002FU, 0x006DU, 0x0069U, 0x006EU, 0U};

/* ---- 提示语 ---- */
static const Q16U_ S_PWD_OK[]     = {0x5BC6U, 0x7801U, 0x6B63U, 0x786EU, 0U};  /* 密码正确 */
static const Q16U_ S_PWD_ERR[]    = {0x5BC6U, 0x7801U, 0x9519U, 0x8BEFU, 0U};  /* 密码错误 */
static const Q16U_ S_SET_OK[]     = {0x8BBEU, 0x7F6EU, 0x6210U, 0x529FU, 0U};  /* 设置成功 */
static const Q16U_ S_SET_CANCEL[] = {0x8BBEU, 0x7F6EU, 0x5931U, 0x8D25U, 0U};  /* 设置失败 */
static const Q16U_ S_CLR_OK[]     = {0x6E05U, 0x9664U, 0x6210U, 0x529FU, 0U};  /* 清除成功 */
static const Q16U_ S_CLR_CANCEL[] = {0x6E05U, 0x9664U, 0x5931U, 0x8D25U, 0U};  /* 清除失败 */
static const Q16U_ S_PRESS_OK[]   = {0x6309U, 0x786EU, 0x8BA4U, 0x8FD4U, 0x56DEU, 0U}; /* 按确认返回 */

static ST_MENU_STATE s_Menu;
static Q16U_ s_Menu_Tick10ms = 0U;
static Q08U_ s_Menu_LastKey  = MENU_KEY_NONE;

/* ======================== 5. Function Prototypes ========== */

/* ---- 硬件接口 ---- */
static Q08U_ Menu_Key_Scan(void);
static void  Menu_Motor_Enable(Q08U_ en);
static void  Menu_Relay_Enable(Q08U_ en);
static Q08U_ Menu_Alarm_Get(void);

/* ---- 绘制工具 ---- */
static void  Menu_Draw_Text(Q16U_ x, Q16U_ y, const Q16U_ *txt, Q16U_ fg, Q16U_ bg);
static void  Menu_Draw_Digit(Q16U_ slot_x, Q16U_ y, Q08U_ d, Q16U_ fg, Q16U_ bg);
static void  Menu_Draw_Char(Q16U_ slot_x, Q16U_ y, Q16U_ code, Q16U_ fg, Q16U_ bg);
static Q32U_ Menu_Pow10(Q08U_ n);
static void  Menu_Draw_UInt(Q16U_ x, Q16U_ y, Q32U_ v, Q08U_ digits, Q16U_ fg, Q16U_ bg);
static void  Menu_Draw_Time(Q16U_ x, Q16U_ y, Q32U_ seconds, Q16U_ fg, Q16U_ bg);
static void  Menu_Draw_RpmMin(Q16U_ x, Q16U_ y, Q16U_ fg, Q16U_ bg);

/* ---- 页面显示 ---- */
static void  Menu_Display_Main(void);
static void  Menu_Display_Main_RunTime(void);
static void  Menu_Display_MenuList(void);
static void  Menu_Display_ModeSelect(void);
static void  Menu_Display_SpeedAdjust(void);
static void  Menu_Display_TimeSet(void);
static void  Menu_Display_Password(void);
static void  Menu_Display_Pressure(void);
static void  Menu_Display_Message(void);

/* ---- 按键处理 ---- */
static void  Menu_Handle_MainKey(Q08U_ key);
static void  Menu_Handle_MenuKey(Q08U_ key);
static void  Menu_Handle_PressureKey(Q08U_ key);
static void  Menu_Handle_ModeSelectKey(Q08U_ key);
static void  Menu_Handle_SpeedAdjustKey(Q08U_ key);
static void  Menu_Handle_TimeSetKey(Q08U_ key);
static void  Menu_Handle_PasswordKey(Q08U_ key);
static void  Menu_Handle_MessageKey(Q08U_ key);

/* ======================== 6. Functions ==================== */

/* ---------------- 硬件接口 ---------------- */

/**
 * @brief  按键扫描（带简单消抖）
 * @return 键值（MENU_KEY_*）
 */
static Q08U_ Menu_Key_Scan(void)
{
    static Q32U_ s_cnt[4]  = {0U, 0U, 0U, 0U};
    static Q08U_ s_last[4] = {0U, 0U, 0U, 0U};

    Q08U_ level[4];
    Q08U_ ret = MENU_KEY_NONE;

    /* 用 BSP 层语义接口（1 = 按下，0 = 松开）*/
    level[0] = (Q08U_)BSP_SYS_GPIO_Read_Key_UP();
    level[1] = (Q08U_)BSP_SYS_GPIO_Read_Key_DOWN();
    level[2] = (Q08U_)BSP_SYS_GPIO_Read_Key_MENU();
    level[3] = (Q08U_)BSP_SYS_GPIO_Read_Key_OK();

    for (Q08U_ i = 0U; i < 4U; i++)
    {
        if (s_last[i] == 0U)
        {
            s_cnt[i]++;
            if (s_cnt[i] >= 2U && s_cnt[i] <= 300U && level[i] == 1U)
            {
                ret = (Q08U_)(i + 1U);
            }
            else if (s_cnt[i] > 300U)
            {
                s_cnt[i] = 0U;
            }
        }
        else
        {
            s_cnt[i] = 0U;
        }
        s_last[i] = level[i];
    }
    return ret;
}

/**
 * @brief  电机使能
 * @param  en  1 使能 / 0 禁用
 */
static void Menu_Motor_Enable(Q08U_ en) { Systask.System_State_Flag.bit.motor_enable = en; }

/**
 * @brief  气阀使能
 * @param  en  1 使能 / 0 禁用
 */
static void Menu_Relay_Enable(Q08U_ en) { Systask.System_State_Flag.bit.value_enable = en; }

/**
 * @brief  读取当前报警码
 * @return 报警码
 */
static Q08U_ Menu_Alarm_Get(void)       { return Systask.V_Q32U_Error_Code; }

/* ---------------- 绘制工具 ---------------- */

/**
 * @brief  绘制 32×32 汉字字符串
 */
static void Menu_Draw_Text(Q16U_ x, Q16U_ y, const Q16U_ *txt, Q16U_ fg, Q16U_ bg)
{
    lcd_draw_hz32_str(x, y, txt, fg, bg);
}

/**
 * @brief  绘制单个数字
 */
static void Menu_Draw_Digit(Q16U_ slot_x, Q16U_ y, Q08U_ d, Q16U_ fg, Q16U_ bg)
{
    lcd_draw_hz16x32(slot_x + 8U, y, (Q16U_)(0x0030U + (d % 10U)), fg, bg);
}

/**
 * @brief  绘制单个 ASCII 字符
 */
static void Menu_Draw_Char(Q16U_ slot_x, Q16U_ y, Q16U_ code, Q16U_ fg, Q16U_ bg)
{
    lcd_draw_hz16x32(slot_x + 8U, y, code, fg, bg);
}

/**
 * @brief  计算 10 的 n 次方
 */
static Q32U_ Menu_Pow10(Q08U_ n) { Q32U_ r = 1U; while (n--) { r *= 10U; } return r; }

/**
 * @brief  绘制无符号整数
 */
static void Menu_Draw_UInt(Q16U_ x, Q16U_ y, Q32U_ v, Q08U_ digits, Q16U_ fg, Q16U_ bg)
{
    for (Q08U_ i = 0U; i < digits; i++)
    {
        Q08U_ d = (Q08U_)((v / Menu_Pow10(digits - 1U - i)) % 10U);
        Menu_Draw_Digit(x + i * MENU_COL_STEP, y, d, fg, bg);
    }
}

/**
 * @brief  绘制 HH:MM:SS 时间
 */
static void Menu_Draw_Time(Q16U_ x, Q16U_ y, Q32U_ seconds, Q16U_ fg, Q16U_ bg)
{
    Q32U_ h = seconds / 3600U;
    Q32U_ m = (seconds % 3600U) / 60U;
    Q32U_ s = seconds % 60U;
    Menu_Draw_Digit(x + 0U * MENU_COL_STEP, y, (Q08U_)((h/1000U)%10U), fg, bg);
    Menu_Draw_Digit(x + 1U * MENU_COL_STEP, y, (Q08U_)((h/100U) %10U), fg, bg);
    Menu_Draw_Digit(x + 2U * MENU_COL_STEP, y, (Q08U_)((h/10U)  %10U), fg, bg);
    Menu_Draw_Digit(x + 3U * MENU_COL_STEP, y, (Q08U_)( h       %10U), fg, bg);
    Menu_Draw_Char (x + 4U * MENU_COL_STEP, y, 0x003AU, fg, bg);
    Menu_Draw_Digit(x + 5U * MENU_COL_STEP, y, (Q08U_)(m/10U),        fg, bg);
    Menu_Draw_Digit(x + 6U * MENU_COL_STEP, y, (Q08U_)(m%10U),        fg, bg);
    Menu_Draw_Char (x + 7U * MENU_COL_STEP, y, 0x003AU, fg, bg);
    Menu_Draw_Digit(x + 8U * MENU_COL_STEP, y, (Q08U_)(s/10U),        fg, bg);
    Menu_Draw_Digit(x + 9U * MENU_COL_STEP, y, (Q08U_)(s%10U),        fg, bg);
}

/**
 * @brief  绘制 "rpm/min" 单位
 */
static void Menu_Draw_RpmMin(Q16U_ x, Q16U_ y, Q16U_ fg, Q16U_ bg)
{
    for (Q08U_ i = 0U; i < 7U; i++)
    {
        Menu_Draw_Char(x + i * MENU_COL_STEP, y, S_RPM_CODES[i], fg, bg);
    }
}

/* ---------------- 页面显示 ---------------- */

/**
 * @brief  主界面
 */
static void Menu_Display_Main(void)
{
    lcd_fill_color(HW_LCD_COLOR_BLACK);

    /* 行 0：工作状态 */
    Menu_Draw_Text(0U, 0U, S_WORK, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);

    if (s_Menu.alarm_code == 0U)
    {
        Menu_Draw_Text(MENU_TITLE_X, 0U, S_NORMAL, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
    }
    else
    {
        lcd_fill_rect(MENU_TITLE_X, 0U, 64U, MENU_HZ_H, HW_LCD_COLOR_WHITE);
        Menu_Draw_Char (MENU_TITLE_X,       0U, 0x0045U, HW_LCD_COLOR_BLACK, HW_LCD_COLOR_WHITE);
        Menu_Draw_Digit(MENU_TITLE_X + 32U, 0U, s_Menu.alarm_code, HW_LCD_COLOR_BLACK, HW_LCD_COLOR_WHITE);
    }
    lcd_fill_rect(MENU_TITLE_X + 64U + MENU_WORD_GAP, 0U, 64U, MENU_HZ_H, HW_LCD_COLOR_WHITE);
    Menu_Draw_Text(MENU_TITLE_X + 64U + MENU_WORD_GAP, 0U,
                   (s_Menu.work_state == STATE_RUN) ? S_START : S_STOP,
                   HW_LCD_COLOR_BLACK, HW_LCD_COLOR_WHITE);

    /* 行 1：模式选择 */
    Menu_Draw_Text(0U, MENU_LINE_STEP, S_MODE, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
    lcd_fill_rect(MENU_TITLE_X, MENU_LINE_STEP, 128U, MENU_HZ_H, HW_LCD_COLOR_WHITE);
    Menu_Draw_Text(MENU_TITLE_X, MENU_LINE_STEP,
                   (s_Menu.mode == MODE_ICE) ? S_ICE : S_AIR,
                   HW_LCD_COLOR_BLACK, HW_LCD_COLOR_WHITE);

    /* 行 2：设置时间 */
    Menu_Draw_Text(0U, MENU_LINE_STEP * 2U, S_SET_TIME, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
    Menu_Draw_Time(MENU_TITLE_X, MENU_LINE_STEP * 2U, s_Menu.set_time,
                   HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);

    /* 行 3：运行时间 */
    Menu_Draw_Text(0U, MENU_LINE_STEP * 3U, S_RUN_TIME, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
    Menu_Draw_Time(MENU_TITLE_X, MENU_LINE_STEP * 3U, s_Menu.run_time,
                   HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);

    /* 行 4：设置速度 */
    Menu_Draw_Text(0U, MENU_LINE_STEP * 4U, S_SET_SPEED, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
    Menu_Draw_UInt(MENU_TITLE_X, MENU_LINE_STEP * 4U, s_Menu.speed, 3U,
                   HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
    Menu_Draw_RpmMin(MENU_TITLE_X + 3U * MENU_COL_STEP, MENU_LINE_STEP * 4U,
                     HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
}

/**
 * @brief  主界面局部刷新：仅运行时间一行
 */
static void Menu_Display_Main_RunTime(void)
{
    Menu_Draw_Text(0U, MENU_LINE_STEP * 3U, S_RUN_TIME, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
    Menu_Draw_Time(MENU_TITLE_X, MENU_LINE_STEP * 3U, s_Menu.run_time, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
}

/**
 * @brief  菜单列表页
 */
static void Menu_Display_MenuList(void)
{
    const Q16U_ *items[] = {S_MENU_0, S_MENU_1, S_MENU_2, S_MENU_3, S_MENU_4};
    lcd_fill_color(HW_LCD_COLOR_BLACK);
    for (Q08U_ i = 0U; i < MENU_ITEM_COUNT; i++)
    {
        Q16U_ y = i * MENU_LINE_STEP;
        if (i == s_Menu.menu_index)
        {
            lcd_fill_rect(0U, y, HW_LCD_WIDTH, MENU_HZ_H, HW_LCD_COLOR_WHITE);
            Menu_Draw_Text(0U, y, items[i], HW_LCD_COLOR_BLACK, HW_LCD_COLOR_WHITE);
        }
        else
        {
            Menu_Draw_Text(0U, y, items[i], HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
        }
    }
}

/**
 * @brief  模式选择页
 */
static void Menu_Display_ModeSelect(void)
{
    lcd_fill_color(HW_LCD_COLOR_BLACK);
    Q16U_ y1 = MENU_LINE_STEP;
    Q16U_ y2 = MENU_LINE_STEP * 2U;

    if (s_Menu.mode == MODE_ICE)
    {
        lcd_fill_rect(0U, y1, HW_LCD_WIDTH, MENU_HZ_H, HW_LCD_COLOR_WHITE);
        Menu_Draw_Text(0U, y1, S_ICE, HW_LCD_COLOR_BLACK, HW_LCD_COLOR_WHITE);
        Menu_Draw_Text(0U, y2, S_AIR, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
    }
    else
    {
        Menu_Draw_Text(0U, y1, S_ICE, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
        lcd_fill_rect(0U, y2, HW_LCD_WIDTH, MENU_HZ_H, HW_LCD_COLOR_WHITE);
        Menu_Draw_Text(0U, y2, S_AIR, HW_LCD_COLOR_BLACK, HW_LCD_COLOR_WHITE);
    }
}

/**
 * @brief  转速调节页
 */
static void Menu_Display_SpeedAdjust(void)
{
    lcd_fill_color(HW_LCD_COLOR_BLACK);
    Q16U_ num_x = 3U * MENU_COL_STEP;
    Q16U_ num_y = MENU_LINE_STEP * 2U;
    lcd_fill_rect(num_x, num_y, 3U * MENU_COL_STEP, MENU_HZ_H, HW_LCD_COLOR_WHITE);
    Menu_Draw_UInt(num_x, num_y, s_Menu.speed, 3U, HW_LCD_COLOR_BLACK, HW_LCD_COLOR_WHITE);
    Menu_Draw_RpmMin(6U * MENU_COL_STEP, num_y, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
}

/**
 * @brief  时间设置页（位选择高亮）
 */
static void Menu_Display_TimeSet(void)
{
    lcd_fill_color(HW_LCD_COLOR_BLACK);
    Q32U_ h = s_Menu.set_time / 3600U;
    Q32U_ m = (s_Menu.set_time % 3600U) / 60U;
    Q32U_ s = s_Menu.set_time % 60U;
    Q08U_ d[8] = {
        (Q08U_)((h/1000U)%10U), (Q08U_)((h/100U)%10U),
        (Q08U_)((h/10U)%10U),   (Q08U_)(h%10U),
        (Q08U_)(m/10U),         (Q08U_)(m%10U),
        (Q08U_)(s/10U),         (Q08U_)(s%10U)
    };
    Q16U_ base_x = 1U * MENU_COL_STEP;
    Q16U_ y = MENU_LINE_STEP * 2U;
    static const Q08U_ slot_of_digit[8] = {0U,1U,2U,3U,5U,6U,8U,9U};

    for (Q08U_ i = 0U; i < 8U; i++)
    {
        Q16U_ x = base_x + slot_of_digit[i] * MENU_COL_STEP;
        if (i == s_Menu.time_index)
        {
            lcd_fill_rect(x, y, MENU_HZ_W, MENU_HZ_H, HW_LCD_COLOR_WHITE);
            Menu_Draw_Digit(x, y, d[i], HW_LCD_COLOR_BLACK, HW_LCD_COLOR_WHITE);
        }else
        {
            lcd_fill_rect(x, y, MENU_HZ_W, MENU_HZ_H, HW_LCD_COLOR_BLACK);
            Menu_Draw_Digit(x, y, d[i], HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
        }
    }
    Menu_Draw_Char(base_x + 4U * MENU_COL_STEP, y, 0x003AU, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
    Menu_Draw_Char(base_x + 7U * MENU_COL_STEP, y, 0x003AU, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
}

/**
 * @brief  密码输入页
 */
static void Menu_Display_Password(void)
{
    lcd_fill_color(HW_LCD_COLOR_BLACK);
    for (Q08U_ i = 0U; i < 8U; i++)
    {
        Menu_Draw_Char(i * MENU_COL_STEP, MENU_LINE_STEP * 2U, S_PASSWORD[i], HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
    }

    Q08U_ digits = (s_Menu.pwd_action == PWD_ACTION_UNLOCK_SPEED) ? 4U : 3U;

    for (Q08U_ i = 0U; i < digits; i++)
    {
        Q16U_ x = 10U * MENU_COL_STEP + i * MENU_COL_STEP;
        Q16U_ y = MENU_LINE_STEP * 2U;
        if (i == s_Menu.pwd_index)
        {
            lcd_fill_rect(x, y, MENU_HZ_W, MENU_HZ_H, HW_LCD_COLOR_WHITE);
            Menu_Draw_Digit(x, y, s_Menu.pwd_input[i], HW_LCD_COLOR_BLACK, HW_LCD_COLOR_WHITE);
        }
        else
        {
            lcd_fill_rect(x, y, MENU_HZ_W, MENU_HZ_H, HW_LCD_COLOR_BLACK);
            Menu_Draw_Digit(x, y, s_Menu.pwd_input[i], HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
        }
    }
}

/**
 * @brief  气压调节页
 */
static void Menu_Display_Pressure(void)
{
    lcd_fill_color(HW_LCD_COLOR_BLACK);
    Q16U_ title_x = (HW_LCD_WIDTH - 4U * MENU_COL_STEP) / 2U;
    Menu_Draw_Text(title_x, MENU_LINE_STEP, S_PRESSURE, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
    Q16U_ line2_x = (HW_LCD_WIDTH - 4U * MENU_COL_STEP) / 2U;
    Q16U_ line2_y = MENU_LINE_STEP * 3U;
    lcd_fill_rect(line2_x, line2_y, 4U * MENU_COL_STEP, MENU_HZ_H, HW_LCD_COLOR_WHITE);
    Menu_Draw_UInt(line2_x, line2_y, s_Menu.pressure, 3U, HW_LCD_COLOR_BLACK, HW_LCD_COLOR_WHITE);
    Menu_Draw_Char(line2_x + 3U * MENU_COL_STEP, line2_y, 0x0025U, HW_LCD_COLOR_BLACK, HW_LCD_COLOR_WHITE);
}

/**
 * @brief  通用提示页
 */
static void Menu_Display_Message(void)
{
    lcd_fill_color(HW_LCD_COLOR_BLACK);

    const Q16U_ *msg = S_PWD_OK;
    switch (s_Menu.msg_type)
    {
        case MSG_PWD_OK:      msg = S_PWD_OK;      break;
        case MSG_PWD_ERR:     msg = S_PWD_ERR;     break;
        case MSG_SET_OK:      msg = S_SET_OK;      break;
        case MSG_SET_CANCEL:  msg = S_SET_CANCEL;  break;
        case MSG_CLR_OK:      msg = S_CLR_OK;      break;
        case MSG_CLR_CANCEL:  msg = S_CLR_CANCEL;  break;
        default:              msg = S_PWD_OK;      break;
    }

    Q16U_ msg_x = (HW_LCD_WIDTH - 4U * MENU_COL_STEP) / 2U;
    Q16U_ msg_y = MENU_LINE_STEP * 2U;
    Menu_Draw_Text(msg_x, msg_y, msg, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);

    Q16U_ tip_x = (HW_LCD_WIDTH - 6U * MENU_COL_STEP) / 2U;
    Q16U_ tip_y = MENU_LINE_STEP * 4U;
    Menu_Draw_Text(tip_x, tip_y, S_PRESS_OK, HW_LCD_COLOR_WHITE, HW_LCD_COLOR_BLACK);
}

/* ---------------- 按键处理 ---------------- */

/**
 * @brief  主页面按键处理
 * @param  key  键值
 */
static void Menu_Handle_MainKey(Q08U_ key)
{
    if (key == MENU_KEY_OK)
    {
        if (s_Menu.alarm_code != 0U && s_Menu.work_state == STATE_STOP) { return; }

        /* 时间到后再启动时先清零运行时间 */
        if (s_Menu.work_state == STATE_STOP && s_Menu.run_time >= s_Menu.set_time && s_Menu.set_time > 0U)
        {
            s_Menu.run_time = 0U;
        }

        s_Menu.work_state = (s_Menu.work_state == STATE_RUN) ? STATE_STOP : STATE_RUN;

        if (s_Menu.work_state == STATE_RUN)
        {
            if (s_Menu.mode == MODE_ICE) { Menu_Motor_Enable(1U); Menu_Relay_Enable(1U); }
            else                         { Menu_Motor_Enable(0U); Menu_Relay_Enable(1U); }
        }
        else
        {
            Menu_Motor_Enable(0U);
            Menu_Relay_Enable(0U);
        }
        s_Menu.need_refresh = 1U;
        s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_MENU)
    {
        s_Menu.page       = PAGE_MENU;
        s_Menu.menu_index = 0U;
        s_Menu.need_refresh = 1U;
        s_Menu.full_refresh = 1U;
    }
}
/**
 * @brief  菜单列表页按键处理
 * @param  key  键值
 */
static void Menu_Handle_MenuKey(Q08U_ key)
{
    if (key == MENU_KEY_UP)
    {
        if (s_Menu.menu_index > 0U)
        {
            s_Menu.menu_index--;
        }
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_DOWN)
    {
        if (s_Menu.menu_index < MENU_ITEM_COUNT - 1U)
        {
            s_Menu.menu_index++;
        }
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_OK)
    {
        switch (s_Menu.menu_index)
        {
            case MENU_ITEM_PRESSURE:
                s_Menu.backup_pressure = s_Menu.pressure;
                s_Menu.page = PAGE_PRESSURE;
                break;

            case MENU_ITEM_MODE:
                s_Menu.backup_mode = s_Menu.mode;
                s_Menu.page = PAGE_MODE_SELECT;
                break;

            case MENU_ITEM_SPEED:
                s_Menu.backup_speed = s_Menu.speed;
                s_Menu.page = PAGE_SPEED_ADJUST;
                break;

            case MENU_ITEM_TIME_SET:
                s_Menu.page       = PAGE_PASSWORD;
                s_Menu.pwd_action = PWD_ACTION_SET_TIME;
                s_Menu.pwd_index  = 0U;
                memset((void *)s_Menu.pwd_input, 0x00, 4U);
                break;

            case MENU_ITEM_TIME_CLEAR:
                s_Menu.page       = PAGE_PASSWORD;
                s_Menu.pwd_action = PWD_ACTION_CLEAR_TIME;
                s_Menu.pwd_index  = 0U;
                memset((void *)s_Menu.pwd_input, 0x00, 4U);
                break;
            default: break;
        }
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_MENU)
    {
        s_Menu.page = PAGE_MAIN;
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
}

/**
 * @brief  气压页按键处理
 * @param  key  键值
 */
static void Menu_Handle_PressureKey(Q08U_ key)
{
    if (key == MENU_KEY_UP)
    {
        if (s_Menu.pressure + MENU_PRESSURE_STEP <= MENU_PRESSURE_MAX)
            s_Menu.pressure += MENU_PRESSURE_STEP;
        else
            s_Menu.pressure = MENU_PRESSURE_MAX;
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_DOWN)
    {
        if (s_Menu.pressure >= MENU_PRESSURE_MIN + MENU_PRESSURE_STEP)
            s_Menu.pressure -= MENU_PRESSURE_STEP;
        else
            s_Menu.pressure = MENU_PRESSURE_MIN;
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_OK)
    {
        s_Menu.msg_type = MSG_SET_OK;
        s_Menu.msg_return_page = PAGE_MENU;
        s_Menu.page = PAGE_MESSAGE;
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_MENU)
    {
        s_Menu.pressure = s_Menu.backup_pressure;
        s_Menu.msg_type = MSG_SET_CANCEL;
        s_Menu.msg_return_page = PAGE_MENU;
        s_Menu.page = PAGE_MESSAGE;
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
}

/**
 * @brief  模式选择页按键处理
 * @param  key  键值
 */
static void Menu_Handle_ModeSelectKey(Q08U_ key)
{
    if (key == MENU_KEY_UP || key == MENU_KEY_DOWN)
    {
        s_Menu.mode = (s_Menu.mode == MODE_ICE) ? MODE_AIR : MODE_ICE;
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_OK)
    {
        if (s_Menu.work_state == STATE_RUN)
        {
            if (s_Menu.mode == MODE_ICE)
            {
                Menu_Motor_Enable(1U);
                Menu_Relay_Enable(1U);
            }
            else
            {
                Menu_Motor_Enable(0U);
                Menu_Relay_Enable(1U);
            }
        }
        s_Menu.msg_type = MSG_SET_OK;
        s_Menu.msg_return_page = PAGE_MENU;
        s_Menu.page = PAGE_MESSAGE;
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_MENU)
    {
        s_Menu.mode = s_Menu.backup_mode;
        s_Menu.msg_type = MSG_SET_CANCEL;
        s_Menu.msg_return_page = PAGE_MENU;
        s_Menu.page = PAGE_MESSAGE;
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
}

/**
 * @brief  转速调节页按键处理
 * @param  key  键值
 */
static void Menu_Handle_SpeedAdjustKey(Q08U_ key)
{
    if (key == MENU_KEY_UP)
    {
        if (s_Menu.speed >= MENU_SPEED_MAX_NORMAL && s_Menu.speed_unlocked == 0U)
        {
            s_Menu.page       = PAGE_SPEED_LIMIT_PASS;
            s_Menu.pwd_action = PWD_ACTION_UNLOCK_SPEED;
            s_Menu.pwd_index  = 0U;
            memset((void *)s_Menu.pwd_input, 0x00, 4U);
        }
        else
        {
            if (s_Menu.speed < MENU_SPEED_MAX_UNLOCK)
            {
                s_Menu.speed += 25U;
            }
            if (s_Menu.speed > MENU_SPEED_MAX_UNLOCK)
            {
                s_Menu.speed = MENU_SPEED_MAX_UNLOCK;
            }
        }
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_DOWN)
    {
        if (s_Menu.speed > MENU_SPEED_MIN)
        {
            s_Menu.speed -= 25U;
        }
        if (s_Menu.speed < MENU_SPEED_MIN)
        {
            s_Menu.speed = MENU_SPEED_MIN;
        }
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_OK)
    {
        s_Menu.msg_type = MSG_SET_OK;
        s_Menu.msg_return_page = PAGE_MENU;
        s_Menu.page = PAGE_MESSAGE;
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_MENU)
    {
        s_Menu.speed = s_Menu.backup_speed;
        s_Menu.msg_type = MSG_SET_CANCEL;
        s_Menu.msg_return_page = PAGE_MENU;
        s_Menu.page = PAGE_MESSAGE;
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
}

/**
 * @brief  时间设置页按键处理
 * @param  key  键值
 */
static void Menu_Handle_TimeSetKey(Q08U_ key)
{
    static const Q32U_ weight[8] = {
        1000UL*3600UL, 100UL*3600UL, 10UL*3600UL, 3600UL,
        10UL*60UL,     60UL,
        10UL,          1UL
    };

    if (key == MENU_KEY_UP)
    {
        Q32U_ w = weight[s_Menu.time_index];
        if (s_Menu.set_time + w <= MENU_TIME_MAX_SECONDS)
        {
            s_Menu.set_time += w;
        }
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_DOWN)
    {
        Q32U_ w = weight[s_Menu.time_index];
        if (s_Menu.set_time >= w)
        {
            s_Menu.set_time -= w;
        }
        else
        {
            s_Menu.set_time = 0U;
        }
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_OK)
    {
        if (s_Menu.time_index >= 7U)
        {
            /* 最后一位 -> 保存 */
            s_Menu.msg_type = MSG_SET_OK;
            s_Menu.msg_return_page = PAGE_MENU;
            s_Menu.page = PAGE_MESSAGE;
        }
        else
        {
            s_Menu.time_index++;
        }
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_MENU)
    {
        s_Menu.set_time = s_Menu.backup_set_time;
        s_Menu.msg_type = MSG_SET_CANCEL;
        s_Menu.msg_return_page = PAGE_MENU;
        s_Menu.page = PAGE_MESSAGE;
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
}

/**
 * @brief  密码页按键处理（按 pwd_action 三分支）
 * @param  key  键值
 */
static void Menu_Handle_PasswordKey(Q08U_ key)
{
    Q08U_ max_digit = (s_Menu.pwd_action == PWD_ACTION_UNLOCK_SPEED) ? 4U : 3U;

    if (key == MENU_KEY_UP)
    {
        s_Menu.pwd_input[s_Menu.pwd_index] = (Q08U_)((s_Menu.pwd_input[s_Menu.pwd_index] + 1U) % 10U);
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_DOWN)
    {
        s_Menu.pwd_input[s_Menu.pwd_index] = (Q08U_)((s_Menu.pwd_input[s_Menu.pwd_index] + 9U) % 10U);
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
    else if (key == MENU_KEY_OK)
    {
        s_Menu.pwd_index++;

        if (s_Menu.pwd_index >= max_digit)
        {
            Q16U_ input = 0U;
            for (Q08U_ i = 0U; i < max_digit; i++)
            {
                input = (Q16U_)(input * 10U + s_Menu.pwd_input[i]);
            }

            Q16U_ correct = (s_Menu.pwd_action == PWD_ACTION_UNLOCK_SPEED) ? MENU_PASSWORD_SPEED : MENU_PASSWORD_TIME;

            if (input == correct)
            {
                s_Menu.msg_type = MSG_PWD_OK;

                switch (s_Menu.pwd_action)
                {
                    case PWD_ACTION_SET_TIME:
                        s_Menu.backup_set_time = s_Menu.set_time;
                        s_Menu.time_index = 0U;
                        s_Menu.msg_return_page = PAGE_TIME_SET;
                        break;

                    case PWD_ACTION_CLEAR_TIME:
                        s_Menu.run_time = 0U;
                        s_Menu.msg_type = MSG_CLR_OK;               /* 清除成功 */
                        s_Menu.msg_return_page = PAGE_MAIN;
                        break;

                    case PWD_ACTION_UNLOCK_SPEED:
                        s_Menu.speed_unlocked = 1U;
                        s_Menu.msg_return_page = PAGE_SPEED_ADJUST;
                        break;
                    default: break;
                }
            }
            else
            {
                s_Menu.msg_type = MSG_PWD_ERR;

                switch (s_Menu.pwd_action)
                {
                    case PWD_ACTION_SET_TIME:
                    case PWD_ACTION_CLEAR_TIME:
                        s_Menu.msg_return_page = PAGE_MENU;
                        break;
                    case PWD_ACTION_UNLOCK_SPEED:
                        s_Menu.msg_return_page = PAGE_SPEED_ADJUST;
                        break;
                    default: break;
                }
            }

            s_Menu.page = PAGE_MESSAGE;
            s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
        }
        else
        {
            s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
        }
    }
    else if (key == MENU_KEY_MENU)
    {
        s_Menu.page = PAGE_MENU;
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
}

/**
 * @brief  提示页按键处理
 * @param  key  键值
 */
static void Menu_Handle_MessageKey(Q08U_ key)
{
    if (key == MENU_KEY_OK || key == MENU_KEY_MENU)
    {
        s_Menu.page = s_Menu.msg_return_page;
        s_Menu.need_refresh = 1U; s_Menu.full_refresh = 1U;
    }
}

/* ---------------- 与 Systask 同步 ---------------- */

/**
 * @brief  菜单状态同步到 Systask
 */
void Menu_SyncToSystask(void)
{
    /* ① 报警码：从 Systask 读，变化时触发重绘 */
    Q08U_ alarm = Menu_Alarm_Get();
    if (alarm != s_Menu.alarm_code)
    {
        s_Menu.alarm_code = alarm;
        s_Menu.need_refresh = 1U;
        s_Menu.full_refresh = 1U;

        if (alarm != 0U)
        {
            s_Menu.work_state = STATE_STOP;
            Menu_Motor_Enable(0U);
            Menu_Relay_Enable(0U);
        }
    }

    /* ② 电机使能：出冰 + 启动 才转 */
    if (s_Menu.work_state == STATE_RUN && s_Menu.mode == MODE_ICE)
    {
        Systask.System_State_Flag.bit.motor_enable = 1U;
    }
    else
    {
        Systask.System_State_Flag.bit.motor_enable = 0U;
    }

    /* ③ 气阀使能：只要启动就开 */
    if (s_Menu.work_state == STATE_RUN)
    {
        Systask.System_State_Flag.bit.value_enable = 1U;
    }
    else
    {
        Systask.System_State_Flag.bit.value_enable = 0U;
    }

    /* ④ 转速 */
    Systask.Speed_rpm = s_Menu.speed;
}

/* ---------------- 初始化与 10ms 主循环 ---------------- */

/**
 * @brief  菜单初始化
 */
void Menu_Init(void)
{
    memset((void *)&s_Menu, 0x00, sizeof(s_Menu));
    memset((void *)s_Menu.pwd_input, 0x00, 4U);

    s_Menu.page         = PAGE_MAIN;
    s_Menu.mode         = MODE_ICE;         /* 默认出冰（与旧工程一致） */
    s_Menu.speed        = 100U;
    s_Menu.set_time     = 3U * 3600U;
    s_Menu.time_index   = 0U;
    s_Menu.pressure     = 0U;
    s_Menu.work_state   = STATE_STOP;
    s_Menu.need_refresh = 1U;
    s_Menu.full_refresh = 1U;

    s_Menu_Tick10ms = 0U;
    s_Menu_LastKey  = MENU_KEY_NONE;
}

/**
 * @brief  菜单 10ms 周期任务
 */
void Menu_Loop_10ms(void)
{
    /* ============ 第 1 步：按键扫描 ============ */
    Q08U_ key = Menu_Key_Scan();
    if (key != MENU_KEY_NONE && key != s_Menu_LastKey)
    {
        switch (s_Menu.page)
        {
            case PAGE_MAIN:             Menu_Handle_MainKey(key);         break;
            case PAGE_MENU:             Menu_Handle_MenuKey(key);         break;
            case PAGE_MODE_SELECT:      Menu_Handle_ModeSelectKey(key);   break;
            case PAGE_SPEED_ADJUST:     Menu_Handle_SpeedAdjustKey(key);  break;
            case PAGE_TIME_SET:         Menu_Handle_TimeSetKey(key);      break;
            case PAGE_PASSWORD:         Menu_Handle_PasswordKey(key);     break;
            case PAGE_SPEED_LIMIT_PASS: Menu_Handle_PasswordKey(key);     break;
            case PAGE_PRESSURE:         Menu_Handle_PressureKey(key);     break;
            case PAGE_MESSAGE:          Menu_Handle_MessageKey(key);      break;
            default: break;
        }
    }
    s_Menu_LastKey = key;

    /* ============ 第 2 步：每秒任务 ============ */
    s_Menu_Tick10ms++;
    if (s_Menu_Tick10ms >= 100U)
    {
        s_Menu_Tick10ms = 0U;

        if (s_Menu.work_state == STATE_RUN)
        {
            s_Menu.run_time++;

            /* 只有 set_time > 0 才做自动停止（0 = 不限时） */
            if (s_Menu.set_time > 0U && s_Menu.run_time >= s_Menu.set_time)
            {
                s_Menu.work_state = STATE_STOP;
                Menu_Motor_Enable(0U);
                Menu_Relay_Enable(0U);
                s_Menu.full_refresh = 1U;
            }
            s_Menu.need_refresh = 1U;
        }
    }

    /* ============ 第 3 步：显示刷新 ============ */
    if (s_Menu.need_refresh != 0U)
    {
        if (s_Menu.full_refresh != 0U)
        {
            switch (s_Menu.page)
            {
                case PAGE_MAIN:             Menu_Display_Main();        break;
                case PAGE_MENU:             Menu_Display_MenuList();    break;
                case PAGE_MODE_SELECT:      Menu_Display_ModeSelect();  break;
                case PAGE_SPEED_ADJUST:     Menu_Display_SpeedAdjust(); break;
                case PAGE_TIME_SET:         Menu_Display_TimeSet();     break;
                case PAGE_PASSWORD:         Menu_Display_Password();    break;
                case PAGE_SPEED_LIMIT_PASS: Menu_Display_Password();    break;
                case PAGE_PRESSURE:         Menu_Display_Pressure();    break;
                case PAGE_MESSAGE:          Menu_Display_Message();     break;
                default: break;
            }
            s_Menu.full_refresh = 0U;
        }
        else
        {
            if (s_Menu.page == PAGE_MAIN)
            {
                Menu_Display_Main_RunTime();
            }
        }
        s_Menu.need_refresh = 0U;
    }

    /* ============ 第 4 步：同步状态到 Systask ============ */
    Menu_SyncToSystask();
}
