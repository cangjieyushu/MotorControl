/*
*     File Name :                        bsp_sys
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统级外设汇总头文件
*/


#ifndef BSP_SYS_H
#define BSP_SYS_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "bsp_sys_clk.h"
#include "bsp_sys_gpio.h"
#include "bsp_sys_isr.h"
#include "bsp_sys_uart.h"
#include "bsp_sys_dma.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: BSP_SYS_Init
Description: 系统级外设初始化汇总
             包含：时钟、GPIO、NVIC、串口、串口DMA
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
*/
void BSP_SYS_Init(void);


#endif /* BSP_SYS_H */
