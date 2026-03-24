/**************************************************************************************************
*     File Name :                        PMSM_PARA.h
*     Library/Module Name :              MC
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机参数头文件
**************************************************************************************************/

#ifndef PMSM_PARA_H
#define PMSM_PARA_H


#include "MATH.h"
#include "HAL_CFG.h"


//启动算法选择
#define MOTOR_OPENLOOP_IF           (00U)
#define MOTOR_OPENLOOP_FLUX         (01U)
#define MOTOR_OPENLOOP_MODE         MOTOR_OPENLOOP_FLUX

//观测器选择
#define MOTOR_EST_SMO               (10U)
#define MOTOR_EST_FLUX              (11U)
#define MOTOR_EST_MODE              MOTOR_EST_FLUX


//电机正反转宏定义
#define MOTOR_DIR_CW                        ( 1)
#define MOTOR_DIR_CCW                       (-1)


//电机额定参数，测功机
#define MOTOR_VOLTAGE_V                     (24.0f)             //V，母线电压
#define MOTOR_CURRENT_PHASE_A               (8.0f)              //A，相电流幅值
#define MOTOR_CURRENT_BUS_A                 (3.0f)              //A，母线电流
#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流
#define MOTOR_HTs                           (1.0f/1000.0f/HAL_PWM_HIGH_FREQ*((float)HAL_CURRENT_LOOP_FREQ_PRESCALER))
#define MOTOR_LTs                           (HAL_SLOW_TIMER_FREQ/1000.0f)
#define MOTOR_POLE_PAIR                     (4.0f)                          //转子极对数
#define MOTOR_Rs                            (0.562f)                        //Ω，相电阻
#define MOTOR_Ld                            (0.365f*0.001f)                 //H，d轴电感
#define MOTOR_Lq                            (0.405f*0.001f)                 //H，q轴电感，q轴电感至少需要比d轴电感大10uH
#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
#define MOTOR_FLUX                          (0.00875f)                      //Wb
#define MOTOR_MAX_SPEED                     (4000.0f)             //rpm，最高转速
#define MOTOR_MIN_SPEED                     (100.0f)              //rpm，最低转速

////电机额定参数，正点原子
//#define MOTOR_VOLTAGE_V                     (24.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (6.0f)              //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (6.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HAL_PWM_HIGH_FREQ*((float)HAL_CURRENT_LOOP_FREQ_PRESCALER))
//#define MOTOR_LTs                           (HAL_SLOW_TIMER_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (2.0f)                          //转子极对数
//#define MOTOR_Rs                            (0.233f)                        //Ω，相电阻
//#define MOTOR_Ld                            (0.381f*0.001f)                 //H，d轴电感
//#define MOTOR_Lq                            (0.468f*0.001f)                 //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.0165f)                       //Wb
//#define MOTOR_MAX_SPEED                     (4000.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (100.0f)              //rpm，最低转速

////电机额定参数，风机
//#define MOTOR_VOLTAGE_V                     (12.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (8.0f)              //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (8.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HAL_PWM_HIGH_FREQ*((float)HAL_CURRENT_LOOP_FREQ_PRESCALER))
//#define MOTOR_LTs                           (HAL_SLOW_TIMER_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (2.0f)                          //转子极对数
//#define MOTOR_Rs                            (0.175f)                        //Ω，相电阻
//#define MOTOR_Ld                            (0.0379f*0.001f)                //H，d轴电感
//#define MOTOR_Lq                            (0.0487f*0.001f)                //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.00069f)                      //Wb
//#define MOTOR_MAX_SPEED                     (48000.0f)            //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (100.0f)              //rpm，最低转速

////电机额定参数，灰色电机
//#define MOTOR_VOLTAGE_V                     (12.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (8.0f)              //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (6.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HAL_PWM_HIGH_FREQ)
//#define MOTOR_LTs                           (HAL_SLOW_TIMER_FREQ/1000.0f*((float)HAL_CURRENT_LOOP_FREQ_PRESCALER))
//#define MOTOR_POLE_PAIR                     (4.0f)                          //转子极对数
//#define MOTOR_Rs                            (0.365f)                        //Ω，相电阻
//#define MOTOR_Ld                            (0.251f*0.001f)                 //H，d轴电感
//#define MOTOR_Lq                            (0.271f*0.001f)                 //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.00504f)                      //Wb
//#define MOTOR_MAX_SPEED                     (3600.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (100.0f)              //rpm，最低转速

////电机额定参数，手枪钻
//#define MOTOR_VOLTAGE_V                     (12.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (12.0f)             //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (5.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (1.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HAL_PWM_HIGH_FREQ*((float)HAL_CURRENT_LOOP_FREQ_PRESCALER))
//#define MOTOR_LTs                           (HAL_SLOW_TIMER_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (2.0f)                          //转子极对数
//#define MOTOR_Rs                            (0.0756f)                       //Ω，相电阻
//#define MOTOR_Ld                            (0.0188f*0.001f)                //H，d轴电感
//#define MOTOR_Lq                            (0.0197f*0.001f)                //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.00975f)                      //Wb
//#define MOTOR_MAX_SPEED                     (24000.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (100.0f)               //rpm，最低转速

////电机额定参数，小电机
//#define MOTOR_VOLTAGE_V                     (24.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (3.0f)              //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (2.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HAL_PWM_HIGH_FREQ*((float)HAL_CURRENT_LOOP_FREQ_PRESCALER))
//#define MOTOR_LTs                           (HAL_SLOW_TIMER_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (2.0f)                          //转子极对数
//#define MOTOR_Rs                            (8.39f)                         //Ω，相电阻
//#define MOTOR_Ld                            (2.38f*0.001f)                  //H，d轴电感
//#define MOTOR_Lq                            (2.45f*0.001f)                  //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.0341f)                       //Wb
//#define MOTOR_MAX_SPEED                     (3000.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (100.0f)              //rpm，最低转速


/**********************************************************************************/


#define MOTOR_SPEED_TO_FREQ(A)              (MOTOR_POLE_PAIR*(A)/60.0f)                 //转速rpm转频率
#define MOTOR_FREQ_TO_SPEED(A)              (60.0f*(A)/MOTOR_POLE_PAIR)                 //频率转转速rpm

#define MOTOR_MAX_FREQ                      (MOTOR_SPEED_TO_FREQ(MOTOR_MAX_SPEED))      //Hz，最高频率
#define MOTOR_MIN_FREQ                      (MOTOR_SPEED_TO_FREQ(MOTOR_MIN_SPEED))      //Hz，最低频率


//标幺化
#define V_BASE                              (HAL_ADC_VOLTAGE_MAX)               //V，电压
#define I_BASE                              (HAL_ADC_CURRENT_MAX)               //A，电流
#define F_BASE                              (MOTOR_MAX_FREQ)                    //Hz，频率
#define R_BASE                              (V_BASE/I_BASE)                     //Ω，电阻
#define L_BASE                              (V_BASE/F_BASE/I_BASE)              //H，电感
#define P_BASE                              (V_BASE/F_BASE)                     //wb，磁链
#define T_BASE                              (1.0f/F_BASE)     		            //s,时间

#define MOTOR_Q14_PU                        (Q14U_MAX)      //16384
#define MOTOR_Q28_PU                        (Q28U_MAX)      //268435456


/************************************定点标幺************************************/
#define Q14I_HTs_PU                         ((Q32I_)(MOTOR_Q14_PU*MOTOR_HTs/T_BASE))
#define Q14I_LTs_PU                         ((Q32I_)(MOTOR_Q14_PU*MOTOR_LTs/T_BASE))
#define Q14I_Rs_PU                          ((Q32I_)(MOTOR_Q14_PU*MOTOR_Rs/R_BASE))
#define Q14I_Ld_PU                          ((Q32I_)(MOTOR_Q14_PU*MOTOR_Ld/L_BASE))
#define Q14I_Lq_PU                          ((Q32I_)(MOTOR_Q14_PU*MOTOR_Lq/L_BASE))
#define Q14I_Ls_PU                          ((Q32I_)(MOTOR_Q14_PU*MOTOR_Ls/L_BASE))
#define Q14I_FLUX_PU                        ((Q32I_)(MOTOR_Q14_PU*MOTOR_FLUX/P_BASE))

#define Q14I_VOLTAGE_TO_PU(A)               ((Q32I_)(MOTOR_Q14_PU*(A)/V_BASE))              //电压标幺转换
#define Q14I_CURRENT_TO_PU(A)               ((Q32I_)(MOTOR_Q14_PU*(A)/I_BASE))              //电流标幺转换
#define Q14I_FREQ_TO_PU(A)                  ((Q32I_)(MOTOR_Q14_PU*(A)/F_BASE))              //频率标幺转换
#define Q14I_ANGLE_TO_PU(A)                 ((Q32I_)(MOTOR_Q14_PU*(A)/MATH_2PI_F))          //角度标幺转换
#define Q14I_DUTY_TO_PU(A)                  ((Q32I_)(MOTOR_Q14_PU*(A)))                     //占空比标幺转换
#define Q28I_VOLTAGE_TO_PU(A)               ((Q32I_)(MOTOR_Q28_PU*(A)/V_BASE))              //电压标幺转换
#define Q28I_CURRENT_TO_PU(A)               ((Q32I_)(MOTOR_Q28_PU*(A)/I_BASE))              //电流标幺转换
#define Q28I_FREQ_TO_PU(A)                  ((Q32I_)(MOTOR_Q28_PU*(A)/F_BASE))              //频率标幺转换
#define Q28I_ANGLE_TO_PU(A)                 ((Q32I_)(MOTOR_Q28_PU*(A)/MATH_2PI_F))          //角度标幺转换
#define Q28I_DUTY_TO_PU(A)                  ((Q32I_)(MOTOR_Q28_PU*(A)))                     //占空比标幺转换

#define Q14I_VOLTAGE_PU                     (Q14I_VOLTAGE_TO_PU(MOTOR_VOLTAGE_V))           //额定电压标幺值
#define Q14I_CURRENT_PHASE_PU               (Q14I_CURRENT_TO_PU(MOTOR_CURRENT_PHASE_A))     //额定相电流标幺值
#define Q14I_CURRENT_BUS_PU                 (Q14I_CURRENT_TO_PU(MOTOR_CURRENT_BUS_A))       //额定母线电流标幺值
#define Q14I_CURRENT_BRAKE_PU               (Q14I_CURRENT_TO_PU(MOTOR_CURRENT_BRAKE_A))     //额定刹车电流标幺值
#define Q14I_MAX_FREQ_PU                    (Q14I_FREQ_TO_PU(MOTOR_MAX_FREQ))               //最高频率标幺值
#define Q14I_MIN_FREQ_PU                    (Q14I_FREQ_TO_PU(MOTOR_MIN_FREQ))               //最低频率标幺值


/************************************浮点标幺************************************/
#define HTs_PU                              (MOTOR_HTs/T_BASE)
#define LTs_PU                              (MOTOR_LTs/T_BASE)
#define Rs_PU                               (MOTOR_Rs/R_BASE)
#define Ld_PU                               (MOTOR_Ld/L_BASE)
#define Lq_PU                               (MOTOR_Lq/L_BASE)
#define Ls_PU                               (MOTOR_Ls/L_BASE)
#define FLUX_PU                             (MOTOR_FLUX/P_BASE)

#define VOLTAGE_TO_PU(A)                    ((A)/V_BASE)                            //电压标幺转换
#define CURRENT_TO_PU(A)                    ((A)/I_BASE)                            //电流标幺转换
#define FREQ_TO_PU(A)                       ((A)/F_BASE)                            //频率标幺转换
#define ANGLE_TO_PU(A)                      ((A)/MATH_2PI_F)                        //角度标幺转换

#define VOLTAGE_PU                          (VOLTAGE_TO_PU(MOTOR_VOLTAGE_V))        //额定电压标幺值
#define CURRENT_PHASE_PU                    (CURRENT_TO_PU(MOTOR_CURRENT_PHASE_A))  //额定相电流标幺值
#define CURRENT_BUS_PU                      (CURRENT_TO_PU(MOTOR_CURRENT_BUS_A))    //额定母线电流标幺值
#define CURRENT_BRAKE_PU                    (CURRENT_TO_PU(MOTOR_CURRENT_BRAKE_A))  //额定刹车电流标幺值
#define MAX_FREQ_PU                         (FREQ_TO_PU(MOTOR_MAX_FREQ))            //最高频率标幺值
#define MIN_FREQ_PU                         (FREQ_TO_PU(MOTOR_MIN_FREQ))            //最低频率标幺值


#endif /* PMSM_PARA_H */
