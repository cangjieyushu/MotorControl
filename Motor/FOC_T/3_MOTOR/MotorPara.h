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


//电机alignloop相关参数 
#define MOTOR_ALIGNLOOP_RAMP_INIT           ((Q32I_)(0.0000f*Q14I_CURRENT_PHASE_PU))  //Iq初始值
#define MOTOR_ALIGNLOOP_RAMP_TARGET         ((Q32I_)(0.2000f*Q14I_CURRENT_PHASE_PU))  //Iq目标值
#define MOTOR_ALIGNLOOP_RAMP_STEP           ((Q32I_)(0.0050f*Q14I_MAX_SRAD_PU))         //Iq每秒增加步长
#define MOTOR_ALIGNLOOP_TIME1               (500U)                                      //ms,电机alignloop第一阶段
#define MOTOR_ALIGNLOOP_TIME2               (500U)                                      //ms,电机alignloop第二阶段
#define MOTOR_ALIGNLOOP_TIME3               (500U)                                      //ms,电机alignloop第三阶段

//电机openloop相关参数 
#define MOTOR_OPENLOOP_MIN_TIME             (5000U)                                     //ms,电机openloop最小时间
#define MOTOR_OPENLOOP_SWITCH_SRAD          ((Q32I_)(0.2000f*Q14I_MAX_SRAD_PU))         //电机openloop切换closeloop1转速
#define MOTOR_OPENLOOP_SWITCH_TIME          (50U)                                       //ms,电机openloop切换closeloop1时间

//电机closeloop1相关参数，闭环开始阶段 
#define MOTOR_CLOSELOOP1_TARGET_SRAD        ((Q32I_)(0.5000f*Q14I_MAX_SRAD_PU))         //电机closeloop1目标转速
#define MOTOR_CLOSELOOP1_STEP               ((Q32I_)(0.0050f*Q14I_MAX_SRAD_PU))         //电机closeloop1增速步长
#define MOTOR_CLOSELOOP1_SWITCH_SRAD        ((Q32I_)(0.3000f*Q14I_MAX_SRAD_PU))         //电机closeloop1切换closeloop2转速
#define MOTOR_CLOSELOOP1_SWITCH_TIME        (100U)                                      //ms,电机closeloop1切换closeloop2的时间

//电机closeloop2相关参数，闭环运行阶段         
#define MOTOR_CLOSELOOP2_SRAD_TARGET        ((Q32I_)(0.5000f*Q14I_MAX_SRAD_PU))         //Hz,电机closeloop2目标转速
#define MOTOR_CLOSELOOP2_STEP               ((Q32I_)(0.0050f*Q14I_MAX_SRAD_PU))         //Hz/ms,电机closeloop2增速步长 


//IF
#define MOTOR_IF_IQRAMP_INIT                ((Q32I_)(0.0000f*Q14I_CURRENT_PHASE_PU))  //Iq初始值
#define MOTOR_IF_IQRAMP_TARGET              ((Q32I_)(0.3000f*Q14I_CURRENT_PHASE_PU))  //Iq目标值
#define MOTOR_IF_IQRAMP_STEP                ((Q32I_)(0.0050f*Q14I_CURRENT_PHASE_PU))  //Iq每秒增加步长

#define MOTOR_IF_ANGLERAMP_INIT             ((Q32I_)(0.0000f*Q14I_MAX_SRAD_PU))         //IF速度初始值
#define MOTOR_IF_ANGLERAMP_TARGET           ((Q32I_)(0.1000f*Q14I_MAX_SRAD_PU))         //IF速度目标值
#define MOTOR_IF_ANGLERAMP_STEP             ((Q32I_)(0.0001f*Q14I_MAX_SRAD_PU))         //IF速度每秒增加步长

#define MOTOR_IF_ANGLE_ERROR                (1024)                                      //rad,IF与观测器角度偏差允许切换值
#define MOTOR_IF_ANGLE_ERROR_RAMP_STEP      (1)                                         //rad,电机IF观测器角度收敛步长

//VF
#define MOTOR_VF_VQRAMP_INIT                ((Q32I_)(0.0000f*Q14I_VOLTAGE_PU))          //Vq初始值
#define MOTOR_VF_VQRAMP_TARGET              ((Q32I_)(0.0500f*Q14I_VOLTAGE_PU))          //Vq目标值
#define MOTOR_VF_VQRAMP_STEP                ((Q32I_)(0.0050f*Q14I_VOLTAGE_PU))          //Vq每秒增加步长

#define MOTOR_VF_ANGLERAMP_INIT             ((Q32I_)(0.0000f*Q14I_MAX_SRAD_PU))         //VF速度初始值
#define MOTOR_VF_ANGLERAMP_TARGET           ((Q32I_)(0.1000f*Q14I_MAX_SRAD_PU))         //VF速度目标值
#define MOTOR_VF_ANGLERAMP_STEP             ((Q32I_)(0.0001f*Q14I_MAX_SRAD_PU))         //VF速度每秒增加步长

#define MOTOR_VF_ANGLE_ERROR                (1024)                                      //rad,VF与观测器角度偏差允许切换值
#define MOTOR_VF_ANGLE_ERROR_RAMP_STEP      (1)                                         //rad,电机VF观测器角度收敛步长


//转速环PID    
#define MOTOR_SPD_PID_Coeff                 (0.05f)                                     //转速环PID增益系数
#define MOTOR_SPD_KP_GAIN                   (Q32I_)(MOTOR_Q14_PU * MOTOR_SPD_PID_Coeff * MOTOR_CURRENT_PHASE_A / MOTOR_MAX_SRAD * W_BASE / I_BASE)
#define MOTOR_SPD_KI_GAIN                   (Q32I_)(MOTOR_Q14_PU * 0.1f * MOTOR_CURRENT_PHASE_A * MOTOR_LTs / MATH_2PI_F * W_BASE / I_BASE)
#define MOTOR_SPD_KD_GAIN                   (Q32I_)(0.0f)
#define MOTOR_SPD_PID_MAX                   ( (Q32I_)(1.0000f*Q14I_CURRENT_PHASE_PU)) //A,转速环输出q轴电流限幅
#define MOTOR_SPD_PID_MIN                   (-(Q32I_)(1.0000f*Q14I_CURRENT_PHASE_PU)) //A,转速环输出q轴电流限幅

//电流PID
#define MOTOR_FOC_P_Coeff                   (0.01f)                       //电流环P增益系数
#define MOTOR_FOC_KP_GAIN                   (Q32I_)(MOTOR_Q14_PU * MOTOR_FOC_P_Coeff * MOTOR_Ls * MATH_2PI_F / MOTOR_HTs * I_BASE / V_BASE)
#define MOTOR_FOC_KI_GAIN                   (Q32I_)(MOTOR_FOC_KP_GAIN * MOTOR_HTs * MOTOR_Rs / MOTOR_Ls * I_BASE / V_BASE)
#define MOTOR_FOC_KD_GAIN                   (Q32I_)(0.0f)
//dq轴输出电压限制，如果保证电压矢量为圆形，设置为0.5774f，如果需要过调制，则最大为0.6667f
#define MOTOR_VS_SCALE                      ((Q32I_)(0.5774f * MOTOR_Q14_PU))


//观测器PLL系数
#define MOTOR_PLL_Coeff                     (0.2f)
#define USER_PLL_SPEED_LPF_COEFF            (10)                        //0~256，越小滤波越深

//非线性磁链观测器  
#define MOTOR_FLUX_KT                       (Q32I_)(Q28U_MAX * 0.02f * Q14I_VOLTAGE_PU / Q14I_FLUX_PU / (Q14I_FLUX_PU*Q14I_FLUX_PU/MOTOR_Q14_PU))      //增益系数
#define MOTOR_FLUX_R_Coeff                  (Q32I_)(MOTOR_Q14_PU * 0.75f)           //电阻系数

#define MOTOR_FLUX_PLL_KP                   (Q32I_)(MOTOR_Q14_PU * 2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_SRAD / Q14I_FLUX_PU)                              //锁相环比例系数
#define MOTOR_FLUX_PLL_KI                   (Q32I_)(MOTOR_Q14_PU * MATH_SQUARE_F(2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_SRAD) * MOTOR_HTs / Q14I_FLUX_PU)   //锁相环积分系数
#define MOTOR_FLUX_PLL_KD                   (Q32I_)(0.0f)                    	    //锁相环微分系数
#define MOTOR_FLUX_PLL_MAX                  (Q32I_)( 2.000f * Q14I_MAX_SRAD_PU)     //锁相环最大输出
#define MOTOR_FLUX_PLL_MIN                  (Q32I_)(-2.000f * Q14I_MAX_SRAD_PU)  	//锁相环最小输出

//SMO观测器            
#define MOTOR_SMO_K1                        (Q32I_)(Q10U_MAX * 2.00f * Q14I_VOLTAGE_PU / Q14I_CURRENT_PHASE_PU)           //增益系数1
#define MOTOR_SMO_K2                        (Q32I_)(MOTOR_Q14_PU * 0.02f * Q14I_VOLTAGE_PU / Q14I_CURRENT_PHASE_PU)       //增益系数2

#define MOTOR_SMO_PLL_KP                    (Q32I_)(MOTOR_Q14_PU * 2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_SRAD / (0.5f * Q14I_VOLTAGE_PU))                              //锁相环比例系数
#define MOTOR_SMO_PLL_KI                    (Q32I_)(MOTOR_Q14_PU * MATH_SQUARE_F(2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_SRAD) * MOTOR_HTs / (0.5f * Q14I_VOLTAGE_PU))   //锁相环积分系数
#define MOTOR_SMO_PLL_KD                    (Q32I_)(0.0f)                    	    //锁相环微分系数
#define MOTOR_SMO_PLL_MAX                   (Q32I_)( 2.000f * Q14I_MAX_SRAD_PU)     //锁相环最大输出
#define MOTOR_SMO_PLL_MIN                   (Q32I_)(-2.000f * Q14I_MAX_SRAD_PU)  	//锁相环最小输出


//母线电流PID 
#define MOTOR_BUS_P_REf                     (MOTOR_CURRENT_BUS_A)           //母线电流参考值
#define MOTOR_BUS_KP_GAIN                   (2.00f)
#define MOTOR_BUS_KI_GAIN                   (5.0f)
#define MOTOR_BUS_KD_GAIN                   (0.0f)


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
    MOTOR_ALIGNLOOP,            //预定位阶段
    MOTOR_OPENLOOP,             //开环阶段
    MOTOR_CLOSELOOP1,           //闭环启动阶段
    MOTOR_CLOSELOOP2,           //闭环运行阶段
}EM_MOTOR_LOOP_MODE;

typedef union{
    ALL all;
    struct{
        BIT motor_run_flag      :1;//电机运行标志位
        BIT pwm_output_flag     :1;//pwm输出使能标志位
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
    ST_RAMP_T                   Align_Ramp;
    Q32U_                       _V_Q32U_Align_cnt;
    Q32U_                       _P_Q32U_Align_Time1;
    Q32U_                       _P_Q32U_Align_Time2;
    Q32U_                       _P_Q32U_Align_Time3;
        
    Q32U_                       _V_Q32U_Open_cnt;
    Q32U_                       _V_Q32U_Open_min_cnt;
    Q32U_                       _P_Q32U_Open_Min_Time;
    Q32I_                       _P_F_Open_Switch_SRAD;
    Q32U_                       _P_Q32U_Open_Switch_Time;
    
    Q32U_                       _V_Q32U_Close1_cnt;
    Q32I_                       _P_F_Close1_Target_SRAD;
    Q32I_                       _P_F_Close1_SRAD_Step;
    Q32I_                       _P_F_Close1_Switch_SRAD;
    Q32U_                       _P_Q32U_Close1_Switch_Time;
    
    Q32U_                       _V_Q32U_Close2_cnt;
    Q32I_                       _P_F_Close2_Target_SRAD;
    Q32I_                       _P_F_Close2_SRAD_Step;
}ST_LOOP_CONTROL_T;

typedef struct{
    EM_MOTOR_STATE_FLOW         Motor_Flow;
    EM_MOTOR_LOOP_MODE          Motor_Loop_Mode;
    UN_MOTOR_STATE_FLAG         Motor_State_Flag;
    UN_MOTOR_ERROR_FLAG         Motor_Error_Flag;
    
    ST_LOOP_CONTROL_T           LOOP_CTRL;
    ST_IF_CONTROL_T             IF_CTRL;
    ST_VF_CONTROL_T             VF_CTRL;
    ST_SVPWM_CONTROL_T          SVPWM_CTRL;
    ST_SRAD_CONTROL_T           SRAD_CTRL;
    ST_CURRENT_CONTROL_T        CURRENT_CTRL;
    
    ST_FLUX_CONTROL_T           FLUX_CTRL;
    ST_SMO_CONTROL_T            SMO_CTRL;
    
    Q32I_                       Q14I_IPHASE_MAX_PU;
}ST_MOTOR_TASK;


extern ST_MOTOR_TASK  Motor;

#endif /* MotorPara_H */
