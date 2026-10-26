/**
 * @file    bsp_mc_pwm.h
 * @brief   PWM 初始化
 *          - 中心对齐互补 PWM，OC4REF 触发 ADC
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef BSP_MC_PWM_H
#define BSP_MC_PWM_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_para.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */
void BSP_MC_PWM_Init(void);

#endif /* BSP_MC_PWM_H */
