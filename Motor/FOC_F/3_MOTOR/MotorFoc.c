/**************************************************************************************************
*     File Name :                        MotorFoc.c
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC算法源文件
**************************************************************************************************/
#include "MotorFoc.h"

/**********************************IF控制************************************/

/**********************************************************************************************
Function: MotorFoc_IF_Init_F
Description: IF初始化
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_IF_Init_F(ST_IF_CONTROL_F* pCTRL)
{
    pCTRL->_O_F_Angle = 0.0f;
    Ramp_Init_F(&pCTRL->Ramp_Iq, pCTRL->Ramp_Iq.F_Init);
    Ramp_Init_F(&pCTRL->Ramp_SRAD, pCTRL->Ramp_SRAD.F_Init);
    Ramp_Init_F(&pCTRL->Ramp_AngleERR, 0.0f);
}

/**********************************************************************************************
Function: MotorFoc_IF_OPEN_F
Description: IF开环控制函数
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_IF_OPEN_F(ST_IF_CONTROL_F* pCTRL)
{
    Ramp_Cal_F(&pCTRL->Ramp_Iq);
    Ramp_Cal_F(&pCTRL->Ramp_SRAD);
}

/**********************************************************************************************
Function: MotorFoc_IF_CLOSE_F
Description: IF闭环控制函数
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_IF_CLOSE_F(ST_IF_CONTROL_F* pCTRL)
{
    Ramp_Cal_F(&pCTRL->Ramp_AngleERR);
}

/**********************************************************************************************
Function: MotorFoc_IF_CURRENT_F
Description: IF电流环中断控制函数
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_IF_CURRENT_F(ST_IF_CONTROL_F* pCTRL)
{
    pCTRL->_O_F_Angle += pCTRL->_I_F_DIR_Target*pCTRL->_P_F_Ts*pCTRL->Ramp_SRAD.F_Output;
    MATH_ANGLE_MOD_F(pCTRL->_O_F_Angle);
}

/**********************************VF控制************************************/

/**********************************************************************************************
Function: MotorFoc_VF_Init_F
Description: VF初始化
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_VF_Init_F(ST_VF_CONTROL_F* pCTRL)
{
    pCTRL->_O_F_Angle = 0.0f;
    Ramp_Init_F(&pCTRL->Ramp_Vq, pCTRL->Ramp_Vq.F_Init);
    Ramp_Init_F(&pCTRL->Ramp_SRAD, pCTRL->Ramp_SRAD.F_Init);
    Ramp_Init_F(&pCTRL->Ramp_AngleERR, 0.0f);
}

/**********************************************************************************************
Function: MotorFoc_VF_OPEN_F
Description: VF开环控制函数
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_VF_OPEN_F(ST_VF_CONTROL_F* pCTRL)
{
    Ramp_Cal_F(&pCTRL->Ramp_Vq);
    Ramp_Cal_F(&pCTRL->Ramp_SRAD);
}

/**********************************************************************************************
Function: MotorFoc_VF_CLOSE_F
Description: VF闭环控制函数
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_VF_CLOSE_F(ST_VF_CONTROL_F* pCTRL)
{
    Ramp_Cal_F(&pCTRL->Ramp_AngleERR);
}

/**********************************************************************************************
Function: MotorFoc_VF_CURRENT_F
Description: VF电流环中断控制函数
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_VF_CURRENT_F(ST_VF_CONTROL_F* pCTRL)
{
    pCTRL->_O_F_Angle += pCTRL->_I_F_DIR_Target*pCTRL->_P_F_Ts*pCTRL->Ramp_SRAD.F_Output;
    MATH_ANGLE_MOD_F(pCTRL->_O_F_Angle);
}

/*********************************坐标变换*************************************/

/**********************************************************************************************
Function: MotorFoc_Clark_F
Description: Clark坐标变换函数
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_Clark_F(ST_SVPWM_CONTROL_F* pCTRL)
{
    pCTRL->_O_F_Ialfa = MATH_ONE_OVER_THREE_F*(2.0f*pCTRL->_I_F_Ia - pCTRL->_I_F_Ib - pCTRL->_I_F_Ic);
    pCTRL->_O_F_Ibeta = MATH_ONE_OVER_SQRT_THREE_F*(pCTRL->_I_F_Ib - pCTRL->_I_F_Ic);
}

/**********************************************************************************************
Function: MotorFoc_Park_F
Description: Park坐标变换函数
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_Park_F(ST_SVPWM_CONTROL_F* pCTRL)
{
    pCTRL->_O_F_Id =  pCTRL->_O_F_Ialfa*pCTRL->TG_Triangle.F_Cos + pCTRL->_O_F_Ibeta*pCTRL->TG_Triangle.F_Sin;
    pCTRL->_O_F_Iq = -pCTRL->_O_F_Ialfa*pCTRL->TG_Triangle.F_Sin + pCTRL->_O_F_Ibeta*pCTRL->TG_Triangle.F_Cos;
}

/**********************************************************************************************
Function: MotorFoc_Ipark_F
Description: Ipark坐标变换函数
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_Ipark_F(ST_SVPWM_CONTROL_F* pCTRL)
{
    pCTRL->_O_F_Ualfa = pCTRL->_I_F_Ud*pCTRL->TG_Triangle.F_Cos - pCTRL->_I_F_Uq*pCTRL->TG_Triangle.F_Sin;
    pCTRL->_O_F_Ubeta = pCTRL->_I_F_Ud*pCTRL->TG_Triangle.F_Sin + pCTRL->_I_F_Uq*pCTRL->TG_Triangle.F_Cos;
}

/*********************************SVPWM*************************************/

/**********************************************************************************************
Function: MotorFoc_SVPWM_Init_F
Description: SVPWM初始化
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_SVPWM_Init_F(ST_SVPWM_CONTROL_F* pCTRL)
{
    pCTRL->TG_Triangle.F_Angle = 0.0f;
    pCTRL->TG_Triangle.F_Cos = 0.0f;
    pCTRL->TG_Triangle.F_Sin = 0.0f;
    pCTRL->TG_Triangle.F_ReAngle = 0.0f;
    
    pCTRL->_O_F_Ualfa = 0.0f;
    pCTRL->_O_F_Ubeta = 0.0f;
}

static Q08U_ Txyz_Table[3][8] = 
{{0U,1U,0U,0U,2U,2U,1U,0U},
{0U,0U,2U,1U,1U,0U,2U,0U},
{0U,2U,1U,2U,0U,1U,0U,0U}};
/**********************************************************************************************
Function: MotorFoc_SVPWM_ThreeShunt_F
Description: 常规SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_SVPWM_ThreeShunt_F(ST_SVPWM_CONTROL_F* pCTRL)
{
    float Utmp1 = 0.0f,Utmp2 = 0.0f,Utmp3 = 0.0f;
    float Ttmp1 = 0.0f,Ttmp2 = 0.0f,Ttmpsum = 0.0f;
    float Txyz[3]= {0.0f,0.0f,0.0f};
    
    Utmp1 = MATH_SQRT_THREE_F*pCTRL->_O_F_Ubeta;
    Utmp2 = 0.5f*(3.0f*pCTRL->_O_F_Ualfa - Utmp1)*pCTRL->_I_F_One_Over_Vbus;
    Utmp3 = 0.5f*(-3.0f*pCTRL->_O_F_Ualfa - Utmp1)*pCTRL->_I_F_One_Over_Vbus;
    Utmp1 = Utmp1*pCTRL->_I_F_One_Over_Vbus;
    
    pCTRL->_O_Q08U_Sector = 0U;
    if(Utmp1>0.0f){pCTRL->_O_Q08U_Sector+=1U;}else{}
    if(Utmp2>0.0f){pCTRL->_O_Q08U_Sector+=2U;}else{}
    if(Utmp3>0.0f){pCTRL->_O_Q08U_Sector+=4U;}else{}
    switch(pCTRL->_O_Q08U_Sector)
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
    if(Ttmpsum > pCTRL->_P_F_MaxDuty){Ttmp1 = pCTRL->_P_F_MaxDuty*Ttmp1/Ttmpsum;Ttmp2 = pCTRL->_P_F_MaxDuty - Ttmp1;}else{}
    Txyz[0] = 0.25f*(pCTRL->_P_F_MaxDuty - Ttmp1 - Ttmp2) + 0.5f*pCTRL->_P_F_MinDuty;
    Txyz[1] = Txyz[0] + 0.5f*Ttmp1;
    Txyz[2] = Txyz[1] + 0.5f*Ttmp2;
    
    switch(pCTRL->_O_Q08U_Sector)
    {
        case 3U:
        {
            pCTRL->_O_F_Ualfa = MATH_ONE_OVER_THREE_F*(2.0f*Ttmp1+Ttmp2)*pCTRL->_I_F_Vbus;
            pCTRL->_O_F_Ubeta = MATH_ONE_OVER_SQRT_THREE_F*Ttmp2*pCTRL->_I_F_Vbus;
            break;
        }
        case 1U:
        {
            pCTRL->_O_F_Ualfa = MATH_ONE_OVER_THREE_F*(Ttmp2-Ttmp1)*pCTRL->_I_F_Vbus;
            pCTRL->_O_F_Ubeta = MATH_ONE_OVER_SQRT_THREE_F*(Ttmp1+Ttmp2)*pCTRL->_I_F_Vbus;
            break;
        }
        case 5U:
        {
            pCTRL->_O_F_Ualfa = MATH_ONE_OVER_THREE_F*(-2.0f*Ttmp2-Ttmp1)*pCTRL->_I_F_Vbus;
            pCTRL->_O_F_Ubeta = MATH_ONE_OVER_SQRT_THREE_F*Ttmp1*pCTRL->_I_F_Vbus;
            break;
        }
        case 4U:
        {
            pCTRL->_O_F_Ualfa = MATH_ONE_OVER_THREE_F*(-2.0f*Ttmp2-Ttmp1)*pCTRL->_I_F_Vbus;
            pCTRL->_O_F_Ubeta = -MATH_ONE_OVER_SQRT_THREE_F*Ttmp1*pCTRL->_I_F_Vbus;
            break;
        }
        case 6U:
        {
            pCTRL->_O_F_Ualfa = MATH_ONE_OVER_THREE_F*(Ttmp2-Ttmp1)*pCTRL->_I_F_Vbus;
            pCTRL->_O_F_Ubeta = MATH_ONE_OVER_SQRT_THREE_F*(-Ttmp1-Ttmp2)*pCTRL->_I_F_Vbus;
            break;
        }
        case 2U:
        {
            pCTRL->_O_F_Ualfa = MATH_ONE_OVER_THREE_F*(2.0f*Ttmp1+Ttmp2)*pCTRL->_I_F_Vbus;
            pCTRL->_O_F_Ubeta = -MATH_ONE_OVER_SQRT_THREE_F*Ttmp2*pCTRL->_I_F_Vbus;
            break;
        }
        default:break;
    }
    
    pCTRL->_O_F_Ta = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]];
    pCTRL->_O_F_Tb = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]];
    pCTRL->_O_F_Tc = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]];
}

/********************************单电阻电流重构**************************************/

static Q08U_ ADC_Table[3][8] = 
{{0U,2U,0U,0U,1U,1U,2U,0U},
 {0U,0U,1U,2U,2U,0U,1U,0U},
 {0U,1U,2U,1U,0U,2U,0U,0U}};
/**********************************************************************************************
Function: MotorFoc_OneShunt_Cal_F
Description: 单电阻采样电流查表
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_OneShunt_Cal_F(ST_SVPWM_CONTROL_F* pCTRL)
{
    pCTRL->_I_F_Ia = pCTRL->_I_F_Ishunt[ADC_Table[0][pCTRL->_O_Q08U_Sector]];
    pCTRL->_I_F_Ib = pCTRL->_I_F_Ishunt[ADC_Table[1][pCTRL->_O_Q08U_Sector]];
    pCTRL->_I_F_Ic = pCTRL->_I_F_Ishunt[ADC_Table[2][pCTRL->_O_Q08U_Sector]];
}

/**********************************************************************************************
Function: MotorFoc_SVPWM_OneShunt_F
Description: 移相SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_SVPWM_OneShunt_F(ST_SVPWM_CONTROL_F* pCTRL)
{
    float Utmp1 = 0.0f,Utmp2 = 0.0f,Utmp3 = 0.0f;
    float Ttmp1 = 0.0f,Ttmp2 = 0.0f,Ttmpsum = 0.0f;
    float Txyz[3]= {0.0f,0.0f,0.0f};
    float Delta_Ttmp1 = 0.0f,Delta_Ttmp2 = 0.0f,Delta_Ttmp3 = 0.0f;
    
    Utmp1 = MATH_SQRT_THREE_F*pCTRL->_O_F_Ubeta;
    Utmp2 = 0.5f*(3.0f*pCTRL->_O_F_Ualfa - Utmp1)*pCTRL->_I_F_One_Over_Vbus;
    Utmp3 = 0.5f*(-3.0f*pCTRL->_O_F_Ualfa - Utmp1)*pCTRL->_I_F_One_Over_Vbus;
    Utmp1 = Utmp1*pCTRL->_I_F_One_Over_Vbus;
    
    pCTRL->_O_Q08U_Sector = 0U;
    if(Utmp1>0.0f){pCTRL->_O_Q08U_Sector+=1U;}else{}
    if(Utmp2>0.0f){pCTRL->_O_Q08U_Sector+=2U;}else{}
    if(Utmp3>0.0f){pCTRL->_O_Q08U_Sector+=4U;}else{}
    switch(pCTRL->_O_Q08U_Sector)
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
    if(Ttmpsum > pCTRL->_P_F_MaxDuty){Ttmp1 = pCTRL->_P_F_MaxDuty*Ttmp1/Ttmpsum;Ttmp2 = pCTRL->_P_F_MaxDuty - Ttmp1;}else{}
//    Txyz[0] = 0.25f*(1.0f - Ttmp1 - Ttmp2);
//    Txyz[1] = Txyz[0] + 0.5f*Ttmp1;
//    Txyz[2] = Txyz[1] + 0.5f*Ttmp2;
    
    Txyz[2] = 0.25f*(1.0f - Ttmp1 - Ttmp2);
    Txyz[1] = Txyz[2] + 0.5f*Ttmp2;
    Txyz[0] = Txyz[1] + 0.5f*Ttmp1;
    
    if((Ttmp1 < pCTRL->_P_F_MinDuty)&&(Ttmp2 < pCTRL->_P_F_MinDuty))
    {
        Delta_Ttmp1 = 0.5f*(pCTRL->_P_F_MinDuty - Ttmp1);
        Delta_Ttmp3 = - 0.5f*(pCTRL->_P_F_MinDuty - Ttmp2);
    }
    else if((Ttmp1 < pCTRL->_P_F_MinDuty)&&(Ttmp2 >= pCTRL->_P_F_MinDuty))
    {
        Delta_Ttmp1 = 0.25f*(pCTRL->_P_F_MinDuty - Ttmp1);
        Delta_Ttmp2 = - 0.25f*pCTRL->_P_F_MinDuty;
    }
    else if((Ttmp1 >= pCTRL->_P_F_MinDuty)&&(Ttmp2 < pCTRL->_P_F_MinDuty))
    {
        Delta_Ttmp2 = 0.25f*pCTRL->_P_F_MinDuty;
        Delta_Ttmp3 = - 0.25f*(pCTRL->_P_F_MinDuty - Ttmp2);
    }
    
    pCTRL->_O_F_ADCTrigTime1 = Txyz[0] + Delta_Ttmp1 - pCTRL->_P_F_ADCSampleDuty;
    pCTRL->_O_F_ADCTrigTime2 = Txyz[1] + Delta_Ttmp2 - pCTRL->_P_F_ADCSampleDuty;
    
    switch(pCTRL->_O_Q08U_Sector)
    {
        case 3U:
        {
            pCTRL->_O_F_Ualfa = MATH_ONE_OVER_THREE_F*(2.0f*Ttmp1+Ttmp2)*pCTRL->_I_F_Vbus;
            pCTRL->_O_F_Ubeta = MATH_ONE_OVER_SQRT_THREE_F*Ttmp2*pCTRL->_I_F_Vbus;
            
            pCTRL-> _O_F_TaUp = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp1;
            pCTRL-> _O_F_TbUp = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp2;
            pCTRL-> _O_F_TcUp = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp3;
            pCTRL-> _O_F_TaDn = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp1;
            pCTRL-> _O_F_TbDn = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp2;
            pCTRL-> _O_F_TcDn = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp3;
            break;
        }
        case 1U:
        {
            pCTRL->_O_F_Ualfa = MATH_ONE_OVER_THREE_F*(Ttmp2-Ttmp1)*pCTRL->_I_F_Vbus;
            pCTRL->_O_F_Ubeta = MATH_ONE_OVER_SQRT_THREE_F*(Ttmp1+Ttmp2)*pCTRL->_I_F_Vbus;
            
            pCTRL-> _O_F_TaUp = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp2;
            pCTRL-> _O_F_TbUp = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp1;
            pCTRL-> _O_F_TcUp = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp3;
            pCTRL-> _O_F_TaDn = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp2;
            pCTRL-> _O_F_TbDn = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp1;
            pCTRL-> _O_F_TcDn = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp3;
            break;
        }
        case 5U:
        {
            pCTRL->_O_F_Ualfa = MATH_ONE_OVER_THREE_F*(-2.0f*Ttmp2-Ttmp1)*pCTRL->_I_F_Vbus;
            pCTRL->_O_F_Ubeta = MATH_ONE_OVER_SQRT_THREE_F*Ttmp1*pCTRL->_I_F_Vbus;
            
            pCTRL-> _O_F_TaUp = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp3;
            pCTRL-> _O_F_TbUp = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp1;
            pCTRL-> _O_F_TcUp = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp2;
            pCTRL-> _O_F_TaDn = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp3;
            pCTRL-> _O_F_TbDn = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp1;
            pCTRL-> _O_F_TcDn = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp2;
            break;
        }
        case 4U:
        {
            pCTRL->_O_F_Ualfa = MATH_ONE_OVER_THREE_F*(-2.0f*Ttmp2-Ttmp1)*pCTRL->_I_F_Vbus;
            pCTRL->_O_F_Ubeta = -MATH_ONE_OVER_SQRT_THREE_F*Ttmp1*pCTRL->_I_F_Vbus;
            
            pCTRL-> _O_F_TaUp = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp3;
            pCTRL-> _O_F_TbUp = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp2;
            pCTRL-> _O_F_TcUp = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp1;
            pCTRL-> _O_F_TaDn = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp3;
            pCTRL-> _O_F_TbDn = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp2;
            pCTRL-> _O_F_TcDn = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp1;
            break;
        }
        case 6U:
        {
            pCTRL->_O_F_Ualfa = MATH_ONE_OVER_THREE_F*(Ttmp2-Ttmp1)*pCTRL->_I_F_Vbus;
            pCTRL->_O_F_Ubeta = MATH_ONE_OVER_SQRT_THREE_F*(-Ttmp1-Ttmp2)*pCTRL->_I_F_Vbus;
            
            pCTRL-> _O_F_TaUp = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp2;
            pCTRL-> _O_F_TbUp = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp3;
            pCTRL-> _O_F_TcUp = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp1;
            pCTRL-> _O_F_TaDn = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp2;
            pCTRL-> _O_F_TbDn = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp3;
            pCTRL-> _O_F_TcDn = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp1;
            break;
        }
        case 2U:
        {
            pCTRL->_O_F_Ualfa = MATH_ONE_OVER_THREE_F*(2.0f*Ttmp1+Ttmp2)*pCTRL->_I_F_Vbus;
            pCTRL->_O_F_Ubeta = -MATH_ONE_OVER_SQRT_THREE_F*Ttmp2*pCTRL->_I_F_Vbus;
            
            pCTRL-> _O_F_TaUp = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp1;
            pCTRL-> _O_F_TbUp = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp3;
            pCTRL-> _O_F_TcUp = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp2;
            pCTRL-> _O_F_TaDn = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp1;
            pCTRL-> _O_F_TbDn = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp3;
            pCTRL-> _O_F_TcDn = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp2;
            break;
        }
        default:break;
    }
}

/********************************速度环**************************************/

/**********************************************************************************************
Function: MotorFoc_SRAD_Init_F
Description: 移相SVPWM
Input: 无
Output: 无
Input_Output: 速度环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_SRAD_Init_F(ST_SRAD_CONTROL_F* pCTRL)
{
    PID_Pos_Init_F(&pCTRL->PID_SRAD, 0.0f);
    PID_Pos_Init_F(&pCTRL->PID_WEAK, 0.0f);
    Ramp_Init_F(&pCTRL->Ramp_SRAD, 0.0f);
}

/**********************************************************************************************
Function: MotorFoc_SRAD_Loop_F
Description: 速度环控制
Input: 无
Output: 无
Input_Output: 速度环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_SRAD_Loop_F(ST_SRAD_CONTROL_F* pCTRL)
{
    pCTRL->Ramp_SRAD.F_Target = MATH_SAT_F(pCTRL->_I_F_SRAD_Target, pCTRL->_P_F_SRAD_Max, pCTRL->_P_F_SRAD_Min);
    Ramp_Cal_F(&pCTRL->Ramp_SRAD);
    
    pCTRL->PID_SRAD.F_Rf = pCTRL->Ramp_SRAD.F_Output;
    pCTRL->PID_SRAD.F_Fb = pCTRL->_I_F_SRAD;
    PID_Pos_Cal_F(&pCTRL->PID_SRAD);
    
    pCTRL->PID_WEAK.F_Rf = MATH_ONE_OVER_SQRT_THREE_F*pCTRL->_I_F_Vbus;
    pCTRL->PID_WEAK.F_Fb = Math_Sqrt_F(MATH_SQUARE_F(pCTRL->_I_F_Ud) + MATH_SQUARE_F(pCTRL->_I_F_Uq));
    PID_Pos_Cal_F(&pCTRL->PID_WEAK);
    
    pCTRL->TG_Triangle.F_Angle = pCTRL->PID_WEAK.F_Output;
    Math_SinCos_F(&pCTRL->TG_Triangle);
    
    pCTRL->_O_F_IdRef = pCTRL->PID_SRAD.F_Output*pCTRL->TG_Triangle.F_Sin;
    pCTRL->_O_F_IqRef = pCTRL->PID_SRAD.F_Output*pCTRL->TG_Triangle.F_Cos;
}

/*******************************电流环***************************************/

/**********************************************************************************************
Function: MotorFoc_Current_Init_F
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_Current_Init_F(ST_CURRENT_CONTROL_F* pCTRL)
{
    PID_Pos_Init_F(&pCTRL->PID_Id, 0.0f);
    PID_Pos_Init_F(&pCTRL->PID_Iq, 0.0f);
}

/**********************************************************************************************
Function: MotorFoc_Current_Loop_F
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_Current_Loop_F(ST_CURRENT_CONTROL_F* pCTRL)
{
    pCTRL->_V_F_Vsd = pCTRL->_I_F_Vbus*pCTRL->_P_F_VsScale;
    pCTRL->_V_F_Vsq = pCTRL->_I_F_Vbus*pCTRL->_P_F_VsScale;
    
    pCTRL->PID_Id.F_OutMax = pCTRL->_V_F_Vsd;
    pCTRL->PID_Id.F_OutMin = -pCTRL->_V_F_Vsd;
    pCTRL->PID_Id.F_Rf = pCTRL->_I_F_IdRef;
    pCTRL->PID_Id.F_Fb = pCTRL->_I_F_Id;
    PID_Pos_Cal_F(&pCTRL->PID_Id);
    pCTRL->_O_F_Ud = pCTRL->PID_Id.F_Output;
    
    pCTRL->PID_Iq.F_OutMax = pCTRL->_V_F_Vsq;
    pCTRL->PID_Iq.F_OutMin = -pCTRL->_V_F_Vsq;
    pCTRL->PID_Iq.F_Rf = pCTRL->_I_F_IqRef;
    pCTRL->PID_Iq.F_Fb = pCTRL->_I_F_Iq;
    PID_Pos_Cal_F(&pCTRL->PID_Iq);
    pCTRL->_O_F_Uq = pCTRL->PID_Iq.F_Output;
}
