/*
*     File Name :                        bsp_mc_gpio
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制 GPIO 初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_mc_gpio.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 内部辅助函数 ----------------------------*/
/*
Function: BSP_MC_GPIO_InitAnalog
Description: 模拟通道引脚初始化（ADC/OPA/CMP）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static void BSP_MC_GPIO_InitAnalog(void)
{
    
}

/*
Function: BSP_MC_GPIO_InitPwm
Description: TIM8 互补 PWM 引脚初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static void BSP_MC_GPIO_InitPwm(void)
{
    

}


/*-------------------------- 4. 公有接口实现 -----------------------------*/
/*
Function: BSP_MC_GPIO_Init
Description: 电机控制 GPIO 初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_GPIO_Init(void)
{
    BSP_MC_GPIO_InitAnalog();
    BSP_MC_GPIO_InitPwm();
}
