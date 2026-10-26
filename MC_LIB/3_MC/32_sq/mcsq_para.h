/**
 * @file    mcsq_para.h
 * @brief   方波控制参数
 * @author  CJYS
 * @date    2024/1/1
 *
 * 提供闭环使能、滤波器系数、偏置/顺风/自举/定位/刹车参数、
 * 换向系数、载频切换、PID 参数等宏定义，以及 ST_MCSQ_TASK 结构体。
 */

#ifndef MCSQ_PARA_H
#define MCSQ_PARA_H

/* ======================== 1. Includes ===================== */
#include "pmsm_para.h"
#include "mc_error.h"
#include "mcsq_ctrl.h"

/* ======================== 2. Defines ====================== */

/* ---- 闭环使能 ---- */
#define SPEED_CLOSE_EN                  (1U)   /**< 0 开环，1 转速环 */
#define I_BUS_CLOSE_EN                  (1U)   /**< 母线电流限流使能 */
#define P_BUS_CLOSE_EN                  (1U)   /**< 母线功率环使能（与电流环同时使能时仅电流环生效） */

/* ---- 滤波器系数（0~16384）---- */
#define IPHASE_FILTER_COEFF             (500)
#define FREQ_FILTER_COEFF               (500)
#define IBUS_FILTER_COEFF               (500)
#define VBUS_FILTER_COEFF               (500)
#define TEMP_FILTER_COEFF               (500)

/* ---- 电流采样偏置检测 ---- */
#define CURRENT_OFFSET_VOLTAGE_V        (HW_ADC_CURRENT_OFFSET)                                          /**< 偏置电压（V） */
#define CURRENT_OFFSET_lsb              (Q32U_)(CURRENT_OFFSET_VOLTAGE_V*HW_ADC_SCALE/HW_ADC_REF_VOLTAGE) /**< 偏置电压（lsb） */
#define CURRENT_OFFSET_TL_V             (0.2f)                                                           /**< 偏置偏差阈值（V） */
#define CURRENT_OFFSET_TL_lsb           (Q32U_)(CURRENT_OFFSET_TL_V*HW_ADC_SCALE/HW_ADC_REF_VOLTAGE)      /**< 偏置偏差阈值（lsb） */
#define CURRENT_OFFSET_MAX_lsb          (CURRENT_OFFSET_lsb + CURRENT_OFFSET_TL_lsb)                      /**< 偏置上限 */
#define CURRENT_OFFSET_MIN_lsb          (CURRENT_OFFSET_lsb - CURRENT_OFFSET_TL_lsb)                      /**< 偏置下限 */
#define CURRENT_OFFSET_COUNT            (20U)                                                            /**< 检测次数 */

/* ---- 顺风检测 ---- */
#define FREE_FLYING_TL_lsb              (150U)     /**< 电压阈值（lsb） */
#define FREE_FLYING_COUNT               (20U)      /**< 电压判断次数 */
#define FREE_FLYING_FAIL_COUNT          (1000U)    /**< 失败阈值 */
#define FREE_FLYING_FILTER              (2U)       /**< 滤波次数 */

/* ---- 电机静止检测 ---- */
#define BOOT_CHECK_TL_lsb               (150U)                    /**< 反电动势阈值 */
#define BOOT_CHECK_COUNT                (20U)                     /**< 判断次数 */
#define BOOT_CHECK_FAIL_COUNT           (1000U)                   /**< 失败阈值 */
#define BOOT_CHECK_DUTY                 (Q14I_DUTY_TO_PU(0.500f)) /**< 自举占空比 */

/* ---- 脉冲定位 ---- */
#define POSITION_DUTY                   (Q14I_DUTY_TO_PU(0.100f)) /**< 1kHz 定位占空比 */
#define POSITION_TL_lsb                 (800U)                    /**< 定位成功电流阈值 */

/* ---- 刹车占空比 ---- */
#define BRAKE_DUTY_RAMP_ADDSTEP         ( Q28I_DUTY_TO_PU(0.020f))  /**< 刹车占空比上升步长 */
#define BRAKE_DUTY_RAMP_SUBSTEP         (-Q28I_DUTY_TO_PU(0.020f))  /**< 刹车占空比下降步长 */

#define BRAKE_DUTY_CTRL_MAX             (Q14I_DUTY_TO_PU(0.400f))   /**< 刹车占空比上限 */
#define BRAKE_DUTY_CTRL_MIN             (Q14I_DUTY_TO_PU(0.200f))   /**< 刹车占空比下限 */

/* ---- 刹车时间 ---- */
#define NO_BRAKE_TIME                   (100U)   /**< 自由滑行时长（ms） */
#define SLOW_BRAKE_TIME                 (0U)     /**< 慢刹时长（ms） */
#define SHORT_BRAKE_TIME                (0U)     /**< 短接刹车时长（ms） */

/* ---- 换向系数 ---- */
#define DIAG_CROSS_RISE_TL              (Q32I_)(0.8000f * Q14U_MAX_F)   /**< 续流上升阈值 */
#define DIAG_CROSS_FALL_TL              (Q32I_)(0.2000f * Q14U_MAX_F)   /**< 续流下降阈值 */
#define FLUX_CROSS_RISE_TL              (Q32I_)(0.5000f * Q14U_MAX_F)   /**< 磁链上升阈值 */
#define FLUX_CROSS_FALL_TL              (Q32I_)(0.5000f * Q14U_MAX_F)   /**< 磁链下降阈值 */

#define DIAG_CROSS_FILTER               (1U)   /**< 续流滤波次数 */
#define FLUX_CROSS_FILTER               (1U)   /**< 磁链滤波次数 */
#define BEMF_CROSS_FILTER               (1U)   /**< BEMF 滤波次数 */

#define BEMF_CROSS_DELAY_COEFF          (1024U/6U)  /**< 0~8192，8192 为理论 30° 延迟 */

/* ---- 换向算法切换 ---- */
#define FLUX_TO_BEMF_FREQ               (Q14I_FREQ_TO_PU(0.35f * MOTOR_MAX_FREQ))   /**< 磁链→BEMF 切换频率 */
#define FLUX_TO_BEMF_NUM                (20U)                                       /**< 磁链→BEMF 切换计数 */

#define BEMF_TO_FLUX_FREQ               (Q14I_FREQ_TO_PU(0.30f * MOTOR_MAX_FREQ))   /**< BEMF→磁链切换频率 */
#define BEMF_TO_FLUX_NUM                (20U)                                       /**< BEMF→磁链切换计数 */

/* ---- 占空比斜坡 / 上下限 ---- */
#define DUTY_RAMP_ADDSTEP               ( Q28I_DUTY_TO_PU(0.020f))   /**< 占空比上升步长 */
#define DUTY_RAMP_SUBSTEP               (-Q28I_DUTY_TO_PU(0.020f))   /**< 占空比下降步长 */

#define DUTY_CTRL_MAX                   (Q14I_DUTY_TO_PU(1.000f))    /**< 占空比上限 */
#define DUTY_CTRL_MIN                   (Q14I_DUTY_TO_PU(0.050f))    /**< 占空比下限 */

/* ---- 载频切换 ---- */
#define PWM_FREQ_START                  (HW_PWM_INIT_VALUE)    /**< 初始化载频计数 */
#define PWM_FREQ_LOW                    (HW_PWM_LOW_VALUE)     /**< 低载频计数 */
#define PWM_FREQ_HIGH                   (HW_PWM_HIGH_VALUE)    /**< 高载频计数 */
#define PWM_FREQ_LOW_TO_HIGH_DUTY       (Q14I_DUTY_TO_PU(50.0f*HW_PWM_LOW_FREQ/1000.0f))   /**< 低频→高频阈值 */
#define PWM_FREQ_HIGH_TO_LOW_DUTY       (Q14I_DUTY_TO_PU(40.0f*HW_PWM_HIGH_FREQ/1000.0f))  /**< 高频→低频阈值 */

/* ---- 转速斜坡 ---- */
#define FREQ_RAMP_ADDSTEP               ( Q28I_FREQ_TO_PU(0.0001f * MOTOR_MAX_FREQ))
#define FREQ_RAMP_SUBSTEP               (-Q28I_FREQ_TO_PU(0.0001f * MOTOR_MAX_FREQ))

/* ---- 转速 PID ---- */
#define FREQ_PID_KP                     (Q32I_)(0.0001f * Q14U_MAX_F)
#define FREQ_PID_KI                     (Q32I_)(0.0010f * Q14U_MAX_F)
#define FREQ_PID_KD                     (Q32I_)(0.0001f * Q14U_MAX_F)
#define FREQ_PID_STEPMAX                ( Q28I_DUTY_TO_PU(0.010f))
#define FREQ_PID_STEPMIN                (-Q28I_DUTY_TO_PU(0.010f))
#define FREQ_PID_OUTMAX                 (DUTY_CTRL_MAX)
#define FREQ_PID_OUTMIN                 (DUTY_CTRL_MIN)

/* ---- 母线电流 PID ---- */
#define IBUS_PID_KP                     (Q32I_)(0.010f * Q14U_MAX_F)
#define IBUS_PID_KI                     (Q32I_)(0.010f * Q14U_MAX_F)
#define IBUS_PID_KD                     (Q32I_)(0.000f * Q14U_MAX_F)
#define IBUS_PID_STEPMAX                ( Q28I_DUTY_TO_PU(0.010f))
#define IBUS_PID_STEPMIN                (-Q28I_DUTY_TO_PU(0.010f))
#define IBUS_PID_OUTMAX                 (DUTY_CTRL_MAX)
#define IBUS_PID_OUTMIN                 (DUTY_CTRL_MIN)

/* ---- 相电流 PID ---- */
#define IPHASE_PID_KP                   (Q32I_)(0.010f * Q14U_MAX_F)
#define IPHASE_PID_KI                   (Q32I_)(0.010f * Q14U_MAX_F)
#define IPHASE_PID_KD                   (Q32I_)(0.000f * Q14U_MAX_F)
#define IPHASE_PID_STEPMAX              ( Q28I_DUTY_TO_PU(0.010f))
#define IPHASE_PID_STEPMIN              (-Q28I_DUTY_TO_PU(0.010f))
#define IPHASE_PID_OUTMAX               (DUTY_CTRL_MAX)
#define IPHASE_PID_OUTMIN               (DUTY_CTRL_MIN)

/* ---- 堵转保护 ---- */
#define MOTOR_STALL_SWITCH_COEFF        (0U)     /**< 换相波动堵转判断系数 */
#define MOTOR_STALL_ERROR_TIME          (350U)   /**< 堵转时间（ms） */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 方波电机任务结构体
 */
typedef struct {
    EM_MOTOR_STATE          Motor_Flow;      /**< 状态机 */
    UN_MOTOR_FLAG           Motor_Flag;      /**< 运行标志 */
    ST_MOTOR_API            Motor_API;       /**< 对外 API 数值 */

    ST_MOTOR_ERROR          Motor_Error;     /**< 故障状态 */

    ST_MCSQ_CONTROL         MCSQ_CTRL;       /**< 方波控制 */
} ST_MCSQ_TASK;

/* ======================== 4. Globals ====================== */
extern ST_MCSQ_TASK MCSQ_Task;   /**< 电机任务实例 */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  电机对外 API 参数刷新（方向 / 运行标志 / 转速 / 电流回读）
 * @param  pMotor  方波电机任务结构体指针
 */
void Motor_Parameter_API_SQ(ST_MCSQ_TASK* pMotor);

#endif /* MCSQ_PARA_H */
