/**************************************************************************************************
*     File Name :                        Current.c
*     Library/Module Name :              SysTask
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电流保护源文件
**************************************************************************************************/
#include "Current.h"

ST_CURRENT_PROTECT Current_Protect_1 = {
    .Q16U_current_protect_tl = CURRENT_PROTECT_LEVEL_1_TL,
    .Q16U_current_protect_time = CURRENT_PROTECT_LEVEL_1_TIME,
};

ST_CURRENT_PROTECT Current_Protect_2 = {
    .Q16U_current_protect_tl = CURRENT_PROTECT_LEVEL_2_TL,
    .Q16U_current_protect_time = CURRENT_PROTECT_LEVEL_2_TIME,
};

ST_CURRENT_PROTECT Current_Protect_3 = {
    .Q16U_current_protect_tl = CURRENT_PROTECT_LEVEL_3_TL,
    .Q16U_current_protect_time = CURRENT_PROTECT_LEVEL_3_TIME,
};

/**********************************************************************************************
Function: Current_Protect_Level
Description: 电流保护分级控制
Input: 无
Output: 无
Input_Output: 电流保护指针，系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Current_Protect_Level(ST_CURRENT_PROTECT* pCP, ST_SYSTEM_TASK*  pST)
{
    if(pST->Q16U_Current_Max >= pCP->Q16U_current_protect_tl)
    {
        if(++pCP->Q16U_current_protect_cnt >= pCP->Q16U_current_protect_time)
        {
            pST->System_Error_Flag.BIT.over_current_error = 1U;
        }
    }
    else
    {
        if(pCP->Q16U_current_protect_cnt > 0)
        {
            pCP->Q16U_current_protect_cnt--;
        }
        
    }
}

/**********************************************************************************************
Function: Current_Protect_Flow
Description: 电流保护控制
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Current_Protect_Flow(ST_SYSTEM_TASK*  pST)
{
    pST->Q16U_Current_Max = Motor_Read_Current_Max();
    
    if((pST->System_Flow == SYSTEM_STATE_RUN)
    && (pST->System_Error_Flag.BIT.over_current_error == 0U))
    {
#if(CURRENT_PROTECT_LEVEL == 1)
        Current_Protect_Level(&Current_Protect_1, pST);
#elif(CURRENT_PROTECT_LEVEL == 2)
        Current_Protect_Level(&Current_Protect_1, pST);
        Current_Protect_Level(&Current_Protect_2, pST);
#elif(CURRENT_PROTECT_LEVEL == 3)
        Current_Protect_Level(&Current_Protect_1, pST);
        Current_Protect_Level(&Current_Protect_2, pST);
        Current_Protect_Level(&Current_Protect_3, pST);
#endif
    }
    else
    {
#if(CURRENT_PROTECT_LEVEL == 1)
        Current_Protect_1.Q16U_current_protect_cnt = 0;
#elif(CURRENT_PROTECT_LEVEL == 2)
        Current_Protect_1.Q16U_current_protect_cnt = 0;
        Current_Protect_2.Q16U_current_protect_cnt = 0;
#elif(CURRENT_PROTECT_LEVEL == 3)
        Current_Protect_1.Q16U_current_protect_cnt = 0;
        Current_Protect_2.Q16U_current_protect_cnt = 0;
        Current_Protect_3.Q16U_current_protect_cnt = 0;
#endif
    }
}
