/*
*     File Name :                        mcfoc_svpwm_f
*     Library/Module Name :              mcfoc_f
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC算法
*/


#ifndef MCFOC_SVPWM_F_H
#define MCFOC_SVPWM_F_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_ramp_f.h"
#include "mcfoc_pmsm_f.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef struct
{
    ST_CHECK        FIVE_CHECK;
    
    Q32U_       O_Q32U_Five_Flag;
    Q32U_       O_Q32U_Five_Flag_Real;
    Q32U_       O_Q32U_Sector;
    
    float       O_F_Dutya;
    float       O_F_Dutyb;
    float       O_F_Dutyc;
    
    float       O_F_TaUp;
    float       O_F_TbUp;
    float       O_F_TcUp;
    float       O_F_TaDn;
    float       O_F_TbDn;
    float       O_F_TcDn;
    float       O_F_ADCTrigTime1;
    float       O_F_ADCTrigTime2;
    
    float       P_F_MaxDuty;
    float       P_F_MidDuty;
    float       P_F_MinDuty;
    float       P_F_ADCSampleDuty;
    
    float       P_F_PWM_All_Count;
    float       P_F_DeadTimeDuty;
    float       P_F_DT_Current_TL;
}ST_SVPWM_CONTROL_F;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: MCFOC_SVPWM_Init_F
Description: SVPWM初始化
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
*/
void MCFOC_SVPWM_Init_F(ST_SVPWM_CONTROL_F* pSVPWM);

/*
Function: MCFOC_SevFiv_Check_F
Description: 七--五段式切换判断
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_SevFiv_Check_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe);

/*
Function: MCFOC_ThreeShunt_Current_Cal_F
Description: 三电阻采样电流查表
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_ThreeShunt_Current_Cal_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe);

/*
Function: MCFOC_SVPWM_ThreeShunt_F
Description: 三电阻SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_SVPWM_ThreeShunt_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe);

/*
Function: MCFOC_OneShunt_Current_Cal_F
Description: 单电阻采样电流查表
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_OneShunt_Current_Cal_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe);

/*
Function: MCFOC_SVPWM_OneShunt_F
Description: 单电阻SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_SVPWM_OneShunt_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe);

/*
Function: MCFOC_SVPWM_Duty_Refactor_F
Description: 占空比重构
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_SVPWM_Duty_Refactor_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe);

/*
Function: MCFOC_SVPWM_DeadTime_Compensate_F
Description: 死区补偿
Input: 无
Output: 无
Input_Output: SVPWM控制指针，PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_SVPWM_DeadTime_Compensate_F(ST_SVPWM_CONTROL_F* pSVPWM, ST_PMSM_ELEC_F* pPMSMe);


#endif /* MCFOC_SVPWM_F_H */
