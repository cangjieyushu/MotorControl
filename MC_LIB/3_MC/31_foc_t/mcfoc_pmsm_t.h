/**
 * @file    mcfoc_pmsm_t.h
 * @brief   FOC 电机参数与坐标变换接口（定点）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef MCFOC_PMSM_T_H
#define MCFOC_PMSM_T_H

/* ======================== 1. Includes ===================== */
#include "math_angle_t.h"
#include "math_filter_t.h"
#include "math_ramp_t.h"
#include "math_table_t.h"
#include "math_check.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 电机滤波器组（均值 / 最大值）
 */
typedef struct {
    ST_MEAN_T   Mean_Freq;          /**< 转速均值 */
    ST_MEAN_T   Mean_Vbus;          /**< 母线电压均值 */
    ST_MEAN_T   Mean_Ibus;          /**< 母线电流均值 */
    ST_MEAN_T   Mean_Id;            /**< d 轴电流均值 */
    ST_MEAN_T   Mean_Iq;            /**< q 轴电流均值 */
    ST_MEAN_T   Mean_Ud;            /**< d 轴电压均值 */
    ST_MEAN_T   Mean_Uq;            /**< q 轴电压均值 */
    ST_MEAN_T   Mean_Es;            /**< 反电动势幅值均值 */

    ST_MAX_T    Max_Ia;             /**< A 相电流最大值 */
    ST_MAX_T    Max_Ib;             /**< B 相电流最大值 */
    ST_MAX_T    Max_Ic;             /**< C 相电流最大值 */

    ST_MEAN_T   Mean_Ibus_10ms;     /**< 母线电流 10ms 均值 */
    ST_MEAN_T   Mean_Is_1000ms;     /**< 相电流 1000ms 均值 */
} ST_PMSM_FILTER_T;

/**
 * @brief 电机电气量（定点）
 */
typedef struct {
    Q32I_       I_Q00I_DIR_Target;      /**< 目标方向（1 / -1） */
    Q32I_       I_Q14I_Ibus;            /**< 母线电流瞬时值 */

    Q32I_       I_Q12I_Ia_Data;         /**< A 相电流 ADC 原始值 */
    Q32I_       I_Q12I_Ib_Data;         /**< B 相电流 ADC 原始值 */
    Q32I_       I_Q12I_Ic_Data;         /**< C 相电流 ADC 原始值 */
    Q32I_       I_Q12I_Ia_Offset;       /**< A 相电流 ADC 偏置 */
    Q32I_       I_Q12I_Ib_Offset;       /**< B 相电流 ADC 偏置 */
    Q32I_       I_Q12I_Ic_Offset;       /**< C 相电流 ADC 偏置 */

    Q32I_       I_Q12I_Ishunt_1_Data;   /**< 单电阻采样 1 原始值 */
    Q32I_       I_Q12I_Ishunt_2_Data;   /**< 单电阻采样 2 原始值 */
    Q32I_       I_Q12I_Ishunt_Offset;   /**< 单电阻 ADC 偏置 */

    Q32I_       I_Q14I_Ishunt[3];       /**< 单电阻三相重构电流 */
    Q32I_       V_Q14I_Ia;              /**< A 相电流（Q14） */
    Q32I_       V_Q14I_Ib;              /**< B 相电流（Q14） */
    Q32I_       V_Q14I_Ic;              /**< C 相电流（Q14） */
    Q32I_       V_Q14I_Ialfa;           /**< α 轴电流 */
    Q32I_       V_Q14I_Ibeta;           /**< β 轴电流 */
    Q32I_       V_Q14I_Ualfa;           /**< α 轴电压 */
    Q32I_       V_Q14I_Ubeta;           /**< β 轴电压 */

    ST_TRIG_T   TG_Triangle_Est;        /**< 估算角度三角量 */
    ST_TRIG_T   TG_Triangle_Comp;       /**< 补偿角度三角量 */
    ST_TRIG_T   TG_Triangle_Pre;        /**< 预测角度三角量 */

    Q32I_       V_Q14I_Sin_Real;        /**< 合成 sin（估算 + 补偿） */
    Q32I_       V_Q14I_Cos_Real;        /**< 合成 cos（估算 + 补偿） */
    Q32I_       V_Q14I_Id_Real;         /**< d 轴实际电流 */
    Q32I_       V_Q14I_Iq_Real;         /**< q 轴实际电流 */
    Q32I_       V_Q14I_Ud_Real;         /**< d 轴实际电压 */
    Q32I_       V_Q14I_Uq_Real;         /**< q 轴实际电压 */

    Q32I_       V_Q14I_Sin_Pre;         /**< 预测 sin */
    Q32I_       V_Q14I_Cos_Pre;         /**< 预测 cos */
    Q32I_       V_Q14I_Ia_Pre;          /**< 预测 A 相电流 */
    Q32I_       V_Q14I_Ib_Pre;          /**< 预测 B 相电流 */
    Q32I_       V_Q14I_Ic_Pre;          /**< 预测 C 相电流 */
    Q32I_       V_Q14I_Ualfa_Pre;       /**< 预测 α 轴电压 */
    Q32I_       V_Q14I_Ubeta_Pre;       /**< 预测 β 轴电压 */

    Q32I_       O_Q14I_Freq;            /**< 转速（Q14） */
    Q32I_       O_Q14I_Vbus;            /**< 母线电压 */
    Q32I_       O_Q14I_Is;              /**< 相电流幅值 */
    Q32I_       O_Q14I_Us;              /**< 相电压幅值 */
    Q32I_       O_Q14I_Es;              /**< 反电动势幅值 */
    Q32I_       O_Q14I_One_Over_Vbus;   /**< 1/Vbus */
    Q32I_       O_Q14I_Modulation_Rate; /**< 调制度 */
    Q32I_       O_Q14I_UsRef;           /**< 电压矢量限幅 */
    Q32I_       O_Q14I_Ibus_10ms;       /**< 母线电流 10ms 均值 */
    Q32I_       O_Q14I_Is_1000ms;       /**< 相电流 1000ms 均值 */

    Q32I_       P_Q14I_Modulation_Mode; /**< 调制模式系数 */
    Q32I_       P_Q14I_UsRef_Scale;     /**< 电压矢量缩放系数 */
    Q32I_       P_Q08U_Pre_Period;      /**< 预测拍数 */
} ST_PMSM_ELEC_T;

/**
 * @brief 电机参数运行量（定点）
 */
typedef struct {
    ST_RAMP_T   Ramp_PWM_FREQ;          /**< 载频斜坡 */
    ST_CHECK    PWM_FREQ_CHECK;         /**< 载频切换确认 */
    Q32U_       O_Q32U_Low_PWM_Flag;    /**< 低载频标志 */

    Q32I_       O_Q14I_Rs;              /**< 相电阻（运行值） */
    Q32I_       O_Q14I_Ld;              /**< d 轴电感（运行值） */
    Q32I_       O_Q14I_Lq;              /**< q 轴电感（运行值） */
    Q32I_       O_Q14I_Ls;              /**< 相电感（运行值） */
    Q32I_       O_Q14I_Flux;            /**< 永磁磁链（运行值） */
    Q32I_       O_Q14I_Ts;              /**< 采样周期（随载频变化） */

    Q32I_       O_Q14I_PWM_Freq_Coeff;  /**< 载频系数 */
    Q32I_       O_Q14I_PWM_Period_Coeff;/**< 载频倒数系数 */

    Q32I_       P_Q14I_Rs;              /**< 相电阻（标幺基准） */
    Q32I_       P_Q14I_Ld;              /**< d 轴电感（标幺基准） */
    Q32I_       P_Q14I_Lq;              /**< q 轴电感（标幺基准） */
    Q32I_       P_Q14I_Ls;              /**< 相电感（标幺基准） */
    Q32I_       P_Q14I_Flux;            /**< 永磁磁链（标幺基准） */
    Q32I_       P_Q14I_Ts;              /**< 采样周期基准 */

    TABLE_1D_T  TAB_Lq_Coeff;           /**< Lq 电流补偿表 */
    Q32I_       P_Q32U_PWM_FREQ_MAX;    /**< 载频上限 */
    Q32I_       P_Q32U_PWM_FREQ_MIN;    /**< 载频下限 */
} ST_PMSM_PARA_T;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  电机电气量初始化
 * @param  pPMSMe  电机电气量指针
 */
void MCFOC_PMSM_Para_Init_T(ST_PMSM_ELEC_T* pPMSMe);

/**
 * @brief  电机参数更新（滤波器、调制度、载频等）
 * @param  pPMSMf  电机滤波器组指针
 * @param  pPMSMe  电机电气量指针
 * @param  pPMSMa  电机参数运行量指针
 */
void MCFOC_PMSM_Para_Adapt_T(ST_PMSM_FILTER_T* pPMSMf, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa);

/**
 * @brief  Clark 变换（3 相 → αβ）
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_PMSM_Clark_T(ST_PMSM_ELEC_T* pPMSMe);

/**
 * @brief  Park 变换（αβ → dq）
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_PMSM_Park_T(ST_PMSM_ELEC_T* pPMSMe);

/**
 * @brief  Inverse Park 变换（dq → αβ，带预测补偿）
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_PMSM_Ipark_T(ST_PMSM_ELEC_T* pPMSMe);

/**
 * @brief  Inverse Clark 变换（αβ → 3 相）
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_PMSM_Iclark_T(ST_PMSM_ELEC_T* pPMSMe);

#endif /* MCFOC_PMSM_T_H */
