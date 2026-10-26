/**
 * @file    mc_api.h
 * @brief   电机控制对外 API 接口
 * @author  CJYS
 * @date    2024/1/1
 *
 * 提供电机启停、方向、转速设定/读取、状态/故障查询接口。
 * 内部按编译配置（FOC_F / FOC_T / SQ）选择具体任务结构体。
 */

#ifndef MC_API_H
#define MC_API_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"
#include "pmsm_para.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  电机启停控制
 * @param  motor_num  电机编号
 * @param  Enable     1 = 使能，0 = 停止
 */
void MC_API_Motor_StartStop(Q32U_ motor_num, Q32U_ Enable);

/**
 * @brief  读取电机运行状态
 * @param  motor_num  电机编号
 * @return 1 = 运行中，0 = 停止
 */
Q32U_ MC_API_Motor_Read_State(Q32U_ motor_num);

/**
 * @brief  设置目标方向
 * @param  motor_num  电机编号
 * @param  Dir        1 = 正转，0 = 反转
 */
void MC_API_Motor_Set_Dir(Q32U_ motor_num, Q32U_ Dir);

/**
 * @brief  读取实际方向
 * @param  motor_num  电机编号
 * @return 1 = 正转，0 = 反转
 */
Q32I_ MC_API_Motor_Read_Dir(Q32U_ motor_num);

/**
 * @brief  设置目标转速（额定范围内的百分比指令）
 * @param  motor_num  电机编号
 * @param  Speed      目标转速指令
 */
void MC_API_Motor_Set_Speed(Q32U_ motor_num, Q32U_ Speed);

/**
 * @brief  读取实际转速
 * @param  motor_num  电机编号
 * @return 实际转速（rpm）
 */
Q32U_ MC_API_Motor_Read_Speed(Q32U_ motor_num);

/**
 * @brief  读取相电流有效值
 * @param  motor_num  电机编号
 * @return 相电流（0.01A）
 */
Q32U_ MC_API_Motor_Read_Iphase(Q32U_ motor_num);

/**
 * @brief  读取母线电流
 * @param  motor_num  电机编号
 * @return 母线电流（0.01A）
 */
Q32U_ MC_API_Motor_Read_Ibus(Q32U_ motor_num);

/**
 * @brief  读取故障标志整体
 * @param  motor_num  电机编号
 * @return 故障位图
 */
Q32U_ MC_API_Motor_Read_Err(Q32U_ motor_num);

/**
 * @brief  清除可复位故障
 * @param  motor_num  电机编号
 */
void MC_API_Motor_Clear_Err(Q32U_ motor_num);

#endif /* MC_API_H */
