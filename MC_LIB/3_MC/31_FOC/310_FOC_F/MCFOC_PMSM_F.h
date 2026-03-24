/**************************************************************************************************
*     File Name :                        MCFOC_PMSM_F.h
*     Library/Module Name :              MCFOC_F
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC电机参数头文件
**************************************************************************************************/

#ifndef MCFOC_PMSM_F_H
#define MCFOC_PMSM_F_H


#include "MATH_ANGLE_F.h"
#include "MATH_LPF_F.h"
#include "MATH_RAMP_F.h"
#include "MATH_TABLE_F.h"
#include "MATH_CHECK.h"


typedef struct
{
    ST_MEAN_F   Mean_Freq;
    ST_MEAN_F   Mean_Vbus;
    ST_MEAN_F   Mean_Ibus;
    ST_MEAN_F   Mean_Id;
    ST_MEAN_F   Mean_Iq;
    ST_MEAN_F   Mean_Ud;
    ST_MEAN_F   Mean_Uq;
    ST_MEAN_F   Mean_Es;
    
    ST_MAX_F    Max_Ia;
    ST_MAX_F    Max_Ib;
    ST_MAX_F    Max_Ic;
    
    ST_MEAN_F   Mean_Ibus_10ms;
    ST_MEAN_F   Mean_Is_1000ms;
}ST_PMSM_FILTER_F;

typedef struct
{
    float       _I_F_DIR_Target;
    float       _I_F_Ibus;
    
    Q32I_       _I_Q12I_Ia_Data;
    Q32I_       _I_Q12I_Ib_Data;
    Q32I_       _I_Q12I_Ic_Data;
    Q32I_       _I_Q12I_Ia_Offset;
    Q32I_       _I_Q12I_Ib_Offset;
    Q32I_       _I_Q12I_Ic_Offset;
    
    Q32I_       _I_Q12I_Ishunt_1_Data;
    Q32I_       _I_Q12I_Ishunt_2_Data;
    Q32I_       _I_Q12I_Ishunt_Offset;
    
    float       _I_F_Ishunt[3];
    float       _V_F_Ia;
    float       _V_F_Ib;
    float       _V_F_Ic;
    float       _V_F_Ialfa;
    float       _V_F_Ibeta;
    float       _V_F_Ualfa;
    float       _V_F_Ubeta;
    
    ST_TRIG_F   TG_Triangle_Est;
    ST_TRIG_F   TG_Triangle_Comp;
    ST_TRIG_F   TG_Triangle_Pre;
    
    float       _V_F_Sin_Real;
    float       _V_F_Cos_Real;
    float       _V_F_Id_Real;
    float       _V_F_Iq_Real;
    float       _V_F_Ud_Real;
    float       _V_F_Uq_Real;
    
    float       _V_F_Sin_Pre;
    float       _V_F_Cos_Pre;
    float       _V_F_Ia_Pre;
    float       _V_F_Ib_Pre;
    float       _V_F_Ic_Pre;
    float       _V_F_Ualfa_Pre;
    float       _V_F_Ubeta_Pre;
    
    float       _O_F_Freq;
    float       _O_F_Vbus;
    float       _O_F_Is;
    float       _O_F_Us;
    float       _O_F_Es;
    float       _O_F_One_Over_Vbus;
    float       _O_F_Modulation_Rate;
    float       _O_F_UsRef;
    float       _O_F_Ibus_10ms;
    float       _O_F_Is_1000ms;
    
    float       _P_F_Modulation_Mode;
    float       _P_F_UsRef_Scale;
    float       _P_F_Pre_Period;
}ST_PMSM_ELEC_F;

typedef struct
{
    ST_RAMP_F   Ramp_PWM_FREQ;
    ST_CHECK    PWM_FREQ_CHECK;
    Q32U_       _O_Q32U_Low_PWM_Flag;

    float       _O_F_Rs;
    float       _O_F_Ld;
    float       _O_F_Lq;
    float       _O_F_Ls;
    float       _O_F_Flux;
    float       _O_F_Ts;
    
    float       _O_F_PWM_Freq_Coeff;
    float       _O_F_PWM_Period_Coeff;
    
    float       _P_F_Rs;
    float       _P_F_Ld;
    float       _P_F_Lq;
    float       _P_F_Ls;
    float       _P_F_Flux;
    float       _P_F_Ts;
    
    TABLE_1D_F  TAB_Lq_Coeff;
    float       _P_F_PWM_FREQ_MAX;
    float       _P_F_PWM_FREQ_MIN;
}ST_PMSM_PARA_F;


/**********************************************************************************************
Function: MCFOC_PMSM_Para_Init_F
Description: PMSM电信号指针
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_PMSM_Para_Init_F(ST_PMSM_ELEC_F* pPMSMe);

/**********************************************************************************************
Function: MCFOC_PMSM_Para_Adapt_F
Description: 电机参数自适应
Input: 无
Output: 无
Input_Output: PMSM信号滤波指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_PMSM_Para_Adapt_F(ST_PMSM_FILTER_F* pPMSMf, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa);

/**********************************************************************************************
Function: MCFOC_Clark_F
Description: Clark坐标变换函数a
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Clark_F(ST_PMSM_ELEC_F* pPMSMe);

/**********************************************************************************************
Function: MCFOC_Park_F
Description: Park坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Park_F(ST_PMSM_ELEC_F* pPMSMe);

/**********************************************************************************************
Function: MCFOC_Ipark_F
Description: Ipark坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Ipark_F(ST_PMSM_ELEC_F* pPMSMe);

/**********************************************************************************************
Function: MCFOC_Iclark_F
Description: IClark坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_Iclark_F(ST_PMSM_ELEC_F* pPMSMe);


#endif /* MCFOC_PMSM_F_H */
