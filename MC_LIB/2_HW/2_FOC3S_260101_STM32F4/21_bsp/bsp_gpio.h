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
/*
Function: BSP_GPIO_Init
Description: GPIO初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
void BSP_GPIO_Init(void);

/*
Function: BSP_GPIO_Read_SW0_State
Description: 按键0状态读取
Input: 无
Output: 无
Input_Output: 无
Return: 按键0状态
Author: CJYS
*/
Q32U_ BSP_GPIO_Read_SW0_State(void);

/*
Function: BSP_GPIO_Read_SW1_State
Description: 按键1状态读取
Input: 无
Output: 无
Input_Output: 无
Return: 按键1状态
Author: CJYS
*/
Q32U_ BSP_GPIO_Read_SW1_State(void);

/*
Function: BSP_GPIO_Read_SW2_State
Description: 按键2状态读取
Input: 无
Output: 无
Input_Output: 无
Return: 按键2状态
Author: CJYS
*/
Q32U_ BSP_GPIO_Read_SW2_State(void);

void BSP_GPIO_Recover_Set_State(void);
void BSP_GPIO_Recover_Clear_State(void);


#endif /* BSP_GPIO_H */
