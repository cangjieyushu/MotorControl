/*
*     File Name :                        sys_err
*     Library/Module Name :              sys
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             故障显示（LED 闪烁错误码）
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "sys_err.h"


/*-------------------------- 2. 变量 ---------------------------------*/
/* 全局唯一实例（error_led_table 全部清零，时间常量用默认值）*/
ST_ERROR_CONTROL Error_Ctrl = {
    .error_led_table[0] = 0,
    .error_led_table[1] = 0,
    .error_led_table[2] = 0,
    .error_led_table[3] = 0,
    .error_led_table[4] = 0,
    .error_led_table[5] = 0,
    .error_led_table[6] = 0,
    .error_led_table[7] = 0,
    .error_led_table[8] = 0,
    .error_led_table[9] = 0,
    .error_led_table[10] = 0,
    .error_led_table[11] = 0,
    .error_led_table[12] = 0,
    .error_led_table[13] = 0,
    .error_led_table[14] = 0,
    .error_led_table[15] = 0,
    .error_led_table[16] = 0,
    .error_led_table[17] = 0,
    .error_led_table[18] = 0,
    .error_led_table[19] = 0,
    .error_led_table[20] = 0,
    .error_led_table[21] = 0,
    .error_led_table[22] = 0,
    .error_led_table[23] = 0,
    .error_led_table[24] = 0,
    .error_led_table[25] = 0,
    .error_led_table[26] = 0,
    .error_led_table[27] = 0,
    .error_led_table[28] = 0,
    .error_led_table[29] = 0,
    .error_led_table[30] = 0,
    .error_led_table[31] = 0,
    .error_led_on_time    = HW_ERR_LED_ON_TIME,
    .error_led_off_time_1 = HW_ERR_LED_OFF_TIME_1,
    .error_led_off_time_2 = HW_ERR_LED_OFF_TIME_2,
};


/*-------------------------- 3. 内部函数 --------------------------------*/
/*
Function: Error_LED
Description: LED 闪烁状态机（根据 error_code 驱动 LED 闪烁模式）
             状态流转：INIT → WAIT → LIGHT → END → INIT
Input: pEC - 错误控制结构体指针
Output: 无
Return: 无
Author: CJYS
*/
static void Error_LED(ST_ERROR_CONTROL* pEC)
{
    /* 无错误：状态机复位 */
    if (pEC->error_code == 0U)
    {
        pEC->error_led_flow    = ERROR_LED_INIT;
        pEC->error_led_counter = 0U;
        return;
    }

    switch (pEC->error_led_flow)
    {
        /* ---- 初始化：拆分错误码到两个数字 ---- */
        case ERROR_LED_INIT:
        {
            Q32U_ code = pEC->error_code;
            if (code >= HW_ERR_CODE_MAX)
            {
                code = HW_ERR_CODE_MAX - 1U;    /* 防止越界 */
            }
            pEC->error_code_led_1 = pEC->error_led_table[code] / 10U;
            pEC->error_code_led_2 = pEC->error_led_table[code] % 10U;
            pEC->error_led_counter = 0U;
            pEC->error_led_flow    = ERROR_LED_WAIT;
        } break;

        /* ---- 第一次熄灭期 ---- */
        case ERROR_LED_WAIT:
        {
            pEC->error_led_counter++;
            if (pEC->error_led_counter >= pEC->error_led_off_time_1)
            {
                pEC->error_led_counter = 0U;
                pEC->error_led_flow    = ERROR_LED_LIGHT;
            }
        } break;

        /* ---- 点亮期 ---- */
        case ERROR_LED_LIGHT:
        {
            pEC->error_led_counter++;
            if (pEC->error_led_counter >= pEC->error_led_on_time)
            {
                pEC->error_led_counter = 0U;
                pEC->error_led_flow    = ERROR_LED_END;
            }
        } break;

        /* ---- 第二次熄灭期 ---- */
        case ERROR_LED_END:
        {
            pEC->error_led_counter++;
            if (pEC->error_led_counter >= pEC->error_led_off_time_2)
            {
                pEC->error_led_counter = 0U;
                pEC->error_led_flow    = ERROR_LED_INIT;   /* 循环 */
            }
        } break;

        default:
        {
            pEC->error_led_flow = ERROR_LED_INIT;
        } break;
    }
}


/*-------------------------- 4. 公有接口实现 -----------------------------*/
/*
Function: Error_Priority_Check
Description: 故障优先级检查 + LED 闪烁状态更新
Input: error_all - 32 位错误位图
Output: 无
Return: 错误码（0 = 无错误；1~32 = 对应错误）
Author: CJYS
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

    /* ---- 2. 更新 LED 闪烁状态机（无论是否有错都更新）---- */
    Error_LED(pEC);

    /* ---- 3. 返回当前错误码 ---- */
    return pEC->error_code;
}
