/*
*     File Name :                        mcfoc_pmsm_t
*     Library/Module Name :              mcfoc_t
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC电机参数
*/


#ifndef MCFOC_PMSM_T_H
#define MCFOC_PMSM_T_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_angle_t.h"
#include "math_filter_t.h"
#include "math_ramp_t.h"
#include "math_table_t.h"
#include "math_check.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef struct
{
    ST_MEAN_T   Mean_Freq;
    ST_MEAN_T   Mean_Vbus;
    ST_MEAN_T   Mean_Ibus;
    ST_MEAN_T   Mean_Id;
    ST_MEAN_T   Mean_Iq;
    ST_MEAN_T   Mean_Ud;
    ST_MEAN_T   Mean_Uq;
    ST_MEAN_T   Mean_Es;
    
    ST_MAX_T    Max_Ia;
    ST_MAX_T    Max_Ib;
    ST_MAX_T    Max_Ic;
    
    ST_MEAN_T   Mean_Ibus_10ms;
    ST_MEAN_T   Mean_Is_1000ms;
}ST_PMSM_FILTER_T;

typedef struct
{
    Q32I_       I_Q00I_DIR_Target;
    Q32I_       I_Q14I_Ibus;
    
    Q32I_       I_Q12I_Ia_Data;
    Q32I_       I_Q12I_Ib_Data;
    Q32I_       I_Q12I_Ic_Data;
    Q32I_       I_Q12I_Ia_Offset;
    Q32I_       I_Q12I_Ib_Offset;
    Q32I_       I_Q12I_Ic_Offset;
    
    Q32I_       I_Q12I_Ishunt_1_Data;
    Q32I_       I_Q12I_Ishunt_2_Data;
    Q32I_       I_Q12I_Ishunt_Offset;
    
    Q32I_       I_Q14I_Ishunt[3];
    Q32I_       V_Q14I_Ia;
    Q32I_       V_Q14I_Ib;
    Q32I_       V_Q14I_Ic;
    Q32I_       V_Q14I_Ialfa;
    Q32I_       V_Q14I_Ibeta;
    Q32I_       V_Q14I_Ualfa;
    Q32I_       V_Q14I_Ubeta;
    
    ST_TRIG_T   TG_Triangle_Est;
    ST_TRIG_T   TG_Triangle_Comp;
    ST_TRIG_T   TG_Triangle_Pre;
    
    Q32I_       V_Q14I_Sin_Real;
    Q32I_       V_Q14I_Cos_Real;
    Q32I_       V_Q14I_Id_Real;
    Q32I_       V_Q14I_Iq_Real;
    Q32I_       V_Q14I_Ud_Real;
    Q32I_       V_Q14I_Uq_Real;
    
    Q32I_       V_Q14I_Sin_Pre;
    Q32I_       V_Q14I_Cos_Pre;
    Q32I_       V_Q14I_Ia_Pre;
    Q32I_       V_Q14I_Ib_Pre;
    Q32I_       V_Q14I_Ic_Pre;
    Q32I_       V_Q14I_Ualfa_Pre;
    Q32I_       V_Q14I_Ubeta_Pre;
    
    Q32I_       O_Q14I_Freq;
    Q32I_       O_Q14I_Vbus;
    Q32I_       O_Q14I_Is;
    Q32I_       O_Q14I_Us;
    Q32I_       O_Q14I_Es;
    Q32I_       O_Q14I_One_Over_Vbus;
    Q32I_       O_Q14I_Modulation_Rate;
    Q32I_       O_Q14I_UsRef;
    Q32I_       O_Q14I_Ibus_10ms;
    Q32I_       O_Q14I_Is_1000ms;
    
    Q32I_       P_Q14I_Modulation_Mode;
    Q32I_       P_Q14I_UsRef_Scale;
    Q32I_       P_Q08U_Pre_Period;
}ST_PMSM_ELEC_T;

typedef struct
{
    ST_RAMP_T   Ramp_PWM_FREQ;
    ST_CHECK    PWM_FREQ_CHECK;
    Q32U_       O_Q32U_Low_PWM_Flag;

    Q32I_       O_Q14I_Rs;
    Q32I_       O_Q14I_Ld;
    Q32I_       O_Q14I_Lq;
    Q32I_       O_Q14I_Ls;
    Q32I_       O_Q14I_Flux;
    Q32I_       O_Q14I_Ts;
    
    Q32I_       O_Q14I_PWM_Freq_Coeff;
    Q32I_       O_Q14I_PWM_Period_Coeff;
    
    Q32I_       P_Q14I_Rs;
    Q32I_       P_Q14I_Ld;
    Q32I_       P_Q14I_Lq;
    Q32I_       P_Q14I_Ls;
    Q32I_       P_Q14I_Flux;
    Q32I_       P_Q14I_Ts;
    
    TABLE_1D_T  TAB_Lq_Coeff;
    Q32I_       P_Q32U_PWM_FREQ_MAX;
    Q32I_       P_Q32U_PWM_FREQ_MIN;
}ST_PMSM_PARA_T;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: MCFOC_PMSM_Para_Init_T
Description: 电机参数初始化
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
*/
void MCFOC_PMSM_Para_Init_T(ST_PMSM_ELEC_T* pPMSMe);

/*
Function: MCFOC_PMSM_Para_Adapt_T
Description: 电机参数自适应
Input: 无
Output: 无
Input_Output: PMSM信号滤波指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
*/
void MCFOC_PMSM_Para_Adapt_T(ST_PMSM_FILTER_T* pPMSMf, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa);

/*
Function: MCFOC_PMSM_Clark_T
Description: Clark坐标变换函数a
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_PMSM_Clark_T(ST_PMSM_ELEC_T* pPMSMe);

/*
Function: MCFOC_PMSM_Park_T
Description: Park坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_PMSM_Park_T(ST_PMSM_ELEC_T* pPMSMe);

/*
Function: MCFOC_PMSM_Ipark_T
Description: Ipark坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_PMSM_Ipark_T(ST_PMSM_ELEC_T* pPMSMe);

/*
Function: MCFOC_PMSM_Iclark_T
Description: IClark坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_PMSM_Iclark_T(ST_PMSM_ELEC_T* pPMSMe);


#endif /* MCFOC_PMSM_T_H */
