/**************************************************************************************************
*     File Name :                        MCFOC_LOOP_F.h
*     Library/Module Name :              MCFOC_F
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC算法头文件
**************************************************************************************************/

#ifndef MCFOC_LOOP_F_H
#define MCFOC_LOOP_F_H


#include "MATH_CHECK.h"
#include "MATH_ANGLE_F.h"
#include "MATH_LPF_F.h"
#include "MATH_PID_F.h"
#include "MATH_RAMP_F.h"
#include "MCFOC_PMSM_F.h"


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
}ST_MCFOC_OFFSET_F;

typedef struct
{
    ST_RAMP_F   Ramp_Align_Id;
    ST_RAMP_F   Ramp_Align_Angle;
    
    Q32U_       _V_Q32U_Align_Check_cnt;

    Q32U_       _O_Q32U_Stand_Flag;
    float       _O_F_Align_IdRef;
    float       _O_F_Align_Angle;

    Q32U_       _P_Q32U_Align_Check_Count;
}ST_ALIGN_CONTROL_F;

typedef struct
{
    ST_RAMP_F   Ramp_IF_Iq;
    ST_RAMP_F   Ramp_IF_FREQ;

    float       _I_F_IF_Est_Angle;
    
    Q32U_       _V_Q32U_IF_Angle_Err_Check_cnt;
    
    Q32U_       _O_Q32U_Switch_Flag;
    float       _O_F_IF_IdRef;
    float       _O_F_IF_IqRef;
    float       _O_F_IF_Angle;

    float       _P_F_IF_Iq_Target;
    float       _P_F_IF_Is_Min;
    float       _P_F_IF_Iq_Min;
    float       _P_F_IF_Angle_Err_Limit;
    Q32U_       _P_Q32U_IF_Angle_Err_Check_Count;
}ST_IF_CONTROL_F;

typedef struct
{
    ST_PID_SAT_F    PID_POWER;
    ST_PID_SAT_F    PID_FREQ;
    ST_PID_SAT_F    PID_WEAK;
    ST_RAMP_F       Ramp_FREQ;

    ST_CHECK        WEAK_CHECK;
    Q32U_       _O_Q32U_Weak_Flag;

    float       _I_F_FREQ_Target;

    float       _V_F_FREQ_IMTPA;

    float       _O_F_FREQ_IdRef;
    float       _O_F_FREQ_IqRef;
    
    TABLE_1D_F  TAB_FREQ_Kp_Coeff;
    TABLE_1D_F  TAB_FREQ_Ki_Coeff;
    float       _P_F_FREQ_Kp;
    float       _P_F_FREQ_Ki;
    float       _P_F_FREQ_PowerRef;
    float       _P_F_FREQ_IbusRef;
}ST_FREQ_CONTROL_F;

typedef struct
{
    ST_PID_SAT_F    PID_Id;
    ST_PID_SAT_F    PID_Iq;
    
    float       _I_F_IdRef;
    float       _I_F_IqRef;
}ST_CURRENT_CONTROL_F;


/**********************************************************************************************
Function: MCFOC_Offset_Check_Init_F
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Offset_Check_Init_F(ST_MCFOC_OFFSET_F* pOFFSET);

/**********************************************************************************************
Function: MCFOC_Offset_Check_Three_F
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCFOC_Offset_Check_Three_F(ST_MCFOC_OFFSET_F* pOFFSET, ST_PMSM_ELEC_F* pPMSMe);

/**********************************************************************************************
Function: MCFOC_Offset_Check_One_F
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
EM_FLAG_STATE MCFOC_Offset_Check_One_F(ST_MCFOC_OFFSET_F* pOFFSET, ST_PMSM_ELEC_F* pPMSMe);

/**********************************************************************************************
Function: MCFOC_ALIGN_Init_F
Description: ALIGN初始化
Input: 无
Output: 无
Input_Output: ALIGN控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ALIGN_Init_F(ST_ALIGN_CONTROL_F* pALIGN);

/**********************************************************************************************
Function: MCFOC_ALIGN_SpeedLoop_F
Description: ALIGN速度环控制函数
Input: 无
Output: 无
Input_Output: ALIGN控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ALIGN_SpeedLoop_F(ST_ALIGN_CONTROL_F* pALIGN);

/**********************************************************************************************
Function: MCFOC_ALIGN_CurrentLoop_F
Description: ALIGN电流环中断控制函数
Input: 无
Output: 无
Input_Output: ALIGN控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_ALIGN_CurrentLoop_F(ST_ALIGN_CONTROL_F* pALIGN);

/**********************************************************************************************
Function: MCFOC_IF_Init_F
Description: IF初始化
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_IF_Init_F(ST_IF_CONTROL_F* pIF);

/**********************************************************************************************
Function: MCFOC_IF_SpeedLoop_F
Description: IF开环控制函数
Input: 无
Output: 无
Input_Output: IF控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_IF_SpeedLoop_F(ST_IF_CONTROL_F* pIF, ST_PMSM_ELEC_F* pPMSMe);

/**********************************************************************************************
Function: MCFOC_IF_CurrentLoop_F
Description: IF电流环中断控制函数
Input: 无
Output: 无
Input_Output: IF控制指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_IF_CurrentLoop_F(ST_IF_CONTROL_F* pIF, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa);

/**********************************************************************************************
Function: MCFOC_SpeedLoop_Init_F
Description: 移相SVPWM
Input: 无
Output: 无
Input_Output: 速度环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SpeedLoop_Init_F(ST_FREQ_CONTROL_F* pFREQ);

/**********************************************************************************************
Function: MCFOC_SpeedLoop_F
Description: 速度环控制
Input: 无
Output: 无
Input_Output: 速度环控制指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_SpeedLoop_F(ST_FREQ_CONTROL_F* pFREQ, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa);

/**********************************************************************************************
Function: MCFOC_CurrentLoop_Init_F
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_CurrentLoop_Init_F(ST_CURRENT_CONTROL_F* pCURRENT);

/**********************************************************************************************
Function: MCFOC_CurrentLoop_F
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_CurrentLoop_F(ST_CURRENT_CONTROL_F* pCURRENT, ST_PMSM_ELEC_F* pPMSMe);


#endif /* MCFOC_LOOP_F_H */
