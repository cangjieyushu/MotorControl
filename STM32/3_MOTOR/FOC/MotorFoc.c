/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
 
#include "MotorFoc.h"

void Ipark_Transform(ST_FOC_CONTROL* pFoc)
{
    pFoc->Ualpha = pFoc->Ud*pFoc->CosValue - pFoc->Uq*pFoc->SinValue;
    pFoc->Ubeta = pFoc->Ud*pFoc->SinValue + pFoc->Uq*pFoc->CosValue;
}

void Park_Transform(ST_FOC_CONTROL* pFoc)
{
    pFoc->Id = pFoc->Ialpha*pFoc->CosValue + pFoc->Ibeta*pFoc->SinValue; 
    pFoc->Iq = -pFoc->Ialpha*pFoc->SinValue + pFoc->Ibeta*pFoc->CosValue;
}

void Clark_Transform(ST_FOC_CONTROL* pFoc)
{
    pFoc->Ialpha = ((pFoc->Ia*2.0f) - (pFoc->Ib+pFoc->Ic))* MATH_ONE_OVER_THREE;
    pFoc->Ibeta = (pFoc->Ib - pFoc->Ic)*MATH_ONE_OVER_SQRT_THREE;
}

static const uint8_t Txyz_Table[3][8] = 
{{0U,1U,0U,0U,2U,2U,1U,0U},
{0U,0U,2U,1U,1U,0U,2U,0U},
{0U,2U,1U,2U,0U,1U,0U,0U}};

void SVPWM_Cal(ST_FOC_CONTROL* pFoc)
{
    uint8_t Sector = 0U;
    float Utmp1 = 0.0f,Utmp2 = 0.0f,Utmp3 = 0.0f;
    float Ttmp1 = 0.0f,Ttmp2 = 0.0f,Ttmpsum = 0.0f;
    float Txyz[3]= {0.0f,0.0f,0.0f};
    
    Utmp1 = MATH_SQRT_THREE*pFoc->Ubeta;
    Utmp2 = 0.5f*(3.0f*pFoc->Ualpha - Utmp1)/pFoc->Vdc;
    Utmp3 = 0.5f*(-3.0f*pFoc->Ualpha - Utmp1)/pFoc->Vdc;
    Utmp1 = Utmp1/pFoc->Vdc;
    if(Utmp1>0.0f){Sector+=1U;}else{}
    if(Utmp2>0.0f){Sector+=2U;}else{}
    if(Utmp3>0.0f){Sector+=4U;}else{}
    switch(Sector)
    {
    case 3U:{Ttmp1 =  Utmp2; Ttmp2 =  Utmp1;break;}
    case 1U:{Ttmp1 = -Utmp2; Ttmp2 = -Utmp3;break;}
    case 5U:{Ttmp1 =  Utmp1; Ttmp2 =  Utmp3;break;}
    case 4U:{Ttmp1 = -Utmp1; Ttmp2 = -Utmp2;break;}
    case 6U:{Ttmp1 =  Utmp3; Ttmp2 =  Utmp2;break;}
    case 2U:{Ttmp1 = -Utmp3; Ttmp2 = -Utmp1;break;}
    default:break;
    }
    
    Ttmpsum = Ttmp1 + Ttmp2;
    if(Ttmpsum > 1.0f){Ttmp1 = 1.0f*Ttmp1/Ttmpsum; Ttmp2 = 1.0f*Ttmp2/Ttmpsum;}else{}
    Txyz[0] = 0.25f*(1.0f - Ttmp1 - Ttmp2);
    if(Txyz[0] < pFoc->MinScale){Txyz[0] = pFoc->MinScale;}else{}
    Txyz[1] = Txyz[0] + 0.5f*Ttmp1;
    Txyz[2] = Txyz[1] + 0.5f*Ttmp2;
    if(Txyz[2] > pFoc->MaxScale){Txyz[2] = pFoc->MaxScale;}else{}
    
    switch(Sector)
    {
    case 3U:
        {
            pFoc->Ualpha = MATH_ONE_OVER_THREE*(2.0f*Ttmp1+Ttmp2)*pFoc->Vdc;
            pFoc->Ubeta = MATH_ONE_OVER_SQRT_THREE*Ttmp2*pFoc->Vdc;
            break;
        }
    case 1U:
        {
            pFoc->Ualpha = MATH_ONE_OVER_THREE*(Ttmp2-Ttmp1)*pFoc->Vdc;
            pFoc->Ubeta = MATH_ONE_OVER_SQRT_THREE*(Ttmp1+Ttmp2)*pFoc->Vdc;
            break;
        }
    case 5U:
        {
            pFoc->Ualpha = MATH_ONE_OVER_THREE*(-2.0f*Ttmp2-Ttmp1)*pFoc->Vdc;
            pFoc->Ubeta = MATH_ONE_OVER_SQRT_THREE*Ttmp1*pFoc->Vdc;
            break;
        }
    case 4U:
        {
            pFoc->Ualpha = MATH_ONE_OVER_THREE*(-2.0f*Ttmp2-Ttmp1)*pFoc->Vdc;
            pFoc->Ubeta = -MATH_ONE_OVER_SQRT_THREE*Ttmp1*pFoc->Vdc;
            break;
        }
    case 6U:
        {
            pFoc->Ualpha = MATH_ONE_OVER_THREE*(Ttmp2-Ttmp1)*pFoc->Vdc;
            pFoc->Ubeta = MATH_ONE_OVER_SQRT_THREE*(-Ttmp1-Ttmp2)*pFoc->Vdc;
            break;
        }
    case 2U:
        {
            pFoc->Ualpha = MATH_ONE_OVER_THREE*(2.0f*Ttmp1+Ttmp2)*pFoc->Vdc;
            pFoc->Ubeta = -MATH_ONE_OVER_SQRT_THREE*Ttmp2*pFoc->Vdc;
            break;
        }
    default:break;
    }
    
    pFoc->Ta = Txyz[Txyz_Table[0][Sector]];
    pFoc->Tb = Txyz[Txyz_Table[1][Sector]];
    pFoc->Tc = Txyz[Txyz_Table[2][Sector]];
}

void Ramp_Init(ST_RAMP* pRamp, float Output)
{
    pRamp->Output = Output;
}

void Ramp_Cal(ST_RAMP* pRamp)
{
    float Step = MATH_ABS(pRamp->Step);      
    if(MATH_ABS(pRamp->Target - pRamp->Output) > Step) 
    {
        if(pRamp->Target > pRamp->Output) 
        {
            pRamp->Output += Step;
        }
        else 
        {
            pRamp->Output -= Step;
        }
    }
    else 
    {   
        pRamp->Output = pRamp->Target;
    }
}

void PID_POS_Init(ST_PID* pPID, float init)
{
    pPID->Ui = init;
}

void PID_POS_Cal(ST_PID* pPID)
{
    float Output_tmp;
    float Error = pPID->Ref - pPID->Fdb;
    
    pPID->Ui = pPID->Ui + pPID->Ki*Error;
    MATH_SAT(pPID->Ui, pPID->OutMax, pPID->OutMin);
    
    Output_tmp = pPID->Kp*Error + pPID->Ui;
    pPID->Output = MATH_SAT(Output_tmp, pPID->OutMax, pPID->OutMin);
}

void Est_IF_Init(ST_IF_CONTROL* pCTRL)
{
    pCTRL->AngleRad = 0.0f;
    pCTRL->AngleRad_cnt = 0U;
    pCTRL->IF_Success_Flag = 0U;
    Ramp_Init(&pCTRL->AngleRadRamp, pCTRL->AngleRadRamp.Init);
}

void Est_IF(ST_IF_CONTROL* pCTRL, float Est_AngleRad)
{
    pCTRL->AngleRad += pCTRL->AngleRadRamp.Output*MATH_2PI;
    MATH_ANGLE_MOD(pCTRL->AngleRad);
    
    if(MATH_ABS(Est_AngleRad - pCTRL->AngleRad - MATH_PI_OVER_TWO) < pCTRL->AngleRad_Error)
    {
        if(++pCTRL->AngleRad_cnt > pCTRL->AngleRad_time)
        {
            pCTRL->IF_Success_Flag = 1U;
        }
    }
    else
    {
        pCTRL->AngleRad_cnt = 0U;
    }
}

void Est_Flux_Init(ST_FLUX_CONTROL* pCTRL)
{
    pCTRL->ElecFreqHz = 0.0f;
    pCTRL->ElecFreqHz_Filter = 0.0f;
    pCTRL->AngleRad = 0.0f;
    pCTRL->AngleSpeed = 0.0f;
    
    pCTRL->Est_Xalpha = 0.0f;
    pCTRL->Est_Xbeta = 0.0f;
    pCTRL->Nn_alpha = 0.0f;
    pCTRL->Nn_beta = 0.0f;
    pCTRL->Nn_2 = 0.0f;
    PID_POS_Init(&pCTRL->Pll_Pid, 0.0f);
}

void Est_Flux(ST_FOC_CONTROL* pFoc, ST_FLUX_CONTROL* pCTRL)
{
    float Ref_Yalpha;
    float Ref_Ybeta;
    
    Clark_Transform(pFoc);
    
    Ref_Yalpha = -pCTRL->Rs*pFoc->Ialpha + pFoc->Ualpha;
    Ref_Ybeta = -pCTRL->Rs*pFoc->Ibeta + pFoc->Ubeta;
    
    pCTRL->Nn_alpha = pCTRL->Est_Xalpha - pCTRL->Ls*pFoc->Ialpha;
    pCTRL->Nn_beta = pCTRL->Est_Xbeta - pCTRL->Ls*pFoc->Ibeta;
    pCTRL->Nn_2 = pCTRL->Nn_alpha*pCTRL->Nn_alpha + pCTRL->Nn_beta*pCTRL->Nn_beta;
    
    pCTRL->Est_Xalpha += pCTRL->Ts*(Ref_Yalpha + pCTRL->Kt*pCTRL->Nn_alpha*(pCTRL->Ref_Flux_2 - pCTRL->Nn_2));
    pCTRL->Est_Xbeta += pCTRL->Ts*(Ref_Ybeta + pCTRL->Kt*pCTRL->Nn_beta*(pCTRL->Ref_Flux_2 - pCTRL->Nn_2));
    
    pCTRL->Pll_Pid.Ref = (pCTRL->Est_Xbeta - pCTRL->Ls*pFoc->Ibeta)*Math_Cos(pCTRL->AngleRad);
    pCTRL->Pll_Pid.Fdb = (pCTRL->Est_Xalpha - pCTRL->Ls*pFoc->Ialpha)*Math_Sin(pCTRL->AngleRad);
    PID_POS_Cal(&pCTRL->Pll_Pid);
    
    pCTRL->AngleSpeed = pCTRL->Pll_Pid.Output;
    pCTRL->ElecFreqHz = MATH_ONE_OVER_2PI*pCTRL->AngleSpeed;
    pCTRL->ElecFreqHz_Filter = 0.001f*(USER_PLL_SPEED_LPF_COEFF*pCTRL->ElecFreqHz + (1000.0f-USER_PLL_SPEED_LPF_COEFF)*pCTRL->ElecFreqHz_Filter);
    pCTRL->AngleRad += pCTRL->Ts*pCTRL->AngleSpeed;
    MATH_ANGLE_MOD(pCTRL->AngleRad);
}

void Est_SMO_Init(ST_SMO_CONTROL* pCTRL)
{
    pCTRL->ElecFreqHz = 0.0f;
    pCTRL->ElecFreqHz_Filter = 0.0f;
    pCTRL->AngleRad = 0.0f;
    pCTRL->AngleSpeed = 0.0f;
    
    pCTRL->Est_Ialpha = 0.0f;
    pCTRL->Est_Ibeta = 0.0f;  
    pCTRL->Est_Ealpha = 0.0f;  
    pCTRL->Est_Ebeta = 0.0f;  
    
    PID_POS_Init(&pCTRL->Pll_Pid, 0.0f);
}

void Est_SMO(ST_FOC_CONTROL* pFoc, ST_SMO_CONTROL* pCTRL)
{
    float Ialpha_Error;
    float Ibeta_Error;
    
    Clark_Transform(pFoc);
    
    pCTRL->Est_Ialpha += pCTRL->Ts*( - pCTRL->Rs_Over_Ld*pCTRL->Est_Ialpha - pCTRL->AngleSpeed*pCTRL->Ld_Lq_Over_Ld*pCTRL->Est_Ibeta
                                    + pCTRL->One_Over_Ld*pFoc->Ualpha - pCTRL->One_Over_Ld*pCTRL->Est_Ealpha);
    pCTRL->Est_Ibeta += pCTRL->Ts*( - pCTRL->Rs_Over_Ld*pCTRL->Est_Ibeta + pCTRL->AngleSpeed*pCTRL->Ld_Lq_Over_Ld*pCTRL->Est_Ialpha
                                   + pCTRL->One_Over_Ld*pFoc->Ubeta - pCTRL->One_Over_Ld*pCTRL->Est_Ebeta);
    
    Ialpha_Error = pCTRL->Est_Ialpha - pFoc->Ialpha;
    Ibeta_Error = pCTRL->Est_Ibeta - pFoc->Ibeta;
    
    pCTRL->Est_Ealpha = MATH_SAT(Ialpha_Error, pCTRL->K1, -pCTRL->K1);
    pCTRL->Est_Ebeta = MATH_SAT(Ibeta_Error, pCTRL->K1, -pCTRL->K1);
    
    pCTRL->Est_Ealpha += pCTRL->K2*Ialpha_Error;
    pCTRL->Est_Ebeta += pCTRL->K2*Ibeta_Error;
    
    pCTRL->Pll_Pid.Ref = -pCTRL->Est_Ealpha*Math_Cos(pCTRL->AngleRad);
    pCTRL->Pll_Pid.Fdb = pCTRL->Est_Ebeta*Math_Sin(pCTRL->AngleRad);
    PID_POS_Cal(&pCTRL->Pll_Pid);
    
    pCTRL->AngleSpeed = pCTRL->Pll_Pid.Output;
    pCTRL->ElecFreqHz = MATH_ONE_OVER_2PI*pCTRL->AngleSpeed;
    pCTRL->ElecFreqHz_Filter = 0.001f*(USER_PLL_SPEED_LPF_COEFF*pCTRL->ElecFreqHz + (1000.0f-USER_PLL_SPEED_LPF_COEFF)*pCTRL->ElecFreqHz_Filter);
    pCTRL->AngleRad += pCTRL->Ts*pCTRL->AngleSpeed;
    MATH_ANGLE_MOD(pCTRL->AngleRad);
}

void MTPA_Control(ST_MTPA_CONTROL* pMTPA, ST_FOC_CONTROL* pFoc, ST_SPEED_CONTROL* pSpeed)
{
    float Itmp = pSpeed->IqRef*pSpeed->IqRef;
    float Istmp = 0.0f;
    pMTPA->IdRef = (pMTPA->Flux - Math_Sqrt(pMTPA->Flux_2 + pMTPA->Eight_Lq_Ld_2*Itmp)) * pMTPA->One_Over_Lq_Ld_Over_4;
    Istmp = Math_Sqrt(Itmp - pMTPA->IdRef*pMTPA->IdRef);
    if(pSpeed->IqRef > 0.0f)
    {
        pMTPA->IqRef = Istmp;
    }
    else
    {
        pMTPA->IqRef = -Istmp;
    }
}

void WEAK_Control(ST_WEAK_CONTROL* pWEAK, ST_MTPA_CONTROL* pMTPA, ST_FOC_CONTROL* pFoc, ST_SPEED_CONTROL* pSpeed)
{
    float Idtmp = 0.0f;
    float Iqtmp = 0.0f;
    
    pWEAK->PidV.Ref = pFoc->VsMax;
    pWEAK->PidV.Fdb = Math_Sqrt(pFoc->Ud*pFoc->Ud + pFoc->Uq*pFoc->Uq);
    PID_POS_Cal(&pWEAK->PidV);
    pWEAK->Theta = pWEAK->PidV.Output + MATH_2PI;
    
    Idtmp = pSpeed->IqRef * Math_Sin(pWEAK->Theta);
    Iqtmp = pSpeed->IqRef * Math_Cos(pWEAK->Theta);
    
    if(pWEAK->Theta >= MATH_2PI)
    {
        pWEAK->IdRef = pMTPA->IdRef;
        pWEAK->IqRef = pMTPA->IqRef;
    }
    else
    {
        pWEAK->IdRef = Idtmp;
        pWEAK->IqRef = Iqtmp;
    }
}

void MotorFoc_Speed_Loop(ST_SPEED_CONTROL* pSpeed)
{
    pSpeed->SpdRamp.Target = MATH_SAT(pSpeed->SpeedRef, pSpeed->SpeedMax, pSpeed->SpeedMin);
    Ramp_Cal(&pSpeed->SpdRamp);
        
    pSpeed->PidSpd.Ref = pSpeed->SpdRamp.Output;
    pSpeed->PidSpd.Fdb = pSpeed->Speed;
    PID_POS_Cal(&pSpeed->PidSpd);
    pSpeed->IqRef = pSpeed->PidSpd.Output;
}

void MotorFoc_Current_Loop(ST_FOC_CONTROL* pFoc)
{
    pFoc->SinValue = Math_Sin(pFoc->AngleRad);
    pFoc->CosValue = Math_Cos(pFoc->AngleRad);
    Park_Transform(pFoc);
    
    pFoc->VsMax = pFoc->Vdc * pFoc->VsMaxScale;
    
    pFoc->PidId.OutMax = pFoc->VsMax;
    pFoc->PidId.OutMin = -pFoc->VsMax;
    pFoc->PidId.Ref = pFoc->IdRef;
    pFoc->PidId.Fdb = pFoc->Id;
    PID_POS_Cal(&pFoc->PidId);
    
    pFoc->PidIq.OutMax = pFoc->VsMax;
    pFoc->PidIq.OutMin = -pFoc->VsMax;
    pFoc->PidIq.Ref = pFoc->IqRef;
    pFoc->PidIq.Fdb = pFoc->Iq;
    PID_POS_Cal(&pFoc->PidIq);
    
    pFoc->Ud = pFoc->PidId.Output;
    pFoc->Uq = pFoc->PidIq.Output;
    Ipark_Transform(pFoc);
    
    SVPWM_Cal(pFoc);
}

void Motor_Brake_Control(ST_BRAKE_CONTROL* pBrake, ST_FOC_CONTROL* pFoc)
{
    if(pBrake->Brake_En == 1U)
    {
        pBrake->Brake_En = 0U;
        pBrake->Brakecnt = 0U;
        pBrake->BrakeCurrentcnt = 0U;
        pBrake->Brake_Run_Flag = 1U;
    }
    
    if(pBrake->Brake_Run_Flag == 1U)
    {
        if(pBrake->Duty > pBrake->MaxScale){pBrake->Duty = pBrake->MaxScale;}
        if(pBrake->Duty < pBrake->MinScale){pBrake->Duty = pBrake->MinScale;}
        pBrake->Duty = 0.0f;
        if(++pBrake->Brakecnt >= pBrake->BrakeTime)
        {
            pBrake->Brake_Finish_Flag = 1U;
        }
        
        if((pFoc->Ia < pBrake->MinBrakeCurrent) && (pFoc->Ib < pBrake->MinBrakeCurrent) && (pFoc->Ic < pBrake->MinBrakeCurrent))
        {
            if(++pBrake->BrakeCurrentcnt >= pBrake->CurrentFilterTime)
            {
                pBrake->Brake_Finish_Flag = 1U;
            }
        }
        else
        {
            pBrake->BrakeCurrentcnt = 0U;
        }
    }
    
    if((pBrake->Brake_Finish_Flag == 1U) && (pBrake->Brake_Run_Flag == 1U))
    {
        pBrake->Brake_Run_Flag = 0U;
    }
}

void Hallest_Init(ST_HALL_CONTROL* pHall)
{
    pHall->ElecFreqHz = 0.0f;
    pHall->ElecFreqHz_Filter = 0.0f;
    pHall->HallCount_tmp[5] = 0U;
    pHall->HallCount_tmp[4] = 0U;
    pHall->HallCount_tmp[3] = 0U;
    pHall->HallCount_tmp[2] = 0U;
    pHall->HallCount_tmp[1] = 0U;
    pHall->HallCount_tmp[0] = 0U;
}

void Hallest_Low_Speed(ST_HALL_CONTROL* pHall)
{
    switch(pHall->HallCurrentLevel)
    {
    case 6U:
        {
            pHall->AngleRad = 0.0f*MATH_PI_OVER_SIX  + USER_HALLSYNCANGLE_RD;
            break;
        }
    case 2U:
        {
            pHall->AngleRad = 2.0f*MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
            break;
        }
    case 3U:
        {
            pHall->AngleRad = 4.0f*MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
            break;}
    case 1U:
        {
            pHall->AngleRad = 6.0f*MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
            break;
        }
    case 5U:
        {
            pHall->AngleRad = 8.0f*MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
            break;
        }
    case 4U:
        {
            pHall->AngleRad = 10.0f*MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
            break;
        }
    default:break;
    }
}

void Hallest_High_Speed(ST_HALL_CONTROL* pHall)
{
    if(pHall->HallCurrentLevel != pHall->HallLastLevel)
    {
        switch(pHall->HallCurrentLevel)
        {
        case 6U:
            {
                if(pHall->HallLastLevel == 4U)
                {
                    pHall->AngleRad = 0.0f*MATH_PI_OVER_SIX - MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                }
                else if(pHall->HallLastLevel == 2U)
                {
                    pHall->AngleRad = 0.0f*MATH_PI_OVER_SIX + MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                }
                else{}
                break;
            }
        case 2U:
            {
                if(pHall->HallLastLevel == 6U)
                {
                    pHall->AngleRad = 2.0f*MATH_PI_OVER_SIX - MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                }
                else if(pHall->HallLastLevel == 3U)
                {
                    pHall->AngleRad = 2.0f*MATH_PI_OVER_SIX + MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                }
                else{}
                break;
            }
        case 3U:
            {
                if(pHall->HallLastLevel == 2U)
                {
                    pHall->AngleRad = 4.0f*MATH_PI_OVER_SIX - MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                }
                else if(pHall->HallLastLevel == 1U)
                {
                    pHall->AngleRad = 4.0f*MATH_PI_OVER_SIX + MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                }
                else{}
                break;
            }
        case 1U:
            {
                if(pHall->HallLastLevel == 3U)
                {
                    pHall->AngleRad = 6.0f*MATH_PI_OVER_SIX - MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                }
                else if(pHall->HallLastLevel == 5U)
                {
                    pHall->AngleRad = 6.0f*MATH_PI_OVER_SIX + MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                }
                else{}
                break;
            }
        case 5U:
            {
                if(pHall->HallLastLevel == 1U)
                {
                    pHall->AngleRad = 8.0f*MATH_PI_OVER_SIX - MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                }
                else if(pHall->HallLastLevel == 4U)
                {
                    pHall->AngleRad = 8.0f*MATH_PI_OVER_SIX + MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                }
                else{}
                break;
            }
        case 4U:
            {
                if(pHall->HallLastLevel == 5U)
                {
                    pHall->AngleRad = 10.0f*MATH_PI_OVER_SIX - MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                }
                else if(pHall->HallLastLevel == 6U)
                {
                    pHall->AngleRad = 10.0f*MATH_PI_OVER_SIX + MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                }
                else{}
                break;
            }
        default:break;
        }
    }
    pHall->AngleRad += MATH_2PI*pHall->ElecFreqHz_Filter*pHall->Ts;
}

void Hallest_Angle_Inc(ST_HALL_CONTROL* pHall, uint32_t cnt)
{
    MATH_ANGLE_MOD(pHall->AngleRad);
    
    if(pHall->HallCurrentLevel != pHall->HallLastLevel)
    {
        pHall->HallStallCount++;
        pHall->HallCurrentCount = cnt;
        pHall->HallCount_tmp[5] = pHall->HallCount_tmp[4];
        pHall->HallCount_tmp[4] = pHall->HallCount_tmp[3];
        pHall->HallCount_tmp[3] = pHall->HallCount_tmp[2];
        pHall->HallCount_tmp[2] = pHall->HallCount_tmp[1];
        pHall->HallCount_tmp[1] = pHall->HallCount_tmp[0];
        pHall->HallCount_tmp[0] = pHall->HallCurrentCount - pHall->HallLastCount;
        
        pHall->ElecFreqHz = pHall->TIM_FreqHz/((float)pHall->HallCount_tmp[0]+(float)pHall->HallCount_tmp[1]+(float)pHall->HallCount_tmp[2]
                                               +(float)pHall->HallCount_tmp[3]+(float)pHall->HallCount_tmp[4]+(float)pHall->HallCount_tmp[5]);
        pHall->ElecFreqHz_Filter = 0.001f*(USER_HALL_SPEED_LPF_COEFF*pHall->ElecFreqHz_Filter + (1000.0f-USER_HALL_SPEED_LPF_COEFF)*pHall->ElecFreqHz);
        pHall->HallLastCount = pHall->HallCurrentCount;
    }
    pHall->HallLastLevel = pHall->HallCurrentLevel;
}
