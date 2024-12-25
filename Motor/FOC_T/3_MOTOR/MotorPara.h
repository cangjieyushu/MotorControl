/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef MotorPara_H
#define MotorPara_H

#include "MotorHal_cfg.h"
#include "MotorFoc.h"
#include "User_Pmsm.h"

//有感算法
#define USER_MOTOR_SENSE_NO             (0000U)
#define USER_MOTOR_SENSE_HALL           (1000U)   //有感霍尔
#define USER_MOTOR_SENSE_RPS            (2000U)   //有感RPS

//无感启动算法
#define USER_MOTOR_START_MASK           (0F00U)
#define USER_MOTOR_START_IF             (0100U)   //IF
#define USER_MOTOR_START_FLUX           (0200U)   //非线性磁链

//无感高速算法
#define USER_MOTOR_SPEED_MASK           (000FU)
#define USER_MOTOR_SPEED_SMO            (0002U)   //SMO
#define USER_MOTOR_SPEED_FLUX           (0001U)   //非线性磁链

//电机运行模式
#define USER_MOTOR_SENSE_MODE           (USER_MOTOR_SENSE_NO)
#define USER_MOTOR_START_MODE           (USER_MOTOR_START_IF)
#define USER_MOTOR_SPEED_MODE           (USER_MOTOR_SPEED_FLUX)


//电机控制模式使能
#define BRAKE_EN            0       //刹车使能
#define SLOW_BRAKE_EN       0       //回馈刹车使能

#define CLOSELOOP3_EN       0       //
#define IBUS_CLOSE_EN       1       //母线电流限流使能


//电流采样偏置检测
#define CURRENT_OFFSET_VOLTAGE_V        (1.65f)                                             //V，电流采样偏置电压
#define CURRENT_OFFSET_lsb              (Q32U_)(HAL_ADC_SCALE_BIT*CURRENT_OFFSET_VOLTAGE_V/HAL_ADC_REF_VOLTAGE_V)    //lsb，电流采样偏置电压
#define CURRENT_OFFSET_TL_lsb           (200U)                                              //lsb，电流采样偏置允许偏差阈值
#define CURRENT_OFFSET_MAX_lsb          (CURRENT_OFFSET_lsb + CURRENT_OFFSET_TL_lsb)        //lsb，电流采样偏置允许偏差最大阈值
#define CURRENT_OFFSET_MIN_lsb          (CURRENT_OFFSET_lsb - CURRENT_OFFSET_TL_lsb)        //lsb，电流采样偏置允许偏差最大阈值
#define CURRENT_OFFSET_NUM              (20U)                                               //电流采样偏置检测次数


//六脉冲定位
#define POSITION_DUTY                   (Q32I_RHT_12(HAL_PWM_DUTY_10_PERCENT*HAL_PWM_COUNT_1K)) //六脉冲定位占空比
#define POSITION_TL_lsb                 (1000U)                                                 //lsb，六脉冲定位电流检测最大阈值


//滤波器系数
#define SRAD_FILTER_COEFF               (10) //0~256
#define IBUS_FILTER_COEFF               (10) //0~256


//IF强拖     
#define LOOP0_IQ_RAMP_INIT              (Q32I_)(Q14I_CURRENT_MOTOR_TO_PU(0.00000f * MOTOR_CURRENT_PHASE_A))   //A,电机LOOP1电流初始值
#define LOOP0_IQ_RAMP_TARGET            (Q32I_)(Q14I_CURRENT_MOTOR_TO_PU(0.20000f * MOTOR_CURRENT_PHASE_A))   //A,电机LOOP1电流目标值
#define LOOP0_IQ_RAMP_ADDSTEP           (Q32I_)(Q14I_CURRENT_MOTOR_TO_PU(0.00001f * MOTOR_CURRENT_PHASE_A))   //A,电机LOOP1电流增加步长

#define LOOP0_ID_RAMP_INIT              (Q32I_)(Q14I_CURRENT_MOTOR_TO_PU(0.00000f * MOTOR_CURRENT_PHASE_A))   //A,电机LOOP1电流初始值
#define LOOP0_ID_RAMP_TARGET            (Q32I_)(Q14I_CURRENT_MOTOR_TO_PU(0.00000f * MOTOR_CURRENT_PHASE_A))   //A,电机LOOP1电流初始值
#define LOOP0_ID_RAMP_ADDSTEP           (Q32I_)(Q14I_CURRENT_MOTOR_TO_PU(0.00010f * MOTOR_CURRENT_PHASE_A))   //A,电机LOOP1电流增加步长

#define LOOP0_SRAD_RAMP_INIT            (Q32I_)(Q14I_SRAD_MOTOR_TO_PU(0.00000f * MOTOR_MAX_SRAD))   //rad,电机IF角度自增初始值
#define LOOP0_SRAD_RAMP_TARGET          (Q32I_)(Q14I_SRAD_MOTOR_TO_PU(0.05000f * MOTOR_MAX_SRAD))   //rad,电机IF角度自增目标值
#define LOOP0_SRAD_RAMP_ADDSTEP         (Q32I_)(Q14I_SRAD_MOTOR_TO_PU(0.00001f * MOTOR_MAX_SRAD))   //rad,电机IF角度自增增加步长
#define LOOP0_ANGLE_ERROR_RAMP_ADDSTEP  (Q32I_)(0.001f * MATH_2PI_U)                              //rad,电机IF角度自增增加步长
        
#define LOOP0_RAD_ERROR                 (Q32I_)(0.005f * MATH_2PI_U)            //rad,电机IF角度与观测器偏差允许切换值
#define LOOP0_RAD_TIME                  (10U)                                   //次（Ts）,电机IF角度与观测器偏差允许切换滤波次数
        
#define LOOP0_SWITCH_SRAD               (Q32I_)(Q14I_SRAD_MOTOR_TO_PU(0.02000f * MOTOR_MAX_SRAD))    //s^-1,电机LOOP0切换LOOP1的转速
#define LOOP0_SWITCH_TIME               (10U)                              //ms,电机LOOP1切换LOOP2的时间

//电机LOOP1  
#define LOOP1_SRAD_RAMP_ADDSTEP         (Q32I_)(Q14I_SRAD_MOTOR_TO_PU(0.00001f * MOTOR_MAX_SRAD))    //s^-1,电机LOOP2增速步长
        
#define LOOP1_SWITCH_SRAD               (Q32I_)(Q14I_SRAD_MOTOR_TO_PU(0.15000f * MOTOR_MAX_SRAD))    //s^-1,电机LOOP1切换LOOP2的转速
#define LOOP1_SWITCH_TIME               (200U)                              //ms,电机LOOP1切换LOOP2的时间

//电机LOOP2，闭环运行              
#define LOOP2_SRAD_RAMP_ADDSTEP         (Q32I_)(Q14I_SRAD_MOTOR_TO_PU(0.00001f * MOTOR_MAX_SRAD))    //s^-1,电机LOOP2增速步长
       
//电机LOOP3  
#define LOOP3_SRAD_RAMP_ADDSTEP         (Q32I_)(Q14I_SRAD_MOTOR_TO_PU(0.00001f * MOTOR_MAX_SRAD))    //s^-1,电机LOOP3增速步长
        
#define LOOP3_SRAD_TARGET               (Q32I_)(Q14I_SRAD_MOTOR_TO_PU(0.10000f * MOTOR_MAX_SRAD))    //s^-1,电机LOOP3转速
#define LOOP3_SWITCH_SRAD               (Q32I_)(Q14I_SRAD_MOTOR_TO_PU(0.20000f * MOTOR_MAX_SRAD))    //s^-1,电机LOOP3关闭的转速
#define LOOP3_SWITCH_TIME               (20U)                              //ms,电机LOOP3关闭的时间

        
//转速环PID        
#define SPD_PID_Coeff                   (0.10f)                              //转速环PID增益系数
        
#define SPD_KP_GAIN                     (Q32I_)(MATH_PID_MAX * SPD_PID_Coeff * MOTOR_CURRENT_PHASE_A / MOTOR_MAX_SRAD * (W_BASE / I_BASE))
#define SPD_KI_GAIN                     (Q32I_)(MATH_PID_MAX * SPD_PID_Coeff * MOTOR_CURRENT_PHASE_A * MOTOR_LTs * (W_BASE / I_BASE))
#define SPD_KD_GAIN                     (Q32I_)(0.0f)
#define SPD_PID_MAX                     (Q32I_)( Q14I_CURRENT_MOTOR_TO_PU(0.25f * MOTOR_CURRENT_PHASE_A))
#define SPD_PID_MIN                     (Q32I_)(-Q14I_CURRENT_MOTOR_TO_PU(0.25f * MOTOR_CURRENT_PHASE_A))
        
        
//电流PID     
#define CURRENT_PID_Coeff               (0.001f)                             //电流环P增益系数
        
#define CURRENT_KP_GAIN                 (Q32I_)(MATH_PID_MAX * CURRENT_PID_Coeff * MATH_2PI_F * MOTOR_Ls / MOTOR_HTs * (I_BASE / V_BASE))//2pi*F*L/20
#define CURRENT_KI_GAIN                 (Q32I_)(MATH_PID_MAX * CURRENT_PID_Coeff * MATH_2PI_F * MOTOR_Rs * (I_BASE / V_BASE))//R/L/F
#define CURRENT_KD_GAIN                 (Q32I_)(0.0f)
            
        
//弱磁控制PID       
#define WEAK_KP_GAIN                    (Q32I_)(MATH_PID_MAX * 0.0f)
#define WEAK_KI_GAIN                    (Q32I_)(MATH_PID_MAX * 0.0f)
#define WEAK_KD_GAIN                    (Q32I_)(0.0f)
        
        
//非线性磁链观测器      
#define EST_FLUX_GAMMA                  (Q32I_)(2.0f * MOTOR_Q14_PU * ((float)Q14I_FLUX_PU / MOTOR_Q14_PU) * ((float)Q14I_FLUX_PU / MOTOR_Q14_PU) * ((float)Q14I_FLUX_PU / (float)Q14I_VOLTAGE_PU))      //增益系数
#define EST_FLUX_R_Coeff                (Q32I_)(0.5f * MOTOR_Q14_PU)             //电阻系数
                
#define EST_FLUX_PLL_KP                 (Q32I_)(0.01f * MATH_PID_MAX * MOTOR_MAX_SRAD * MOTOR_MAX_SRAD / (float)Q14I_FLUX_PU)   //锁相环比例系数
#define EST_FLUX_PLL_KI                 (Q32I_)(0.1f * MATH_PID_MAX * MOTOR_MAX_SRAD / (float)Q14I_FLUX_PU)     //锁相环积分系数
#define EST_FLUX_PLL_KD                 (Q32I_)(0.0f)                        //锁相环微分系数
#define EST_FLUX_PLL_MAX                (Q32I_)(1.2f * (float)Q14I_MAX_SRAD_PU)     //锁相环最大输出
#define EST_FLUX_PLL_MIN                (Q32I_)(-1.2f * (float)Q14I_MAX_SRAD_PU)    //锁相环最小输出


//SMO观测器                
#define EST_SMO_K1                      (Q32I_)(2.00f * MOTOR_Q14_PU * (float)Q14I_CURRENT_PHASE_A_PU / (float)Q14I_VOLTAGE_PU)    //增益系数1
#define EST_SMO_K2                      (Q32I_)(0.01f * MOTOR_Q14_PU * (float)Q14I_CURRENT_PHASE_A_PU / (float)Q14I_VOLTAGE_PU)    //增益系数2
                
#define EST_SMO_PLL_KP                  (Q32I_)(0.01f * MATH_PID_MAX * MOTOR_MAX_SRAD * MOTOR_MAX_SRAD / (float)Q14I_VOLTAGE_PU) //锁相环比例系数
#define EST_SMO_PLL_KI                  (Q32I_)(0.1f * MATH_PID_MAX * MOTOR_MAX_SRAD / (float)Q14I_VOLTAGE_PU)   //锁相环积分系数
#define EST_SMO_PLL_KD                  (Q32I_)(0.0f)                        //锁相环微分系数
#define EST_SMO_PLL_MAX                 (Q32I_)(1.2f * (float)Q14I_MAX_SRAD_PU)     //锁相环最大输出
#define EST_SMO_PLL_MIN                 (Q32I_)(-1.2f * (float)Q14I_MAX_SRAD_PU)    //锁相环最小输出


//母线电流PID
#define IBUS_PID_KP                     (Q32I_)(0.001f * MATH_PID_MAX)
#define IBUS_PID_KI                     (Q32I_)(0.010f * MATH_PID_MAX)
#define IBUS_PID_KD                     (Q32I_)(0.000f * MATH_PID_MAX)
#define IBUS_PID_STEPMAX                (Q32I_)( 0.010f * HAL_PWM_DUTY_MAX)
#define IBUS_PID_STEPMIN                (Q32I_)(-0.010f * HAL_PWM_DUTY_MAX)
#define IBUS_PID_OUTMAX                 (Q32I_)(1.000f * HAL_PWM_DUTY_MAX)
#define IBUS_PID_OUTMIN                 (Q32I_)(0.050f * HAL_PWM_DUTY_MAX)


typedef enum{
    MOTOR_STATE_INIT,
    MOTOR_STATE_IDLE,
    MOTOR_STATE_MOS,
    MOTOR_STATE_BOOT,
    MOTOR_STATE_POSITION,
    MOTOR_STATE_RUN,
    MOTOR_STATE_BRAKE,
}EM_MOTOR_STATE_FLOW;

typedef enum
{
    ADC_FIRST_READ,
    ADC_SECND_READ,
    ADC_THIRD_READ,
    PWM_DUTY_DNDATE,
    PWM_DUTY_UPDATE,
}EM_ADC_PWM_FLOW;

typedef enum
{
    OPENLOOP,
    CLOSELOOP_INIT,
    CLOSELOOP_RUN,
    CLOSELOOP_END,
}EM_MOTOR_SPEED_MODE;

typedef union{
    ALL all;
    struct{
        BIT                motor_run_flag              :1;//电机运行标志位
        BIT                pwm_output_flag             :1;//PWM脉冲输出标志位
        BIT                para_init_flag              :1;//参数初始化标志位
    }bit;
}UN_MOTOR_STATE_FLAG;

typedef union{
    ALL all;
    struct{
        BIT                 current_offset           :1;//偏置故障
        BIT                 current_short            :1;//短路故障
        BIT                 mos_fault                :1;//mos故障（单个上电周期内，发生三次短路保护，锁死故障状态）
        BIT                 motor_stall              :1;//电机堵转故障
    }bit;
}UN_MOTOR_ERROR_FLAG;

typedef struct{
    EM_MOTOR_STATE_FLOW         Motor_Flow;
    UN_MOTOR_STATE_FLAG         Motor_State_Flag;
    UN_MOTOR_ERROR_FLAG         Motor_Error_Flag;
    EM_ADC_PWM_FLOW             ADC_Read_Flow;
    EM_MOTOR_SPEED_MODE         Motor_Speed_Mode;
    
    ST_COMMON_CONTROL           Common_Ctrl;
    
    ST_PMSM_PARAMETER           PMSM_Para;
    ST_FOC_PARAMETER            FOC_Para;
    
    ST_SRAD_CONTROL             SRAD_Ctrl;
    ST_CURRENT_CONTROL          Current_Ctrl;
    
    ST_WEAK_CONTROL             WEAK_Ctrl;
    
    ST_IF_CONTROL               IF_Ctrl;
    ST_FLUX_CONTROL             FLUX_Ctrl;
    ST_SMO_CONTROL              SMO_Ctrl;
    
    uint32_t                    flow_cnt;
}ST_MOTOR_TASK;

extern ST_MOTOR_TASK  Motor;

#endif /* MotorPara_H */
