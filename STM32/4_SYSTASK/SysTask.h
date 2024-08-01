/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef SysTask_H
#define SysTask_H

#include <stdint.h>
#include "MotorPara.h"
#include "MotorTask.h"

typedef enum{
    SYSTEM_STATE_POWERUP,
    SYSTEM_STATE_IDLE,
    SYSTEM_STATE_BOOT,
    SYSTEM_STATE_RUN,
    SYSTEM_STATE_ERROR,
}EM_SYSTEM_STATE_FLOW;

typedef union{
    uint32_t ALL;
    struct{
        uint32_t        systick_intflow:1;
    }BIT;
}UN_SYSTEM_STATE_FLAG;

typedef union{
    uint32_t ALL;
    struct{
        uint32_t systick_overflow				:1;
        uint32_t motor_1_error 					:1;
        uint32_t motor_2_error 					:1;
    }BIT;
}UN_SYSTEM_ERROR_FLAG;

typedef struct{
    uint8_t                     systick_count;
    EM_SYSTEM_STATE_FLOW        state_flow;
    UN_SYSTEM_STATE_FLAG        state_flag;
    UN_SYSTEM_ERROR_FLAG        error_flag;
    
    uint32_t                    flow_cnt;
}ST_SYSTEM_TASK;

void System_Task_Flow(ST_SYSTEM_TASK*  pSystask);
void System_Tick_Isr(ST_SYSTEM_TASK*  pSystask);

extern ST_SYSTEM_TASK  Systask;

#endif /* SysTask_H */
