/**
 * @file    mcfoc_est_f.h
 * @brief   FOC 速度角度观测器（浮点）
 * @author  CJYS
 * @date    2024/1/1
 *
 * 反电动势观测器、滑模观测器（SMO）、磁链观测器的浮点实现。
 */

#ifndef MCFOC_EST_F_H
#define MCFOC_EST_F_H

/* ======================== 1. Includes ===================== */
#include "math_angle_f.h"
#include "math_filter_f.h"
#include "math_pid_f.h"
#include "math_table_f.h"
#include "mcfoc_pmsm_f.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 反电动势观测器（浮点）
 */
typedef struct {
    ST_LPF_F FL_EMF_Ialfa_err;     /**< α 轴电流误差低通 */
    ST_LPF_F FL_EMF_Ibeta_err;     /**< β 轴电流误差低通 */

    float V_F_EMF_Ialfa_Last;      /**< 上一帧 α 轴电流 */
    float V_F_EMF_Ibeta_Last;      /**< 上一帧 β 轴电流 */

    float O_F_EMF_Ealfa;           /**< α 轴反电动势估计 */
    float O_F_EMF_Ebeta;           /**< β 轴反电动势估计 */

    float D_F_EMF_Rs;              /**< 相电阻 */
    float D_F_EMF_Ls_Over_Ts;      /**< Ls/Ts */
} ST_EMF_CONTROL_F;

/**
 * @brief 滑模观测器（SMO，浮点）
 */
typedef struct {
    ST_PID_POS_F PID_SMO_PLL;          /**< PLL 位置式 PID */
    ST_LPF_F     FL_SMO_FREQ;          /**< 转速低通 */
    ST_TRIG_F    TG_SMO_Triangle;      /**< 角度三角量 */
    ST_TRIG_F    TG_SMO_Triangle_Comp; /**< 补偿角度三角量 */

    float V_F_SMO_Aalfa;               /**< α 轴中间量 */
    float V_F_SMO_Abeta;               /**< β 轴中间量 */
    float V_F_SMO_Ealfa;               /**< α 轴切换函数 */
    float V_F_SMO_Ebeta;               /**< β 轴切换函数 */

    float D_F_SMO_H1_Set;              /**< 自适应 H1 */
    float D_F_SMO_Ts;                  /**< 采样周期 */
    float D_F_SMO_One_Over_Ld;         /**< 1/Ld */
    float D_F_SMO_Rs_Over_Ld;          /**< Rs/Ld */
    float D_F_SMO_Ld_Lq_Over_Ld;       /**< (Ld-Lq)/Ld */

    float P_F_SMO_H1;                  /**< H1 基础增益 */
    float P_F_SMO_PLL_Kp;              /**< PLL 基础 Kp */
    float P_F_SMO_PLL_Ki;              /**< PLL 基础 Ki */
    TABLE_1D_F TAB_SMO_H1_Coeff;       /**< H1 频率补偿表 */
    TABLE_1D_F TAB_SMO_Kp_Coeff;       /**< Kp 频率补偿表 */
    TABLE_1D_F TAB_SMO_Ki_Coeff;       /**< Ki 频率补偿表 */
    TABLE_2D_F TAB_SMO_Angle_Comp;     /**< 角度补偿表（频率×电流） */
} ST_SMO_CONTROL_F;

/**
 * @brief 磁链观测器（浮点）
 */
typedef struct {
    ST_PID_POS_F PID_FLUX_PLL;          /**< PLL 位置式 PID */
    ST_LPF_F     FL_FLUX_FREQ;          /**< 转速低通 */
    ST_TRIG_F    TG_FLUX_Triangle;      /**< 角度三角量 */
    ST_TRIG_F    TG_FLUX_Triangle_Comp; /**< 补偿角度三角量 */

    float V_F_FLUX_Xalfa;               /**< α 轴磁链 */
    float V_F_FLUX_Xbeta;               /**< β 轴磁链 */

    float D_F_FLUX_Gamma_Set;           /**< 自适应增益 */
    float D_F_FLUX_Ts;                  /**< 采样周期 */
    float D_F_FLUX_Rs;                  /**< 相电阻 */
    float D_F_FLUX_Ld;                  /**< d 轴电感 */
    float D_F_FLUX_Lq;                  /**< q 轴电感 */
    float D_F_FLUX_Flux;                /**< 永磁磁链 */

    float P_F_FLUX_Gamma;               /**< 基础增益 */
    float P_F_FLUX_PLL_Kp;              /**< PLL 基础 Kp */
    float P_F_FLUX_PLL_Ki;              /**< PLL 基础 Ki */
    TABLE_1D_F TAB_FLUX_Gamma_Coeff;    /**< 增益频率补偿表 */
    TABLE_1D_F TAB_FLUX_Kp_Coeff;       /**< Kp 频率补偿表 */
    TABLE_1D_F TAB_FLUX_Ki_Coeff;       /**< Ki 频率补偿表 */
    TABLE_2D_F TAB_FLUX_Angle_Comp;     /**< 角度补偿表（频率×电流） */
} ST_FLUX_CONTROL_F;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  反电动势观测器初始化
 * @param  pEMF  反电动势结构体指针
 */
void MCFOC_EST_EMF_Init_F(ST_EMF_CONTROL_F* pEMF);

/**
 * @brief  反电动势观测器参数更新
 * @param  pEMF    反电动势结构体指针
 * @param  pPMSMa  电机参数结构体指针
 */
void MCFOC_EST_EMF_Adapt_F(ST_EMF_CONTROL_F* pEMF, ST_PMSM_PARA_F* pPMSMa);

/**
 * @brief  反电动势观测器单帧计算
 * @param  pEMF    反电动势结构体指针
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_EST_EMF_Cal_F(ST_EMF_CONTROL_F* pEMF, ST_PMSM_ELEC_F* pPMSMe);

/**
 * @brief  滑模观测器初始化
 * @param  pSMO  滑模结构体指针
 */
void MCFOC_EST_SMO_Init_F(ST_SMO_CONTROL_F* pSMO);

/**
 * @brief  滑模观测器参数更新
 * @param  pSMO    滑模结构体指针
 * @param  pPMSMe  电机电气量指针
 * @param  pPMSMa  电机参数结构体指针
 */
void MCFOC_EST_SMO_Adapt_F(ST_SMO_CONTROL_F* pSMO, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa);

/**
 * @brief  滑模观测器单帧计算
 * @param  pSMO    滑模结构体指针
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_EST_SMO_Cal_F(ST_SMO_CONTROL_F* pSMO, ST_PMSM_ELEC_F* pPMSMe);

/**
 * @brief  磁链观测器初始化
 * @param  pFLUX  磁链结构体指针
 */
void MCFOC_EST_FLUX_Init_F(ST_FLUX_CONTROL_F* pFLUX);

/**
 * @brief  磁链观测器参数更新
 * @param  pFLUX   磁链结构体指针
 * @param  pPMSMe  电机电气量指针
 * @param  pPMSMa  电机参数结构体指针
 */
void MCFOC_EST_FLUX_Adapt_F(ST_FLUX_CONTROL_F* pFLUX, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa);

/**
 * @brief  磁链观测器单帧计算
 * @param  pFLUX   磁链结构体指针
 * @param  pPMSMe  电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_EST_FLUX_Cal_F(ST_FLUX_CONTROL_F* pFLUX, ST_PMSM_ELEC_F* pPMSMe);

#endif /* MCFOC_EST_F_H */
