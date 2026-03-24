/**************************************************************************************************
*     File Name :                        MCFOC_SVPWM_F.h
*     Library/Module Name :              MCFOC_F
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC算法头文件
**************************************************************************************************/

#ifndef MCFOC_SVPWM_F_H
#define MCFOC_SVPWM_F_H


#include "MATH_RAMP_F.h"
#include "MCFOC_PMSM_F.h"


typedef struct
{
    ST_CHECK        FIVE_CHECK;

    Q32U_       _O_Q32U_Five_Flag;
    Q32U_       _O_Q32U_Five_Flag_Real;
    Q32U_       _O_Q32U_Sector;
    
    float       _O_F_Dutya;
    float       _O_F_Dutyb;
    float       _O_F_Dutyc;
    
    float       _O_F_TaUp;
    float       _O_F_TbUp;
    float       _O_F_TcUp;
    float       _O_F_TaDn;
    float       _O_F_TbDn;
    float       _O_F_TcDn;
    float       _O_F_ADCTrigTime1;
    float       _O_F_ADCTrigTime2;
    
    float       _P_F_MaxDuty;
    float       _P_F_MidDuty;
    float       _P_F_MinDuty;
    float       _P_F_ADCSampleDuty;
    
    float       _P_F_PWM_All_Count;
    float       _P_F_DeadTimeDuty;
    float       _P_F_DT_Current_TL;
}ST_SVPWM_CONTROL_F;


/**********************************************************************************************
Function: MCFOC_SVPWM_Init_F
Description: SVPWM初始化
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SVPWM_Init_F(ST_SVPWM_CONTROL_F* pSVPWM);

/**********************************************************************************************
Function: MCFOC_Five_Cal_F
Description: 五段式切换判断
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Five_Cal_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe);

/**********************************************************************************************
Function: MCFOC_ThreeShunt_Current_Cal_F
Description: 三电阻采样电流查表
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ThreeShunt_Current_Cal_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe);

/**********************************************************************************************
Function: MCFOC_SVPWM_ThreeShunt_F
Description: 三电阻SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SVPWM_ThreeShunt_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe);

/**********************************************************************************************
Function: MCFOC_OneShunt_Current_Cal_F
Description: 单电阻采样电流查表
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_OneShunt_Current_Cal_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe);

/**********************************************************************************************
Function: MCFOC_SVPWM_OneShunt_F
Description: 单电阻SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SVPWM_OneShunt_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe);

/**********************************************************************************************
Function: MCFOC_Duty_Resolution_F
Description: 占空比重构
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Duty_Resolution_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe);

/**********************************************************************************************
Function: MCFOC_DeadTime_COMP_F
Description: 死区补偿
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_DeadTime_COMP_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe);


#endif /* MCFOC_SVPWM_F_H */
