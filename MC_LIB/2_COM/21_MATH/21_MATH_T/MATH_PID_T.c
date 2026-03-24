/**************************************************************************************************
*     File Name :                        MATH_PID_T.c
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             PID
**************************************************************************************************/

#include "MATH_PID_T.h"


/**********************************************************************************************
Function: PID_Inc_Init_T
Description: 定点增量式PID初始化
Input: 定点积分器初始值
Output: 无
Input_Output: 定点增量式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Inc_Init_T(ST_PID_INC_T* pPID, Q32I_ init)
{
    pPID->Q14I_Rf = 0;
    pPID->Q14I_Fb = 0;
    pPID->Q28I_Step = 0;
    pPID->Q14I_LastError = 0;   
    pPID->Q14I_PrevError = 0;
    pPID->Q14I_Output = init;
    pPID->Q28I_Output_tmp = Q16I_LFT_14(init);
}

/**********************************************************************************************
Function: PID_Inc_Cal_T
Description: 定点增量式PID计算
Input: 无
Output: 无
Input_Output: 定点增量式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Inc_Cal_T(ST_PID_INC_T* pPID)
{
    Q32I_ Q14I_Error = pPID->Q14I_Rf - pPID->Q14I_Fb;
    
    pPID->Q28I_Step = pPID->Q14I_Kp*(Q14I_Error - pPID->Q14I_LastError) + pPID->Q14I_Ki*Q14I_Error
    + pPID->Q14I_Kd*(Q14I_Error + pPID->Q14I_PrevError - 2*pPID->Q14I_LastError);
    pPID->Q28I_Step = MATH_SAT_T(pPID->Q28I_Step, pPID->Q28I_StepMax, pPID->Q28I_StepMin);
    
    pPID->Q28I_Output_tmp += pPID->Q28I_Step;
    pPID->Q28I_Output_tmp = MATH_SAT_T(pPID->Q28I_Output_tmp, Q16I_LFT_14(pPID->Q14I_OutMax), Q16I_LFT_14(pPID->Q14I_OutMin));
    
    pPID->Q14I_Output = Q32I_RHT_14(pPID->Q28I_Output_tmp);
    pPID->Q14I_PrevError = pPID->Q14I_LastError;
    pPID->Q14I_LastError = Q14I_Error;
}

/**********************************************************************************************
Function: PID_Pos_Init_T
Description: 定点位置式PID初始化
Input: 定点积分器初始值
Output: 无
Input_Output: 定点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Init_T(ST_PID_POS_T* pPID, Q32I_ init)
{
    pPID->Q14I_Rf = 0;
    pPID->Q14I_Fb = 0;
    pPID->Q14I_Int = init;
    pPID->Q28I_Ui_tmp = Q16I_LFT_14(init);
    pPID->Q14I_Output = init;
}

/**********************************************************************************************
Function: PID_Pos_Cal_T
Description: 定点位置式PID计算
Input: 无
Output: 无
Input_Output: 定点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Cal_T(ST_PID_POS_T* pPID)
{
    Q32I_ Q14I_Error = pPID->Q14I_Rf - pPID->Q14I_Fb;
    
    pPID->Q28I_Ui_tmp += pPID->Q14I_Ki*Q14I_Error;
    pPID->Q28I_Ui_tmp = MATH_SAT_T(pPID->Q28I_Ui_tmp, Q16I_LFT_14(pPID->Q14I_OutMax), Q16I_LFT_14(pPID->Q14I_OutMin));
    pPID->Q14I_Int = Q32I_RHT_14(pPID->Q28I_Ui_tmp);
    
    pPID->Q14I_Output = Q32I_RHT_14(pPID->Q14I_Kp*Q14I_Error) + pPID->Q14I_Int;
    pPID->Q14I_Output = MATH_SAT_T(pPID->Q14I_Output, pPID->Q14I_OutMax, pPID->Q14I_OutMin);
}

/**********************************************************************************************
Function: PID_Sat_Init_T
Description: 抗饱和位置式PID初始化
Input: 抗饱和积分器初始值
Output: 无
Input_Output: 抗饱和位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Sat_Init_T(ST_PID_SAT_T* pPID, Q32I_ init)
{
    pPID->Q14I_Rf = 0;
    pPID->Q14I_Fb = 0;
    pPID->Q14I_Int = init;
    pPID->Q28I_Ui_tmp = Q16I_LFT_14(init);
    pPID->Q14I_USat = 0;
    pPID->Q14I_Output = init;
}

/**********************************************************************************************
Function: PID_Sat_Cal_T
Description: 抗饱和位置式PID计算
Input: 无
Output: 无
Input_Output: 抗饱和位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Sat_Cal_T(ST_PID_SAT_T* pPID)
{
    Q32I_ Q14I_Error = pPID->Q14I_Rf - pPID->Q14I_Fb;
    Q32I_ Q14I_Output_tmp = 0;
    
    pPID->Q28I_Ui_tmp += pPID->Q14I_Ki*Q14I_Error - pPID->Q14I_Kc*pPID->Q14I_USat;
    pPID->Q28I_Ui_tmp = MATH_SAT_T(pPID->Q28I_Ui_tmp, Q16I_LFT_14(pPID->Q14I_OutMax), Q16I_LFT_14(pPID->Q14I_OutMin));
    pPID->Q14I_Int = Q32I_RHT_14(pPID->Q28I_Ui_tmp);
    
    Q14I_Output_tmp = Q32I_RHT_14(pPID->Q14I_Kp*Q14I_Error) + pPID->Q14I_Int;
    pPID->Q14I_Output = MATH_SAT_T(Q14I_Output_tmp, pPID->Q14I_OutMax, pPID->Q14I_OutMin);
    pPID->Q14I_USat = Q14I_Output_tmp - pPID->Q14I_Output;
}
