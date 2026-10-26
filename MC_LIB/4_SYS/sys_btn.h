/**
 * @file    sys_btn.h
 * @brief   按键 / VR 控制
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef SYS_BTN_H
#define SYS_BTN_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_para.h"
#include "bsp.h"

/* ======================== 2. Defines ====================== */
/* ---- VR 阈值（Q14 定点数）---- */
#define VR_START_TL                 ((Q32U_)(100.0f))    /* VR 启动阈值 */
#define VR_STOP_TL                  ((Q32U_)(50.0f))     /* VR 停止阈值 */

#define VR_MAX_LIMIT                ((Q32U_)(3800.0f))   /* VR 最大阈值 */
#define VR_MIN_LIMIT                ((Q32U_)(200.0f))    /* VR 最小阈值 */

#define VR_MAX_DUTY                 (Q14U_MAX_T)         /* VR 最大占空比 */

/* ======================== 3. Typedefs ===================== */
typedef struct{
    /* ---- VR 参数（Q14 定点数）---- */
    Q32U_  vr_start_tl;         /* VR 启动阈值 */
    Q32U_  vr_stop_tl;          /* VR 停止阈值 */

    Q32U_  vr_max_limit;        /* VR 最大阈值 */
    Q32U_  vr_min_limit;        /* VR 最小阈值 */

    Q32U_  vr_duty_max;         /* VR 最大占空比 */

    /* ---- 按键状态 ---- */
    Q32U_  button0_state;       /* 按键 0 当前状态 */
    Q32U_  button0_state_last;  /* 按键 0 上次状态（边沿检测用）*/
    Q32U_  button1_state;       /* 按键 1 当前状态 */
    Q32U_  button1_state_last;  /* 按键 1 上次状态 */
    Q32U_  button2_state;       /* 按键 2 当前状态 */
    Q32U_  button2_state_last;  /* 按键 2 上次状态 */
} ST_BUTTON_CONTROL;

/* ======================== 4. Globals ====================== */
extern ST_BUTTON_CONTROL Button_Ctrl;

/* ======================== 5. Function Prototypes ========== */
void Button_Control(ST_BUTTON_CONTROL* pButton);

#endif /* SYS_BTN_H */
