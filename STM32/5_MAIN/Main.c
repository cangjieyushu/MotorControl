/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#include "Main.h"

#if(JSCOPE_RTT_EN == 1U)
float Buffer[2048];
float RTT_DATA[8];
#endif

void System_Task_Tick(ST_SYSTEM_TASK* pSystask)
{
    if(pSystask->state_flag.BIT.systick_intflow == 1U)
    {
        //500us
        pSystask->systick_count++;
        
        if((pSystask->systick_count & BIT0) == BIT0)  //1ms
        {
            Motor_Task_Flow(&Motor);
        }
        else  //1ms
        {
            if(Motor.error_flag.ALL != 0U)
            {
                Systask.error_flag.BIT.motor_1_error = 1U;
            }
            System_Task_Flow(&Systask);
            if((pSystask->systick_count & BIT1) == BIT1)  //2ms
            {
                
            }
            else if((pSystask->systick_count & BIT2) == BIT2)  //4ms
            {
                
            }
            else if((pSystask->systick_count & BIT3) == BIT3)  //8ms
            {
                
            }
            else if((pSystask->systick_count & BIT4) == BIT4)  //16ms
            {
                
            }
            else if((pSystask->systick_count & BIT5) == BIT5)  //32ms
            {
                
            }
            else if((pSystask->systick_count & BIT6) == BIT6)  //64ms
            {
                
            }
            else if((pSystask->systick_count & BIT7) == BIT7)  //128ms
            {
                
            }
            else  //128ms
            {
                
            }
        }
        pSystask->state_flag.BIT.systick_intflow = 0U;
    }
}

int main(void)
{
    for(;;)
    {
        System_Task_Tick(&Systask);
    }
}
