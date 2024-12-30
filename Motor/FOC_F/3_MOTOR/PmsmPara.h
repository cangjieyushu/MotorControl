/**************************************************************************************************
*     File Name :                        PmsmPara.h
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机参数头文件
**************************************************************************************************/
#ifndef PmsmPara_H
#define PmsmPara_H

#include "Math.h"
#include "MotorHal_cfg.h"   

//电机额定参数，正点原子
//#define MOTOR_VOLTAGE_V                     (24.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (12.0f)             //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (8.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流
//
//#define MOTOR_HTs                           (1.0f/1000.0f/HAL_PWM_SET_FREQ)
//#define MOTOR_LTs                           (HAL_SLOW_TIMER_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (2.0f)                          //转子极对数
//#define MOTOR_Rs                            (0.31f)                         //Ω，相电阻
//#define MOTOR_Ld                            (0.37f*0.001f)                  //H，d轴电感
//#define MOTOR_Lq                            (0.44f*0.001f)                  //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.017f)                        //Wb
//
//#define MOTOR_MAX_SPEED                     (3300.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (100.0f)              //rpm，最低转速
//
//#define MOTOR_MAX_SRAD                      (MATH_2PI_F*MOTOR_POLE_PAIR*MOTOR_MAX_SPEED/60.0f)        //Hz，最高角频率
//#define MOTOR_MIN_SRAD                      (MATH_2PI_F*MOTOR_POLE_PAIR*MOTOR_MIN_SPEED/60.0f)        //Hz，最低角频率

//电机额定参数，灰色电机
#define MOTOR_VOLTAGE_V                     (12.0f)             //V，母线电压
#define MOTOR_CURRENT_PHASE_A               (10.0f)             //A，相电流幅值
#define MOTOR_CURRENT_BUS_A                 (6.0f)              //A，母线电流
#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流

#define MOTOR_HTs                           (1.0f/1000.0f/HAL_PWM_SET_FREQ)
#define MOTOR_LTs                           (HAL_SLOW_TIMER_FREQ/1000.0f)
#define MOTOR_POLE_PAIR                     (4.0f)                          //转子极对数
#define MOTOR_Rs                            (0.36f)                         //Ω，相电阻
#define MOTOR_Ld                            (0.225f*0.001f)                 //H，d轴电感
#define MOTOR_Lq                            (0.245f*0.001f)                 //H，q轴电感，q轴电感至少需要比d轴电感大10uH
#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
#define MOTOR_FLUX                          (0.00577f)                      //Wb

#define MOTOR_MAX_SPEED                     (3500.0f)             //rpm，最高转速
#define MOTOR_MIN_SPEED                     (100.0f)              //rpm，最低转速

#define MOTOR_MAX_SRAD                      (MATH_2PI_F*MOTOR_POLE_PAIR*MOTOR_MAX_SPEED/60.0f)        //Hz，最高角频率
#define MOTOR_MIN_SRAD                      (MATH_2PI_F*MOTOR_POLE_PAIR*MOTOR_MIN_SPEED/60.0f)        //Hz，最低角频率

////电机额定参数，白色大电机
//#define MOTOR_VOLTAGE_V                     (12.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (12.0f)             //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (8.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流
//
//#define MOTOR_HTs                           (1.0f/1000.0f/HAL_PWM_SET_FREQ)
//#define MOTOR_LTs                           (HAL_SLOW_TIMER_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (5.0f)                          //转子极对数
//#define MOTOR_Rs                            (0.175f)                         //Ω，相电阻
//#define MOTOR_Ld                            (0.31f*0.001f)                  //H，d轴电感
//#define MOTOR_Lq                            (0.43f*0.001f)                  //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.00975f)                        //Wb
//
//#define MOTOR_MAX_SPEED                     (3300.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (100.0f)              //rpm，最低转速
//
//#define MOTOR_MAX_SRAD                      (MATH_2PI_F*MOTOR_POLE_PAIR*MOTOR_MAX_SPEED/60.0f)        //Hz，最高角频率
//#define MOTOR_MIN_SRAD                      (MATH_2PI_F*MOTOR_POLE_PAIR*MOTOR_MIN_SPEED/60.0f)        //Hz，最低角频率

#endif /* PmsmPara_H */
