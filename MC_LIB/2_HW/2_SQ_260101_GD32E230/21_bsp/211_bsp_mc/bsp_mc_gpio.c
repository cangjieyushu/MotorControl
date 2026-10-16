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
    //ADC
    /* config the GPIO as analog mode */
    gpio_mode_set(HW_MC_ADC_U_BEMF_GPIO_Port, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, HW_MC_ADC_U_BEMF_Pin);
    gpio_mode_set(HW_MC_ADC_V_BEMF_GPIO_Port, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, HW_MC_ADC_V_BEMF_Pin);
    gpio_mode_set(HW_MC_ADC_W_BEMF_GPIO_Port, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, HW_MC_ADC_W_BEMF_Pin);
    gpio_mode_set(HW_MC_ADC_CURRENT_GPIO_Port, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, HW_MC_ADC_CURRENT_Pin);
    gpio_mode_set(HW_MC_ADC_VBUS_GPIO_Port, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, HW_MC_ADC_VBUS_Pin);
    gpio_mode_set(HW_MC_ADC_TEMP_GPIO_Port, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, HW_MC_ADC_TEMP_Pin);

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
    /*TIM0:*/ 
    /*configure PA8/PA9/PA10(TIMER0/CH0/CH1/CH2) as alternate function*/
    gpio_mode_set(HW_MC_PWM_UH_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, HW_MC_PWM_UH_Pin);
    gpio_output_options_set(HW_MC_PWM_UH_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,HW_MC_PWM_UH_Pin);

    gpio_mode_set(HW_MC_PWM_VH_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, HW_MC_PWM_VH_Pin);
    gpio_output_options_set(HW_MC_PWM_VH_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,HW_MC_PWM_VH_Pin);

    gpio_mode_set(HW_MC_PWM_WH_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, HW_MC_PWM_WH_Pin);
    gpio_output_options_set(HW_MC_PWM_WH_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,HW_MC_PWM_WH_Pin);

    gpio_af_set(HW_MC_PWM_UH_GPIO_Port, GPIO_AF_2, HW_MC_PWM_UH_Pin);
    gpio_af_set(HW_MC_PWM_VH_GPIO_Port, GPIO_AF_2, HW_MC_PWM_VH_Pin);
    gpio_af_set(HW_MC_PWM_WH_GPIO_Port, GPIO_AF_2, HW_MC_PWM_WH_Pin);

    /*configure PB13/PB14/PB15(TIMER0/CH0N/CH1N/CH2N) as alternate function*/
    gpio_mode_set(HW_MC_PWM_UL_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, HW_MC_PWM_UL_Pin);
    gpio_output_options_set(HW_MC_PWM_UL_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,HW_MC_PWM_UL_Pin);

    gpio_mode_set(HW_MC_PWM_VL_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, HW_MC_PWM_VL_Pin);
    gpio_output_options_set(HW_MC_PWM_VL_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,HW_MC_PWM_VL_Pin);

    gpio_mode_set(HW_MC_PWM_WL_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, HW_MC_PWM_WL_Pin);
    gpio_output_options_set(HW_MC_PWM_WL_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,HW_MC_PWM_WL_Pin);

    gpio_af_set(HW_MC_PWM_UL_GPIO_Port, GPIO_AF_2, HW_MC_PWM_UL_Pin);
    gpio_af_set(HW_MC_PWM_VL_GPIO_Port, GPIO_AF_2, HW_MC_PWM_VL_Pin);
    gpio_af_set(HW_MC_PWM_WL_GPIO_Port, GPIO_AF_2, HW_MC_PWM_WL_Pin);
    
    gpio_mode_set(HW_MC_PWM_BRK_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, HW_MC_PWM_BRK_Pin);
    gpio_af_set(HW_MC_PWM_BRK_GPIO_Port, GPIO_AF_2, HW_MC_PWM_BRK_Pin);

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
