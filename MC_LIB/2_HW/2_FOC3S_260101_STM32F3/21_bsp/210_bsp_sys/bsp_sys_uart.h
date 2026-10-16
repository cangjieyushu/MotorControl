/*
*     File Name :                        bsp_sys_uart
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             上位机通讯串口初始化
*/


#ifndef BSP_SYS_UART_H
#define BSP_SYS_UART_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
/* 数据寄存器访问 */
#define UART_TRANSMISSION_DATA     (HW_SYS_UART->TDR)
#define UART_RECEIVE_DATA          (HW_SYS_UART->RDR)

/* 缓冲区大小 */
#define UART_TX_BUF_SIZE           (256U)      /* 发送缓冲区大小 */
#define UART_RX_BUF_SIZE           (256U)      /* 接收环形缓冲区大小 */


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: BSP_SYS_UART_Init
Description: USART 参数配置（引脚 + 外设 + IDLE 中断）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_SYS_UART_Init(void);


#endif /* BSP_SYS_UART_H */
