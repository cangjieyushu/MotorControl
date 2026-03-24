/**************************************************************************************************
*     File Name :                        BUTTON.c
*     Library/Module Name :              SysTask
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             按键控制源文件
**************************************************************************************************/
#include "BUTTON.h"

ST_BUTTON_CONTROL Button_Ctrl = {
    .Q16U_vr_start_tl = VR_START_TL,
    .Q16U_vr_stop_tl = VR_STOP_TL,
    
    .Q16U_vr_max_limit = VR_MAX_LIMIT,
    .Q16U_vr_min_limit = VR_MIN_LIMIT,
    
    .Q16U_vr_duty_max = VR_MAX_DUTY,
};

/**********************************************************************************************
Function: Button_Control
Description: 按键逻辑控制
Input: 无
Output: 无
Input_Output: 按键控制指针，系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Button_Control(ST_BUTTON_CONTROL* pButton, ST_SYSTEM_TASK*  pST)
{
#if(BUTTON_MODE == BUTTON_MODE_BUTTON)
    Button_Ctrl.Button0_State = BSP_GPIO_Read_SW0_State();
    Button_Ctrl.Button1_State = BSP_GPIO_Read_SW1_State();
    
    if(pST->System_State_Flag.BIT.system_runflag == 0U)
    {
        if((pButton->Button0_State == 0U) && (pButton->Button0_State_Last == 1U))
        {
            pST->System_State_Flag.BIT.system_runflag = 1U;
        }
    }
    else if(pST->System_State_Flag.BIT.system_runflag == 1U)
    {
        if((pButton->Button1_State == 0U) && (pButton->Button1_State_Last == 1U))
        {
            pST->System_State_Flag.BIT.system_runflag = 0U;
        }
    }
    
    pButton->Button0_State_Last = pButton->Button0_State;
    pButton->Button1_State_Last = pButton->Button1_State;
    
    pST->Q16U_Duty_Target = pButton->Q16U_vr_duty_max;
        
#elif(BUTTON_MODE == BUTTON_MODE_VR)
    Q32I_ VRtmp = 0U;
    
    VRtmp = (Q32I_)pST->FL_VR.Q14I_LPF_Out;
    if(VRtmp > pButton->Q16U_vr_start_tl)
    {
        pST->System_State_Flag.BIT.system_runflag = 1U;
    }
    else if(VRtmp < pButton->Q16U_vr_stop_tl)
    {
        pST->System_State_Flag.BIT.system_runflag = 0U;
    }
    
    if(VRtmp > pButton->Q16U_vr_max_limit)
    {
        VRtmp = pButton->Q16U_vr_max_limit;
    }
    else if(VRtmp < pButton->Q16U_vr_min_limit)
    {
        VRtmp = pButton->Q16U_vr_min_limit;
    }
    
    pST->Q16U_Duty_Target = (pButton->Q16U_vr_duty_max*(VRtmp - pButton->Q16U_vr_min_limit))/(pButton->Q16U_vr_max_limit - pButton->Q16U_vr_min_limit);
	
#elif(BUTTON_MODE == BUTTON_MODE_BUTTON_VR)
    Q32I_ VRtmp = 0U;
    
    Button_Ctrl.Button0_State = BSP_GPIO_Read_SW0_State();
    Button_Ctrl.Button1_State = BSP_GPIO_Read_SW1_State();
    
    VRtmp = (Q32I_)pST->FL_VR.Q14I_LPF_Out;
    
    if(pST->System_State_Flag.BIT.system_runflag == 0U)
    {
        if((pButton->Button0_State == 0U) && (pButton->Button0_State_Last == 1U))
        {
            pST->System_State_Flag.BIT.system_runflag = 1U;
        }
    }
    else if(pST->System_State_Flag.BIT.system_runflag == 1U)
    {
        if((pButton->Button1_State == 0U) && (pButton->Button1_State_Last == 1U))
        {
            pST->System_State_Flag.BIT.system_runflag = 0U;
        }
    }
    
    pButton->Button0_State_Last = pButton->Button0_State;
    pButton->Button1_State_Last = pButton->Button1_State;
    
    if(VRtmp > pButton->Q16U_vr_max_limit)
    {
        VRtmp = pButton->Q16U_vr_max_limit;
    }
    else if(VRtmp < pButton->Q16U_vr_min_limit)
    {
        VRtmp = pButton->Q16U_vr_min_limit;
    }
    
    pST->Q16U_Duty_Target = (pButton->Q16U_vr_duty_max*(VRtmp - pButton->Q16U_vr_min_limit))/(pButton->Q16U_vr_max_limit - pButton->Q16U_vr_min_limit);
    
#else
    
#endif
}

