/**
 * @file    mc_error.h
 * @brief   电机故障检测与确认
 * @author  CJYS
 * @date    2024/1/1
 *
 * 定义故障位图、故障输入量、各故障的时间确认结构体，
 * 并提供 1ms 任务、电流中断任务、故障清除等接口。
 */

#ifndef MC_ERROR_H
#define MC_ERROR_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"
#include "math_check.h"

/* ======================== 2. Defines ====================== */

/* ---- 电压保护 ---- */
#define OVER_VOLTAGE_PROTECT_LEVEL_TL           (Q14I_VOLTAGE_TO_PU(28.0f))    /**< 过压保护阈值（V） */
#define OVER_VOLTAGE_PROTECT_LEVEL_TIME         (100U)                         /**< 过压保护时间（ms） */
#define OVER_VOLTAGE_CLEAR_LEVEL_TL             (Q14I_VOLTAGE_TO_PU(26.0f))    /**< 过压恢复阈值（V） */
#define OVER_VOLTAGE_CLEAR_LEVEL_TIME           (100U)                         /**< 过压恢复时间（ms） */

#define LOW_VOLTAGE_PROTECT_LEVEL_TL            (Q14I_VOLTAGE_TO_PU(10.0f))    /**< 低压保护阈值（V） */
#define LOW_VOLTAGE_PROTECT_LEVEL_TIME          (100U)                         /**< 低压保护时间（ms） */

#define FAST_OVER_VOLTAGE_PROTECT_LEVEL_TL      (Q14I_VOLTAGE_TO_PU(32.0f))    /**< 快速过压保护阈值（V） */
#define FAST_OVER_VOLTAGE_PROTECT_LEVEL_TIME    (5U)                           /**< 快速过压保护时间 */

/* ---- 电流保护 ---- */
#define CURRENT_PROTECT_LEVEL                   3                              /**< 过流保护档位 */
#define CURRENT_PROTECT_LEVEL_1_TL              (Q14I_CURRENT_TO_PU(40.0f))    /**< 过流保护阈值（A） */
#define CURRENT_PROTECT_LEVEL_1_TIME            (100U)                         /**< 过流保护时间（ms） */

#define CURRENT_PROTECT_LEVEL_2_TL              (Q14I_CURRENT_TO_PU(35.0f))    /**< 过流保护阈值（A） */
#define CURRENT_PROTECT_LEVEL_2_TIME            (1000U)                        /**< 过流保护时间（ms） */

#define CURRENT_PROTECT_LEVEL_3_TL              (Q14I_CURRENT_TO_PU(30.0f))    /**< 过流保护阈值（A） */
#define CURRENT_PROTECT_LEVEL_3_TIME            (10000U)                       /**< 过流保护时间（ms） */

#define FAST_CURRENT_PROTECT_LEVEL_TL           (Q14I_CURRENT_TO_PU(50.0f))    /**< 快速过流保护阈值（A） */
#define FAST_CURRENT_PROTECT_LEVEL_TIME         (5U)                           /**< 快速过流保护时间 */

/* ---- 温度保护 ---- */
#define OVER_TEMP_PROTECT_LEVEL_TL              ((Q32U_)(400.0f))              /**< 过温保护阈值（lsb） */
#define OVER_TEMP_PROTECT_LEVEL_TIME            (1000U)                        /**< 过温保护时间（ms） */
#define OVER_TEMP_CLEAR_LEVEL_TL                ((Q32U_)(600.0f))              /**< 过温恢复阈值（lsb） */
#define OVER_TEMP_CLEAR_LEVEL_TIME              (1000U)                        /**< 过温恢复时间（ms） */

#define LOW_TEMP_PROTECT_LEVEL_TL               ((Q32U_)(4000.0f))             /**< 低温保护阈值（lsb） */
#define LOW_TEMP_PROTECT_LEVEL_TIME             (1000U)                        /**< 低温保护时间（ms） */
#define LOW_TEMP_CLEAR_LEVEL_TL                 ((Q32U_)(3800.0f))             /**< 低温恢复阈值（lsb） */
#define LOW_TEMP_CLEAR_LEVEL_TIME               (1000U)                        /**< 低温恢复时间（ms） */

/* ---- 速度保护 ---- */
#define OVER_SPEED_PROTECT_LEVEL_TL             (Q14I_FREQ_TO_PU(MOTOR_SPEED_TO_FREQ(125000.0f)))  /**< 超速保护阈值（rpm） */
#define OVER_SPEED_PROTECT_LEVEL_TIME           (1000U)                                            /**< 超速保护时间（ms） */

#define LOW_SPEED_PROTECT_LEVEL_TL              (Q14I_FREQ_TO_PU(MOTOR_SPEED_TO_FREQ(0.0f)))       /**< 低速保护阈值（rpm） */
#define LOW_SPEED_PROTECT_LEVEL_TIME            (10000U)                                           /**< 低速保护时间（ms） */

/* ---- 功率 / 母线保护 ---- */
#define OVER_POWER_PROTECT_LEVEL_TL             (Q14I_VOLTAGE_TO_PU(24.0f) * Q14I_CURRENT_TO_PU(15.0f))  /**< 过功率保护阈值（W） */
#define OVER_POWER_PROTECT_LEVEL_TIME           (1000U)                                                   /**< 过功率保护时间（ms） */
#define OVER_IBUS_PROTECT_LEVEL_TL              (Q14I_CURRENT_TO_PU(30.0f))                               /**< 过母线电流阈值（A） */
#define OVER_IBUS_PROTECT_LEVEL_TIME            (1000U)                                                   /**< 过母线电流时间（ms） */

/* ---- MOS 损坏 ---- */
#define MOS_ERROR_COUNT                         (3U)  /**< MOS 损坏次数阈值 */

/* ---- 缺相保护 ---- */
#define PHASE_LACK_IPHASE_PROTECT_LEVEL_TL      (Q14I_CURRENT_TO_PU(5.0f))   /**< 缺相相电流阈值（A） */
#define PHASE_LACK_ISREF_PROTECT_LEVEL_TL       (Q14I_CURRENT_TO_PU(30.0f))  /**< 缺相 IsRef 阈值（A） */
#define PHASE_LACK_PROTECT_LEVEL_TIME           (5000U)                      /**< 缺相保护时间（ms） */

/* ---- 堵转保护 ---- */
#define ROTOR_LOCK_ISREF_PROTECT_LEVEL_TL       (Q14I_CURRENT_TO_PU(30.0f))                             /**< 堵转 IsRef 阈值（A） */
#define ROTOR_LOCK_SPEED_PROTECT_LEVEL_TL       (Q14I_FREQ_TO_PU(MOTOR_SPEED_TO_FREQ(100.0f)))          /**< 堵转速度阈值（rpm） */
#define ROTOR_LOCK_PROTECT_LEVEL_TIME           (5000U)                                                 /**< 堵转保护时间（ms） */

/* ---- 失步保护 ---- */
#define LOSS_STEP_ES_PROTECT_LEVEL_TL           (Q14I_VOLTAGE_TO_PU(0.1f))                              /**< 失步 Es 阈值（V） */
#define LOSS_STEP_SPEED_PROTECT_LEVEL_TL        (Q14I_FREQ_TO_PU(MOTOR_SPEED_TO_FREQ(1000.0f)))         /**< 失步速度阈值（rpm） */
#define LOSS_STEP_PROTECT_LEVEL_TIME            (5000U)                                                 /**< 失步保护时间（ms） */




///* ---- 电压保护 ---- */
//#define OVER_VOLTAGE_PROTECT_LEVEL_TL           (Q14I_VOLTAGE_TO_PU(380.0f))   /**< 过压保护阈值（V） */
//#define OVER_VOLTAGE_PROTECT_LEVEL_TIME         (100U)                         /**< 过压保护时间（ms） */
//#define OVER_VOLTAGE_CLEAR_LEVEL_TL             (Q14I_VOLTAGE_TO_PU(360.0f))   /**< 过压恢复阈值（V） */
//#define OVER_VOLTAGE_CLEAR_LEVEL_TIME           (100U)                         /**< 过压恢复时间（ms） */

//#define LOW_VOLTAGE_PROTECT_LEVEL_TL            (Q14I_VOLTAGE_TO_PU(210.0f))   /**< 低压保护阈值（V） */
//#define LOW_VOLTAGE_PROTECT_LEVEL_TIME          (100U)                         /**< 低压保护时间（ms） */

//#define FAST_OVER_VOLTAGE_PROTECT_LEVEL_TL      (Q14I_VOLTAGE_TO_PU(420.0f))   /**< 快速过压保护阈值（V） */
//#define FAST_OVER_VOLTAGE_PROTECT_LEVEL_TIME    (5U)                           /**< 快速过压保护时间 */

///* ---- 电流保护 ---- */
//#define CURRENT_PROTECT_LEVEL                   3                              /**< 过流保护档位 */
//#define CURRENT_PROTECT_LEVEL_1_TL              (Q14I_CURRENT_TO_PU(40.0f))    /**< 过流保护阈值（A） */
//#define CURRENT_PROTECT_LEVEL_1_TIME            (100U)                         /**< 过流保护时间（ms） */

//#define CURRENT_PROTECT_LEVEL_2_TL              (Q14I_CURRENT_TO_PU(35.0f))    /**< 过流保护阈值（A） */
//#define CURRENT_PROTECT_LEVEL_2_TIME            (1000U)                        /**< 过流保护时间（ms） */

//#define CURRENT_PROTECT_LEVEL_3_TL              (Q14I_CURRENT_TO_PU(30.0f))    /**< 过流保护阈值（A） */
//#define CURRENT_PROTECT_LEVEL_3_TIME            (10000U)                       /**< 过流保护时间（ms） */

//#define FAST_CURRENT_PROTECT_LEVEL_TL           (Q14I_CURRENT_TO_PU(50.0f))    /**< 快速过流保护阈值（A） */
//#define FAST_CURRENT_PROTECT_LEVEL_TIME         (5U)                           /**< 快速过流保护时间 */

///* ---- 温度保护 ---- */
//#define OVER_TEMP_PROTECT_LEVEL_TL              ((Q32U_)(400.0f))              /**< 过温保护阈值（lsb） */
//#define OVER_TEMP_PROTECT_LEVEL_TIME            (1000U)                        /**< 过温保护时间（ms） */
//#define OVER_TEMP_CLEAR_LEVEL_TL                ((Q32U_)(600.0f))              /**< 过温恢复阈值（lsb） */
//#define OVER_TEMP_CLEAR_LEVEL_TIME              (1000U)                        /**< 过温恢复时间（ms） */

//#define LOW_TEMP_PROTECT_LEVEL_TL               ((Q32U_)(4000.0f))             /**< 低温保护阈值（lsb） */
//#define LOW_TEMP_PROTECT_LEVEL_TIME             (1000U)                        /**< 低温保护时间（ms） */
//#define LOW_TEMP_CLEAR_LEVEL_TL                 ((Q32U_)(3800.0f))             /**< 低温恢复阈值（lsb） */
//#define LOW_TEMP_CLEAR_LEVEL_TIME               (1000U)                        /**< 低温恢复时间（ms） */

///* ---- 速度保护 ---- */
//#define OVER_SPEED_PROTECT_LEVEL_TL             (Q14I_FREQ_TO_PU(MOTOR_SPEED_TO_FREQ(125000.0f)))  /**< 超速保护阈值（rpm） */
//#define OVER_SPEED_PROTECT_LEVEL_TIME           (1000U)                                            /**< 超速保护时间（ms） */

//#define LOW_SPEED_PROTECT_LEVEL_TL              (Q14I_FREQ_TO_PU(MOTOR_SPEED_TO_FREQ(0.0f)))       /**< 低速保护阈值（rpm） */
//#define LOW_SPEED_PROTECT_LEVEL_TIME            (10000U)                                           /**< 低速保护时间（ms） */

///* ---- 功率 / 母线保护 ---- */
//#define OVER_POWER_PROTECT_LEVEL_TL             (Q14I_VOLTAGE_TO_PU(24.0f) * Q14I_CURRENT_TO_PU(15.0f))  /**< 过功率保护阈值（W） */
//#define OVER_POWER_PROTECT_LEVEL_TIME           (1000U)                                                   /**< 过功率保护时间（ms） */
//#define OVER_IBUS_PROTECT_LEVEL_TL              (Q14I_CURRENT_TO_PU(30.0f))                               /**< 过母线电流阈值（A） */
//#define OVER_IBUS_PROTECT_LEVEL_TIME            (1000U)                                                   /**< 过母线电流时间（ms） */

///* ---- MOS 损坏 ---- */
//#define MOS_ERROR_COUNT                         (3U)  /**< MOS 损坏次数阈值 */

///* ---- 缺相保护 ---- */
//#define PHASE_LACK_IPHASE_PROTECT_LEVEL_TL      (Q14I_CURRENT_TO_PU(5.0f))   /**< 缺相相电流阈值（A） */
//#define PHASE_LACK_ISREF_PROTECT_LEVEL_TL       (Q14I_CURRENT_TO_PU(30.0f))  /**< 缺相 IsRef 阈值（A） */
//#define PHASE_LACK_PROTECT_LEVEL_TIME           (5000U)                      /**< 缺相保护时间（ms） */

///* ---- 堵转保护 ---- */
//#define ROTOR_LOCK_ISREF_PROTECT_LEVEL_TL       (Q14I_CURRENT_TO_PU(30.0f))                             /**< 堵转 IsRef 阈值（A） */
//#define ROTOR_LOCK_SPEED_PROTECT_LEVEL_TL       (Q14I_FREQ_TO_PU(MOTOR_SPEED_TO_FREQ(100.0f)))          /**< 堵转速度阈值（rpm） */
//#define ROTOR_LOCK_PROTECT_LEVEL_TIME           (5000U)                                                 /**< 堵转保护时间（ms） */

///* ---- 失步保护 ---- */
//#define LOSS_STEP_ES_PROTECT_LEVEL_TL           (Q14I_VOLTAGE_TO_PU(1.0f))                              /**< 失步 Es 阈值（V） */
//#define LOSS_STEP_SPEED_PROTECT_LEVEL_TL        (Q14I_FREQ_TO_PU(MOTOR_SPEED_TO_FREQ(1000.0f)))         /**< 失步速度阈值（rpm） */
//#define LOSS_STEP_PROTECT_LEVEL_TIME            (5000U)                                                 /**< 失步保护时间（ms） */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 电机故障标志位联合体
 */
typedef union {
    SC_ALL all;                          /**< 整体访问 */
    struct {
        SC_BIT current_short       :1;   /**< 短路 */
        SC_BIT mos_fault           :1;   /**< MOS 损坏（单个上电周期内多次短路） */
        SC_BIT current_offset      :1;   /**< 电流偏置异常 */
        SC_BIT position_error      :1;   /**< 电机定位失败 / 缺相 SQ */
        SC_BIT rotor_stall         :1;   /**< 电机堵转（方波） */

        SC_BIT over_voltage        :1;   /**< 过压 */
        SC_BIT low_voltage         :1;   /**< 低压 */
        SC_BIT over_current1       :1;   /**< 过流 1 */
        SC_BIT over_current2       :1;   /**< 过流 2 */
        SC_BIT over_current3       :1;   /**< 过流 3 */
        SC_BIT over_temp           :1;   /**< 过温 */
        SC_BIT low_temp            :1;   /**< 低温 */
        SC_BIT over_speed          :1;   /**< 过速 */
        SC_BIT low_speed           :1;   /**< 低速 */
        SC_BIT over_power          :1;   /**< 过功率 */
        SC_BIT over_ibus           :1;   /**< 过母线电流 */

        SC_BIT fast_over_voltage   :1;   /**< 快速过压 */
        SC_BIT fast_over_current   :1;   /**< 快速过流 */

        SC_BIT phase_lack_a        :1;   /**< A 相缺相 */
        SC_BIT phase_lack_b        :1;   /**< B 相缺相 */
        SC_BIT phase_lack_c        :1;   /**< C 相缺相 */
        SC_BIT rotor_lock          :1;   /**< 电机堵转（FOC） */
        SC_BIT loss_step           :1;   /**< 失步 */
    } bit;
} UN_MOTOR_ERROR_FLAG;

/**
 * @brief 电机故障运行状态与参数
 */
typedef struct {
    UN_MOTOR_ERROR_FLAG Motor_Error_Flag;   /**< 故障标志位图 */

    Q32I_ I_Q14U_Vbus_pu;            /**< 母线电压（Q14） */
    Q32I_ I_Q14U_Iphase_Max_pu;      /**< 相电流最大值（Q14） */
    Q32I_ I_Q14U_Temp_ADC;           /**< 温度 ADC 值 */
    Q32I_ I_Q14U_Speed_pu;           /**< 转速（Q14） */
    Q32I_ I_Q14U_Ibus_pu;            /**< 母线电流（Q14） */

    Q32I_ I_Q14U_IsRef_pu;           /**< 电流指令（Q14） */
    Q32I_ I_Q14U_Iphase_A_Max_pu;    /**< A 相电流最大值（Q14） */
    Q32I_ I_Q14U_Iphase_B_Max_pu;    /**< B 相电流最大值（Q14） */
    Q32I_ I_Q14U_Iphase_C_Max_pu;    /**< C 相电流最大值（Q14） */
    Q32I_ I_Q14U_Es_pu;              /**< 反电动势幅值（Q14） */

    ST_CHECK Over_Voltage;           /**< 过压确认 */
    ST_CHECK Low_Voltage;            /**< 低压确认 */
    ST_CHECK Over_Current1;          /**< 过流 1 确认 */
    ST_CHECK Over_Current2;          /**< 过流 2 确认 */
    ST_CHECK Over_Current3;          /**< 过流 3 确认 */
    ST_CHECK Over_Temp;              /**< 过温确认 */
    ST_CHECK Low_Temp;               /**< 低温确认 */
    ST_CHECK Over_Speed;             /**< 过速确认 */
    ST_CHECK Low_Speed;              /**< 低速确认 */
    ST_CHECK Over_Power;             /**< 过功率确认 */
    ST_CHECK Over_Ibus;              /**< 过母线电流确认 */
    ST_CHECK Phase_Lack_A;           /**< A 相缺相确认 */
    ST_CHECK Phase_Lack_B;           /**< B 相缺相确认 */
    ST_CHECK Phase_Lack_C;           /**< C 相缺相确认 */
    ST_CHECK Rotor_Lock;             /**< 堵转确认 */
    ST_CHECK Loss_Step;              /**< 失步确认 */

    ST_CHECK Fast_Over_Voltage;      /**< 快速过压确认 */
    ST_CHECK Fast_Over_Current;      /**< 快速过流确认 */

    Q32U_ V_Q32U_MOS_Error_cnt;      /**< 本上电周期内 MOS 短路计数 */
    Q32U_ V_Q32U_MOS_Error_cnt_Last; /**< 上一帧计数 */
    Q32U_ P_Q32U_MOS_Error_Count;    /**< MOS 损坏累计阈值 */
} ST_MOTOR_ERROR;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  1ms 任务：常规电压/电流/温度/速度/功率保护
 * @param  pError        故障结构体指针
 * @param  Q32U_Enable   使能（0 = 旁路部分保护，1 = 全部使能）
 */
void MC_Error_Speed_Flow(ST_MOTOR_ERROR* pError, Q32U_ Q32U_Enable);

/**
 * @brief  1ms 任务：FOC 专用保护（缺相 / 堵转 / 失步）
 * @param  pError        故障结构体指针
 * @param  Q32U_Enable   使能
 */
void MC_Error_Speed_Flow_FOC(ST_MOTOR_ERROR* pError, Q32U_ Q32U_Enable);

/**
 * @brief  电流中断任务：快速过压 / 快速过流
 * @param  pError  故障结构体指针
 */
__attribute__CCMRAM
void MC_Error_Current_Flow(ST_MOTOR_ERROR* pError);

/**
 * @brief  短路事件记录（电流中断或硬件刹车触发）
 * @param  pError  故障结构体指针
 */
void MC_Error_Short_Flow(ST_MOTOR_ERROR* pError);

/**
 * @brief  1ms 任务：MOS 短路次数累积判断
 * @param  pError  故障结构体指针
 */
void MC_Error_Init_Flow(ST_MOTOR_ERROR* pError);

/**
 * @brief  清除可复位故障并复位确认结构体
 * @param  pError  故障结构体指针
 */
void MC_Error_Clear(ST_MOTOR_ERROR* pError);

#endif /* MC_ERROR_H */
