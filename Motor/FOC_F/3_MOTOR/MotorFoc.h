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
    ST_RAMP_F       Ramp_Iq;
    ST_RAMP_F       Ramp_SRAD;
    ST_RAMP_F       Ramp_AngleERR;
    
    float       _I_F_DIR_Target;
    float       _I_F_AngleEst;
    
    float       _O_F_Angle;

    float       _P_F_Ts;
    float       _P_F_AngleERRLimit;
}ST_IF_CONTROL_F;

typedef struct
{
    ST_RAMP_F       Ramp_Vq;
    ST_RAMP_F       Ramp_SRAD;
    ST_RAMP_F       Ramp_AngleERR;

    float       _I_F_DIR_Target;
    float       _I_F_AngleEst;
    
    float       _O_F_Angle;
    float       _P_F_Ts;
    float       _P_F_AngleERRLimit;
}ST_VF_CONTROL_F;

typedef struct
{
    ST_TRIG_F   TG_Triangle;
    
    float       _I_F_Vbus;
    float       _I_F_One_Over_Vbus;
    float       _I_F_Ia;
    float       _I_F_Ib;
    float       _I_F_Ic;
    float       _I_F_Ud;
    float       _I_F_Uq;
    
    float       _I_F_Ia_Data;
    float       _I_F_Ib_Data;
    float       _I_F_Ic_Data;
    float       _I_F_Ia_Offset;
    float       _I_F_Ib_Offset;
    float       _I_F_Ic_Offset;
    
    Q08U_       _O_Q08U_Sector; 
    float       _O_F_Ialfa;
    float       _O_F_Ibeta;
    float       _O_F_Id;
    float       _O_F_Iq;
    float       _O_F_Ualfa;
    float       _O_F_Ubeta;
     
    float       _O_F_Ta;
    float       _O_F_Tb;
    float       _O_F_Tc;
    
    float       _P_F_MaxDuty;
    float       _P_F_MinDuty;
    float       _P_F_ADCSampleDuty;
    
    
    float       _I_F_Ishunt[3];
    
    float       _I_F_Ishunt_1_Data;
    float       _I_F_Ishunt_2_Data;
    float       _I_F_Ishunt_1_Offset;
    float       _I_F_Ishunt_2_Offset;
    
    float       _O_F_TaUp;
    float       _O_F_TbUp;
    float       _O_F_TcUp;
    float       _O_F_TaDn;
    float       _O_F_TbDn;
    float       _O_F_TcDn;
    
    float       _O_F_ADCTrigTime1;
    float       _O_F_ADCTrigTime2;
}ST_SVPWM_CONTROL_F;

typedef struct
{
    ST_PID_POS_F    PID_SRAD;
    ST_PID_POS_F    PID_WEAK;
    ST_RAMP_F       Ramp_SRAD;
    
    float       _I_F_DIR_Target;
    float       _I_F_SRAD_Target;
    float       _I_F_SRAD;
    float       _I_F_Vbus;
    float       _I_F_Ud;
    float       _I_F_Uq;

    float       _O_F_DIR_Set;
    float       _O_F_IdRef;
    float       _O_F_IqRef;
    
    float       _P_F_SRAD_Max;
    float       _P_F_SRAD_Min;
}ST_SRAD_CONTROL_F;

typedef struct
{
    ST_PID_POS_F    PID_Id;
    ST_PID_POS_F    PID_Iq;
    
    float       _I_F_Vbus;
    float       _I_F_IdRef;
    float       _I_F_IqRef;
    float       _I_F_Id;
    float       _I_F_Iq;
    
    float       _V_F_Vsd;
    float       _V_F_Vsq;  
    
    float       _O_F_Ud;
    float       _O_F_Uq;
                               
    float       _P_F_VsScale;
}ST_CURRENT_CONTROL_F;

/**********************************************************************************************
Function: MotorFoc_IF_Init_F
Description: IF初始化
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_IF_Init_F(ST_IF_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_IF_OPEN_F
Description: IF开环控制函数
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_IF_OPEN_F(ST_IF_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_IF_CLOSE_F
Description: IF闭环控制函数
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_IF_CLOSE_F(ST_IF_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_IF_CURRENT_F
Description: IF电流环中断控制函数
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_IF_CURRENT_F(ST_IF_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_VF_Init_F
Description: VF初始化
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_VF_Init_F(ST_VF_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_VF_OPEN_F
Description: VF开环控制函数
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_VF_OPEN_F(ST_VF_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_VF_CLOSE_F
Description: VF闭环控制函数
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_VF_CLOSE_F(ST_VF_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_VF_CURRENT_F
Description: VF电流环中断控制函数
Input: 无
Output: 无
Input_Output: VF控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_VF_CURRENT_F(ST_VF_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_Clark_F
Description: Clark坐标变换函数
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_Clark_F(ST_SVPWM_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_Park_F
Description: Park坐标变换函数
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_Park_F(ST_SVPWM_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_Ipark_F
Description: Ipark坐标变换函数
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_Ipark_F(ST_SVPWM_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_SVPWM_ThreeShunt_F
Description: 常规SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_SVPWM_ThreeShunt_F(ST_SVPWM_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_OneShunt_Cal_F
Description: 单电阻采样电流查表
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_OneShunt_Cal_F(ST_SVPWM_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_SVPWM_OneShunt_F
Description: 移相SVPWM
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_SVPWM_OneShunt_F(ST_SVPWM_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_SRAD_Init_F
Description: 移相SVPWM
Input: 无
Output: 无
Input_Output: 速度环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_SRAD_Init_F(ST_SRAD_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_SRAD_Loop_F
Description: 速度环控制
Input: 无
Output: 无
Input_Output: 速度环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorFoc_SRAD_Loop_F(ST_SRAD_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_Current_Init_F
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_Current_Init_F(ST_CURRENT_CONTROL_F* pCTRL);

/**********************************************************************************************
Function: MotorFoc_Current_Loop_F
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func void MotorFoc_Current_Loop_F(ST_CURRENT_CONTROL_F* pCTRL);

#endif /* MotorState_H */
