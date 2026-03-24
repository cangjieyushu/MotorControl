/**************************************************************************************************
*     File Name :                        MC_ERR.c
*     Library/Module Name :              MC
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机子任务源文件
**************************************************************************************************/

#include "MC_ERR.h"


/**********************************************************************************************
Function: MC_Error_Speed_Flow
Description: 电机故障检测速度环
Input: 无
Output: 无
Input_Output: 电机故障检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MC_Error_Speed_Flow(ST_MOTOR_ERROR* pERR, Q32U_ Q32U_Enable)
{
    pERR->Over_Voltage.Check_Flag.bit.Enable = 1U;
    pERR->Over_Voltage.Check_Flag.bit.Condition_Set =
        (pERR->_I_Q14U_Vbus_pu >= pERR->Over_Voltage._P_Q14I_Check_TL);
    pERR->Over_Voltage.Check_Flag.bit.Condition_Clear =
        (pERR->_I_Q14U_Vbus_pu <= pERR->Over_Voltage._P_Q14I_Clear_TL);
    Check_Cal(&pERR->Over_Voltage, pERR->Motor_Error_Flag.bit.over_voltage);
    
    pERR->Low_Voltage.Check_Flag.bit.Enable = Q32U_Enable;
    pERR->Low_Voltage.Check_Flag.bit.Condition_Set =
        (pERR->_I_Q14U_Vbus_pu <= pERR->Low_Voltage._P_Q14I_Check_TL);
    Check_Cal(&pERR->Low_Voltage, pERR->Motor_Error_Flag.bit.low_voltage);
    
    pERR->Over_Current1.Check_Flag.bit.Enable = Q32U_Enable;
    pERR->Over_Current1.Check_Flag.bit.Condition_Set =
        (pERR->_I_Q14U_Iphase_Max_pu >= pERR->Over_Current1._P_Q14I_Check_TL);
    Check_Cal(&pERR->Over_Current1, pERR->Motor_Error_Flag.bit.over_current1);
    
    pERR->Over_Current2.Check_Flag.bit.Enable = Q32U_Enable;
    pERR->Over_Current2.Check_Flag.bit.Condition_Set =
        (pERR->_I_Q14U_Iphase_Max_pu >= pERR->Over_Current2._P_Q14I_Check_TL);
    Check_Cal(&pERR->Over_Current2, pERR->Motor_Error_Flag.bit.over_current2);
    
    pERR->Over_Current3.Check_Flag.bit.Enable = Q32U_Enable;
    pERR->Over_Current3.Check_Flag.bit.Condition_Set =
        (pERR->_I_Q14U_Iphase_Max_pu >= pERR->Over_Current3._P_Q14I_Check_TL);
    Check_Cal(&pERR->Over_Current3, pERR->Motor_Error_Flag.bit.over_current3);
    
    pERR->Over_Temp.Check_Flag.bit.Enable = 1U;
    pERR->Over_Temp.Check_Flag.bit.Condition_Set =
        (pERR->_I_Q14U_Temp_ADC <= pERR->Over_Temp._P_Q14I_Check_TL);
    pERR->Over_Temp.Check_Flag.bit.Condition_Clear =
        (pERR->_I_Q14U_Temp_ADC >= pERR->Over_Temp._P_Q14I_Clear_TL);
    Check_Cal(&pERR->Over_Temp, pERR->Motor_Error_Flag.bit.over_temp);
    
    pERR->Low_Temp.Check_Flag.bit.Enable = 1U;
    pERR->Low_Temp.Check_Flag.bit.Condition_Set =
        (pERR->_I_Q14U_Temp_ADC >= pERR->Low_Temp._P_Q14I_Check_TL);
    pERR->Low_Temp.Check_Flag.bit.Condition_Clear =
        (pERR->_I_Q14U_Temp_ADC <= pERR->Low_Temp._P_Q14I_Clear_TL);
    Check_Cal(&pERR->Low_Temp, pERR->Motor_Error_Flag.bit.low_temp);
    
    pERR->Over_Speed.Check_Flag.bit.Enable = Q32U_Enable;
    pERR->Over_Speed.Check_Flag.bit.Condition_Set =
        (pERR->_I_Q14U_Speed_pu >= pERR->Over_Speed._P_Q14I_Check_TL);
    Check_Cal(&pERR->Over_Speed, pERR->Motor_Error_Flag.bit.over_speed);
    
    pERR->Low_Speed.Check_Flag.bit.Enable = Q32U_Enable;
    pERR->Low_Speed.Check_Flag.bit.Condition_Set =
        (pERR->_I_Q14U_Speed_pu <= pERR->Low_Speed._P_Q14I_Check_TL);
    Check_Cal(&pERR->Low_Speed, pERR->Motor_Error_Flag.bit.low_speed);
    
    pERR->Over_Power.Check_Flag.bit.Enable = Q32U_Enable;
    pERR->Over_Power.Check_Flag.bit.Condition_Set =
        (pERR->_I_Q14U_Vbus_pu*pERR->_I_Q14U_Ibus_pu >= pERR->Over_Power._P_Q14I_Check_TL);
    Check_Cal(&pERR->Over_Power, pERR->Motor_Error_Flag.bit.over_power);
    
    pERR->Over_Ibus.Check_Flag.bit.Enable = Q32U_Enable;
    pERR->Over_Ibus.Check_Flag.bit.Condition_Set =
        (pERR->_I_Q14U_Ibus_pu >= pERR->Over_Ibus._P_Q14I_Check_TL);
    Check_Cal(&pERR->Over_Ibus, pERR->Motor_Error_Flag.bit.over_ibus);
    
    pERR->Fast_Over_Voltage.Check_Flag.bit.Enable = 1U;
    pERR->Fast_Over_Current.Check_Flag.bit.Enable = 1U;
}

/**********************************************************************************************
Function: MC_Error_Speed_Flow_FOC
Description: 电机故障检测速度环FOC
Input: 无
Output: 无
Input_Output: 电机故障检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MC_Error_Speed_Flow_FOC(ST_MOTOR_ERROR* pERR, Q32U_ Q32U_Enable)
{
    pERR->Phase_Lack_A.Check_Flag.bit.Enable = Q32U_Enable;
    pERR->Phase_Lack_A.Check_Flag.bit.Condition_Set =
        ((pERR->_I_Q14U_Iphase_A_Max_pu <= pERR->Phase_Lack_A._P_Q14I_Check_TL)
        && (pERR->_I_Q14U_IsRef_pu >= pERR->Phase_Lack_A._P_Q14I_Clear_TL));
    Check_Cal(&pERR->Phase_Lack_A, pERR->Motor_Error_Flag.bit.phase_lack_a);
    
    pERR->Phase_Lack_B.Check_Flag.bit.Enable = Q32U_Enable;
    pERR->Phase_Lack_B.Check_Flag.bit.Condition_Set =
        ((pERR->_I_Q14U_Iphase_B_Max_pu <= pERR->Phase_Lack_B._P_Q14I_Check_TL)
        && (pERR->_I_Q14U_IsRef_pu >= pERR->Phase_Lack_B._P_Q14I_Clear_TL));
    Check_Cal(&pERR->Phase_Lack_B, pERR->Motor_Error_Flag.bit.phase_lack_b);
    
    pERR->Phase_Lack_C.Check_Flag.bit.Enable = Q32U_Enable;
    pERR->Phase_Lack_C.Check_Flag.bit.Condition_Set =
        ((pERR->_I_Q14U_Iphase_C_Max_pu <= pERR->Phase_Lack_C._P_Q14I_Check_TL)
        && (pERR->_I_Q14U_IsRef_pu >= pERR->Phase_Lack_C._P_Q14I_Clear_TL));
    Check_Cal(&pERR->Phase_Lack_C, pERR->Motor_Error_Flag.bit.phase_lack_c);
    
    pERR->Rotor_Lock.Check_Flag.bit.Enable = Q32U_Enable;
    pERR->Rotor_Lock.Check_Flag.bit.Condition_Set =
        ((pERR->_I_Q14U_IsRef_pu >= pERR->Rotor_Lock._P_Q14I_Check_TL)
        && (pERR->_I_Q14U_Speed_pu <= pERR->Rotor_Lock._P_Q14I_Clear_TL));
    Check_Cal(&pERR->Rotor_Lock, pERR->Motor_Error_Flag.bit.rotor_lock);
    
    pERR->Loss_Step.Check_Flag.bit.Enable = Q32U_Enable;
    pERR->Loss_Step.Check_Flag.bit.Condition_Set =
        ((pERR->_I_Q14U_Es_pu <= pERR->Loss_Step._P_Q14I_Check_TL)
        && (pERR->_I_Q14U_Speed_pu >= pERR->Loss_Step._P_Q14I_Clear_TL));
    Check_Cal(&pERR->Loss_Step, pERR->Motor_Error_Flag.bit.loss_step);
    
}

/**********************************************************************************************
Function: MC_Error_Current_Flow
Description: 电机故障检测电流环
Input: 无
Output: 无
Input_Output: 电机故障检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MC_Error_Current_Flow(ST_MOTOR_ERROR* pERR)
{
    pERR->Fast_Over_Voltage.Check_Flag.bit.Condition_Set =
        (pERR->_I_Q14U_Vbus_pu >= pERR->Fast_Over_Voltage._P_Q14I_Check_TL);
    Check_Cal(&pERR->Fast_Over_Voltage, pERR->Motor_Error_Flag.bit.fast_over_voltage);
    
    pERR->Fast_Over_Current.Check_Flag.bit.Condition_Set =
        (pERR->_I_Q14U_Iphase_Max_pu >= pERR->Fast_Over_Current._P_Q14I_Check_TL);
    Check_Cal(&pERR->Fast_Over_Current, pERR->Motor_Error_Flag.bit.fast_over_current);
}

/**********************************************************************************************
Function: MC_Error_Short_Flow
Description: 电机故障检测短路环
Input: 无
Output: 无
Input_Output: 电机故障检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MC_Error_Short_Flow(ST_MOTOR_ERROR* pERR)
{
    pERR->_V_Q32U_MOS_Error_cnt++;
    pERR->Motor_Error_Flag.bit.current_short = 1U;
}

/**********************************************************************************************
Function: MC_Error_Clear
Description: 清除电机故障
Input: 无
Output: 无
Input_Output: 电机故障检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MC_Error_Clear(ST_MOTOR_ERROR* pERR)
{
    pERR->Motor_Error_Flag.bit.current_short = 0U;
    pERR->Motor_Error_Flag.bit.current_offset = 0U;
    pERR->Motor_Error_Flag.bit.position_error = 0U;
    pERR->Motor_Error_Flag.bit.rotor_stall = 0U;
    
    pERR->Motor_Error_Flag.bit.low_voltage = 0U;
    
    pERR->Motor_Error_Flag.bit.over_current1 = 0U;
    pERR->Motor_Error_Flag.bit.over_current2 = 0U;
    pERR->Motor_Error_Flag.bit.over_current3 = 0U;
    
    pERR->Motor_Error_Flag.bit.over_speed = 0U;
    pERR->Motor_Error_Flag.bit.low_speed = 0U;
    
    pERR->Motor_Error_Flag.bit.over_power = 0U;
    pERR->Motor_Error_Flag.bit.over_ibus = 0U;
    
    pERR->Motor_Error_Flag.bit.phase_lack_a = 0U;
    pERR->Motor_Error_Flag.bit.phase_lack_b = 0U;
    pERR->Motor_Error_Flag.bit.phase_lack_c = 0U;
    pERR->Motor_Error_Flag.bit.rotor_lock = 0U;
    pERR->Motor_Error_Flag.bit.loss_step = 0U;

    pERR->Motor_Error_Flag.bit.fast_over_voltage = 0U;
    pERR->Motor_Error_Flag.bit.fast_over_current = 0U;
    
    Check_Init(&pERR->Low_Voltage);
    Check_Init(&pERR->Over_Current1);
    Check_Init(&pERR->Over_Current2);
    Check_Init(&pERR->Over_Current3);
    Check_Init(&pERR->Over_Speed);
    Check_Init(&pERR->Low_Speed);
    Check_Init(&pERR->Over_Power);
    Check_Init(&pERR->Over_Ibus);
    Check_Init(&pERR->Phase_Lack_A);
    Check_Init(&pERR->Phase_Lack_B);
    Check_Init(&pERR->Phase_Lack_C);
    Check_Init(&pERR->Rotor_Lock);
    Check_Init(&pERR->Loss_Step);
    Check_Init(&pERR->Fast_Over_Voltage);
    Check_Init(&pERR->Fast_Over_Current);
}
