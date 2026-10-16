/*
*     File Name :                        hw_fun
*     Library/Module Name :              hw
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             硬件参数
*/


#ifndef HW_FUN_H
#define HW_FUN_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/

/* 功能开关 */
#define SYS_CFG_MC_ENABLE                   (1U)    /* 电机控制：ADC/PWM/CMP/OPA/DAC/TIM */
#define SYS_CFG_LCD_ENABLE                  (1U)    /* ★ UI 分区：LCD 驱动 + 字模 + 菜单 */
#define SYS_CFG_UART_ENABLE                 (1U)    /* 上位机串口：协议状态机 */
#define SYS_CFG_BTN_ENABLE                  (1U)    /* 按键 / VR 控制 */
#define SYS_CFG_ERR_ENABLE                  (1U)    /* 故障 LED 闪烁显示 */



/* ==================== 主从机通讯设置 ==================== */
/* ---- 本机角色 ---- */
#define SYS_PROTO_ROLE_SLAVE                (0U)    /* 从机：被询问才应答 */
#define SYS_PROTO_ROLE_MASTER               (1U)    /* 主机：主动轮询、汇总上报上位机 */

#define SYS_PROTO_ROLE                      SYS_PROTO_ROLE_SLAVE   /* ★ 改这里切换主/从机 */

/* ---- 本机地址（485 总线内唯一，1~247；0x00 保留给广播）---- */
#define SYS_PROTO_SLAVE_ADDR                (0x01U)  /* 从机自身地址 */
#define SYS_PROTO_MASTER_ADDR               (0xF0U)  /* 主机自身地址（上位机就认这个） */

/* ---- 主机轮询参数（SYS_PROTO_ROLE == MASTER 时生效）---- */
#define SYS_PROTO_SLAVE_NUM                 (1U)     /* 轮询的从机数量，1~8 */
#define SYS_PROTO_POLL_PERIOD_MS            (100U)   /* 轮询周期 */
#define SYS_PROTO_REPLY_TIMEOUT_MS          (500U)   /* 等待从机应答超时 */

/* ---- 从机是否允许主动上报（多机共总线建议 0，避免碰撞）---- */
#define SYS_PROTO_SLAVE_AUTO_REPORT         (0U)     /* 0：只应答；1：也周期上报 */

/* ---- 总线类型：0 = RS485 半双工（自动切方向）；1 = 全双工 TTL ---- */
#define SYS_PROTO_RS485_ENABLE              (0U)     /* 带屏机与电机板直连 TTL 时填 1 */



/* ---- 按键工作模式 ---- */
#define BUTTON_MODE_BUTTON                  (0U)    /* 按键启动/停止 */
#define BUTTON_MODE_VR                      (1U)    /* VR 启动/停止/调速 */
#define BUTTON_MODE_BUTTON_VR               (2U)    /* 按键启停 + VR 调速 */
#define BUTTON_MODE_NULL                    (9U)    /* 无按键 */

#define BUTTON_MODE                         BUTTON_MODE_BUTTON  /* ★ 改这里切换模式 */



//电机编号
#define HW_MC_MOTOR_NUMBER_N0               (00U)
#define HW_MC_MOTOR_NUMBER_N1               (01U)
#define HW_MC_MOTOR_NUMBER_N2               (02U)

//控制算法选择
#define HW_MC_MOTOR_CONTROL_FOC_F           (10U)
#define HW_MC_MOTOR_CONTROL_FOC_T           (11U)
#define HW_MC_MOTOR_CONTROL_SQ              (12U)
#define HW_MC_MOTOR_CONTROL_MODE            HW_MC_MOTOR_CONTROL_FOC_F

//FOC设置
//采样方式选择
#define HW_MC_MOTOR_SHUNT_THREE             (20U)
#define HW_MC_MOTOR_SHUNT_ONE               (21U)
#define HW_MC_MOTOR_SHUNT_MODE              HW_MC_MOTOR_SHUNT_THREE

//启动算法选择
#define HW_MC_MOTOR_OPENLOOP_IF             (30U)
#define HW_MC_MOTOR_OPENLOOP_FLUX           (31U)
#define HW_MC_MOTOR_OPENLOOP_MODE           HW_MC_MOTOR_OPENLOOP_IF

//观测器选择
#define HW_MC_MOTOR_EST_SMO                 (40U)
#define HW_MC_MOTOR_EST_FLUX                (41U)
#define HW_MC_MOTOR_EST_MODE                HW_MC_MOTOR_EST_FLUX


#endif /* HW_FUN_H */
