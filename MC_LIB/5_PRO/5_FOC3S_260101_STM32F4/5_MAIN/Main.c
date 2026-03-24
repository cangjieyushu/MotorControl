/**************************************************************************************************
*     File Name :                        Main.c
*     Library/Module Name :              Main
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             任务管理
**************************************************************************************************/

#include "Main.h"


#if(JSCOPE_RTT_EN == 1U)
Q32I_ Buffer[128];
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
        
		BSP_FeedWatchDog();

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
    BSP_DMA_Init();
    BSP_ADC_Init();
    BSP_PWM_Init();
    BSP_TIM_Init();
    BSP_ISR_Init();

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
Function: IRQHandleDMAIsr
Description: 电流环中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void ADC_IRQHandler(void)
{
    if(ADC_GetFlagStatus(ADC1, ADC_FLAG_JEOC))
	{
        ADC_ClearFlag(ADC1, ADC_FLAG_JEOC);
        
        MotorTask_Current_Flow(&Motor);
	
#if(JSCOPE_RTT_EN == 1U)
    	RTT_DATA[0] = 0;
    	RTT_DATA[1] = 0;
    	RTT_DATA[2] = 0;
    	SEGGER_RTT_Write(1,&RTT_DATA,12U);
#endif
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
void TIM1_BRK_TIM9_IRQHandler(void)
{
    TIM_ClearFlag(TIM1, TIM_FLAG_Break);
    MH_PWM_Output_Disable();
	MotorTask_Shut_Flow(&Motor);
}

/**********************************************************************************************
Function: TIM2_IRQHandler
Description: HALL电平翻转中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void TIM2_IRQHandler(void)
{
    if(TIM_GetFlagStatus(TIM2, TIM_FLAG_Update))
    {
        TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    }
}

/**********************************************************************************************
Function: IRQHandleSTIMIsr
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
