/**************************************************************************************************
*     File Name :                        MCSQ_PARA.h
*     Library/Module Name :              MCSQ
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制参数初始化头文件
**************************************************************************************************/

#ifndef MCSQ_PARA_H
#define MCSQ_PARA_H


#include "MCSQ_BLDC.h"
#include "MC_ERR.h"


#define SPEED_CLOSE_EN                  (1U)        //0：开环，1：转速环
#define I_BUS_CLOSE_EN                  (1U)        //母线电流限流使能，0：未使能，1：母线电流环
#define P_BUS_CLOSE_EN                  (1U)        //母线电流限流使能，0：未使能，1：功率环，如果同时使能了电流环和功率环，只有电流环起作用


//电流采样偏置检测
#define CURRENT_OFFSET_VOLTAGE_V        (HAL_ADC_CURRENT_OFFSET)                                                        //V，电流采样偏置电压
#define CURRENT_OFFSET_lsb              (Q32U_)(CURRENT_OFFSET_VOLTAGE_V*HAL_ADC_SCALE_BIT/HAL_ADC_REF_VOLTAGE_V)       //lsb，电流采样偏置
#define CURRENT_OFFSET_TL_V             (0.2f)                                                                          //V，电流采样偏置偏差阈值
#define CURRENT_OFFSET_TL_lsb           (Q32U_)(CURRENT_OFFSET_TL_V*HAL_ADC_SCALE_BIT/HAL_ADC_REF_VOLTAGE_V)            //lsb，电流采样偏置偏差阈值
#define CURRENT_OFFSET_MAX_lsb          (CURRENT_OFFSET_lsb + CURRENT_OFFSET_TL_lsb)                                    //lsb，电流采样偏置上限
#define CURRENT_OFFSET_MIN_lsb          (CURRENT_OFFSET_lsb - CURRENT_OFFSET_TL_lsb)                                    //lsb，电流采样偏置下限
#define CURRENT_OFFSET_COUNT            (20U)                                                                           //电流采样偏置检测次数


//顺风检测
#define FREE_FLYING_TL_lsb              (150U)              //lsb，顺风检测电压阈值
#define FREE_FLYING_COUNT               (20U)               //顺风检测电压判断次数
#define FREE_FLYING_FILTER              (2U)                //滤波次数


//电机静止检测  
#define BOOT_CHECK_TL_lsb               (150U)                      //电机静止检测反电动势阈值
#define BOOT_CHECK_COUNT                (10U)                       //电机静止检测判断次数
#define BOOT_CHECK_DUTY                 (Q14I_DUTY_TO_PU(0.500f))   //电机静止检测占空比


//脉冲定位 
#define POSITION_DUTY                   (Q14I_DUTY_TO_PU(0.500f))   //1kHz，脉冲定位占空比
#define POSITION_TL_lsb                 (1000U)                     //脉冲定位是否成功判断阈值


//滤波器系数
#define IPHASE_FILTER_COEFF             (500)                       //0~16384
#define FREQ_FILTER_COEFF               (500)                       //0~16384
#define IBUS_FILTER_COEFF               (500)                       //0~16384


//换向系数
#define DIAG_CROSS_RISE_TL              (14000U)                    //0~16384
#define DIAG_CROSS_FALL_TL              (2384U)                     //0~16384
#define FLUX_CROSS_RISE_TL              (8192U)                     //0~16384
#define FLUX_CROSS_FALL_TL              (8192U)                     //0~16384

#define DIAG_CROSS_FILTER               (2U)                        //滤波次数
#define FLUX_CROSS_FILTER               (2U)                        //滤波次数
#define BEMF_CROSS_FILTER               (2U)                        //滤波次数

#define BEMF_CROSS_DELAY_COEFF          (4096U/6U)                  //0~8192，延迟换向比例，8192为理论的30度


//换向算法切换
#define FLUX_TO_BEMF_FREQ               (Q14I_FREQ_TO_PU(0.25f * MOTOR_MAX_FREQ))
#define FLUX_TO_BEMF_NUM                (20U)

#define BEMF_TO_FLUX_FREQ               (Q14I_FREQ_TO_PU(0.20f * MOTOR_MAX_FREQ))
#define BEMF_TO_FLUX_NUM                (20U)


//载频切换
#define PWM_FREQ_START                  (HAL_PWM_INIT_SET)
#define PWM_FREQ_LOW                    (HAL_PWM_RUN1_SET)
#define PWM_FREQ_HIGH                   (HAL_PWM_RUN2_SET)
#define PWM_FREQ_LOW_TO_HIGH_DUTY       (Q14I_DUTY_TO_PU(30.0f*HAL_PWM_RUN1_FREQ/1000.0f))     //30us
#define PWM_FREQ_HIGH_TO_LOW_DUTY       (Q14I_DUTY_TO_PU(40.0f*HAL_PWM_RUN2_FREQ/1000.0f))     //40us


//最大占空比，最小占空比
#define DUTY_RAMP_ADDSTEP               ( Q28I_DUTY_TO_PU(0.020f))
#define DUTY_RAMP_SUBSTEP               (-Q28I_DUTY_TO_PU(0.020f))

#define DUTY_CTRL_MAX                   (Q14I_DUTY_TO_PU(1.000f))
#define DUTY_CTRL_MIN                   (Q14I_DUTY_TO_PU(0.100f))


//转速PID
#define FREQ_RAMP_ADDSTEP               ( Q28I_FREQ_TO_PU(0.005f * MOTOR_MAX_FREQ))
#define FREQ_RAMP_SUBSTEP               (-Q28I_FREQ_TO_PU(0.005f * MOTOR_MAX_FREQ))

#define FREQ_PID_KP                     (Q32I_)(0.0001f * MOTOR_Q14_PU)
#define FREQ_PID_KI                     (Q32I_)(0.0050f * MOTOR_Q14_PU)
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
#define BRAKE_DUTY_RAMP_ADDSTEP         ( Q28I_DUTY_TO_PU(0.020f))
#define BRAKE_DUTY_RAMP_SUBSTEP         (-Q28I_DUTY_TO_PU(0.020f))

#define BRAKE_DUTY_CTRL_MAX             (Q14I_DUTY_TO_PU(0.400f))
#define BRAKE_DUTY_CTRL_MIN             (Q14I_DUTY_TO_PU(0.200f))


//刹车时间
#define NO_BRAKE_TIME                   (100U)              //ms，第1段自由滑行
#define SLOW_BRAKE_TIME                 (0U)                //ms，第2段馈电刹车
#define SHORT_BRAKE_TIME                (200U)              //ms，第3段短接刹车


//堵转保护参数
#define MOTOR_STALL_SWITCH_COEFF        (31U)   //base64，换相波动堵转判断系数
#define MOTOR_STALL_ERROR_TIME          (2000U) //ms，堵转时间


typedef enum{
    MOTOR_STATE_PRE,            //参数复位阶段
    MOTOR_STATE_INIT,           //硬件初始化阶段
    MOTOR_STATE_IDLE,           //电机静止检测阶段
    MOTOR_STATE_BOOT,           //自举电容充电阶段
    MOTOR_STATE_POSITION,       //脉冲定位阶段阶段
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
    }bit;
}UN_MOTOR_STATE_FLAG;

typedef struct{
    EM_MOTOR_STATE_FLOW         Motor_Flow;
    UN_MOTOR_STATE_FLAG         Motor_State_Flag;
    
    ST_MCSQ_CONTROL             MCSQ_CTRL;
    ST_MOTOR_ERROR              MC_ERR;
}ST_MOTOR_TASK;


extern ST_MOTOR_TASK  Motor;


#endif /* MCSQ_PARA_H */
