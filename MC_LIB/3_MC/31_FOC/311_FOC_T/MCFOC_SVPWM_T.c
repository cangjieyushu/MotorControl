/**************************************************************************************************
*     File Name :                        MCFOC_SVPWM_T.c
*     Library/Module Name :              MCFOC_T
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC算法源文件
**************************************************************************************************/

#include "MCFOC_SVPWM_T.h"


/*********************************SVPWM*************************************/

static Q08U_ Txyz_Table[3][8] = 
//   2  6  1  4  3  5
{{0U,1U,0U,0U,2U,2U,1U,0U},
 {0U,0U,2U,1U,1U,0U,2U,0U},
 {0U,2U,1U,2U,0U,1U,0U,0U}};

/**********************************************************************************************
Function: MCFOC_SVPWM_Init_T
Description: SVPWM初始化
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SVPWM_Init_T(ST_SVPWM_CONTROL_T* pSVPWM)
{
    pSVPWM->_O_Q32U_Five_Flag_Real = 0U;
}

/**********************************************************************************************
Function: MCFOC_Five_Cal_T
Description: 五段式切换判断
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Five_Cal_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    pSVPWM->FIVE_CHECK.Check_Flag.bit.Enable = 1U;
    pSVPWM->FIVE_CHECK.Check_Flag.bit.Condition_Set = (pPMSMe->_O_Q14I_Modulation_Rate >= pSVPWM->FIVE_CHECK._P_Q14I_Check_TL);
    pSVPWM->FIVE_CHECK.Check_Flag.bit.Condition_Clear = (pPMSMe->_O_Q14I_Modulation_Rate <= pSVPWM->FIVE_CHECK._P_Q14I_Clear_TL);
    pSVPWM->_O_Q32U_Five_Flag = Check_Cal(&pSVPWM->FIVE_CHECK, pSVPWM->_O_Q32U_Five_Flag);
}

/**********************************************************************************************
Function: MCFOC_ThreeShunt_Current_Cal_T
Description: 三电阻采样电流查表
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ThreeShunt_Current_Cal_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    switch(pSVPWM->_O_Q32U_Sector)
    {
        case 3U:{pPMSMe->_V_Q14I_Ia = - pPMSMe->_V_Q14I_Ib - pPMSMe->_V_Q14I_Ic;break;}
        case 1U:{pPMSMe->_V_Q14I_Ib = - pPMSMe->_V_Q14I_Ia - pPMSMe->_V_Q14I_Ic;break;}
        case 5U:{pPMSMe->_V_Q14I_Ib = - pPMSMe->_V_Q14I_Ia - pPMSMe->_V_Q14I_Ic;break;}
        case 4U:{pPMSMe->_V_Q14I_Ic = - pPMSMe->_V_Q14I_Ia - pPMSMe->_V_Q14I_Ib;break;}
        case 6U:{pPMSMe->_V_Q14I_Ic = - pPMSMe->_V_Q14I_Ia - pPMSMe->_V_Q14I_Ib;break;}
        case 2U:{pPMSMe->_V_Q14I_Ia = - pPMSMe->_V_Q14I_Ib - pPMSMe->_V_Q14I_Ic;break;}
        default:break;
    }
}

/**********************************************************************************************
Function: MCFOC_SVPWM_ThreeShunt_T
Description: 三电阻SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SVPWM_ThreeShunt_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    Q32I_ Q14I_Utmp1 = 0, Q14I_Utmp2 = 0, Q14I_Utmp3 = 0;
    Q32I_ Q14I_Ttmp1 = 0, Q14I_Ttmp2 = 0, Q14I_Ttmpsum = 0;
    Q32I_ Q14I_Txyz[3] = {0,0,0};
    
    Q14I_Utmp1 = MATH_SQRT_THREE_T(pPMSMe->_V_Q14I_Ubeta_Pre);
    Q14I_Utmp2 = Q32I_RHT_15(( 3*pPMSMe->_V_Q14I_Ualfa_Pre - Q14I_Utmp1)*pPMSMe->_O_Q14I_One_Over_Vbus);
    Q14I_Utmp3 = Q32I_RHT_15((-3*pPMSMe->_V_Q14I_Ualfa_Pre - Q14I_Utmp1)*pPMSMe->_O_Q14I_One_Over_Vbus);
    Q14I_Utmp1 = Q32I_RHT_14(Q14I_Utmp1*pPMSMe->_O_Q14I_One_Over_Vbus);
    
    pSVPWM->_O_Q32U_Sector = 0U;
    if(Q14I_Utmp1>0){pSVPWM->_O_Q32U_Sector+=1U;}else{}
    if(Q14I_Utmp2>0){pSVPWM->_O_Q32U_Sector+=2U;}else{}
    if(Q14I_Utmp3>0){pSVPWM->_O_Q32U_Sector+=4U;}else{}
    switch(pSVPWM->_O_Q32U_Sector)
    {
        case 3U:{Q14I_Ttmp1 =  Q14I_Utmp2; Q14I_Ttmp2 =  Q14I_Utmp1;break;}
        case 1U:{Q14I_Ttmp1 = -Q14I_Utmp2; Q14I_Ttmp2 = -Q14I_Utmp3;break;}
        case 5U:{Q14I_Ttmp1 =  Q14I_Utmp1; Q14I_Ttmp2 =  Q14I_Utmp3;break;}
        case 4U:{Q14I_Ttmp1 = -Q14I_Utmp1; Q14I_Ttmp2 = -Q14I_Utmp2;break;}
        case 6U:{Q14I_Ttmp1 =  Q14I_Utmp3; Q14I_Ttmp2 =  Q14I_Utmp2;break;}
        case 2U:{Q14I_Ttmp1 = -Q14I_Utmp3; Q14I_Ttmp2 = -Q14I_Utmp1;break;}
        default:break;
    }

    if(pSVPWM->_O_Q32U_Five_Flag_Real)
    {
        Q14I_Ttmpsum = Q14I_Ttmp1 + Q14I_Ttmp2;
        if(Q14I_Ttmpsum > pSVPWM->_P_Q14U_MidDuty + Q32I_RHT_01(pSVPWM->_P_Q14U_MinDuty))
        {
            Q14I_Ttmpsum = pSVPWM->_P_Q14U_MaxDuty;
        }
        else if(Q14I_Ttmpsum > pSVPWM->_P_Q14U_MidDuty)
        {
            Q14I_Ttmpsum = pSVPWM->_P_Q14U_MidDuty;
        }
        else
        {
        
        }
        if(Q14I_Ttmp2 > pSVPWM->_P_Q14U_MidDuty)
        {
            Q14I_Ttmp2 = pSVPWM->_P_Q14U_MidDuty;
        }

        Q14I_Txyz[0] = Q14I_Ttmpsum;
        Q14I_Txyz[1] = Q14I_Ttmp2;
        Q14I_Txyz[2] = 0;

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
        Q14I_Ttmpsum = Q14I_Ttmp1 + Q14I_Ttmp2;
        if(Q14I_Ttmpsum > pSVPWM->_P_Q14U_MidDuty)
        {
            Q14I_Ttmp1 = pSVPWM->_P_Q14U_MidDuty*Q14I_Ttmp1/Q14I_Ttmpsum;
            Q14I_Ttmp2 = pSVPWM->_P_Q14U_MidDuty - Q14I_Ttmp1;
        }
        
        Q14I_Txyz[2] = Q32I_RHT_01(pSVPWM->_P_Q14U_MaxDuty - Q14I_Ttmp1 - Q14I_Ttmp2);
        Q14I_Txyz[1] = Q14I_Txyz[2] + Q14I_Ttmp2;
        Q14I_Txyz[0] = Q14I_Txyz[1] + Q14I_Ttmp1;
        
        if((pSVPWM->_O_Q32U_Five_Flag == 1U) && (Q14I_Txyz[2] < 2458))
        {
            pSVPWM->_O_Q32U_Five_Flag_Real = 1U;
        }
        else
        {
            
        }
    }

    pSVPWM->_O_Q14U_Dutya = Q14I_Txyz[Txyz_Table[0][pSVPWM->_O_Q32U_Sector]];
    pSVPWM->_O_Q14U_Dutyb = Q14I_Txyz[Txyz_Table[1][pSVPWM->_O_Q32U_Sector]];
    pSVPWM->_O_Q14U_Dutyc = Q14I_Txyz[Txyz_Table[2][pSVPWM->_O_Q32U_Sector]];
}

/**********************************************************************************************
Function: MCFOC_OneShunt_Current_Cal_T
Description: 单电阻采样电流查表
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_OneShunt_Current_Cal_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    pPMSMe->_V_Q14I_Ia = pPMSMe->_I_Q14I_Ishunt[Txyz_Table[0][pSVPWM->_O_Q32U_Sector]];
    pPMSMe->_V_Q14I_Ib = pPMSMe->_I_Q14I_Ishunt[Txyz_Table[1][pSVPWM->_O_Q32U_Sector]];
    pPMSMe->_V_Q14I_Ic = pPMSMe->_I_Q14I_Ishunt[Txyz_Table[2][pSVPWM->_O_Q32U_Sector]];
}

/**********************************************************************************************
Function: MCFOC_SVPWM_OneShunt_T
Description: 单电阻SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SVPWM_OneShunt_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    Q32I_ Q14I_Utmp1 = 0, Q14I_Utmp2 = 0, Q14I_Utmp3 = 0;
    Q32I_ Q14I_Ttmp1 = 0, Q14I_Ttmp2 = 0, Q14I_Ttmpsum = 0;
    Q32I_ Q14I_Txyz[3] = {0, 0, 0};
    Q32I_ Q14I_Delta_Ttmp[3] = {0, 0, 0};
    Q32U_ Q32U_Ntmp1 = 0, Q32U_Ntmp2 = 0, Q32U_Ntmp3 = 0;
    
    Q14I_Utmp1 = MATH_SQRT_THREE_T(pPMSMe->_V_Q14I_Ubeta_Pre);
    Q14I_Utmp2 = Q32I_RHT_15(( 3*pPMSMe->_V_Q14I_Ualfa_Pre - Q14I_Utmp1)*pPMSMe->_O_Q14I_One_Over_Vbus);
    Q14I_Utmp3 = Q32I_RHT_15((-3*pPMSMe->_V_Q14I_Ualfa_Pre - Q14I_Utmp1)*pPMSMe->_O_Q14I_One_Over_Vbus);
    Q14I_Utmp1 = Q32I_RHT_14(Q14I_Utmp1*pPMSMe->_O_Q14I_One_Over_Vbus);
    
    pSVPWM->_O_Q32U_Sector = 0U;
    if(Q14I_Utmp1>0){pSVPWM->_O_Q32U_Sector+=1U;}else{}
    if(Q14I_Utmp2>0){pSVPWM->_O_Q32U_Sector+=2U;}else{}
    if(Q14I_Utmp3>0){pSVPWM->_O_Q32U_Sector+=4U;}else{}
    switch(pSVPWM->_O_Q32U_Sector)
    {
        case 3U:{Q14I_Ttmp1 =  Q14I_Utmp2; Q14I_Ttmp2 =  Q14I_Utmp1;break;}
        case 1U:{Q14I_Ttmp1 = -Q14I_Utmp2; Q14I_Ttmp2 = -Q14I_Utmp3;break;}
        case 5U:{Q14I_Ttmp1 =  Q14I_Utmp1; Q14I_Ttmp2 =  Q14I_Utmp3;break;}
        case 4U:{Q14I_Ttmp1 = -Q14I_Utmp1; Q14I_Ttmp2 = -Q14I_Utmp2;break;}
        case 6U:{Q14I_Ttmp1 =  Q14I_Utmp3; Q14I_Ttmp2 =  Q14I_Utmp2;break;}
        case 2U:{Q14I_Ttmp1 = -Q14I_Utmp3; Q14I_Ttmp2 = -Q14I_Utmp1;break;}
        default:break;
    }
    
    Q14I_Ttmpsum = Q14I_Ttmp1 + Q14I_Ttmp2;
    if(Q14I_Ttmpsum > pSVPWM->_P_Q14U_MaxDuty)
    {
        Q14I_Ttmp1 = pSVPWM->_P_Q14U_MaxDuty*Q14I_Ttmp1/Q14I_Ttmpsum;
        Q14I_Ttmp2 = pSVPWM->_P_Q14U_MaxDuty - Q14I_Ttmp1;
    }else{}
    
    Q14I_Txyz[0] = Q32I_RHT_02(16384 - Q14I_Ttmp1 - Q14I_Ttmp2);
    Q14I_Txyz[1] = Q14I_Txyz[0] + Q32I_RHT_01(Q14I_Ttmp1);
    Q14I_Txyz[2] = Q14I_Txyz[1] + Q32I_RHT_01(Q14I_Ttmp2);
    
    if((Q14I_Ttmp1 < pSVPWM->_P_Q14U_MinDuty)&&(Q14I_Ttmp2 < pSVPWM->_P_Q14U_MinDuty))
    {
        Q14I_Delta_Ttmp[0] =  Q32I_RHT_01(pSVPWM->_P_Q14U_MinDuty - Q14I_Ttmp1);
        Q14I_Delta_Ttmp[2] = -Q32I_RHT_01(pSVPWM->_P_Q14U_MinDuty - Q14I_Ttmp2);
    }
    else if(Q14I_Ttmp1 < pSVPWM->_P_Q14U_MinDuty)
    {
        Q14I_Delta_Ttmp[0] =  Q32I_RHT_02(pSVPWM->_P_Q14U_MinDuty - Q14I_Ttmp1);
        Q14I_Delta_Ttmp[1] = -Q32I_RHT_02(pSVPWM->_P_Q14U_MinDuty - Q14I_Ttmp1);
        Q14I_Delta_Ttmp[2] =  Q14I_Delta_Ttmp[1];
    }
    else if(Q14I_Ttmp2 < pSVPWM->_P_Q14U_MinDuty)
    {
        Q14I_Delta_Ttmp[1] =  Q32I_RHT_02(pSVPWM->_P_Q14U_MinDuty - Q14I_Ttmp2);
        Q14I_Delta_Ttmp[2] = -Q32I_RHT_02(pSVPWM->_P_Q14U_MinDuty - Q14I_Ttmp2);
        Q14I_Delta_Ttmp[0] =  Q14I_Delta_Ttmp[1];
    }
    
    pSVPWM->_O_Q14U_ADCTrigTime1 = Q14I_Txyz[1] - Q14I_Delta_Ttmp[1] - pSVPWM->_P_Q14U_ADCSampleDuty;
    pSVPWM->_O_Q14U_ADCTrigTime2 = Q14I_Txyz[2] - Q14I_Delta_Ttmp[2] - pSVPWM->_P_Q14U_ADCSampleDuty;
    
    Q32U_Ntmp1 = Txyz_Table[0][pSVPWM->_O_Q32U_Sector];
    Q32U_Ntmp2 = Txyz_Table[1][pSVPWM->_O_Q32U_Sector];
    Q32U_Ntmp3 = Txyz_Table[2][pSVPWM->_O_Q32U_Sector];
    
    pSVPWM->_O_Q14U_TaUp = Q14I_Txyz[Q32U_Ntmp1] - Q14I_Delta_Ttmp[Q32U_Ntmp1];
    pSVPWM->_O_Q14U_TbUp = Q14I_Txyz[Q32U_Ntmp2] - Q14I_Delta_Ttmp[Q32U_Ntmp2];
    pSVPWM->_O_Q14U_TcUp = Q14I_Txyz[Q32U_Ntmp3] - Q14I_Delta_Ttmp[Q32U_Ntmp3];
    pSVPWM->_O_Q14U_TaDn = Q14I_Txyz[Q32U_Ntmp1] + Q14I_Delta_Ttmp[Q32U_Ntmp1];
    pSVPWM->_O_Q14U_TbDn = Q14I_Txyz[Q32U_Ntmp2] + Q14I_Delta_Ttmp[Q32U_Ntmp2];
    pSVPWM->_O_Q14U_TcDn = Q14I_Txyz[Q32U_Ntmp3] + Q14I_Delta_Ttmp[Q32U_Ntmp3];
    
    Q14I_Txyz[2] = Q32I_RHT_01(16384 - Q14I_Ttmp1 - Q14I_Ttmp2);
    Q14I_Txyz[1] = Q14I_Txyz[2] + Q14I_Ttmp2;
    Q14I_Txyz[0] = Q14I_Txyz[1] + Q14I_Ttmp1;
    
    pSVPWM->_O_Q14U_Dutya = Q14I_Txyz[Txyz_Table[0][pSVPWM->_O_Q32U_Sector]];
    pSVPWM->_O_Q14U_Dutyb = Q14I_Txyz[Txyz_Table[1][pSVPWM->_O_Q32U_Sector]];
    pSVPWM->_O_Q14U_Dutyc = Q14I_Txyz[Txyz_Table[2][pSVPWM->_O_Q32U_Sector]];
}


/*********************************死区电压重构*************************************/

/**********************************************************************************************
Function: MCFOC_Duty_Resolution_T
Description: 占空比重构
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Duty_Resolution_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    Q32I_ Q14I_DT_Duty_tmpa = 0, Q14I_DT_Duty_tmpb = 0, Q14I_DT_Duty_tmpc = 0;

    if(pPMSMe->_V_Q14I_Ia >= pSVPWM->_P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpa = pSVPWM->_P_Q14U_DeadTimeDuty;
    }
    else if(pPMSMe->_V_Q14I_Ia <= -pSVPWM->_P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpa = -pSVPWM->_P_Q14U_DeadTimeDuty;
    }
    else
    {

    }

    if(pPMSMe->_V_Q14I_Ib >= pSVPWM->_P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpb = pSVPWM->_P_Q14U_DeadTimeDuty;
    }
    else if(pPMSMe->_V_Q14I_Ib <= -pSVPWM->_P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpb = -pSVPWM->_P_Q14U_DeadTimeDuty;
    }
    else
    {

    }

    if(pPMSMe->_V_Q14I_Ic >= pSVPWM->_P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpc = pSVPWM->_P_Q14U_DeadTimeDuty;
    }
    else if(pPMSMe->_V_Q14I_Ic <= -pSVPWM->_P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpc = -pSVPWM->_P_Q14U_DeadTimeDuty;
    }
    else
    {

    }

    if((pSVPWM->_O_Q14U_Dutya != 0) && (pSVPWM->_O_Q14U_Dutya != 16384))
    {
        pSVPWM->_O_Q14U_Dutya -= Q14I_DT_Duty_tmpa;
    }
    else
    {

    }

    if((pSVPWM->_O_Q14U_Dutyb != 0) && (pSVPWM->_O_Q14U_Dutyb != 16384))
    {
        pSVPWM->_O_Q14U_Dutyb -= Q14I_DT_Duty_tmpb;
    }
    else
    {

    }

    if((pSVPWM->_O_Q14U_Dutyc != 0) && (pSVPWM->_O_Q14U_Dutyc != 16384))
    {
        pSVPWM->_O_Q14U_Dutyc -= Q14I_DT_Duty_tmpc;
    }
    else
    {

    }
 
    pPMSMe->_V_Q14I_Ualfa = Q32I_RHT_14(pPMSMe->_O_Q14I_Vbus
    *MATH_ONE_OVER_THREE_T(2*pSVPWM->_O_Q14U_Dutya - pSVPWM->_O_Q14U_Dutyb - pSVPWM->_O_Q14U_Dutyc));
    pPMSMe->_V_Q14I_Ubeta = Q32I_RHT_14(pPMSMe->_O_Q14I_Vbus
    *MATH_ONE_OVER_SQRT_THREE_T(pSVPWM->_O_Q14U_Dutyb - pSVPWM->_O_Q14U_Dutyc));

    pPMSMe->_I_Q14I_Ibus = Q32I_RHT_14(pPMSMe->_V_Q14I_Ia*pSVPWM->_O_Q14U_Dutya
                                     + pPMSMe->_V_Q14I_Ib*pSVPWM->_O_Q14U_Dutyb
                                     + pPMSMe->_V_Q14I_Ic*pSVPWM->_O_Q14U_Dutyc);
}

/**********************************************************************************************
Function: MCFOC_DeadTime_COMP_T
Description: 死区补偿
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_DeadTime_COMP_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    Q32I_ Q14I_DT_Duty_tmpa = 0, Q14I_DT_Duty_tmpb = 0, Q14I_DT_Duty_tmpc = 0;

    if(pPMSMe->_V_Q14I_Ia_Pre >= pSVPWM->_P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpa = pSVPWM->_P_Q14U_DeadTimeDuty;
    }
    else if(pPMSMe->_V_Q14I_Ia_Pre <= -pSVPWM->_P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpa = -pSVPWM->_P_Q14U_DeadTimeDuty;
    }
    else
    {

    }

    if(pPMSMe->_V_Q14I_Ib_Pre >= pSVPWM->_P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpb = pSVPWM->_P_Q14U_DeadTimeDuty;
    }
    else if(pPMSMe->_V_Q14I_Ib_Pre <= -pSVPWM->_P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpb = -pSVPWM->_P_Q14U_DeadTimeDuty;
    }
    else
    {

    }

    if(pPMSMe->_V_Q14I_Ic_Pre >= pSVPWM->_P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpc = pSVPWM->_P_Q14U_DeadTimeDuty;
    }
    else if(pPMSMe->_V_Q14I_Ic_Pre <= -pSVPWM->_P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpc = -pSVPWM->_P_Q14U_DeadTimeDuty;
    }
    else
    {

    }

    if((pSVPWM->_O_Q14U_Dutya != 0) && (pSVPWM->_O_Q14U_Dutya != 16384))
    {
        pSVPWM->_O_Q14U_Dutya += Q14I_DT_Duty_tmpa;
    }
    else
    {

    }

    if((pSVPWM->_O_Q14U_Dutyb != 0) && (pSVPWM->_O_Q14U_Dutyb != 16384))
    {
        pSVPWM->_O_Q14U_Dutyb += Q14I_DT_Duty_tmpb;
    }
    else
    {

    }

    if((pSVPWM->_O_Q14U_Dutyc != 0) && (pSVPWM->_O_Q14U_Dutyc != 16384))
    {
        pSVPWM->_O_Q14U_Dutyc += Q14I_DT_Duty_tmpc;
    }
    else
    {

    }
}
