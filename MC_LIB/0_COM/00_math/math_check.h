/**
 * @file    math_check.h
 * @brief   故障时间确认（时间滤波）接口
 * @author  CJYS
 * @date    2024/1/1
 *
 * 提供带时间确认的故障置位/清除逻辑。Clear_Mode 选择计数器在条件
 * 不满足时的行为：0 = 立即清零；1 = 递减回退。
 */

#ifndef MATH_CHECK_H
#define MATH_CHECK_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 故障确认标志位联合体
 */
typedef union
{
    SC_ALL all;                          /**< 整体访问 */
    struct
    {
        SC_BIT Enable              :1;   /**< 1 使能 / 0 旁路 */
        SC_BIT Condition_Set       :1;   /**< 1 满足置位条件 */
        SC_BIT Condition_Clear     :1;   /**< 1 满足清除条件 */
        SC_BIT Clear_Mode          :1;   /**< 0 清零模式 / 1 递减模式 */
    } bit;
} UN_CHECK_FLAG;

/**
 * @brief 故障确认运行状态与参数
 */
typedef struct
{
    UN_CHECK_FLAG Check_Flag;         /**< 使能与条件标志 */
    Q32U_         V_Q32U_Check_cnt;   /**< 内部累加计数 */

    float         P_F_Check_TL;       /**< 置位阈值（浮点辅助量） */
    Q32U_         P_Q14I_Check_TL;    /**< 置位阈值（Q14 辅助量） */
    Q32U_         P_Q32U_Check_Time;  /**< 置位确认时间（帧数） */

    float         P_F_Clear_TL;       /**< 清除阈值（浮点辅助量） */
    Q32U_         P_Q14I_Clear_TL;    /**< 清除阈值（Q14 辅助量） */
    Q32U_         P_Q32U_Clear_Time;  /**< 清除确认时间（帧数） */

    Q32U_         P_Q32U_Check_Count; /**< 每帧累加步长 */
} ST_CHECK;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  初始化确认结构体
 * @param  pCheck  待初始化结构体指针
 */
__attribute__CCMRAM
void Check_Init(ST_CHECK* pCheck);

/**
 * @brief  执行一帧确认逻辑
 * @param  pCheck       确认结构体指针
 * @param  Fault_State  原始故障状态（0 正常 / 非 0 故障）
 * @return 确认后的故障状态
 */
__attribute__CCMRAM
Q32U_ Check_Cal(ST_CHECK* pCheck, Q32U_ Fault_State);

#endif /* MATH_CHECK_H */
