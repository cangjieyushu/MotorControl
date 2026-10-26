/**
 * @file    pmsm_para.h
 * @brief   PMSM 电机参数与状态机定义
 * @author  CJYS
 * @date    2024/1/1
 *
 * 提供：
 *   - 电机额定参数（当前选中型号见下方未注释块）
 *   - 极对数、转速 / 频率换算、标幺化、Q 格式系数
 *   - 状态机 / 环路模式 / 电机标志 / API 结构体
 */

#ifndef PMSM_PARA_H
#define PMSM_PARA_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_fun.h"
#include "hw_para.h"

/* ======================== 2. Defines ====================== */

/* ---- 可选电机型号参考（未选中，仅作选型保留，不参与编译）---- */

///* 压缩机 */
//#define MOTOR_VOLTAGE_V                     (385.0f)            //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (15.0f)             //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (7.00f)             //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (1.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HW_PWM_HIGH_FREQ*((float)HW_CURRENT_LOOP_PRESCALER))
//#define MOTOR_LTs                           (HW_STICK_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (4.0f)                          //转子极对数
//#define MOTOR_Rs                            (3.000f)                        //Ω，相电阻
//#define MOTOR_Ld                            (8.000f*0.001f)                 //H，d轴电感
//#define MOTOR_Lq                            (16.00f*0.001f)                 //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.00875f)                      //Wb
//#define MOTOR_MAX_SPEED                     (8000.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (500.0f)              //rpm，最低转速

/* 研磨电机 */
//#define MOTOR_VOLTAGE_V                     (315.0f)            //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (1.5f)              //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (1.25f)             //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (1.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HW_PWM_HIGH_FREQ*((float)HW_CURRENT_LOOP_PRESCALER))
//#define MOTOR_LTs                           (HW_STICK_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (4.0f)                          //转子极对数
//#define MOTOR_Rs                            (15.00f)                        //Ω，相电阻
//#define MOTOR_Ld                            (40.00f*0.001f)                 //H，d轴电感
//#define MOTOR_Lq                            (45.00f*0.001f)                 //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.00875f)                      //Wb
//#define MOTOR_MAX_SPEED                     (2500.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (500.0f)              //rpm，最低转速

/* 测功机 */
//#define MOTOR_VOLTAGE_V                     (24.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (8.0f)              //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (3.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HW_PWM_HIGH_FREQ*((float)HW_CURRENT_LOOP_PRESCALER))
//#define MOTOR_LTs                           (HW_STICK_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (4.0f)                          //转子极对数
//#define MOTOR_Rs                            (0.562f)                        //Ω，相电阻
//#define MOTOR_Ld                            (0.365f*0.001f)                 //H，d轴电感
//#define MOTOR_Lq                            (0.405f*0.001f)                 //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.00875f)                      //Wb
//#define MOTOR_MAX_SPEED                     (4000.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (100.0f)              //rpm，最低转速

/* ---- 电机额定参数：当前选中型号（正点原子）---- */
#define MOTOR_VOLTAGE_V                     (24.0f)             //V，母线电压
#define MOTOR_CURRENT_PHASE_A               (12.0f)             //A，相电流幅值
#define MOTOR_CURRENT_BUS_A                 (6.0f)              //A，母线电流
#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流
#define MOTOR_HTs                           (1.0f/1000.0f/HW_PWM_HIGH_FREQ*((float)HW_CURRENT_LOOP_PRESCALER))
#define MOTOR_LTs                           (HW_STICK_FREQ/1000.0f)
#define MOTOR_POLE_PAIR                     (2.0f)                          //转子极对数
#define MOTOR_Rs                            (0.233f)                        //Ω，相电阻
#define MOTOR_Ld                            (0.381f*0.001f)                 //H，d轴电感
#define MOTOR_Lq                            (0.468f*0.001f)                 //H，q轴电感，q轴电感至少需要比d轴电感大10uH
#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
#define MOTOR_FLUX                          (0.0165f)                       //Wb
#define MOTOR_MAX_SPEED                     (6000.0f)             //rpm，最高转速
#define MOTOR_MIN_SPEED                     (1.0f)              //rpm，最低转速

/* 风机 */
//#define MOTOR_VOLTAGE_V                     (12.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (8.0f)              //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (8.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HW_PWM_HIGH_FREQ*((float)HW_CURRENT_LOOP_PRESCALER))
//#define MOTOR_LTs                           (HW_STICK_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (2.0f)                          //转子极对数
//#define MOTOR_Rs                            (0.175f)                        //Ω，相电阻
//#define MOTOR_Ld                            (0.0379f*0.001f)                //H，d轴电感
//#define MOTOR_Lq                            (0.0487f*0.001f)                //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.00069f)                      //Wb
//#define MOTOR_MAX_SPEED                     (48000.0f)            //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (100.0f)              //rpm，最低转速

/* 灰色电机 */
//#define MOTOR_VOLTAGE_V                     (12.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (8.0f)              //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (6.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HW_PWM_HIGH_FREQ)
//#define MOTOR_LTs                           (HW_STICK_FREQ/1000.0f*((float)HW_CURRENT_LOOP_PRESCALER))
//#define MOTOR_POLE_PAIR                     (4.0f)                          //转子极对数
//#define MOTOR_Rs                            (0.365f)                        //Ω，相电阻
//#define MOTOR_Ld                            (0.251f*0.001f)                 //H，d轴电感
//#define MOTOR_Lq                            (0.271f*0.001f)                 //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.00504f)                      //Wb
//#define MOTOR_MAX_SPEED                     (3600.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (100.0f)              //rpm，最低转速

/* 手枪钻 */
//#define MOTOR_VOLTAGE_V                     (12.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (12.0f)             //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (5.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (1.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HW_PWM_HIGH_FREQ*((float)HW_CURRENT_LOOP_PRESCALER))
//#define MOTOR_LTs                           (HW_STICK_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (2.0f)                          //转子极对数
//#define MOTOR_Rs                            (0.0756f)                       //Ω，相电阻
//#define MOTOR_Ld                            (0.0188f*0.001f)                //H，d轴电感
//#define MOTOR_Lq                            (0.0197f*0.001f)                //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.00975f)                      //Wb
//#define MOTOR_MAX_SPEED                     (24000.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (100.0f)               //rpm，最低转速

/* 小电机 */
//#define MOTOR_VOLTAGE_V                     (24.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (3.0f)              //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (2.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (2.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HW_PWM_HIGH_FREQ*((float)HW_CURRENT_LOOP_PRESCALER))
//#define MOTOR_LTs                           (HW_STICK_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (2.0f)                          //转子极对数
//#define MOTOR_Rs                            (8.39f)                         //Ω，相电阻
//#define MOTOR_Ld                            (2.38f*0.001f)                  //H，d轴电感
//#define MOTOR_Lq                            (2.45f*0.001f)                  //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.0341f)                       //Wb
//#define MOTOR_MAX_SPEED                     (3000.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (100.0f)              //rpm，最低转速

/* 高速电机 1 */
//#define MOTOR_VOLTAGE_V                     (24.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (12.0f)             //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (6.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (3.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HW_PWM_HIGH_FREQ*((float)HW_CURRENT_LOOP_PRESCALER))
//#define MOTOR_LTs                           (HW_STICK_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (1.0f)                          //转子极对数
//#define MOTOR_Rs                            (0.325f)                        //Ω，相电阻
//#define MOTOR_Ld                            (140.00f*0.001f*0.001f)         //H，d轴电感
//#define MOTOR_Lq                            (145.00f*0.001f*0.001f)         //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.00875f)                      //Wb
//#define MOTOR_MAX_SPEED                     (90000.0f)             //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (4500.0f)              //rpm，最低转速

/* 高速电机 2 */
//#define MOTOR_VOLTAGE_V                     (24.0f)             //V，母线电压
//#define MOTOR_CURRENT_PHASE_A               (12.0f)             //A，相电流幅值
//#define MOTOR_CURRENT_BUS_A                 (8.0f)              //A，母线电流
//#define MOTOR_CURRENT_BRAKE_A               (3.0f)              //A，刹车电流
//#define MOTOR_HTs                           (1.0f/1000.0f/HW_PWM_HIGH_FREQ*((float)HW_CURRENT_LOOP_PRESCALER))
//#define MOTOR_LTs                           (HW_STICK_FREQ/1000.0f)
//#define MOTOR_POLE_PAIR                     (1.0f)                          //转子极对数
//#define MOTOR_Rs                            (0.072f)                        //Ω，相电阻
//#define MOTOR_Ld                            (30.00f*0.001f*0.001f)          //H，d轴电感
//#define MOTOR_Lq                            (32.00f*0.001f*0.001f)          //H，q轴电感，q轴电感至少需要比d轴电感大10uH
//#define MOTOR_Ls                            (0.5f*(MOTOR_Ld + MOTOR_Lq))    //H，相电感
//#define MOTOR_FLUX                          (0.00875f)                      //Wb
//#define MOTOR_MAX_SPEED                     (120000.0f)            //rpm，最高转速
//#define MOTOR_MIN_SPEED                     (3600.0f)              //rpm，最低转速

/* ---- 转速 / 频率换算 ---- */
#define MOTOR_SPEED_TO_FREQ(A)              (MOTOR_POLE_PAIR*(A)/60.0f)  /**< 转速→电频率 */
#define MOTOR_FREQ_TO_SPEED(A)              (60.0f*(A)/MOTOR_POLE_PAIR)  /**< 电频率→转速 */

#define MOTOR_MAX_FREQ                      (MOTOR_SPEED_TO_FREQ(MOTOR_MAX_SPEED)) /**< 最高电频率（Hz） */
#define MOTOR_MIN_FREQ                      (MOTOR_SPEED_TO_FREQ(MOTOR_MIN_SPEED)) /**< 最低电频率（Hz） */

/* ---- 标幺化基准 ---- */
#define V_BASE                              (HW_ADC_VOLTAGE_MAX)   /**< 电压基准（V） */
#define I_BASE                              (HW_ADC_CURRENT_MAX)   /**< 电流基准（A） */
#define F_BASE                              (MOTOR_MAX_FREQ)       /**< 频率基准（Hz） */
#define R_BASE                              (V_BASE/I_BASE)        /**< 电阻基准（Ω） */
#define L_BASE                              (V_BASE/F_BASE/I_BASE) /**< 电感基准（H） */
#define P_BASE                              (V_BASE/F_BASE)        /**< 磁链基准（Wb） */
#define T_BASE                              (1.0f/F_BASE)          /**< 时间基准（s） */

/* ---- 定点标幺 ---- */
#define Q14I_HTs_PU                         ((Q32I_)(Q14U_MAX_F*MOTOR_HTs/T_BASE))
#define Q14I_LTs_PU                         ((Q32I_)(Q14U_MAX_F*MOTOR_LTs/T_BASE))
#define Q14I_Rs_PU                          ((Q32I_)(Q14U_MAX_F*MOTOR_Rs/R_BASE))
#define Q14I_Ld_PU                          ((Q32I_)(Q14U_MAX_F*MOTOR_Ld/L_BASE))
#define Q14I_Lq_PU                          ((Q32I_)(Q14U_MAX_F*MOTOR_Lq/L_BASE))
#define Q14I_Ls_PU                          ((Q32I_)(Q14U_MAX_F*MOTOR_Ls/L_BASE))
#define Q14I_FLUX_PU                        ((Q32I_)(Q14U_MAX_F*MOTOR_FLUX/P_BASE))

#define Q14I_VOLTAGE_TO_PU(A)               ((Q32I_)(Q14U_MAX_F*(A)/V_BASE))     /**< 电压→Q14 */
#define Q14I_CURRENT_TO_PU(A)               ((Q32I_)(Q14U_MAX_F*(A)/I_BASE))     /**< 电流→Q14 */
#define Q14I_FREQ_TO_PU(A)                  ((Q32I_)(Q14U_MAX_F*(A)/F_BASE))     /**< 频率→Q14 */
#define Q14I_ANGLE_TO_PU(A)                 ((Q32I_)(Q14U_MAX_F*(A)/MATH_2PI_F)) /**< 角度→Q14 */
#define Q14I_DUTY_TO_PU(A)                  ((Q32I_)(Q14U_MAX_F*(A)))            /**< 占空比→Q14 */
#define Q28I_VOLTAGE_TO_PU(A)               ((Q32I_)(Q28U_MAX_F*(A)/V_BASE))     /**< 电压→Q28 */
#define Q28I_CURRENT_TO_PU(A)               ((Q32I_)(Q28U_MAX_F*(A)/I_BASE))     /**< 电流→Q28 */
#define Q28I_FREQ_TO_PU(A)                  ((Q32I_)(Q28U_MAX_F*(A)/F_BASE))     /**< 频率→Q28 */
#define Q28I_ANGLE_TO_PU(A)                 ((Q32I_)(Q28U_MAX_F*(A)/MATH_2PI_F)) /**< 角度→Q28 */
#define Q28I_DUTY_TO_PU(A)                  ((Q32I_)(Q28U_MAX_F*(A)))            /**< 占空比→Q28 */

#define Q14I_VOLTAGE_PU                     (Q14I_VOLTAGE_TO_PU(MOTOR_VOLTAGE_V))       /**< 额定电压 Q14 */
#define Q14I_CURRENT_PHASE_PU               (Q14I_CURRENT_TO_PU(MOTOR_CURRENT_PHASE_A)) /**< 额定相电流 Q14 */
#define Q14I_CURRENT_BUS_PU                 (Q14I_CURRENT_TO_PU(MOTOR_CURRENT_BUS_A))   /**< 额定母线电流 Q14 */
#define Q14I_CURRENT_BRAKE_PU               (Q14I_CURRENT_TO_PU(MOTOR_CURRENT_BRAKE_A)) /**< 额定刹车电流 Q14 */
#define Q14I_MAX_FREQ_PU                    (Q14I_FREQ_TO_PU(MOTOR_MAX_FREQ))           /**< 最高频率 Q14 */
#define Q14I_MIN_FREQ_PU                    (Q14I_FREQ_TO_PU(MOTOR_MIN_FREQ))           /**< 最低频率 Q14 */

/* ---- 浮点标幺 ---- */
#define HTs_PU                              (MOTOR_HTs/T_BASE)
#define LTs_PU                              (MOTOR_LTs/T_BASE)
#define Rs_PU                               (MOTOR_Rs/R_BASE)
#define Ld_PU                               (MOTOR_Ld/L_BASE)
#define Lq_PU                               (MOTOR_Lq/L_BASE)
#define Ls_PU                               (MOTOR_Ls/L_BASE)
#define FLUX_PU                             (MOTOR_FLUX/P_BASE)

#define VOLTAGE_TO_PU(A)                    ((A)/V_BASE)    /**< 电压→浮点标幺 */
#define CURRENT_TO_PU(A)                    ((A)/I_BASE)    /**< 电流→浮点标幺 */
#define FREQ_TO_PU(A)                       ((A)/F_BASE)    /**< 频率→浮点标幺 */
#define ANGLE_TO_PU(A)                      ((A)/MATH_2PI_F)/**< 角度→浮点标幺 */

#define VOLTAGE_PU                          (VOLTAGE_TO_PU(MOTOR_VOLTAGE_V))       /**< 额定电压 */
#define CURRENT_PHASE_PU                    (CURRENT_TO_PU(MOTOR_CURRENT_PHASE_A)) /**< 额定相电流 */
#define CURRENT_BUS_PU                      (CURRENT_TO_PU(MOTOR_CURRENT_BUS_A))   /**< 额定母线电流 */
#define CURRENT_BRAKE_PU                    (CURRENT_TO_PU(MOTOR_CURRENT_BRAKE_A)) /**< 额定刹车电流 */
#define MAX_FREQ_PU                         (FREQ_TO_PU(MOTOR_MAX_FREQ))           /**< 最高频率 */
#define MIN_FREQ_PU                         (FREQ_TO_PU(MOTOR_MIN_FREQ))           /**< 最低频率 */

/* ======================== 3. Typedefs ===================== */

/**
 * @brief 电机任务状态机
 */
typedef enum {
    MOTOR_STATE_PRE,        /**< 参数复位阶段 */
    MOTOR_STATE_INIT,       /**< 硬件初始化阶段 */
    MOTOR_STATE_IDLE,       /**< 电机静止检测阶段 */
    MOTOR_STATE_BOOT,       /**< 自举电容充电阶段 */
    MOTOR_STATE_POSITION,   /**< 脉冲定位阶段 */
    MOTOR_STATE_RUN,        /**< 电机运行阶段 */
    MOTOR_STATE_BRAKE,      /**< 电机刹车阶段 */
} EM_MOTOR_STATE;

/**
 * @brief 电机环路模式
 */
typedef enum {
    MOTOR_LOOP_ALIGN,       /**< 定位阶段 */
    MOTOR_LOOP_OPEN,        /**< 开环阶段 */
    MOTOR_LOOP_CLOSE,       /**< 闭环阶段 */
} EM_MOTOR_LOOP_MODE;

/**
 * @brief 电机运行标志联合体
 */
typedef union {
    SC_ALL all;                         /**< 整体访问 */
    struct {
        SC_BIT motor_target_dir    :1;  /**< 目标方向：1 正 / 0 反 */
        SC_BIT motor_real_dir      :1;  /**< 实际方向：1 正 / 0 反 */
        SC_BIT motor_running_flag  :1;  /**< 运行标志 */
        SC_BIT motor_enable_flag   :1;  /**< 使能标志 */
        SC_BIT motor_position_flag :1;  /**< 位置环使能 */
        SC_BIT motor_speed_flag    :1;  /**< 速度环使能 */
        SC_BIT motor_busA_flag     :1;  /**< 母线电流环使能 */
        SC_BIT motor_busP_flag     :1;  /**< 母线功率环使能 */
    } bit;
} UN_MOTOR_FLAG;

/**
 * @brief 电机对外 API 数值
 */
typedef struct {
    Q32I_ Target_Speed_pu;      /**< 目标转速指令 */
    Q32I_ Real_Speed_pu;        /**< 实际转速 */
    Q32I_ Real_Iphase_pu;       /**< 实际相电流 */
    Q32I_ Real_Ibus_pu;         /**< 实际母线电流 */

    Q32I_ Max_Speed_rpm;        /**< 最高转速（rpm） */
    Q32I_ Min_Speed_rpm;        /**< 最低转速（rpm） */
    Q32I_ Max_Iphase_0p01A;     /**< 相电流满量程（0.01A） */
    Q32I_ Max_IBus_0p01A;       /**< 母线电流满量程（0.01A） */
} ST_MOTOR_API;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

#endif /* PMSM_PARA_H */
