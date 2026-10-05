/**************************************************************************************************
*     File Name :                        BSP_TIM.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             TIM初始化及应用层接口源文件
**************************************************************************************************/
#include "bsp_tim.h"

/**********************************************************************************************
Function: BSP_TIM_Init
Description: HALL换向时间计数器初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_TIM_Init(void)
{
    timer_parameter_struct timer_initpara;

    /* TIMER configuration */
    timer_initpara.prescaler         = (Q32U_)HAL_HALL_TIM_PRESCALER - 1U;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = HAL_HALL_TIM_MAX_CNT;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0U;
    timer_init(HAL_MOTOR_HALL_TIM, &timer_initpara);
    timer_enable(HAL_MOTOR_HALL_TIM);
    
    /* TIMER configuration */
    timer_initpara.prescaler         = (Q32U_)HAL_SWITCH_TIM_PRESCALER - 1U;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = HAL_SWITCH_TIM_MAX_CNT;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0U;
    timer_init(HAL_MOTOR_SWITCH_TIM, &timer_initpara);
    
    /* configure TIMER channel 0 */
    timer_channel_output_pulse_value_config(HAL_MOTOR_SWITCH_TIM, TIMER_CH_0, 1);
    timer_channel_output_mode_config(HAL_MOTOR_SWITCH_TIM, TIMER_CH_0, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(HAL_MOTOR_SWITCH_TIM, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);
    
    timer_auto_reload_shadow_disable(HAL_MOTOR_SWITCH_TIM);
    
    timer_interrupt_flag_clear(HAL_MOTOR_SWITCH_TIM, TIMER_INT_FLAG_UP);
    timer_interrupt_flag_clear(HAL_MOTOR_SWITCH_TIM, TIMER_INT_FLAG_CH0);
    timer_interrupt_flag_clear(HAL_MOTOR_SWITCH_TIM, TIMER_INT_FLAG_CH1);
    timer_interrupt_flag_clear(HAL_MOTOR_SWITCH_TIM, TIMER_INT_FLAG_CH2);
    timer_interrupt_flag_clear(HAL_MOTOR_SWITCH_TIM, TIMER_INT_FLAG_CH3);
    
    timer_disable(HAL_MOTOR_SWITCH_TIM);
    
    timer_interrupt_enable(HAL_MOTOR_SWITCH_TIM, TIMER_INT_CH0);
}
