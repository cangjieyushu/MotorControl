/**************************************************************************************************
*     File Name :                        SYSTASK.c
*     Library/Module Name :              SYSTASK
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统状态源文件
**************************************************************************************************/

#include "BUTTON.h"
#include "SYS_ERR.h"
#include "SYS_LCD.h"
#include "SYS_VOFA.h"
#include "SYSTASK.h"


ST_SYSTEM_TASK  Systask = {
    ._P_Q32U_System_PowerUp_Time = SYSTEM_POWERUP_TIME,
    
    .FL_VR.Q14I_LPF_Coeff = 2000,
    .FL_VBG.Q14I_LPF_Coeff = 2000,
};

void System_Tick_Isr(ST_SYSTEM_TASK*  pST);


/**********************************************************************************************
Function: System_Task_Init
Description: 系统任务控制初始化
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void System_Task_Init(ST_SYSTEM_TASK* pST)
{
    Q32U_ adc_tmp = 0U;
    
    adc_tmp = BSP_ADC_DATA_READ_VR;     LPF_Init_T(&pST->FL_VR, (Q32I_)adc_tmp);
}

/**********************************************************************************************
Function: System_ADC_Read
Description: 系统ADC数据读取及滤波
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void System_ADC_Read(ST_SYSTEM_TASK* pST)
{
    Q32U_ adc_tmp = 0U;
    
    adc_tmp = BSP_ADC_DATA_READ_VR;     pST->FL_VR.Q14I_LPF_In = (Q32I_)adc_tmp;
    
    LPF_Cal_T(&pST->FL_VR);
}

/**********************************************************************************************
Function: System_Task_Flow
Description: 系统状态控制
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void System_Task_Flow(ST_SYSTEM_TASK* pST)
{
    System_ADC_Read(pST);
    
//    Motor_Set_Target_Speed(&Motor, pST->Q16U_Duty_Target);
    
//    SYS_VOFA_TASK(&Motor, pST, &UART_Ctrl);
    
        
    if(Motor_Read_Error(&Motor) != 0U)
    {
        pST->System_Error_Flag.BIT.motor_error = 1U;
    }
    
    switch(pST->System_Flow)
    {
        case SYSTEM_STATE_POWERUP:
        {
            pST->_V_flow_cnt++;
            if(pST->_V_flow_cnt >= pST->_P_Q32U_System_PowerUp_Time)
            {
                pST->_V_flow_cnt = 0U;
                System_Task_Init(pST);
                pST->System_Flow = SYSTEM_STATE_IDLE;
            }
            break;
        }
        case SYSTEM_STATE_IDLE:
        {
            if(pST->System_Error_Flag.ALL != 0U)
            {
                pST->System_Flow = SYSTEM_STATE_ERROR;
            }
            else
            {
                if(pST->System_State_Flag.BIT.system_runflag == 1U)
                {
                    pST->System_Flow = SYSTEM_STATE_RUN;
                }
            }
            break;
        }
        case SYSTEM_STATE_RUN:
        {
            if(pST->System_Error_Flag.ALL != 0U)
            {
                pST->System_Flow = SYSTEM_STATE_ERROR;
            }
            else
            {
                if(pST->System_State_Flag.BIT.system_runflag == 0U)
                {
                    pST->System_Flow = SYSTEM_STATE_IDLE;
                }
            }
            break;
        }
        case SYSTEM_STATE_ERROR:
        {
            if(pST->System_State_Flag.BIT.system_runflag == 0U)
            {
                pST->System_Error_Flag.ALL = 0U;
                Motor_Clear_Error(&Motor);
                pST->System_Flow = SYSTEM_STATE_IDLE;
            }
            break;
        }
        default:break;
    }
    
    if(pST->System_Flow == SYSTEM_STATE_RUN)
    {
        Motor_Start(&Motor);
    }
    else
    {
        Motor_Stop(&Motor);
    }
    
    System_Tick_Isr(pST);
}

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
//        BSP_FeedWatchDog();
        
        Motor_Set_Target_Speed(&Motor, 0U);
        
//        Button_Control(&Button_Ctrl, pST);
    
//        UART_Get_Resceive_Data();
//        UART_Send_Transmission_Data();
    
        Error_Priority_Check(0U);
        pST->System_State_Flag.BIT.systick_intflow = 0U;
    }
}

/**********************************************************************************************
Function: System_Tick_Isr
Description: 系统负载率防溢出
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void System_Tick_Isr(ST_SYSTEM_TASK* pST)
{
    pST->systick_10ms_count++;
    if(pST->systick_10ms_count >= 10U)
    {
        pST->systick_10ms_count = 0U;
        if(pST->System_State_Flag.BIT.systick_intflow == 0U)
        {
            pST->System_State_Flag.BIT.systick_intflow = 1U;
        }
        else
        {
            pST->System_Error_Flag.BIT.systick_overflow = 1U;
        }
    }
}
