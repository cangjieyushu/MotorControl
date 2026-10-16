/*
*     File Name :                        bsp_mc_pwm
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             PWM 初始化
*                                        TIM8 中心对齐互补 PWM + 死区 + OC4REF 触发 ADC
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_mc_pwm.h"


/*-------------------------- 2. 内部辅助函数 ----------------------------*/
/**
 * @brief  根据期望死区时间（us）计算 TIM8 BDTR 寄存器 DTG[7:0] 编码
 * @param  dt_us  期望死区时间，单位：微秒 (us)，浮点数
 * @retval DTG[7:0] 寄存器值，可直接赋给 BDTR.TIM_DeadTime
 * @note   GD32E230：TIM8 时钟 = 72 MHz
 *         CKD_DIV=4，tDTS = 4 / 72 MHz，系数 = fTIM8/4 = 18.0
 */
static uint8_t BSP_MC_PWM_CalcDeadTimeReg_us(float dt_us)
{
    uint32_t n;
    float    nf;

    if (dt_us <= 0.0f)
    {
        return 0U;
    }

    nf = dt_us * 18.0f;        /* ← 只需改这一处 */
    n  = (uint32_t)nf;
    if (nf > (float)n)
    {
        n++;
    }

    if (n <= 127U)
    {
        return (uint8_t)n;
    }
    else if (n <= 254U)
    {
        return (uint8_t)(0x80U | (uint8_t)((n + 1U) / 2U - 64U));
    }
    else if (n <= 504U)
    {
        return (uint8_t)(0xC0U | (uint8_t)((n + 7U) / 8U - 32U));
    }
    else if (n <= 1008U)
    {
        return (uint8_t)(0xE0U | (uint8_t)((n + 15U) / 16U - 32U));
    }
    else
    {
        return 0xFFU;
    }
}


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_MC_PWM_Init
Description: 电机控制用 PWM 初始化（TIM8 中心对齐互补 PWM）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_PWM_Init(void)
{
    /* -----------------------------------------------------------------------
    HW_MC_PWM configuration:
    generate 3 complementary PWM signal.
    HW_MC_PWMCLK is fixed to systemcoreclock, the HW_MC_PWM prescaler is equal to 71 
    so the HW_MC_PWM counter clock used is 1MHz.
    insert a dead time equal to 164/systemcoreclock = 2.28us 
    configure the break feature, active at low level, and using the automatic
    output enable feature.
    use the locking parameters level 0.
    ----------------------------------------------------------------------- */
    timer_oc_parameter_struct timer_ocinitpara;
    timer_parameter_struct timer_initpara;
    timer_break_parameter_struct timer_breakpara;
    
    
    timer_deinit(HW_MC_PWM);
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
    /* HW_MC_PWM configuration */
    timer_initpara.prescaler         = (Q32U_)HW_PWM_PRESCALER - 1U;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = HW_PWM_INIT_VALUE -1U;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV4;
    timer_initpara.repetitioncounter = 0;
    timer_init(HW_MC_PWM, &timer_initpara);
    
    /* initialize TIMER channel output parameter struct */
    timer_channel_output_struct_para_init(&timer_ocinitpara);
    /* CH0/CH0N, CH1/CH1N and CH2/CH2N configuration in timing mode */
    timer_ocinitpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocinitpara.outputnstate = TIMER_CCXN_ENABLE;
    timer_ocinitpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocinitpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocinitpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocinitpara.ocnidlestate = TIMER_OC_IDLE_STATE_LOW;
    
    timer_channel_output_config(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL, &timer_ocinitpara);
    timer_channel_output_config(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL, &timer_ocinitpara);
    timer_channel_output_config(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL, &timer_ocinitpara);
    
    /* configure TIMER channel 0 */
    timer_channel_output_pulse_value_config(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL, 0);
    timer_channel_output_mode_config(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL, TIMER_OC_SHADOW_ENABLE);
    
    /* configure TIMER channel 1 */
    timer_channel_output_pulse_value_config(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL, 0);
    timer_channel_output_mode_config(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL, TIMER_OC_SHADOW_ENABLE);

    /* configure TIMER channel 2 */
    timer_channel_output_pulse_value_config(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL, 0);
    timer_channel_output_mode_config(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL, TIMER_OC_SHADOW_ENABLE);
    
    /* configure TIMER channel 3 */
    timer_channel_output_pulse_value_config(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL, 0);
    timer_channel_output_mode_config(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL, TIMER_OC_SHADOW_ENABLE);
    
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2EN
                                            |TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2NEN));
    
    /* initialize TIMER break parameter struct */
    timer_break_struct_para_init(&timer_breakpara);
    /* automatic output enable, break, dead time and lock configuration*/
    timer_breakpara.runoffstate      = TIMER_ROS_STATE_ENABLE;
    timer_breakpara.ideloffstate     = TIMER_IOS_STATE_ENABLE;
    timer_breakpara.deadtime         = 90U;                      //10us,154U     5us,90U   //18M
    timer_breakpara.breakpolarity    = TIMER_BREAK_POLARITY_LOW;
    timer_breakpara.outputautostate  = TIMER_OUTAUTO_ENABLE;
    timer_breakpara.protectmode      = TIMER_CCHP_PROT_OFF;
    timer_breakpara.breakstate       = TIMER_BREAK_ENABLE;     //TIMER_BREAK_ENABLE,TIMER_BREAK_DISABLE
    timer_break_config(HW_MC_PWM, &timer_breakpara);
    
    /* HW_MC_PWM primary output function enable */
    timer_primary_output_config(HW_MC_PWM, ENABLE);
    
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_UP);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH0);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH1);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH2);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH3);
    timer_flag_clear(HW_MC_PWM, TIMER_INTF_BRKIF);
    
    /* HW_MC_PWM counter enable */
    timer_enable(HW_MC_PWM);
    
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_UP);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH0);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH1);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH2);
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_CH3);
    timer_flag_clear(HW_MC_PWM, TIMER_INTF_BRKIF);
    
    Math_Delay_us(1000U);
    
    timer_interrupt_flag_clear(HW_MC_PWM, TIMER_INT_FLAG_UP);
    timer_interrupt_flag_clear(HW_MC_PWM, TIMER_INT_FLAG_CH0);
    timer_interrupt_flag_clear(HW_MC_PWM, TIMER_INT_FLAG_CH1);
    timer_interrupt_flag_clear(HW_MC_PWM, TIMER_INT_FLAG_CH2);
    timer_interrupt_flag_clear(HW_MC_PWM, TIMER_INT_FLAG_CH3);
    timer_interrupt_flag_clear(HW_MC_PWM, TIMER_INTF_BRKIF);
    
    /* HW_MC_PWM channel control update interrupt enable */
    timer_interrupt_enable(HW_MC_PWM, TIMER_INT_CH3);
    /* HW_MC_PWM break interrupt disable */
//    timer_interrupt_enable(HW_MC_PWM, TIMER_INT_BRK);
}
