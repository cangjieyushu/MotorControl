/**
 * @file    mcfoc_pmsm_f.h
 * @brief   FOC 电机参数与坐标变换接口（浮点）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef MCFOC_PMSM_F_H
#define MCFOC_PMSM_F_H

/* ======================== 1. Includes ===================== */
#include "math_angle_f.h"
#include "math_filter_f.h"
#include "math_ramp_f.h"
#include "math_table_f.h"
#include "math_check.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 电机滤波器组（均值 / 最大值）
 */
typedef struct {
    ST_MEAN_F   Mean_Freq;          /**< 转速均值 */
    ST_MEAN_F   Mean_Vbus;          /**< 母线电压均值 */
    ST_MEAN_F   Mean_Ibus;          /**< 母线电流均值 */
    ST_MEAN_F   Mean_Id;            /**< d 轴电流均值 */
    ST_MEAN_F   Mean_Iq;            /**< q 轴电流均值 */
    ST_MEAN_F   Mean_Ud;            /**< d 轴电压均值 */
    ST_MEAN_F   Mean_Uq;            /**< q 轴电压均值 */
    ST_MEAN_F   Mean_Es;            /**< 反电动势幅值均值 */

    ST_MAX_F    Max_Ia;             /**< A 相电流最大值 */
    ST_MAX_F    Max_Ib;             /**< B 相电流最大值 */
    ST_MAX_F    Max_Ic;             /**< C 相电流最大值 */

    ST_MEAN_F   Mean_Ibus_10ms;     /**< 母线电流 10ms 均值 */
    ST_MEAN_F   Mean_Is_1000ms;     /**< 相电流 1000ms 均值 */
} ST_PMSM_FILTER_F;

/**
 * @brief 电机电气量（浮点）
 */
typedef struct {
    float       I_F_DIR_Target;     /**< 目标方向（1 / -1） */
    float       I_F_Ibus;           /**< 母线电流瞬时值 */

    Q32I_       I_Q12I_Ia_Data;     /**< A 相电流 ADC 原始值 */
    Q32I_       I_Q12I_Ib_Data;     /**< B 相电流 ADC 原始值 */
    Q32I_       I_Q12I_Ic_Data;     /**< C 相电流 ADC 原始值 */
    Q32I_       I_Q12I_Ia_Offset;   /**< A 相电流 ADC 偏置 */
    Q32I_       I_Q12I_Ib_Offset;   /**< B 相电流 ADC 偏置 */
    Q32I_       I_Q12I_Ic_Offset;   /**< C 相电流 ADC 偏置 */

    Q32I_       I_Q12I_Ishunt_1_Data;  /**< 单电阻采样 1 原始值 */
    Q32I_       I_Q12I_Ishunt_2_Data;  /**< 单电阻采样 2 原始值 */
    Q32I_       I_Q12I_Ishunt_Offset;  /**< 单电阻 ADC 偏置 */

    float       I_F_Ishunt[3];      /**< 单电阻三相重构电流 */
    float       V_F_Ia;             /**< A 相电流（标幺） */
    float       V_F_Ib;             /**< B 相电流（标幺） */
    float       V_F_Ic;             /**< C 相电流（标幺） */
    float       V_F_Ialfa;          /**< α 轴电流 */
    float       V_F_Ibeta;          /**< β 轴电流 */
    float       V_F_Ualfa;          /**< α 轴电压 */
    float       V_F_Ubeta;          /**< β 轴电压 */

    ST_TRIG_F   TG_Triangle_Est;    /**< 估算角度三角量 */
    ST_TRIG_F   TG_Triangle_Comp;   /**< 补偿角度三角量 */
    ST_TRIG_F   TG_Triangle_Pre;    /**< 预测角度三角量 */

    float       V_F_Sin_Real;       /**< 合成 sin（估算 + 补偿） */
    float       V_F_Cos_Real;       /**< 合成 cos（估算 + 补偿） */
    float       V_F_Id_Real;        /**< d 轴实际电流 */
    float       V_F_Iq_Real;        /**< q 轴实际电流 */
    float       V_F_Ud_Real;        /**< d 轴实际电压 */
    float       V_F_Uq_Real;        /**< q 轴实际电压 */

    float       V_F_Sin_Pre;        /**< 预测 sin */
    float       V_F_Cos_Pre;        /**< 预测 cos */
    float       V_F_Ia_Pre;         /**< 预测 A 相电流 */
    float       V_F_Ib_Pre;         /**< 预测 B 相电流 */
    float       V_F_Ic_Pre;         /**< 预测 C 相电流 */
    float       V_F_Ualfa_Pre;      /**< 预测 α 轴电压 */
    float       V_F_Ubeta_Pre;      /**< 预测 β 轴电压 */

    float       O_F_Freq;           /**< 转速（标幺） */
    float       O_F_Vbus;           /**< 母线电压 */
    float       O_F_Is;             /**< 相电流幅值 */
    float       O_F_Us;             /**< 相电压幅值 */
    float       O_F_Es;             /**< 反电动势幅值 */
    float       O_F_One_Over_Vbus;  /**< 1/Vbus */
    float       O_F_Modulation_Rate;/**< 调制度 */
    float       O_F_UsRef;          /**< 电压矢量限幅 */
    float       O_F_Ibus_10ms;      /**< 母线电流 10ms 均值 */
    float       O_F_Is_1000ms;      /**< 相电流 1000ms 均值 */

    float       P_F_Modulation_Mode;/**< 调制模式系数 */
    float       P_F_UsRef_Scale;    /**< 电压矢量缩放系数 */
    float       P_F_Pre_Period;     /**< 预测拍数 */
} ST_PMSM_ELEC_F;

/**
 * @brief 电机参数运行量（浮点）
 */
typedef struct {
    ST_RAMP_F   Ramp_PWM_FREQ;      /**< 载频斜坡 */
    ST_CHECK    PWM_FREQ_CHECK;     /**< 载频切换确认 */
    Q32U_       O_Q32U_Low_PWM_Flag;/**< 低载频标志 */

    float       O_F_Rs;             /**< 相电阻（运行值） */
    float       O_F_Ld;             /**< d 轴电感（运行值） */
    float       O_F_Lq;             /**< q 轴电感（运行值） */
    float       O_F_Ls;             /**< 相电感（运行值） */
    float       O_F_Flux;           /**< 永磁磁链（运行值） */
    float       O_F_Ts;             /**< 采样周期（随载频变化） */

    float       O_F_PWM_Freq_Coeff; /**< 载频系数 */
    float       O_F_PWM_Period_Coeff;/**< 载频倒数系数 */

    float       P_F_Rs;             /**< 相电阻（标幺基准） */
    float       P_F_Ld;             /**< d 轴电感（标幺基准） */
    float       P_F_Lq;             /**< q 轴电感（标幺基准） */
    float       P_F_Ls;             /**< 相电感（标幺基准） */
    float       P_F_Flux;           /**< 永磁磁链（标幺基准） */
    float       P_F_Ts;             /**< 采样周期基准 */

    TABLE_1D_F  TAB_Lq_Coeff;       /**< Lq 电流补偿表 */
    float       P_F_PWM_FREQ_MAX;   /**< 载频上限 */
    float       P_F_PWM_FREQ_MIN;   /**< 载频下限 */
} ST_PMSM_PARA_F;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  电机电气量初始化
 * @param  pPMSMe  电机电气量指针
 */
void MCFOC_PMSM_Para_Init_F(ST_PMSM_ELEC_F* pPMSMe);

/**
 * @brief  电机参数更新（滤波器、调制度、载频等）
 * @param  pPMSMf  电机滤波器组指针
 * @param  pPMSMe  电机电气量指针
 * @param  pPMSMa  电机参数运行量指针
 */
void MCFOC_PMSM_Para_Adapt_F(ST_PMSM_FILTER_F* pPMSMf, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa);

/**
 * @brief  Clark 变换（3 相 → αβ）
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_PMSM_Clark_F(ST_PMSM_ELEC_F* pPMSMe);

/**
 * @brief  Park 变换（αβ → dq）
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_PMSM_Park_F(ST_PMSM_ELEC_F* pPMSMe);

/**
 * @brief  Inverse Park 变换（dq → αβ，带预测补偿）
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_PMSM_Ipark_F(ST_PMSM_ELEC_F* pPMSMe);

/**
 * @brief  Inverse Clark 变换（αβ → 3 相）
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_PMSM_Iclark_F(ST_PMSM_ELEC_F* pPMSMe);

#endif /* MCFOC_PMSM_F_H */
