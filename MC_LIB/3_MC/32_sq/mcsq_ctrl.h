/**
 * @file    mcsq_ctrl.h
 * @brief   无感方波（BLDC）控制模块
 * @author  CJYS
 * @date    2024/1/1
 *
 * 定义换向算法、换向流程、方向/扇区/相序等枚举，以及各子模块
 * （偏置、顺风、自举、定位、刹车、诊断、磁链、BEMF、CMP、PWM）
 * 状态结构体。
 */

#ifndef MCSQ_CTRL_H
#define MCSQ_CTRL_H

/* ======================== 1. Includes ===================== */
#include "math_type.h"
#include "math_filter_t.h"
#include "math_pid_t.h"
#include "math_ramp_t.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 电机旋转方向
 */
typedef enum {
    CW,     /**< 顺时针 */
    CCW,    /**< 逆时针 */
} EM_DIRECTION;

/**
 * @brief 电机相序
 */
typedef enum {
    U_CHANNEL_NUM,   /**< U 相 */
    V_CHANNEL_NUM,   /**< V 相 */
    W_CHANNEL_NUM,   /**< W 相 */
} EM_CHANNEL_NUM;

/**
 * @brief 转子扇区
 */
typedef enum {
    sector_1,   /**< 扇区 1 */
    sector_2,   /**< 扇区 2 */
    sector_3,   /**< 扇区 3 */
    sector_4,   /**< 扇区 4 */
    sector_5,   /**< 扇区 5 */
    sector_6,   /**< 扇区 6 */
} EM_SECTOR_NUM;

/**
 * @brief 换向算法状态机
 */
typedef enum {
    SWITCH_FLUX,    /**< 磁链换向 */
    SWITCH_BEMF,    /**< 反电动势过零换向 */
    SWITCH_CMP,     /**< 比较器过零换向 */
} EM_SWITCH_MATH;

/**
 * @brief 换向流程状态机
 */
typedef enum {
    SQUARE_DIAG_ING,    /**< 续流检测 */
    SQUARE_CROSS_ING,   /**< 过零点检测 */
    SQUARE_CROSS_SUCC,  /**< 过零检测成功，等待换向 */
    SQUARE_SWITCH_SUCC, /**< 换向成功 */
} EM_SQUARE_FLOW;

/**
 * @brief 任务状态机
 */
typedef enum {
    ING,    /**< 未完成 */
    SUCS,   /**< 成功 */
    FAIL,   /**< 失败 */
} EM_FLAG_STATE;

/**
 * @brief 频率计算状态
 */
typedef struct {
    Q32U_ I_Q32U_Time_Count;             /**< 输入：当前计时值 */
    Q32U_ O_Q32U_Switch_cnt;             /**< 输出：累计换向次数 */

    Q32U_ V_Q32U_60Deg_Time_cnt;         /**< 本 60° 区间用时 */
    Q32U_ V_Q32U_60Deg_Time_cnt_last;    /**< 上一换向时刻 */
    Q32U_ V_Q32U_60Deg_Time_cnt_tmp[6];  /**< 6 次 60° 区间历史 */
    Q32U_ V_Q32U_60Deg_Time_cnt_Filter;  /**< 历史求和值 */

    Q32U_ P_Q32U_Hall_Time_Freq;         /**< HALL 定时器时钟（Hz） */
    Q32U_ P_Q32U_Hall_Time_Max_count;    /**< HALL 定时器溢出值 */
} ST_FREQ_CAL;

/**
 * @brief BLDC 电气量
 */
typedef struct {
    EM_SWITCH_MATH  SW_Math;             /**< 当前换向算法 */
    EM_SQUARE_FLOW  SQ_Flow;             /**< 当前换向流程 */

    EM_DIRECTION    DIR_Set;             /**< 实际方向 */
    EM_DIRECTION    DIR_Target;          /**< 目标方向 */
    EM_SECTOR_NUM   Sector;              /**< 当前扇区 */
    EM_SECTOR_NUM   Sector_Last;         /**< 上一扇区 */

    ST_LPF_T        FL_Freq;             /**< 频率滤波器 */
    ST_LPF_T        FL_Ibus;             /**< 母线电流滤波器 */
    ST_LPF_T        FL_Iphase;           /**< 相电流滤波器 */
    ST_LPF_T        FL_Vbus_ADC;         /**< 母线电压 ADC 滤波器 */
    ST_LPF_T        FL_Temp_ADC;         /**< 温度 ADC 滤波器 */

    ST_FREQ_CAL     Freq_Cal;            /**< 频率计算 */

    Q32U_ V_Q12U_Bemf_ADC_tmp[3];        /**< 三相 BEMF ADC 值 */
    Q32U_ V_Q12U_Bemf_ON_ADC;            /**< 导通相 BEMF ADC */
    Q32U_ V_Q12U_Bemf_ZI_ADC;            /**< 悬空相 BEMF ADC */
    Q32U_ V_Q12U_Bemf_OF_ADC;            /**< 关断相 BEMF ADC */

    Q32U_ V_Q12U_Iphase_ADC;             /**< 相电流 ADC */
    Q32U_ V_Q12U_Iphase_ADC_Offset;      /**< 相电流 ADC 偏置 */

    Q32U_ V_Q14U_Iphase_pu;              /**< 相电流（Q14 标幺） */
    Q32U_ V_Q14U_Vbus_pu;                /**< 母线电压（Q14 标幺） */

    Q32U_ P_Q14U_Iphase_Max_pu;          /**< 相电流限值 */
    Q32U_ P_Q14U_Ibus_Max_pu;            /**< 母线电流限值 */
    Q32U_ P_Q14U_Vbus_Max_pu;            /**< 母线电压基准 */
    Q32U_ P_Q28U_Freq_Scale;             /**< 频率缩放系数（Q28） */
} ST_MCSQ_BLDC;

/**
 * @brief 电流偏置检测
 */
typedef struct {
    Q32U_ V_Q32U_Offset_Check_cnt;   /**< 采样计数 */

    Q32U_ P_Q12U_Offset_Max;         /**< 偏置上限 */
    Q32U_ P_Q12U_Offset_Min;         /**< 偏置下限 */
    Q32U_ P_Q16U_Offset_Check_Count; /**< 平均次数 */
} ST_MCSQ_OFFSET;

/**
 * @brief 顺风检测
 */
typedef struct {
    Q32U_ V_Q32U_Flying_Low_Bemf_cnt;   /**< 低 BEMF 持续计数 */
    Q32U_ V_Q32U_Flying_Fail_cnt;       /**< 超时失败计数 */
    Q32U_ V_Q16U_Flying_Check_cnt;      /**< 换向滤波计数 */
    Q32U_ V_Q16U_Flying_Phase_cnt;      /**< 已完成换向相数 */

    Q32U_ P_Q32U_Flying_Low_Bemf_TL;    /**< 低 BEMF 判定阈值 */
    Q32U_ P_Q16U_Flying_Low_Bemf_Count; /**< 低 BEMF 判定次数 */
    Q32U_ P_Q16U_Flying_Fail_Count;     /**< 超时次数 */
    Q32U_ P_Q16U_Flying_Check_Filter;   /**< 换向滤波次数 */
} ST_MCSQ_FLYING;

/**
 * @brief 自举检测
 */
typedef struct {
    Q32U_ V_Q32U_Boot_Low_Bemf_cnt;   /**< 低 BEMF 持续计数 */
    Q32U_ V_Q32U_Boot_Fail_cnt;       /**< 超时计数 */

    Q32U_ P_Q32U_Boot_Low_Bemf_TL;    /**< 低 BEMF 阈值 */
    Q32U_ P_Q16U_Boot_Low_Bemf_Count; /**< 低 BEMF 判定次数 */
    Q32U_ P_Q16U_Boot_Fail_Count;     /**< 超时次数 */
    Q32U_ P_Q14U_Boot_Duty_Set;       /**< 自举占空比 */
} ST_MCSQ_BOOT;

/**
 * @brief 脉冲定位
 */
typedef struct {
    Q32U_ V_Q12U_Position_Iphase_ADC_tmp[6];  /**< 6 步电流 ADC 采样 */
    Q32U_ V_Q32U_Position_cnt;                /**< 步序 */
    Q32U_ V_Q14U_Position_Duty_PWMCount;      /**< 定位 PWM 计数 */

    Q32U_ P_Q12U_Position_Iphase_TL;          /**< 定位成功相电流阈值 */
    Q32U_ P_Q14U_Position_Duty_Set;           /**< 定位占空比 */
} ST_MCSQ_POSITION;

/**
 * @brief 刹车阶段
 */
typedef struct {
    ST_RAMP_T Ramp_Brake_Duty;        /**< 刹车占空比斜坡 */

    Q32U_ O_Q32U_Brake_Finish_Flag;   /**< 刹车完成标志 */
    Q32U_ O_Q14U_Brake_Duty_Set;      /**< 刹车占空比指令 */

    Q32U_ V_Q32U_Brake_cnt;           /**< 刹车阶段计数 */

    Q32U_ P_Q16U_NoBrake_Count;       /**< 自由滑行时长 */
    Q32U_ P_Q16U_SlowBrake_Count;     /**< 慢刹时长 */
    Q32U_ P_Q16U_ShortBrake_Count;    /**< 短接刹车时长 */
} ST_MCSQ_BRAKE;

/**
 * @brief 续流检测参数
 */
typedef struct {
    Q32U_ V_Q32U_DIAG_cnt;            /**< 续流计数 */

    Q32U_ P_Q14U_DIAG_Rise_tl;        /**< 上升沿阈值 */
    Q32U_ P_Q14U_DIAG_Fall_tl;        /**< 下降沿阈值 */
    Q32U_ P_Q16U_DIAG_Filter_Count;   /**< 滤波次数 */
} ST_MS_DIAG;

/**
 * @brief 磁链换向参数
 */
typedef struct {
    Q32U_ V_Q32U_Flux_cnt;            /**< 磁链过零计数 */
    Q32U_ V_Q32U_Flux_to_Bemf_cnt;    /**< 磁链→BEMF 切换计数 */

    Q32U_ P_Q14U_Flux_Rise_tl;        /**< 磁链上升阈值 */
    Q32U_ P_Q14U_Flux_Fall_tl;        /**< 磁链下降阈值 */
    Q32U_ P_Q16U_Flux_Filter_Count;   /**< 滤波次数 */
    Q32U_ P_Q14U_Flux_to_Bemf_Freq;   /**< 切换频率阈值 */
    Q32U_ P_Q14U_Flux_to_Bemf_Count;  /**< 切换计数阈值 */
} ST_MS_FLUX;

/**
 * @brief 反电动势换向参数
 */
typedef struct {
    Q32U_ V_Q32U_Bemf_cnt;            /**< BEMF 过零计数 */
    Q32U_ V_Q32U_Bemf_to_Flux_cnt;    /**< BEMF→磁链切换计数 */

    Q32U_ P_Q16U_Bemf_Filter_Count;   /**< 滤波次数 */
    Q32U_ P_Q14U_Bemf_Delay_Coeff;    /**< 延迟换向系数 */
    Q32U_ P_Q14U_Bemf_to_Flux_Freq;   /**< 切换频率阈值 */
    Q32U_ P_Q14U_Bemf_to_Flux_Count;  /**< 切换计数阈值 */
} ST_MS_BEMF;

/**
 * @brief 比较器换向（预留）
 */
typedef struct {
    Q32U_ V_Q32U_temp;   /**< 预留 */
} ST_MS_CMP;

/**
 * @brief PWM 控制
 */
typedef struct {
    ST_RAMP_T Ramp_Duty;                 /**< 占空比斜坡 */

    Q08U_ PWM_Freq_Flag;                 /**< 0 低频，1 高频 */

    Q32U_ I_Q14U_Duty_VR;                /**< 输入：速度指令占空比 */
    Q32U_ I_Q14U_Duty_Freq;              /**< 输入：速度环 PID 输出 */
    Q32U_ I_Q14U_Duty_Ibus;              /**< 输入：母线电流环 PID 输出 */
    Q32U_ I_Q14U_Duty_Iphase;            /**< 输入：相电流环 PID 输出 */

    Q32U_ O_Q14U_Duty_Set;               /**< 输出：最终占空比 */
    Q32U_ O_Q32U_Duty_PWMCount;          /**< 输出：占空比 PWM 计数 */
    Q32U_ O_Q32U_PWMCount_Set;           /**< 输出：周期 PWM 计数 */

    Q32U_ P_Q14U_Low_to_High_Duty;       /**< 低频→高频阈值 */
    Q32U_ P_Q14U_High_to_Low_Duty;       /**< 高频→低频阈值 */
    Q32U_ P_Q32U_Init_PWMCount;          /**< 初始化 PWM 计数 */
    Q32U_ P_Q32U_Low_PWMCount;           /**< 低载频计数 */
    Q32U_ P_Q32U_High_PWMCount;          /**< 高载频计数 */

    Q32U_ P_Q14U_Duty_Max;               /**< 占空比上限 */
    Q32U_ P_Q14U_Duty_Min;               /**< 占空比下限 */
    Q32U_ P_Q14U_Motor_Freq_Max;         /**< 频率上限 */
    Q32U_ P_Q14U_Motor_Freq_Min;         /**< 频率下限 */

    Q32U_ P_Q32U_ADC_Delay_Value;        /**< ADC 采样延时 */
    Q32U_ P_Q32U_ADC_Sample_Value;       /**< ADC 采样时长 */
    Q32U_ P_Q32U_ADC_Solve_Value;        /**< ADC 计算耗时 */

    Q32U_ P_Q32U_TIM_Delay_Value;        /**< 换向延时计数 */
} ST_PWM_CONTROL;

/**
 * @brief 堵转检测
 */
typedef struct {
    Q32U_ V_Q32U_Stall_cnt;            /**< 堵转计数 */
    Q32U_ V_Q32U_Stall_Switch_cnt;     /**< 上次换向次数 */

    Q32U_ P_Q16U_Stall_Count;          /**< 堵转计数阈值 */
    Q32U_ P_Q06U_Stall_Switch_Coeff;   /**< 换向波动系数 */
} ST_STALL_CONTROL;

/**
 * @brief 方波控制总结构体
 */
typedef struct {
    ST_MCSQ_BLDC        MCSQ_BLDC;     /**< 电气量 */
    ST_MCSQ_OFFSET      MCSQ_OFFSET;   /**< 偏置 */
    ST_MCSQ_FLYING      MCSQ_FLYING;   /**< 顺风 */
    ST_MCSQ_BOOT        MCSQ_BOOT;     /**< 自举 */
    ST_MCSQ_POSITION    MCSQ_POSITION; /**< 定位 */
    ST_MCSQ_BRAKE       MCSQ_BRAKE;    /**< 刹车 */

    ST_MS_DIAG          MCSQ_DIAG;     /**< 续流 */
    ST_MS_FLUX          MCSQ_FLUX;     /**< 磁链 */
    ST_MS_BEMF          MCSQ_BEMF;     /**< BEMF */
    ST_MS_CMP           MCSQ_CMP;      /**< CMP */

    ST_PWM_CONTROL      PWM_CTRL;      /**< PWM 控制 */

    ST_RAMP_T           Ramp_Freq;     /**< 频率斜坡 */
    ST_PID_INC_T        PID_Freq;      /**< 频率环 PID */
    ST_PID_INC_T        PID_Ibus;      /**< 母线电流环 PID */
    ST_PID_INC_T        PID_Iphase;    /**< 相电流环 PID */

    ST_STALL_CONTROL    STALL_CTRL;    /**< 堵转 */
} ST_MCSQ_CONTROL;

/* ======================== 4. Globals ====================== */
extern EM_SECTOR_NUM Position_Sector[6][2];   /**< 定位扇区映射表 */
extern EM_SECTOR_NUM Last_Sector[6];          /**< 上一扇区映射表 */
extern EM_SECTOR_NUM Next_Sector[6];          /**< 下一扇区映射表 */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  方波控制结构体初始化
 * @param  pMS_CTRL  方波控制结构体指针
 */
void MCSQ_Init(ST_MCSQ_CONTROL* pMS_CTRL);

/**
 * @brief  顺风启动初始化
 * @param  pMS_CTRL  方波控制结构体指针
 */
void MCSQ_Flying_Init(ST_MCSQ_CONTROL* pMS_CTRL);

/**
 * @brief  60° 区间频率计算与滤波
 * @param  pBLDC            BLDC 电气量
 * @param  Q32U_Time_Count  当前 HALL 计时值
 */
void MCSQ_Freq_Cal(ST_MCSQ_BLDC* pBLDC, Q32U_ Q32U_Time_Count);

/**
 * @brief  母线电流估算与滤波
 * @param  pMS_CTRL  方波控制结构体指针
 */
void MCSQ_Ibus_Cal(ST_MCSQ_CONTROL* pMS_CTRL);

/**
 * @brief  电流偏置平均值检测
 * @param  pOFFSET                偏置结构体
 * @param  pBLDC                  BLDC 电气量
 * @param  Q32U_Iphase_adc_value  相电流 ADC 值
 * @return ING / SUCS / FAIL
 */
EM_FLAG_STATE MCSQ_Offset_Check(ST_MCSQ_OFFSET* pOFFSET, ST_MCSQ_BLDC* pBLDC, Q32U_ Q32U_Iphase_adc_value);

/**
 * @brief  顺风启动状态检测
 * @param  pFLYING           顺风结构体
 * @param  pBLDC             BLDC 电气量
 * @param  Q32U_Time_Count   当前 HALL 计时值
 * @return ING / SUCS / FAIL
 */
EM_FLAG_STATE MCSQ_Flying_Check(ST_MCSQ_FLYING* pFLYING, ST_MCSQ_BLDC* pBLDC, Q32U_ Q32U_Time_Count);

/**
 * @brief  自举电容充电检测
 * @param  pMS_BOOT  自举结构体
 * @param  pBLDC     BLDC 电气量
 * @return ING / SUCS / FAIL
 */
EM_FLAG_STATE MCSQ_Boot_Check(ST_MCSQ_BOOT* pMS_BOOT, ST_MCSQ_BLDC* pBLDC);

/**
 * @brief  6 步脉冲定位
 * @param  pMCSQ_POSITION         定位结构体
 * @param  pBLDC                  BLDC 电气量
 * @param  Q32U_Iphase_adc_value  相电流 ADC 值
 * @return ING / SUCS / FAIL
 */
EM_FLAG_STATE MCSQ_Pluse_Positon(ST_MCSQ_POSITION* pMCSQ_POSITION, ST_MCSQ_BLDC* pBLDC, Q32U_ Q32U_Iphase_adc_value);

/**
 * @brief  刹车状态机（滑行 / 慢刹 / 短接刹车）
 * @param  pBRAKE_CTRL  刹车结构体
 * @param  pPWM_CTRL    PWM 控制结构体
 */
void MCSQ_Brake(ST_MCSQ_BRAKE* pBRAKE_CTRL, ST_PWM_CONTROL* pPWM_CTRL);

/**
 * @brief  续流检测
 * @param  pMS_DIAG  续流结构体
 * @param  pBLDC     BLDC 电气量
 */
void MCSQ_DIAG(ST_MS_DIAG* pMS_DIAG, ST_MCSQ_BLDC* pBLDC);

/**
 * @brief  磁链换向检测
 * @param  pMS_FLUX  磁链结构体
 * @param  pBLDC     BLDC 电气量
 */
void MCSQ_FLUX(ST_MS_FLUX* pMS_FLUX, ST_MCSQ_BLDC* pBLDC);

/**
 * @brief  BEMF 换向检测
 * @param  pMS_BEMF  BEMF 结构体
 * @param  pBLDC     BLDC 电气量
 */
void MCSQ_BEMF(ST_MS_BEMF* pMS_BEMF, ST_MCSQ_BLDC* pBLDC);

/**
 * @brief  比较器换向检测（预留）
 * @param  pMS_CMP  比较器结构体
 * @param  pBLDC    BLDC 电气量
 */
void MCSQ_CMP(ST_MS_CMP* pMS_CMP, ST_MCSQ_BLDC* pBLDC);

/**
 * @brief  PWM 载频切换与占空比斜坡
 * @param  pPWM_CTRL  PWM 控制结构体
 */
void MCSQ_PWM_Freq_Switch(ST_PWM_CONTROL* pPWM_CTRL);

/**
 * @brief  堵转检测
 * @param  pSTALL_CTRL  堵转结构体
 * @param  pMS_CTRL     方波控制结构体
 * @return ING / SUCS
 */
EM_FLAG_STATE MCSQ_Stall_Check(ST_STALL_CONTROL* pSTALL_CTRL, ST_MCSQ_CONTROL* pMS_CTRL);

#endif /* MCSQ_CTRL_H */
