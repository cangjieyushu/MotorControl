/**
 * @file    mcsq_task.h
 * @brief   方波电机任务接口
 * @author  CJYS
 * @date    2024/1/1
 *
 * 提供 1ms 任务、电流中断、换向中断、ADC 触发接口。
 */

#ifndef MCSQ_TASK_H
#define MCSQ_TASK_H

/* ======================== 1. Includes ===================== */
#include "pmsm_para.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  方波 1ms 任务（状态机 / 保护 / 速度/电流环）
 * @param  motor_num  电机编号
 */
void MCSQ_Speed_Flow(Q32U_ motor_num);

/**
 * @brief  方波电流中断任务（ADC 采样 / 状态机单步执行）
 * @param  motor_num  电机编号
 */
void MCSQ_Current_Flow(Q32U_ motor_num);

/**
 * @brief  方波换向中断任务（换向状态推进）
 * @param  motor_num  电机编号
 */
void MCSQ_Switch_Flow(Q32U_ motor_num);

/**
 * @brief  方波 ADC 触发
 * @param  motor_num  电机编号
 */
void MCSQ_ADC_Trig_Flow(Q32U_ motor_num);

#endif /* MCSQ_TASK_H */
