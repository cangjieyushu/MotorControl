/*
*     File Name :                        mcfoc_para_t
*     Library/Module Name :              mcfoc_t
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制参数初始化
*/


#ifndef MCFOC_PARA_T_H
#define MCFOC_PARA_T_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "pmsm_para.h"
#include "mc_error.h"
#include "mcfoc_est_t.h"
#include "mcfoc_svpwm_t.h"
#include "mcfoc_pmsm_t.h"
#include "mcfoc_loop_t.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
//载频切换转速
#define MOTOR_PWM_FREQ_LOW                  ((Q32I_)(HAL_PWM_HIGH_FREQ*1000.0f))     //Hz，低载频
#define MOTOR_PWM_FREQ_HIGH                 ((Q32I_)(HAL_PWM_HIGH_FREQ*1000.0f))     //Hz，高载频
#define MOTOR_PWM_FREQ_TL                   (Q14I_FREQ_TO_PU(30.0f))                 //Hz，从高载频切换至低载频
#define MOTOR_PWM_FREQ_CLR                  (Q14I_FREQ_TO_PU(40.0f))                 //Hz，从低载频切换至高载频


//电流采样偏置检测
#define CURRENT_OFFSET_VOLTAGE_V            (HAL_ADC_CURRENT_OFFSET)                            //V，电流采样偏置电压
#define CURRENT_OFFSET_lsb                  (Q32U_)(CURRENT_OFFSET_VOLTAGE_V*HAL_ADC_SCALE_BIT/HAL_ADC_REF_VOLTAGE_V)    //lsb，电流采样偏置
#define CURRENT_OFFSET_TL_lsb               (200U)                                              //lsb，电流采样偏置偏差阈值
#define CURRENT_OFFSET_MAX_lsb              (CURRENT_OFFSET_lsb + CURRENT_OFFSET_TL_lsb)        //lsb，电流采样偏置上限
#define CURRENT_OFFSET_MIN_lsb              (CURRENT_OFFSET_lsb - CURRENT_OFFSET_TL_lsb)        //lsb，电流采样偏置下限
#define CURRENT_OFFSET_NUM                  (20U)                                               //电流采样偏置检测次数


//ALIGN
#define MOTOR_ALIGN_ID_TARGET               (Q14I_CURRENT_TO_PU(1.0f))                  //A，Id目标值
#define MOTOR_ALIGN_IDRAMP_ADDSTEP          (Q28I_CURRENT_TO_PU(5.0f * MOTOR_LTs))      //A/s，Id每秒增加步长
#define MOTOR_ALIGN_ANGLERAMP_ADDSTEP       (Q28I_ANGLE_TO_PU(1.0f * MOTOR_LTs))        //rad/s，角度每秒增加步长
#define MOTOR_ALIGN_COUNT                   (1000U)                                     //ms


//IF
#define MOTOR_IF_IQ_TARGET                  (Q14I_CURRENT_TO_PU(5.0f))                  //A，Iq目标值
#define MOTOR_IF_IS_MIN                     (Q14I_CURRENT_TO_PU(2.0f))                  //A，Is最小值
#define MOTOR_IF_IQ_MIN                     (Q14I_CURRENT_TO_PU(0.5f))                  //A，Iq最小值，切闭环
#define MOTOR_IF_IQRAMP_ADDSTEP             ( Q28I_CURRENT_TO_PU(10.0f * MOTOR_LTs))    //A/s，Iq每秒增加步长
#define MOTOR_IF_IQRAMP_SUBSTEP             (-Q28I_CURRENT_TO_PU(0.5f * MOTOR_LTs))     //A/s，Iq每秒减小步长

#define MOTOR_IF_FREQRAMP_TARGET            (Q14I_FREQ_TO_PU(20.0f))                    //Hz，IF速度目标值
#define MOTOR_IF_FREQRAMP_ADDSTEP           (Q28I_FREQ_TO_PU(5.0f * MOTOR_LTs))         //Hz/s，IF速度每秒增加步长

#define MOTOR_IF_ANGLE_ERROR                (Q14I_ANGLE_TO_PU(0.35f))                   //rad，IF与观测器角度偏差允许切换值
#define MOTOR_IF_SWITCH_COUNT               (20U)                                       //次，电机OpenLoop切换CloseLoop转速检测


//转速环PID
#define MOTOR_FREQ_RAMP_ADDSTEP             (Q28I_FREQ_TO_PU( 20.0f * MOTOR_LTs))       //Hz/s，电机closeloop每秒增速步长
#define MOTOR_FREQ_RAMP_SUBSTEP             (Q28I_FREQ_TO_PU(-20.0f * MOTOR_LTs))       //Hz/s，电机closeloop每秒增速步长

#define MOTOR_FREQ_PID_Coeff                (1.00f)                             //转速环PID增益系数
#define MOTOR_FREQ_KP_GAIN                  ((Q32I_)(MOTOR_FREQ_PID_Coeff * MOTOR_CURRENT_PHASE_A / MOTOR_MAX_FREQ * F_BASE / I_BASE * 16384.0f))
#define MOTOR_FREQ_KI_GAIN                  ((Q32I_)(0.05f * MOTOR_CURRENT_PHASE_A * MOTOR_LTs * F_BASE / I_BASE * 16384.0f))
#define MOTOR_FREQ_KD_GAIN                  ((Q32I_)(0.0f))

#define MOTOR_FREQ_PID_MAX                  (Q14I_CURRENT_TO_PU( 1.0f * MOTOR_CURRENT_PHASE_A))             //A，转速环输出q轴电流限幅
#define MOTOR_FREQ_PID_MIN                  (Q14I_CURRENT_TO_PU(-1.0f * MOTOR_CURRENT_PHASE_A))             //A，转速环输出q轴电流限幅

//电流PID
#define MOTOR_CURRENT_PID_Coeff             (0.05f)                             //电流环P增益系数
#define MOTOR_CURRENT_KP_GAIN               ((Q32I_)(MOTOR_CURRENT_PID_Coeff * MOTOR_Ls * MATH_2PI_F / MOTOR_HTs * I_BASE / V_BASE * 16384.0f))
#define MOTOR_CURRENT_KI_GAIN               ((Q32I_)(MOTOR_CURRENT_PID_Coeff * MOTOR_Rs * I_BASE / V_BASE * 16384.0f))
#define MOTOR_CURRENT_KD_GAIN               ((Q32I_)(0.0f))


//观测器PLL系数
#define MOTOR_PLL_Coeff                     (0.20f)
#define MOTOR_PLL_SPEED_LPF_COEFF           ((Q32I_)(0.05f * 16384.0f))                           	//0~1，越小滤波越深
#define MOTOR_MAX_SRAD                      (MOTOR_MAX_FREQ * MATH_2PI_F)


//SMO观测器
#define MOTOR_SMO_H1                        ((Q32I_)(VOLTAGE_PU / CURRENT_PHASE_PU * 16384.0f))     //增益系数

#define MOTOR_SMO_PLL_KP                    ((Q32I_)(2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_SRAD * 2.0f / VOLTAGE_PU / F_BASE / MATH_2PI_F * 16384.0f))                          //锁相环比例系数
#define MOTOR_SMO_PLL_KI                    ((Q32I_)((MOTOR_PLL_Coeff*MOTOR_MAX_SRAD * MOTOR_PLL_Coeff*MOTOR_MAX_SRAD) * MOTOR_HTs * 2.0f / VOLTAGE_PU / F_BASE / MATH_2PI_F * 16384.0f))      //锁相环积分系数
#define MOTOR_SMO_PLL_KD                    ((Q32I_)(0.0f))                    	                    //锁相环微分系数
#define MOTOR_SMO_PLL_MAX                   (Q14I_FREQ_TO_PU( 2.0f * MOTOR_MAX_FREQ))               //锁相环最大输出
#define MOTOR_SMO_PLL_MIN                   (Q14I_FREQ_TO_PU(-2.0f * MOTOR_MAX_FREQ))  	            //锁相环最小输出


//磁链观测器  
#define MOTOR_FLUX_GAMMA                    ((Q32I_)(0.02f * VOLTAGE_PU / FLUX_PU * 16384.0f))      //增益系数

#define MOTOR_FLUX_PLL_KP                   ((Q32I_)(2.0f * MOTOR_PLL_Coeff * MOTOR_MAX_FREQ / FLUX_PU / F_BASE / MATH_2PI_F * 16384.0f))                                    //锁相环比例系数
#define MOTOR_FLUX_PLL_KI                   ((Q32I_)((MOTOR_PLL_Coeff*MOTOR_MAX_SRAD * MOTOR_PLL_Coeff*MOTOR_MAX_SRAD) * MOTOR_HTs / FLUX_PU / F_BASE / MATH_2PI_F * 16384.0f))                //锁相环积分系数
#define MOTOR_FLUX_PLL_KD                   ((Q32I_)(0.0f))                    	                    //锁相环微分系数
#define MOTOR_FLUX_PLL_MAX                  (Q14I_FREQ_TO_PU( 2.0f * MOTOR_MAX_FREQ))               //锁相环最大输出
#define MOTOR_FLUX_PLL_MIN                  (Q14I_FREQ_TO_PU(-2.0f * MOTOR_MAX_FREQ))  	            //锁相环最小输出


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef struct{
    EM_MOTOR_STATE              Motor_Flow;
    UN_MOTOR_FLAG               Motor_Flag;
    ST_MOTOR_API                Motor_API;

    ST_MOTOR_ERROR              Motor_Error;

    EM_MOTOR_LOOP_MODE          Motor_Loop_Mode;
    
    ST_PMSM_FILTER_T            PMSM_Filter;
    ST_PMSM_ELEC_T              PMSM_Elec;
    ST_PMSM_PARA_T              PMSM_Para;
    
    ST_MCFOC_OFFSET_T           MCFOC_Offset;
    ST_ALIGN_CONTROL_T          Align_Ctrl;
    ST_IF_CONTROL_T             IF_Ctrl;
    ST_FREQ_CONTROL_T           Freq_Ctrl;
    ST_CURRENT_CONTROL_T        Current_Ctrl;
    ST_SVPWM_CONTROL_T          SVPWM_Ctrl;
    
    ST_EMF_CONTROL_T            EMF_Ctrl;
    ST_SMO_CONTROL_T            SMO_Ctrl;
    ST_FLUX_CONTROL_T           FLUX_Ctrl;

}ST_MCFOC_TASK_T;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/
extern ST_MCFOC_TASK_T MCFOC_Task_T;


/*-------------------------- 5. 接口函数声明 ------------------------------*/
void Motor_Parameter_API_T(ST_MCFOC_TASK_T* pMotor);


#endif /* MCFOC_PARA_T_H */
