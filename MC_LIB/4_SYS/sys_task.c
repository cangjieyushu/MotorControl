/*
*     File Name :                        sys_task
*     Library/Module Name :              sys
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统状态
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "sys_task.h"
#include "sys_btn.h"
#include "sys_err.h"


/*-------------------------- 2. 变量 ---------------------------------*/
ST_SYSTEM_TASK Systask = {
    .P_Q32U_System_PowerUp_Time = SYSTEM_POWERUP_TIME,
    
    .FL_VR.P_Q14I_LPF_Coeff = 2000,
    .FL_VBG.P_Q14I_LPF_Coeff = 2000,
};

ST_SYSTEM_TASK* pST = &Systask;

/*-------------------------- 3. 公有接口实现 -----------------------------*/
static void System_Task_Init(ST_SYSTEM_TASK* pST)
{
    Q32U_ adc_tmp = 0U;
    
    adc_tmp = BSP_ADC_DATA_READ_VR;     LPF_Init_T(&pST->FL_VR, (Q32I_)adc_tmp);
}

static void System_ADC_Read(ST_SYSTEM_TASK* pST)
{
    Q32U_ adc_tmp = 0U;
    
    adc_tmp = BSP_ADC_DATA_READ_VR;     pST->FL_VR.I_Q14I_LPF_In = (Q32I_)adc_tmp;
    
    LPF_Cal_T(&pST->FL_VR);
}

static void System_Tick_Isr(void)
{
    pST->systick_10ms_count++;
    if(pST->systick_10ms_count >= 10U)
    {
        pST->systick_10ms_count = 0U;
        if(pST->System_State_Flag.bit.systick_intflow == 0U)
        {
            pST->System_State_Flag.bit.systick_intflow = 1U;
        }
        else
        {
            pST->System_Error_Flag.bit.systick_overflow = 1U;
        }
    }
}

void System_1msTask_Flow(void)
{
    System_ADC_Read(pST);
    
    if(MC_API_Motor_Read_Err(MOTOR_NUMBER_N0) != 0U)
    {
        pST->System_Error_Flag.bit.motor_error = 1U;
    }
    
    switch(pST->System_Flow)
    {
        case SYSTEM_STATE_POWERUP:
        {
            pST->V_flow_cnt++;
            if(pST->V_flow_cnt >= pST->P_Q32U_System_PowerUp_Time)
            {
                pST->V_flow_cnt = 0U;
                System_Task_Init(pST);
                pST->System_Flow = SYSTEM_STATE_IDLE;
            }
            break;
        }
        case SYSTEM_STATE_IDLE:
        {
            if(pST->System_Error_Flag.all != 0U)
            {
                pST->System_Flow = SYSTEM_STATE_ERROR;
            }
            else
            {
                if(pST->System_State_Flag.bit.system_runflag == 1U)
                {
                    pST->System_Flow = SYSTEM_STATE_RUN;
                }
            }
            break;
        }
        case SYSTEM_STATE_RUN:
        {
            if(pST->System_Error_Flag.all != 0U)
            {
                pST->System_Flow = SYSTEM_STATE_ERROR;
            }
            else
            {
                if(pST->System_State_Flag.bit.system_runflag == 0U)
                {
                    pST->System_Flow = SYSTEM_STATE_IDLE;
                }
            }
            break;
        }
        case SYSTEM_STATE_ERROR:
        {
            if(pST->System_State_Flag.bit.system_runflag == 0U)
            {
                pST->System_Error_Flag.all = 0U;
                MC_API_Motor_Clear_Err(MOTOR_NUMBER_N0);
                pST->System_Flow = SYSTEM_STATE_IDLE;
            }
            break;
        }
        default:break;
    }
    
    if(pST->System_Flow == SYSTEM_STATE_RUN)
    {
        MC_API_Motor_StartStop(MOTOR_NUMBER_N0, 1U);
    }
    else
    {
        MC_API_Motor_StartStop(MOTOR_NUMBER_N0, 0U);
    }
    
    //正点原子开发板复位
    if(BSP_GPIO_Read_SW2_State() == 0U)
    {
        MC_API_Motor_StartStop(MOTOR_NUMBER_N0, 0U);
        pST->System_State_Flag.bit.system_runflag = 0U;
        BSP_GPIO_Recover_Clear_State();
    }
    else
    {
        BSP_GPIO_Recover_Set_State();
    }
    
    System_Tick_Isr();
}

void System_10msTask_Flow(void)
{
    if(pST->System_State_Flag.bit.systick_intflow == 1U)
    {
        Button_Control(&Button_Ctrl, pST);
        
        MC_API_Motor_Set_Dir(MOTOR_NUMBER_N0, 1U);
        MC_API_Motor_Set_Speed(MOTOR_NUMBER_N0, pST->Q16U_Duty_Target*90000/16384);
        pST->Speed_rpm = MC_API_Motor_Read_Speed(MOTOR_NUMBER_N0);
        pST->Iphase_0p01A = MC_API_Motor_Read_Iphase(MOTOR_NUMBER_N0);
        pST->IBus_0p01A = MC_API_Motor_Read_Ibus(MOTOR_NUMBER_N0);
        
        Error_Priority_Check(0U);
        pST->System_State_Flag.bit.systick_intflow = 0U;
    }
}
