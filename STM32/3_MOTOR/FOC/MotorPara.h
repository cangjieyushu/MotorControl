/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef MotorPara_H
#define MotorPara_H

#include <stdint.h>
#include "Math.h"
#include "MotorTask.h"
#include "User_Pmsm.h"
#include "MotorHal_cfg.h"

//电机closeloop1相关参数      
#define USER_M1_CURRENTRAMP_INIT                        (1.0f)                          //A,电机closeloop1电流初始值
#define USER_M1_CURRENTRAMP_TARGET                      (USER_MOTOR1_MAX_CURRENT)       //A,电机closeloop1电流目标值
#define USER_M1_CURRENTRAMP_STEP                        (0.0005f)                       //A,电机closeloop1电流增加步长
#define USER_M1_CLOSELOOP1_SPEED                        (35.0f)                         //Hz,电机closeloop1切换closeloop2的转速
#define USER_M1_CLOSELOOP1_SWITCH_TIME                  (200U)                          //ms,电机closeloop1切换closeloop2的时间
        
//电机closeloop3相关参数      
#define USER_M1_CLOSELOOP3_SPEED                        (USER_MOTOR1_MAX_SPEED)         //ms,电机closeloop3目标转速
#define USER_M1_SPDRAMP_STEP                            (0.05f)                         //Hz,电机closeloop3增速步长

//刹车相关参数
#define USER_M1_BRAKE_MAX_TIME                          (1000U)                         //ms,最长刹车时间
#define USER_M1_BRAKE_CURRENT_TL                        (0.5f)                          //A,退出刹车电流
#define USER_M1_BRAKE_CURRENT_FILTER                    (200U)                          //ms,退出刹车，电流滤波时间

//转速环PID
#define USER_M1_SPD_PID_Coeff                           (1.0f)                          //转速环PID增益系数
     
#define USER_M1_SPD_KP_GAIN                             (USER_M1_SPD_PID_Coeff * USER_MOTOR1_MAX_CURRENT / (USER_MOTOR1_MAX_SPEED * MATH_2PI))
#define USER_M1_SPD_KI_GAIN                             (USER_M1_SPD_PID_Coeff * USER_M1_SPD_KP_GAIN * USER_M1_SPDRAMP_STEP)
#define USER_M1_SPD_KD_GAIN                             (0.0f)
#define USER_M1_SPD_PID_MAX                             (USER_MOTOR1_MAX_CURRENT)       //A,转速环输出q轴电流限幅
#define USER_M1_SPD_PID_MIN                             (-USER_MOTOR1_MAX_CURRENT)      //A,转速环输出q轴电流限幅

//电流PID
#define USER_M1_FOC_P_Coeff                             (0.02f)                         //电流环P增益系数
#define USER_M1_FOC_I_Coeff                             (0.0008f)                       //电流环I增益系数
                   
#define USER_M1_FOC_KP_GAIN                             (USER_M1_FOC_P_Coeff * USER_MOTOR1_Ls * MATH_2PI / HAL_CURRENT_LOOP_TIME)
#define USER_M1_FOC_KI_GAIN                             (USER_M1_FOC_I_Coeff * HAL_CURRENT_LOOP_TIME * USER_MOTOR1_Rs / USER_MOTOR1_Ls)
#define USER_M1_FOC_KD_GAIN                             (0.0f)
     
//电机IF相关参数
#define USER_M1_ANGLERADRAMP_INIT                       (0.0f)                          //rad,电机IF角度自增初始值
#define USER_M1_ANGLERADRAMP_TARGET                     (0.0005f)                       //rad,电机IF角度自增目标值
#define USER_M1_ANGLERADRAMP_STEP                       (0.0000001f)                     //rad,电机IF角度自增增加步长
#define USER_M1_ANGLERAD_ERROR                          (0.2f)                          //rad,电机IF角度与观测器偏差允许切换值
#define USER_M1_ANGLERAD_TIME                           (10U)                            //次（Ts）,电机IF角度与观测器偏差允许切换滤波次数

//非线性磁链观测器
#define USER_M1_FLUX_KT                                 (250000.0f)                                     //增益系数
#define USER_M1_FLUX_R_Coeff                            (0.1f)                                          //电阻系数
     
#define USER_M1_FLUX_PLL_KP                             (8000.0f)                                       //锁相环比例系数
#define USER_M1_FLUX_PLL_KI                             (400.0f)                                        //锁相环积分系数
#define USER_M1_FLUX_PLL_KD                             (0.0f)                                          //锁相环微分系数
#define USER_M1_FLUX_PLL_MAX                            (1.1f * USER_MOTOR1_MAX_SPEED * MATH_2PI)     //锁相环最大输出
#define USER_M1_FLUX_PLL_MIN                            (-1.1f * USER_MOTOR1_MAX_SPEED * MATH_2PI)    //锁相环最小输出
    
//SMO观测器        
#define USER_M1_SMO_K1                                  (100.0f)                                        //增益系数
#define USER_M1_SMO_K2                                  (0.5f)                                          //增益系数
    
#define USER_M1_SMO_PLL_KP                              (100.0f)                                        //锁相环比例系数
#define USER_M1_SMO_PLL_KI                              (0.25f)                                         //锁相环积分系数
#define USER_M1_SMO_PLL_KD                              (0.0f)                                          //锁相环微分系数
#define USER_M1_SMO_PLL_MAX                             (1.1f * USER_MOTOR1_MAX_SPEED * MATH_2PI)     //锁相环最大输出
#define USER_M1_SMO_PLL_MIN                             (-1.1f * USER_MOTOR1_MAX_SPEED * MATH_2PI)    //锁相环最小输出
     
//霍尔传感器
#define USER_DIR_FORWARD                                (1)
#define USER_DIR_BACKWARD                               (-1)

extern ST_MOTOR_TASK  Motor;

#endif /* MotorPara_H */
