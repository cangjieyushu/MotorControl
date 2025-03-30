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
#include "MotorDent.h"
#include "MotorEst.h"
#include "MotorFoc.h"
#include "MotorSQ.h"

//启动算法选择
#define MOTOR_OPENLOOP_PARAID           (00U)
#define MOTOR_OPENLOOP_IF               (01U)
#define MOTOR_OPENLOOP_VF               (02U)
#define MOTOR_OPENLOOP_HFI              (03U)
#define MOTOR_OPENLOOP_FLUX             (04U)
#define MOTOR_OPENLOOP_MRAS             (05U)
#define MOTOR_OPENLOOP_MODE             MOTOR_OPENLOOP_IF

//观测器选择
#define MOTOR_EST_FLUX                  (10U)
#define MOTOR_EST_SMO                   (11U)
#define MOTOR_EST_MRAS                  (12U)
#define MOTOR_EST_MODE                  MOTOR_EST_SMO


//静态参数辨识
#define MOTOR_PARAID_ID_TARGET1         (1.0f)                   //A,Id目标值
#define MOTOR_PARAID_ID_TARGET2         (2.0f)                   //A,Id目标值

#define MOTOR_PARAID_UD_REF             (0.2f * MOTOR_VS_SCALE * MOTOR_VOLTAGE_V)      //V,HFI高频注入电压幅值
#define MOTOR_PARAID_UD_PERIOD          (2.0f)                   //kHz，注入频率
#define MOTOR_PARAID_UDQ_COEFF          (0.50f)                  //调制度限制

#define MOTOR_PARAID_LPF_COEFF          (0.05f)                  //0~1，越小滤波越深
#define MOTOR_PARAID_HPF_COEFF          (0.999f)                 //0~1，越大滤波越深
#define MOTOR_PARAID_RS_TIME            (2000U)                  //ms,电机电阻阶段
#define MOTOR_PARAID_LS_TIME            (2000U)                  //ms,电机电感阶段
#define MOTOR_PARAID_FLUX_TIME          (10000U)                 //ms,电机磁链阶段


//电流采样偏置检测
#define CURRENT_OFFSET_VOLTAGE_V        (HAL_ADC_CURRENT_OFFSET)                            //V，电流采样偏置电压
#define CURRENT_OFFSET_lsb              (Q32U_)(CURRENT_OFFSET_VOLTAGE_V*HAL_ADC_SCALE_BIT/HAL_ADC_REF_VOLTAGE_V)//lsb，电流采样偏置
#define CURRENT_OFFSET_TL_lsb           (200U)                                              //lsb，电流采样偏置偏差阈值
#define CURRENT_OFFSET_MAX_lsb          (CURRENT_OFFSET_lsb + CURRENT_OFFSET_TL_lsb)        //lsb，电流采样偏置上限
#define CURRENT_OFFSET_MIN_lsb          (CURRENT_OFFSET_lsb - CURRENT_OFFSET_TL_lsb)        //lsb，电流采样偏置下限
#define CURRENT_OFFSET_NUM              (20U)                                               //电流采样偏置检测次数

//电机静止检测  
#define BOOT_CHECK_DUTY                 (HAL_PWM_DUTY_50_PERCENT)   //电机静止检测占空比
#define BOOT_CHECK_TL_lsb               (50U)                       //电机静止检测反电动势阈值
#define BOOT_CHECK_NUM                  (10U)                       //电机静止检测判断次数
#define BOOT_CHECK_TIME                 (5000U)                     //电机静止检测总次数

//刹车占空比控制
#define BRAKE_DUTY_RAMP_ADDSTEP         (Q32I_)( 0.020f * HAL_PWM_DUTY_MAX_F)
#define BRAKE_DUTY_RAMP_SUBSTEP         (Q32I_)(-0.020f * HAL_PWM_DUTY_MAX_F)

#define BRAKE_DUTY_CTRL_MAX             (Q32I_)(0.400f * HAL_PWM_DUTY_MAX_F)
#define BRAKE_DUTY_CTRL_MIN             (Q32I_)(0.200f * HAL_PWM_DUTY_MAX_F)

//刹车时间
#define NO_BRAKE_TIME                   (100U)              //ms，第1段自由滑行
#define SLOW_BRAKE_TIME                 (0U)                //ms，第2段馈电刹车
#define SHORT_BRAKE_TIME                (200U)              //ms，第3段短接刹车


//电机alignloop相关参数 
#define MOTOR_ALIGNLOOP_RAMP_INIT           (0.0f)                     		//A,Iq初始值
#define MOTOR_ALIGNLOOP_RAMP_TARGET         (1.0f)                    	 	//A,Iq目标值
#define MOTOR_ALIGNLOOP_RAMP_STEP           (1.0f * MOTOR_LTs)        		//A/s,Iq每秒增加步长
#define MOTOR_ALIGNLOOP_TIME1               (500U)                          //ms,电机alignloop第一阶段
#define MOTOR_ALIGNLOOP_TIME2               (500U)                          //ms,电机alignloop第二阶段
#define MOTOR_ALIGNLOOP_TIME3               (500U)                          //ms,电机alignloop第三阶段

//电机openloop相关参数 
#define MOTOR_OPENLOOP_MIN_TIME             (5000U)                         //ms,电机openloop最小时间
#define MOTOR_OPENLOOP_SWITCH_SRAD          (10.0f * MATH_2PI_F)            //Hz,电机openloop切换closeloop1转速
#define MOTOR_OPENLOOP_SWITCH_TIME          (50U)                           //ms,电机openloop切换closeloop1时间

//电机closeloop1相关参数，闭环开始阶段 
#define MOTOR_CLOSELOOP_STEP                (0.5f * MATH_2PI_F)             //Hz/ms,电机closeloop增速步长


//IF
#define MOTOR_IF_IQRAMP_INIT                (0.0f)                          //A,Iq初始值
#define MOTOR_IF_IQRAMP_TARGET              (2.0f)                          //A,Iq目标值
#define MOTOR_IF_IQRAMP_STEP                (1.0f * MOTOR_LTs)              //A/s,Iq每秒增加步长

#define MOTOR_IF_ANGLERAMP_INIT             (0.0f * MATH_2PI_F)             //Hz,IF速度初始值
#define MOTOR_IF_ANGLERAMP_TARGET           (20.0f * MATH_2PI_F)            //Hz,IF速度目标值
#define MOTOR_IF_ANGLERAMP_STEP             (5.0f * MATH_2PI_F * MOTOR_LTs) //Hz/s,IF速度每秒增加步长

#define MOTOR_IF_ANGLE_ERROR                (1.5f)                          //rad,IF与观测器角度偏差允许切换值
#define MOTOR_IF_ANGLE_ERROR_RAMP_STEP      (1.0f * MOTOR_LTs)              //Hz,电机IF观测器角度收敛步长

//VF
#define MOTOR_VF_VQRAMP_INIT                (0.0f)                          //V,Vq初始值
#define MOTOR_VF_VQRAMP_TARGET              (2.0f)                          //V,Vq目标值
#define MOTOR_VF_VQRAMP_STEP                (1.0f * MOTOR_LTs)              //V/s,Vq每秒增加步长

#define MOTOR_VF_ANGLERAMP_INIT             (0.0f * MATH_2PI_F)             //Hz,VF速度初始值
#define MOTOR_VF_ANGLERAMP_TARGET           (20.0f * MATH_2PI_F)            //Hz,VF速度目标值
#define MOTOR_VF_ANGLERAMP_STEP             (5.0f * MATH_2PI_F * MOTOR_LTs) //Hz/s,VF速度每秒增加步长

#define MOTOR_VF_ANGLE_ERROR                (1.5f)                          //rad,VF与观测器角度偏差允许切换值
#define MOTOR_VF_ANGLE_ERROR_RAMP_STEP      (1.0f * MOTOR_LTs)              //Hz,电机VF观测器角度收敛步长


//转速环PID    
#define MOTOR_SPD_PID_Coeff                 (0.80f)                         //转速环PID增益系数
#define MOTOR_SPD_KP_GAIN                   (MOTOR_SPD_PID_Coeff * MOTOR_CURRENT_PHASE_A / MOTOR_MAX_SRAD)
#define MOTOR_SPD_KI_GAIN                   (0.02f * MOTOR_CURRENT_PHASE_A * MOTOR_LTs / MATH_2PI_F)
#define MOTOR_SPD_KD_GAIN                   (0.0f)

#define MOTOR_SPD_PID_MAX                   (MOTOR_CURRENT_PHASE_A)         //A,转速环输出q轴电流限幅
#define MOTOR_SPD_PID_MIN                   (-MOTOR_CURRENT_PHASE_A)        //A,转速环输出q轴电流限幅

//电流PID
#define MOTOR_FOC_P_Coeff                   (0.05f)                         //电流环P增益系数
#define MOTOR_FOC_KP_GAIN                   (MOTOR_FOC_P_Coeff * MOTOR_Ls * MATH_2PI_F / MOTOR_HTs)
#define MOTOR_FOC_KI_GAIN                   (MOTOR_FOC_KP_GAIN * MOTOR_HTs * MOTOR_Rs / MOTOR_Ls)
#define MOTOR_FOC_KD_GAIN                   (0.0f)
//dq轴输出电压限制，如果保证电压矢量为圆形，设置为0.5774f，如果需要过调制，则最大为0.6667f
#define MOTOR_VS_SCALE                      (0.6667f)


//观测器PLL系数
#define MOTOR_PLL_Coeff                     (0.20f)
#define USER_PLL_SPEED_LPF_COEFF            (0.05f)                     //0~1，越小滤波越深

//HFI观测器
#define MOTOR_HFI_TARGET                    (10.0f * MATH_2PI_F)                            //Hz,HFI速度目标值
#define MOTOR_HFI_UD_REF                    (0.20f * MOTOR_VS_SCALE * MOTOR_VOLTAGE_V)      //V,HFI高频注入电压幅值
#define MOTOR_HFI_UD_PERIOD                 (4.0f)                                          //kHz，注入频率
#define MOTOR_HFI_UDQ_COEFF                 (0.50f)                                         //调制度限制
#define MOTOR_HFI_NS_TIME                   (100U)                                          //电机HFI

#define MOTOR_HFI_PLL_KP                    (2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_SRAD / (0.05f * MOTOR_CURRENT_PHASE_A))                         //锁相环比例系数
#define MOTOR_HFI_PLL_KI                    (MATH_SQUARE_F(MOTOR_PLL_Coeff * MOTOR_MAX_SRAD) * MOTOR_HTs / (0.05f * MOTOR_CURRENT_PHASE_A))     //锁相环积分系数
#define MOTOR_HFI_PLL_KD                    (0.0f)                    	//锁相环微分系数
#define MOTOR_HFI_PLL_MAX                   ( 10.0f * MOTOR_MAX_SRAD)   //锁相环最大输出
#define MOTOR_HFI_PLL_MIN                   (-10.0f * MOTOR_MAX_SRAD)  	//锁相环最小输出05

//非线性磁链观测器  
#define MOTOR_FLUX_GAMMA                    (0.02f * MOTOR_VOLTAGE_V / MOTOR_FLUX / MOTOR_FLUX / MOTOR_FLUX) //增益系数

#define MOTOR_FLUX_PLL_KP                   (2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_SRAD / MOTOR_FLUX)                          //锁相环比例系数
#define MOTOR_FLUX_PLL_KI                   (MATH_SQUARE_F(MOTOR_PLL_Coeff * MOTOR_MAX_SRAD) * MOTOR_HTs / MOTOR_FLUX)      //锁相环积分系数
#define MOTOR_FLUX_PLL_KD                   (0.0f)                    	//锁相环微分系数
#define MOTOR_FLUX_PLL_MAX                  ( 2.0f * MOTOR_MAX_SRAD)    //锁相环最大输出
#define MOTOR_FLUX_PLL_MIN                  (-2.0f * MOTOR_MAX_SRAD)  	//锁相环最小输出

//SMO观测器
#define MOTOR_SMO_K1                        (5.00f)           			//增益系数

#define MOTOR_SMO_PLL_KP                    (2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_SRAD / MOTOR_VOLTAGE_V)                     //锁相环比例系数
#define MOTOR_SMO_PLL_KI                    (MATH_SQUARE_F(MOTOR_PLL_Coeff * MOTOR_MAX_SRAD) * MOTOR_HTs / MOTOR_VOLTAGE_V) //锁相环积分系数
#define MOTOR_SMO_PLL_KD                    (0.0f)                    	//锁相环微分系数
#define MOTOR_SMO_PLL_MAX                   ( 2.0f * MOTOR_MAX_SRAD)    //锁相环最大输出
#define MOTOR_SMO_PLL_MIN                   (-2.0f * MOTOR_MAX_SRAD)  	//锁相环最小输出

//MRAS
#define MOTOR_MRAS_PLL_KP                   (0.5f)                      //锁相环比例系数
#define MOTOR_MRAS_PLL_KI                   (0.2f)                      //锁相环积分系数
#define MOTOR_MRAS_PLL_KD                   (0.0f)                    	//锁相环微分系数
#define MOTOR_MRAS_PLL_MAX                  ( 2.0f * MOTOR_MAX_SRAD)    //锁相环最大输出
#define MOTOR_MRAS_PLL_MIN                  (-2.0f * MOTOR_MAX_SRAD)  	//锁相环最小输出


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
        BIT paraid_finish       :1;//电机自学习结束
    }bit;
}UN_MOTOR_ERROR_FLAG;

typedef struct{
    ST_RAMP_F                   Align_Ramp;
    Q32U_                       _V_Q32U_Align_cnt;
    Q32U_                       _P_Q32U_Align_Time1;
    Q32U_                       _P_Q32U_Align_Time2;
    Q32U_                       _P_Q32U_Align_Time3;
        
    Q32U_                       _V_Q32U_Open_cnt;
    Q32U_                       _V_Q32U_Open_min_cnt;
    Q32U_                       _P_Q32U_Open_Min_Time;
    float                       _P_F_Open_Switch_SRAD;
    Q32U_                       _P_Q32U_Open_Switch_Time;
    
    Q32U_                       _V_Q32U_Close_cnt;
    float                       _P_F_Close_SRAD_Step;
}ST_LOOP_CONTROL_F;

typedef struct{
    EM_MOTOR_STATE_FLOW         Motor_Flow;
    EM_MOTOR_LOOP_MODE          Motor_Loop_Mode;
    UN_MOTOR_STATE_FLAG         Motor_State_Flag;
    UN_MOTOR_ERROR_FLAG         Motor_Error_Flag;
    
    ST_PARA_ID_F                PARA_ID;
    ST_MS_OFFSET                MS_OFFSET;
    ST_MS_BOOT                  MS_BOOT;
    ST_BRAKE_CONTROL            BRAKE_CTRL;
    
    ST_LOOP_CONTROL_F           LOOP_CTRL;
    ST_IF_CONTROL_F             IF_CTRL;
    ST_VF_CONTROL_F             VF_CTRL;
    ST_SVPWM_CONTROL_F          SVPWM_CTRL;
    ST_SRAD_CONTROL_F           SRAD_CTRL;
    ST_CURRENT_CONTROL_F        CURRENT_CTRL;
    
    ST_HFI_CONTROL_F            HFI_CTRL;
    ST_FLUX_CONTROL_F           FLUX_CTRL;
    ST_SMO_CONTROL_F            SMO_CTRL;
    ST_MRAS_CONTROL_F           MRAS_CTRL;
    
    float                       F_Iphase_Max;
}ST_MOTOR_TASK;


extern ST_MOTOR_TASK  Motor;

#endif /* MotorPara_H */
