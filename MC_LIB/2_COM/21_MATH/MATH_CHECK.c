/**************************************************************************************************
*     File Name :                        MATH_CHECK.c
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             确认函数
**************************************************************************************************/

#include "MATH_CHECK.h"


/**********************************************************************************************
Function: Check_Init
Description: 计数器初始化
Input: 无
Output: 无
Input_Output: 检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Check_Init(ST_CHECK* pCheck)
{
    pCheck->_V_Q32U_Check_cnt = 0U;
}

/**********************************************************************************************
Function: Check_Cal
Description: 计数器检测
Input: 无
Output: 无
Input_Output: 检测指针，故障状态
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ Check_Cal(ST_CHECK* pCheck, Q32U_ Fault_State)
{
    Q32U_ Flag_Out_tmp = Fault_State;
    
    // 如果故障检测未使能，直接返回正常状态
    if(!pCheck->Check_Flag.bit.Enable)
    {
        pCheck->_V_Q32U_Check_cnt = 0U;
        return Flag_Out_tmp;
    }
 
    if(pCheck->Check_Flag.bit.Clear_Mode)
    {
        // 如果当前处于故障状态，检查清除条件
        if(Fault_State)
        {
            // 故障清除条件判断
            if(pCheck->Check_Flag.bit.Condition_Clear)
            {
                // 满足清除条件，增加故障检测计数器
                pCheck->_V_Q32U_Check_cnt += pCheck->_P_Q32U_Check_Count;
                if(pCheck->_V_Q32U_Check_cnt >= pCheck->_P_Q32U_Clear_Time*pCheck->_P_Q32U_Check_Count)
                {
                    Flag_Out_tmp = 0U;                  // 故障标志清楚
                    pCheck->_V_Q32U_Check_cnt = 0U;     // 复位清除计数器
                }
            }
            else
            {
                // 未超过阈值，重置故障检测计数器
                if(pCheck->_V_Q32U_Check_cnt > 0U)
                {
                    pCheck->_V_Q32U_Check_cnt--;// 复位清除计数器
                }
            }
        }
        else
        {
            // 故障触发条件判断
            if(pCheck->Check_Flag.bit.Condition_Set)
            {
                // 满足触发条件，增加故障检测计数器
                pCheck->_V_Q32U_Check_cnt += pCheck->_P_Q32U_Check_Count;
                if(pCheck->_V_Q32U_Check_cnt >= pCheck->_P_Q32U_Check_Time*pCheck->_P_Q32U_Check_Count)
                {
                    Flag_Out_tmp = 1U;                  // 故障标志置位
                    pCheck->_V_Q32U_Check_cnt = 0U;     // 复位清除计数器
                }
            }
            else
            {
                // 未超过阈值，重置故障检测计数器
                if(pCheck->_V_Q32U_Check_cnt > 0U)
                {
                    pCheck->_V_Q32U_Check_cnt--;// 复位清除计数器
                }
            }
        }
    }
    else
    {
        // 如果当前处于故障状态，检查清除条件
        if(Fault_State)
        {
            // 故障清除条件判断
            if(pCheck->Check_Flag.bit.Condition_Clear)
            {
                // 满足清除条件，增加故障检测计数器
                pCheck->_V_Q32U_Check_cnt++;
                if(pCheck->_V_Q32U_Check_cnt >= pCheck->_P_Q32U_Clear_Time)
                {
                    Flag_Out_tmp = 0U;                  // 故障标志清楚
                    pCheck->_V_Q32U_Check_cnt = 0U;     // 复位清除计数器
                }
            }
            else
            {
                // 未超过阈值，重置故障检测计数器
                pCheck->_V_Q32U_Check_cnt = 0U;
            }
        }
        else
        {
            // 故障触发条件判断
            if(pCheck->Check_Flag.bit.Condition_Set)
            {
                // 满足触发条件，增加故障检测计数器
                pCheck->_V_Q32U_Check_cnt++;
                if(pCheck->_V_Q32U_Check_cnt >= pCheck->_P_Q32U_Check_Time)
                {
                    Flag_Out_tmp = 1U;                  // 故障标志置位
                    pCheck->_V_Q32U_Check_cnt = 0U;     // 复位清除计数器
                }
            }
            else
            {
                // 未超过阈值，重置故障检测计数器
                pCheck->_V_Q32U_Check_cnt = 0U;
            }
        }
    }
    
    return Flag_Out_tmp;
}
