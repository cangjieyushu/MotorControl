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
static void BSP_MC_GPIO_InitAnalog(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

    /* ---- 三相电流 ADC 输入 ---- */
    GPIO_InitStruct.GPIO_Pin = HW_MC_ADC_U_CURRENT_Pin; GPIO_Init(HW_MC_ADC_U_CURRENT_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_ADC_V_CURRENT_Pin; GPIO_Init(HW_MC_ADC_V_CURRENT_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_ADC_W_CURRENT_Pin; GPIO_Init(HW_MC_ADC_W_CURRENT_GPIO_Port, &GPIO_InitStruct);

    /* ---- 母线电压 / 温度 ADC 输入 ---- */
    GPIO_InitStruct.GPIO_Pin = HW_MC_ADC_VBUS_Pin;      GPIO_Init(HW_MC_ADC_VBUS_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_ADC_TEMP_Pin;      GPIO_Init(HW_MC_ADC_TEMP_GPIO_Port, &GPIO_InitStruct);

    /* ---- OPA 输出引脚（模拟输出）---- */
    GPIO_InitStruct.GPIO_Pin = HW_MC_OPAMP1_OUT_Pin; GPIO_Init(HW_MC_OPAMP1_OUT_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_OPAMP2_OUT_Pin; GPIO_Init(HW_MC_OPAMP2_OUT_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_OPAMP3_OUT_Pin; GPIO_Init(HW_MC_OPAMP3_OUT_GPIO_Port, &GPIO_InitStruct);

    /* ---- DAC 输出引脚（模拟输出）---- */
    GPIO_InitStruct.GPIO_Pin = HW_MC_DAC_VH_Pin; GPIO_Init(HW_MC_DAC_VH_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_DAC_VL_Pin; GPIO_Init(HW_MC_DAC_VL_GPIO_Port, &GPIO_InitStruct);

    /* ---- CMP 主比较器 P 端 ---- */
    GPIO_InitStruct.GPIO_Pin = HW_MC_OCP_COMP1_Pin; GPIO_Init(HW_MC_OCP_COMP1_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_OCP_COMP3_Pin; GPIO_Init(HW_MC_OCP_COMP3_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_OCP_COMP5_Pin; GPIO_Init(HW_MC_OCP_COMP5_GPIO_Port, &GPIO_InitStruct);
}

static void BSP_MC_GPIO_InitPwm(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;

    /* ---- TIM8 高侧 CH1/2/3（PC6/PC7/PC8）---- */
    GPIO_InitStruct.GPIO_Pin = HW_MC_PWM_UH_Pin; GPIO_Init(HW_MC_PWM_UH_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_PWM_VH_Pin; GPIO_Init(HW_MC_PWM_VH_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_PWM_WH_Pin; GPIO_Init(HW_MC_PWM_WH_GPIO_Port, &GPIO_InitStruct);

    /* ---- TIM8 低侧 CH1N/2N/3N（PB3/PB4/PB5）---- */
    GPIO_InitStruct.GPIO_Pin = HW_MC_PWM_UL_Pin; GPIO_Init(HW_MC_PWM_UL_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_PWM_VL_Pin; GPIO_Init(HW_MC_PWM_VL_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_PWM_WL_Pin; GPIO_Init(HW_MC_PWM_WL_GPIO_Port, &GPIO_InitStruct);

    /* ---- AF4（TIM8 的 AF 编号）---- */
    GPIO_PinAFConfig(HW_MC_PWM_UH_GPIO_Port, HW_MC_PWM_UH_Pin_Source, GPIO_AF_4);
    GPIO_PinAFConfig(HW_MC_PWM_VH_GPIO_Port, HW_MC_PWM_VH_Pin_Source, GPIO_AF_4);
    GPIO_PinAFConfig(HW_MC_PWM_WH_GPIO_Port, HW_MC_PWM_WH_Pin_Source, GPIO_AF_4);
    GPIO_PinAFConfig(HW_MC_PWM_UL_GPIO_Port, HW_MC_PWM_UL_Pin_Source, GPIO_AF_4);
    GPIO_PinAFConfig(HW_MC_PWM_VL_GPIO_Port, HW_MC_PWM_VL_Pin_Source, GPIO_AF_4);
    GPIO_PinAFConfig(HW_MC_PWM_WL_GPIO_Port, HW_MC_PWM_WL_Pin_Source, GPIO_AF_4);
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
