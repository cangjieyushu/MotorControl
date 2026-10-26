/**
 * @file    mcfoc_est_t.h
 * @brief   FOC 速度角度观测器（定点）
 * @author  CJYS
 * @date    2024/1/1
 *
 * 反电动势观测器、滑模观测器（SMO）、磁链观测器的参数与接口。
 */

#ifndef MCFOC_EST_T_H
#define MCFOC_EST_T_H

/* ======================== 1. Includes ===================== */
#include "math_angle_t.h"
#include "math_filter_t.h"
#include "math_pid_t.h"
#include "math_table_t.h"
#include "mcfoc_pmsm_t.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 反电动势观测器（定点）
 */
typedef struct {
    ST_LPF_T FL_EMF_Ialfa_err;     /**< α 轴电流误差低通 */
    ST_LPF_T FL_EMF_Ibeta_err;     /**< β 轴电流误差低通 */

    Q32I_ V_Q14I_EMF_Ialfa_Last;   /**< 上一帧 α 轴电流 */
    Q32I_ V_Q14I_EMF_Ibeta_Last;   /**< 上一帧 β 轴电流 */

    Q32I_ O_Q14I_EMF_Ealfa;        /**< α 轴反电动势估计 */
    Q32I_ O_Q14I_EMF_Ebeta;        /**< β 轴反电动势估计 */

    Q32I_ D_Q14I_EMF_Rs;           /**< 相电阻（Q14） */
    Q32I_ D_Q10I_EMF_Ls_Over_Ts;   /**< Ls/Ts（Q10） */
} ST_EMF_CONTROL_T;

/**
 * @brief 滑模观测器（SMO，定点）
 */
typedef struct {
    ST_PID_POS_T PID_SMO_PLL;          /**< PLL 位置式 PID */
    ST_LPF_T     FL_SMO_FREQ;          /**< 转速低通 */
    ST_TRIG_T    TG_SMO_Triangle;      /**< 角度三角量 */
    ST_TRIG_T    TG_SMO_Triangle_Comp; /**< 补偿角度三角量 */

    Q32I_ V_Q28I_SMO_Angle_tmp;        /**< 角度累加（Q28） */
    Q32I_ V_Q28I_SMO_Aalfa;            /**< α 轴中间量（Q28） */
    Q32I_ V_Q28I_SMO_Abeta;            /**< β 轴中间量（Q28） */
    Q32I_ V_Q14I_SMO_Aalfa;            /**< α 轴中间量（Q14） */
    Q32I_ V_Q14I_SMO_Abeta;            /**< β 轴中间量（Q14） */
    Q32I_ V_Q14I_SMO_Ealfa;            /**< α 轴切换函数 */
    Q32I_ V_Q14I_SMO_Ebeta;            /**< β 轴切换函数 */

    Q32I_ D_Q14I_SMO_H1_Set;           /**< 自适应 H1（Q14） */
    Q32I_ D_Q14I_SMO_Ts;               /**< 采样周期 */
    Q32I_ D_Q10I_SMO_One_Over_Ld;      /**< 1/Ld（Q10） */
    Q32I_ D_Q10I_SMO_Rs_Over_Ld;       /**< Rs/Ld（Q10） */
    Q32I_ D_Q14I_SMO_Ld_Lq_Over_Ld;    /**< (Ld-Lq)/Ld（Q14） */

    Q32I_ P_Q14I_SMO_H1;               /**< H1 基础增益 */
    Q32I_ P_Q14I_SMO_PLL_Kp;           /**< PLL 基础 Kp */
    Q32I_ P_Q14I_SMO_PLL_Ki;           /**< PLL 基础 Ki */
    TABLE_1D_T TAB_SMO_H1_Coeff;       /**< H1 频率补偿表 */
    TABLE_1D_T TAB_SMO_Kp_Coeff;       /**< Kp 频率补偿表 */
    TABLE_1D_T TAB_SMO_Ki_Coeff;       /**< Ki 频率补偿表 */
    TABLE_2D_T TAB_SMO_Angle_Comp;     /**< 角度补偿表（频率×电流） */
} ST_SMO_CONTROL_T;

/**
 * @brief 磁链观测器（定点）
 */
typedef struct {
    ST_PID_POS_T PID_FLUX_PLL;          /**< PLL 位置式 PID */
    ST_LPF_T     FL_FLUX_FREQ;          /**< 转速低通 */
    ST_TRIG_T    TG_FLUX_Triangle;      /**< 角度三角量 */
    ST_TRIG_T    TG_FLUX_Triangle_Comp; /**< 补偿角度三角量 */

    Q32I_ V_Q28I_FLUX_Angle_tmp;        /**< 角度累加（Q28） */
    Q32I_ V_Q28I_FLUX_Xalfa;            /**< α 轴磁链 */
    Q32I_ V_Q28I_FLUX_Xbeta;            /**< β 轴磁链 */

    Q32I_ D_Q14I_FLUX_Gamma_Set;        /**< 自适应增益 */
    Q32I_ D_Q14I_FLUX_Ts;               /**< 采样周期 */
    Q32I_ D_Q14I_FLUX_Rs;               /**< 相电阻 */
    Q32I_ D_Q14I_FLUX_Ld;               /**< d 轴电感 */
    Q32I_ D_Q14I_FLUX_Lq;               /**< q 轴电感 */
    Q32I_ D_Q14I_FLUX_Flux;             /**< 永磁磁链 */

    Q32I_ P_Q14I_FLUX_Gamma;            /**< 基础增益 */
    Q32I_ P_Q14I_FLUX_PLL_Kp;           /**< PLL 基础 Kp */
    Q32I_ P_Q14I_FLUX_PLL_Ki;           /**< PLL 基础 Ki */
    TABLE_1D_T TAB_FLUX_Gamma_Coeff;    /**< 增益频率补偿表 */
    TABLE_1D_T TAB_FLUX_Kp_Coeff;       /**< Kp 频率补偿表 */
    TABLE_1D_T TAB_FLUX_Ki_Coeff;       /**< Ki 频率补偿表 */
    TABLE_2D_T TAB_FLUX_Angle_Comp;     /**< 角度补偿表（频率×电流） */
} ST_FLUX_CONTROL_T;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  反电动势观测器初始化
 * @param  pEMF  反电动势结构体指针
 */
void MCFOC_EST_EMF_Init_T(ST_EMF_CONTROL_T* pEMF);

/**
 * @brief  反电动势观测器参数更新
 * @param  pEMF    反电动势结构体指针
 * @param  pPMSMa  电机参数结构体指针
 */
void MCFOC_EST_EMF_Adapt_T(ST_EMF_CONTROL_T* pEMF, ST_PMSM_PARA_T* pPMSMa);

/**
 * @brief  反电动势观测器单帧计算
 * @param  pEMF    反电动势结构体指针
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_EST_EMF_Cal_T(ST_EMF_CONTROL_T* pEMF, ST_PMSM_ELEC_T* pPMSMe);

/**
 * @brief  滑模观测器初始化
 * @param  pSMO  滑模结构体指针
 */
void MCFOC_EST_SMO_Init_T(ST_SMO_CONTROL_T* pSMO);

/**
 * @brief  滑模观测器参数更新
 * @param  pSMO    滑模结构体指针
 * @param  pPMSMe  电机电气量指针
 * @param  pPMSMa  电机参数结构体指针
 */
void MCFOC_EST_SMO_Adapt_T(ST_SMO_CONTROL_T* pSMO, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa);

/**
 * @brief  滑模观测器单帧计算
 * @param  pSMO    滑模结构体指针
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_EST_SMO_Cal_T(ST_SMO_CONTROL_T* pSMO, ST_PMSM_ELEC_T* pPMSMe);

/**
 * @brief  磁链观测器初始化
 * @param  pFLUX  磁链结构体指针
 */
void MCFOC_EST_FLUX_Init_T(ST_FLUX_CONTROL_T* pFLUX);

/**
 * @brief  磁链观测器参数更新
 * @param  pFLUX   磁链结构体指针
 * @param  pPMSMe  电机电气量指针
 * @param  pPMSMa  电机参数结构体指针
 */
void MCFOC_EST_FLUX_Adapt_T(ST_FLUX_CONTROL_T* pFLUX, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa);

/**
 * @brief  磁链观测器单帧计算
 * @param  pFLUX   磁链结构体指针
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_EST_FLUX_Cal_T(ST_FLUX_CONTROL_T* pFLUX, ST_PMSM_ELEC_T* pPMSMe);

#endif /* MCFOC_EST_T_H */
