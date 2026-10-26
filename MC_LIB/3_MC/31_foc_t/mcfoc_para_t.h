/**
 * @file    mcfoc_para_t.h
 * @brief   FOC 电机控制参数初始化（定点）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef MCFOC_PARA_T_H
#define MCFOC_PARA_T_H

/* ======================== 1. Includes ===================== */
#include "pmsm_para.h"
#include "mc_error.h"
#include "mcfoc_est_t.h"
#include "mcfoc_svpwm_t.h"
#include "mcfoc_pmsm_t.h"
#include "mcfoc_loop_t.h"

/* ======================== 2. Defines ====================== */
/* ---- 载频切换转速 ---- */
#define MOTOR_PWM_FREQ_LOW                  ((Q32I_)(HW_PWM_HIGH_FREQ*1000.0f))     /* Hz，低载频 */
#define MOTOR_PWM_FREQ_HIGH                 ((Q32I_)(HW_PWM_HIGH_FREQ*1000.0f))     /* Hz，高载频 */
#define MOTOR_PWM_FREQ_TL                   (Q14I_FREQ_TO_PU(30.0f))                /* Hz，从高载频切换至低载频 */
#define MOTOR_PWM_FREQ_CLR                  (Q14I_FREQ_TO_PU(40.0f))                /* Hz，从低载频切换至高载频 */

/* ---- 电流采样偏置检测 ---- */
#define CURRENT_OFFSET_VOLTAGE_V            (HW_ADC_CURRENT_OFFSET)                                          /* V，电流采样偏置电压 */
#define CURRENT_OFFSET_lsb                  (Q32U_)(CURRENT_OFFSET_VOLTAGE_V*HW_ADC_SCALE/HW_ADC_REF_VOLTAGE) /* lsb，电流采样偏置 */
#define CURRENT_OFFSET_TL_lsb               (400U)                                                          /* lsb，电流采样偏置偏差阈值 */
#define CURRENT_OFFSET_MAX_lsb              (CURRENT_OFFSET_lsb + CURRENT_OFFSET_TL_lsb)                    /* lsb，电流采样偏置上限 */
#define CURRENT_OFFSET_MIN_lsb              (CURRENT_OFFSET_lsb - CURRENT_OFFSET_TL_lsb)                    /* lsb，电流采样偏置下限 */
#define CURRENT_OFFSET_NUM                  (20U)                                                           /* 电流采样偏置检测次数 */

/* ---- ALIGN ---- */
#define MOTOR_ALIGN_ID_TARGET               (Q14I_CURRENT_TO_PU(1.0f))                  /* A，Id目标值 */
#define MOTOR_ALIGN_IDRAMP_ADDSTEP          (Q28I_CURRENT_TO_PU(1.0f * MOTOR_LTs))      /* A/s，Id每秒增加步长 */
#define MOTOR_ALIGN_ANGLERAMP_ADDSTEP       (67108864 * MOTOR_LTs)        				/* rad/s，角度每秒增加步长 */
#define MOTOR_ALIGN_COUNT                   (1000U)                                     /* ms */

/* ---- IF ---- */
#define MOTOR_IF_IQRAMP_TARGET_1            (Q14I_CURRENT_TO_PU(1.0f))                  /* A，Iq目标值 */
#define MOTOR_IF_IQRAMP_TARGET_2            (Q14I_CURRENT_TO_PU(5.0f))                  /* A，Iq目标值 */
#define MOTOR_IF_IQRAMP_ADDSTEP_1           ( Q28I_CURRENT_TO_PU(0.5f * MOTOR_LTs))     /* A/s，Iq每秒增加步长 */
#define MOTOR_IF_IQRAMP_ADDSTEP_2           ( Q28I_CURRENT_TO_PU(2.0f * MOTOR_LTs))     /* A/s，Iq每秒增加步长 */
#define MOTOR_IF_IQRAMP_SUBSTEP             (-Q28I_CURRENT_TO_PU(0.5f * MOTOR_LTs))     /* A/s，Iq每秒减小步长 */
#define MOTOR_IF_IS_MIN                     (Q14I_CURRENT_TO_PU(2.0f))                  /* A，Is最小值 */
#define MOTOR_IF_IQ_MIN                     (Q14I_CURRENT_TO_PU(1.0f))                  /* A，Iq最小值，切闭环 */

#define MOTOR_IF_FREQRAMP_TARGET_1          (Q14I_FREQ_TO_PU(5.0f))                     /* Hz，IF速度目标值 */
#define MOTOR_IF_FREQRAMP_TARGET_2          (Q14I_FREQ_TO_PU(20.0f))                    /* Hz，IF速度目标值 */
#define MOTOR_IF_FREQRAMP_ADDSTEP_1         (Q28I_FREQ_TO_PU(1.0f * MOTOR_LTs))         /* Hz/s，IF速度每秒增加步长 */
#define MOTOR_IF_FREQRAMP_ADDSTEP_2         (Q28I_FREQ_TO_PU(10.0f * MOTOR_LTs))        /* Hz/s，IF速度每秒增加步长 */

#define MOTOR_IF_ANGLE_ERROR                (820)                                       /* rad，IF与观测器角度偏差允许切换值 */
#define MOTOR_IF_SWITCH_COUNT               (20U)                                       /* 次，OpenLoop→CloseLoop 切换判定计数 */

/* ---- 转速环 PID ---- */
#define MOTOR_FREQ_RAMP_ADDSTEP             (Q28I_FREQ_TO_PU( 20.0f * MOTOR_LTs))       /* Hz/s，closeloop 每秒增速步长 */
#define MOTOR_FREQ_RAMP_SUBSTEP             (Q28I_FREQ_TO_PU(-20.0f * MOTOR_LTs))       /* Hz/s，closeloop 每秒减速度步长 */

#define MOTOR_FREQ_PID_Coeff                (1.00f)                                     /* 转速环 PID 增益系数 */
#define MOTOR_FREQ_KP_GAIN                  ((Q32I_)(MOTOR_FREQ_PID_Coeff * MOTOR_CURRENT_PHASE_A / MOTOR_MAX_FREQ * F_BASE / I_BASE * 16384.0f))
#define MOTOR_FREQ_KI_GAIN                  ((Q32I_)(0.05f * MOTOR_CURRENT_PHASE_A * MOTOR_LTs * F_BASE / I_BASE * 16384.0f))
#define MOTOR_FREQ_KD_GAIN                  ((Q32I_)(0.0f))

#define MOTOR_FREQ_PID_MAX                  (Q14I_CURRENT_TO_PU( 0.5f * MOTOR_CURRENT_PHASE_A))   /* A，转速环输出 q 轴电流限幅 */
#define MOTOR_FREQ_PID_MIN                  (Q14I_CURRENT_TO_PU(-0.5f * MOTOR_CURRENT_PHASE_A))   /* A，转速环输出 q 轴电流限幅 */

/* ---- 电流 PID ---- */
#define MOTOR_CURRENT_PID_Coeff             (0.05f)                                     /* 电流环 P 增益系数 */
#define MOTOR_CURRENT_KP_GAIN               ((Q32I_)(MOTOR_CURRENT_PID_Coeff * MOTOR_Ls * MATH_2PI_F / MOTOR_HTs * I_BASE / V_BASE * 16384.0f))
#define MOTOR_CURRENT_KI_GAIN               ((Q32I_)(MOTOR_CURRENT_PID_Coeff * MOTOR_Rs * I_BASE / V_BASE * 16384.0f))
#define MOTOR_CURRENT_KD_GAIN               ((Q32I_)(0.0f))

/* ---- 观测器 PLL 系数 ---- */
#define MOTOR_PLL_Coeff                     (0.20f)
#define MOTOR_PLL_SPEED_LPF_COEFF           ((Q32I_)(0.05f * 16384.0f))                 /* 0~1，越小滤波越深 */
#define MOTOR_MAX_SRAD                      (MOTOR_MAX_FREQ * MATH_2PI_F)

/* ---- SMO 观测器 ---- */
#define MOTOR_SMO_H1                        ((Q32I_)(VOLTAGE_PU / CURRENT_PHASE_PU * 16384.0f))     /* 增益系数 */

#define MOTOR_SMO_PLL_KP                    ((Q32I_)(2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_SRAD * 2.0f / VOLTAGE_PU / F_BASE / MATH_2PI_F * 16384.0f))                        /* 锁相环比例系数 */
#define MOTOR_SMO_PLL_KI                    ((Q32I_)((MOTOR_PLL_Coeff*MOTOR_MAX_SRAD * MOTOR_PLL_Coeff*MOTOR_MAX_SRAD) * MOTOR_HTs * 2.0f / VOLTAGE_PU / F_BASE / MATH_2PI_F * 16384.0f))   /* 锁相环积分系数 */
#define MOTOR_SMO_PLL_KD                    ((Q32I_)(0.0f))                                                                                                                    /* 锁相环微分系数 */
#define MOTOR_SMO_PLL_MAX                   (Q14I_FREQ_TO_PU( 2.0f * MOTOR_MAX_FREQ))                                                                                        /* 锁相环最大输出 */
#define MOTOR_SMO_PLL_MIN                   (Q14I_FREQ_TO_PU(-2.0f * MOTOR_MAX_FREQ))                                                                                        /* 锁相环最小输出 */

/* ---- 磁链观测器 ---- */
#define MOTOR_FLUX_GAMMA                    ((Q32I_)(0.02f * VOLTAGE_PU / FLUX_PU * 16384.0f))      /* 增益系数 */

#define MOTOR_FLUX_PLL_KP                   ((Q32I_)(2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_FREQ / FLUX_PU / F_BASE / MATH_2PI_F * 16384.0f))                                      /* 锁相环比例系数 */
#define MOTOR_FLUX_PLL_KI                   ((Q32I_)((MOTOR_PLL_Coeff*MOTOR_MAX_SRAD * MOTOR_PLL_Coeff*MOTOR_MAX_SRAD) * MOTOR_HTs / FLUX_PU / F_BASE / MATH_2PI_F * 16384.0f))  /* 锁相环积分系数 */
#define MOTOR_FLUX_PLL_KD                   ((Q32I_)(0.0f))                                                                                                                    /* 锁相环微分系数 */
#define MOTOR_FLUX_PLL_MAX                  (Q14I_FREQ_TO_PU( 2.0f * MOTOR_MAX_FREQ))                                                                                        /* 锁相环最大输出 */
#define MOTOR_FLUX_PLL_MIN                  (Q14I_FREQ_TO_PU(-2.0f * MOTOR_MAX_FREQ))                                                                                        /* 锁相环最小输出 */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief FOC 电机任务总结构体（定点）
 */
typedef struct {
    EM_MOTOR_STATE              Motor_Flow;      /**< 电机状态机 */
    UN_MOTOR_FLAG               Motor_Flag;      /**< 电机运行标志 */
    ST_MOTOR_API                Motor_API;       /**< 对外 API 数值 */

    ST_MOTOR_ERROR              Motor_Error;     /**< 故障状态 */

    EM_MOTOR_LOOP_MODE          Motor_Loop_Mode; /**< 环路模式：ALIGN / OPEN / CLOSE */

    ST_PMSM_FILTER_T            PMSM_Filter;     /**< 电机滤波器组 */
    ST_PMSM_ELEC_T              PMSM_Elec;       /**< 电机电气量 */
    ST_PMSM_PARA_T              PMSM_Para;       /**< 电机参数运行量 */

    ST_MCFOC_OFFSET_T           MCFOC_Offset;    /**< 电流偏置自学习 */
    ST_ALIGN_CONTROL_T          Align_Ctrl;      /**< ALIGN 控制 */
    ST_IF_CONTROL_T             IF_Ctrl;         /**< IF 控制 */
    ST_FREQ_CONTROL_T           Freq_Ctrl;       /**< 速度环 */
    ST_CURRENT_CONTROL_T        Current_Ctrl;    /**< 电流环 */
    ST_SVPWM_CONTROL_T          SVPWM_Ctrl;      /**< SVPWM 控制 */

    ST_EMF_CONTROL_T            EMF_Ctrl;        /**< 反电动势观测器 */
    ST_SMO_CONTROL_T            SMO_Ctrl;        /**< 滑模观测器 */
    ST_FLUX_CONTROL_T           FLUX_Ctrl;       /**< 磁链观测器 */
} ST_MCFOC_TASK_T;

/* ======================== 4. Globals ====================== */
extern ST_MCFOC_TASK_T MCFOC_Task_T;

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  电机对外 API 参数刷新
 * @param  pMotor  电机任务结构体指针
 */
void Motor_Parameter_API_T(ST_MCFOC_TASK_T* pMotor);

#endif /* MCFOC_PARA_T_H */
