/**
 * @file    mcfoc_svpwm_t.h
 * @brief   FOC SVPWM 算法接口（定点）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef MCFOC_SVPWM_T_H
#define MCFOC_SVPWM_T_H

/* ======================== 1. Includes ===================== */
#include "math_ramp_t.h"
#include "mcfoc_pmsm_t.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief SVPWM 控制结构体（定点）
 */
typedef struct {
    ST_CHECK    FIVE_CHECK;             /**< 五段式切换确认 */

    Q32U_       O_Q32U_Five_Flag;       /**< 五段式目标标志 */
    Q32U_       O_Q32U_Five_Flag_Real;  /**< 五段式实际标志 */
    Q32U_       O_Q32U_Sector;          /**< 当前扇区（1~6） */

    Q32I_       O_Q14U_Dutya;           /**< A 相占空比（Q14） */
    Q32I_       O_Q14U_Dutyb;           /**< B 相占空比（Q14） */
    Q32I_       O_Q14U_Dutyc;           /**< C 相占空比（Q14） */

    Q32I_       O_Q14U_TaUp;            /**< A 相上桥臂触发时刻 */
    Q32I_       O_Q14U_TbUp;            /**< B 相上桥臂触发时刻 */
    Q32I_       O_Q14U_TcUp;            /**< C 相上桥臂触发时刻 */
    Q32I_       O_Q14U_TaDn;            /**< A 相下桥臂触发时刻 */
    Q32I_       O_Q14U_TbDn;            /**< B 相下桥臂触发时刻 */
    Q32I_       O_Q14U_TcDn;            /**< C 相下桥臂触发时刻 */
    Q32I_       O_Q14U_ADCTrigTime1;    /**< ADC 触发时刻 1 */
    Q32I_       O_Q14U_ADCTrigTime2;    /**< ADC 触发时刻 2 */

    Q32I_       P_Q14U_MaxDuty;         /**< 占空比上限 */
    Q32I_       P_Q14U_MidDuty;         /**< 占空比中值 */
    Q32I_       P_Q14U_MinDuty;         /**< 占空比下限 */
    Q32I_       P_Q14U_ADCSampleDuty;   /**< ADC 采样窗口 */

    Q32I_       P_Q32U_PWM_All_Count;   /**< PWM 计数满值 */
    Q32I_       P_Q14U_DeadTimeDuty;    /**< 死区占空比补偿量 */
    Q32I_       P_Q14I_DT_Current_TL;   /**< 死区补偿电流阈值 */
} ST_SVPWM_CONTROL_T;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  SVPWM 初始化
 * @param  pSVPWM  SVPWM 结构体指针
 */
void MCFOC_SVPWM_Init_T(ST_SVPWM_CONTROL_T* pSVPWM);

/**
 * @brief  五段式 / 七段式切换确认
 * @param  pSVPWM  SVPWM 结构体指针
 * @param  pPMSMe  电机电气量指针
 */
void MCFOC_SevFiv_Check_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe);

/**
 * @brief  三相采样电流重构（第三相）
 * @param  pSVPWM  SVPWM 结构体指针
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_ThreeShunt_Current_Cal_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe);

/**
 * @brief  三相采样 SVPWM 计算
 * @param  pSVPWM  SVPWM 结构体指针
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_SVPWM_ThreeShunt_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe);

/**
 * @brief  单电阻采样电流重构
 * @param  pSVPWM  SVPWM 结构体指针
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_OneShunt_Current_Cal_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe);

/**
 * @brief  单电阻采样 SVPWM 计算（含移相）
 * @param  pSVPWM  SVPWM 结构体指针
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_SVPWM_OneShunt_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe);

/**
 * @brief  占空比 → 电压 / 母线电流反算
 * @param  pSVPWM  SVPWM 结构体指针
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_SVPWM_Duty_Refactor_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe);

/**
 * @brief  死区电压补偿（叠加到占空比）
 * @param  pSVPWM  SVPWM 结构体指针
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_SVPWM_DeadTime_Compensate_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe);

#endif /* MCFOC_SVPWM_T_H */
