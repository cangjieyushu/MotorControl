/*
*     File Name :                        math_pid_f
*     Library/Module Name :              math
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             PID
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "math_pid_f.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
void PID_Pos_Init_F(ST_PID_POS_F* pPID, float init)
{
    pPID->O_F_Output = init;
    pPID->V_F_Int = init;
}

void PID_Pos_Cal_F(ST_PID_POS_F* pPID)
{
    float F_Error = pPID->I_F_Rf - pPID->I_F_Fb;
    
    pPID->V_F_Int += pPID->P_F_Ki*F_Error;
    pPID->V_F_Int = MATH_SAT_F(pPID->V_F_Int, pPID->P_F_OutMax, pPID->P_F_OutMin);
    
    pPID->O_F_Output = pPID->P_F_Kp*F_Error + pPID->V_F_Int;
    pPID->O_F_Output = MATH_SAT_F(pPID->O_F_Output, pPID->P_F_OutMax, pPID->P_F_OutMin);
}

void PID_Sat_Init_F(ST_PID_SAT_F* pPID, float init)
{
    pPID->O_F_Output = init;
    pPID->V_F_Int = init;
    pPID->V_F_USat = 0.0f;
}

void PID_Sat_Cal_F(ST_PID_SAT_F* pPID)
{
    float F_Error = pPID->I_F_Rf - pPID->I_F_Fb;
    float F_Output_tmp = 0.0f;
    
    pPID->V_F_Int += pPID->P_F_Ki*F_Error - pPID->P_F_Kc*pPID->V_F_USat;
    
    F_Output_tmp = pPID->P_F_Kp*F_Error + pPID->V_F_Int;
    pPID->O_F_Output = MATH_SAT_F(F_Output_tmp, pPID->P_F_OutMax, pPID->P_F_OutMin);
    pPID->V_F_USat = F_Output_tmp - pPID->O_F_Output;
}
