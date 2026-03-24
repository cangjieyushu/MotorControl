/**************************************************************************************************
*     File Name :                        MCSQ_BLDC.c
*     Library/Module Name :              MCSQ
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             无感方波源文件
**************************************************************************************************/

#include "MCSQ_BLDC.h"


EM_CHANNEL_NUM ADC_VAL_Table[6][3] = 
{
    U_CHANNEL_NUM, W_CHANNEL_NUM, V_CHANNEL_NUM, 
    U_CHANNEL_NUM, V_CHANNEL_NUM, W_CHANNEL_NUM,
    V_CHANNEL_NUM, U_CHANNEL_NUM, W_CHANNEL_NUM, 
    V_CHANNEL_NUM, W_CHANNEL_NUM, U_CHANNEL_NUM,
    W_CHANNEL_NUM, V_CHANNEL_NUM, U_CHANNEL_NUM, 
    W_CHANNEL_NUM, U_CHANNEL_NUM, V_CHANNEL_NUM,
};

EM_SECTOR_NUM Position_Sector[6][2] = {sector_3, sector_6,
                                       sector_4, sector_1,
                                       sector_5, sector_2,
                                       sector_6, sector_3,
                                       sector_1, sector_4,
                                       sector_2, sector_5};

EM_SECTOR_NUM Last_Sector[6] = {sector_6, sector_1, sector_2, sector_3, sector_4, sector_5};
EM_SECTOR_NUM Next_Sector[6] = {sector_2, sector_3, sector_4, sector_5, sector_6, sector_1};


/**********************************************************************************************
Function: MCSQ_Init
Description: 方波算法初始化
Input: 无
Output: 无
Input_Output: 方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_Init(ST_MCSQ_CONTROL* pMS_CTRL)
{
    pMS_CTRL->MCSQ_BLDC.SW_Math = SWITCH_FLUX;
    pMS_CTRL->MCSQ_BLDC.SQ_Flow = SQUARE_CROSS_ING;
    pMS_CTRL->MCSQ_BLDC.DIR_Set = pMS_CTRL->MCSQ_BLDC.DIR_Target;
    
    pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_last = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[0] = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[1] = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[2] = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[3] = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[4] = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[5] = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal._O_Q32U_Switch_cnt = 0U;
    
    LPF_Init_T(&pMS_CTRL->MCSQ_BLDC.FL_Iphase, 0);
    LPF_Init_T(&pMS_CTRL->MCSQ_BLDC.FL_Freq, 0);
    LPF_Init_T(&pMS_CTRL->MCSQ_BLDC.FL_Ibus, 0);
    
    pMS_CTRL->MCSQ_BLDC._V_Q12U_Iphase_ADC_Offset = 0U;
    
    pMS_CTRL->MCSQ_OFFSET._V_Q32U_Offset_Check_cnt = 0U;
    
    pMS_CTRL->MCSQ_FLYING._V_Q32U_Flying_Low_Bemf_cnt = 0U;
    pMS_CTRL->MCSQ_FLYING._P_Q16U_Flying_Check_cnt = 0U;
    pMS_CTRL->MCSQ_FLYING._P_Q16U_Flying_Phase_cnt = 0U;
    
    pMS_CTRL->MCSQ_BOOT._V_Q32U_Boot_Low_Bemf_cnt = 0U;
    
    pMS_CTRL->MCSQ_POSITION._V_Q32U_Position_cnt = 0U;
    
    pMS_CTRL->MCSQ_BRAKE._O_Q32U_Brake_Finish_Flag = 0U;
    pMS_CTRL->MCSQ_BRAKE._O_Q14U_Brake_Duty_Set = 0U;
    pMS_CTRL->MCSQ_BRAKE._V_Q32U_Brake_cnt = 0U;
    
    pMS_CTRL->MCSQ_DIAG._V_Q32U_DIAG_cnt = 0U;
    pMS_CTRL->MCSQ_FLUX._V_Q32U_Flux_cnt = 0U;
    pMS_CTRL->MCSQ_FLUX._V_Q32U_Flux_to_Bemf_cnt = 0U;
    pMS_CTRL->MCSQ_BEMF._V_Q32U_Bemf_cnt = 0U;
    pMS_CTRL->MCSQ_BEMF._V_Q32U_Bemf_to_Flux_cnt = 0U;
    
    Ramp_Init_T(&pMS_CTRL->Ramp_Freq, pMS_CTRL->Ramp_Freq.Q14I_Init);
    PID_Inc_Init_T(&pMS_CTRL->PID_Freq, pMS_CTRL->PWM_CTRL._P_Q14U_Duty_Min);
    PID_Inc_Init_T(&pMS_CTRL->PID_Ibus, pMS_CTRL->PWM_CTRL._P_Q14U_Duty_Max);
    PID_Inc_Init_T(&pMS_CTRL->PID_Iphase, pMS_CTRL->PWM_CTRL._P_Q14U_Duty_Max);
    
    Ramp_Init_T(&pMS_CTRL->PWM_CTRL.Ramp_Duty, pMS_CTRL->PWM_CTRL.Ramp_Duty.Q14I_Init);
    pMS_CTRL->PWM_CTRL.PWM_Freq_Flag = 0U;
    pMS_CTRL->PWM_CTRL._O_Q32U_PWMCount_Set = pMS_CTRL->PWM_CTRL._P_Q32U_Low_PWMCount;
    
    pMS_CTRL->STALL_CTRL._V_Q32U_Stall_cnt = 0U;
}

/**********************************************************************************************
Function: MCSQ_Flying_Init
Description: 顺风启动初始化
Input: 无
Output: 无
Input_Output: 方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_Flying_Init(ST_MCSQ_CONTROL* pMS_CTRL)
{
    pMS_CTRL->MCSQ_BLDC.SW_Math = SWITCH_BEMF;
    pMS_CTRL->MCSQ_BLDC.SQ_Flow = SQUARE_CROSS_ING;
    pMS_CTRL->PWM_CTRL.PWM_Freq_Flag = SUCS;
    
    pMS_CTRL->MCSQ_BLDC.FL_Freq.Q14I_LPF_In = Q32I_RHT_14(pMS_CTRL->MCSQ_BLDC._P_Q28U_Freq_Scale*(pMS_CTRL->MCSQ_BLDC.Freq_Cal._P_Q32U_Hall_Time_Freq/(
    pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[0] + pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[1]
    + pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[2] + pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[3]
    + pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[4] + pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[5])));
    
    pMS_CTRL->PWM_CTRL._O_Q32U_Duty_PWMCount = ((pMS_CTRL->PWM_CTRL._P_Q14U_Duty_Max*pMS_CTRL->MCSQ_BLDC.FL_Freq.Q14I_LPF_In
    /pMS_CTRL->PWM_CTRL._P_Q14U_Motor_Freq_Max)*pMS_CTRL->MCSQ_BLDC._P_Q14U_Vbus_Max_pu)/pMS_CTRL->MCSQ_BLDC._V_Q14U_Vbus_pu;
    
    Ramp_Init_T(&pMS_CTRL->Ramp_Freq, pMS_CTRL->MCSQ_BLDC.FL_Freq.Q14I_LPF_In);
    
    PID_Inc_Init_T(&pMS_CTRL->PID_Iphase, pMS_CTRL->PWM_CTRL._O_Q32U_Duty_PWMCount);
    PID_Inc_Init_T(&pMS_CTRL->PID_Freq, pMS_CTRL->PWM_CTRL._O_Q32U_Duty_PWMCount);
    PID_Inc_Init_T(&pMS_CTRL->PID_Ibus, pMS_CTRL->PWM_CTRL._O_Q32U_Duty_PWMCount);
    
    Ramp_Init_T(&pMS_CTRL->PWM_CTRL.Ramp_Duty, pMS_CTRL->PWM_CTRL._O_Q32U_Duty_PWMCount);
    
    LPF_Init_T(&pMS_CTRL->MCSQ_BLDC.FL_Freq, pMS_CTRL->MCSQ_BLDC.FL_Freq.Q14I_LPF_In);
    
    pMS_CTRL->PWM_CTRL._I_Q14U_Duty_Freq = pMS_CTRL->PWM_CTRL._O_Q32U_Duty_PWMCount;
    pMS_CTRL->PWM_CTRL._I_Q14U_Duty_Ibus = pMS_CTRL->PWM_CTRL._O_Q32U_Duty_PWMCount;
    pMS_CTRL->PWM_CTRL._I_Q14U_Duty_Iphase = pMS_CTRL->PWM_CTRL._O_Q32U_Duty_PWMCount;
    pMS_CTRL->PWM_CTRL._O_Q14U_Duty_Set = pMS_CTRL->PWM_CTRL._O_Q32U_Duty_PWMCount;
    pMS_CTRL->PWM_CTRL._O_Q32U_PWMCount_Set = pMS_CTRL->PWM_CTRL._P_Q32U_High_PWMCount;
    
    pMS_CTRL->PWM_CTRL._O_Q32U_Duty_PWMCount = Q32I_RHT_14(pMS_CTRL->PWM_CTRL._O_Q14U_Duty_Set*pMS_CTRL->PWM_CTRL._O_Q32U_PWMCount_Set);
}

/**********************************************************************************************
Function: MCSQ_Freq_Cal
Description: 频率计算
Input: 无
Output: 无
Input_Output: 频率计算指针，方波控制指针，换相定时器
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_Freq_Cal(ST_FREQ_CAL* pFREQ_CAL, ST_MCSQ_CONTROL* pMS_CTRL, Q32U_ Q32U_Time_Count)
{
    if(Q32U_Time_Count > pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_last)
    {
        pFREQ_CAL->_V_Q32U_60Deg_Time_cnt = Q32U_Time_Count - pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_last;
    }
    else
    {
        pFREQ_CAL->_V_Q32U_60Deg_Time_cnt = (pFREQ_CAL->_P_Q32U_Hall_Time_Max_count - pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_last) + Q32U_Time_Count;
    }
    
    pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_last = Q32U_Time_Count;
    pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[5] = pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[4];
    pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[4] = pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[3];
    pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[3] = pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[2];
    pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[2] = pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[1];
    pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[1] = pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[0];
    pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[0] = pFREQ_CAL->_V_Q32U_60Deg_Time_cnt;
    
    pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_Filter = 
     (pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[0] + pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[1]
    + pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[2] + pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[3]
    + pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[4] + pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_tmp[5]);
    
    pMS_CTRL->MCSQ_BLDC.FL_Freq.Q14I_LPF_In = Q32I_RHT_14(pMS_CTRL->MCSQ_BLDC._P_Q28U_Freq_Scale*(pFREQ_CAL->_P_Q32U_Hall_Time_Freq/pFREQ_CAL->_V_Q32U_60Deg_Time_cnt_Filter));
    
    LPF_Cal_T(&pMS_CTRL->MCSQ_BLDC.FL_Freq);
    
    pMS_CTRL->MCSQ_BLDC.Freq_Cal._O_Q32U_Switch_cnt++;
}

/**********************************************************************************************
Function: MCSQ_Ibus_Cal
Description: 母线电流计算
Input: 无
Output: 无
Input_Output: 方波控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_Ibus_Cal(ST_MCSQ_CONTROL* pMS_CTRL)
{
    if(pMS_CTRL->MCSQ_BLDC.SQ_Flow != SQUARE_DIAG_ING)
    {
        pMS_CTRL->MCSQ_BLDC.FL_Ibus.Q14I_LPF_In = Q32I_RHT_14(pMS_CTRL->PWM_CTRL._O_Q14U_Duty_Set*pMS_CTRL->MCSQ_BLDC._V_Q14U_Iphase_pu);
        LPF_Cal_T(&pMS_CTRL->MCSQ_BLDC.FL_Ibus);
    }
}

/**********************************************************************************************
Function: MCSQ_Offset_Check
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针，BLDC参数指针，电流采样输入
Return: 偏置检测状态，0：未完成，1：成功，2：失败
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCSQ_Offset_Check(ST_MCSQ_OFFSET* pOFFSET, ST_MCSQ_BLDC* pBLDC, Q32U_ Q32U_Iphase_adc_value)
{
    EM_FLAG_STATE flag_tmp = ING;
    
    pBLDC->_V_Q12U_Iphase_ADC_Offset += Q32U_Iphase_adc_value;
    pOFFSET->_V_Q32U_Offset_Check_cnt++;
    
    if(pOFFSET->_V_Q32U_Offset_Check_cnt == pOFFSET->_P_Q16U_Offset_Check_Count)
    {
        pBLDC->_V_Q12U_Iphase_ADC_Offset /= pOFFSET->_V_Q32U_Offset_Check_cnt;
        if((pBLDC->_V_Q12U_Iphase_ADC_Offset > pOFFSET->_P_Q12U_Offset_Max)
        || (pBLDC->_V_Q12U_Iphase_ADC_Offset < pOFFSET->_P_Q12U_Offset_Min))
        {
            flag_tmp = FAIL;
        }
        else
        {
            flag_tmp = SUCS;
        }
    }
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MCSQ_Flying_Check
Description: 顺风检测计算
Input: 无
Output: 无
Input_Output: 顺风检测指针，BLDC参数指针，换相定时器
Return: 顺风检测状态，0：未完成，1：成功，2：失败
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCSQ_Flying_Check(ST_MCSQ_FLYING* pFLYING, ST_MCSQ_BLDC* pBLDC, Q32U_ Q32U_Time_Count)
{
    EM_FLAG_STATE flag_tmp = ING;
    
    if((pBLDC->_V_Q12U_Bemf_ADC_tmp[0] < pFLYING->_P_Q32U_Flying_Low_Bemf_TL)
    && (pBLDC->_V_Q12U_Bemf_ADC_tmp[1] < pFLYING->_P_Q32U_Flying_Low_Bemf_TL)
    && (pBLDC->_V_Q12U_Bemf_ADC_tmp[2] < pFLYING->_P_Q32U_Flying_Low_Bemf_TL))
    {
        pFLYING->_V_Q32U_Flying_Low_Bemf_cnt++;
    }
    else
    {
        if((pBLDC->_V_Q12U_Bemf_ADC_tmp[0] > pBLDC->_V_Q12U_Bemf_ADC_tmp[1])
        && (pBLDC->_V_Q12U_Bemf_ADC_tmp[0] > pBLDC->_V_Q12U_Bemf_ADC_tmp[2]))
        {
            if(pBLDC->_V_Q12U_Bemf_ADC_tmp[1] > pBLDC->_V_Q12U_Bemf_ADC_tmp[2])
            {//UVW
                pBLDC->Sector = sector_3;
            }
            else
            {//UWV
                pBLDC->Sector = sector_2;
            }
        }
        else
        {
            if(pBLDC->_V_Q12U_Bemf_ADC_tmp[1] > pBLDC->_V_Q12U_Bemf_ADC_tmp[2])
            {
                if(pBLDC->_V_Q12U_Bemf_ADC_tmp[0] > pBLDC->_V_Q12U_Bemf_ADC_tmp[2])
                {//VUW
                    pBLDC->Sector = sector_4;
                }
                else
                {//VWU
                    pBLDC->Sector = sector_5;
                }
            }
            else
            {
                if(pBLDC->_V_Q12U_Bemf_ADC_tmp[0] > pBLDC->_V_Q12U_Bemf_ADC_tmp[1])
                {//WUV
                    pBLDC->Sector = sector_1;
                }
                else
                {//WVU
                    pBLDC->Sector = sector_6;
                }
            }
        }
        
        if(Next_Sector[pBLDC->Sector_Last] == pBLDC->Sector)
        {
            pFLYING->_P_Q16U_Flying_Check_cnt++;
            if(pFLYING->_P_Q16U_Flying_Check_cnt > pFLYING->_P_Q16U_Flying_Check_Filter)
            {
                pFLYING->_P_Q16U_Flying_Check_cnt = 0;
                if(pFLYING->_P_Q16U_Flying_Phase_cnt == 0U)
                { 
                    pBLDC->Freq_Cal._V_Q32U_60Deg_Time_cnt_last = Q32U_Time_Count;
                }
                else
                {
                    if(Q32U_Time_Count > pBLDC->Freq_Cal._V_Q32U_60Deg_Time_cnt_last)
                    {
                        pBLDC->Freq_Cal._V_Q32U_60Deg_Time_cnt = Q32U_Time_Count - pBLDC->Freq_Cal._V_Q32U_60Deg_Time_cnt_last;
                    }
                    else
                    {
                        pBLDC->Freq_Cal._V_Q32U_60Deg_Time_cnt = (pBLDC->Freq_Cal._P_Q32U_Hall_Time_Max_count - pBLDC->Freq_Cal._V_Q32U_60Deg_Time_cnt_last) + Q32U_Time_Count;
                    }
                    pBLDC->Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[pFLYING->_P_Q16U_Flying_Phase_cnt-1] = pBLDC->Freq_Cal._V_Q32U_60Deg_Time_cnt;
                    pBLDC->Freq_Cal._V_Q32U_60Deg_Time_cnt_last = Q32U_Time_Count;
                }
                if(pFLYING->_P_Q16U_Flying_Phase_cnt == 6U)
                {
                    flag_tmp = SUCS;
                }
                pFLYING->_P_Q16U_Flying_Phase_cnt++;
                pBLDC->Sector_Last = pBLDC->Sector;
            }
        }
        
        pFLYING->_V_Q32U_Flying_Low_Bemf_cnt = 0U;
    }
    
    if(pFLYING->_V_Q32U_Flying_Low_Bemf_cnt > pFLYING->_P_Q16U_Flying_Low_Bemf_Count)
    {
        flag_tmp = FAIL;
    }
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MCSQ_Boot_Check
Description: 自举控制计算
Input: 无
Output: 无
Input_Output: 自举控制指针，BLDC参数指针
Return: 自举检测状态，0：未完成，1：成功
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCSQ_Boot_Check(ST_MCSQ_BOOT* pMS_BOOT, ST_MCSQ_BLDC* pBLDC)
{
    EM_FLAG_STATE flag_tmp = ING;
    
    if((pBLDC->_V_Q12U_Bemf_ADC_tmp[0] < pMS_BOOT->_P_Q32U_Boot_Low_Bemf_TL)
    && (pBLDC->_V_Q12U_Bemf_ADC_tmp[1] < pMS_BOOT->_P_Q32U_Boot_Low_Bemf_TL)
    && (pBLDC->_V_Q12U_Bemf_ADC_tmp[2] < pMS_BOOT->_P_Q32U_Boot_Low_Bemf_TL))
    {
        pMS_BOOT->_V_Q32U_Boot_Low_Bemf_cnt++;
        if(pMS_BOOT->_V_Q32U_Boot_Low_Bemf_cnt == pMS_BOOT->_P_Q16U_Boot_Low_Bemf_Count)
        {
            flag_tmp = SUCS;
        }
    }
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MCSQ_Pluse_Positon
Description: 脉冲定位计算
Input: 无
Output: 无
Input_Output: 脉冲定位控制指针，BLDC参数指针，电流采样输入
Return: 脉冲定位检测状态，0：未完成，1：成功，2：失败
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCSQ_Pluse_Positon(ST_MCSQ_POSITION* pMS_POSITION, ST_MCSQ_BLDC* pBLDC, Q32U_ Q32U_Iphase_adc_value)
{
    EM_FLAG_STATE flag_tmp = ING;
    
    pMS_POSITION->_V_Q12U_Position_Iphase_ADC_tmp[pMS_POSITION->_V_Q32U_Position_cnt] = Q32U_Iphase_adc_value;
    
    switch(pMS_POSITION->_V_Q32U_Position_cnt)
    {
        case 0U:{pMS_POSITION->_V_Q32U_Position_cnt = 3U;break;}
        case 3U:{pMS_POSITION->_V_Q32U_Position_cnt = 1U;break;}
        case 1U:{pMS_POSITION->_V_Q32U_Position_cnt = 4U;break;}
        case 4U:{pMS_POSITION->_V_Q32U_Position_cnt = 2U;break;}
        case 2U:{pMS_POSITION->_V_Q32U_Position_cnt = 5U;break;}
        case 5U:{pMS_POSITION->_V_Q32U_Position_cnt = 6U;break;}
        default:break;
    }
        
    if(pMS_POSITION->_V_Q32U_Position_cnt == 6U)
    {
        Q16U_ max_tmp = pMS_POSITION->_V_Q12U_Position_Iphase_ADC_tmp[sector_1];
        Q08U_ max_index = sector_1;
        for(Q08U_ i=1U;i<6U;i++)
        {
            if(pMS_POSITION->_V_Q12U_Position_Iphase_ADC_tmp[i] > max_tmp)
            {
                max_index = i;
                max_tmp = pMS_POSITION->_V_Q12U_Position_Iphase_ADC_tmp[i];
            }
        }
        
        pBLDC->Sector = Position_Sector[max_index][pBLDC->DIR_Set];
        
        flag_tmp = SUCS;
        for(Q08U_ j=0U;j<6U;j++)
        {
            if(pMS_POSITION->_V_Q12U_Position_Iphase_ADC_tmp[j] < pMS_POSITION->_P_Q12U_Position_Iphase_TL)
            {
                flag_tmp = FAIL;
            }
        }
    }
    
    return flag_tmp;
}

/**********************************************************************************************
Function: MCSQ_Brake
Description: 刹车控制占空比计算
Input: 无
Output: 无
Input_Output: 刹车控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_Brake(ST_MCSQ_BRAKE* pBRAKE_CTRL)
{
    if(pBRAKE_CTRL->_V_Q32U_Brake_cnt <= pBRAKE_CTRL->_P_Q16U_NoBrake_Count)
    {
        pBRAKE_CTRL->_O_Q14U_Brake_Duty_Set = 0U;
        if(pBRAKE_CTRL->_V_Q32U_Brake_cnt == pBRAKE_CTRL->_P_Q16U_NoBrake_Count)
        {
            if(pBRAKE_CTRL->_P_Q16U_SlowBrake_Count > 0U)
            {
                Ramp_Init_T(&pBRAKE_CTRL->Ramp_Brake_Duty, pBRAKE_CTRL->Ramp_Brake_Duty.Q14I_Init);
            }
            else
            {
                if(pBRAKE_CTRL->_P_Q16U_ShortBrake_Count > 0U)
                {
                    pBRAKE_CTRL->_O_Q14U_Brake_Duty_Set = Q14U_MAX;
                }
            }
        }
    }
    else if(pBRAKE_CTRL->_V_Q32U_Brake_cnt <= pBRAKE_CTRL->_P_Q16U_NoBrake_Count + pBRAKE_CTRL->_P_Q16U_SlowBrake_Count)
    {
        Ramp_Cal_T(&pBRAKE_CTRL->Ramp_Brake_Duty);
        pBRAKE_CTRL->_O_Q14U_Brake_Duty_Set = pBRAKE_CTRL->Ramp_Brake_Duty.Q14I_Output;
    }
    else if(pBRAKE_CTRL->_V_Q32U_Brake_cnt <= pBRAKE_CTRL->_P_Q16U_NoBrake_Count + pBRAKE_CTRL->_P_Q16U_SlowBrake_Count + pBRAKE_CTRL->_P_Q16U_ShortBrake_Count)
    {
        pBRAKE_CTRL->_O_Q14U_Brake_Duty_Set = Q14U_MAX;
    }
    else
    {
        pBRAKE_CTRL->_O_Q32U_Brake_Finish_Flag = 1U;
        pBRAKE_CTRL->_V_Q32U_Brake_cnt = 0U;
    }
    
    pBRAKE_CTRL->_V_Q32U_Brake_cnt++;
}

/**********************************************************************************************
Function: MCSQ_DIAG
Description: 续流检测计算
Input: 无
Output: 无
Input_Output: 续流检测指针，BLDC参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_DIAG(ST_MS_DIAG* pMS_DIAG, ST_MCSQ_BLDC* pBLDC)
{ 
    pBLDC->_V_Q12U_Bemf_ZI_ADC = pBLDC->_V_Q12U_Bemf_ADC_tmp[ADC_VAL_Table[pBLDC->Sector][1]];
    
    switch(pBLDC->Sector)
    {
        case sector_1:case sector_3:case sector_5:
        {
            if(Q16I_LFT_14(pBLDC->_V_Q12U_Bemf_ZI_ADC) > pMS_DIAG->_P_Q14U_DIAG_Fall_tl*pBLDC->_V_Q12U_Vbus_ADC)
            {
                pMS_DIAG->_V_Q32U_DIAG_cnt++;
                if(pMS_DIAG->_V_Q32U_DIAG_cnt > pMS_DIAG->_P_Q16U_DIAG_Filter_Count)
                {
                    pMS_DIAG->_V_Q32U_DIAG_cnt = 0U;
                    pBLDC->SQ_Flow = SQUARE_CROSS_ING;
                }
            }
            else
            {
                pMS_DIAG->_V_Q32U_DIAG_cnt = 0U;
            }
            break;
        }
        case sector_2:case sector_4:case sector_6:
        {
            if(Q16I_LFT_14(pBLDC->_V_Q12U_Bemf_ZI_ADC) < pMS_DIAG->_P_Q14U_DIAG_Rise_tl*pBLDC->_V_Q12U_Vbus_ADC)
            {
                pMS_DIAG->_V_Q32U_DIAG_cnt++;
                if(pMS_DIAG->_V_Q32U_DIAG_cnt > pMS_DIAG->_P_Q16U_DIAG_Filter_Count)
                {
                    pMS_DIAG->_V_Q32U_DIAG_cnt = 0U;
                    pBLDC->SQ_Flow = SQUARE_CROSS_ING;
                }
            }
            else
            {
                pMS_DIAG->_V_Q32U_DIAG_cnt = 0U;
            }
            break;
        }
        default:break;
    }
}

/**********************************************************************************************
Function: MCSQ_FLUX
Description: 磁链换向计算
Input: 无
Output: 无
Input_Output: 磁链换向指针，BLDC参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_FLUX(ST_MS_FLUX* pMS_FLUX, ST_MCSQ_BLDC* pBLDC)
{
    pBLDC->_V_Q12U_Bemf_ON_ADC = pBLDC->_V_Q12U_Bemf_ADC_tmp[ADC_VAL_Table[pBLDC->Sector][0]];
    pBLDC->_V_Q12U_Bemf_ZI_ADC = pBLDC->_V_Q12U_Bemf_ADC_tmp[ADC_VAL_Table[pBLDC->Sector][1]];
    pBLDC->_V_Q12U_Bemf_OF_ADC = pBLDC->_V_Q12U_Bemf_ADC_tmp[ADC_VAL_Table[pBLDC->Sector][2]];
    
    switch(pBLDC->Sector)
    {
        case sector_1:case sector_3:case sector_5:
        {
            if(Q16I_LFT_14(pBLDC->_V_Q12U_Bemf_ZI_ADC) < pMS_FLUX->_P_Q14U_Flux_Fall_tl*(pBLDC->_V_Q12U_Bemf_ON_ADC + pBLDC->_V_Q12U_Bemf_OF_ADC))
            {
                pMS_FLUX->_V_Q32U_Flux_cnt++;
                if(pMS_FLUX->_V_Q32U_Flux_cnt > pMS_FLUX->_P_Q16U_Flux_Filter_Count)
                {
                    pMS_FLUX->_V_Q32U_Flux_cnt = 0U;
                    pBLDC->SQ_Flow = SQUARE_CROSS_SUCC;
                }
            }
            else
            {
                pMS_FLUX->_V_Q32U_Flux_cnt = 0U;
            }
            break;
        }
        case sector_2:case sector_4:case sector_6:
        {
            if(Q16I_LFT_14(pBLDC->_V_Q12U_Bemf_ZI_ADC) > pMS_FLUX->_P_Q14U_Flux_Rise_tl*(pBLDC->_V_Q12U_Bemf_ON_ADC + pBLDC->_V_Q12U_Bemf_OF_ADC))
            {
                pMS_FLUX->_V_Q32U_Flux_cnt++;
                if(pMS_FLUX->_V_Q32U_Flux_cnt > pMS_FLUX->_P_Q16U_Flux_Filter_Count)
                {
                    pMS_FLUX->_V_Q32U_Flux_cnt = 0U;
                    pBLDC->SQ_Flow = SQUARE_CROSS_SUCC;
                }
            }
            else
            {
                pMS_FLUX->_V_Q32U_Flux_cnt = 0U;
            }
            break;
        }
        default:break;
    }
    
    if(pBLDC->SQ_Flow == SQUARE_CROSS_SUCC)
    {
        if(pBLDC->FL_Freq.Q14I_LPF_Out > pMS_FLUX->_P_Q14U_Flux_to_Bemf_Freq)
        {
            pMS_FLUX->_V_Q32U_Flux_to_Bemf_cnt++;
            if(pMS_FLUX->_V_Q32U_Flux_to_Bemf_cnt > pMS_FLUX->_P_Q14U_Flux_to_Bemf_Count)
            {
                pMS_FLUX->_V_Q32U_Flux_to_Bemf_cnt = 0U;
                pBLDC->SW_Math = SWITCH_BEMF;
            }
        }
        else
        {
            pMS_FLUX->_V_Q32U_Flux_to_Bemf_cnt = 0U;
        }
    }
}

/**********************************************************************************************
Function: MCSQ_BEMF
Description: 反电动势换向计算
Input: 无
Output: 无
Input_Output: 反电动势换向指针，BLDC参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_BEMF(ST_MS_BEMF* pMS_BEMF, ST_MCSQ_BLDC* pBLDC)
{
    pBLDC->_V_Q12U_Bemf_ON_ADC = pBLDC->_V_Q12U_Bemf_ADC_tmp[ADC_VAL_Table[pBLDC->Sector][0]];
    pBLDC->_V_Q12U_Bemf_ZI_ADC = pBLDC->_V_Q12U_Bemf_ADC_tmp[ADC_VAL_Table[pBLDC->Sector][1]];
    pBLDC->_V_Q12U_Bemf_OF_ADC = pBLDC->_V_Q12U_Bemf_ADC_tmp[ADC_VAL_Table[pBLDC->Sector][2]];
    
    switch(pBLDC->Sector)
    {
        case sector_1:case sector_3:case sector_5:
        {
            if(Q16I_LFT_01(pBLDC->_V_Q12U_Bemf_ZI_ADC) < pBLDC->_V_Q12U_Bemf_ON_ADC + pBLDC->_V_Q12U_Bemf_OF_ADC)
            {
                pMS_BEMF->_V_Q32U_Bemf_cnt++;
                if(pMS_BEMF->_V_Q32U_Bemf_cnt > pMS_BEMF->_P_Q16U_Bemf_Filter_Count)
                {
                    pMS_BEMF->_V_Q32U_Bemf_cnt = 0U;
                    pBLDC->SQ_Flow = SQUARE_CROSS_SUCC;
                }
            }
            else
            {
                pMS_BEMF->_V_Q32U_Bemf_cnt = 0U;
            }
            break;
        }
        case sector_2:case sector_4:case sector_6:
        {
            if(Q16I_LFT_01(pBLDC->_V_Q12U_Bemf_ZI_ADC) > pBLDC->_V_Q12U_Bemf_ON_ADC + pBLDC->_V_Q12U_Bemf_OF_ADC)
            {
                pMS_BEMF->_V_Q32U_Bemf_cnt++;
                if(pMS_BEMF->_V_Q32U_Bemf_cnt > pMS_BEMF->_P_Q16U_Bemf_Filter_Count)
                {
                    pMS_BEMF->_V_Q32U_Bemf_cnt = 0U;
                    pBLDC->SQ_Flow = SQUARE_CROSS_SUCC;
                }
            }
            else
            {
                pMS_BEMF->_V_Q32U_Bemf_cnt = 0U;
            }
            break;
        }
        default:break;
    }
    
    if(pBLDC->SQ_Flow == SQUARE_CROSS_SUCC)
    {
        if(pBLDC->FL_Freq.Q14I_LPF_Out < pMS_BEMF->_P_Q14U_Bemf_to_Flux_Freq)
        {
            pMS_BEMF->_V_Q32U_Bemf_to_Flux_cnt++;
            if(pMS_BEMF->_V_Q32U_Bemf_to_Flux_cnt > pMS_BEMF->_P_Q14U_Bemf_to_Flux_Count)
            {
                pMS_BEMF->_V_Q32U_Bemf_to_Flux_cnt = 0U;
                pBLDC->SW_Math = SWITCH_FLUX;
            }
        }
        else
        {
            pMS_BEMF->_V_Q32U_Bemf_to_Flux_cnt = 0U;
        }
    }
}

/**********************************************************************************************
Function: MCSQ_CMP
Description: 比较器换向计算
Input: 无
Output: 无
Input_Output: 比较器换向指针，BLDC参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_CMP(ST_MS_CMP* pMS_CMP, ST_MCSQ_BLDC* pBLDC)
{
    
}

/**********************************************************************************************
Function: MCSQ_PWM_Freq_Switch
Description: 载频控制计算
Input: 无
Output: 无
Input_Output: 载频控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCSQ_PWM_Freq_Switch(ST_PWM_CONTROL* pPWM_CTRL)
{
    Q32U_   Q14I_duty_tmp = pPWM_CTRL->_P_Q14U_Duty_Max;
    
    if(Q14I_duty_tmp > pPWM_CTRL->_I_Q14U_Duty_Freq)
    {
        Q14I_duty_tmp = pPWM_CTRL->_I_Q14U_Duty_Freq;
    }
    if(Q14I_duty_tmp > pPWM_CTRL->_I_Q14U_Duty_Ibus)
    {
        Q14I_duty_tmp = pPWM_CTRL->_I_Q14U_Duty_Ibus;
    }
    if(Q14I_duty_tmp > pPWM_CTRL->_I_Q14U_Duty_Iphase)
    {
        Q14I_duty_tmp = pPWM_CTRL->_I_Q14U_Duty_Iphase;
    }
    
    pPWM_CTRL->Ramp_Duty.Q14I_Target = Q14I_duty_tmp;
    Ramp_Cal_T(&pPWM_CTRL->Ramp_Duty);
    pPWM_CTRL->_O_Q14U_Duty_Set = pPWM_CTRL->Ramp_Duty.Q14I_Output;
                    
    if(pPWM_CTRL->PWM_Freq_Flag == 0U)
    {
        if(pPWM_CTRL->_O_Q14U_Duty_Set > pPWM_CTRL->_P_Q14U_Low_to_High_Duty)//低频启动
        {
            pPWM_CTRL->_O_Q32U_PWMCount_Set = pPWM_CTRL->_P_Q14U_Low_to_High_Duty
                *pPWM_CTRL->_P_Q32U_Low_PWMCount/pPWM_CTRL->_O_Q14U_Duty_Set;
            
            if(pPWM_CTRL->_O_Q32U_PWMCount_Set > pPWM_CTRL->_P_Q32U_Low_PWMCount)
            {
                pPWM_CTRL->_O_Q32U_PWMCount_Set = pPWM_CTRL->_P_Q32U_Low_PWMCount;
            }
            if(pPWM_CTRL->_O_Q32U_PWMCount_Set <= pPWM_CTRL->_P_Q32U_High_PWMCount)
            {
                pPWM_CTRL->PWM_Freq_Flag = 1U;
                pPWM_CTRL->_O_Q32U_PWMCount_Set = pPWM_CTRL->_P_Q32U_High_PWMCount;
            }       
        }
        else
        {
            pPWM_CTRL->_O_Q32U_PWMCount_Set = pPWM_CTRL->_P_Q32U_Low_PWMCount;
        }
    }
    else
    {
        if(pPWM_CTRL->_O_Q14U_Duty_Set < pPWM_CTRL->_P_Q14U_High_to_Low_Duty)//高频运行
        {
            pPWM_CTRL->_O_Q32U_PWMCount_Set = pPWM_CTRL->_P_Q14U_High_to_Low_Duty
                *pPWM_CTRL->_P_Q32U_High_PWMCount/pPWM_CTRL->_O_Q14U_Duty_Set;
            
            if(pPWM_CTRL->_O_Q32U_PWMCount_Set >= pPWM_CTRL->_P_Q32U_Low_PWMCount)
            {
                pPWM_CTRL->PWM_Freq_Flag = 0U;
                pPWM_CTRL->_O_Q32U_PWMCount_Set = pPWM_CTRL->_P_Q32U_Low_PWMCount;
            }
            if(pPWM_CTRL->_O_Q32U_PWMCount_Set < pPWM_CTRL->_P_Q32U_High_PWMCount)
            {
                pPWM_CTRL->_O_Q32U_PWMCount_Set = pPWM_CTRL->_P_Q32U_High_PWMCount;
            } 
        }
        else
        {
            pPWM_CTRL->_O_Q32U_PWMCount_Set = pPWM_CTRL->_P_Q32U_High_PWMCount;
        }
    }
    
    pPWM_CTRL->_O_Q32U_Duty_PWMCount = Q32I_RHT_14(pPWM_CTRL->_O_Q14U_Duty_Set*pPWM_CTRL->_O_Q32U_PWMCount_Set);
}

/**********************************************************************************************
Function: MCSQ_Stall_Check
Description: 堵转检测计算
Input: 无
Output: 无
Input_Output: 堵转检测指针
Return: 堵转检测状态，0：未完成，1：堵转，2：正常
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCSQ_Stall_Check(ST_STALL_CONTROL* pSTALL_CTRL, ST_MCSQ_CONTROL* pMS_CTRL)
{
    EM_FLAG_STATE flag_tmp = ING;
    Q32U_ motor_switch_cnt_max = 0U;
    Q32U_ motor_switch_cnt_min = 0U;
    
    motor_switch_cnt_max = pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[0];
    motor_switch_cnt_min = pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[0];
    for(Q08U_ i=1;i<6;i++)
    {
        if(motor_switch_cnt_max < pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[i])
        {
            motor_switch_cnt_max = pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[i];
        }
        if(motor_switch_cnt_min > pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[i])
        {
            motor_switch_cnt_min = pMS_CTRL->MCSQ_BLDC.Freq_Cal._V_Q32U_60Deg_Time_cnt_tmp[i];
        }
    }
    
    if((Q16I_LFT_06(motor_switch_cnt_min) < pSTALL_CTRL->_P_Q06U_Stall_Switch_Coeff*motor_switch_cnt_max)
    && (pMS_CTRL->MCSQ_BLDC.Freq_Cal._O_Q32U_Switch_cnt>=12U))
    {
        flag_tmp = SUCS;
    }
    
    if(pMS_CTRL->MCSQ_BLDC.Freq_Cal._O_Q32U_Switch_cnt == pSTALL_CTRL->_V_Q32U_Stall_Switch_cnt)
    {
        pSTALL_CTRL->_V_Q32U_Stall_cnt++;
        if(pSTALL_CTRL->_V_Q32U_Stall_cnt > pSTALL_CTRL->_P_Q16U_Stall_Count)
        {
            pSTALL_CTRL->_V_Q32U_Stall_cnt = 0U;
            flag_tmp = SUCS;
        }
    }
    else
    {
        pSTALL_CTRL->_V_Q32U_Stall_cnt = 0U;
    }
    
     pSTALL_CTRL->_V_Q32U_Stall_Switch_cnt = pMS_CTRL->MCSQ_BLDC.Freq_Cal._O_Q32U_Switch_cnt;
    
    return flag_tmp;
}
