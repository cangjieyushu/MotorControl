/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#include "Error.h"

ST_ERROR_CONTROL Error_Ctrl = {
    .error_led_table[0] = 0,
    .error_led_table[1] = 0,
    .error_led_table[2] = 0,
    .error_led_table[3] = 0,
    .error_led_table[4] = 0,
    .error_led_table[5] = 0,
    .error_led_table[6] = 0,
    .error_led_table[7] = 0,
    .error_led_table[8] = 0,
    .error_led_table[9] = 0,
    .error_led_table[10] = 0,
    .error_led_table[11] = 0,
    .error_led_table[12] = 0,
    .error_led_table[13] = 0,
    .error_led_table[14] = 0,
    .error_led_table[15] = 0,
    .error_led_table[16] = 0,
    .error_led_table[17] = 0,
    .error_led_table[18] = 0,
    .error_led_table[19] = 0,
    .error_led_table[20] = 0,
    .error_led_table[21] = 0,
    .error_led_table[22] = 0,
    .error_led_table[23] = 0,
    .error_led_table[24] = 0,
    .error_led_table[25] = 0,
    .error_led_table[26] = 0,
    .error_led_table[27] = 0,
    .error_led_table[28] = 0,
    .error_led_table[29] = 0,
    .error_led_table[30] = 0,
    .error_led_table[31] = 0,
};

void Error_LED(ST_ERROR_CONTROL* pEC)
{
    if(pEC->error_code != 0U)
    {
        switch(pEC->error_led_flow)
        {
            case ERROR_LED_INIT:
            {
                pEC->error_code_led_1 = pEC->error_led_table[pEC->error_code]/10;
                pEC->error_code_led_2 = pEC->error_led_table[pEC->error_code]%10;
                pEC->error_led_flow = ERROR_LED_WAIT;
            }break;
            case ERROR_LED_BEGIN:
            {
                if(++pEC->error_led_flow > pEC->error_led_on_time)
                {
                    pEC->error_led_flow = ERROR_LED_WAIT;
                }
            }break;
            case ERROR_LED_WAIT:
            {
                if(++pEC->error_led_flow > pEC->error_led_off_time_1)
                {
                    pEC->error_led_flow = ERROR_LED_LIGHT;
                }
            }break;
            case ERROR_LED_LIGHT:
            {
                if(++pEC->error_led_flow > pEC->error_led_on_time)
                {
                    pEC->error_led_flow = ERROR_LED_END;
                }
            }break;
            case ERROR_LED_END:
            {
                if(++pEC->error_led_flow > pEC->error_led_off_time_2)
                {
                    pEC->error_led_flow = ERROR_LED_INIT;
                }
            }break;
            default:break;
        }
    }
    else
    {
        pEC->error_led_flow = ERROR_LED_INIT;
        pEC->led_cnt = 0U;
    }
}

void Error_Priority_Check(ST_SYSTEM_TASK*  pST)
{
    ST_ERROR_CONTROL* pEC = &Error_Ctrl;
    if(pST->System_Error_Flag.ALL != 0U)
    {
        for(Q32I_ i=0;i<32;i++)
        {
            if(pST->System_Error_Flag.ALL & (1<<i))
            {
                pEC->error_code = i + 1U;
                break;
            }
        }
    }
    else
    {
        pEC->error_code = 0U;
    }
    
    Error_LED(pEC);
}
