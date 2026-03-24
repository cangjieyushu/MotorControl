/**************************************************************************************************
*     File Name :                        MCFOC_LOOP_T.c
*     Library/Module Name :              MCFOC_T
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC算法源文件
**************************************************************************************************/

#include "MCFOC_LOOP_T.h"


/**********************************偏置检测************************************/

/**********************************************************************************************
Function: MCFOC_Offset_Check_Init_T
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Offset_Check_Init_T(ST_MCFOC_OFFSET_T* pOFFSET)
{
    pOFFSET->_V_Q32U_Offset_Check_cnt = 0U;
    
    pOFFSET->_V_Q12I_Ia_Offset = 0U;
    pOFFSET->_V_Q12I_Ib_Offset = 0U;
    pOFFSET->_V_Q12I_Ic_Offset = 0U;
    pOFFSET->_V_Q12I_Ishunt_Offset = 0U;
}

/**********************************************************************************************
Function: MCFOC_Offset_Check_Three_T
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCFOC_Offset_Check_Three_T(ST_MCFOC_OFFSET_T* pOFFSET, ST_PMSM_ELEC_T* pPMSMe)
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
Function: MCFOC_Offset_Check_One_T
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCFOC_Offset_Check_One_T(ST_MCFOC_OFFSET_T* pOFFSET, ST_PMSM_ELEC_T* pPMSMe)
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
Function: MCFOC_ALIGN_Init_T
Description: ALIGN初始化
Input: 无
Output: 无
Input_Output: ALIGN控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ALIGN_Init_T(ST_ALIGN_CONTROL_T* pALIGN)
{
    Ramp_Init_T(&pALIGN->Ramp_Align_Id, 0);
    Ramp_Init_T(&pALIGN->Ramp_Align_Angle, 12288);
    
    pALIGN->_V_Q32U_Align_Check_cnt = 0U;
    
    pALIGN->_O_Q32U_Stand_Flag = 0U;
    pALIGN->_O_Q14I_Align_IdRef = 0;
    pALIGN->_O_Q14I_Align_Angle = 0;
}

/**********************************************************************************************
Function: MCFOC_ALIGN_SpeedLoop_T
Description: ALIGN速度环控制函数
Input: 无
Output: 无
Input_Output: ALIGN控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ALIGN_SpeedLoop_T(ST_ALIGN_CONTROL_T* pALIGN)
{
    Ramp_Cal_T(&pALIGN->Ramp_Align_Id);
    Ramp_Cal_T(&pALIGN->Ramp_Align_Angle);

    pALIGN->_O_Q14I_Align_IdRef = pALIGN->Ramp_Align_Id.Q14I_Output;
    pALIGN->_V_Q32U_Align_Check_cnt++;
    if(pALIGN->_V_Q32U_Align_Check_cnt >= pALIGN->_P_Q32U_Align_Check_Count)
    {
        pALIGN->_V_Q32U_Align_Check_cnt = 0U;
        pALIGN->_O_Q32U_Stand_Flag = 1U;
    }
}

/**********************************************************************************************
Function: MCFOC_ALIGN_CurrentLoop_T
Description: ALIGN电流环中断控制函数
Input: 无
Output: 无
Input_Output: ALIGN控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ALIGN_CurrentLoop_T(ST_ALIGN_CONTROL_T* pALIGN)
{
    pALIGN->_O_Q14I_Align_Angle = pALIGN->Ramp_Align_Angle.Q14I_Output;
    MATH_ANGLE_MOD_T(pALIGN->_O_Q14I_Align_Angle);
}


/**********************************IF控制************************************/

/**********************************************************************************************
Function: MCFOC_IF_Init_T
Description: IF初始化
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_IF_Init_T(ST_IF_CONTROL_T* pIF)
{
    Ramp_Init_T(&pIF->Ramp_IF_Iq, 0);
    Ramp_Init_T(&pIF->Ramp_IF_FREQ, 0);
    pIF->Ramp_IF_Iq.Q14I_Target = pIF->_P_Q14I_IF_Iq_Target;
    
    pIF->_V_Q32U_IF_Angle_Err_Check_cnt = 0U;

    pIF->_O_Q32U_Switch_Flag = 0U;
    pIF->_O_Q14I_IF_IdRef = 0;
    pIF->_O_Q14I_IF_IqRef = 0;
    pIF->_O_Q14I_IF_Angle = 0;
    pIF->_O_Q28I_IF_Angle_tmp = 0;
}

/**********************************************************************************************
Function: MCFOC_IF_SpeedLoop_T
Description: IF速度环控制函数
Input: 无
Output: 无
Input_Output: IF控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_IF_SpeedLoop_T(ST_IF_CONTROL_T* pIF, ST_PMSM_ELEC_T* pPMSMe)
{
    if(pIF->Ramp_IF_FREQ.Q14I_Output >= pIF->Ramp_IF_FREQ.Q14I_Target)
    {
        pIF->Ramp_IF_Iq.Q14I_Target = pIF->_P_Q14I_IF_Iq_Min;
    }
    Ramp_Cal_T(&pIF->Ramp_IF_Iq);
    Ramp_Cal_T(&pIF->Ramp_IF_FREQ);
    if(pIF->Ramp_IF_Iq.Q14I_Output <= pIF->_P_Q14I_IF_Is_Min)
    {
        pIF->_O_Q14I_IF_IdRef = pIF->_P_Q14I_IF_Is_Min;
    }
    else
    {
        pIF->_O_Q14I_IF_IdRef = 0;
    }
    pIF->_O_Q14I_IF_IqRef = pPMSMe->_I_Q00I_DIR_Target*pIF->Ramp_IF_Iq.Q14I_Output;
}

/**********************************************************************************************
Function: MCFOC_IF_CurrentLoop_T
Description: IF电流环中断控制函数
Input: 无
Output: 无
Input_Output: IF控制指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_IF_CurrentLoop_T(ST_IF_CONTROL_T* pIF, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa)
{
    Q32I_ Q14_Angle_Err_tmp = 0;
    
    pIF->_O_Q28I_IF_Angle_tmp += pPMSMe->_I_Q00I_DIR_Target*pPMSMa->_P_Q14I_Ts*pIF->Ramp_IF_FREQ.Q14I_Output;
    MATH_ANGLE_TMP_T(pIF->_O_Q28I_IF_Angle_tmp);
    pIF->_O_Q14I_IF_Angle = Q32I_RHT_14(pIF->_O_Q28I_IF_Angle_tmp);
    
    Q14_Angle_Err_tmp = pIF->_O_Q14I_IF_Angle - pIF->_I_Q14I_IF_Est_Angle;
    if(Q14_Angle_Err_tmp > 8192)
    {
        Q14_Angle_Err_tmp -= 16384;
    }
    else if(Q14_Angle_Err_tmp < -8192)
    {
        Q14_Angle_Err_tmp += 16384;
    }
    
    if(pIF->Ramp_IF_FREQ.Q14I_Output >= pIF->Ramp_IF_FREQ.Q14I_Target)
    {
        if(MATH_ABS_T(Q14_Angle_Err_tmp) <= pIF->_P_Q14I_IF_Angle_Err_Limit)
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
        
        if(pIF->Ramp_IF_Iq.Q14I_Output <= pIF->_P_Q14I_IF_Iq_Min)
        {
            pIF->_O_Q32U_Switch_Flag = 1U;
        }
    }
}


/********************************速度环**************************************/

/**********************************************************************************************
Function: MCFOC_SpeedLoop_Init_T
Description: 移相SVPWM
Input: 无
Output: 无
Input_Output: 速度环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SpeedLoop_Init_T(ST_FREQ_CONTROL_T* pFREQ)
{
    pFREQ->_O_Q14I_FREQ_IdRef = 0;
    pFREQ->_O_Q14I_FREQ_IqRef = 0;

    PID_Sat_Init_T(&pFREQ->PID_POWER, 16384);
    PID_Sat_Init_T(&pFREQ->PID_FREQ, 0);
    PID_Sat_Init_T(&pFREQ->PID_WEAK, 0);
    Ramp_Init_T(&pFREQ->Ramp_FREQ, 0);
}

/**********************************************************************************************
Function: MCFOC_SpeedLoop_T
Description: 速度环控制
Input: 无
Output: 无
Input_Output: 速度环控制指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SpeedLoop_T(ST_FREQ_CONTROL_T* pFREQ, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa)
{
    Q32I_ Q14I_Is_tmp = 0;
    Q32I_ Q14I_Ld_Lq_tmp = pPMSMa->_O_Q14I_Ld - pPMSMa->_O_Q14I_Lq;
    
    Q32I_ Q14I_Freq_tmp = 0;
    Q14I_Freq_tmp = MATH_ABS_T(pPMSMe->_O_Q14I_Freq);

    pFREQ->Ramp_FREQ.Q14I_Target = MATH_SAT_T(pPMSMe->_I_Q00I_DIR_Target*pFREQ->_I_Q14I_FREQ_Target, 16384, -16384);
    
    Ramp_Cal_T(&pFREQ->Ramp_FREQ);
    
    pFREQ->PID_POWER.Q14I_Rf = MATH_MIN_T(pFREQ->_P_Q14I_FREQ_IbusRef, Q32I_RHT_14(pFREQ->_P_Q14I_FREQ_PowerRef*pPMSMe->_O_Q14I_One_Over_Vbus));
    pFREQ->PID_POWER.Q14I_Fb = pPMSMe->_O_Q14I_Ibus_10ms;
    PID_Sat_Cal_T(&pFREQ->PID_POWER);

    pFREQ->PID_FREQ.Q14I_Kp = Q32I_RHT_14(pFREQ->_P_Q14I_FREQ_Kp*TABLE_1D_Inter_T(&pFREQ->TAB_FREQ_Kp_Coeff, Q14I_Freq_tmp));
    pFREQ->PID_FREQ.Q14I_Ki = Q32I_RHT_14(pFREQ->_P_Q14I_FREQ_Ki*TABLE_1D_Inter_T(&pFREQ->TAB_FREQ_Ki_Coeff, Q14I_Freq_tmp));
    pFREQ->PID_FREQ.Q14I_Rf = MATH_MIN_T(pFREQ->Ramp_FREQ.Q14I_Output, pFREQ->PID_POWER.Q14I_Output);
    pFREQ->PID_FREQ.Q14I_Fb = pPMSMe->_O_Q14I_Freq;
    PID_Sat_Cal_T(&pFREQ->PID_FREQ);
    Q14I_Is_tmp = pFREQ->PID_FREQ.Q14I_Output;

    pFREQ->WEAK_CHECK.Check_Flag.bit.Enable = 1U;
    pFREQ->WEAK_CHECK.Check_Flag.bit.Condition_Set = (pPMSMe->_O_Q14I_Modulation_Rate >= pFREQ->WEAK_CHECK._P_Q14I_Check_TL);
    pFREQ->WEAK_CHECK.Check_Flag.bit.Condition_Clear = (pPMSMe->_O_Q14I_Modulation_Rate <= pFREQ->WEAK_CHECK._P_Q14I_Clear_TL);
    pFREQ->_O_Q32U_Weak_Flag = Check_Cal(&pFREQ->WEAK_CHECK, pFREQ->_O_Q32U_Weak_Flag);
    
    if(pFREQ->_O_Q32U_Weak_Flag)
    {
        pFREQ->PID_WEAK.Q14I_Rf = 16384;
        pFREQ->PID_WEAK.Q14I_Fb = pPMSMe->_O_Q14I_Modulation_Rate;
        PID_Sat_Cal_T(&pFREQ->PID_WEAK);
    }
    else
    {
        PID_Sat_Init_T(&pFREQ->PID_WEAK, 0);
        if(Q14I_Ld_Lq_tmp == 0)
        {
            pFREQ->_V_Q14I_FREQ_IMTPA = 0;
        }
        else
        {
            pFREQ->_V_Q14I_FREQ_IMTPA = Q16I_LFT_12(MATH_ABS_T(Math_Sqrt_T(8*MATH_SQUARE_T(Q32I_RHT_14(Q14I_Ld_Lq_tmp*Q14I_Is_tmp))
             + MATH_SQUARE_T(pPMSMa->_O_Q14I_Flux)) - pPMSMa->_O_Q14I_Flux))/Q14I_Ld_Lq_tmp;
        }
    }
    
    pFREQ->_O_Q14I_FREQ_IdRef = pFREQ->PID_WEAK.Q14I_Output + pFREQ->_V_Q14I_FREQ_IMTPA;
    pFREQ->_O_Q14I_FREQ_IqRef = MATH_SIGN_T(Q14I_Is_tmp)*MATH_SQSUB_T(Q14I_Is_tmp, pFREQ->_O_Q14I_FREQ_IdRef);
}


/*******************************电流环***************************************/

/**********************************************************************************************
Function: MCFOC_CurrentLoop_Init_T
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_CurrentLoop_Init_T(ST_CURRENT_CONTROL_T* pCURRENT)
{
    pCURRENT->_I_Q14I_IdRef = 0;
    pCURRENT->_I_Q14I_IqRef = 0;
    
    PID_Sat_Init_T(&pCURRENT->PID_Id, 0);
    PID_Sat_Init_T(&pCURRENT->PID_Iq, 0);
}

/**********************************************************************************************
Function: MCFOC_CurrentLoop_T
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_CurrentLoop_T(ST_CURRENT_CONTROL_T* pCURRENT, ST_PMSM_ELEC_T* pPMSMe)
{
    pCURRENT->PID_Id.Q14I_OutMax = pPMSMe->_O_Q14I_UsRef;
    pCURRENT->PID_Id.Q14I_OutMin = -pPMSMe->_O_Q14I_UsRef;
    pCURRENT->PID_Id.Q14I_Rf = pCURRENT->_I_Q14I_IdRef;
    pCURRENT->PID_Id.Q14I_Fb = pPMSMe->_V_Q14I_Id_Real;
    PID_Sat_Cal_T(&pCURRENT->PID_Id);
    pPMSMe->_V_Q14I_Ud_Real = pCURRENT->PID_Id.Q14I_Output;
    
    pCURRENT->PID_Iq.Q14I_OutMax = MATH_SQSUB_T(pPMSMe->_O_Q14I_UsRef, pCURRENT->PID_Id.Q14I_Output);
    pCURRENT->PID_Iq.Q14I_OutMin = -pCURRENT->PID_Iq.Q14I_OutMax;
    pCURRENT->PID_Iq.Q14I_Rf = pCURRENT->_I_Q14I_IqRef;
    pCURRENT->PID_Iq.Q14I_Fb = pPMSMe->_V_Q14I_Iq_Real;
    PID_Sat_Cal_T(&pCURRENT->PID_Iq);
    pPMSMe->_V_Q14I_Uq_Real = pCURRENT->PID_Iq.Q14I_Output;
}
