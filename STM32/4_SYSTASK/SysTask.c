/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#include "SysTask.h"

ST_SYSTEM_TASK  Systask;

void System_Task_Flow(ST_SYSTEM_TASK*  pSystask)
{
    switch(pSystask->state_flow)
    {
    case SYSTEM_STATE_POWERUP:
        {
            break;
        }
    case SYSTEM_STATE_IDLE:
        {
            break;
        }
    case SYSTEM_STATE_BOOT:
        {
            break;
        }
    case SYSTEM_STATE_RUN:
        {
            break;
        }
    case SYSTEM_STATE_ERROR:
        {
            break;
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
