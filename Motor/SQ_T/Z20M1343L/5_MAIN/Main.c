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
Function: System_Task_Tick
Description: 时间片任务调度
Input: 无
Output: 无
Input_Output: ST_SYSTEM_TASK
Return: 无
Author: CJYS
***********************************************************************************************/
void System_Task_Tick(ST_SYSTEM_TASK* pST)
{
    if(pST->System_State_Flag.BIT.systick_intflow == 1U)
    {
        //1ms
        pST->systick_count++;
        
        System_Task_Flow(&Systask);
        
        if((pST->systick_count & BIT0) == BIT0)  //2ms
        {
//            USART_Get_Resceive_Data_1();
//            USART_Get_Resceive_Data_2();
        }
        else if((pST->systick_count & BIT1) == BIT1)  //4ms
        {
//            USART_Send_Transmission_Data_1();
//            USART_Send_Transmission_Data_2();
        }
        else if((pST->systick_count & BIT2) == BIT2)  //8ms
        {
            
        }
        else if((pST->systick_count & BIT3) == BIT3)  //16ms
        {
            Voltage_Protect_Flow(&Systask);
        }
        else if((pST->systick_count & BIT4) == BIT4)  //32ms
        {
            Current_Protect_Flow(&Systask);
        }
        else if((pST->systick_count & BIT5) == BIT5)  //64ms
        {
            Speed_Protect_Flow(&Systask);
        }
        else if((pST->systick_count & BIT6) == BIT6)  //128ms
        {
            Error_Priority_Check(&Systask);
        }
        else if((pST->systick_count & BIT7) == BIT7)  //256ms
        {
            Temperature_Protect_Flow(&Systask);
        }
        else  //256ms
        {
//            IWDG_Reload_Counter(IWDG);
        }
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
    
//    BSP_CLK_Init();
//    BSP_GPIO_Init();
//    BSP_ADC_Init();
//    BSP_PWM_Init();
//    BSP_OPA_Init();
//    BSP_CMP_Init();
//    BSP_TIM_Init();
//    BSP_ISR_Init();
//    BSP_USART_Init();
//    BSP_WDG_Init();
    
#if(JSCOPE_RTT_EN == 1U)
    SEGGER_RTT_ConfigUpBuffer(1,JSCOPE_RTT_Sytle,Buffer,sizeof(Buffer),SEGGER_RTT_MODE_NO_BLOCK_SKIP);
#endif
    
    __enable_irq();
    
    for(;;)
    {
        System_Task_Tick(&Systask);
    }
}

/**********************************************************************************************
Function: Adc_LoopScomp_IrqHandler
Description: 电流环中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Adc_LoopScomp_IrqHandler(void)
{
//    if(ADC_Get_SR(HAL_MOTOR_ADC, ADC_SR_JEOC))
//    {
//        ADC_Clear_SR(HAL_MOTOR_ADC, ADC_SR_JEOC);
        MotorTask_Current_Flow(&Motor);
#if(JSCOPE_RTT_EN == 1U)
        RTT_DATA[0] = 100;
        RTT_DATA[1] = 100;
        RTT_DATA[2] = 100;
        SEGGER_RTT_Write(1,&RTT_DATA,12);
#endif
//    }
}

/**********************************************************************************************
Function: Stim_IrqHandler
Description: 换向中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Stim_IrqHandler(void)
{
//    if(TIM_Get_Flag(HAL_MOTOR_SWITCH_TIM, TIM_SR_UIF))
//    {
//        TIM_Clear_Flag(HAL_MOTOR_SWITCH_TIM, TIM_SR_UIF);
        MotorTask_Switch_Flow(&Motor);
//    }
}

/**********************************************************************************************
Function: Mcpwm_IrqHandler
Description: 刹车故障中断，首次硬件触发ADC中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Mcpwm_IrqHandler(void)
{
//    if(TIM_Get_Flag(HAL_MOTOR_PWM, TIM_SR_BIF))
//    {
//        TIM_Clear_Flag(HAL_MOTOR_PWM, TIM_SR_BIF);
        MotorTask_Shut_Flow(&Motor);
//    }
//    if(TIM_Get_Flag(HAL_MOTOR_PWM, TIM_SR_CC4IF))
//    {
//        TIM_Clear_Flag(HAL_MOTOR_PWM, TIM_SR_CC4IF);
        MotorTask_PWM_Start_ADC_Flow(&Motor);
//    }
}

/**********************************************************************************************
Function: Ctimer_IrqHandler
Description: 速度环中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Ctimer_IrqHandler(void)
{
    System_Tick_Isr(&Systask);
    MotorTask_Freq_Flow(&Motor);
}


