/**************************************************************************************************
*     File Name :                        MCFOC_LOOP_T.h
*     Library/Module Name :              MCFOC_T
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC算法头文件
**************************************************************************************************/

#ifndef MCFOC_LOOP_T_H
#define MCFOC_LOOP_T_H


#include "MATH_CHECK.h"
#include "MATH_ANGLE_T.h"
#include "MATH_LPF_T.h"
#include "MATH_PID_T.h"
#include "MATH_RAMP_T.h"
#include "MCFOC_PMSM_T.h"


typedef enum
{
    ING,
    SUCS,
    FAIL,
}EM_FLAG_STATE;

typedef struct
{
    Q32I_       _I_Q12I_Ia_Data;
    Q32I_       _I_Q12I_Ib_Data;
    Q32I_       _I_Q12I_Ic_Data;
    Q32I_       _I_Q12I_Ishunt_Data;
    
    Q32I_       _V_Q12I_Ia_Offset;
    Q32I_       _V_Q12I_Ib_Offset;
    Q32I_       _V_Q12I_Ic_Offset;
    Q32I_       _V_Q12I_Ishunt_Offset;

    Q32U_       _V_Q32U_Offset_Check_cnt;
    
    Q32I_       _P_Q12U_Offset_Max;
    Q32I_       _P_Q12U_Offset_Min;
    Q32U_       _P_Q16U_Offset_Check_Count;
}ST_MCFOC_OFFSET_T;

typedef struct
{
    ST_RAMP_T   Ramp_Align_Id;
    ST_RAMP_T   Ramp_Align_Angle;
    
    Q32U_       _V_Q32U_Align_Check_cnt;

    Q32U_       _O_Q32U_Stand_Flag;
    Q32I_       _O_Q14I_Align_IdRef;
    Q32I_       _O_Q14I_Align_Angle;

    Q32U_       _P_Q32U_Align_Check_Count;
}ST_ALIGN_CONTROL_T;

typedef struct
{
    ST_RAMP_T   Ramp_IF_Iq;
    ST_RAMP_T   Ramp_IF_FREQ;

    Q32I_       _I_Q14I_IF_Est_Angle;
    
    Q32U_       _V_Q32U_IF_Angle_Err_Check_cnt;
    
    Q32U_       _O_Q32U_Switch_Flag;
    Q32I_       _O_Q14I_IF_IdRef;
    Q32I_       _O_Q14I_IF_IqRef;
    Q32I_       _O_Q14I_IF_Angle;
    Q32I_       _O_Q28I_IF_Angle_tmp;
    
    Q32I_       _P_Q14I_IF_Iq_Target;
    Q32I_       _P_Q14I_IF_Is_Min;
    Q32I_       _P_Q14I_IF_Iq_Min;
    Q32I_       _P_Q14I_IF_Angle_Err_Limit;
    Q32U_       _P_Q32U_IF_Angle_Err_Check_Count;
}ST_IF_CONTROL_T;

typedef struct
{
    ST_PID_SAT_T    PID_POWER;
    ST_PID_SAT_T    PID_FREQ;
    ST_PID_SAT_T    PID_WEAK;
    ST_RAMP_T       Ramp_FREQ;

    ST_CHECK        WEAK_CHECK;
    Q32U_       _O_Q32U_Weak_Flag;

    Q32I_       _I_Q14I_FREQ_Target;

    Q32I_       _V_Q14I_FREQ_IMTPA;

    Q32I_       _O_Q14I_FREQ_IdRef;
    Q32I_       _O_Q14I_FREQ_IqRef;
    
    TABLE_1D_T  TAB_FREQ_Kp_Coeff;
    TABLE_1D_T  TAB_FREQ_Ki_Coeff;
    Q32I_       _P_Q14I_FREQ_Kp;
    Q32I_       _P_Q14I_FREQ_Ki;
    Q32I_       _P_Q14I_FREQ_PowerRef;
    Q32I_       _P_Q14I_FREQ_IbusRef;
}ST_FREQ_CONTROL_T;

typedef struct
{
    ST_PID_SAT_T    PID_Id;
    ST_PID_SAT_T    PID_Iq;
    
    Q32I_       _I_Q14I_IdRef;
    Q32I_       _I_Q14I_IqRef;
}ST_CURRENT_CONTROL_T;


/**********************************************************************************************
Function: MCFOC_Offset_Check_Init_T
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Offset_Check_Init_T(ST_MCFOC_OFFSET_T* pOFFSET);

/**********************************************************************************************
Function: MCFOC_Offset_Check_Three_T
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCFOC_Offset_Check_Three_T(ST_MCFOC_OFFSET_T* pOFFSET, ST_PMSM_ELEC_T* pPMSMe);

/**********************************************************************************************
Function: MCFOC_Offset_Check_One_T
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCFOC_Offset_Check_One_T(ST_MCFOC_OFFSET_T* pOFFSET, ST_PMSM_ELEC_T* pPMSMe);

/**********************************************************************************************
Function: MCFOC_ALIGN_Init_T
Description: ALIGN初始化
Input: 无
Output: 无
Input_Output: ALIGN控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ALIGN_Init_T(ST_ALIGN_CONTROL_T* pALIGN);

/**********************************************************************************************
Function: MCFOC_ALIGN_SpeedLoop_T
Description: ALIGN速度环控制函数
Input: 无
Output: 无
Input_Output: ALIGN控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ALIGN_SpeedLoop_T(ST_ALIGN_CONTROL_T* pALIGN);

/**********************************************************************************************
Function: MCFOC_ALIGN_CurrentLoop_T
Description: ALIGN电流环中断控制函数
Input: 无
Output: 无
Input_Output: ALIGN控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ALIGN_CurrentLoop_T(ST_ALIGN_CONTROL_T* pALIGN);

/**********************************************************************************************
Function: MCFOC_IF_Init_T
Description: IF初始化
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_IF_Init_T(ST_IF_CONTROL_T* pIF);

/**********************************************************************************************
Function: MCFOC_IF_SpeedLoop_T
Description: IF开环控制函数
Input: 无
Output: 无
Input_Output: IF控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_IF_SpeedLoop_T(ST_IF_CONTROL_T* pIF, ST_PMSM_ELEC_T* pPMSMe);

/**********************************************************************************************
Function: MCFOC_IF_CurrentLoop_T
Description: IF电流环中断控制函数
Input: 无
Output: 无
Input_Output: IF控制指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_IF_CurrentLoop_T(ST_IF_CONTROL_T* pIF, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa);

/**********************************************************************************************
Function: MCFOC_SpeedLoop_Init_T
Description: 移相SVPWM
Input: 无
Output: 无
Input_Output: 速度环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SpeedLoop_Init_T(ST_FREQ_CONTROL_T* pFREQ);

/**********************************************************************************************
Function: MCFOC_SpeedLoop_T
Description: 速度环控制
Input: 无
Output: 无
Input_Output: 速度环控制指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SpeedLoop_T(ST_FREQ_CONTROL_T* pFREQ, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa);

/**********************************************************************************************
Function: MCFOC_CurrentLoop_Init_T
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_CurrentLoop_Init_T(ST_CURRENT_CONTROL_T* pCURRENT);

/**********************************************************************************************
Function: MCFOC_CurrentLoop_T
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_CurrentLoop_T(ST_CURRENT_CONTROL_T* pCURRENT, ST_PMSM_ELEC_T* pPMSMe);


#endif /* MCFOC_LOOP_T_H */
