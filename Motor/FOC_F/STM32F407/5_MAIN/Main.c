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
float RTT_DATA[8];
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
            
        }
        else if((pST->systick_count & BIT1) == BIT1)  //4ms
        {
            
        }
        else if((pST->systick_count & BIT2) == BIT2)  //8ms
        {
            
        }
        else if((pST->systick_count & BIT3) == BIT3)  //16ms
        {
            
        }
        else if((pST->systick_count & BIT4) == BIT4)  //32ms
        {
            
        }
        else if((pST->systick_count & BIT5) == BIT5)  //64ms
        {
            
        }
        else if((pST->systick_count & BIT6) == BIT6)  //128ms
        {
            
        }
        else if((pST->systick_count & BIT7) == BIT7)  //256ms
        {
            
        }
        else  //256ms
        {
            
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
        System_Task_Tick(&Systask);
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
Ram_Func void ADC_IRQHandler(void)
{
    if(ADC_GetFlagStatus(ADC1, ADC_FLAG_JEOC))
    {
        ADC_ClearFlag(ADC1, ADC_FLAG_JEOC);
        MH_Read_ADC_Data(&Adc_Data);
        
        Motor.SVPWM_CTRL._I_F_Ia_Data = Adc_Data.Ia;
        Motor.SVPWM_CTRL._I_F_Ib_Data = Adc_Data.Ib;
        Motor.SVPWM_CTRL._I_F_Ic_Data = Adc_Data.Ic;
        Motor.SVPWM_CTRL._I_F_Ia = HAL_ADC_CURRENT_SCALE*(Motor.SVPWM_CTRL._I_F_Ia_Offset - Motor.SVPWM_CTRL._I_F_Ia_Data);
        Motor.SVPWM_CTRL._I_F_Ib = HAL_ADC_CURRENT_SCALE*(Motor.SVPWM_CTRL._I_F_Ib_Offset - Motor.SVPWM_CTRL._I_F_Ib_Data);
        Motor.SVPWM_CTRL._I_F_Ic = HAL_ADC_CURRENT_SCALE*(Motor.SVPWM_CTRL._I_F_Ic_Offset - Motor.SVPWM_CTRL._I_F_Ic_Data);
        
        MotorTask_Current_Flow(&Motor);
        
        if(Motor.Motor_State_Flag.bit.pwm_output_flag == 1)
        {
            MotorFoc_SVPWM_ThreeShunt_F(&Motor.SVPWM_CTRL);
            MH_PWM_Duty_Set_Three(Motor.SVPWM_CTRL._O_F_Ta, Motor.SVPWM_CTRL._O_F_Tb, Motor.SVPWM_CTRL._O_F_Tc);
            MH_PWM_Output_Enable();
        }
        else
        {
            MH_PWM_Output_Disable(); 
        }
	
#if(JSCOPE_RTT_EN == 1U)
        RTT_DATA[0] = 1000.0f*Motor.SVPWM_CTRL._I_F_Ia;
        RTT_DATA[1] = 1000.0f*Motor.SVPWM_CTRL._I_F_Ib;
        RTT_DATA[2] = 1000.0f*Motor.SVPWM_CTRL._I_F_Ic;
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
}

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
    MotorTask_SRAD_Flow(&Motor);
}
