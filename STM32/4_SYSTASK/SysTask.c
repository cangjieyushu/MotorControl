/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#include "SysTask.h"

ST_SYSTEM_TASK  Systask;
uint8_t START = 0U;

void KEY_KEIL(void)
{
    uint8_t tmp1 = GPIO_ReadInputDataBit(KEY0_GPIO_PORT, KEY0_Pin);
    uint8_t tmp2 = GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_Pin);
    uint8_t tmp3 = GPIO_ReadInputDataBit(KEY2_GPIO_PORT, KEY2_Pin);
    static uint8_t last_tmp1 = 0U;
    static uint8_t last_tmp2 = 0U;
    static uint8_t last_tmp3 = 0U;
    
    if((tmp1 == 1U) && (last_tmp1 == 0U))
    {
        START = 1U;
    }
    if((tmp2 == 1U) && (last_tmp2 == 0U))
    {
        START = 2U;
    }
    if((tmp3 == 1U) && (last_tmp3 == 0U))
    {
        Motor.speed_ctrl.SpeedRef = -Motor.speed_ctrl.SpeedRef;
    }
    last_tmp1 = tmp1;
    last_tmp2 = tmp2;
    last_tmp3 = tmp3;
}

void System_Task_Flow(ST_SYSTEM_TASK*  pSystask)
{
    KEY_KEIL();
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
            if(START == 2U)
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
