/**
 * @file    mcfoc_task_f.h
 * @brief   FOC 电机子任务接口（浮点）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef MCFOC_TASK_F_H
#define MCFOC_TASK_F_H

/* ======================== 1. Includes ===================== */
#include "pmsm_para.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  FOC 速度环任务（1ms 调用）
 * @param  motor_num  电机编号
 */
void MCFOC_Speed_Flow_F(Q32U_ motor_num);

/**
 * @brief  FOC 电流中断任务（PWM 周期调用）
 * @param  motor_num  电机编号
 */
__attribute__CCMRAM
void MCFOC_Current_Flow_F(Q32U_ motor_num);

#endif /* MCFOC_TASK_F_H */
