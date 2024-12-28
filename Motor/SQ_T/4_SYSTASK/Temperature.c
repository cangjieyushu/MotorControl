/**************************************************************************************************
*     File Name :                        Temperature.c
*     Library/Module Name :              SysTask
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             温度保护源文件
**************************************************************************************************/
#include "Temperature.h"

ST_TEMP_PROTECT Temperature_Protect_Over = {
    .Q16I_temp_protect_tl = OVER_TEMP_PROTECT_LEVEL_TL,
    .Q16U_temp_protect_time = OVER_TEMP_PROTECT_LEVEL_TIME,
};

ST_TEMP_PROTECT Temperature_Protect_Low = {
    .Q16I_temp_protect_tl = LOW_TEMP_PROTECT_LEVEL_TL,
    .Q16U_temp_protect_time = LOW_TEMP_PROTECT_LEVEL_TIME,
};

/**********************************************************************************************
Function: Temperature_Protect_Flow
Description: 温度保护控制
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Temperature_Protect_Flow(ST_SYSTEM_TASK*  pST)
{
    ST_TEMP_PROTECT* pCVO = &Temperature_Protect_Over;
    ST_TEMP_PROTECT* pCVL = &Temperature_Protect_Low;
    
    pST->Q16U_Temp_0p01_C = pST->FL_TEMP.Q16I_Filter_out;
    
    if(pST->System_Flow != SYSTEM_STATE_POWERUP)
    {
        if(pST->System_Error_Flag.BIT.over_temperature_error == 0U)
        {
            if(pST->Q16U_Temp_0p01_C >= pCVO->Q16I_temp_protect_tl)
            {
                if(++pCVO->Q16U_temp_protect_cnt >= pCVO->Q16U_temp_protect_time)
                {
                    pCVO->Q16U_temp_protect_cnt = 0;
//                    pST->System_Error_Flag.BIT.over_temperature_error = 1U;
                }
            }
            else
            {
                pCVO->Q16U_temp_protect_cnt = 0;
            }
        }
        else
        {
            pCVO->Q16U_temp_protect_cnt = 0;
        }
        
        if(pST->System_Error_Flag.BIT.low_temperature_error == 0U)
        {
            if(pST->Q16U_Temp_0p01_C <= pCVL->Q16I_temp_protect_tl)
            {
                if(++pCVL->Q16U_temp_protect_cnt >= pCVL->Q16U_temp_protect_time)
                {
                    pCVL->Q16U_temp_protect_cnt = 0;
//                    pST->System_Error_Flag.BIT.low_temperature_error = 1U;
                }
            }
            else
            {
                pCVL->Q16U_temp_protect_cnt = 0;
            }
        }
        else
        {
            pCVL->Q16U_temp_protect_cnt = 0;
        }
    }
    else
    {
        pCVO->Q16U_temp_protect_cnt = 0;
        pCVL->Q16U_temp_protect_cnt = 0;
    }
}

