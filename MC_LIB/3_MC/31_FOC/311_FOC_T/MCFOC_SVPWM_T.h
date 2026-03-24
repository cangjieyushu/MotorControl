/**************************************************************************************************
*     File Name :                        MCFOC_SVPWM_T.h
*     Library/Module Name :              MCFOC_T
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC算法头文件
**************************************************************************************************/

#ifndef MCFOC_SVPWM_T_H
#define MCFOC_SVPWM_T_H


#include "MATH_RAMP_T.h"
#include "MCFOC_PMSM_T.h"


typedef struct
{
    ST_CHECK        FIVE_CHECK;

    Q32U_       _O_Q32U_Five_Flag;
    Q32U_       _O_Q32U_Five_Flag_Real;
    Q32U_       _O_Q32U_Sector;
    
    Q32I_       _O_Q14U_Dutya;
    Q32I_       _O_Q14U_Dutyb;
    Q32I_       _O_Q14U_Dutyc;
    
    Q32I_       _O_Q14U_TaUp;
    Q32I_       _O_Q14U_TbUp;
    Q32I_       _O_Q14U_TcUp;
    Q32I_       _O_Q14U_TaDn;
    Q32I_       _O_Q14U_TbDn;
    Q32I_       _O_Q14U_TcDn;
    Q32I_       _O_Q14U_ADCTrigTime1;
    Q32I_       _O_Q14U_ADCTrigTime2;
    
    Q32I_       _P_Q14U_MaxDuty;
    Q32I_       _P_Q14U_MidDuty;
    Q32I_       _P_Q14U_MinDuty;
    Q32I_       _P_Q14U_ADCSampleDuty;
    
    Q32I_       _P_Q32U_PWM_All_Count;
    Q32I_       _P_Q14U_DeadTimeDuty;
    Q32I_       _P_Q14I_DT_Current_TL;
}ST_SVPWM_CONTROL_T;


/**********************************************************************************************
Function: MCFOC_SVPWM_Init_T
Description: SVPWM初始化
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SVPWM_Init_T(ST_SVPWM_CONTROL_T* pSVPWM);

/**********************************************************************************************
Function: MCFOC_Tive_Cal_T
Description: 五段式切换判断
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Five_Cal_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe);

/**********************************************************************************************
Function: MCFOC_ThreeShunt_Current_Cal_T
Description: 三电阻采样电流查表
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ThreeShunt_Current_Cal_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe);

/**********************************************************************************************
Function: MCFOC_SVPWM_ThreeShunt_T
Description: 三电阻SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SVPWM_ThreeShunt_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe);

/**********************************************************************************************
Function: MCFOC_OneShunt_Current_Cal_T
Description: 单电阻采样电流查表
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_OneShunt_Current_Cal_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe);

/**********************************************************************************************
Function: MCFOC_SVPWM_OneShunt_T
Description: 单电阻SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SVPWM_OneShunt_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe);

/**********************************************************************************************
Function: MCFOC_Duty_Resolution_T
Description: 占空比重构
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Duty_Resolution_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe);

/**********************************************************************************************
Function: MCFOC_DeadTime_COMP_T
Description: 死区补偿
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_DeadTime_COMP_T(ST_SVPWM_CONTROL_T* pSVPWM, ST_PMSM_ELEC_T* pPMSMe);


#endif /* MCFOC_SVPWM_T_H */
