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
 *         若 HSI 为 8 MHz（PLL=144MHz），系数改为 36.0
 *         编码向上取整，保证实际死区 ≥ 期望值
 *         期望值超过最大范围（约 14 μs @ 288 MHz / 28 μs @ 144 MHz）时返回 0xFF
 */
static uint8_t BSP_MC_PWM_CalcDeadTimeReg_us(float dt_us)
{
    uint32_t n;
    float    nf;

    if (dt_us <= 0.0f)
    {
        return 0U;
    }

    nf = dt_us * 36.0f;        /* ← 只需改这一处 */
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
    //SET CNT BASE
    TIM_Set_CounterMode(HW_MC_PWM, TIM_COUNTERMODE_UP);
    TIM_Set_Prescaler(HW_MC_PWM, ((uint32_t)HW_PWM_PRESCALER) - 1U);
    TIM_Set_AutoReload(HW_MC_PWM, (HW_PWM_INIT_VALUE-1U));
    TIM_Set_RepetitionCounter(HW_MC_PWM, 0U);

    //CH1 / CH1N
    TIM_Set_OC_Mode(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL, TIM_OCMODE_PWM1);
    TIM_Set_OC_Polarity(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL, TIM_OCPOLARITY_HIGH);
    TIM_Set_OC_Polarity(HW_MC_PWM, HW_MC_PWM_UL_CHANNEL, TIM_OCPOLARITY_HIGH);

    //CH2 / CH2N
    TIM_Set_OC_Mode(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL, TIM_OCMODE_PWM1);
    TIM_Set_OC_Polarity(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL, TIM_OCPOLARITY_HIGH);
    TIM_Set_OC_Polarity(HW_MC_PWM, HW_MC_PWM_VL_CHANNEL, TIM_OCPOLARITY_HIGH);

    //CH3 / CH3N
    TIM_Set_OC_Mode(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL, TIM_OCMODE_PWM1);
    TIM_Set_OC_Polarity(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL, TIM_OCPOLARITY_HIGH);
    TIM_Set_OC_Polarity(HW_MC_PWM, HW_MC_PWM_WL_CHANNEL, TIM_OCPOLARITY_HIGH);
    
    TIM_Set_OC_CompareCH1(HW_MC_PWM, 0U);
    TIM_Set_OC_CompareCH2(HW_MC_PWM, 0U);
    TIM_Set_OC_CompareCH3(HW_MC_PWM, 0U);
    
    //CH4
    TIM_Set_OC_Mode(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL, TIM_OCMODE_PWM1);
    TIM_Set_OC_Polarity(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL, TIM_OCPOLARITY_HIGH);
    TIM_Set_OC_CompareCH4(HW_MC_PWM, HW_ADC_DELAY_VALUE);
    
    //Preload
    TIM_Enable_OC_Preload(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL);
    TIM_Enable_OC_Preload(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL);
    TIM_Enable_OC_Preload(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL);
    TIM_Enable_OC_Preload(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL);
    
    /* Set Deadtime */
    TIM_Set_ClockDivision(HW_MC_PWM, TIM_CLOCKDIVISION_DIV1);
    TIM_Set_OC_DeadTime(HW_MC_PWM, BSP_MC_PWM_CalcDeadTimeReg_us(HW_PWM_DEADTIME_TIME));  //deadtime
    
    /*  BDTR   AF1*/
    /*comp1 out high break*/
    TIM_Config_BRK(HW_MC_PWM, TIM_BREAK_POLARITY_HIGH, TIM_BREAK_FILTER_FDIV4_N8, TIM_BREAK_AFMODE_INPUT);
    TIM_Disable_BreakInputSource(HW_MC_PWM,TIM_BREAK_INPUT_BKIN,TIM_AF_BKINE); //BKINE=0
    TIM_Set_BreakInputSourcePolarity(HW_MC_PWM,TIM_BREAK_INPUT_BKIN,TIM_AF_BKCMP1P,TIM_BKCMP_POLARITY_NoInvert);//BKCMPxP =0
    TIM_Enable_BreakInputSource(HW_MC_PWM,TIM_BREAK_INPUT_BKIN,TIM_AF_BKCMP1E); //BKCMPxE=1
  
    /*The channel pwm output can be selected to be affected by the brake input*/
    TIM_Enable_Break_Control(HW_MC_PWM);
    TIM_Set_CH1Break_Invalid(HW_MC_PWM);
    TIM_Set_CH2Break_Invalid(HW_MC_PWM);
    TIM_Set_CH3Break_Invalid(HW_MC_PWM);
    TIM_Disable_AOE(HW_MC_PWM);//AOE=0 
  
    /**********************************/
    /* Start output signal generation */
    /**********************************/
    /* Enable outputs OC1, OC1N, OC2, OC2N, OC3 and OC3N */
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL);

    //TIM_Enable_IT(HW_MC_PWM, TIM_DIER_BIE);
    TIM_Enable_IT(HW_MC_PWM, TIM_DIER_CC4IE);

    TIM_Enable_MOE(HW_MC_PWM);
    TIM_Enable_CEN(HW_MC_PWM);
}
