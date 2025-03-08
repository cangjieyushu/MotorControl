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
    BSP_PWM_Init(IRQHandleMCBKIsr);
    BSP_TMU_Init();
    BSP_ISR_Init();
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
    
    MCU_Z20A8300A_SpiInit();
    MCU_Z20A8300A_GpioInit();
    
    Z20A8300AIf.SpiSendCallBack = MCU_SPI_SendToZ20A8300A;
    Z20A8300AIf.SpiReceiveCallBack = MCU_SPI_ReceiveFromZ20A8300A;
    Z20A8300AIf.SpiWaitingForReceptionCallBack = MCU_SPI_WaitingForReceptionFromZ20A8300A;
    if(Z20A8300A_ERR_OK == Z20A8300A_Diag_ReadClearDiag(&Z20A8300AIf, &Z20A8300AStatus, &Z20A8300ADiag))
    {
        if(Z20A8300ADiag.WORD != 0U)
        {
            Motor.Motor_Error_Flag.bit.current_short = 1U;
        }
    }
	
    MH_PWMFault_IntFlag_Clear();
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


