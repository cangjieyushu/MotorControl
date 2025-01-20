/**************************************************************************************************
*     File Name :                        Main.c
*     Library/Module Name :              Main
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             任务管理
**************************************************************************************************/
#include "Main.h"

#if(JSCOPE_RTT_EN == 1U)
char Buffer[128];
Q32I_ RTT_DATA[8];
#endif

/**********************************************************************************************
Function: System_10msTask_Tick
Description: 10ms时间片任务调度
Input: 无
Output: 无
Input_Output: ST_SYSTEM_TASK
Return: 无
Author: CJYS
***********************************************************************************************/
void System_10msTask_Tick(ST_SYSTEM_TASK* pST)
{
    if(pST->System_State_Flag.BIT.systick_intflow == 1U)
    {
        Button_Control(&Button_Ctrl, pST);
        
//        USART_Get_Resceive_Data_1();
//        USART_Get_Resceive_Data_2();
//        USART_Send_Transmission_Data_1();
//        USART_Send_Transmission_Data_2();
        
        Voltage_Protect_Flow(&Systask);
        Current_Protect_Flow(&Systask);
        Speed_Protect_Flow(&Systask);
        Temperature_Protect_Flow(&Systask);
        
        Error_Priority_Check(&Systask);
        IWDG_Reload_Counter(IWDG);
        
        pST->System_State_Flag.BIT.systick_intflow = 0U;
    }
}

/**********************************************************************************************
Function: main
Description: 主函数，执行初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
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
    SEGGER_RTT_ConfigUpBuffer(1,JSCOPE_RTT_Sytle,Buffer,sizeof(Buffer),SEGGER_RTT_MODE_NO_BLOCK_SKIP);
#endif
    
    __enable_irq();
    
    for(;;)
    {
        System_10msTask_Tick(&Systask);
    }
}

/**********************************************************************************************
Function: ADC_IRQHandler
Description: 电流环中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void ADC_IRQHandler(void)
{
    if(ADC_Get_SR(HAL_MOTOR_ADC, ADC_SR_JEOC))
    {
        ADC_Clear_SR(HAL_MOTOR_ADC, ADC_SR_JEOC);
        Q32I_ pwm_tmp1,pwm_tmp2,pwm_tmp3,adc_tmp1,adc_tmp2 = 0;
        
        MH_ADC_Data_Read_One(&Motor.SVPWM_CTRL._I_Q14I_Ishunt_1_Data, &Motor.SVPWM_CTRL._I_Q14I_Ishunt_2_Data);
        
        Motor.SVPWM_CTRL._I_Q14I_Ishunt[0] =  Q32I_RHT_10(Motor.SVPWM_CTRL._P_Q32I_Current_Scale
        *(Motor.SVPWM_CTRL._I_Q14I_Ishunt_1_Data - Motor.SVPWM_CTRL._I_Q14I_Ishunt_1_Offset));
        Motor.SVPWM_CTRL._I_Q14I_Ishunt[1] = -Q32I_RHT_10(Motor.SVPWM_CTRL._P_Q32I_Current_Scale
        *(Motor.SVPWM_CTRL._I_Q14I_Ishunt_2_Data - Motor.SVPWM_CTRL._I_Q14I_Ishunt_2_Offset));
        Motor.SVPWM_CTRL._I_Q14I_Ishunt[2] = -Motor.SVPWM_CTRL._I_Q14I_Ishunt[0] - Motor.SVPWM_CTRL._I_Q14I_Ishunt[1];
        MotorFoc_OneShunt_Cal_T(&Motor.SVPWM_CTRL);
        
        MotorTask_Current_Flow(&Motor);
        
        if(Motor.Motor_State_Flag.bit.pwm_output_flag == 1U)
        {
            MotorFoc_SVPWM_OneShunt_T(&Motor.SVPWM_CTRL);
            
            pwm_tmp1 = Q32I_RHT_12(Motor.SVPWM_CTRL._P_Q12I_PWM_All_Count*Motor.SVPWM_CTRL._O_Q12I_TaDn);
            pwm_tmp2 = Q32I_RHT_12(Motor.SVPWM_CTRL._P_Q12I_PWM_All_Count*Motor.SVPWM_CTRL._O_Q12I_TbDn);
            pwm_tmp3 = Q32I_RHT_12(Motor.SVPWM_CTRL._P_Q12I_PWM_All_Count*Motor.SVPWM_CTRL._O_Q12I_TcDn);
            adc_tmp1 = Q32I_RHT_12(Motor.SVPWM_CTRL._P_Q12I_PWM_All_Count*Motor.SVPWM_CTRL._O_Q12I_ADCTrigTime1);
            adc_tmp2 = Q32I_RHT_12(Motor.SVPWM_CTRL._P_Q12I_PWM_All_Count*Motor.SVPWM_CTRL._O_Q12I_ADCTrigTime2);
            
            MH_PWM_Duty_Set_One((Q32U_)pwm_tmp1,(Q32U_)pwm_tmp2,(Q32U_)pwm_tmp3);
            MH_ADC_TrigTime_Set((Q32U_)adc_tmp1,(Q32U_)adc_tmp2);
            MH_PWM_Output_Enable();
        }
        else
        {
            MH_PWM_Output_Disable(); 
        }
    }
}

/**********************************************************************************************
Function: IRQHandleMCBKIsr
Description: 刹车故障中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void TIM8_BRK_UP_TRG_COM_IRQHandler(void)
{
    if(TIM_Get_Flag(HAL_MOTOR_PWM, TIM_SR_BIF))
    {
        TIM_Clear_Flag(HAL_MOTOR_PWM, TIM_SR_BIF);
        MH_PWM_Output_Disable();
    }
    else if(TIM_Get_Flag(HAL_MOTOR_PWM, TIM_SR_UIF))
    {
        TIM_Clear_Flag(HAL_MOTOR_PWM, TIM_SR_UIF);
        Q32I_ pwm_tmp1,pwm_tmp2,pwm_tmp3 = 0;
        
        pwm_tmp1 = Q32I_RHT_12(Motor.SVPWM_CTRL._P_Q12I_PWM_All_Count*Motor.SVPWM_CTRL._O_Q12I_TaUp);
        pwm_tmp2 = Q32I_RHT_12(Motor.SVPWM_CTRL._P_Q12I_PWM_All_Count*Motor.SVPWM_CTRL._O_Q12I_TbUp);
        pwm_tmp3 = Q32I_RHT_12(Motor.SVPWM_CTRL._P_Q12I_PWM_All_Count*Motor.SVPWM_CTRL._O_Q12I_TcUp);
        MH_PWM_Duty_Set_One((Q32U_)pwm_tmp1,(Q32U_)pwm_tmp2,(Q32U_)pwm_tmp3);
		
#if(JSCOPE_RTT_EN == 1U)
        RTT_DATA[0] = Motor.SMO_Ctrl.FL_SRAD.Q16I_Filter_out;
        RTT_DATA[1] = Motor.FLUX_Ctrl.FL_SRAD.Q16I_Filter_out;
        RTT_DATA[2] = Motor.IF_Ctrl.SRad_Ramp.Q32I_Output;

        SEGGER_RTT_Write(1,&RTT_DATA,12);
#endif
    }
}

/**********************************************************************************************
Function: SysTick_Handler
Description: 速度环中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void SysTick_Handler(void)
{
    System_Tick_Isr(&Systask);
    System_Task_Flow(&Systask);
    MotorTask_Speed_Flow(&Motor);
}

/**********************************************************************************************
Function: UART1_IRQHandler
Description: 串口1收发中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
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

/**********************************************************************************************
Function: UART2_IRQHandler
Description: 串口2收发中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
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

