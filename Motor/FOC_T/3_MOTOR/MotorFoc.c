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
Function: MotorFoc_IF_Init_T
Description: IF初始化
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_IF_Init_T(ST_IF_CONTROL_T* pCTRL)
{
    pCTRL->_O_Q12U_Angle = 0;
    Ramp_Init_T(&pCTRL->Ramp_Iq, 0);
    Ramp_Init_T(&pCTRL->Ramp_SRAD, 0);
    Ramp_Init_T(&pCTRL->Ramp_AngleERR, 0);
}

/**********************************************************************************************
Function: MotorFoc_IF_OPEN_T
Description: IF开环控制函数
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_IF_OPEN_T(ST_IF_CONTROL_T* pCTRL)
{
    Ramp_Cal_T(&pCTRL->Ramp_Iq);
    Ramp_Cal_T(&pCTRL->Ramp_SRAD);
}

/**********************************************************************************************
Function: MotorFoc_IF_CLOSE_T
Description: IF闭环控制函数
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_IF_CLOSE_T(ST_IF_CONTROL_T* pCTRL)
{
    Ramp_Cal_T(&pCTRL->Ramp_AngleERR);
}

/**********************************************************************************************
Function: MotorFoc_IF_CURRENT_T
Description: IF电流环中断控制函数
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_IF_CURRENT_T(ST_IF_CONTROL_T* pCTRL)
{
    pCTRL->_O_Q12U_Angle += Q32I_RHT_16(pCTRL->_I_Q14I_DIR_Target*pCTRL->_P_Q14I_Ts*pCTRL->Ramp_SRAD.Q32I_Output);
    MATH_ANGLE_MOD_T(pCTRL->_O_Q12U_Angle);
}

/**********************************VF控制************************************/

/**********************************************************************************************
Function: MotorFoc_VF_Init_T
Description: VF初始化
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_VF_Init_T(ST_VF_CONTROL_T* pCTRL)
{
    pCTRL->_O_Q12U_Angle = 0;
    Ramp_Init_T(&pCTRL->Ramp_Vq, 0);
    Ramp_Init_T(&pCTRL->Ramp_SRAD, 0);
    Ramp_Init_T(&pCTRL->Ramp_AngleERR, 0);
}

/**********************************************************************************************
Function: MotorFoc_VF_OPEN_T
Description: VF开环控制函数
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_VF_OPEN_T(ST_VF_CONTROL_T* pCTRL)
{
    Ramp_Cal_T(&pCTRL->Ramp_Vq);
    Ramp_Cal_T(&pCTRL->Ramp_SRAD);
}

/**********************************************************************************************
Function: MotorFoc_VF_CLOSE_T
Description: VF闭环控制函数
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_VF_CLOSE_T(ST_VF_CONTROL_T* pCTRL)
{
    Ramp_Cal_T(&pCTRL->Ramp_AngleERR);
}

/**********************************************************************************************
Function: MotorFoc_VF_CURRENT_T
Description: VF电流环中断控制函数
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_VF_CURRENT_T(ST_VF_CONTROL_T* pCTRL)
{
    pCTRL->_O_Q12U_Angle += Q32I_RHT_16(pCTRL->_I_Q14I_DIR_Target*pCTRL->_P_Q14I_Ts*pCTRL->Ramp_SRAD.Q32I_Output);
    MATH_ANGLE_MOD_T(pCTRL->_O_Q12U_Angle);
}

/*********************************坐标变换*************************************/

/**********************************************************************************************
Function: MotorFoc_Clark_T
Description: Clark坐标变换函数
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_Clark_T(ST_SVPWM_CONTROL_T* pCTRL)
{
    pCTRL->_O_Q14I_Ialfa = MATH_ONE_OVER_THREE_T(2*pCTRL->_I_Q14I_Ia - pCTRL->_I_Q14I_Ib - pCTRL->_I_Q14I_Ic);
    pCTRL->_O_Q14I_Ibeta = MATH_ONE_OVER_SQRT_THREE_T(pCTRL->_I_Q14I_Ib - pCTRL->_I_Q14I_Ic);
}

/**********************************************************************************************
Function: MotorFoc_Park_T
Description: Park坐标变换函数
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_Park_T(ST_SVPWM_CONTROL_T* pCTRL)
{
    pCTRL->_O_Q14I_Id = Q32I_RHT_14( pCTRL->_O_Q14I_Ialfa*pCTRL->TG_Triangle.Q14I_Cos + pCTRL->_O_Q14I_Ibeta*pCTRL->TG_Triangle.Q14I_Sin);
    pCTRL->_O_Q14I_Iq = Q32I_RHT_14(-pCTRL->_O_Q14I_Ialfa*pCTRL->TG_Triangle.Q14I_Sin + pCTRL->_O_Q14I_Ibeta*pCTRL->TG_Triangle.Q14I_Cos);
}

/**********************************************************************************************
Function: MotorFoc_Ipark_T
Description: Ipark坐标变换函数
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_Ipark_T(ST_SVPWM_CONTROL_T* pCTRL)
{
    pCTRL->_O_Q14I_Ualfa = Q32I_RHT_14(pCTRL->_I_Q14I_Ud*pCTRL->TG_Triangle.Q14I_Cos - pCTRL->_I_Q14I_Uq*pCTRL->TG_Triangle.Q14I_Sin);
    pCTRL->_O_Q14I_Ubeta = Q32I_RHT_14(pCTRL->_I_Q14I_Ud*pCTRL->TG_Triangle.Q14I_Sin + pCTRL->_I_Q14I_Uq*pCTRL->TG_Triangle.Q14I_Cos);
}

/*********************************SVPWM*************************************/

/**********************************************************************************************
Function: MotorFoc_SVPWM_Init_T
Description: SVPWM初始化
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_SVPWM_Init_T(ST_SVPWM_CONTROL_T* pCTRL)
{
    pCTRL->TG_Triangle.Q12U_Angle = 0;
    pCTRL->TG_Triangle.Q14I_Cos = 0;
    pCTRL->TG_Triangle.Q14I_Sin = 0;
    pCTRL->TG_Triangle.Q12U_ReAngle = 0;
    
    pCTRL->_O_Q14I_Ualfa = 0;
    pCTRL->_O_Q14I_Ubeta = 0;
}

static Q08U_ Txyz_Table[3][8] = 
{{0U,1U,0U,0U,2U,2U,1U,0U},
{0U,0U,2U,1U,1U,0U,2U,0U},
{0U,2U,1U,2U,0U,1U,0U,0U}};
/**********************************************************************************************
Function: MotorFoc_SVPWM_ThreeShunt_T
Description: 常规SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_SVPWM_ThreeShunt_T(ST_SVPWM_CONTROL_T* pCTRL)
{
    Q32I_ Utmp1 = 0,Utmp2 = 0,Utmp3 = 0;
    Q32I_ Ttmp1 = 0,Ttmp2 = 0,Ttmpsum = 0;
    Q32I_ Txyz[3]= {0,0,0};
    
    Utmp1 = MATH_SQRT_THREE_T(pCTRL->_O_Q14I_Ubeta);
    Utmp2 = Q32I_RHT_10((( 3*pCTRL->_O_Q14I_Ualfa - Utmp1)>>1)*pCTRL->_I_Q10I_One_Over_Vbus);
    Utmp3 = Q32I_RHT_10(((-3*pCTRL->_O_Q14I_Ualfa - Utmp1)>>1)*pCTRL->_I_Q10I_One_Over_Vbus);
    Utmp1 = Q32I_RHT_10(Utmp1*pCTRL->_I_Q10I_One_Over_Vbus);
    
    pCTRL->_O_Q08U_Sector = 0U;
    if(Utmp1>0){pCTRL->_O_Q08U_Sector+=1U;}else{}
    if(Utmp2>0){pCTRL->_O_Q08U_Sector+=2U;}else{}
    if(Utmp3>0){pCTRL->_O_Q08U_Sector+=4U;}else{}
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
    if(Ttmpsum > pCTRL->_P_Q12I_MaxDuty){Ttmp1 = pCTRL->_P_Q12I_MaxDuty*Ttmp1/Ttmpsum;Ttmp2 = pCTRL->_P_Q12I_MaxDuty - Ttmp1;}else{}
    Txyz[0] = ((pCTRL->_P_Q12I_MaxDuty - Ttmp1 - Ttmp2)>>2) + (pCTRL->_P_Q12I_MinDuty>>1);
    Txyz[1] = Txyz[0] + (Ttmp1>>1);
    Txyz[2] = Txyz[1] + (Ttmp2>>1);
    
    switch(pCTRL->_O_Q08U_Sector)
    {
        case 3U:
        {
            pCTRL->_O_Q14I_Ualfa = Q32I_RHT_14(MATH_ONE_OVER_THREE_T(2*Ttmp1+Ttmp2)*pCTRL->_I_Q14I_Vbus);
            pCTRL->_O_Q14I_Ubeta = Q32I_RHT_14(MATH_ONE_OVER_SQRT_THREE_T(Ttmp2)*pCTRL->_I_Q14I_Vbus);
            break;
        }
        case 1U:
        {
            pCTRL->_O_Q14I_Ualfa = Q32I_RHT_14(MATH_ONE_OVER_THREE_T(Ttmp2-Ttmp1)*pCTRL->_I_Q14I_Vbus);
            pCTRL->_O_Q14I_Ubeta = Q32I_RHT_14(MATH_ONE_OVER_SQRT_THREE_T(Ttmp1+Ttmp2)*pCTRL->_I_Q14I_Vbus);
            break;
        }
        case 5U:
        {
            pCTRL->_O_Q14I_Ualfa = Q32I_RHT_14(MATH_ONE_OVER_THREE_T(-2*Ttmp2-Ttmp1)*pCTRL->_I_Q14I_Vbus);
            pCTRL->_O_Q14I_Ubeta = Q32I_RHT_14(MATH_ONE_OVER_SQRT_THREE_T(Ttmp1)*pCTRL->_I_Q14I_Vbus);
            break;
        }
        case 4U:
        {
            pCTRL->_O_Q14I_Ualfa = Q32I_RHT_14(MATH_ONE_OVER_THREE_T(-2*Ttmp2-Ttmp1)*pCTRL->_I_Q14I_Vbus);
            pCTRL->_O_Q14I_Ubeta = Q32I_RHT_14(-MATH_ONE_OVER_SQRT_THREE_T(Ttmp1)*pCTRL->_I_Q14I_Vbus);
            break;
        }
        case 6U:
        {
            pCTRL->_O_Q14I_Ualfa = Q32I_RHT_14(MATH_ONE_OVER_THREE_T(Ttmp2-Ttmp1)*pCTRL->_I_Q14I_Vbus);
            pCTRL->_O_Q14I_Ubeta = Q32I_RHT_14(MATH_ONE_OVER_SQRT_THREE_T(-Ttmp1-Ttmp2)*pCTRL->_I_Q14I_Vbus);
            break;
        }
        case 2U:
        {
            pCTRL->_O_Q14I_Ualfa = Q32I_RHT_14(MATH_ONE_OVER_THREE_T(2*Ttmp1+Ttmp2)*pCTRL->_I_Q14I_Vbus);
            pCTRL->_O_Q14I_Ubeta = Q32I_RHT_14(-MATH_ONE_OVER_SQRT_THREE_T(Ttmp2)*pCTRL->_I_Q14I_Vbus);
            break;
        }
        default:break;
    }
    
    pCTRL->_O_Q12I_Ta = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]];
    pCTRL->_O_Q12I_Tb = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]];
    pCTRL->_O_Q12I_Tc = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]];
}

/********************************单电阻电流重构**************************************/

static Q08U_ ADC_Table[3][8] = 
{{0U,2U,0U,0U,1U,1U,2U,0U},
 {0U,0U,1U,2U,2U,0U,1U,0U},
 {0U,1U,2U,1U,0U,2U,0U,0U}};
/**********************************************************************************************
Function: MotorFoc_OneShunt_Cal_T
Description: 单电阻采样电流查表
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_OneShunt_Cal_T(ST_SVPWM_CONTROL_T* pCTRL)
{
    pCTRL->_I_Q14I_Ia = pCTRL->_I_Q14I_Ishunt[ADC_Table[0][pCTRL->_O_Q08U_Sector]];
    pCTRL->_I_Q14I_Ib = pCTRL->_I_Q14I_Ishunt[ADC_Table[1][pCTRL->_O_Q08U_Sector]];
    pCTRL->_I_Q14I_Ic = pCTRL->_I_Q14I_Ishunt[ADC_Table[2][pCTRL->_O_Q08U_Sector]];
}

/**********************************************************************************************
Function: MotorFoc_SVPWM_OneShunt_T
Description: 移相SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_SVPWM_OneShunt_T(ST_SVPWM_CONTROL_T* pCTRL)
{
    Q32I_ Utmp1 = 0,Utmp2 = 0,Utmp3 = 0;
    Q32I_ Ttmp1 = 0,Ttmp2 = 0,Ttmpsum = 0;
    Q32I_ Txyz[3]= {0,0,0};
    Q32I_ Delta_Ttmp1 = 0,Delta_Ttmp2 = 0,Delta_Ttmp3 = 0;
    
    Utmp1 = MATH_SQRT_THREE_T(pCTRL->_O_Q14I_Ubeta);
    Utmp2 = Q32I_RHT_10((( 3*pCTRL->_O_Q14I_Ualfa - Utmp1)>>1)*pCTRL->_I_Q10I_One_Over_Vbus);
    Utmp3 = Q32I_RHT_10(((-3*pCTRL->_O_Q14I_Ualfa - Utmp1)>>1)*pCTRL->_I_Q10I_One_Over_Vbus);
    Utmp1 = Q32I_RHT_10(Utmp1*pCTRL->_I_Q10I_One_Over_Vbus);
    
    pCTRL->_O_Q08U_Sector = 0U;
    if(Utmp1>0){pCTRL->_O_Q08U_Sector+=1U;}else{}
    if(Utmp2>0){pCTRL->_O_Q08U_Sector+=2U;}else{}
    if(Utmp3>0){pCTRL->_O_Q08U_Sector+=4U;}else{}
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
    if(Ttmpsum > pCTRL->_P_Q12I_MaxDuty){Ttmp1 = pCTRL->_P_Q12I_MaxDuty*Ttmp1/Ttmpsum;Ttmp2 = pCTRL->_P_Q12I_MaxDuty - Ttmp1;}else{}
//    Txyz[0] = (4096U - Ttmp1 - Ttmp2)>>2;
//    Txyz[1] = Txyz[0] + (Ttmp1>>1);
//    Txyz[2] = Txyz[1] + (Ttmp2>>1);
    
    Txyz[2] = (4096U - Ttmp1 - Ttmp2)>>2;
    Txyz[1] = Txyz[2] + (Ttmp2>>1);
    Txyz[0] = Txyz[1] + (Ttmp1>>1);
    
    if((Ttmp1 < pCTRL->_P_Q12I_MinDuty)&&(Ttmp2 < pCTRL->_P_Q12I_MinDuty))
    {
        Delta_Ttmp1 =  (pCTRL->_P_Q12I_MinDuty - Ttmp1)>>1;
        Delta_Ttmp3 = -(pCTRL->_P_Q12I_MinDuty - Ttmp2)>>1;
    }
    else if((Ttmp1 < pCTRL->_P_Q12I_MinDuty)&&(Ttmp2 >= pCTRL->_P_Q12I_MinDuty))
    {
        Delta_Ttmp1 =  (pCTRL->_P_Q12I_MinDuty - Ttmp1)>>2;
        Delta_Ttmp2 = -pCTRL->_P_Q12I_MinDuty>>2;
    }
    else if((Ttmp1 >= pCTRL->_P_Q12I_MinDuty)&&(Ttmp2 < pCTRL->_P_Q12I_MinDuty))
    {
        Delta_Ttmp2 =  pCTRL->_P_Q12I_MinDuty>>2;
        Delta_Ttmp3 = -(pCTRL->_P_Q12I_MinDuty - Ttmp2)>>2;
    }
    
    pCTRL->_O_Q12I_ADCTrigTime1 = Txyz[0] + Delta_Ttmp1 - pCTRL->_P_Q12I_ADCSampleDuty;
    pCTRL->_O_Q12I_ADCTrigTime2 = Txyz[1] + Delta_Ttmp2 - pCTRL->_P_Q12I_ADCSampleDuty;
    
    switch(pCTRL->_O_Q08U_Sector)
    {
        case 3U:
        {
            pCTRL->_O_Q14I_Ualfa = Q32I_RHT_14(MATH_ONE_OVER_THREE_T(2*Ttmp1+Ttmp2)*pCTRL->_I_Q14I_Vbus);
            pCTRL->_O_Q14I_Ubeta = Q32I_RHT_14(MATH_ONE_OVER_SQRT_THREE_T(Ttmp2)*pCTRL->_I_Q14I_Vbus);
            
            pCTRL->_O_Q12I_TaUp = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp1;
            pCTRL->_O_Q12I_TbUp = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp2;
            pCTRL->_O_Q12I_TcUp = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp3;
            pCTRL->_O_Q12I_TaDn = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp1;
            pCTRL->_O_Q12I_TbDn = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp2;
            pCTRL->_O_Q12I_TcDn = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp3;
            break;
        }
        case 1U:
        {
            pCTRL->_O_Q14I_Ualfa = Q32I_RHT_14(MATH_ONE_OVER_THREE_T(Ttmp2-Ttmp1)*pCTRL->_I_Q14I_Vbus);
            pCTRL->_O_Q14I_Ubeta = Q32I_RHT_14(MATH_ONE_OVER_SQRT_THREE_T(Ttmp1+Ttmp2)*pCTRL->_I_Q14I_Vbus);
            
            pCTRL->_O_Q12I_TaUp = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp2;
            pCTRL->_O_Q12I_TbUp = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp1;
            pCTRL->_O_Q12I_TcUp = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp3;
            pCTRL->_O_Q12I_TaDn = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp2;
            pCTRL->_O_Q12I_TbDn = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp1;
            pCTRL->_O_Q12I_TcDn = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp3;
            break;
        }
        case 5U:
        {
            pCTRL->_O_Q14I_Ualfa = Q32I_RHT_14(MATH_ONE_OVER_THREE_T(-2*Ttmp2-Ttmp1)*pCTRL->_I_Q14I_Vbus);
            pCTRL->_O_Q14I_Ubeta = Q32I_RHT_14(MATH_ONE_OVER_SQRT_THREE_T(Ttmp1)*pCTRL->_I_Q14I_Vbus);
            
            pCTRL->_O_Q12I_TaUp = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp3;
            pCTRL->_O_Q12I_TbUp = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp1;
            pCTRL->_O_Q12I_TcUp = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp2;
            pCTRL->_O_Q12I_TaDn = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp3;
            pCTRL->_O_Q12I_TbDn = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp1;
            pCTRL->_O_Q12I_TcDn = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp2;
            break;
        }
        case 4U:
        {
            pCTRL->_O_Q14I_Ualfa = Q32I_RHT_14(MATH_ONE_OVER_THREE_T(-2*Ttmp2-Ttmp1)*pCTRL->_I_Q14I_Vbus);
            pCTRL->_O_Q14I_Ubeta = Q32I_RHT_14(-MATH_ONE_OVER_SQRT_THREE_T(Ttmp1)*pCTRL->_I_Q14I_Vbus);
            
            pCTRL->_O_Q12I_TaUp = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp3;
            pCTRL->_O_Q12I_TbUp = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp2;
            pCTRL->_O_Q12I_TcUp = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp1;
            pCTRL->_O_Q12I_TaDn = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp3;
            pCTRL->_O_Q12I_TbDn = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp2;
            pCTRL->_O_Q12I_TcDn = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp1;
            break;
        }
        case 6U:
        {
            pCTRL->_O_Q14I_Ualfa = Q32I_RHT_14(MATH_ONE_OVER_THREE_T(Ttmp2-Ttmp1)*pCTRL->_I_Q14I_Vbus);
            pCTRL->_O_Q14I_Ubeta = Q32I_RHT_14(MATH_ONE_OVER_SQRT_THREE_T(-Ttmp1-Ttmp2)*pCTRL->_I_Q14I_Vbus);
            
            pCTRL->_O_Q12I_TaUp = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp2;
            pCTRL->_O_Q12I_TbUp = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp3;
            pCTRL->_O_Q12I_TcUp = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp1;
            pCTRL->_O_Q12I_TaDn = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp2;
            pCTRL->_O_Q12I_TbDn = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp3;
            pCTRL->_O_Q12I_TcDn = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp1;
            break;
        }
        case 2U:
        {
            pCTRL->_O_Q14I_Ualfa = Q32I_RHT_14(MATH_ONE_OVER_THREE_T(2*Ttmp1+Ttmp2)*pCTRL->_I_Q14I_Vbus);
            pCTRL->_O_Q14I_Ubeta = Q32I_RHT_14(-MATH_ONE_OVER_SQRT_THREE_T(Ttmp2)*pCTRL->_I_Q14I_Vbus);
            
            pCTRL->_O_Q12I_TaUp = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp1;
            pCTRL->_O_Q12I_TbUp = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp3;
            pCTRL->_O_Q12I_TcUp = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] + Delta_Ttmp2;
            pCTRL->_O_Q12I_TaDn = Txyz[Txyz_Table[0][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp1;
            pCTRL->_O_Q12I_TbDn = Txyz[Txyz_Table[1][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp3;
            pCTRL->_O_Q12I_TcDn = Txyz[Txyz_Table[2][pCTRL->_O_Q08U_Sector]] - Delta_Ttmp2;
            break;
        }
        default:break;
    }
}

/********************************速度环**************************************/

/**********************************************************************************************
Function: MotorFoc_SRAD_Init_T
Description: 移相SVPWM
Input: 无
Output: 无
Input_Output: 速度环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_SRAD_Init_T(ST_SRAD_CONTROL_T* pCTRL)
{
    PID_Pos_Init_T(&pCTRL->PID_SRAD, 0);
    PID_Pos_Init_T(&pCTRL->PID_WEAK, 0);
    Ramp_Init_T(&pCTRL->Ramp_SRAD, 0);
}

/**********************************************************************************************
Function: MotorFoc_SRAD_Loop_T
Description: 速度环控制
Input: 无
Output: 无
Input_Output: 速度环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_SRAD_Loop_T(ST_SRAD_CONTROL_T* pCTRL)
{
    pCTRL->Ramp_SRAD.Q32I_Target = MATH_SAT_T(pCTRL->_I_Q14I_SRAD_Target, pCTRL->_P_Q14I_SRAD_Max, pCTRL->_P_Q14I_SRAD_Min);
    Ramp_Cal_T(&pCTRL->Ramp_SRAD);
    
    pCTRL->PID_SRAD.Q14I_Rf = pCTRL->Ramp_SRAD.Q32I_Output;
    pCTRL->PID_SRAD.Q14I_Fb = pCTRL->_I_Q14I_SRAD;
    PID_Pos_Cal_T(&pCTRL->PID_SRAD);
    
    pCTRL->PID_WEAK.Q14I_Rf = MATH_ONE_OVER_SQRT_THREE_T(pCTRL->_I_Q14I_Vbus);
    pCTRL->PID_WEAK.Q14I_Fb = MATH_SQUARE_T(pCTRL->_I_Q14I_Ud) + MATH_SQUARE_T(pCTRL->_I_Q14I_Uq);
    PID_Pos_Cal_T(&pCTRL->PID_WEAK);
    
    pCTRL->TG_Triangle.Q12U_Angle = pCTRL->PID_WEAK.Q14I_Output;
    Math_SinCos_T(&pCTRL->TG_Triangle);
    
    pCTRL->_O_Q14I_IdRef = Q32I_RHT_14(pCTRL->PID_SRAD.Q14I_Output*pCTRL->TG_Triangle.Q14I_Sin);
    pCTRL->_O_Q14I_IqRef = Q32I_RHT_14(pCTRL->PID_SRAD.Q14I_Output*pCTRL->TG_Triangle.Q14I_Cos);
}

/*******************************电流环***************************************/

/**********************************************************************************************
Function: MotorFoc_Current_Init_T
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_Current_Init_T(ST_CURRENT_CONTROL_T* pCTRL)
{
    PID_Pos_Init_T(&pCTRL->PID_Id, 0);
    PID_Pos_Init_T(&pCTRL->PID_Iq, 0);
}

/**********************************************************************************************
Function: MotorFoc_Current_Loop_T
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_Current_Loop_T(ST_CURRENT_CONTROL_T* pCTRL)
{
    pCTRL->_V_Q14I_Vsd = Q32I_RHT_14(pCTRL->_I_Q14I_Vbus*pCTRL->_P_Q14I_VsScale);
    pCTRL->_V_Q14I_Vsq = Q32I_RHT_14(pCTRL->_I_Q14I_Vbus*pCTRL->_P_Q14I_VsScale);
    
    pCTRL->PID_Id.Q14I_OutMax = pCTRL->_V_Q14I_Vsd;
    pCTRL->PID_Id.Q14I_OutMin = -pCTRL->_V_Q14I_Vsd;
    pCTRL->PID_Id.Q14I_Rf = pCTRL->_I_Q14I_IdRef;
    pCTRL->PID_Id.Q14I_Fb = pCTRL->_I_Q14I_Id;
    PID_Pos_Cal_T(&pCTRL->PID_Id);
    pCTRL->_O_Q14I_Ud = pCTRL->PID_Id.Q14I_Output;
    
    pCTRL->PID_Iq.Q14I_OutMax = pCTRL->_V_Q14I_Vsq;
    pCTRL->PID_Iq.Q14I_OutMin = -pCTRL->_V_Q14I_Vsq;
    pCTRL->PID_Iq.Q14I_Rf = pCTRL->_I_Q14I_IqRef;
    pCTRL->PID_Iq.Q14I_Fb = pCTRL->_I_Q14I_Iq;
    PID_Pos_Cal_T(&pCTRL->PID_Iq);
    pCTRL->_O_Q14I_Uq = pCTRL->PID_Iq.Q14I_Output;
}
