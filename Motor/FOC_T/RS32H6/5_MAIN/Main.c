/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#include "Main.h"

#if(JSCOPE_RTT_EN == 1U)
int32_t Buffer[128];
int32_t RTT_DATA[8];
//        Delay_us(1);
//    GPIO_Toggle_Pin(LED0_GPIO_PORT, LED0_PIN);
//    GPIO_Toggle_Pin(LED0_GPIO_PORT, LED0_PIN);

//    GPIO_Toggle_Pin(LED1_GPIO_PORT, LED1_PIN);
//    GPIO_Toggle_Pin(LED1_GPIO_PORT, LED1_PIN);
#endif

void System_Task_Tick(ST_SYSTEM_TASK* pST)
{
    if(pST->System_State_Flag.BIT.systick_intflow == 1U)
    {
        //1ms
        pST->systick_count++;
        
        System_Task_Flow(&Systask);
        MotorTask_Speed_Flow(&Motor);
        
        if((pST->systick_count & BIT0) == BIT0)  //2ms
        {
            
        }
        else  if((pST->systick_count & BIT1) == BIT1)  //4ms
        {
//            USART_Get_Resceive_Data_1();
//            USART_Get_Resceive_Data_2();
        }
        else if((pST->systick_count & BIT2) == BIT2)  //8ms
        {
//            USART_Send_Transmission_Data_1();
//            USART_Send_Transmission_Data_2();
        }
        else if((pST->systick_count & BIT3) == BIT3)  //16ms
        {
            
        }
        else if((pST->systick_count & BIT4) == BIT4)  //32ms
        {
            Voltage_Protect_Flow(&Systask);
        }
        else if((pST->systick_count & BIT5) == BIT5)  //64ms
        {
            Current_Protect_Flow(&Systask);
        }
        else if((pST->systick_count & BIT6) == BIT6)  //128ms
        {
            Speed_Protect_Flow(&Systask);
        }
        else if((pST->systick_count & BIT7) == BIT7)  //256ms
        {
            Temperature_Protect_Flow(&Systask);
            Error_Priority_Check(&Systask);
        }
        else  //256ms
        {
            IWDG_Reload_Counter(IWDG);
        }
        pST->System_State_Flag.BIT.systick_intflow = 0U;
    }
}

int main(void)
{
    __disable_irq();
    
    BSP_CLK_Init();
    BSP_GPIO_Init();
    BSP_ADC_Init();
    BSP_PWM_Init();
    BSP_OPA_Init();
    BSP_CMP_Init();
    BSP_TIM_Init();
    BSP_ISR_Init();
//    BSP_USART_Init();
    BSP_WDG_Init();
    
#if(JSCOPE_RTT_EN == 1U)
    SEGGER_RTT_ConfigUpBuffer(1,JSCOPE_RTT_Sytle,Buffer,128,SEGGER_RTT_MODE_NO_BLOCK_SKIP);
#endif
    
    __enable_irq();
    
    for(;;)
    {
        System_Task_Tick(&Systask);
    }
}

void ADC_IRQHandler(void)
{
    if(ADC_Get_SR(HAL_MOTOR_ADC, ADC_SR_JEOC))
    {
        ADC_Clear_SR(HAL_MOTOR_ADC, ADC_SR_JEOC);
        MotorTask_Current_Flow(&Motor);
    }
}

void TIM8_BRK_UP_TRG_COM_IRQHandler(void)
{
    if(TIM_Get_Flag(HAL_MOTOR_PWM, TIM_SR_BIF))
    {
        TIM_Clear_Flag(HAL_MOTOR_PWM, TIM_SR_BIF);
        MotorTask_Shut_Down_Flow(&Motor);
    }
    else if(TIM_Get_Flag(HAL_MOTOR_PWM, TIM_SR_UIF))
    {
        GPIO_Toggle_Pin(LED1_GPIO_PORT, LED1_PIN);
        TIM_Clear_Flag(HAL_MOTOR_PWM, TIM_SR_UIF);
        MotorTask_Update_Flow(&Motor);
        GPIO_Toggle_Pin(LED1_GPIO_PORT, LED1_PIN);
#if(JSCOPE_RTT_EN == 1U)
//        RTT_DATA[0] = Motor.FOC_Para.Q14I_Ia;
//        RTT_DATA[1] = Motor.FOC_Para.Q14I_Ib;
//        RTT_DATA[2] = Motor.FOC_Para.Q14I_Ic;
        
//        RTT_DATA[0] = Motor.SMO_Ctrl.Angle.Q12U_Angle;
//        RTT_DATA[1] = Motor.FLUX_Ctrl.Angle.Q12U_Angle;
//        RTT_DATA[2] = Motor.FOC_Para.Angle.Q12U_Angle;
        
        RTT_DATA[0] = Motor.SMO_Ctrl.FL_SRAD.Q16I_Filter_out;
        RTT_DATA[1] = Motor.FLUX_Ctrl.FL_SRAD.Q16I_Filter_out;
        RTT_DATA[2] = Motor.IF_Ctrl.SRad_Ramp.Q32I_Output;

        SEGGER_RTT_Write(1,&RTT_DATA,12);
#endif
    }
}

void SysTick_Handler(void)
{
    System_Tick_Isr(&Systask);
}

void UART1_IRQHandler(void)
{
	if(UART_Get_Flag(UART1, UART_FLAG_RXNE)==1)
	{		
		UART_Clear_Flag(UART1, UART_FLAG_RXNE);
        USART_Resceive_Int_1();
	}
	else if(UART_Get_Flag(UART1, UART_FLAG_TXE)==1)
	{
		UART_Clear_Flag(UART1, UART_IT_TCIE);
        USART_Transmission_Int_1();
    }
}

void UART2_IRQHandler()
{
	if(UART_Get_Flag(UART2, UART_FLAG_RXNE)==1)
	{		
		UART_Clear_Flag(UART2, UART_FLAG_RXNE);
        USART_Resceive_Int_2();
	}
	else if(UART_Get_Flag(UART2, UART_IT_TCIE)==1)
	{
		UART_Clear_Flag(UART2, UART_IT_TCIE);
        USART_Transmission_Int_2();
    }
}
