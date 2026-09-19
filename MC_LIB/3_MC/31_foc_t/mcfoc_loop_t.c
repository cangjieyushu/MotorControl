/*
*     File Name :                        mcfoc_loop_t
*     Library/Module Name :              mcfoc_t
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC偏置自学习，IF，电流，转速闭环模块
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "mcfoc_loop_t.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/**********************************偏置检测************************************/
void MCFOC_Offset_Check_Init_T(ST_MCFOC_OFFSET_T* pOFFSET)
{
    pOFFSET->V_Q32U_Offset_Check_cnt = 0U;
    
    pOFFSET->V_Q12I_Ia_Offset = 0U;
    pOFFSET->V_Q12I_Ib_Offset = 0U;
    pOFFSET->V_Q12I_Ic_Offset = 0U;
    pOFFSET->V_Q12I_Ishunt_Offset = 0U;
}

EM_FLAG_STATE MCFOC_Offset_Check_Three_T(ST_MCFOC_OFFSET_T* pOFFSET, ST_PMSM_ELEC_T* pPMSMe)
{
    EM_FLAG_STATE flag_tmp = ING;
    
    pOFFSET->V_Q12I_Ia_Offset += pOFFSET->I_Q12I_Ia_Data;
    pOFFSET->V_Q12I_Ib_Offset += pOFFSET->I_Q12I_Ib_Data;
    pOFFSET->V_Q12I_Ic_Offset += pOFFSET->I_Q12I_Ic_Data;
    pOFFSET->V_Q32U_Offset_Check_cnt++;
    
    if(pOFFSET->V_Q32U_Offset_Check_cnt == pOFFSET->P_Q16U_Offset_Check_Count)
    {
        pOFFSET->V_Q12I_Ia_Offset /= pOFFSET->V_Q32U_Offset_Check_cnt;
        pOFFSET->V_Q12I_Ib_Offset /= pOFFSET->V_Q32U_Offset_Check_cnt;
        pOFFSET->V_Q12I_Ic_Offset /= pOFFSET->V_Q32U_Offset_Check_cnt;
        pPMSMe->I_Q12I_Ia_Offset = pOFFSET->V_Q12I_Ia_Offset;
        pPMSMe->I_Q12I_Ib_Offset = pOFFSET->V_Q12I_Ib_Offset;
        pPMSMe->I_Q12I_Ic_Offset = pOFFSET->V_Q12I_Ic_Offset;
        
        if((pOFFSET->V_Q12I_Ia_Offset > pOFFSET->P_Q12U_Offset_Max)
        || (pOFFSET->V_Q12I_Ia_Offset < pOFFSET->P_Q12U_Offset_Min)
        || (pOFFSET->V_Q12I_Ib_Offset > pOFFSET->P_Q12U_Offset_Max)
        || (pOFFSET->V_Q12I_Ib_Offset < pOFFSET->P_Q12U_Offset_Min)
        || (pOFFSET->V_Q12I_Ic_Offset > pOFFSET->P_Q12U_Offset_Max)
        || (pOFFSET->V_Q12I_Ic_Offset < pOFFSET->P_Q12U_Offset_Min))
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

EM_FLAG_STATE MCFOC_Offset_Check_One_T(ST_MCFOC_OFFSET_T* pOFFSET, ST_PMSM_ELEC_T* pPMSMe)
{
    EM_FLAG_STATE flag_tmp = ING;
    
    pOFFSET->V_Q12I_Ishunt_Offset += pOFFSET->I_Q12I_Ishunt_Data;
    pOFFSET->V_Q32U_Offset_Check_cnt++;
    
    if(pOFFSET->V_Q32U_Offset_Check_cnt == pOFFSET->P_Q16U_Offset_Check_Count)
    {
        pOFFSET->V_Q12I_Ishunt_Offset /= pOFFSET->V_Q32U_Offset_Check_cnt;
        pPMSMe->I_Q12I_Ishunt_Offset = pOFFSET->V_Q12I_Ishunt_Offset;

        if((pOFFSET->V_Q12I_Ishunt_Offset > pOFFSET->P_Q12U_Offset_Max)
        || (pOFFSET->V_Q12I_Ishunt_Offset < pOFFSET->P_Q12U_Offset_Min))
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


/**********************************ALIGN控制************************************/
void MCFOC_ALIGN_Init_T(ST_ALIGN_CONTROL_T* pALIGN)
{
    Ramp_Init_T(&pALIGN->Ramp_Align_Id, 0);
    Ramp_Init_T(&pALIGN->Ramp_Align_Angle, 12288);
    
    pALIGN->V_Q32U_Align_Check_cnt = 0U;
    
    pALIGN->O_Q32U_Stand_Flag = 0U;
    pALIGN->O_Q14I_Align_IdRef = 0;
    pALIGN->O_Q14I_Align_Angle = 0;
}

void MCFOC_ALIGN_SpeedLoop_T(ST_ALIGN_CONTROL_T* pALIGN)
{
    Ramp_Cal_T(&pALIGN->Ramp_Align_Id);
    Ramp_Cal_T(&pALIGN->Ramp_Align_Angle);

    pALIGN->O_Q14I_Align_IdRef = pALIGN->Ramp_Align_Id.O_Q14I_Output;
    pALIGN->V_Q32U_Align_Check_cnt++;
    if(pALIGN->V_Q32U_Align_Check_cnt >= pALIGN->P_Q32U_Align_Check_Count)
    {
        pALIGN->V_Q32U_Align_Check_cnt = 0U;
        pALIGN->O_Q32U_Stand_Flag = 1U;
    }
}

void MCFOC_ALIGN_CurrentLoop_T(ST_ALIGN_CONTROL_T* pALIGN)
{
    pALIGN->O_Q14I_Align_Angle = pALIGN->Ramp_Align_Angle.O_Q14I_Output;
    MATH_ANGLE_MOD_T(pALIGN->O_Q14I_Align_Angle);
}


/**********************************IF控制************************************/
void MCFOC_IF_Init_T(ST_IF_CONTROL_T* pIF)
{
    Ramp_Init_T(&pIF->Ramp_IF_Iq, 0);
    Ramp_Init_T(&pIF->Ramp_IF_FREQ, 0);
    pIF->Ramp_IF_Iq.P_Q14I_Target = pIF->P_Q14I_IF_Iq_Target;
    
    pIF->V_Q32U_IF_Angle_Err_Check_cnt = 0U;

    pIF->O_Q32U_Switch_Flag = 0U;
    pIF->O_Q14I_IF_IdRef = 0;
    pIF->O_Q14I_IF_IqRef = 0;
    pIF->O_Q14I_IF_Angle = 0;
    pIF->O_Q28I_IF_Angle_tmp = 0;
}

void MCFOC_IF_SpeedLoop_T(ST_IF_CONTROL_T* pIF, ST_PMSM_ELEC_T* pPMSMe)
{
    if(pIF->Ramp_IF_FREQ.O_Q14I_Output >= pIF->Ramp_IF_FREQ.P_Q14I_Target)
    {
        pIF->Ramp_IF_Iq.P_Q14I_Target = pIF->P_Q14I_IF_Iq_Min;
    }
    Ramp_Cal_T(&pIF->Ramp_IF_Iq);
    Ramp_Cal_T(&pIF->Ramp_IF_FREQ);
    if(pIF->Ramp_IF_Iq.O_Q14I_Output <= pIF->P_Q14I_IF_Is_Min)
    {
        pIF->O_Q14I_IF_IdRef = pIF->P_Q14I_IF_Is_Min;
    }
    else
    {
        pIF->O_Q14I_IF_IdRef = 0;
    }
    pIF->O_Q14I_IF_IqRef = pPMSMe->I_Q00I_DIR_Target*pIF->Ramp_IF_Iq.O_Q14I_Output;
}

void MCFOC_IF_CurrentLoop_T(ST_IF_CONTROL_T* pIF, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa)
{
    Q32I_ Q14_Angle_Err_tmp = 0;
    
    pIF->O_Q28I_IF_Angle_tmp += pPMSMe->I_Q00I_DIR_Target*pPMSMa->P_Q14I_Ts*pIF->Ramp_IF_FREQ.O_Q14I_Output;
    MATH_ANGLE_TMP_T(pIF->O_Q28I_IF_Angle_tmp);
    pIF->O_Q14I_IF_Angle = Q32I_RHT_14(pIF->O_Q28I_IF_Angle_tmp);
    
    Q14_Angle_Err_tmp = pIF->O_Q14I_IF_Angle - pIF->I_Q14I_IF_Est_Angle;
    if(Q14_Angle_Err_tmp > 8192)
    {
        Q14_Angle_Err_tmp -= 16384;
    }
    else if(Q14_Angle_Err_tmp < -8192)
    {
        Q14_Angle_Err_tmp += 16384;
    }
    
    if(pIF->Ramp_IF_FREQ.O_Q14I_Output >= pIF->Ramp_IF_FREQ.P_Q14I_Target)
    {
        if(MATH_ABS_T(Q14_Angle_Err_tmp) <= pIF->P_Q14I_IF_Angle_Err_Limit)
        {
            pIF->V_Q32U_IF_Angle_Err_Check_cnt++;
            if(pIF->V_Q32U_IF_Angle_Err_Check_cnt >= pIF->P_Q32U_IF_Angle_Err_Check_Count)
            {
                pIF->V_Q32U_IF_Angle_Err_Check_cnt = 0U;
                pIF->O_Q32U_Switch_Flag = 1U;
            }
        }
        else
        {
            pIF->V_Q32U_IF_Angle_Err_Check_cnt = 0U;
        }
        
        if(pIF->Ramp_IF_Iq.O_Q14I_Output <= pIF->P_Q14I_IF_Iq_Min)
        {
            pIF->O_Q32U_Switch_Flag = 1U;
        }
    }
}


/********************************速度环**************************************/
void MCFOC_SpeedLoop_Init_T(ST_FREQ_CONTROL_T* pFREQ)
{
    pFREQ->O_Q14I_FREQ_IdRef = 0;
    pFREQ->O_Q14I_FREQ_IqRef = 0;

    PID_Sat_Init_T(&pFREQ->PID_POWER, 16384);
    PID_Sat_Init_T(&pFREQ->PID_FREQ, 0);
    PID_Sat_Init_T(&pFREQ->PID_WEAK, 0);
    Ramp_Init_T(&pFREQ->Ramp_FREQ, 0);
}

void MCFOC_SpeedLoop_T(ST_FREQ_CONTROL_T* pFREQ, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa)
{
    Q32I_ Q14I_Is_tmp = 0;
    Q32I_ Q14I_Ld_Lq_tmp = pPMSMa->O_Q14I_Ld - pPMSMa->O_Q14I_Lq;
    
    Q32I_ Q14I_Freq_tmp = 0;
    Q14I_Freq_tmp = MATH_ABS_T(pPMSMe->O_Q14I_Freq);

    pFREQ->Ramp_FREQ.P_Q14I_Target = MATH_SAT_T(pPMSMe->I_Q00I_DIR_Target*pFREQ->I_Q14I_FREQ_Target, 16384, -16384);
    
    Ramp_Cal_T(&pFREQ->Ramp_FREQ);
    
    pFREQ->PID_POWER.I_Q14I_Rf = MATH_MIN_T(pFREQ->P_Q14I_FREQ_IbusRef, Q32I_RHT_14(pFREQ->P_Q14I_FREQ_PowerRef*pPMSMe->O_Q14I_One_Over_Vbus));
    pFREQ->PID_POWER.I_Q14I_Fb = pPMSMe->O_Q14I_Ibus_10ms;
    PID_Sat_Cal_T(&pFREQ->PID_POWER);

    pFREQ->PID_FREQ.P_Q14I_Kp = Q32I_RHT_14(pFREQ->P_Q14I_FREQ_Kp*TABLE_1D_Inter_T(&pFREQ->TAB_FREQ_Kp_Coeff, Q14I_Freq_tmp));
    pFREQ->PID_FREQ.P_Q14I_Ki = Q32I_RHT_14(pFREQ->P_Q14I_FREQ_Ki*TABLE_1D_Inter_T(&pFREQ->TAB_FREQ_Ki_Coeff, Q14I_Freq_tmp));
    pFREQ->PID_FREQ.I_Q14I_Rf = MATH_MIN_T(pFREQ->Ramp_FREQ.O_Q14I_Output, pFREQ->PID_POWER.O_Q14I_Output);
    pFREQ->PID_FREQ.I_Q14I_Fb = pPMSMe->O_Q14I_Freq;
    PID_Sat_Cal_T(&pFREQ->PID_FREQ);
    Q14I_Is_tmp = pFREQ->PID_FREQ.O_Q14I_Output;

    pFREQ->WEAK_CHECK.Check_Flag.bit.Enable = 1U;
    pFREQ->WEAK_CHECK.Check_Flag.bit.Condition_Set = (pPMSMe->O_Q14I_Modulation_Rate >= pFREQ->WEAK_CHECK.P_Q14I_Check_TL);
    pFREQ->WEAK_CHECK.Check_Flag.bit.Condition_Clear = (pPMSMe->O_Q14I_Modulation_Rate <= pFREQ->WEAK_CHECK.P_Q14I_Clear_TL);
    pFREQ->O_Q32U_Weak_Flag = Check_Cal(&pFREQ->WEAK_CHECK, pFREQ->O_Q32U_Weak_Flag);
    
    if(pFREQ->O_Q32U_Weak_Flag)
    {
        pFREQ->PID_WEAK.I_Q14I_Rf = 16384;
        pFREQ->PID_WEAK.I_Q14I_Fb = pPMSMe->O_Q14I_Modulation_Rate;
        PID_Sat_Cal_T(&pFREQ->PID_WEAK);
    }
    else
    {
        PID_Sat_Init_T(&pFREQ->PID_WEAK, 0);
        if(Q14I_Ld_Lq_tmp == 0)
        {
            pFREQ->V_Q14I_FREQ_IMTPA = 0;
        }
        else
        {
            pFREQ->V_Q14I_FREQ_IMTPA = Q16I_LFT_12(MATH_ABS_T(Math_Sqrt_T(8*MATH_SQUARE_T(Q32I_RHT_14(Q14I_Ld_Lq_tmp*Q14I_Is_tmp))
             + MATH_SQUARE_T(pPMSMa->O_Q14I_Flux)) - pPMSMa->O_Q14I_Flux))/Q14I_Ld_Lq_tmp;
        }
    }
    
    pFREQ->O_Q14I_FREQ_IdRef = pFREQ->PID_WEAK.O_Q14I_Output + pFREQ->V_Q14I_FREQ_IMTPA;
    pFREQ->O_Q14I_FREQ_IqRef = MATH_SIGN_T(Q14I_Is_tmp)*MATH_SQRTSUB_T(Q14I_Is_tmp, pFREQ->O_Q14I_FREQ_IdRef);
}


/*******************************电流环***************************************/
void MCFOC_CurrentLoop_Init_T(ST_CURRENT_CONTROL_T* pCURRENT)
{
    pCURRENT->I_Q14I_IdRef = 0;
    pCURRENT->I_Q14I_IqRef = 0;
    
    PID_Sat_Init_T(&pCURRENT->PID_Id, 0);
    PID_Sat_Init_T(&pCURRENT->PID_Iq, 0);
}

void MCFOC_CurrentLoop_T(ST_CURRENT_CONTROL_T* pCURRENT, ST_PMSM_ELEC_T* pPMSMe)
{
    pCURRENT->PID_Id.P_Q14I_OutMax = pPMSMe->O_Q14I_UsRef;
    pCURRENT->PID_Id.P_Q14I_OutMin = -pPMSMe->O_Q14I_UsRef;
    pCURRENT->PID_Id.I_Q14I_Rf = pCURRENT->I_Q14I_IdRef;
    pCURRENT->PID_Id.I_Q14I_Fb = pPMSMe->V_Q14I_Id_Real;
    PID_Sat_Cal_T(&pCURRENT->PID_Id);
    pPMSMe->V_Q14I_Ud_Real = pCURRENT->PID_Id.O_Q14I_Output;
    
    pCURRENT->PID_Iq.P_Q14I_OutMax = MATH_SQRTSUB_T(pPMSMe->O_Q14I_UsRef, pCURRENT->PID_Id.O_Q14I_Output);
    pCURRENT->PID_Iq.P_Q14I_OutMin = -pCURRENT->PID_Iq.P_Q14I_OutMax;
    pCURRENT->PID_Iq.I_Q14I_Rf = pCURRENT->I_Q14I_IqRef;
    pCURRENT->PID_Iq.I_Q14I_Fb = pPMSMe->V_Q14I_Iq_Real;
    PID_Sat_Cal_T(&pCURRENT->PID_Iq);
    pPMSMe->V_Q14I_Uq_Real = pCURRENT->PID_Iq.O_Q14I_Output;
}
