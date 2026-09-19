/*
*     File Name :                        math_pid_t
*     Library/Module Name :              math
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             PID
*/

/*-------------------------- 1. 对应头文件--------------------------------*/
#include "math_pid_t.h"

/*-------------------------- 2. 变量 ---------------------------------*/

/*-------------------------- 3. 公有接口实现 -----------------------------*/
void PID_Inc_Init_T(ST_PID_INC_T* pPID, Q32I_ init)
{
    pPID->O_Q14I_Output = init;
    pPID->V_Q14I_LastError = 0;   
    pPID->V_Q14I_PrevError = 0;
    pPID->V_Q28I_Step = 0;
    pPID->V_Q28I_Output_tmp = Q16I_LFT_14(init);
}

void PID_Inc_Cal_T(ST_PID_INC_T* pPID)
{
    Q32I_ Q14I_Error = pPID->I_Q14I_Rf - pPID->I_Q14I_Fb;
    
    pPID->V_Q28I_Step = pPID->P_Q14I_Kp*(Q14I_Error - pPID->V_Q14I_LastError) + pPID->P_Q14I_Ki*Q14I_Error
    + pPID->P_Q14I_Kd*(Q14I_Error + pPID->V_Q14I_PrevError - 2*pPID->V_Q14I_LastError);
    pPID->V_Q28I_Step = MATH_SAT_T(pPID->V_Q28I_Step, pPID->P_Q28I_StepMax, pPID->P_Q28I_StepMin);
    
    pPID->V_Q28I_Output_tmp += pPID->V_Q28I_Step;
    pPID->V_Q28I_Output_tmp = MATH_SAT_T(pPID->V_Q28I_Output_tmp, Q16I_LFT_14(pPID->P_Q14I_OutMax), Q16I_LFT_14(pPID->P_Q14I_OutMin));
    
    pPID->O_Q14I_Output = Q32I_RHT_14(pPID->V_Q28I_Output_tmp);
    pPID->V_Q14I_PrevError = pPID->V_Q14I_LastError;
    pPID->V_Q14I_LastError = Q14I_Error;
}

void PID_Pos_Init_T(ST_PID_POS_T* pPID, Q32I_ init)
{
    pPID->V_Q14I_Int = init;
    pPID->O_Q14I_Output = init;
    pPID->V_Q28I_Ui_tmp = Q16I_LFT_14(init);
}

void PID_Pos_Cal_T(ST_PID_POS_T* pPID)
{
    Q32I_ Q14I_Error = pPID->I_Q14I_Rf - pPID->I_Q14I_Fb;
    
    pPID->V_Q28I_Ui_tmp += pPID->P_Q14I_Ki*Q14I_Error;
    pPID->V_Q28I_Ui_tmp = MATH_SAT_T(pPID->V_Q28I_Ui_tmp, Q16I_LFT_14(pPID->P_Q14I_OutMax), Q16I_LFT_14(pPID->P_Q14I_OutMin));
    pPID->V_Q14I_Int = Q32I_RHT_14(pPID->V_Q28I_Ui_tmp);
    
    pPID->O_Q14I_Output = Q32I_RHT_14(pPID->P_Q14I_Kp*Q14I_Error) + pPID->V_Q14I_Int;
    pPID->O_Q14I_Output = MATH_SAT_T(pPID->O_Q14I_Output, pPID->P_Q14I_OutMax, pPID->P_Q14I_OutMin);
}

void PID_Sat_Init_T(ST_PID_SAT_T* pPID, Q32I_ init)
{
    pPID->O_Q14I_Output = init;
    pPID->V_Q14I_Int = init;
    pPID->V_Q14I_USat = 0;
    pPID->V_Q28I_Ui_tmp = Q16I_LFT_14(init);
}

void PID_Sat_Cal_T(ST_PID_SAT_T* pPID)
{
    Q32I_ Q14I_Error = pPID->I_Q14I_Rf - pPID->I_Q14I_Fb;
    Q32I_ O_Q14I_Output_tmp = 0;
    
    pPID->V_Q28I_Ui_tmp += pPID->P_Q14I_Ki*Q14I_Error - pPID->P_Q14I_Kc*pPID->V_Q14I_USat;
    pPID->V_Q28I_Ui_tmp = MATH_SAT_T(pPID->V_Q28I_Ui_tmp, Q16I_LFT_14(pPID->P_Q14I_OutMax), Q16I_LFT_14(pPID->P_Q14I_OutMin));
    pPID->V_Q14I_Int = Q32I_RHT_14(pPID->V_Q28I_Ui_tmp);
    
    O_Q14I_Output_tmp = Q32I_RHT_14(pPID->P_Q14I_Kp*Q14I_Error) + pPID->V_Q14I_Int;
    pPID->O_Q14I_Output = MATH_SAT_T(O_Q14I_Output_tmp, pPID->P_Q14I_OutMax, pPID->P_Q14I_OutMin);
    pPID->V_Q14I_USat = O_Q14I_Output_tmp - pPID->O_Q14I_Output;
}
