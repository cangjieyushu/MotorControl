/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
 
#include "MotorFoc.h"

void Ramp_Init(ST_RAMP_CAL* pRamp, float Output)
{
    pRamp->Output = Output;
}

void Ramp_Cal(ST_RAMP_CAL* pRamp)
{
    /* step must be a positive value */
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
        /* less than one step needed, just jump to the target */
        pRamp->Output = pRamp->Target;
    }
}

void PID_POS_Init(ST_PID_POS* pPID, float init)
{
    pPID->Ui = init;
}

void PID_POS_Cal(ST_PID_POS* pPID)
{
    float TmpOutput;
    float Error = pPID->Ref - pPID->Fdb;
    /* Compute the proportional output */
    float Up = pPID->Kp*Error;
    /* Compute the integral output */
    pPID->Ui = pPID->Ui + pPID->Ki*Error;
    if(pPID->Ui > pPID->OutMax) 
    {
        pPID->Ui = pPID->OutMax;
    }
    if(pPID->Ui < pPID->OutMin) 
    {
        pPID->Ui = pPID->OutMin;
    }
    
    /* Compute the derivative output */
    /* _iq Ud = _IQmpy(ObjPtr->Kd, (error - ObjPtr->lastError)); */
    /* ObjPtr->lastError = error; */
    TmpOutput = Up + pPID->Ui;
    
    /* Saturate the output */
    if (TmpOutput > pPID->OutMax) 
    {
        pPID->Output = pPID->OutMax;
    }
    else if (TmpOutput < pPID->OutMin) 
    {
        pPID->Output = pPID->OutMin;
    }
    else 
    {
        pPID->Output = TmpOutput;
    }
}

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

void Clarke_Transform(ST_FOC_CONTROL* pFoc)
{
    pFoc->Ialpha = ((pFoc->Ia*2.0f) - (pFoc->Ib+pFoc->Ic))* MATH_ONE_OVER_THREE;
    pFoc->Ibeta = (pFoc->Ib - pFoc->Ic)*MATH_ONE_OVER_SQRT_THREE;
}

static uint8_t Txyz_Table[3][8] = {{0U,1U,0U,0U,2U,2U,1U,0U},
{0U,0U,2U,1U,1U,0U,2U,0U},
{0U,2U,1U,2U,0U,1U,0U,0U}};

void SVPWM_Cal(ST_FOC_CONTROL* pFoc)
{
    uint8_t Sector = 0U;
    float Utmp1 = 0.0f,Utmp2 = 0.0f,Utmp3 = 0.0f;
    float Ttmp1 = 0.0f,Ttmp2 = 0.0f,Ttmpsum = 0.0f;
    float Txyz[3]= {0.0f,0.0f,0.0f};
    
    Utmp1 = MATH_SQRT_THREE*pFoc->Ubeta;
    Utmp2 = 0.5f*(3.0f*pFoc->Ualpha - Utmp1)/pFoc->RealVdc;
    Utmp3 = 0.5f*(-3.0f*pFoc->Ualpha - Utmp1)/pFoc->RealVdc;
    Utmp1 = Utmp1/pFoc->RealVdc;
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
            pFoc->Ualpha = MATH_ONE_OVER_THREE*(2.0f*Ttmp1+Ttmp2)*pFoc->RealVdc;
            pFoc->Ubeta = MATH_ONE_OVER_SQRT_THREE*Ttmp2*pFoc->RealVdc;
            break;
        }
    case 1U:
        {
            pFoc->Ualpha = MATH_ONE_OVER_THREE*(Ttmp2-Ttmp1)*pFoc->RealVdc;
            pFoc->Ubeta = MATH_ONE_OVER_SQRT_THREE*(Ttmp1+Ttmp2)*pFoc->RealVdc;
            break;
        }
    case 5U:
        {
            pFoc->Ualpha = MATH_ONE_OVER_THREE*(-2.0f*Ttmp2-Ttmp1)*pFoc->RealVdc;
            pFoc->Ubeta = MATH_ONE_OVER_SQRT_THREE*Ttmp1*pFoc->RealVdc;
            break;
        }
    case 4U:
        {
            pFoc->Ualpha = MATH_ONE_OVER_THREE*(-2.0f*Ttmp2-Ttmp1)*pFoc->RealVdc;
            pFoc->Ubeta = -MATH_ONE_OVER_SQRT_THREE*Ttmp1*pFoc->RealVdc;
            break;
        }
    case 6U:
        {
            pFoc->Ualpha = MATH_ONE_OVER_THREE*(Ttmp2-Ttmp1)*pFoc->RealVdc;
            pFoc->Ubeta = MATH_ONE_OVER_SQRT_THREE*(-Ttmp1-Ttmp2)*pFoc->RealVdc;
            break;
        }
    case 2U:
        {
            pFoc->Ualpha = MATH_ONE_OVER_THREE*(2.0f*Ttmp1+Ttmp2)*pFoc->RealVdc;
            pFoc->Ubeta = -MATH_ONE_OVER_SQRT_THREE*Ttmp2*pFoc->RealVdc;
            break;
        }
    default:break;
    }
    
    pFoc->TaPu = Txyz[Txyz_Table[0][Sector]];
    pFoc->TbPu = Txyz[Txyz_Table[1][Sector]];
    pFoc->TcPu = Txyz[Txyz_Table[2][Sector]];
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
    if(pCTRL->AngleRad > MATH_2PI)
    {
        pCTRL->AngleRad -= MATH_2PI;
    }
    else if(pCTRL->AngleRad < 0.0f)
    {
        pCTRL->AngleRad += MATH_2PI;
    }
    else{}
    
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
    
    pCTRL->Ref_Yalpha = 0.0f;
    pCTRL->Ref_Ybeta = 0.0f;
    pCTRL->Est_Xalpha = 0.0f;
    pCTRL->Est_Xbeta = 0.0f;
    pCTRL->Cos_Angle = 0.0f;
    pCTRL->Sin_Angle = 0.0f;
    pCTRL->Nn_alpha = 0.0f;
    pCTRL->Nn_beta = 0.0f;
    pCTRL->Nn_2 = 0.0f;
    PID_POS_Init(&pCTRL->Pll_Pid, 0.0f);
}

void Est_Flux(ST_FOC_CONTROL* pFoc, ST_FLUX_CONTROL* pCTRL)
{
    Clarke_Transform(pFoc);
    
    pCTRL->Ref_Yalpha = -pCTRL->Rs*pFoc->Ialpha + pFoc->Ualpha;
    pCTRL->Ref_Ybeta = -pCTRL->Rs*pFoc->Ibeta + pFoc->Ubeta;
    
    pCTRL->Nn_alpha = pCTRL->Est_Xalpha - pCTRL->Ls*pFoc->Ialpha;
    pCTRL->Nn_beta = pCTRL->Est_Xbeta - pCTRL->Ls*pFoc->Ibeta;
    pCTRL->Nn_2 = pCTRL->Nn_alpha*pCTRL->Nn_alpha + pCTRL->Nn_beta*pCTRL->Nn_beta;
    
    pCTRL->Est_Xalpha += pCTRL->Ts*(pCTRL->Ref_Yalpha + pCTRL->Kt*pCTRL->Nn_alpha*(pCTRL->Ref_Flux_2 - pCTRL->Nn_2));
    pCTRL->Est_Xbeta += pCTRL->Ts*(pCTRL->Ref_Ybeta + pCTRL->Kt*pCTRL->Nn_beta*(pCTRL->Ref_Flux_2 - pCTRL->Nn_2));
    
    pCTRL->Cos_Angle = (pCTRL->Est_Xalpha - pCTRL->Ls*pFoc->Ialpha);
    pCTRL->Sin_Angle = (pCTRL->Est_Xbeta - pCTRL->Ls*pFoc->Ibeta);
    
    pCTRL->Pll_Pid.Ref = pCTRL->Sin_Angle*Math_CosF32(pCTRL->AngleRad);
    pCTRL->Pll_Pid.Fdb = pCTRL->Cos_Angle*Math_SinF32(pCTRL->AngleRad);
    PID_POS_Cal(&pCTRL->Pll_Pid);
    
    pCTRL->AngleSpeed = pCTRL->Pll_Pid.Output;
    pCTRL->ElecFreqHz = MATH_ONE_OVER_2PI*pCTRL->AngleSpeed;
    pCTRL->ElecFreqHz_Filter = 0.001f*(USER_PLL_SPEED_LPF_COEFF*pCTRL->ElecFreqHz + (1000.0f-USER_PLL_SPEED_LPF_COEFF)*pCTRL->ElecFreqHz_Filter);
    pCTRL->AngleRad += pCTRL->Ts*pCTRL->AngleSpeed;
    if(pCTRL->AngleRad > MATH_2PI)
    {
        pCTRL->AngleRad -= MATH_2PI;
    }
    else if(pCTRL->AngleRad < 0.0f)
    {
        pCTRL->AngleRad += MATH_2PI;
    }
    else{}
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
    
    Clarke_Transform(pFoc);
    
    pCTRL->Est_Ialpha += pCTRL->Ts*( - pCTRL->Rs_Over_Ld*pCTRL->Est_Ialpha - pCTRL->AngleSpeed*pCTRL->Ld_Lq_Over_Ld*pCTRL->Est_Ibeta
                                    + pCTRL->One_Over_Ld*pFoc->Ualpha - pCTRL->One_Over_Ld*pCTRL->Est_Ealpha);
    pCTRL->Est_Ibeta += pCTRL->Ts*( - pCTRL->Rs_Over_Ld*pCTRL->Est_Ibeta + pCTRL->AngleSpeed*pCTRL->Ld_Lq_Over_Ld*pCTRL->Est_Ialpha
                                   + pCTRL->One_Over_Ld*pFoc->Ubeta - pCTRL->One_Over_Ld*pCTRL->Est_Ebeta);
    
    Ialpha_Error = pCTRL->Est_Ialpha - pFoc->Ialpha;
    Ibeta_Error = pCTRL->Est_Ibeta - pFoc->Ibeta;
    
    if(Ialpha_Error > pCTRL->K1)
    {
        pCTRL->Est_Ealpha = pCTRL->K1;
    }
    else if(Ialpha_Error < -pCTRL->K1)
    {
        pCTRL->Est_Ealpha = -pCTRL->K1;
    }
    else
    {
        pCTRL->Est_Ealpha = Ialpha_Error;
    }
    
    if(Ibeta_Error > pCTRL->K1)
    {
        pCTRL->Est_Ebeta = pCTRL->K1;
    }
    else if(Ibeta_Error < -pCTRL->K1)
    {
        pCTRL->Est_Ebeta = -pCTRL->K1;
    }
    else
    {
        pCTRL->Est_Ebeta = Ibeta_Error;
    }
    
    pCTRL->Est_Ealpha += pCTRL->K2*Ialpha_Error;
    pCTRL->Est_Ebeta += pCTRL->K2*Ibeta_Error;
    
    pCTRL->Pll_Pid.Ref = -pCTRL->Est_Ealpha*Math_CosF32(pCTRL->AngleRad);
    pCTRL->Pll_Pid.Fdb = pCTRL->Est_Ebeta*Math_SinF32(pCTRL->AngleRad);
    PID_POS_Cal(&pCTRL->Pll_Pid);
    
    pCTRL->AngleSpeed = pCTRL->Pll_Pid.Output;
    pCTRL->ElecFreqHz = MATH_ONE_OVER_2PI*pCTRL->AngleSpeed;
    pCTRL->ElecFreqHz_Filter = 0.001f*(USER_PLL_SPEED_LPF_COEFF*pCTRL->ElecFreqHz + (1000.0f-USER_PLL_SPEED_LPF_COEFF)*pCTRL->ElecFreqHz_Filter);
    pCTRL->AngleRad += pCTRL->Ts*pCTRL->AngleSpeed;
    if(pCTRL->AngleRad > MATH_2PI)
    {
        pCTRL->AngleRad -= MATH_2PI;
    }
    else if(pCTRL->AngleRad < 0.0f)
    {
        pCTRL->AngleRad += MATH_2PI;
    }
    else{}
}

void Tc_Cal(ST_TC_CONTROL* pTc)
{
    /* Ramp for the reference */
    if(pTc->SpeedRef >= pTc->SpeedMax)
    {
        pTc->SpeedRef = pTc->SpeedMax;
    }
    else if(pTc->SpeedRef <= pTc->SpeedMin)
    {
        pTc->SpeedRef = pTc->SpeedMin;
    }
    else{}
    pTc->SpdRamp.Target = pTc->SpeedRef;
    Ramp_Cal(&pTc->SpdRamp);
    /* PID for speed */
    pTc->PidSpd.Ref = pTc->SpdRamp.Output;
    pTc->PidSpd.Fdb = pTc->Speed;
    PID_POS_Cal(&pTc->PidSpd);
    pTc->IqRef = pTc->PidSpd.Output;
}

void Foc_Cal(ST_FOC_CONTROL* pFoc)
{
    /* Clarke transform */   
    Clarke_Transform(pFoc);
    /* Park transform */
    pFoc->SinValue = Math_SinF32(pFoc->AngleRad);
    pFoc->CosValue = Math_CosF32(pFoc->AngleRad);
    Park_Transform(pFoc);
    
    pFoc->VsMax = pFoc->RealVdc * pFoc->VsMaxScale;
    /* Id PID */
    pFoc->PidId.OutMax = pFoc->VsMax;
    pFoc->PidId.OutMin = -pFoc->VsMax;
    pFoc->PidId.Ref = pFoc->IdRef;
    pFoc->PidId.Fdb = pFoc->Id;
    PID_POS_Cal(&pFoc->PidId);
    /* Iq PID */
    pFoc->PidIq.OutMax = pFoc->VsMax;
    pFoc->PidIq.OutMin = -pFoc->VsMax;
    pFoc->PidIq.Ref = pFoc->IqRef;
    pFoc->PidIq.Fdb = pFoc->Iq;
    PID_POS_Cal(&pFoc->PidIq);
    
    pFoc->Ud = pFoc->PidId.Output;
    pFoc->Uq = pFoc->PidIq.Output;
    /* IPark transform */	
    Ipark_Transform(pFoc);
    /* SVGEN */
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
    if(pHall->AngleRad > MATH_2PI)
    {
        pHall->AngleRad -= MATH_2PI;
    }
    else if(pHall->AngleRad < 0.0f)
    {
        pHall->AngleRad += MATH_2PI;
    }
    else{}
    
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
        //stimÊ±ÖÓÎª10M
        pHall->ElecFreqHz = pHall->TIM_FreqHz/((float)pHall->HallCount_tmp[0]+(float)pHall->HallCount_tmp[1]+(float)pHall->HallCount_tmp[2]
                                               +(float)pHall->HallCount_tmp[3]+(float)pHall->HallCount_tmp[4]+(float)pHall->HallCount_tmp[5]);
        pHall->ElecFreqHz_Filter = 0.001f*(USER_HALL_SPEED_LPF_COEFF*pHall->ElecFreqHz_Filter + (1000.0f-USER_HALL_SPEED_LPF_COEFF)*pHall->ElecFreqHz);
        pHall->HallLastCount = pHall->HallCurrentCount;
    }
    pHall->HallLastLevel = pHall->HallCurrentLevel;
}
