/**************************************************************************************************
*     File Name :                        hal_uart
*     Library/Module Name :              hal_uart
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统串口 HAL 层头文件
*                                        引脚 / 收发使能 / DMA 收发 / 环形缓冲区
*                                        全部 static inline，无 .c 文件
**************************************************************************************************/
#ifndef HAL_UART_H
#define HAL_UART_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_para.h"
#include "bsp_sys.h"
#include "bsp_sys_dma.h"        /* ★ 提供数据缓冲区 + 环形缓冲区 extern 声明 */
#include <string.h>


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/
/* 注：g_uart_tx_buf / g_uart_rx_buf / g_ring_* 的 extern 已在 bsp_sys_dma.h 中声明 */


/*-------------------------- 5. UART 收发使能 ---------------------------*/
/*
Function: UARTH_Enable_Rx
Description: UART 打开接收
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UARTH_Enable_Rx(void)
{
    
}

/*
Function: UARTH_Disable_Rx
Description: UART 关闭接收
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UARTH_Disable_Rx(void)
{
    
}

/*
Function: UARTH_Enable_Tx
Description: UART 打开发送（同时切换到 RS485 发送方向）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UARTH_Enable_Tx(void)
{
    
}

/*
Function: UARTH_Disable_Tx
Description: UART 关闭发送（同时切回 RS485 接收方向）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UARTH_Disable_Tx(void)
{
    
}


/*-------------------------- 6. UART 的 DMA 收发 ------------------------*/
/*
Function: UARTH_Tx_DMA_Flag
Description: 读取 UART 的 DMA 发送完成标志（TC）
Return: 0 - 未完成；非 0 - 已完成
Author: CJYS
*/
static inline Q32U_ UARTH_Tx_DMA_Flag(void)
{
    return 1U;
}

/*
Function: UARTH_Tx_DMA_Start
Description: 启动 UART 的 DMA 发送
Input: txbuffer - 待发送数据指针；len - 长度
Return: 无
Author: CJYS
*/
static inline void UARTH_Tx_DMA_Start(Q08U_* txbuffer, Q32U_ len)
{
    
}

/*
Function: UARTH_Tx_DMA_Stop
Description: 停止 UART 的 DMA 发送
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UARTH_Tx_DMA_Stop(void)
{
    
}

/*
Function: UARTH_Rx_DMA_Flag
Description: 读取 UART 的 DMA 接收完成标志
Return: 0 - 未完成；非 0 - 已完成
Author: CJYS
*/
static inline Q32U_ UARTH_Rx_DMA_Flag(void)
{
    return 1U;
}

/*
Function: UARTH_Rx_DMA_Start
Description: 启动 UART 的 DMA 接收
Input: rxbuffer - 接收缓冲区指针；len - 期望接收长度
Return: 无
Author: CJYS
*/
static inline void UARTH_Rx_DMA_Start(Q08U_* rxbuffer, Q32U_ len)
{
    
}

/*
Function: UARTH_Rx_DMA_Stop
Description: 停止 UART 的 DMA 接收
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UARTH_Rx_DMA_Stop(void)
{
    
}

/*
Function: UARTH_Rx_DMA_RemainCount
Description: 读取 UART 的 DMA 接收剩余数据数（用于 IDLE 帧长度计算）
Return: 剩余未接收的字节数
Author: CJYS
*/
static inline Q32U_ UARTH_Rx_DMA_RemainCount(void)
{
    return 1U;
}


/*-------------------------- 7. DMA 通用发送接口 -----------------------*/
/*
Function: uart_send_data
Description: 通过 DMA 发送指定长度的数据
Input: data - 数据指针；len - 长度
Output: 无
Return: 无
Author: CJYS
*/
static inline void uart_send_data(uint8_t *data, uint16_t len)
{
    
}

/*
Function: uart_send_string
Description: 发送以 '\0' 结尾的字符串
Input: str - 字符串指针
Output: 无
Return: 无
Author: CJYS
*/
static inline void uart_send_string(const char *str)
{
}

/*
Function: UART_DMA_Tx_Poll
Description: 发送轮询（放在 10ms 任务里调用）
             检测到"待发送"且上一帧已发完（TC 置位）时，启动 DMA 并切 485 方向
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UART_DMA_Tx_Poll(void)
{
}


/*-------------------------- 8. 环形缓冲区 ------------------------------*/
/*
Function: ring_buffer_init
Description: 环形缓冲区初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void ring_buffer_init(void)
{
    
}

/*
Function: ring_buffer_available
Description: 返回缓冲区中可读字节数
Return: 可读字节数
Author: CJYS
*/
static inline uint16_t ring_buffer_available(void)
{
    return 1U;
}

/*
Function: ring_buffer_get
Description: 从缓冲区读取一个字节
Return: 0~255 - 读到的字节；-1 - 缓冲区为空
Author: CJYS
*/
static inline int ring_buffer_get(void)
{
    return 1U;
}

/*
Function: ring_buffer_put
Description: 向缓冲区写入一个字节
Input: data - 待写入字节
Return: 0 - 缓冲区满，丢弃；1 - 成功
Author: CJYS
*/
static inline Q08U_ ring_buffer_put(uint8_t data)
{
    return 1U;
}

/*
Function: ring_buffer_clear
Description: 环形缓冲区清空
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void ring_buffer_clear(void)
{
    
}


/*-------------------------- 9. DMA 接收处理 ---------------------------*/
/*
Function: UART_DMA_Rx_Int
Description: UART 的 DMA 接收处理（在 USART1 IDLE 中断里调用）
             把 DMA 线性缓冲区中的新数据搬到环形缓冲区
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static inline void UART_DMA_Rx_Int(void)
{
    
}


#endif /* HAL_UART_H */
