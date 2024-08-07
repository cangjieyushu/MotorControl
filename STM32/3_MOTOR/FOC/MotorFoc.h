/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef MotorFoc_H
#define MotorFoc_H

#include <stdint.h>
#include "Math.h"
    
//有感算法
#define USER_MOTOR_SENSE_HALL                           (1000U)                         //有感霍尔
#define USER_MOTOR_SENSE_RPS                            (2000U)                         //有感RPS

//无感算法
#define USER_MOTOR_SENSELESS_FLUX                       (0001U)                         //FLUX
#define USER_MOTOR_SENSELESS_SVC                        (0002U)                         //SVC
#define USER_MOTOR_SENSELESS_SMO                        (0003U)                         //SMO

//电机运行模式
#define USER_MOTOR_MODE                                 (USER_MOTOR_SENSELESS_SVC)

#define USER_MOTOR_MTPA_EN                              (1U)
#define USER_MOTOR_FLUX_EN                              (1U)

#define USER_HALL_SPEED_LPF_COEFF                       (200.0f)                        //0~1000，越小滤波越深
#define USER_PLL_SPEED_LPF_COEFF                        (50.0f)                         //0~1000，越小滤波越深
#define USER_VDC_LPF_COEFF                              (50.0f)                         //0~1000，越小滤波越深

//霍尔传感器安装方式参数
#define USER_HALLSYNCANGLE_RD                           (0.0125663735897932384626433832795f)
#define USER_HALLFIRSTORDER                             (1U)
#define USER_HALLSECONDORDER                            (2U)
#define USER_HALLORDER                                  (USER_HALLFIRSTORDER)

typedef struct
{
    float Ia;    
    float Ib;    
    float Ic;    
    float Ialpha;
    float Ibeta; 
    float Id;    
    float Iq;    
    
    float Ualpha;      
    float Ubeta;
    float Ud;      
    float Uq;    
    
    float Vbat;
    float VsMax;
    
    float AngleRad;
    float SinValue;
    float CosValue;
    
    uint16_t Ia_data;    
    uint16_t Ib_data;    
    uint16_t Ic_data;   
    uint16_t Ia_offset;    
    uint16_t Ib_offset;    
    uint16_t Ic_offset; 
    uint16_t Vbat_data; 
    
    float VsMaxScale;
}ST_FOC_PARAMETER;

typedef struct
{
    float Ts; 
    float Rs;
    float Ls;
    float Ld;
    float Lq;
    float Flux;
    
    float Flux_2;
    
    float One_Over_Ld;
    float Rs_Over_Ld;
    float Ld_Lq_Over_Ld;
    
    float Eight_Lq_Ld_2;
    float One_Over_Lq_Ld_Over_4;
    
}ST_PMSM_PARAMETER;

typedef struct
{
    float Init;
    float Target;
    float Step;
    float Output;
}ST_RAMP;

typedef struct
{
    float Ref;
    float Fdb;
    float Output;
    float Kp;
    float Ki;
    float Kd;
    float OutMax;
    float OutMin;
    float Ui;
    float LastError;
}ST_PID;

typedef struct
{
    float Speed;   
    float SpeedRef;
    float IdRef;
    float IqRef;

    ST_PID PidSpd;    
    ST_RAMP CurrentRamp;  
    ST_RAMP SpdRamp;    

    float SpeedMax;
    float SpeedMin;
    float SpeedChange;
    uint32_t SpeedChangeTime_Num;
}ST_SPEED_CONTROL;

typedef struct
{
    float IdRef;   
    float IqRef;    
    
    ST_PID PidId;
    ST_PID PidIq;
    
    float Ta;    
    float Tb;     
    float Tc;        
    uint16_t Ta_value;    
    uint16_t Tb_value;     
    uint16_t Tc_value;  
    
    float MaxScale; 
    float MinScale; 
}ST_CURRENT_CONTROL;

typedef struct
{ 
    uint16_t            Ta_value;    
    uint16_t            Tb_value;     
    uint16_t            Tc_value;
    
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
    float IdRef;
    float IqRef;
}ST_MTPA_CONTROL;

typedef struct
{
    ST_PID PidV;
    float Theta;
    float IdRef;
    float IqRef;
}ST_WEAK_CONTROL;

typedef struct
{
    float AngleRad;
    ST_RAMP AngleRadRamp;
    uint32_t AngleRad_cnt;
    uint8_t IF_Success_Flag;

    float AngleRad_Error;
    uint32_t AngleRad_time;
}ST_IF_CONTROL;

typedef struct
{
    float AngleRad;
    float AngleSpeed;
    float AngleSpeed_Filter;

    float Est_Xalpha;
    float Est_Xbeta;
    
    float Ks;
    float Kt;
    ST_PID Pll_Pid;
}ST_FLUX_CONTROL;

typedef struct
{
    float AngleRad;
    float AngleSpeed;
    float AngleSpeed_Filter;
    
    float SpeedLimit;
    float Lambda;
    float Alpha;
}ST_SVC_CONTROL;

typedef struct
{
    float AngleRad;
    float AngleSpeed;
    float AngleSpeed_Filter;

    float Est_Ialpha;
    float Est_Ibeta;
    float Est_Ealpha;
    float Est_Ebeta;  
    
    float K1;
    float K2;
    ST_PID Pll_Pid;
}ST_SMO_CONTROL;

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
    float AngleSpeed;
    float AngleSpeed_Filter;
    
    float Ts;        
    float TIM_FreqHz;  
    uint32_t HallStallTime;        
}ST_HALL_CONTROL;

void Ipark_Transform(ST_FOC_PARAMETER* pFocPara);
void Park_Transform(ST_FOC_PARAMETER* pFocPara);
void Clark_Transform(ST_FOC_PARAMETER* pFocPara);
void SVPWM_Cal(ST_FOC_PARAMETER* pFocPara, ST_CURRENT_CONTROL* pCurrentCtrl);
    
void Ramp_Init(ST_RAMP* pRamp, float Output);
void Ramp_Control(ST_RAMP* pRamp);
void PID_POS_Init(ST_PID* pPID, float init);
void PID_POS_Control(ST_PID* pPID);

void MotorFoc_Speed_Loop(ST_SPEED_CONTROL* pSpeed);
void MotorFoc_Current_Loop(ST_FOC_PARAMETER* pFocPara, ST_CURRENT_CONTROL* pCurrentCtrl);
void Motor_Brake_Control(ST_BRAKE_CONTROL* pBrake, ST_FOC_PARAMETER* pFocPara);

void MTPA_Control(ST_PMSM_PARAMETER* pPMSMPara, ST_SPEED_CONTROL* pSpeed, ST_MTPA_CONTROL* pMTPA);
void WEAK_Init(ST_WEAK_CONTROL* pWEAK);
void WEAK_Control(ST_FOC_PARAMETER* pFocPara, ST_SPEED_CONTROL* pSpeed, ST_MTPA_CONTROL* pMTPA, ST_WEAK_CONTROL* pWEAK);

void Est_IF_Init(ST_IF_CONTROL* pCTRL);
void Est_IF(ST_IF_CONTROL* pCTRL, float Est_AngleRad);

void Est_Flux_Init(ST_FLUX_CONTROL* pCTRL);
void Est_Flux(ST_PMSM_PARAMETER* pPMSMPara, ST_FOC_PARAMETER* pFocPara, ST_CURRENT_CONTROL* pCurrentCtrl, ST_FLUX_CONTROL* pCTRL);

void Est_SVC_Init(ST_SVC_CONTROL* pCTRL);
void Est_SVC(ST_PMSM_PARAMETER* pPMSMPara, ST_FOC_PARAMETER* pFocPara, ST_CURRENT_CONTROL* pCurrentCtrl, ST_SVC_CONTROL* pCTRL);

void Est_SMO_Init(ST_SMO_CONTROL* pCTRL);
void Est_SMO(ST_PMSM_PARAMETER* pPMSMPara, ST_FOC_PARAMETER* pFocPara, ST_CURRENT_CONTROL* pCurrentCtrl, ST_SMO_CONTROL* pCTRL);

void Hallest_Init(ST_HALL_CONTROL* pHall);
void Hallest_Low_Speed(ST_HALL_CONTROL* pHall);
void Hallest_High_Speed(ST_HALL_CONTROL* pHall);
void Hallest_Angle_Inc(ST_HALL_CONTROL* pHall, uint32_t cnt);

/** @}end of group PMSM */

/** @}end of group Z20K14XM_Foc */

#endif /* MotorState_H */
