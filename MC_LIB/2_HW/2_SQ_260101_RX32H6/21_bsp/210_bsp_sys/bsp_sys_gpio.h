/*
*     File Name :                        bsp_sys_gpio
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统 GPIO 初始化（按键/LED/测试点/RS485_EN）
*/


#ifndef BSP_SYS_GPIO_H
#define BSP_SYS_GPIO_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: BSP_SYS_GPIO_Init
Description: 系统 GPIO 初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
void BSP_SYS_GPIO_Init(void);

/*
Function: BSP_SYS_GPIO_Read_START_State
Description: START 按键状态读取
Return: 0 - 按下；1 - 松开
*/
Q08U_ BSP_SYS_GPIO_Read_START_State(void);

/*
Function: BSP_SYS_GPIO_Read_STOP_State
Description: STOP 按键状态读取
Return: 0 - 按下；1 - 松开
*/
Q08U_ BSP_SYS_GPIO_Read_STOP_State(void);

Q08U_ BSP_SYS_GPIO_Read_Key_UP(void);
Q08U_ BSP_SYS_GPIO_Read_Key_DOWN(void);
Q08U_ BSP_SYS_GPIO_Read_Key_MENU(void);
Q08U_ BSP_SYS_GPIO_Read_Key_OK(void);

/* LED 控制 */
void BSP_SYS_GPIO_RED_Set(void);
void BSP_SYS_GPIO_RED_Clr(void);
void BSP_SYS_GPIO_RED_Toggle(void);

void BSP_SYS_GPIO_YEW_Set(void);
void BSP_SYS_GPIO_YEW_Clr(void);
void BSP_SYS_GPIO_YEW_Toggle(void);

void BSP_SYS_GPIO_GRE_Set(void);
void BSP_SYS_GPIO_GRE_Clr(void);
void BSP_SYS_GPIO_GRE_Toggle(void);

/* 测试点 */
void BSP_SYS_GPIO_TEST1_Set(void);
void BSP_SYS_GPIO_TEST1_Clr(void);
void BSP_SYS_GPIO_TEST1_Toggle(void);

void BSP_SYS_GPIO_TEST2_Set(void);
void BSP_SYS_GPIO_TEST2_Clr(void);
void BSP_SYS_GPIO_TEST2_Toggle(void);

/*
Function: BSP_SYS_GPIO_TXEN
Description: RS485 方向控制（1 = 发送；0 = 接收）
Input: state - 1 发送 / 0 接收
Return: 无
*/
void BSP_SYS_GPIO_TXEN(Q32U_ state);


#endif /* BSP_SYS_GPIO_H */
