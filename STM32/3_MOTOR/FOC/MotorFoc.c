/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
 
#include "MotorFoc.h"

void Ipark_Transform(ST_FOC_PARAMETER* pFocPara)
{
    pFocPara->Ualpha = pFocPara->Ud*pFocPara->CosValue - pFocPara->Uq*pFocPara->SinValue;
    pFocPara->Ubeta = pFocPara->Ud*pFocPara->SinValue + pFocPara->Uq*pFocPara->CosValue;
}

void Park_Transform(ST_FOC_PARAMETER* pFocPara)
{
    pFocPara->Id = pFocPara->Ialpha*pFocPara->CosValue + pFocPara->Ibeta*pFocPara->SinValue; 
    pFocPara->Iq = -pFocPara->Ialpha*pFocPara->SinValue + pFocPara->Ibeta*pFocPara->CosValue;
}

void Clark_Transform(ST_FOC_PARAMETER* pFocPara)
{
    pFocPara->Ialpha = ((pFocPara->Ia*2.0f) - (pFocPara->Ib+pFocPara->Ic))* MATH_ONE_OVER_THREE;
    pFocPara->Ibeta = (pFocPara->Ib - pFocPara->Ic)*MATH_ONE_OVER_SQRT_THREE;
}

static const uint8_t Txyz_Table[3][8] = 
{{0U,1U,0U,0U,2U,2U,1U,0U},
{0U,0U,2U,1U,1U,0U,2U,0U},
{0U,2U,1U,2U,0U,1U,0U,0U}};

void SVPWM_Cal(ST_FOC_PARAMETER* pFocPara, ST_CURRENT_CONTROL* pCurrentCtrl)
{
    uint8_t Sector = 0U;
    float Utmp1 = 0.0f,Utmp2 = 0.0f,Utmp3 = 0.0f;
    float Ttmp1 = 0.0f,Ttmp2 = 0.0f,Ttmpsum = 0.0f;
    float Txyz[3]= {0.0f,0.0f,0.0f};
    
    Utmp1 = MATH_SQRT_THREE*pFocPara->Ubeta;
    Utmp2 = 0.5f*(3.0f*pFocPara->Ualpha - Utmp1)/pFocPara->Vbat;
    Utmp3 = 0.5f*(-3.0f*pFocPara->Ualpha - Utmp1)/pFocPara->Vbat;
    Utmp1 = Utmp1/pFocPara->Vbat;
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
    if(Txyz[0] < pCurrentCtrl->MinScale){Txyz[0] = pCurrentCtrl->MinScale;}else{}
    Txyz[1] = Txyz[0] + 0.5f*Ttmp1;
    Txyz[2] = Txyz[1] + 0.5f*Ttmp2;
    if(Txyz[2] > pCurrentCtrl->MaxScale){Txyz[2] = pCurrentCtrl->MaxScale;}else{}
    
    switch(Sector)
    {
    case 3U:
        {
            pFocPara->Ualpha = MATH_ONE_OVER_THREE*(2.0f*Ttmp1+Ttmp2)*pFocPara->Vbat;
            pFocPara->Ubeta = MATH_ONE_OVER_SQRT_THREE*Ttmp2*pFocPara->Vbat;
            break;
        }
    case 1U:
        {
            pFocPara->Ualpha = MATH_ONE_OVER_THREE*(Ttmp2-Ttmp1)*pFocPara->Vbat;
            pFocPara->Ubeta = MATH_ONE_OVER_SQRT_THREE*(Ttmp1+Ttmp2)*pFocPara->Vbat;
            break;
        }
    case 5U:
        {
            pFocPara->Ualpha = MATH_ONE_OVER_THREE*(-2.0f*Ttmp2-Ttmp1)*pFocPara->Vbat;
            pFocPara->Ubeta = MATH_ONE_OVER_SQRT_THREE*Ttmp1*pFocPara->Vbat;
            break;
        }
    case 4U:
        {
            pFocPara->Ualpha = MATH_ONE_OVER_THREE*(-2.0f*Ttmp2-Ttmp1)*pFocPara->Vbat;
            pFocPara->Ubeta = -MATH_ONE_OVER_SQRT_THREE*Ttmp1*pFocPara->Vbat;
            break;
        }
    case 6U:
        {
            pFocPara->Ualpha = MATH_ONE_OVER_THREE*(Ttmp2-Ttmp1)*pFocPara->Vbat;
            pFocPara->Ubeta = MATH_ONE_OVER_SQRT_THREE*(-Ttmp1-Ttmp2)*pFocPara->Vbat;
            break;
        }
    case 2U:
        {
            pFocPara->Ualpha = MATH_ONE_OVER_THREE*(2.0f*Ttmp1+Ttmp2)*pFocPara->Vbat;
            pFocPara->Ubeta = -MATH_ONE_OVER_SQRT_THREE*Ttmp2*pFocPara->Vbat;
            break;
        }
    default:break;
    }
    
    pCurrentCtrl->Ta = Txyz[Txyz_Table[0][Sector]];
    pCurrentCtrl->Tb = Txyz[Txyz_Table[1][Sector]];
    pCurrentCtrl->Tc = Txyz[Txyz_Table[2][Sector]];
}

void Ramp_Init(ST_RAMP* pRamp, float Output)
{
    pRamp->Output = Output;
}

void Ramp_Control(ST_RAMP* pRamp)
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

void PID_POS_Control(ST_PID* pPID)
{
    float Output_tmp;
    float Error = pPID->Ref - pPID->Fdb;
    
    pPID->Ui = pPID->Ui + pPID->Ki*Error;
    pPID->Ui = MATH_SAT(pPID->Ui, pPID->OutMax, pPID->OutMin);
    
    Output_tmp = pPID->Kp*Error + pPID->Ui;
    pPID->Output = MATH_SAT(Output_tmp, pPID->OutMax, pPID->OutMin);
}

void MTPA_Control(ST_PMSM_PARAMETER* pPMSMPara, ST_SPEED_CONTROL* pSpeed, ST_MTPA_CONTROL* pMTPA)
{
    float Itmp = pSpeed->IqRef*pSpeed->IqRef;
    float Istmp = 0.0f;
    pMTPA->IdRef = (pPMSMPara->Flux - Math_Sqrt(pPMSMPara->Flux_2 + pPMSMPara->Eight_Lq_Ld_2*Itmp)) * pPMSMPara->One_Over_Lq_Ld_Over_4;
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

void WEAK_Init(ST_WEAK_CONTROL* pWEAK)
{
    PID_POS_Init(&pWEAK->PidV, 0.0f);
}

void WEAK_Control(ST_FOC_PARAMETER* pFocPara, ST_SPEED_CONTROL* pSpeed, ST_MTPA_CONTROL* pMTPA, ST_WEAK_CONTROL* pWEAK)
{
    float Idtmp = 0.0f;
    float Iqtmp = 0.0f;
    
    pWEAK->PidV.Ref = pFocPara->VsMax;
    pWEAK->PidV.Fdb = Math_Sqrt(pFocPara->Ud*pFocPara->Ud + pFocPara->Uq*pFocPara->Uq);
    PID_POS_Control(&pWEAK->PidV);
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
    
    if(MATH_ABS(Est_AngleRad - pCTRL->AngleRad) < (pCTRL->AngleRad_Error + MATH_PI_OVER_TWO))
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
    pCTRL->AngleRad = 0.0f;
    pCTRL->AngleSpeed = 0.0f;
    pCTRL->AngleSpeed_Filter = 0.0f;
    
    pCTRL->Est_Xalpha = 0.0f;
    pCTRL->Est_Xbeta = 0.0f;
    PID_POS_Init(&pCTRL->Pll_Pid, 0.0f);
}

void Est_Flux(ST_PMSM_PARAMETER* pPMSMPara, ST_FOC_PARAMETER* pFocPara, ST_CURRENT_CONTROL* pCurrentCtrl, ST_FLUX_CONTROL* pCTRL)
{
    float Ref_Yalpha;
    float Ref_Ybeta;
    float Nn_alpha;
    float Nn_beta;
    
    Ref_Yalpha = -pCTRL->Ks*pFocPara->Ialpha + pFocPara->Ualpha;
    Ref_Ybeta = -pCTRL->Ks*pFocPara->Ibeta + pFocPara->Ubeta;
    
    Nn_alpha = pCTRL->Est_Xalpha - pPMSMPara->Ls*pFocPara->Ialpha;
    Nn_beta = pCTRL->Est_Xbeta - pPMSMPara->Ls*pFocPara->Ibeta;
    pCTRL->Nn_2 = Nn_alpha*Nn_alpha + Nn_beta*Nn_beta;
    
    pCTRL->Est_Xalpha += pPMSMPara->Ts*(Ref_Yalpha + pCTRL->Kt*Nn_alpha*(pPMSMPara->Flux_2 -  pCTRL->Nn_2));
    pCTRL->Est_Xbeta += pPMSMPara->Ts*(Ref_Ybeta + pCTRL->Kt*Nn_beta*(pPMSMPara->Flux_2 -  pCTRL->Nn_2));
    
    pCTRL->Pll_Pid.Ref = (pCTRL->Est_Xbeta - pPMSMPara->Ls*pFocPara->Ibeta)*Math_Cos(pCTRL->AngleRad);
    pCTRL->Pll_Pid.Fdb = (pCTRL->Est_Xalpha - pPMSMPara->Ls*pFocPara->Ialpha)*Math_Sin(pCTRL->AngleRad);
    PID_POS_Control(&pCTRL->Pll_Pid);
    
    pCTRL->AngleSpeed = pCTRL->Pll_Pid.Output;
    pCTRL->AngleSpeed_Filter = 0.001f*(USER_PLL_SPEED_LPF_COEFF*pCTRL->AngleSpeed + (1000.0f-USER_PLL_SPEED_LPF_COEFF)*pCTRL->AngleSpeed_Filter);
    pCTRL->AngleRad += pPMSMPara->Ts*pCTRL->AngleSpeed;
    MATH_ANGLE_MOD(pCTRL->AngleRad);
}

void Est_SVC_Init(ST_SVC_CONTROL* pCTRL)
{
    pCTRL->AngleRad = 0.0f;
    pCTRL->AngleSpeed = 0.0f;
    
    pCTRL->AngleSpeed_Filter = 0.0f;
}
void Est_SVC(ST_PMSM_PARAMETER* pPMSMPara, ST_FOC_PARAMETER* pFocPara, ST_CURRENT_CONTROL* pCurrentCtrl, ST_SVC_CONTROL* pCTRL)
{
    float lambda = 0.0f;
    float ed = 0.0f;
    float eq = 0.0f;
    float alpha = 0.0f;
    
    if(pCTRL->AngleSpeed > 0.0f)
    {
        lambda = pCTRL->Lambda;
    }
    else
    {
        lambda = -pCTRL->Lambda;
    }
    
    if(MATH_ABS(pCTRL->AngleSpeed) > pCTRL->SpeedLimit)
    {
        pCurrentCtrl->IdRef = 0.0f;
    }
    else
    {
        pCurrentCtrl->IdRef = pCurrentCtrl->IqRef/lambda;
    }
    
    ed = pFocPara->Ud - pPMSMPara->Rs*pCurrentCtrl->IdRef + pCTRL->AngleSpeed*pPMSMPara->Ls*pCurrentCtrl->IqRef;
    eq = pFocPara->Uq - pPMSMPara->Rs*pCurrentCtrl->IqRef - pCTRL->AngleSpeed*pPMSMPara->Ls*pCurrentCtrl->IdRef;
    
    alpha = pCTRL->Alpha + 2.0f*pCTRL->Lambda*MATH_ABS(pCTRL->AngleSpeed);
    
    pCTRL->AngleSpeed += pPMSMPara->Ts*alpha*((eq - lambda*ed)/pPMSMPara->Flux - pCTRL->AngleSpeed);
    pCTRL->AngleRad += pPMSMPara->Ts*pCTRL->AngleSpeed;
    
    MATH_ANGLE_MOD(pCTRL->AngleRad);
    
    pCTRL->AngleSpeed_Filter = 0.001f*(USER_PLL_SPEED_LPF_COEFF*pCTRL->AngleSpeed + (1000.0f-USER_PLL_SPEED_LPF_COEFF)*pCTRL->AngleSpeed_Filter);
}

void Est_SMO_Init(ST_SMO_CONTROL* pCTRL)
{
    pCTRL->AngleRad = 0.0f;
    pCTRL->AngleSpeed = 0.0f;
    pCTRL->AngleSpeed_Filter = 0.0f;
    
    pCTRL->Est_Ialpha = 0.0f;
    pCTRL->Est_Ibeta = 0.0f;  
    pCTRL->Est_Ealpha = 0.0f;
    pCTRL->Est_Ebeta = 0.0f;  
    
    PID_POS_Init(&pCTRL->Pll_Pid, 0.0f);
}

void Est_SMO(ST_PMSM_PARAMETER* pPMSMPara, ST_FOC_PARAMETER* pFocPara, ST_CURRENT_CONTROL* pCurrentCtrl, ST_SMO_CONTROL* pCTRL)
{
    float Ialpha_Error;
    float Ibeta_Error;
    
    pCTRL->Est_Ialpha += pPMSMPara->Ts*( - pPMSMPara->Rs_Over_Ld*pCTRL->Est_Ialpha - pCTRL->AngleSpeed*pPMSMPara->Ld_Lq_Over_Ld*pCTRL->Est_Ibeta
                                    + pPMSMPara->One_Over_Ld*pFocPara->Ualpha - pPMSMPara->One_Over_Ld*pCTRL->Est_Ealpha);
    pCTRL->Est_Ibeta += pPMSMPara->Ts*( - pPMSMPara->Rs_Over_Ld*pCTRL->Est_Ibeta + pCTRL->AngleSpeed*pPMSMPara->Ld_Lq_Over_Ld*pCTRL->Est_Ialpha
                                   + pPMSMPara->One_Over_Ld*pFocPara->Ubeta - pPMSMPara->One_Over_Ld*pCTRL->Est_Ebeta);
    
    Ialpha_Error = pCTRL->Est_Ialpha - pFocPara->Ialpha;
    Ibeta_Error = pCTRL->Est_Ibeta - pFocPara->Ibeta;
    
    pCTRL->Est_Ealpha = MATH_SAT(Ialpha_Error, pCTRL->K1, -pCTRL->K1);
    pCTRL->Est_Ebeta = MATH_SAT(Ibeta_Error, pCTRL->K1, -pCTRL->K1);
    
    pCTRL->Est_Ealpha += pCTRL->K2*Ialpha_Error;
    pCTRL->Est_Ebeta += pCTRL->K2*Ibeta_Error;
    
    pCTRL->Pll_Pid.Ref = -pFocPara->TargetDir*pCTRL->Est_Ealpha*Math_Cos(pCTRL->AngleRad);
    pCTRL->Pll_Pid.Fdb = pFocPara->TargetDir*pCTRL->Est_Ebeta*Math_Sin(pCTRL->AngleRad);
    PID_POS_Control(&pCTRL->Pll_Pid);
    
    pCTRL->AngleSpeed = pCTRL->Pll_Pid.Output;
    pCTRL->AngleSpeed_Filter = 0.001f*(USER_PLL_SPEED_LPF_COEFF*pCTRL->AngleSpeed + (1000.0f-USER_PLL_SPEED_LPF_COEFF)*pCTRL->AngleSpeed_Filter);
    pCTRL->AngleRad += pPMSMPara->Ts*pCTRL->AngleSpeed;
    MATH_ANGLE_MOD(pCTRL->AngleRad);
}

void MotorFoc_Speed_Loop(ST_SPEED_CONTROL* pSpeed)
{
    pSpeed->SpdRamp.Target = MATH_SAT(pSpeed->SpeedRef, pSpeed->SpeedMax, pSpeed->SpeedMin);
    Ramp_Control(&pSpeed->SpdRamp);
        
    pSpeed->PidSpd.Ref = pSpeed->SpdRamp.Output;
    pSpeed->PidSpd.Fdb = pSpeed->Speed;
    PID_POS_Control(&pSpeed->PidSpd);
    pSpeed->IqRef = pSpeed->PidSpd.Output;
}

void MotorFoc_Current_Loop(ST_FOC_PARAMETER* pFocPara, ST_CURRENT_CONTROL* pCurrentCtrl)
{
    pFocPara->SinValue = Math_Sin(pFocPara->AngleRad);
    pFocPara->CosValue = Math_Cos(pFocPara->AngleRad);
    Park_Transform(pFocPara);
    
    pFocPara->VsMax = pFocPara->Vbat * pFocPara->VsMaxScale;
    
    pCurrentCtrl->PidId.OutMax = pFocPara->VsMax;
    pCurrentCtrl->PidId.OutMin = -pFocPara->VsMax;
    pCurrentCtrl->PidId.Ref = pCurrentCtrl->IdRef;
    pCurrentCtrl->PidId.Fdb = pFocPara->Id;
    PID_POS_Control(&pCurrentCtrl->PidId);
    
    pCurrentCtrl->PidIq.OutMax = pFocPara->VsMax;
    pCurrentCtrl->PidIq.OutMin = -pFocPara->VsMax;
    pCurrentCtrl->PidIq.Ref = pCurrentCtrl->IqRef;
    pCurrentCtrl->PidIq.Fdb = pFocPara->Iq;
    PID_POS_Control(&pCurrentCtrl->PidIq);
    
    pFocPara->Ud = pCurrentCtrl->PidId.Output;
    pFocPara->Uq = pCurrentCtrl->PidIq.Output;
    Ipark_Transform(pFocPara);
    
    SVPWM_Cal(pFocPara, pCurrentCtrl);
}

void Motor_Brake_Control(ST_BRAKE_CONTROL* pBrake, ST_FOC_PARAMETER* pFocPara)
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
        
        if((pFocPara->Ia < pBrake->MinBrakeCurrent) && (pFocPara->Ib < pBrake->MinBrakeCurrent) && (pFocPara->Ic < pBrake->MinBrakeCurrent))
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


void Est_Hall_Init(ST_HALL_CONTROL* pHall)
{
    pHall->HallDir = 0.0f;
    pHall->AngleRad = 0.0f;
    pHall->AngleRad_Hall = 0.0f;
    pHall->AngleSpeed = 0.0f;
    pHall->AngleSpeed_Filter = 0.0f;
    pHall->HallCount_tmp[5] = 0U;
    pHall->HallCount_tmp[4] = 0U;
    pHall->HallCount_tmp[3] = 0U;
    pHall->HallCount_tmp[2] = 0U;
    pHall->HallCount_tmp[1] = 0U;
    pHall->HallCount_tmp[0] = 0U;  
    pHall->HallSwitchCount = 0U;            
    pHall->HallLastSwitchCount = 0U;         
    pHall->HallStallCount = 0U;           
    pHall->HallStallLastCount = 0U;       
    pHall->HallStall_cnt = 0U;     
}

void Est_Hall_Low_Speed(ST_HALL_CONTROL* pHall)
{
    switch(pHall->HallCurrentLevel)
    {
        case 6U:
        {
            pHall->AngleRad_Hall = 0.0f*MATH_PI_OVER_SIX  + USER_HALLSYNCANGLE_RD;
            if(pHall->HallLastLevel == 4U)
            {
                pHall->HallDir = 1.0f;
            }
            else if(pHall->HallLastLevel == 2U)
            {
                pHall->HallDir = -1.0f;
            }
            break;
        }
        case 2U:
        {
            pHall->AngleRad_Hall = 2.0f*MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
            if(pHall->HallLastLevel == 6U)
            {
                pHall->HallDir = 1.0f;
            }
            else if(pHall->HallLastLevel == 3U)
            {
                pHall->HallDir = -1.0f;
            }
            break;
        }
        case 3U:
        {
            pHall->AngleRad_Hall = 4.0f*MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
            if(pHall->HallLastLevel == 2U)
            {
                pHall->HallDir = 1.0f;
            }
            else if(pHall->HallLastLevel == 1U)
            {
                pHall->HallDir = -1.0f;
            }
            break;}
        case 1U:
        {
            pHall->AngleRad_Hall = 6.0f*MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
            if(pHall->HallLastLevel == 3U)
            {
                pHall->HallDir = 1.0f;
            }
            else if(pHall->HallLastLevel == 5U)
            {
                pHall->HallDir = -1.0f;
            }
            break;
        }
        case 5U:
        {
            pHall->AngleRad_Hall = 8.0f*MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
            if(pHall->HallLastLevel == 1U)
            {
                pHall->HallDir = 1.0f;
            }
            else if(pHall->HallLastLevel == 4U)
            {
                pHall->HallDir = -1.0f;
            }
            break;
        }
        case 4U:
        {
            pHall->AngleRad_Hall = 10.0f*MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
            if(pHall->HallLastLevel == 5U)
            {
                pHall->HallDir = 1.0f;
            }
            else if(pHall->HallLastLevel == 6U)
            {
                pHall->HallDir = -1.0f;
            }
            break;
        }
        default:break;
    }
}

void Est_Hall_High_Speed(ST_HALL_CONTROL* pHall)
{
    if(pHall->HallCurrentLevel != pHall->HallLastLevel)
    {
        switch(pHall->HallCurrentLevel)
        {
            case 6U:
            {
                if(pHall->HallLastLevel == 4U)
                {
                    pHall->AngleRad_Hall = 0.0f*MATH_PI_OVER_SIX - MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                    pHall->HallDir = 1.0f;
                }
                else if(pHall->HallLastLevel == 2U)
                {
                    pHall->AngleRad_Hall = 0.0f*MATH_PI_OVER_SIX + MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                    pHall->HallDir = -1.0f;
                }
                break;
            }
            case 2U:
            {
                if(pHall->HallLastLevel == 6U)
                {
                    pHall->AngleRad_Hall = 2.0f*MATH_PI_OVER_SIX - MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                    pHall->HallDir = 1.0f;
                }
                else if(pHall->HallLastLevel == 3U)
                {
                    pHall->AngleRad_Hall = 2.0f*MATH_PI_OVER_SIX + MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                    pHall->HallDir = -1.0f;
                }
                break;
            }
            case 3U:
            {
                if(pHall->HallLastLevel == 2U)
                {
                    pHall->AngleRad_Hall = 4.0f*MATH_PI_OVER_SIX - MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                    pHall->HallDir = 1.0f;
                }
                else if(pHall->HallLastLevel == 1U)
                {
                    pHall->AngleRad_Hall = 4.0f*MATH_PI_OVER_SIX + MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                    pHall->HallDir = -1.0f;
                }
                break;
            }
            case 1U:
            {
                if(pHall->HallLastLevel == 3U)
                {
                    pHall->AngleRad_Hall = 6.0f*MATH_PI_OVER_SIX - MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                    pHall->HallDir = 1.0f;
                }
                else if(pHall->HallLastLevel == 5U)
                {
                    pHall->AngleRad_Hall = 6.0f*MATH_PI_OVER_SIX + MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                    pHall->HallDir = -1.0f;
                }
                break;
            }
            case 5U:
            {
                if(pHall->HallLastLevel == 1U)
                {
                    pHall->AngleRad_Hall = 8.0f*MATH_PI_OVER_SIX - MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                    pHall->HallDir = 1.0f;
                }
                else if(pHall->HallLastLevel == 4U)
                {
                    pHall->AngleRad_Hall = 8.0f*MATH_PI_OVER_SIX + MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                    pHall->HallDir = -1.0f;
                }
                break;
            }
            case 4U:
            {
                if(pHall->HallLastLevel == 5U)
                {
                    pHall->AngleRad_Hall = 10.0f*MATH_PI_OVER_SIX - MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                    pHall->HallDir = 1.0f;
                }
                else if(pHall->HallLastLevel == 6U)
                {
                    pHall->AngleRad_Hall = 10.0f*MATH_PI_OVER_SIX + MATH_PI_OVER_SIX + USER_HALLSYNCANGLE_RD;
                    pHall->HallDir = -1.0f;
                }
                break;
            }
            default:break;
        }
    }
}

void Est_Hall_Speed_Cal(ST_HALL_CONTROL* pHall)
{
    pHall->HallStallCount++;
    pHall->HallCount_tmp[5] = pHall->HallCount_tmp[4];
    pHall->HallCount_tmp[4] = pHall->HallCount_tmp[3];
    pHall->HallCount_tmp[3] = pHall->HallCount_tmp[2];
    pHall->HallCount_tmp[2] = pHall->HallCount_tmp[1];
    pHall->HallCount_tmp[1] = pHall->HallCount_tmp[0];
    pHall->HallCount_tmp[0] = pHall->HallSwitchCount - pHall->HallLastSwitchCount;
    
    pHall->AngleSpeed = pHall->HallDir*MATH_2PI*pHall->TIM_FreqHz/((float)(pHall->HallCount_tmp[0]+pHall->HallCount_tmp[1]+pHall->HallCount_tmp[2]
                                                                          +pHall->HallCount_tmp[3]+pHall->HallCount_tmp[4]+pHall->HallCount_tmp[5]));
    pHall->AngleSpeed_Filter = 0.001f*(USER_HALL_SPEED_LPF_COEFF*pHall->AngleSpeed_Filter + (1000.0f-USER_HALL_SPEED_LPF_COEFF)*pHall->AngleSpeed);
    pHall->HallLastSwitchCount = pHall->HallSwitchCount;
}

void Est_Hall_Angle_Inc(ST_HALL_CONTROL* pHall, uint32_t cnt)
{
    float tmp;
    tmp = pHall->AngleSpeed_Filter*((float)(cnt - pHall->HallSwitchCount))/pHall->TIM_FreqHz;
    if(tmp > MATH_PI_OVER_TWO)
    {
        tmp = MATH_PI_OVER_TWO;
    }
    else if(tmp < -MATH_PI_OVER_TWO)
    {
        tmp = -MATH_PI_OVER_TWO;
    }
    pHall->AngleRad = pHall->AngleRad_Hall + tmp;
    MATH_ANGLE_MOD(pHall->AngleRad);
}
