/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
 
#include "MotorFoc.h"

EM_SECTOR_NUM Position_CW[6][2] = {sector_3, sector_5,
                                   sector_4, sector_6,
                                   sector_5, sector_1,
                                   sector_6, sector_2,
                                   sector_1, sector_3,
                                   sector_2, sector_4};

EM_SECTOR_NUM Last_Sector[6] = {sector_6, sector_1, sector_2, sector_3, sector_4, sector_5};
EM_SECTOR_NUM Next_Sector[6] = {sector_2, sector_3, sector_4, sector_5, sector_6, sector_1};

void Motor_Current_Offset_Check(ST_COMMON_CONTROL* pCOM, ST_FOC_PARAMETER* pFocPara)
{
    pFocPara->Q12I_I_Data_tmp += pFocPara->Q12I_I_Data[3];
    if(++pCOM->sq_cnt == pCOM->Q08U_iphase_offset_num)
    {
        pFocPara->Q12I_I_Offset = pFocPara->Q12I_I_Data_tmp/pCOM->sq_cnt;
        if((pFocPara->Q12I_I_Offset > pCOM->Q16U_iphase_offset_min)
        && (pFocPara->Q12I_I_Offset < pCOM->Q16U_iphase_offset_max))
        {
            pCOM->Motor_Flag.bit.current_offset_Succ = 1U;
        }
        else
        {
            pCOM->Motor_Flag.bit.current_offset_Fail = 1U;
        }
        pCOM->sq_cnt = 0U;
        pFocPara->Q12I_I_Data_tmp = 0;
    }
}

void Six_Pluse_Positon(ST_COMMON_CONTROL* pCOM)
{
	Q16U_ max_tmp = pCOM->Q12U_Position_Current_VAL[sector_1];
    Q08U_ max_index = sector_1;
    for(Q08U_ i=1U;i<6U;i++)
    {
        if(pCOM->Q12U_Position_Current_VAL[i] > max_tmp)
        {
            max_index = i;
            max_tmp = pCOM->Q12U_Position_Current_VAL[i];
        }
    }
    
    pCOM->Sector = Position_CW[max_index][1];
    if(pCOM->Q12U_Position_Current_VAL[Next_Sector[pCOM->Sector]] > pCOM->Q12U_Position_Current_VAL[Last_Sector[pCOM->Sector]])
    {
        pCOM->Sector = Next_Sector[pCOM->Sector];
    }
    else
    {
        pCOM->Sector = Last_Sector[pCOM->Sector];
    }
    
    pCOM->Motor_Flag.bit.motor_position_Fail = 0U;
    pCOM->Motor_Flag.bit.motor_position_Succ = 1U;
    for(Q08U_ j=0U;j<6U;j++)
    {
        if(pCOM->Q12U_Position_Current_VAL[j] < pCOM->Q16U_position_tl)
        {
            pCOM->Motor_Flag.bit.motor_position_Fail = 1U;
            pCOM->Motor_Flag.bit.motor_position_Succ = 0U;
        }
    }
}

void MotorFoc_Clark(ST_FOC_PARAMETER* pFocPara)
{
    pFocPara->Q14I_Ialfa = pFocPara->Q14I_Ia;
    pFocPara->Q14I_Ibeta = MATH_ONE_OVER_SQRT_THREE_U(pFocPara->Q14I_Ib - pFocPara->Q14I_Ic);
}

void MotorFoc_Park(ST_FOC_PARAMETER* pFocPara)
{
    pFocPara->Q14I_Id = Q32I_RHT_14( pFocPara->Q14I_Ialfa*pFocPara->Angle.Q14I_Cos + pFocPara->Q14I_Ibeta*pFocPara->Angle.Q14I_Sin); 
    pFocPara->Q14I_Iq = Q32I_RHT_14(-pFocPara->Q14I_Ialfa*pFocPara->Angle.Q14I_Sin + pFocPara->Q14I_Ibeta*pFocPara->Angle.Q14I_Cos);
}

void MotorFoc_Ipark(ST_FOC_PARAMETER* pFocPara)
{
    pFocPara->Q14I_Ualfa = Q32I_RHT_14(pFocPara->Q14I_Ud*pFocPara->Angle.Q14I_Cos - pFocPara->Q14I_Uq*pFocPara->Angle.Q14I_Sin);
    pFocPara->Q14I_Ubeta = Q32I_RHT_14(pFocPara->Q14I_Ud*pFocPara->Angle.Q14I_Sin + pFocPara->Q14I_Uq*pFocPara->Angle.Q14I_Cos);
}

static const Q08U_ ADC_Table[3][8] = 
{{0U,2U,0U,0U,1U,1U,2U,0U},
 {0U,0U,1U,2U,2U,0U,1U,0U},
 {0U,1U,2U,1U,0U,2U,0U,0U}};
void MotorFoc_Simple_Cal(ST_FOC_PARAMETER* pFocPara)
{
    pFocPara->Q12I_I_Data[0] = pFocPara->Q12I_I_Data[0] - pFocPara->Q12I_I_Offset;
    pFocPara->Q12I_I_Data[1] = pFocPara->Q12I_I_Offset - pFocPara->Q12I_I_Data[1];
    pFocPara->Q12I_I_Data[2] = - pFocPara->Q12I_I_Data[0] - pFocPara->Q12I_I_Data[1];
    pFocPara->Q14I_Ia = pFocPara->Q12I_I_Data[ADC_Table[0][pFocPara->Q08U_Sector]];
    pFocPara->Q14I_Ib = pFocPara->Q12I_I_Data[ADC_Table[1][pFocPara->Q08U_Sector]];
    pFocPara->Q14I_Ic = pFocPara->Q12I_I_Data[ADC_Table[2][pFocPara->Q08U_Sector]];
}

static const Q08U_ Txyz_Table[3][8] = 
{{0U,1U,0U,0U,2U,2U,1U,0U},
 {0U,0U,2U,1U,1U,0U,2U,0U},
 {0U,2U,1U,2U,0U,1U,0U,0U}};
void MotorFoc_SVPWM(ST_FOC_PARAMETER* pFocPara, ST_CURRENT_CONTROL* pCurrentCtrl)
{
    Q32I_ Q16I_Ualfa_tmp = 0,Q16I_Ubeta_tmp = 0;
    Q32I_ Utmp1 = 0,Utmp2 = 0,Utmp3 = 0;
    Q32I_ Ttmp1 = 0,Ttmp2 = 0,Ttmpsum = 0;
    Q32I_ Delta_Ttmp1 = 0,Delta_Ttmp2 = 0,Delta_Ttmp3 = 0;
    Q32I_ Txyz[3]= {0,0,0};
    
    Q16I_Ualfa_tmp = Q16I_LFT_12(pFocPara->Q14I_Ualfa)/pFocPara->Q14I_Vbus;
    Q16I_Ubeta_tmp = Q16I_LFT_12(pFocPara->Q14I_Ubeta)/pFocPara->Q14I_Vbus;
    
    Utmp1 = MATH_SQRT_THREE_U(Q16I_Ubeta_tmp);
    Utmp2 = (Q16I_)Q32I_RHT_01(3*Q16I_Ualfa_tmp - Utmp1);
    Utmp3 = (Q16I_)Q32I_RHT_01(-3*Q16I_Ualfa_tmp - Utmp1);
    
    pFocPara->Q08U_Sector = 0U;
    if(Utmp1>0){pFocPara->Q08U_Sector += 1U;}
    if(Utmp2>0){pFocPara->Q08U_Sector += 2U;}
    if(Utmp3>0){pFocPara->Q08U_Sector += 4U;}
    switch(pFocPara->Q08U_Sector)
    {
        case 3U:{Ttmp1 =  Utmp2; Ttmp2 =  Utmp1;}break;
        case 1U:{Ttmp1 = -Utmp2; Ttmp2 = -Utmp3;}break;
        case 5U:{Ttmp1 =  Utmp1; Ttmp2 =  Utmp3;}break;
        case 4U:{Ttmp1 = -Utmp1; Ttmp2 = -Utmp2;}break;
        case 6U:{Ttmp1 =  Utmp3; Ttmp2 =  Utmp2;}break;
        case 2U:{Ttmp1 = -Utmp3; Ttmp2 = -Utmp1;}break;
        default:break;
    }
    
    Ttmpsum = Ttmp1 + Ttmp2;
    if(Ttmpsum > pFocPara->Q12I_MaxScale)
    {
        Ttmp1 = Ttmp1*pFocPara->Q12I_MaxScale/Ttmpsum;
        Ttmp2 = pFocPara->Q12I_MaxScale - Ttmp1;
    }
    Txyz[0] = Q32I_RHT_01(pFocPara->Q12I_MaxDuty - Ttmp1 - Ttmp2);
    Txyz[1] = Txyz[0] + Ttmp1;
    Txyz[2] = Txyz[1] + Ttmp2;
    
    if((Ttmp1 < pFocPara->Q12I_ADC_Time)&&(Ttmp2 < pFocPara->Q12I_ADC_Time))
    {
        Delta_Ttmp1 = pFocPara->Q12I_ADC_Time - Ttmp1;
        Delta_Ttmp3 = -(pFocPara->Q12I_ADC_Time - Ttmp2);
    }
    else if((Ttmp1 < pFocPara->Q12I_ADC_Time)&&(Ttmp2 >= pFocPara->Q12I_ADC_Time))
    {
        Delta_Ttmp1 = (pFocPara->Q12I_ADC_Time - Ttmp1)>>1;
        Delta_Ttmp2 = -pFocPara->Q12I_ADC_Time>>1;
    }
    else if((Ttmp1 >= pFocPara->Q12I_ADC_Time)&&(Ttmp2 < pFocPara->Q12I_ADC_Time))
    {
        Delta_Ttmp2 = pFocPara->Q12I_ADC_Time>>1;
        Delta_Ttmp3 = -(pFocPara->Q12I_ADC_Time - Ttmp2)>>1;
    }
    
    pCurrentCtrl->Q12I_TADC_1 = Txyz[0] - Delta_Ttmp1 + pFocPara->Q12I_VTime_1;
    pCurrentCtrl->Q12I_TADC_2 = Txyz[1] - Delta_Ttmp2 + pFocPara->Q12I_VTime_2;
    
    switch(pFocPara->Q08U_Sector)
    {
        case 3U:
        {
            pFocPara->Q14I_Ualfa = Q32I_RHT_12(MATH_ONE_OVER_THREE_U(2*Ttmp1+Ttmp2)*pFocPara->Q14I_Vbus);
            pFocPara->Q14I_Ubeta = Q32I_RHT_12(MATH_ONE_OVER_SQRT_THREE_U(Ttmp2)*pFocPara->Q14I_Vbus);
    
            pCurrentCtrl->Q12I_TaUp = Txyz[Txyz_Table[0][pFocPara->Q08U_Sector]] + Delta_Ttmp1;
            pCurrentCtrl->Q12I_TbUp = Txyz[Txyz_Table[1][pFocPara->Q08U_Sector]] + Delta_Ttmp2;
            pCurrentCtrl->Q12I_TcUp = Txyz[Txyz_Table[2][pFocPara->Q08U_Sector]] + Delta_Ttmp3;
            pCurrentCtrl->Q12I_TaDn = Txyz[Txyz_Table[0][pFocPara->Q08U_Sector]] - Delta_Ttmp1;
            pCurrentCtrl->Q12I_TbDn = Txyz[Txyz_Table[1][pFocPara->Q08U_Sector]] - Delta_Ttmp2;
            pCurrentCtrl->Q12I_TcDn = Txyz[Txyz_Table[2][pFocPara->Q08U_Sector]] - Delta_Ttmp3;
        }break;
        case 1U:
        {
            pFocPara->Q14I_Ualfa = Q32I_RHT_12(MATH_ONE_OVER_THREE_U(Ttmp2-Ttmp1)*pFocPara->Q14I_Vbus);
            pFocPara->Q14I_Ubeta = Q32I_RHT_12(MATH_ONE_OVER_SQRT_THREE_U(Ttmp1+Ttmp2)*pFocPara->Q14I_Vbus);
    
            pCurrentCtrl->Q12I_TaUp = Txyz[Txyz_Table[0][pFocPara->Q08U_Sector]] + Delta_Ttmp2;
            pCurrentCtrl->Q12I_TbUp = Txyz[Txyz_Table[1][pFocPara->Q08U_Sector]] + Delta_Ttmp1;;
            pCurrentCtrl->Q12I_TcUp = Txyz[Txyz_Table[2][pFocPara->Q08U_Sector]] + Delta_Ttmp3;
            pCurrentCtrl->Q12I_TaDn = Txyz[Txyz_Table[0][pFocPara->Q08U_Sector]] - Delta_Ttmp2;
            pCurrentCtrl->Q12I_TbDn = Txyz[Txyz_Table[1][pFocPara->Q08U_Sector]] - Delta_Ttmp1;
            pCurrentCtrl->Q12I_TcDn = Txyz[Txyz_Table[2][pFocPara->Q08U_Sector]] - Delta_Ttmp3;
        }break;
        case 5U:
        {
            pFocPara->Q14I_Ualfa = Q32I_RHT_12(MATH_ONE_OVER_THREE_U(-2*Ttmp2-Ttmp1)*pFocPara->Q14I_Vbus);
            pFocPara->Q14I_Ubeta = Q32I_RHT_12(MATH_ONE_OVER_SQRT_THREE_U(Ttmp1)*pFocPara->Q14I_Vbus);
    
            pCurrentCtrl->Q12I_TaUp = Txyz[Txyz_Table[0][pFocPara->Q08U_Sector]] + Delta_Ttmp3;
            pCurrentCtrl->Q12I_TbUp = Txyz[Txyz_Table[1][pFocPara->Q08U_Sector]] + Delta_Ttmp1;;
            pCurrentCtrl->Q12I_TcUp = Txyz[Txyz_Table[2][pFocPara->Q08U_Sector]] + Delta_Ttmp2;
            pCurrentCtrl->Q12I_TaDn = Txyz[Txyz_Table[0][pFocPara->Q08U_Sector]] - Delta_Ttmp3;
            pCurrentCtrl->Q12I_TbDn = Txyz[Txyz_Table[1][pFocPara->Q08U_Sector]] - Delta_Ttmp1;
            pCurrentCtrl->Q12I_TcDn = Txyz[Txyz_Table[2][pFocPara->Q08U_Sector]] - Delta_Ttmp2;
        }break;
        case 4U:
        {
            pFocPara->Q14I_Ualfa = Q32I_RHT_12(MATH_ONE_OVER_THREE_U(-2*Ttmp2-Ttmp1)*pFocPara->Q14I_Vbus);
            pFocPara->Q14I_Ubeta = Q32I_RHT_12(-MATH_ONE_OVER_SQRT_THREE_U(Ttmp1)*pFocPara->Q14I_Vbus);
    
            pCurrentCtrl->Q12I_TaUp = Txyz[Txyz_Table[0][pFocPara->Q08U_Sector]] + Delta_Ttmp3;
            pCurrentCtrl->Q12I_TbUp = Txyz[Txyz_Table[1][pFocPara->Q08U_Sector]] + Delta_Ttmp2;
            pCurrentCtrl->Q12I_TcUp = Txyz[Txyz_Table[2][pFocPara->Q08U_Sector]] + Delta_Ttmp1;;
            pCurrentCtrl->Q12I_TaDn = Txyz[Txyz_Table[0][pFocPara->Q08U_Sector]] - Delta_Ttmp3;
            pCurrentCtrl->Q12I_TbDn = Txyz[Txyz_Table[1][pFocPara->Q08U_Sector]] - Delta_Ttmp2;
            pCurrentCtrl->Q12I_TcDn = Txyz[Txyz_Table[2][pFocPara->Q08U_Sector]] - Delta_Ttmp1;
        }break;
        case 6U:
        {
            pFocPara->Q14I_Ualfa = Q32I_RHT_12(MATH_ONE_OVER_THREE_U(Ttmp2-Ttmp1)*pFocPara->Q14I_Vbus);
            pFocPara->Q14I_Ubeta = Q32I_RHT_12(MATH_ONE_OVER_SQRT_THREE_U(-Ttmp1-Ttmp2)*pFocPara->Q14I_Vbus);
    
            pCurrentCtrl->Q12I_TaUp = Txyz[Txyz_Table[0][pFocPara->Q08U_Sector]] + Delta_Ttmp2;
            pCurrentCtrl->Q12I_TbUp = Txyz[Txyz_Table[1][pFocPara->Q08U_Sector]] + Delta_Ttmp3;
            pCurrentCtrl->Q12I_TcUp = Txyz[Txyz_Table[2][pFocPara->Q08U_Sector]] + Delta_Ttmp1;;
            pCurrentCtrl->Q12I_TaDn = Txyz[Txyz_Table[0][pFocPara->Q08U_Sector]] - Delta_Ttmp2;
            pCurrentCtrl->Q12I_TbDn = Txyz[Txyz_Table[1][pFocPara->Q08U_Sector]] - Delta_Ttmp3;
            pCurrentCtrl->Q12I_TcDn = Txyz[Txyz_Table[2][pFocPara->Q08U_Sector]] - Delta_Ttmp1;
        }break;
        case 2U:
        {
            pFocPara->Q14I_Ualfa = Q32I_RHT_12(MATH_ONE_OVER_THREE_U(2*Ttmp1+Ttmp2)*pFocPara->Q14I_Vbus);
            pFocPara->Q14I_Ubeta = Q32I_RHT_12(-MATH_ONE_OVER_SQRT_THREE_U(Ttmp2)*pFocPara->Q14I_Vbus);
    
            pCurrentCtrl->Q12I_TaUp = Txyz[Txyz_Table[0][pFocPara->Q08U_Sector]] + Delta_Ttmp1;;
            pCurrentCtrl->Q12I_TbUp = Txyz[Txyz_Table[1][pFocPara->Q08U_Sector]] + Delta_Ttmp3;
            pCurrentCtrl->Q12I_TcUp = Txyz[Txyz_Table[2][pFocPara->Q08U_Sector]] + Delta_Ttmp2;
            pCurrentCtrl->Q12I_TaDn = Txyz[Txyz_Table[0][pFocPara->Q08U_Sector]] - Delta_Ttmp1;
            pCurrentCtrl->Q12I_TbDn = Txyz[Txyz_Table[1][pFocPara->Q08U_Sector]] - Delta_Ttmp3;
            pCurrentCtrl->Q12I_TcDn = Txyz[Txyz_Table[2][pFocPara->Q08U_Sector]] - Delta_Ttmp2;
        }break;
        default:break;
    }
}

void MotorFoc_WEAK_Init(ST_WEAK_CONTROL* pWEAK)
{
    PID_Pos_Init(&pWEAK->PidV, 0);
}

void MotorFoc_WEAK_Control(ST_FOC_PARAMETER* pFocPara, ST_SRAD_CONTROL* pSpeed, ST_WEAK_CONTROL* pWEAK)
{
    Q32I_ Idtmp = 0;
    Q32I_ Iqtmp = 0;
    
    pWEAK->PidV.Q14I_Rf = pFocPara->Q14I_Vs;
//    pWEAK->PidV.Q14I_Fb = Math_Sqrt(pFocPara->Q14I_Ud*pFocPara->Q14I_Ud + pFocPara->Q14I_Uq*pFocPara->Q14I_Uq);
    PID_Pos_Cal(&pWEAK->PidV);
    pWEAK->Q12I_Theta = pWEAK->PidV.Q14I_Output + MATH_2PI_U;
    
//    Idtmp = pSpeed->Q14I_IqRef * Math_Sin(pWEAK->Q12I_Theta);
//    Iqtmp = pSpeed->Q14I_IqRef * Math_Cos(pWEAK->Q12I_Theta);
    
    if(pWEAK->Q12I_Theta >= MATH_2PI_U)
    {
//        pWEAK->Q14I_IdRef = pMTPA->Q14I_IdRef;
//        pWEAK->Q14I_IqRef = pMTPA->Q14I_IqRef;
    }
    else
    {
        pWEAK->Q14I_IdRef = Idtmp;
        pWEAK->Q14I_IqRef = Iqtmp;
    }
}

void MotorFoc_IF_Init(ST_IF_CONTROL* pCTRL)
{
    pCTRL->Angle.Q12U_Angle = 0;
    pCTRL->Est_AngleRad = 0;
    pCTRL->AngleRad_cnt = 0U;
    pCTRL->IF_Success_Flag = 0U;
    Ramp_Init(&pCTRL->SRad_Ramp, pCTRL->SRad_Ramp.Q32I_Init);
}

void MotorFoc_IF_Control(ST_PMSM_PARAMETER* pPMSMPara, ST_IF_CONTROL* pCTRL)
{
    pCTRL->Q28I_Angle_tmp += pPMSMPara->Q14I_Motor_HTs*pCTRL->SRad_Ramp.Q32I_Output;
    MATH_ANGLE_TMP_U(pCTRL->Q28I_Angle_tmp);
    pCTRL->Angle.Q12U_Angle = Q32I_RHT_16(pCTRL->Q28I_Angle_tmp);
    Math_SinCos(&pCTRL->Angle);
}

void MotorFoc_Flux_Init(ST_FLUX_CONTROL* pCTRL)
{
    pCTRL->Angle.Q12U_Angle = 0;
    pCTRL->Q28I_Angle_tmp = 0;
    pCTRL->FL_SRAD.Q16I_Filter_out = 0;
    pCTRL->FL_SRAD.Q32I_Filter_tmp = 0;
    
    pCTRL->Q28I_Ref_Yalfa = 0;
    pCTRL->Q28I_Ref_Ybeta = 0;
    
    pCTRL->Q14I_Nn_alfa = 0;
    pCTRL->Q14I_Nn_beta = 0;
    pCTRL->Q14I_Nn_2 = 0;
    
    pCTRL->Q28I_Xalfa_addtmp = 0;
    pCTRL->Q28I_Xbeta_addtmp = 0;
    
    pCTRL->Q28I_Est_Xalfatmp1 = 0;
    pCTRL->Q28I_Est_Xbetatmp1 = 0;
    pCTRL->Q28I_Est_Xalfatmp2 = 0;
    pCTRL->Q28I_Est_Xbetatmp2 = 0;
    pCTRL->Q14I_Est_Xalfa = 0;
    pCTRL->Q14I_Est_Xbeta = 0;
    
    PID_Pos_Init(&pCTRL->PLL_PID, 0);
}

void MotorFoc_Flux_Control(ST_PMSM_PARAMETER* pPMSMPara, ST_FOC_PARAMETER* pFocPara, ST_FLUX_CONTROL* pCTRL)
{
    MotorFoc_Clark(pFocPara);
    
    pCTRL->Q28I_Ref_Yalfa = Q16I_LFT_14(pFocPara->Q14I_Ualfa) - pCTRL->Q14I_Ks*pFocPara->Q14I_Ialfa;
    pCTRL->Q28I_Ref_Ybeta = Q16I_LFT_14(pFocPara->Q14I_Ubeta) - pCTRL->Q14I_Ks*pFocPara->Q14I_Ibeta;
    
    pCTRL->Q14I_Nn_alfa = Q32I_RHT_14(pCTRL->Q14I_Est_Xalfa) - Q32I_RHT_14(pPMSMPara->Q14I_Ls*pFocPara->Q14I_Ialfa);
    pCTRL->Q14I_Nn_beta = Q32I_RHT_14(pCTRL->Q14I_Est_Xbeta) - Q32I_RHT_14(pPMSMPara->Q14I_Ls*pFocPara->Q14I_Ibeta);
    pCTRL->Q14I_Nn_2 = Q32I_RHT_14(pCTRL->Q14I_Nn_alfa*pCTRL->Q14I_Nn_alfa + pCTRL->Q14I_Nn_beta*pCTRL->Q14I_Nn_beta);
    
    pCTRL->Q28I_Xalfa_addtmp = pCTRL->Q14I_Nn_alfa*(pPMSMPara->Q14I_Flux_2 - pCTRL->Q14I_Nn_2);
    pCTRL->Q28I_Xbeta_addtmp = pCTRL->Q14I_Nn_beta*(pPMSMPara->Q14I_Flux_2 - pCTRL->Q14I_Nn_2);
    
    pCTRL->Q28I_Est_Xalfatmp1 += pPMSMPara->Q14I_Motor_HTs*Q32I_RHT_09(pCTRL->Q28I_Ref_Yalfa);
    pCTRL->Q28I_Est_Xbetatmp1 += pPMSMPara->Q14I_Motor_HTs*Q32I_RHT_09(pCTRL->Q28I_Ref_Ybeta);
    pCTRL->Q28I_Est_Xalfatmp1 = MATH_SAT_U(pCTRL->Q28I_Est_Xalfatmp1, 1073741824, -1073741824);
    pCTRL->Q28I_Est_Xbetatmp1 = MATH_SAT_U(pCTRL->Q28I_Est_Xbetatmp1, 1073741824, -1073741824);
    
    pCTRL->Q28I_Est_Xalfatmp2 += pPMSMPara->Q14I_Motor_HTs*Q32I_RHT_10(pCTRL->Q28I_Xalfa_addtmp);
    pCTRL->Q28I_Est_Xbetatmp2 += pPMSMPara->Q14I_Motor_HTs*Q32I_RHT_10(pCTRL->Q28I_Xbeta_addtmp);
    pCTRL->Q28I_Est_Xalfatmp2 = MATH_SAT_U(pCTRL->Q28I_Est_Xalfatmp2, 1073741824, -1073741824);
    pCTRL->Q28I_Est_Xbetatmp2 = MATH_SAT_U(pCTRL->Q28I_Est_Xbetatmp2, 1073741824, -1073741824);
    
    pCTRL->Q14I_Est_Xalfa = Q32I_RHT_04(pCTRL->Q28I_Est_Xalfatmp1 + Q32I_RHT_04(pCTRL->Q14I_Gamma*Q32I_RHT_10(pCTRL->Q28I_Est_Xalfatmp2)));
    pCTRL->Q14I_Est_Xbeta = Q32I_RHT_04(pCTRL->Q28I_Est_Xbetatmp1 + Q32I_RHT_04(pCTRL->Q14I_Gamma*Q32I_RHT_10(pCTRL->Q28I_Est_Xbetatmp2)));
    
    pCTRL->Q14I_Nn_alfa = Q32I_RHT_14(pCTRL->Q14I_Est_Xalfa) - Q32I_RHT_14(pPMSMPara->Q14I_Ls*pFocPara->Q14I_Ialfa);
    pCTRL->Q14I_Nn_beta = Q32I_RHT_14(pCTRL->Q14I_Est_Xbeta) - Q32I_RHT_14(pPMSMPara->Q14I_Ls*pFocPara->Q14I_Ibeta);
    
    pCTRL->PLL_PID.Q14I_Rf = Q32I_RHT_14(pCTRL->Q14I_Nn_beta*pCTRL->Angle.Q14I_Cos);
    pCTRL->PLL_PID.Q14I_Fb = Q32I_RHT_14(pCTRL->Q14I_Nn_alfa*pCTRL->Angle.Q14I_Sin);
    PID_Pos_Cal(&pCTRL->PLL_PID);
    
    pCTRL->FL_SRAD.Q16I_Filter_in = pCTRL->PLL_PID.Q14I_Output;
    Filter_Cal(&pCTRL->FL_SRAD);
    
    pCTRL->Q28I_Angle_tmp += pPMSMPara->Q14I_Motor_HTs*pCTRL->FL_SRAD.Q16I_Filter_in;
    MATH_ANGLE_TMP_U(pCTRL->Q28I_Angle_tmp);
    pCTRL->Angle.Q12U_Angle = Q32I_RHT_16(pCTRL->Q28I_Angle_tmp);
    Math_SinCos(&pCTRL->Angle);
}

void MotorFoc_SMO_Init(ST_SMO_CONTROL* pCTRL)
{
    pCTRL->Angle.Q12U_Angle = 0;
    pCTRL->Q28I_Angle_tmp = 0;
    pCTRL->FL_SRAD.Q16I_Filter_out = 0;
    pCTRL->FL_SRAD.Q32I_Filter_tmp = 0;
    
    pCTRL->Q28I_Est_Ialfa_tmp = 0;
    pCTRL->Q28I_Est_Ibeta_tmp = 0;
    pCTRL->Q14I_Est_Ialfa = 0;
    pCTRL->Q14I_Est_Ibeta = 0;  
    pCTRL->Q14I_Est_Ealfa = 0;
    pCTRL->Q14I_Est_Ebeta = 0;  
    
    PID_Pos_Init(&pCTRL->PLL_PID, 0);
}

void MotorFoc_SMO_Control(ST_PMSM_PARAMETER* pPMSMPara, ST_FOC_PARAMETER* pFocPara, ST_SMO_CONTROL* pCTRL)
{
    Q32I_ Q14I_Ialfa_Error;
    Q32I_ Q14I_Ibeta_Error;
    
    MotorFoc_Clark(pFocPara);
    
    pCTRL->Q28I_Est_Ialfa_tmp += pPMSMPara->Q14I_Motor_HTs*
                          (- Q32I_RHT_14(pPMSMPara->Q14I_Rs_Over_Ld*pCTRL->Q14I_Est_Ialfa)
                           - Q32I_RHT_14(pCTRL->FL_SRAD.Q16I_Filter_in*Q32I_RHT_14(pPMSMPara->Q14I_Ld_Lq_Over_Ld*pCTRL->Q14I_Est_Ibeta))
                           + Q32I_RHT_10(pPMSMPara->Q10I_One_Over_Ld*pFocPara->Q14I_Ualfa)
                           - Q32I_RHT_10(pPMSMPara->Q10I_One_Over_Ld*pCTRL->Q14I_Est_Ealfa));
    
    pCTRL->Q28I_Est_Ibeta_tmp += pPMSMPara->Q14I_Motor_HTs*
                          (- Q32I_RHT_14(pPMSMPara->Q14I_Rs_Over_Ld*pCTRL->Q14I_Est_Ibeta)
                           + Q32I_RHT_14(pCTRL->FL_SRAD.Q16I_Filter_in*Q32I_RHT_14(pPMSMPara->Q14I_Ld_Lq_Over_Ld*pCTRL->Q14I_Est_Ialfa))
                           + Q32I_RHT_10(pPMSMPara->Q10I_One_Over_Ld*pFocPara->Q14I_Ubeta)
                           - Q32I_RHT_10(pPMSMPara->Q10I_One_Over_Ld*pCTRL->Q14I_Est_Ebeta));
    
    pCTRL->Q28I_Est_Ialfa_tmp = MATH_SAT_U(pCTRL->Q28I_Est_Ialfa_tmp, 1073741824, -1073741824);
    pCTRL->Q28I_Est_Ibeta_tmp = MATH_SAT_U(pCTRL->Q28I_Est_Ibeta_tmp, 1073741824, -1073741824);
    
    pCTRL->Q14I_Est_Ialfa = Q32I_RHT_14(pCTRL->Q28I_Est_Ialfa_tmp);
    pCTRL->Q14I_Est_Ibeta = Q32I_RHT_14(pCTRL->Q28I_Est_Ibeta_tmp);  
    
    Q14I_Ialfa_Error = pCTRL->Q14I_Est_Ialfa - pFocPara->Q14I_Ialfa;
    Q14I_Ibeta_Error = pCTRL->Q14I_Est_Ibeta - pFocPara->Q14I_Ibeta;
    
    pCTRL->Q14I_Est_Ealfa = MATH_SAT_U(Q14I_Ialfa_Error, pCTRL->Q14I_K1, -pCTRL->Q14I_K1);
    pCTRL->Q14I_Est_Ebeta = MATH_SAT_U(Q14I_Ibeta_Error, pCTRL->Q14I_K1, -pCTRL->Q14I_K1);
    
    pCTRL->Q14I_Est_Ealfa += Q32I_RHT_14(pCTRL->Q14I_K2*Q14I_Ialfa_Error);
    pCTRL->Q14I_Est_Ebeta += Q32I_RHT_14(pCTRL->Q14I_K2*Q14I_Ibeta_Error);
    
    pCTRL->PLL_PID.Q14I_Rf = -Q32I_RHT_14(pCTRL->Q14I_Est_Ealfa*pCTRL->Angle.Q14I_Cos);
    pCTRL->PLL_PID.Q14I_Fb = Q32I_RHT_14(pCTRL->Q14I_Est_Ebeta*pCTRL->Angle.Q14I_Sin);
    PID_Pos_Cal(&pCTRL->PLL_PID);
    
    pCTRL->FL_SRAD.Q16I_Filter_in = pCTRL->PLL_PID.Q14I_Output;
    Filter_Cal(&pCTRL->FL_SRAD);
    
    pCTRL->Q28I_Angle_tmp += pPMSMPara->Q14I_Motor_HTs*pCTRL->FL_SRAD.Q16I_Filter_in;
    MATH_ANGLE_TMP_U(pCTRL->Q28I_Angle_tmp);
    pCTRL->Angle.Q12U_Angle = Q32I_RHT_16(pCTRL->Q28I_Angle_tmp);
    Math_SinCos(&pCTRL->Angle);
}

void MotorFoc_Speed_Init(ST_SRAD_CONTROL* pSpeed)
{
    pSpeed->Q14I_SRAD_Rf = 0;
    pSpeed->Q14I_SRAD_Fb = 0;
    pSpeed->Q14I_IdRef = 0;
    pSpeed->Q14I_IqRef = 0;
    
    Ramp_Init(&pSpeed->Id_Ramp, pSpeed->Id_Ramp.Q32I_Init);
    Ramp_Init(&pSpeed->Iq_Ramp, 0);
    Ramp_Init(&pSpeed->SRad_Ramp, 0);
    PID_Pos_Init(&pSpeed->PidSpd, 0);
}

void MotorFoc_Speed_Loop(ST_SRAD_CONTROL* pSpeed)
{
    pSpeed->SRad_Ramp.Q32I_Target = MATH_SAT_U(pSpeed->Q14I_SRAD_Rf, pSpeed->SRAD_Max, pSpeed->SRAD_Min);
    Ramp_Cal(&pSpeed->SRad_Ramp);
        
    pSpeed->PidSpd.Q14I_Rf = pSpeed->SRad_Ramp.Q32I_Output;
    pSpeed->PidSpd.Q14I_Fb = pSpeed->Q14I_SRAD_Fb;
    PID_Pos_Cal(&pSpeed->PidSpd);
    pSpeed->Q14I_IqRef = pSpeed->PidSpd.Q14I_Output;
}

void MotorFoc_Current_Init(ST_CURRENT_CONTROL* pCurrentCtrl)
{
    pCurrentCtrl->Q14I_IdRef = 0;
    pCurrentCtrl->Q14I_IqRef = 0;
    
    PID_Pos_Init(&pCurrentCtrl->PidId, 0);
    PID_Pos_Init(&pCurrentCtrl->PidIq, 0);
}

void MotorFoc_Current_Loop(ST_FOC_PARAMETER* pFocPara, ST_CURRENT_CONTROL* pCurrentCtrl)
{
    MotorFoc_Park(pFocPara);
    
    pFocPara->Q14I_Vs = Q32I_RHT_14(pFocPara->Q14I_Vbus * pFocPara->Q14I_VsCoeff);
    
    pCurrentCtrl->PidId.Q14I_OutMax = pFocPara->Q14I_Vs;
    pCurrentCtrl->PidId.Q14I_OutMin = -pFocPara->Q14I_Vs;
    pCurrentCtrl->PidId.Q14I_Rf = pCurrentCtrl->Q14I_IdRef;
    pCurrentCtrl->PidId.Q14I_Fb = pFocPara->Q14I_Id;
    PID_Pos_Cal(&pCurrentCtrl->PidId);
    
    pCurrentCtrl->PidIq.Q14I_OutMax = pFocPara->Q14I_Vs;
    pCurrentCtrl->PidIq.Q14I_OutMin = -pFocPara->Q14I_Vs;
    pCurrentCtrl->PidIq.Q14I_Rf = pCurrentCtrl->Q14I_IqRef;
    pCurrentCtrl->PidIq.Q14I_Fb = pFocPara->Q14I_Iq;
    PID_Pos_Cal(&pCurrentCtrl->PidIq);
    
    pFocPara->Q14I_Ud = pCurrentCtrl->PidId.Q14I_Output;
    pFocPara->Q14I_Uq = pCurrentCtrl->PidIq.Q14I_Output;
    MotorFoc_Ipark(pFocPara);
    
    MotorFoc_SVPWM(pFocPara, pCurrentCtrl);
}
