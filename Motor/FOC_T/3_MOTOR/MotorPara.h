/**************************************************************************************************
*     File Name :                        MotorPara.h
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制参数初始化头文件
**************************************************************************************************/
#ifndef MotorPara_H
#define MotorPara_H

#include "Math.h"
#include "PmsmPara.h"
#include "MotorHal_cfg.h"
#include "MotorEst.h"
#include "MotorFoc.h"
#include "MotorState.h"

//启动算法选择
#define MOTOR_OPENLOOP_PARAID       (00U)
#define MOTOR_OPENLOOP_IF           (01U)
#define MOTOR_OPENLOOP_VF           (02U)
#define MOTOR_OPENLOOP_HFI          (03U)
#define MOTOR_OPENLOOP_FLUX         (04U)
#define MOTOR_OPENLOOP_MRAS         (05U)
#define MOTOR_OPENLOOP_MODE         MOTOR_OPENLOOP_IF

//观测器选择
#define MOTOR_EST_FLUX              (10U)
#define MOTOR_EST_SMO               (11U)
#define MOTOR_EST_MRAS              (12U)
#define MOTOR_EST_MODE              MOTOR_EST_SMO


//电流采样偏置检测
#define CURRENT_OFFSET_VOLTAGE_V        (HAL_ADC_CURRENT_OFFSET)                            //V，电流采样偏置电压
#define CURRENT_OFFSET_lsb              (Q32U_)(CURRENT_OFFSET_VOLTAGE_V*HAL_ADC_SCALE_BIT/HAL_ADC_REF_VOLTAGE_V)    //lsb，电流采样偏置
#define CURRENT_OFFSET_TL_lsb           (200U)                                              //lsb，电流采样偏置偏差阈值
#define CURRENT_OFFSET_MAX_lsb          (CURRENT_OFFSET_lsb + CURRENT_OFFSET_TL_lsb)        //lsb，电流采样偏置上限
#define CURRENT_OFFSET_MIN_lsb          (CURRENT_OFFSET_lsb - CURRENT_OFFSET_TL_lsb)        //lsb，电流采样偏置下限
#define CURRENT_OFFSET_NUM              (20U)                                               //电流采样偏置检测次数

//电机静止检测  
#define BOOT_CHECK_DUTY                 (Q12I_DUTY_TO_PU(0.5f))     //电机静止检测占空比
#define BOOT_CHECK_TL_lsb               (50U)                       //电机静止检测反电动势阈值
#define BOOT_CHECK_NUM                  (10U)                       //电机静止检测判断次数
#define BOOT_CHECK_TIME                 (5000U)                     //电机静止检测总次数

//刹车占空比控制
#define BRAKE_DUTY_RAMP_ADDSTEP         ( Q22I_DUTY_TO_PU(0.02f))
#define BRAKE_DUTY_RAMP_SUBSTEP         (-Q22I_DUTY_TO_PU(0.02f))

#define BRAKE_DUTY_CTRL_MAX             (Q12I_DUTY_TO_PU(0.4f))
#define BRAKE_DUTY_CTRL_MIN             (Q12I_DUTY_TO_PU(0.2f))

//刹车时间
#define NO_BRAKE_TIME                   (100U)              //ms，第1段自由滑行
#define SLOW_BRAKE_TIME                 (0U)                //ms，第2段馈电刹车
#define SHORT_BRAKE_TIME                (200U)              //ms，第3段短接刹车


//电机openloop相关参数 
#define MOTOR_OPENLOOP_MIN_TIME             (5000U)                                 //ms,电机openloop最小时间
#define MOTOR_OPENLOOP_SWITCH_FREQ          (Q14I_FREQ_TO_PU(10.0f))                //Hz,电机openloop切换closeloop转速阈值
#define MOTOR_OPENLOOP_SWITCH_TIME          (50U)                                   //ms,电机openloop切换closeloop转速检测时间

//电机closeloop相关参数，闭环开始阶段 
#define MOTOR_CLOSELOOP_STEP                (Q24I_FREQ_TO_PU(100.0f * MOTOR_LTs))   //Hz/s,电机closeloop每秒增速步长


//IF
#define MOTOR_IF_IQRAMP_INIT                (Q14I_CURRENT_TO_PU(0.0f))              //A,Iq初始值
#define MOTOR_IF_IQRAMP_TARGET              (Q14I_CURRENT_TO_PU(2.0f))              //A,Iq目标值
#define MOTOR_IF_IQRAMP_STEP                (Q24I_CURRENT_TO_PU(1.0f * MOTOR_LTs))  //A/s,Iq每秒增加步长

#define MOTOR_IF_FREQRAMP_INIT              (Q14I_FREQ_TO_PU(0.0f))                 //Hz,IF速度初始值
#define MOTOR_IF_FREQRAMP_TARGET            (Q14I_FREQ_TO_PU(20.0f))                //Hz,IF速度目标值
#define MOTOR_IF_FREQRAMP_STEP              (Q24I_FREQ_TO_PU(5.0f * MOTOR_LTs))     //Hz/s,IF速度每秒增加步长

#define MOTOR_IF_ANGLE_ERROR                (Q12I_ANGLE_TO_PU(1.5f))                //rad,IF与观测器角度偏差允许切换值
#define MOTOR_IF_ANGLE_ERROR_RAMP_STEP      (Q12I_ANGLE_TO_PU(1.0f * MOTOR_LTs))    //rad,电机IF观测器角度收敛步长

//VF
#define MOTOR_VF_VQRAMP_INIT                (Q14I_VOLTAGE_TO_PU(0.0f))              //V,Vq初始值
#define MOTOR_VF_VQRAMP_TARGET              (Q14I_VOLTAGE_TO_PU(2.0f))              //V,Vq目标值
#define MOTOR_VF_VQRAMP_STEP                (Q24I_VOLTAGE_TO_PU(1.0f * MOTOR_LTs))  //V/s,Vq每秒增加步长

#define MOTOR_VF_FREQRAMP_INIT              (Q14I_FREQ_TO_PU(0.0f))                 //Hz,VF速度初始值
#define MOTOR_VF_FREQRAMP_TARGET            (Q14I_FREQ_TO_PU(20.0f))                //Hz,VF速度目标值
#define MOTOR_VF_FREQRAMP_STEP              (Q24I_FREQ_TO_PU(5.0f * MOTOR_LTs))     //Hz/s,VF速度每秒增加步长

#define MOTOR_VF_ANGLE_ERROR                (Q12I_ANGLE_TO_PU(1.5f))                //rad,VF与观测器角度偏差允许切换值
#define MOTOR_VF_ANGLE_ERROR_RAMP_STEP      (Q12I_ANGLE_TO_PU(1.0f * MOTOR_LTs))    //rad,电机VF观测器角度收敛步长


//转速环PID
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
#define MOTOR_PLL_Coeff                     (0.20f)
#define MOTOR_PLL_SPEED_LPF_COEFF           (13)                                //0~256，越小滤波越深
#define MOTOR_MAX_SRAD                      (MOTOR_MAX_FREQ * MATH_2PI_F)

//非线性磁链观测器  
#define MOTOR_FLUX_GAMMA                    ((Q32I_)(0.02f * Q14I_VOLTAGE_PU * ((MOTOR_Q14_PU/Q14I_FLUX_PU)*(MOTOR_Q14_PU/Q14I_FLUX_PU)*(MOTOR_Q14_PU/Q14I_FLUX_PU))))    //增益系数

#define MOTOR_FLUX_PLL_KP                   ((Q32I_)(MOTOR_Q14_PU * 2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_SRAD / Q14I_FLUX_PU))                                        //锁相环比例系数
#define MOTOR_FLUX_PLL_KI                   ((Q32I_)(MOTOR_Q14_PU * MATH_SQUARE_F(2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_SRAD) * MOTOR_HTs / Q14I_FLUX_PU))             //锁相环积分系数
#define MOTOR_FLUX_PLL_KD                   ((Q32I_)(0.0f))                     //锁相环微分系数
#define MOTOR_FLUX_PLL_MAX                  ((Q32I_)( 2.0f * Q14I_MAX_FREQ_PU)) //锁相环最大输出
#define MOTOR_FLUX_PLL_MIN                  ((Q32I_)(-2.0f * Q14I_MAX_FREQ_PU)) //锁相环最小输出

//SMO观测器
#define MOTOR_SMO_K1                        (3500)                              //增益系数

#define MOTOR_SMO_PLL_KP                    ((Q32I_)(MOTOR_Q14_PU * 2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_SRAD / (0.5f * Q14I_VOLTAGE_PU)))                            //锁相环比例系数
#define MOTOR_SMO_PLL_KI                    ((Q32I_)(MOTOR_Q14_PU * MATH_SQUARE_F(2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_SRAD) * MOTOR_HTs / (0.5f * Q14I_VOLTAGE_PU))) //锁相环积分系数
#define MOTOR_SMO_PLL_KD                    ((Q32I_)(0.0f))                     //锁相环微分系数
#define MOTOR_SMO_PLL_MAX                   ((Q32I_)( 2.0f * Q14I_MAX_FREQ_PU)) //锁相环最大输出
#define MOTOR_SMO_PLL_MIN                   ((Q32I_)(-2.0f * Q14I_MAX_FREQ_PU)) //锁相环最小输出


typedef enum{
    MOTOR_STATE_PRE,            //参数复位阶段
    MOTOR_STATE_INIT,           //硬件初始化阶段
    MOTOR_STATE_IDLE,           //电机静止检测阶段
    MOTOR_STATE_BOOT,           //自举电容充电阶段
    MOTOR_STATE_POSITION,       //脉冲定位阶段阶段
    MOTOR_STATE_RUN,            //电机运行阶段
    MOTOR_STATE_BRAKE,          //电机刹车阶段
}EM_MOTOR_STATE_FLOW;

typedef enum
{
    MOTOR_OPENLOOP,             //开环阶段
    MOTOR_CLOSELOOP             //闭环阶段
}EM_MOTOR_LOOP_MODE;

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
    Q32U_                       _V_Q32U_Open_cnt;
    Q32U_                       _V_Q32U_Open_min_cnt;
    Q32U_                       _P_Q32U_Open_Min_Time;
    Q32I_                       _P_Q32I_Open_Switch_Freq;
    Q32U_                       _P_Q32U_Open_Switch_Time;
    
    Q32U_                       _V_Q32U_Close_cnt;
}ST_LOOP_CONTROL_T;

typedef struct{
    EM_MOTOR_STATE_FLOW         Motor_Flow;
    EM_MOTOR_LOOP_MODE          Motor_Loop_Mode;
    UN_MOTOR_STATE_FLAG         Motor_State_Flag;
    UN_MOTOR_ERROR_FLAG         Motor_Error_Flag;
    
    ST_MS_OFFSET                MS_OFFSET;
    ST_MS_BOOT                  MS_BOOT;
    ST_BRAKE_CONTROL            BRAKE_CTRL;
    
    ST_LOOP_CONTROL_T           LOOP_CTRL;
    ST_IF_CONTROL_T             IF_CTRL;
    ST_VF_CONTROL_T             VF_CTRL;
    ST_SVPWM_CONTROL_T          SVPWM_CTRL;
    ST_FREQ_CONTROL_T           FREQ_CTRL;
    ST_CURRENT_CONTROL_T        CURRENT_CTRL;
    
    ST_FLUX_CONTROL_T           FLUX_CTRL;
    ST_SMO_CONTROL_T            SMO_CTRL;
    
    Q32I_                       Q14I_IPHASE_MAX_PU;
}ST_MOTOR_TASK;


extern ST_MOTOR_TASK  Motor;

#endif /* MotorPara_H */
