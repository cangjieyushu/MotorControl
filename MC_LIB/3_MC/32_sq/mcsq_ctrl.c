/*
*     File Name :                        mcsq_ctrl
*     Library/Module Name :              mcsq
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             无感方波
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "mcsq_ctrl.h"


/*-------------------------- 2. 变量 ---------------------------------*/
EM_CHANNEL_NUM ADC_VAL_Table[6][3] = 
{// 正端导通相     悬空相          负端导通相
    U_CHANNEL_NUM, W_CHANNEL_NUM, V_CHANNEL_NUM, 
    U_CHANNEL_NUM, V_CHANNEL_NUM, W_CHANNEL_NUM,
    V_CHANNEL_NUM, U_CHANNEL_NUM, W_CHANNEL_NUM, 
    V_CHANNEL_NUM, W_CHANNEL_NUM, U_CHANNEL_NUM,
    W_CHANNEL_NUM, V_CHANNEL_NUM, U_CHANNEL_NUM, 
    W_CHANNEL_NUM, U_CHANNEL_NUM, V_CHANNEL_NUM,
};

//转子定位转换至电压矢量输出             正转      反转
EM_SECTOR_NUM Position_Sector[6][2] = {sector_3, sector_6,
                                       sector_4, sector_1,
                                       sector_5, sector_2,
                                       sector_6, sector_3,
                                       sector_1, sector_4,
                                       sector_2, sector_5};

//扇区步进及回退
EM_SECTOR_NUM Last_Sector[6] = {sector_6, sector_1, sector_2, sector_3, sector_4, sector_5};
EM_SECTOR_NUM Next_Sector[6] = {sector_2, sector_3, sector_4, sector_5, sector_6, sector_1};


/*-------------------------- 3. 公有接口实现 -----------------------------*/
void MCSQ_Init(ST_MCSQ_CONTROL* pMS_CTRL)
{
    //MCSQ_BLDC初始化
    pMS_CTRL->MCSQ_BLDC.SW_Math = SWITCH_FLUX;
    pMS_CTRL->MCSQ_BLDC.SQ_Flow = SQUARE_CROSS_ING;
    pMS_CTRL->MCSQ_BLDC.DIR_Set = pMS_CTRL->MCSQ_BLDC.DIR_Target;
    
    pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_last = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[0] = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[1] = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[2] = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[3] = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[4] = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[5] = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_Filter = 0U;
    pMS_CTRL->MCSQ_BLDC.Freq_Cal.O_Q32U_Switch_cnt = 0U;
    
    LPF_Init_T(&pMS_CTRL->MCSQ_BLDC.FL_Iphase, 0);
    LPF_Init_T(&pMS_CTRL->MCSQ_BLDC.FL_Freq, 0);
    LPF_Init_T(&pMS_CTRL->MCSQ_BLDC.FL_Ibus, 0);
    
    pMS_CTRL->MCSQ_BLDC.V_Q12U_Bemf_ADC_tmp[0] = 0U;
    pMS_CTRL->MCSQ_BLDC.V_Q12U_Bemf_ADC_tmp[1] = 0U;
    pMS_CTRL->MCSQ_BLDC.V_Q12U_Bemf_ADC_tmp[2] = 0U;
    pMS_CTRL->MCSQ_BLDC.V_Q12U_Bemf_ON_ADC = 0U;
    pMS_CTRL->MCSQ_BLDC.V_Q12U_Bemf_ZI_ADC = 0U;
    pMS_CTRL->MCSQ_BLDC.V_Q12U_Bemf_OF_ADC = 0U;
    pMS_CTRL->MCSQ_BLDC.V_Q12U_Iphase_ADC = 0U;
    pMS_CTRL->MCSQ_BLDC.V_Q12U_Iphase_ADC_Offset = 0U;
    pMS_CTRL->MCSQ_BLDC.V_Q14U_Iphase_pu = 0U;
    pMS_CTRL->MCSQ_BLDC.V_Q14U_Vbus_pu = 0U;
    
    //MCSQ_OFFSET初始化
    pMS_CTRL->MCSQ_OFFSET.V_Q32U_Offset_Check_cnt = 0U;
    
    //MCSQ_FLYING初始化
    pMS_CTRL->MCSQ_FLYING.V_Q32U_Flying_Low_Bemf_cnt = 0U;
    pMS_CTRL->MCSQ_FLYING.V_Q16U_Flying_Check_cnt = 0U;
    pMS_CTRL->MCSQ_FLYING.V_Q16U_Flying_Phase_cnt = 0U;
    
    //MCSQ_BOOT初始化
    pMS_CTRL->MCSQ_BOOT.V_Q32U_Boot_Low_Bemf_cnt = 0U;
    
    //MCSQ_POSITION初始化
    pMS_CTRL->MCSQ_POSITION.V_Q12U_Position_Iphase_ADC_tmp[0] = 0U;
    pMS_CTRL->MCSQ_POSITION.V_Q12U_Position_Iphase_ADC_tmp[1] = 0U;
    pMS_CTRL->MCSQ_POSITION.V_Q12U_Position_Iphase_ADC_tmp[2] = 0U;
    pMS_CTRL->MCSQ_POSITION.V_Q12U_Position_Iphase_ADC_tmp[3] = 0U;
    pMS_CTRL->MCSQ_POSITION.V_Q12U_Position_Iphase_ADC_tmp[4] = 0U;
    pMS_CTRL->MCSQ_POSITION.V_Q12U_Position_Iphase_ADC_tmp[5] = 0U;
    pMS_CTRL->MCSQ_POSITION.V_Q32U_Position_cnt = 0U;
    pMS_CTRL->MCSQ_POSITION.V_Q14U_Position_Duty_PWMCount = 0U;
    
    //MCSQ_BRAKE初始化
    Ramp_Init_T(&pMS_CTRL->MCSQ_BRAKE.Ramp_Brake_Duty, pMS_CTRL->MCSQ_BRAKE.Ramp_Brake_Duty.P_Q14I_Init);
    pMS_CTRL->MCSQ_BRAKE.O_Q32U_Brake_Finish_Flag = 0U;
    pMS_CTRL->MCSQ_BRAKE.O_Q14U_Brake_Duty_Set = 0U;
    pMS_CTRL->MCSQ_BRAKE.V_Q32U_Brake_cnt = 0U;
    
    //换向初始化
    pMS_CTRL->MCSQ_DIAG.V_Q32U_DIAG_cnt = 0U;
    pMS_CTRL->MCSQ_FLUX.V_Q32U_Flux_cnt = 0U;
    pMS_CTRL->MCSQ_FLUX.V_Q32U_Flux_to_Bemf_cnt = 0U;
    pMS_CTRL->MCSQ_BEMF.V_Q32U_Bemf_cnt = 0U;
    pMS_CTRL->MCSQ_BEMF.V_Q32U_Bemf_to_Flux_cnt = 0U;
    pMS_CTRL->MCSQ_CMP.V_Q32U_temp = 0U;
    
    //控制初始化
    Ramp_Init_T(&pMS_CTRL->Ramp_Freq, pMS_CTRL->Ramp_Freq.P_Q14I_Init);
    PID_Inc_Init_T(&pMS_CTRL->PID_Freq, pMS_CTRL->PWM_CTRL.P_Q14U_Duty_Min);
    PID_Inc_Init_T(&pMS_CTRL->PID_Ibus, pMS_CTRL->PWM_CTRL.P_Q14U_Duty_Max);
    PID_Inc_Init_T(&pMS_CTRL->PID_Iphase, pMS_CTRL->PWM_CTRL.P_Q14U_Duty_Max);
    
    //PWM_CTRL初始化
    Ramp_Init_T(&pMS_CTRL->PWM_CTRL.Ramp_Duty, pMS_CTRL->PWM_CTRL.Ramp_Duty.P_Q14I_Init);
    pMS_CTRL->PWM_CTRL.PWM_Freq_Flag = 0U;
    pMS_CTRL->PWM_CTRL.I_Q14U_Duty_VR = 0U;
    pMS_CTRL->PWM_CTRL.I_Q14U_Duty_Freq = 0U;
    pMS_CTRL->PWM_CTRL.I_Q14U_Duty_Ibus = 0U;
    pMS_CTRL->PWM_CTRL.I_Q14U_Duty_Iphase = 0U;
    pMS_CTRL->PWM_CTRL.O_Q14U_Duty_Set = 0U;
    pMS_CTRL->PWM_CTRL.O_Q32U_Duty_PWMCount = 0U;
    pMS_CTRL->PWM_CTRL.O_Q32U_PWMCount_Set = pMS_CTRL->PWM_CTRL.P_Q32U_Low_PWMCount;
    
    //STALL_CTRL初始化
    pMS_CTRL->STALL_CTRL.V_Q32U_Stall_cnt = 0U;
    pMS_CTRL->STALL_CTRL.V_Q32U_Stall_Switch_cnt = 0U;
}

void MCSQ_Flying_Init(ST_MCSQ_CONTROL* pMS_CTRL)
{
    pMS_CTRL->MCSQ_BLDC.SW_Math = SWITCH_BEMF;
    pMS_CTRL->MCSQ_BLDC.SQ_Flow = SQUARE_CROSS_ING;
    
    pMS_CTRL->MCSQ_BLDC.FL_Freq.I_Q14I_LPF_In = Q32I_RHT_14(pMS_CTRL->MCSQ_BLDC.P_Q28U_Freq_Scale*(pMS_CTRL->MCSQ_BLDC.Freq_Cal.P_Q32U_Hall_Time_Freq/(
    pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[0] + pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[1]
    + pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[2] + pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[3]
    + pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[4] + pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[5])));
    
    pMS_CTRL->PWM_CTRL.O_Q32U_Duty_PWMCount = ((pMS_CTRL->PWM_CTRL.P_Q14U_Duty_Max*pMS_CTRL->MCSQ_BLDC.FL_Freq.I_Q14I_LPF_In
    /pMS_CTRL->PWM_CTRL.P_Q14U_Motor_Freq_Max)*pMS_CTRL->MCSQ_BLDC.P_Q14U_Vbus_Max_pu)/pMS_CTRL->MCSQ_BLDC.V_Q14U_Vbus_pu;
    
    Ramp_Init_T(&pMS_CTRL->Ramp_Freq, pMS_CTRL->MCSQ_BLDC.FL_Freq.I_Q14I_LPF_In);
    PID_Inc_Init_T(&pMS_CTRL->PID_Iphase, pMS_CTRL->PWM_CTRL.O_Q32U_Duty_PWMCount);
    PID_Inc_Init_T(&pMS_CTRL->PID_Freq, pMS_CTRL->PWM_CTRL.O_Q32U_Duty_PWMCount);
    PID_Inc_Init_T(&pMS_CTRL->PID_Ibus, pMS_CTRL->PWM_CTRL.O_Q32U_Duty_PWMCount);
    
    Ramp_Init_T(&pMS_CTRL->PWM_CTRL.Ramp_Duty, pMS_CTRL->PWM_CTRL.O_Q32U_Duty_PWMCount);
    
    LPF_Init_T(&pMS_CTRL->MCSQ_BLDC.FL_Freq, pMS_CTRL->MCSQ_BLDC.FL_Freq.I_Q14I_LPF_In);
    
    pMS_CTRL->PWM_CTRL.PWM_Freq_Flag = SUCS;
    pMS_CTRL->PWM_CTRL.I_Q14U_Duty_Freq = pMS_CTRL->PWM_CTRL.O_Q32U_Duty_PWMCount;
    pMS_CTRL->PWM_CTRL.I_Q14U_Duty_Ibus = pMS_CTRL->PWM_CTRL.O_Q32U_Duty_PWMCount;
    pMS_CTRL->PWM_CTRL.I_Q14U_Duty_Iphase = pMS_CTRL->PWM_CTRL.O_Q32U_Duty_PWMCount;
    pMS_CTRL->PWM_CTRL.O_Q14U_Duty_Set = pMS_CTRL->PWM_CTRL.O_Q32U_Duty_PWMCount;
    pMS_CTRL->PWM_CTRL.O_Q32U_PWMCount_Set = pMS_CTRL->PWM_CTRL.P_Q32U_High_PWMCount;
    
    pMS_CTRL->PWM_CTRL.O_Q32U_Duty_PWMCount = Q32I_RHT_14(pMS_CTRL->PWM_CTRL.O_Q14U_Duty_Set*pMS_CTRL->PWM_CTRL.O_Q32U_PWMCount_Set);
}

void MCSQ_Freq_Cal(ST_MCSQ_BLDC* pBLDC, Q32U_ Q32U_Time_Count)
{
    ST_FREQ_CAL* pFREQ_CAL = &pBLDC->Freq_Cal;
    
    if(Q32U_Time_Count > pFREQ_CAL->V_Q32U_60Deg_Time_cnt_last)
    {
        pFREQ_CAL->V_Q32U_60Deg_Time_cnt = Q32U_Time_Count - pFREQ_CAL->V_Q32U_60Deg_Time_cnt_last;
    }
    else
    {
        pFREQ_CAL->V_Q32U_60Deg_Time_cnt = (pFREQ_CAL->P_Q32U_Hall_Time_Max_count - pFREQ_CAL->V_Q32U_60Deg_Time_cnt_last) + Q32U_Time_Count;
    }
    
    pFREQ_CAL->V_Q32U_60Deg_Time_cnt_last = Q32U_Time_Count;
    pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[5] = pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[4];
    pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[4] = pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[3];
    pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[3] = pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[2];
    pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[2] = pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[1];
    pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[1] = pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[0];
    pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[0] = pFREQ_CAL->V_Q32U_60Deg_Time_cnt;
    
    pFREQ_CAL->V_Q32U_60Deg_Time_cnt_Filter = 
     (pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[0] + pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[1]
    + pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[2] + pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[3]
    + pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[4] + pFREQ_CAL->V_Q32U_60Deg_Time_cnt_tmp[5]);
    
    pBLDC->FL_Freq.I_Q14I_LPF_In = Q32I_RHT_14(pBLDC->P_Q28U_Freq_Scale*(pFREQ_CAL->P_Q32U_Hall_Time_Freq/pFREQ_CAL->V_Q32U_60Deg_Time_cnt_Filter));
    
    LPF_Cal_T(&pBLDC->FL_Freq);
    
    pBLDC->Freq_Cal.O_Q32U_Switch_cnt++;
}

void MCSQ_Ibus_Cal(ST_MCSQ_CONTROL* pMS_CTRL)
{
    if(pMS_CTRL->MCSQ_BLDC.SQ_Flow != SQUARE_DIAG_ING)
    {
        pMS_CTRL->MCSQ_BLDC.FL_Ibus.I_Q14I_LPF_In = Q32I_RHT_14(pMS_CTRL->PWM_CTRL.O_Q14U_Duty_Set*pMS_CTRL->MCSQ_BLDC.V_Q14U_Iphase_pu);
        LPF_Cal_T(&pMS_CTRL->MCSQ_BLDC.FL_Ibus);
    }
}

EM_FLAG_STATE MCSQ_Offset_Check(ST_MCSQ_OFFSET* pOFFSET, ST_MCSQ_BLDC* pBLDC, Q32U_ Q32U_Iphase_adc_value)
{
    EM_FLAG_STATE flag_tmp = ING;
    
    pBLDC->V_Q12U_Iphase_ADC_Offset += Q32U_Iphase_adc_value;
    pOFFSET->V_Q32U_Offset_Check_cnt++;
    
    if(pOFFSET->V_Q32U_Offset_Check_cnt == pOFFSET->P_Q16U_Offset_Check_Count)
    {
        pBLDC->V_Q12U_Iphase_ADC_Offset /= pOFFSET->V_Q32U_Offset_Check_cnt;
        if((pBLDC->V_Q12U_Iphase_ADC_Offset > pOFFSET->P_Q12U_Offset_Max)
        || (pBLDC->V_Q12U_Iphase_ADC_Offset < pOFFSET->P_Q12U_Offset_Min))
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

EM_FLAG_STATE MCSQ_Flying_Check(ST_MCSQ_FLYING* pFLYING, ST_MCSQ_BLDC* pBLDC, Q32U_ Q32U_Time_Count)
{
    EM_FLAG_STATE flag_tmp = ING;
    
    if((pBLDC->V_Q12U_Bemf_ADC_tmp[0] < pFLYING->P_Q32U_Flying_Low_Bemf_TL)
    && (pBLDC->V_Q12U_Bemf_ADC_tmp[1] < pFLYING->P_Q32U_Flying_Low_Bemf_TL)
    && (pBLDC->V_Q12U_Bemf_ADC_tmp[2] < pFLYING->P_Q32U_Flying_Low_Bemf_TL))
    {
        pFLYING->V_Q32U_Flying_Low_Bemf_cnt++;
    }
    else
    {
        if((pBLDC->V_Q12U_Bemf_ADC_tmp[0] > pBLDC->V_Q12U_Bemf_ADC_tmp[1])
        && (pBLDC->V_Q12U_Bemf_ADC_tmp[0] > pBLDC->V_Q12U_Bemf_ADC_tmp[2]))
        {
            if(pBLDC->V_Q12U_Bemf_ADC_tmp[1] > pBLDC->V_Q12U_Bemf_ADC_tmp[2])
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
            if(pBLDC->V_Q12U_Bemf_ADC_tmp[1] > pBLDC->V_Q12U_Bemf_ADC_tmp[2])
            {
                if(pBLDC->V_Q12U_Bemf_ADC_tmp[0] > pBLDC->V_Q12U_Bemf_ADC_tmp[2])
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
                if(pBLDC->V_Q12U_Bemf_ADC_tmp[0] > pBLDC->V_Q12U_Bemf_ADC_tmp[1])
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
            pFLYING->V_Q16U_Flying_Check_cnt++;
            if(pFLYING->V_Q16U_Flying_Check_cnt > pFLYING->P_Q16U_Flying_Check_Filter)
            {
                pFLYING->V_Q16U_Flying_Check_cnt = 0;
                if(pFLYING->V_Q16U_Flying_Phase_cnt == 0U)
                { 
                    pBLDC->Freq_Cal.V_Q32U_60Deg_Time_cnt_last = Q32U_Time_Count;
                }
                else
                {
                    if(Q32U_Time_Count > pBLDC->Freq_Cal.V_Q32U_60Deg_Time_cnt_last)
                    {
                        pBLDC->Freq_Cal.V_Q32U_60Deg_Time_cnt = Q32U_Time_Count - pBLDC->Freq_Cal.V_Q32U_60Deg_Time_cnt_last;
                    }
                    else
                    {
                        pBLDC->Freq_Cal.V_Q32U_60Deg_Time_cnt = (pBLDC->Freq_Cal.P_Q32U_Hall_Time_Max_count - pBLDC->Freq_Cal.V_Q32U_60Deg_Time_cnt_last) + Q32U_Time_Count;
                    }
                    pBLDC->Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[pFLYING->V_Q16U_Flying_Phase_cnt-1] = pBLDC->Freq_Cal.V_Q32U_60Deg_Time_cnt;
                    pBLDC->Freq_Cal.V_Q32U_60Deg_Time_cnt_last = Q32U_Time_Count;
                }
                if(pFLYING->V_Q16U_Flying_Phase_cnt == 6U)
                {
                    flag_tmp = SUCS;
                }
                pFLYING->V_Q16U_Flying_Phase_cnt++;
                pBLDC->Sector_Last = pBLDC->Sector;
            }
        }
        
        pFLYING->V_Q32U_Flying_Low_Bemf_cnt = 0U;
    }
    
    if(pFLYING->V_Q32U_Flying_Low_Bemf_cnt > pFLYING->P_Q16U_Flying_Low_Bemf_Count)
    {
        flag_tmp = FAIL;
    }
    
    pFLYING->V_Q32U_Flying_Fail_cnt++;
    if(pFLYING->V_Q32U_Flying_Fail_cnt > pFLYING->P_Q16U_Flying_Fail_Count)
    {
        flag_tmp = FAIL;
    }
    
    return flag_tmp;
}

EM_FLAG_STATE MCSQ_Boot_Check(ST_MCSQ_BOOT* pMS_BOOT, ST_MCSQ_BLDC* pBLDC)
{
    EM_FLAG_STATE flag_tmp = ING;
    
    if((pBLDC->V_Q12U_Bemf_ADC_tmp[0] < pMS_BOOT->P_Q32U_Boot_Low_Bemf_TL)
    && (pBLDC->V_Q12U_Bemf_ADC_tmp[1] < pMS_BOOT->P_Q32U_Boot_Low_Bemf_TL)
    && (pBLDC->V_Q12U_Bemf_ADC_tmp[2] < pMS_BOOT->P_Q32U_Boot_Low_Bemf_TL))
    {
        pMS_BOOT->V_Q32U_Boot_Low_Bemf_cnt++;
        if(pMS_BOOT->V_Q32U_Boot_Low_Bemf_cnt == pMS_BOOT->P_Q16U_Boot_Low_Bemf_Count)
        {
            flag_tmp = SUCS;
        }
    }
    
    pMS_BOOT->V_Q32U_Boot_Fail_cnt++;
    if(pMS_BOOT->V_Q32U_Boot_Fail_cnt == pMS_BOOT->P_Q16U_Boot_Fail_Count)
    {
        flag_tmp = SUCS;
    }
        
    return flag_tmp;
}

EM_FLAG_STATE MCSQ_Pluse_Positon(ST_MCSQ_POSITION* pMS_POSITION, ST_MCSQ_BLDC* pBLDC, Q32U_ Q32U_Iphase_adc_value)
{
    EM_FLAG_STATE flag_tmp = ING;
    
    pMS_POSITION->V_Q12U_Position_Iphase_ADC_tmp[pMS_POSITION->V_Q32U_Position_cnt] = Q32U_Iphase_adc_value;
    
    switch(pMS_POSITION->V_Q32U_Position_cnt)
    {
        case 0U:{pMS_POSITION->V_Q32U_Position_cnt = 3U;break;}
        case 3U:{pMS_POSITION->V_Q32U_Position_cnt = 1U;break;}
        case 1U:{pMS_POSITION->V_Q32U_Position_cnt = 4U;break;}
        case 4U:{pMS_POSITION->V_Q32U_Position_cnt = 2U;break;}
        case 2U:{pMS_POSITION->V_Q32U_Position_cnt = 5U;break;}
        case 5U:{pMS_POSITION->V_Q32U_Position_cnt = 6U;break;}
        default:break;
    }
        
    if(pMS_POSITION->V_Q32U_Position_cnt == 6U)
    {
        Q16U_ max_tmp = pMS_POSITION->V_Q12U_Position_Iphase_ADC_tmp[sector_1];
        Q08U_ max_index = sector_1;
        for(Q08U_ i=1U;i<6U;i++)
        {
            if(pMS_POSITION->V_Q12U_Position_Iphase_ADC_tmp[i] > max_tmp)
            {
                max_index = i;
                max_tmp = pMS_POSITION->V_Q12U_Position_Iphase_ADC_tmp[i];
            }
        }
        
        pBLDC->Sector = Position_Sector[max_index][pBLDC->DIR_Set];
        
        flag_tmp = SUCS;
        for(Q08U_ j=0U;j<6U;j++)
        {
            if(pMS_POSITION->V_Q12U_Position_Iphase_ADC_tmp[j] < pMS_POSITION->P_Q12U_Position_Iphase_TL)
            {
                flag_tmp = FAIL;
            }
        }
    }
    
    return flag_tmp;
}

void MCSQ_Brake(ST_MCSQ_BRAKE* pBRAKE_CTRL, ST_PWM_CONTROL* pPWM_CTRL)
{
    if(pBRAKE_CTRL->V_Q32U_Brake_cnt <= pBRAKE_CTRL->P_Q16U_NoBrake_Count)
    {
        pBRAKE_CTRL->O_Q14U_Brake_Duty_Set = 0U;
        if(pBRAKE_CTRL->V_Q32U_Brake_cnt == pBRAKE_CTRL->P_Q16U_NoBrake_Count)
        {
            if(pBRAKE_CTRL->P_Q16U_SlowBrake_Count > 0U)
            {
                Ramp_Init_T(&pBRAKE_CTRL->Ramp_Brake_Duty, pBRAKE_CTRL->Ramp_Brake_Duty.P_Q14I_Init);
            }
            else
            {
                if(pBRAKE_CTRL->P_Q16U_ShortBrake_Count > 0U)
                {
                    pBRAKE_CTRL->O_Q14U_Brake_Duty_Set = pPWM_CTRL->P_Q14U_Duty_Max;
                }
            }
        }
    }
    else if(pBRAKE_CTRL->V_Q32U_Brake_cnt <= pBRAKE_CTRL->P_Q16U_NoBrake_Count + pBRAKE_CTRL->P_Q16U_SlowBrake_Count)
    {
        Ramp_Cal_T(&pBRAKE_CTRL->Ramp_Brake_Duty);
        pBRAKE_CTRL->O_Q14U_Brake_Duty_Set = pBRAKE_CTRL->Ramp_Brake_Duty.O_Q14I_Output;
    }
    else if(pBRAKE_CTRL->V_Q32U_Brake_cnt <= pBRAKE_CTRL->P_Q16U_NoBrake_Count + pBRAKE_CTRL->P_Q16U_SlowBrake_Count + pBRAKE_CTRL->P_Q16U_ShortBrake_Count)
    {
        pBRAKE_CTRL->O_Q14U_Brake_Duty_Set = pPWM_CTRL->P_Q14U_Duty_Max;
    }
    else
    {
        pBRAKE_CTRL->O_Q32U_Brake_Finish_Flag = 1U;
        pBRAKE_CTRL->V_Q32U_Brake_cnt = 0U;
    }
    
    pBRAKE_CTRL->V_Q32U_Brake_cnt++;
}

void MCSQ_DIAG(ST_MS_DIAG* pMS_DIAG, ST_MCSQ_BLDC* pBLDC)
{ 
    pBLDC->V_Q12U_Bemf_ZI_ADC = pBLDC->V_Q12U_Bemf_ADC_tmp[ADC_VAL_Table[pBLDC->Sector][1]];
    
    switch(pBLDC->Sector)
    {
        case sector_1:case sector_3:case sector_5:
        {
            if(Q16I_LFT_14(pBLDC->V_Q12U_Bemf_ZI_ADC) > pMS_DIAG->P_Q14U_DIAG_Fall_tl*pBLDC->FL_Vbus_ADC.O_Q14I_LPF_Out)
            {
                pMS_DIAG->V_Q32U_DIAG_cnt++;
                if(pMS_DIAG->V_Q32U_DIAG_cnt > pMS_DIAG->P_Q16U_DIAG_Filter_Count)
                {
                    pMS_DIAG->V_Q32U_DIAG_cnt = 0U;
                    pBLDC->SQ_Flow = SQUARE_CROSS_ING;
                }
            }
            else
            {
                pMS_DIAG->V_Q32U_DIAG_cnt = 0U;
            }
            break;
        }
        case sector_2:case sector_4:case sector_6:
        {
            if(Q16I_LFT_14(pBLDC->V_Q12U_Bemf_ZI_ADC) < pMS_DIAG->P_Q14U_DIAG_Rise_tl*pBLDC->FL_Vbus_ADC.O_Q14I_LPF_Out)
            {
                pMS_DIAG->V_Q32U_DIAG_cnt++;
                if(pMS_DIAG->V_Q32U_DIAG_cnt > pMS_DIAG->P_Q16U_DIAG_Filter_Count)
                {
                    pMS_DIAG->V_Q32U_DIAG_cnt = 0U;
                    pBLDC->SQ_Flow = SQUARE_CROSS_ING;
                }
            }
            else
            {
                pMS_DIAG->V_Q32U_DIAG_cnt = 0U;
            }
            break;
        }
        default:break;
    }
}

void MCSQ_FLUX(ST_MS_FLUX* pMS_FLUX, ST_MCSQ_BLDC* pBLDC)
{
    pBLDC->V_Q12U_Bemf_ON_ADC = pBLDC->V_Q12U_Bemf_ADC_tmp[ADC_VAL_Table[pBLDC->Sector][0]];
    pBLDC->V_Q12U_Bemf_ZI_ADC = pBLDC->V_Q12U_Bemf_ADC_tmp[ADC_VAL_Table[pBLDC->Sector][1]];
    pBLDC->V_Q12U_Bemf_OF_ADC = pBLDC->V_Q12U_Bemf_ADC_tmp[ADC_VAL_Table[pBLDC->Sector][2]];
    
    switch(pBLDC->Sector)
    {
        case sector_1:case sector_3:case sector_5:
        {
            if(Q16I_LFT_14(pBLDC->V_Q12U_Bemf_ZI_ADC) < pMS_FLUX->P_Q14U_Flux_Fall_tl*(pBLDC->V_Q12U_Bemf_ON_ADC + pBLDC->V_Q12U_Bemf_OF_ADC))
            {
                pMS_FLUX->V_Q32U_Flux_cnt++;
                if(pMS_FLUX->V_Q32U_Flux_cnt > pMS_FLUX->P_Q16U_Flux_Filter_Count)
                {
                    pMS_FLUX->V_Q32U_Flux_cnt = 0U;
                    pBLDC->SQ_Flow = SQUARE_CROSS_SUCC;
                }
            }
            else
            {
                pMS_FLUX->V_Q32U_Flux_cnt = 0U;
            }
            break;
        }
        case sector_2:case sector_4:case sector_6:
        {
            if(Q16I_LFT_14(pBLDC->V_Q12U_Bemf_ZI_ADC) > pMS_FLUX->P_Q14U_Flux_Rise_tl*(pBLDC->V_Q12U_Bemf_ON_ADC + pBLDC->V_Q12U_Bemf_OF_ADC))
            {
                pMS_FLUX->V_Q32U_Flux_cnt++;
                if(pMS_FLUX->V_Q32U_Flux_cnt > pMS_FLUX->P_Q16U_Flux_Filter_Count)
                {
                    pMS_FLUX->V_Q32U_Flux_cnt = 0U;
                    pBLDC->SQ_Flow = SQUARE_CROSS_SUCC;
                }
            }
            else
            {
                pMS_FLUX->V_Q32U_Flux_cnt = 0U;
            }
            break;
        }
        default:break;
    }
    
    if(pBLDC->SQ_Flow == SQUARE_CROSS_SUCC)
    {
        if(pBLDC->FL_Freq.O_Q14I_LPF_Out > pMS_FLUX->P_Q14U_Flux_to_Bemf_Freq)
        {
            pMS_FLUX->V_Q32U_Flux_to_Bemf_cnt++;
            if(pMS_FLUX->V_Q32U_Flux_to_Bemf_cnt > pMS_FLUX->P_Q14U_Flux_to_Bemf_Count)
            {
                pMS_FLUX->V_Q32U_Flux_to_Bemf_cnt = 0U;
                pBLDC->SW_Math = SWITCH_BEMF;
            }
        }
        else
        {
            pMS_FLUX->V_Q32U_Flux_to_Bemf_cnt = 0U;
        }
    }
}

void MCSQ_BEMF(ST_MS_BEMF* pMS_BEMF, ST_MCSQ_BLDC* pBLDC)
{
    pBLDC->V_Q12U_Bemf_ON_ADC = pBLDC->V_Q12U_Bemf_ADC_tmp[ADC_VAL_Table[pBLDC->Sector][0]];
    pBLDC->V_Q12U_Bemf_ZI_ADC = pBLDC->V_Q12U_Bemf_ADC_tmp[ADC_VAL_Table[pBLDC->Sector][1]];
    pBLDC->V_Q12U_Bemf_OF_ADC = pBLDC->V_Q12U_Bemf_ADC_tmp[ADC_VAL_Table[pBLDC->Sector][2]];
    
    switch(pBLDC->Sector)
    {
        case sector_1:case sector_3:case sector_5:
        {
            if(Q16I_LFT_01(pBLDC->V_Q12U_Bemf_ZI_ADC) < pBLDC->V_Q12U_Bemf_ON_ADC + pBLDC->V_Q12U_Bemf_OF_ADC)
            {
                pMS_BEMF->V_Q32U_Bemf_cnt++;
                if(pMS_BEMF->V_Q32U_Bemf_cnt > pMS_BEMF->P_Q16U_Bemf_Filter_Count)
                {
                    pMS_BEMF->V_Q32U_Bemf_cnt = 0U;
                    pBLDC->SQ_Flow = SQUARE_CROSS_SUCC;
                }
            }
            else
            {
                pMS_BEMF->V_Q32U_Bemf_cnt = 0U;
            }
            break;
        }
        case sector_2:case sector_4:case sector_6:
        {
            if(Q16I_LFT_01(pBLDC->V_Q12U_Bemf_ZI_ADC) > pBLDC->V_Q12U_Bemf_ON_ADC + pBLDC->V_Q12U_Bemf_OF_ADC)
            {
                pMS_BEMF->V_Q32U_Bemf_cnt++;
                if(pMS_BEMF->V_Q32U_Bemf_cnt > pMS_BEMF->P_Q16U_Bemf_Filter_Count)
                {
                    pMS_BEMF->V_Q32U_Bemf_cnt = 0U;
                    pBLDC->SQ_Flow = SQUARE_CROSS_SUCC;
                }
            }
            else
            {
                pMS_BEMF->V_Q32U_Bemf_cnt = 0U;
            }
            break;
        }
        default:break;
    }
    
    if(pBLDC->SQ_Flow == SQUARE_CROSS_SUCC)
    {
        if(pBLDC->FL_Freq.O_Q14I_LPF_Out < pMS_BEMF->P_Q14U_Bemf_to_Flux_Freq)
        {
            pMS_BEMF->V_Q32U_Bemf_to_Flux_cnt++;
            if(pMS_BEMF->V_Q32U_Bemf_to_Flux_cnt > pMS_BEMF->P_Q14U_Bemf_to_Flux_Count)
            {
                pMS_BEMF->V_Q32U_Bemf_to_Flux_cnt = 0U;
                pBLDC->SW_Math = SWITCH_FLUX;
            }
        }
        else
        {
            pMS_BEMF->V_Q32U_Bemf_to_Flux_cnt = 0U;
        }
    }
}

void MCSQ_CMP(ST_MS_CMP* pMS_CMP, ST_MCSQ_BLDC* pBLDC)
{
    
}

void MCSQ_PWM_Freq_Switch(ST_PWM_CONTROL* pPWM_CTRL)
{
    Q32U_   Q14I_duty_tmp = pPWM_CTRL->P_Q14U_Duty_Max;
    
    if(Q14I_duty_tmp > pPWM_CTRL->I_Q14U_Duty_Freq)
    {
        Q14I_duty_tmp = pPWM_CTRL->I_Q14U_Duty_Freq;
    }
    if(Q14I_duty_tmp > pPWM_CTRL->I_Q14U_Duty_Ibus)
    {
        Q14I_duty_tmp = pPWM_CTRL->I_Q14U_Duty_Ibus;
    }
    if(Q14I_duty_tmp > pPWM_CTRL->I_Q14U_Duty_Iphase)
    {
        Q14I_duty_tmp = pPWM_CTRL->I_Q14U_Duty_Iphase;
    }
    
    pPWM_CTRL->Ramp_Duty.P_Q14I_Target = Q14I_duty_tmp;
    Ramp_Cal_T(&pPWM_CTRL->Ramp_Duty);
    pPWM_CTRL->O_Q14U_Duty_Set = pPWM_CTRL->Ramp_Duty.O_Q14I_Output;
    
    if(pPWM_CTRL->PWM_Freq_Flag == 0U)
    {
        if(pPWM_CTRL->O_Q14U_Duty_Set > pPWM_CTRL->P_Q14U_Low_to_High_Duty)//低频启动
        {
            pPWM_CTRL->O_Q32U_PWMCount_Set = pPWM_CTRL->P_Q14U_Low_to_High_Duty
                *pPWM_CTRL->P_Q32U_Low_PWMCount/pPWM_CTRL->O_Q14U_Duty_Set;
            
            if(pPWM_CTRL->O_Q32U_PWMCount_Set > pPWM_CTRL->P_Q32U_Low_PWMCount)
            {
                pPWM_CTRL->O_Q32U_PWMCount_Set = pPWM_CTRL->P_Q32U_Low_PWMCount;
            }
            if(pPWM_CTRL->O_Q32U_PWMCount_Set <= pPWM_CTRL->P_Q32U_High_PWMCount)
            {
                pPWM_CTRL->PWM_Freq_Flag = 1U;
                pPWM_CTRL->O_Q32U_PWMCount_Set = pPWM_CTRL->P_Q32U_High_PWMCount;
            }
        }
        else
        {
            pPWM_CTRL->O_Q32U_PWMCount_Set = pPWM_CTRL->P_Q32U_Low_PWMCount;
        }
    }
    else
    {
        if(pPWM_CTRL->O_Q14U_Duty_Set < pPWM_CTRL->P_Q14U_High_to_Low_Duty)//高频运行
        {
            pPWM_CTRL->O_Q32U_PWMCount_Set = pPWM_CTRL->P_Q14U_High_to_Low_Duty
                *pPWM_CTRL->P_Q32U_High_PWMCount/pPWM_CTRL->O_Q14U_Duty_Set;
            
            if(pPWM_CTRL->O_Q32U_PWMCount_Set >= pPWM_CTRL->P_Q32U_Low_PWMCount)
            {
                pPWM_CTRL->PWM_Freq_Flag = 0U;
                pPWM_CTRL->O_Q32U_PWMCount_Set = pPWM_CTRL->P_Q32U_Low_PWMCount;
            }
            if(pPWM_CTRL->O_Q32U_PWMCount_Set < pPWM_CTRL->P_Q32U_High_PWMCount)
            {
                pPWM_CTRL->O_Q32U_PWMCount_Set = pPWM_CTRL->P_Q32U_High_PWMCount;
            } 
        }
        else
        {
            pPWM_CTRL->O_Q32U_PWMCount_Set = pPWM_CTRL->P_Q32U_High_PWMCount;
        }
    }
    
    pPWM_CTRL->O_Q32U_Duty_PWMCount = Q32I_RHT_14(pPWM_CTRL->O_Q14U_Duty_Set*pPWM_CTRL->O_Q32U_PWMCount_Set);
}

EM_FLAG_STATE MCSQ_Stall_Check(ST_STALL_CONTROL* pSTALL_CTRL, ST_MCSQ_CONTROL* pMS_CTRL)
{
    EM_FLAG_STATE flag_tmp = ING;
    Q32U_ motor_switch_cnt_max = 0U;
    Q32U_ motor_switch_cnt_min = 0U;
    
    motor_switch_cnt_max = pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[0];
    motor_switch_cnt_min = pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[0];
    for(Q08U_ i=1;i<6;i++)
    {
        if(motor_switch_cnt_max < pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[i])
        {
            motor_switch_cnt_max = pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[i];
        }
        if(motor_switch_cnt_min > pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[i])
        {
            motor_switch_cnt_min = pMS_CTRL->MCSQ_BLDC.Freq_Cal.V_Q32U_60Deg_Time_cnt_tmp[i];
        }
    }
    
    if((Q16I_LFT_06(motor_switch_cnt_min) < pSTALL_CTRL->P_Q06U_Stall_Switch_Coeff*motor_switch_cnt_max)
    && (pMS_CTRL->MCSQ_BLDC.Freq_Cal.O_Q32U_Switch_cnt >= 360U))
    {
        flag_tmp = SUCS;
    }
    
    if(pMS_CTRL->MCSQ_BLDC.Freq_Cal.O_Q32U_Switch_cnt == pSTALL_CTRL->V_Q32U_Stall_Switch_cnt)
    {
        pSTALL_CTRL->V_Q32U_Stall_cnt++;
        if(pSTALL_CTRL->V_Q32U_Stall_cnt > pSTALL_CTRL->P_Q16U_Stall_Count)
        {
            pSTALL_CTRL->V_Q32U_Stall_cnt = 0U;
            flag_tmp = SUCS;
        }
    }
    else
    {
        pSTALL_CTRL->V_Q32U_Stall_cnt = 0U;
    }
    
     pSTALL_CTRL->V_Q32U_Stall_Switch_cnt = pMS_CTRL->MCSQ_BLDC.Freq_Cal.O_Q32U_Switch_cnt;
    
    return flag_tmp;
}
