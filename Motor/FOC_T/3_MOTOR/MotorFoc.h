/**************************************************************************************************
*     File Name :                        MotorFoc.h
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC算法头文件
**************************************************************************************************/
#ifndef MotorFoc_H
#define MotorFoc_H

#include "Math.h"

typedef struct
{
    ST_RAMP_T       Ramp_Iq;
    ST_RAMP_T       Ramp_SRAD;
    ST_RAMP_T       Ramp_AngleERR;
    
    Q32I_       _I_Q14I_DIR_Target;
    Q32I_       _I_Q14I_AngleEst;
    
    Q32I_       _O_Q14I_Angle;

    Q32I_       _P_Q14I_Ts;
    Q32I_       _P_Q14I_AngleERRLimit;
}ST_IF_CONTROL_T;

typedef struct
{
    ST_RAMP_T       Ramp_Vq;
    ST_RAMP_T       Ramp_SRAD;
    ST_RAMP_T       Ramp_AngleERR;

    Q32I_       _I_Q14I_DIR_Target;
    Q32I_       _I_Q14I_AngleEst;
    
    Q32I_       _O_Q14I_Angle;
    Q32I_       _P_Q14I_Ts;
    Q32I_       _P_Q14I_AngleERRLimit;
}ST_VF_CONTROL_T;

typedef struct
{
    ST_TRIG_T       TG_Triangle;
    
    Q32I_       _I_Q14I_Vbus;
    Q32I_       _I_Q14I_One_Over_Vbus;
    Q32I_       _I_Q14I_Ia;
    Q32I_       _I_Q14I_Ib;
    Q32I_       _I_Q14I_Ic;
    Q32I_       _I_Q14I_Ud;
    Q32I_       _I_Q14I_Uq;
    
    Q32I_       _I_Q14I_Ia_Data;
    Q32I_       _I_Q14I_Ib_Data;
    Q32I_       _I_Q14I_Ic_Data;
    Q32I_       _I_Q14I_Ia_Offset;
    Q32I_       _I_Q14I_Ib_Offset;
    Q32I_       _I_Q14I_Ic_Offset;
    
    Q08U_       _O_Q08U_Sector; 
    Q32I_       _O_Q14I_Ialfa;
    Q32I_       _O_Q14I_Ibeta;
    Q32I_       _O_Q14I_Id;
    Q32I_       _O_Q14I_Iq;
    Q32I_       _O_Q14I_Ualfa;
    Q32I_       _O_Q14I_Ubeta;
     
    Q32I_       _O_Q14I_Ta;
    Q32I_       _O_Q14I_Tb;
    Q32I_       _O_Q14I_Tc;
    
    Q32I_       _P_Q14I_MaxDuty;
    Q32I_       _P_Q14I_MinDuty;
    Q32I_       _P_Q14I_ADCSampleDuty;
    
    
    Q32I_       _I_Q14I_Ishunt[3];
    
    Q32I_       _I_Q14I_Ishunt_1_Data;
    Q32I_       _I_Q14I_Ishunt_2_Data;
    Q32I_       _I_Q14I_Ishunt_1_Offset;
    Q32I_       _I_Q14I_Ishunt_2_Offset;
    
    Q32I_       _O_Q14I_TaUp;
    Q32I_       _O_Q14I_TbUp;
    Q32I_       _O_Q14I_TcUp;
    Q32I_       _O_Q14I_TaDn;
    Q32I_       _O_Q14I_TbDn;
    Q32I_       _O_Q14I_TcDn;
    
    Q32I_       _O_Q14I_ADCTrigTime1;
    Q32I_       _O_Q14I_ADCTrigTime2;
}ST_SVPWM_CONTROL_T;

typedef struct
{
    ST_PID_POS_T    PID_SRAD;
    ST_PID_POS_T    PID_WEAK;
    ST_RAMP_T       Ramp_SRAD;
    ST_TRIG_T       TG_Triangle;
    
    Q32I_       _I_Q14I_DIR_Target;
    Q32I_       _I_Q14I_SRAD_Target;
    Q32I_       _I_Q14I_SRAD;
    Q32I_       _I_Q14I_Vbus;
    Q32I_       _I_Q14I_Ud;
    Q32I_       _I_Q14I_Uq;

    Q32I_       _O_Q14I_DIR_Set;
    Q32I_       _O_Q14I_IdRef;
    Q32I_       _O_Q14I_IqRef;
    
    Q32I_       _P_Q14I_SRAD_Max;
    Q32I_       _P_Q14I_SRAD_Min;
}ST_SRAD_CONTROL_T;

typedef struct
{
    ST_PID_POS_T    PID_Id;
    ST_PID_POS_T    PID_Iq;
    
    Q32I_       _I_Q14I_Vbus;
    Q32I_       _I_Q14I_IdRef;
    Q32I_       _I_Q14I_IqRef;
    Q32I_       _I_Q14I_Id;
    Q32I_       _I_Q14I_Iq;
    
    Q32I_       _V_Q14I_Vsd;
    Q32I_       _V_Q14I_Vsq;  
    
    Q32I_       _O_Q14I_Ud;
    Q32I_       _O_Q14I_Uq;
                               
    Q32I_       _P_Q14I_VsScale;
}ST_CURRENT_CONTROL_T;

/**********************************************************************************************
Function: MotorFoc_IF_Init_T
Description: IF初始化
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_IF_Init_T(ST_IF_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_IF_OPEN_T
Description: IF开环控制函数
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_IF_OPEN_T(ST_IF_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_IF_CLOSE_T
Description: IF闭环控制函数
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_IF_CLOSE_T(ST_IF_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_IF_CURRENT_T
Description: IF电流环中断控制函数
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_IF_CURRENT_T(ST_IF_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_VF_Init_T
Description: VF初始化
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_VF_Init_T(ST_VF_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_VF_OPEN_T
Description: VF开环控制函数
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_VF_OPEN_T(ST_VF_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_VF_CLOSE_T
Description: VF闭环控制函数
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_VF_CLOSE_T(ST_VF_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_VF_CURRENT_T
Description: VF电流环中断控制函数
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_VF_CURRENT_T(ST_VF_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_Clark_T
Description: Clark坐标变换函数
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_Clark_T(ST_SVPWM_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_Park_T
Description: Park坐标变换函数
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_Park_T(ST_SVPWM_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_Ipark_T
Description: Ipark坐标变换函数
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_Ipark_T(ST_SVPWM_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_SVPWM_ThreeShunt_T
Description: 常规SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_SVPWM_ThreeShunt_T(ST_SVPWM_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_OneShunt_Cal_T
Description: 单电阻采样电流查表
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_OneShunt_Cal_T(ST_SVPWM_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_SVPWM_OneShunt_T
Description: 移相SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_SVPWM_OneShunt_T(ST_SVPWM_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_SRAD_Init_T
Description: 移相SVPWM
Input: 无
Output: 无
Input_Output: 速度环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_SRAD_Init_T(ST_SRAD_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_SRAD_Loop_T
Description: 速度环控制
Input: 无
Output: 无
Input_Output: 速度环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_SRAD_Loop_T(ST_SRAD_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_Current_Init_T
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_Current_Init_T(ST_CURRENT_CONTROL_T* pCTRL);

/**********************************************************************************************
Function: MotorFoc_Current_Loop_T
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_Current_Loop_T(ST_CURRENT_CONTROL_T* pCTRL);

#endif /* MotorState_H */
