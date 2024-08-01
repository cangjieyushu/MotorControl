/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef MotorTask_H
#define MotorTask_H

#include <stdint.h>
#include "Math.h"
#include "MotorFoc.h"
#include "MotorHal.h"

typedef enum
{
    EM_MOTOR_SPEED_MODE_CLOSELOOP1,
    EM_MOTOR_SPEED_MODE_CLOSELOOP2,
    EM_MOTOR_SPEED_MODE_CLOSELOOP3,
}EM_MOTOR_SPEED_MODE;

typedef enum{
    MOTOR_STATE_IDLE,
    MOTOR_STATE_BOOT,
    MOTOR_STATE_POSITION,
    MOTOR_STATE_RUN,
    MOTOR_STATE_BRAKE,
}EM_MOTOR_STATE_FLOW;

typedef union{
    uint32_t ALL;
    struct{
        uint32_t                motor_run               :1;//电机运行使能位
        uint32_t                PWM_output_en           :1;//电机PWM脉冲输出使能位
    }BIT;
}UN_MOTOR_STATE_FLAG;

typedef union{
    uint32_t ALL;
    struct{
        uint32_t                PDInitFaultB0           :1;//预驱初始化故障            0
        uint32_t                PDRunFaultB1            :1;//预驱运行故障              1
        uint32_t                OverCurrentFaultB2      :1;//过流故障                  2
        uint32_t                StallFaultB3            :1;//堵转故障                  3
        uint32_t                OverSpeedFaultB4        :1;//失速故障                  4
        uint32_t                HallFaultB5             :1;//霍尔故障                  5
        
        uint32_t                OpenPhaseFaultB6        :1;//开路故障                  6
        uint32_t                CurrentLossCtrlFaultB7  :1;//电流失控故障              7
        uint32_t                CurrentSampleFaultB8    :1;//电流采样故障              8
        uint32_t                MOSFaultB9              :1;//MOS故障                   9
    }BIT;
}UN_MOTOR_ERROR_FLAG;

typedef struct{
    EM_MOTOR_STATE_FLOW         state_flow;
    EM_MOTOR_SPEED_MODE         speed_mode;
    UN_MOTOR_STATE_FLAG         state_flag;
    UN_MOTOR_ERROR_FLAG         error_flag;
    
    ST_MTPA_CONTROL             mtpa_ctrl;
    ST_WEAK_CONTROL             weak_ctrl;
    ST_TC_CONTROL               tc_ctrl;
    ST_FOC_CONTROL              foc_ctrl;
    ST_BRAKE_CONTROL            brake_ctrl;
    
    ST_IF_CONTROL               if_ctrl;
    ST_FLUX_CONTROL             flux_ctrl;
    ST_SMO_CONTROL              smo_ctrl;
    ST_HALL_CONTROL             hall_ctrl;
    
    uint32_t                    flow_cnt;
}ST_MOTOR_TASK;
    
void Motor_Task_Flow(ST_MOTOR_TASK* pMotor);
void Hallest_Angle_Cal(ST_MOTOR_TASK* pMotor);
void Motor_Foc_Cal(ST_MOTOR_TASK* pMotor);

#endif /* MotorTask_H */
