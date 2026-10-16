/*
*     File Name :                        bsp_sys
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统级外设汇总初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_sys.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_SYS_Init
Description: 系统级外设初始化汇总
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_SYS_Init(void)
{
    BSP_SYS_CLK_Init();         /* 系统时钟 + SysTick */
    BSP_SYS_GPIO_Init();        /* 按键/LED/测试点/RS485 EN */
    BSP_SYS_ISR_Init();         /* NVIC 优先级 */

    BSP_SYS_DMA_UART_Init();    /* 串口 DMA 先配置 */
    BSP_SYS_UART_Init();        /* 再使能 USART（避免 IDLE 中断早于 DMA 就绪）*/
}
