/**************************************************************************************************
*     File Name :                        MotorSQ.c
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             无感方波源文件
**************************************************************************************************/
 
#include "MotorSQ.h"

/**********************************************************************************************
Function: MotorSQ_Offset_Check_Init
Description: 偏置检测初始化
Input: 无
Output: 无
Input_Output: 偏置检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Offset_Check_Init(ST_MS_OFFSET* pMS_OFFSET)
{
    Q32U_ flag_tmp = ING;
    
    if(pMS_OFFSET->Flag.bit.b0_init == 0U)
    {
        pMS_OFFSET->Flag.all = 0U;
        
        pMS_OFFSET->_V_Q32U_cnt = 0U;
        
        pMS_OFFSET->_O_Q12I_Ia_Offset = 0;
        pMS_OFFSET->_O_Q12I_Ib_Offset = 0;
        pMS_OFFSET->_O_Q12I_Ic_Offset = 0;
        pMS_OFFSET->_O_Q12I_Ishunt_1_Offset = 0;
        pMS_OFFSET->_O_Q12I_Ishunt_2_Offset = 0;

        pMS_OFFSET->Flag.bit.b0_init = 1U;
    }
    else
    {
        flag_tmp = SUCS;
    }
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MotorSQ_Offset_Check_Three
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Offset_Check_Three(ST_MS_OFFSET* pMS_OFFSET)
{
    Q32U_ flag_tmp = ING;
    
    pMS_OFFSET->_O_Q12I_Ia_Offset += pMS_OFFSET->_I_Q12I_Ia_Data;
    pMS_OFFSET->_O_Q12I_Ib_Offset += pMS_OFFSET->_I_Q12I_Ib_Data;
    pMS_OFFSET->_O_Q12I_Ic_Offset += pMS_OFFSET->_I_Q12I_Ic_Data;
    pMS_OFFSET->_V_Q32U_cnt++;
    
    if(pMS_OFFSET->_V_Q32U_cnt == pMS_OFFSET->_P_Q16U_check_num)
    {
        pMS_OFFSET->_O_Q12I_Ia_Offset /= pMS_OFFSET->_V_Q32U_cnt;
        pMS_OFFSET->_O_Q12I_Ib_Offset /= pMS_OFFSET->_V_Q32U_cnt;
        pMS_OFFSET->_O_Q12I_Ic_Offset /= pMS_OFFSET->_V_Q32U_cnt;
        if((pMS_OFFSET->_O_Q12I_Ia_Offset > pMS_OFFSET->_P_Q16U_offset_max)
        || (pMS_OFFSET->_O_Q12I_Ia_Offset < pMS_OFFSET->_P_Q16U_offset_min)
        || (pMS_OFFSET->_O_Q12I_Ib_Offset > pMS_OFFSET->_P_Q16U_offset_max)
        || (pMS_OFFSET->_O_Q12I_Ib_Offset < pMS_OFFSET->_P_Q16U_offset_min)
        || (pMS_OFFSET->_O_Q12I_Ic_Offset > pMS_OFFSET->_P_Q16U_offset_max)
        || (pMS_OFFSET->_O_Q12I_Ic_Offset < pMS_OFFSET->_P_Q16U_offset_min))
        {
            pMS_OFFSET->Flag.bit.b2_fail = 1U;
        }
        else
        {
            pMS_OFFSET->Flag.bit.b1_sucs = 1U;
        }
    }
    
    if(pMS_OFFSET->Flag.bit.b1_sucs == 1U)
    {
        pMS_OFFSET->Flag.bit.b0_init = 0U;
        flag_tmp = SUCS;
    }
    else if(pMS_OFFSET->Flag.bit.b2_fail == 1U)
    {
        pMS_OFFSET->Flag.bit.b0_init = 0U;
        flag_tmp = FAIL;
    }
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MotorSQ_Offset_Check_One
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Offset_Check_One(ST_MS_OFFSET* pMS_OFFSET)
{
    Q32U_ flag_tmp = ING;
    
    pMS_OFFSET->_O_Q12I_Ishunt_1_Offset += pMS_OFFSET->_I_Q12I_Ishunt_1_Data;
    pMS_OFFSET->_O_Q12I_Ishunt_2_Offset += pMS_OFFSET->_I_Q12I_Ishunt_2_Data;
    pMS_OFFSET->_V_Q32U_cnt++;
    
    if(pMS_OFFSET->_V_Q32U_cnt == pMS_OFFSET->_P_Q16U_check_num)
    {
        pMS_OFFSET->_O_Q12I_Ishunt_1_Offset /= pMS_OFFSET->_V_Q32U_cnt;
        pMS_OFFSET->_O_Q12I_Ishunt_2_Offset /= pMS_OFFSET->_V_Q32U_cnt;
        if((pMS_OFFSET->_O_Q12I_Ishunt_1_Offset > pMS_OFFSET->_P_Q16U_offset_max)
        || (pMS_OFFSET->_O_Q12I_Ishunt_1_Offset < pMS_OFFSET->_P_Q16U_offset_min)
        || (pMS_OFFSET->_O_Q12I_Ishunt_2_Offset > pMS_OFFSET->_P_Q16U_offset_max)
        || (pMS_OFFSET->_O_Q12I_Ishunt_2_Offset < pMS_OFFSET->_P_Q16U_offset_min))
        {
            pMS_OFFSET->Flag.bit.b2_fail = 1U;
        }
        else
        {
            pMS_OFFSET->Flag.bit.b1_sucs = 1U;
        }
    }
    
    if(pMS_OFFSET->Flag.bit.b1_sucs == 1U)
    {
        pMS_OFFSET->Flag.bit.b0_init = 0U;
        flag_tmp = SUCS;
    }
    else if(pMS_OFFSET->Flag.bit.b2_fail == 1U)
    {
        pMS_OFFSET->Flag.bit.b0_init = 0U;
        flag_tmp = FAIL;
    }
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MotorSQ_Boot_Check_Init
Description: 自举控制初始化
Input: 无
Output: 无
Input_Output: 自举控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Boot_Check_Init(ST_MS_BOOT* pMS_BOOT)
{
    Q32U_ flag_tmp = ING;
    
    if(pMS_BOOT->Flag.bit.b0_init == 0U)
    {
        pMS_BOOT->Flag.all = 0U;

        pMS_BOOT->_V_Q32U_cnt = 0U;
        pMS_BOOT->_V_Q32U_time_cnt = 0U;
        
        pMS_BOOT->Flag.bit.b0_init = 1U;
    }
    else
    {
        flag_tmp = SUCS;
    }
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MotorSQ_Boot_Check
Description: 自举控制计算
Input: 无
Output: 无
Input_Output: 自举控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Boot_Check(ST_MS_BOOT* pMS_BOOT)
{
    Q32U_ flag_tmp = ING;
    
    if((pMS_BOOT->_I_Q12I_BEMF_U_ADC < pMS_BOOT->_P_Q16U_boot_tl)
    && (pMS_BOOT->_I_Q12I_BEMF_V_ADC < pMS_BOOT->_P_Q16U_boot_tl)
    && (pMS_BOOT->_I_Q12I_BEMF_W_ADC < pMS_BOOT->_P_Q16U_boot_tl))
    {
        pMS_BOOT->_V_Q32U_cnt++;
        if(++pMS_BOOT->_V_Q32U_cnt == pMS_BOOT->_P_Q16U_boot_num)
        {
            pMS_BOOT->Flag.bit.b1_sucs = 1U;
        }
    }
    pMS_BOOT->_V_Q32U_time_cnt++;
    if(pMS_BOOT->_V_Q32U_time_cnt == pMS_BOOT->_P_Q16U_boot_time)
    {
        pMS_BOOT->Flag.bit.b2_fail = 1U;
    }
    
    if(pMS_BOOT->Flag.bit.b1_sucs == 1U)
    {
        pMS_BOOT->Flag.bit.b0_init = 0U;
        flag_tmp = SUCS;
    }
    else if(pMS_BOOT->Flag.bit.b2_fail == 1U)
    {
        pMS_BOOT->Flag.bit.b0_init = 0U;
        flag_tmp = FAIL;
    }
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MotorSQ_Brake_Init
Description: 刹车控制初始化
Input: 无
Output: 无
Input_Output: 刹车控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Brake_Init(ST_BRAKE_CONTROL* pBRAKE_CTRL)
{
    Q32U_ flag_tmp = ING;
    
    if(pBRAKE_CTRL->Flag.bit.b0_init == 0U)
    {
        pBRAKE_CTRL->Flag.all = 0U;

        pBRAKE_CTRL->_V_Q32U_cnt = 0U;
        pBRAKE_CTRL->_O_Q12U_brake_duty = 0U;
        
        pBRAKE_CTRL->Flag.bit.b0_init = 1U;
    }
    else
    {
        flag_tmp = SUCS;
    }
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MotorSQ_Brake
Description: 刹车控制占空比计算
Input: 无
Output: 无
Input_Output: 刹车控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Brake(ST_BRAKE_CONTROL* pBRAKE_CTRL)
{
    Q32U_ flag_tmp = ING;
    
    if(pBRAKE_CTRL->_V_Q32U_cnt <= pBRAKE_CTRL->_P_Q16U_no_time)
    {
        pBRAKE_CTRL->_O_Q12U_brake_duty = 0U;
        if(pBRAKE_CTRL->_V_Q32U_cnt == pBRAKE_CTRL->_P_Q16U_no_time)
        {
            if(pBRAKE_CTRL->_P_Q16U_slow_time > 0U)
            {
                Ramp_Init_T(&pBRAKE_CTRL->Ramp_Brake_Duty, pBRAKE_CTRL->Ramp_Brake_Duty.Q32I_Init);
            }
            else
            {
                if(pBRAKE_CTRL->_P_Q16U_short_time > 0U)
                {
                    pBRAKE_CTRL->_O_Q12U_brake_duty = pBRAKE_CTRL->_P_Q12U_duty_max;
                }
            }
        }
    }
    else if(pBRAKE_CTRL->_V_Q32U_cnt <= pBRAKE_CTRL->_P_Q16U_no_time + pBRAKE_CTRL->_P_Q16U_slow_time)
    {
        Ramp_Cal_T(&pBRAKE_CTRL->Ramp_Brake_Duty);
        pBRAKE_CTRL->_O_Q12U_brake_duty = pBRAKE_CTRL->Ramp_Brake_Duty.Q32I_Output;
    }
    else if(pBRAKE_CTRL->_V_Q32U_cnt <= pBRAKE_CTRL->_P_Q16U_no_time + pBRAKE_CTRL->_P_Q16U_slow_time + pBRAKE_CTRL->_P_Q16U_short_time)
    {
        pBRAKE_CTRL->_O_Q12U_brake_duty = pBRAKE_CTRL->_P_Q12U_duty_max;
    }
    else
    {
        pBRAKE_CTRL->_V_Q32U_cnt = 0U;
        pBRAKE_CTRL->Flag.bit.b1_sucs = 1U;
    }
        
    if(pBRAKE_CTRL->Flag.bit.b1_sucs == 1U)
    {
        pBRAKE_CTRL->Flag.bit.b0_init = 0U;
        flag_tmp = SUCS;
    }
    
    pBRAKE_CTRL->_V_Q32U_cnt++;
    
    return flag_tmp;
}
