/**************************************************************************************************
*     File Name :                        MCFOC_LOOP_F.c
*     Library/Module Name :              MCFOC_F
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC算法源文件
**************************************************************************************************/

#include "MCFOC_LOOP_F.h"


/**********************************偏置检测************************************/

/**********************************************************************************************
Function: MCFOC_Offset_Check_Init_F
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Offset_Check_Init_F(ST_MCFOC_OFFSET_F* pOFFSET)
{
    pOFFSET->_V_Q32U_Offset_Check_cnt = 0U;
    
    pOFFSET->_V_Q12I_Ia_Offset = 0U;
    pOFFSET->_V_Q12I_Ib_Offset = 0U;
    pOFFSET->_V_Q12I_Ic_Offset = 0U;
    pOFFSET->_V_Q12I_Ishunt_Offset = 0U;
}

/**********************************************************************************************
Function: MCFOC_Offset_Check_Three_F
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCFOC_Offset_Check_Three_F(ST_MCFOC_OFFSET_F* pOFFSET, ST_PMSM_ELEC_F* pPMSMe)
{
    EM_FLAG_STATE flag_tmp = ING;
    
    pOFFSET->_V_Q12I_Ia_Offset += pOFFSET->_I_Q12I_Ia_Data;
    pOFFSET->_V_Q12I_Ib_Offset += pOFFSET->_I_Q12I_Ib_Data;
    pOFFSET->_V_Q12I_Ic_Offset += pOFFSET->_I_Q12I_Ic_Data;
    pOFFSET->_V_Q32U_Offset_Check_cnt++;
    
    if(pOFFSET->_V_Q32U_Offset_Check_cnt == pOFFSET->_P_Q16U_Offset_Check_Count)
    {
        pOFFSET->_V_Q12I_Ia_Offset /= pOFFSET->_V_Q32U_Offset_Check_cnt;
        pOFFSET->_V_Q12I_Ib_Offset /= pOFFSET->_V_Q32U_Offset_Check_cnt;
        pOFFSET->_V_Q12I_Ic_Offset /= pOFFSET->_V_Q32U_Offset_Check_cnt;
        pPMSMe->_I_Q12I_Ia_Offset = pOFFSET->_V_Q12I_Ia_Offset;
        pPMSMe->_I_Q12I_Ib_Offset = pOFFSET->_V_Q12I_Ib_Offset;
        pPMSMe->_I_Q12I_Ic_Offset = pOFFSET->_V_Q12I_Ic_Offset;
        
        if((pOFFSET->_V_Q12I_Ia_Offset > pOFFSET->_P_Q12U_Offset_Max)
        || (pOFFSET->_V_Q12I_Ia_Offset < pOFFSET->_P_Q12U_Offset_Min)
        || (pOFFSET->_V_Q12I_Ib_Offset > pOFFSET->_P_Q12U_Offset_Max)
        || (pOFFSET->_V_Q12I_Ib_Offset < pOFFSET->_P_Q12U_Offset_Min)
        || (pOFFSET->_V_Q12I_Ic_Offset > pOFFSET->_P_Q12U_Offset_Max)
        || (pOFFSET->_V_Q12I_Ic_Offset < pOFFSET->_P_Q12U_Offset_Min))
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
Function: MCFOC_Offset_Check_One_F
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCFOC_Offset_Check_One_F(ST_MCFOC_OFFSET_F* pOFFSET, ST_PMSM_ELEC_F* pPMSMe)
{
    EM_FLAG_STATE flag_tmp = ING;
    
    pOFFSET->_V_Q12I_Ishunt_Offset += pOFFSET->_I_Q12I_Ishunt_Data;
    pOFFSET->_V_Q32U_Offset_Check_cnt++;
    
    if(pOFFSET->_V_Q32U_Offset_Check_cnt == pOFFSET->_P_Q16U_Offset_Check_Count)
    {
        pOFFSET->_V_Q12I_Ishunt_Offset /= pOFFSET->_V_Q32U_Offset_Check_cnt;
        pPMSMe->_I_Q12I_Ishunt_Offset = pOFFSET->_V_Q12I_Ishunt_Offset;

        if((pOFFSET->_V_Q12I_Ishunt_Offset > pOFFSET->_P_Q12U_Offset_Max)
        || (pOFFSET->_V_Q12I_Ishunt_Offset < pOFFSET->_P_Q12U_Offset_Min))
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

/**********************************************************************************************
Function: MCFOC_ALIGN_Init_F
Description: ALIGN初始化
Input: 无
Output: 无
Input_Output: ALIGN控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ALIGN_Init_F(ST_ALIGN_CONTROL_F* pALIGN)
{
    Ramp_Init_F(&pALIGN->Ramp_Align_Id, 0.0f);
    Ramp_Init_F(&pALIGN->Ramp_Align_Angle, 0.75f);
    
    pALIGN->_V_Q32U_Align_Check_cnt = 0U;
    
    pALIGN->_O_Q32U_Stand_Flag = 0U;
    pALIGN->_O_F_Align_IdRef = 0.0f;
    pALIGN->_O_F_Align_Angle = 0.0f;
}

/**********************************************************************************************
Function: MCFOC_ALIGN_SpeedLoop_F
Description: ALIGN速度环控制函数
Input: 无
Output: 无
Input_Output: ALIGN控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ALIGN_SpeedLoop_F(ST_ALIGN_CONTROL_F* pALIGN)
{
    Ramp_Cal_F(&pALIGN->Ramp_Align_Id);
    Ramp_Cal_F(&pALIGN->Ramp_Align_Angle);

    pALIGN->_O_F_Align_IdRef = pALIGN->Ramp_Align_Id.F_Output;
    pALIGN->_V_Q32U_Align_Check_cnt++;
    if(pALIGN->_V_Q32U_Align_Check_cnt >= pALIGN->_P_Q32U_Align_Check_Count)
    {
        pALIGN->_V_Q32U_Align_Check_cnt = 0U;
        pALIGN->_O_Q32U_Stand_Flag = 1U;
    }
}

/**********************************************************************************************
Function: MCFOC_ALIGN_CurrentLoop_F
Description: ALIGN电流环中断控制函数
Input: 无
Output: 无
Input_Output: ALIGN控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ALIGN_CurrentLoop_F(ST_ALIGN_CONTROL_F* pALIGN)
{
    pALIGN->_O_F_Align_Angle = pALIGN->Ramp_Align_Angle.F_Output;
    MATH_ANGLE_MOD_F(pALIGN->_O_F_Align_Angle);
}


/**********************************IF控制************************************/

/**********************************************************************************************
Function: MCFOC_IF_Init_F
Description: IF初始化
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_IF_Init_F(ST_IF_CONTROL_F* pIF)
{
    Ramp_Init_F(&pIF->Ramp_IF_Iq, 0.0f);
    Ramp_Init_F(&pIF->Ramp_IF_FREQ, 0.0f);
    pIF->Ramp_IF_Iq.F_Target = pIF->_P_F_IF_Iq_Target;
    
    pIF->_V_Q32U_IF_Angle_Err_Check_cnt = 0U;

    pIF->_O_Q32U_Switch_Flag = 0U;
    pIF->_O_F_IF_IdRef = 0.0f;
    pIF->_O_F_IF_IqRef = 0.0f;
    pIF->_O_F_IF_Angle = 0.0f;
}

/**********************************************************************************************
Function: MCFOC_IF_SpeedLoop_F
Description: IF速度环控制函数
Input: 无
Output: 无
Input_Output: IF控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_IF_SpeedLoop_F(ST_IF_CONTROL_F* pIF, ST_PMSM_ELEC_F* pPMSMe)
{
    if(pIF->Ramp_IF_FREQ.F_Output >= pIF->Ramp_IF_FREQ.F_Target)
    {
        pIF->Ramp_IF_Iq.F_Target = pIF->_P_F_IF_Iq_Min;
    }
    Ramp_Cal_F(&pIF->Ramp_IF_Iq);
    Ramp_Cal_F(&pIF->Ramp_IF_FREQ);
    if(pIF->Ramp_IF_Iq.F_Output <= pIF->_P_F_IF_Is_Min)
    {
        pIF->_O_F_IF_IdRef = pIF->_P_F_IF_Is_Min;
    }
    else
    {
        pIF->_O_F_IF_IdRef = 0.0f;
    }
    pIF->_O_F_IF_IqRef = pPMSMe->_I_F_DIR_Target*pIF->Ramp_IF_Iq.F_Output;
}

/**********************************************************************************************
Function: MCFOC_IF_CurrentLoop_F
Description: IF电流环中断控制函数
Input: 无
Output: 无
Input_Output: IF控制指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_IF_CurrentLoop_F(ST_IF_CONTROL_F* pIF, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa)
{
    float F_Angle_Err_tmp = 0.0f;
    
    pIF->_O_F_IF_Angle += pPMSMe->_I_F_DIR_Target*pPMSMa->_O_F_Ts*pIF->Ramp_IF_FREQ.F_Output;
    MATH_ANGLE_MOD_F(pIF->_O_F_IF_Angle);
    
    F_Angle_Err_tmp = pIF->_O_F_IF_Angle - pIF->_I_F_IF_Est_Angle;
    if(F_Angle_Err_tmp > 0.5f)
    {
        F_Angle_Err_tmp -= 1.0f;
    }
    else if(F_Angle_Err_tmp < -0.5f)
    {
        F_Angle_Err_tmp += 1.0f;
    }
    
    if(pIF->Ramp_IF_FREQ.F_Output >= pIF->Ramp_IF_FREQ.F_Target)
    {
        if(MATH_ABS_F(F_Angle_Err_tmp) <= pIF->_P_F_IF_Angle_Err_Limit)
        {
            pIF->_V_Q32U_IF_Angle_Err_Check_cnt++;
            if(pIF->_V_Q32U_IF_Angle_Err_Check_cnt >= pIF->_P_Q32U_IF_Angle_Err_Check_Count)
            {
                pIF->_V_Q32U_IF_Angle_Err_Check_cnt = 0U;
                pIF->_O_Q32U_Switch_Flag = 1U;
            }
        }
        else
        {
            pIF->_V_Q32U_IF_Angle_Err_Check_cnt = 0U;
        }
        
        if(pIF->Ramp_IF_Iq.F_Output <= pIF->_P_F_IF_Iq_Min)
        {
            pIF->_O_Q32U_Switch_Flag = 1U;
        }
    }
}


/********************************速度环**************************************/

/**********************************************************************************************
Function: MCFOC_SpeedLoop_Init_F
Description: 移相SVPWM
Input: 无
Output: 无
Input_Output: 速度环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SpeedLoop_Init_F(ST_FREQ_CONTROL_F* pFREQ)
{
    pFREQ->_O_F_FREQ_IdRef = 0.0f;
    pFREQ->_O_F_FREQ_IqRef = 0.0f;

    PID_Sat_Init_F(&pFREQ->PID_POWER, 1.0f);
    PID_Sat_Init_F(&pFREQ->PID_FREQ, 0.0f);
    PID_Sat_Init_F(&pFREQ->PID_WEAK, 0.0f);
    Ramp_Init_F(&pFREQ->Ramp_FREQ, 0.0f);
}

/**********************************************************************************************
Function: MCFOC_SpeedLoop_F
Description: 速度环控制
Input: 无
Output: 无
Input_Output: 速度环控制指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SpeedLoop_F(ST_FREQ_CONTROL_F* pFREQ, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa)
{
    float F_Is_tmp = 0.0f;
    float F_Ld_Lq_tmp = pPMSMa->_O_F_Ld - pPMSMa->_O_F_Lq;
    
    float F_Freq_tmp = 0.0f;
    F_Freq_tmp = MATH_ABS_F(pPMSMe->_O_F_Freq);

    pFREQ->Ramp_FREQ.F_Target = MATH_SAT_F(pPMSMe->_I_F_DIR_Target*pFREQ->_I_F_FREQ_Target, 1.0f, -1.0f);
    
    Ramp_Cal_F(&pFREQ->Ramp_FREQ);
    
    pFREQ->PID_POWER.F_Rf = MATH_MIN_F(pFREQ->_P_F_FREQ_IbusRef, pFREQ->_P_F_FREQ_PowerRef*pPMSMe->_O_F_One_Over_Vbus);
    pFREQ->PID_POWER.F_Fb = pPMSMe->_O_F_Ibus_10ms;
    PID_Sat_Cal_F(&pFREQ->PID_POWER);

    pFREQ->PID_FREQ.F_Kp = pFREQ->_P_F_FREQ_Kp*TABLE_1D_Inter_F(&pFREQ->TAB_FREQ_Kp_Coeff, F_Freq_tmp);
    pFREQ->PID_FREQ.F_Ki = pFREQ->_P_F_FREQ_Ki*TABLE_1D_Inter_F(&pFREQ->TAB_FREQ_Ki_Coeff, F_Freq_tmp);
    pFREQ->PID_FREQ.F_Rf = MATH_MIN_F(pFREQ->Ramp_FREQ.F_Output, pFREQ->PID_POWER.F_Output);
    pFREQ->PID_FREQ.F_Fb = pPMSMe->_O_F_Freq;
    PID_Sat_Cal_F(&pFREQ->PID_FREQ);
    F_Is_tmp = pFREQ->PID_FREQ.F_Output;

    pFREQ->WEAK_CHECK.Check_Flag.bit.Enable = 1U;
    pFREQ->WEAK_CHECK.Check_Flag.bit.Condition_Set = (pPMSMe->_O_F_Modulation_Rate >= pFREQ->WEAK_CHECK._P_F_Check_TL);
    pFREQ->WEAK_CHECK.Check_Flag.bit.Condition_Clear = (pPMSMe->_O_F_Modulation_Rate <= pFREQ->WEAK_CHECK._P_F_Clear_TL);
    pFREQ->_O_Q32U_Weak_Flag = Check_Cal(&pFREQ->WEAK_CHECK, pFREQ->_O_Q32U_Weak_Flag);
    
    if(pFREQ->_O_Q32U_Weak_Flag)
    {
        pFREQ->PID_WEAK.F_Rf = 1.0f;
        pFREQ->PID_WEAK.F_Fb = pPMSMe->_O_F_Modulation_Rate;
        PID_Sat_Cal_F(&pFREQ->PID_WEAK);
    }
    else
    {
        PID_Sat_Init_F(&pFREQ->PID_WEAK, 0.0f);
        if(F_Ld_Lq_tmp == 0.0f)
        {
            pFREQ->_V_F_FREQ_IMTPA = 0.0f;
        }
        else
        {
            pFREQ->_V_F_FREQ_IMTPA = 0.25f*(Math_Sqrt_F(8.0f*MATH_SQUARE_F(F_Ld_Lq_tmp*F_Is_tmp) + MATH_SQUARE_F(pPMSMa->_O_F_Flux)) - pPMSMa->_O_F_Flux)/F_Ld_Lq_tmp;
        }
    }
    
    pFREQ->_O_F_FREQ_IdRef = pFREQ->PID_WEAK.F_Output + pFREQ->_V_F_FREQ_IMTPA;
    pFREQ->_O_F_FREQ_IqRef = MATH_SIGN_F(F_Is_tmp)*MATH_SQSUB_F(F_Is_tmp, pFREQ->_O_F_FREQ_IdRef);
}


/*******************************电流环***************************************/

/**********************************************************************************************
Function: MCFOC_CurrentLoop_Init_F
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_CurrentLoop_Init_F(ST_CURRENT_CONTROL_F* pCURRENT)
{
    pCURRENT->_I_F_IdRef = 0.0f;
    pCURRENT->_I_F_IqRef = 0.0f;
    
    PID_Sat_Init_F(&pCURRENT->PID_Id, 0.0f);
    PID_Sat_Init_F(&pCURRENT->PID_Iq, 0.0f);
}

/**********************************************************************************************
Function: MCFOC_CurrentLoop_F
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_CurrentLoop_F(ST_CURRENT_CONTROL_F* pCURRENT, ST_PMSM_ELEC_F* pPMSMe)
{
    pCURRENT->PID_Id.F_OutMax = pPMSMe->_O_F_UsRef;
    pCURRENT->PID_Id.F_OutMin = -pPMSMe->_O_F_UsRef;
    pCURRENT->PID_Id.F_Rf = pCURRENT->_I_F_IdRef;
    pCURRENT->PID_Id.F_Fb = pPMSMe->_V_F_Id_Real;
    PID_Sat_Cal_F(&pCURRENT->PID_Id);
    pPMSMe->_V_F_Ud_Real = pCURRENT->PID_Id.F_Output;
    
    pCURRENT->PID_Iq.F_OutMax = MATH_SQSUB_F(pPMSMe->_O_F_UsRef, pCURRENT->PID_Id.F_Output);
    pCURRENT->PID_Iq.F_OutMin = -pCURRENT->PID_Iq.F_OutMax;
    pCURRENT->PID_Iq.F_Rf = pCURRENT->_I_F_IqRef;
    pCURRENT->PID_Iq.F_Fb = pPMSMe->_V_F_Iq_Real;
    PID_Sat_Cal_F(&pCURRENT->PID_Iq);
    pPMSMe->_V_F_Uq_Real = pCURRENT->PID_Iq.F_Output;
}
