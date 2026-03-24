/**************************************************************************************************
*     File Name :                        MCFOC_SVPWM_F.c
*     Library/Module Name :              MCFOC_F
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC算法源文件
**************************************************************************************************/

#include "MCFOC_SVPWM_F.h"


/*********************************SVPWM*************************************/

static Q08U_ Txyz_Table[3][8] = 
//   2  6  1  4  3  5
{{0U,1U,0U,0U,2U,2U,1U,0U},
 {0U,0U,2U,1U,1U,0U,2U,0U},
 {0U,2U,1U,2U,0U,1U,0U,0U}};

/**********************************************************************************************
Function: MCFOC_SVPWM_Init_F
Description: SVPWM初始化
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SVPWM_Init_F(ST_SVPWM_CONTROL_F* pSVPWM)
{
    pSVPWM->_O_Q32U_Five_Flag_Real = 0U;
}

/**********************************************************************************************
Function: MCFOC_Five_Cal_F
Description: 五段式切换判断
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Five_Cal_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe)
{
    pSVPWM->FIVE_CHECK.Check_Flag.bit.Enable = 1U;
    pSVPWM->FIVE_CHECK.Check_Flag.bit.Condition_Set = (pPMSMe->_O_F_Modulation_Rate >= pSVPWM->FIVE_CHECK._P_F_Check_TL);
    pSVPWM->FIVE_CHECK.Check_Flag.bit.Condition_Clear = (pPMSMe->_O_F_Modulation_Rate <= pSVPWM->FIVE_CHECK._P_F_Clear_TL);
    pSVPWM->_O_Q32U_Five_Flag = Check_Cal(&pSVPWM->FIVE_CHECK, pSVPWM->_O_Q32U_Five_Flag);
}

/**********************************************************************************************
Function: MCFOC_ThreeShunt_Current_Cal_F
Description: 三电阻采样电流查表
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ThreeShunt_Current_Cal_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe)
{
    switch(pSVPWM->_O_Q32U_Sector)
    {
        case 3U:{pPMSMe->_V_F_Ia = - pPMSMe->_V_F_Ib - pPMSMe->_V_F_Ic;break;}
        case 1U:{pPMSMe->_V_F_Ib = - pPMSMe->_V_F_Ia - pPMSMe->_V_F_Ic;break;}
        case 5U:{pPMSMe->_V_F_Ib = - pPMSMe->_V_F_Ia - pPMSMe->_V_F_Ic;break;}
        case 4U:{pPMSMe->_V_F_Ic = - pPMSMe->_V_F_Ia - pPMSMe->_V_F_Ib;break;}
        case 6U:{pPMSMe->_V_F_Ic = - pPMSMe->_V_F_Ia - pPMSMe->_V_F_Ib;break;}
        case 2U:{pPMSMe->_V_F_Ia = - pPMSMe->_V_F_Ib - pPMSMe->_V_F_Ic;break;}
        default:break;
    }
}

/**********************************************************************************************
Function: MCFOC_SVPWM_ThreeShunt_F
Description: 三电阻SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SVPWM_ThreeShunt_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe)
{
    float F_Utmp1 = 0.0f, F_Utmp2 = 0.0f, F_Utmp3 = 0.0f;
    float F_Ttmp1 = 0.0f, F_Ttmp2 = 0.0f, F_Ttmpsum = 0.0f;
    float F_Txyz[3] = {0.0f, 0.0f, 0.0f};
    
    F_Utmp1 = MATH_SQRT_THREE_F*pPMSMe->_V_F_Ubeta_Pre;
    F_Utmp2 = 0.5f*( 3.0f*pPMSMe->_V_F_Ualfa_Pre - F_Utmp1)*pPMSMe->_O_F_One_Over_Vbus;
    F_Utmp3 = 0.5f*(-3.0f*pPMSMe->_V_F_Ualfa_Pre - F_Utmp1)*pPMSMe->_O_F_One_Over_Vbus;
    F_Utmp1 = F_Utmp1*pPMSMe->_O_F_One_Over_Vbus;
    
    pSVPWM->_O_Q32U_Sector = 0U;
    if(F_Utmp1>0.0f){pSVPWM->_O_Q32U_Sector+=1U;}else{}
    if(F_Utmp2>0.0f){pSVPWM->_O_Q32U_Sector+=2U;}else{}
    if(F_Utmp3>0.0f){pSVPWM->_O_Q32U_Sector+=4U;}else{}
    switch(pSVPWM->_O_Q32U_Sector)
    {
        case 3U:{F_Ttmp1 =  F_Utmp2; F_Ttmp2 =  F_Utmp1;break;}
        case 1U:{F_Ttmp1 = -F_Utmp2; F_Ttmp2 = -F_Utmp3;break;}
        case 5U:{F_Ttmp1 =  F_Utmp1; F_Ttmp2 =  F_Utmp3;break;}
        case 4U:{F_Ttmp1 = -F_Utmp1; F_Ttmp2 = -F_Utmp2;break;}
        case 6U:{F_Ttmp1 =  F_Utmp3; F_Ttmp2 =  F_Utmp2;break;}
        case 2U:{F_Ttmp1 = -F_Utmp3; F_Ttmp2 = -F_Utmp1;break;}
        default:break;
    }

    if(pSVPWM->_O_Q32U_Five_Flag_Real)
    {
        F_Ttmpsum = F_Ttmp1 + F_Ttmp2;
        if(F_Ttmpsum > pSVPWM->_P_F_MidDuty + 0.5f*pSVPWM->_P_F_MinDuty)
        {
            F_Ttmpsum = pSVPWM->_P_F_MaxDuty;
        }
        else if(F_Ttmpsum > pSVPWM->_P_F_MidDuty)
        {
            F_Ttmpsum = pSVPWM->_P_F_MidDuty;
        }
        else
        {
        
        }
        if(F_Ttmp2 > pSVPWM->_P_F_MidDuty)
        {
            F_Ttmp2 = pSVPWM->_P_F_MidDuty;
        }

        F_Txyz[0] = F_Ttmpsum;
        F_Txyz[1] = F_Ttmp2;
        F_Txyz[2] = 0.0f;

        if(pSVPWM->_O_Q32U_Five_Flag == 1U)
        {
            pSVPWM->_O_Q32U_Five_Flag_Real = 0U;
        }
        else
        {

        }
    }
    else
    {
        F_Ttmpsum = F_Ttmp1 + F_Ttmp2;
        if(F_Ttmpsum > pSVPWM->_P_F_MidDuty)
        {
            F_Ttmp1 = pSVPWM->_P_F_MidDuty*F_Ttmp1/F_Ttmpsum;
            F_Ttmp2 = pSVPWM->_P_F_MidDuty - F_Ttmp1;
        }
        
        F_Txyz[2] = 0.5f*(pSVPWM->_P_F_MaxDuty - F_Ttmp1 - F_Ttmp2);
        F_Txyz[1] = F_Txyz[2] + F_Ttmp2;
        F_Txyz[0] = F_Txyz[1] + F_Ttmp1;
        
        if((pSVPWM->_O_Q32U_Five_Flag == 1U) && (F_Txyz[2] < 0.15f))
        {
            pSVPWM->_O_Q32U_Five_Flag_Real = 1U;
        }
        else
        {
            
        }
    }

    pSVPWM->_O_F_Dutya = F_Txyz[Txyz_Table[0][pSVPWM->_O_Q32U_Sector]];
    pSVPWM->_O_F_Dutyb = F_Txyz[Txyz_Table[1][pSVPWM->_O_Q32U_Sector]];
    pSVPWM->_O_F_Dutyc = F_Txyz[Txyz_Table[2][pSVPWM->_O_Q32U_Sector]];
}

/**********************************************************************************************
Function: MCFOC_OneShunt_Current_Cal_F
Description: 单电阻采样电流查表
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_OneShunt_Current_Cal_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe)
{
    pPMSMe->_V_F_Ia = pPMSMe->_I_F_Ishunt[Txyz_Table[0][pSVPWM->_O_Q32U_Sector]];
    pPMSMe->_V_F_Ib = pPMSMe->_I_F_Ishunt[Txyz_Table[1][pSVPWM->_O_Q32U_Sector]];
    pPMSMe->_V_F_Ic = pPMSMe->_I_F_Ishunt[Txyz_Table[2][pSVPWM->_O_Q32U_Sector]];
}

/**********************************************************************************************
Function: MCFOC_SVPWM_OneShunt_F
Description: 单电阻SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SVPWM_OneShunt_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe)
{
    float F_Utmp1 = 0.0f, F_Utmp2 = 0.0f, F_Utmp3 = 0.0f;
    float F_Ttmp1 = 0.0f, F_Ttmp2 = 0.0f, F_Ttmpsum = 0.0f;
    float F_Txyz[3] = {0.0f, 0.0f, 0.0f};
    float F_Delta_Ttmp[3] = {0.0f, 0.0f, 0.0f};
    Q32U_ Q32U_Ntmp1 = 0, Q32U_Ntmp2 = 0, Q32U_Ntmp3 = 0;
    
    F_Utmp1 = MATH_SQRT_THREE_F*pPMSMe->_V_F_Ubeta_Pre;
    F_Utmp2 = 0.5f*( 3.0f*pPMSMe->_V_F_Ualfa_Pre - F_Utmp1)*pPMSMe->_O_F_One_Over_Vbus;
    F_Utmp3 = 0.5f*(-3.0f*pPMSMe->_V_F_Ualfa_Pre - F_Utmp1)*pPMSMe->_O_F_One_Over_Vbus;
    F_Utmp1 = F_Utmp1*pPMSMe->_O_F_One_Over_Vbus;
    
    pSVPWM->_O_Q32U_Sector = 0U;
    if(F_Utmp1>0.0f){pSVPWM->_O_Q32U_Sector+=1U;}else{}
    if(F_Utmp2>0.0f){pSVPWM->_O_Q32U_Sector+=2U;}else{}
    if(F_Utmp3>0.0f){pSVPWM->_O_Q32U_Sector+=4U;}else{}
    switch(pSVPWM->_O_Q32U_Sector)
    {
        case 3U:{F_Ttmp1 =  F_Utmp2; F_Ttmp2 =  F_Utmp1;break;}
        case 1U:{F_Ttmp1 = -F_Utmp2; F_Ttmp2 = -F_Utmp3;break;}
        case 5U:{F_Ttmp1 =  F_Utmp1; F_Ttmp2 =  F_Utmp3;break;}
        case 4U:{F_Ttmp1 = -F_Utmp1; F_Ttmp2 = -F_Utmp2;break;}
        case 6U:{F_Ttmp1 =  F_Utmp3; F_Ttmp2 =  F_Utmp2;break;}
        case 2U:{F_Ttmp1 = -F_Utmp3; F_Ttmp2 = -F_Utmp1;break;}
        default:break;
    }
    
    F_Ttmpsum = F_Ttmp1 + F_Ttmp2;
    if(F_Ttmpsum > pSVPWM->_P_F_MaxDuty)
    {
        F_Ttmp1 = pSVPWM->_P_F_MaxDuty*F_Ttmp1/F_Ttmpsum;
        F_Ttmp2 = pSVPWM->_P_F_MaxDuty - F_Ttmp1;
    }else{}
    
    F_Txyz[0] = 0.25f*(1.0f - F_Ttmp1 - F_Ttmp2);
    F_Txyz[1] = F_Txyz[0] + 0.5f*F_Ttmp1;
    F_Txyz[2] = F_Txyz[1] + 0.5f*F_Ttmp2;
    
    if((F_Ttmp1 < pSVPWM->_P_F_MinDuty)&&(F_Ttmp2 < pSVPWM->_P_F_MinDuty))
    {
        F_Delta_Ttmp[0] =  0.5f*(pSVPWM->_P_F_MinDuty - F_Ttmp1);
        F_Delta_Ttmp[2] = -0.5f*(pSVPWM->_P_F_MinDuty - F_Ttmp2);
    }
    else if(F_Ttmp1 < pSVPWM->_P_F_MinDuty)
    {
        F_Delta_Ttmp[0] =  0.25f*(pSVPWM->_P_F_MinDuty - F_Ttmp1);
        F_Delta_Ttmp[1] = -0.25f*(pSVPWM->_P_F_MinDuty - F_Ttmp1);
        F_Delta_Ttmp[2] =  F_Delta_Ttmp[1];
    }
    else if(F_Ttmp2 < pSVPWM->_P_F_MinDuty)
    {
        F_Delta_Ttmp[1] =  0.25f*(pSVPWM->_P_F_MinDuty - F_Ttmp2);
        F_Delta_Ttmp[2] = -0.25f*(pSVPWM->_P_F_MinDuty - F_Ttmp2);
        F_Delta_Ttmp[0] =  F_Delta_Ttmp[1];
    }
    
    pSVPWM->_O_F_ADCTrigTime1 = F_Txyz[1] - F_Delta_Ttmp[1] - pSVPWM->_P_F_ADCSampleDuty;
    pSVPWM->_O_F_ADCTrigTime2 = F_Txyz[2] - F_Delta_Ttmp[2] - pSVPWM->_P_F_ADCSampleDuty;
    
    Q32U_Ntmp1 = Txyz_Table[0][pSVPWM->_O_Q32U_Sector];
    Q32U_Ntmp2 = Txyz_Table[1][pSVPWM->_O_Q32U_Sector];
    Q32U_Ntmp3 = Txyz_Table[2][pSVPWM->_O_Q32U_Sector];
    
    pSVPWM->_O_F_TaUp = F_Txyz[Q32U_Ntmp1] - F_Delta_Ttmp[Q32U_Ntmp1];
    pSVPWM->_O_F_TbUp = F_Txyz[Q32U_Ntmp2] - F_Delta_Ttmp[Q32U_Ntmp2];
    pSVPWM->_O_F_TcUp = F_Txyz[Q32U_Ntmp3] - F_Delta_Ttmp[Q32U_Ntmp3];
    pSVPWM->_O_F_TaDn = F_Txyz[Q32U_Ntmp1] + F_Delta_Ttmp[Q32U_Ntmp1];
    pSVPWM->_O_F_TbDn = F_Txyz[Q32U_Ntmp2] + F_Delta_Ttmp[Q32U_Ntmp2];
    pSVPWM->_O_F_TcDn = F_Txyz[Q32U_Ntmp3] + F_Delta_Ttmp[Q32U_Ntmp3];
    
    F_Txyz[2] = 0.5f*(1.0f - F_Ttmp1 - F_Ttmp2);
    F_Txyz[1] = F_Txyz[2] + F_Ttmp2;
    F_Txyz[0] = F_Txyz[1] + F_Ttmp1;
    
    pSVPWM->_O_F_Dutya = F_Txyz[Txyz_Table[0][pSVPWM->_O_Q32U_Sector]];
    pSVPWM->_O_F_Dutyb = F_Txyz[Txyz_Table[1][pSVPWM->_O_Q32U_Sector]];
    pSVPWM->_O_F_Dutyc = F_Txyz[Txyz_Table[2][pSVPWM->_O_Q32U_Sector]];
}


/*********************************死区电压重构*************************************/

/**********************************************************************************************
Function: MCFOC_Duty_Resolution_F
Description: 占空比重构
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Duty_Resolution_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe)
{
    float F_DT_Duty_tmpa = 0.0f, F_DT_Duty_tmpb = 0.0f, F_DT_Duty_tmpc = 0.0f;

    if(pPMSMe->_V_F_Ia >= pSVPWM->_P_F_DT_Current_TL)
    {
        F_DT_Duty_tmpa = pSVPWM->_P_F_DeadTimeDuty;
    }
    else if(pPMSMe->_V_F_Ia <= -pSVPWM->_P_F_DT_Current_TL)
    {
        F_DT_Duty_tmpa = -pSVPWM->_P_F_DeadTimeDuty;
    }
    else
    {

    }

    if(pPMSMe->_V_F_Ib >= pSVPWM->_P_F_DT_Current_TL)
    {
        F_DT_Duty_tmpb = pSVPWM->_P_F_DeadTimeDuty;
    }
    else if(pPMSMe->_V_F_Ib <= -pSVPWM->_P_F_DT_Current_TL)
    {
        F_DT_Duty_tmpb = -pSVPWM->_P_F_DeadTimeDuty;
    }
    else
    {

    }

    if(pPMSMe->_V_F_Ic >= pSVPWM->_P_F_DT_Current_TL)
    {
        F_DT_Duty_tmpc = pSVPWM->_P_F_DeadTimeDuty;
    }
    else if(pPMSMe->_V_F_Ic <= -pSVPWM->_P_F_DT_Current_TL)
    {
        F_DT_Duty_tmpc = -pSVPWM->_P_F_DeadTimeDuty;
    }
    else
    {

    }

    if((pSVPWM->_O_F_Dutya != 0.0f) && (pSVPWM->_O_F_Dutya != 1.0f))
    {
        pSVPWM->_O_F_Dutya -= F_DT_Duty_tmpa;
    }
    else
    {

    }

    if((pSVPWM->_O_F_Dutyb != 0.0f) && (pSVPWM->_O_F_Dutyb != 1.0f))
    {
        pSVPWM->_O_F_Dutyb -= F_DT_Duty_tmpb;
    }
    else
    {

    }

    if((pSVPWM->_O_F_Dutyc != 0.0f) && (pSVPWM->_O_F_Dutyc != 1.0f))
    {
        pSVPWM->_O_F_Dutyc -= F_DT_Duty_tmpc;
    }
    else
    {

    }
 
    pPMSMe->_V_F_Ualfa = pPMSMe->_O_F_Vbus*MATH_ONE_OVER_THREE_F
                       * (2.0f*pSVPWM->_O_F_Dutya - pSVPWM->_O_F_Dutyb - pSVPWM->_O_F_Dutyc);
    pPMSMe->_V_F_Ubeta = pPMSMe->_O_F_Vbus*MATH_ONE_OVER_SQRT_THREE_F
                       * (pSVPWM->_O_F_Dutyb - pSVPWM->_O_F_Dutyc);

    pPMSMe->_I_F_Ibus = pPMSMe->_V_F_Ia*pSVPWM->_O_F_Dutya
                      + pPMSMe->_V_F_Ib*pSVPWM->_O_F_Dutyb
                      + pPMSMe->_V_F_Ic*pSVPWM->_O_F_Dutyc;
}

/**********************************************************************************************
Function: MCFOC_DeadTime_COMP_F
Description: 死区补偿
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_DeadTime_COMP_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe)
{
    float F_DT_Duty_tmpa = 0.0f, F_DT_Duty_tmpb = 0.0f, F_DT_Duty_tmpc = 0.0f;

    if(pPMSMe->_V_F_Ia_Pre >= pSVPWM->_P_F_DT_Current_TL)
    {
        F_DT_Duty_tmpa = pSVPWM->_P_F_DeadTimeDuty;
    }
    else if(pPMSMe->_V_F_Ia_Pre <= -pSVPWM->_P_F_DT_Current_TL)
    {
        F_DT_Duty_tmpa = -pSVPWM->_P_F_DeadTimeDuty;
    }
    else
    {

    }

    if(pPMSMe->_V_F_Ib_Pre >= pSVPWM->_P_F_DT_Current_TL)
    {
        F_DT_Duty_tmpb = pSVPWM->_P_F_DeadTimeDuty;
    }
    else if(pPMSMe->_V_F_Ib_Pre <= -pSVPWM->_P_F_DT_Current_TL)
    {
        F_DT_Duty_tmpb = -pSVPWM->_P_F_DeadTimeDuty;
    }
    else
    {

    }

    if(pPMSMe->_V_F_Ic_Pre >= pSVPWM->_P_F_DT_Current_TL)
    {
        F_DT_Duty_tmpc = pSVPWM->_P_F_DeadTimeDuty;
    }
    else if(pPMSMe->_V_F_Ic_Pre <= -pSVPWM->_P_F_DT_Current_TL)
    {
        F_DT_Duty_tmpc = -pSVPWM->_P_F_DeadTimeDuty;
    }
    else
    {

    }

    if((pSVPWM->_O_F_Dutya != 0.0f) && (pSVPWM->_O_F_Dutya != 1.0f))
    {
        pSVPWM->_O_F_Dutya += F_DT_Duty_tmpa;
    }
    else
    {

    }

    if((pSVPWM->_O_F_Dutyb != 0.0f) && (pSVPWM->_O_F_Dutyb != 1.0f))
    {
        pSVPWM->_O_F_Dutyb += F_DT_Duty_tmpb;
    }
    else
    {

    }

    if((pSVPWM->_O_F_Dutyc != 0.0f) && (pSVPWM->_O_F_Dutyc != 1.0f))
    {
        pSVPWM->_O_F_Dutyc += F_DT_Duty_tmpc;
    }
    else
    {

    }
}
