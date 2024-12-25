/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef USER_PMSM_H
#define USER_PMSM_H

#include "Math.h"
#include "MotorHal_cfg.h"   

//电机额定参数
#define MOTOR_VOLTAGE_V                     (24.0f)             //V，母线电压
#define MOTOR_CURRENT_PHASE_A               (30.0f)             //A，相电流幅值
#define MOTOR_CURRENT_BUS_A                 (10.0f)             //A，母线电流
#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流

#define MOTOR_HTs                           (1.0f/1000.0f/HAL_PWM_FREQ_SET)
#define MOTOR_LTs                           (HAL_SLOW_TIMER_FREQ/2.0f/1000.0f)
#define MOTOR_POLE_PAIR                     (2.0f)                          //转子极对数
#define MOTOR_Rs                            (0.31f)                         //Ω，相电阻
#define MOTOR_Ld                            (0.37f*0.001f)                  //H，d轴电感
#define MOTOR_Lq                            (0.44f*0.001f)                  //H，q轴电感，q轴电感至少需要比d轴电感大10uH
#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
#define MOTOR_FLUX                          (0.017f)                        //Wb

#define MOTOR_MAX_SPEED                     (4000.0f)             //rpm，最高转速
#define MOTOR_MIN_SPEED                     (1000.0f)             //rpm，最低转速

#define MOTOR_MAX_SRAD                      (MATH_2PI_F*MOTOR_POLE_PAIR*MOTOR_MAX_SPEED/60.0f)        //Hz，最高角频率
#define MOTOR_MIN_SRAD                      (MATH_2PI_F*MOTOR_POLE_PAIR*MOTOR_MIN_SPEED/60.0f)        //Hz，最低角频率

//dq轴输出电压限制，如果保证电压矢量为圆形，设置为0.5774f，如果需要过调制，则最大为0.6667f
#define MOTOR_VS_SCALE                      (0.5774f)

//标幺化
#define V_BASE                              (0.5f*HAL_ADC_VOLTAGE_MAX)      //V，电压
#define I_BASE                              (0.5f*HAL_ADC_CURRENT_MAX)      //A，电流
#define F_BASE                              (1.0f*MOTOR_POLE_PAIR*MOTOR_MAX_SPEED/60.0f)    //Hz，频率

#define W_BASE                              (F_BASE*MATH_2PI_F)     //Hz，角频率
#define R_BASE                              (V_BASE/I_BASE)         //Ω，电阻

#define L_BASE                              (V_BASE/W_BASE/I_BASE)  //H，电感
#define P_BASE                              (V_BASE/W_BASE)         //wb，磁链
#define T_BASE                              (MATH_2PI_F/W_BASE)     //s,时间

#define MOTOR_Q14_PU                        (Q14U_MAX)      //16384
#define MOTOR_Q24_PU                        (Q24U_MAX)      //

#define Q24I_VOLTAGE_SCALE_PU               (Q32U_)(MOTOR_Q24_PU*HAL_ADC_VOLTAGE_SCALE/V_BASE)          //电压
#define Q24I_CURRENT_SCALE_PU               (Q32U_)(MOTOR_Q24_PU*HAL_ADC_CURRENT_SCALE/I_BASE)          //电流

#define Q14I_VOLTAGE_LSB_TO_PU(a)           (Q32I_RHT_10(Q24I_VOLTAGE_SCALE_PU*(a)))          //电压
#define Q14I_CURRENT_LSB_TO_PU(a)           (Q32I_RHT_10(Q24I_CURRENT_SCALE_PU*(a)))          //电流
     
#define Q14I_HTs_PU                         (Q32U_)(MOTOR_Q14_PU*MOTOR_HTs/T_BASE)
#define Q14I_LTs_PU                         (Q32U_)(MOTOR_Q14_PU*MOTOR_LTs/T_BASE)
#define Q14I_Rs_PU                          (Q32U_)(MOTOR_Q14_PU*MOTOR_Rs/R_BASE)       //Ω，相电阻
#define Q14I_Ld_PU                          (Q32U_)(MOTOR_Q14_PU*MOTOR_Ld/L_BASE)       //H，d轴电感
#define Q14I_Lq_PU                          (Q32U_)(MOTOR_Q14_PU*MOTOR_Lq/L_BASE)       //H，q轴电感
#define Q14I_Ls_PU                          (Q32U_)(MOTOR_Q14_PU*MOTOR_Ls/L_BASE)       //H，相电感
#define Q14I_FLUX_PU                        (Q32U_)(MOTOR_Q14_PU*MOTOR_FLUX/P_BASE)     //V*S，Wb

#define Q14I_VOLTAGE_MOTOR_TO_PU(a)         (Q32U_)(MOTOR_Q14_PU*(a)/V_BASE)              //电压标幺转换
#define Q14I_CURRENT_MOTOR_TO_PU(a)         (Q32U_)(MOTOR_Q14_PU*(a)/I_BASE)              //电流标幺转换
#define Q14I_SRAD_MOTOR_TO_PU(a)            (Q32U_)(MOTOR_Q14_PU*(a)/W_BASE)              //频率标幺转换

#define Q14I_VOLTAGE_PU                     (Q32U_)(MOTOR_Q14_PU*MOTOR_VOLTAGE_V/V_BASE)        //额定电压标幺值
#define Q14I_CURRENT_PHASE_A_PU             (Q32U_)(MOTOR_Q14_PU*MOTOR_CURRENT_PHASE_A/I_BASE)  //额定相电流标幺值
#define Q14I_CURRENT_BUS_A_IPU              (Q32U_)(MOTOR_Q14_PU*MOTOR_CURRENT_BUS_A/I_BASE)    //额定母线电流标幺值
#define Q14I_CURRENT_BRAKE_A_PU             (Q32U_)(MOTOR_Q14_PU*MOTOR_CURRENT_BRAKE_A/I_BASE)  //额定刹车电流标幺值
#define Q14I_MAX_SRAD_PU                    (Q32U_)(MOTOR_Q14_PU*MOTOR_MAX_SRAD/W_BASE)         //额定频率标幺值
#define Q14I_MIN_SRAD_PU                    (Q32U_)(MOTOR_Q14_PU*MOTOR_MIN_SRAD/W_BASE)         //额定频率标幺值

#endif /* USER_PMSM_H */
