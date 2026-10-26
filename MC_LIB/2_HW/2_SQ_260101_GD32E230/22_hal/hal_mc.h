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
 * @note   GD32E230 注入组：IDATA0~3 按转换完成顺序存放
 */
static inline void HAL_MC_ADC_Read_Motor(Q32U_* u_bemf, Q32U_* v_bemf, Q32U_* w_bemf, Q32U_* current)
{
    (*u_bemf)  = ((Q32U_)ADC_IDATA0);
    (*v_bemf)  = ((Q32U_)ADC_IDATA1);
    (*w_bemf)  = ((Q32U_)ADC_IDATA2);
    (*current) = ((Q32U_)ADC_IDATA3);
}

/**
 * @brief  获取系统采样值（母线电压 / 外部温度）
 * @param  vbus  母线电压原始 ADC 值
 * @param  temp  外部温度原始 ADC 值
 * @note   规则组 DMA 缓冲区：[0] = 母线电压，[1] = 外部温度；取低 12 位
 */
static inline void HAL_MC_ADC_Read_System(Q32U_* vbus, Q32U_* temp)
{
    (*vbus) = (BSP_ADC_SYSTEM_BUFFER[0] & 0x00000FFFU);
    (*temp) = (BSP_ADC_SYSTEM_BUFFER[1] & 0x00000FFFU);
}

/**
 * @brief  软件触发 ADC（规则组）
 */
static inline void HAL_MC_ADC_Soft_Trigger(void)
{
    ADC_CTL1 |= ADC_CTL1_SWICST;
}

/* ======================== 6. PWM 基础控制 ================= */

/**
 * @brief  延迟触发 ADC，避开米勒平台
 * @param  count  延迟触发采样计数器值（写入 TIMER0 CH3CV）
 */
static inline void HAL_MC_ADC_TrigTime_Set(Q32U_ count)
{
    TIMER_CH3CV(HW_MC_PWM) = count;
}

/**
 * @brief  设置 PWM 载频
 * @param  count  PWM 载频控制计数器值（写入 TIMER0 CAR）
 */
static inline void HAL_MC_PWM_Freq_Set(Q32U_ count)
{
    TIMER_CAR(HW_MC_PWM) = (count - 1U);
}

/**
 * @brief  预装载使能（CH0~CH3 比较影子）
 */
static inline void HAL_MC_PWM_Preload_Enable(void)
{
    TIMER_CHCTL0(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL0_CH0COMSEN | TIMER_CHCTL0_CH1COMSEN);
    TIMER_CHCTL1(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL1_CH2COMSEN | TIMER_CHCTL1_CH3COMSEN);
}

/**
 * @brief  预装载关闭（CH0~CH3 比较影子）
 */
static inline void HAL_MC_PWM_Preload_Disable(void)
{
    TIMER_CHCTL0(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL0_CH0COMSEN | TIMER_CHCTL0_CH1COMSEN));
    TIMER_CHCTL1(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL1_CH2COMSEN | TIMER_CHCTL1_CH3COMSEN));
}

/* ======================== 7. 定位脉冲控制 ================= */

/**
 * @brief  定位脉冲（UpVn）：开 U 上 / V 下
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_POSITION_Up(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0NEN | TIMER_CHCTL2_CH1EN | TIMER_CHCTL2_CH2EN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN | TIMER_CHCTL2_CH1NEN | TIMER_CHCTL2_CH2NEN);
}

/**
 * @brief  定位脉冲（WnUp）：开 W 下 / U 上
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_POSITION_Wn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0NEN | TIMER_CHCTL2_CH1NEN | TIMER_CHCTL2_CH2EN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN | TIMER_CHCTL2_CH1EN | TIMER_CHCTL2_CH2NEN);
}

/**
 * @brief  定位脉冲（Vp）：开 V 上
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_POSITION_Vp(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN | TIMER_CHCTL2_CH1NEN | TIMER_CHCTL2_CH2EN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0NEN | TIMER_CHCTL2_CH1EN | TIMER_CHCTL2_CH2NEN);
}

/**
 * @brief  定位脉冲（Un）：开 U 下
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_POSITION_Un(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN | TIMER_CHCTL2_CH1NEN | TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0NEN | TIMER_CHCTL2_CH1EN | TIMER_CHCTL2_CH2EN);
}

/**
 * @brief  定位脉冲（Wp）：开 W 上
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_POSITION_Wp(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN | TIMER_CHCTL2_CH1EN | TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0NEN | TIMER_CHCTL2_CH1NEN | TIMER_CHCTL2_CH2EN);
}

/**
 * @brief  定位脉冲（Vn）：开 V 下
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_POSITION_Vn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0NEN | TIMER_CHCTL2_CH1EN | TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN | TIMER_CHCTL2_CH1NEN | TIMER_CHCTL2_CH2EN);
}

/* ======================== 8. 同步整流控制 ================= */

/**
 * @brief  同步整流控制：UpVn（U 上 / V 下导通）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_UpVn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = 0U;
    TIMER_CH2CV(HW_MC_PWM) = 0U;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH2EN | TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN | TIMER_CHCTL2_CH0NEN
                                      | TIMER_CHCTL2_CH1EN | TIMER_CHCTL2_CH1NEN);
}

/**
 * @brief  同步整流控制：UpWn（U 上 / W 下导通）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_UpWn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = 0U;
    TIMER_CH2CV(HW_MC_PWM) = 0U;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH1EN | TIMER_CHCTL2_CH1NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN | TIMER_CHCTL2_CH0NEN
                                      | TIMER_CHCTL2_CH2EN | TIMER_CHCTL2_CH2NEN);
}

/**
 * @brief  同步整流控制：VpWn（V 上 / W 下导通）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_VpWn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = 0U;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = 0U;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN | TIMER_CHCTL2_CH0NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH1EN | TIMER_CHCTL2_CH1NEN
                                      | TIMER_CHCTL2_CH2EN | TIMER_CHCTL2_CH2NEN);
}

/**
 * @brief  同步整流控制：VpUn（V 上 / U 下导通）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_VpUn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = 0U;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = 0U;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH2EN | TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN | TIMER_CHCTL2_CH0NEN
                                      | TIMER_CHCTL2_CH1EN | TIMER_CHCTL2_CH1NEN);
}

/**
 * @brief  同步整流控制：WpUn（W 上 / U 下导通）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_WpUn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = 0U;
    TIMER_CH1CV(HW_MC_PWM) = 0U;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH1EN | TIMER_CHCTL2_CH1NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN | TIMER_CHCTL2_CH0NEN
                                      | TIMER_CHCTL2_CH2EN | TIMER_CHCTL2_CH2NEN);
}

/**
 * @brief  同步整流控制：WpVn（W 上 / V 下导通）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_WpVn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = 0U;
    TIMER_CH1CV(HW_MC_PWM) = 0U;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN | TIMER_CHCTL2_CH0NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH1EN | TIMER_CHCTL2_CH1NEN
                                      | TIMER_CHCTL2_CH2EN | TIMER_CHCTL2_CH2NEN);
}

/**
 * @brief  同步整流控制：HOpen（开三相上 / 关三相下）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_HOpen(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0NEN | TIMER_CHCTL2_CH1NEN | TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN | TIMER_CHCTL2_CH1EN | TIMER_CHCTL2_CH2EN);
}

/**
 * @brief  同步整流控制：LOpen（关三相上 / 开三相下）
 * @param  ccr_value  PWM 占空比控制计数器值
 */
static inline void HAL_MC_HPWM_LPWM_LOpen(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN | TIMER_CHCTL2_CH1EN | TIMER_CHCTL2_CH2EN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0NEN | TIMER_CHCTL2_CH1NEN | TIMER_CHCTL2_CH2NEN);
}

/**
 * @brief  同步整流控制：Close（六管全关）
 */
static inline void HAL_MC_HPWM_LPWM_Close(void)
{
    TIMER_CH0CV(HW_MC_PWM) = 0U;
    TIMER_CH1CV(HW_MC_PWM) = 0U;
    TIMER_CH2CV(HW_MC_PWM) = 0U;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN  | TIMER_CHCTL2_CH1EN  | TIMER_CHCTL2_CH2EN
                                        | TIMER_CHCTL2_CH0NEN | TIMER_CHCTL2_CH1NEN | TIMER_CHCTL2_CH2NEN));
}

/* ======================== 9. 计数器读取 =================== */

/**
 * @brief  读取当前 PWM 计数器值
 * @return PWM 计数器值
 */
static inline Q32U_ HAL_MC_PWM_Count_Read(void)
{
    return TIMER_CNT(HW_MC_PWM);
}

/**
 * @brief  读取当前 HALL 换向计数器值
 * @return HALL 换向计数器值
 */
static inline Q32U_ HAL_MC_HALL_TIM_Count_Read(void)
{
    return TIMER_CNT(HW_MC_HTIM);
}

/* ======================== 10. SWITCH 计时控制 ============= */

/**
 * @brief  设置延迟换向计数器值并启动（进入中断）
 * @param  ccr_value  换向计数器值
 */
static inline void HAL_MC_SWITCH_TIM_Delay(Q32U_ ccr_value)
{
    TIMER_CNT(HW_MC_STIM)   = 0U;
    TIMER_CH0CV(HW_MC_STIM) = (Q32U_)ccr_value;
    TIMER_CTL0(HW_MC_STIM) |= (Q32U_)TIMER_CTL0_CEN;
}

/**
 * @brief  停止延迟换向计数器并清计数
 */
static inline void HAL_MC_SWITCH_TIM_Stop(void)
{
    TIMER_CTL0(HW_MC_STIM) &= ~(Q32U_)TIMER_CTL0_CEN;
    TIMER_CNT(HW_MC_STIM)   = 0U;
}

/* ======================== 11. 刹车标志管理 ================ */

/**
 * @brief  读取刹车标志位
 * @return 1 = 已触发刹车，0 = 未触发
 */
static inline Q32U_ HAL_MC_PWM_Brake_Read(void)
{
    return (Q32U_)timer_flag_get(HW_MC_PWM, TIMER_FLAG_BRK);
}

/**
 * @brief  清除刹车标志位
 */
static inline void HAL_MC_PWM_Brake_Clear(void)
{
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_BRK);
}

#endif /* HAL_MC_H */