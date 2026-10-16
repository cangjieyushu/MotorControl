#ifndef BSP_SYS_UART_H
#define BSP_SYS_UART_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
/* 数据寄存器访问 */
#define UART_TRANSMISSION_DATA      ((uint32_t)&USART_TDATA(USART0))
#define UART_RECEIVE_DATA           ((uint32_t)&USART_RDATA(USART0))

/* 通讯参数 */
#define BSP_SYS_UART_BAUD           (9600U)     /* bps，上位机通讯波特率 */


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
void BSP_SYS_UART_Init(void);

#endif /* BSP_SYS_UART_H */
