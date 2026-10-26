/**
 * @file    bsp_sys_gpio.h
 * @brief   系统 GPIO 初始化（按键/LED/测试点/RS485_EN）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef BSP_SYS_GPIO_H
#define BSP_SYS_GPIO_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_para.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */
void BSP_SYS_GPIO_Init(void);

Q08U_ BSP_SYS_GPIO_Read_START_State(void);
Q08U_ BSP_SYS_GPIO_Read_STOP_State(void);

Q08U_ BSP_SYS_GPIO_Read_Key_UP(void);
Q08U_ BSP_SYS_GPIO_Read_Key_DOWN(void);
Q08U_ BSP_SYS_GPIO_Read_Key_MENU(void);
Q08U_ BSP_SYS_GPIO_Read_Key_OK(void);

/* LED 控制 */
void BSP_SYS_GPIO_LED1_Set(void);
void BSP_SYS_GPIO_LED1_Clr(void);

void BSP_SYS_GPIO_LED2_Set(void);
void BSP_SYS_GPIO_LED2_Clr(void);

void BSP_SYS_GPIO_RED_Set(void);
void BSP_SYS_GPIO_RED_Clr(void);

void BSP_SYS_GPIO_YEW_Set(void);
void BSP_SYS_GPIO_YEW_Clr(void);

void BSP_SYS_GPIO_GRE_Set(void);
void BSP_SYS_GPIO_GRE_Clr(void);

/* 测试点 */
void BSP_SYS_GPIO_TEST1_Set(void);
void BSP_SYS_GPIO_TEST1_Clr(void);

void BSP_SYS_GPIO_TEST2_Set(void);
void BSP_SYS_GPIO_TEST2_Clr(void);

/* RS485 方向控制（1 = 发送；0 = 接收） */
void BSP_SYS_GPIO_TXEN(Q32U_ state);

#endif /* BSP_SYS_GPIO_H */
