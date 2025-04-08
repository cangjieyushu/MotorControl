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

////电机额定参数，正点原子
//#define MOTOR_VOLTAGE_V                     (36.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (12.0f)             //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (8.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流
//
//#define MOTOR_HTs                           (1.0f/1000.0f/HAL_PWM_SET_FREQ)
//#define MOTOR_LTs                           (HAL_SLOW_TIMER_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (2.0f)                          //转子极对数
//#define MOTOR_Rs                            (0.233f)                        //Ω，相电阻
//#define MOTOR_Ld                            (0.402f*0.001f)                 //H，d轴电感
//#define MOTOR_Lq                            (0.513f*0.001f)                 //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.0165f)                       //Wb
//
//#define MOTOR_MAX_SPEED                     (4000.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (1000.0f)             //rpm，最低转速

//电机额定参数，灰色电机
#define MOTOR_VOLTAGE_V                     (12.0f)             //V，母线电压
#define MOTOR_CURRENT_PHASE_A               (8.0f)              //A，相电流幅值
#define MOTOR_CURRENT_BUS_A                 (6.0f)              //A，母线电流
#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流

#define MOTOR_HTs                           (1.0f/1000.0f/HAL_PWM_SET_FREQ)
#define MOTOR_LTs                           (HAL_SLOW_TIMER_FREQ/1000.0f)
#define MOTOR_POLE_PAIR                     (4.0f)                          //转子极对数
#define MOTOR_Rs                            (0.365f)                        //Ω，相电阻
#define MOTOR_Ld                            (0.251f*0.001f)                 //H，d轴电感
#define MOTOR_Lq                            (0.271f*0.001f)                 //H，q轴电感，q轴电感至少需要比d轴电感大10uH
#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
#define MOTOR_FLUX                          (0.00504f)                      //Wb

#define MOTOR_MAX_SPEED                     (3600.0f)             //rpm，最高转速
#define MOTOR_MIN_SPEED                     (100.0f)              //rpm，最低转速

////电机额定参数，手枪钻
//#define MOTOR_VOLTAGE_V                     (12.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (12.0f)             //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (8.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HAL_PWM_SET_FREQ)
//#define MOTOR_LTs                           (HAL_SLOW_TIMER_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (2.0f)                          //转子极对数
//#define MOTOR_Rs                            (0.0756f)                       //Ω，相电阻
//#define MOTOR_Ld                            (0.0188f*0.001f)                //H，d轴电感
//#define MOTOR_Lq                            (0.0197f*0.001f)                //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.00975f)                      //Wb
//#define MOTOR_MAX_SPEED                     (24000.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (100.0f)              //rpm，最低转速

////电机额定参数，小电机
//#define MOTOR_VOLTAGE_V                     (24.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (3.0f)              //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (2.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HAL_PWM_SET_FREQ)
//#define MOTOR_LTs                           (HAL_SLOW_TIMER_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (2.0f)                          //转子极对数
//#define MOTOR_Rs                            (8.39f)                         //Ω，相电阻
//#define MOTOR_Ld                            (2.38f*0.001f)                  //H，d轴电感
//#define MOTOR_Lq                            (2.45f*0.001f)                  //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.0341f)                       //Wb
//#define MOTOR_MAX_SPEED                     (4000.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (1000.0f)             //rpm，最低转速

/**********************************************************************************/

#define MOTOR_SPEED_TO_FREQ(A)              (MOTOR_POLE_PAIR*(A)/60.0f)                 //转速rpm转频率
#define MOTOR_FREQ_TO_SPEED(A)              (60.0f*(A)/MOTOR_POLE_PAIR)                 //频率转转速rpm

#define MOTOR_MAX_FREQ                      (MOTOR_SPEED_TO_FREQ(MOTOR_MAX_SPEED))      //Hz，最高频率
#define MOTOR_MIN_FREQ                      (MOTOR_SPEED_TO_FREQ(MOTOR_MIN_SPEED)) 

#endif /* PmsmPara_H */
