/**************************************************************************************************
*     File Name :                        BSP_WDG.h
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             WDG初始化及应用层接口头文件
**************************************************************************************************/
#ifndef BSP_WDG_H
#define BSP_WDG_H

#include "HAL_CFG.h"

#define HAL_WDOG_WIN_WINDOWVALUE (360000U)
#define HAL_WDOG_WIN_TIMEOUTVALUE (4000000U)     //100ms溢出，10ms喂一次狗

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
