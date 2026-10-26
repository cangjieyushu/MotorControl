/**
 * @file    sys_menu.h
 * @brief   菜单模块对外接口头文件
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef SYS_MENU_H
#define SYS_MENU_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_para.h"
#include "bsp.h"

/* ======================== 2. Defines ====================== */
/* 菜单模块对外没有宏定义 */

/* ======================== 3. Typedefs ===================== */
/* 菜单模块内部状态结构体 ST_MENU_STATE 在 sys_menu.c 中声明，不对外暴露 */

/* ======================== 4. Globals ====================== */
/* 无：菜单模块内部状态全部为文件私有（static），外部通过接口函数访问 */

/* ======================== 5. Function Prototypes ========== */
void Menu_Init(void);

void Menu_Loop_10ms(void);

#endif /* SYS_MENU_H */
