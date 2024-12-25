/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef MotorFoc_H
#define MotorFoc_H

#include <stdint.h>
#include "Math.h"
#include "User_Pmsm.h"

typedef enum
{
    sector_1,
    sector_2,
    sector_3,
    sector_4,
    sector_5,
    sector_6,
}EM_SECTOR_NUM;

typedef union{
    ALL            all;
    struct{
        BIT        current_offset_Succ         :1;
        BIT        current_offset_Fail         :1;
        BIT        free_flying_Succ            :1;
        BIT        free_flying_Fail            :1;
        BIT        mos_check_Succ              :1;
        BIT        mos_check_Fail              :1;
        BIT        motor_standby_Succ          :1;
        BIT        motor_standby_Fail          :1;
        BIT        motor_position_Succ         :1;
        BIT        motor_position_Fail         :1;
    }bit;
}UN_MOTOR_FLAG;

typedef struct{
    EM_SECTOR_NUM       Sector;
    UN_MOTOR_FLAG       Motor_Flag;
    Q16U_               Q12U_Position_Current_VAL[6];
    
    Q16U_   Q16U_iphase_offset_max;
    Q16U_   Q16U_iphase_offset_min;
    Q08U_   Q08U_iphase_offset_num;
    
    Q16U_   Q16U_position_duty;
    Q16U_   Q16U_position_tl;
    
    Q32U_   Q32U_hall_tim_freq;
    Q16U_   sq_cnt;
}ST_COMMON_CONTROL;
typedef struct
{
    ST_TRIG Angle;
    
    Q08U_ Q08U_Sector;
    Q32I_ Q14I_TargetDir; 
    Q32I_ Q14I_Ia;    
    Q32I_ Q14I_Ib;    
    Q32I_ Q14I_Ic;    
    Q32I_ Q14I_Ialfa;
    Q32I_ Q14I_Ibeta; 
    Q32I_ Q14I_Id;    
    Q32I_ Q14I_Iq;    
    
    Q32I_ Q14I_Ualfa;      
    Q32I_ Q14I_Ubeta;
    Q32I_ Q14I_Ud;      
    Q32I_ Q14I_Uq;    
    
    Q32I_ Q14I_Vbus;
    Q32I_ Q14I_Vs;
    
    Q32I_ Q12I_I_Data[4]; 
    Q32I_ Q12I_X_Data[4]; 
    Q32I_ Q12I_I_Data_tmp; 
    Q32I_ Q12I_I_Offset;
    
    Q32I_ Q14I_VsCoeff;
    Q32I_ Q12I_ADC_Time; 
    Q32I_ Q12I_VTime_1;
    Q32I_ Q12I_VTime_2;
    Q32I_ Q12I_MaxScale; 
    Q32I_ Q12I_MaxDuty; 
    
    Q32I_ Q14I_IPHASE_MAX;
}ST_FOC_PARAMETER;

typedef struct
{
    float MC_HT;
    float MC_LT;
    float MC_U;
    float MC_I;
    float MC_F;
    float MC_W;
    float MC_R;
    float MC_L;
    float MC_P;
    float MC_T;
        
    Q32I_ Q14I_Motor_HTs; 
    Q32I_ Q14I_Motor_LTs; 
    
    Q32I_ Q14I_Rs;
    Q32I_ Q14I_Ls;
    Q32I_ Q14I_Ld;
    Q32I_ Q14I_Lq;
    Q32I_ Q14I_Flux;
    Q32I_ Q14I_Flux_2;
    
    Q32I_ Q10I_One_Over_Ld;
    Q32I_ Q14I_Rs_Over_Ld;
    Q32I_ Q14I_Ld_Lq_Over_Ld;
    
}ST_PMSM_PARAMETER;

typedef struct
{
    Q32I_ Q14I_SRAD_Rf;
    Q32I_ Q14I_SRAD_Fb;   
    Q32I_ Q14I_IdRef;
    Q32I_ Q14I_IqRef;

    ST_PID_POS PidSpd;    
    ST_RAMP Id_Ramp;  
    ST_RAMP Iq_Ramp;  
    ST_RAMP SRad_Ramp;    

    Q32I_ SRAD_Max;
    Q32I_ SRAD_Min;
    
    Q32I_ SpeedChange0;
    Q32I_ SpeedChangeTime_Num0;
    Q32I_ SpeedChange1;
    Q32I_ SpeedChangeTime_Num1;
    Q32I_ SpeedChange2;
    Q32I_ SpeedChangeTime_Num2;
    Q32I_ SpeedChange3;
    Q32I_ SpeedChangeTime_Num3;
    
    Q32I_ SpeedTarget;
    Q32I_ SpeedStep1;
    Q32I_ SpeedStep2;
    Q32I_ SpeedStep3;
}ST_SRAD_CONTROL;

typedef struct
{
    Q32I_ Q14I_IdRef;   
    Q32I_ Q14I_IqRef;    
    
    ST_PID_POS PidId;
    ST_PID_POS PidIq;
    
    Q32I_ Q12I_TaUp;    
    Q32I_ Q12I_TbUp;     
    Q32I_ Q12I_TcUp;
    Q32I_ Q12I_TaDn;    
    Q32I_ Q12I_TbDn;     
    Q32I_ Q12I_TcDn;    
    Q32I_ Q12I_TADC_1;     
    Q32I_ Q12I_TADC_2;  
}ST_CURRENT_CONTROL;

typedef struct
{
    ST_PID_POS PidV;
    Q32I_ Q12I_Theta;
    Q32I_ Q14I_IdRef;
    Q32I_ Q14I_IqRef;
}ST_WEAK_CONTROL;

typedef struct
{
    ST_TRIG Angle;
    ST_RAMP SRad_Ramp;
    ST_RAMP AngleError_Ramp;
    Q32I_ Q28I_Angle_tmp;
    
    Q32U_ AngleRad_cnt;
    Q08U_ IF_Success_Flag;
    
    Q32I_ Est_AngleRad;
    
    Q32I_ AngleRad_Error;
    Q32U_ AngleRad_time;
}ST_IF_CONTROL;

typedef struct
{
    ST_TRIG Angle;
    ST_FILTER FL_SRAD;
    Q32I_ Q28I_Angle_tmp;

    Q32I_ Q28I_Ref_Yalfa;
    Q32I_ Q28I_Ref_Ybeta;
    
    Q32I_ Q14I_Nn_alfa;
    Q32I_ Q14I_Nn_beta;
    Q32I_ Q14I_Nn_2;
    
    Q32I_ Q28I_Xalfa_addtmp;
    Q32I_ Q28I_Xbeta_addtmp;
    
    Q32I_ Q28I_Est_Xalfatmp1;
    Q32I_ Q28I_Est_Xbetatmp1;
    Q32I_ Q28I_Est_Xalfatmp2;
    Q32I_ Q28I_Est_Xbetatmp2;
    Q32I_ Q14I_Est_Xalfa;
    Q32I_ Q14I_Est_Xbeta;
    
    Q32I_ Q14I_Ks;
    Q32I_ Q14I_Gamma;
    ST_PID_POS PLL_PID;
}ST_FLUX_CONTROL;

typedef struct
{
    ST_TRIG Angle;
    ST_FILTER FL_SRAD;
    Q32I_ Q28I_Angle_tmp;

    Q32I_ Q28I_Est_Ialfa_tmp;
    Q32I_ Q28I_Est_Ibeta_tmp;
    Q32I_ Q14I_Est_Ialfa;
    Q32I_ Q14I_Est_Ibeta;
    Q32I_ Q14I_Est_Ealfa;
    Q32I_ Q14I_Est_Ebeta;  
    
    Q32I_ Q14I_K1;
    Q32I_ Q14I_K2;
    ST_PID_POS PLL_PID;
}ST_SMO_CONTROL;

void Motor_Current_Offset_Check(ST_COMMON_CONTROL* pCOM, ST_FOC_PARAMETER* pFocPara);
void Six_Pluse_Positon(ST_COMMON_CONTROL* pCOM);

void MotorFoc_Clark(ST_FOC_PARAMETER* pFocPara);
void MotorFoc_Park(ST_FOC_PARAMETER* pFocPara);
void MotorFoc_Ipark(ST_FOC_PARAMETER* pFocPara);
void MotorFoc_Simple_Cal(ST_FOC_PARAMETER* pFocPara);
void MotorFoc_SVPWM(ST_FOC_PARAMETER* pFocPara, ST_CURRENT_CONTROL* pCurrentCtrl);

void MotorFoc_WEAK_Init(ST_WEAK_CONTROL* pWEAK);
void MotorFoc_WEAK_Control(ST_FOC_PARAMETER* pFocPara, ST_SRAD_CONTROL* pSpeed, ST_WEAK_CONTROL* pWEAK);

void MotorFoc_IF_Init(ST_IF_CONTROL* pCTRL);
void MotorFoc_IF_Control(ST_PMSM_PARAMETER* pPMSMPara, ST_IF_CONTROL* pCTRL);

void MotorFoc_Flux_Init(ST_FLUX_CONTROL* pCTRL);
void MotorFoc_Flux_Control(ST_PMSM_PARAMETER* pPMSMPara, ST_FOC_PARAMETER* pFocPara, ST_FLUX_CONTROL* pCTRL);

void MotorFoc_SMO_Init(ST_SMO_CONTROL* pCTRL);
void MotorFoc_SMO_Control(ST_PMSM_PARAMETER* pPMSMPara, ST_FOC_PARAMETER* pFocPara, ST_SMO_CONTROL* pCTRL);

void MotorFoc_Speed_Init(ST_SRAD_CONTROL* pSpeed);
void MotorFoc_Speed_Loop(ST_SRAD_CONTROL* pSpeed);
void MotorFoc_Current_Init(ST_CURRENT_CONTROL* pCurrentCtrl);
void MotorFoc_Current_Loop(ST_FOC_PARAMETER* pFocPara, ST_CURRENT_CONTROL* pCurrentCtrl);
    
extern EM_SECTOR_NUM Position_CW[6][2];
    
#endif /* MotorFoc_H */
