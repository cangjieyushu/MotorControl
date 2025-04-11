/**************************************************************************************************
*     File Name :                        BSP_GPIO.h
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             GPIO初始化及应用层接口头文件
**************************************************************************************************/
#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include "MotorHal_cfg.h"

#define HAL_SW2_PORT                        PORT_E
#define HAL_SW2_PIN                         GPIO_11
#define HAL_SW2_PINMUX                      PTE11_GPIO

#define HAL_SW3_PORT                        PORT_E
#define HAL_SW3_PIN                         GPIO_3
#define HAL_SW3_PINMUX                      PTE3_GPIO

typedef union
{
    Q32U_ Word;
    struct
    {
        Q32U_ B0 : 1;
        Q32U_ B1 : 1;
        Q32U_ B2 : 1;
        Q32U_ B3 : 1;
        Q32U_ B4 : 1;
        Q32U_ B5 : 1;
        Q32U_ B6 : 1;
        Q32U_ B7 : 1;
        Q32U_ B8 : 1;
        Q32U_ B9 : 1;
        Q32U_ B10 : 1;
        Q32U_ B11 : 1;
        Q32U_ B12 : 1;
        Q32U_ B13 : 1;
        Q32U_ B14 : 1;
        Q32U_ B15 : 1;
        Q32U_ B16 : 1;
        Q32U_ B17 : 1;
        Q32U_ B18 : 1;
        Q32U_ B19 : 1;
        Q32U_ B20 : 1;
        Q32U_ B21 : 1;
        Q32U_ B22 : 1;
        Q32U_ B23 : 1;
        Q32U_ B24 : 1;
        Q32U_ B25 : 1;
        Q32U_ B26 : 1;
        Q32U_ B27 : 1;
        Q32U_ B28 : 1;
        Q32U_ B29 : 1;
        Q32U_ B30 : 1;
        Q32U_ B31 : 1;
    }Bits;
}PortStatusType;

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

/**********************************************************************************************
Function: BSP_GPIO_Read_SW0_State
Description: 按键0状态读取
Input: 无
Output: 无
Input_Output: 无
Return: 按键0状态
Author: CJYS
***********************************************************************************************/
Q32U_ BSP_GPIO_Read_SW0_State(void);

/**********************************************************************************************
Function: BSP_GPIO_Read_SW1_State
Description: 按键1状态读取
Input: 无
Output: 无
Input_Output: 无
Return: 按键1状态
Author: CJYS
***********************************************************************************************/
Q32U_ BSP_GPIO_Read_SW1_State(void);

/**********************************************************************************************
Function: HGPIO_TogglePinOutput
Description: GPIO翻转
Input: 引脚编号，引脚位号
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void HGPIO_TogglePinOutput(PORT_Id_t port, PORT_GpioNum_t gpioNum);

#endif /* BSP_GPIO_H */
