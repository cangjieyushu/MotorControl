/*
*     File Name :                        mcfoc_svpwm_t
*     Library/Module Name :              mcfoc_t
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC算法
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "mcfoc_svpwm_t.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*********************************SVPWM*************************************/
static Q08U_ Txyz_Table[3][8] = 
//   2  6  1  4  3  5
{{0U,1U,0U,0U,2U,2U,1U,0U},
 {0U,0U,2U,1U,1U,0U,2U,0U},
 {0U,2U,1U,2U,0U,1U,0U,0U}};

void MCFOC_SVPWM_Init_T(ST_SVPWM_CONTROL_T* pSVPWM)
{
    pSVPWM->O_Q32U_Five_Flag_Real = 0U;
}

void MCFOC_SevFiv_Check_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    pSVPWM->FIVE_CHECK.Check_Flag.bit.Enable = 1U;
    pSVPWM->FIVE_CHECK.Check_Flag.bit.Condition_Set = (pPMSMe->O_Q14I_Modulation_Rate >= pSVPWM->FIVE_CHECK.P_Q14I_Check_TL);
    pSVPWM->FIVE_CHECK.Check_Flag.bit.Condition_Clear = (pPMSMe->O_Q14I_Modulation_Rate <= pSVPWM->FIVE_CHECK.P_Q14I_Clear_TL);
    pSVPWM->O_Q32U_Five_Flag = Check_Cal(&pSVPWM->FIVE_CHECK, pSVPWM->O_Q32U_Five_Flag);
}

void MCFOC_ThreeShunt_Current_Cal_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    switch(pSVPWM->O_Q32U_Sector)
    {
        case 3U:{pPMSMe->V_Q14I_Ia = - pPMSMe->V_Q14I_Ib - pPMSMe->V_Q14I_Ic;break;}
        case 1U:{pPMSMe->V_Q14I_Ib = - pPMSMe->V_Q14I_Ia - pPMSMe->V_Q14I_Ic;break;}
        case 5U:{pPMSMe->V_Q14I_Ib = - pPMSMe->V_Q14I_Ia - pPMSMe->V_Q14I_Ic;break;}
        case 4U:{pPMSMe->V_Q14I_Ic = - pPMSMe->V_Q14I_Ia - pPMSMe->V_Q14I_Ib;break;}
        case 6U:{pPMSMe->V_Q14I_Ic = - pPMSMe->V_Q14I_Ia - pPMSMe->V_Q14I_Ib;break;}
        case 2U:{pPMSMe->V_Q14I_Ia = - pPMSMe->V_Q14I_Ib - pPMSMe->V_Q14I_Ic;break;}
        default:break;
    }
}

void MCFOC_SVPWM_ThreeShunt_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    Q32I_ Q14I_Utmp1 = 0, Q14I_Utmp2 = 0, Q14I_Utmp3 = 0;
    Q32I_ Q14I_Ttmp1 = 0, Q14I_Ttmp2 = 0, Q14I_Ttmpsum = 0;
    Q32I_ Q14I_Txyz[3] = {0,0,0};
    
    Q14I_Utmp1 = MATH_SQRT_THREE_T(pPMSMe->V_Q14I_Ubeta_Pre);
    Q14I_Utmp2 = Q32I_RHT_15(( 3*pPMSMe->V_Q14I_Ualfa_Pre - Q14I_Utmp1)*pPMSMe->O_Q14I_One_Over_Vbus);
    Q14I_Utmp3 = Q32I_RHT_15((-3*pPMSMe->V_Q14I_Ualfa_Pre - Q14I_Utmp1)*pPMSMe->O_Q14I_One_Over_Vbus);
    Q14I_Utmp1 = Q32I_RHT_14(Q14I_Utmp1*pPMSMe->O_Q14I_One_Over_Vbus);
    
    pSVPWM->O_Q32U_Sector = 0U;
    if(Q14I_Utmp1>0){pSVPWM->O_Q32U_Sector+=1U;}else{}
    if(Q14I_Utmp2>0){pSVPWM->O_Q32U_Sector+=2U;}else{}
    if(Q14I_Utmp3>0){pSVPWM->O_Q32U_Sector+=4U;}else{}
    switch(pSVPWM->O_Q32U_Sector)
    {
        case 3U:{Q14I_Ttmp1 =  Q14I_Utmp2; Q14I_Ttmp2 =  Q14I_Utmp1;break;}
        case 1U:{Q14I_Ttmp1 = -Q14I_Utmp2; Q14I_Ttmp2 = -Q14I_Utmp3;break;}
        case 5U:{Q14I_Ttmp1 =  Q14I_Utmp1; Q14I_Ttmp2 =  Q14I_Utmp3;break;}
        case 4U:{Q14I_Ttmp1 = -Q14I_Utmp1; Q14I_Ttmp2 = -Q14I_Utmp2;break;}
        case 6U:{Q14I_Ttmp1 =  Q14I_Utmp3; Q14I_Ttmp2 =  Q14I_Utmp2;break;}
        case 2U:{Q14I_Ttmp1 = -Q14I_Utmp3; Q14I_Ttmp2 = -Q14I_Utmp1;break;}
        default:break;
    }

    if(pSVPWM->O_Q32U_Five_Flag_Real)
    {
        Q14I_Ttmpsum = Q14I_Ttmp1 + Q14I_Ttmp2;
        if(Q14I_Ttmpsum > pSVPWM->P_Q14U_MidDuty + Q32I_RHT_01(pSVPWM->P_Q14U_MinDuty))
        {
            Q14I_Ttmpsum = pSVPWM->P_Q14U_MaxDuty;
        }
        else if(Q14I_Ttmpsum > pSVPWM->P_Q14U_MidDuty)
        {
            Q14I_Ttmpsum = pSVPWM->P_Q14U_MidDuty;
        }
        else
        {
        
        }
        if(Q14I_Ttmp2 > pSVPWM->P_Q14U_MidDuty)
        {
            Q14I_Ttmp2 = pSVPWM->P_Q14U_MidDuty;
        }

        Q14I_Txyz[0] = Q14I_Ttmpsum;
        Q14I_Txyz[1] = Q14I_Ttmp2;
        Q14I_Txyz[2] = 0;

        if(pSVPWM->O_Q32U_Five_Flag == 0U)
        {
            pSVPWM->O_Q32U_Five_Flag_Real = 0U;
        }
        else
        {

        }
    }
    else
    {
        Q14I_Ttmpsum = Q14I_Ttmp1 + Q14I_Ttmp2;
        if(Q14I_Ttmpsum > pSVPWM->P_Q14U_MidDuty)
        {
            Q14I_Ttmp1 = pSVPWM->P_Q14U_MidDuty*Q14I_Ttmp1/Q14I_Ttmpsum;
            Q14I_Ttmp2 = pSVPWM->P_Q14U_MidDuty - Q14I_Ttmp1;
        }
        
        Q14I_Txyz[2] = Q32I_RHT_01(pSVPWM->P_Q14U_MaxDuty - Q14I_Ttmp1 - Q14I_Ttmp2);
        Q14I_Txyz[1] = Q14I_Txyz[2] + Q14I_Ttmp2;
        Q14I_Txyz[0] = Q14I_Txyz[1] + Q14I_Ttmp1;
        
        if((pSVPWM->O_Q32U_Five_Flag == 1U) && (Q14I_Txyz[2] < 2458))
        {
            pSVPWM->O_Q32U_Five_Flag_Real = 1U;
        }
        else
        {
            
        }
    }

    pSVPWM->O_Q14U_Dutya = Q14I_Txyz[Txyz_Table[0][pSVPWM->O_Q32U_Sector]];
    pSVPWM->O_Q14U_Dutyb = Q14I_Txyz[Txyz_Table[1][pSVPWM->O_Q32U_Sector]];
    pSVPWM->O_Q14U_Dutyc = Q14I_Txyz[Txyz_Table[2][pSVPWM->O_Q32U_Sector]];
}

void MCFOC_OneShunt_Current_Cal_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    pPMSMe->V_Q14I_Ia = pPMSMe->I_Q14I_Ishunt[Txyz_Table[0][pSVPWM->O_Q32U_Sector]];
    pPMSMe->V_Q14I_Ib = pPMSMe->I_Q14I_Ishunt[Txyz_Table[1][pSVPWM->O_Q32U_Sector]];
    pPMSMe->V_Q14I_Ic = pPMSMe->I_Q14I_Ishunt[Txyz_Table[2][pSVPWM->O_Q32U_Sector]];
}

void MCFOC_SVPWM_OneShunt_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    Q32I_ Q14I_Utmp1 = 0, Q14I_Utmp2 = 0, Q14I_Utmp3 = 0;
    Q32I_ Q14I_Ttmp1 = 0, Q14I_Ttmp2 = 0, Q14I_Ttmpsum = 0;
    Q32I_ Q14I_Txyz[3] = {0, 0, 0};
    Q32I_ Q14I_Delta_Ttmp[3] = {0, 0, 0};
    Q32U_ Q32U_Ntmp1 = 0, Q32U_Ntmp2 = 0, Q32U_Ntmp3 = 0;
    
    Q14I_Utmp1 = MATH_SQRT_THREE_T(pPMSMe->V_Q14I_Ubeta_Pre);
    Q14I_Utmp2 = Q32I_RHT_15(( 3*pPMSMe->V_Q14I_Ualfa_Pre - Q14I_Utmp1)*pPMSMe->O_Q14I_One_Over_Vbus);
    Q14I_Utmp3 = Q32I_RHT_15((-3*pPMSMe->V_Q14I_Ualfa_Pre - Q14I_Utmp1)*pPMSMe->O_Q14I_One_Over_Vbus);
    Q14I_Utmp1 = Q32I_RHT_14(Q14I_Utmp1*pPMSMe->O_Q14I_One_Over_Vbus);
    
    pSVPWM->O_Q32U_Sector = 0U;
    if(Q14I_Utmp1>0){pSVPWM->O_Q32U_Sector+=1U;}else{}
    if(Q14I_Utmp2>0){pSVPWM->O_Q32U_Sector+=2U;}else{}
    if(Q14I_Utmp3>0){pSVPWM->O_Q32U_Sector+=4U;}else{}
    switch(pSVPWM->O_Q32U_Sector)
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
    if(Q14I_Ttmpsum > pSVPWM->P_Q14U_MaxDuty)
    {
        Q14I_Ttmp1 = pSVPWM->P_Q14U_MaxDuty*Q14I_Ttmp1/Q14I_Ttmpsum;
        Q14I_Ttmp2 = pSVPWM->P_Q14U_MaxDuty - Q14I_Ttmp1;
    }else{}
    
    Q14I_Txyz[0] = Q32I_RHT_02(16384 - Q14I_Ttmp1 - Q14I_Ttmp2);
    Q14I_Txyz[1] = Q14I_Txyz[0] + Q32I_RHT_01(Q14I_Ttmp1);
    Q14I_Txyz[2] = Q14I_Txyz[1] + Q32I_RHT_01(Q14I_Ttmp2);
    
    if((Q14I_Ttmp1 < pSVPWM->P_Q14U_MinDuty)&&(Q14I_Ttmp2 < pSVPWM->P_Q14U_MinDuty))
    {
        Q14I_Delta_Ttmp[0] =  Q32I_RHT_01(pSVPWM->P_Q14U_MinDuty - Q14I_Ttmp1);
        Q14I_Delta_Ttmp[2] = -Q32I_RHT_01(pSVPWM->P_Q14U_MinDuty - Q14I_Ttmp2);
    }
    else if(Q14I_Ttmp1 < pSVPWM->P_Q14U_MinDuty)
    {
        Q14I_Delta_Ttmp[0] =  Q32I_RHT_02(pSVPWM->P_Q14U_MinDuty - Q14I_Ttmp1);
        Q14I_Delta_Ttmp[1] = -Q32I_RHT_02(pSVPWM->P_Q14U_MinDuty - Q14I_Ttmp1);
        Q14I_Delta_Ttmp[2] =  Q14I_Delta_Ttmp[1];
    }
    else if(Q14I_Ttmp2 < pSVPWM->P_Q14U_MinDuty)
    {
        Q14I_Delta_Ttmp[1] =  Q32I_RHT_02(pSVPWM->P_Q14U_MinDuty - Q14I_Ttmp2);
        Q14I_Delta_Ttmp[2] = -Q32I_RHT_02(pSVPWM->P_Q14U_MinDuty - Q14I_Ttmp2);
        Q14I_Delta_Ttmp[0] =  Q14I_Delta_Ttmp[1];
    }
    
    pSVPWM->O_Q14U_ADCTrigTime1 = Q14I_Txyz[1] - Q14I_Delta_Ttmp[1] - pSVPWM->P_Q14U_ADCSampleDuty;
    pSVPWM->O_Q14U_ADCTrigTime2 = Q14I_Txyz[2] - Q14I_Delta_Ttmp[2] - pSVPWM->P_Q14U_ADCSampleDuty;
    
    Q32U_Ntmp1 = Txyz_Table[0][pSVPWM->O_Q32U_Sector];
    Q32U_Ntmp2 = Txyz_Table[1][pSVPWM->O_Q32U_Sector];
    Q32U_Ntmp3 = Txyz_Table[2][pSVPWM->O_Q32U_Sector];
    
    pSVPWM->O_Q14U_TaUp = Q14I_Txyz[Q32U_Ntmp1] - Q14I_Delta_Ttmp[Q32U_Ntmp1];
    pSVPWM->O_Q14U_TbUp = Q14I_Txyz[Q32U_Ntmp2] - Q14I_Delta_Ttmp[Q32U_Ntmp2];
    pSVPWM->O_Q14U_TcUp = Q14I_Txyz[Q32U_Ntmp3] - Q14I_Delta_Ttmp[Q32U_Ntmp3];
    pSVPWM->O_Q14U_TaDn = Q14I_Txyz[Q32U_Ntmp1] + Q14I_Delta_Ttmp[Q32U_Ntmp1];
    pSVPWM->O_Q14U_TbDn = Q14I_Txyz[Q32U_Ntmp2] + Q14I_Delta_Ttmp[Q32U_Ntmp2];
    pSVPWM->O_Q14U_TcDn = Q14I_Txyz[Q32U_Ntmp3] + Q14I_Delta_Ttmp[Q32U_Ntmp3];
    
    Q14I_Txyz[2] = Q32I_RHT_01(16384 - Q14I_Ttmp1 - Q14I_Ttmp2);
    Q14I_Txyz[1] = Q14I_Txyz[2] + Q14I_Ttmp2;
    Q14I_Txyz[0] = Q14I_Txyz[1] + Q14I_Ttmp1;
    
    pSVPWM->O_Q14U_Dutya = Q14I_Txyz[Txyz_Table[0][pSVPWM->O_Q32U_Sector]];
    pSVPWM->O_Q14U_Dutyb = Q14I_Txyz[Txyz_Table[1][pSVPWM->O_Q32U_Sector]];
    pSVPWM->O_Q14U_Dutyc = Q14I_Txyz[Txyz_Table[2][pSVPWM->O_Q32U_Sector]];
}


/*********************************死区电压重构*************************************/
void MCFOC_SVPWM_Duty_Refactor_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    Q32I_ Q14I_DT_Duty_tmpa = 0, Q14I_DT_Duty_tmpb = 0, Q14I_DT_Duty_tmpc = 0;

    if(pPMSMe->V_Q14I_Ia >= pSVPWM->P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpa = pSVPWM->P_Q14U_DeadTimeDuty;
    }
    else if(pPMSMe->V_Q14I_Ia <= -pSVPWM->P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpa = -pSVPWM->P_Q14U_DeadTimeDuty;
    }
    else
    {

    }

    if(pPMSMe->V_Q14I_Ib >= pSVPWM->P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpb = pSVPWM->P_Q14U_DeadTimeDuty;
    }
    else if(pPMSMe->V_Q14I_Ib <= -pSVPWM->P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpb = -pSVPWM->P_Q14U_DeadTimeDuty;
    }
    else
    {

    }

    if(pPMSMe->V_Q14I_Ic >= pSVPWM->P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpc = pSVPWM->P_Q14U_DeadTimeDuty;
    }
    else if(pPMSMe->V_Q14I_Ic <= -pSVPWM->P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpc = -pSVPWM->P_Q14U_DeadTimeDuty;
    }
    else
    {

    }

    if((pSVPWM->O_Q14U_Dutya != 0) && (pSVPWM->O_Q14U_Dutya != 16384))
    {
        pSVPWM->O_Q14U_Dutya -= Q14I_DT_Duty_tmpa;
    }
    else
    {

    }

    if((pSVPWM->O_Q14U_Dutyb != 0) && (pSVPWM->O_Q14U_Dutyb != 16384))
    {
        pSVPWM->O_Q14U_Dutyb -= Q14I_DT_Duty_tmpb;
    }
    else
    {

    }

    if((pSVPWM->O_Q14U_Dutyc != 0) && (pSVPWM->O_Q14U_Dutyc != 16384))
    {
        pSVPWM->O_Q14U_Dutyc -= Q14I_DT_Duty_tmpc;
    }
    else
    {

    }
 
    pPMSMe->V_Q14I_Ualfa = Q32I_RHT_14(pPMSMe->O_Q14I_Vbus
    *MATH_ONE_OVER_THREE_T(2*pSVPWM->O_Q14U_Dutya - pSVPWM->O_Q14U_Dutyb - pSVPWM->O_Q14U_Dutyc));
    pPMSMe->V_Q14I_Ubeta = Q32I_RHT_14(pPMSMe->O_Q14I_Vbus
    *MATH_ONE_OVER_SQRT_THREE_T(pSVPWM->O_Q14U_Dutyb - pSVPWM->O_Q14U_Dutyc));

    pPMSMe->I_Q14I_Ibus = Q32I_RHT_14(pPMSMe->V_Q14I_Ia*pSVPWM->O_Q14U_Dutya
                                     + pPMSMe->V_Q14I_Ib*pSVPWM->O_Q14U_Dutyb
                                     + pPMSMe->V_Q14I_Ic*pSVPWM->O_Q14U_Dutyc);
}

void MCFOC_SVPWM_DeadTime_Compensate_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe)
{
    Q32I_ Q14I_DT_Duty_tmpa = 0, Q14I_DT_Duty_tmpb = 0, Q14I_DT_Duty_tmpc = 0;

    if(pPMSMe->V_Q14I_Ia_Pre >= pSVPWM->P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpa = pSVPWM->P_Q14U_DeadTimeDuty;
    }
    else if(pPMSMe->V_Q14I_Ia_Pre <= -pSVPWM->P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpa = -pSVPWM->P_Q14U_DeadTimeDuty;
    }
    else
    {

    }

    if(pPMSMe->V_Q14I_Ib_Pre >= pSVPWM->P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpb = pSVPWM->P_Q14U_DeadTimeDuty;
    }
    else if(pPMSMe->V_Q14I_Ib_Pre <= -pSVPWM->P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpb = -pSVPWM->P_Q14U_DeadTimeDuty;
    }
    else
    {

    }

    if(pPMSMe->V_Q14I_Ic_Pre >= pSVPWM->P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpc = pSVPWM->P_Q14U_DeadTimeDuty;
    }
    else if(pPMSMe->V_Q14I_Ic_Pre <= -pSVPWM->P_Q14I_DT_Current_TL)
    {
        Q14I_DT_Duty_tmpc = -pSVPWM->P_Q14U_DeadTimeDuty;
    }
    else
    {

    }

    if((pSVPWM->O_Q14U_Dutya != 0) && (pSVPWM->O_Q14U_Dutya != 16384))
    {
        pSVPWM->O_Q14U_Dutya += Q14I_DT_Duty_tmpa;
    }
    else
    {

    }

    if((pSVPWM->O_Q14U_Dutyb != 0) && (pSVPWM->O_Q14U_Dutyb != 16384))
    {
        pSVPWM->O_Q14U_Dutyb += Q14I_DT_Duty_tmpb;
    }
    else
    {

    }

    if((pSVPWM->O_Q14U_Dutyc != 0) && (pSVPWM->O_Q14U_Dutyc != 16384))
    {
        pSVPWM->O_Q14U_Dutyc += Q14I_DT_Duty_tmpc;
    }
    else
    {

    }
}
