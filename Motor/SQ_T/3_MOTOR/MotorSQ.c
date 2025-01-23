/**************************************************************************************************
*     File Name :                        MotorSQ.c
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             无感方波源文件
**************************************************************************************************/
 
#include "MotorSQ.h"

EM_CHANNEL_NUM ADC_VAL_Table[6][3] = 
{
    U_CHANNEL_NUM, W_CHANNEL_NUM, V_CHANNEL_NUM, 
    U_CHANNEL_NUM, V_CHANNEL_NUM, W_CHANNEL_NUM,
    V_CHANNEL_NUM, U_CHANNEL_NUM, W_CHANNEL_NUM, 
    V_CHANNEL_NUM, W_CHANNEL_NUM, U_CHANNEL_NUM,
    W_CHANNEL_NUM, V_CHANNEL_NUM, U_CHANNEL_NUM, 
    W_CHANNEL_NUM, U_CHANNEL_NUM, V_CHANNEL_NUM,
};

EM_SECTOR_NUM Position_Sector[6][2] = {sector_3, sector_5,
                                       sector_4, sector_6,
                                       sector_5, sector_1,
                                       sector_6, sector_2,
                                       sector_1, sector_3,
                                       sector_2, sector_4};

EM_SECTOR_NUM Last_Sector[6] = {sector_6, sector_1, sector_2, sector_3, sector_4, sector_5};
EM_SECTOR_NUM Next_Sector[6] = {sector_2, sector_3, sector_4, sector_5, sector_6, sector_1};

/**********************************************************************************************
Function: MotorSQ_Init
Description: 方波算法初始化
Input: 无
Output: 无
Input_Output: 方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_Init(ST_MS_CONTROL* pMS_CTRL)
{
    pMS_CTRL->SW_Math = SWITCH_CURRENT;
    pMS_CTRL->SQ_Flow = SQUARE_CROSS_ING;
    pMS_CTRL->DIR_Set = pMS_CTRL->DIR_Target;
    
    Ramp_Init_T(&pMS_CTRL->Ramp_Freq, pMS_CTRL->Ramp_Freq.Q32I_Init);
    
    Filter_Init_T(&pMS_CTRL->FL_Iphase, 0);
    Filter_Init_T(&pMS_CTRL->FL_Freq, 0);
    Filter_Init_T(&pMS_CTRL->FL_Ibus, 0);
    Filter_Init_T(&pMS_CTRL->FL_Ibrake, 0);
    
    PID_Inc_Init_T(&pMS_CTRL->PID_Iphase, 0);
    PID_Inc_Init_T(&pMS_CTRL->PID_Freq, 0);
    PID_Inc_Init_T(&pMS_CTRL->PID_Ibus, 0);
    PID_Inc_Init_T(&pMS_CTRL->PID_Ibrake, 0);
    
    MotorSQ_DIAG_Init(&pMS_CTRL->MS_DIAG);
    MotorSQ_CURRENT_Init(&pMS_CTRL->MS_CURRENT);
    MotorSQ_FLUX_Init(&pMS_CTRL->MS_FLUX);
    MotorSQ_BEMF_Init(&pMS_CTRL->MS_BEMF);
    MotorSQ_CMP_Init(&pMS_CTRL->MS_CMP);
    MotorSQ_Freq_Cal_Init(&pMS_CTRL->FREQ_CAL);
    MotorSQ_PWM_Freq_Switch_Init(&pMS_CTRL->PWM_CTRL);
    MotorSQ_Stall_Check_Init(&pMS_CTRL->STALL_CTRL, pMS_CTRL);
    
    pMS_CTRL->Q12I_BEMF_ADC_tmp[0] = 0;
    pMS_CTRL->Q12I_BEMF_ADC_tmp[1] = 0;
    pMS_CTRL->Q12I_BEMF_ADC_tmp[2] = 0;
    pMS_CTRL->Q12I_VBUS_VAL = 0;
    pMS_CTRL->Q12I_IPHASE_ADC = 0;
    pMS_CTRL->Q12I_IPHASE_OFFSET = 0;
    pMS_CTRL->Q14I_IPHASE_PU = 0;
    
    pMS_CTRL->Q32U_switch_cnt = 0;
}

/**********************************************************************************************
Function: MotorSQ_Flying_Init
Description: 顺风启动初始化
Input: 无
Output: 无
Input_Output: 方波控制指针，顺风检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_Flying_Init(ST_MS_CONTROL* pMS_CTRL, ST_MS_FLYING* pMS_FLYING)
{
    pMS_CTRL->SW_Math = SWITCH_BEMF;
    pMS_CTRL->SQ_Flow = SQUARE_SWITCH_SUCC;
    pMS_CTRL->PWM_CTRL.Flag.bit.b0_init = SUCC;
    
    pMS_CTRL->FL_Freq.Q16I_Filter_in = Q32I_RHT_10(pMS_CTRL->_P_Q32U_Freq_Scale*(pMS_CTRL->FREQ_CAL._P_Q32U_hall_tim_freq/(
    pMS_CTRL->FREQ_CAL._V_Q32U_60_degree_cnt_tmp[0] + pMS_CTRL->FREQ_CAL._V_Q32U_60_degree_cnt_tmp[1]
    + pMS_CTRL->FREQ_CAL._V_Q32U_60_degree_cnt_tmp[2] + pMS_CTRL->FREQ_CAL._V_Q32U_60_degree_cnt_tmp[3]
    + pMS_CTRL->FREQ_CAL._V_Q32U_60_degree_cnt_tmp[4] + pMS_CTRL->FREQ_CAL._V_Q32U_60_degree_cnt_tmp[5])));
    
    pMS_CTRL->PWM_CTRL._O_Q16U_duty_final_val = pMS_FLYING->_P_Q12U_vbus_max_val*(pMS_CTRL->PWM_CTRL._P_Q12U_duty_max
    *pMS_CTRL->FL_Freq.Q16I_Filter_in/pMS_CTRL->PWM_CTRL._P_Q14U_motor_freq_max)/pMS_CTRL->Q12I_VBUS_VAL;
    if(pMS_CTRL->PWM_CTRL._O_Q16U_duty_final_val > pMS_CTRL->PWM_CTRL._P_Q12U_duty_max)
    {
        pMS_CTRL->PWM_CTRL._O_Q16U_duty_final_val = pMS_CTRL->PWM_CTRL._P_Q12U_duty_max;
    }
    
    Ramp_Init_T(&pMS_CTRL->Ramp_Freq, pMS_CTRL->FL_Freq.Q16I_Filter_in);
    
    PID_Inc_Init_T(&pMS_CTRL->PID_Iphase, pMS_CTRL->PWM_CTRL._O_Q16U_duty_final_val);
    PID_Inc_Init_T(&pMS_CTRL->PID_Freq, pMS_CTRL->PWM_CTRL._O_Q16U_duty_final_val);
    PID_Inc_Init_T(&pMS_CTRL->PID_Ibus, pMS_CTRL->PWM_CTRL._O_Q16U_duty_final_val);
    
    Ramp_Init_T(&pMS_CTRL->PWM_CTRL.Ramp_Duty, pMS_CTRL->PWM_CTRL._O_Q16U_duty_final_val);
    
    Filter_Init_T(&pMS_CTRL->FL_Freq, pMS_CTRL->FL_Freq.Q16I_Filter_in);
    
    pMS_CTRL->PWM_CTRL._I_Q12I_duty_freq = pMS_CTRL->PWM_CTRL._O_Q16U_duty_final_val;
    pMS_CTRL->PWM_CTRL._I_Q12I_duty_ibus = pMS_CTRL->PWM_CTRL._O_Q16U_duty_final_val;
    pMS_CTRL->PWM_CTRL._I_Q12I_duty_iphase = pMS_CTRL->PWM_CTRL._O_Q16U_duty_final_val;
    pMS_CTRL->PWM_CTRL._O_Q12I_duty_set = pMS_CTRL->PWM_CTRL._O_Q16U_duty_final_val;
    pMS_CTRL->PWM_CTRL._O_Q16U_arr_set = pMS_CTRL->PWM_CTRL._P_Q14U_high_pwm_freq;
    
    pMS_CTRL->PWM_CTRL._O_Q16U_duty_final_val = Q32I_RHT_12(pMS_CTRL->PWM_CTRL._O_Q12I_duty_set*pMS_CTRL->PWM_CTRL._O_Q16U_arr_set);
}

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

        pMS_OFFSET->Flag.bit.b0_init = 1U;
    }
    else
    {
        flag_tmp = SUCC;
    }
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MotorSQ_Offset_Check
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Offset_Check(ST_MS_OFFSET* pMS_OFFSET)
{
    Q32U_ flag_tmp = ING;
    
    pMS_OFFSET->_O_Q12I_IPHASE_OFFSET += pMS_OFFSET->_I_Q12I_IPHASE_ADC;
    pMS_OFFSET->_V_Q32U_cnt++;
    
    if(pMS_OFFSET->_V_Q32U_cnt == pMS_OFFSET->_P_Q16U_check_num)
    {
        pMS_OFFSET->_O_Q12I_IPHASE_OFFSET /= pMS_OFFSET->_V_Q32U_cnt;
        if((pMS_OFFSET->_O_Q12I_IPHASE_OFFSET > pMS_OFFSET->_P_Q16U_offset_max)
        || (pMS_OFFSET->_O_Q12I_IPHASE_OFFSET < pMS_OFFSET->_P_Q16U_offset_min))
        {
            pMS_OFFSET->Flag.bit.b2_fail = 1U;
        }
        else
        {
            pMS_OFFSET->Flag.bit.b1_succ = 1U;
        }
    }
    
    if(pMS_OFFSET->Flag.bit.b1_succ == 1U)
    {
        pMS_OFFSET->Flag.bit.b0_init = 0U;
        flag_tmp = SUCC;
    }
    else if(pMS_OFFSET->Flag.bit.b2_fail == 1U)
    {
        pMS_OFFSET->Flag.bit.b0_init = 0U;
        flag_tmp = FAIL;
    }
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MotorSQ_Flying_Check_Init
Description: 顺风检测初始化
Input: 无
Output: 无
Input_Output: 顺风检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Flying_Check_Init(ST_MS_FLYING* pMS_FLYING)
{
    Q32U_ flag_tmp = ING;
    
    if(pMS_FLYING->Flag.bit.b0_init == 0U)
    {
        pMS_FLYING->Flag.all = 0U;

        pMS_FLYING->_V_Q32U_cnt = 0U;
        pMS_FLYING->_V_Q32U_time_cnt = 0U;
        pMS_FLYING->_V_Q32U_switch_cnt = 0U;
        pMS_FLYING->_V_Q32U_phase_cnt = 0U;
        
        pMS_FLYING->Flag.bit.b0_init = 1U;
    }
    else
    {
        flag_tmp = SUCC;
    }
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MotorSQ_Flying_Check
Description: 顺风检测计算
Input: 无
Output: 无
Input_Output: 顺风检测指针，频率计算指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Flying_Check(ST_MS_FLYING* pMS_FLYING, ST_FREQ_CAL* pFREQ_CAL, ST_MS_CONTROL* pMS_CTRL)
{
    Q32U_ flag_tmp = ING;
    
    if((pMS_FLYING->_I_Q12I_BEMF_U_ADC < pMS_FLYING->_P_Q16U_check_tl)
    && (pMS_FLYING->_I_Q12I_BEMF_V_ADC < pMS_FLYING->_P_Q16U_check_tl)
    && (pMS_FLYING->_I_Q12I_BEMF_W_ADC < pMS_FLYING->_P_Q16U_check_tl))
    {
        pMS_FLYING->_V_Q32U_cnt++;
    }
    else
    {
        if((pMS_FLYING->_I_Q12I_BEMF_U_ADC > pMS_FLYING->_I_Q12I_BEMF_V_ADC)
        && (pMS_FLYING->_I_Q12I_BEMF_U_ADC > pMS_FLYING->_I_Q12I_BEMF_W_ADC))
        {
            if(pMS_FLYING->_I_Q12I_BEMF_V_ADC > pMS_FLYING->_I_Q12I_BEMF_W_ADC)
            {//UVW
                pMS_CTRL->Sector = sector_3;
            }
            else
            {//UWV
                pMS_CTRL->Sector = sector_2;
            }
        }
        else
        {
            if(pMS_FLYING->_I_Q12I_BEMF_V_ADC > pMS_FLYING->_I_Q12I_BEMF_W_ADC)
            {
                if(pMS_FLYING->_I_Q12I_BEMF_U_ADC > pMS_FLYING->_I_Q12I_BEMF_W_ADC)
                {//VUW
                    pMS_CTRL->Sector = sector_4;
                }
                else
                {//VWU
                    pMS_CTRL->Sector = sector_5;
                }
            }
            else
            {
                if(pMS_FLYING->_I_Q12I_BEMF_U_ADC > pMS_FLYING->_I_Q12I_BEMF_V_ADC)
                {//WUV
                    pMS_CTRL->Sector = sector_1;
                }
                else
                {//WVU
                    pMS_CTRL->Sector = sector_6;
                }
            }
        }
        
        if(Next_Sector[pMS_CTRL->Sector_Last] == pMS_CTRL->Sector)
        {
            pMS_FLYING->_V_Q32U_switch_cnt++;
            if(pMS_FLYING->_V_Q32U_switch_cnt > pMS_FLYING->_P_Q16U_flying_filter)
            {
                pMS_FLYING->_V_Q32U_switch_cnt = 0;
                if(pMS_FLYING->_V_Q32U_phase_cnt == 0U)
                {
                    pFREQ_CAL->_V_Q32U_60_degree_cnt_last = pFREQ_CAL->_I_Q32U_time_count;
                }
                else
                {
                    if(pFREQ_CAL->_I_Q32U_time_count > pFREQ_CAL->_V_Q32U_60_degree_cnt_last)
                    {
                        pFREQ_CAL->_O_Q32U_60_degree_cnt = pFREQ_CAL->_I_Q32U_time_count - pFREQ_CAL->_V_Q32U_60_degree_cnt_last;
                    }
                    else
                    {
                        pFREQ_CAL->_O_Q32U_60_degree_cnt = (pFREQ_CAL->_P_Q32U_hall_tim_max_cnt - pFREQ_CAL->_V_Q32U_60_degree_cnt_last) + pFREQ_CAL->_I_Q32U_time_count;
                    }
                    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[pMS_FLYING->_V_Q32U_phase_cnt-1] = pFREQ_CAL->_O_Q32U_60_degree_cnt;
                    pFREQ_CAL->_V_Q32U_60_degree_cnt_last = pFREQ_CAL->_I_Q32U_time_count;
                }
                if(pMS_FLYING->_V_Q32U_phase_cnt == 6U)
                {
                    pMS_FLYING->Flag.bit.b1_succ = 1U;
                }
                pMS_FLYING->_V_Q32U_phase_cnt++;
                pMS_CTRL->Sector_Last = pMS_CTRL->Sector;
            }
        }
        
        pMS_FLYING->_V_Q32U_cnt = 0U;
    }
    
    if((pMS_FLYING->_V_Q32U_cnt > pMS_FLYING->_P_Q16U_check_num)
    || (pMS_FLYING->_V_Q32U_time_cnt > pMS_FLYING->_P_Q16U_flying_time))
    {
        pMS_FLYING->Flag.bit.b2_fail = 1U;
    }
    
    if(pMS_FLYING->Flag.bit.b1_succ == 1U)
    {
        pMS_FLYING->Flag.bit.b0_init = 0U;
        flag_tmp = SUCC;
    }
    else if(pMS_FLYING->Flag.bit.b2_fail == 1U)
    {
        pMS_FLYING->Flag.bit.b0_init = 0U;
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
        flag_tmp = SUCC;
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
            pMS_BOOT->Flag.bit.b1_succ = 1U;
        }
    }
    pMS_BOOT->_V_Q32U_time_cnt++;
    if(pMS_BOOT->_V_Q32U_time_cnt == pMS_BOOT->_P_Q16U_boot_time)
    {
        pMS_BOOT->Flag.bit.b2_fail = 1U;
    }
    
    if(pMS_BOOT->Flag.bit.b1_succ == 1U)
    {
        pMS_BOOT->Flag.bit.b0_init = 0U;
        flag_tmp = SUCC;
    }
    else if(pMS_BOOT->Flag.bit.b2_fail == 1U)
    {
        pMS_BOOT->Flag.bit.b0_init = 0U;
        flag_tmp = FAIL;
    }
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MotorSQ_Pluse_Positon_Init
Description: 脉冲定位初始化
Input: 无
Output: 无
Input_Output: 脉冲定位指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Pluse_Positon_Init(ST_MS_POSITION* pMS_POSITION)
{
    Q32U_ flag_tmp = ING;
    
    if(pMS_POSITION->Flag.bit.b0_init == 0U)
    {
        pMS_POSITION->Flag.all = 0U;

        pMS_POSITION->_V_Q32U_cnt = 0U;
        
        pMS_POSITION->Flag.bit.b0_init = 1U;
    }
    else
    {
        flag_tmp = SUCC;
    }
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MotorSQ_Pluse_Positon
Description: 脉冲定位计算
Input: 无
Output: 无
Input_Output: 脉冲定位指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Pluse_Positon(ST_MS_POSITION* pMS_POSITION, ST_MS_CONTROL* pMS_CTRL)
{
    Q32U_ flag_tmp = ING;
    
    switch(pMS_POSITION->_V_Q32U_cnt)
    {
        case 0U:{pMS_POSITION->_V_Q32U_cnt = 3U;break;}
        case 3U:{pMS_POSITION->_V_Q32U_cnt = 1U;break;}
        case 1U:{pMS_POSITION->_V_Q32U_cnt = 4U;break;}
        case 4U:{pMS_POSITION->_V_Q32U_cnt = 2U;break;}
        case 2U:{pMS_POSITION->_V_Q32U_cnt = 5U;break;}
        case 5U:{pMS_POSITION->_V_Q32U_cnt = 6U;break;}
        default:break;
    }
        
    if(pMS_POSITION->_V_Q32U_cnt == 6U)
    {
        Q16U_ max_tmp = pMS_POSITION->_I_Q12I_Position_Current_VAL[sector_1];
        Q08U_ max_index = sector_1;
        for(Q08U_ i=1U;i<6U;i++)
        {
            if(pMS_POSITION->_I_Q12I_Position_Current_VAL[i] > max_tmp)
            {
                max_index = i;
                max_tmp = pMS_POSITION->_I_Q12I_Position_Current_VAL[i];
            }
        }
        
        pMS_CTRL->Sector = Position_Sector[max_index][pMS_CTRL->DIR_Set];
        
        pMS_POSITION->Flag.bit.b2_fail = 0U;
        pMS_POSITION->Flag.bit.b1_succ = 1U;
        for(Q08U_ j=0U;j<6U;j++)
        {
            if(pMS_POSITION->_I_Q12I_Position_Current_VAL[j] < pMS_POSITION->_P_Q16U_position_tl)
            {
                pMS_POSITION->Flag.bit.b1_succ = 0U;
                pMS_POSITION->Flag.bit.b2_fail = 1U;
            }
        }
        
        pMS_POSITION->Flag.bit.b0_init = 0U;
        if(pMS_POSITION->Flag.bit.b1_succ == 1U)
        {
            flag_tmp = SUCC;
        }
        else if(pMS_POSITION->Flag.bit.b2_fail == 1U)
        {
            flag_tmp = FAIL;
        }
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
Q32U_ MotorSQ_Brake_Init(ST_BRAKE_CONTROL* pBRAKE_CTRL, ST_MS_CONTROL* pMS_CTRL)
{
    Q32U_ flag_tmp = ING;
    
    if(pBRAKE_CTRL->Flag.bit.b0_init == 0U)
    {
        pBRAKE_CTRL->Flag.all = 0U;

        pBRAKE_CTRL->_V_Q32U_cnt = 0U;
        pBRAKE_CTRL->_O_Q12U_brake_duty = 0U;
        PID_Inc_Init_T(&pMS_CTRL->PID_Ibrake, pMS_CTRL->PID_Ibrake.Q14I_OutMin);
        
        pBRAKE_CTRL->Flag.bit.b0_init = 1U;
    }
    else
    {
        flag_tmp = SUCC;
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
Q32U_ MotorSQ_Brake(ST_BRAKE_CONTROL* pBRAKE_CTRL, ST_MS_CONTROL* pMS_CTRL)
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
        pBRAKE_CTRL->Flag.bit.b1_succ = 1U;
    }
        
    if(pBRAKE_CTRL->Flag.bit.b1_succ == 1U)
    {
        pBRAKE_CTRL->Flag.bit.b0_init = 0U;
        flag_tmp = SUCC;
    }
    
    pBRAKE_CTRL->_V_Q32U_cnt++;
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MotorSQ_DIAG_Init
Description: 续流检测初始化
Input: 无
Output: 无
Input_Output: 续流检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_DIAG_Init(ST_MS_DIAG* pMS_DIAG)
{
    pMS_DIAG->_V_Q32U_cnt = 0U;
    pMS_DIAG->_V_Q32U_time_cnt = 0U;
}

/**********************************************************************************************
Function: MotorSQ_DIAG_Zero_Cross
Description: 续流检测计算
Input: 无
Output: 无
Input_Output: 续流检测指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_DIAG_Zero_Cross(ST_MS_DIAG* pMS_DIAG, ST_MS_CONTROL* pMS_CTRL)
{ 
    pMS_DIAG->_I_Q12I_BEMF_ZI_VAL = pMS_CTRL->Q12I_BEMF_ADC_tmp[ADC_VAL_Table[pMS_CTRL->Sector][1]];
    pMS_DIAG->_I_Q12I_VBUS_VAL = pMS_CTRL->Q12I_VBUS_VAL;
    
    switch(pMS_CTRL->Sector)
    {
        case sector_1:case sector_3:case sector_5:
        {
            if(Q16I_LFT_06(pMS_DIAG->_I_Q12I_BEMF_ZI_VAL) > pMS_DIAG->_P_Q06U_fall_tl*pMS_DIAG->_I_Q12I_VBUS_VAL)
            {
                pMS_DIAG->_V_Q32U_cnt++;
                if(pMS_DIAG->_V_Q32U_cnt > pMS_DIAG->_P_Q08U_filter)
                {
                    pMS_DIAG->_V_Q32U_cnt = 0U;
                    pMS_CTRL->SQ_Flow = SQUARE_CROSS_ING;
                }
            }
            else
            {
                pMS_DIAG->_V_Q32U_cnt = 0U;
            }
            break;
        }
        case sector_2:case sector_4:case sector_6:
        {
            if(Q16I_LFT_06(pMS_DIAG->_I_Q12I_BEMF_ZI_VAL) < pMS_DIAG->_P_Q06U_rise_tl*pMS_DIAG->_I_Q12I_VBUS_VAL)
            {
                pMS_DIAG->_V_Q32U_cnt++;
                if(pMS_DIAG->_V_Q32U_cnt > pMS_DIAG->_P_Q08U_filter)
                {
                    pMS_DIAG->_V_Q32U_cnt = 0U;
                    pMS_CTRL->SQ_Flow = SQUARE_CROSS_ING;
                }
            }
            else
            {
                pMS_DIAG->_V_Q32U_cnt = 0U;
            }
            break;
        }
        default:break;
    }
    
    if(pMS_CTRL->SW_Math == SWITCH_CURRENT)
    {
        pMS_DIAG->_V_Q32U_time_cnt++;
        if(pMS_DIAG->_V_Q32U_time_cnt > pMS_DIAG->_P_Q16U_current_filter)
        {
            pMS_CTRL->SQ_Flow = SQUARE_CROSS_ING;
        }
    }
    if(pMS_CTRL->SQ_Flow == SQUARE_CROSS_ING)
    {
        pMS_DIAG->_V_Q32U_time_cnt = 0U;
    }
}

/**********************************************************************************************
Function: MotorSQ_CURRENT_Init
Description: 电流换向初始化
Input: 无
Output: 无
Input_Output: 电流换向指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_CURRENT_Init(ST_MS_CURRENT* pMS_CURRENT)
{
    pMS_CURRENT->_V_Q32U_cnt = 0U;
    pMS_CURRENT->_V_Q32U_time_cnt = 0U;
    pMS_CURRENT->_V_Q32U_switch_cnt = 0U;
}

/**********************************************************************************************
Function: MotorSQ_CURRENT_Zero_Cross
Description: 电流换向计算
Input: 无
Output: 无
Input_Output: 电流换向指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_CURRENT_Zero_Cross(ST_MS_CURRENT* pMS_CURRENT, ST_MS_CONTROL* pMS_CTRL)
{
    pMS_CURRENT->_I_Q12I_BEMF_ON_VAL = pMS_CTRL->Q12I_BEMF_ADC_tmp[ADC_VAL_Table[pMS_CTRL->Sector][0]];
    pMS_CURRENT->_I_Q12I_BEMF_ZI_VAL = pMS_CTRL->Q12I_BEMF_ADC_tmp[ADC_VAL_Table[pMS_CTRL->Sector][1]];
    pMS_CURRENT->_I_Q12I_BEMF_OF_VAL = pMS_CTRL->Q12I_BEMF_ADC_tmp[ADC_VAL_Table[pMS_CTRL->Sector][2]];
    
    switch(pMS_CTRL->Sector)
    {
        case sector_1:case sector_3:case sector_5:
        {
            if(Q16I_LFT_06(pMS_CURRENT->_I_Q12I_BEMF_ZI_VAL) < pMS_CURRENT->_P_Q06U_fall_tl
                                 *(pMS_CURRENT->_I_Q12I_BEMF_ON_VAL + pMS_CURRENT->_I_Q12I_BEMF_OF_VAL))
            {
                pMS_CURRENT->_V_Q32U_cnt++;
                if(pMS_CURRENT->_V_Q32U_cnt > pMS_CURRENT->_P_Q08U_filter)
                {
                    pMS_CURRENT->_V_Q32U_time_cnt = 0U;
                    pMS_CURRENT->_V_Q32U_cnt = 0U;
                    pMS_CTRL->SQ_Flow = SQUARE_CROSS_SUCC;
                }
            }
            else
            {
                pMS_CURRENT->_V_Q32U_time_cnt++;
                if(pMS_CURRENT->_V_Q32U_time_cnt > pMS_CURRENT->_P_Q16U_current_filter)
                {
                    pMS_CURRENT->_V_Q32U_time_cnt = 0U;
                    pMS_CTRL->STALL_CTRL._V_Q32U_current_cnt++;
                    pMS_CTRL->Sector = Last_Sector[pMS_CTRL->Sector];
                    pMS_CTRL->SQ_Flow = SQUARE_CROSS_ING;
                }
                pMS_CURRENT->_V_Q32U_cnt = 0U;
            }
            break;
        }
        case sector_2:case sector_4:case sector_6:
        {
            if(Q16I_LFT_06(pMS_CURRENT->_I_Q12I_BEMF_ZI_VAL) > pMS_CURRENT->_P_Q06U_rise_tl
                                  *(pMS_CURRENT->_I_Q12I_BEMF_ON_VAL + pMS_CURRENT->_I_Q12I_BEMF_OF_VAL))
            {
                pMS_CURRENT->_V_Q32U_cnt++;
                if(pMS_CURRENT->_V_Q32U_cnt > pMS_CURRENT->_P_Q08U_filter)
                {
                    pMS_CURRENT->_V_Q32U_time_cnt = 0U;
                    pMS_CURRENT->_V_Q32U_cnt = 0U;
                    pMS_CTRL->SQ_Flow = SQUARE_CROSS_SUCC;
                }
            }
            else
            {
                pMS_CURRENT->_V_Q32U_time_cnt++;
                if(pMS_CURRENT->_V_Q32U_time_cnt > pMS_CURRENT->_P_Q16U_current_filter)
                {
                    pMS_CURRENT->_V_Q32U_time_cnt = 0;
                    pMS_CTRL->STALL_CTRL._V_Q32U_current_cnt++;
                    pMS_CTRL->Sector = Last_Sector[pMS_CTRL->Sector];
                    pMS_CTRL->SQ_Flow = SQUARE_CROSS_ING;
                }
                pMS_CURRENT->_V_Q32U_cnt = 0;
            }
            break;
        }
        default:break;
    }
    
    if(pMS_CTRL->SQ_Flow == SQUARE_CROSS_SUCC)
    {
        if((pMS_CTRL->FL_Freq.Q16I_Filter_out > pMS_CURRENT->_P_Q14U_to_flux_freq))
        {
            pMS_CURRENT->_V_Q32U_switch_cnt++;
            if(pMS_CURRENT->_V_Q32U_switch_cnt > pMS_CURRENT->_P_Q16U_to_flux_num)
            {
                pMS_CURRENT->_V_Q32U_switch_cnt = 0U;
                pMS_CTRL->SW_Math = SWITCH_FLUX;
            }
        }
        else
        {
            pMS_CURRENT->_V_Q32U_switch_cnt = 0U;
        }
    }
}

/**********************************************************************************************
Function: MotorSQ_FLUX_Init
Description: 磁链换向初始化
Input: 无
Output: 无
Input_Output: 磁链换向指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_FLUX_Init(ST_MS_FLUX* pMS_FLUX)
{
    pMS_FLUX->_V_Q32U_cnt = 0U;
    pMS_FLUX->_V_Q32U_time_cnt = 0U;
    pMS_FLUX->_V_Q32U_switch_cnt = 0U;
}

/**********************************************************************************************
Function: MotorSQ_FLUX_Zero_Cross
Description: 磁链换向计算
Input: 无
Output: 无
Input_Output: 磁链换向指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_FLUX_Zero_Cross(ST_MS_FLUX* pMS_FLUX, ST_MS_CONTROL* pMS_CTRL)
{
    pMS_FLUX->_I_Q12I_BEMF_ON_VAL = pMS_CTRL->Q12I_BEMF_ADC_tmp[ADC_VAL_Table[pMS_CTRL->Sector][0]];
    pMS_FLUX->_I_Q12I_BEMF_ZI_VAL = pMS_CTRL->Q12I_BEMF_ADC_tmp[ADC_VAL_Table[pMS_CTRL->Sector][1]];
    pMS_FLUX->_I_Q12I_BEMF_OF_VAL = pMS_CTRL->Q12I_BEMF_ADC_tmp[ADC_VAL_Table[pMS_CTRL->Sector][2]];
    
    switch(pMS_CTRL->Sector)
    {
        case sector_1:case sector_3:case sector_5:
        {
            if(Q16I_LFT_06(pMS_FLUX->_I_Q12I_BEMF_ZI_VAL) < pMS_FLUX->_P_Q06U_fall_tl
                                 *(pMS_FLUX->_I_Q12I_BEMF_ON_VAL + pMS_FLUX->_I_Q12I_BEMF_OF_VAL))
            {
                pMS_FLUX->_V_Q32U_cnt++;
                if(pMS_FLUX->_V_Q32U_cnt > pMS_FLUX->_P_Q08U_filter)
                {
                    pMS_FLUX->_V_Q32U_cnt = 0U;
                    pMS_CTRL->SQ_Flow = SQUARE_CROSS_SUCC;
                }
            }
            else
            {
                pMS_FLUX->_V_Q32U_cnt = 0U;
            }
            break;
        }
        case sector_2:case sector_4:case sector_6:
        {
            if(Q16I_LFT_06(pMS_FLUX->_I_Q12I_BEMF_ZI_VAL) > pMS_FLUX->_P_Q06U_rise_tl
                                 *(pMS_FLUX->_I_Q12I_BEMF_ON_VAL + pMS_FLUX->_I_Q12I_BEMF_OF_VAL))
            {
                pMS_FLUX->_V_Q32U_cnt++;
                if(pMS_FLUX->_V_Q32U_cnt > pMS_FLUX->_P_Q08U_filter)
                {
                    pMS_FLUX->_V_Q32U_cnt = 0U;
                    pMS_CTRL->SQ_Flow = SQUARE_CROSS_SUCC;
                }
            }
            else
            {
                pMS_FLUX->_V_Q32U_cnt = 0U;
            }
            break;
        }
        default:break;
    }
    
    if(pMS_CTRL->SQ_Flow == SQUARE_CROSS_SUCC)
    {
        if(pMS_CTRL->FL_Freq.Q16I_Filter_out > pMS_FLUX->_P_Q14U_to_bemf_freq)
        {
            pMS_FLUX->_V_Q32U_time_cnt++;
            if(pMS_FLUX->_V_Q32U_time_cnt > pMS_FLUX->_P_Q16U_to_bemf_num)
            {
                pMS_FLUX->_V_Q32U_time_cnt = 0U;
                pMS_FLUX->_V_Q32U_switch_cnt = 0U;
                pMS_CTRL->SW_Math = SWITCH_BEMF;
            }
        }
        else
        {
            pMS_FLUX->_V_Q32U_time_cnt = 0U;
        }
    }
        
    if(pMS_CTRL->FL_Freq.Q16I_Filter_out < pMS_FLUX->_P_Q14U_to_current_freq)
    {
        pMS_FLUX->_V_Q32U_switch_cnt++;
        if(pMS_FLUX->_V_Q32U_switch_cnt > pMS_FLUX->_P_Q16U_to_current_num)
        {
            pMS_FLUX->_V_Q32U_time_cnt = 0U;
            pMS_FLUX->_V_Q32U_switch_cnt = 0U;
            pMS_CTRL->SW_Math = SWITCH_CURRENT;
        }
    }
    else
    {
        pMS_FLUX->_V_Q32U_switch_cnt = 0U;
    }
}

/**********************************************************************************************
Function: MotorSQ_BEMF_Init
Description: 反电动势换向初始化
Input: 无
Output: 无
Input_Output: 反电动势换向指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_BEMF_Init(ST_MS_BEMF* pMS_BEMF)
{
    pMS_BEMF->_V_Q32U_cnt = 0U;
    pMS_BEMF->_V_Q32U_time_cnt = 0U;
}

/**********************************************************************************************
Function: MotorSQ_BEMF_Zero_Cross
Description: 反电动势换向计算
Input: 无
Output: 无
Input_Output: 反电动势换向指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_BEMF_Zero_Cross(ST_MS_BEMF* pMS_BEMF, ST_MS_CONTROL* pMS_CTRL)
{
    pMS_BEMF->_I_Q12I_BEMF_ON_VAL = pMS_CTRL->Q12I_BEMF_ADC_tmp[ADC_VAL_Table[pMS_CTRL->Sector][0]];
    pMS_BEMF->_I_Q12I_BEMF_ZI_VAL = pMS_CTRL->Q12I_BEMF_ADC_tmp[ADC_VAL_Table[pMS_CTRL->Sector][1]];
    pMS_BEMF->_I_Q12I_BEMF_OF_VAL = pMS_CTRL->Q12I_BEMF_ADC_tmp[ADC_VAL_Table[pMS_CTRL->Sector][2]];
    
    switch(pMS_CTRL->Sector)
    {
        case sector_1:case sector_3:case sector_5:
        {
            if(Q16I_LFT_01(pMS_BEMF->_I_Q12I_BEMF_ZI_VAL) < pMS_BEMF->_I_Q12I_BEMF_ON_VAL + pMS_BEMF->_I_Q12I_BEMF_OF_VAL)
            {
                pMS_BEMF->_V_Q32U_cnt++;
                if(pMS_BEMF->_V_Q32U_cnt > pMS_BEMF->_P_Q08U_filter)
                {
                    pMS_BEMF->_V_Q32U_cnt = 0U;
                    pMS_CTRL->SQ_Flow = SQUARE_CROSS_SUCC;
                }
            }
            else
            {
                pMS_BEMF->_V_Q32U_cnt = 0U;
            }
            break;
        }
        case sector_2:case sector_4:case sector_6:
        {
            if(Q16I_LFT_01(pMS_BEMF->_I_Q12I_BEMF_ZI_VAL) > pMS_BEMF->_I_Q12I_BEMF_ON_VAL + pMS_BEMF->_I_Q12I_BEMF_OF_VAL)
            {
                pMS_BEMF->_V_Q32U_cnt++;
                if(pMS_BEMF->_V_Q32U_cnt > pMS_BEMF->_P_Q08U_filter)
                {
                    pMS_BEMF->_V_Q32U_cnt = 0U;
                    pMS_CTRL->SQ_Flow = SQUARE_CROSS_SUCC;
                }
            }
            else
            {
                pMS_BEMF->_V_Q32U_cnt = 0U;
            }
            break;
        }
        default:break;
    }
    
    if(pMS_CTRL->SQ_Flow == SQUARE_CROSS_SUCC)
    {
        if(pMS_CTRL->FL_Freq.Q16I_Filter_out < pMS_BEMF->_P_Q14U_to_flux_freq)
        {
            pMS_BEMF->_V_Q32U_time_cnt++;
            if(pMS_BEMF->_V_Q32U_time_cnt > pMS_BEMF->_P_Q16U_to_flux_num)
            {
                pMS_BEMF->_V_Q32U_time_cnt = 0U;
                pMS_CTRL->SW_Math = SWITCH_FLUX;
            }
        }
        else
        {
            pMS_BEMF->_V_Q32U_time_cnt = 0U;
        }
    }
}

/**********************************************************************************************
Function: MotorSQ_CMP_Init
Description: 比较器换向初始化
Input: 无
Output: 无
Input_Output: 比较器换向指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_CMP_Init(ST_MS_CMP* pMS_CMP)
{
    
}

/**********************************************************************************************
Function: MotorSQ_CMP_Zero_Cross
Description: 比较器换向计算
Input: 无
Output: 无
Input_Output: 比较器换向指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_CMP_Zero_Cross(ST_MS_CMP* pMS_CMP, ST_MS_CONTROL* pMS_CTRL)
{
    
}

/**********************************************************************************************
Function: MotorSQ_Freq_Cal_Init
Description: 频率计算初始化
Input: 无
Output: 无
Input_Output: 频率计算指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_Freq_Cal_Init(ST_FREQ_CAL* pFREQ_CAL)
{
    pFREQ_CAL->Flag.bit.b0_init = 0U;
    pFREQ_CAL->_V_Q32U_60_degree_cnt_last = 0U;
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[0] = 0U;
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[1] = 0U;
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[2] = 0U;
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[3] = 0U;
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[4] = 0U;
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[5] = 0U;
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[6] = 0U;
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[7] = 0U;
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[8] = 0U;
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[9] = 0U;
    pFREQ_CAL->_O_Q32U_60_degree_cnt = 0U;
}

/**********************************************************************************************
Function: MotorSQ_Freq_Cal
Description: 频率计算
Input: 无
Output: 无
Input_Output: 频率计算指针，方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_Freq_Cal(ST_FREQ_CAL* pFREQ_CAL, ST_MS_CONTROL* pMS_CTRL)
{
    if(pFREQ_CAL->_I_Q32U_time_count > pFREQ_CAL->_V_Q32U_60_degree_cnt_last)
    {
        pFREQ_CAL->_O_Q32U_60_degree_cnt = pFREQ_CAL->_I_Q32U_time_count - pFREQ_CAL->_V_Q32U_60_degree_cnt_last;
    }
    else
    {
        pFREQ_CAL->_O_Q32U_60_degree_cnt = (pFREQ_CAL->_P_Q32U_hall_tim_max_cnt - pFREQ_CAL->_V_Q32U_60_degree_cnt_last) + pFREQ_CAL->_I_Q32U_time_count;
    }
    
    if(pFREQ_CAL->Flag.bit.b0_init == 0U)
    {
        pFREQ_CAL->_O_Q32U_60_degree_cnt = pFREQ_CAL->_P_Q32U_hall_tim_max_cnt;
        pFREQ_CAL->Flag.bit.b0_init = 1U;
    }
    
    pFREQ_CAL->_V_Q32U_60_degree_cnt_last = pFREQ_CAL->_I_Q32U_time_count;
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[5] = pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[4];
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[4] = pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[3];
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[3] = pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[2];
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[2] = pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[1];
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[1] = pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[0];
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[0] = pFREQ_CAL->_O_Q32U_60_degree_cnt;
    
    pMS_CTRL->FL_Freq.Q16I_Filter_in = Q32I_RHT_10(pMS_CTRL->_P_Q32U_Freq_Scale*(pFREQ_CAL->_P_Q32U_hall_tim_freq/(
    pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[0] + pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[1]
    + pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[2] + pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[3]
    + pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[4] + pFREQ_CAL->_V_Q32U_60_degree_cnt_tmp[5])));
    
    Filter_Cal_T(&pMS_CTRL->FL_Freq);
    
    pMS_CTRL->Q32U_switch_cnt++;
}

/**********************************************************************************************
Function: MotorSQ_PWM_Freq_Switch_Init
Description: 载频控制初始化
Input: 无
Output: 无
Input_Output: 载频控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_PWM_Freq_Switch_Init(ST_PWM_CONTROL* pPWM_CTRL)
{
    pPWM_CTRL->Flag.all = 0U;
    pPWM_CTRL->Ramp_Duty.Q32I_Output = 0U;
    pPWM_CTRL->_O_Q16U_arr_set = pPWM_CTRL->_P_Q14U_low_pwm_freq;
}

/**********************************************************************************************
Function: MotorSQ_PWM_Freq_Switch
Description: 载频控制计算
Input: 无
Output: 无
Input_Output: 载频控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_PWM_Freq_Switch(ST_PWM_CONTROL* pPWM_CTRL)
{
    Q32U_   Q12I_duty_tmp = pPWM_CTRL->_P_Q12U_duty_max;
    
    if(Q12I_duty_tmp > pPWM_CTRL->_I_Q12I_duty_freq)
    {
        Q12I_duty_tmp = pPWM_CTRL->_I_Q12I_duty_freq;
    }
    if(Q12I_duty_tmp > pPWM_CTRL->_I_Q12I_duty_ibus)
    {
        Q12I_duty_tmp = pPWM_CTRL->_I_Q12I_duty_ibus;
    }
    if(Q12I_duty_tmp > pPWM_CTRL->_I_Q12I_duty_iphase)
    {
        Q12I_duty_tmp = pPWM_CTRL->_I_Q12I_duty_iphase;
    }
    
    pPWM_CTRL->Ramp_Duty.Q32I_Target = Q12I_duty_tmp;
    Ramp_Cal_T(&pPWM_CTRL->Ramp_Duty);
    pPWM_CTRL->_O_Q12I_duty_set = pPWM_CTRL->Ramp_Duty.Q32I_Output;
                    
    if(pPWM_CTRL->Flag.bit.b0_init == ING)
    {
        if(pPWM_CTRL->_O_Q12I_duty_set > pPWM_CTRL->_P_Q12U_low_to_high_duty)//低频启动
        {
            if(pPWM_CTRL->_O_Q16U_arr_set > pPWM_CTRL->_P_Q14U_high_pwm_freq)
            {
                pPWM_CTRL->_O_Q16U_arr_set = pPWM_CTRL->_P_Q12U_low_to_high_duty
                *pPWM_CTRL->_P_Q14U_low_pwm_freq/pPWM_CTRL->_O_Q12I_duty_set;
                
                if(pPWM_CTRL->_O_Q16U_arr_set > pPWM_CTRL->_P_Q14U_low_pwm_freq)
                {
                    pPWM_CTRL->_O_Q16U_arr_set = pPWM_CTRL->_P_Q14U_low_pwm_freq;
                }
                if(pPWM_CTRL->_O_Q16U_arr_set <= pPWM_CTRL->_P_Q14U_high_pwm_freq)
                {
                    if(pPWM_CTRL->_O_Q12I_duty_set > pPWM_CTRL->_P_Q12U_high_to_low_duty)//达到高占空比
                    {
                        pPWM_CTRL->Flag.bit.b0_init = SUCC;
                    }
                    pPWM_CTRL->_O_Q16U_arr_set = pPWM_CTRL->_P_Q14U_high_pwm_freq;
                }
            }            
        }
    }
    else
    {
        if(pPWM_CTRL->_O_Q12I_duty_set < pPWM_CTRL->_P_Q12U_high_to_low_duty)//高频运行
        {
            if(pPWM_CTRL->_O_Q16U_arr_set < pPWM_CTRL->_P_Q14U_low_pwm_freq)
            {
                pPWM_CTRL->_O_Q16U_arr_set = pPWM_CTRL->_P_Q12U_high_to_low_duty
                *pPWM_CTRL->_P_Q14U_high_pwm_freq/pPWM_CTRL->_O_Q12I_duty_set;
                
                if(pPWM_CTRL->_O_Q16U_arr_set >= pPWM_CTRL->_P_Q14U_low_pwm_freq)
                {
                    if(pPWM_CTRL->_O_Q12I_duty_set < pPWM_CTRL->_P_Q12U_low_to_high_duty)//达到低占空比
                    {
                        pPWM_CTRL->Flag.bit.b0_init = ING;
                    }
                    pPWM_CTRL->_O_Q16U_arr_set = pPWM_CTRL->_P_Q14U_low_pwm_freq;
                }
                if(pPWM_CTRL->_O_Q16U_arr_set < pPWM_CTRL->_P_Q14U_high_pwm_freq)
                {
                    pPWM_CTRL->_O_Q16U_arr_set = pPWM_CTRL->_P_Q14U_high_pwm_freq;
                }
            }    
        }
    }
    
    pPWM_CTRL->_O_Q16U_duty_final_val = Q32I_RHT_12(pPWM_CTRL->_O_Q12I_duty_set*pPWM_CTRL->_O_Q16U_arr_set);
}

/**********************************************************************************************
Function: MotorSQ_Stall_Check_Init
Description: 堵转检测初始化
Input: 无
Output: 无
Input_Output: 堵转检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_Stall_Check_Init(ST_STALL_CONTROL* pSTALL_CTRL, ST_MS_CONTROL* pMS_CTRL)
{
    pSTALL_CTRL->Flag.all = 0U;
    pSTALL_CTRL->_V_Q32U_current_cnt = 0U;
    pSTALL_CTRL->_V_Q32U_cnt = 0U;
    pSTALL_CTRL->_V_Q32U_switch_cnt = 0U;
    
    pMS_CTRL->Q32U_switch_cnt = 0U;
}

/**********************************************************************************************
Function: MotorSQ_Stall_Check
Description: 堵转检测计算
Input: 无
Output: 无
Input_Output: 堵转检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ MotorSQ_Stall_Check(ST_STALL_CONTROL* pSTALL_CTRL, ST_MS_CONTROL* pMS_CTRL)
{
    Q32U_ flag_tmp = ING;
    Q32U_ motor_switch_cnt_max = 0U;
    Q32U_ motor_switch_cnt_min = 0U;
    
    if(pMS_CTRL->SW_Math == SWITCH_CURRENT)
    {
        if(pSTALL_CTRL->_V_Q32U_current_cnt >= pSTALL_CTRL->_P_Q16U_current_error_time)
        {
            pSTALL_CTRL->_V_Q32U_current_cnt = 0U;
            flag_tmp = SUCC;
        }
    }
    else
    {
        motor_switch_cnt_max = pMS_CTRL->FREQ_CAL._V_Q32U_60_degree_cnt_tmp[0];
        motor_switch_cnt_min = pMS_CTRL->FREQ_CAL._V_Q32U_60_degree_cnt_tmp[0];
        for(Q08U_ i=1;i<6;i++)
        {
            if(motor_switch_cnt_max > pMS_CTRL->FREQ_CAL._V_Q32U_60_degree_cnt_tmp[i])
            {
                motor_switch_cnt_max = pMS_CTRL->FREQ_CAL._V_Q32U_60_degree_cnt_tmp[i];
            }
            if(motor_switch_cnt_min < pMS_CTRL->FREQ_CAL._V_Q32U_60_degree_cnt_tmp[i])
            {
                motor_switch_cnt_min = pMS_CTRL->FREQ_CAL._V_Q32U_60_degree_cnt_tmp[i];
            }
        }
        if(Q16I_LFT_06(motor_switch_cnt_min) < pSTALL_CTRL->_P_Q06U_switch_coeff*motor_switch_cnt_max)
        {
            flag_tmp = SUCC;
        }
    
        if(pMS_CTRL->Q32U_switch_cnt == pSTALL_CTRL->_V_Q32U_switch_cnt)
        {
            pSTALL_CTRL->_V_Q32U_cnt++;
            if(pSTALL_CTRL->_V_Q32U_cnt > pSTALL_CTRL->_P_Q16U_error_time)
            {
                pSTALL_CTRL->_V_Q32U_cnt = 0U;
                flag_tmp = SUCC;
            }
        }
        else
        {
            pSTALL_CTRL->_V_Q32U_cnt = 0U;
        }
    }
    
    pSTALL_CTRL->_V_Q32U_switch_cnt = pMS_CTRL->Q32U_switch_cnt;
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MotorSQ_Ibus_Cal
Description: 母线电流计算
Input: 无
Output: 无
Input_Output: 方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorSQ_Ibus_Cal(ST_MS_CONTROL* pMS_CTRL)
{
    if(pMS_CTRL->SQ_Flow != SQUARE_DIAG_ING)
    {
        pMS_CTRL->FL_Ibus.Q16I_Filter_in = Q32I_RHT_12(pMS_CTRL->PWM_CTRL._O_Q12I_duty_set*pMS_CTRL->Q14I_IPHASE_PU);
        Filter_Cal_T(&pMS_CTRL->FL_Ibus);
    }
}
