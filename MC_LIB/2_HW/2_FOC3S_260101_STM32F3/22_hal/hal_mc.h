/**
 * @file    hal_mc.h
 * @brief   电机控制 HAL 层
 *          提供 ADC / PWM 的寄存器级操作接口
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef HAL_MC_H
#define HAL_MC_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_para.h"
#include "bsp_mc_adc.h"

/* ======================== 2. Defines ====================== */
/*
 * TIM8 CCER 输出使能掩码
 *   bit0  = CC1E   bit2  = CC1NE
 *   bit4  = CC2E   bit6  = CC2NE
 *   bit8  = CC3E   bit10 = CC3NE
 *   CH4 只做内部触发，CC4E 保持关闭，避免占用
 */
#define HW_MC_PWM_CCER_EN_MASK      ((Q16U_)0x0555U)

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. ADC 数据读取 ================= */

/**
 * @brief  读取母线电压
 * @param  vbus  输出指针
 * @note   F4 单 ADC：注入组 Seq4 = 母线电压（JDR4）
 */
static inline void HAL_MC_ADC_Read_Vbus(Q32U_* vbus)
{
    (*vbus) = HW_MC_ADC1->JDR2;
}

/**
 * @brief  读取外部温度
 * @param  temp  输出指针
 * @note   F4 单 ADC：规则组 Seq1 = 外部温度（DR）
 */
static inline void HAL_MC_ADC_Read_Temp(Q32U_* temp)
{
    (*temp) = HW_MC_ADC1->JDR3;
}

/**
 * @brief  读取三相电流
 * @param  pADC_Ia  U 相输出
 * @param  pADC_Ib  V 相输出
 * @param  pADC_Ic  W 相输出
 * @note   F4 单 ADC：注入组 Seq1/2/3 = U/V/W 相电流（JDR1/2/3）
 */
static inline void HAL_MC_ADC_Read_Three(Q32U_* pADC_Ia, Q32U_* pADC_Ib, Q32U_* pADC_Ic)
{
    (*pADC_Ia) = HW_MC_ADC1->JDR1;    /* U 相 = ADC1 */
    (*pADC_Ib) = HW_MC_ADC2->JDR1;    /* V 相 = ADC2 */
    (*pADC_Ic) = HW_MC_ADC3->JDR1;    /* W 相 = ADC4 */
}

/**
 * @brief  读取单电阻方案下的两路采样
 * @param  pADC_I1  采样点 1 输出
 * @param  pADC_I2  采样点 2 输出
 * @note   预留，待实现（单电阻方案需两次触发 ADC，在 PWM 周期内不同时刻采样）
 */
static inline void HAL_MC_ADC_Read_One(Q32U_* pADC_I1, Q32U_* pADC_I2)
{
    /* TODO: 单电阻方案需两次触发 ADC，在 PWM 周期内不同时刻采样 */
    (*pADC_I1) = 0U;
    (*pADC_I2) = 0U;
}

/* ======================== 6. PWM 输出控制 ================= */

/**
 * @brief  使能三相 PWM 输出
 * @note   使能 CH1/1N/2/2N/3/3N + 主输出 MOE
 */
static inline void HAL_MC_PWM_Output_Enable(void)
{
    /* 使能 CH1/CH1N/CH2/CH2N/CH3/CH3N */
    HW_MC_PWM->CCER |= HW_MC_PWM_CCER_EN_MASK;

    /* 使能主输出 MOE */
    HW_MC_PWM->BDTR |= (Q16U_)TIM_BDTR_MOE;
}

/**
 * @brief  关闭三相 PWM 输出
 * @note   先清零占空比 → 关 CCER → 关 MOE，避免关断瞬间产生毛刺
 */
static inline void HAL_MC_PWM_Output_Disable(void)
{
    /* 先清零占空比，避免关断瞬间产生毛刺 */
    HW_MC_PWM->CCR1 = 0U;
    HW_MC_PWM->CCR2 = 0U;
    HW_MC_PWM->CCR3 = 0U;

    /* 关闭 CH1/CH1N/CH2/CH2N/CH3/CH3N 输出使能 */
    HW_MC_PWM->CCER &= (Q16U_)~HW_MC_PWM_CCER_EN_MASK;

    /* 关闭主输出 MOE（硬件级封锁六路 PWM）*/
    HW_MC_PWM->BDTR &= (Q16U_)~TIM_BDTR_MOE;
}

/**
 * @brief  设置三相 PWM 占空比
 * @param  PWM_Count  PWM 周期计数值（ARR + 1）
 * @param  Ta         U 相比较值（CCR1）
 * @param  Tb         V 相比较值（CCR2）
 * @param  Tc         W 相比较值（CCR3）
 */
static inline void HAL_MC_PWM_Duty_Set_Three(Q32U_ PWM_Count, Q32U_ Ta, Q32U_ Tb, Q32U_ Tc)
{
    HW_MC_PWM->ARR  = PWM_Count - 1U;
    HW_MC_PWM->CCR1 = Ta;
    HW_MC_PWM->CCR2 = Tb;
    HW_MC_PWM->CCR3 = Tc;
}

/**
 * @brief  设置单电阻方案下的六段比较值
 * @param  Ta1   U 相上升段比较值
 * @param  Ta2   U 相下降段比较值
 * @param  Tb1   V 相上升段比较值
 * @param  Tb2   V 相下降段比较值
 * @param  Tc1   W 相上升段比较值
 * @param  Tc2   W 相下降段比较值
 * @note   预留，待实现（单电阻方案需在上升/下降段使用不同比较值）
 */
static inline void HAL_MC_PWM_Duty_Set_One(Q32U_ Ta1, Q32U_ Ta2, Q32U_ Tb1, Q32U_ Tb2, Q32U_ Tc1, Q32U_ Tc2)
{
    /* TODO: 单电阻方案需要在上升/下降段使用不同的比较值 */
    (void)Ta1; (void)Ta2;
    (void)Tb1; (void)Tb2;
    (void)Tc1; (void)Tc2;
}

/* ======================== 7. ADC 触发时刻调整 ============= */

/**
 * @brief  设置 ADC 注入组触发时刻（三电阻方案）
 * @param  trig_time  TIM8 OC4REF 比较值（CCR4）
 * @note   TIM8 的 OC4REF 作为 TRGO 触发 ADC 注入组
 */
static inline void HAL_MC_ADC_TrigTime_Set_Three(Q32U_ trig_time)
{
    /* TIM8 的 OC4REF 作为 TRGO 触发 ADC 注入组 */
    HW_MC_PWM->CCR4 = trig_time;
}

/**
 * @brief  设置单电阻方案下的两次触发时刻
 * @param  trig_time1  第一次触发时刻
 * @param  trig_time2  第二次触发时刻
 * @note   预留，待实现
 */
static inline void HAL_MC_ADC_TrigTime_Set_One(Q32U_ trig_time1, Q32U_ trig_time2)
{
    (void)trig_time1;
    (void)trig_time2;
}

/* ======================== 8. 刹车标志管理 ================= */

/**
 * @brief  读取刹车标志
 * @return 1 = 已触发刹车，0 = 未触发
 */
static inline Q32U_ HAL_MC_PWM_Brake_Read(void)
{
    return (TIM_GetFlagStatus(HW_MC_PWM, TIM_FLAG_Break) != RESET) ? 1U : 0U;
}

/**
 * @brief  清除刹车标志
 */
static inline void HAL_MC_PWM_Brake_Clear(void)
{
    TIM_ClearFlag(HW_MC_PWM, TIM_FLAG_Break);
}

#endif /* HAL_MC_H */
