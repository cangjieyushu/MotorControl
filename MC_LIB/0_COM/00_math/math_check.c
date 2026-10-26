/**
 * @file    math_check.c
 * @brief   故障时间确认（时间滤波）实现
 * @author  CJYS
 * @date    2024/1/1
 *
 * 单出口实现：仅通过 Flag_Out_tmp 返回确认结果，
 * 内部状态机依据 Clear_Mode 分别处理置位/清除确认。
 */

/* ======================== 1. Header ======================= */
#include "math_check.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  初始化确认结构体
 * @param  pCheck  待初始化结构体指针
 */
void Check_Init(ST_CHECK* pCheck)
{
    pCheck->V_Q32U_Check_cnt = 0U;
}

/**
 * @brief  执行一帧确认逻辑
 * @param  pCheck       确认结构体指针
 * @param  Fault_State  原始故障状态（0 正常 / 非 0 故障）
 * @return 确认后的故障状态
 */
Q32U_ Check_Cal(ST_CHECK* pCheck, Q32U_ Fault_State)
{
    Q32U_ Flag_Out_tmp = Fault_State;

    if (pCheck->Check_Flag.bit.Enable)
    {
        if (pCheck->Check_Flag.bit.Clear_Mode)
        {
            if (Fault_State)
            {
                if (pCheck->Check_Flag.bit.Condition_Clear)
                {
                    pCheck->V_Q32U_Check_cnt += pCheck->P_Q32U_Check_Count;
                    if (pCheck->V_Q32U_Check_cnt >= (pCheck->P_Q32U_Clear_Time * pCheck->P_Q32U_Check_Count))
                    {
                        Flag_Out_tmp = 0U;
                        pCheck->V_Q32U_Check_cnt = 0U;
                    }
                }
                else
                {
                    if (pCheck->V_Q32U_Check_cnt > 0U)
                    {
                        pCheck->V_Q32U_Check_cnt--;
                    }
                }
            }
            else
            {
                if (pCheck->Check_Flag.bit.Condition_Set)
                {
                    pCheck->V_Q32U_Check_cnt += pCheck->P_Q32U_Check_Count;
                    if (pCheck->V_Q32U_Check_cnt >= (pCheck->P_Q32U_Check_Time * pCheck->P_Q32U_Check_Count))
                    {
                        Flag_Out_tmp = 1U;
                        pCheck->V_Q32U_Check_cnt = 0U;
                    }
                }
                else
                {
                    if (pCheck->V_Q32U_Check_cnt > 0U)
                    {
                        pCheck->V_Q32U_Check_cnt--;
                    }
                }
            }
        }
        else
        {
            if (Fault_State)
            {
                if (pCheck->Check_Flag.bit.Condition_Clear)
                {
                    pCheck->V_Q32U_Check_cnt++;
                    if (pCheck->V_Q32U_Check_cnt >= pCheck->P_Q32U_Clear_Time)
                    {
                        Flag_Out_tmp = 0U;
                        pCheck->V_Q32U_Check_cnt = 0U;
                    }
                }
                else
                {
                    pCheck->V_Q32U_Check_cnt = 0U;
                }
            }
            else
            {
                if (pCheck->Check_Flag.bit.Condition_Set)
                {
                    pCheck->V_Q32U_Check_cnt++;
                    if (pCheck->V_Q32U_Check_cnt >= pCheck->P_Q32U_Check_Time)
                    {
                        Flag_Out_tmp = 1U;
                        pCheck->V_Q32U_Check_cnt = 0U;
                    }
                }
                else
                {
                    pCheck->V_Q32U_Check_cnt = 0U;
                }
            }
        }
    }
    else
    {
        pCheck->V_Q32U_Check_cnt = 0U;
    }

    return Flag_Out_tmp;
}
