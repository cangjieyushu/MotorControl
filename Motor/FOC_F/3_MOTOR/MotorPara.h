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


//电机openloop相关参数 
#define MOTOR_OPENLOOP_SRAD                 (5.0f * MATH_2PI_F)             //Hz,电机OPENLOOP切换closeloop1转速
#define MOTOR_OPENLOOP_SWITCH_TIME          (50)                            //ms,电机OPENLOOP切换closeloop1时间

//电机closeloop1相关参数，闭环开始阶段，使用反正切角度  
#define MOTOR_CLOSELOOP1_STEP               (0.1f * MATH_2PI_F)             //Hz/s,电机closeloop1增速步长
#define MOTOR_CLOSELOOP1_SRAD               (30.0f * MATH_2PI_F)            //Hz,电机closeloop1切换closeloop2转速
#define MOTOR_CLOSELOOP1_SWITCH_TIME        (100)                           //ms,电机closeloop1切换closeloop2的时间

//电机closeloop2相关参数，闭环运行阶段，使用锁相环角度           
#define MOTOR_CLOSELOOP2_SRAD_TARGET        (MOTOR_MAX_SRAD)                //Hz,电机closeloop2目标转速
#define MOTOR_CLOSELOOP2_STEP               (0.025f * MATH_2PI_F)           //Hz/s,电机closeloop2增速步长 

//电机closeloop3相关参数，闭环结束阶段，低于设定转速后停机 
#define MOTOR_CLOSELOOP3_SRAD_TARGET        (30.0f * MATH_2PI_F)            //Hz,电机closeloop3目标转速
#define MOTOR_CLOSELOOP3_STEP               (0.1f * MATH_2PI_F)             //Hz/s,电机closeloop3增速步长
#define MOTOR_CLOSELOOP3_SRAD               (60.0f * MATH_2PI_F)            //Hz,电机closeloop3切换停止速度
#define MOTOR_CLOSELOOP3_SWITCH_TIME        (20)                            //ms,电机closeloop3切换停止时间


//位置传感器
#define MOTOR_SENSE_MASK                (0F00U)
#define MOTOR_SENSE_NO                  (0100U)                     //无感
#define MOTOR_SENSE_HALL                (0200U)                     //HALL开关传感器

//无感启动算法
#define MOTOR_START_MASK                (00F0U)
#define MOTOR_START_IF                  (0010U)                     //IF
#define MOTOR_START_VF                  (0020U)                     //VF
#define MOTOR_START_FLUX                (0030U)                     //非线性磁链
#define MOTOR_START_HFI                 (0040U)                     //HFI

//无感运行算法
#define MOTOR_SPEED_MASK                (000FU)
#define MOTOR_SPEED_FLUX                (0001U)                     //非线性磁链
#define MOTOR_SPEED_SMO                 (0002U)                     //SMO

//电机运行模式
#define MOTOR_SENSE_MODE                (MOTOR_SENSE_NO)
#define MOTOR_START_MODE                (MOTOR_START_IF)
#define MOTOR_SPEED_MODE                (MOTOR_SPEED_FLUX)


//IF
#define MOTOR_IF_IQRAMP_INIT                (0.0f)                          //A,Iq初始值
#define MOTOR_IF_IQRAMP_TARGET              (4.0f)                          //A,Iq目标值
#define MOTOR_IF_IQRAMP_STEP                (1.0f / 1000.0f)                //A/s,Iq每秒增加步长

#define MOTOR_IF_ANGLERAMP_INIT             (0.0f * MATH_2PI_F)             //Hz,IF速度初始值
#define MOTOR_IF_ANGLERAMP_TARGET           (8.0f * MATH_2PI_F)             //Hz,IF速度目标值
#define MOTOR_IF_ANGLERAMP_STEP             (2.0f * MATH_2PI_F / 1000.0f)   //Hz/s,IF速度每秒增加步长

#define MOTOR_IF_ANGLE_ERROR                (3.0f)                          //rad,IF与观测器角度偏差允许切换值
#define MOTOR_IF_ANGLE_ERROR_RAMP_STEP      (1.0f / 1000.0f)                //Hz,电机IF观测器角度收敛步长

//VF
#define MOTOR_VF_IQRAMP_INIT                (0.1f)                          //V,Vq初始值
#define MOTOR_VF_IQRAMP_TARGET              (0.5f)                          //V,Vq目标值
#define MOTOR_VF_IQRAMP_STEP                (0.2f / 1000.0f)                //V/s,Vq每秒增加步长

#define MOTOR_VF_ANGLERAMP_INIT             (0.0f * MATH_2PI_F)             //Hz,VF速度初始值
#define MOTOR_VF_ANGLERAMP_TARGET           (8.0f * MATH_2PI_F)             //Hz,VF速度目标值
#define MOTOR_VF_ANGLERAMP_STEP             (2.0f * MATH_2PI_F / 1000.0f)   //Hz/s,VF速度每秒增加步长

#define MOTOR_VF_ANGLE_ERROR                (3.0f)                          //rad,VF与观测器角度偏差允许切换值
#define MOTOR_VF_ANGLE_ERROR_RAMP_STEP      (1.0f / 1000.0f)                //Hz,电机VF观测器角度收敛步长


//转速环PID    
#define MOTOR_SPD_PID_Coeff                 (0.25f)                          //转速环PID增益系数
#define MOTOR_SPD_KP_GAIN                   (MOTOR_SPD_PID_Coeff * MOTOR_CURRENT_PHASE_A / MOTOR_MAX_SRAD)
#define MOTOR_SPD_KI_GAIN                   (MOTOR_CURRENT_PHASE_A * MOTOR_CLOSELOOP2_STEP * MOTOR_LTs / MATH_2PI_F / MATH_2PI_F)
#define MOTOR_SPD_KD_GAIN                   (0.0f)
#define MOTOR_SPD_PID_MAX                   (MOTOR_CURRENT_PHASE_A)       //A,转速环输出q轴电流限幅
#define MOTOR_SPD_PID_MIN                   (-MOTOR_CURRENT_PHASE_A)      //A,转速环输出q轴电流限幅

//电流PID 
#define MOTOR_FOC_P_Coeff                   (0.05f)                         //电流环P增益系数
#define MOTOR_FOC_KP_GAIN                   (MOTOR_FOC_P_Coeff * MOTOR_Ls * MATH_2PI_F / MOTOR_HTs)
#define MOTOR_FOC_KI_GAIN                   (MOTOR_FOC_KP_GAIN * MOTOR_HTs * MOTOR_Rs / MOTOR_Ls)
#define MOTOR_FOC_KD_GAIN                   (0.0f)
//dq轴输出电压限制，如果保证电压矢量为圆形，设置为0.5774f，如果需要过调制，则最大为0.6667f
#define MOTOR_VS_SCALE                      (0.5774f)


//观测器PLL系数
#define MOTOR_PLL_KI_Coeff                  (0.1f)
#define MOTOR_PLL_KP_Coeff                  (MOTOR_PLL_KI_Coeff*MOTOR_PLL_KI_Coeff)
#define USER_PLL_SPEED_LPF_COEFF            (0.05f)                     //0~1，越小滤波越深

//非线性磁链观测器  
#define MOTOR_FLUX_KT                       (2.0f / MOTOR_VOLTAGE_V / MOTOR_FLUX / MOTOR_FLUX / MOTOR_FLUX) //增益系数

#define MOTOR_FLUX_PLL_KP                   (MOTOR_PLL_KP_Coeff * MOTOR_MAX_SRAD * MOTOR_MAX_SRAD / MOTOR_FLUX)  //锁相环比例系数
#define MOTOR_FLUX_PLL_KI                   (MOTOR_PLL_KI_Coeff * MOTOR_MAX_SRAD / MOTOR_FLUX)                   //锁相环积分系数
#define MOTOR_FLUX_PLL_KD                   (0.0f)                    //锁相环微分系数
#define MOTOR_FLUX_PLL_MAX                  (10.0f * MOTOR_MAX_SRAD)   //锁相环最大输出
#define MOTOR_FLUX_PLL_MIN                  (-10.0f * MOTOR_MAX_SRAD)  //锁相环最小输出

//SMO观测器            
#define MOTOR_SMO_K1                        (8.00f * MOTOR_VOLTAGE_V / MOTOR_CURRENT_PHASE_A)           //增益系数1
#define MOTOR_SMO_K2                        (0.02f * MOTOR_VOLTAGE_V / MOTOR_CURRENT_PHASE_A)           //增益系数2

#define MOTOR_SMO_PLL_KP                    (MOTOR_PLL_KP_Coeff * MOTOR_MAX_SRAD * MOTOR_MAX_SRAD / MOTOR_VOLTAGE_V)    //锁相环比例系数
#define MOTOR_SMO_PLL_KI                    (MOTOR_PLL_KI_Coeff * MOTOR_MAX_SRAD / MOTOR_VOLTAGE_V)                     //锁相环积分系数
#define MOTOR_SMO_PLL_KD                    (0.0f)                    //锁相环微分系数
#define MOTOR_SMO_PLL_MAX                   (10.0f * MOTOR_MAX_SRAD)   //锁相环最大输出
#define MOTOR_SMO_PLL_MIN                   (-10.0f * MOTOR_MAX_SRAD)  //锁相环最小输出


//母线电流PID 
#define MOTOR_BUS_P_REf                     (MOTOR_CURRENT_BUS_A)           //母线电流参考值
#define MOTOR_BUS_KP_GAIN                   (2.00f)
#define MOTOR_BUS_KI_GAIN                   (5.0f)
#define MOTOR_BUS_KD_GAIN                   (0.0f)


typedef enum{
    MOTOR_STATE_PRE,
    MOTOR_STATE_INIT,
    MOTOR_STATE_IDLE,
    MOTOR_STATE_BOOT,
    MOTOR_STATE_POSITION,
    MOTOR_STATE_RUN,
    MOTOR_STATE_BRAKE,
}EM_MOTOR_STATE_FLOW;

typedef enum
{
    MOTOR_ALIGNLOOP,   
    MOTOR_OPENLOOP,  
    MOTOR_CLOSELOOP1,
    MOTOR_CLOSELOOP2,
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
    EM_MOTOR_STATE_FLOW         Motor_Flow;
    EM_MOTOR_LOOP_MODE          Motor_Loop_Mode;
    UN_MOTOR_STATE_FLAG         Motor_State_Flag;
    UN_MOTOR_ERROR_FLAG         Motor_Error_Flag;
    
    ST_IF_CONTROL_F             IF_CTRL;
    ST_VF_CONTROL_F             VF_CTRL;
    ST_SVPWM_CONTROL_F          SVPWM_CTRL;
    ST_SRAD_CONTROL_F           SRAD_CTRL;
    ST_CURRENT_CONTROL_F        CURRENT_CTRL;
    
    ST_FLUX_CONTROL_F           FLUX_CTRL;
    ST_SMO_CONTROL_F            SMO_CTRL;
    
    Q32U_                       flow_cnt;
    float                       F_Iphase_Max;
}ST_MOTOR_TASK;


extern ST_MOTOR_TASK  Motor;

#endif /* MotorPara_H */
