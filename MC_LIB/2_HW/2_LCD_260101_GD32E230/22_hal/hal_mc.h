/*
*     File Name :                        hal_mc
*     Library/Module Name :              hal
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制 HAL 层
*                                        提供 ADC / PWM 的寄存器级操作接口
*/


#ifndef HAL_MC_H
#define HAL_MC_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_para.h"
#include "bsp_mc_adc.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. ADC 数据读取 -----------------------------*/
/*
Function: HAL_MC_ADC_Read_Motor
Description: 获取电机采样值
Input: 无
Output: u_bemf / v_bemf / w_bemf / current - 电机采样原始 ADC 值
Author: CJYS
*/
static inline void HAL_MC_ADC_Read_Motor(Q32U_* u_bemf, Q32U_* v_bemf, Q32U_* w_bemf, Q32U_* current)
{
    (*u_bemf) = ((Q32U_)ADC_IDATA0);
    (*v_bemf) = ((Q32U_)ADC_IDATA1);
    (*w_bemf) = ((Q32U_)ADC_IDATA2);
    (*current) = ((Q32U_)ADC_IDATA3);
}

/*
Function: HAL_MC_ADC_Read_System
Description: 获取电压温度采样值
Input: 无
Output: vbus - 母线电压原始 ADC 值；temp - 温度原始 ADC 值
Author: CJYS
*/
static inline void HAL_MC_ADC_Read_System(Q32U_* vbus, Q32U_* temp)
{
    (*vbus) = (BSP_ADC_SYSTEM_BUFFER[0] & 0x00000FFFU);
    (*temp) = (BSP_ADC_SYSTEM_BUFFER[1] & 0x00000FFFU);
}

/*
Function: HAL_MC_ADC_Soft_Trigger
Description: 软件触发 ADC
Input: 无
Output: 无
Author: CJYS
*/
static inline void HAL_MC_ADC_Soft_Trigger(void)
{
    ADC_CTL1 |= ADC_CTL1_SWICST;
}


/*-------------------------- 6. PWM 基础控制 ----------------------------*/
/*
Function: HAL_MC_ADC_TrigTime_Set
Description: 延迟触发 ADC，避开米勒平台
Input: count - 延迟触发采样计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_ADC_TrigTime_Set(Q32U_ count)
{
    TIMER_CH3CV(HW_MC_PWM) = count;
}

/*
Function: HAL_MC_PWM_Freq_Set
Description: 设置载频
Input: count - PWM 载频控制计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_PWM_Freq_Set(Q32U_ count)
{
    TIMER_CAR(HW_MC_PWM) = (count - 1U);
}

/*
Function: HAL_MC_PWM_Preload_Enable
Description: 预装载使能
Input: 无
Output: 无
Author: CJYS
*/
static inline void HAL_MC_PWM_Preload_Enable(void)
{
    TIMER_CHCTL0(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL0_CH0COMSEN|TIMER_CHCTL0_CH1COMSEN);
    TIMER_CHCTL1(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL1_CH2COMSEN|TIMER_CHCTL1_CH3COMSEN);
}

/*
Function: HAL_MC_PWM_Preload_Disable
Description: 预装载关闭
Input: 无
Output: 无
Author: CJYS
*/
static inline void HAL_MC_PWM_Preload_Disable(void)
{
    TIMER_CHCTL0(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL0_CH0COMSEN|TIMER_CHCTL0_CH1COMSEN));
    TIMER_CHCTL1(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL1_CH2COMSEN|TIMER_CHCTL1_CH3COMSEN));
}


/*-------------------------- 7. 定位脉冲控制 ----------------------------*/
/*
Function: HAL_MC_POSITION_Up
Description: 定位脉冲，开三管
Input: ccr_value - PWM 占空比控制计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_POSITION_Up(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2EN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2NEN);
}

/*
Function: HAL_MC_POSITION_Wn
Description: 定位脉冲，开三管
Input: ccr_value - PWM 占空比控制计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_POSITION_Wn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2EN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2NEN);
}

/*
Function: HAL_MC_POSITION_Vp
Description: 定位脉冲，开三管
Input: ccr_value - PWM 占空比控制计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_POSITION_Vp(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2EN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2NEN);
}

/*
Function: HAL_MC_POSITION_Un
Description: 定位脉冲，开三管
Input: ccr_value - PWM 占空比控制计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_POSITION_Un(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2EN);
}

/*
Function: HAL_MC_POSITION_Wp
Description: 定位脉冲，开三管
Input: ccr_value - PWM 占空比控制计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_POSITION_Wp(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2EN);
}

/*
Function: HAL_MC_POSITION_Vn
Description: 定位脉冲，开三管
Input: ccr_value - PWM 占空比控制计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_POSITION_Vn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2EN);
}


/*-------------------------- 8. 同步整流控制 ----------------------------*/
/*
Function: HAL_MC_HPWM_LPWM_UpVn
Description: 同步整流控制，UpVn 为导通 U 上和 V 下，其他以此类推；
             HOpen 为开三相上关三相下，LOpen 为关三相上开三相下，CLOSE 为六管全关
Input: ccr_value - PWM 占空比控制计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_HPWM_LPWM_UpVn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = 0U;
    TIMER_CH2CV(HW_MC_PWM) = 0U;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH2EN|TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH1NEN);
}

/*
Function: HAL_MC_HPWM_LPWM_UpWn
Description: 同步整流控制
Input: ccr_value - PWM 占空比控制计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_HPWM_LPWM_UpWn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = 0U;
    TIMER_CH2CV(HW_MC_PWM) = 0U;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH1NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH2EN|TIMER_CHCTL2_CH2NEN);
}

/*
Function: HAL_MC_HPWM_LPWM_VpWn
Description: 同步整流控制
Input: ccr_value - PWM 占空比控制计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_HPWM_LPWM_VpWn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = 0U;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = 0U;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH0NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2EN|TIMER_CHCTL2_CH2NEN);
}

/*
Function: HAL_MC_HPWM_LPWM_VpUn
Description: 同步整流控制
Input: ccr_value - PWM 占空比控制计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_HPWM_LPWM_VpUn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = 0U;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = 0U;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH2EN|TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH1NEN);
}

/*
Function: HAL_MC_HPWM_LPWM_WpUn
Description: 同步整流控制
Input: ccr_value - PWM 占空比控制计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_HPWM_LPWM_WpUn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = 0U;
    TIMER_CH1CV(HW_MC_PWM) = 0U;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH1NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH2EN|TIMER_CHCTL2_CH2NEN);
}

/*
Function: HAL_MC_HPWM_LPWM_WpVn
Description: 同步整流控制
Input: ccr_value - PWM 占空比控制计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_HPWM_LPWM_WpVn(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = 0U;
    TIMER_CH1CV(HW_MC_PWM) = 0U;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH0NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2EN|TIMER_CHCTL2_CH2NEN);
}

/*
Function: HAL_MC_HPWM_LPWM_HOpen
Description: 同步整流控制，开三相上关三相下
Input: ccr_value - PWM 占空比控制计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_HPWM_LPWM_HOpen(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2NEN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2EN);
}

/*
Function: HAL_MC_HPWM_LPWM_LOpen
Description: 同步整流控制，关三相上开三相下
Input: ccr_value - PWM 占空比控制计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_HPWM_LPWM_LOpen(Q32U_ ccr_value)
{
    TIMER_CH0CV(HW_MC_PWM) = ccr_value;
    TIMER_CH1CV(HW_MC_PWM) = ccr_value;
    TIMER_CH2CV(HW_MC_PWM) = ccr_value;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2EN));
    TIMER_CHCTL2(HW_MC_PWM) |= (Q32U_)(TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2NEN);
}

/*
Function: HAL_MC_HPWM_LPWM_Close
Description: 同步整流控制，六管全关
Input: 无
Output: 无
Author: CJYS
*/
static inline void HAL_MC_HPWM_LPWM_Close(void)
{
    TIMER_CH0CV(HW_MC_PWM) = 0U;
    TIMER_CH1CV(HW_MC_PWM) = 0U;
    TIMER_CH2CV(HW_MC_PWM) = 0U;
    TIMER_CHCTL2(HW_MC_PWM) &= (~(Q32U_)(TIMER_CHCTL2_CH0EN|TIMER_CHCTL2_CH1EN|TIMER_CHCTL2_CH2EN
                                            |TIMER_CHCTL2_CH0NEN|TIMER_CHCTL2_CH1NEN|TIMER_CHCTL2_CH2NEN));
}


/*-------------------------- 9. 计数器读取 ------------------------------*/
/*
Function: HAL_MC_PWM_Count_Read
Description: 读取当前 PWM 计数器值
Input: 无
Output: 无
Return: PWM 计数器值
Author: CJYS
*/
static inline Q32U_ HAL_MC_PWM_Count_Read(void)
{
   return TIMER_CNT(HW_MC_PWM);
}

/*
Function: HAL_MC_HALL_TIM_Count_Read
Description: 读取当前 HALL 换向计数器值
Input: 无
Output: 无
Return: HALL 换向计数器值
Author: CJYS
*/
static inline Q32U_ HAL_MC_HALL_TIM_Count_Read(void)
{
   return TIMER_CNT(HW_MC_HTIM);
}


/*-------------------------- 10. SWITCH 计时控制 ------------------------*/
/*
Function: HAL_MC_SWITCH_TIM_Delay
Description: 设置延迟换向计数器值，进入中断
Input: ccr_value - 换向计数器值
Output: 无
Author: CJYS
*/
static inline void HAL_MC_SWITCH_TIM_Delay(Q32U_ ccr_value)
{
    TIMER_CNT(HW_MC_STIM) = 0U;
    TIMER_CH0CV(HW_MC_STIM) = (Q32U_)ccr_value;
    TIMER_CTL0(HW_MC_STIM) |= (Q32U_)TIMER_CTL0_CEN;
}

/*
Function: HAL_MC_SWITCH_TIM_Stop
Description: 停止延迟换向计数器值，屏蔽中断
Input: 无
Output: 无
Author: CJYS
*/
static inline void HAL_MC_SWITCH_TIM_Stop(void)
{
    TIMER_CTL0(HW_MC_STIM) &= ~(Q32U_)TIMER_CTL0_CEN;
    TIMER_CNT(HW_MC_STIM) = 0U;
}


/*-------------------------- 11. 刹车标志管理 ---------------------------*/
/*
Function: HAL_MC_PWM_Brake_Read
Description: 读取刹车标志位
Input: 无
Output: 无
Return: 刹车标志状态
Author: CJYS
*/
static inline Q32U_ HAL_MC_PWM_Brake_Read(void)
{
    return (Q32U_)timer_flag_get(HW_MC_PWM, TIMER_FLAG_BRK);
}

/*
Function: HAL_MC_PWM_Brake_Clear
Description: 清除刹车标志位
Input: 无
Output: 无
Author: CJYS
*/
static inline void HAL_MC_PWM_Brake_Clear(void)
{
    timer_flag_clear(HW_MC_PWM, TIMER_FLAG_BRK);
}


#endif /* HAL_MC_H */
