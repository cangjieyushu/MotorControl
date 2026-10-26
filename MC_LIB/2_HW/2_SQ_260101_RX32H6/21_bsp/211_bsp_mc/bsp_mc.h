/**
 * @file    bsp_mc.h
 * @brief   电机控制外设汇总头文件
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef BSP_MC_H
#define BSP_MC_H

/* ======================== 1. Includes ===================== */
#include "hw_fun.h"
#include "bsp_mc_gpio.h"
#include "bsp_mc_adc.h"
#include "bsp_mc_dma.h"
#include "bsp_mc_pwm.h"
#include "bsp_mc_tim.h"
#include "bsp_mc_cmp.h"
#include "bsp_mc_dac.h"
#include "bsp_mc_opamp.h"
#include "SEGGER_RTT.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */
#if (HW_FUN_MC_RTT_ENABLE == 1U)
extern int  JS_RTT_Channel;        // J-Scope RTT Channel
extern Q16I_ JS_RTT_Data[4];           // J-Scope RTT Buffer
#endif

/* ======================== 5. Function Prototypes ========== */
void BSP_MC_Init(void);

#endif /* BSP_MC_H */
