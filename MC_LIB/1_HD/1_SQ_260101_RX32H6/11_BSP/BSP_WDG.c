/**************************************************************************************************
*     File Name :                        BSP_WDG.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             WDG初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_WDG.h"

/**********************************************************************************************
Function: BSP_WDG_Init
Description: WDG初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_WDG_Init(void)
{
    RCC_Enable_LSI();//Enable LSI
    while (RCC_Get_LSIRDY() != 1){;}
                          
    IWDG_Enable_WriteAccess(IWDG);
    IWDG_Set_Prescaler(IWDG,IWDGPrescaler);
    IWDG_Set_ReloadCounter(IWDG,ReloadCounter);
    while (IWDG_Is_Ready(IWDG) != 1){;}
    IWDG_Reload_Counter(IWDG);
    IWDG_Enable(IWDG); 
}
