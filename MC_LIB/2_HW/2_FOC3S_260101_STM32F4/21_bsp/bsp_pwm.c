/*
*     File Name :                        bsp_pwm
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             PWM初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_pwm.h"


/*-------------------------- 2. 变量 ---------------------------------*//**
 * @brief  根据期望死区时间（us）计算 HAL_MOTOR_PWM/TIM8 BDTR 寄存器 DTG[7:0] 编码
 * @param  dt_us  期望死区时间，单位：微秒 (us)
 * @retval DTG[7:0] 寄存器值，可直接赋给 BDTR.TIM_DeadTime
 * @note   时钟 42 MHz、CKD_DIV=4，tDTS ≈ 95.238 ns
 *         编码向上取整，保证实际死区 ≥ 期望值
 *         期望值超过最大范围（约 96 us）时返回 0xFF
 */
static uint8_t BSP_PWM_CalcDeadTimeReg_us(uint32_t dt_us)
{
    uint32_t n;   /* 死区时间 = n × tDTS，向上取整 */

    if (dt_us == 0U)
    {
        return 0U;                 /* 死区为 0 */
    }

    /* n = ceil(dt_us * 10.5) = ceil(dt_us * 21 / 2) = (dt_us * 21 + 1) / 2 */
    n = (dt_us * 21U + 1U) / 2U;

    if (n <= 127U)
    {
        /* DTG[7:5]=0xx : DT = n × tDTS */
        return (uint8_t)(n & 0x7FU);
    }
    else if (n <= 254U)
    {
        /* DTG[7:5]=10x : DT = (64 + x) × 2 × tDTS */
        uint32_t x = (n + 1U) / 2U - 64U;      /* ceil(n/2) - 64 */
        if (x > 63U) { x = 63U; }
        return (uint8_t)(0x80U | (uint8_t)(x & 0x3FU));
    }
    else if (n <= 504U)
    {
        /* DTG[7:5]=110 : DT = (32 + x) × 8 × tDTS */
        uint32_t x = (n + 7U) / 8U - 32U;      /* ceil(n/8) - 32 */
        if (x > 31U) { x = 31U; }
        return (uint8_t)(0xC0U | (uint8_t)(x & 0x1FU));
    }
    else if (n <= 1008U)
    {
        /* DTG[7:5]=111 : DT = (32 + x) × 16 × tDTS */
        uint32_t x = (n + 15U) / 16U - 32U;    /* ceil(n/16) - 32 */
        if (x > 31U) { x = 31U; }
        return (uint8_t)(0xE0U | (uint8_t)(x & 0x1FU));
    }
    else
    {
        /* 超出最大死区时间，返回最大编码 */
        return 0xFFU;
    }
}


/*-------------------------- 3. 公有接口实现 -----------------------------*/
void BSP_PWM_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;	
    TIM_BDTRInitTypeDef HAL_MOTOR_PWM_BDTRInitStructure;
    
    TIM_Cmd(HAL_MOTOR_PWM, ENABLE); // 最后使能

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV4;                     // 4分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;     // 互补中心对称
    TIM_TimeBaseInitStructure.TIM_Prescaler = (Q32U_)HAL_PWM_PRESCALER - 1U;        // Timer clock = sysclock /(TIM_Prescaler+1) = 168M
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 1U * (Q32U_)HAL_CURRENT_LOOP_FREQ_PRESCALER;
    TIM_TimeBaseInitStructure.TIM_Period = (HAL_PWM_SET_VALUE_T - 1U);               // Period = (TIM counter clock / TIM output clock) - 1 = 20K
    TIM_TimeBaseInit(HAL_MOTOR_PWM,&TIM_TimeBaseInitStructure);
        
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                               // pwm模式
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;                      // TIM_OCNPolarity_High 
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    
    TIM_OC1Init(HAL_MOTOR_PWM,&TIM_OCInitStructure);
    TIM_OC2Init(HAL_MOTOR_PWM,&TIM_OCInitStructure);
    TIM_OC3Init(HAL_MOTOR_PWM,&TIM_OCInitStructure);
    
    TIM_OCInitStructure.TIM_Pulse = (HAL_ADC_DELAY_VALUE - HAL_ADC_SAMPLE_VALUE)/2U + 1U;
    TIM_OC4Init(HAL_MOTOR_PWM,&TIM_OCInitStructure);
    TIM_SelectOutputTrigger(HAL_MOTOR_PWM, TIM_TRGOSource_OC4Ref);
    
    HAL_MOTOR_PWM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
    HAL_MOTOR_PWM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
    HAL_MOTOR_PWM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF; 
    HAL_MOTOR_PWM_BDTRInitStructure.TIM_DeadTime = BSP_PWM_CalcDeadTimeReg_us(HAL_PWM_DEADTIME_TIME);
    HAL_MOTOR_PWM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;                    // 过流立即停车，封锁PWM  TIM_Break_Disable TIM_Break_Enable
    HAL_MOTOR_PWM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
    HAL_MOTOR_PWM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;  
    TIM_BDTRConfig(HAL_MOTOR_PWM, &HAL_MOTOR_PWM_BDTRInitStructure);
    
    TIM_ClearITPendingBit(HAL_MOTOR_PWM, TIM_IT_Break);      //清中断标志位

    TIM_ARRPreloadConfig(HAL_MOTOR_PWM, ENABLE);
    TIM_CtrlPWMOutputs(HAL_MOTOR_PWM, ENABLE);
}
