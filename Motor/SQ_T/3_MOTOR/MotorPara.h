/**************************************************************************************************
*     File Name :                        MotorPara.h
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制参数初始化头文件
**************************************************************************************************/
#ifndef MotorPara_H
#define MotorPara_H

#include "MotorHal_cfg.h"
#include "MotorSQ.h"
#include "PmsmPara.h"

#define SYS_RECTIFICAITON   1       //0：非同步整流，1：同步整流

#define BRAKE_EN            1       //刹车使能

#define SPEED_CLOSE_EN      1       //0：开环，1：转速环
#define IBUS_CLOSE_EN       1       //母线电流限流使能，0：未使能，1：母线电流环，2：功率环
#define IPHASE_CLOSE_EN     1       //相电流限流使能

//电流采样偏置检测
#define CURRENT_OFFSET_VOLTAGE_V        (0.5f)                                              //V，电流采样偏置电压
#define CURRENT_OFFSET_lsb              (Q32U_)(CURRENT_OFFSET_VOLTAGE_V*HAL_ADC_SCALE_BIT/HAL_ADC_REF_VOLTAGE_V)//lsb，电流采样偏置
#define CURRENT_OFFSET_TL_lsb           (200U)                                              //lsb，电流采样偏置偏差阈值
#define CURRENT_OFFSET_MAX_lsb          (CURRENT_OFFSET_lsb + CURRENT_OFFSET_TL_lsb)        //lsb，电流采样偏置上限
#define CURRENT_OFFSET_MIN_lsb          (CURRENT_OFFSET_lsb - CURRENT_OFFSET_TL_lsb)        //lsb，电流采样偏置下限
#define CURRENT_OFFSET_NUM              (20U)                                               //电流采样偏置检测次数
    
//顺风检测
#define FREE_FLYING_TL                  (50U)               //lsb，顺风检测电压阈值
#define FREE_FLYING_NUM                 (20U)               //顺风检测电压判断次数
#define FREE_FLYING_FILTER              (2U)                //滤波次数
#define FREE_FLYING_TIME                (1000U)             //顺风检测每个扇区最长检测次数

//电机静止检测  
#define BOOT_CHECK_DUTY                 (HAL_PWM_DUTY_50_PERCENT)   //电机静止检测占空比
#define BOOT_CHECK_TL_lsb               (50U)                       //电机静止检测反电动势阈值
#define BOOT_CHECK_NUM                  (10U)                       //电机静止检测判断次数
#define BOOT_CHECK_TIME                 (10000U)                    //电机静止检测总次数

//脉冲定位 
#define POSITION_DUTY                   (HAL_PWM_DUTY_5_PERCENT)   //1kHz，脉冲定位占空比
#define POSITION_TL_lsb                 (1000U)                      //脉冲定位是否成功判断

//滤波器系数
#define IPHASE_FILTER_COEFF             (25U) //0~256
#define FREQ_FILTER_COEFF               (25U) //0~256
#define IBUS_FILTER_COEFF               (25U) //0~256
#define IBRAKE_FILTER_COEFF             (25U) //0~256


//换向系数
#define DIAG_CROSS_RISE_TL              (51U)//base64
#define DIAG_CROSS_FALL_TL              (13U)//base64
#define CURRENT_CROSS_RISE_TL           (37U)//base64
#define CURRENT_CROSS_FALL_TL           (27U)//base64
#define FLUX_CROSS_RISE_TL              (37U)//base64
#define FLUX_CROSS_FALL_TL              (27U)//base64

#define DIAG_CROSS_FILTER               (2U)//滤波次数
#define CURRENT_CROSS_FILTER            (2U)//滤波次数
#define FLUX_CROSS_FILTER               (2U)//滤波次数
#define BEMF_CROSS_FILTER               (2U)//滤波次数

#define BEMF_CROSS_DELAY_COEFF          (16U)//base64，延迟换向比例32为理论的30度

#define CURRENT_CROSS_FAIL_FILTER       (1000U) //电流换向滤波次数
#define CURRENT_CROSS_DIAG_FILTER       (500U)  //电流换向续流滤波次数

//换向算法切换
#define CURRENT_TO_FLUX_FREQ            (Q32U_)(Q14I_FREQ_MOTOR_TO_PU(0.20f * MOTOR_MAX_FREQ))
#define CURRENT_TO_FLUX_NUM             (10U)

#define FLUX_TO_CURRENT_FREQ            (Q32U_)(Q14I_FREQ_MOTOR_TO_PU(0.15f * MOTOR_MAX_FREQ))
#define FLUX_TO_CURRENT_NUM             (5U)

#define FLUX_TO_BEMF_FREQ               (Q32U_)(Q14I_FREQ_MOTOR_TO_PU(0.25f * MOTOR_MAX_FREQ))
#define FLUX_TO_BEMF_DUTY               (HAL_PWM_DUTY_20_PERCENT)
#define FLUX_TO_BEMF_NUM                (5U)

#define BEMF_TO_FLUX_FREQ               (Q32U_)(Q14I_FREQ_MOTOR_TO_PU(0.20f * MOTOR_MAX_FREQ))
#define BEMF_TO_FLUX_DUTY               (HAL_PWM_DUTY_15_PERCENT)
#define BEMF_TO_FLUX_NUM                (5U)

//载频切换
#define PWM_FREQ_START                  (HAL_PWM_INIT_SET)
#define PWM_FREQ_LOW                    (HAL_PWM_RUN1_SET)
#define PWM_FREQ_HIGH                   (HAL_PWM_RUN2_SET)
#define PWM_FREQ_LOW_TO_HIGH_DUTY       ((Q32U_)(40.0f*HAL_PWM_DUTY_MAX*HAL_PWM_RUN1_FREQ/1000.0f))     //40us
#define PWM_FREQ_HIGH_TO_LOW_DUTY       ((Q32U_)(30.0f*HAL_PWM_DUTY_MAX*HAL_PWM_RUN2_FREQ/1000.0f))     //30us


//最大占空比，最小占空比
#define DUTY_RAMP_ADDSTEP               (Q32I_)( 0.020f * HAL_PWM_DUTY_MAX)
#define DUTY_RAMP_SUBSTEP               (Q32I_)(-0.020f * HAL_PWM_DUTY_MAX)

#define DUTY_CTRL_MAX                   (Q32I_)(HAL_PWM_DUTY_100_PERCENT)
#define DUTY_CTRL_MIN                   (Q32I_)(HAL_PWM_DUTY_5_PERCENT)

//转速PID
#define FREQ_RAMP_ADDSTEP               (Q32I_)( Q14I_FREQ_MOTOR_TO_PU(0.001f * MOTOR_MAX_FREQ))
#define FREQ_RAMP_SUBSTEP               (Q32I_)(-Q14I_FREQ_MOTOR_TO_PU(0.001f * MOTOR_MAX_FREQ))

#define FREQ_PID_KP                     (Q32I_)(0.0001f * MATH_PID_MAX)
#define FREQ_PID_KI                     (Q32I_)(0.0010f * MATH_PID_MAX)
#define FREQ_PID_KD                     (Q32I_)(0.0001f * MATH_PID_MAX)
#define FREQ_PID_STEPMAX                (Q32I_)( 0.010f * HAL_PWM_DUTY_MAX)
#define FREQ_PID_STEPMIN                (Q32I_)(-0.010f * HAL_PWM_DUTY_MAX)
#define FREQ_PID_OUTMAX                 (DUTY_CTRL_MAX)
#define FREQ_PID_OUTMIN                 (DUTY_CTRL_MIN)
    
//母线电流PID
#define IBUS_GAIN                       (2)//母线电流放大倍数，未使用
#define IBUS_PID_RF                     (Q32I_)(Q14I_CURRENT_MOTOR_TO_PU(0.5f * MOTOR_CURRENT_BUS_A))

#define IBUS_PID_KP                     (Q32I_)(0.010f * MATH_PID_MAX)
#define IBUS_PID_KI                     (Q32I_)(0.010f * MATH_PID_MAX)
#define IBUS_PID_KD                     (Q32I_)(0.000f * MATH_PID_MAX)
#define IBUS_PID_STEPMAX                (Q32I_)( 0.010f * HAL_PWM_DUTY_MAX)
#define IBUS_PID_STEPMIN                (Q32I_)(-0.010f * HAL_PWM_DUTY_MAX)
#define IBUS_PID_OUTMAX                 (DUTY_CTRL_MAX)
#define IBUS_PID_OUTMIN                 (DUTY_CTRL_MIN)

//相电流PID
#define IPHSAE_PID_RF                   (Q32I_)(Q14I_CURRENT_MOTOR_TO_PU(0.5f * MOTOR_CURRENT_PHASE_A))

#define IPHASE_PID_KP                   (Q32I_)(0.010f * MATH_PID_MAX)
#define IPHASE_PID_KI                   (Q32I_)(0.010f * MATH_PID_MAX)
#define IPHASE_PID_KD                   (Q32I_)(0.000f * MATH_PID_MAX)
#define IPHASE_PID_STEPMAX              (Q32I_)( 0.010f * HAL_PWM_DUTY_MAX)
#define IPHASE_PID_STEPMIN              (Q32I_)(-0.010f * HAL_PWM_DUTY_MAX)
#define IPHASE_PID_OUTMAX               (DUTY_CTRL_MAX)
#define IPHASE_PID_OUTMIN               (DUTY_CTRL_MIN)

//刹车母线电流PID
#define BRAKE_DUTY_RAMP_ADDSTEP         (Q32I_)( 0.020f * HAL_PWM_DUTY_MAX)
#define BRAKE_DUTY_RAMP_SUBSTEP         (Q32I_)(-0.020f * HAL_PWM_DUTY_MAX)

#define BRAKE_DUTY_CTRL_MAX             (Q32I_)(0.400f * HAL_PWM_DUTY_MAX)
#define BRAKE_DUTY_CTRL_MIN             (Q32I_)(0.200f * HAL_PWM_DUTY_MAX)

#define IBRAKE_GAIN                     (5)//刹车电流放大倍数，未使用
#define IBRAKE_PID_RF                   (Q32I_)(Q14I_CURRENT_MOTOR_TO_PU(0.5f * MOTOR_CURRENT_BRAKE_A))

#define IBRAKE_PID_KP                   (Q32I_)(0.010f * MATH_PID_MAX)
#define IBRAKE_PID_KI                   (Q32I_)(0.010f * MATH_PID_MAX)
#define IBRAKE_PID_KD                   (Q32I_)(0.000f * MATH_PID_MAX)
#define IBRAKE_PID_STEPMAX              (Q32I_)( 0.010f * HAL_PWM_DUTY_MAX)
#define IBRAKE_PID_STEPMIN              (Q32I_)(-0.010f * HAL_PWM_DUTY_MAX)
#define IBRAKE_PID_OUTMAX               (DUTY_CTRL_MAX)
#define IBRAKE_PID_OUTMIN               (DUTY_CTRL_MIN)

//刹车时间
#define NO_BRAKE_TIME                   (100U)              //ms，第1段自由滑行
#define SLOW_BRAKE_TIME                 (100U)              //ms，第2段馈电刹车，如果没有使能，则跳过第2阶段
#define SHORT_BRAKE_TIME                (1000U)             //ms，第3段短接刹车

//堵转保护参数
#define MOTOR_STALL_SWITCH_COEFF        (31U)  //base64
#define MOTOR_STALL_ERROR_TIME          (200U)  //ms，堵转时间
#define MOTOR_STALL_CURRENT_ERROR_TIME  (50U)


typedef enum{
    MOTOR_STATE_PRE,
    MOTOR_STATE_INIT,
    MOTOR_STATE_IDLE,
    MOTOR_STATE_BOOT,
    MOTOR_STATE_POSITION,
    MOTOR_STATE_RUN,
    MOTOR_STATE_BRAKE,
}EM_MOTOR_STATE_FLOW;

typedef union{
    ALL all;
    struct{
        BIT motor_run_flag      :1;//电机运行标志位
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
    EM_MOTOR_STATE_FLOW         Motor_Flow;
    UN_MOTOR_STATE_FLAG         Motor_State_Flag;
    UN_MOTOR_ERROR_FLAG         Motor_Error_Flag;
    
    ST_MS_OFFSET                MS_OFFSET;
    ST_MS_FLYING                MS_FLYING;
    ST_MS_BOOT                  MS_BOOT;
    ST_MS_POSITION              MS_POSITION;
    ST_BRAKE_CONTROL            BRAKE_CTRL;
    
    ST_MS_CONTROL               MS_CTRL;
    
    Q32I_                       Q14I_IPHASE_MAX_PU;
    Q32U_                       flow_cnt;
}ST_MOTOR_TASK;

extern ST_MOTOR_TASK  Motor;

#endif /* MotorPara_H */
