/**************************************************************************************************
*     File Name :                        BSP_GPIO.h
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             GPIO初始化及应用层接口头文件
**************************************************************************************************/
#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include "HAL_CFG.h"


/**********************************************************************************************
Function: BSP_GPIO_Init
Description: GPIO初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_GPIO_Init(void);


void BSP_GPIO_RLY0(Q32U_ state);
void BSP_GPIO_RLY1(Q32U_ state);
void BSP_GPIO_RLYN(Q32U_ state);

Q32U_ BSP_GPIO_BTN1(void);
Q32U_ BSP_GPIO_BTN2(void);
Q32U_ BSP_GPIO_BTN3(void);
Q32U_ BSP_GPIO_BTN4(void);

void BSP_SPI_RST(Q32U_ state);
void BSP_SPI_A0(Q32U_ state);
void BSP_SPI_CS(Q32U_ state);


#endif /* BSP_GPIO_H */
