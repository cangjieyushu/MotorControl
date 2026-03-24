/**************************************************************************************************
*     File Name :                        MATH_PID_F.c
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             PID
**************************************************************************************************/

#include "MATH_PID_F.h"


/**********************************************************************************************
Function: PID_Pos_Init_F
Description: 浮点位置式PID初始化
Input: 浮点积分器初始值
Output: 无
Input_Output: 浮点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Init_F(ST_PID_POS_F* pPID, float init)
{
    pPID->F_Rf = 0.0f;
    pPID->F_Fb = 0.0f;
    pPID->F_Int = init;
    pPID->F_Output = init;
}

/**********************************************************************************************
Function: PID_Pos_Cal_F
Description: 浮点位置式PID计算
Input: 无
Output: 无
Input_Output: 浮点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Cal_F(ST_PID_POS_F* pPID)
{
    float F_Error = pPID->F_Rf - pPID->F_Fb;
    
    pPID->F_Int += pPID->F_Ki*F_Error;
    pPID->F_Int = MATH_SAT_F(pPID->F_Int, pPID->F_OutMax, pPID->F_OutMin);
    
    pPID->F_Output = pPID->F_Kp*F_Error + pPID->F_Int;
    pPID->F_Output = MATH_SAT_F(pPID->F_Output, pPID->F_OutMax, pPID->F_OutMin);
}

/**********************************************************************************************
Function: PID_Sat_Init_F
Description: 抗饱和位置式PID初始化
Input: 抗饱和积分器初始值
Output: 无
Input_Output: 抗饱和位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Sat_Init_F(ST_PID_SAT_F* pPID, float init)
{
    pPID->F_Rf = 0.0f;
    pPID->F_Fb = 0.0f;
    pPID->F_Int = init;
    pPID->F_USat = 0.0f;
    pPID->F_Output = init;
}

/**********************************************************************************************
Function: PID_Sat_Cal_F
Description: 抗饱和位置式PID计算
Input: 无
Output: 无
Input_Output: 抗饱和位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Sat_Cal_F(ST_PID_SAT_F* pPID)
{
    float F_Error = pPID->F_Rf - pPID->F_Fb;
    float F_Output_tmp = 0.0f;
    
    pPID->F_Int += pPID->F_Ki*F_Error - pPID->F_Kc*pPID->F_USat;
    
    F_Output_tmp = pPID->F_Kp*F_Error + pPID->F_Int;
    pPID->F_Output = MATH_SAT_F(F_Output_tmp, pPID->F_OutMax, pPID->F_OutMin);
    pPID->F_USat = F_Output_tmp - pPID->F_Output;
}
