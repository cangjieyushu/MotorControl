/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#include "SysTask.h"

ST_SYSTEM_TASK  Systask;
uint8_t START = 0U;

void System_Task_Flow(ST_SYSTEM_TASK*  pSystask)
{
    if(Motor.error_flag.ALL != 0U)
    {
        pSystask->error_flag.BIT.motor_1_error = 1U;
    }
    
    switch(pSystask->state_flow)
    {
    case SYSTEM_STATE_POWERUP:
        {
            if(pSystask->error_flag.ALL != 0U)
            {
                pSystask->state_flow = SYSTEM_STATE_ERROR;
            }
            else
            {
                if(++pSystask->flow_cnt >= 1000U)
                {
                    pSystask->flow_cnt = 0U;
                    pSystask->state_flow = SYSTEM_STATE_IDLE;
                }
            }
        }break;
    case SYSTEM_STATE_IDLE:
        {
            if(pSystask->error_flag.ALL != 0U)
            {
                pSystask->state_flow = SYSTEM_STATE_ERROR;
            }
            else
            {
                if(START == 1U)
                {
                    START = 0U;
                    pSystask->state_flow = SYSTEM_STATE_BOOT;
                }
            }
            break;
        }
    case SYSTEM_STATE_BOOT:
        {
            if(pSystask->error_flag.ALL != 0U)
            {
                pSystask->state_flow = SYSTEM_STATE_ERROR;
            }
            else
            {
                pSystask->state_flow = SYSTEM_STATE_RUN;
            }break;
        }
    case SYSTEM_STATE_RUN:
        {
            if(pSystask->error_flag.ALL != 0U)
            {
                pSystask->state_flow = SYSTEM_STATE_ERROR;
            }
            else
            {
                if(START == 2U)
                {
                    START = 0U;
                    pSystask->state_flow = SYSTEM_STATE_IDLE;
                }
            }break;
        }
    case SYSTEM_STATE_ERROR:
        {
            if(START == 3U)
            {
                START = 0U;
                pSystask->error_flag.ALL = 0U;
                Motor.error_flag.ALL = 0U;
                pSystask->state_flow = SYSTEM_STATE_IDLE;
            }break;
        }
    default:break;
    }
}

void System_Tick_Isr(ST_SYSTEM_TASK*  pSystask)
{
    if(pSystask->state_flag.BIT.systick_intflow == 0U)
    {
        pSystask->state_flag.BIT.systick_intflow = 1U;
    }
    else
    {
        pSystask->error_flag.BIT.systick_overflow = 1U;
    }
}
