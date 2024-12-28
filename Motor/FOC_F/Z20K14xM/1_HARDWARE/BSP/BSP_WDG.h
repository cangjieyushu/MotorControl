/**************************************************************************************************
*     File Name :                        BSP_WDG.h
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             WDG初始化及应用层接口头文件
**************************************************************************************************/
#ifndef BSP_WDG_H
#define BSP_WDG_H

#include "MotorHal_cfg.h"

#define HAL_WDOG_WIN_WINDOWVALUE (36000U)
#define HAL_WDOG_WIN_TIMEOUTVALUE (400000U)     //10ms溢出，4ms喂一次狗

/**********************************************************************************************
Function: BSP_FeedWatchDog
Description: 喂狗函数
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void BSP_FeedWatchDog(void)
{
    if(WDOG_GetCounter() > HAL_WDOG_WIN_WINDOWVALUE)
    {
        WDOG_Refresh();
    }
}

/**********************************************************************************************
Function: BSP_WDG_Init
Description: WDG初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_WDG_Init(void);

#endif /* BSP_WDG_H */
