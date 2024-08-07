/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#include "Main.h"

#if(JSCOPE_RTT_EN == 1U)
float Buffer[2048];
float RTT_DATA[8];
#endif

uint16_t tmp = 0;
void System_Task_Tick(ST_SYSTEM_TASK* pSystask)
{
    if(pSystask->state_flag.BIT.systick_intflow == 1U)
    {
        //500us
        pSystask->systick_count++;
        
        if((pSystask->systick_count & BIT0) == BIT0)  //1ms
        {
            if(Systask.state_flow == SYSTEM_STATE_RUN)
            {
                Motor.state_flag.BIT.motor_run = 1U;
            }
            else
            {
                Motor.state_flag.BIT.motor_run = 0U;
            }
            MotorTask_Speed_Flow(&Motor);
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
    __disable_irq();
    
    BSP_CLK_Init();
    BSP_GPIO_Init();
    BSP_ADC_Init();
    BSP_DAC_Init();
    BSP_DMA_Init();
    BSP_PWM_Init();
    BSP_ISR_Init();
    
    __enable_irq();
    
    for(;;)
    {
        System_Task_Tick(&Systask);
    }
}

void ADC_IRQHandler(void)
{
    ADC_ClearFlag(ADC1, ADC_FLAG_JEOC);
    
    MH_ADC_Data_Read(&Motor.foc_para.Ia_data, &Motor.foc_para.Ib_data, &Motor.foc_para.Ic_data, &Motor.foc_para.Vbat_data);
    
    if(Motor.state_flag.BIT.PWM_output_en == 1U)
    {
        if(Motor.state_flow == MOTOR_STATE_RUN)
        {
            MotorTask_Current_Flow(&Motor);
            MH_PWM_Duty_Set(Motor.current_ctrl.Ta, Motor.current_ctrl.Tb, Motor.current_ctrl.Tc);
        }
        else if(Motor.state_flow == MOTOR_STATE_BRAKE)
        {
            MH_PWM_Duty_Set(Motor.brake_ctrl.Ta_value, Motor.brake_ctrl.Tb_value, Motor.brake_ctrl.Tc_value);
        }
        else
        {
            MH_PWM_Duty_Disable();
        }
    }
    else
    {
        MH_PWM_Duty_Disable();
    }
}

void SysTick_Handler(void)
{
    System_Tick_Isr(&Systask);
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
    TIM_ClearFlag(TIM1, TIM_FLAG_Break);
    MH_PWM_Duty_Disable();
}

void TIM1_UP_TIM10_IRQHandler(void)
{
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
}
