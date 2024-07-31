/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef MotorFoc_H
#define MotorFoc_H

#include <stdint.h>
#include "Math.h"

//电机使能控制1：电机运行；0：电机不运行
#define USER_MOTOR_1_EN                                 (1U)
#define USER_MOTOR_2_EN                                 (1U)
    
//有感算法
#define USER_MOTOR_SENSE_NO                             (0000U)
#define USER_MOTOR_SENSE_HALL                           (1000U)                         //有感霍尔
#define USER_MOTOR_SENSE_RPS                            (2000U)                         //有感RPS

//无感启动算法
#define USER_MOTOR_START_MASK                           (0F00U)
#define USER_MOTOR_START_IF                             (0100U)                         //IF
#define USER_MOTOR_START_FLUX                           (0200U)                         //非线性磁链

//无感低速算法
#define USER_MOTOR_LOWSPEED_MASK                        (00F0U)
#define USER_MOTOR_LOWSPEED_FLUX                        (0010U)                         //非线性磁链

//无感高速算法
#define USER_MOTOR_HIGHSPEED_MASK                       (000FU)
#define USER_MOTOR_HIGHSPEED_FLUX                       (0001U)                         //非线性磁链
#define USER_MOTOR_HIGHSPEED_SMO                        (0002U)                         //SMO

//电机运行模式
#define USER_MOTOR_SENSE_MODE                           (USER_MOTOR_SENSE_HALL)
#define USER_MOTOR_START_MODE                           (USER_MOTOR_START_IF)
#define USER_MOTOR_LOWSPEED_MODE                        (USER_MOTOR_LOWSPEED_FLUX)
#define USER_MOTOR_HIGHSPEED_MODE                       (USER_MOTOR_HIGHSPEED_SMO)

#define USER_HALL_SPEED_LPF_COEFF                       (200.0f)                        //0~1000，越小滤波越深
#define USER_PLL_SPEED_LPF_COEFF                        (50.0f)                         //0~1000，越小滤波越深
#define USER_VDC_LPF_COEFF                              (50.0f)                         //0~1000，越小滤波越深

//霍尔传感器安装方式参数
#define USER_HALLSYNCANGLE_RD                           (0.0125663735897932384626433832795f)
#define USER_HALLFIRSTORDER                             (1U)
#define USER_HALLSECONDORDER                            (2U)
#define USER_HALLORDER                                  (USER_HALLFIRSTORDER)

/**
 *  @brief EST paramter of calculation type definition
 */
/**
 *  @brief RAMP paramter type definition
 */
typedef struct
{
    float Init; /*!< Input: target input */
    float Target; /*!< Input: target input */
    float Step;   /*!< Parameter: step of ramp */
    float Output; /*!< Output: output value */
}ST_RAMP_CAL;

/**
 *  @brief EST paramter of calculation type definition
 */
typedef struct
{
    float Ref;	   /*!< Input: Reference input */
    float Fdb;	   /*!< Input: Feedback input */
    float Output;	   /*!< Output: PID output */
    float Kp;		   /*!< Parameter: Proportional gain */
    float Ki;		   /*!< Parameter: Integral gain */
    float Kd;		   /*!< Parameter: Derivative gain */
    float OutMax;	   /*!< Parameter: Maximum output */
    float OutMin;	   /*!< Parameter: Minimum output */
    float Ui;		   /*!< Internal Variable: Integral output */
    float LastError;          /*!< Internal Variable: last error */
}ST_PID_POS;

typedef struct
{
    float AngleRad;
    ST_RAMP_CAL AngleRadRamp;       /*!< Internal Variable: The ramp for speed reference value */
    uint32_t AngleRad_cnt;
    uint8_t IF_Success_Flag;

    float AngleRad_Error;
    uint32_t AngleRad_time;
}ST_IF_CONTROL;

typedef struct
{
    float ElecFreqHz;
    float ElecFreqHz_Filter;
    float AngleRad;
    float AngleSpeed;

    float Ref_Yalpha;
    float Ref_Ybeta;
    float Est_Xalpha;
    float Est_Xbeta;
    float Cos_Angle;
    float Sin_Angle;
    float Nn_alpha;
    float Nn_beta;
    float Nn_2;
    
    float Rs;
    float Ls;
    float Ref_Flux_2;
    float Ts;
    float Kt;
    ST_PID_POS        Pll_Pid;      /*!< Internal Variable: The PLL PID in FSO */
}ST_FLUX_CONTROL;

typedef struct
{
    float ElecFreqHz;
    float ElecFreqHz_Filter;
    float AngleRad;
    float AngleSpeed;

    float Est_Ialpha;
    float Est_Ibeta;
    float Est_Ealpha;
    float Est_Ebeta;
    
    float Rs;
    float Ld;
    float Lq;
    float One_Over_Ld;
    float Rs_Over_Ld;
    float Ld_Lq_Over_Ld;
    float Ts;
    float K1;
    float K2;
    ST_PID_POS        Pll_Pid;      /*!< Internal Variable: The PLL PID in FSO */
}ST_SMO_CONTROL;

/**
 *  @brief TC control varible type definition
 */
typedef struct
{
    float Speed;     /*!< Input: The speed feedback */
    float SpeedRef;  /*!< Input: The speed reference value of speed loop control, not available in torque mode */
    float SpeedMax;  /*!< Input: The speed reference value of speed loop control, not available in torque mode */
    float SpeedMin;  /*!< Input: The speed reference value of speed loop control, not available in torque mode */
    float IdRef;
    float IqRef;

    ST_PID_POS PidSpd;         /*!< Internal Variable: The PID for speed loop */
    ST_RAMP_CAL SpdRamp;       /*!< Internal Variable: The ramp for speed reference value */
    ST_RAMP_CAL CurrentRamp; /*!< Internal Variable: The ramp for I/F control current */

    float SpeedChange;  /*!< Input: The speed reference value of speed loop control, not available in torque mode */
    uint32_t SpeedChangeTime_Num;  /*!< Input: The speed reference value of speed loop control, not available in torque mode */
}ST_TC_CONTROL;

typedef struct
{
    float ElecFreqHz;
    
    float RealVdc;
    float IdRef;
    float IqRef;
    float Ia;      /*!< Input: The phase-A current */
    float Ib;      /*!< Input: The phase-B current */
    float Ic;      /*!< Input: The phase-C current */
    float Ialpha;      /*!< Input: The phase-A current */
    float Ibeta;      /*!< Input: The phase-B current */
    float Id;      /*!< Input: The phase-A current */
    float Iq;      /*!< Input: The phase-B current */
    
    ST_PID_POS PidId;
    ST_PID_POS PidIq;
    float AngleRad; /*!< Input: The motor electric angle */
    float SinValue;
    float CosValue;
    
    float VsMaxScale;
    float VsMax;
    
    float Ualpha;      /*!< Input: The phase-A current */
    float Ubeta;      /*!< Input: The phase-B current */
    float Ud;      /*!< Input: The phase-A current */
    float Uq;      /*!< Input: The phase-B current */
    float TaPu;     /*!< Output: reference phase-a duty ratio */
    float TbPu;     /*!< Output: reference phase-b duty ratio */
    float TcPu;     /*!< Output: reference phase-c duty ratio */
    
    float MaxScale; /*!< Output: Max scale in pwm */
    float MinScale; /*!< Output: Min scale in pwm */
    float ERROR_ANGLE; /*!< Output: Min scale in pwm */
}ST_FOC_CONTROL;

typedef struct
{
    uint8_t             Brake_En;         
    uint8_t             Brake_Run_Flag;   
    uint8_t             Brake_Finish_Flag;
    
    float               Duty;           
    uint32_t            Brakecnt;       
    uint32_t            BrakeCurrentcnt;
    
    float               MinBrakeCurrent;      
    float               MaxScale;             
    float               MinScale;             
    uint32_t            BrakeTime;            
    uint32_t            CurrentFilterTime;    
}ST_BRAKE_CONTROL;

typedef struct
{
    float HallDir;   
    uint8_t HallLastLevel;             
    uint8_t HallCurrentLevel;    
    uint32_t HallCount_tmp[6];       
    uint32_t HallLastCount;            
    uint32_t HallCurrentCount;         
    uint32_t HallStallCount;           
    uint32_t HallStallLastCount;       
    uint32_t HallStall_cnt;            
    float AngleRad;                 
    float ElecFreqHz;                 
    float ElecFreqHz_Filter;  
    
    float Ts;        
    float TIM_FreqHz;  
    uint32_t HallStallTime;        
}ST_HALL_CONTROL;

void Ipark_Transform(ST_FOC_CONTROL* pFoc);
void Park_Transform(ST_FOC_CONTROL* pFoc);
void Clarke_Transform(ST_FOC_CONTROL* pFoc);
void SVPWM_Cal(ST_FOC_CONTROL* pFoc);

void Ramp_Init(ST_RAMP_CAL* pRamp, float Output);
void Ramp_Cal(ST_RAMP_CAL* pRamp);
void PID_POS_Init(ST_PID_POS* pPID, float init);
void PID_POS_Cal(ST_PID_POS* pPID);

void Est_IF_Init(ST_IF_CONTROL* pCTRL);
void Est_IF(ST_IF_CONTROL* pCTRL, float Est_AngleRad);

void Est_Flux_Init(ST_FLUX_CONTROL* pCTRL);
void Est_Flux(ST_FOC_CONTROL* pFoc, ST_FLUX_CONTROL* pCTRL);

void Est_SMO_Init(ST_SMO_CONTROL* pCTRL);
void Est_SMO(ST_FOC_CONTROL* pFoc, ST_SMO_CONTROL* pCTRL);

void Foc_Cal(ST_FOC_CONTROL* pFoc);
void Tc_Cal(ST_TC_CONTROL* pTc);
void Motor_Brake_Control(ST_BRAKE_CONTROL* pBrake, ST_FOC_CONTROL* pFoc);

void Hallest_Init(ST_HALL_CONTROL* pHall);
void Hallest_Low_Speed(ST_HALL_CONTROL* pHall);
void Hallest_High_Speed(ST_HALL_CONTROL* pHall);
void Hallest_Angle_Inc(ST_HALL_CONTROL* pHall, uint32_t cnt);

/** @}end of group PMSM */

/** @}end of group Z20K14XM_Foc */

#endif /* MotorState_H */
