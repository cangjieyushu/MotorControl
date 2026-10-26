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

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. ADC 数据读取 ================= */

/**
 * @brief  获取电机采样值（BEMF / 相电流）
 * @param  u_bemf   U 相 BEMF 原始 ADC 值
 * @param  v_bemf   V 相 BEMF 原始 ADC 值
 * @param  w_bemf   W 相 BEMF 原始 ADC 值
 * @param  current  相电流原始 ADC 值
 */
static inline void HAL_MC_ADC_Read_Motor(Q32U_* u_bemf, Q32U_* v_bemf, Q32U_* w_bemf, Q32U_* current)
{
    (*u_bemf)  = ((Q32U_)HW_MC_ADC->JDR1);
    (*v_bemf)  = ((Q32U_)HW_MC_ADC->JDR2);
    (*w_bemf)  = ((Q32U_)HW_MC_ADC->JDR3);
    (*current) = ((Q32U_)HW_MC_ADC->JDR4);
}

/**
 * @brief  获取电压温度采样值
 * @param  vbus  母线电压原始 ADC 值
 * @param  temp  温度原始 ADC 值
 */
static inline void HAL_MC_ADC_Read_System(Q32U_* vbus, Q32U_* temp)
{
    (*vbus) = ((Q32U_)HW_MC_ADC->DATA1);
    (*temp) = ((Q32U_)HW_MC_ADC->DATA2);
}

/**
 * @brief  软件触发 ADC（规则组）
 */
static inline void HAL_MC_ADC_Soft_Trigger(void)
{
    SET_BIT(HW_MC_ADC->CR2, ADC_CR2_JSWSTART);
}

/* ======================== 6. PWM 基础控制 ================= */

/**
 * @brief  延迟触发 ADC，避开米勒平台
 * @param  count  延迟触发采样计数器值（写入 TIMER0 CH3CV）
 */
static inline void HAL_MC_ADC_TrigTime_Set(Q32U_ count)
{
    TIM_Set_OC_CompareCH4(HW_MC_PWM, count);
}

/**
 * @brief  设置 PWM 载频
 * @param  count  PWM 载频控制计数器值（写入 TIMER0 CAR）
 */
static inline void HAL_MC_PWM_Freq_Set(Q32U_ count)
{
    TIM_Set_AutoReload(HW_MC_PWM, (count - 1U));
}

/**
 * @brief  预装载使能（CH0~CH3 比较影子）
 */
static inline void HAL_MC_PWM_Preload_Enable(void)
{
    TIM_Enable_OC_Preload(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL);
    TIM_Enable_OC_Preload(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL);
    TIM_Enable_OC_Preload(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL);
    TIM_Enable_OC_Preload(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL);
}

/**
 * @brief  预装载关闭（CH0~CH3 比较影子）
 */
static inline void HAL_MC_PWM_Preload_Disable(void)
{
    TIM_Disable_OC_Preload(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL);
    TIM_Disable_OC_Preload(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL);
    TIM_Disable_OC_Preload(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL);
    TIM_Disable_OC_Preload(HW_MC_PWM, HW_MC_PWM_TRIG_ADC_CHANNEL);
}

/* ======================== 7. 定位脉冲控制 ================= */

/**
 * @brief  定位脉冲（UpVn）：开 U 上 / V 下
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_POSITION_Up(Q32U_ ccr_value)
{
    HW_MC_PWM->CCR1 = ccr_value;
    HW_MC_PWM->CCR2 = ccr_value;
    HW_MC_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL | HW_MC_PWM_VL_CHANNEL | HW_MC_PWM_WL_CHANNEL);
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UL_CHANNEL | HW_MC_PWM_VH_CHANNEL | HW_MC_PWM_WH_CHANNEL);
}

/**
 * @brief  定位脉冲（WnUp）：开 W 下 / U 上
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_POSITION_Wn(Q32U_ ccr_value)
{
    HW_MC_PWM->CCR1 = ccr_value;
    HW_MC_PWM->CCR2 = ccr_value;
    HW_MC_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL | HW_MC_PWM_VH_CHANNEL | HW_MC_PWM_WL_CHANNEL);
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UL_CHANNEL | HW_MC_PWM_VL_CHANNEL | HW_MC_PWM_WH_CHANNEL);
}

/**
 * @brief  定位脉冲（Vp）：开 V 上
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_POSITION_Vp(Q32U_ ccr_value)
{
    HW_MC_PWM->CCR1 = ccr_value;
    HW_MC_PWM->CCR2 = ccr_value;
    HW_MC_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UL_CHANNEL | HW_MC_PWM_VH_CHANNEL | HW_MC_PWM_WL_CHANNEL);
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL | HW_MC_PWM_VL_CHANNEL | HW_MC_PWM_WH_CHANNEL);
}

/**
 * @brief  定位脉冲（Un）：开 U 下
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_POSITION_Un(Q32U_ ccr_value)
{
    HW_MC_PWM->CCR1 = ccr_value;
    HW_MC_PWM->CCR2 = ccr_value;
    HW_MC_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UL_CHANNEL | HW_MC_PWM_VH_CHANNEL | HW_MC_PWM_WH_CHANNEL);
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL | HW_MC_PWM_VL_CHANNEL | HW_MC_PWM_WL_CHANNEL);
}

/**
 * @brief  定位脉冲（Wp）：开 W 上
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_POSITION_Wp(Q32U_ ccr_value)
{
    HW_MC_PWM->CCR1 = ccr_value;
    HW_MC_PWM->CCR2 = ccr_value;
    HW_MC_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UL_CHANNEL | HW_MC_PWM_VL_CHANNEL | HW_MC_PWM_WH_CHANNEL);
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL | HW_MC_PWM_VH_CHANNEL | HW_MC_PWM_WL_CHANNEL);
}

/**
 * @brief  定位脉冲（Vn）：开 V 下
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_POSITION_Vn(Q32U_ ccr_value)
{
    HW_MC_PWM->CCR1 = ccr_value;
    HW_MC_PWM->CCR2 = ccr_value;
    HW_MC_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL | HW_MC_PWM_VL_CHANNEL | HW_MC_PWM_WH_CHANNEL);
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UL_CHANNEL | HW_MC_PWM_VH_CHANNEL | HW_MC_PWM_WL_CHANNEL);
}

/* ======================== 8. 同步整流控制 ================= */

/**
 * @brief  同步整流控制：UpVn（U 上 / V 下导通）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_UpVn(Q32U_ ccr_value)
{
    HW_MC_PWM->CCR1 = ccr_value;
    HW_MC_PWM->CCR2 = 0U;
    HW_MC_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL | HW_MC_PWM_UL_CHANNEL | HW_MC_PWM_VH_CHANNEL | HW_MC_PWM_VL_CHANNEL);
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL | HW_MC_PWM_WL_CHANNEL);
}

/**
 * @brief  同步整流控制：UpWn（U 上 / W 下导通）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_UpWn(Q32U_ ccr_value)
{
    HW_MC_PWM->CCR1 = ccr_value;
    HW_MC_PWM->CCR2 = 0U;
    HW_MC_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL | HW_MC_PWM_UL_CHANNEL | HW_MC_PWM_WH_CHANNEL | HW_MC_PWM_WL_CHANNEL);
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL | HW_MC_PWM_VL_CHANNEL);
}

/**
 * @brief  同步整流控制：VpWn（V 上 / W 下导通）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_VpWn(Q32U_ ccr_value)
{
    HW_MC_PWM->CCR1 = 0U;
    HW_MC_PWM->CCR2 = ccr_value;
    HW_MC_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL | HW_MC_PWM_VL_CHANNEL | HW_MC_PWM_WH_CHANNEL | HW_MC_PWM_WL_CHANNEL);
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL | HW_MC_PWM_UL_CHANNEL);
}

/**
 * @brief  同步整流控制：VpUn（V 上 / U 下导通）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_VpUn(Q32U_ ccr_value)
{
    HW_MC_PWM->CCR1 = 0U;
    HW_MC_PWM->CCR2 = ccr_value;
    HW_MC_PWM->CCR3 = 0U;
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL | HW_MC_PWM_UL_CHANNEL | HW_MC_PWM_VH_CHANNEL | HW_MC_PWM_VL_CHANNEL);
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_WH_CHANNEL | HW_MC_PWM_WL_CHANNEL);
}

/**
 * @brief  同步整流控制：WpUn（W 上 / U 下导通）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_WpUn(Q32U_ ccr_value)
{
    HW_MC_PWM->CCR1 = 0U;
    HW_MC_PWM->CCR2 = 0U;
    HW_MC_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL | HW_MC_PWM_UL_CHANNEL | HW_MC_PWM_WH_CHANNEL | HW_MC_PWM_WL_CHANNEL);
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL | HW_MC_PWM_VL_CHANNEL);
}

/**
 * @brief  同步整流控制：WpVn（W 上 / V 下导通）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_WpVn(Q32U_ ccr_value)
{
    HW_MC_PWM->CCR1 = 0U;
    HW_MC_PWM->CCR2 = 0U;
    HW_MC_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_VH_CHANNEL | HW_MC_PWM_VL_CHANNEL | HW_MC_PWM_WH_CHANNEL | HW_MC_PWM_WL_CHANNEL);
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL | HW_MC_PWM_UL_CHANNEL);
}

/**
 * @brief  同步整流控制：HOpen（开三相上 / 关三相下）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_HOpen(Q32U_ ccr_value)
{
    HW_MC_PWM->CCR1 = ccr_value;
    HW_MC_PWM->CCR2 = ccr_value;
    HW_MC_PWM->CCR3 = ccr_value;
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL | HW_MC_PWM_VH_CHANNEL | HW_MC_PWM_WH_CHANNEL);
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UL_CHANNEL | HW_MC_PWM_VL_CHANNEL | HW_MC_PWM_WL_CHANNEL);
}

/**
 * @brief  同步整流控制：LOpen（关三相上 / 开三相下）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_LOpen(Q32U_ ccr_value)
{
    HW_MC_PWM->CCR1 = ccr_value;
    HW_MC_PWM->CCR2 = ccr_value;
    HW_MC_PWM->CCR3 = ccr_value;
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL | HW_MC_PWM_VH_CHANNEL | HW_MC_PWM_WH_CHANNEL);
    TIM_Enable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UL_CHANNEL | HW_MC_PWM_VL_CHANNEL | HW_MC_PWM_WL_CHANNEL);
}

/**
 * @brief  同步整流控制：Close（六管全关）
 */
static inline void HAL_MC_HPWM_LPWM_Close(void)
{
    HW_MC_PWM->CCR1 = 0U;
    HW_MC_PWM->CCR2 = 0U;
    HW_MC_PWM->CCR3 = 0U;
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UH_CHANNEL | HW_MC_PWM_VH_CHANNEL | HW_MC_PWM_WH_CHANNEL);
    TIM_Disable_CC_Channel(HW_MC_PWM, HW_MC_PWM_UL_CHANNEL | HW_MC_PWM_VL_CHANNEL | HW_MC_PWM_WL_CHANNEL);
}

/* ======================== 9. 计数器读取 =================== */

/**
 * @brief  读取当前 PWM 计数器值
 * @return PWM 计数器值
 */
static inline Q32U_ HAL_MC_PWM_Count_Read(void)
{
    return (Q32U_)HW_MC_PWM->CNT;
}

/**
 * @brief  读取当前 HALL 换向计数器值
 * @return HALL 换向计数器值
 */
static inline Q32U_ HAL_MC_HALL_TIM_Count_Read(void)
{
    return (Q32U_)HW_MC_HTIM->CNT;
}

/* ======================== 10. SWITCH 计时控制 ============= */

/**
 * @brief  设置延迟换向计数器值并启动（进入中断）
 * @param  ccr_value  换向计数器值
 */
static inline void HAL_MC_SWITCH_TIM_Delay(Q32U_ ccr_value)
{
    HW_MC_STIM->CNT  = 0U;
    HW_MC_STIM->CCR1 = (Q32U_)ccr_value;
    SET_BIT(HW_MC_STIM->CR1, TIM_CR1_CEN);
}

/**
 * @brief  停止延迟换向计数器并清计数
 */
static inline void HAL_MC_SWITCH_TIM_Stop(void)
{
    CLEAR_BIT(HW_MC_STIM->CR1, TIM_CR1_CEN);
    HW_MC_STIM->CNT = 0U;
}

/* ======================== 11. 刹车标志管理 ================ */

/**
 * @brief  读取刹车标志位
 * @return 1 = 已触发刹车，0 = 未触发
 */
static inline Q32U_ HAL_MC_PWM_Brake_Read(void)
{
    return (Q32U_)TIM_Get_Flag(HW_MC_PWM, TIM_SR_BIF);
}

/**
 * @brief  清除刹车标志位
 */
static inline void HAL_MC_PWM_Brake_Clear(void)
{
    TIM_Clear_Flag(HW_MC_PWM, TIM_SR_BIF);
}

#endif /* HAL_MC_H */
