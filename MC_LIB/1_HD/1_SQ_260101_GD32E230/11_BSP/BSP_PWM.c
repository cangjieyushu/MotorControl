/**************************************************************************************************
*     File Name :                        BSP_PWM.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             PWM初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_PWM.h"

/**********************************************************************************************
Function: BSP_PWM_Init
Description: 电机控制用PWM初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_PWM_Init(void)
{
    /* -----------------------------------------------------------------------
    HAL_MOTOR_PWM configuration:
    generate 3 complementary PWM signal.
    HAL_MOTOR_PWMCLK is fixed to systemcoreclock, the HAL_MOTOR_PWM prescaler is equal to 71 
    so the HAL_MOTOR_PWM counter clock used is 1MHz.
    insert a dead time equal to 164/systemcoreclock = 2.28us 
    configure the break feature, active at low level, and using the automatic
    output enable feature.
    use the locking parameters level 0.
    ----------------------------------------------------------------------- */
    timer_oc_parameter_struct timer_ocinitpara;
    timer_parameter_struct timer_initpara;
    timer_break_parameter_struct timer_breakpara;


    timer_deinit(HAL_MOTOR_PWM);
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
    /* HAL_MOTOR_PWM configuration */
    timer_initpara.prescaler         = HAL_PWM_PRESCALER;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = HAL_PWM_INIT_SET;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV4;
    timer_initpara.repetitioncounter = 0;
    timer_init(HAL_MOTOR_PWM, &timer_initpara);
    
    /* initialize TIMER channel output parameter struct */
    timer_channel_output_struct_para_init(&timer_ocinitpara);
    /* CH0/CH0N, CH1/CH1N and CH2/CH2N configuration in timing mode */
    timer_ocinitpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocinitpara.outputnstate = TIMER_CCXN_ENABLE;
    timer_ocinitpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocinitpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocinitpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocinitpara.ocnidlestate = TIMER_OC_IDLE_STATE_LOW;

    timer_channel_output_config(HAL_MOTOR_PWM, UH_PWM_CHANNEL, &timer_ocinitpara);
    timer_channel_output_config(HAL_MOTOR_PWM, VH_PWM_CHANNEL, &timer_ocinitpara);
    timer_channel_output_config(HAL_MOTOR_PWM, WH_PWM_CHANNEL, &timer_ocinitpara);

    /* configure TIMER channel 0 */
    timer_channel_output_pulse_value_config(HAL_MOTOR_PWM, UH_PWM_CHANNEL, 0);
    timer_channel_output_mode_config(HAL_MOTOR_PWM, UH_PWM_CHANNEL, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(HAL_MOTOR_PWM, UH_PWM_CHANNEL, TIMER_OC_SHADOW_ENABLE);
    
    /* configure TIMER channel 1 */
    timer_channel_output_pulse_value_config(HAL_MOTOR_PWM, VH_PWM_CHANNEL, 0);
    timer_channel_output_mode_config(HAL_MOTOR_PWM, VH_PWM_CHANNEL, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(HAL_MOTOR_PWM, VH_PWM_CHANNEL, TIMER_OC_SHADOW_ENABLE);

    /* configure TIMER channel 2 */
    timer_channel_output_pulse_value_config(HAL_MOTOR_PWM, WH_PWM_CHANNEL, 0);
    timer_channel_output_mode_config(HAL_MOTOR_PWM, WH_PWM_CHANNEL, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(HAL_MOTOR_PWM, WH_PWM_CHANNEL, TIMER_OC_SHADOW_ENABLE);

    /* configure TIMER channel 3 */
    timer_channel_output_pulse_value_config(HAL_MOTOR_PWM, ADC_TRIGGER_CHANNEL, 0);
    timer_channel_output_mode_config(HAL_MOTOR_PWM, ADC_TRIGGER_CHANNEL, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(HAL_MOTOR_PWM, ADC_TRIGGER_CHANNEL, TIMER_OC_SHADOW_ENABLE);
    
    TIMER_CHCTL2(HAL_MOTOR_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2EN
                                            |TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2NEN));
                                            
    /* initialize TIMER break parameter struct */
    timer_break_struct_para_init(&timer_breakpara);
    /* automatic output enable, break, dead time and lock configuration*/
    timer_breakpara.runoffstate      = TIMER_ROS_STATE_ENABLE;
    timer_breakpara.ideloffstate     = TIMER_IOS_STATE_ENABLE;
    timer_breakpara.deadtime         = 90;                      //10us,154     5us,90   //18M
    timer_breakpara.breakpolarity    = TIMER_BREAK_POLARITY_LOW;
    timer_breakpara.outputautostate  = TIMER_OUTAUTO_ENABLE;
    timer_breakpara.protectmode      = TIMER_CCHP_PROT_OFF;
    timer_breakpara.breakstate       = TIMER_BREAK_ENABLE;     //TIMER_BREAK_ENABLE,TIMER_BREAK_DISABLE
    timer_break_config(HAL_MOTOR_PWM, &timer_breakpara);
    
    /* HAL_MOTOR_PWM primary output function enable */
    timer_primary_output_config(HAL_MOTOR_PWM, ENABLE);
    
    /* HAL_MOTOR_PWM counter enable */
    timer_enable(HAL_MOTOR_PWM);
    
    Math_Delay_us(1000U);
    
    timer_interrupt_flag_clear(HAL_MOTOR_PWM, TIMER_INT_FLAG_UP);
    timer_interrupt_flag_clear(HAL_MOTOR_PWM, TIMER_INT_FLAG_CH0);
    timer_interrupt_flag_clear(HAL_MOTOR_PWM, TIMER_INT_FLAG_CH1);
    timer_interrupt_flag_clear(HAL_MOTOR_PWM, TIMER_INT_FLAG_CH2);
    timer_interrupt_flag_clear(HAL_MOTOR_PWM, TIMER_INT_FLAG_CH3);
    timer_interrupt_flag_clear(HAL_MOTOR_PWM, TIMER_INTF_BRKIF);
    
    /* HAL_MOTOR_PWM channel control update interrupt enable */
    timer_interrupt_enable(HAL_MOTOR_PWM, TIMER_INT_CH3);
    /* HAL_MOTOR_PWM break interrupt disable */
    timer_interrupt_enable(HAL_MOTOR_PWM, TIMER_INT_BRK);
}
