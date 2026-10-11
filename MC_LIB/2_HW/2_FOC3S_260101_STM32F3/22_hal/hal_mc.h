/*
*     File Name :                        hal_mc
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制HAL
*/


#ifndef HAL_MC_H
#define HAL_MC_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_clk.h"
#include "hw_map.h"
#include "hw_para.h"
#include "bsp_adc.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
/* CCER 使能位：
 * TIM8 有 CH1/CH2/CH3 及互补 CH1N/CH2N/CH3N，CH4 无互补输出
 * bit0  = CC1E   bit2  = CC1NE
 * bit4  = CC2E   bit6  = CC2NE
 * bit8  = CC3E   bit10 = CC3NE
 * CH4 只做内部触发，CC4E 保持关闭，避免占用 PC9
 */
#define HAL_PWM_CCER_EN_MASK        ((Q16U_)0x0555U)   /* ★ 不再用 0x5555 */


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数实现 ------------------------------*/
/*
Function: HM_ADC_Data_Read_Vbus
Description: 获取母线电压采样值（ADC1 规则组 DMA 搬运）
Input: 无
Output: vbus - 母线电压原始 ADC 值（12 位）
Author: CJYS
*/
static inline void HM_ADC_Data_Read_Vbus(Q32U_* vbus)
{
    /* 规则组：Rank1 = 温度，Rank2 = 母线电压 */
    (*vbus) = BSP_ADC_SYSTEM_BUFFER[1];      /* ★ 从 BSP_ADC_SYSTEM_BUFFER[1] 读 */
}

/*
Function: HM_ADC_Data_Read_Temp
Description: 获取外部温度采样值（ADC1 规则组 DMA 搬运）
Input: 无
Output: temp - 温度原始 ADC 值（12 位）
Author: CJYS
*/
static inline void HM_ADC_Data_Read_Temp(Q32U_* temp)
{
    (*temp) = BSP_ADC_SYSTEM_BUFFER[0];      /* Rank1 = 温度 */
}

/*
Function: HM_ADC_Data_Read_Three
Description: 三电阻读取 ADC 三相电流采样值
             （三 ADC 同步：U=ADC1, V=ADC2, W=ADC3）
Input: 无
Output: pADC_Ia / pADC_Ib / pADC_Ic - 三相电流原始 ADC 值（12 位）
Author: CJYS
*/
static inline void HM_ADC_Data_Read_Three(Q32U_* pADC_Ia, Q32U_* pADC_Ib, Q32U_* pADC_Ic)
{
    /* 三个 ADC 的注入数据由 JEOC 中断读取到 BSP_ADC_MOTOR_BUFFER */
    (*pADC_Ia) = HAL_MOTOR_ADC1->JDR1;    /* U 相 = ADC1 */
    (*pADC_Ib) = HAL_MOTOR_ADC2->JDR1;    /* V 相 = ADC2 */
    (*pADC_Ic) = HAL_MOTOR_ADC3->JDR1;    /* W 相 = ADC3 */
}

/*
Function: HM_ADC_Data_Read_One
Description: 单电阻读取 ADC 采样数据（保留接口，待实现）
*/
static inline void HM_ADC_Data_Read_One(Q32U_* pADC_I1, Q32U_* pADC_I2)
{
    /* TODO: 单电阻方案需两次触发 ADC，在 PWM 周期内不同时刻采样 */
}

/*
Function: HM_PWM_Output_Enable
Description: PWM 输出通道开通（上桥+下桥共 6 路）
Input: 无
Output: 无
Author: CJYS
*/
static inline void HM_PWM_Output_Enable(void)
{
    /* 使能 CH1/CH1N/CH2/CH2N/CH3/CH3N（不使能 CH4，避免占用 PC9）*/
    HAL_MOTOR_PWM->CCER |= HAL_PWM_CCER_EN_MASK;

    /* 使能主输出 MOE */
    HAL_MOTOR_PWM->BDTR |= (Q16U_)TIM_BDTR_MOE;
}

/*
Function: HM_PWM_Output_Disable
Description: PWM 输出通道关闭（先关占空比，再关 CCER，最后关 MOE）
Input: 无
Output: 无
Author: CJYS
*/
static inline void HM_PWM_Output_Disable(void)
{
    /* 先清零占空比，避免关断瞬间产生毛刺 */
    HAL_MOTOR_PWM->CCR1 = 0;
    HAL_MOTOR_PWM->CCR2 = 0;
    HAL_MOTOR_PWM->CCR3 = 0;

    /* 关闭 CH1/CH1N/CH2/CH2N/CH3/CH3N 输出使能 */
    HAL_MOTOR_PWM->CCER &= (Q16U_)~HAL_PWM_CCER_EN_MASK;

    /* 关闭主输出 MOE（硬件级封锁六路 PWM）*/
    HAL_MOTOR_PWM->BDTR &= (Q16U_)~TIM_BDTR_MOE;
}

/*
Function: HM_PWM_Duty_Set_Three
Description: 设置三相 PWM 占空比（三电阻方案）
Input: PWM_Count - 周期值（ARR + 1）
       Ta / Tb / Tc - 三相切换时间点（0~PWM_Count/2，中心对齐模式）
Author: CJYS
*/
static inline void HM_PWM_Duty_Set_Three(Q32U_ PWM_Count, Q32U_ Ta, Q32U_ Tb, Q32U_ Tc)
{
    HAL_MOTOR_PWM->ARR  = PWM_Count - 1U;
    HAL_MOTOR_PWM->CCR1 = Ta;
    HAL_MOTOR_PWM->CCR2 = Tb;
    HAL_MOTOR_PWM->CCR3 = Tc;
}

/*
Function: HM_PWM_Duty_Set_One
Description: 单电阻方案的 PWM 占空比（带移相，保留接口）
*/
static inline void HM_PWM_Duty_Set_One(Q32U_ Ta1, Q32U_ Ta2,
                                       Q32U_ Tb1, Q32U_ Tb2,
                                       Q32U_ Tc1, Q32U_ Tc2)
{
    /* TODO: 单电阻方案需要在上升/下降段使用不同的比较值 */
}

/*
Function: HM_ADC_TrigTime_Set
Description: 设置 ADC 触发时刻（TIM8_CH4 的 OC4REF，通过 CCR4 控制）
Input: trig_time - CNT 上升段触发 ADC 的时刻（0 ~ PWM_Count/2 范围内）
       （单电阻方案下可能需要两个时刻，此处只用一个）
Author: CJYS
*/
static inline void HM_ADC_TrigTime_Set(Q32U_ trig_time)
{
    /* TIM8 的 OC4REF 作为 TRGO 触发 ADC 注入组 */
    HAL_MOTOR_PWM->CCR4 = trig_time;
}

/*
Function: HM_Read_PWM_Brake_Flag
Description: 读取刹车标志位（TIM8 BKIN 触发后置位）
Return: 0 - 未触发；1 - 已触发
Author: CJYS
*/
static inline Q32U_ HM_Read_PWM_Brake_Flag(void)
{
    return (TIM_GetFlagStatus(HAL_MOTOR_PWM, TIM_FLAG_Break) != RESET) ? 1U : 0U;
}

/*
Function: HM_Clear_PWM_Brake_Flag
Description: 清除刹车标志位
Input: 无
Output: 无
Author: CJYS
*/
static inline void HM_Clear_PWM_Brake_Flag(void)
{
    TIM_ClearFlag(HAL_MOTOR_PWM, TIM_FLAG_Break);
}

#endif /* HAL_MC_H */
