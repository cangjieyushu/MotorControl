/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#include "Speed.h"

ST_SPEED_PROTECT Speed_Protect_Over = {
    .Q16I_speed_protect_tl = OVER_SPEED_PROTECT_LEVEL_TL,
    .Q16U_speed_protect_time = OVER_SPEED_PROTECT_LEVEL_TIME,
};

ST_SPEED_PROTECT Speed_Protect_Low = {
    .Q16I_speed_protect_tl = LOW_SPEED_PROTECT_LEVEL_TL,
    .Q16U_speed_protect_time = LOW_SPEED_PROTECT_LEVEL_TIME,
};

void Speed_Protect_Flow(ST_SYSTEM_TASK*  pST)
{
    ST_SPEED_PROTECT* pCVO = &Speed_Protect_Over;
    ST_SPEED_PROTECT* pCVL = &Speed_Protect_Low;
    
    pST->Q16U_Motor_Freq = Motor_Read_Freq();
    
    if(pST->System_Flow != SYSTEM_STATE_POWERUP)
    {
        if(pST->System_Error_Flag.BIT.over_speed_error == 0U)
        {
            if(pST->Q16U_Motor_Freq >= pCVO->Q16I_speed_protect_tl)
            {
                if(++pCVO->Q16U_speed_protect_cnt >= pCVO->Q16U_speed_protect_time)
                {
                    pCVO->Q16U_speed_protect_cnt = 0;
//                    pST->System_Error_Flag.BIT.over_speed_error = 1U;
                }
            }
            else
            {
                pCVO->Q16U_speed_protect_cnt = 0;
            }
        }
        else
        {
            pCVO->Q16U_speed_protect_cnt = 0;
        }
        
        if(pST->System_Error_Flag.BIT.low_speed_error == 0U)
        {
            if(pST->Q16U_Motor_Freq <= pCVL->Q16I_speed_protect_tl)
            {
                if(++pCVL->Q16U_speed_protect_cnt >= pCVL->Q16U_speed_protect_time)
                {
                    pCVL->Q16U_speed_protect_cnt = 0;
//                    pST->System_Error_Flag.BIT.low_speed_error = 1U;
                }
            }
            else
            {
                pCVL->Q16U_speed_protect_cnt = 0;
            }
        }
        else
        {
            pCVL->Q16U_speed_protect_cnt = 0;
        }
    }
    else
    {
        pCVO->Q16U_speed_protect_cnt = 0;
        pCVL->Q16U_speed_protect_cnt = 0;
    }
}
