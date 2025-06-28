/**************************************************************************************************
*     File Name :                        MotorPara.h
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制参数初始化头文件
**************************************************************************************************/
#ifndef MotorPara_H
#define MotorPara_H

#include "PmsmPara.h"
#include "MotorHal_cfg.h"
#include "MotorEst.h"
#include "MotorFoc.h"
#include "MotorSQ.h"

#define SPEED_CLOSE_EN                  (1U)        //0：开环，1：转速环
#define I_BUS_CLOSE_EN                  (1U)        //母线电流限流使能，0：未使能，1：母线电流环
#define P_BUS_CLOSE_EN                  (1U)        //母线电流限流使能，0：未使能，1：功率环，如果同时使能了电流环和功率环，只有电流环起作用


//电流采样偏置检测
#define CURRENT_OFFSET_VOLTAGE_V        (HAL_ADC_CURRENT_OFFSET)                            //V，电流采样偏置电压
#define CURRENT_OFFSET_lsb              (Q32U_)(CURRENT_OFFSET_VOLTAGE_V*HAL_ADC_SCALE_BIT/HAL_ADC_REF_VOLTAGE_V)//lsb，电流采样偏置
#define CURRENT_OFFSET_TL_lsb           (200U)                                              //lsb，电流采样偏置偏差阈值
#define CURRENT_OFFSET_MAX_lsb          (CURRENT_OFFSET_lsb + CURRENT_OFFSET_TL_lsb)        //lsb，电流采样偏置上限
#define CURRENT_OFFSET_MIN_lsb          (CURRENT_OFFSET_lsb - CURRENT_OFFSET_TL_lsb)        //lsb，电流采样偏置下限
#define CURRENT_OFFSET_NUM              (20U)                                               //电流采样偏置检测次数


//顺风检测
#define FREE_FLYING_TL                  (150U)              //lsb，顺风检测电压阈值
#define FREE_FLYING_NUM                 (20U)               //顺风检测电压判断次数
#define FREE_FLYING_FILTER              (2U)                //滤波次数
#define FREE_FLYING_TIME                (1000U)             //顺风检测每个扇区最长检测次数


//电机静止检测  
#define BOOT_CHECK_DUTY                 (Q12I_DUTY_TO_PU(0.500f))   //电机静止检测占空比
#define BOOT_CHECK_TL_lsb               (150U)                      //电机静止检测反电动势阈值
#define BOOT_CHECK_NUM                  (10U)                       //电机静止检测判断次数
#define BOOT_CHECK_TIME                 (5000U)                     //电机静止检测总次数


//脉冲定位 
#define POSITION_DUTY                   (Q12I_DUTY_TO_PU(0.500f))   //1kHz，脉冲定位占空比
#define POSITION_TL_lsb                 (1000U)                     //脉冲定位是否成功判断阈值


//滤波器系数
#define IPHASE_FILTER_COEFF             (25U) //0~256
#define FREQ_FILTER_COEFF               (25U) //0~256
#define IBUS_FILTER_COEFF               (25U) //0~256

//换向系数
#define DIAG_CROSS_RISE_TL              (51U)//base64
#define DIAG_CROSS_FALL_TL              (13U)//base64
#define FLUX_CROSS_RISE_TL              (37U)//base64
#define FLUX_CROSS_FALL_TL              (27U)//base64

#define DIAG_CROSS_FILTER               (2U)//滤波次数
#define FLUX_CROSS_FILTER               (2U)//滤波次数
#define BEMF_CROSS_FILTER               (2U)//滤波次数

#define BEMF_CROSS_DELAY_COEFF          (256U/6U)//base1024，延迟换向比例，512为理论的30度

//换向算法切换
#define FLUX_TO_BEMF_FREQ               (Q14I_FREQ_TO_PU(0.25f * MOTOR_MAX_FREQ))
#define FLUX_TO_BEMF_NUM                (20U)

#define BEMF_TO_FLUX_FREQ               (Q14I_FREQ_TO_PU(0.20f * MOTOR_MAX_FREQ))
#define BEMF_TO_FLUX_NUM                (20U)


//载频切换
#define PWM_FREQ_START                  (HAL_PWM_INIT_SET)
#define PWM_FREQ_LOW                    (HAL_PWM_RUN1_SET)
#define PWM_FREQ_HIGH                   (HAL_PWM_RUN2_SET)
#define PWM_FREQ_LOW_TO_HIGH_DUTY       (Q12I_DUTY_TO_PU(30.0f*HAL_PWM_RUN1_FREQ/1000.0f))     //30us
#define PWM_FREQ_HIGH_TO_LOW_DUTY       (Q12I_DUTY_TO_PU(40.0f*HAL_PWM_RUN2_FREQ/1000.0f))     //40us


//最大占空比，最小占空比
#define DUTY_RAMP_ADDSTEP               ( Q22I_DUTY_TO_PU(0.020f))
#define DUTY_RAMP_SUBSTEP               (-Q22I_DUTY_TO_PU(0.020f))

#define DUTY_CTRL_MAX                   (Q12I_DUTY_TO_PU(0.950f))
#define DUTY_CTRL_MIN                   (Q12I_DUTY_TO_PU(0.050f))

//转速PID
#define FREQ_RAMP_ADDSTEP               ( Q24I_FREQ_TO_PU(0.005f * MOTOR_MAX_FREQ))
#define FREQ_RAMP_SUBSTEP               (-Q24I_FREQ_TO_PU(0.005f * MOTOR_MAX_FREQ))

#define FREQ_PID_KP                     (Q32I_)(0.0001f * MOTOR_Q14_PU)
#define FREQ_PID_KI                     (Q32I_)(0.0010f * MOTOR_Q14_PU)
#define FREQ_PID_KD                     (Q32I_)(0.0001f * MOTOR_Q14_PU)
#define FREQ_PID_STEPMAX                ( Q28I_DUTY_TO_PU(0.010f))
#define FREQ_PID_STEPMIN                (-Q28I_DUTY_TO_PU(0.010f))
#define FREQ_PID_OUTMAX                 (DUTY_CTRL_MAX)
#define FREQ_PID_OUTMIN                 (DUTY_CTRL_MIN)
    
//母线电流PID
#define IBUS_PID_KP                     (Q32I_)(0.010f * MOTOR_Q14_PU)
#define IBUS_PID_KI                     (Q32I_)(0.010f * MOTOR_Q14_PU)
#define IBUS_PID_KD                     (Q32I_)(0.000f * MOTOR_Q14_PU)
#define IBUS_PID_STEPMAX                ( Q28I_DUTY_TO_PU(0.010f))
#define IBUS_PID_STEPMIN                (-Q28I_DUTY_TO_PU(0.010f))
#define IBUS_PID_OUTMAX                 (DUTY_CTRL_MAX)
#define IBUS_PID_OUTMIN                 (DUTY_CTRL_MIN)

//相电流PID
#define IPHASE_PID_KP                   (Q32I_)(0.010f * MOTOR_Q14_PU)
#define IPHASE_PID_KI                   (Q32I_)(0.010f * MOTOR_Q14_PU)
#define IPHASE_PID_KD                   (Q32I_)(0.000f * MOTOR_Q14_PU)
#define IPHASE_PID_STEPMAX              ( Q28I_DUTY_TO_PU(0.010f))
#define IPHASE_PID_STEPMIN              (-Q28I_DUTY_TO_PU(0.010f))
#define IPHASE_PID_OUTMAX               (DUTY_CTRL_MAX)
#define IPHASE_PID_OUTMIN               (DUTY_CTRL_MIN)


//刹车占空比控制
#define BRAKE_DUTY_RAMP_ADDSTEP         ( Q22I_DUTY_TO_PU(0.020f))
#define BRAKE_DUTY_RAMP_SUBSTEP         (-Q22I_DUTY_TO_PU(0.020f))

#define BRAKE_DUTY_CTRL_MAX             (Q12I_DUTY_TO_PU(0.400f))
#define BRAKE_DUTY_CTRL_MIN             (Q12I_DUTY_TO_PU(0.200f))

//刹车时间
#define NO_BRAKE_TIME                   (100U)              //ms，第1段自由滑行
#define SLOW_BRAKE_TIME                 (0U)                //ms，第2段馈电刹车
#define SHORT_BRAKE_TIME                (0U)                //ms，第3段短接刹车


//堵转保护参数
#define MOTOR_STALL_SWITCH_COEFF        (31U)   //base64，换相波动堵转判断系数
#define MOTOR_STALL_ERROR_TIME          (2000U) //ms，堵转时间

/******************************************************************************/
//观测器选择
#define MOTOR_EST_FLUX              (10U)
#define MOTOR_EST_SMO               (11U)
#define MOTOR_EST_MODE              MOTOR_EST_SMO


//电机closeloop相关参数，闭环开始阶段 
#define MOTOR_CLOSELOOP_STEP                (Q24I_FREQ_TO_PU(100.0f * MOTOR_LTs))   //Hz/s,电机closeloop每秒增速步长


//转速环PID
#define MOTOR_FREQ_CURRENT_MIN              ((Q32I_)(0.1f * Q14I_CURRENT_PHASE_PU)) //A,转速环输出q轴电流限幅

#define MOTOR_FREQ_PID_Coeff                (0.35f)                                 //转速环PID增益系数
#define MOTOR_FREQ_KP_GAIN                  ((Q32I_)(MOTOR_Q14_PU * MOTOR_FREQ_PID_Coeff * MOTOR_CURRENT_PHASE_A / MOTOR_MAX_FREQ * F_BASE / I_BASE))
#define MOTOR_FREQ_KI_GAIN                  ((Q32I_)(MOTOR_Q14_PU * 0.05f * MOTOR_CURRENT_PHASE_A * MOTOR_LTs * F_BASE / I_BASE))
#define MOTOR_FREQ_KD_GAIN             	    ((Q32I_)(0.0f))

#define MOTOR_FREQ_PID_MAX                  ((Q32I_)( 1.0f * Q14I_CURRENT_PHASE_PU))//A,转速环输出q轴电流限幅
#define MOTOR_FREQ_PID_MIN                  ((Q32I_)(-1.0f * Q14I_CURRENT_PHASE_PU))//A,转速环输出q轴电流限幅

//电流PID
#define MOTOR_CURRENT_PID_Coeff             (0.05f)                             //电流环P增益系数
#define MOTOR_CURRENT_KP_GAIN               ((Q32I_)(MOTOR_Q14_PU * MOTOR_CURRENT_PID_Coeff * MOTOR_Ls * MATH_2PI_F / MOTOR_HTs * I_BASE / V_BASE))
#define MOTOR_CURRENT_KI_GAIN               ((Q32I_)(MOTOR_CURRENT_KP_GAIN * MOTOR_HTs * MOTOR_Rs / MOTOR_Ls * I_BASE / V_BASE))
#define MOTOR_CURRENT_KD_GAIN               ((Q32I_)(0.0f))
//dq轴输出电压限制，如果保证电压矢量为圆形，设置为0.5774f，如果需要过调制，则最大为0.6667f
#define MOTOR_VS_MAX_SCALE                  ((Q32I_)(0.6667f * MOTOR_Q14_PU))


//观测器PLL系数
#define MOTOR_PLL_Coeff                     (0.40f)
#define MOTOR_PLL_SPEED_LPF_COEFF           (13)                                //0~256，越小滤波越深
#define MOTOR_MAX_SRAD                      (MOTOR_MAX_FREQ * MATH_2PI_F)

//非线性磁链观测器  
#define MOTOR_FLUX_GAMMA                    ((Q32I_)(0.02f * Q14I_VOLTAGE_PU * ((MOTOR_Q14_PU/Q14I_FLUX_PU)*(MOTOR_Q14_PU/Q14I_FLUX_PU)*(MOTOR_Q14_PU/Q14I_FLUX_PU))))      //增益系数

#define MOTOR_FLUX_PLL_KP                   ((Q32I_)(MOTOR_Q28_PU * 2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_SRAD / Q14I_FLUX_PU / W_BASE))                                       //锁相环比例系数
#define MOTOR_FLUX_PLL_KI                   ((Q32I_)(MOTOR_Q28_PU * MATH_SQUARE_F(MOTOR_PLL_Coeff * MOTOR_MAX_SRAD) * MOTOR_HTs / Q14I_FLUX_PU / W_BASE))                   //锁相环积分系数
#define MOTOR_FLUX_PLL_KD                   ((Q32I_)(0.0f))                     //锁相环微分系数
#define MOTOR_FLUX_PLL_MAX                  ((Q32I_)( 2.0f * Q14I_MAX_FREQ_PU)) //锁相环最大输出
#define MOTOR_FLUX_PLL_MIN                  ((Q32I_)(-2.0f * Q14I_MAX_FREQ_PU)) //锁相环最小输出

//SMO观测器
#define MOTOR_SMO_H1                        ((Q32I_)(MOTOR_Q14_PU * VOLTAGE_PU / CURRENT_PHASE_PU))       //增益系数
#define MOTOR_SMO_K1                        ((Q32I_)(0.20f * MOTOR_Q14_PU))     //限幅系数

#define MOTOR_SMO_PLL_KP                    ((Q32I_)(MOTOR_Q28_PU * 2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_SRAD * 2.0f / Q14I_VOLTAGE_PU / W_BASE))                             //锁相环比例系数
#define MOTOR_SMO_PLL_KI                    ((Q32I_)(MOTOR_Q28_PU * MATH_SQUARE_F(MOTOR_PLL_Coeff * MOTOR_MAX_SRAD) * MOTOR_HTs * 2.0f / Q14I_VOLTAGE_PU / W_BASE))         //锁相环积分系数
#define MOTOR_SMO_PLL_KD                    ((Q32I_)(0.0f))                     //锁相环微分系数
#define MOTOR_SMO_PLL_MAX                   ((Q32I_)( 2.0f * Q14I_MAX_FREQ_PU)) //锁相环最大输出
#define MOTOR_SMO_PLL_MIN                   ((Q32I_)(-2.0f * Q14I_MAX_FREQ_PU)) //锁相环最小输出


typedef enum{
    MOTOR_STATE_PRE,            //参数复位阶段
    MOTOR_STATE_INIT,           //硬件初始化阶段
    MOTOR_STATE_IDLE,           //电机静止检测阶段
    MOTOR_STATE_BOOT,           //自举电容充电阶段
    MOTOR_STATE_POSITION,       //脉冲定位阶段阶段
    MOTOR_STATE_RUN_SQ,         //电机方波运行阶段
    MOTOR_STATE_RUN,            //电机运行阶段
    MOTOR_STATE_BRAKE,          //电机刹车阶段
}EM_MOTOR_STATE_FLOW;

typedef union{
    ALL all;
    struct{
        BIT motor_run_flag      :1;//电机运行标志位
        BIT motor_speed_flag    :1;//速度环使能标志位
        BIT motor_busA_flag     :1;//母线电流环使能标志位
        BIT motor_busP_flag     :1;//母线功率环使能标志位
        BIT motor_sq_flag       :1;//方波标志位
        BIT motor_foc_flag      :1;//FOC标志位
        BIT motor_sqtofoc_en    :1;//方波切FOC使能位
        BIT motor_foctosq_en    :1;//FOC切方波使能位
        BIT motor_sqtofoc_flag  :1;//方波切FOC标志位
        BIT motor_foctosq_flag  :1;//FOC切方波标志位
    }bit;
}UN_MOTOR_STATE_FLAG;

typedef union{
    ALL all;
    struct{
        BIT current_offset      :1;//偏置故障
        BIT current_short       :1;//短路故障
        BIT mos_fault           :1;//mos故障（单个上电周期内，发生三次短路保护，锁死故障状态）
        BIT motor_stall         :1;//电机堵转故障
        BIT position_error      :1;//电机定位故障
    }bit;
}UN_MOTOR_ERROR_FLAG;

typedef struct{
    Q32U_                       _V_Q32U_Close_cnt;
}ST_LOOP_CONTROL_T;

typedef struct{
    float F_V_BASE;
    float F_I_BASE;
    float F_F_BASE;
    float F_W_BASE;
    float F_R_BASE;
    float F_L_BASE;
    float F_P_BASE;
    float F_T_BASE;
        
    EM_MOTOR_STATE_FLOW         Motor_Flow;
    UN_MOTOR_STATE_FLAG         Motor_State_Flag;
    UN_MOTOR_ERROR_FLAG         Motor_Error_Flag;
    
    ST_MS_OFFSET                MS_OFFSET;
    ST_MS_FLYING                MS_FLYING;
    ST_MS_BOOT                  MS_BOOT;
    ST_MS_POSITION              MS_POSITION;
    ST_BRAKE_CONTROL            BRAKE_CTRL;
    
    ST_MS_CONTROL               MS_CTRL;
    
    ST_LOOP_CONTROL_T           LOOP_CTRL;
    ST_SVPWM_CONTROL_T          SVPWM_CTRL;
    ST_FREQ_CONTROL_T           FREQ_CTRL;
    ST_CURRENT_CONTROL_T        CURRENT_CTRL;
    
    ST_FLUX_CONTROL_T           FLUX_CTRL;
    ST_SMO_CONTROL_T            SMO_CTRL;
    
    Q32I_                       Q12U_Last_Angle;
    Q32U_                       Q32U_MOS_Error_cnt;
    Q32I_                       Q14I_IPHASE_MAX_PU;
}ST_MOTOR_TASK;

extern ST_MOTOR_TASK  Motor;

#endif /* MotorPara_H */
