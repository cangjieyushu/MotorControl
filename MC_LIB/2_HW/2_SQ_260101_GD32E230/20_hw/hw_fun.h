/**
 * @file    hw_fun.h
 * @brief   硬件功能开关与算法选型
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef HW_FUN_H
#define HW_FUN_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"

/* ======================== 2. Defines ====================== */

/* ---- 功能开关：1U = 使能，0U = 关闭 ---- */
#define HW_FUN_MC_ENABLE                    (1U)    /* 电机控制：ADC/PWM/CMP/OPA/DAC/TIM */
#define HW_FUN_BTN_ENABLE                   (0U)    /* 按键 / VR 控制 */
#define HW_FUN_ERR_ENABLE                   (1U)    /* 故障 LED 闪烁显示 */
#define HW_FUN_UART_ENABLE                  (1U)    /* 上位机串口：协议状态机 */
#define HW_FUN_LCD_ENABLE                   (0U)    /* UI 分区：LCD 驱动 + 字模 + 菜单 */

/* ---- 按键工作模式 ---- */
#define HW_FUN_BTN_MODE_DB                  (0U)    /* 双按键启动/停止 */
#define HW_FUN_BTN_MODE_VR                  (1U)    /* VR 启动/停止/调速 */
#define HW_FUN_BTN_MODE_DB_VR               (2U)    /* 双按键启停 + VR 调速 */
#define HW_FUN_BTN_MODE_NULL                (9U)    /* 无按键 */

#define HW_FUN_BTN_MODE                     HW_FUN_BTN_MODE_DB  /* 改这里切换模式 */

/* ---- 串口物理层类型 ---- */
#define HW_FUN_UART_PHY_RS485               (1U)    /* 485：需方向控制，发送完成必须等 USART TC */
#define HW_FUN_UART_PHY_TTL                 (0U)    /* TTL：无方向控制，DMA TC 即可结束 */

#define HW_FUN_UART_PHY                     HW_FUN_UART_PHY_RS485

/* ---- 电机编号 ---- */
#define HW_FUN_MC_MOTOR_NUMBER_N0           (00U)
#define HW_FUN_MC_MOTOR_NUMBER_N1           (01U)
#define HW_FUN_MC_MOTOR_NUMBER_N2           (02U)

/* ---- 控制算法选择 ---- */
#define HW_FUN_MC_MOTOR_CONTROL_FOC_F       (10U)
#define HW_FUN_MC_MOTOR_CONTROL_FOC_T       (11U)
#define HW_FUN_MC_MOTOR_CONTROL_SQ          (12U)
#define HW_FUN_MC_MOTOR_CONTROL_MODE        HW_FUN_MC_MOTOR_CONTROL_SQ

/* ---- FOC 设置：采样方式选择 ---- */
#define HW_FUN_MC_MOTOR_SHUNT_THREE         (20U)
#define HW_FUN_MC_MOTOR_SHUNT_ONE           (21U)
#define HW_FUN_MC_MOTOR_SHUNT_MODE          HW_FUN_MC_MOTOR_SHUNT_THREE

/* ---- FOC 设置：启动算法选择 ---- */
#define HW_FUN_MC_MOTOR_OPENLOOP_IF         (30U)
#define HW_FUN_MC_MOTOR_OPENLOOP_FLUX       (31U)
#define HW_FUN_MC_MOTOR_OPENLOOP_MODE       HW_FUN_MC_MOTOR_OPENLOOP_FLUX

/* ---- FOC 设置：观测器选择 ---- */
#define HW_FUN_MC_MOTOR_EST_SMO             (40U)
#define HW_FUN_MC_MOTOR_EST_FLUX            (41U)
#define HW_FUN_MC_MOTOR_EST_MODE            HW_FUN_MC_MOTOR_EST_SMO

/* ---- RTT使能 ---- */
#define HW_FUN_MC_RTT_ENABLE                (0U)

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

#endif /* HW_FUN_H */