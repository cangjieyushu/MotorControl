/**
 * @file    mcfoc_loop_f.h
 * @brief   FOC 偏置自学习、IF、电流、转速闭环模块（浮点）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef MCFOC_LOOP_F_H
#define MCFOC_LOOP_F_H

/* ======================== 1. Includes ===================== */
#include "math_check.h"
#include "math_angle_f.h"
#include "math_filter_f.h"
#include "math_pid_f.h"
#include "math_ramp_f.h"
#include "mcfoc_pmsm_f.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 任务执行状态
 */
typedef enum {
    ING,        /**< 进行中（未完成） */
    SUCS,       /**< 成功 */
    FAIL,       /**< 失败 */
} EM_FLAG_STATE;

/**
 * @brief 电流偏置自学习结构体（浮点）
 */
typedef struct {
    /* ---- 输入：原始 ADC 采样值 ---- */
    Q32I_       I_Q12I_Ia_Data;             /**< A 相电流 ADC 采样 */
    Q32I_       I_Q12I_Ib_Data;             /**< B 相电流 ADC 采样 */
    Q32I_       I_Q12I_Ic_Data;             /**< C 相电流 ADC 采样 */
    Q32I_       I_Q12I_Ishunt_Data;         /**< 单电阻电流 ADC 采样 */

    /* ---- 累加与平均后的偏置值 ---- */
    Q32I_       V_Q12I_Ia_Offset;           /**< A 相电流偏置累加 / 平均结果 */
    Q32I_       V_Q12I_Ib_Offset;           /**< B 相电流偏置累加 / 平均结果 */
    Q32I_       V_Q12I_Ic_Offset;           /**< C 相电流偏置累加 / 平均结果 */
    Q32I_       V_Q12I_Ishunt_Offset;       /**< 单电阻电流偏置累加 / 平均结果 */

    Q32U_       V_Q32U_Offset_Check_cnt;    /**< 偏置采样计数 */

    /* ---- 偏置有效性判定参数 ---- */
    Q32I_       P_Q12U_Offset_Max;          /**< 偏置允许上限 */
    Q32I_       P_Q12U_Offset_Min;          /**< 偏置允许下限 */
    Q32U_       P_Q16U_Offset_Check_Count;  /**< 平均采样次数 */
} ST_MCFOC_OFFSET_F;

/**
 * @brief ALIGN（定位）控制结构体
 */
typedef struct {
    ST_RAMP_F   Ramp_Align_Id;              /**< 定位 Id 电流斜坡 */
    ST_RAMP_F   Ramp_Align_Angle;           /**< 定位角度斜坡 */

    Q32U_       V_Q32U_Align_Check_cnt;     /**< 定位保持计数 */

    /* ---- 输出 ---- */
    Q32U_       O_Q32U_Stand_Flag;          /**< 定位完成标志（1 = 完成） */
    float       O_F_Align_IdRef;            /**< 定位 Id 电流指令 */
    float       O_F_Align_Angle;            /**< 定位角度输出 */

    /* ---- 参数 ---- */
    Q32U_       P_Q32U_Align_Check_Count;   /**< 定位保持时间（速度环节拍） */
} ST_ALIGN_CONTROL_F;

/**
 * @brief IF（强制拖动）控制结构体
 */
typedef struct {
    ST_RAMP_F   Ramp_IF_Id;                 /**< IF 阶段 Id 电流斜坡 */
    ST_RAMP_F   Ramp_IF_Iq;                 /**< IF 阶段 Iq 电流斜坡 */
    ST_RAMP_F   Ramp_IF_FREQ;               /**< IF 阶段频率（转速）斜坡 */

    float       I_F_IF_Est_Angle;           /**< 输入：观测器估算角度（用于切闭环判定） */

    Q32U_       V_Q32U_IF_Angle_Err_Check_cnt;  /**< 角度误差合格计数 */

    /* ---- 输出 ---- */
    Q32U_       O_Q32U_Switch_Flag;         /**< 切闭环标志（1 = 允许切换） */
    float       O_F_IF_IdRef;               /**< IF 阶段 Id 电流指令 */
    float       O_F_IF_IqRef;               /**< IF 阶段 Iq 电流指令 */
    float       O_F_IF_Angle;               /**< IF 阶段合成角度 */

    /* ---- 参数：频率分段加速 ---- */
    float       P_F_IF_Iq_Target_1;         /**< Iq 目标电流1 */
    float       P_F_IF_Iq_Target_2;         /**< Iq 目标电流2 */
    float       P_F_IF_Freq_TL;             /**< 第一段加速上限阈值 */
    float       P_F_IF_Iq_Add_Step1;        /**< 电流第一段加速步长 */
    float       P_F_IF_Iq_Add_Step2;        /**< 电流第二段加速步长 */
    float       P_F_IF_Freq_Add_Step1;      /**< 频率第一段加速步长 */
    float       P_F_IF_Freq_Add_Step2;      /**< 频率第二段加速步长 */

    /* ---- 参数：电流与切换判定 ---- */
    float       P_F_IF_Is_Min;              /**< Is 最小电流（低速时保持） */
    float       P_F_IF_Iq_Min;              /**< Iq 最小电流 */

    float       P_F_IF_Angle_Err_Limit;     /**< 切换允许的角度偏差 */
    Q32U_       P_Q32U_IF_Angle_Err_Check_Count;  /**< 切换判定连续合格次数 */
} ST_IF_CONTROL_F;

/**
 * @brief 速度环控制结构体（含功率环 / 弱磁 / MTPA）
 */
typedef struct {
    ST_PID_SAT_F    PID_POWER;              /**< 功率环 PID（限功率） */
    ST_PID_SAT_F    PID_FREQ;               /**< 速度环 PID */
    ST_PID_SAT_F    PID_WEAK;               /**< 弱磁环 PID */
    ST_RAMP_F       Ramp_FREQ;              /**< 速度斜坡 */

    ST_CHECK        WEAK_CHECK;             /**< 弱磁使能时间确认 */
    Q32U_           O_Q32U_Weak_Flag;       /**< 弱磁状态标志（1 = 弱磁中） */

    float           I_F_FREQ_Target;        /**< 输入：目标转速（标幺） */

    float           V_F_FREQ_IMTPA;         /**< MTPA 计算出的 Id 指令 */

    /* ---- 输出 ---- */
    float           O_F_FREQ_IdRef;         /**< 输出：Id 电流指令 */
    float           O_F_FREQ_IqRef;         /**< 输出：Iq 电流指令 */

    /* ---- 参数 ---- */
    TABLE_1D_F      TAB_FREQ_Kp_Coeff;      /**< Kp 频率补偿表 */
    TABLE_1D_F      TAB_FREQ_Ki_Coeff;      /**< Ki 频率补偿表 */
    float           P_F_FREQ_Kp;            /**< Kp 基础增益 */
    float           P_F_FREQ_Ki;            /**< Ki 基础增益 */
    float           P_F_FREQ_PowerRef;      /**< 功率环参考系数 */
    float           P_F_FREQ_IbusRef;       /**< 母线电流参考系数 */
} ST_FREQ_CONTROL_F;

/**
 * @brief 电流环控制结构体
 */
typedef struct {
    ST_PID_SAT_F    PID_Id;                 /**< d 轴电流环 PID */
    ST_PID_SAT_F    PID_Iq;                 /**< q 轴电流环 PID */

    float           I_F_IdRef;              /**< 输入：d 轴电流指令 */
    float           I_F_IqRef;              /**< 输入：q 轴电流指令 */
} ST_CURRENT_CONTROL_F;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  电流偏置检测初始化
 * @param  pOFFSET  偏置结构体指针
 */
void MCFOC_Offset_Check_Init_F(ST_MCFOC_OFFSET_F* pOFFSET);

/**
 * @brief  三相电流偏置检测
 * @param  pOFFSET  偏置结构体指针
 * @param  pPMSMe   电机电气量指针
 * @return ING / SUCS / FAIL
 */
EM_FLAG_STATE MCFOC_Offset_Check_Three_F(ST_MCFOC_OFFSET_F* pOFFSET, ST_PMSM_ELEC_F* pPMSMe);

/**
 * @brief  单电阻电流偏置检测
 * @param  pOFFSET  偏置结构体指针
 * @param  pPMSMe   电机电气量指针
 * @return ING / SUCS / FAIL
 */
EM_FLAG_STATE MCFOC_Offset_Check_One_F(ST_MCFOC_OFFSET_F* pOFFSET, ST_PMSM_ELEC_F* pPMSMe);

/**
 * @brief  ALIGN 控制初始化
 * @param  pALIGN  ALIGN 结构体指针
 */
void MCFOC_ALIGN_Init_F(ST_ALIGN_CONTROL_F* pALIGN);

/**
 * @brief  ALIGN 速度环任务（Id 斜坡 + 定位完成判定）
 * @param  pALIGN  ALIGN 结构体指针
 */
void MCFOC_ALIGN_SpeedLoop_F(ST_ALIGN_CONTROL_F* pALIGN);

/**
 * @brief  ALIGN 电流环任务（角度输出）
 * @param  pALIGN  ALIGN 结构体指针
 */
__attribute__CCMRAM
void MCFOC_ALIGN_CurrentLoop_F(ST_ALIGN_CONTROL_F* pALIGN);

/**
 * @brief  IF 控制初始化
 * @param  pIF  IF 结构体指针
 */
void MCFOC_IF_Init_F(ST_IF_CONTROL_F* pIF);

/**
 * @brief  IF 速度环任务（Iq / 频率斜坡 + 切闭环准备）
 * @param  pIF     IF 结构体指针
 * @param  pPMSMe  电机电气量指针
 */
void MCFOC_IF_SpeedLoop_F(ST_IF_CONTROL_F* pIF, ST_PMSM_ELEC_F* pPMSMe);

/**
 * @brief  IF 电流环任务（角度推进 + 切闭环判定）
 * @param  pIF     IF 结构体指针
 * @param  pPMSMe  电机电气量指针
 * @param  pPMSMa  电机参数结构体指针
 */
__attribute__CCMRAM
void MCFOC_IF_CurrentLoop_F(ST_IF_CONTROL_F* pIF, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa);

/**
 * @brief  速度环初始化
 * @param  pFREQ  速度环结构体指针
 */
void MCFOC_SpeedLoop_Init_F(ST_FREQ_CONTROL_F* pFREQ);

/**
 * @brief  速度环任务（功率环 + 速度环 + 弱磁 / MTPA）
 * @param  pFREQ   速度环结构体指针
 * @param  pPMSMe  电机电气量指针
 * @param  pPMSMa  电机参数结构体指针
 */
void MCFOC_SpeedLoop_F(ST_FREQ_CONTROL_F* pFREQ, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa);

/**
 * @brief  电流环初始化
 * @param  pCURRENT  电流环结构体指针
 */
void MCFOC_CurrentLoop_Init_F(ST_CURRENT_CONTROL_F* pCURRENT);

/**
 * @brief  电流环任务（d/q 轴分别计算）
 * @param  pCURRENT  电流环结构体指针
 * @param  pPMSMe    电机电气量指针
 */
__attribute__CCMRAM
void MCFOC_CurrentLoop_F(ST_CURRENT_CONTROL_F* pCURRENT, ST_PMSM_ELEC_F* pPMSMe);

#endif /* MCFOC_LOOP_F_H */
