/**************************************************************************************************
*     File Name :                        Button.c
*     Library/Module Name :              SysTask
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             按键控制源文件
**************************************************************************************************/
#include "Button.h"

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
    int32_t VRtmp = 0U;
    
    VRtmp = (int32_t)pST->FL_VR.Q16I_Filter_out;
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
    
    pST->Q16U_Duty_Target = (pButton->Q16U_vr_duty_max*(VRtmp - pButton->Q16U_vr_min_limit))
    /(pButton->Q16U_vr_max_limit - pButton->Q16U_vr_min_limit);
}

