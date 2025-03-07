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
        Button_Ctrl.Button0_State = BSP_GPIO_Read_SW0_State();
        Button_Ctrl.Button1_State = BSP_GPIO_Read_SW1_State();
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
//        IWDG_Reload_Counter(IWDG);
        
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
    Z20A8300A_Init();
    
    BSP_ADC_Init(IRQHandleADCIsr);
    BSP_PWM_Init(IRQHandleMCBKIsr, IRQHandleTIMCPIsr);
    BSP_TIM_Init(IRQHandleTIMSWIsr);
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
Function: IRQHandleADCIsr
Description: 电流环中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void IRQHandleADCIsr(void)
{
    GPIO_TogglePinOutput(HAL_HALLB_PORT, HAL_HALLB_PIN);
    MH_ADC_FIFO_Read();
    MotorTask_Current_Flow(&Motor);
    ADC_IntClear(HAL_MOTOR_ADC, ADC_FWM_INT);
    
#if(JSCOPE_RTT_EN == 1U)
    RTT_DATA[0] = 100;
    RTT_DATA[1] = 100;
    RTT_DATA[2] = 100;
    SEGGER_RTT_Write(1,&RTT_DATA,12);
#endif
}

/**********************************************************************************************
Function: IRQHandleTIMSWIsr
Description: 换向中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void IRQHandleTIMSWIsr(void)
{
    MotorTask_Switch_Flow(&Motor);
    STIM_ClearInt(STIM_0);
}

/**********************************************************************************************
Function: IRQHandleTIMCPIsr
Description: 首次硬件触发ADC中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void IRQHandleTIMCPIsr(void)
{
    GPIO_TogglePinOutput(HAL_HALLA_PORT, HAL_HALLA_PIN);
    MotorTask_PWM_Start_ADC_Flow(&Motor);
    TIM_IntClear(HAL_MOTOR_PWM, TIM_INT_CH3);
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
void IRQHandleMCBKIsr(void)
{
    MotorTask_Shut_Flow(&Motor);
    TIM_IntClear(HAL_MOTOR_PWM, TIM_INT_FAULT);
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


