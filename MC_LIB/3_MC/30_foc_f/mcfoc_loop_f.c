/*
*     File Name :                        mcfoc_loop_f
*     Library/Module Name :              mcfoc_f
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC偏置自学习，IF，电流，转速闭环模块
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "mcfoc_loop_f.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/**********************************偏置检测************************************/
void MCFOC_Offset_Check_Init_F(ST_MCFOC_OFFSET_F* pOFFSET)
{
    pOFFSET->V_Q32U_Offset_Check_cnt = 0U;
    
    pOFFSET->V_Q12I_Ia_Offset = 0U;
    pOFFSET->V_Q12I_Ib_Offset = 0U;
    pOFFSET->V_Q12I_Ic_Offset = 0U;
    pOFFSET->V_Q12I_Ishunt_Offset = 0U;
}

EM_FLAG_STATE MCFOC_Offset_Check_Three_F(ST_MCFOC_OFFSET_F* pOFFSET, ST_PMSM_ELEC_F* pPMSMe)
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

EM_FLAG_STATE MCFOC_Offset_Check_One_F(ST_MCFOC_OFFSET_F* pOFFSET, ST_PMSM_ELEC_F* pPMSMe)
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
void MCFOC_ALIGN_Init_F(ST_ALIGN_CONTROL_F* pALIGN)
{
    Ramp_Init_F(&pALIGN->Ramp_Align_Id, 0.0f);
    Ramp_Init_F(&pALIGN->Ramp_Align_Angle, 0.75f);
    
    pALIGN->V_Q32U_Align_Check_cnt = 0U;
    
    pALIGN->O_Q32U_Stand_Flag = 0U;
    pALIGN->O_F_Align_IdRef = 0.0f;
    pALIGN->O_F_Align_Angle = 0.0f;
}

void MCFOC_ALIGN_SpeedLoop_F(ST_ALIGN_CONTROL_F* pALIGN)
{
    Ramp_Cal_F(&pALIGN->Ramp_Align_Id);
    Ramp_Cal_F(&pALIGN->Ramp_Align_Angle);

    pALIGN->O_F_Align_IdRef = pALIGN->Ramp_Align_Id.O_F_Output;
    pALIGN->V_Q32U_Align_Check_cnt++;
    if(pALIGN->V_Q32U_Align_Check_cnt >= pALIGN->P_Q32U_Align_Check_Count)
    {
        pALIGN->V_Q32U_Align_Check_cnt = 0U;
        pALIGN->O_Q32U_Stand_Flag = 1U;
    }
}

void MCFOC_ALIGN_CurrentLoop_F(ST_ALIGN_CONTROL_F* pALIGN)
{
    pALIGN->O_F_Align_Angle = pALIGN->Ramp_Align_Angle.O_F_Output;
    MATH_ANGLE_MOD_F(pALIGN->O_F_Align_Angle);
}


/**********************************IF控制************************************/
void MCFOC_IF_Init_F(ST_IF_CONTROL_F* pIF)
{
    Ramp_Init_F(&pIF->Ramp_IF_Iq, 0.0f);
    Ramp_Init_F(&pIF->Ramp_IF_FREQ, 0.0f);
    pIF->Ramp_IF_Iq.P_F_Target = pIF->P_F_IF_Iq_Target;
    
    pIF->V_Q32U_IF_Angle_Err_Check_cnt = 0U;

    pIF->O_Q32U_Switch_Flag = 0U;
    pIF->O_F_IF_IdRef = 0.0f;
    pIF->O_F_IF_IqRef = 0.0f;
    pIF->O_F_IF_Angle = 0.0f;
}

void MCFOC_IF_SpeedLoop_F(ST_IF_CONTROL_F* pIF, ST_PMSM_ELEC_F* pPMSMe)
{
    if(pIF->Ramp_IF_FREQ.O_F_Output >= pIF->Ramp_IF_FREQ.P_F_Target)
    {
        pIF->Ramp_IF_Iq.P_F_Target = pIF->P_F_IF_Iq_Min;
    }
    Ramp_Cal_F(&pIF->Ramp_IF_Iq);
    Ramp_Cal_F(&pIF->Ramp_IF_FREQ);
    if(pIF->Ramp_IF_Iq.O_F_Output <= pIF->P_F_IF_Is_Min)
    {
        pIF->O_F_IF_IdRef = pIF->P_F_IF_Is_Min;
    }
    else
    {
        pIF->O_F_IF_IdRef = 0.0f;
    }
    pIF->O_F_IF_IqRef = pPMSMe->I_F_DIR_Target*pIF->Ramp_IF_Iq.O_F_Output;
}

void MCFOC_IF_CurrentLoop_F(ST_IF_CONTROL_F* pIF, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa)
{
    float F_Angle_Err_tmp = 0.0f;
    
    pIF->O_F_IF_Angle += pPMSMe->I_F_DIR_Target*pPMSMa->O_F_Ts*pIF->Ramp_IF_FREQ.O_F_Output;
    MATH_ANGLE_MOD_F(pIF->O_F_IF_Angle);
    
    F_Angle_Err_tmp = pIF->O_F_IF_Angle - pIF->I_F_IF_Est_Angle;
    if(F_Angle_Err_tmp > 0.5f)
    {
        F_Angle_Err_tmp -= 1.0f;
    }
    else if(F_Angle_Err_tmp < -0.5f)
    {
        F_Angle_Err_tmp += 1.0f;
    }
    
    if(pIF->Ramp_IF_FREQ.O_F_Output >= pIF->Ramp_IF_FREQ.P_F_Target)
    {
        if(MATH_ABS_F(F_Angle_Err_tmp) <= pIF->P_F_IF_Angle_Err_Limit)
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
        
        if(pIF->Ramp_IF_Iq.O_F_Output <= pIF->P_F_IF_Iq_Min)
        {
            pIF->O_Q32U_Switch_Flag = 1U;
        }
    }
}


/********************************速度环**************************************/
void MCFOC_SpeedLoop_Init_F(ST_FREQ_CONTROL_F* pFREQ)
{
    pFREQ->O_F_FREQ_IdRef = 0.0f;
    pFREQ->O_F_FREQ_IqRef = 0.0f;

    PID_Sat_Init_F(&pFREQ->PID_POWER, 1.0f);
    PID_Sat_Init_F(&pFREQ->PID_FREQ, 0.0f);
    PID_Sat_Init_F(&pFREQ->PID_WEAK, 0.0f);
    Ramp_Init_F(&pFREQ->Ramp_FREQ, 0.0f);
}

void MCFOC_SpeedLoop_F(ST_FREQ_CONTROL_F* pFREQ, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa)
{
    float F_Is_tmp = 0.0f;
    float F_Ld_Lq_tmp = pPMSMa->O_F_Ld - pPMSMa->O_F_Lq;
    
    float F_Freq_tmp = 0.0f;
    F_Freq_tmp = MATH_ABS_F(pPMSMe->O_F_Freq);

    pFREQ->Ramp_FREQ.P_F_Target = MATH_SAT_F(pPMSMe->I_F_DIR_Target*pFREQ->I_F_FREQ_Target, 1.0f, -1.0f);
    
    Ramp_Cal_F(&pFREQ->Ramp_FREQ);
    
    pFREQ->PID_POWER.I_F_Rf = MATH_MIN_F(pFREQ->P_F_FREQ_IbusRef, pFREQ->P_F_FREQ_PowerRef*pPMSMe->O_F_One_Over_Vbus);
    pFREQ->PID_POWER.I_F_Fb = pPMSMe->O_F_Ibus_10ms;
    PID_Sat_Cal_F(&pFREQ->PID_POWER);

    pFREQ->PID_FREQ.P_F_Kp = pFREQ->P_F_FREQ_Kp*TABLE_1D_Inter_F(&pFREQ->TAB_FREQ_Kp_Coeff, F_Freq_tmp);
    pFREQ->PID_FREQ.P_F_Ki = pFREQ->P_F_FREQ_Ki*TABLE_1D_Inter_F(&pFREQ->TAB_FREQ_Ki_Coeff, F_Freq_tmp);
    pFREQ->PID_FREQ.I_F_Rf = MATH_MIN_F(pFREQ->Ramp_FREQ.O_F_Output, pFREQ->PID_POWER.O_F_Output);
    pFREQ->PID_FREQ.I_F_Fb = pPMSMe->O_F_Freq;
    PID_Sat_Cal_F(&pFREQ->PID_FREQ);
    F_Is_tmp = pFREQ->PID_FREQ.O_F_Output;

    pFREQ->WEAK_CHECK.Check_Flag.bit.Enable = 1U;
    pFREQ->WEAK_CHECK.Check_Flag.bit.Condition_Set = (pPMSMe->O_F_Modulation_Rate >= pFREQ->WEAK_CHECK.P_F_Check_TL);
    pFREQ->WEAK_CHECK.Check_Flag.bit.Condition_Clear = (pPMSMe->O_F_Modulation_Rate <= pFREQ->WEAK_CHECK.P_F_Clear_TL);
    pFREQ->O_Q32U_Weak_Flag = Check_Cal(&pFREQ->WEAK_CHECK, pFREQ->O_Q32U_Weak_Flag);
    
    if(pFREQ->O_Q32U_Weak_Flag)
    {
        pFREQ->PID_WEAK.I_F_Rf = 1.0f;
        pFREQ->PID_WEAK.I_F_Fb = pPMSMe->O_F_Modulation_Rate;
        PID_Sat_Cal_F(&pFREQ->PID_WEAK);
    }
    else
    {
        PID_Sat_Init_F(&pFREQ->PID_WEAK, 0.0f);
        if(F_Ld_Lq_tmp == 0.0f)
        {
            pFREQ->V_F_FREQ_IMTPA = 0.0f;
        }
        else
        {
            pFREQ->V_F_FREQ_IMTPA = 0.25f*(Math_Sqrt_F(8.0f*MATH_SQUARE_F(F_Ld_Lq_tmp*F_Is_tmp) + MATH_SQUARE_F(pPMSMa->O_F_Flux)) - pPMSMa->O_F_Flux)/F_Ld_Lq_tmp;
        }
    }
    
    pFREQ->O_F_FREQ_IdRef = pFREQ->PID_WEAK.O_F_Output + pFREQ->V_F_FREQ_IMTPA;
    pFREQ->O_F_FREQ_IqRef = MATH_SIGN_F(F_Is_tmp)*MATH_SQRTSUB_F(F_Is_tmp, pFREQ->O_F_FREQ_IdRef);
}


/*******************************电流环***************************************/
void MCFOC_CurrentLoop_Init_F(ST_CURRENT_CONTROL_F* pCURRENT)
{
    pCURRENT->I_F_IdRef = 0.0f;
    pCURRENT->I_F_IqRef = 0.0f;
    
    PID_Sat_Init_F(&pCURRENT->PID_Id, 0.0f);
    PID_Sat_Init_F(&pCURRENT->PID_Iq, 0.0f);
}

void MCFOC_CurrentLoop_F(ST_CURRENT_CONTROL_F* pCURRENT, ST_PMSM_ELEC_F* pPMSMe)
{
    pCURRENT->PID_Id.P_F_OutMax = pPMSMe->O_F_UsRef;
    pCURRENT->PID_Id.P_F_OutMin = -pPMSMe->O_F_UsRef;
    pCURRENT->PID_Id.I_F_Rf = pCURRENT->I_F_IdRef;
    pCURRENT->PID_Id.I_F_Fb = pPMSMe->V_F_Id_Real;
    PID_Sat_Cal_F(&pCURRENT->PID_Id);
    pPMSMe->V_F_Ud_Real = pCURRENT->PID_Id.O_F_Output;
    
    pCURRENT->PID_Iq.P_F_OutMax = MATH_SQRTSUB_F(pPMSMe->O_F_UsRef, pCURRENT->PID_Id.O_F_Output);
    pCURRENT->PID_Iq.P_F_OutMin = -pCURRENT->PID_Iq.P_F_OutMax;
    pCURRENT->PID_Iq.I_F_Rf = pCURRENT->I_F_IqRef;
    pCURRENT->PID_Iq.I_F_Fb = pPMSMe->V_F_Iq_Real;
    PID_Sat_Cal_F(&pCURRENT->PID_Iq);
    pPMSMe->V_F_Uq_Real = pCURRENT->PID_Iq.O_F_Output;
}
