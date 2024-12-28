/**************************************************************************************************
*     File Name :                        Voltage.c
*     Library/Module Name :              SysTask
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电压保护源文件
**************************************************************************************************/
#include "Voltage.h"

ST_VOLTAGE_PROTECT Voltage_Protect_Over = {
    .F_voltage_protect_tl = OVER_VOLTAGE_PROTECT_LEVEL_TL,
    .Q16U_voltage_protect_time = OVER_VOLTAGE_PROTECT_LEVEL_TIME,
};

ST_VOLTAGE_PROTECT Voltage_Protect_Low = {
    .F_voltage_protect_tl = LOW_VOLTAGE_PROTECT_LEVEL_TL,
    .Q16U_voltage_protect_time = LOW_VOLTAGE_PROTECT_LEVEL_TIME,
};

/**********************************************************************************************
Function: Voltage_Protect_Flow
Description: 电压保护控制
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Voltage_Protect_Flow(ST_SYSTEM_TASK*  pST)
{
    ST_VOLTAGE_PROTECT* pCVO = &Voltage_Protect_Over;
    ST_VOLTAGE_PROTECT* pCVL = &Voltage_Protect_Low;
    
    pST->F_Voltage_Bus = pST->F_FL_VBUS.F_Filter_out;
    
    if(pST->System_Flow != SYSTEM_STATE_POWERUP)
    {
        if(pST->System_Error_Flag.BIT.over_voltage_error == 0U)
        {
            if(pST->F_Voltage_Bus >= pCVO->F_voltage_protect_tl)
            {
                if(++pCVO->Q16U_voltage_protect_cnt >= pCVO->Q16U_voltage_protect_time)
                {
                    pCVO->Q16U_voltage_protect_cnt = 0;
//                    pST->System_Error_Flag.BIT.over_voltage_error = 1U;
                }
            }
            else
            {
                pCVO->Q16U_voltage_protect_cnt = 0;
            }
        }
        else
        {
            pCVO->Q16U_voltage_protect_cnt = 0;
        }
        
        if(pST->System_Error_Flag.BIT.low_voltage_error == 0U)
        {
            if(pST->F_Voltage_Bus <= pCVL->F_voltage_protect_tl)
            {
                if(++pCVL->Q16U_voltage_protect_cnt >= pCVL->Q16U_voltage_protect_time)
                {
                    pCVL->Q16U_voltage_protect_cnt = 0;
//                    pST->System_Error_Flag.BIT.low_voltage_error = 1U;
                }
            }
            else
            {
                pCVL->Q16U_voltage_protect_cnt = 0;
            }
        }
        else
        {
            pCVL->Q16U_voltage_protect_cnt = 0;
        }
    }
    else
    {
        pCVO->Q16U_voltage_protect_cnt = 0;
        pCVL->Q16U_voltage_protect_cnt = 0;
    }
}
