/**
 * @file    sys_err.h
 * @brief   故障显示（LED 二段式闪烁错误码）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef SYS_ERR_H
#define SYS_ERR_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "bsp_sys_gpio.h"      /* LED 亮灭控制接口（红灯）*/

/* ======================== 2. Defines ====================== */
/* 错误 LED 闪烁时间常量（单位：10ms 调用一次）*/
#define HW_ERR_LED_ON_TIME          (10U)   /* 单次点亮时长：100ms  */
#define HW_ERR_LED_OFF_TIME         (5U)    /* 闪烁间隔（灭）：50ms */
#define HW_ERR_LED_GAP_1_TIME       (50U)   /* 十位→个位 间隔：500ms */
#define HW_ERR_LED_GAP_2_TIME       (200U)  /* 个位→循环 间隔：2s    */

/* 错误码最大个数 */
#define HW_ERR_CODE_MAX             (32U)

/* LED 亮/灭操作 */
#define SYS_ERR_LED_ON()            BSP_SYS_GPIO_LED1_Set()
#define SYS_ERR_LED_OFF()           BSP_SYS_GPIO_LED1_Clr()

/* ======================== 3. Typedefs ===================== */
typedef enum{
    ERROR_LED_INIT,         /* 初始化：拆分错误码到十位/个位闪烁次数 */
    ERROR_LED_TENS_ON,      /* 十位：点亮中 */
    ERROR_LED_TENS_OFF,     /* 十位：熄灭中（闪烁间隔）*/
    ERROR_LED_GAP_1,        /* 十位→个位 长间隔 */
    ERROR_LED_ONES_ON,      /* 个位：点亮中 */
    ERROR_LED_ONES_OFF,     /* 个位：熄灭中（闪烁间隔）*/
    ERROR_LED_GAP_2,        /* 个位→循环 长间隔 */
} EM_ERROR_LED_FLOW;

typedef struct{
    EM_ERROR_LED_FLOW  error_led_flow;        /* 当前状态 */
    Q32U_              error_led_cnt;         /* 状态内计时器 */

    Q32U_              error_led_table[HW_ERR_CODE_MAX];  /* 错误码 → 显示值映射 */

    Q32U_              error_code;            /* 当前错误码（0 = 正常）*/
    Q32U_              error_code_led_1;      /* 十位段闪烁次数 */
    Q32U_              error_code_led_2;      /* 个位段闪烁次数 */

    Q32U_              error_led_on_time;     /* 单次点亮时长 */
    Q32U_              error_led_off_time;    /* 闪烁间隔（灭）*/
    Q32U_              error_led_gap_1;       /* 十位→个位 长间隔 */
    Q32U_              error_led_gap_2;       /* 个位→循环 长间隔 */
} ST_ERROR_CONTROL;

/* ======================== 4. Globals ====================== */
extern ST_ERROR_CONTROL Error_Ctrl;

/* ======================== 5. Function Prototypes ========== */
Q32U_ Error_Priority_Check(Q32U_ error_all);

#endif /* SYS_ERR_H */
