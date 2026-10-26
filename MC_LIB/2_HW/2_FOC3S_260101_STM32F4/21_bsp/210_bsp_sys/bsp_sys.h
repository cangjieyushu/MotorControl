/**
 * @file    bsp_sys.h
 * @brief   系统级外设汇总头文件
 *          - 聚合时钟、GPIO、NVIC、串口、串口 DMA 初始化
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef BSP_SYS_H
#define BSP_SYS_H

/* ======================== 1. Includes ===================== */
#include "bsp_sys_clk.h"
#include "bsp_sys_gpio.h"
#include "bsp_sys_isr.h"
#include "bsp_sys_uart.h"
#include "bsp_sys_dma.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */
void BSP_SYS_Init(void);

#endif /* BSP_SYS_H */
