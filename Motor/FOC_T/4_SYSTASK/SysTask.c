/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#include "SysTask.h"
#include "Button.h"
#include "Current.h"
#include "Voltage.h"
#include "Error.h"
#include "USART.h"
#include "Speed.h"
#include "Temperature.h"

ST_SYSTEM_TASK  Systask = {
    .Q32U_System_PowerUp_Time = SYSTEM_POWERUP_TIME,
    
    .FL_VBUS.Q08I_Filter_Coeff = 25,
    .FL_TEMP.Q08I_Filter_Coeff = 25,
    .FL_VR.Q08I_Filter_Coeff = 25,
    .FL_VBG.Q08I_Filter_Coeff = 25,
};

void System_ADC_Read(ST_SYSTEM_TASK*  pST)
{
    pST->FL_VBUS.Q16I_Filter_in = (int32_t)BSP_ADC_READ_DATA_VBUS;
    pST->FL_TEMP.Q16I_Filter_in = (int32_t)BSP_ADC_READ_DATA_TEMP;
    pST->FL_VR.Q16I_Filter_in = (int32_t)BSP_ADC_READ_DATA_VR;
    pST->FL_VBG.Q16I_Filter_in = (int32_t)BSP_ADC_READ_DATA_VBG;
    Filter_Cal(&pST->FL_VBUS);
    Filter_Cal(&pST->FL_TEMP);
    Filter_Cal(&pST->FL_VR);
    Filter_Cal(&pST->FL_VBG);
}

void System_Task_Flow(ST_SYSTEM_TASK*  pST)
{
    System_ADC_Read(pST);
    
    Button_Control(&Button_Ctrl, pST);
    
    
//    Motor_Set_Dir((Q32I_)1);
    Motor_Set_Vbus((Q32I_)pST->FL_VBUS.Q16I_Filter_out);
    Motor_Set_Target_Freq((Q32I_)pST->Q16U_Duty_Target);
    
    
    if(Motor_Read_Error() != 0U)
    {
        pST->System_Error_Flag.BIT.motor_error = 1U;
    }
    
    
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
                if(pST->System_State_Flag.BIT.system_runflag == 1U)
                {
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
                if(pST->System_State_Flag.BIT.system_runflag == 0U)
                {
                    Motor_Stop();
                    pST->System_Flow = SYSTEM_STATE_IDLE;
                }
            }break;
        }
        case SYSTEM_STATE_ERROR:
        {
            if(pST->System_State_Flag.BIT.system_runflag == 0U)
            {
                pST->System_Error_Flag.ALL = 0U;
                Motor_Clear_Error();
                pST->System_Flow = SYSTEM_STATE_IDLE;
            }break;
        }
        default:
            break;
    }
}

void System_Task_Init(ST_SYSTEM_TASK*  pST)
{
    Filter_Init(&pST->FL_VBUS, (int32_t)BSP_ADC_READ_DATA_VBUS);
    Filter_Init(&pST->FL_TEMP, (int32_t)BSP_ADC_READ_DATA_TEMP);
    Filter_Init(&pST->FL_VR, (int32_t)BSP_ADC_READ_DATA_VR);
    Filter_Init(&pST->FL_VBG, (int32_t)BSP_ADC_READ_DATA_VBG);
}
    
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
