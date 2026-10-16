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
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* ---- ADC 模拟输入 ---- */
    GPIO_InitStruct.Mode      = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull      = GPIO_PUPDR_Floating;
    GPIO_InitStruct.Speed     = GPIO_OSPEEDR_High;
    GPIO_InitStruct.Alternate = GPIO_AF0;

    GPIO_InitStruct.Pin = HW_MC_ADC_U_BEMF_Pin;
    GPIO_Init(HW_MC_ADC_U_BEMF_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = HW_MC_ADC_V_BEMF_Pin;
    GPIO_Init(HW_MC_ADC_V_BEMF_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = HW_MC_ADC_W_BEMF_Pin;
    GPIO_Init(HW_MC_ADC_W_BEMF_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = HW_MC_ADC_VBUS_Pin;
    GPIO_Init(HW_MC_ADC_VBUS_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = HW_MC_ADC_TEMP_Pin;
    GPIO_Init(HW_MC_ADC_TEMP_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = HW_MC_ADC_VR_Pin;
    GPIO_Init(HW_MC_ADC_VR_GPIO_Port, &GPIO_InitStruct);

    /* ---- OPA 模拟输入 ---- */
    GPIO_InitStruct.Speed = GPIO_OSPEEDR_Low;

    GPIO_InitStruct.Pin = HW_MC_OPAMP_VINP_Pin;
    GPIO_Init(HW_MC_OPAMP_VINP_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = HW_MC_OPAMP_VINN_Pin;
    GPIO_Init(HW_MC_OPAMP_VINN_GPIO_Port, &GPIO_InitStruct);

    /* ---- CMP 模拟输入 ---- */
    GPIO_InitStruct.Speed = GPIO_OSPEEDR_High;

    GPIO_InitStruct.Pin = HW_MC_CMP_VINP_Pin;
    GPIO_Init(HW_MC_CMP_VINP_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = HW_MC_CMP_VINN_Pin;
    GPIO_Init(HW_MC_CMP_VINN_GPIO_Port, &GPIO_InitStruct);
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
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull  = GPIO_PUPDR_Floating;
    GPIO_InitStruct.Speed = GPIO_OSPEEDR_High;

    GPIO_InitStruct.Alternate = HW_MC_PWM_UH_AF;
    GPIO_InitStruct.Pin       = HW_MC_PWM_UH_Pin;
    GPIO_Init(HW_MC_PWM_UH_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Alternate = HW_MC_PWM_VH_AF;
    GPIO_InitStruct.Pin       = HW_MC_PWM_VH_Pin;
    GPIO_Init(HW_MC_PWM_VH_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Alternate = HW_MC_PWM_WH_AF;
    GPIO_InitStruct.Pin       = HW_MC_PWM_WH_Pin;
    GPIO_Init(HW_MC_PWM_WH_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Alternate = HW_MC_PWM_UL_AF;
    GPIO_InitStruct.Pin       = HW_MC_PWM_UL_Pin;
    GPIO_Init(HW_MC_PWM_UL_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Alternate = HW_MC_PWM_VL_AF;
    GPIO_InitStruct.Pin       = HW_MC_PWM_VL_Pin;
    GPIO_Init(HW_MC_PWM_VL_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Alternate = HW_MC_PWM_WL_AF;
    GPIO_InitStruct.Pin       = HW_MC_PWM_WL_Pin;
    GPIO_Init(HW_MC_PWM_WL_GPIO_Port, &GPIO_InitStruct);
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
