/**************************************************************************************************
*     File Name :                        SysTask.c
*     Library/Module Name :              SysTask
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统状态源文件
**************************************************************************************************/
#include "SysTask.h"

Q32U_ START = 0U;

void KEY_KEIL(void)
{
    Q32U_ tmp1 = BSP_GPIO_Read_SW0_State();
    Q32U_ tmp2 = BSP_GPIO_Read_SW1_State();
    static Q32U_ last_tmp1 = 0U;
    static Q32U_ last_tmp2 = 0U;
    
    if((tmp1 == 1U) && (last_tmp1 == 0U))
    {
        START = 1U;
    }
    if((tmp2 == 1U) && (last_tmp2 == 0U))
    {
        START = 2U;
    }
    last_tmp1 = tmp1;
    last_tmp2 = tmp2;
}

ST_SYSTEM_TASK  Systask = {
    .Q32U_System_PowerUp_Time = SYSTEM_POWERUP_TIME,
    
    .F_FL_VBUS.F_Filter_Coeff = 0.05f,
    .F_FL_TEMP.F_Filter_Coeff = 0.05f,
    .F_FL_VR.F_Filter_Coeff = 0.05f,
    .F_FL_VBG.F_Filter_Coeff = 0.05f,
};

/**********************************************************************************************
Function: System_Task_Init
Description: 系统任务控制初始化
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void System_Task_Init(ST_SYSTEM_TASK*  pST)
{
    Filter_Init_F(&pST->F_FL_VBUS, (float)BSP_ADC_READ_DATA_VBUS);
    Filter_Init_F(&pST->F_FL_TEMP, (float)BSP_ADC_READ_DATA_TEMP);
    Filter_Init_F(&pST->F_FL_VR, (float)BSP_ADC_READ_DATA_VR);
    Filter_Init_F(&pST->F_FL_VBG, (float)BSP_ADC_READ_DATA_VBG);
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
void System_ADC_Read(ST_SYSTEM_TASK*  pST)
{
    pST->F_FL_VBUS.F_Filter_in = (float)BSP_ADC_READ_DATA_VBUS;
    pST->F_FL_TEMP.F_Filter_in = (float)BSP_ADC_READ_DATA_TEMP;
    pST->F_FL_VR.F_Filter_in = (float)BSP_ADC_READ_DATA_VR;
    pST->F_FL_VBG.F_Filter_in = (float)BSP_ADC_READ_DATA_VBG;
    Filter_Cal_F(&pST->F_FL_VBUS);
    Filter_Cal_F(&pST->F_FL_TEMP);
    Filter_Cal_F(&pST->F_FL_VR);
    Filter_Cal_F(&pST->F_FL_VBG);
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
void System_Task_Flow(ST_SYSTEM_TASK*  pST)
{
    System_ADC_Read(pST);
    
    KEY_KEIL();
    
    if(Motor_Read_Error() != 0U)
    {
        pST->System_Error_Flag.BIT.motor_error = 1U;
    }
    
    Motor_Set_Dir(1.0f);
    Motor_Set_Target_SRAD((pST->F_FL_VR.F_Filter_out - 2048.0f)*MOTOR_MAX_SRAD/1800.0f);
    Motor_Set_Vbus(HAL_ADC_VOLTAGE_SCALE*pST->F_FL_VBUS.F_Filter_out);
    
    switch(pST->System_Flow)
    {
        case SYSTEM_STATE_POWERUP:
        {
            if(++pST->flow_cnt >= pST->Q32U_System_PowerUp_Time)
            {
                pST->flow_cnt = 0U;
                System_Task_Init(pST);
                pST->System_Flow = SYSTEM_STATE_IDLE;
            }
        }break;
        case SYSTEM_STATE_IDLE:
        {
            if(pST->System_Error_Flag.ALL != 0U)
            {
                Motor_Stop();
                pST->System_Flow = SYSTEM_STATE_ERROR;
            }
            else
            {
                if(START == 1U)
                {
                    START = 0U;
                    Motor_Start();
                    pST->System_Flow = SYSTEM_STATE_RUN;
                }
            }
            break;
        }
        case SYSTEM_STATE_RUN:
        {
            if(pST->System_Error_Flag.ALL != 0U)
            {
                Motor_Stop();
                pST->System_Flow = SYSTEM_STATE_ERROR;
            }
            else
            {
                if(START == 1U)
                {
                    START = 0U;
                    Motor_Stop();
                    pST->System_Flow = SYSTEM_STATE_IDLE;
                }
            }break;
        }
        case SYSTEM_STATE_ERROR:
        {
            if(START == 2U)
            {
                START = 0U;                
				pST->System_Error_Flag.ALL = 0U;
                Motor_Clear_Error();
                pST->System_Flow = SYSTEM_STATE_IDLE;
            }break;
        }
        default:break;
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
void System_Tick_Isr(ST_SYSTEM_TASK*  pST)
{
    if(pST->System_State_Flag.BIT.systick_intflow == 0U)
    {
        pST->System_State_Flag.BIT.systick_intflow = 1U;
    }
    else
    {
        pST->System_Error_Flag.BIT.systick_overflow = 1U;
    }
}
