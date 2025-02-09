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
    COMMON_DISABLE_INTERRUPTS();
    
    BSP_CLK_Init();
    BSP_GPIO_Init();
    Z20A8300A_Init1();
    
#if(HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
    BSP_ADC_Init_Three_Shunt();
    BSP_DMA_Init_Three_Shunt(IRQHandleDMAIsr);
    BSP_PWM_Init_Three_Shunt(IRQHandleMCBKIsr);
#else
    BSP_ADC_Init_One_Shunt();
    BSP_DMA_Init_One_Shunt(IRQHandleDMAIsr);
    BSP_PWM_Init_One_Shunt(IRQHandleMCBKIsr);
#endif
    
    BSP_ADC_Init_S();
    BSP_DMA_Init_S();
    BSP_TMU_Init();
    BSP_TIM_Init(IRQHandleSTIMIsr);
    BSP_HALL_Init();
    BSP_ISR_Init();
    BSP_WDG_Init();
    
#if(JSCOPE_RTT_EN == 1U)
    SEGGER_RTT_ConfigUpBuffer(1,JSCOPE_RTT_Sytle,Buffer,sizeof(Buffer),SEGGER_RTT_MODE_NO_BLOCK_SKIP);
#endif
    
    COMMON_ENABLE_INTERRUPTS();
    
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
void IRQHandleDMAIsr(void)
{
#if(HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
    float pwm_tmp1,pwm_tmp2,pwm_tmp3 = 0.0f;
    
    MH_ADC_Data_Read_Three(&Motor.SVPWM_CTRL._I_F_Ia_Data, &Motor.SVPWM_CTRL._I_F_Ib_Data, &Motor.SVPWM_CTRL._I_F_Ic_Data);
    
    Motor.SVPWM_CTRL._I_F_Ia = Motor.SVPWM_CTRL._P_F_Current_Scale*(Motor.SVPWM_CTRL._I_F_Ia_Offset - Motor.SVPWM_CTRL._I_F_Ia_Data);
    Motor.SVPWM_CTRL._I_F_Ib = Motor.SVPWM_CTRL._P_F_Current_Scale*(Motor.SVPWM_CTRL._I_F_Ib_Offset - Motor.SVPWM_CTRL._I_F_Ib_Data);
    Motor.SVPWM_CTRL._I_F_Ic = Motor.SVPWM_CTRL._P_F_Current_Scale*(Motor.SVPWM_CTRL._I_F_Ic_Offset - Motor.SVPWM_CTRL._I_F_Ic_Data);
    
    MotorTask_Current_Flow(&Motor);
    
    if(Motor.Motor_State_Flag.bit.pwm_output_flag == 1U)
    {
        MotorFoc_SVPWM_ThreeShunt_F(&Motor.SVPWM_CTRL);
        
        pwm_tmp1 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_Ta;
        pwm_tmp2 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_Tb;
        pwm_tmp3 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_Tc;
            
        MH_PWM_Duty_Set_Three((Q32U_)pwm_tmp1,(Q32U_)pwm_tmp2,(Q32U_)pwm_tmp3);
        MH_PWM_Output_Enable();
    }
    else
    {
        MH_PWM_Output_Disable();
    }
    
#else
    
    float pwm_tmp1,pwm_tmp2,pwm_tmp3,pwm_tmp4,pwm_tmp5,pwm_tmp6,adc_tmp1,adc_tmp2 = 0.0f;
    
    MH_ADC_Data_Read_One(&Motor.SVPWM_CTRL._I_F_Ishunt_2_Data, &Motor.SVPWM_CTRL._I_F_Ishunt_1_Data);
    
    Motor.SVPWM_CTRL._I_F_Ishunt[0] =  Motor.SVPWM_CTRL._P_F_Current_Scale*(Motor.SVPWM_CTRL._I_F_Ishunt_1_Data - Motor.SVPWM_CTRL._I_F_Ishunt_1_Offset);
    Motor.SVPWM_CTRL._I_F_Ishunt[1] = -Motor.SVPWM_CTRL._P_F_Current_Scale*(Motor.SVPWM_CTRL._I_F_Ishunt_2_Data - Motor.SVPWM_CTRL._I_F_Ishunt_2_Offset);
    Motor.SVPWM_CTRL._I_F_Ishunt[2] = -Motor.SVPWM_CTRL._I_F_Ishunt[0] - Motor.SVPWM_CTRL._I_F_Ishunt[1];
    MotorFoc_OneShunt_Cal_F(&Motor.SVPWM_CTRL);
    
    MotorTask_Current_Flow(&Motor);
    
    if(Motor.Motor_State_Flag.bit.pwm_output_flag == 1U)
    {
        MotorFoc_SVPWM_OneShunt_F(&Motor.SVPWM_CTRL);
        
        pwm_tmp1 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_TaUp;
        pwm_tmp2 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_TaDn;
        pwm_tmp3 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_TbUp;
        pwm_tmp4 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_TbDn;
        pwm_tmp5 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_TcUp;
        pwm_tmp6 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_TcDn;
        adc_tmp1 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_ADCTrigTime1;
        adc_tmp2 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_ADCTrigTime2;
        
        MH_PWM_Duty_Set_One((Q32U_)pwm_tmp1,(Q32U_)pwm_tmp2,(Q32U_)pwm_tmp3,(Q32U_)pwm_tmp4,(Q32U_)pwm_tmp5,(Q32U_)pwm_tmp6);
        MH_ADC_TrigTime_Set((Q32U_)adc_tmp1,(Q32U_)adc_tmp2);
        MH_PWM_Output_Enable();
    }
    else
    {
        MH_PWM_Output_Disable(); 
    }
#endif
    
#if(JSCOPE_RTT_EN == 1U)
    RTT_DATA[0] = 10000.0f*Motor.IF_CTRL._O_F_Angle;
    RTT_DATA[1] = 10000.0f*Motor.SMO_CTRL.TG_Triangle.F_Angle;
    RTT_DATA[2] = 10000.0f*Motor.SVPWM_CTRL._I_F_Ia;
    SEGGER_RTT_Write(1,&RTT_DATA,12U);
#endif
    
    MH_Current_IntFlag_Clear();
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
    MH_PWM_Output_Disable();
    
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
    MH_PWMFault_IntFlag_Clear();
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
    System_Task_Flow(&Systask);
    MotorTask_Speed_Flow(&Motor);
    TDG_SoftwareTrig(TDG1_ID);
    STIM_ClearInt(HAL_STIM_ID); 
}
