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
        TDG_SoftwareTrig(TDG1_ID);
        if((pST->systick_count & BIT0) == BIT0)  //2ms
        {
            
        }
        else if((pST->systick_count & BIT1) == BIT1)  //4ms
        {
            BSP_FeedWatchDog();
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
    COMMON_DISABLE_INTERRUPTS();
    
    BSP_CLK_Init();
    BSP_GPIO_Init();
    Z20A8300A_Init1();
    BSP_ADC_Init();
    BSP_DMA_Init(IRQHandleDMAIsr);
    BSP_ADC_Init_S();
    BSP_DMA_Init_S();
    BSP_PWM_Init(IRQHandleMCBKIsr);
    BSP_TMU_Init();
    BSP_TIM_Init(IRQHandleSTIMIsr);
    BSP_HALL_Init();
    BSP_ISR_Init();
    BSP_WDG_Init();
    
#if(JSCOPE_RTT_EN == 1U)
    SEGGER_RTT_ConfigUpBuffer(1,JSCOPE_RTT_Sytle,Buffer,128U,SEGGER_RTT_MODE_NO_BLOCK_SKIP);
#endif
    
    COMMON_ENABLE_INTERRUPTS();
    
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
Ram_Func void IRQHandleDMAIsr(void)
{
    MH_Read_ADC_Data(&Adc_Data);
    
#if(HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
    
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
        MH_PWM_Output_En(true);
    }
    else
    {
        MH_PWM_Output_En(false); 
    }
    
#else
    
    Motor.SVPWM_CTRL._I_F_Ishunt_1_Data = Adc_Data.Ishunt_1;
    Motor.SVPWM_CTRL._I_F_Ishunt_2_Data = Adc_Data.Ishunt_2;
    Motor.SVPWM_CTRL._I_F_Ishunt[0] = HAL_ADC_CURRENT_SCALE*(Motor.SVPWM_CTRL._I_F_Ishunt_1_Data - Motor.SVPWM_CTRL._I_F_Ishunt_1_Offset);
    Motor.SVPWM_CTRL._I_F_Ishunt[1] = - HAL_ADC_CURRENT_SCALE*(Motor.SVPWM_CTRL._I_F_Ishunt_2_Data - Motor.SVPWM_CTRL._I_F_Ishunt_2_Offset);
    Motor.SVPWM_CTRL._I_F_Ishunt[2] = - Motor.SVPWM_CTRL._I_F_Ishunt[0] - Motor.SVPWM_CTRL._I_F_Ishunt[1];
    MotorFoc_OneShunt_Cal_F(&Motor.SVPWM_CTRL);
    
    MotorTask_Current_Flow(&Motor);
    
    if(Motor.Motor_State_Flag.bit.pwm_output_flag == 1)
    {
        MotorFoc_SVPWM_OneShunt_F(&Motor.SVPWM_CTRL);
        MH_PWM_Duty_Set_One(Motor.SVPWM_CTRL._O_F_TaUp, Motor.SVPWM_CTRL._O_F_TaDn,
                            Motor.SVPWM_CTRL._O_F_TbUp, Motor.SVPWM_CTRL._O_F_TbDn,
                            Motor.SVPWM_CTRL._O_F_TcUp, Motor.SVPWM_CTRL._O_F_TcDn);
        MH_ADC_TrigTime_Set(Motor.SVPWM_CTRL._O_F_ADCTrigTime1,
                            Motor.SVPWM_CTRL._O_F_ADCTrigTime2);
        MH_PWM_Output_En(true);
    }
    else
    {
        MH_ADC_TrigTime_Set(HAL_ADC_TRIGGER_TIME1,
                            HAL_ADC_TRIGGER_TIME2);
        MH_PWM_Output_En(false); 
    }
#endif
    
#if(JSCOPE_RTT_EN == 1U)
    RTT_DATA[0] = 100.0f;
    RTT_DATA[1] = 100.0f;
    RTT_DATA[2] = 100.0f;
    SEGGER_RTT_Write(1,&RTT_DATA,12U);
#endif
    
    MH_DMA0_ClearChannel0Int();
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
    MH_PWM_Output_En(false);
    
    MCU_Z20A8300A_SpiInit1();
    MCU_Z20A8300A_GpioInit1();
    
    Z20A8300AIf1.SpiSendCallBack = MCU_SPI_SendToZ20A8300A1;
    Z20A8300AIf1.SpiReceiveCallBack = MCU_SPI_ReceiveFromZ20A8300A1;
    Z20A8300AIf1.SpiWaitingForReceptionCallBack = MCU_SPI_WaitingForReceptionFromZ20A8300A1;
    if(Z20A8300A_ERR_OK == Z20A8300A_Diag_ReadClearDiag(&Z20A8300AIf1,
                                                        &Z20A8300AStatus_1,
                                                        &Z20A8300ADiag_1))
    {
        if(Z20A8300ADiag_1.WORD != 0U)
        {
            Motor.Motor_Error_Flag.bit.current_short = 1U;
        }
    }
    MCPWM_IntClear(HAL_MCPWM_ID, HAL_FAULTIN);
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
void IRQHandleSTIMIsr(void)
{
    System_Tick_Isr(&Systask);
    MotorTask_SRAD_Flow(&Motor);
    STIM_ClearInt(HAL_STIM_ID); 
}

