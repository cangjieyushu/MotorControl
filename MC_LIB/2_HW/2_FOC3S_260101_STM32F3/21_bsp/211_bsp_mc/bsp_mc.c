/*
*     File Name :                        bsp_mc
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制外设汇总初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_mc.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_MC_Init
Description: 电机控制外设初始化汇总
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_Init(void)
{
    /* GPIO 引脚复用先配置（ADC/OPA/DAC/CMP/PWM） */
    BSP_MC_GPIO_Init();

    /* 有依赖关系的按序初始化：DAC → OPA → CMP */
    BSP_MC_DAC_Init();         /* 建立窗口阈值电压 */
    BSP_MC_OPAMP_Init();       /* OPA 输出到 CMP 的 P 端 */
    BSP_MC_CMP_Init();         /* 窗口比较器输出到 TIM8_BKIN */

    /* 电机控制主外设 */
    BSP_MC_PWM_Init();         /* TIM8 三相互补 PWM */
    BSP_MC_TIM_Init();         /* TIM2 HALL 计时 */

    /* ADC 最后：注入组配置 + 规则组 DMA */
    BSP_MC_ADC_Init();         /* 三 ADC 配置，未启动转换 */
    BSP_MC_DMA_Init();         /* DMA 配置 + 启动 ADC1 规则组 */
}
