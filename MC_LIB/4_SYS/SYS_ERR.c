/**
 * @file    sys_err.c
 * @brief   故障显示（LED 二段式闪烁错误码）
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "sys_err.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */
ST_ERROR_CONTROL Error_Ctrl = {
    .error_led_table[0] = 11,
    .error_led_table[1] = 12,
    .error_led_table[2] = 13,
    .error_led_table[3] = 14,
    .error_led_table[4] = 15,
    .error_led_table[5] = 21,
    .error_led_table[6] = 22,
    .error_led_table[7] = 23,
    .error_led_table[8] = 24,
    .error_led_table[9] = 25,
    .error_led_table[10] = 31,
    .error_led_table[11] = 32,
    .error_led_table[12] = 33,
    .error_led_table[13] = 34,
    .error_led_table[14] = 35,
    .error_led_table[15] = 41,
    .error_led_table[16] = 42,
    .error_led_table[17] = 43,
    .error_led_table[18] = 44,
    .error_led_table[19] = 45,
    .error_led_table[20] = 51,
    .error_led_table[21] = 52,
    .error_led_table[22] = 53,
    .error_led_table[23] = 54,
    .error_led_table[24] = 55,
    .error_led_table[25] = 61,
    .error_led_table[26] = 62,
    .error_led_table[27] = 63,
    .error_led_table[28] = 64,
    .error_led_table[29] = 65,
    .error_led_table[30] = 71,
    .error_led_table[31] = 72,

    .error_led_on_time    = HW_ERR_LED_ON_TIME,     /* 50ms  */
    .error_led_off_time   = HW_ERR_LED_OFF_TIME,    /* 50ms  */
    .error_led_gap_1      = HW_ERR_LED_GAP_1_TIME,  /* 300ms */
    .error_led_gap_2      = HW_ERR_LED_GAP_2_TIME,  /* 2s    */
};

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  LED 二段式闪烁状态机
 * @param  pEC  错误控制结构体指针
 */
static void Error_LED(ST_ERROR_CONTROL* pEC)
{
    /* 无错误：LED 熄灭，状态机复位 */
    if (pEC->error_code == 0U)
    {
        pEC->error_led_flow = ERROR_LED_INIT;
        pEC->error_led_cnt  = 0U;
        SYS_ERR_LED_OFF();
        return;
    }

    switch (pEC->error_led_flow)
    {
        /* ---- 初始化：拆分错误码到十位/个位闪烁次数 ---- */
        case ERROR_LED_INIT:
        {
            Q32U_ idx = pEC->error_code;

            if (idx > HW_ERR_CODE_MAX)
            {
                idx = HW_ERR_CODE_MAX;              /* 防止越界 */
            }
            idx -= 1U;                              /* 错误码1 → table[0] */

            pEC->error_code_led_1 = pEC->error_led_table[idx] / 10U;   /* 十位：第1段闪次数 */
            pEC->error_code_led_2 = pEC->error_led_table[idx] % 10U;   /* 个位：第2段闪次数 */
            pEC->error_led_cnt    = 0U;
            SYS_ERR_LED_OFF();
            pEC->error_led_flow   = ERROR_LED_TENS_ON;                 /* 从十位段开始 */
        } break;

        /* ---- 十位段：点亮 ---- */
        case ERROR_LED_TENS_ON:
        {
            SYS_ERR_LED_ON();
            pEC->error_led_cnt++;
            if (pEC->error_led_cnt >= pEC->error_led_on_time)          /* 亮满100ms */
            {
                pEC->error_led_cnt = 0U;
                SYS_ERR_LED_OFF();
                pEC->error_led_flow = ERROR_LED_TENS_OFF;
            }
        } break;

        /* ---- 十位段：熄灭（闪烁间隔）---- */
        case ERROR_LED_TENS_OFF:
        {
            pEC->error_led_cnt++;
            if (pEC->error_led_cnt >= pEC->error_led_off_time)         /* 灭满50ms */
            {
                pEC->error_led_cnt = 0U;
                if (pEC->error_code_led_1 > 0U)
                {
                    pEC->error_code_led_1--;                          /* 又闪完一次 */
                    pEC->error_led_flow = ERROR_LED_TENS_ON;          /* 继续闪十位 */
                }
                else
                {
                    pEC->error_led_flow = ERROR_LED_GAP_1;            /* 十位闪完，长间隔 */
                }
            }
        } break;

        /* ---- 十位→个位 长间隔（300ms）---- */
        case ERROR_LED_GAP_1:
        {
            pEC->error_led_cnt++;
            if (pEC->error_led_cnt >= pEC->error_led_gap_1)
            {
                pEC->error_led_cnt  = 0U;
                pEC->error_led_flow = ERROR_LED_ONES_ON;
            }
        } break;

        /* ---- 个位段：点亮 ---- */
        case ERROR_LED_ONES_ON:
        {
            SYS_ERR_LED_ON();
            pEC->error_led_cnt++;
            if (pEC->error_led_cnt >= pEC->error_led_on_time)          /* 亮满100ms */
            {
                pEC->error_led_cnt = 0U;
                SYS_ERR_LED_OFF();
                pEC->error_led_flow = ERROR_LED_ONES_OFF;
            }
        } break;

        /* ---- 个位段：熄灭（闪烁间隔）---- */
        case ERROR_LED_ONES_OFF:
        {
            pEC->error_led_cnt++;
            if (pEC->error_led_cnt >= pEC->error_led_off_time)         /* 灭满50ms */
            {
                pEC->error_led_cnt = 0U;
                if (pEC->error_code_led_2 > 0U)
                {
                    pEC->error_code_led_2--;                          /* 又闪完一次 */
                    pEC->error_led_flow = ERROR_LED_ONES_ON;          /* 继续闪个位 */
                }
                else
                {
                    pEC->error_led_flow = ERROR_LED_GAP_2;            /* 个位闪完，长间隔 */
                }
            }
        } break;

        /* ---- 个位→循环 长间隔（2s）---- */
        case ERROR_LED_GAP_2:
        {
            pEC->error_led_cnt++;
            if (pEC->error_led_cnt >= pEC->error_led_gap_2)
            {
                pEC->error_led_cnt = 0U;
                pEC->error_led_flow = ERROR_LED_TENS_ON;              /* 回到十位，循环 */
            }
        } break;

        default:
        {
            pEC->error_led_flow = ERROR_LED_INIT;
        } break;
    }
}

/* ======================== 6. Functions ==================== */

/**
 * @brief  错误优先级检查 + LED 刷新
 * @param  error_all  错误位图（bit0 优先级最高）
 * @return 当前错误码（0 = 正常）
 */
Q32U_ Error_Priority_Check(Q32U_ error_all)
{
    ST_ERROR_CONTROL* pEC = &Error_Ctrl;

    /* ---- 1. 扫描错误位图，找最高优先级错误（bit0 优先级最高）---- */
    pEC->error_code = 0U;

    if (error_all != 0U)
    {
        for (Q08U_ i = 0U; i < 32U; i++)
        {
            if ((error_all & (1UL << i)) != 0U)
            {
                pEC->error_code = (Q32U_)(i + 1U);   /* 错误码从 1 开始 */
                break;
            }
        }
    }

    /* ---- 2. 更新 LED 二段式闪烁状态机（无论是否有错都更新）---- */
    Error_LED(pEC);

    /* ---- 3. 返回当前错误码 ---- */
    return pEC->error_code;
}
