/*
*     File Name :                        mcfoc_loop_f
*     Library/Module Name :              mcfoc_f
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC偏置自学习，IF，电流，转速闭环模块
*/


#ifndef MCFOC_LOOP_F_H
#define MCFOC_LOOP_F_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_check.h"
#include "math_angle_f.h"
#include "math_filter_f.h"
#include "math_pid_f.h"
#include "math_ramp_f.h"
#include "mcfoc_pmsm_f.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef enum
{
    ING,
    SUCS,
    FAIL,
}EM_FLAG_STATE;

typedef struct
{
    Q32I_       I_Q12I_Ia_Data;
    Q32I_       I_Q12I_Ib_Data;
    Q32I_       I_Q12I_Ic_Data;
    Q32I_       I_Q12I_Ishunt_Data;
    
    Q32I_       V_Q12I_Ia_Offset;
    Q32I_       V_Q12I_Ib_Offset;
    Q32I_       V_Q12I_Ic_Offset;
    Q32I_       V_Q12I_Ishunt_Offset;

    Q32U_       V_Q32U_Offset_Check_cnt;
    
    Q32I_       P_Q12U_Offset_Max;
    Q32I_       P_Q12U_Offset_Min;
    Q32U_       P_Q16U_Offset_Check_Count;
}ST_MCFOC_OFFSET_F;

typedef struct
{
    ST_RAMP_F   Ramp_Align_Id;
    ST_RAMP_F   Ramp_Align_Angle;
    
    Q32U_       V_Q32U_Align_Check_cnt;

    Q32U_       O_Q32U_Stand_Flag;
    float       O_F_Align_IdRef;
    float       O_F_Align_Angle;

    Q32U_       P_Q32U_Align_Check_Count;
}ST_ALIGN_CONTROL_F;

typedef struct
{
    ST_HPF_F        FL_Active_Power;
    ST_PID_POS_F    PID_Reactive_Power;
    
    ST_RAMP_F   Ramp_IF_Iq;
    ST_RAMP_F   Ramp_IF_FREQ;
    
    float       I_F_IF_Est_Angle;
    
    float       V_F_We_Comp_tmp;
    Q32U_       V_Q32U_IF_Angle_Err_Check_cnt;
    
    Q32U_       O_Q32U_Switch_Flag;
    float       O_F_IF_IdRef;
    float       O_F_IF_IqRef;
    float       O_F_IF_Angle;
    
    float       P_F_IF_Freq_Add_Step0;
    float       P_F_IF_Freq_Add_Step1;
    float       P_F_IF_Freq_Add_Step2;
    float       P_F_IF_Freq_TL1;
    float       P_F_IF_Freq_TL2;
    
    float       P_F_IF_Angle_Err_Limit;
    float       P_F_IF_Q_Coeff;
    Q32U_       P_Q32U_IF_Angle_Err_Check_Count;
}ST_IF_CONTROL_F;

typedef struct
{
    ST_PID_SAT_F    PID_POWER;
    ST_PID_SAT_F    PID_FREQ;
    ST_PID_SAT_F    PID_WEAK;
    ST_RAMP_F       Ramp_FREQ;
    
    ST_CHECK        WEAK_CHECK;
    Q32U_       O_Q32U_Weak_Flag;
    
    float       I_F_FREQ_Target;
    
    float       V_F_FREQ_IMTPA;
    
    float       O_F_FREQ_IdRef;
    float       O_F_FREQ_IqRef;
    
    TABLE_1D_F  TAB_FREQ_Kp_Coeff;
    TABLE_1D_F  TAB_FREQ_Ki_Coeff;
    float       P_F_FREQ_Kp;
    float       P_F_FREQ_Ki;
    float       P_F_FREQ_PowerRef;
    float       P_F_FREQ_IbusRef;
}ST_FREQ_CONTROL_F;

typedef struct
{
    ST_PID_SAT_F    PID_Id;
    ST_PID_SAT_F    PID_Iq;
    
    float       I_F_IdRef;
    float       I_F_IqRef;
}ST_CURRENT_CONTROL_F;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: MCFOC_Offset_Check_Init_F
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针
Return: 无
Author: CJYS
*/
void MCFOC_Offset_Check_Init_F(ST_MCFOC_OFFSET_F* pOFFSET);

/*
Function: MCFOC_Offset_Check_Three_F
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针，PMSM电信号指针
Return: 无
Author: CJYS
*/
EM_FLAG_STATE MCFOC_Offset_Check_Three_F(ST_MCFOC_OFFSET_F* pOFFSET, ST_PMSM_ELEC_F* pPMSMe);

/*
Function: MCFOC_Offset_Check_One_F
Description: 偏置检测计算
Input: 无
Output: 无
Input_Output: 偏置检测指针，PMSM电信号指针
Return: 无
Author: CJYS
*/
EM_FLAG_STATE MCFOC_Offset_Check_One_F(ST_MCFOC_OFFSET_F* pOFFSET, ST_PMSM_ELEC_F* pPMSMe);

/*
Function: MCFOC_ALIGN_Init_F
Description: ALIGN初始化
Input: 无
Output: 无
Input_Output: ALIGN控制指针
Return: 无
Author: CJYS
*/
void MCFOC_ALIGN_Init_F(ST_ALIGN_CONTROL_F* pALIGN);

/*
Function: MCFOC_ALIGN_SpeedLoop_F
Description: ALIGN速度环控制函数
Input: 无
Output: 无
Input_Output: ALIGN控制指针
Return: 无
Author: CJYS
*/
void MCFOC_ALIGN_SpeedLoop_F(ST_ALIGN_CONTROL_F* pALIGN);

/*
Function: MCFOC_ALIGN_CurrentLoop_F
Description: ALIGN电流环中断控制函数
Input: 无
Output: 无
Input_Output: ALIGN控制指针
Return: 无
Author: CJYS
*/
void MCFOC_ALIGN_CurrentLoop_F(ST_ALIGN_CONTROL_F* pALIGN);

/*
Function: MCFOC_IF_Init_F
Description: IF初始化
Input: 无
Output: 无
Input_Output: IF控制指针
Return: 无
Author: CJYS
*/
void MCFOC_IF_Init_F(ST_IF_CONTROL_F* pIF);

/*
Function: MCFOC_IF_SpeedLoop_F
Description: IF开环控制函数
Input: 无
Output: 无
Input_Output: IF控制指针，PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_IF_SpeedLoop_F(ST_IF_CONTROL_F* pIF, ST_PMSM_ELEC_F* pPMSMe);

/*
Function: MCFOC_IF_CurrentLoop_F
Description: IF电流环中断控制函数
Input: 无
Output: 无
Input_Output: IF控制指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
*/
void MCFOC_IF_CurrentLoop_F(ST_IF_CONTROL_F* pIF, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa);

/*
Function: MCFOC_SpeedLoop_Init_F
Description: 移相SVPWM
Input: 无
Output: 无
Input_Output: 速度环控制指针
Return: 无
Author: CJYS
*/
void MCFOC_SpeedLoop_Init_F(ST_FREQ_CONTROL_F* pFREQ);

/*
Function: MCFOC_SpeedLoop_F
Description: 速度环控制
Input: 无
Output: 无
Input_Output: 速度环控制指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
*/
void MCFOC_SpeedLoop_F(ST_FREQ_CONTROL_F* pFREQ, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa);

/*
Function: MCFOC_CurrentLoop_Init_F
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针
Return: 无
Author: CJYS
*/
void MCFOC_CurrentLoop_Init_F(ST_CURRENT_CONTROL_F* pCURRENT);

/*
Function: MCFOC_CurrentLoop_F
Description: 电流环控制
Input: 无
Output: 无
Input_Output: 电流环控制指针，PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_CurrentLoop_F(ST_CURRENT_CONTROL_F* pCURRENT, ST_PMSM_ELEC_F* pPMSMe);


#endif /* MCFOC_LOOP_F_H */
