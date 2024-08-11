/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef USER_PMSM_H
#define USER_PMSM_H

//dq轴输出电压限制，如果保证电压矢量为圆形，设置为0.5774f，如果需要过调制，则最大为0.6667f
#define USER_MAX_VS_MAG_PU                      (0.5774f)

//全占空比输出使能标志位1：最大占空比输出，保存上一笔采样值用于当前周期进行计算，0：保证采样时间限制最大占空比的值
#define USER_ALL_DUTY_OUTPUT                    (1U)

//为了保证自举电容充电，上桥最大占空比输出限制
#define USER_PWM_MAXSCALE                       (1.0f)
#if(USER_ALL_DUTY_OUTPUT == 1U)
#define USER_PWM_MINSCALE                       (0.05f)
#else
#define USER_PWM_MINSCALE                       (HAL_ADC_SAMPLE_DUTY)
#endif
     
#define USER_MOTOR1_NUM_POLE_PAIRS              (2.0f)                  //极对数
#define USER_MOTOR1_Rs                          (0.15f)                 //Ω，相电阻
#define USER_MOTOR1_Ld                          ((0.265f)*(0.001f))      //H，d轴电感
#define USER_MOTOR1_Lq                          ((0.275f)*(0.001f))      //H，q轴电感
#define USER_MOTOR1_Ls                          ((0.5f)*(USER_MOTOR1_Ld + USER_MOTOR1_Lq))                 //H，相电感
#define USER_MOTOR1_ROTOR_FLUX                  (0.0166f)              //V*S，Wb
#define USER_MOTOR1_MAX_CURRENT                 (6.0f)                 //A,最大相电流
#define USER_MOTOR1_MAX_SPEED                   (100.0f * MATH_2PI)    //Hz,最大转速

//#define USER_MOTOR1_NUM_POLE_PAIRS              (6.0f)                  //极对数
//#define USER_MOTOR1_Rs                          (0.06f)                 //Ω，相电阻
//#define USER_MOTOR1_Ld                          ((0.065f)*(0.001f))      //H，d轴电感
//#define USER_MOTOR1_Lq                          ((0.115f)*(0.001f))      //H，q轴电感
//#define USER_MOTOR1_Ls                          ((0.5f)*(USER_MOTOR1_Ld + USER_MOTOR1_Lq))                 //H，相电感
//#define USER_MOTOR1_ROTOR_FLUX                  (0.006f)              //V*S，Wb
//#define USER_MOTOR1_MAX_CURRENT                 (6.0f)                 //A,最大相电流
//#define USER_MOTOR1_MAX_SPEED                   (260.0f)                //Hz,最大转速

//#define USER_MOTOR1_NUM_POLE_PAIRS              (6.0f)                  //极对数
//#define USER_MOTOR1_Rs                          (0.36f)                 //Ω，相电阻
//#define USER_MOTOR1_Ld                          ((0.225f)*(0.001f))      //H，d轴电感
//#define USER_MOTOR1_Lq                          ((0.245f)*(0.001f))      //H，q轴电感
//#define USER_MOTOR1_Ls                          ((0.5f)*(USER_MOTOR1_Ld + USER_MOTOR1_Lq))                 //H，相电感
//#define USER_MOTOR1_ROTOR_FLUX                  (0.00577f)              //V*S，Wb
//#define USER_MOTOR1_MAX_CURRENT                 (6.0f)                 //A,最大相电流
//#define USER_MOTOR1_MAX_SPEED                   (220.0f)                //Hz,最大转速

#endif /* USER_PMSM_H */
