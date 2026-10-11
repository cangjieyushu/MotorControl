/*
*     File Name :                        bsp_gpio
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             GPIO初始化
*/


#ifndef BSP_GPIO_H
#define BSP_GPIO_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_clk.h"
#include "hw_map.h"
#include "hw_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/* 初始化 */
void BSP_GPIO_Init(void);

/* 按键读取（返回 0 = 按下，1 = 松开）*/
Q32U_ BSP_GPIO_Read_START_State(void);
Q32U_ BSP_GPIO_Read_STOP_State(void);

/* LED 控制 */
void BSP_GPIO_RED_Set(void);
void BSP_GPIO_RED_Clr(void);
void BSP_GPIO_RED_Toggle(void);

void BSP_GPIO_YEW_Set(void);
void BSP_GPIO_YEW_Clr(void);
void BSP_GPIO_YEW_Toggle(void);

void BSP_GPIO_GRE_Set(void);
void BSP_GPIO_GRE_Clr(void);
void BSP_GPIO_GRE_Toggle(void);

/* 测试点 */
void BSP_GPIO_TEST1_Set(void);
void BSP_GPIO_TEST1_Clr(void);
void BSP_GPIO_TEST1_Toggle(void);

void BSP_GPIO_TEST2_Set(void);
void BSP_GPIO_TEST2_Clr(void);
void BSP_GPIO_TEST2_Toggle(void);

/*
Function: BSP_GPIO_TXEN
Description: RS485 方向控制（1 = 发送；0 = 接收）
Input: state - 1 发送 / 0 接收
Output: 无
Return: 无
Author: CJYS
*/
void BSP_GPIO_TXEN(Q32U_ state);

#endif /* BSP_GPIO_H */
